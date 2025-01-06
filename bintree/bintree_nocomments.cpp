
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

#include "blah_aligned_alloc.h"

#include "ssmm_nocomments.h"
#include "ssStack_nocomments.h"
#include "ssQueue_nocomments.h"

#include "bintree_nocomments.h"

typedef int ORDER;

#define PREORDER preorder
#define INORDER inorder
#define POSTORDER postorder
#define LEVELORDER levelorder

#include "binpriv_nocomments.h"

#undef TRUE
#define TRUE 1

#undef FALSE
#define FALSE 0

#define RED 1
#define BLACK 2

#define RETURN_OK 0
#define RETURN_ERROR -1

#define GETCLIENT(node) (void*)(node + 1)

//#define GETROOTFROMSENTINEL(sentinel) (sentinel->left)
//#define SETROOTFROMSENTINEL(sentinel, node) (sentinel->left = node)

#define GETROOTFROMTREE(tree) (tree->sentinelRoot.left)
#define SETROOTFROMTREE(tree, node) (tree->sentinelRoot.left = node)

#define SETROOTCOLORFROMTREE(tree, value) (tree->sentinelRoot.left->color = value)

#define GETSENTINELFROMTREE(tree) ( &tree->sentinelRoot)

#define LESSTHANWRAPPER(tree, client, node) \
  (node == GETSENTINELFROMTREE(tree) ? 1 : tree->lessThan(client, GETCLIENT(node) ) )

//#define EQUALTOWRAPPER(tree, client, node) \
//  (node == GETSENTINELFROMTREE(tree) ? 0 : tree->equalTo(client, GETCLIENT(node) ) )

//#define CLIENTEVALUATEWRAPPER(tree, node) \
//  (node == GETSENTINELFROMTREE(tree) ? 0 : tree->clientEvaluate(GETCLIENT(node) ) )

//#define _log(blah) {}
#define _log(blah) printf("%s\n", blah)

const int bintree::ok = 0;
const int bintree::error = -1;

const int bintree::empty = 1;

const int bintree::preorder = 0;
const int bintree::inorder = 1;
const int bintree::postorder = 2;
const int bintree::levelorder = 3;

// bintree.cpp
static uint32_t DepthMax(BinaryTreeNode* node);
static uint32_t CalculateLogBase2(uint32_t number);
static BinaryTreeNode* TreeMinimum(BinaryTreeNode* node);
static BinaryTreeNode* TreeMaximum(BinaryTreeNode* node);
static BinaryTreeNode* TreeSuccessor(BinaryTreeNode* x);
static BinaryTreeNode* TreeSearch(BinaryTreeNode* x, void* objectKey, binaryTreeCompare LessThan, binaryTreeEquivalence EqualTo);

uint32_t gDebugRotate[69] = {0};

// binleft.cpp
static void LeftRotateDelete1(BinaryTreeNode* xP);
static void LeftRotateDelete2(BinaryTreeNode* xP);
static void LeftRotateInsert(BinaryTreeNode* xPP);

// binleftleft.cpp
static void LeftLeftRotate(BinaryTreeNode* xP);

// binleftright.cpp
static void LeftRightRotateInsert(BinaryTreeNode* x);
static void LeftRightRotateDelete(BinaryTreeNode* xP);

// binleftrightleft.cpp
static void LeftRightLeftRotate(BinaryTreeNode* xP);

#include "binleft_nocomments.cpp"
#include "binleftleft_nocomments.cpp"
#include "binleftright_nocomments.cpp"
#include "binleftrightleft_nocomments.cpp"

// binright.cpp
static void RightRotateDelete1(BinaryTreeNode* xP);
static void RightRotateDelete2(BinaryTreeNode* xP);
static void RightRotateInsert(BinaryTreeNode* xPP);

// binrightright.cpp
static void RightRightRotate(BinaryTreeNode* xP);

// binrightleft.cpp
static void RightLeftRotateInsert(BinaryTreeNode* x);
static void RightLeftRotateDelete(BinaryTreeNode* xP);

// binrightleftright.cpp
static void RightLeftRightRotate(BinaryTreeNode* xP);

#include "binright_nocomments.cpp"
#include "binrightright_nocomments.cpp"
#include "binrightleft_nocomments.cpp"
#include "binrightleftright_nocomments.cpp"

// bininsert.cpp
static void TreeInsert(BinaryTree* tree, BinaryTreeNode* insert);
static void BinInsert(BinaryTree* tree, BinaryTreeNode* x);

#include "bininsert_nocomments.cpp"

// binremove.cpp
static void BinDeleteFixup(BinaryTree* tree, BinaryTreeNode* x);
static BinaryTreeNode* BinDelete(BinaryTree* tree, BinaryTreeNode* z);

#include "binremove_nocomments.cpp"

// bintraverse.cpp
static void IterativePreorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate);
static void IterativeInorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate);
static void IterativePostorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate);
static void IterativeLevelorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate);

#include "bintraverse_nocomments.cpp"

