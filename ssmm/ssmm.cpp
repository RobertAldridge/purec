
// ssmm.cpp
// Robert Aldridge and Charlie Burns

#if defined(_MSC_VER)
  #pragma warning (disable: 4711)
#endif

enum class ssmm_debug
{
  off = 0,
  constant = 1, // O(1)
  logarithmic = 2, // O(lg(n) )
  linear = 2 // O(n)
};

using enum ssmm_debug;

// dereferencing node <> client reference
struct SsmmNode
{
  // next used as magic when owned by client (when debug > 0)
  SsmmNode* next;
};

struct SsmmPool
{
  SsmmPool* previous;

  // have to keep track of my own unaligned pointer because
  // no aligned_alloc in vc runtime
  int unaligned;

  int num;
};

struct ssmm
{

  SsmmNode* freeChunks;
  SsmmPool* freePools;

  SsmmPool* poolTail;

  // have to keep track of my own unaligned pointer because
  // no aligned_alloc in vc runtime
  void* unaligned;

  int num;
  int most;
  int max;
  int resize;
  int sizeOf;

  ssmm_debug debug;
};

#include "ssmm.h"

//using enum ssmm_debug;

#include <cstddef> // ptrdiff_t, size_t
#include <cstdint> // INTPTR_MAX
#include <cstdlib> // malloc, free
#include <cstring> // memset

#include <new> // bad_alloc
using std::bad_alloc;
using std::free;
using std::malloc;
using std::memset;
using std::ptrdiff_t;
using std::size_t;
//using std::INTPTR_MAX;

// ~9,000,000 terabytes is limit for addressing via int64_t

#define SSMM_IS_DEBUG_RANGE(debug, beginInclusive, endInclusive) ( (int)debug >= (int)beginInclusive && (int)debug <= (int)endInclusive)

#define SSMM_IS_DEBUG(debug) SSMM_IS_DEBUG_RANGE(debug, ssmm_debug::constant, ssmm_debug::linear)
#define SSMM_IS_DEBUG_CONSTANT(debug) SSMM_IS_DEBUG(debug)
#define SSMM_IS_DEBUG_LOGARITHMIC(debug) SSMM_IS_DEBUG_RANGE(debug, ssmm_debug::logarithmic, ssmm_debug::linear)
#define SSMM_IS_DEBUG_LINEAR(debug) (debug == ssmm_debug::linear)

static bool SsmmIsDebug(ssmm* _this);
static bool SsmmIsDebugConstant(ssmm* _this);
static bool SsmmIsDebugLogarithmic(ssmm* _this);
static bool SsmmIsDebugLinear(ssmm* _this);
static void PoolSetUnaligned(SsmmPool* pool, void* unaligned);
static void* PoolGetUnaligned(SsmmPool* pool);

// alignment is typically sizeof(void*)
// result is either size if already aligned, otherwise returns the minimum value larger than size that is aligned
static size_t ALIGNEDOFVALUE(size_t size);

// alignment is typically sizeof(void*)
// assumes size is already a multiple of alignment
// pass result of MALLOCSIZEPADDED as size parameter to malloc to allow for post-malloc alignment
static size_t MALLOCSIZEPADDED(size_t size);

// alignment is typically sizeof(void*)
// assumes the parameter passed to malloc is sufficiently padded
// ptr is of type char*
// 'address' is of type int64_t, assigned to the value (char*)ptr - (char*)0
// pass return value of malloc to MALLOCRETURNALIGN (pass stored value not the literal malloc call)
static char* MALLOCRETURNALIGN(char* unaligned, int64_t address);

static SsmmNode* SSMM_CHUNK_CLIENT_TO_NODE(SsmmNode* client, ssmm_debug debug);
static SsmmNode* SSMM_CHUNK_NODE_TO_CLIENT(SsmmNode* node, ssmm_debug debug);
static SsmmNode* SSMM_CHUNK_POOL_TO_FIRSTNODE(SsmmPool* pool);
static SsmmNode* SSMM_CHUNK_NODE_TO_NODE_SEQUENTIAL(ssmm* _this, SsmmNode* node);
static void* cstandard_aligned_alloc(size_t size, void** unalignedRef/*unaligned;ptr*/);
static size_t SsmmGetSizeOfNode(ssmm_debug debug);
static size_t SsmmGetSizeOfPool();
static size_t SsmmGetSizeOfSsmm();
static size_t SsmmGetSizeOfChunk(size_t sizeOf, ssmm_debug debug);
static void SsmmMemset(ssmm* _this);
static void ChunkMemset(ssmm* _this, SsmmNode* chunk);

