
// ssmm.cpp
// Robert Aldridge and Charlie Burns

#include "ssmm.h"

#include <cstddef> // ptrdiff_t
#include <cstdlib> // malloc, free
#include <cstring> // memset

#include <new> // bad_alloc
using namespace std;

// dereferencing node <> client reference
struct SsmmNode
{
  SsmmNode* next;

  // dereferencing magic is only valid when debug is true
  int magic;
};

struct SsmmPool
{
  SsmmPool* next;
  int num;
};

struct ssmm
{
  int num;
  int most;
  int max;
  int resize;
  int sizeOf;

  bool debug;

  SsmmNode* freeChunks;
  SsmmPool* freePools;

  SsmmPool* poolHead;
  SsmmPool* poolTail;
};

#define INTEGERMAX(lhs, rhs) (lhs >= rhs ? lhs : rhs)

static int SsmmGetSizeOfChunk(int sizeOf, bool debug);

static void PoolMemset(ssmm* _this, SsmmPool* pool, bool header);
static void PoolListWalk(ssmm* _this, SsmmPool* head, bool clear, bool doFree);
static void PoolListReverseAndFree(ssmm* _this, SsmmPool* head);

static bool SsmmSsmm(ssmm* _this, int newSizeOf, int newMax, bool newDebug);

static int SsmmResetOrClear(ssmm* _this, bool freeAppendedPools);

static bool SsmmResize(ssmm* _this);

int SsmmGetSizeOfChunk(int sizeOf, bool debug)
{
  if(debug)
    sizeOf += sizeof(SsmmNode);
  else
    sizeOf = INTEGERMAX(sizeOf, sizeof(void*) );

  return sizeOf;
}

void PoolMemset(ssmm* _this, SsmmPool* pool, bool header)
{
  int size = pool->num * _this->sizeOf;

  if(header)
    size += (int)sizeof(SsmmPool);
  else
    pool++;

  memset(pool, 0, size);
}

void PoolListWalk(ssmm* _this, SsmmPool* head, bool clear, bool doFree)
{
  SsmmPool* next = 0;

  for(SsmmPool* curr = head; curr; curr = next)
  {
    next = curr->next;

    if(clear)
      PoolMemset(_this, curr, doFree);

    if(doFree)
      free(curr);

    curr = next;
  }
}

void PoolListReverseAndFree(ssmm* _this, SsmmPool* head)
{
  // we want to free pools in opposite order of their allocation

  // reverse list
  SsmmPool* prev = 0;
  SsmmPool* next = 0;

  for(SsmmPool* curr = head; curr; curr = next)
  {
    next = curr->next;
    curr->next = prev;

    prev = curr;
  }

  // free pools
  PoolListWalk(_this, prev, _this->debug, true);
}

bool SsmmSsmm(ssmm* _this, int newSizeOf, int newMax, bool newDebug)
{
  bool result = false;

  if( !_this)
    goto error;

  memset(_this, 0, sizeof(ssmm) );

  if(newSizeOf <= 0 || newMax <= 0)
    goto error;

  newSizeOf = SsmmGetSizeOfChunk(newSizeOf, newDebug);

  _this->num = 0;
  _this->most = 0;

  _this->sizeOf = newSizeOf;

  _this->debug = newDebug;

  _this->freePools = 0;

  _this->max = 0;
  _this->resize = newMax;

  result = SsmmResize(_this);

  // _this->freeChunks = (SsmmNode*)(pool + 1)
  // _this->poolHead = pool
  // _this->poolTail = pool

  // _this->max = newMax
  _this->resize = -1;

error:
  return result;
}

