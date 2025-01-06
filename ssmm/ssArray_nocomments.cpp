
// ssArray.cpp
// Robert Aldridge, code
// Robert Aldridge and Charlie Burns, design

#include <cstddef> // ptrdiff_t
#include <cstdint> // uint32_t, uint8_t
#include <cstring> // memcpy

using std::memcpy;
using std::ptrdiff_t;
using std::uint32_t;
using std::uint8_t;

struct SsArrayPool
{
  SsArrayPool* next;

  uint32_t num;

  uint32_t padding;
};

struct ssArray
{
  uint8_t* chunk;

  SsArrayPool* current;

  SsArrayPool* head;
  SsArrayPool* tail;

  uint32_t numPools;
  uint32_t numChunks;

  uint32_t max;

  uint32_t counter;

  uint32_t resize;
  uint32_t capacity;

  uint32_t sizeOfRef;
  uint32_t sizeOf;
};

#include "ssArray_nocomments.h"

#include "blah_aligned_alloc.h"

static uint32_t SsArrayAlignedOfValue(uint32_t size)
  { return (size % sizeof(void*) ) ? size + (sizeof(void*) - size % sizeof(void*) ) : size; }

static uint32_t SsArrayGetSizeOfPoolHeader()
  { return SsArrayAlignedOfValue(sizeof(SsArrayPool) ); }

static uint32_t SsArrayGetSizeOfSsArrayHeader()
  { return SsArrayAlignedOfValue(sizeof(ssArray) ); }

static uint32_t SsArrayGetSizeOfChunk(uint32_t sizeOf)
  { return SsArrayAlignedOfValue(sizeOf); }

static uint32_t SsArrayGetPoolSizeOf(ssArray* _this, uint32_t nmemb)
  { return SsArrayGetSizeOfPoolHeader() + nmemb * _this->sizeOf; }

static uint8_t* SsArrayPoolToChunkOperatorIndex(ssArray* _this, SsArrayPool* pool, uint32_t index)
  { return (uint8_t*)pool + SsArrayGetSizeOfPoolHeader() + index * _this->sizeOf; }

static uint8_t* SsArrayPoolToFirstChunk(SsArrayPool* pool)
  { return (uint8_t*)pool + SsArrayGetSizeOfPoolHeader(); }

static uint8_t* SsArrayChunkToChunkPrevious(ssArray* _this, uint8_t* chunk)
  { return chunk - (ptrdiff_t)_this->sizeOf; }

static uint8_t* SsArrayChunkToChunkNext(ssArray* _this, uint8_t* chunk)
  { return chunk + _this->sizeOf; }

static void SsArrayMemcpySsArray(uint8_t* destination, ssArray* source)
  { memcpy(destination, source, sizeof(ssArray) ); }

static void SsArrayMemcpyChunk(ssArray* _this, void* destination, void* source)
  { memcpy(destination, source, _this->sizeOfRef); }

static void SsArrayPoolListFree(ssArray* _this, SsArrayPool* current)
{
  for(SsArrayPool* next = 0; current; current = next)
  {
    next = current->next;

    if(current != _this->head)
      blah_free_aligned_sized(current);
  }
}

static void SsArrayPoolListReverseAndFree(ssArray* _this, SsArrayPool* current)
{
  SsArrayPool* previous = 0;

  for(SsArrayPool* next = 0; current; current = next)
  {
    next = current->next;
    current->next = previous;

    previous = current;
  }

  SsArrayPoolListFree(_this, previous);
}

static bool SsArrayResizeExistingPool(ssArray* _this)
{
  SsArrayPool* pool = _this->current->next;

  _this->chunk = SsArrayPoolToFirstChunk(pool);

  _this->current = pool;

  _this->max += pool->num;

  return true;
}