// only set 'header' to true in preparation for calling free(ptr) on the memory associated with the pool
static void PoolMemset(ssmm* _this, SsmmPool* pool, size_t num, bool header);

static SsmmPool* PoolListWalk(ssmm* _this, SsmmPool* tail, bool doFree, bool skipLast);
static bool SsmmFirstPool(ssmm* _this, int64_t initialCapacity);

// initial capacity must be larger than zero
//
// you can delay the overhead of creating a pool by setting isTentative to true.  in that case, the first pool will be
// created upon first call to SsmmAlloc.  note that in this case calls to SsmmSetResize will fail until after the first
// call to SsmmAlloc
static bool SsmmSsmm(ssmm* _this, size_t sizeOf, size_t initialCapacity, bool isTentative, ssmm_debug debug);

// ssmm* SsmmConstruct(int sizeOf, int initialCapacity, bool isTentative, ssmm_debug debug)
// int SsmmDestruct(ssmm** _thisRef/*_this*/)
// int SsmmNum(ssmm* _this)
// bool SsmmSetResize(ssmm* _this, int resize)

static int64_t SsmmResetOrClear(ssmm* _this, bool freeAppendedPools);

// int SsmmReset(ssmm* _this)
// int SsmmClear(ssmm* _this)

static bool SsmmResize(ssmm* _this);

// void* SsmmAlloc(ssmm* _this)
// bool SsmmFree(ssmm* _this, void** memory/*chunk*/)

static bool SsmmFreeDebugCheckConstant(SsmmNode* chunk);
static bool SsmmFreeDebugCheckLogarithmic(ssmm* _this, SsmmNode* chunk);
static bool SsmmFreeDebugCheckLinear(ssmm* _this, SsmmNode* chunk);

//#define INTEGER_MAX(lhs, rhs) (lhs >= rhs ? lhs : rhs)

bool SsmmIsDebug(ssmm* _this) { return SSMM_IS_DEBUG(_this->debug); }
bool SsmmIsDebugConstant(ssmm* _this) { return SSMM_IS_DEBUG_CONSTANT(_this->debug); }
bool SsmmIsDebugLogarithmic(ssmm* _this) { return SSMM_IS_DEBUG_LOGARITHMIC(_this->debug); }
bool SsmmIsDebugLinear(ssmm* _this) { return SSMM_IS_DEBUG_LINEAR(_this->debug); }

void PoolSetUnaligned(SsmmPool* pool, void* unaligned) { pool->unaligned = (int)( (char*)unaligned - (char*)pool); }
void* PoolGetUnaligned(SsmmPool* pool) { return (char*)pool + (int64_t)pool->unaligned; }

size_t ALIGNEDOFVALUE(size_t size) { return (size % sizeof(void*) ) ? size + (sizeof(void*) - size % sizeof(void*) ) : size; }

size_t MALLOCSIZEPADDED(size_t size) { return size + (sizeof(void*) - 1); }

char* MALLOCRETURNALIGN(char* unaligned, int64_t address) { return (address % sizeof(void*) ) ? unaligned + (sizeof(void*) - address % sizeof(void*) ) : unaligned; }

SsmmNode* SSMM_CHUNK_CLIENT_TO_NODE(SsmmNode* client, ssmm_debug debug) { return (SsmmNode*)( (char*)client - SsmmGetSizeOfNode(debug) ); }

SsmmNode* SSMM_CHUNK_NODE_TO_CLIENT(SsmmNode* node, ssmm_debug debug) { return (SsmmNode*)( (char*)node + SsmmGetSizeOfNode(debug) ); }

SsmmNode* SSMM_CHUNK_POOL_TO_FIRSTNODE(SsmmPool* pool) { return (SsmmNode*)( (char*)pool + SsmmGetSizeOfPool() ); }

