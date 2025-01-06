
// ssQueue.cpp
// Robert Aldridge, code
// Robert Aldridge and Charlie Burns, design

#include <cstddef> // ptrdiff_t
#include <cstdint> // uint64_t, uint32_t, uint8_t
#include <cstring> // memcpy

using std::memcpy;
using std::ptrdiff_t;
using std::uint64_t;
using std::uint32_t;
using std::uint8_t;

#define BLAH_DEBUG 1

#if BLAH_DEBUG
#include <cstdio>
using std::printf;
#endif

struct SsQueueNode
{
  SsQueueNode* previous;
  SsQueueNode* next;

  uint8_t* chunk;

  uint32_t num;

  uint32_t padding;
};

struct SsQueuePool
{
  SsQueueNode back;
  SsQueueNode front;

  SsQueuePool* previous;
  SsQueuePool* next;

  uint32_t num;

  uint32_t padding;
};

struct ssQueue
{
  SsQueueNode* back;
  SsQueueNode* front;

  SsQueuePool* head;
  SsQueuePool* tail;

  uint32_t numNodes;
  uint32_t numPools;
  uint32_t numChunks;

  uint32_t indexBack;
  uint32_t indexFront;

  uint32_t max;

  uint32_t counter;

  uint32_t resize;
  uint32_t capacity;

  uint32_t sizeOfRef;
  uint32_t sizeOf;

  uint32_t padding;
};

#include "ssQueue_nocomments.h"

#include "blah_aligned_alloc.h"

static uint32_t SsQueueAlignedOfValue(uint32_t size)
  { return (size % sizeof(void*) ) ? size + (sizeof(void*) - size % sizeof(void*) ) : size; }

static uint32_t SsQueueGetSizeOfPoolHeader()
  { return SsQueueAlignedOfValue(sizeof(SsQueuePool) ); }

static uint32_t SsQueueGetSizeOfSsQueueHeader()
  { return SsQueueAlignedOfValue(sizeof(ssQueue) ); }

static uint32_t SsQueueGetSizeOfChunk(uint32_t sizeOf)
  { return SsQueueAlignedOfValue(sizeOf); }

static uint32_t SsQueueGetPoolSizeOf(ssQueue* _this, uint32_t nmemb)
  { return SsQueueGetSizeOfPoolHeader() + nmemb * _this->sizeOf; }

static uint8_t* SsQueuePoolToChunkOperatorIndex(ssQueue* _this, SsQueuePool* pool, uint32_t index)
  { return (uint8_t*)pool + SsQueueGetSizeOfPoolHeader() + index * _this->sizeOf; }

static uint8_t* SsQueueNodeToChunkOperatorIndex(ssQueue* _this, SsQueueNode* node, uint32_t index)
  { return node->chunk + index * _this->sizeOf; }

static void SsQueueMemcpySsQueue(uint8_t* destination, ssQueue* source)
  { memcpy(destination, source, sizeof(ssQueue) ); }

static void SsQueueMemcpyChunk(ssQueue* _this, void* destination, void* source)
  { memcpy(destination, source, _this->sizeOfRef); }

// free in reverse order by walking previous from tail
static void SsQueuePoolListFree(ssQueue* _this, SsQueuePool* current)
{
  for(SsQueuePool* previous = 0; current; current = previous)
  {
    previous = current->previous;

    if(current != _this->head)
      blah_free_aligned_sized(current);
  }
}

#if BLAH_DEBUG
static void SsQueueDebug(ssQueue* _this)
{
  {
    uint64_t blah = 0;
    SsQueueGetFront(_this, &blah);
    printf(" front %i", (uint32_t)blah);
  }
  printf(";");
  {
    uint64_t blah = 0;
    SsQueueGetBack(_this, &blah);
    printf(" back %i", (uint32_t)blah);
  }
  printf("\n");

  printf("get at");
  for(uint32_t index = 0; index < _this->numChunks; index++)
  {
    uint64_t blah = 0;
    SsQueueGetAt(_this, index, &blah);
    printf(" %i", (uint32_t)blah);
  }
  printf("\n");
}

