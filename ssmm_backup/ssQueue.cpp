
// ssQueue.cpp
// Robert Aldridge, code
// Robert Aldridge and Charlie Burns, design

#include "ssQueue.h"

#include <cstdio>
using std::printf;

struct SsQueueNode
{
  SsQueueNode* previous;
  SsQueueNode* next;

  uint8_t* chunk;

  int num;

  int padding;
};

struct SsQueuePool
{
  SsQueueNode back;
  SsQueueNode front;

  SsQueuePool* previous;
  SsQueuePool* next;

  //uint8_t* alloc;
  int unaligned;

  int num;

  // uint8_t chunk[]
};

struct ssQueue
{
  // if node list is circular then only need back and front
  SsQueueNode* back;
  SsQueueNode* front;

  // if node list is circular then don't need nodeHead or nodeTail
  //SsQueueNode* nodeHead;
  //SsQueueNode* nodeTail;

  SsQueuePool* head;
  SsQueuePool* tail;

  int numPools;

  int numChunks;
  int indexBack;
  int indexFront;
  int max;

  int counter;

  int resize;
  int capacity;

  int sizeOfRef;
  int sizeOf;
};

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

// ~9,000,000 terabytes is limit for addressing via int64_t

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// alignment is typically sizeof(void*)
// result is either size if already aligned, otherwise returns the minimum value larger than size that is aligned
static size_t ALIGNEDOFVALUE(size_t size);

// only for node header
static size_t SsQueueGetSizeOfNode();

// only for pool header
static size_t SsQueueGetSizeOfPool();

// only for ssQueue header
static size_t SsQueueGetSizeOfSsQueue();

// returns entire chunk size (node header + client data)
static size_t SsQueueGetSizeOfChunk(size_t sizeOf);

static void PoolSetUnaligned(SsQueuePool* pool, uint8_t* unaligned);
static uint8_t* PoolGetUnaligned(SsQueuePool* pool);

// alignment is typically sizeof(void*)
// assumes size is already a multiple of alignment
// pass result of MALLOCSIZEPADDED as size parameter to malloc to allow for post-malloc alignment
static size_t MALLOCSIZEPADDED(size_t size);

// alignment is typically sizeof(void*)
// assumes the parameter passed to malloc is sufficiently padded
// ptr is of type uint8_t*
// 'address' is of type ptrdiff_t, assigned to the value (uint8_t*)ptr - (uint8_t*)0
// pass return value of malloc to MALLOCRETURNALIGN (pass stored value not the literal malloc call)
static uint8_t* MALLOCRETURNALIGN(uint8_t* unaligned, ptrdiff_t address);

static size_t SSQUEUE_GET_POOL_SIZEOF(ssQueue* _this, size_t nmemb);

static uint8_t* SSQUEUE_POOL_TO_CHUNK_OPERATOR_INDEX(ssQueue* _this, SsQueuePool* pool, size_t index);

static uint8_t* SSQUEUE_NODE_TO_CHUNK_OPERATOR_INDEX(ssQueue* _this, SsQueueNode* node, size_t index);

// specifically when one side is passed by the client, in which case we have to use the unpadded sizeof
static void SSQUEUE_MEMCPY_CHUNK(ssQueue* _this, void* destination, void* source);

// when you're forced to use a compiler/runtime that claims to conform yet
// doesn't implement aligned_alloc (*cough* microsoft)
//   void* aligned_alloc(size_t alignment, size_t size)
//
// in this case assume alignment is sizeof(void*)
static uint8_t* cstandard_aligned_alloc(size_t size, uint8_t** unalignedRef/*unaligned;ptr*/);

static void PoolListWalk(SsQueuePool* head, bool doFree);
static void PoolListReverseAndFree(SsQueuePool* head);

// ssQueue* SsQueueConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize);

// returns the number of elements previously in the queue or -1 on error
// int SsQueueDestruct(ssQueue** reference/*_this*/);

// int SsQueueNum(ssQueue* _this);

