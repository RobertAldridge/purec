
// File Name: bintree.cpp
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

#define RED 1
#define BLACK 2

#define GETCLIENT(node) (void*)(node + 1)

//#define GETROOTFROMSENTINEL(sentinel) (sentinel->left)
//#define SETROOTFROMSENTINEL(sentinel, node) (sentinel->left = node)

#define GETROOTFROMTREE(tree) (tree->root.left)
#define SETROOTFROMTREE(tree, node) (tree->root.left = node)

#define SETROOTCOLORFROMTREE(tree, value) (tree->root.left->color = value)

#define GETSENTINELFROMTREE(tree) ( &tree->root)

#define LESSTHANWRAPPER(tree, client, node) \
  (node == GETSENTINELFROMTREE(tree) ? 1 : tree->lessThan(client, GETCLIENT(node) ) )

//#define EQUALTOWRAPPER(tree, client, node) \
//  (node == GETSENTINELFROMTREE(tree) ? 0 : tree->equalTo(client, GETCLIENT(node) ) )

//#define CLIENTEVALUATEWRAPPER(tree, node) \
//  (node == GETSENTINELFROMTREE(tree) ? 0 : tree->clientEvaluate(GETCLIENT(node) ) )

//#define _log(blah) {}
#define _log(blah) printf("%s\n", blah)

// bintree.cpp
static uint32_t DepthMax(SsSetNode* node);
static uint32_t CalculateLogBase2(uint32_t number);
static SsSetNode* TreeMinimum(SsSetNode* node);
static SsSetNode* TreeMaximum(SsSetNode* node);
static SsSetNode* TreeSuccessor(SsSetNode* x);
static SsSetNode* TreeSearch(SsSetNode* x, void* objectKey, binaryTreeCompare LessThan, binaryTreeEquivalence EqualTo);

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
static void TreeInsert(ssSet* tree, SsSetNode* insert);
static void BinInsert(ssSet* tree, SsSetNode* x);

#include "bininsert_nocomments.cpp"

// binremove.cpp
static void BinDeleteFixup(ssSet* tree, SsSetNode* x);
static SsSetNode* BinDelete(ssSet* tree, SsSetNode* z);

#include "binremove_nocomments.cpp"

// bintraverse.cpp
static void IterativePreorderTreeTraverse(ssSet* tree, SsSetNode* node, binaryTreeEvaluate ClientEvaluate);
static void IterativeInorderTreeTraverse(ssSet* tree, SsSetNode* node, binaryTreeEvaluate ClientEvaluate);
static void IterativePostorderTreeTraverse(ssSet* tree, SsSetNode* node, binaryTreeEvaluate ClientEvaluate);
static void IterativeLevelorderTreeTraverse(ssSet* tree, SsSetNode* node, binaryTreeEvaluate ClientEvaluate);

#include "bintraverse_nocomments.cpp"

uint32_t DepthMax(SsSetNode* node)
{
  uint32_t result = 0;

  uint32_t left = 0;
  uint32_t right = 0;

  if( !node)
    goto error;

  left = DepthMax(node->left);

  right = DepthMax(node->right);

  if(left >= right)
    result = left + 1;
  else
    result = right + 1;

error:
  return result;
}

uint32_t CalculateLogBase2(uint32_t number)
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
SsSetNode* TreeSearch(SsSetNode* x, void* objectKey, binaryTreeCompare lessThan, binaryTreeEquivalence equalTo)
{
  while(x && !equalTo(objectKey, GETCLIENT(x) ) )
  {
    if(lessThan(objectKey, GETCLIENT(x) ) )
      x = x->left;
    else
      x = x->right;
  }

  return x;
}

// integrated for root sentinel
bool SsSetGetExtrema(ssSet* _this, int getGreatest, void* client, bool* found)
{
  ssSet* tree = (ssSet*)this;

  int result = RETURN_ERROR;

  SsSetNode* node = 0;

  if( !tree || (getGreatest != TRUE && getGreatest != FALSE) )
  {
    _log("error");
    goto error;
  }

  if(getGreatest == FALSE)
    node = TreeMinimum(GETROOTFROMTREE(tree) );
  else
    node = TreeMaximum(GETROOTFROMTREE(tree) );

  if( !node)
    goto error;

  if(objectReturn)
    memcpy(objectReturn, GETCLIENT(node), tree->sizeOfClient);

  result = RETURN_OK;

error:
  return result;
}