static void SsQueueDeepDebug1(ssQueue* _this)
{
  SsQueueNode* node = _this->front;

  uint32_t queueSize = 0;

  printf("num %i; ", SsQueueNum(_this) );

  printf("[");
  for(uint32_t index = 0; index < node->num; index++)
  {
    uint8_t* chunk = SsQueueNodeToChunkOperatorIndex(_this, node, index);

    printf("%i", (uint32_t)( *(uint64_t*)chunk) );

    if(index != node->num - 1)
      printf(" ");
  }
  printf("]");

  node = node->next;

  while(node != _this->front)
  {
    printf("[");
    for(uint32_t index = 0; index < node->num; index++)
    {
      uint8_t* chunk = SsQueueNodeToChunkOperatorIndex(_this, node, index);

      printf("%i", (uint32_t)( *(uint64_t*)chunk) );

      if(index != node->num - 1)
        printf(" ");
    }
    printf("]");

    node = node->next;
  }
  printf("\n");
}

static void SsQueueDeepDebug2(ssQueue* _this)
{
  uint32_t index = _this->indexFront;
  SsQueueNode* node = _this->front;

  printf("[");
  for(uint32_t count = 0; count < _this->numChunks; count++)
  {
    if(index >= node->num)
    {
      index -= node->num;
      node = node->next;

      printf("][");
    }

    uint8_t* chunk = SsQueueNodeToChunkOperatorIndex(_this, node, index);

    uint64_t client = 0;
    SsQueueMemcpyChunk(_this, &client, chunk);

    printf("%i", (uint32_t)client);

    if(index != (node->num - 1) && count != (_this->numChunks - 1) )
      printf(" ");

    index++;

  }
  printf("]\n\n");
}
#endif

static uint8_t* SsQueueGetPreviousBackChunk(ssQueue* _this)
{
  uint8_t* chunk = 0;

  SsQueueNode* node = _this->back;
  uint32_t index = _this->indexBack;

  if( !index)
  {
    node = node->previous;

    // use new node in arithmetic
    index = node->num - 1;
  }
  else
  {
    index--;
  }

  chunk = SsQueueNodeToChunkOperatorIndex(_this, node, index);

  return chunk;
}

// _this->indexBack-- is integrated into the call as if it had occurred before the call
static void SsQueueStateChangeProcessRolloverBackPrevious(ssQueue* _this)
{
  if( !_this->indexBack)
  {
    SsQueueNode* node = _this->back;

    node = node->previous;

    _this->back = node;

    // use new node in arithmetic
    _this->indexBack = node->num - 1;
  }
  else
  {
    _this->indexBack--;
  }
}

static void SsQueueStateChangeProcessRolloverBackNext(ssQueue* _this)
{
  SsQueueNode* node = _this->back;

  if(_this->indexBack == node->num)
  {
    _this->back = node->next;

    _this->indexBack = 0;
  }
}

// _this->indexFront-- is integrated into the call as if it had occurred before the call
static void SsQueueStateChangeProcessRolloverFrontPrevious(ssQueue* _this)
{
  if( !_this->indexFront)
  {
    SsQueueNode* node = _this->front;

    node = node->previous;

    _this->front = node;

    // use new node in arithmetic
    _this->indexFront = node->num - 1;
  }
  else
  {
    _this->indexFront--;
  }
}

static void SsQueueStateChangeProcessRolloverFrontNext(ssQueue* _this)
{
  SsQueueNode* node = _this->front;

  if(_this->indexFront == node->num)
  {
    _this->front = node->next;

    _this->indexFront = 0;
  }
}

