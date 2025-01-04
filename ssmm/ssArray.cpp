
// ssArray.cpp
// Robert Aldridge, code
// Robert Aldridge and Charlie Burns, design

#if defined(_MSC_VER)
  #pragma warning (disable: 4711)
#endif

#include "ssArray.h"

#include <cstdio>
using std::printf;

struct SsArrayPool
{
  // only need previous if supports pop/remove
  SsArrayPool* next;

  //uint8_t* alloc;
  int unaligned;

  int num;

  // uint8_t chunk[]
};

struct ssArray
{
  SsArrayPool* current;

  SsArrayPool* head;
  SsArrayPool* tail;

  int numPools;

  int numChunks;
  int index;
  int max;

  int resize;
  int capacity;

  int sizeOfRef;
  int sizeOf;
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
static size_t SsArrayGetSizeOfNode();

// only for pool header
static size_t SsArrayGetSizeOfPool();

// only for ssArray header
static size_t SsArrayGetSizeOfSsArray();

// returns entire chunk size (node header + client data)
static size_t SsArrayGetSizeOfChunk(size_t sizeOf);

static void PoolSetUnaligned(SsArrayPool* pool, uint8_t* unaligned);
static uint8_t* PoolGetUnaligned(SsArrayPool* pool);

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

static size_t SSARRAY_GET_POOL_SIZEOF(ssArray* _this, size_t nmemb);

static uint8_t* SSARRAY_POOL_TO_CHUNK_OPERATOR_INDEX(ssArray* _this, SsArrayPool* pool, size_t index);

// specifically when one side is passed by the client, in which case we have to use the unpadded sizeof
static void SSARRAY_MEMCPY_CHUNK(ssArray* _this, void* destination, void* source);

// when you're forced to use a compiler/runtime that claims to conform yet
// doesn't implement aligned_alloc (*cough* microsoft)
//   void* aligned_alloc(size_t alignment, size_t size)
//
// in this case assume alignment is sizeof(void*)
static uint8_t* cstandard_aligned_alloc(size_t size, uint8_t** unalignedRef/*unaligned;ptr*/);

static void PoolListWalk(SsArrayPool* head, bool doFree);
static void PoolListReverseAndFree(SsArrayPool* head);

// ssArray* SsArrayConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize);

// returns the number of elements previously in the array or -1 on error
// int SsArrayDestruct(ssArray** reference/*_this*/);

// int SsArrayNum(ssArray* _this);

// returns the number of nodes previously held by client or -1 on error
// int SsArrayReset(ssArray* _this);

static bool SsArrayResize(ssArray* _this, size_t minimumCapacity);

// bool SsArrayPush(ssArray* _this, void* memory/*chunk*/);

/*bool SsArrayGet(ssArray* _this, void* chunk) todo*/

// bool SsArrayPop(ssArray* _this, void* memory/*chunk*/);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define INTEGER_MAX(lhs, rhs) (lhs >= rhs ? lhs : rhs)

//#define SSARRAY_GET_CHUNK_PADDED_SIZEOF(_this) \
//  (size_t)_this->sizeOf

//#define SSARRAY_GET_CHUNK_UNPADDED_SIZEOF(_this) \
//  (size_t)_this->sizeOfRef

size_t ALIGNEDOFVALUE(size_t size)
  { return (size % sizeof(void*) ) ? size + (sizeof(void*) - size % sizeof(void*) ) : size; }

// only for node header
size_t SsArrayGetSizeOfNode()
  { return 0; }

// only for pool header
size_t SsArrayGetSizeOfPool()
  { return ALIGNEDOFVALUE(sizeof(SsArrayPool) ); }

// only for ssArray header
size_t SsArrayGetSizeOfSsArray()
  { return ALIGNEDOFVALUE(sizeof(ssArray) ); }

// returns entire chunk size (node header + client data)
size_t SsArrayGetSizeOfChunk(size_t sizeOf)
  { return ALIGNEDOFVALUE(sizeOf) + SsArrayGetSizeOfNode(); }

void PoolSetUnaligned(SsArrayPool* pool, uint8_t* unaligned)
  { pool->unaligned = (int)( (uint8_t*)unaligned - (uint8_t*)pool); }

uint8_t* PoolGetUnaligned(SsArrayPool* pool)
  { return (uint8_t*)pool + (ptrdiff_t)pool->unaligned; }

size_t MALLOCSIZEPADDED(size_t size)
  { return size + (sizeof(void*) - 1); }

uint8_t* MALLOCRETURNALIGN(uint8_t* unaligned, ptrdiff_t address)
  { return (address % sizeof(void*) ) ? unaligned + (sizeof(void*) - address % sizeof(void*) ) : unaligned; }

size_t SSARRAY_GET_POOL_SIZEOF(ssArray* _this, size_t nmemb)
  { return SsArrayGetSizeOfPool() + nmemb * (size_t)_this->sizeOf; }

uint8_t* SSARRAY_POOL_TO_CHUNK_OPERATOR_INDEX(ssArray* _this, SsArrayPool* pool, size_t index)
  { return (uint8_t*)pool + SSARRAY_GET_POOL_SIZEOF(_this, index); }

// specifically when one side is passed by the client, in which case we have to use the unpadded sizeof
void SSARRAY_MEMCPY_CHUNK(ssArray* _this, void* destination, void* source)
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

void PoolListWalk(SsArrayPool* head, bool doFree)
{
  SsArrayPool* next = 0;

  for(SsArrayPool* curr = head; curr; curr = next)
  {
    next = curr->next;

    if(doFree)
      free(PoolGetUnaligned(curr) );
  }
}

void PoolListReverseAndFree(SsArrayPool* head)
{
  // we want to free pools in opposite order of their allocation

  // reverse list
  SsArrayPool* prev = 0;
  SsArrayPool* next = 0;

  for(SsArrayPool* curr = head; curr; curr = next)
  {
    next = curr->next;
    curr->next = prev;

    prev = curr;
  }

  // free pools
  PoolListWalk(prev, true);
}

ssArray* SsArrayConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize)
{
  uint8_t* result = 0;

  ssArray _this = {0};

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
  _this.sizeOf = (int)SsArrayGetSizeOfChunk( (size_t)sizeOf);

  try
  {
    if( !SsArrayResize( &_this, (size_t)minimumCapacity) || !_this.head)
      goto error;

    // extract 'this' pointer which prefixes the first pool
    result = (uint8_t*)_this.head - (ptrdiff_t)SsArrayGetSizeOfSsArray();
  }
  catch(bad_alloc& )
  {
  }

  if( !result)
    goto error;

  // use unpadded sizeof in copy
  memcpy(result, &_this, sizeof(ssArray) );

error:
  return (ssArray*)result;
}

