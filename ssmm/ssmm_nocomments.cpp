
// ssmm.cpp
// Robert Aldridge, code
// Robert Aldridge and Charlie Burns, design

#include <cstddef> // ptrdiff_t
#include <cstdint> // uint32_t, uint8_t
#include <cstring> // memcpy

using std::memcpy;
using std::ptrdiff_t;
using std::uint32_t;
using std::uint8_t;

#define BLAH_DEBUG 0

#if BLAH_DEBUG
#include <cstdio>
using std::printf;
#endif

struct SsmmNode
{
  SsmmNode* next;
};

struct SsmmPool
{
  SsmmPool* next;

  uint32_t num;

  uint32_t sizeOf;
};

struct ssmm
{
  SsmmNode* chunk;

  SsmmPool* current;

  SsmmPool* head;
  SsmmPool* tail;

  uint32_t numPools;
  uint32_t numChunks;

  uint32_t most;
  uint32_t max;

  uint32_t resize;
  uint32_t capacity;

  uint32_t sizeOf;

  uint32_t padding;
};

#include "ssmm_nocomments.h"

#include "blah_alloc.h"

static uint32_t SsmmAlignedOfValue(uint32_t size)
  { return (size % sizeof(void*) ) ? size + (sizeof(void*) - size % sizeof(void*) ) : size; }

static uint32_t SsmmGetSizeOfPoolHeader()
  { return SsmmAlignedOfValue(sizeof(SsmmPool) ); }

static uint32_t SsmmGetSizeOfSsmmHeader()
  { return SsmmAlignedOfValue(sizeof(ssmm) ); }

static uint32_t SsmmGetPoolSizeOf(ssmm* _this, uint32_t nmemb)
  { return SsmmGetSizeOfPoolHeader() + nmemb * _this->sizeOf; }

static uint8_t* SsmmPoolToChunkOperatorIndex(ssmm* _this, SsmmPool* pool, uint32_t index)
  { return (uint8_t*)pool + SsmmGetSizeOfPoolHeader() + index * _this->sizeOf; }

static SsmmNode* SsmmPoolToFirstChunk(SsmmPool* pool)
  { return (SsmmNode*)( (uint8_t*)pool + SsmmGetSizeOfPoolHeader() ); }

static SsmmNode* SsmmChunkToChunkSequential(ssmm* _this, SsmmNode* chunk)
  { return (SsmmNode*)( (uint8_t*)chunk + _this->sizeOf); }

static void SsmmMemcpySsmm(uint8_t* destination, ssmm* source)
  { memcpy(destination, source, sizeof(ssmm) ); }

// list was reversed before this call so we are actually walking the list backwards
static void SsmmPoolListFree(ssmm* _this, SsmmPool* current)
{
  for(SsmmPool* next = 0; current; current = next)
  {
    next = current->next;

    if(current != _this->head)
      BlahFree(current, current->sizeOf, true);
  }
}

static void SsmmPoolListReverseAndFree(ssmm* _this, SsmmPool* current)
{
  SsmmPool* previous = 0;

  for(SsmmPool* next = 0; current; current = next)
  {
    next = current->next;
    current->next = previous;

    previous = current;
  }

  SsmmPoolListFree(_this, previous);
}

// ZERO

static bool SsArrayResizeExistingPool(ssmm* _this)
{
  SsmmPool* pool = _this->current->next;

  _this->chunk = SsmmPoolToFirstChunk(pool);

  _this->current = pool;

  _this->max += pool->num;

  return true;
}

static bool SsmmResizeNewPool(ssmm* _this, uint32_t minimumCapacity)
{
  bool result = false;

  uint32_t diff = 0;

  uint32_t sizeOf = 0;

  uint8_t* pointer = 0;

  SsmmPool* pool = 0;

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

  sizeOf = SsmmGetPoolSizeOf(_this, diff);

  if(minimumCapacity > 0)
    sizeOf += SsmmGetSizeOfSsmmHeader();

  pointer = (uint8_t*)BlahAlloc(sizeOf, true);

  if(minimumCapacity > 0)
    pointer += SsmmGetSizeOfSsmmHeader();

  pool = (SsmmPool*)pointer;

  if( !pool)
    goto error;

  pool->sizeOf = sizeOf;

  pool->next = 0;

  pool->num = diff;

  _this->chunk = SsmmPoolToFirstChunk(pool);

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

static bool SsmmResize(ssmm* _this, uint32_t minimumCapacity)
{
  bool result = false;

  if(_this->max >= _this->capacity)
    goto error;

  if(_this->current != _this->tail)
    result = SsArrayResizeExistingPool(_this);
  else// if(_this->current == _this->tail)
    result = SsmmResizeNewPool(_this, minimumCapacity);

error:
  return result;
}

ssmm* SsmmConstruct(uint32_t sizeOf, uint32_t minimumCapacity, uint32_t maximumCapacity, uint32_t resize)
{
  uint8_t* result = 0;

  ssmm _this = {0};

  if( !sizeOf || !minimumCapacity || minimumCapacity > maximumCapacity || !resize)
    goto error;

  _this.resize = resize;
  _this.capacity = maximumCapacity;

  _this.sizeOf = sizeOf;

  if( !SsmmResize( &_this, minimumCapacity) || !_this.head)
    goto error;

  result = (uint8_t*)_this.head - (ptrdiff_t)SsmmGetSizeOfSsmmHeader();

  SsmmMemcpySsmm(result, &_this);

error:
  return (ssmm*)result;
}

bool SsmmDestruct(ssmm** reference)
{
  bool result = false;

  uint32_t numChunks = 0;

  ssmm* _this = 0;

  if( !reference)
    goto error;

  _this = reference[0];

  if( !_this)
    goto error;

  SsmmPoolListReverseAndFree(_this, _this->head);

  BlahFree(_this, _this->head->sizeOf, true);

  reference[0] = 0;

  result = true;

error:
  return result;
}

bool SsmmNum(ssmm* _this, uint32_t* num)
{
  bool result = false;

  if( !_this || !num)
    goto error;

  *num = _this->numChunks;

  result = true;

error:
  return result;
}

bool SsmmReset(ssmm* _this)
{
  bool result = false;

  uint32_t numChunks = 0;

  SsmmPool* pool = 0;

  if( !_this)
    goto error;

  pool = _this->head;

  _this->chunk = SsmmPoolToFirstChunk(pool);

  _this->current = pool;

  _this->most = 0;
  _this->max = pool->num;

  *num = numChunks;

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
    if( !SsmmResize(_this, 0) )
      goto error;
  }

  if(_this->numChunks >= _this->max)
    goto error;

  chunk = _this->chunk;

  if(_this->numChunks == _this->most)
  {
    _this->chunk = SsmmChunkToChunkSequential(_this, chunk);

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

bool SsmmFree(ssmm* _this, void** client)
{
  bool result = false;

  SsmmNode* chunk = 0;

  if( !_this || !client || !client[0] || !_this->numChunks)
    goto error;

  chunk = (SsmmNode*)client[0];

  _this->numChunks--;

  chunk->next = _this->chunk;
  _this->chunk = chunk;

  client[0] = 0;

  result = true;

error:
  return result;
}
