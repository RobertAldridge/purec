
// ssSet.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

//#include <cstdint> // int64_t, uint32_t
//#include <cstring> // memcpy

//using std::int64_t;
//using std::memcpy;
//using std::uint32_t;

#include "BlahAlloc.h"

#include "BlahLog.h"

#include "ssMm.h"
#include "ssStack.h"
#include "ssQueue.h"

#include "ssSet.h"

struct SsSetNode
{
  SsSetNode* left;
  SsSetNode* right;
  SsSetNode* parent;

  uint32_t color;

  uint32_t padding;
};

struct ssSet
{
  // sentinel
  SsSetNode root;

  // sentinel
  SsSetNode leaf;

  // sentinel
  SsSetNode end;

  SsSetCompare lessThan;

  SsSetEvaluate evaluate;

  // main allocator for ssSet nodes
  ssMm* allocator;

  // for interative pre-order, in-order, post-order traversal
  ssStack* stack;

  // for interactive level-order traversal
  ssQueue* queue;

  int64_t maxStack;
  int64_t maxQueue;

  uint32_t num;

  uint32_t sizeOf;

  int64_t debug[88];

  SsSetNode* iterator;
  SsSetNode* current;
  int64_t index;
};

const uint32_t SsSetRed = 1;
const uint32_t SsSetBlack = 2;

#define GETCLIENT(node) (void*)(node + 1)

//#define GETROOTFROMSENTINEL(sentinel) (sentinel->left)
//#define SETROOTFROMSENTINEL(sentinel, node) (sentinel->left = node)

#define GETROOTFROMTREE(_this) (_this->root.left)
#define SETROOTFROMTREE(_this, node) (_this->root.left = node)

#define SETROOTCOLORFROMTREE(_this, value) (_this->root.left->color = value)

#define GETSENTINELFROMTREE(_this) ( &_this->root)

#define LESSTHANWRAPPER(_this, client, node, lessThan) \
  (node == GETSENTINELFROMTREE(_this) ? 1 : lessThan(client, GETCLIENT(node) ) )

#define EQUALTOWRAPPER(lessThan, lhs, rhs) !lessThan(lhs, rhs) && !lessThan(rhs, lhs)

//#define EQUALTOWRAPPER(_this, client, node, lessThan) \
//  (node == GETSENTINELFROMTREE(_this) ? 0 : EQUALTOWRAPPER(lessThan, client, GETCLIENT(node) ) )

//#define CLIENTEVALUATEWRAPPER(_this, node, evaluate) \
//  (node == GETSENTINELFROMTREE(_this) ? 0 : evaluate(GETCLIENT(node) ) )

// ssSet.cpp
static uint32_t SsSetDepthTreeLevel2(SsSetNode* node);
static uint32_t SsSetCalculateLogBase2Level2(int64_t number);
static SsSetNode* SsSetTreeSearchLevel2(SsSetNode* x, void* objectKey, SsSetCompare lessThan);

// ssSetLeft.cpp
static void SsSetRotateLeftErase1Level4(ssSet* _this, SsSetNode* xP);
static void SsSetRotateLeftErase2Level4(ssSet* _this, SsSetNode* xP);
static void SsSetRotateLeftInsertLevel3(ssSet* _this, SsSetNode* xPP);

// ssSetLeftLeft.cpp
static void SsSetRotateLeftLeftEraseLevel4(ssSet* _this, SsSetNode* xP);

// ssSetLeftRight.cpp
static void SsSetRotateLeftRightInsertLevel3(ssSet* _this, SsSetNode* x);
static void SsSetRotateLeftRightEraseLevel4(ssSet* _this, SsSetNode* xP);

// ssSetLeftRightLeft.cpp
static void SsSetRotateLeftRightLeftEraseLevel4(ssSet* _this, SsSetNode* xP);

// ssSetRight.cpp
static void SsSetRotateRightErase1Level4(ssSet* _this, SsSetNode* xP);
static void SsSetRotateRightErase2Level4(ssSet* _this, SsSetNode* xP);
static void SsSetRotateRightInsertLevel3(ssSet* _this, SsSetNode* xPP);

// ssSetRightRight.cpp
static void SsSetRotateRightRightEraseLevel4(ssSet* _this, SsSetNode* xP);

