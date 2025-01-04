
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
#include <cstdlib> // free
#include <cstring> // memcpy

using std::free;
using std::memcpy;
using std::ptrdiff_t;
using std::size_t;
using std::uint8_t;

#include "blah_aligned_alloc.h"

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

static size_t SSARRAY_GET_POOL_SIZEOF(ssArray* _this, size_t nmemb);

static uint8_t* SSARRAY_POOL_TO_CHUNK_OPERATOR_INDEX(ssArray* _this, SsArrayPool* pool, size_t index);

// specifically when one side is passed by the client, in which case we have to use the unpadded sizeof
static void SSARRAY_MEMCPY_CHUNK(ssArray* _this, void* destination, void* source);

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

size_t SSARRAY_GET_POOL_SIZEOF(ssArray* _this, size_t nmemb)
  { return SsArrayGetSizeOfPool() + nmemb * (size_t)_this->sizeOf; }

uint8_t* SSARRAY_POOL_TO_CHUNK_OPERATOR_INDEX(ssArray* _this, SsArrayPool* pool, size_t index)
  { return (uint8_t*)pool + SSARRAY_GET_POOL_SIZEOF(_this, index); }

// specifically when one side is passed by the client, in which case we have to use the unpadded sizeof
void SSARRAY_MEMCPY_CHUNK(ssArray* _this, void* destination, void* source)
  { memcpy(destination, source, (size_t)_this->sizeOfRef; }

void PoolListFree(SsArrayPool* current)
{
  for(SsArrayPool* next = 0; current; current = next)
  {
    next = current->next;

    free(PoolGetUnaligned(current) );
  }
}

void PoolListReverseAndFree(SsArrayPool* current)
{
  // we want to free pools in opposite order of their allocation

  // reverse list
  SsArrayPool* previous = 0;

  for(SsArrayPool* next = 0; current; current = next)
  {
    next = current->next;
    current->next = previous;

    previous = current;
  }

  // free pools
  PoolListFree(previous);
}

ssArray* SsArrayConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize)
{
  uint8_t* result = 0;

  ssArray _this = {0};

  if(sizeOf <= 0 || minimumCapacity <= 0 || minimumCapacity > maximumCapacity || !resize)
    goto error;

  _this.resize = resize;
  _this.capacity = maximumCapacity;

  _this.sizeOfRef = sizeOf;
  _this.sizeOf = (int)SsArrayGetSizeOfChunk( (size_t)sizeOf);

  if( !SsArrayResize( &_this, (size_t)minimumCapacity) || !_this.head)
    goto error;

  // extract 'this' pointer which prefixes the first pool
  result = (uint8_t*)_this.head - (ptrdiff_t)SsArrayGetSizeOfSsArray();

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

  //_this->chunk = SSMM_CHUNK_POOL_TO_FIRSTNODE(pool)
  _this->current = pool;

  _this->numChunks = 0;
  _this->index = 0;
  _this->max = pool->num;

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
  {
    SsmmPool* pool = _this->current->next;

    //_this->chunk = SSMM_CHUNK_POOL_TO_FIRSTNODE(pool)
    _this->current = pool;

    _this->index = 0;
    _this->max += pool->num;
    
    result = true;
    
    goto error;
  }

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
  uint8_t* aligned = blah_aligned_alloc(size, &unaligned, false);

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

  result = true;

error:
  return result;
}

bool SsArrayPush(ssArray* _this, void* client) // todo
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || _this->numChunks > _this->max)
    goto error;

  if(_this->numChunks == _this->max)
  {
    if( !SsArrayResize(_this, 0) )
      goto error;
  }

  if(_this->numChunks == _this->max)
    goto error;

  // what is expected to change every call
  // _this->numChunks
  // _this->index

  if(_this->index < 0 || _this->index >= _this->current->num)
    goto error;

  // _this->index >= 0 && _this->index < _this->current->num

  // or uint8_t* chunk = (uint8_t*)_this->chunk
  chunk = SSARRAY_POOL_TO_CHUNK_OPERATOR_INDEX(_this, _this->current, _this->index);

  // move to next chunk
  //
  // or _this->chunk = (uint8_t*)_this->chunk + (ptrdiff_t)_this->sizeOf
  _this->index++;

  // _this->index > 0 && _this->index <= _this->current->num

  _this->numChunks++;

  SSARRAY_MEMCPY_CHUNK(_this, chunk, memory);

  result = true;

error:
  return result;
}

// get or set element at end of array
//
// there will be at least one element in the current pool, so we never have to
// walk backwards to the previous pool to get/set the element at the end of the
// array

bool SsArrayGet(ssArray* _this, void* client)
{
  bool result = false;

  if( !_this || !client || _this->numChunks <= 0 || _this->index <= 0)
    goto error;

  // or uint8_t* chunk = (uint8_t*)_this->chunk - (ptrdiff_t)_this->sizeOf
  uint8_t* chunk = SSARRAY_POOL_TO_CHUNK_OPERATOR_INDEX(_this, _this->current, _this->index - 1);
  
  // client <- chunk; copy from us to client
  SSARRAY_MEMCPY_CHUNK(_this, client, chunk);
  
  result = true;

error:
  return result;
}

bool SsArraySet(ssArray* _this, void* client)
{
  bool result = false;

  if( !_this || !client || _this->numChunks <= 0 || _this->index <= 0)
    goto error;

  // or uint8_t* chunk = (uint8_t*)_this->chunk - (ptrdiff_t)_this->sizeOf
  uint8_t* chunk = SSARRAY_POOL_TO_CHUNK_OPERATOR_INDEX(_this, _this->current, _this->index - 1);
  
  // chunk <- client; copy from client to us
  SSARRAY_MEMCPY_CHUNK(_this, chunk, client);
  
  result = true;

error:
  return result;
}

// get or set element at arbitrary valid index
//
// cannot append to array so index must be in the range
// 0 <= index < SsArrayNum(...)

bool SsArrayGetAt(ssArray* _this, int index, void* client)
{
  bool result = false;

  if( !_this || !client || index < 0 || index >= _this->numChunks || _this->numChunks <= 0)
    goto error;
  
  SsArrayPool pool = _this->head;

  for(int walk = 0; pool; pool = pool->next)
  {
    if(index >= walk && index < walk + pool->num)
    {
      // _this->chunk not used; _this->current, _this->index not used
      uint8_t* chunk = SSARRAY_POOL_TO_CHUNK_OPERATOR_INDEX(_this, pool, index - walk);

      // client <- chunk; copy from us to client
      SSARRAY_MEMCPY_CHUNK(_this, client, chunk);
  
      result = true;
      
      break;
    }
    
    walk += pool->num;
  }

error:
  return result;
}

bool SsArraySetAt(ssArray* _this, int index, void* client)
{
  bool result = false;

  if( !_this || !client || index < 0 || index >= _this->numChunks || _this->numChunks <= 0)
    goto error;
  
  SsArrayPool pool = _this->head;

  for(int walk = 0; pool; pool = pool->next)
  {
    if(index >= walk && index < walk + pool->num)
    {
      // _this->chunk not used; _this->current, _this->index not used
      uint8_t* chunk = SSARRAY_POOL_TO_CHUNK_OPERATOR_INDEX(_this, pool, index - walk);

      // chunk <- client; copy from client to us
      SSARRAY_MEMCPY_CHUNK(_this, chunk, client);
  
      result = true;
      
      break;
    }
    
    walk += pool->num;
  }

error:
  return result;
}

#if defined(_MSC_VER)
  #pragma warning (default: 4711)
#endif





























