
// ssArray.cpp
// Robert Aldridge, code
// Robert Aldridge and Charlie Burns, design

#include <cstddef> // ptrdiff_t
#include <cstdint> // int64_t, uint32_t, uint8_t
#include <cstring> // memcpy

using std::int64_t;
using std::memcpy;
using std::ptrdiff_t;
using std::uint32_t;
using std::uint8_t;

#include "BlahAlloc.h"

struct SsArrayPool
{
  SsArrayPool* next;

  uint32_t num;

  uint32_t index;
};

struct ssArray
{
  uint8_t* chunk;

  SsArrayPool* current;

  SsArrayPool* head;
  SsArrayPool* tail;

//SsArrayPool** lookup;

  uint32_t numPools;
  uint32_t numChunks;

  uint32_t max;

  uint32_t counter;

  uint32_t resize;
  uint32_t capacity;

  uint32_t sizeOf;

  uint32_t padding;
};

#include "ssArray.h"

static uint32_t SsArrayAlignedOfValue(uint32_t size)
  { return (size % sizeof(void*) ) ? size + (sizeof(void*) - size % sizeof(void*) ) : size; }

static uint32_t SsArrayGetSizeOfPoolHeader()
  { return SsArrayAlignedOfValue(sizeof(SsArrayPool) ); }

static uint32_t SsArrayGetSizeOfSsArrayHeader()
  { return SsArrayAlignedOfValue(sizeof(ssArray) ); }

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
  { memcpy(destination, source, _this->sizeOf); }

static void SsArrayPoolListFree(ssArray* _this, SsArrayPool* current)
{
  for(SsArrayPool* next = 0; current; current = next)
  {
    next = current->next;

    if(current != _this->head)
    {
      uint32_t sizeOf = SsArrayGetPoolSizeOf(_this, current->num);
      BlahFree(current, sizeOf, true);
    }
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

// ZERO

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

  uint32_t sizeOf = 0;

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
    goto label_return;

  sizeOf = SsArrayGetPoolSizeOf(_this, diff);

  if(minimumCapacity > 0)
    sizeOf += SsArrayGetSizeOfSsArrayHeader();

  pointer = (uint8_t*)BlahAlloc(sizeOf, true);

  if(minimumCapacity > 0)
    pointer += SsArrayGetSizeOfSsArrayHeader();

  pool = (SsArrayPool*)pointer;

  if( !pool)
    goto label_return;

  pool->next = 0;

  pool->num = diff;

  _this->chunk = SsArrayPoolToFirstChunk(pool);

  _this->current = pool;

  if( !_this->head)
    _this->head = pool;
  else // if(_this->head)
    _this->tail->next = pool;

  _this->tail = pool;

  _this->numPools++;

  _this->max += diff;

  result = true;

label_return:
  return result;
}

static bool SsArrayResize(ssArray* _this, uint32_t minimum)
{
  bool result = false;

  if(_this->max >= _this->capacity)
    goto label_return;

  if(_this->current != _this->tail)
    result = SsArrayResizeExistingPool(_this);
  else // if(_this->current == _this->tail)
    result = SsArrayResizeNewPool(_this, minimum);

label_return:
  return result;
}

ssArray* SsArrayConstruct(uint32_t sizeOf, uint32_t minimum, int64_t maximum, uint32_t resize/*, bool lookup*/)
{
  uint8_t* result = 0;

  ssArray _this = {0};

  if( !sizeOf || !minimum || minimum > (uint32_t)maximum || !resize)
    goto label_return;

  _this.resize = resize;
  _this.capacity = (uint32_t)maximum;

  _this.sizeOf = sizeOf;

  if( !SsArrayResize( &_this, minimum) || !_this.head)
    goto label_return;

  result = (uint8_t*)_this.head - (ptrdiff_t)SsArrayGetSizeOfSsArrayHeader();

  SsArrayMemcpySsArray(result, &_this);

#if 0
  if(lookup)
  {
    SsArrayPool* current = 0;

    _this->lookup = (SsArrayPool**)BlahAlloc(sizeof(SsArrayPool*) * _this->numPools, true);
    if( !_this->lookup)
      goto label_return;

    current = _this->head;

    for(int index = 0; index < _this->numPools; index++)
    {
      _this->lookup[index] = current;
      current = current->next;
    }
  }
#endif

label_return:
  return (ssArray*)result;
}

int64_t SsArrayDestruct(ssArray** reference)
{
  bool result = false;

  ssArray* _this = 0;

  uint32_t num = 0;

  uint32_t sizeOf = 0;

  if( !reference)
    goto label_return;

  _this = reference[0];

  if( !_this)
    goto label_return;

  num = _this->numChunks;

#if 0
  if(_this->lookup)
  {
    BlahFree(_this->lookup, sizeof(SsArrayPool*) * _this->numPools, true);
    _this->lookup = 0;
  }
#endif

  SsArrayPoolListReverseAndFree(_this, _this->head);

  sizeOf = SsArrayGetPoolSizeOf(_this, _this->head->num);
  BlahFree(_this, sizeOf + SsArrayGetSizeOfSsArrayHeader(), true);

  reference[0] = 0;

  result = true;

label_return:
  return result ? (int64_t)num : -1;
}

int64_t SsArrayNum(ssArray* _this)
{
  bool result = false;

  uint32_t num = 0;

  if( !_this)
    goto label_return;

  num = _this->numChunks;

  result = true;

label_return:
  return result ? (int64_t)num : -1;
}

int64_t SsArrayReset(ssArray* _this)
{
  bool result = false;

  uint32_t num = 0;

  if( !_this)
    goto label_return;

  num = _this->numChunks;

  _this->current = _this->head;

  _this->chunk = SsArrayPoolToFirstChunk(_this->current);

  this->numChunks = 0;

  _this->max = pool->num;

  _this->counter++;

  result = true;

label_return:
  return result ? (int64_t)num : -1;
}

bool SsArrayPush(ssArray* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client)
    goto label_return;

  if(_this->numChunks == _this->max)
  {
    if( !SsArrayResize(_this, 0) )
      goto label_return;
  }

  if(_this->numChunks >= _this->max)
    goto label_return;

  chunk = _this->chunk;

  _this->chunk = SsArrayChunkToChunkNext(_this, _this->chunk);

  _this->numChunks++;

  SsArrayMemcpyChunk(_this, chunk, client);

  result = true;

label_return:
  return result;
}

bool SsArrayGet(ssArray* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || !_this->numChunks)
    goto label_return;

  chunk = SsArrayChunkToChunkPrevious(_this, _this->chunk);

  SsArrayMemcpyChunk(_this, client, chunk);

  result = true;

label_return:
  return result;
}

bool SsArraySet(ssArray* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || !_this->numChunks)
    goto label_return;

  chunk = SsArrayChunkToChunkPrevious(_this, _this->chunk);

  SsArrayMemcpyChunk(_this, chunk, client);

  result = true;

label_return:
  return result;
}

bool SsArrayGetAt(ssArray* _this, uint32_t index, void* client)
{
  bool result = false;

  if( !_this || !client || index >= _this->numChunks)
    goto label_return;

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

label_return:
  return result;
}

bool SsArraySetAt(ssArray* _this, uint32_t index, void* client)
{
  bool result = false;

  if( !_this || !client || index >= _this->numChunks)
    goto label_return;

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

label_return:
  return result;
}
