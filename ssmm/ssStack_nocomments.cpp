
// ssStack.cpp
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

#include <cstdio>
using std::printf;

struct SsStackPool
{
  SsStackPool* previous;
  SsStackPool* next;

  int32_t unaligned;

  int32_t num;
};

struct ssStack
{
  SsStackPool* current;

  SsStackPool* head;
  SsStackPool* tail;

  int32_t numPools;
  int32_t numChunks;

  int32_t index;

  int32_t max;

  int32_t counter;

  int32_t resize;
  int32_t capacity;

  int32_t sizeOfRef;
  int32_t sizeOf;

  int32_t padding;
};

#include "ssStack_nocomments.h"

#include "blah_aligned_alloc.h"

static size_t SsStackAlignedOfValue(size_t size)
  { return (size % sizeof(void*) ) ? size + (sizeof(void*) - size % sizeof(void*) ) : size; }

static size_t SsStackGetSizeOfPoolHeader()
  { return SsStackAlignedOfValue(sizeof(SsStackPool) ); }

static size_t SsStackGetSizeOfSsStackHeader()
  { return SsStackAlignedOfValue(sizeof(ssStack) ); }

static size_t SsStackGetSizeOfChunk(size_t sizeOf)
  { return SsStackAlignedOfValue(sizeOf); }

static void SsStackPoolSetUnaligned(SsStackPool* pool, uint8_t* unaligned)
  { pool->unaligned = (int)( (uint8_t*)unaligned - (uint8_t*)pool); }

static uint8_t* SsStackPoolGetUnaligned(SsStackPool* pool)
  { return (uint8_t*)pool + (ptrdiff_t)pool->unaligned; }

static size_t SsStackGetPoolSizeOf(ssStack* _this, size_t nmemb)
  { return SsStackGetSizeOfPoolHeader() + nmemb * (size_t)_this->sizeOf; }

static uint8_t* SsStackPoolToChunkOperatorIndex(ssStack* _this, SsStackPool* pool, size_t index)
  { return (uint8_t*)pool + SsStackGetSizeOfPoolHeader() + index * (size_t)_this->sizeOf; }

static void SsStackMemcpySsStack(uint8_t* destination, ssStack* source)
  { memcpy(destination, source, sizeof(ssStack) ); }

static void SsStackMemcpyChunk(ssStack* _this, void* destination, void* source)
  { memcpy(destination, source, (size_t)_this->sizeOfRef); }

// free in reverse order by walking previous from tail
static void SsStackPoolListFree(SsStackPool* current)
{
  for(SsStackPool* previous = 0; current; current = previous)
  {
    previous = current->previous;

    free(SsStackPoolGetUnaligned(current) );
  }
}

static void SsStackDebug(ssStack* _this)
{
  {
    int64_t blah = 0;
    SsStackGet(_this, &blah);
    printf(" front %i", (int)blah);
  }
  printf("\n");

  printf("get at");
  for(int index = 0; index < _this->numChunks; index++)
  {
    int64_t blah = 0;
    SsStackGetAt(_this, index, &blah);
    printf(" %i", (int)blah);
  }
  printf("\n");
}

static void SsStackDeepDebug1(ssStack* _this)
{
  SsStackPool* pool = _this->head;

  printf("num %i; ", SsStackNum(_this) );

  printf("[");
  for(int index = 0; index < pool->num; index++)
  {
    uint8_t* chunk = SsStackPoolToChunkOperatorIndex(_this, pool, (size_t)index);

    printf("%i", (int)( *(int64_t*)chunk) );

    if(index != pool->num - 1)
      printf(" ");
  }
  printf("]");

  pool = pool->next;

  while(pool)
  {
    printf("[");
    for(int index = 0; index < pool->num; index++)
    {
      uint8_t* chunk = SsStackPoolToChunkOperatorIndex(_this, pool, (size_t)index);

      printf("%i", (int)( *(int64_t*)chunk) );

      if(index != pool->num - 1)
        printf(" ");
    }
    printf("]");

    pool = pool->next;
  }
  printf("\n\n");
}

static uint8_t* SsStackGetPreviousChunk(ssStack* _this)
{
  uint8_t* chunk = 0;

  SsStackPool* pool = _this->current;

  int index = _this->index - 1;

  if(index < 0)
  {
    pool = pool->previous;

    // we specifically want the new pool's num for arithmetic
    // _this->current->previous->num, not _this->current->num
    index = pool->num + index;
  }

  chunk = SsStackPoolToChunkOperatorIndex(_this, pool, (size_t)index);

  return chunk;
}

static void SsStackStateChangeProcessRolloverPrevious(ssStack* _this)
{
  int index = _this->index;

  if(index < 0)
  {
    SsStackPool* pool = _this->current->previous;

    _this->current = pool;

    // we specifically want the new pool's num for arithmetic
    // _this->current->previous->num, not _this->current->num
    _this->index = pool->num + index;
  }
}

static void SsStackStateChangeProcessRolloverNext(ssStack* _this)
{
  SsStackPool* pool = _this->current;
  int index = _this->index;

  if(index >= pool->num)
  {
    _this->current = pool->next;

    // we want to specifically subtract the previous pool's num
    // _this->current->num, not _this->current->next->num
    _this->index = index - pool->num;
  }
}