// returns the number of elements previously in the array or -1 on error
int SsArrayDestruct(ssArray** reference)
{
  int result = -1;
  int numChunks = 0;

  ssArray* _this = 0;

  if( !reference)
    goto error;

  _this = reference[0];

  if( !_this)
    goto error;

  numChunks = SsArrayNum(_this);
  if(numChunks < 0)
    goto error;

  // free all pools
  PoolListReverseAndFree(_this->head);

  reference[0] = 0;

  result = numChunks;

error:
  return result;
}

int SsArrayNum(ssArray* _this)
{
  int result = -1;

  if( !_this)
    goto error;

  result = _this->numChunks;

error:
  return result;
}

// returns the number of nodes previously held by client or -1 on error
int SsArrayReset(ssArray* _this) // todo
{
  int result = -1;
  int numChunksRef = 0;

  SsArrayPool* pool = 0;

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

bool SsArrayResize(ssArray* _this, size_t minimumCapacity) // todo
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
  // resize != 0 is verified during construction of ssArray instance

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
  size_t size = SSARRAY_GET_POOL_SIZEOF(_this, (size_t)diff);

  if(minimumCapacity > 0)
    size += SsArrayGetSizeOfSsArray();

  uint8_t* unaligned = 0;
  uint8_t* aligned = cstandard_aligned_alloc(size, &unaligned);

  if(minimumCapacity > 0)
    aligned += SsArrayGetSizeOfSsArray();

  SsArrayPool* pool = (SsArrayPool*)aligned;

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

bool SsArrayPush(ssArray* _this, void* memory/*chunk*/) // todo
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !memory || _this->numChunks > _this->max)
    goto error;

  if(_this->numChunks == _this->max)
  {
    if( !SsArrayResize(_this, 0) )
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

  chunk = SSARRAY_POOL_TO_CHUNK_OPERATOR_INDEX(_this, _this->current, _this->index);

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
    // have called resize earlier in SsArrayPush call)

    if(_this->current == _this->tail)
      goto error;

    _this->current = _this->current->next;

    _this->index = 0;
  }

  // _this->index >= 0 && _this->index < _this->current->num

  _this->numChunks++;

  SSARRAY_MEMCPY_CHUNK(_this, chunk, memory);

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

// get or set element at end of array
//
// there will be at least one element in the current pool, so we never have to
// walk backwards to the previous pool to get/set the element at the end of the
// array

bool SsArrayGet(ssArray* _this, void* memory/*chunk*/)
{
  bool result = false;

  if( !_this || !memory || _this->numChunks <= 0 || _this->index <= 0)
    goto error;

  uint8_t* chunk = SSARRAY_POOL_TO_CHUNK_OPERATOR_INDEX(_this, _this->current, _this->index - 1);
  
  SSARRAY_MEMCPY_CHUNK(_this, memory, chunk);
  
  result = true;

error:
  return result;
}

bool SsArraySet(ssArray* _this, void* chunk)
{
}

// get or set element at arbitrary valid index
//
// cannot append to array so index must be in the range
// 0 <= index < SsArrayNum(...)

bool SsArrayGetAt(ssArray* _this, int index, void* chunk)
{
}

bool SsArraySetAt(ssArray* _this, int index, void* chunk)
{
}

#if defined(_MSC_VER)
  #pragma warning (default: 4711)
#endif





