SsmmNode* SSMM_CHUNK_NODE_TO_NODE_SEQUENTIAL(ssmm* _this, SsmmNode* node) { return (SsmmNode*)( (char*)node + _this->sizeOf); }

// when you're forced to use a compiler/runtime that claims to conform yet doesn't implement aligned_alloc (*cough* microsoft)
//   void* aligned_alloc(size_t alignment, size_t size)

// in this case assume alignment is sizeof(void*)
void* cstandard_aligned_alloc(size_t size, void** unalignedRef/*unaligned;ptr*/)
{
  char* aligned = 0;
  char* unaligned = 0;

  int64_t address = 0;

  if( !size || !unalignedRef)
    goto labelReturn;

  // fail if size is not a multiple of alignment
  if(size % sizeof(void*) )
    goto labelReturn;

  size = MALLOCSIZEPADDED(size);

  unaligned = (char*)malloc(size);
  if( !unaligned)
    goto labelReturn;

  *unalignedRef = unaligned;

  address = (char*)unaligned - (char*)0;

  aligned = MALLOCRETURNALIGN(unaligned, address);

labelReturn:

  return aligned;
}

// only for node header
size_t SsmmGetSizeOfNode(ssmm_debug debug)
{
  size_t result = ALIGNEDOFVALUE(sizeof(SsmmNode) );

  return SSMM_IS_DEBUG(debug) ? result : 0;
}

// only for pool header
size_t SsmmGetSizeOfPool()
{
  size_t result = ALIGNEDOFVALUE(sizeof(SsmmPool) );
  return result;
}

// only for ssmm header
size_t SsmmGetSizeOfSsmm()
{
  size_t result = ALIGNEDOFVALUE(sizeof(ssmm) );
  return result;
}

// returns entire chunk size (node header + client data)
size_t SsmmGetSizeOfChunk(size_t sizeOf, ssmm_debug debug)
{
  size_t result = ALIGNEDOFVALUE(sizeOf);

  return result + SsmmGetSizeOfNode(debug);
}

void SsmmMemset(ssmm* _this)
{
  memset(_this, 0, SsmmGetSizeOfSsmm() );
}

void ChunkMemset(ssmm* _this, SsmmNode* chunk)
{
  memset(chunk, 0, (size_t)_this->sizeOf);
}

// if header is true then will memset pool header and client pool
//
// if header is false then will memset client pool
void PoolMemset(ssmm* _this, SsmmPool* pool, size_t num, bool header)
{
  size_t size = num * (size_t)_this->sizeOf;

  if(header)
    size += SsmmGetSizeOfPool();
  else
    pool = (SsmmPool*)SSMM_CHUNK_POOL_TO_FIRSTNODE(pool);

  memset(pool, 0, size);
}

SsmmPool* PoolListWalk(ssmm* _this, SsmmPool* tail, bool doFree, bool skipLast)
{
  SsmmPool* next = 0;
  SsmmPool* current = tail;

  while(current)
  {
    SsmmPool* previous = current->previous;

    // we aren't actually reversing the list, and not even walking it backwards
    //
    // we are just doing a regular forward walk and returning the last non-null node

    //current->previous = previous;

    next = current;

    bool clear = SsmmIsDebug(_this);

    if(previous || !skipLast)
    {
      void* unaligned = PoolGetUnaligned(current);

      if(clear)
        PoolMemset(_this, current, (size_t)current->num, doFree);

      if(doFree)
        free(unaligned);
    }
    else if(clear)
    {
      // in the case that we free (p - 1) pools, and for those (p - 1) pools we memset each of them both the header and
      // all client data
      //
      // in that case, for that last pool that we would otherwise not touch, we still memset - not the header of that
      // pool - we memset all of the client data of that pool
      PoolMemset(_this, current, (size_t)current->num, false);
    }

    current = previous;
  }

  return next;
}

bool SsmmFirstPool(ssmm* _this, int64_t initialCapacity)
{
  bool result = false;

  _this->resize = (int)initialCapacity;

  if( !SsmmResize(_this) )
    goto error;

  // _this->freeChunks = SSMM_CHUNK_POOL_TO_FIRSTNODE(pool)
  // _this->poolTail = pool

  // _this->max = max
  _this->resize = -1;

  result = true;

error:
  return result;
}