static bool SsStackResizeNewPool(ssStack* _this, size_t minimumCapacity) // todo
{
  bool result = false;

  int diff = 0;

  size_t size = 0;

  uint8_t* unaligned = 0;
  uint8_t* aligned = 0;

  SsStackPool* pool = 0;

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

  size = SsStackGetPoolSizeOf(_this, (size_t)diff);

  if(minimumCapacity > 0)
    size += SsStackGetSizeOfSsStackHeader();

  aligned = blah_aligned_alloc(size, &unaligned, true);

  if(minimumCapacity > 0)
    aligned += SsStackGetSizeOfSsStackHeader();

  pool = (SsStackPool*)aligned;

  if( !pool)
    goto error;

  pool->previous = 0;
  pool->next = 0;

  SsStackPoolSetUnaligned(pool, unaligned);
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

static bool SsStackResize(ssStack* _this, size_t minimumCapacity) // todo
{
  bool result = false;

  if(_this->max >= _this->capacity)
    goto error;

  if(_this->current != _this->tail)
    goto error;

  result = SsStackResizeNewPool(_this, minimumCapacity);

error:
  return result;
}

ssStack* SsStackConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize)
{
  uint8_t* result = 0;

  ssStack _this = {0};

  if(sizeOf <= 0 || minimumCapacity <= 0 || minimumCapacity > maximumCapacity || !resize)
    goto error;

  _this.resize = resize;
  _this.capacity = maximumCapacity;

  _this.sizeOfRef = sizeOf;
  _this.sizeOf = (int)SsStackGetSizeOfChunk( (size_t)sizeOf);

  if( !SsStackResize( &_this, (size_t)minimumCapacity) || !_this.head)
    goto error;

  result = (uint8_t*)_this.head - (ptrdiff_t)SsStackGetSizeOfSsStackHeader();

  SsStackMemcpySsStack(result, &_this);

error:
  return (ssStack*)result;
}

int SsStackDestruct(ssStack** reference/*_this*/)
{
  int result = -1;
  int numChunks = 0;

  ssStack* _this = 0;

  if( !reference)
    goto error;

  _this = reference[0];

  if( !_this)
    goto error;

  numChunks = _this->numChunks;

  SsStackPoolListFree(_this->tail);

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

int SsStackReset(ssStack* _this)
{
  int result = -1;
  int numChunksRef = 0;

  if( !_this)
    goto error;

  numChunksRef = _this->numChunks;

  _this->current = _this->head;

  _this->numChunks = 0;

  _this->index = 0;

  _this->counter++;

  result = numChunksRef;

error:
  return result;
}

bool SsStackPush(ssStack* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client)
    goto error;

  if(_this->numChunks == _this->max)
  {
    if( !SsStackResize(_this, 0) )
      goto error;
  }

  if(_this->numChunks >= _this->max)
    goto error;

  // for this type of data structure, this call must be before _this->index++
  SsStackStateChangeProcessRolloverNext(_this);

  chunk = SsStackPoolToChunkOperatorIndex(_this, _this->current, (size_t)_this->index);

  // call SsStackStateChangeProcessRolloverNext(...) before _this->index++
  _this->index++;

  _this->numChunks++;

  SsStackMemcpyChunk(_this, chunk, client);

  printf("pushed %i;", (int)( *(int64_t*)client) );
  SsStackDebug(_this);
  SsStackDeepDebug1(_this);

  result = true;

error:
  return result;
}

bool SsStackPop(ssStack* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || _this->numChunks <= 0)
    goto error;

  _this->index--;

  SsStackStateChangeProcessRolloverPrevious(_this);

  chunk = SsStackPoolToChunkOperatorIndex(_this, _this->current, (size_t)_this->index);

  _this->numChunks--;

  SsStackMemcpyChunk(_this, client, chunk);

  printf("popped %i;", (int)( *(int64_t*)client) );
  SsStackDebug(_this);
  SsStackDeepDebug1(_this);

  result = true;

error:
  return result;
}

bool SsStackGet(ssStack* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || _this->numChunks <= 0)
    goto error;

  chunk = SsStackGetPreviousChunk(_this);

  if( !chunk)
    goto error;

  SsStackMemcpyChunk(_this, client, chunk);

  result = true;

error:
  return result;
}

bool SsStackSet(ssStack* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || _this->numChunks <= 0)
    goto error;

  chunk = SsStackGetPreviousChunk(_this);

  if( !chunk)
    goto error;

  SsStackMemcpyChunk(_this, chunk, client);

  result = true;

error:
  return result;
}

bool SsStackGetAt(ssStack* _this, int index, void* client)
{
  bool result = false;

  if( !_this || !client || index < 0 || index >= _this->numChunks)
    goto error;

  for(SsStackPool* pool = _this->head; index >= 0; pool = pool->next)
  {
    if(index < pool->num)
    {
      uint8_t* chunk = SsStackPoolToChunkOperatorIndex(_this, pool, (size_t)index);

      SsStackMemcpyChunk(_this, client, chunk);

      result = true;

      break;
    }

    index -= pool->num;
  }

error:
  return result;
}

bool SsStackSetAt(ssStack* _this, int index, void* client)
{
  bool result = false;

  if( !_this || !client || index < 0 || index >= _this->numChunks)
    goto error;

  for(SsStackPool* pool = _this->head; index >= 0; pool = pool->next)
  {
    if(index < pool->num)
    {
      uint8_t* chunk = SsStackPoolToChunkOperatorIndex(_this, pool, (size_t)index);

      SsStackMemcpyChunk(_this, chunk, client);

      result = true;

      break;
    }

    index -= pool->num;
  }

error:
  return result;
}