ssmm* SsmmConstruct(int sizeOf, int initialCapacity, bool debug)
{
  bool result = false;

  ssmm* _this = 0;

  try
  {
    _this = (ssmm*)malloc(sizeof(ssmm) );

    result = SsmmSsmm(_this, sizeOf, initialCapacity, debug);
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

  ssmm* _this = 0;
  int numRef = 0;

  if( !_thisRef || !_thisRef[0] )
    goto error;

  _this = _thisRef[0];

  numRef = SsmmNum(_this);

  PoolListReverseAndFree(_this, _this->poolHead);
  memset(_this, 0, sizeof(ssmm) );

  free(_this);
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
  return result;
}

bool SsmmSetResize(ssmm* _this, int newResize/*resize*/)
{
  bool result = false;

  if( !_this || newResize < -1)
    goto error;

  _this->resize = newResize;

  result = true;

error:
  return result;
}

// returns the number of nodes previously held by client or -1 on error
int SsmmResetOrClear(ssmm* _this, bool freeAppendedPools)
{
  int result = -1;

  SsmmPool* pool = 0;
  int numRef = 0;

  if( !_this)
    goto error;

  pool = _this->poolHead;

  numRef = _this->num;

  _this->num = 0;
  _this->most = 0;
  _this->max = pool->num;

  _this->freeChunks = (SsmmNode*)(pool + 1);

  if( !freeAppendedPools)
  {
    _this->freePools = pool->next;

    PoolMemset(_this, _this->poolHead, false);
  }
  else
  {
    _this->freePools = 0;

    _this->poolTail = _this->poolHead;

    PoolListReverseAndFree(_this, pool->next);

    pool->next = 0;
  }

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
    _this->freePools = pool->next;

    _this->freeChunks = (SsmmNode*)(pool + 1);

    _this->max += pool->num;
  }
  else
  {
    int maxDiff = 0;

    if(_this->resize == -1)
      maxDiff = _this->max;
    else
      maxDiff = _this->resize;

    int size = (int)sizeof(SsmmPool) + maxDiff * _this->sizeOf;

    SsmmPool* pool = (SsmmPool*)malloc(size);
    if(!pool)
      goto error;

    if(_this->debug)
    {
      memset(pool, 0, size);
    }

    _this->max += maxDiff;

    _this->freeChunks = (SsmmNode*)(pool + 1);

    pool->next = 0;
    pool->num = maxDiff;

    if(_this->poolHead)
      _this->poolTail->next = pool;
    else
      _this->poolHead = pool;

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

    if( !SsmmResize(_this) )
      goto error;
  }

  chunk = _this->freeChunks;

  if(_this->num == _this->most)
  {
    _this->freeChunks = (SsmmNode*)( (char*)chunk + _this->sizeOf);

    _this->most++;
  }
  else
  {
    _this->freeChunks = chunk->next;
  }

  if(_this->debug)
  {
    memset(chunk, 0, _this->sizeOf);

    chunk->next = 0;
    chunk->magic = INT_MAX;

    chunk++;
  }

  _this->num++;

  result = (void*)chunk;

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

  if(_this->debug)
  {
    bool contained = false;

    chunk--;

    // check if in any pool
    for(SsmmPool* pool = _this->poolHead; pool; pool = pool->next)
    {
      SsmmNode* nodes = (SsmmNode*)(pool + 1);

      char* nodesBegin = (char*)nodes;
      char* nodesEnd = (char*)(nodes + pool->num);

      ptrdiff_t nodesDiff = nodesEnd - nodesBegin;
      ptrdiff_t chunkDiff = (char*)chunk - nodesBegin;

      // check if in the current pool
      if(chunkDiff < 0 || chunkDiff >= nodesDiff)
        continue;

      // check if properly aligned
      if(chunkDiff % _this->sizeOf)
        goto error;

      // check make sure it is a used pool
      for(SsmmPool* freePool = _this->freePools; freePool; freePool = freePool->next)
        if(pool == freePool)
          goto error;

      // check if pool is last used pool
      if( !pool->next || pool->next == _this->freePools)
      {
        // if is last used pool then have to check if chunk is in the
        // used portion of the pool

        // used
        // (max - pool->num) + (chunk - nodes) < most

        // free
        // (max - pool->num) + (chunk - nodes) >= most
        int base = _this->max - pool->num;
        ptrdiff_t differential = chunk - nodes;

        if(base + differential >= _this->most)
          goto error;
      }

      // everything passed, so set the flag and get outa there
      contained = true;
      break;
    }

    if( !contained)
      goto error;

    if(chunk->next || chunk->magic != INT_MAX)
      goto error;

    memset(chunk, 0, _this->sizeOf);

    chunk->magic = 0;
  }

  _this->num--;

  chunk->next = _this->freeChunks;
  _this->freeChunks = chunk;

  memory[0] = 0;

  result = true;

error:
  return result;
}
