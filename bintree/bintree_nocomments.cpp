
// File Name: bintree.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

#undef DEBUG
#undef _DEBUG
#undef NDEBUG
#define NDEBUG

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using std::free;
using std::malloc;
using std::memset;
using std::printf;
using std::ptrdiff_t;

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

#if defined(_MSC_VER)
  // conditional expression is constant
  #pragma warning (disable: 4127)

  // code dereferences a potentially null pointer
  #pragma warning (disable: 6011)

  // the code analysis tool isn't smart enough to figure out the pointer must be valid
  #pragma warning (disable: 28182)
#endif

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
  (node == GETSENTINELFROMTREE(tree) ? 1 : tree->LessThan(client, GETCLIENT(node) ) )

//#define EQUALTOWRAPPER(tree, client, node) \
//  (node == GETSENTINELFROMTREE(tree) ? 0 : tree->EqualTo(client, GETCLIENT(node) ) )

//#define CLIENTEVALUATEWRAPPER(tree, node) \
//  (node == GETSENTINELFROMTREE(tree) ? 0 : tree->ClientEvaluate(GETCLIENT(node) ) )

//#define _log(blah) {}
#define _log(blah) printf("%s\n", blah)

const int bintree::ok = 0;
const int bintree::error = -1;

const int bintree::empty = 1;

const int bintree::preorder = 0;
const int bintree::inorder = 1;
const int bintree::postorder = 2;
const int bintree::levelorder = 3;

static BinaryTreeNode* TreeMinimum(BinaryTreeNode* node);

static BinaryTreeNode* TreeMaximum(BinaryTreeNode* node);

static BinaryTreeNode* TreeSuccessor(BinaryTreeNode* x);

static BinaryTreeNode* TreeSearch(BinaryTreeNode* x, void* objectKey, binaryTreeCompare LessThan, binaryTreeEquivalence EqualTo);

int gDebugRotate[69] = {0};

static void LeftRotateDelete1(BinaryTreeNode* xP);
static void LeftRotateDelete2(BinaryTreeNode* xP);
static void LeftRotateInsert(BinaryTreeNode* xPP);

static void LeftLeftRotate(BinaryTreeNode* xP);

static void LeftRightRotateInsert(BinaryTreeNode* x);
static void LeftRightRotateDelete(BinaryTreeNode* xP);

static void LeftRightLeftRotate(BinaryTreeNode* xP);

#include "binleft.cpp"
#include "binleftleft.cpp"
#include "binleftright.cpp"
#include "binleftrightleft.cpp"

static void RightRotateDelete1(BinaryTreeNode* xP);
static void RightRotateDelete2(BinaryTreeNode* xP);
static void RightRotateInsert(BinaryTreeNode* xPP);

static void RightRightRotate(BinaryTreeNode* xP);

static void RightLeftRotateInsert(BinaryTreeNode* x);
static void RightLeftRotateDelete(BinaryTreeNode* xP);

static void RightLeftRightRotate(BinaryTreeNode* xP);

#include "binright.cpp"
#include "binrightright.cpp"
#include "binrightleft.cpp"
#include "binrightleftright.cpp"

static void TreeInsert(BinaryTree* tree, BinaryTreeNode* insert);

static void BinInsert(BinaryTree* tree, BinaryTreeNode* x);

#include "bininsert.cpp"

static void BinDeleteFixup(BinaryTree* tree, BinaryTreeNode* x);

static BinaryTreeNode* BinDelete(BinaryTree* tree, BinaryTreeNode* z);

#include "binremove.cpp"

static void IterativePreorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate);

static void IterativeInorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate);

static void IterativePostorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate);

static void IterativeLevelorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate);

#include "bintraverse.cpp"

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
    return TreeMinimum(x->right);

  for(y = x->parent; y && x == y->right; y = y->parent)
    x = y;

  return y;
}

// integrated for root sentinel
BinaryTreeNode* TreeSearch(BinaryTreeNode* x, void* objectKey, binaryTreeCompare LessThan, binaryTreeEquivalence EqualTo)
{
  while(x && !EqualTo(objectKey, GETCLIENT(x) ) )
  {
    if(LessThan(objectKey, GETCLIENT(x) ) )
      x = x->left;
    else
      x = x->right;
  }

  return x;
}

// integrated for root sentinel
int bintree::getExtrema(int GetGreatest, void* objectReturn)
{
  BinaryTree* tree = (BinaryTree*)this;

  BinaryTreeNode* node = 0;

  if( !tree || (GetGreatest != TRUE && GetGreatest != FALSE) )
  {
    _log("error");
    return RETURN_ERROR;
  }

  if(GetGreatest == FALSE)
    node = TreeMinimum(GETROOTFROMTREE(tree) );
  else
    node = TreeMaximum(GETROOTFROMTREE(tree) );

  if( !node)
    return RETURN_ERROR;

  if(objectReturn)
    memcpy(objectReturn, GETCLIENT(node), tree->SizeOfClientExact);

  return RETURN_OK;
}

