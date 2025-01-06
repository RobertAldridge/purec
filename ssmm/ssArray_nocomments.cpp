
// ssArray.cpp
// Robert Aldridge, code
// Robert Aldridge and Charlie Burns, design

#include <cstddef> // ptrdiff_t, size_t
#include <cstdint> // int32_t, uint8_t
#include <cstdlib> // free
#include <cstring> // memcpy

using std::free;
using std::int32_t;
using std::memcpy;
using std::ptrdiff_t;
using std::size_t;
using std::uint8_t;

struct SsArrayPool
{
  SsArrayPool* next;

  int32_t unaligned;

  int32_t num;
};

struct ssArray
{
  uint8_t* chunk;

  SsArrayPool* current;

  SsArrayPool* head;
  SsArrayPool* tail;

  int32_t numPools;
  int32_t numChunks;

  int32_t max;

  int32_t counter;

  int32_t resize;
  int32_t capacity;

  int32_t sizeOfRef;
  int32_t sizeOf;

  //int32_t padding;
};

#include "ssArray_nocomments.h"

#include "blah_aligned_alloc.h"

static size_t SsArrayAlignedOfValue(size_t size)
  { return (size % sizeof(void*) ) ? size + (sizeof(void*) - size % sizeof(void*) ) : size; }

static size_t SsArrayGetSizeOfPoolHeader()
  { return SsArrayAlignedOfValue(sizeof(SsArrayPool) ); }

static size_t SsArrayGetSizeOfSsArrayHeader()
  { return SsArrayAlignedOfValue(sizeof(ssArray) ); }

static size_t SsArrayGetSizeOfChunk(size_t sizeOf)
  { return SsArrayAlignedOfValue(sizeOf); }

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

static void SsArrayMemcpySsArray(uint8_t* destination, ssArray* source)
  { memcpy(destination, source, sizeof(ssArray) ); }

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
  SsArrayPool* previous = 0;

  for(SsArrayPool* next = 0; current; current = next)
  {
    next = current->next;
    current->next = previous;

    previous = current;
  }

  SsArrayPoolListFree(previous);
}

static bool SsArrayResizeExistingPool(ssArray* _this)
{
  SsArrayPool* pool = _this->current->next;

  _this->chunk = SsArrayPoolToFirstChunk(pool);

  _this->current = pool;

  _this->max += pool->num;

  return true;
}

static bool SsArrayResizeNewPool(ssArray* _this, size_t minimumCapacity)
{
  bool result = false;

  int diff = 0;

  size_t size = 0;

  uint8_t* unaligned = 0;
  uint8_t* aligned = 0;

  SsArrayPool* pool = 0;

  if(minimumCapacity > 0)
  {
    diff = (int)minimumCapacity;
  }
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
  else if(_this->resize == -1)
  {
    diff = _this->max;

    if(_this->max + diff > _this->capacity)
      diff = _this->capacity - _this->max;
  }
  else if(_this->resize > 0)
  {
    diff = _this->resize;

    if(_this->max + diff > _this->capacity)
      diff = _this->capacity - _this->max;
  }

  if( !diff)
    goto error;

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
  {
    _this->head = pool;
  }
  else// if(_this->head)
  {
    _this->tail->next = pool;
    //pool->previous = _this->tail;
  }

  _this->tail = pool;

  _this->numPools++;

  //_this->index = 0;
  _this->max += diff;

  result = true;

error:
  return result;
}

static bool SsArrayResize(ssArray* _this, size_t minimumCapacity)
{
  bool result = false;

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

  result = (uint8_t*)_this.head - (ptrdiff_t)SsArrayGetSizeOfSsArrayHeader();

  SsArrayMemcpySsArray(result, &_this);

error:
  return (ssArray*)result;
}

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

  SsArrayPoolListReverseAndFree(_this->head);

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

  //_this->index = 0;
  _this->max = pool->num;

  _this->counter++;

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

  chunk = _this->chunk;

  _this->chunk = SsArrayChunkToChunkNext(_this, _this->chunk);

  _this->numChunks++;

  SsArrayMemcpyChunk(_this, chunk, client);

  result = true;

error:
  return result;
}

bool SsArrayGet(ssArray* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || _this->numChunks <= 0)
    goto error;

  chunk = SsArrayChunkToChunkPrevious(_this, _this->chunk);

  SsArrayMemcpyChunk(_this, client, chunk);

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

  chunk = SsArrayChunkToChunkPrevious(_this, _this->chunk);

  SsArrayMemcpyChunk(_this, chunk, client);

  result = true;

error:
  return result;
}

bool SsArrayGetAt(ssArray* _this, int index, void* client)
{
  bool result = false;

  SsArrayPool* pool = 0;

  if( !_this || !client || index < 0 || index >= _this->numChunks)
    goto error;

  pool = _this->head;

  for(int walk = 0; pool; pool = pool->next)
  {
    if(index >= walk && index < walk + pool->num)
    {
      uint8_t* chunk = SsArrayPoolToChunkOperatorIndex(_this, pool, (size_t)(index - walk) );

      SsArrayMemcpyChunk(_this, client, chunk);

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

  SsArrayPool* pool = 0;

  if( !_this || !client || index < 0 || index >= _this->numChunks)
    goto error;

  pool = _this->head;

  for(int walk = 0; pool; pool = pool->next)
  {
    if(index >= walk && index < walk + pool->num)
    {
      uint8_t* chunk = SsArrayPoolToChunkOperatorIndex(_this, pool, (size_t)(index - walk) );

      SsArrayMemcpyChunk(_this, chunk, client);

      result = true;

      break;
    }

    walk += pool->num;
  }

error:
  return result;
}
