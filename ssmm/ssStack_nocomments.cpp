
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

struct SsStackPool
{
  SsStackPool* previous;
  SsStackPool* next;

  int unaligned;

  int num;
};

struct ssStack
{
  //uint8_t* chunk;

  SsStackPool* current;

  SsStackPool* head;
  SsStackPool* tail;

  int numPools;

  int numChunks;
  int index;
  int max;

  int counter;

  int resize;
  int capacity;

  int sizeOfRef;
  int sizeOf;

  int padding;
};

#include "ssStack.h"

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
  { return (uint8_t*)pool + SsStackGetPoolSizeOf(_this, index); }

#if 1
static uint8_t* SsStackPoolToFirstChunk(SsStackPool* pool) // todo
  { return (uint8_t*)pool + SsStackGetSizeOfPoolHeader(); }

static uint8_t* SsStackChunkToChunkPrevious(ssStack* _this, uint8_t* chunk) // todo
  {return chunk - (ptrdiff_t)_this->sizeOf; }

static uint8_t* SsStackChunkToChunkNext(ssStack* _this, uint8_t* chunk) // todo
  { return chunk + (size_t)_this->sizeOf; }

static void SsStackMemcpySsStack(uint8_t* destination, ssStack* source) // todo
  { memcpy(destination, source, sizeof(ssStack) ); }
#endif

static void SsStackMemcpyChunk(ssStack* _this, void* destination, void* source)
  { memcpy(destination, source, (size_t)_this->sizeOfRef); }

static void SsStackPoolListFree(SsStackPool* current)
{
  for(SsStackPool* next = 0; current; current = next)
  {
    next = current->next;

    free(SsStackPoolGetUnaligned(current) );
  }
}

static void SsStackPoolListReverseAndFree(SsStackPool* current)
{
  SsStackPool* previous = 0;

  for(SsStackPool* next = 0; current; current = next)
  {
    next = current->next;
    current->next = previous;

    previous = current;
  }

  SsStackPoolListFree(previous);
}

static bool SsStackResizeExistingPool(ssStack* _this)
{
  bool result = false;

#if 0
  SsStackPool* pool = _this->current->next;

  _this->chunk = SsStackPoolToFirstChunk(pool);

  _this->current = pool;

  _this->max += pool->num;

  result = true;

  goto error;
#endif

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

  //_this->chunk = SsStackPoolToFirstChunk(pool);

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
    result = SsStackResizeExistingPool(_this);
  else// if(_this->current == _this->tail)
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

  memcpy(result, &_this, sizeof(ssStack) );

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

  SsStackPoolListReverseAndFree(_this->head);

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

  //_this->chunk = SsStackPoolToFirstChunk(pool);

  _this->current = pool;

  _this->numChunks = 0;
  _this->index = 0;
  //_this->max = pool->num;

  _this->counter++;

  result = numChunksRef;

error:
  return result;
}

bool SsStackPush(ssStack* _this, void* client) // todo
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || _this->numChunks > _this->max)
    goto error;

  if(_this->numChunks == _this->max)
  {
    if( !SsStackResize(_this, 0) )
      goto error;
  }

  if(_this->numChunks == _this->max)
    goto error;

  if(_this->index < 0 || _this->index >= _this->current->num)
    goto error;

  chunk = SsStackPoolToChunkOperatorIndex(_this, _this->current, _this->index);

  //_this->chunk = SsStackChunkToChunkNext(_this, _this->chunk);

#if 1
  _this->index++;

  if(_this->index >= _this->current->num)
  {
    if(_this->current == _this->tail)
      goto error;

    _this->current = _this->current->next;

    _this->index = 0;
  }
#endif

  _this->numChunks++;

  SsStackMemcpyChunk(_this, chunk, client);

  result = true;

error:
  return result;
}

#if 1
bool SsStackPop(ssStack* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || _this->numChunks <= 0)
    goto error;

  if(_this->index < 0 || _this->index >= _this->current->num)
    goto error;

  _this->index--;

  if(_this->index < 0)
  {
    if(_this->current == _this->head)
      goto error;

    _this->current = _this->current->previous;

    _this->index = _this->current->num - 1;
  }

  chunk = SsStackPoolToChunkOperatorIndex(_this, _this->current, _this->index);

  _this->numChunks--;

  SsStackMemcpyChunk(_this, client, chunk);

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

  chunk = SsStackChunkToChunkPrevious(_this, _this->chunk);

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

  chunk = SsStackChunkToChunkPrevious(_this, _this->chunk);

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