// integrated for root sentinel
int bintree::find(void* Object1, binaryTreeEquivalence EqualTo, void* ObjectReturn)
{
  BinaryTree* tree = (BinaryTree*)this;

  BinaryTreeNode* node = 0;

  if( !tree || !Object1)
  {
    _log("error");
    return RETURN_ERROR;
  }

  if(EqualTo)
    tree->EqualTo = EqualTo;

  if( !tree->EqualTo)
  {
    _log("error");
    return RETURN_ERROR;
  }

  node = TreeSearch(GETROOTFROMTREE(tree), Object1, tree->LessThan, tree->EqualTo);

  if(node)
  {
    if(ObjectReturn)
      memcpy(ObjectReturn, GETCLIENT(node), tree->SizeOfClientExact);

    return RETURN_OK;
  }
  else
  {
    return bintree::empty;
  }

  return RETURN_ERROR;
}

// integrated for root sentinel
int bintree::reset()
{
  BinaryTree* tree = (BinaryTree*)this;

  if(tree)
  {
    tree->NumberOfNodes = 0;

    SETROOTFROMTREE(tree, 0);
    
    SsQueueReset(ssQueue);
    SsStackReset(ssStack);
    SsmmReset(ssmm);

    return RETURN_OK;
  }

  _log("error");
  return RETURN_ERROR;
}

// integrated for root sentinel
int bintree::isEmpty(int* NumberOfClientObjects)
{
  BinaryTree* tree = (BinaryTree*)this;

  if( !tree)
  {
    _log("error");
    return RETURN_ERROR;
  }

  if(NumberOfClientObjects)
    *NumberOfClientObjects = tree->NumberOfNodes;

  return !tree->NumberOfNodes ? bintree::empty : RETURN_OK;
}

static int depthMax(BinaryTreeNode* node)
{
  if( !node)
    return 0;

  int left = depthMax(node->left);

  int right = depthMax(node->right);

  if(left >= right)
    return left + 1;
  else
    return right + 1;
}

int bintree::depthTree()
{
  BinaryTree* tree = (BinaryTree*)this;

  if( !tree)
  {
    _log("error");
    return RETURN_ERROR;
  }

  return depthMax(GETROOTFROMTREE(tree) );
}

int bintree::depthStack()
{
  BinaryTree* tree = (BinaryTree*)this;

  if( !tree)
  {
    _log("error");
    return RETURN_ERROR;
  }

  return tree->maxStack;
}

int bintree::depthQueue()
{
  BinaryTree* tree = (BinaryTree*)this;

  if( !tree)
  {
    _log("error");
    return RETURN_ERROR;
  }

  return tree->maxQueue;
}

// integrated for root sentinel
int bintree::term()
{
  BinaryTree* tree = (BinaryTree*)this;

  if(tree)
  {
    SsQueueDestruct( &tree->queue);
    
    SsStackDestruct( &tree->stack);

    SsmmDestruct( &tree->allocator);

    memset(tree, 0, sizeof(BinaryTree) );

    free(tree);

    return RETURN_OK;
  }

  _log("error");
  return RETURN_ERROR;
}

static int calculateLogBase2(int number)
{
  int result = 0;

  while(number)
  {
    result++;

    number /= 2;
  }

  return result;
}

// integrated for root sentinel
bintree* bintree::init(int initialCapacity, int SizeOfEachObjectExact, binaryTreeCompare LessThan)
{
  BinaryTree* tree = 0;

  int SizeOfEachObjectAligned = 0;

  int loop = 0;

  int stackSize = 0;

  if(initialCapacity <= 0 || SizeOfEachObjectExact <= 0 || !LessThan)
  {
    _log("error");
    return 0;
  }

  tree = (BinaryTree*)malloc(sizeof(BinaryTree) );

  if( !tree)
  {
    _log("error");
    return 0;
  }

  memset(tree, 0, sizeof(BinaryTree) );

  tree->LessThan = LessThan;

  tree->SizeOfClientExact = SizeOfEachObjectExact;

  //tree->SizeOfClientAligned = SizeOfEachObjectAligned;
  tree->SizeOfClientAligned = SizeOfEachObjectExact;

  //SsConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize)

  tree->allocator = SsmmConstruct(SizeOfEachObjectAligned + sizeof(BinaryTreeNode), initialCapacity, 200000000, -1000000);
  if( !tree->allocator)
  {
    _log("error");
    return 0;
  }

  stackSize = 2 * calculateLogBase2(initialCapacity + 1);

  tree->stack = SsStackConstruct(sizeof(BinaryTreeNode*), stackSize, 200000000, -1000000);
  if( !tree->stack)
  {
    _log("error");
    return 0;
  }

  tree->queue = SsQueueConstruct(sizeof(BinaryTreeNode*), initialCapacity / 4, 200000000, -1000000);
  if( !tree->queue)
  {
    _log("error");
    return 0;
  }

  return (bintree*)tree;
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