static bool SsQueueResizeNewPool(ssQueue* _this, uint32_t minimumCapacity)
{
  bool result = false;

  uint32_t diff = 0;

  uint32_t size = 0;

  uint8_t* pointer = 0;

  SsQueuePool* pool = 0;

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

  size = SsQueueGetPoolSizeOf(_this, diff);

  if(minimumCapacity > 0)
    size += SsQueueGetSizeOfSsQueueHeader();

  pointer = (uint8_t*)blah_aligned_alloc(size);

  if(minimumCapacity > 0)
    pointer += SsQueueGetSizeOfSsQueueHeader();

  pool = (SsQueuePool*)pointer;

  if( !pool)
    goto error;

  pool->previous = 0;
  pool->next = 0;

  pool->num = diff;

  if( !_this->head)
  {
    _this->head = pool;

    SsQueueNode* node = &pool->back;
    node->chunk = SsQueuePoolToChunkOperatorIndex(_this, pool, 0);
    node->num = pool->num;

    node->previous = node;
    node->next = node;

    _this->back = node;
    _this->front = node;

    _this->numNodes++;

    _this->indexBack = 0;
    _this->indexFront = 0;
  }
  else// if(_this->head)
  {
    _this->tail->next = pool;
    pool->previous = _this->tail;

    uint32_t count_lhs = (_this->indexBack + _this->back->num) % _this->back->num;

    uint32_t count_rhs = _this->back->num - count_lhs;

    if(count_lhs)
    {
#if BLAH_DEBUG
      printf("grow count_lhs != 0\n\n");
#endif

      // _this->back->previous -> _this->back -> middle -> splitRhs -> _this->back->next
      //
      // middle is new back; splitRhs is new front
      //
      // splitLhs _this->back[0, _this->indexBack); count is _this->indexBack
      //
      // splitRhs _this->back[_this->indexBack, _this->back->num); count is _this->back->num - _this->indexBack

      SsQueueNode* middle = &pool->back;
      middle->chunk = SsQueuePoolToChunkOperatorIndex(_this, pool, 0);
      middle->num = pool->num;

      SsQueueNode* splitRhs = &pool->front;
      splitRhs->chunk = SsQueueNodeToChunkOperatorIndex(_this, _this->back, _this->indexBack);
      splitRhs->num = count_rhs; //  count_rhs == _this->back->num - _this->indexBack

      // right to left

      // connect splitRhs <- _this->back
      _this->back->next->previous = splitRhs;
      splitRhs->next = _this->back->next;

      // connect middle <- splitRhs
      splitRhs->previous = middle;
      middle->next = splitRhs;

      // connect _this->back <- middle
      middle->previous = _this->back;
      _this->back->next = middle;

      _this->back->num = count_lhs; // count_lhs == _this->indexBack

      _this->back = middle;
      _this->front = splitRhs;

      _this->numNodes += 2;

      _this->indexBack = 0;
      _this->indexFront = 0;
    }
    else// if( !count_lhs)
    {
#if BLAH_DEBUG
      printf("grow count_lhs == 0\n\n");
#endif

      // _this->back->previous -> splitLhs -> _this->back -> _this->back->next
      //
      // splitLhs is the newly created pool; splitLhs is the new back

      SsQueueNode* splitLhs = &pool->back;
      splitLhs->chunk = SsQueuePoolToChunkOperatorIndex(_this, pool, 0);
      splitLhs->num = pool->num;

      // left to right

      // connect _this->back -> splitLhs
      _this->back->previous->next = splitLhs;
      splitLhs->previous = _this->back->previous;

      // connect splitLhs -> _this->back
      splitLhs->next = _this->back;
      _this->back->previous = splitLhs;

      //_this->front; doesn't change
      _this->back = splitLhs;

      _this->numNodes++;

      _this->indexBack = 0;
      _this->indexFront = 0;
    }
  }

  _this->tail = pool;

  _this->numPools++;

  _this->max += diff;

  result = true;

error:
  return result;
}

