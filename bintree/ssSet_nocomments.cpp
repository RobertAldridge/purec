
// ssSet.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

#include <cstddef>
#include <cstdint> // int32_t, uint8_t
#include <cstdio>
#include <cstdlib>
#include <cstring>

using std::free;
using std::int32_t;
using std::memset;
using std::printf;
using std::ptrdiff_t;

#include "blah_alloc.h"

#include "ssMm_nocomments.h"
#include "ssStack_nocomments.h"
#include "ssQueue_nocomments.h"

#include "bintree_nocomments.h"

#include "binpriv_nocomments.h"

const uint32_t SsSetRed = 1;
const uint32_t SsSetBlack = 2;

#define GETCLIENT(node) (void*)(node + 1)

//#define GETROOTFROMSENTINEL(sentinel) (sentinel->left)
//#define SETROOTFROMSENTINEL(sentinel, node) (sentinel->left = node)

#define GETROOTFROMTREE(_this) (_this->root.left)
#define SETROOTFROMTREE(_this, node) (_this->root.left = node)

#define SETROOTCOLORFROMTREE(_this, value) (_this->root.left->color = value)

#define GETSENTINELFROMTREE(_this) ( &_this->root)

#define LESSTHANWRAPPER(_this, client, node) \
  (node == GETSENTINELFROMTREE(_this) ? 1 : _this->lessThan(client, GETCLIENT(node) ) )
  
#define EQUALTOWRAPPER(lessThan, lhs, rhs) !lessThan(lhs, rhs) && !lessThan(rhs, lhs)

//#define EQUALTOWRAPPER(_this, client, node) \
//  (node == GETSENTINELFROMTREE(_this) ? 0 : _this->equalTo(client, GETCLIENT(node) ) )

//#define CLIENTEVALUATEWRAPPER(_this, node) \
//  (node == GETSENTINELFROMTREE(_this) ? 0 : _this->clientEvaluate(GETCLIENT(node) ) )

//#define _log(blah) {}
#define _log(blah) printf("%s %s %i\n", blah, __FILE__, (int)__LINE__)

// bintree.cpp
static uint32_t DepthMax(SsSetNode* node);
static uint32_t CalculateLogBase2(uint32_t number);
static SsSetNode* TreeMinimum(SsSetNode* node);
static SsSetNode* TreeMaximum(SsSetNode* node);
static SsSetNode* TreeSuccessor(SsSetNode* x);
static SsSetNode* TreeSearch(SsSetNode* x, void* objectKey, SsSetCompare lessThan);

uint32_t gDebugRotate[69] = {0};

// binleft.cpp
static void LeftRotateDelete1(SsSetNode* xP);
static void LeftRotateDelete2(SsSetNode* xP);
static void LeftRotateInsert(SsSetNode* xPP);

// binleftleft.cpp
static void LeftLeftRotate(SsSetNode* xP);

// binleftright.cpp
static void LeftRightRotateInsert(SsSetNode* x);
static void LeftRightRotateDelete(SsSetNode* xP);

// binleftrightleft.cpp
static void LeftRightLeftRotate(SsSetNode* xP);

#include "binleft_nocomments.cpp"
#include "binleftleft_nocomments.cpp"
#include "binleftright_nocomments.cpp"
#include "binleftrightleft_nocomments.cpp"

// binright.cpp
static void RightRotateDelete1(SsSetNode* xP);
static void RightRotateDelete2(SsSetNode* xP);
static void RightRotateInsert(SsSetNode* xPP);

// binrightright.cpp
static void RightRightRotate(SsSetNode* xP);

// binrightleft.cpp
static void RightLeftRotateInsert(SsSetNode* x);
static void RightLeftRotateDelete(SsSetNode* xP);

// binrightleftright.cpp
static void RightLeftRightRotate(SsSetNode* xP);

#include "binright_nocomments.cpp"
#include "binrightright_nocomments.cpp"
#include "binrightleft_nocomments.cpp"
#include "binrightleftright_nocomments.cpp"

// bininsert.cpp
static bool TreeInsert(ssSet* _this, SsSetNode* insert);
static bool BinInsert(ssSet* _this, SsSetNode* x);

