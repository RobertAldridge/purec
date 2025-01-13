
// ssArray.cpp
// Robert Aldridge, code
// Robert Aldridge and Charlie Burns, design

#include <cstddef> // ptrdiff_t, size_t
#include <cstdint> // uint8_t
#include <cstdlib> // free
#include <cstring> // memcpy

using std::free;
using std::memcpy;
using std::ptrdiff_t;
using std::size_t;
using std::uint8_t;

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
  uint8_t* chunk;

  SsArrayPool* current;

  SsArrayPool* head;
  SsArrayPool* tail;

  int numPools;

  int numChunks;
  int max;

  int counter;

  int resize;
  int capacity;

  int sizeOfRef;
  int sizeOf;
};

#include "ssArray.h"

#include "blah_aligned_alloc.h"

// ~9,000,000 terabytes is limit for addressing via int64_t

// alignment is typically sizeof(void*)
// result is either size if already aligned, otherwise returns the minimum value larger than size that is aligned
static size_t SsArrayAlignedOfValue(size_t size)
  { return (size % sizeof(void*) ) ? size + (sizeof(void*) - size % sizeof(void*) ) : size; }

// only for pool header
static size_t SsArrayGetSizeOfPoolHeader()
  { return SsArrayAlignedOfValue(sizeof(SsArrayPool) ); }

// only for ssArray header
static size_t SsArrayGetSizeOfSsArrayHeader()
  { return SsArrayAlignedOfValue(sizeof(ssArray) ); }

// returns entire chunk size (node header + client data)
//
// except if debug portion of code is stripped from file, in which case the
// entire chunk size is only the size of the client data after padding the size
// for alignment purposes
static size_t SsArrayGetSizeOfChunk(size_t sizeOf)
  { return SsArrayAlignedOfValue(sizeOf); }

// unaligned <= pool; pool->unaligned <= 0
//
// ptrDiff is either zero or negative
// ptrdiff_t ptrDiff = (uint8_t*)unaligned - (uint8_t*)pool
// pool->unaligned = (int)ptrDiff
static void SsArrayPoolSetUnaligned(SsArrayPool* pool, uint8_t* unaligned)
  { pool->unaligned = (int)( (uint8_t*)unaligned - (uint8_t*)pool); }

static uint8_t* SsArrayPoolGetUnaligned(SsArrayPool* pool)
  { return (uint8_t*)pool + (ptrdiff_t)pool->unaligned; }

static size_t SsArrayGetPoolSizeOf(ssArray* _this, size_t nmemb)
  { return SsArrayGetSizeOfPoolHeader() + nmemb * (size_t)_this->sizeOf; }

static uint8_t* SsArrayPoolToChunkOperatorIndex(ssArray* _this, SsArrayPool* pool, size_t index)
  { return (uint8_t*)pool + SsArrayGetSizeOfPoolHeader() + index * (size_t)_this->sizeOf; }

static uint8_t* SsArrayPoolToFirstChunk(SsArrayPool* pool)
  { return (uint8_t*)pool + SsArrayGetSizeOfPoolHeader(); }

static uint8_t* SsArrayChunkToChunkPrevious(ssArray* _this, uint8_t* chunk)
  {return chunk - (ptrdiff_t)_this->sizeOf; }

static uint8_t* SsArrayChunkToChunkNext(ssArray* _this, uint8_t* chunk)
  { return chunk + (size_t)_this->sizeOf; }

// specifically when one side is on the stack, in which case we have to use the unpadded sizeof
static void SsArrayMemcpySsArray(uint8_t* destination, ssArray* source)
  { memcpy(destination, source, sizeof(ssArray) ); }

// specifically when one side is passed by the client, in which case we have to use the unpadded sizeof
static void SsArrayMemcpyChunk(ssArray* _this, void* destination, void* source)
  { memcpy(destination, source, (size_t)_this->sizeOfRef); }

static void SsArrayPoolListFree(SsArrayPool* current)
{
  for(SsArrayPool* next = 0; current; current = next)
  {
    next = current->next;

    free(SsArrayPoolGetUnaligned(current) );
  }
}

static void SsArrayPoolListReverseAndFree(SsArrayPool* current)
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
  SsArrayPoolListFree(previous);
}

