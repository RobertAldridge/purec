
// ssmm.cpp
// Robert Aldridge, code
// Robert Aldridge and Charlie Burns, design

#if defined(_MSC_VER)
  #pragma warning (disable: 4711)
#endif

#include "ssmm.h"

#include <cstdio>
using std::printf;

struct SsmmNode
{
  SsmmNode* next;
};

struct SsmmPool
{
  SsmmPool* next;
  //uint8_t* alloc;
  int unaligned;
  int num;
  //uint8_t chunk[]
};

struct ssmm
{
  SsmmNode* chunk;

  SsmmPool* current;

  SsmmPool* head;
  SsmmPool* tail;

  int numPools;

  int numChunks;
  int most;
  int max;

  int resize;
  int capacity;

  int sizeOf;

  int padding;
};

#include <cstddef> // ptrdiff_t, size_t
#include <cstdint> // uint8_t
#include <cstdlib> // malloc, free
#include <cstring> // memset

#include <new> // bad_alloc
using std::bad_alloc;
using std::free;
using std::malloc;
using std::memset;
using std::ptrdiff_t;
using std::size_t;
using std::uint8_t;

// ~9,000,000 terabytes is limit for addressing via int64_t

#define SSMM_GET_SIZEOF(_this) (size_t)_this->sizeOf

static void PoolSetUnaligned(SsmmPool* pool, uint8_t* unaligned);
static uint8_t* PoolGetUnaligned(SsmmPool* pool);

// alignment is typically sizeof(void*)
// result is either size if already aligned, otherwise returns the minimum value larger than size that is aligned
static size_t ALIGNEDOFVALUE(size_t size);

// alignment is typically sizeof(void*)
// assumes size is already a multiple of alignment
// pass result of MALLOCSIZEPADDED as size parameter to malloc to allow for post-malloc alignment
static size_t MALLOCSIZEPADDED(size_t size);

// alignment is typically sizeof(void*)
// assumes the parameter passed to malloc is sufficiently padded
// ptr is of type uint8_t*
// 'address' is of type ptrdiff_t, assigned to the value (uint8_t*)ptr - (uint8_t*)0
// pass return value of malloc to MALLOCRETURNALIGN (pass stored value not the literal malloc call)
static uint8_t* MALLOCRETURNALIGN(uint8_t* unaligned, ptrdiff_t address);

static SsmmNode* SSMM_CHUNK_POOL_TO_FIRSTNODE(SsmmPool* pool);
static SsmmNode* SSMM_CHUNK_NODE_TO_NODE_SEQUENTIAL(ssmm* _this, SsmmNode* node);

static uint8_t* cstandard_aligned_alloc(size_t size, uint8_t** unalignedRef/*unaligned;ptr*/);
static size_t SsmmGetSizeOfNode();
static size_t SsmmGetSizeOfPool();
static size_t SsmmGetSizeOfSsmm();
static size_t SsmmGetSizeOfChunk(size_t sizeOf);
static void SsmmMemset(ssmm* _this);

static void PoolListWalk(SsmmPool* head, bool doFree);
static void PoolListReverseAndFree(SsmmPool* head);

// initial capacity must be larger than zero
//
// you can delay the overhead of creating a pool by setting isTentative to true.  in that case, the first pool will be
// created upon first call to SsmmAlloc.  note that in this case calls to SsmmSetResize will fail until after the first
// call to SsmmAlloc
static bool SsmmSsmm(ssmm* _this, size_t sizeOf, size_t minimumCapacity, size_t maximumCapacity, int resize);

// ssmm* SsmmConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize)
// int SsmmDestruct(ssmm** _thisRef/*_this*/)
// int SsmmNum(ssmm* _this)

/**/ bool SsmmSetResize(ssmm* _this, int resize);

// int SsmmReset(ssmm* _this)

static bool SsmmResize(ssmm* _this, int minimumCapacity);

// void* SsmmAlloc(ssmm* _this)
// bool SsmmFree(ssmm* _this, void** memory/*chunk*/)

//#define INTEGER_MAX(lhs, rhs) (lhs >= rhs ? lhs : rhs)

void PoolSetUnaligned(SsmmPool* pool, uint8_t* unaligned) { pool->unaligned = (int)( (uint8_t*)unaligned - (uint8_t*)pool); }
uint8_t* PoolGetUnaligned(SsmmPool* pool) { return (uint8_t*)pool + (ptrdiff_t)pool->unaligned; }

