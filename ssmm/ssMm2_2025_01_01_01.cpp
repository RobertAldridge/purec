
// ssmm.cpp
// Robert Aldridge and Charlie Burns

#if defined(_MSC_VER)
  #pragma warning (disable: 4711)
#endif

#include "ssmm.h"

#include <cstdio>
using std::printf;

// dereferencing node <> client reference
struct SsmmNode
{
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

  int padding;
};

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

#define SSMM_GET_SIZEOF(_this) (size_t)_this->sizeOf

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
// 'address' is of type ptrdiff_t, assigned to the value (char*)ptr - (char*)0
// pass return value of malloc to MALLOCRETURNALIGN (pass stored value not the literal malloc call)
static char* MALLOCRETURNALIGN(char* unaligned, ptrdiff_t address);

static SsmmNode* SSMM_CHUNK_POOL_TO_FIRSTNODE(SsmmPool* pool);
static SsmmNode* SSMM_CHUNK_NODE_TO_NODE_SEQUENTIAL(ssmm* _this, SsmmNode* node);

static void* cstandard_aligned_alloc(size_t size, void** unalignedRef/*unaligned;ptr*/);
static size_t SsmmGetSizeOfNode();
static size_t SsmmGetSizeOfPool();
static size_t SsmmGetSizeOfSsmm();
static size_t SsmmGetSizeOfChunk(size_t sizeOf);
static void SsmmMemset(ssmm* _this);

static SsmmPool* PoolListWalk(SsmmPool* tail, bool doFree, bool skipLast);
static bool SsmmFirstPool(ssmm* _this, size_t initialCapacity);

// initial capacity must be larger than zero
//
// you can delay the overhead of creating a pool by setting isTentative to true.  in that case, the first pool will be
// created upon first call to SsmmAlloc.  note that in this case calls to SsmmSetResize will fail until after the first
// call to SsmmAlloc
static bool SsmmSsmm(ssmm* _this, size_t sizeOf, size_t initialCapacity, bool isTentative);

// ssmm* SsmmConstruct(int sizeOf, int initialCapacity, bool isTentative)
// int SsmmDestruct(ssmm** _thisRef/*_this*/)
// int SsmmNum(ssmm* _this)
// bool SsmmSetResize(ssmm* _this, int resize)

static int SsmmResetOrClear(ssmm* _this, bool freeAppendedPools);

// int SsmmReset(ssmm* _this)
// int SsmmClear(ssmm* _this)

static bool SsmmResize(ssmm* _this);

// void* SsmmAlloc(ssmm* _this)
// bool SsmmFree(ssmm* _this, void** memory/*chunk*/)

//#define INTEGER_MAX(lhs, rhs) (lhs >= rhs ? lhs : rhs)

void PoolSetUnaligned(SsmmPool* pool, void* unaligned) { pool->unaligned = (int)( (char*)unaligned - (char*)pool); }
void* PoolGetUnaligned(SsmmPool* pool) { return (char*)pool + (ptrdiff_t)pool->unaligned; }

size_t ALIGNEDOFVALUE(size_t size) { return (size % sizeof(void*) ) ? size + (sizeof(void*) - size % sizeof(void*) ) : size; }

size_t MALLOCSIZEPADDED(size_t size) { return size + (sizeof(void*) - 1); }

char* MALLOCRETURNALIGN(char* unaligned, ptrdiff_t address) { return (address % sizeof(void*) ) ? unaligned + (sizeof(void*) - address % sizeof(void*) ) : unaligned; }

SsmmNode* SSMM_CHUNK_POOL_TO_FIRSTNODE(SsmmPool* pool) { return (SsmmNode*)( (char*)pool + SsmmGetSizeOfPool() ); }

SsmmNode* SSMM_CHUNK_NODE_TO_NODE_SEQUENTIAL(ssmm* _this, SsmmNode* node) { return (SsmmNode*)( (char*)node + SSMM_GET_SIZEOF(_this) ); }

// when you're forced to use a compiler/runtime that claims to conform yet doesn't implement aligned_alloc (*cough* microsoft)
//   void* aligned_alloc(size_t alignment, size_t size)