uint32_t DepthMax(BinaryTreeNode* node)
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
BinaryTreeNode* TreeMinimum(BinaryTreeNode* node)
{
  for(BinaryTreeNode* left = node; left; left = left->left)
    node = left;

  return node;
}

// integrated for root sentinel
BinaryTreeNode* TreeMaximum(BinaryTreeNode* node)
{
  for(BinaryTreeNode* right = node; right; right = right->right)
    node = right;

  return node;
}

BinaryTreeNode* TreeSuccessor(BinaryTreeNode* x)
{
  BinaryTreeNode* y = 0;

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
BinaryTreeNode* TreeSearch(BinaryTreeNode* x, void* objectKey, binaryTreeCompare lessThan, binaryTreeEquivalence equalTo)
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
int bintree::getExtrema(int getGreatest, void* objectReturn)
{
  BinaryTree* tree = (BinaryTree*)this;

  int result = RETURN_ERROR;

  BinaryTreeNode* node = 0;

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
int bintree::find(void* object1, binaryTreeEquivalence equalTo, void* objectReturn)
{
  BinaryTree* tree = (BinaryTree*)this;

  int result = RETURN_ERROR;

  BinaryTreeNode* node = 0;

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

    result = RETURN_OK;
  }
  else
  {
    result = bintree::empty;
  }

error:
  return result;
}

// integrated for root sentinel
int bintree::reset()
{
  BinaryTree* tree = (BinaryTree*)this;

  int result = RETURN_ERROR;

  if(tree)
  {
    tree->numberOfNodes = 0;

    SETROOTFROMTREE(tree, 0);

    uint32_t allocatorSize = 0;
    uint32_t stackSize = 0;
    uint32_t queueSize = 0;

    SsQueueReset(tree->queue, &queueSize);
    SsStackReset(tree->stack, &stackSize);
    SsmmReset(tree->allocator, &allocatorSize);

    result = RETURN_OK;
  }

  if(result != RETURN_OK)
  {
    _log("error");
  }

  return result;
}

// integrated for root sentinel
int bintree::isEmpty(uint32_t* numberOfClientObjects)
{
  BinaryTree* tree = (BinaryTree*)this;

  int result = RETURN_ERROR;

  if( !tree)
  {
    _log("error");
    goto error;
  }

  if(numberOfClientObjects)
    *numberOfClientObjects = tree->numberOfNodes;

  result = ( !tree->numberOfNodes ? bintree::empty : RETURN_OK);

error:
  return result;
}

int bintree::depthTree()
{
  BinaryTree* tree = (BinaryTree*)this;

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

int bintree::depthStack()
{
  BinaryTree* tree = (BinaryTree*)this;

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

int bintree::depthQueue()
{
  BinaryTree* tree = (BinaryTree*)this;

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
int bintree::term()
{
  BinaryTree* tree = (BinaryTree*)this;

  int result = RETURN_ERROR;

  if(tree)
  {
    uint32_t allocatorSize = 0;
    uint32_t stackSize = 0;
    uint32_t queueSize = 0;

    SsQueueDestruct( &tree->queue, &queueSize);
    tree->queue = 0;

    SsStackDestruct( &tree->stack, &stackSize);
    tree->stack = 0;

    SsmmDestruct( &tree->allocator, &allocatorSize);
    tree->allocator = 0;

    memset(tree, 0, sizeof(BinaryTree) );

    blah_free_aligned_sized(tree);
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
bintree* bintree::init(uint32_t initialCapacity, uint32_t sizeOfClient, binaryTreeCompare lessThan)
{
  BinaryTree* tree = 0;

  void* result = 0;

  uint32_t stackSize = 0;

  if( !initialCapacity || !sizeOfClient || !lessThan)
  {
    _log("error");
    goto error;
  }

  tree = (BinaryTree*)blah_aligned_alloc(sizeof(BinaryTree) );
  if( !tree)
  {
    _log("error");
    goto error;
  }

  tree->lessThan = lessThan;

  tree->sizeOfClient = sizeOfClient;

  tree->allocator = SsmmConstruct(sizeof(BinaryTreeNode) + sizeOfClient, initialCapacity, 4100000000, 10000000);
  if( !tree->allocator)
  {
    _log("error");
    goto error;
  }

  stackSize = 2 * CalculateLogBase2(initialCapacity + 1);

  tree->stack = SsStackConstruct(sizeof(BinaryTreeNode*), stackSize, 4100000000, 10000000);
  if( !tree->stack)
  {
    _log("error");
    goto error;
  }

  tree->queue = SsQueueConstruct(sizeof(BinaryTreeNode*), initialCapacity / 2, 4100000000, 10000000);
  if( !tree->queue)
  {
    _log("error");
    goto error;
  }

  result = tree;

error:
  return (bintree*)result;
}

bintree::bintree()
{
}

bintree::bintree(bintree& )
{
}

bintree& bintree::operator=(bintree& )
{
  return *this;
}