// returns the number of nodes previously held by client or -1 on error
// int SsQueueReset(ssQueue* _this);

static bool SsQueueResize(ssQueue* _this, size_t minimumCapacity);

// bool SsQueuePush(ssQueue* _this, void* memory/*chunk*/);

/*bool SsQueueGet(ssQueue* _this, void* chunk) todo*/

// bool SsQueuePop(ssQueue* _this, void* memory/*chunk*/);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define INTEGER_MAX(lhs, rhs) (lhs >= rhs ? lhs : rhs)

//#define SSQUEUE_GET_CHUNK_PADDED_SIZEOF(_this) \
//  (size_t)_this->sizeOf

//#define SSQUEUE_GET_CHUNK_UNPADDED_SIZEOF(_this) \
//  (size_t)_this->sizeOfRef

size_t ALIGNEDOFVALUE(size_t size)
  { return (size % sizeof(void*) ) ? size + (sizeof(void*) - size % sizeof(void*) ) : size; }

// only for node header
size_t SsQueueGetSizeOfNode()
  { return 0; }

// only for pool header
size_t SsQueueGetSizeOfPool()
  { return ALIGNEDOFVALUE(sizeof(SsQueuePool) ); }

// only for ssQueue header
size_t SsQueueGetSizeOfSsQueue()
  { return ALIGNEDOFVALUE(sizeof(ssQueue) ); }

// returns entire chunk size (node header + client data)
size_t SsQueueGetSizeOfChunk(size_t sizeOf)
  { return ALIGNEDOFVALUE(sizeOf) + SsQueueGetSizeOfNode(); }

void PoolSetUnaligned(SsQueuePool* pool, uint8_t* unaligned)
  { pool->unaligned = (int)( (uint8_t*)unaligned - (uint8_t*)pool); }

uint8_t* PoolGetUnaligned(SsQueuePool* pool)
  { return (uint8_t*)pool + (ptrdiff_t)pool->unaligned; }

size_t MALLOCSIZEPADDED(size_t size)
  { return size + (sizeof(void*) - 1); }

uint8_t* MALLOCRETURNALIGN(uint8_t* unaligned, ptrdiff_t address)
  { return (address % sizeof(void*) ) ? unaligned + (sizeof(void*) - address % sizeof(void*) ) : unaligned; }

size_t SSQUEUE_GET_POOL_SIZEOF(ssQueue* _this, size_t nmemb)
  { return SsQueueGetSizeOfPool() + nmemb * (size_t)_this->sizeOf; }

uint8_t* SSQUEUE_POOL_TO_CHUNK_OPERATOR_INDEX(ssQueue* _this, SsQueuePool* pool, size_t index)
  { return (uint8_t*)pool + SSQUEUE_GET_POOL_SIZEOF(_this, index); }

uint8_t* SSQUEUE_NODE_TO_CHUNK_OPERATOR_INDEX(ssQueue* _this, SsQueueNode* node, size_t index)
  { return node->chunk + index * (size_t)_this->sizeOf; }