bool SsmmSsmm(ssmm* _this, size_t sizeOf, size_t initialCapacity, bool isTentative, ssmm_debug debug)
{
  bool result = false;

  // _this checked in SsmmConstruct

  // _this memset in SsmmConstruct

  if(sizeOf <= 0 || initialCapacity <= 0)
    goto error;

  sizeOf = SsmmGetSizeOfChunk(sizeOf, debug);

  _this->num = 0;
  _this->most = 0;

  _this->sizeOf = (int)sizeOf;

  _this->debug = debug;

  _this->freePools = 0;

  _this->max = 0;

  if(isTentative)
  {
    _this->resize = -(int)initialCapacity - 1;
  }
  else if( !SsmmFirstPool(_this, (int64_t)initialCapacity) )
  {
    goto error;
  }

  result = true;

error:
  return result;
}

ssmm* SsmmConstruct(int sizeOf, int initialCapacity, bool isTentative, ssmm_debug debug)
{
  bool result = false;

  ssmm* _this = 0;

  try
  {
    void* unaligned = 0;
    _this = (ssmm*)cstandard_aligned_alloc(SsmmGetSizeOfSsmm(), &unaligned);

    if(_this && sizeOf > 0 && initialCapacity > 0)
    {
      SsmmMemset(_this);

      result = SsmmSsmm(_this, (size_t)sizeOf, (size_t)initialCapacity, isTentative, debug);
      _this->unaligned = unaligned;
    }
  }
  catch(bad_alloc& )
  {
  }

  if( !result)
  {
    SsmmDestruct( &_this);
  }

  return _this;
}

// returns the number of nodes previously held by client or -1 on error
int SsmmDestruct(ssmm** _thisRef)
{
  int64_t result = -1;
  int64_t numRef = 0;

  ssmm* _this = 0;
  void* unaligned = 0;

  if( !_thisRef || !_thisRef[0] )
    goto error;

  _this = _thisRef[0];

  numRef = SsmmNum(_this);
  if(numRef < 0)
    goto error;

  // free all pools (and memset all pools if debug)
  PoolListWalk(_this, _this->poolTail, true, false);

  unaligned = _this->unaligned;
  SsmmMemset(_this);

  free(unaligned);
  _thisRef[0] = 0;

  result = numRef;

error:
  return (int)result;
}

int SsmmNum(ssmm* _this)
{
  int64_t result = -1;

  if( !_this)
    goto error;

  result = _this->num;

error:
  return (int)result;
}

bool SsmmSetResize(ssmm* _this, int resize)
{
  bool result = false;

  if( !_this || resize < -1 || _this->resize < -1)
    goto error;

  _this->resize = resize;

  result = true;

error:
  return result;
}

// returns the number of nodes previously held by client or -1 on error
int64_t SsmmResetOrClear(ssmm* _this, bool freeAppendedPools)
{
  int64_t result = -1;
  int64_t numRef = 0;

  SsmmPool* pool = 0;

  if( !_this)
    goto error;

  numRef = _this->num;

  _this->num = 0;
  _this->most = 0;

  if( !freeAppendedPools)
  {
    // memset all pools if debug
    // ignore pointer returned by PoolListWalk
    if(SsmmIsDebug(_this) )
      PoolListWalk(_this, _this->poolTail, false, false);
  }
  else/* if(freeAppendedPools)*/
  {
    // free all pools except the first (and memset all pools if debug)
    _this->poolTail = PoolListWalk(_this, _this->poolTail, true, true);
  }

  pool = _this->poolTail;

  _this->max = pool->num;

  _this->freeChunks = SSMM_CHUNK_POOL_TO_FIRSTNODE(pool);

  _this->freePools = pool->previous; // will end up being null for freeAppendedPools == true, as desired

  result = numRef;

error:
  return result;
}

// returns the number of nodes previously held by client or -1 on error
int SsmmReset(ssmm* _this)
{
  return (int)SsmmResetOrClear(_this, false);
}

