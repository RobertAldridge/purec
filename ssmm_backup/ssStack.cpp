
// ssStack.cpp
// Robert Aldridge, code
// Robert Aldridge and Charlie Burns, design

#include "ssStack.h"

#include <cstdio>
using std::printf;

struct SsStackPool
{
  SsStackPool* previous;
  SsStackPool* next;

  //uint8_t* alloc;
  int unaligned;

  int num;

  // uint8_t chunk[]
};

struct ssStack
{
  SsStackPool* current;

  SsStackPool* head;
  SsStackPool* tail;

  int numPools;

  int numChunks;
  int index;
  int max;

  int counter;

  int resize;
  int capacity;

  int sizeOfRef;
  int sizeOf;

  int padding;
};

#include <cstddef> // ptrdiff_t, size_t
#include <cstdint> // uint8_t
#include <cstdlib> // malloc, free
#include <cstring> // memcpy

#include <new> // bad_alloc
using std::bad_alloc;
using std::free;
using std::malloc;
using std::memcpy;
using std::ptrdiff_t;
using std::size_t;
using std::uint8_t;

// ~9,000,000 terabytes is limit for addressing via int64_t

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// alignment is typically sizeof(void*)
// result is either size if already aligned, otherwise returns the minimum value larger than size that is aligned
static size_t ALIGNEDOFVALUE(size_t size);

// only for node header
static size_t SsStackGetSizeOfNode();

// only for pool header
static size_t SsStackGetSizeOfPool();

// only for ssStack header
static size_t SsStackGetSizeOfSsStack();

// returns entire chunk size (node header + client data)
static size_t SsStackGetSizeOfChunk(size_t sizeOf);

static void PoolSetUnaligned(SsStackPool* pool, uint8_t* unaligned);
static uint8_t* PoolGetUnaligned(SsStackPool* pool);

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

static size_t SSSTACK_GET_POOL_SIZEOF(ssStack* _this, size_t nmemb);

static uint8_t* SSSTACK_POOL_TO_CHUNK_OPERATOR_INDEX(ssStack* _this, SsStackPool* pool, size_t index);

// specifically when one side is passed by the client, in which case we have to use the unpadded sizeof
static void SSSTACK_MEMCPY_CHUNK(ssStack* _this, void* destination, void* source);

// when you're forced to use a compiler/runtime that claims to conform yet
// doesn't implement aligned_alloc (*cough* microsoft)
//   void* aligned_alloc(size_t alignment, size_t size)
//
// in this case assume alignment is sizeof(void*)
static uint8_t* cstandard_aligned_alloc(size_t size, uint8_t** unalignedRef/*unaligned;ptr*/);

static void PoolListWalk(SsStackPool* head, bool doFree);
static void PoolListReverseAndFree(SsStackPool* head);

// ssStack* SsStackConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize);

// returns the number of elements previously in the stack or -1 on error
// int SsStackDestruct(ssStack** reference/*_this*/);

// int SsStackNum(ssStack* _this);

// returns the number of nodes previously held by client or -1 on error
// int SsStackReset(ssStack* _this);

static bool SsStackResize(ssStack* _this, size_t minimumCapacity);

// bool SsStackPush(ssStack* _this, void* memory/*chunk*/);

/*bool SsStackGet(ssStack* _this, void* chunk) todo*/

// bool SsStackPop(ssStack* _this, void* memory/*chunk*/);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define INTEGER_MAX(lhs, rhs) (lhs >= rhs ? lhs : rhs)

//#define SSSTACK_GET_CHUNK_PADDED_SIZEOF(_this) \
//  (size_t)_this->sizeOf

//#define SSSTACK_GET_CHUNK_UNPADDED_SIZEOF(_this) \
//  (size_t)_this->sizeOfRef

size_t ALIGNEDOFVALUE(size_t size)
  { return (size % sizeof(void*) ) ? size + (sizeof(void*) - size % sizeof(void*) ) : size; }

// only for node header
size_t SsStackGetSizeOfNode()
  { return 0; }

// only for pool header
size_t SsStackGetSizeOfPool()
  { return ALIGNEDOFVALUE(sizeof(SsStackPool) ); }

// only for ssStack header
size_t SsStackGetSizeOfSsStack()
  { return ALIGNEDOFVALUE(sizeof(ssStack) ); }

// returns entire chunk size (node header + client data)
size_t SsStackGetSizeOfChunk(size_t sizeOf)
  { return ALIGNEDOFVALUE(sizeOf) + SsStackGetSizeOfNode(); }

void PoolSetUnaligned(SsStackPool* pool, uint8_t* unaligned)
  { pool->unaligned = (int)( (uint8_t*)unaligned - (uint8_t*)pool); }