// specifically when one side is passed by the client, in which case we have to use the unpadded sizeof
void SSQUEUE_MEMCPY_CHUNK(ssQueue* _this, void* destination, void* source)
  { memcpy(destination, source, (size_t)_this->sizeOfRef; }

// when you're forced to use a compiler/runtime that claims to conform yet
// doesn't implement aligned_alloc (*cough* microsoft)
//   void* aligned_alloc(size_t alignment, size_t size)
//
// in this case assume alignment is sizeof(void*)
uint8_t* cstandard_aligned_alloc(size_t size, uint8_t** unalignedRef/*unaligned;ptr*/)
{
  uint8_t* aligned = 0;
  uint8_t* unaligned = 0;

  ptrdiff_t address = 0;

  if( !size || !unalignedRef)
    goto labelReturn;

  // fail if size is not a multiple of alignment
  if(size % sizeof(void*) )
    goto labelReturn;

  size = MALLOCSIZEPADDED(size);

  unaligned = (uint8_t*)malloc(size);
  if( !unaligned)
    goto labelReturn;

  *unalignedRef = unaligned;

  address = (uint8_t*)unaligned - (uint8_t*)0;

  aligned = MALLOCRETURNALIGN(unaligned, address);

labelReturn:

  return aligned;
}

void PoolListWalk(SsQueuePool* head, bool doFree)
{
  SsQueuePool* next = 0;

  for(SsQueuePool* curr = head; curr; curr = next)
  {
    next = curr->next;

    if(doFree)
      free(PoolGetUnaligned(curr) );
  }
}

void PoolListReverseAndFree(SsQueuePool* head)
{
  // we want to free pools in opposite order of their allocation

  // reverse list
  SsQueuePool* prev = 0;
  SsQueuePool* next = 0;

  for(SsQueuePool* curr = head; curr; curr = next)
  {
    next = curr->next;
    curr->next = prev;

    prev = curr;
  }

  // free pools
  PoolListWalk(prev, true);
}

ssQueue* SsQueueConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize)
{
  uint8_t* result = 0;

  ssQueue _this = {0};

  if(sizeOf <= 0 || minimumCapacity <= 0 || minimumCapacity > maximumCapacity || !resize)
    goto error;

  // _this.current = 0;

  // _this.head = 0;
  // _this.tail = 0;

  // _this.numPools = 0;

  // _this.numChunks = 0;
  // _this.index = 0;
  // _this.max = 0;

  // _this.counter = 0;

  _this.resize = resize;
  _this.capacity = maximumCapacity;

  _this.sizeOfRef = sizeOf;
  _this.sizeOf = (int)SsQueueGetSizeOfChunk( (size_t)sizeOf);

  try
  {
    if( !SsQueueResize( &_this, (size_t)minimumCapacity) || !_this.head)
      goto error;

    // extract 'this' pointer which prefixes the first pool
    result = (uint8_t*)_this.head - (ptrdiff_t)SsQueueGetSizeOfSsQueue();
  }
  catch(bad_alloc& )
  {
  }

  if( !result)
    goto error;

  // use unpadded sizeof in copy
  memcpy(result, &_this, sizeof(ssQueue) );

error:
  return (ssQueue*)result;
}