// in this case assume alignment is sizeof(void*)
void* cstandard_aligned_alloc(size_t size, void** unalignedRef/*unaligned;ptr*/)
{
  char* aligned = 0;
  char* unaligned = 0;

  ptrdiff_t address = 0;

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
size_t SsmmGetSizeOfNode()
{
  return 0;
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
size_t SsmmGetSizeOfChunk(size_t sizeOf)
{
  size_t result = ALIGNEDOFVALUE(sizeOf);

  return result + SsmmGetSizeOfNode();
}

void SsmmMemset(ssmm* _this)
{
  memset(_this, 0, SsmmGetSizeOfSsmm() );
}

SsmmPool* PoolListWalk(SsmmPool* tail, bool doFree, bool skipLast)
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

    if(previous || !skipLast)
    {
      void* unaligned = PoolGetUnaligned(current);

      if(doFree)
        free(unaligned);
    }

    current = previous;
  }

  return next;
}

bool SsmmFirstPool(ssmm* _this, size_t initialCapacity)
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

bool SsmmSsmm(ssmm* _this, size_t sizeOf, size_t initialCapacity, bool isTentative)
{
  bool result = false;

  // _this checked in SsmmConstruct

  // _this memset in SsmmConstruct

  if(sizeOf <= 0 || initialCapacity <= 0)
    goto error;

  sizeOf = SsmmGetSizeOfChunk(sizeOf);

  _this->num = 0;
  _this->most = 0;

  _this->sizeOf = (int)sizeOf;

  _this->freePools = 0;

  _this->max = 0;

  if(isTentative)
  {
    _this->resize = -(int)initialCapacity - 1;
  }
  else if( !SsmmFirstPool(_this, initialCapacity) )
  {
    goto error;
  }

  result = true;

error:
  return result;
}

ssmm* SsmmConstruct(int sizeOf, int initialCapacity, bool isTentative)
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

      result = SsmmSsmm(_this, (size_t)sizeOf, (size_t)initialCapacity, isTentative);
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
  int result = -1;
  int numRef = 0;

  ssmm* _this = 0;
  void* unaligned = 0;

  if( !_thisRef || !_thisRef[0] )
    goto error;

  _this = _thisRef[0];

  numRef = SsmmNum(_this);
  if(numRef < 0)
    goto error;

  // free all pools
  PoolListWalk(_this->poolTail, true, false);

  unaligned = _this->unaligned;
  SsmmMemset(_this);

  free(unaligned);
  _thisRef[0] = 0;

  result = numRef;

error:
  return result;
}

int SsmmNum(ssmm* _this)
{
  int result = -1;

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
int SsmmResetOrClear(ssmm* _this, bool freeAppendedPools)
{
  int result = -1;
  int numRef = 0;

  SsmmPool* pool = 0;

  if( !_this)
    goto error;

  numRef = _this->num;

  _this->num = 0;
  _this->most = 0;

  if(freeAppendedPools)
  {
    // free all pools except the first
    _this->poolTail = PoolListWalk(_this->poolTail, true, true);
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
  return SsmmResetOrClear(_this, false);
}

// returns the number of nodes previously held by client or -1 on error
int SsmmClear(ssmm* _this)
{
  return SsmmResetOrClear(_this, true);
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

    pool->previous = _this->poolTail;

    _this->poolTail = pool;
  }
  else
  {
    int maxDiff = 0;

    if(_this->resize == -1  && _this->max >= 0)
      maxDiff = _this->max;
    else if(_this->resize >= 0)
      maxDiff = _this->resize;
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
    if( !maxDiff)
      goto error;

    // already aligned
    size_t size = SsmmGetSizeOfPool() + (size_t)maxDiff * SSMM_GET_SIZEOF(_this);

    void* unaligned = 0;
    SsmmPool* pool = (SsmmPool*)cstandard_aligned_alloc(size, &unaligned);

    if( !pool)
      goto error;

    PoolSetUnaligned(pool, unaligned);

    _this->max += maxDiff;

    _this->freeChunks = SSMM_CHUNK_POOL_TO_FIRSTNODE(pool);

    pool->num = maxDiff;

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
    else if( !SsmmFirstPool(_this, (size_t)(-_this->resize - 1) ) )
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

  _this->num--;

  chunk->next = _this->freeChunks;
  _this->freeChunks = chunk;

  memory[0] = 0;

  result = true;

error:
  return result;
}

void* SsmmStackPush(ssmm* /*_this*/, void* /*memory*//*chunk*/){ return 0; }

void* SsmmStackPop(ssmm* /*_this*/){ return 0; }

#if defined(_MSC_VER)
  #pragma warning (default: 4711)
#endif