// returns the number of nodes previously held by client or -1 on error
int SsmmClear(ssmm* _this)
{
  return (int)SsmmResetOrClear(_this, true);
}

bool SsmmResize(ssmm* _this)
{
  bool result = false;

  if(_this->num != _this->max)
    goto error;

  if(_this->freePools)
  {
    SsmmPool* pool = _this->freePools;
    _this->freePools = pool->previous;

    _this->freeChunks = SSMM_CHUNK_POOL_TO_FIRSTNODE(pool);

    _this->max += pool->num;
  }
  else
  {
    size_t maxDiff = 0;

    if(_this->resize == -1  && _this->max >= 0)
      maxDiff = (size_t)_this->max;
    else if(_this->resize >= 0)
      maxDiff = (size_t)_this->resize;
    else
      goto error;

    // if ssmm is constructed with initial capacity of zero and resize is left
    // at default of -1 then capacity will remain at zero
    //
    // the behavior is the same as if resize is zero (whose behavior is to not
    // grow after reaching capacity)
    //
    // in this case call SsmmSetResize with an intended initial capacity > 0,
    // call SsmmAlloc once to actualize the initial capacity,
    // then call SsmmSetResize(-1) to return to default behavior
    if(maxDiff == 0)
      goto error;

    // already aligned
    size_t size = SsmmGetSizeOfPool() + maxDiff * (size_t)_this->sizeOf;

    void* unaligned = 0;
    SsmmPool* pool = (SsmmPool*)cstandard_aligned_alloc(size, &unaligned);

    if( !pool)
      goto error;

    if(SsmmIsDebug(_this) )
    {
      PoolMemset(_this, pool, maxDiff, true);
    }

    PoolSetUnaligned(pool, unaligned);

    _this->max += (int)maxDiff;

    _this->freeChunks = SSMM_CHUNK_POOL_TO_FIRSTNODE(pool);

    pool->num = (int)maxDiff;

    pool->previous = _this->poolTail;

    _this->poolTail = pool;
  }

  result = true;

error:
  return result;
}

void* SsmmAlloc(ssmm* _this)
{
  void* result = 0;

  SsmmNode* chunk = 0;

  if( !_this || _this->num > _this->max)
    goto error;

  if(_this->num == _this->max)
  {
    if( !_this->resize)
      goto error;

    if(_this->resize >= -1)
    {
      if( !SsmmResize(_this) )
        goto error;
    }
    else if( !SsmmFirstPool(_this, -(int64_t)_this->resize - 1) )
    {
      goto error;
    }
  }

  chunk = _this->freeChunks;

  if(_this->num == _this->most)
  {
    _this->freeChunks = SSMM_CHUNK_NODE_TO_NODE_SEQUENTIAL(_this, chunk);

    _this->most++;
  }
  else
  {
    _this->freeChunks = chunk->next;
  }

  if(SsmmIsDebug(_this) )
  {
    ChunkMemset(_this, chunk);

    // use next as magic
    chunk->next = (SsmmNode*)INTPTR_MAX;

    chunk = SSMM_CHUNK_NODE_TO_CLIENT(chunk, _this->debug);
  }

  _this->num++;

  result = chunk;

error:
  return result;
}

bool SsmmFree(ssmm* _this, void** memory/*chunk*/)
{
  bool result = false;

  SsmmNode* chunk = 0;

  if( !_this || !memory || !memory[0] || _this->num <= 0)
    goto error;

  chunk = (SsmmNode*)memory[0];

  // debug <= 0; chunks have no header; no checks

  // debug > 0; chunks have header

  // debug >= 1; check magic value; O(1)

  // debug >= 2; check pool range; O(lg(n) ) or O(number of pools)

  // debug >= 3; verify not in free list; O(n)

  if(SsmmIsDebug(_this) )
  {
    // walk back from the portion of the chunk's memory intended for client
    // use, to the portion of the chunk's memory not intended for client use
    // (the header)
    chunk = SSMM_CHUNK_CLIENT_TO_NODE(chunk, _this->debug);
  }

  if( SsmmIsDebugLogarithmic(_this) && !SsmmFreeDebugCheckLogarithmic(_this, chunk) )
    goto error;

  if( SsmmIsDebugLinear(_this) && !SsmmFreeDebugCheckLinear(_this, chunk) )
    goto error;

  if( SsmmIsDebugConstant(_this) && !SsmmFreeDebugCheckConstant(chunk) )
    goto error;

  if(SsmmIsDebug(_this) )
  {
    ChunkMemset(_this, chunk);
  }

  _this->num--;

  chunk->next = _this->freeChunks;
  _this->freeChunks = chunk;

  memory[0] = 0;

  result = true;

error:
  return result;
}

