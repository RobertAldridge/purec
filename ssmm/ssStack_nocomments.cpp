
// ssStack.cpp
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

struct SsStackPool
{
  SsStackPool* previous;
  SsStackPool* next;

  uint32_t num;

  uint32_t index;
};

struct ssStack
{
  SsStackPool* current;

  SsStackPool* head;
  SsStackPool* tail;
  
  SsStackPool** lookup;

  uint32_t numPools;
  uint32_t numChunks;

  uint32_t index;

  uint32_t max;

  uint32_t counter;

  uint32_t resize;
  uint32_t capacity;

  uint32_t sizeOf;
};

#include "ssStack_nocomments.h"

#include "blah_alloc.h"

static uint32_t SsStackAlignedOfValue(uint32_t size)
  { return (size % sizeof(void*) ) ? size + (sizeof(void*) - size % sizeof(void*) ) : size; }

static uint32_t SsStackGetSizeOfPoolHeader()
  { return SsStackAlignedOfValue(sizeof(SsStackPool) ); }

static uint32_t SsStackGetSizeOfSsStackHeader()
  { return SsStackAlignedOfValue(sizeof(ssStack) ); }

static uint32_t SsStackGetPoolSizeOf(ssStack* _this, uint32_t nmemb)
  { return SsStackGetSizeOfPoolHeader() + nmemb * _this->sizeOf; }

static uint8_t* SsStackPoolToChunkOperatorIndex(ssStack* _this, SsStackPool* pool, uint32_t index)
  { return (uint8_t*)pool + SsStackGetSizeOfPoolHeader() + index * _this->sizeOf; }

static void SsStackMemcpySsStack(uint8_t* destination, ssStack* source)
  { memcpy(destination, source, sizeof(ssStack) ); }

static void SsStackMemcpyChunk(ssStack* _this, void* destination, void* source)
  { memcpy(destination, source, _this->sizeOf); }

// free in reverse order by walking previous from tail
static void SsStackPoolListFree(ssStack* _this, SsStackPool* current)
{
  for(SsStackPool* previous = 0; current; current = previous)
  {
    previous = current->previous;

    if(current != _this->head)
      BlahFree(current, current->sizeOf, true);
  }
}

#if BLAH_DEBUG
static void SsStackDebugShallow(ssStack* _this)
{
  {
    uint64_t blah = 0;
    SsStackGet(_this, &blah);
    printf(" front %i", (uint32_t)blah);
  }
  printf("\n");

  printf("get at");
  for(uint32_t index = 0; index < _this->numChunks; index++)
  {
    uint64_t blah = 0;
    SsStackGetAt(_this, index, &blah);
    printf(" %i", (uint32_t)blah);
  }
  printf("\n");
}

static void SsStackDeepDebug1(ssStack* _this)
{
  SsStackPool* pool = _this->head;

  uint32_t stackSize = 0;
  SsStackNum(_this, &stackSize);

  printf("num %i; ", stackSize);

  printf("[");
  for(uint32_t index = 0; index < pool->num; index++)
  {
    uint8_t* chunk = SsStackPoolToChunkOperatorIndex(_this, pool, index);

    printf("%i", (uint32_t)( *(uint64_t*)chunk) );

    if(index != pool->num - 1)
      printf(" ");
  }
  printf("]");

  pool = pool->next;

  while(pool)
  {
    printf("[");
    for(uint32_t index = 0; index < pool->num; index++)
    {
      uint8_t* chunk = SsStackPoolToChunkOperatorIndex(_this, pool, index);

      printf("%i", (uint32_t)( *(uint64_t*)chunk) );

      if(index != pool->num - 1)
        printf(" ");
    }
    printf("]");

    pool = pool->next;
  }
  printf("\n\n");
}

static void SsStackDebug(const char* _string, ssStack* _this, void* client)
{
  printf("%s %i;", _string, (uint32_t)( *(uint64_t*)client) );
  SsStackDebugShallow(_this);
  SsStackDeepDebug1(_this);
}
#endif

// ZERO

// ONE
static uint8_t* SsStackGetPreviousChunk(ssStack* _this)
{
  uint8_t* chunk = 0;

  SsStackPool* pool = _this->current;
  uint32_t index = _this->index;

  if( !index)
  {
    pool = pool->previous;

    // we specifically want the new pool's num for arithmetic
    // _this->current->previous->num, not _this->current->num
    index = pool->num - 1;
  }
  else
  {
    index--;
  }

  chunk = SsStackPoolToChunkOperatorIndex(_this, pool, index);

  return chunk;
}

// TWO
// _this->index-- is integrated into the call as if it had occurred before the call
static void SsStackStateChangeProcessRolloverPrevious(ssStack* _this)
{
  if( !_this->index)
  {
    SsStackPool* pool = _this->current->previous;

    _this->current = pool;

    // we specifically want the new pool's num for arithmetic
    // _this->current->previous->num, not _this->current->num
    _this->index = pool->num - 1;
  }
  else
  {
    _this->index--;
  }
}

// THREE
static void SsStackStateChangeProcessRolloverNext(ssStack* _this)
{
  SsStackPool* pool = _this->current;
  uint32_t index = _this->index;

  if(index == pool->num)
  {
    _this->current = pool->next;

    _this->index = 0;
  }
}

