
// ssQueue.cpp
// Robert Aldridge, code
// Robert Aldridge and Charlie Burns, design

#include <cstddef> // ptrdiff_t, size_t
#include <cstdint> // uint8_t
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

struct SsQueueNode
{
  SsQueueNode* previous;
  SsQueueNode* next;

  uint8_t* chunk;

  int32_t num;

  int32_t padding;
};

struct SsQueuePool
{
  SsQueueNode back;
  SsQueueNode front;

  SsQueuePool* previous;
  SsQueuePool* next;

  int32_t unaligned;

  int32_t num;
};

struct ssQueue
{
  SsQueueNode* back;
  SsQueueNode* front;

  SsQueuePool* head;
  SsQueuePool* tail;

  int32_t numNodes;
  int32_t numPools;
  int32_t numChunks;

  int32_t indexBack;
  int32_t indexFront;

  int32_t max;

  int32_t counter;

  int32_t resize;
  int32_t capacity;

  int32_t sizeOfRef;
  int32_t sizeOf;

  int32_t padding;
};

#include "ssQueue_nocomments.h"

#include "blah_aligned_alloc.h"

static size_t SsQueueAlignedOfValue(size_t size)
  { return (size % sizeof(void*) ) ? size + (sizeof(void*) - size % sizeof(void*) ) : size; }

static size_t SsQueueGetSizeOfPoolHeader()
  { return SsQueueAlignedOfValue(sizeof(SsQueuePool) ); }

static size_t SsQueueGetSizeOfSsQueueHeader()
  { return SsQueueAlignedOfValue(sizeof(ssQueue) ); }

static size_t SsQueueGetSizeOfChunk(size_t sizeOf)
  { return SsQueueAlignedOfValue(sizeOf); }

static void SsQueuePoolSetUnaligned(SsQueuePool* pool, uint8_t* unaligned)
  { pool->unaligned = (int)( (uint8_t*)unaligned - (uint8_t*)pool); }

static uint8_t* SsQueuePoolGetUnaligned(SsQueuePool* pool)
  { return (uint8_t*)pool + (ptrdiff_t)pool->unaligned; }

static size_t SsQueueGetPoolSizeOf(ssQueue* _this, size_t nmemb)
  { return SsQueueGetSizeOfPoolHeader() + nmemb * (size_t)_this->sizeOf; }

static uint8_t* SsQueuePoolToChunkOperatorIndex(ssQueue* _this, SsQueuePool* pool, size_t index)
  { return (uint8_t*)pool + SsQueueGetSizeOfPoolHeader() + index * (size_t)_this->sizeOf; }

static uint8_t* SsQueueNodeToChunkOperatorIndex(ssQueue* _this, SsQueueNode* node, size_t index)
  { return node->chunk + index * (size_t)_this->sizeOf; }

static void SsQueueMemcpySsQueue(uint8_t* destination, ssQueue* source)
  { memcpy(destination, source, sizeof(ssQueue) ); }

static void SsQueueMemcpyChunk(ssQueue* _this, void* destination, void* source)
  { memcpy(destination, source, (size_t)_this->sizeOfRef); }

// free in reverse order by walking previous from tail
static void SsQueuePoolListFree(SsQueuePool* current)
{
  for(SsQueuePool* previous = 0; current; current = previous)
  {
    previous = current->previous;

    free(SsQueuePoolGetUnaligned(current) );
  }
}

#if BLAH_DEBUG
static void SsQueueDebug(ssQueue* _this)
{
  {
    int64_t blah = 0;
    SsQueueGetFront(_this, &blah);
    printf(" front %i", (int)blah);
  }
  printf(";");
  {
    int64_t blah = 0;
    SsQueueGetBack(_this, &blah);
    printf(" back %i", (int)blah);
  }
  printf("\n");

  printf("get at");
  for(int index = 0; index < _this->numChunks; index++)
  {
    int64_t blah = 0;
    SsQueueGetAt(_this, index, &blah);
    printf(" %i", (int)blah);
  }
  printf("\n");
}