// integrated for root sentinel
bool SsSetFind(ssSet* _this, void* key, SsSetEquivalence equalTo, void* client, bool* found)
{
  ssSet* tree = (ssSet*)this;

  int result = RETURN_ERROR;

  SsSetNode* node = 0;
  
  if( !found)
    goto error;
  
  *found = false;

  if( !tree || !object1)
  {
    _log("error");
    goto error;
  }

  if(equalTo)
    tree->equalTo = equalTo;

  if( !tree->equalTo)
  {
    _log("error");
    goto error;
  }

  node = TreeSearch(GETROOTFROMTREE(tree), object1, tree->lessThan, tree->equalTo);

  if(node)
  {
    if(objectReturn)
      memcpy(objectReturn, GETCLIENT(node), tree->sizeOfClient);

    *found = true;
    result = RETURN_OK;
  }

error:
  return result;
}

// integrated for root sentinel
bool SsSetReset(ssSet* _this)
{
  ssSet* tree = (ssSet*)this;

  int result = RETURN_ERROR;

  if(tree)
  {
    tree->numberOfNodes = 0;

    SETROOTFROMTREE(tree, 0);

    SsQueueReset(tree->queue);
    SsStackReset(tree->stack);
    SsMmReset(tree->allocator);

    result = RETURN_OK;
  }

  if(result != RETURN_OK)
  {
    _log("error");
  }

  return result;
}

// integrated for root sentinel
bool SsSetNum(ssSet* _this, uint32_t* num)
{
  ssSet* tree = (ssSet*)this;

  bool result = false;
  
  if( !num)
    goto error;
  
  *num = 0;

  if( !tree)
  {
    _log("error");
    goto error;
  }

  *num = _this->num;

  result = true;

error:
  return result;
}

int SsSetDepthTree(ssSet* _this)
{
  ssSet* tree = (ssSet*)this;

  int result = RETURN_ERROR;

  if( !tree)
  {
    _log("error");
    goto error;
  }

  result = (int)DepthMax(GETROOTFROMTREE(tree) );

error:
  return result;
}

int SsSetDepthStack(ssSet* _this)
{
  ssSet* tree = (ssSet*)this;

  int result = RETURN_ERROR;

  if( !tree)
  {
    _log("error");
    goto error;
  }

  result = (int)tree->maxStack;

error:
  return result;
}

int SsSetDepthQueue(ssSet* _this)
{
  ssSet* tree = (ssSet*)this;

  int result = RETURN_ERROR;

  if( !tree)
  {
    _log("error");
    goto error;
  }

  result = (int)tree->maxQueue;

error:
  return result;
}

// integrated for root sentinel
bool SsSetDestruct(ssSet* _this)
{
  ssSet* tree = (ssSet*)this;

  int result = RETURN_ERROR;

  if(tree)
  {
    SsQueueDestruct( &tree->queue);
    tree->queue = 0;

    SsStackDestruct( &tree->stack);
    tree->stack = 0;

    SsMmDestruct( &tree->allocator);
    tree->allocator = 0;

    BlahFree(tree, sizeof(ssSet), true);
    tree = 0;

    result = RETURN_OK;
  }

  if(result != RETURN_OK)
  {
    _log("error");
  }

  return result;
}

// integrated for root sentinel
ssSet* SsSetConstruct(uint32_t sizeOf, uint32_t minimum, uint32_t maximum, uint32_t resize, SsSetCompare lessThan)
{
  ssSet* tree = 0;

  void* result = 0;

  uint32_t stackSize = 0;

  if( !initialCapacity || !sizeOfClient || !lessThan)
  {
    _log("error");
    goto error;
  }

  tree = (ssSet*)BlahAlloc(sizeof(ssSet), true);
  if( !tree)
  {
    _log("error");
    goto error;
  }

  tree->lessThan = lessThan;

  tree->sizeOfClient = sizeOfClient;

  tree->allocator = SsMmConstruct(sizeof(SsSetNode) + sizeOfClient, initialCapacity, 4100000000, 10000000);
  if( !tree->allocator)
  {
    _log("error");
    goto error;
  }

  stackSize = 2 * CalculateLogBase2(initialCapacity + 1);

  tree->stack = SsStackConstruct(sizeof(SsSetNode*), stackSize, 4100000000, 10000000);
  if( !tree->stack)
  {
    _log("error");
    goto error;
  }

  tree->queue = SsQueueConstruct(sizeof(SsSetNode*), initialCapacity / 2, 4100000000, 10000000);
  if( !tree->queue)
  {
    _log("error");
    goto error;
  }

  result = tree;

error:
  return (bintree*)result;
}