static bool SsStackResizeNewPool(ssStack* _this, uint32_t minimumCapacity)
{
  bool result = false;

  uint32_t diff = 0;

  uint32_t sizeOf = 0;

  uint8_t* pointer = 0;

  SsStackPool* pool = 0;

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

  sizeOf = SsStackGetPoolSizeOf(_this, diff);

  if(minimumCapacity > 0)
    sizeOf += SsStackGetSizeOfSsStackHeader();

  pointer = (uint8_t*)BlahAlloc(sizeOf, true);

  if(minimumCapacity > 0)
    pointer += SsStackGetSizeOfSsStackHeader();

  pool = (SsStackPool*)pointer;

  if( !pool)
    goto label_return;

  pool->sizeOf = sizeOf;

  pool->previous = 0;
  pool->next = 0;

  pool->num = diff;

  _this->current = pool;

  if( !_this->head)
  {
    _this->head = pool;
  }
  else // if(_this->head)
  {
    _this->tail->next = pool;
    pool->previous = _this->tail;
  }

  _this->tail = pool;

  _this->numPools++;

  _this->index = 0;
  _this->max += diff;

  result = true;

label_return:
  return result;
}

static bool SsStackResize(ssStack* _this, uint32_t minimum)
{
  bool result = false;

  if(_this->max >= _this->capacity)
    goto label_return;

  if(_this->current != _this->tail)
    goto label_return;

  result = SsStackResizeNewPool(_this, minimum);

label_return:
  return result;
}

ssStack* SsStackConstruct(uint32_t sizeOf, uint32_t minimum, int64_t maximum, uint32_t resize)
{
  uint8_t* result = 0;

  ssStack _this = {0};

  if( !sizeOf || !minimum || minimum > (uint32_t)maximum || !resize)
    goto label_return;

  _this.resize = resize;
  _this.capacity = (uint32_t)maximum;

  _this.sizeOf = sizeOf;

  if( !SsStackResize( &_this, minimum) || !_this.head)
    goto label_return;

  result = (uint8_t*)_this.head - (ptrdiff_t)SsStackGetSizeOfSsStackHeader();

  SsStackMemcpySsStack(result, &_this);

label_return:
  return (ssStack*)result;
}

int64_t SsStackDestruct(ssStack** reference)
{
  bool result = false;

  ssStack* _this = 0;
  
  uint32_t num = 0;

  if( !reference)
    goto label_return;

  _this = reference[0];

  if( !_this)
    goto label_return;
  
  num = _this->numChunks;

  SsStackPoolListFree(_this, _this->tail);

  BlahFree(_this, _this->head->sizeOf, true);

  reference[0] = 0;

  result = true;

label_return:
  return result ? (int64_t)num : -1;
}

int64_t SsStackNum(ssStack* _this)
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

int64_t SsStackReset(ssStack* _this)
{
  bool result = false;
  
  uint32_t num = 0;

  if( !_this)
    goto label_return;
  
  num = _this->numChunks;

  _this->current = _this->head;

  _this->numChunks = 0;

  _this->index = 0;

  _this->counter++;

  result = true;

label_return:
  return result ? (int64_t)num : -1;
}

bool SsStackPush(ssStack* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client)
    goto label_return;

  if(_this->numChunks == _this->max)
  {
    if( !SsStackResize(_this, 0) )
      goto label_return;
  }

  if(_this->numChunks >= _this->max)
    goto label_return;

  // for this type of data structure, this call must be before _this->index++
  SsStackStateChangeProcessRolloverNext(_this);

  chunk = SsStackPoolToChunkOperatorIndex(_this, _this->current, _this->index);

  // call SsStackStateChangeProcessRolloverNext(...) before _this->index++
  _this->index++;

  _this->numChunks++;

  SsStackMemcpyChunk(_this, chunk, client);

#if BLAH_DEBUG
  SsStackDebug("pushed", _this, client);
#endif

  result = true;

label_return:
  return result;
}

bool SsStackPop(ssStack* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || !_this->numChunks)
    goto label_return;

  // _this->index-- is performed inside of SsStackStateChangeProcessRolloverPrevious(...)
  SsStackStateChangeProcessRolloverPrevious(_this);

  chunk = SsStackPoolToChunkOperatorIndex(_this, _this->current, _this->index);

  _this->numChunks--;

  SsStackMemcpyChunk(_this, client, chunk);

#if BLAH_DEBUG
  SsStackDebug("popped", _this, client);
#endif

  result = true;

label_return:
  return result;
}

bool SsStackGet(ssStack* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || !_this->numChunks)
    goto label_return;

  chunk = SsStackGetPreviousChunk(_this);

  if( !chunk)
    goto label_return;

  SsStackMemcpyChunk(_this, client, chunk);

  result = true;

label_return:
  return result;
}

bool SsStackSet(ssStack* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || !_this->numChunks)
    goto label_return;

  chunk = SsStackGetPreviousChunk(_this);

  if( !chunk)
    goto label_return;

  SsStackMemcpyChunk(_this, chunk, client);

  result = true;

label_return:
  return result;
}

bool SsStackGetAt(ssStack* _this, uint32_t index, void* client)
{
  bool result = false;

  if( !_this || !client || index >= _this->numChunks)
    goto label_return;

  for(SsStackPool* pool = _this->head; pool; pool = pool->next)
  {
    if(index < pool->num)
    {
      uint8_t* chunk = SsStackPoolToChunkOperatorIndex(_this, pool, index);

      SsStackMemcpyChunk(_this, client, chunk);

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

bool SsStackSetAt(ssStack* _this, uint32_t index, void* client)
{
  bool result = false;

  if( !_this || !client || index >= _this->numChunks)
    goto label_return;

  for(SsStackPool* pool = _this->head; pool; pool = pool->next)
  {
    if(index < pool->num)
    {
      uint8_t* chunk = SsStackPoolToChunkOperatorIndex(_this, pool, index);

      SsStackMemcpyChunk(_this, chunk, client);

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