static bool SsQueueResize(ssQueue* _this, uint32_t minimumCapacity)
{
  bool result = false;

  if(_this->max >= _this->capacity)
    goto error;

  if(_this->front != _this->back)
    goto error;

  result = SsQueueResizeNewPool(_this, minimumCapacity);

error:
  return result;
}

ssQueue* SsQueueConstruct(uint32_t sizeOf, uint32_t minimumCapacity, uint32_t maximumCapacity, uint32_t resize)
{
  uint8_t* result = 0;

  ssQueue _this = {0};

  if( !sizeOf || !minimumCapacity || minimumCapacity > maximumCapacity || !resize)
    goto error;

  _this.resize = resize;
  _this.capacity = maximumCapacity;

  _this.sizeOfRef = sizeOf;
  _this.sizeOf = SsQueueGetSizeOfChunk(sizeOf);

  if( !SsQueueResize( &_this, minimumCapacity) || !_this.head)
    goto error;

  result = (uint8_t*)_this.head - (ptrdiff_t)SsQueueGetSizeOfSsQueueHeader();

  SsQueueMemcpySsQueue(result, &_this);

error:
  return (ssQueue*)result;
}

bool SsQueueDestruct(ssQueue** reference, uint32_t* num)
{
  bool result = false;

  uint32_t numChunks = 0;

  ssQueue* _this = 0;

  if( !reference || !num)
    goto error;

  _this = reference[0];

  if( !_this)
    goto error;

  numChunks = _this->numChunks;

  SsQueuePoolListFree(_this, _this->tail);
  
  blah_free_aligned_sized(_this);

  reference[0] = 0;

  *num = numChunks;
  
  result = true;

error:
  return result;
}

bool SsQueueNum(ssQueue* _this, uint32_t* num)
{
  bool result = false;

  if( !_this || !num)
    goto error;

  *num = _this->numChunks;
  
  result = true;

error:
  return result;
}

bool SsQueueReset(ssQueue* _this, uint32_t* num)
{
  bool result = false;

  uint32_t numChunks = 0;

  if( !_this || !num)
    goto error;

  numChunks = _this->numChunks;

  _this->front = _this->back;

  _this->numChunks = 0;

  _this->indexBack = 0;
  _this->indexFront = 0;

  _this->counter++;

  *num = numChunks;
  
  result = true;

error:
  return result;
}

bool SsQueuePushBack(ssQueue* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client)
    goto error;

  if(_this->numChunks == _this->max)
  {
    if( !SsQueueResize(_this, 0) )
      goto error;
  }

  if(_this->numChunks >= _this->max)
    goto error;

  chunk = SsQueueNodeToChunkOperatorIndex(_this, _this->back, _this->indexBack);

  _this->indexBack++;

  // putting this call after _this->indexBack++ instead of before only works because we are a rotating queue
  SsQueueStateChangeProcessRolloverBackNext(_this);

  _this->numChunks++;

  SsQueueMemcpyChunk(_this, chunk, client);

#if BLAH_DEBUG
  printf("pushed to back %i;", (uint32_t)( *(uint64_t*)client) );
  SsQueueDebug(_this);
  SsQueueDeepDebug1(_this);
  SsQueueDeepDebug2(_this);
#endif

  result = true;

error:
  return result;
}

bool SsQueuePopBack(ssQueue* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || !_this->numChunks)
    goto error;

  // _this->indexBack-- is performed inside of SsQueueStateChangeProcessRolloverBackPrevious(...)
  SsQueueStateChangeProcessRolloverBackPrevious(_this);

  chunk = SsQueueNodeToChunkOperatorIndex(_this, _this->back, _this->indexBack);

  _this->numChunks--;

  SsQueueMemcpyChunk(_this, client, chunk);

  result = true;

error:
  return result;
}

