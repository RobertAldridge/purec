
// ssQueue.cpp
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

#if 1
struct SsQueueNode
{
  SsQueueNode* previous;
  SsQueueNode* next;

  uint8_t* chunk;

  int num;

  int padding;
};
#endif

struct SsQueuePool
{
#if 1
  SsQueueNode back;
  SsQueueNode front;
#endif

  SsQueuePool* previous;
  SsQueuePool* next;

  int unaligned;

  int num;
};

struct ssQueue
{
#if 1
  SsQueueNode* back;
  SsQueueNode* front;
#else
  SsQueuePool* current;
#endif

  SsQueuePool* head;
  SsQueuePool* tail;

  int numPools;

  int numChunks;

#if 1
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

  //int padding;
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

//static uint8_t* SsQueuePoolToFirstChunk(SsQueuePool* pool)
//  { return (uint8_t*)pool + SsQueueGetSizeOfPoolHeader(); }

//static uint8_t* SsQueueChunkToChunkPrevious(ssQueue* _this, uint8_t* chunk)
//  {return chunk - (ptrdiff_t)_this->sizeOf; }

//static uint8_t* SsQueueChunkToChunkNext(ssQueue* _this, uint8_t* chunk)
//  { return chunk + (size_t)_this->sizeOf; }

static uint8_t* SsQueueNodeToChunkOperatorIndex(ssQueue* _this, SsQueueNode* node, size_t index)
  { return node->chunk + index * (size_t)_this->sizeOf; }

static void SsQueueMemcpySsQueue(uint8_t* destination, ssQueue* source)
  { memcpy(destination, source, sizeof(ssQueue) ); }

static void SsQueueMemcpyChunk(ssQueue* _this, void* destination, void* source)
  { memcpy(destination, source, (size_t)_this->sizeOfRef); }

static void SsQueuePoolListFree(SsQueuePool* current)
{
  for(SsQueuePool* previous = 0; current; current = previous)
  {
    previous = current->previous;

    free(SsQueuePoolGetUnaligned(current) );
  }
}

#if 1
static uint8_t* SsQueueGetPreviousBackChunk(ssQueue* _this)
{
  uint8_t* chunk = 0;

  SsQueueNode* node = _this->back;
  int index = _this->indexBack - 1;

  if(index < 0)
  {
    if(index < -1)
      goto error;

    node = node->previous;

    index = node->num - 1;
  }

  chunk = SsQueueNodeToChunkOperatorIndex(_this, node, (size_t)index);

error:
  return chunk;
}
#endif

static uint8_t* SsQueueGetPreviousFrontChunk(ssQueue* _this)
{
  uint8_t* chunk = 0;

  SsQueueNode* node = _this->front;
  int index = _this->indexFront - 1;

  if(index < 0)
  {
    if(index < -1)
      goto error;

    node = node->previous;

    index = node->num - 1;
  }

  chunk = SsQueueNodeToChunkOperatorIndex(_this, node, (size_t)index);

error:
  return chunk;
}

#if 1
static bool SsQueueStateChangeProcessRolloverBackPrevious(ssQueue* _this)
{
  bool result = false;

  int index = _this->indexBack;

  if(index < 0)
  {
    SsQueueNode* node = _this->back;

    if(index < -1)
      goto error;

    _this->back = node->previous;

    _this->indexBack = node->num - 1;
  }

  result = true;

error:
  return result;
}

static bool SsQueueStateChangeProcessRolloverBackNext(ssQueue* _this)
{
  bool result = false;

  SsQueueNode* node = _this->back;
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

static bool SsQueueStateChangeProcessRolloverFrontPrevious(ssQueue* _this)
{
  bool result = false;

  int index = _this->indexFront;

  if(index < 0)
  {
    SsQueueNode* node = _this->front;

    if(index < -1)
      goto error;

    _this->front = node->previous;

    _this->indexFront = node->num - 1;
  }

  result = true;

error:
  return result;
}

static bool SsQueueStateChangeProcessRolloverFrontNext(ssQueue* _this)
{
  bool result = false;

  SsQueueNode* node = _this->front;
  int index = _this->indexFront;

  if(index >= node->num)
  {
    if(index > node->num)
      goto error;

    _this->front = node->next;

    _this->indexFront = 0;
  }

  result = true;

error:
  return result;
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

  aligned = blah_aligned_alloc(size, &unaligned, false);

  if(minimumCapacity > 0)
    aligned += SsQueueGetSizeOfSsQueueHeader();

  pool = (SsQueuePool*)aligned;

  if( !pool)
    goto error;

  pool->next = 0;
  SsQueuePoolSetUnaligned(pool, unaligned);
  pool->num = diff;

  if( !_this->head)
  {
    _this->head = pool;

#if 0
struct SsQueueNode
{
  SsQueueNode* previous;
  SsQueueNode* next;

  uint8_t* chunk;

  int num;

  int padding;
};

uint8_t* SsQueuePoolToChunkOperatorIndex(ssQueue* _this, SsQueuePool* pool, size_t index)
  { return (uint8_t*)pool + SsQueueGetPoolSizeOf(_this, index); }
#endif

    SsQueueNode* node = &pool->back;
    node->chunk = SsQueuePoolToChunkOperatorIndex(_this, pool, 0);
    node->num = pool->num;

    node->previous = node;
    node->next = node;

    _this->back = node;
    _this->front = node;

    _this->indexBack = 0;
    _this->indexFront = 0;
  }
  else// if(_this->head)
  {
    _this->tail->next = pool;
    pool->previous = _this->tail;

    int count_back = _this->indexBack;

    int count_front = _this->back->num - count_back;

#if 0
back -> new pool -> front

 B
 F
[0 1 2 3 4 5 6 7 8 9]
 a b c d e f g h i j


 F                        B         F
[0 1 2 3 4 5 6 7 8 9] -> [pool] -> [0 1 2 3 4 5 6 7 8 9]
 a b c d e f g h i j                a b c d e f g h i j


           B
           F
[0 1 2 3 4 5 6 7 8 9]
 f g h i j a b c d e


                B         F
[0 1 2 3 4] -> [pool] -> [5 6 7 8 9] -> [0 1 2 3 4]
 f g h i j                a b c d e      f g h i j

struct SsQueueNode
{
  SsQueueNode* previous;
  SsQueueNode* next;
  uint8_t* chunk;
  int num;
};

struct SsQueuePool
{
  SsQueueNode back;
  SsQueueNode front;
};

struct ssQueue
{
  SsQueueNode* back;
  SsQueueNode* front;
  int indexBack;
  int indexFront;
};
#endif

    if(count_back && count_front)
    {
      // split

      // new pool; becomes new back
      SsQueueNode* node = &pool->back;
      node->chunk = SsQueuePoolToChunkOperatorIndex(_this, pool, 0);
      node->num = pool->num;

      // new front split; becomes new front (next from new pool)
      //
      // splits the old front node, starting at old front node index, to end of old front node chunk
      SsQueueNode* newFrontSplit = &pool->front;
      newFrontSplit->chunk = SsQueueNodeToChunkOperatorIndex(_this, _this->front, (size_t)_this->indexFront);
      newFrontSplit->num = count_front;

      // new split (previous from new pool)
      //
      // splits the old back node (though it will no longer be the back node after the split)
      //
      // from beginning of old back node chunk, to one before old back node index (new length is old back node index)
      SsQueueNode* oldBackSplit = _this->back;
      //oldBackSplit->chunk = _this->back->chunk;
      oldBackSplit->num = count_back;

      oldBackSplit->next = node;
      node->previous = oldBackSplit;

      node->next = newFrontSplit;
      newFrontSplit->previous = node;

      _this->back = node;
      _this->front = newFrontSplit;

      _this->indexBack = 0;
      _this->indexFront = 0;
    }
    else if( !count_front)
    {
      // todo
    }
    else// if( !count_back)
    {
      // no split

      SsQueueNode* node = &pool->back;
      node->chunk = SsQueuePoolToChunkOperatorIndex(_this, pool, 0);
      node->num = pool->num;

      SsQueueNode* previous = _this->back->previous;

      SsQueueNode* next = _this->front;

      previous->next = node;

      node->previous = previous;
      node->next = next;

      next->previous = node;

      _this->back = node;
      // _this->front = node; doesn't change

      _this->indexBack = 0;
      _this->indexFront = 0;
    }
  }

  _this->tail = pool;

  _this->numPools++;

  _this->max += diff;

  // no change
  // _this->numChunks
  // _this->counter
  // _this->resize
  // _this->capacity
  // _this->sizeOfRef
  // _this->sizeOf

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

  memcpy(result, &_this, sizeof(ssQueue) );

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

  SsQueuePoolListFree(_this->head);

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

  SsQueueNode* node = 0;

  if( !_this)
    goto error;

  numChunksRef = _this->numChunks;

  node = _this->back;

#if 1
  _this->front = node;
#else
  _this->current = pool;
#endif

  _this->numChunks = 0;

#if 1
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

  if( !SsQueueStateChangeProcessRolloverBackNext(_this) )
    goto error;

  chunk = SsQueueNodeToChunkOperatorIndex(_this, _this->back, (size_t)_this->indexBack);

  _this->indexBack++;

  _this->numChunks++;

  SsQueueMemcpyChunk(_this, chunk, client);

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

  if( !SsQueueStateChangeProcessRolloverBackPrevious(_this) )
    goto error;

  chunk = SsQueueNodeToChunkOperatorIndex(_this, _this->back, (size_t)_this->indexBack);

  _this->numChunks--;

  SsQueueMemcpyChunk(_this, client, chunk);

  result = true;

error:
  return result;
}

#if 1
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

  if( !SsQueueStateChangeProcessRolloverFrontPrevious(_this) )
    goto error;

  chunk = SsQueueNodeToChunkOperatorIndex(_this, _this->front, (size_t)_this->indexFront);

  _this->numChunks++;

  SsQueueMemcpyChunk(_this, chunk, client);

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

  if( !SsQueueStateChangeProcessRolloverFrontNext(_this) )
    goto error;

  chunk = SsQueueNodeToChunkOperatorIndex(_this, _this->front, (size_t)_this->indexFront);

  _this->indexFront++;

  _this->numChunks--;

  SsQueueMemcpyChunk(_this, client, chunk);

  result = true;

error:
  return result;
}
#endif

#if 1
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
#endif

bool SsQueueGetFront(ssQueue* _this, void* client)
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !client || _this->numChunks <= 0)
    goto error;

  chunk = SsQueueGetPreviousFrontChunk(_this);

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

  chunk = SsQueueGetPreviousFrontChunk(_this);

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

  SsQueueNode* node = 0;

  if( !_this || !client || index < 0 || index >= _this->numChunks)
    goto error;

  node = _this->front;

  for(int walk = 0; walk < _this->numChunks; node = node->next)
  {
    if(index >= walk && index < walk + node->num)
    {
      uint8_t* chunk = SsQueueNodeToChunkOperatorIndex(_this, node, (size_t)(index - walk) );

      SsQueueMemcpyChunk(_this, client, chunk);

      result = true;

      break;
    }

    walk += node->num;
  }

error:
  return result;
}

bool SsQueueSetAt(ssQueue* _this, int index, void* client)
{
  bool result = false;

  SsQueueNode* node = 0;

  if( !_this || !client || index < 0 || index >= _this->numChunks)
    goto error;

  node = _this->front;

  for(int walk = 0; walk < _this->numChunks; node = node->next)
  {
    if(index >= walk && index < walk + node->num)
    {
      uint8_t* chunk = SsQueueNodeToChunkOperatorIndex(_this, node, (size_t)(index - walk) );

      SsQueueMemcpyChunk(_this, chunk, client);

      result = true;

      break;
    }

    walk += node->num;
  }

error:
  return result;
}