size_t ALIGNEDOFVALUE(size_t size) { return (size % sizeof(void*) ) ? size + (sizeof(void*) - size % sizeof(void*) ) : size; }

size_t MALLOCSIZEPADDED(size_t size) { return size + (sizeof(void*) - 1); }

uint8_t* MALLOCRETURNALIGN(uint8_t* unaligned, ptrdiff_t address) { return (address % sizeof(void*) ) ? unaligned + (sizeof(void*) - address % sizeof(void*) ) : unaligned; }

SsmmNode* SSMM_CHUNK_POOL_TO_FIRSTNODE(SsmmPool* pool) { return (SsmmNode*)( (uint8_t*)pool + SsmmGetSizeOfPool() ); }

SsmmNode* SSMM_CHUNK_NODE_TO_NODE_SEQUENTIAL(ssmm* _this, SsmmNode* node) { return (SsmmNode*)( (uint8_t*)node + SSMM_GET_SIZEOF(_this) ); }

// when you're forced to use a compiler/runtime that claims to conform yet doesn't implement aligned_alloc (*cough* microsoft)
//   void* aligned_alloc(size_t alignment, size_t size)

// in this case assume alignment is sizeof(void*)
uint8_t* cstandard_aligned_alloc(size_t size, uint8_t** unalignedRef/*unaligned;ptr*/)
{
  uint8_t* aligned = 0;
  uint8_t* unaligned = 0;

  ptrdiff_t address = 0;

  if( !size || !unalignedRef)
    goto labelReturn;

  // fail if size is not a multiple of alignment
  if(size % sizeof(void*) )
    goto labelReturn;

  size = MALLOCSIZEPADDED(size);

  unaligned = (uint8_t*)malloc(size);
  if( !unaligned)
    goto labelReturn;

  *unalignedRef = unaligned;

  address = (uint8_t*)unaligned - (uint8_t*)0;

  aligned = MALLOCRETURNALIGN(unaligned, address);

labelReturn:

  return aligned;
}

// only for node header
size_t SsmmGetSizeOfNode()
{
  return 0;
}

// only for pool header
size_t SsmmGetSizeOfPool()
{
  size_t result = ALIGNEDOFVALUE(sizeof(SsmmPool) );
  return result;
}

// only for ssmm header
size_t SsmmGetSizeOfSsmm()
{
  size_t result = ALIGNEDOFVALUE(sizeof(ssmm) );
  return result;
}

// returns entire chunk size (node header + client data)
size_t SsmmGetSizeOfChunk(size_t sizeOf)
{
  size_t result = ALIGNEDOFVALUE(sizeOf);

  return result + SsmmGetSizeOfNode();
}

void SsmmMemset(ssmm* _this)
{
  memset(_this, 0, SsmmGetSizeOfSsmm() );
}

void PoolListWalk(SsmmPool* head, bool doFree)
{
  SsmmPool* next = 0;

  for(SsmmPool* curr = head; curr; curr = next)
  {
    next = curr->next;

    if(doFree)
      free(PoolGetUnaligned(curr) );
  }
}

void PoolListReverseAndFree(SsmmPool* head)
{
  // we want to free pools in opposite order of their allocation

  // reverse list
  SsmmPool* prev = 0;
  SsmmPool* next = 0;

  for(SsmmPool* curr = head; curr; curr = next)
  {
    next = curr->next;
    curr->next = prev;

    prev = curr;
  }

  // free pools
  PoolListWalk(prev, true);
}

bool SsmmSsmm(ssmm* _this, size_t sizeOf, size_t minimumCapacity, size_t maximumCapacity, int resize)
{
  bool result = false;

  // _this checked in SsmmConstruct

  // _this memset in SsmmConstruct

  if( !_this || sizeOf <= 0 || minimumCapacity <= 0 || minimumCapacity > maximumCapacity || !resize)
    goto error;

  sizeOf = SsmmGetSizeOfChunk(sizeOf);

  _this->numChunks = 0;
  _this->most = 0;

  _this->sizeOf = (int)sizeOf;

  _this->chunk = 0;
  _this->current = 0;
  _this->head = 0;
  _this->tail = 0;

  _this->max = 0;
  
  _this->resize = resize;
  
  _this->capacity = (int)maximumCapacity;

  if( !SsmmResize(_this, (int)minimumCapacity) )
    goto error;

  result = true;

error:
  return result;
}