static bool SsArrayResizeExistingPool(ssArray* _this)
{
  bool result = false;

  SsArrayPool* pool = _this->current->next;

  _this->chunk = SsArrayPoolToFirstChunk(pool);

  _this->current = pool;

  _this->max += pool->num;

  // changed
  // _this->chunk
  // _this->current
  // _this->max

  // no change
  // _this->head
  // _this->tail
  // _this->numPools
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

static bool SsArrayResizeNewPool(ssArray* _this, size_t minimumCapacity)
{
  bool result = false;

  int diff = 0;

  size_t size = 0;

  uint8_t* unaligned = 0;
  uint8_t* aligned = 0;

  SsArrayPool* pool = 0;

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

  // _this->resize != 0; verified in SsArrayConstruct

  /*int resize;*/

  /*int capacity;*/

  if( !diff)
    goto error;

  // already aligned
  size = SsArrayGetPoolSizeOf(_this, (size_t)diff);

  if(minimumCapacity > 0)
    size += SsArrayGetSizeOfSsArrayHeader();

  aligned = blah_aligned_alloc(size, &unaligned, false);

  if(minimumCapacity > 0)
    aligned += SsArrayGetSizeOfSsArrayHeader();

  pool = (SsArrayPool*)aligned;

  if( !pool)
    goto error;

  pool->next = 0;
  SsArrayPoolSetUnaligned(pool, unaligned);
  pool->num = diff;

  _this->chunk = SsArrayPoolToFirstChunk(pool);

  _this->current = pool;

  if( !_this->head)
    _this->head = pool;
  else// if(_this->head)
    _this->tail->next = pool;

  _this->tail = pool;

  _this->numPools++;

  _this->max += diff;

  // changed
  // _this->chunk
  // _this->current
  // _this->head
  // _this->tail
  // _this->numPools
  // _this->max

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

static bool SsArrayResize(ssArray* _this, size_t minimumCapacity)
{
  bool result = false;

  // not as much an error per say, since this is expected behavior,
  // but we still return an error since caller is asking to grow and our response is to not grow
  //
  // nop if 'old capacity' >= maximumCapacity
  if(_this->max >= _this->capacity)
    goto error;

  if(_this->current != _this->tail)
    result = SsArrayResizeExistingPool(_this);
  else// if(_this->current == _this->tail)
    result = SsArrayResizeNewPool(_this, minimumCapacity);

error:
  return result;
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

  // changed
  // _this.resize
  // _this.capacity
  // _this.sizeOfRef
  // _this.sizeOf

  // no change
  // _this.chunk; set in SsArrayResize
  // _this.current; set in SsArrayResize
  // _this.head; set in SsArrayResize
  // _this.tail; set in SsArrayResize
  // _this.numPools; set in SsArrayResize
  // _this.numChunks; stays at default of zero
  // _this.max; set in SsArrayResize
  // _this.counter; stays at default of zero

  // extract 'this' pointer which prefixes the first pool
  result = (uint8_t*)_this.head - (ptrdiff_t)SsArrayGetSizeOfSsArrayHeader();

  // use unpadded sizeof in copy
  SsArrayMemcpySsArray(result, &_this);

error:
  return (ssArray*)result;
}

// returns the number of elements previously in the array or -1 on error
int SsArrayDestruct(ssArray** reference/*_this*/)
{
  int result = -1;
  int numChunks = 0;

  ssArray* _this = 0;

  if( !reference)
    goto error;

  _this = reference[0];

  if( !_this)
    goto error;

  numChunks = _this->numChunks;

  // free all pools
  //
  // last pool freed also frees SsArray header
  SsArrayPoolListReverseAndFree(_this->head);

  reference[0] = 0;

  // all data freed

  result = numChunks;

error:
  return result;
}

int SsArrayNum(ssArray* _this)
{
  int result = -1;

  if( !_this)
    goto error;

  // no change for anything in _this

  result = _this->numChunks;

error:
  return result;
}

// returns the number of nodes previously held by client or -1 on error
int SsArrayReset(ssArray* _this)
{
  int result = -1;
  int numChunksRef = 0;

  SsArrayPool* pool = 0;

  if( !_this)
    goto error;

  numChunksRef = _this->numChunks;

  pool = _this->head;

  _this->chunk = SsArrayPoolToFirstChunk(pool);

  _this->current = pool;

  _this->numChunks = 0;
  _this->max = pool->num;

  _this->counter++;

  // changed
  // _this->chunk
  // _this->current
  // _this->numChunks
  // _this->max
  // _this->counter

  // no change
  // _this->head
  // _this->tail
  // _this->numPools
  // _this->resize
  // _this->capacity
  // _this->sizeOfRef
  // _this->sizeOf

  result = numChunksRef;

error:
  return result;
}

bool SsArrayPush(ssArray* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client)
    goto error;

  if(_this->numChunks == _this->max)
  {
    if( !SsArrayResize(_this, 0) )
      goto error;
  }

  if(_this->numChunks >= _this->max)
    goto error;

  // what is expected to change every call
  // _this->chunk
  // _this->numChunks

  //if(_this->index < 0 || _this->index >= _this->current->num)
  //  goto error;

  // _this->index >= 0 && _this->index < _this->current->num

  //chunk = SsArrayPoolToChunkOperatorIndex(_this, _this->current, _this->index)
  chunk = _this->chunk;

  // move to next chunk
  //
  //_this->index++;
  _this->chunk = SsArrayChunkToChunkNext(_this, _this->chunk);

  // _this->index > 0 && _this->index <= _this->current->num

  _this->numChunks++;

  // chunk <- client; copy from client side towards our side
  SsArrayMemcpyChunk(_this, chunk, client);

  // changed
  // _this->chunk
  // _this->numChunks

  // no change
  // _this->current
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

bool SsArrayGet(ssArray* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || _this->numChunks <= 0)
    goto error;

  //uint8_t* chunk = SsArrayPoolToChunkOperatorIndex(_this, _this->current, _this->index - 1)
  chunk = SsArrayChunkToChunkPrevious(_this, _this->chunk);

  // client <- chunk; copy from our side towards client side
  SsArrayMemcpyChunk(_this, client, chunk);

  // no change for anything in _this

  result = true;

error:
  return result;
}

bool SsArraySet(ssArray* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || _this->numChunks <= 0)
    goto error;

  //uint8_t* chunk = SsArrayPoolToChunkOperatorIndex(_this, _this->current, _this->index - 1)
  chunk = SsArrayChunkToChunkPrevious(_this, _this->chunk);

  // chunk <- client; copy from client side towards our side
  SsArrayMemcpyChunk(_this, chunk, client);

  // no change for anything in _this

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

  SsArrayPool* pool = 0;

  if( !_this || !client || index < 0 || index >= _this->numChunks)
    goto error;

  pool = _this->head;

  // walk all pools to find index; for default resize behavior of 2*n the number of pools will be <= logBase2(n)
  for(int walk = 0; pool; pool = pool->next)
  {
    if(index >= walk && index < walk + pool->num)
    {
      // _this->chunk not used; _this->current, _this->index not used
      uint8_t* chunk = SsArrayPoolToChunkOperatorIndex(_this, pool, (size_t)(index - walk) );

      // client <- chunk; copy from our side towards client side
      SsArrayMemcpyChunk(_this, client, chunk);

      result = true;

      break;
    }

    walk += pool->num;
  }

  // no change for anything in _this

error:
  return result;
}

bool SsArraySetAt(ssArray* _this, int index, void* client)
{
  bool result = false;

  SsArrayPool* pool = 0;

  if( !_this || !client || index < 0 || index >= _this->numChunks)
    goto error;

  pool = _this->head;

  // walk all pools to find index; for default resize behavior of 2*n the number of pools will be <= logBase2(n)
  for(int walk = 0; pool; pool = pool->next)
  {
    if(index >= walk && index < walk + pool->num)
    {
      // _this->chunk not used; _this->current, _this->index not used
      uint8_t* chunk = SsArrayPoolToChunkOperatorIndex(_this, pool, (size_t)(index - walk) );

      // chunk <- client; copy from client side towards our side
      SsArrayMemcpyChunk(_this, chunk, client);

      result = true;

      break;
    }

    walk += pool->num;
  }

  // no change for anything in _this

error:
  return result;
}