bool SsmmFreeDebugCheckConstant(SsmmNode* chunk)
{
  bool result = false;

  // use next as magic
  if(chunk->next != (SsmmNode*)INTPTR_MAX)
    goto error;

  result = true;

error:

  return result;
}

bool SsmmFreeDebugCheckLogarithmic(ssmm* _this, SsmmNode* chunk)
{
  bool result = false;

// check if the particular chunk being freed is in any of our pools
  for(SsmmPool* pool = _this->poolTail; pool; pool = pool->previous)
  {
    // for this particular collection of chunks (defined as a pool), walk from
    // the collection's header to the first chunk of the pool
    SsmmNode* nodes = SSMM_CHUNK_POOL_TO_FIRSTNODE(pool);

    // the address of the beginning of the first chunk, of this particular
    // collection of chunks
    char* nodesBegin = (char*)nodes;

    // the address one byte after the last byte of the last chunk, of this
    // particular collection of chunks (equivalent to container.end() )
    char* nodesEnd = (char*)nodes + pool->num * _this->sizeOf;

    // nodesDiff is similar to sizeof(type) * distance(container<type>.begin(), container<type>.end() )
    int64_t nodesDiff = nodesEnd - nodesBegin;

    // given chunk as container<type>::iterator somewhere between container<type>.begin() and container<type>.end()
    // chunkDiff is similar to sizeof(type) * distance(container<type>.begin(), chunk)
    int64_t chunkDiff = (char*)chunk - nodesBegin;

    // check if chunk in the current pool
    //
    // 'continue' (as in jump to the next iteration of the for loop) if the
    // particular chunk being freed is *not* in this pool
    if(chunkDiff < 0 || chunkDiff >= nodesDiff)
      continue;

    // at this point we know the chunk being freed is in the current pool
    // but we're still not done

    // check if the chunk is properly aligned.  if it's not then something is
    // wrong
    if(chunkDiff % _this->sizeOf || nodesDiff % _this->sizeOf)
      goto error;

    // just because the chunk being freed is in one of our owned pools,
    // that's not enough
    //
    // the chunk being freed needs to be associated with a pool currently in use
    //
    // verify the pool containing this chunk is in fact in use, or else something is wrong
    for(SsmmPool* freePool = _this->freePools; freePool; freePool = freePool->previous)
    {
      if(pool == freePool)
        goto error;
    }

    // out of all the used pools, only the last used pool will have a portion
    // not in use that is trivial to check for
    //
    // take advantage of this to do another check at minimal cost

    // check if pool is last used pool
    if( !pool->previous || pool->previous == _this->freePools)
    {
      // if is last used pool, make sure chunk is not within the known unused
      // portion of the pool

      // used
      // (max - pool->num) + (chunk - nodes) < most

      // free
      // (max - pool->num) + (chunk - nodes) >= most
      int64_t base = _this->max - pool->num;
      int64_t differential = ( (char*)chunk - (char*)nodes) / (int64_t)_this->sizeOf;

      if(base + differential >= _this->most)
        goto error;
    }

    // everything passed, so set the flag and get outta there
    result = true;
    break;
  }

error:

  return result;
}

bool SsmmFreeDebugCheckLinear(ssmm* _this, SsmmNode* chunk)
{
  bool result = false;

  // make sure chunk being freed is not already in free list
  for(SsmmNode* freeChunk = _this->freeChunks; freeChunk; freeChunk = freeChunk->next)
  {
    if(chunk == freeChunk)
      goto error;
  }

  result = true;

error:

  return result;
}

#if defined(_MSC_VER)
  #pragma warning (default: 4711)
#endif