static bool SsArrayResizeNewPool(ssArray* _this, uint32_t minimumCapacity)
{
  bool result = false;

  uint32_t diff = 0;

  uint32_t size = 0;

  uint8_t* pointer = 0;

  SsArrayPool* pool = 0;

  if(minimumCapacity > 0)
    diff = minimumCapacity;
  else if(_this->max <= _this->resize)
    diff = _this->max;
  else
    diff = _this->resize;

  if(_this->max + diff > _this->capacity)
    diff = _this->capacity - _this->max;

  if( !diff)
    goto error;

  size = SsArrayGetPoolSizeOf(_this, diff);

  if(minimumCapacity > 0)
    size += SsArrayGetSizeOfSsArrayHeader();

  pointer = (uint8_t*)blah_aligned_alloc(size);

  if(minimumCapacity > 0)
    pointer += SsArrayGetSizeOfSsArrayHeader();

  pool = (SsArrayPool*)pointer;

  if( !pool)
    goto error;

  pool->next = 0;

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

  result = true;

error:
  return result;
}

static bool SsArrayResize(ssArray* _this, uint32_t minimumCapacity)
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

ssArray* SsArrayConstruct(uint32_t sizeOf, uint32_t minimumCapacity, uint32_t maximumCapacity, uint32_t resize)
{
  uint8_t* result = 0;

  ssArray _this = {0};

  if( !sizeOf || !minimumCapacity || minimumCapacity > maximumCapacity || !resize)
    goto error;

  _this.resize = resize;
  _this.capacity = maximumCapacity;

  _this.sizeOfRef = sizeOf;
  _this.sizeOf = SsArrayGetSizeOfChunk(sizeOf);

  if( !SsArrayResize( &_this, minimumCapacity) || !_this.head)
    goto error;

  result = (uint8_t*)_this.head - (ptrdiff_t)SsArrayGetSizeOfSsArrayHeader();

  SsArrayMemcpySsArray(result, &_this);

error:
  return (ssArray*)result;
}

bool SsArrayDestruct(ssArray** reference, uint32_t* num)
{
  bool result = false;

  uint32_t numChunks = 0;

  ssArray* _this = 0;

  if( !reference || !num)
    goto error;

  _this = reference[0];

  if( !_this)
    goto error;

  numChunks = _this->numChunks;

  SsArrayPoolListReverseAndFree(_this, _this->head);
  
  blah_free_aligned_sized(_this);

  reference[0] = 0;

  *num = numChunks;
  
  result = true;

error:
  return result;
}

bool SsArrayNum(ssArray* _this, uint32_t* num)
{
  bool result = false;

  if( !_this || !num)
    goto error;

  *num = _this->numChunks;
  
  result = true;

error:
  return result;
}

bool SsArrayReset(ssArray* _this, uint32_t* num)
{
  bool result = false;

  uint32_t numChunks = 0;

  SsArrayPool* pool = 0;

  if( !_this || !num)
    goto error;

  numChunks = _this->numChunks;

  pool = _this->head;

  _this->chunk = SsArrayPoolToFirstChunk(pool);

  _this->current = pool;

  _this->numChunks = 0;

  _this->max = pool->num;

  _this->counter++;

  *num = numChunks;
  
  result = true;

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

  if( !_this || !client || !_this->numChunks)
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

  if( !_this || !client || !_this->numChunks)
    goto error;

  chunk = SsArrayChunkToChunkPrevious(_this, _this->chunk);

  SsArrayMemcpyChunk(_this, chunk, client);

  result = true;

error:
  return result;
}

bool SsArrayGetAt(ssArray* _this, uint32_t index, void* client)
{
  bool result = false;

  if( !_this || !client || index >= _this->numChunks)
    goto error;

  for(SsArrayPool* pool = _this->head; pool; pool = pool->next)
  {
    if(index < pool->num)
    {
      uint8_t* chunk = SsArrayPoolToChunkOperatorIndex(_this, pool, index);

      SsArrayMemcpyChunk(_this, client, chunk);

      result = true;

      break;
    }

    if(pool->num > index)
      break;
    
    index -= pool->num;
  }

error:
  return result;
}

bool SsArraySetAt(ssArray* _this, uint32_t index, void* client)
{
  bool result = false;

  if( !_this || !client || index >= _this->numChunks)
    goto error;

  for(SsArrayPool* pool = _this->head; pool; pool = pool->next)
  {
    if(index < pool->num)
    {
      uint8_t* chunk = SsArrayPoolToChunkOperatorIndex(_this, pool, index);

      SsArrayMemcpyChunk(_this, chunk, client);

      result = true;

      break;
    }
    
    if(pool->num > index)
      break;
    
    index -= pool->num;
  }

error:
  return result;
}