#include "bininsert_nocomments.cpp"

// binremove.cpp
static void BinDeleteFixup(ssSet* _this, SsSetNode* x);
static SsSetNode* BinDelete(ssSet* _this, SsSetNode* z);

#include "binremove_nocomments.cpp"

// bintraverse.cpp
static int64_t IterativePreorderTreeTraverse(ssSet* _this, SsSetNode* node, SsSetEvaluate ClientEvaluate);
static int64_t IterativeInorderTreeTraverse(ssSet* _this, SsSetNode* node, SsSetEvaluate ClientEvaluate);
static int64_t IterativePostorderTreeTraverse(ssSet* _this, SsSetNode* node, SsSetEvaluate ClientEvaluate);
static int64_t IterativeLevelorderTreeTraverse(ssSet* _this, SsSetNode* node, SsSetEvaluate ClientEvaluate);

#include "bintraverse_nocomments.cpp"

uint32_t DepthMax(SsSetNode* node)
{
  uint32_t result = 0;

  uint32_t left = 0;
  uint32_t right = 0;

  if( !node)
    goto label_return;

  left = DepthMax(node->left);

  right = DepthMax(node->right);

  if(left >= right)
    result = left + 1;
  else
    result = right + 1;

label_return:
  return result;
}

uint32_t CalculateLogBase2(int64_t number)
{
  uint32_t result = 0;

  while(number)
  {
    result++;

    number /= 2;
  }

  return result;
}

// integrated for root sentinel
SsSetNode* TreeMinimum(SsSetNode* node)
{
  for(SsSetNode* left = node; left; left = left->left)
    node = left;

  return node;
}

// integrated for root sentinel
SsSetNode* TreeMaximum(SsSetNode* node)
{
  for(SsSetNode* right = node; right; right = right->right)
    node = right;

  return node;
}

SsSetNode* TreeSuccessor(SsSetNode* x)
{
  SsSetNode* y = 0;

  if(x->right)
  {
    y = TreeMinimum(x->right);
  }
  else
  {
    for(y = x->parent; y && x == y->right; y = y->parent)
      x = y;
  }

  return y;
}

// integrated for root sentinel
SsSetNode* TreeSearch(SsSetNode* x, void* objectKey, SsSetCompare lessThan)
{
#if 0
  while(x && !equalTo(objectKey, GETCLIENT(x) ) )
  {
    if(lessThan(objectKey, GETCLIENT(x) ) )
      x = x->left;
    else
      x = x->right;
  }
#else
  while(x)
  {
    // less than
    if(lessThan(objectKey, GETCLIENT(x) ) )
    {
      x = x->left;
    }
    // greater than
    else if(lessThan(GETCLIENT(x), objectKey) )
    {
      x = x->right;
    }
    // equivalent
    else
    {
      // when there are duplicates, return the chronologically earliest
      while(x->left && EQUALTOWRAPPER(lessThan, objectKey, x->left) )
      {
        x = x->left;
      }

      break;
    }
  }
#endif

  return x;
}

// integrated for root sentinel
int64_t SsSetGetExtrema(ssSet* _this, bool maximum, void* client)
{
  bool result = false;

  int empty = 1;

  SsSetNode* node = 0;

  if( !_this)
  {
    _log("error");
    goto label_return;
  }

  // root
  // leaf
  // lessThan
  // equalTo
  // evaluate
  // allocator
  // stack
  // queue
  // maxStack
  // maxQueue
  // num
  // sizeOf

  // no change
  // -----
  // root
  // leaf
  // lessThan
  // equalTo
  // evaluate
  // allocator
  // stack
  // queue
  // maxStack
  // maxQueue
  // num
  // sizeOf

  // touched in this function
  // -----
  // n/a

  if(maximum)
    node = TreeMaximum(GETROOTFROMTREE(_this) );
  else
    node = TreeMinimum(GETROOTFROMTREE(_this) );

  if(node)
  {
    empty = 0;
    
    if(client)
      memcpy(client, GETCLIENT(node), _this->sizeOf);
  }

  result = true;

label_return:
  return result ? empty : -1;
}