uint8_t* PoolGetUnaligned(SsStackPool* pool)
  { return (uint8_t*)pool + (ptrdiff_t)pool->unaligned; }

size_t MALLOCSIZEPADDED(size_t size)
  { return size + (sizeof(void*) - 1); }

uint8_t* MALLOCRETURNALIGN(uint8_t* unaligned, ptrdiff_t address)
  { return (address % sizeof(void*) ) ? unaligned + (sizeof(void*) - address % sizeof(void*) ) : unaligned; }

size_t SSSTACK_GET_POOL_SIZEOF(ssStack* _this, size_t nmemb)
  { return SsStackGetSizeOfPool() + nmemb * (size_t)_this->sizeOf; }

uint8_t* SSSTACK_POOL_TO_CHUNK_OPERATOR_INDEX(ssStack* _this, SsStackPool* pool, size_t index)
  { return (uint8_t*)pool + SSSTACK_GET_POOL_SIZEOF(_this, index); }

// specifically when one side is passed by the client, in which case we have to use the unpadded sizeof
void SSSTACK_MEMCPY_CHUNK(ssStack* _this, void* destination, void* source)
  { memcpy(destination, source, (size_t)_this->sizeOfRef; }

// when you're forced to use a compiler/runtime that claims to conform yet
// doesn't implement aligned_alloc (*cough* microsoft)
//   void* aligned_alloc(size_t alignment, size_t size)
//
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

void PoolListWalk(SsStackPool* head, bool doFree)
{
  SsStackPool* next = 0;

  for(SsStackPool* curr = head; curr; curr = next)
  {
    next = curr->next;

    if(doFree)
      free(PoolGetUnaligned(curr) );
  }
}

void PoolListReverseAndFree(SsStackPool* head)
{
  // we want to free pools in opposite order of their allocation

  // reverse list
  SsStackPool* prev = 0;
  SsStackPool* next = 0;

  for(SsStackPool* curr = head; curr; curr = next)
  {
    next = curr->next;
    curr->next = prev;

    prev = curr;
  }

  // free pools
  PoolListWalk(prev, true);
}

ssStack* SsStackConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize)
{
  uint8_t* result = 0;

  ssStack _this = {0};

  if(sizeOf <= 0 || minimumCapacity <= 0 || minimumCapacity > maximumCapacity || !resize)
    goto error;

  // _this.current = 0;

  // _this.head = 0;
  // _this.tail = 0;

  // _this.numPools = 0;

  // _this.numChunks = 0;
  // _this.index = 0;
  // _this.max = 0;

  // _this.counter = 0;

  _this.resize = resize;
  _this.capacity = maximumCapacity;

  _this.sizeOfRef = sizeOf;
  _this.sizeOf = (int)SsStackGetSizeOfChunk( (size_t)sizeOf);

  try
  {
    if( !SsStackResize( &_this, (size_t)minimumCapacity) || !_this.head)
      goto error;

    // extract 'this' pointer which prefixes the first pool
    result = (uint8_t*)_this.head - (ptrdiff_t)SsStackGetSizeOfSsStack();
  }
  catch(bad_alloc& )
  {
  }

  if( !result)
    goto error;

  // use unpadded sizeof in copy
  memcpy(result, &_this, sizeof(ssStack) );

error:
  return (ssStack*)result;
}

// returns the number of elements previously in the stack or -1 on error
int SsStackDestruct(ssStack** reference)
{
  int result = -1;
  int numChunks = 0;

  ssStack* _this = 0;

  if( !reference)
    goto error;

  _this = reference[0];

  if( !_this)
    goto error;

  numChunks = SsStackNum(_this);
  if(numChunks < 0)
    goto error;

  // free all pools
  PoolListReverseAndFree(_this->head);

  reference[0] = 0;

  result = numChunks;

error:
  return result;
}

int SsStackNum(ssStack* _this)
{
  int result = -1;

  if( !_this)
    goto error;

  result = _this->numChunks;

error:
  return result;
}

// returns the number of nodes previously held by client or -1 on error
int SsStackReset(ssStack* _this) // todo
{
  int result = -1;
  int numChunksRef = 0;

  SsStackPool* pool = 0;

  if( !_this || _this->numPools <= 0)
    goto error;

  numChunksRef = _this->numChunks;

  pool = _this->head;

  _this->current = pool;

  _this->numChunks = 0;
  _this->index = 0;

  _this->counter++;

  // no change
  // _this->head
  // _this->tail
  // _this->numPools
  // _this->max
  // _this->resize
  // _this->capacity
  // _this->sizeOfRef
  // _this->sizeOf

  result = numChunksRef;

error:
  return result;
}

