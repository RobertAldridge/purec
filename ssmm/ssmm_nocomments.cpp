
// ssmm.cpp
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

  int32_t unaligned;

  int32_t num;
};

struct ssmm
{
  SsmmNode* chunk;

  SsmmPool* current;

  SsmmPool* head;
  SsmmPool* tail;

  int32_t numPools;
  int32_t numChunks;

  int32_t most;
  int32_t max;

  int32_t resize;
  int32_t capacity;

  int32_t sizeOf;

  int32_t padding;
};

#include "ssmm_nocomments.h"

#include "blah_aligned_alloc.h"

static size_t SsmmAlignedOfValue(size_t size)
  { return (size % sizeof(void*) ) ? size + (sizeof(void*) - size % sizeof(void*) ) : size; }

static size_t SsmmGetSizeOfPoolHeader()
  { return SsmmAlignedOfValue(sizeof(SsmmPool) ); }

static size_t SsmmGetSizeOfSsmmHeader()
  { return SsmmAlignedOfValue(sizeof(ssmm) ); }

static size_t SsmmGetSizeOfChunk(size_t sizeOf)
  { return SsmmAlignedOfValue(sizeOf); }

static void SsmmPoolSetUnaligned(SsmmPool* pool, uint8_t* unaligned)
  { pool->unaligned = (int)( (uint8_t*)unaligned - (uint8_t*)pool); }

static uint8_t* SsmmPoolGetUnaligned(SsmmPool* pool)
  { return (uint8_t*)pool + (ptrdiff_t)pool->unaligned; }

static size_t SsmmGetPoolSizeOf(ssmm* _this, size_t nmemb)
  { return SsmmGetSizeOfPoolHeader() + nmemb * (size_t)_this->sizeOf; }

static uint8_t* SsmmPoolToChunkOperatorIndex(ssmm* _this, SsmmPool* pool, size_t index)
  { return (uint8_t*)pool + SsmmGetSizeOfPoolHeader() + index * (size_t)_this->sizeOf; }

SsmmNode* SsmmPoolToFirstChunk(SsmmPool* pool)
  { return (SsmmNode*)( (uint8_t*)pool + SsmmGetSizeOfPoolHeader() ); }

SsmmNode* SsmmChunkToChunkSequential(ssmm* _this, SsmmNode* chunk)
  { return (SsmmNode*)( (uint8_t*)chunk + (size_t)_this->sizeOf); }

static void SsmmMemcpySsmm(uint8_t* destination, ssmm* source)
  { memcpy(destination, source, sizeof(ssmm) ); }

// list was reversed before this call so we are actually walking the list backwards
void SsmmPoolListFree(SsmmPool* current)
{
  for(SsmmPool* next = 0; current; current = next)
  {
    next = current->next;

    blah_free_aligned_sized(SsmmPoolGetUnaligned(current), 0, 0);
  }
}

void SsmmPoolListReverseAndFree(SsmmPool* current)
{
  SsmmPool* previous = 0;

  for(SsmmPool* next = 0; current; current = next)
  {
    next = current->next;
    current->next = previous;

    previous = current;
  }

  SsmmPoolListFree(previous);
}

static bool SsArrayResizeExistingPool(ssmm* _this)
{
  SsmmPool* pool = _this->current->next;

  _this->chunk = SsmmPoolToFirstChunk(pool);

  _this->current = pool;

  _this->max += pool->num;

  return true;
}

static bool SsmmResizeNewPool(ssmm* _this, size_t minimumCapacity)
{
  bool result = false;

  int diff = 0;

  size_t size = 0;

  uint8_t* unaligned = 0;
  uint8_t* aligned = 0;

  SsmmPool* pool = 0;

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

  size = SsmmGetPoolSizeOf(_this, (size_t)diff);

  if(minimumCapacity > 0)
    size += SsmmGetSizeOfSsmmHeader();

  aligned = blah_aligned_alloc(size, &unaligned, true);

  if(minimumCapacity > 0)
    aligned += SsmmGetSizeOfSsmmHeader();

  pool = (SsmmPool*)aligned;

  if( !pool)
    goto error;

  pool->next = 0;

  SsmmPoolSetUnaligned(pool, unaligned);
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

static bool SsmmResize(ssmm* _this, size_t minimumCapacity)
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

ssmm* SsmmConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize)
{
  uint8_t* result = 0;

  ssmm _this = {0};

  if(sizeOf <= 0 || minimumCapacity <= 0 || minimumCapacity > maximumCapacity || !resize)
    goto error;

  _this.resize = resize;
  _this.capacity = maximumCapacity;

  _this.sizeOf = (int)SsmmGetSizeOfChunk( (size_t)sizeOf);

  if( !SsmmResize( &_this, (size_t)minimumCapacity) || !_this.head)
    goto error;

  result = (uint8_t*)_this.head - (ptrdiff_t)SsmmGetSizeOfSsmmHeader();

  SsmmMemcpySsmm(result, &_this);

error:
  return (ssmm*)result;
}

int SsmmDestruct(ssmm** reference/*_this*/)
{
  int result = -1;
  int numChunks = 0;

  ssmm* _this = 0;

  if( !reference)
    goto error;

  _this = reference[0];

  if( !_this)
    goto error;

  numChunks = _this->numChunks;

  SsmmPoolListReverseAndFree(_this->head);

  reference[0] = 0;

  result = numChunks;

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
  return result;
}

int SsmmReset(ssmm* _this)
{
  int result = -1;
  int numChunksRef = 0;

  SsmmPool* pool = 0;

  if( !_this)
    goto error;

  numChunksRef = _this->numChunks;

  pool = _this->head;

  _this->chunk = SsmmPoolToFirstChunk(pool);

  _this->current = pool;

  _this->numChunks = 0;

  _this->most = 0;
  _this->max = pool->num;

  result = numChunksRef;

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

  if( !_this || !client || !client[0] || _this->numChunks <= 0)
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
