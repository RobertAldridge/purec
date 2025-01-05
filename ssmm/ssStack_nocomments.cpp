
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

#if 0
struct SsStackNode
{
  SsStackNode* previous;
  SsStackNode* next;

  uint8_t* chunk;

  int num;

  int padding;
};
#endif

struct SsStackPool
{
#if 0
  SsStackNode back;
  SsStackNode front;
#endif

  SsStackPool* previous;
  SsStackPool* next;

  int unaligned;

  int num;
};

struct ssStack
{
#if 0
  SsStackNode* back;
  SsStackNode* front;
#else
  SsStackPool* current;
#endif

  SsStackPool* head;
  SsStackPool* tail;

  int numPools;

  int numChunks;

#if 0
  int indexBack;
  int indexFront;
#else
  int index;
#endif

  int max;

  int counter;

  int resize;
  int capacity;

  int sizeOfRef;
  int sizeOf;

  int padding;
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

static uint8_t* SsStackPoolToFirstChunk(SsStackPool* pool)
  { return (uint8_t*)pool + SsStackGetSizeOfPoolHeader(); }

static uint8_t* SsStackChunkToChunkPrevious(ssStack* _this, uint8_t* chunk)
  {return chunk - (ptrdiff_t)_this->sizeOf; }

static uint8_t* SsStackChunkToChunkNext(ssStack* _this, uint8_t* chunk)
  { return chunk + (size_t)_this->sizeOf; }

//static uint8_t* SsStackNodeToChunkOperatorIndex(ssStack* _this, SsStackNode* node, size_t index)
//  { return node->chunk + index * (size_t)_this->sizeOf; }

static void SsStackMemcpySsStack(uint8_t* destination, ssStack* source)
  { memcpy(destination, source, sizeof(ssStack) ); }

static void SsStackMemcpyChunk(ssStack* _this, void* destination, void* source)
  { memcpy(destination, source, (size_t)_this->sizeOfRef); }

static void SsStackPoolListFree(SsStackPool* current)
{
  for(SsStackPool* previous = 0; current; current = previous)
  {
    previous = current->previous;

    free(SsStackPoolGetUnaligned(current) );
  }
}

#if 0
static uint8_t* SsStackGetPreviousBackChunk(ssStack* _this)
{
  uint8_t* chunk = 0;

  SsStackNode* node = _this->back;
  int index = _this->indexBack - 1;

  if(index < 0)
  {
    if(index < -1)
      goto error;

    node = node->previous;

    index = node->num - 1;
  }

  chunk = SsStackNodeToChunkOperatorIndex(_this, node, (size_t)index);

error:
  return chunk;
}
#endif

static uint8_t* SsStackGetPreviousChunk(ssStack* _this)
{
  uint8_t* chunk = 0;

  SsStackPool* pool = _this->current;
  int index = _this->index - 1;

  if(index < 0)
  {
    if(index < -1)
      goto error;

    pool = pool->previous;

    index = pool->num - 1;
  }

  chunk = SsStackPoolToChunkOperatorIndex(_this, pool, (size_t)index);

error:
  return chunk;
}

#if 0
static bool SsStackStateChangeProcessRolloverBackPrevious(ssStack* _this)
{
  bool result = false;

  int index = _this->indexBack;

  if(index < 0)
  {
    SsStackNode* node = _this->back;

    if(index < -1)
      goto error;

    _this->back = node->previous;

    _this->indexBack = node->num - 1;
  }

  result = true;

error:
  return result;
}

static bool SsStackStateChangeProcessRolloverBackNext(ssStack* _this)
{
  bool result = false;

  SsStackNode* node = _this->back;
  int index = _this->indexBack;

  if(index >= node->num)
  {
    if(index > node->num)
      goto error;

    _this->back = node->next;

    _this->indexBack = 0;
  }

  result = true;

error:
  return result;
}
#endif

static bool SsStackStateChangeProcessRolloverPrevious(ssStack* _this)
{
  bool result = false;

  int index = _this->index;

  if(index < 0)
  {
    SsStackPool* pool = _this->current;

    if(index < -1)
      goto error;

    _this->current = pool->previous;

    _this->index = pool->num - 1;
  }

  result = true;

error:
  return result;
}

static bool SsStackStateChangeProcessRolloverNext(ssStack* _this)
{
  bool result = false;

  SsStackPool* pool = _this->current;
  int index = _this->index;

  if(index >= pool->num)
  {
    if(index > pool->num)
      goto error;

    _this->current = pool->next;

    _this->index = 0;
  }

  result = true;

error:
  return result;
}

static bool SsStackResizeNewPool(ssStack* _this, size_t minimumCapacity)
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