// integrated for root sentinel
int64_t SsSetFind(ssSet* _this, void* key, SsSetCompare lessThan, void* client)
{
  bool result = false;

  int empty = 1;

  SsSetNode* node = 0;

  if( !_this || !key)
  {
    _log("error");
    goto label_return;
  }

  if( !lessThan && !_this->lessThan)
  {
    _log("error");
    goto label_return;
  }

  // root
  // leaf
  // lessThan
  // equalTo
  // evaluate
  // allocator
  // stack
  // queue
  // maxStack
  // maxQueue
  // num
  // sizeOf

  // no change
  // -----
  // root
  // leaf
  // equalTo
  // evaluate
  // allocator
  // stack
  // queue
  // maxStack
  // maxQueue
  // num
  // sizeOf

  // touched in this function
  // -----
  // lessThan

  if(lessThan)
    _this->lessThan = lessThan;

  node = TreeSearch(GETROOTFROMTREE(_this), key, _this->lessThan);

  if(node)
  {
    empty = 0;

    if(client)
      memcpy(client, GETCLIENT(node), _this->sizeOf);
  }

  result = true;

label_return:
  return result ? empty : -1;
}

// integrated for root sentinel
int64_t SsSetReset(ssSet* _this)
{
  bool result = false;

  uint32_t num = 0;

  if( !_this)
  {
    _log("error");
    goto label_return;
  }

  // root
  // leaf
  // lessThan
  // equalTo
  // evaluate
  // allocator
  // stack
  // queue
  // maxStack
  // maxQueue
  // num
  // sizeOf

  // no change
  // -----
  // leaf
  // lessThan
  // equalTo
  // evaluate
  // maxStack
  // maxQueue
  // sizeOf

  // touched in this function
  // -----
  // root SETROOTFROMTREE
  // allocator SsMmReset
  // stack SsStackReset
  // queue SsQueueReset
  // num

  num = _this->num;

  _this->num = 0;

  SETROOTFROMTREE(_this, 0);

  SsQueueReset(_this->queue);
  SsStackReset(_this->stack);
  SsMmReset(_this->allocator);

  result = true;

label_return:
  return result ? (int64_t)num : -1;
}

// integrated for root sentinel
int64_t SsSetNum(ssSet* _this)
{
  bool result = false;

  uint32_t num = 0;

  if( !_this)
  {
    _log("error");
    goto label_return;
  }

  // root
  // leaf
  // lessThan
  // equalTo
  // evaluate
  // allocator
  // stack
  // queue
  // maxStack
  // maxQueue
  // num
  // sizeOf

  // no change
  // -----
  // root
  // leaf
  // lessThan
  // equalTo
  // evaluate
  // allocator
  // stack
  // queue
  // maxStack
  // maxQueue
  // num
  // sizeOf

  // touched in this function
  // -----
  // n/a

  num = _this->num;

  result = true;

label_return:
  return result ? (int64_t)num : -1;
}

int64_t SsSetDepthTree(ssSet* _this)
{
  bool result = false;

  uint32_t depthTree = 0;

  if( !_this)
  {
    _log("error");
    goto label_return;
  }

  // root
  // leaf
  // lessThan
  // equalTo
  // evaluate
  // allocator
  // stack
  // queue
  // maxStack
  // maxQueue
  // num
  // sizeOf

  // no change
  // -----
  // root
  // leaf
  // lessThan
  // equalTo
  // evaluate
  // allocator
  // stack
  // queue
  // maxStack
  // maxQueue
  // num
  // sizeOf

  // touched in this function
  // -----
  // n/a

  depthTree = DepthMax(GETROOTFROMTREE(_this) );

  result = true;

label_return:
  return result ? (int64_t)depthTree : -1;
}

int64_t SsSetMaxStack(ssSet* _this)
{
  bool result = false;

  int64_t maxStack = 0;

  if( !_this)
  {
    _log("error");
    goto label_return;
  }

  // root
  // leaf
  // lessThan
  // equalTo
  // evaluate
  // allocator
  // stack
  // queue
  // maxStack
  // maxQueue
  // num
  // sizeOf

  // no change
  // -----
  // root
  // leaf
  // lessThan
  // equalTo
  // evaluate
  // allocator
  // stack
  // queue
  // maxStack
  // maxQueue
  // num
  // sizeOf

  // touched in this function
  // -----
  // n/a

  maxStack = _this->maxStack;

  result = true;

label_return:
  return result ? maxStack : -1;
}