// returns the number of elements previously in the queue or -1 on error
int SsQueueDestruct(ssQueue** reference)
{
  int result = -1;
  int numChunks = 0;

  ssQueue* _this = 0;

  if( !reference)
    goto error;

  _this = reference[0];

  if( !_this)
    goto error;

  numChunks = SsQueueNum(_this);
  if(numChunks < 0)
    goto error;

  // free all pools
  PoolListReverseAndFree(_this->head);

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

// returns the number of nodes previously held by client or -1 on error
int SsQueueReset(ssQueue* _this) // todo
{
  int result = -1;
  int numChunksRef = 0;

  if( !_this || _this->numPools <= 0)
    goto error;

  numChunksRef = _this->numChunks;

  _this->front = _this->back;

  _this->numChunks = 0;
  _this->indexBack = 0;
  _this->indexFront = 0;

  _this->counter++;

  // no change
  // _this->head
  // _this->tail
  // _this->numPools
  // _this->max
  // _this->resize
  // _this->capacity
  // _this->sizeOfRef
  // _this->sizeOf

  result = numChunksRef;

error:
  return result;
}

bool SsQueueResize(ssQueue* _this, size_t minimumCapacity) // todo
{
  bool result = false;

  if( !_this || _this->numChunks != _this->max || minimumCapacity > _this->capacity)
    goto error;

  if(minimumCapacity > 0 && _this->numPools > 0)
    goto error;

  // not as much an error per say, since this is expected behavior,
  // but we still return an error since caller is asking to grow and our response is to not grow
  //
  // nop if 'old capacity' >= maximumCapacity
  if(_this->max >= _this->capacity)
    goto error;

  if(_this->front != _this->back)
    goto;

  int diff = 0;

  // start is initial capacity
  // must be greater than zero
  // minimumCapacity <= maximumCapacity
  /*int minimumCapacity;*/

  // 'initial capacity * sizeof(client type)' must be a reasonable size to pass to malloc

  // first pool grow() behavior
  // 'new capacity' == minimumCapacity
  if(minimumCapacity > 0)
  {
    diff = (int)minimumCapacity;
  }

  // non-first grow() behavior, if resize < -1
  //
  // 'new capacity' == 2 * 'old capacity',
  // if 'old capacity' <= abs(resize + 1) and 2 * 'old capacity' <= maximumCapacity
  //
  // 'new capacity' == 'old capacity' + abs(resize),
  // if 'old capacity' > abs(resize + 1) and 'old capacity' + abs(resize + 1) <= maximumCapacity
  //
  // 'new capacity' == maximumCapacity,
  // if 'old capacity' > abs(resize + 1) and 'old capacity' + abs(resize + 1) > maximumCapacity
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

  // non-first grow() behavior, if resize == -1
  //
  // 'new capacity' == 2 * 'old capacity',
  // if 2 * 'old capacity' <= maximumCapacity
  //
  // 'new capacity' == maximumCapacity,
  // if 2 * 'old capacity' > maximumCapacity
  else if(_this->resize == -1)
  {
    diff = _this->max;

    if(_this->max + diff > _this->capacity)
      diff = _this->capacity - _this->max;
  }

  // resize cannot be zero.  to disable grow() set minimumCapacity and maximumCapacity to same value
  //
  // resize != 0 is verified during construction of ssQueue instance

  // non-first grow() behavior, if resize > 0
  //
  // 'new capacity' == 'old capacity' + resize,
  // if 'old capacity' + resize <= maximumCapacity
  //
  // 'new capacity' == maximumCapacity,
  // if 'old capacity' + resize > maximumCapacity
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

  /*int resize;*/

  /*int capacity;*/

  if( !diff)
    goto error;

  // already aligned
  size_t size = SSQUEUE_GET_POOL_SIZEOF(_this, (size_t)diff);

  if(minimumCapacity > 0)
    size += SsQueueGetSizeOfSsQueue();

  uint8_t* unaligned = 0;
  uint8_t* aligned = cstandard_aligned_alloc(size, &unaligned);

  if(minimumCapacity > 0)
    aligned += SsQueueGetSizeOfSsQueue();

  SsQueuePool* pool = (SsQueuePool*)aligned;

  if( !pool)
    goto error;

  pool->next = 0;
  PoolSetUnaligned(pool, unaligned);
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

uint8_t* SSQUEUE_POOL_TO_CHUNK_OPERATOR_INDEX(ssQueue* _this, SsQueuePool* pool, size_t index)
  { return (uint8_t*)pool + SSQUEUE_GET_POOL_SIZEOF(_this, index); }
#endif

    SsQueueNode* node = &pool->back; // todo
    node->chunk = SSQUEUE_POOL_TO_CHUNK_OPERATOR_INDEX(_this, pool, 0); // todo
    node->num = pool->num; // todo

    node->previous = node; // todo
    node->next = node; // todo

    _this->back = node; // todo
    _this->front = node; // todo

    _this->indexBack = 0; // todo
    _this->indexFront = 0; // todo
  }
  else// if(_this->head)
  {
    _this->tail->next = pool;
    pool->previous = _this->tail;

    int count_back = _this->indexBack; // todo

    int count_front = _this->back->num - count_back; // todo

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

    if(count_back) // todo
    {
      // split

      // new pool; becomes new back
      SsQueueNode* node = &pool->back;
      node->chunk = SSQUEUE_POOL_TO_CHUNK_OPERATOR_INDEX(_this, pool, 0);
      node->num = pool->num;

      // new front split; becomes new front (next from new pool)
      //
      // splits the old front node, starting at old front node index, to end of old front node chunk
      SsQueueNode* newFrontSplit = &pool->front;
      newFrontSplit->chunk = SSQUEUE_NODE_TO_CHUNK_OPERATOR_INDEX(_this, _this->front, _this->indexFront);
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
    else// if( !count_back) todo
    {
      // no split

      SsQueueNode* node = &pool->back; // todo
      node->chunk = SSQUEUE_POOL_TO_CHUNK_OPERATOR_INDEX(_this, pool, 0); // todo
      node->num = pool->num; // todo

      SsQueueNode* previous = _this->back->previous;

      SsQueueNode* next = _this->front;

      previous->next = node;

      node->previous = previous; // todo
      node->next = next; // todo

      next->previous = node;

      _this->back = node; // todo
      // _this->front = node; doesn't change

      _this->indexBack = 0; // todo
      _this->indexFront = 0; // todo
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

bool SsQueuePushBack(ssQueue* _this, void* memory/*chunk*/) // todo
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !memory || _this->numChunks > _this->max)
    goto error;

  if(_this->numChunks == _this->max)
  {
    if( !SsQueueResize(_this, 0) )
      goto error;
  }

  if(_this->numChunks == _this->max)
    goto error;

  // what is expected to occassionally change upon call
  // _this->back

  // what is expected to change every call
  // _this->numChunks
  // _this->indexBack

  if(_this->indexBack < 0 || _this->indexBack >= _this->back->num)
    goto error;

  // _this->indexBack >= 0 && _this->indexBack < _this->back->num

  chunk = SSQUEUE_POOL_TO_CHUNK_OPERATOR_INDEX(_this, _this->back, _this->indexBack);

  // move to next chunk
  _this->indexBack++;

  // if(_this->indexBack < _this->back->num)
  //   move to next chunk
  // else if(_this->indexBack >= _this->back->num)
  //   move to next pool

  // after grabbing chunk
  if(_this->indexBack >= _this->back->num)
  {
    // move to next pool (should never be at tail since if out of space it would
    // have called resize earlier in SsQueuePush call)

    if(_this->back == _this->tail)
      goto error;

    _this->back = _this->back->next;

    _this->indexBack = 0;
  }

  // _this->indexBack >= 0 && _this->indexBack < _this->back->num

  _this->numChunks++;

  SSQUEUE_MEMCPY_CHUNK(_this, chunk, memory);

  // no change
  // _this->front
  // _this->head
  // _this->tail
  // _this->numPools
  // _this->indexFront
  // _this->max
  // _this->counter
  // _this->resize
  // _this->capacity
  // _this->sizeOfRef
  // _this->sizeOf

  result = true;

error:
  return result;
}

bool SsQueuePushFront(ssQueue* _this, void* memory/*chunk*/) // todo
{
  bool result = false;

  SsQueueNode* chunk = 0;

  if( !_this || !memory || _this->numChunks > _this->max)
    goto error;

  if(_this->numChunks == _this->max)
  {
    if( !SsQueueResize(_this, 0) )
      goto error;
  }

  if(_this->numChunks == _this->max)
    goto error;

  // what is expected to occassionally change upon call
  // _this->front

  // what is expected to change every call
  // _this->numChunks
  // _this->indexFront

  if(_this->indexFront < 0 || _this->indexFront >= _this->front->num)
    goto error;

  // _this->indexFront >= 0 && _this->indexFront < _this->front->num

  // move to previous chunk
  _this->indexFront--;

  // if(_this->indexFront < 0)
  //   move to next pool
  // else if(_this->indexFront >= 0)
  //   move to next chunk

  // before grabbing chunk
  if(_this->indexFront < 0)
  {
    // move to previous pool (should never be at head since in that case
    // _this->numChunks would be zero)

    if(_this->front == _this->head)
      goto error;

    _this->front = _this->front->previous;

    _this->indexFront = _this->front->num - 1;
  }

  // _this->indexFront >= 0 && _this->indexFront < _this->front->num

  chunk = SSQUEUE_POOL_TO_CHUNK_OPERATOR_INDEX(_this, _this->front, _this->indexFront);

  _this->numChunks++;

  SSQUEUE_MEMCPY_CHUNK(_this, memory, chunk);

  // no change
  // _this->back
  // _this->head
  // _this->tail
  // _this->numPools
  // _this->indexBack
  // _this->max
  // _this->counter
  // _this->resize
  // _this->capacity
  // _this->sizeOfRef
  // _this->sizeOf

  result = true;

error:
  return result;
}

/*bool SsQueueGetBack(ssQueue* _this, void* chunk) todo*/

bool SsQueuePopBack(ssQueue* _this, void* memory/*chunk*/) // todo
{
  bool result = false;

  SsQueueNode* chunk = 0;

  if( !_this || !memory || _this->numChunks <= 0)
    goto error;

  // what is expected to occassionally change upon call
  // _this->back

  // what is expected to change every call
  // _this->numChunks
  // _this->indexBack

  if(_this->indexBack < 0 || _this->indexBack >= _this->back->num)
    goto error;

  // _this->indexBack >= 0 && _this->indexBack < _this->back->num

  // move to previous chunk
  _this->indexBack--;

  // if(_this->indexBack < 0)
  //   move to next pool
  // else if(_this->indexBack >= 0)
  //   move to next chunk

  // before grabbing chunk
  if(_this->indexBack < 0)
  {
    // move to previous pool (should never be at head since in that case
    // _this->numChunks would be zero)

    if(_this->back == _this->head)
      goto error;

    _this->back = _this->back->previous;

    _this->indexBack = _this->back->num - 1;
  }

  // _this->indexBack >= 0 && _this->indexBack < _this->back->num

  chunk = SSQUEUE_POOL_TO_CHUNK_OPERATOR_INDEX(_this, _this->back, _this->indexBack);

  _this->numChunks--;

  SSQUEUE_MEMCPY_CHUNK(_this, memory, chunk);

  // no change
  // _this->front
  // _this->head
  // _this->tail
  // _this->numPools
  // _this->indexFront
  // _this->max
  // _this->counter
  // _this->resize
  // _this->capacity
  // _this->sizeOfRef
  // _this->sizeOf

  result = true;

error:
  return result;
}

/*bool SsQueueGetFront(ssQueue* _this, void* chunk) todo*/

bool SsQueuePopFront(ssQueue* _this, void* memory/*chunk*/) // todo
{
  bool result = false;

  uint8_t* chunk = 0;

  if( !_this || !memory || _this->numChunks <= 0)
    goto error;

  // what is expected to occassionally change upon call
  // _this->front

  // what is expected to change every call
  // _this->numChunks
  // _this->indexFront

  if(_this->indexFront < 0 || _this->indexFront >= _this->front->num)
    goto error;

  // _this->indexFront >= 0 && _this->indexFront < _this->front->num

  chunk = SSQUEUE_POOL_TO_CHUNK_OPERATOR_INDEX(_this, _this->front, _this->indexFront);

  // move to next chunk
  _this->indexFront++;

  // if(_this->indexFront < _this->front->num)
  //   move to next chunk
  // else if(_this->indexFront >= _this->front->num)
  //   move to next pool

  // after grabbing chunk
  if(_this->indexFront >= _this->front->num)
  {
    // move to next pool (should never be at tail since if out of space it would
    // have called resize earlier in SsQueuePush call)

    if(_this->front == _this->tail)
      goto error;

    _this->front = _this->front->next;

    _this->indexFront = 0;
  }

  // _this->indexFront >= 0 && _this->indexFront < _this->front->num

  _this->numChunks--;

  SSQUEUE_MEMCPY_CHUNK(_this, chunk, memory);

  // no change
  // _this->back
  // _this->head
  // _this->tail
  // _this->numPools
  // _this->indexBack
  // _this->max
  // _this->counter
  // _this->resize
  // _this->capacity
  // _this->sizeOfRef
  // _this->sizeOf

  result = true;

error:
  return result;
}