// ssSetRightLeft.cpp
static void SsSetRotateRightLeftInsertLevel3(ssSet* _this, SsSetNode* x);
static void SsSetRotateRightLeftEraseLevel4(ssSet* _this, SsSetNode* xP);

// ssSetRightLeftRight.cpp
static void SsSetRotateRightLeftRightEraseLevel4(ssSet* _this, SsSetNode* xP);

// ssSetInsert.cpp
static bool SsSetInsertLevel3(ssSet* _this, SsSetNode* insert, SsSetCompare lessThan);
static bool SsSetInsertLevel2(ssSet* _this, SsSetNode* x, SsSetCompare lessThan);

// ssSetErase.cpp
static void SsSetEraseLevel3(ssSet* _this, SsSetNode* x);
static SsSetNode* SsSetEraseLevel2(ssSet* _this, SsSetNode* z);

// ssSetDump.cpp
static int64_t SsSetDumpLevel2preorder(ssSet* _this, SsSetNode* node, SsSetEvaluate ClientEvaluate);
static int64_t SsSetDumpLevel2inorder(ssSet* _this, SsSetNode* node, SsSetEvaluate ClientEvaluate);
static int64_t SsSetDumpLevel2postorder(ssSet* _this, SsSetNode* node, SsSetEvaluate ClientEvaluate);
static int64_t SsSetDumpLevel2levelorder(ssSet* _this, SsSetNode* node, SsSetEvaluate ClientEvaluate);

// ssSet.cpp

#include "ssSetLeft.cpp"
#include "ssSetLeftLeft.cpp"
#include "ssSetLeftRight.cpp"
#include "ssSetLeftRightLeft.cpp"

#include "ssSetRight.cpp"
#include "ssSetRightRight.cpp"
#include "ssSetRightLeft.cpp"
#include "ssSetRightLeftRight.cpp"

#include "ssSetInsert.cpp"

#include "ssSetErase.cpp"

#include "ssSetDump.cpp"

uint32_t SsSetDepthTreeLevel2(SsSetNode* node)
{
  uint32_t result = 0;

  uint32_t left = 0;
  uint32_t right = 0;

  if( !node)
    goto label_return;

  left = SsSetDepthTreeLevel2(node->left);

  right = SsSetDepthTreeLevel2(node->right);

  if(left >= right)
    result = left + 1;
  else
    result = right + 1;

label_return:
  return result;
}

uint32_t SsSetCalculateLogBase2Level2(int64_t number)
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
SsSetNode* SsSetTreeSearchLevel2(SsSetNode* x, void* objectKey, SsSetCompare lessThan)
{
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

  return x;
}

// integrated for root sentinel
int64_t SsSetGetExtrema(ssSet* _this, bool maximum, void* client)
{
  bool result = false;

  int notFound = 1;

  SsSetNode* node = 0;

  if( !_this)
  {
    BlahLog("error");
    goto label_return;
  }

  // root
  // leaf
  // lessThan
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
  {
    // hierarchical rightmost starting at root; tree maximum
    for(SsSetNode* right = GETROOTFROMTREE(_this); right; right = right->right)
      node = right;
  }
  else
  {
    // hierarchical leftmost starting at root; tree minimum
    for(SsSetNode* left = GETROOTFROMTREE(_this); left; left = left->left)
      node = left;
  }

  if(node)
  {
    notFound = 0;

    if(client)
      memcpy(client, GETCLIENT(node), _this->sizeOf);
  }

  result = true;

label_return:
  return result ? notFound : SsSetError;
}

// integrated for root sentinel
int64_t SsSetFind(ssSet* _this, void* key, SsSetCompare lessThan, void* client)
{
  bool result = false;

  int notFound = 1;

  SsSetNode* node = 0;

  if( !_this || !key)
  {
    BlahLog("error");
    goto label_return;
  }

  if( !lessThan && !_this->lessThan)
  {
    BlahLog("error");
    goto label_return;
  }

  // root
  // leaf
  // lessThan
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

  if( !lessThan)
    lessThan = _this->lessThan;

  node = SsSetTreeSearchLevel2(GETROOTFROMTREE(_this), key, lessThan);

  if(node)
  {
    notFound = 0;

    if(client)
      memcpy(client, GETCLIENT(node), _this->sizeOf);
  }

  result = true;

label_return:
  return result ? notFound : SsSetError;
}