ssmm* SsmmConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize)
{
  bool result = false;

  ssmm* _this = 0;

  ssmm _thisRef = {0};

  if(sizeOf <= 0 || minimumCapacity <= 0 || minimumCapacity > maximumCapacity || !resize)
    goto error;

  try
  {
    result = SsmmSsmm( &_thisRef, (size_t)sizeOf, (size_t)minimumCapacity, (size_t)maximumCapacity, resize);
  }
  catch(bad_alloc& )
  {
  }

  if( !result)
    goto error;

  // extract 'this' pointer which prefixes the first pool
  _this = (ssmm*)( (uint8_t*)_thisRef.head - (ptrdiff_t)SsmmGetSizeOfSsmm() );

  memcpy(_this, &_thisRef, sizeof(ssmm) );

error:
  return _this;
}

// returns the number of nodes previously held by client or -1 on error
int SsmmDestruct(ssmm** _this)
{
  int result = -1;
  int numRef = 0;

  ssmm _thisRef = {0};

  if( !_this || !_this[0] )
    goto error;

  memcpy( &_thisRef, _this[0], sizeof(ssmm) );

  numRef = SsmmNum( &_thisRef);
  if(numRef < 0)
    goto error;

  SsmmMemset(_this[0] );

  // free all pools
  PoolListReverseAndFree(_thisRef.head);

  _this[0] = 0;

  result = numRef;

error:
  return result;
}

int SsmmNum(ssmm* _this)
{
  int result = -1;

  if( !_this)
    goto error;

  result = _this->numChunks;

error:
  return (int)result;
}

bool SsmmSetResize(ssmm* _this, int resize)
{
  bool result = false;

  if( !_this || resize < -1 || _this->resize < -1)
    goto error;

  _this->resize = resize;

  result = true;

error:
  return result;
}

// returns the number of nodes previously held by client or -1 on error
int SsmmReset(ssmm* _this)
{
  int result = -1;
  int numChunksRef = 0;

  SsmmPool* pool = 0;

  if( !_this || _this->numPools <= 0)
    goto error;

  numChunksRef = _this->numChunks;

  _this->numChunks = 0;
  _this->most = 0;

  pool = _this->head;

  _this->chunk = SSMM_CHUNK_POOL_TO_FIRSTNODE(pool);

  _this->current = pool;

  _this->max = pool->num;

  // no change
  // _this->head
  // _this->tail
  // _this->alloc/unaligned
  // _this->numPools
  // _this->resize
  // _this->capacity
  // _this->sizeOf
  // (_this->padding)

  result = numChunksRef;

error:
  return result;
}