static void SsQueueDeepDebug1(ssQueue* _this)
{
  SsQueueNode* node = _this->front;

  printf("num %i; ", SsQueueNum(_this) );

  printf("[");
  for(int index = 0; index < node->num; index++)
  {
    uint8_t* chunk = SsQueueNodeToChunkOperatorIndex(_this, node, (size_t)index);

    printf("%i", (int)( *(int64_t*)chunk) );

    if(index != node->num - 1)
      printf(" ");
  }
  printf("]");

  node = node->next;

  while(node != _this->front)
  {
    printf("[");
    for(int index = 0; index < node->num; index++)
    {
      uint8_t* chunk = SsQueueNodeToChunkOperatorIndex(_this, node, (size_t)index);

      printf("%i", (int)( *(int64_t*)chunk) );

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
  int index = _this->indexFront;
  SsQueueNode* node = _this->front;

  printf("[");
  for(int count = 0; count < _this->numChunks; count++)
  {
    if(index >= node->num)
    {
      index -= node->num;
      node = node->next;

      printf("][");
    }

    uint8_t* chunk = SsQueueNodeToChunkOperatorIndex(_this, node, (size_t)index);

    uint64_t client = 0;
    SsQueueMemcpyChunk(_this, &client, chunk);

    printf("%i", (int)client);

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
  int index = _this->indexBack - 1;

  if(index < 0)
  {
    node = node->previous;

    // use new node in arithmetic
    index = node->num + index;
  }

  chunk = SsQueueNodeToChunkOperatorIndex(_this, node, (size_t)index);

  return chunk;
}

static void SsQueueStateChangeProcessRolloverBackPrevious(ssQueue* _this)
{
  int index = _this->indexBack;

  if(index < 0)
  {
    SsQueueNode* node = _this->back;

    node = node->previous;

    _this->back = node;

    // use new node in arithmetic
    _this->indexBack = node->num + index;
  }
}

static void SsQueueStateChangeProcessRolloverBackNext(ssQueue* _this)
{
  SsQueueNode* node = _this->back;
  int index = _this->indexBack;

  if(index >= node->num)
  {
    _this->back = node->next;

    // use old node in arithmetic
    _this->indexBack = index - node->num;
  }
}

static void SsQueueStateChangeProcessRolloverFrontPrevious(ssQueue* _this)
{
  int index = _this->indexFront;

  if(index < 0)
  {
    SsQueueNode* node = _this->front;

    node = node->previous;

    _this->front = node;

    // use new node in arithmetic
    _this->indexFront = node->num + index;
  }
}

static void SsQueueStateChangeProcessRolloverFrontNext(ssQueue* _this)
{
  SsQueueNode* node = _this->front;
  int index = _this->indexFront;

  if(index >= node->num)
  {
    _this->front = node->next;

    // use old node in arithmetic
    _this->indexFront = index - node->num;
  }
}

static bool SsQueueResizeNewPool(ssQueue* _this, size_t minimumCapacity)
{
  bool result = false;

  int diff = 0;

  size_t size = 0;

  uint8_t* unaligned = 0;
  uint8_t* aligned = 0;

  SsQueuePool* pool = 0;

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

  size = SsQueueGetPoolSizeOf(_this, (size_t)diff);

  if(minimumCapacity > 0)
    size += SsQueueGetSizeOfSsQueueHeader();

  aligned = blah_aligned_alloc(size, &unaligned, true);

  if(minimumCapacity > 0)
    aligned += SsQueueGetSizeOfSsQueueHeader();

  pool = (SsQueuePool*)aligned;

  if( !pool)
    goto error;

  pool->previous = 0;
  pool->next = 0;
  SsQueuePoolSetUnaligned(pool, unaligned);
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

    int count_lhs = (_this->indexBack + _this->back->num) % _this->back->num;

    int count_rhs = _this->back->num - count_lhs;

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
      splitRhs->chunk = SsQueueNodeToChunkOperatorIndex(_this, _this->back, (size_t)_this->indexBack);
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

static bool SsQueueResize(ssQueue* _this, size_t minimumCapacity)
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

ssQueue* SsQueueConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize)
{
  uint8_t* result = 0;

  ssQueue _this = {0};

  if(sizeOf <= 0 || minimumCapacity <= 0 || minimumCapacity > maximumCapacity || !resize)
    goto error;

  _this.resize = resize;
  _this.capacity = maximumCapacity;

  _this.sizeOfRef = sizeOf;
  _this.sizeOf = (int)SsQueueGetSizeOfChunk( (size_t)sizeOf);

  if( !SsQueueResize( &_this, (size_t)minimumCapacity) || !_this.head)
    goto error;

  result = (uint8_t*)_this.head - (ptrdiff_t)SsQueueGetSizeOfSsQueueHeader();

  SsQueueMemcpySsQueue(result, &_this);

error:
  return (ssQueue*)result;
}

int SsQueueDestruct(ssQueue** reference/*_this*/)
{
  int result = -1;
  int numChunks = 0;

  ssQueue* _this = 0;

  if( !reference)
    goto error;

  _this = reference[0];

  if( !_this)
    goto error;

  numChunks = _this->numChunks;

  SsQueuePoolListFree(_this->tail);

  reference[0] = 0;

  result = numChunks;

error:
  return result;
}

int SsQueueNum(ssQueue* _this)
{
  int result = -1;

  if( !_this)
    goto error;

  result = _this->numChunks;

error:
  return result;
}

int SsQueueReset(ssQueue* _this)
{
  int result = -1;
  int numChunksRef = 0;

  if( !_this)
    goto error;

  numChunksRef = _this->numChunks;

  _this->front = _this->back;

  _this->numChunks = 0;

  _this->indexBack = 0;
  _this->indexFront = 0;

  _this->counter++;

  result = numChunksRef;

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

  chunk = SsQueueNodeToChunkOperatorIndex(_this, _this->back, (size_t)_this->indexBack);

  _this->indexBack++;

  // putting this call after _this->indexBack++ instead of before only works because we are a rotating queue
  SsQueueStateChangeProcessRolloverBackNext(_this);

  _this->numChunks++;

  SsQueueMemcpyChunk(_this, chunk, client);

#if BLAH_DEBUG
  printf("pushed to back %i;", (int)( *(int64_t*)client) );
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

  if( !_this || !client || _this->numChunks <= 0)
    goto error;

  _this->indexBack--;

  SsQueueStateChangeProcessRolloverBackPrevious(_this);

  chunk = SsQueueNodeToChunkOperatorIndex(_this, _this->back, (size_t)_this->indexBack);

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

  _this->indexFront--;

  SsQueueStateChangeProcessRolloverFrontPrevious(_this);

  chunk = SsQueueNodeToChunkOperatorIndex(_this, _this->front, (size_t)_this->indexFront);

  _this->numChunks++;

  SsQueueMemcpyChunk(_this, chunk, client);

#if BLAH_DEBUG
  printf("pushed to front %i;", (int)( *(int64_t*)client) );
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

  chunk = SsQueueNodeToChunkOperatorIndex(_this, _this->front, (size_t)_this->indexFront);

  _this->indexFront++;

  // putting this call after _this->indexFront++ instead of before only works because we are a rotating queue
  SsQueueStateChangeProcessRolloverFrontNext(_this);

  _this->numChunks--;

  SsQueueMemcpyChunk(_this, client, chunk);

#if BLAH_DEBUG
  printf("popped from front %i;", (int)( *(int64_t*)client) );
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

  if( !_this || !client || _this->numChunks <= 0)
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

  if( !_this || !client || _this->numChunks <= 0)
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

  if( !_this || !client || _this->numChunks <= 0)
    goto error;

  chunk = SsQueueNodeToChunkOperatorIndex(_this, _this->front, (size_t)_this->indexFront);

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

  if( !_this || !client || _this->numChunks <= 0)
    goto error;

  chunk = SsQueueNodeToChunkOperatorIndex(_this, _this->front, (size_t)_this->indexFront);

  if( !chunk)
    goto error;

  SsQueueMemcpyChunk(_this, chunk, client);

  result = true;

error:
  return result;
}

bool SsQueueGetAt(ssQueue* _this, int index, void* client)
{
  bool result = false;

  if( !_this || !client || index < 0 || index >= _this->numChunks)
    goto error;

  index += _this->indexFront;

  for(SsQueueNode* node = _this->front; index >= 0; node = node->next)
  {
    if(index < node->num)
    {
      uint8_t* chunk = SsQueueNodeToChunkOperatorIndex(_this, node, (size_t)index);

      SsQueueMemcpyChunk(_this, client, chunk);

      result = true;

      break;
    }

    index -= node->num;
  }

error:
  return result;
}

bool SsQueueSetAt(ssQueue* _this, int index, void* client)
{
  bool result = false;

  if( !_this || !client || index < 0 || index >= _this->numChunks)
    goto error;

  index += _this->indexFront;

  for(SsQueueNode* node = _this->front; index >= 0; node = node->next)
  {
    if(index < node->num)
    {
      uint8_t* chunk = SsQueueNodeToChunkOperatorIndex(_this, node, (size_t)index);

      SsQueueMemcpyChunk(_this, chunk, client);

      result = true;

      break;
    }

    index -= node->num;
  }

error:
  return result;
}