bool SsStackResize(ssStack* _this, size_t minimumCapacity) // todo
{
  bool result = false;

  if( !_this || _this->numChunks != _this->max || minimumCapacity > _this->capacity)
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
    goto error;

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
    diff = (int)minimumCapacity;
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
  // resize != 0 is verified during construction of ssStack instance

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

  if( !diff)
    goto error;

  // already aligned
  size_t size = SSSTACK_GET_POOL_SIZEOF(_this, (size_t)diff);

  if(minimumCapacity > 0)
    size += SsStackGetSizeOfSsStack();

  uint8_t* unaligned = 0;
  uint8_t* aligned = cstandard_aligned_alloc(size, &unaligned);

  if(minimumCapacity > 0)
    aligned += SsStackGetSizeOfSsStack();

  SsStackPool* pool = (SsStackPool*)aligned;

  if( !pool)
    goto error;

  pool->next = 0;
  PoolSetUnaligned(pool, unaligned);
  pool->num = diff;

  _this->current = pool;

  if( !_this->head)
  {
    _this->head = pool;
  }
  else// if(_this->head)
  {
    _this->tail->next = pool;
    pool->previous = _this->tail;
  }

  _this->tail = pool;

  _this->numPools++;

  _this->index = 0;
  _this->max += diff;

  // no change
  // _this->numChunks
  // _this->counter
  // _this->resize
  // _this->capacity
  // _this->sizeOfRef
  // _this->sizeOf

  result = true;

error:
  return result;
}

bool SsStackPush(ssStack* _this, void* memory/*chunk*/) // todo
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !memory || _this->numChunks > _this->max)
    goto error;

  if(_this->numChunks == _this->max)
  {
    if( !SsStackResize(_this, 0) )
      goto error;
  }

  if(_this->numChunks == _this->max)
    goto error;

  // what is expected to occassionally change upon call
  // _this->current

  // what is expected to change every call
  // _this->numChunks
  // _this->index

  if(_this->index < 0 || _this->index >= _this->current->num)
    goto error;

  // _this->index >= 0 && _this->index < _this->current->num

  chunk = SSSTACK_POOL_TO_CHUNK_OPERATOR_INDEX(_this, _this->current, _this->index);

  // move to next chunk
  _this->index++;

  // if(_this->index < _this->current->num)
  //   move to next chunk
  // else if(_this->index >= _this->current->num)
  //   move to next pool

  // after grabbing chunk
  if(_this->index >= _this->current->num)
  {
    // move to next pool (should never be at tail since if out of space it would
    // have called resize earlier in SsStackPush call)

    if(_this->current == _this->tail)
      goto error;

    _this->current = _this->current->next;

    _this->index = 0;
  }

  // _this->index >= 0 && _this->index < _this->current->num

  _this->numChunks++;

  SSSTACK_MEMCPY_CHUNK(_this, chunk, memory);

  // no change
  // _this->head
  // _this->tail
  // _this->numPools
  // _this->max
  // _this->counter
  // _this->resize
  // _this->capacity
  // _this->sizeOfRef
  // _this->sizeOf

  result = true;

error:
  return result;
}

/*bool SsStackGet(ssStack* _this, void* chunk) todo*/

bool SsStackPop(ssStack* _this, void* memory/*chunk*/) // todo
{
  bool result = false;

  SsStackNode* chunk = 0;

  if( !_this || !memory || _this->numChunks <= 0)
    goto error;

  // what is expected to occassionally change upon call
  // _this->current

  // what is expected to change every call
  // _this->numChunks
  // _this->index

  if(_this->index < 0 || _this->index >= _this->current->num)
    goto error;

  // _this->index >= 0 && _this->index < _this->current->num

  // move to previous chunk
  _this->index--;

  // if(_this->index < 0)
  //   move to next pool
  // else if(_this->index >= 0)
  //   move to next chunk

  // before grabbing chunk
  if(_this->index < 0)
  {
    // move to previous pool (should never be at head since in that case
    // _this->numChunks would be zero)

    if(_this->current == _this->head)
      goto error;

    _this->current = _this->current->previous;

    _this->index = _this->current->num - 1;
  }

  // _this->index >= 0 && _this->index < _this->current->num

  chunk = SSSTACK_POOL_TO_CHUNK_OPERATOR_INDEX(_this, _this->current, _this->index);

  _this->numChunks--;

  SSSTACK_MEMCPY_CHUNK(_this, memory, chunk);

  // no change
  // _this->head
  // _this->tail
  // _this->numPools
  // _this->max
  // _this->counter
  // _this->resize
  // _this->capacity
  // _this->sizeOfRef
  // _this->sizeOf

  result = true;

error:
  return result;
}
