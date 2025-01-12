
// ssMm.cpp
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

#define BLAH_DEBUG 0

#if BLAH_DEBUG
#include <cstdio>
using std::printf;
#endif

struct SsMmNode
{
  SsMmNode* next;
};

struct SsMmPool
{
  SsMmPool* next;

  uint32_t num;

  uint32_t index;
};

struct ssMm
{
  SsMmNode* chunk;

  SsMmPool* current;

  SsMmPool* head;
  SsMmPool* tail;

//SsMmPool** lookup;

  uint32_t numPools;
  uint32_t numChunks;

  uint32_t most;

  uint32_t max;

  uint32_t resize;
  uint32_t capacity;

  uint32_t sizeOf;

  uint32_t padding;
};

#include "ssMm_nocomments.h"

#include "blah_alloc.h"

static uint32_t SsMmAlignedOfValue(uint32_t size)
  { return (size % sizeof(void*) ) ? size + (sizeof(void*) - size % sizeof(void*) ) : size; }

static uint32_t SsMmGetSizeOfPoolHeader()
  { return SsMmAlignedOfValue(sizeof(SsMmPool) ); }

static uint32_t SsMmGetSizeOfSsMmHeader()
  { return SsMmAlignedOfValue(sizeof(ssMm) ); }

static uint32_t SsMmGetPoolSizeOf(ssMm* _this, uint32_t nmemb)
  { return SsMmGetSizeOfPoolHeader() + nmemb * _this->sizeOf; }

static uint8_t* SsMmPoolToChunkOperatorIndex(ssMm* _this, SsMmPool* pool, uint32_t index)
  { return (uint8_t*)pool + SsMmGetSizeOfPoolHeader() + index * _this->sizeOf; }

static SsMmNode* SsMmPoolToFirstChunk(SsMmPool* pool)
  { return (SsMmNode*)( (uint8_t*)pool + SsMmGetSizeOfPoolHeader() ); }

static SsMmNode* SsMmChunkToChunkSequential(ssMm* _this, SsMmNode* chunk)
  { return (SsMmNode*)( (uint8_t*)chunk + _this->sizeOf); }

static void SsMmMemcpySsMm(uint8_t* destination, ssMm* source)
  { memcpy(destination, source, sizeof(ssMm) ); }

// list was reversed before this call so we are actually walking the list backwards
static void SsMmPoolListFree(ssMm* _this, SsMmPool* current)
{
  for(SsMmPool* next = 0; current; current = next)
  {
    next = current->next;

    if(current != _this->head)
    {
      uint32_t sizeOf = SsMmGetPoolSizeOf(_this, current->num);
      BlahFree(current, sizeOf, true);
    }
  }
}

static void SsMmPoolListReverseAndFree(ssMm* _this, SsMmPool* current)
{
  SsMmPool* previous = 0;

  for(SsMmPool* next = 0; current; current = next)
  {
    next = current->next;
    current->next = previous;

    previous = current;
  }

  SsMmPoolListFree(_this, previous);
}

// ZERO

static bool SsMmResizeExistingPool(ssMm* _this)
{
  SsMmPool* pool = _this->current->next;

  _this->chunk = SsMmPoolToFirstChunk(pool);

  _this->current = pool;

  _this->max += pool->num;

  return true;
}

static bool SsMmResizeNewPool(ssMm* _this, uint32_t minimumCapacity)
{
  bool result = false;

  uint32_t diff = 0;

  uint32_t sizeOf = 0;

  uint8_t* pointer = 0;

  SsMmPool* pool = 0;

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

  sizeOf = SsMmGetPoolSizeOf(_this, diff);

  if(minimumCapacity > 0)
    sizeOf += SsMmGetSizeOfSsMmHeader();

  pointer = (uint8_t*)BlahAlloc(sizeOf, true);

  if(minimumCapacity > 0)
    pointer += SsMmGetSizeOfSsMmHeader();

  pool = (SsMmPool*)pointer;

  if( !pool)
    goto label_return;

  pool->next = 0;

  pool->num = diff;

  _this->chunk = SsMmPoolToFirstChunk(pool);

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

static bool SsMmResize(ssMm* _this, uint32_t minimum)
{
  bool result = false;

  if(_this->max >= _this->capacity)
    goto label_return;

  if(_this->current != _this->tail)
    result = SsMmResizeExistingPool(_this);
  else // if(_this->current == _this->tail)
    result = SsMmResizeNewPool(_this, minimum);

label_return:
  return result;
}

ssMm* SsMmConstruct(uint32_t sizeOf, uint32_t minimum, int64_t maximum, uint32_t resize)
{
  uint8_t* result = 0;

  ssMm _this = {0};

  if( !sizeOf || !minimum || minimum > (uint32_t)maximum || !resize)
    goto label_return;

  _this.resize = resize;
  _this.capacity = (uint32_t)maximum;

  _this.sizeOf = sizeOf;

  if( !SsMmResize( &_this, minimum) || !_this.head)
    goto label_return;

  result = (uint8_t*)_this.head - (ptrdiff_t)SsMmGetSizeOfSsMmHeader();

  SsMmMemcpySsMm(result, &_this);

label_return:
  return (ssMm*)result;
}

int64_t SsMmDestruct(ssMm** reference)
{
  bool result = false;

  ssMm* _this = 0;

  uint32_t num = 0;

  uint32_t sizeOf = 0;

  if( !reference)
    goto label_return;

  _this = reference[0];

  if( !_this)
    goto label_return;

  num = _this->numChunks;

  SsMmPoolListReverseAndFree(_this, _this->head);

  sizeOf = SsMmGetPoolSizeOf(_this, _this->head->num);
  BlahFree(_this, sizeOf + SsMmGetSizeOfSsMmHeader(), true);

  reference[0] = 0;

  result = true;

label_return:
  return result ? (int64_t)num : -1;
}

int64_t SsMmNum(ssMm* _this)
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

int64_t SsMmReset(ssMm* _this)
{
  bool result = false;

  uint32_t num = 0;

  SsMmPool* pool = 0;

  if( !_this)
    goto label_return;

  num = _this->numChunks;

  pool = _this->head;

  _this->chunk = SsMmPoolToFirstChunk(pool);

  _this->current = pool;

  _this->most = 0;
  _this->max = pool->num;

  result = true;

label_return:
  return result ? (int64_t)num : -1;
}

void* SsMmAlloc(ssMm* _this)
{
  void* result = 0;

  SsMmNode* chunk = 0;

  if( !_this || _this->numChunks > _this->max)
    goto label_return;

  if(_this->numChunks == _this->max)
  {
    if( !SsMmResize(_this, 0) )
      goto label_return;
  }

  if(_this->numChunks >= _this->max)
    goto label_return;

  chunk = _this->chunk;

  if(_this->numChunks == _this->most)
  {
    _this->chunk = SsMmChunkToChunkSequential(_this, chunk);

    _this->most++;
  }
  else
  {
    _this->chunk = chunk->next;
  }

  _this->numChunks++;

  result = chunk;

label_return:
  return result;
}

bool SsMmFree(ssMm* _this, void** client)
{
  bool result = false;

  SsMmNode* chunk = 0;

  if( !_this || !client || !client[0] || !_this->numChunks)
    goto label_return;

  chunk = (SsMmNode*)client[0];

  _this->numChunks--;

  chunk->next = _this->chunk;
  _this->chunk = chunk;

  client[0] = 0;

  result = true;

label_return:
  return result;
}