bool SsQueuePushFront(ssQueue* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client)
    goto error;

  if(_this->numChunks == _this->max)
  {
    if( !SsQueueResize(_this, 0) )
      goto error;
  }

  if(_this->numChunks >= _this->max)
    goto error;

  // _this->indexFront-- is performed inside of SsQueueStateChangeProcessRolloverFrontPrevious(...)
  SsQueueStateChangeProcessRolloverFrontPrevious(_this);

  chunk = SsQueueNodeToChunkOperatorIndex(_this, _this->front, _this->indexFront);

  _this->numChunks++;

  SsQueueMemcpyChunk(_this, chunk, client);

#if BLAH_DEBUG
  printf("pushed to front %i;", (uint32_t)( *(uint64_t*)client) );
  SsQueueDebug(_this);
  SsQueueDeepDebug1(_this);
  SsQueueDeepDebug2(_this);
#endif

  result = true;

error:
  return result;
}

bool SsQueuePopFront(ssQueue* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || _this->numChunks <= 0)
    goto error;

  chunk = SsQueueNodeToChunkOperatorIndex(_this, _this->front, _this->indexFront);

  _this->indexFront++;

  // putting this call after _this->indexFront++ instead of before only works because we are a rotating queue
  SsQueueStateChangeProcessRolloverFrontNext(_this);

  _this->numChunks--;

  SsQueueMemcpyChunk(_this, client, chunk);

#if BLAH_DEBUG
  printf("popped from front %i;", (uint32_t)( *(uint64_t*)client) );
  SsQueueDebug(_this);
  SsQueueDeepDebug1(_this);
  SsQueueDeepDebug2(_this);
#endif

  result = true;

error:
  return result;
}

bool SsQueueGetBack(ssQueue* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || !_this->numChunks)
    goto error;

  chunk = SsQueueGetPreviousBackChunk(_this);

  if( !chunk)
    goto error;

  SsQueueMemcpyChunk(_this, client, chunk);

  result = true;

error:
  return result;
}

bool SsQueueSetBack(ssQueue* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || !_this->numChunks)
    goto error;

  chunk = SsQueueGetPreviousBackChunk(_this);

  if( !chunk)
    goto error;

  SsQueueMemcpyChunk(_this, chunk, client);

  result = true;

error:
  return result;
}

bool SsQueueGetFront(ssQueue* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || !_this->numChunks)
    goto error;

  chunk = SsQueueNodeToChunkOperatorIndex(_this, _this->front, _this->indexFront);

  if( !chunk)
    goto error;

  SsQueueMemcpyChunk(_this, client, chunk);

  result = true;

error:
  return result;
}

bool SsQueueSetFront(ssQueue* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || !_this->numChunks)
    goto error;

  chunk = SsQueueNodeToChunkOperatorIndex(_this, _this->front, _this->indexFront);

  if( !chunk)
    goto error;

  SsQueueMemcpyChunk(_this, chunk, client);

  result = true;

error:
  return result;
}

bool SsQueueGetAt(ssQueue* _this, uint32_t index, void* client)
{
  bool result = false;

  if( !_this || !client || index >= _this->numChunks)
    goto error;

  index += _this->indexFront;

  for(SsQueueNode* node = _this->front; node; node = node->next)
  {
    if(index < node->num)
    {
      uint8_t* chunk = SsQueueNodeToChunkOperatorIndex(_this, node, index);

      SsQueueMemcpyChunk(_this, client, chunk);

      result = true;

      break;
    }

    if(node->num > index)
      break;

    index -= node->num;
  }

error:
  return result;
}

bool SsQueueSetAt(ssQueue* _this, uint32_t index, void* client)
{
  bool result = false;

  if( !_this || !client || index >= _this->numChunks)
    goto error;

  index += _this->indexFront;

  for(SsQueueNode* node = _this->front; node; node = node->next)
  {
    if(index < node->num)
    {
      uint8_t* chunk = SsQueueNodeToChunkOperatorIndex(_this, node, index);

      SsQueueMemcpyChunk(_this, chunk, client);

      result = true;

      break;
    }
    
    if(node->num > index)
      break;

    index -= node->num;
  }

error:
  return result;
}
