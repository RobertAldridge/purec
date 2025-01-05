
// ssStack.cpp
// Robert Aldridge, code
// Robert Aldridge and Charlie Burns, design

#include <cstddef> // ptrdiff_t, size_t
#include <cstdint> // uint8_t
#include <cstdlib> // malloc, free
#include <cstring> // memcpy

#include <new> // bad_alloc
using std::bad_alloc;
using std::free;
using std::malloc;
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

static size_t ALIGNEDOFVALUE(size_t size);

static size_t SsStackGetSizeOfNode();

static size_t SsStackGetSizeOfPool();

static size_t SsStackGetSizeOfSsStack();

static size_t SsStackGetSizeOfChunk(size_t sizeOf);

static void PoolSetUnaligned(SsStackPool* pool, uint8_t* unaligned);
static uint8_t* PoolGetUnaligned(SsStackPool* pool);

static size_t SSSTACK_GET_POOL_SIZEOF(ssStack* _this, size_t nmemb);

static uint8_t* SSSTACK_POOL_TO_CHUNK_OPERATOR_INDEX(ssStack* _this, SsStackPool* pool, size_t index);

static void SSSTACK_MEMCPY_CHUNK(ssStack* _this, void* destination, void* source);

static uint8_t* cstandard_aligned_alloc(size_t size, uint8_t** unalignedRef/*unaligned;ptr*/);

static void PoolListWalk(SsStackPool* head, bool doFree);
static void PoolListReverseAndFree(SsStackPool* head);

static bool SsStackResize(ssStack* _this, size_t minimumCapacity);

size_t ALIGNEDOFVALUE(size_t size)
  { return (size % sizeof(void*) ) ? size + (sizeof(void*) - size % sizeof(void*) ) : size; }

size_t SsStackGetSizeOfNode()
  { return 0; }

size_t SsStackGetSizeOfPool()
  { return ALIGNEDOFVALUE(sizeof(SsStackPool) ); }

size_t SsStackGetSizeOfSsStack()
  { return ALIGNEDOFVALUE(sizeof(ssStack) ); }

size_t SsStackGetSizeOfChunk(size_t sizeOf)
  { return ALIGNEDOFVALUE(sizeOf) + SsStackGetSizeOfNode(); }

void PoolSetUnaligned(SsStackPool* pool, uint8_t* unaligned)
  { pool->unaligned = (int)( (uint8_t*)unaligned - (uint8_t*)pool); }

uint8_t* PoolGetUnaligned(SsStackPool* pool)
  { return (uint8_t*)pool + (ptrdiff_t)pool->unaligned; }

size_t SSSTACK_GET_POOL_SIZEOF(ssStack* _this, size_t nmemb)
  { return SsStackGetSizeOfPool() + nmemb * (size_t)_this->sizeOf; }

uint8_t* SSSTACK_POOL_TO_CHUNK_OPERATOR_INDEX(ssStack* _this, SsStackPool* pool, size_t index)
  { return (uint8_t*)pool + SSSTACK_GET_POOL_SIZEOF(_this, index); }

void SSSTACK_MEMCPY_CHUNK(ssStack* _this, void* destination, void* source)
  { memcpy(destination, source, (size_t)_this->sizeOfRef; }

void PoolListWalk(SsStackPool* head, bool doFree)
{
  SsStackPool* next = 0;

  for(SsStackPool* curr = head; curr; curr = next)
  {
    next = curr->next;

    if(doFree)
      free(PoolGetUnaligned(curr) );
  }
}

void PoolListReverseAndFree(SsStackPool* head)
{
  SsStackPool* prev = 0;
  SsStackPool* next = 0;

  for(SsStackPool* curr = head; curr; curr = next)
  {
    next = curr->next;
    curr->next = prev;

    prev = curr;
  }

  PoolListWalk(prev, true);
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

  try
  {
    if( !SsStackResize( &_this, (size_t)minimumCapacity) || !_this.head)
      goto error;

    result = (uint8_t*)_this.head - (ptrdiff_t)SsStackGetSizeOfSsStack();
  }
  catch(bad_alloc& )
  {
  }

  if( !result)
    goto error;

  memcpy(result, &_this, sizeof(ssStack) );

error:
  return (ssStack*)result;
}

int SsStackDestruct(ssStack** reference)
{
  int result = -1;
  int numChunks = 0;

  ssStack* _this = 0;

  if( !reference)
    goto error;

  _this = reference[0];

  if( !_this)
    goto error;

  numChunks = SsStackNum(_this);
  if(numChunks < 0)
    goto error;

  PoolListReverseAndFree(_this->head);

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

  if( !_this || _this->numPools <= 0)
    goto error;

  numChunksRef = _this->numChunks;

  pool = _this->head;

  _this->current = pool;

  _this->numChunks = 0;
  _this->index = 0;

  _this->counter++;

  result = numChunksRef;

error:
  return result;
}

bool SsStackResize(ssStack* _this, size_t minimumCapacity) // todo
{
  bool result = false;

  if( !_this || _this->numChunks != _this->max || minimumCapacity > _this->capacity)
    goto error;

  if(minimumCapacity > 0 && _this->numPools > 0)
    goto error;

  if(_this->max >= _this->capacity)
    goto error;

  if(_this->current != _this->tail)
    goto error;

  int diff = 0;

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
  else
  {
    goto error;
  }

  if( !diff)
    goto error;

  size_t size = SSSTACK_GET_POOL_SIZEOF(_this, (size_t)diff);

  if(minimumCapacity > 0)
    size += SsStackGetSizeOfSsStack();

  uint8_t* unaligned = 0;
  uint8_t* aligned = cstandard_aligned_alloc(size, &unaligned);

  if(minimumCapacity > 0)
    aligned += SsStackGetSizeOfSsStack();

  SsStackPool* pool = (SsStackPool*)aligned;

  if( !pool)
    goto error;

  pool->next = 0;
  PoolSetUnaligned(pool, unaligned);
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

bool SsStackPush(ssStack* _this, void* memory/*chunk*/) // todo
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !memory || _this->numChunks > _this->max)
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

  chunk = SSSTACK_POOL_TO_CHUNK_OPERATOR_INDEX(_this, _this->current, _this->index);

  _this->index++;

  if(_this->index >= _this->current->num)
  {
    if(_this->current == _this->tail)
      goto error;

    _this->current = _this->current->next;

    _this->index = 0;
  }

  _this->numChunks++;

  SSSTACK_MEMCPY_CHUNK(_this, chunk, memory);

  result = true;

error:
  return result;
}

bool SsStackPop(ssStack* _this, void* memory/*chunk*/)
{
  bool result = false;

  SsStackNode* chunk = 0;

  if( !_this || !memory || _this->numChunks <= 0)
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

  chunk = SSSTACK_POOL_TO_CHUNK_OPERATOR_INDEX(_this, _this->current, _this->index);

  _this->numChunks--;

  SSSTACK_MEMCPY_CHUNK(_this, memory, chunk);

  result = true;

error:
  return result;
}