bool SsmmResize(ssmm* _this, int minimumCapacity)
{
  bool result = false;

  if( !_this || _this->numChunks != _this->max || minimumCapacity < 0 || minimumCapacity > _this->capacity)
    goto error;

  if(minimumCapacity > 0 && _this->numPools > 0)
    goto error;

  // not as much an error per say, since this is expected behavior,
  // but we still return an error since caller is asking to grow and our response is to not grow
  //
  // nop if 'old capacity' >= maximumCapacity
  if(_this->max >= _this->capacity)
    goto error;

  if(_this->current != _this->tail)
  {
    SsmmPool* pool = _this->current->next;

    _this->chunk = SSMM_CHUNK_POOL_TO_FIRSTNODE(pool);

    _this->current = pool;

    _this->max += pool->num;

    // no change
    // _this->head
    // _this->tail
    // _this->alloc/unaligned
    // _this->numPools
    // _this->numChunks
    // _this->most
    // _this->resize
    // _this->capacity
    // _this->sizeOf
    // (_this->padding)
  }
  else
  {
    int diff = 0;

    // start is initial capacity
    // must be greater than zero
    // minimumCapacity <= maximumCapacity
    /*int minimumCapacity;*/

    // 'initial capacity * sizeof(client type)' must be a reasonable size to pass to malloc

    // first pool grow() behavior
    // 'new capacity' == minimumCapacity
    if(minimumCapacity > 0)
    {
      diff = minimumCapacity;
    }

    // non-first grow() behavior, if resize < -1
    //
    // 'new capacity' == 2 * 'old capacity',
    // if 'old capacity' <= abs(resize + 1) and 2 * 'old capacity' <= maximumCapacity
    //
    // 'new capacity' == 'old capacity' + abs(resize),
    // if 'old capacity' > abs(resize + 1) and 'old capacity' + abs(resize + 1) <= maximumCapacity
    //
    // 'new capacity' == maximumCapacity,
    // if 'old capacity' > abs(resize + 1) and 'old capacity' + abs(resize + 1) > maximumCapacity
    else if(_this->resize < -1)
    {
      int resize = -_this->resize - 1;

      if(_this->max <= resize)
        diff = _this->max;
      else
        diff = resize;

      if(_this->max + diff > _this->capacity)
        diff = _this->capacity - _this->max;
    }

    // non-first grow() behavior, if resize == -1
    //
    // 'new capacity' == 2 * 'old capacity',
    // if 2 * 'old capacity' <= maximumCapacity
    //
    // 'new capacity' == maximumCapacity,
    // if 2 * 'old capacity' > maximumCapacity
    else if(_this->resize == -1)
    {
      diff = _this->max;

      if(_this->max + diff > _this->capacity)
        diff = _this->capacity - _this->max;
    }

    // resize cannot be zero.  to disable grow() set minimumCapacity and maximumCapacity to same value
    //
    // resize != 0 is verified during construction of ssmm instance

    // non-first grow() behavior, if resize > 0
    //
    // 'new capacity' == 'old capacity' + resize,
    // if 'old capacity' + resize <= maximumCapacity
    //
    // 'new capacity' == maximumCapacity,
    // if 'old capacity' + resize > maximumCapacity
    else if(_this->resize > 0)
    {
      diff = _this->resize;

      if(_this->max + diff > _this->capacity)
        diff = _this->capacity - _this->max;
    }
    else
    {
      goto error;
    }

    /*int resize;*/

    /*int capacity;*/

    // if ssmm is constructed with initial capacity of zero and resize is left
    // at default of -1 then capacity will remain at zero
    //
    // the behavior is the same as if resize is zero (whose behavior is to not
    // grow after reaching capacity)
    //
    // in this case call SsmmSetResize with an intended initial capacity > 0,
    // call SsmmAlloc once to actualize the initial capacity,
    // then call SsmmSetResize(-1) to return to default behavior
    if( !diff)
      goto error;

    // already aligned
    size_t size = SsmmGetSizeOfPool() + (size_t)diff * SSMM_GET_SIZEOF(_this);

    if(minimumCapacity > 0)
      size += SsmmGetSizeOfSsmm();

    uint8_t* unaligned = 0;
    uint8_t* aligned = cstandard_aligned_alloc(size, &unaligned);

    if(minimumCapacity > 0)
      aligned += SsmmGetSizeOfSsmm();

    SsmmPool* pool = (SsmmPool*)aligned;

    if( !pool)
      goto error;

    pool->next = 0;
    PoolSetUnaligned(pool, unaligned);
    pool->num = diff;

    _this->max += diff;

    _this->chunk = SSMM_CHUNK_POOL_TO_FIRSTNODE(pool);

    _this->current = pool;
    
    if( !_this->head)
      _this->head = pool;
    else// if(_this->head)
      _this->tail->next = pool;

    _this->tail = pool;

    _this->numPools++;

    // no change
    // _this->head
    // _this->alloc/unaligned
    // _this->numChunks
    // _this->most
    // _this->resize
    // _this->capacity
    // _this->sizeOf
    // (_this->padding)
  }

  result = true;

error:
  return result;
}

void* SsmmAlloc(ssmm* _this)
{
  void* result = 0;

  SsmmNode* chunk = 0;

  if( !_this || _this->numChunks > _this->max)
    goto error;

  if(_this->numChunks == _this->max)
  {
    if( !_this->resize)
      goto error;

    if( !SsmmResize(_this, 0) )
      goto error;
  }

  chunk = _this->chunk;

  if(_this->numChunks == _this->most)
  {
    _this->chunk = SSMM_CHUNK_NODE_TO_NODE_SEQUENTIAL(_this, chunk);

    _this->most++;
  }
  else
  {
    _this->chunk = chunk->next;
  }

  _this->numChunks++;

  result = chunk;

error:
  return result;
}

bool SsmmFree(ssmm* _this, void** memory/*chunk*/)
{
  bool result = false;

  SsmmNode* chunk = 0;

  if( !_this || !memory || !memory[0] || _this->numChunks <= 0)
    goto error;

  chunk = (SsmmNode*)memory[0];

  _this->numChunks--;

  chunk->next = _this->chunk;
  _this->chunk = chunk;

  memory[0] = 0;

  result = true;

error:
  return result;
}

#if defined(_MSC_VER)
  #pragma warning (default: 4711)
#endif