// integrated for root sentinel
int64_t SsSetReset(ssSet* _this)
{
  bool result = false;

  uint32_t num = 0;

  if( !_this)
  {
    BlahLog("error");
    goto label_return;
  }

  // root
  // leaf
  // lessThan
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

  _this->iterator = &_this->end;
  _this->current = 0;
  _this->index = _this->num;

  result = true;

label_return:
  return result ? (int64_t)num : SsSetError;
}

// integrated for root sentinel
int64_t SsSetNum(ssSet* _this)
{
  bool result = false;

  uint32_t num = 0;

  if( !_this)
  {
    BlahLog("error");
    goto label_return;
  }

  // root
  // leaf
  // lessThan
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
  return result ? (int64_t)num : SsSetError;
}

int64_t SsSetDepthTree(ssSet* _this)
{
  bool result = false;

  uint32_t depthTree = 0;

  if( !_this)
  {
    BlahLog("error");
    goto label_return;
  }

  // root
  // leaf
  // lessThan
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

  depthTree = SsSetDepthTreeLevel2(GETROOTFROMTREE(_this) );

  result = true;

label_return:
  return result ? (int64_t)depthTree : SsSetError;
}

int64_t SsSetMaxStack(ssSet* _this)
{
  bool result = false;

  int64_t maxStack = 0;

  if( !_this)
  {
    BlahLog("error");
    goto label_return;
  }

  // root
  // leaf
  // lessThan
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
  return result ? maxStack : SsSetError;
}

int64_t SsSetMaxQueue(ssSet* _this)
{
  bool result = false;

  int64_t maxQueue = 0;

  if( !_this)
  {
    BlahLog("error");
    goto label_return;
  }

  // root
  // leaf
  // lessThan
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
  return result ? maxQueue : SsSetError;
}

int64_t SsSetGetDebug(ssSet* _this, uint32_t index)
{
  bool result = false;

  int64_t debug = 0;

  if( !_this || index >= countof(_this->debug) )
  {
    BlahLog("error");
    goto label_return;
  }

  // root
  // leaf
  // lessThan
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

  debug = _this->debug[index];

  result = true;

label_return:
  return result ? debug : SsSetError;
}

// integrated for root sentinel
int64_t SsSetDestruct(ssSet** reference)
{
  bool result = false;

  ssSet* _this = 0;

  uint32_t num = 0;

  if( !reference)
  {
    BlahLog("error");
    goto label_return;
  }

  _this = reference[0];

  if( !_this)
  {
    BlahLog("error");
    goto label_return;
  }

  // _this

  // root
  // leaf
  // lessThan
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

  reference[0] = 0;

  result = true;

label_return:
  return result ? (int64_t)num : SsSetError;
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
    BlahLog("error");
    goto label_return;
  }

  // _this

  // root
  // leaf
  // lessThan
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
    BlahLog("error");
    goto label_return;
  }

  _this->lessThan = lessThan;

  _this->sizeOf = sizeOf;

  _this->allocator = SsMmConstruct(sizeof(SsSetNode) + sizeOf, minimum, maximum, resize);
  if( !_this->allocator)
  {
    BlahLog("error");
    goto label_return;
  }

  stackSize = 2 * SsSetCalculateLogBase2Level2( (int64_t)minimum + 1);
  if( !stackSize)
    stackSize = 1;

  _this->stack = SsStackConstruct(sizeof(SsSetNode*), stackSize, maximum, resize);
  if( !_this->stack)
  {
    BlahLog("error");
    goto label_return;
  }

  queueSize = minimum / 2;
  if( !queueSize)
    queueSize = 1;

  _this->queue = SsQueueConstruct(sizeof(SsSetNode*), queueSize, maximum, resize);
  if( !_this->queue)
  {
    BlahLog("error");
    goto label_return;
  }

  _this->iterator = &_this->end;
  _this->current = 0;
  _this->index = _this->num;

  result = true;

label_return:
  return result ? _this : 0;
}