  aligned = blah_aligned_alloc(size, &unaligned, false);

  if(minimumCapacity > 0)
    aligned += SsStackGetSizeOfSsStackHeader();

  pool = (SsStackPool*)aligned;

  if( !pool)
    goto error;

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

static bool SsStackResize(ssStack* _this, size_t minimumCapacity)
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

  SsStackPoolListFree(_this->head);

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

  SsStackPool* pool = 0;

  if( !_this)
    goto error;

  numChunksRef = _this->numChunks;

  pool = _this->head;

#if 0
  _this->front = node;
#else
  _this->current = pool;
#endif

  _this->numChunks = 0;

#if 0
  _this->indexBack = 0;
  _this->indexFront = 0;
#else
  _this->index = 0;
#endif

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

  if( !SsStackStateChangeProcessRolloverNext(_this) )
    goto error;

  chunk = SsStackPoolToChunkOperatorIndex(_this, _this->current, (size_t)_this->index);

  _this->index++;

  _this->numChunks++;

  SsStackMemcpyChunk(_this, chunk, client);

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

  if( !SsStackStateChangeProcessRolloverPrevious(_this) )
    goto error;

  chunk = SsStackPoolToChunkOperatorIndex(_this, _this->current, (size_t)_this->index);

  _this->numChunks--;

  SsStackMemcpyChunk(_this, client, chunk);

  result = true;

error:
  return result;
}

#if 0
bool SsStackPushFront(ssStack* _this, void* client)
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

  _this->indexFront--;

  if( !SsStackStateChangeProcessRolloverFrontPrevious(_this) )
    goto error;

  chunk = SsStackNodeToChunkOperatorIndex(_this, _this->front, (size_t)_this->indexFront);

  _this->numChunks++;

  SsStackMemcpyChunk(_this, chunk, client);

  result = true;

error:
  return result;
}

bool SsStackPopFront(ssStack* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || _this->numChunks <= 0)
    goto error;

  if( !SsStackStateChangeProcessRolloverFrontNext(_this) )
    goto error;

  chunk = SsStackNodeToChunkOperatorIndex(_this, _this->front, (size_t)_this->indexFront);

  _this->indexFront++;

  _this->numChunks--;

  SsStackMemcpyChunk(_this, client, chunk);

  result = true;

error:
  return result;
}
#endif

#if 0
bool SsStackGetBack(ssStack* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || _this->numChunks <= 0)
    goto error;

  chunk = SsStackGetPreviousBackChunk(_this);

  if( !chunk)
    goto error;

  SsStackMemcpyChunk(_this, client, chunk);

  result = true;

error:
  return result;
}

bool SsStackSetBack(ssStack* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || _this->numChunks <= 0)
    goto error;

  chunk = SsStackGetPreviousBackChunk(_this);

  if( !chunk)
    goto error;

  SsStackMemcpyChunk(_this, chunk, client);

  result = true;

error:
  return result;
}
#endif

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

  SsStackPool* pool = 0;

  if( !_this || !client || index < 0 || index >= _this->numChunks)
    goto error;

  pool = _this->head;

  for(int walk = 0; pool; pool = pool->next)
  {
    if(index >= walk && index < walk + pool->num)
    {
      uint8_t* chunk = SsStackPoolToChunkOperatorIndex(_this, pool, (size_t)(index - walk) );

      SsStackMemcpyChunk(_this, client, chunk);

      result = true;

      break;
    }

    walk += pool->num;
  }

error:
  return result;
}

bool SsStackSetAt(ssStack* _this, int index, void* client)
{
  bool result = false;

  SsStackPool* pool = 0;

  if( !_this || !client || index < 0 || index >= _this->numChunks)
    goto error;

  pool = _this->head;

  for(int walk = 0; pool; pool = pool->next)
  {
    if(index >= walk && index < walk + pool->num)
    {
      uint8_t* chunk = SsStackPoolToChunkOperatorIndex(_this, pool, (size_t)(index - walk) );

      SsStackMemcpyChunk(_this, chunk, client);

      result = true;

      break;
    }

    walk += pool->num;
  }

error:
  return result;
}