int64_t SsSetMaxQueue(ssSet* _this)
{
  bool result = false;

  int64_t maxQueue = 0;

  if( !_this)
  {
    _log("error");
    goto label_return;
  }

  // root
  // leaf
  // lessThan
  // equalTo
  // evaluate
  // allocator
  // stack
  // queue
  // maxStack
  // maxQueue
  // num
  // sizeOf

  // no change
  // -----
  // root
  // leaf
  // lessThan
  // equalTo
  // evaluate
  // allocator
  // stack
  // queue
  // maxStack
  // maxQueue
  // num
  // sizeOf

  // touched in this function
  // -----
  // n/a

  maxQueue = _this->maxQueue;

  result = true;

label_return:
  return result ? maxQueue : -1;
}

// integrated for root sentinel
int64_t SsSetDestruct(ssSet* _this)
{
  bool result = false;

  uint32_t num = 0;

  if( !_this)
  {
    _log("error");
    goto label_return;
  }
  
  // _this

  // root
  // leaf
  // lessThan
  // equalTo
  // evaluate
  // allocator
  // stack
  // queue
  // maxStack
  // maxQueue
  // num
  // sizeOf

  // no other change, then cleared in BlahFree
  // -----
  // root
  // leaf
  // lessThan
  // equalTo
  // evaluate
  // maxStack
  // maxQueue
  // num
  // sizeOf

  // first touched in this function, then cleared in BlahFree
  // -----
  // allocator SsMmDestruct
  // stack SsStackDestruct
  // queue SsQueueDestruct

  num = _this->num;

  SsQueueDestruct( &_this->queue);
  SsStackDestruct( &_this->stack);
  SsMmDestruct( &_this->allocator);

  BlahFree(_this, sizeof(ssSet), true);
  _this = 0;

  result = true;

label_return:
  return result ? (int64_t)num : -1;
}

// integrated for root sentinel
ssSet* SsSetConstruct(uint32_t sizeOf, uint32_t minimum, int64_t maximum, uint32_t resize, SsSetCompare lessThan)
{
  bool result = false;

  ssSet* _this = 0;

  uint32_t stackSize = 0;
  uint32_t queueSize = 0;

  if( !sizeOf || !minimum || minimum > (uint32_t)maximum || !resize || !lessThan)
  {
    _log("error");
    goto label_return;
  }
  
  // _this

  // root
  // leaf
  // lessThan
  // equalTo
  // evaluate
  // allocator
  // stack
  // queue
  // maxStack
  // maxQueue
  // num
  // sizeOf

  // cleared in BlahAlloc, then no other change
  // -----
  // root
  // leaf
  // equalTo
  // evaluate
  // maxStack
  // maxQueue
  // num

  // cleared in BlahAlloc, then further touched in this function
  // -----
  // lessThan
  // allocator SsMmConstruct
  // stack SsStackConstruct
  // queue SsQueueConstruct
  // sizeOf

  _this = (ssSet*)BlahAlloc(sizeof(ssSet), true);
  if( !_this)
  {
    _log("error");
    goto label_return;
  }

  _this->lessThan = lessThan;

  _this->sizeOf = sizeOf;

  _this->allocator = SsMmConstruct(sizeof(SsSetNode) + sizeOf, minimum, maximum, resize);
  if( !_this->allocator)
  {
    _log("error");
    goto label_return;
  }

  stackSize = 2 * CalculateLogBase2( (int64_t)minimum + 1);
  if( !stackSize)
    stackSize = 1;

  _this->stack = SsStackConstruct(sizeof(SsSetNode*), stackSize, maximum, resize);
  if( !_this->stack)
  {
    _log("error");
    goto label_return;
  }

  queueSize = minimum / 2;
  if( !queueSize)
    queueSize = 1;

  _this->queue = SsQueueConstruct(sizeof(SsSetNode*), queueSize, maximum, resize);
  if( !_this->queue)
  {
    _log("error");
    goto label_return;
  }

  result = true;

label_return:
  return result ? _this : 0;
}
