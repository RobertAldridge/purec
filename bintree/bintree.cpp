
// File Name: bintree.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

//#include "../../general.h"

#if defined(_MSC_VER)
  #pragma warning (push, 4)
#endif

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

//#include <malloc.h>
//#include <memory.h>

//#include "ptrtrack.h"

#include "bintree.h"

typedef int ORDER;

#define PREORDER preorder
#define INORDER inorder
#define POSTORDER postorder
#define LEVELORDER levelorder

#include "binpriv.h"
//#include "../debugutils/log.h"

//#ifdef __cplusplus
//  extern "C" {
//#endif

#if defined(_MSC_VER)
  #pragma warning (disable: 4127)
  #pragma warning (disable: 4711)

  #pragma warning (disable: 6011)
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

#if !defined(_MSC_VER)
  #define __forceinline inline
#endif

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

#define _log(blah) {}

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

#if 0
left (delete) 2
left (insert) 1
left-left (delete) 1
left-right (delete) 1
left-right (insert) 1
left-right-left (delete) 1

right (delete) 2
right (insert) 1
right-right (delete) 1
right-left (delete) 1
right-left (insert) 1
right-left-right (delete) 1
#endif

int gDebugRotate[69] = {0};

// LeftRotate(xP)
// LeftRotate(xPP)
static void LeftRotateDelete1(BinaryTreeNode* xP);
static void LeftRotateDelete2(BinaryTreeNode* xP);
static void LeftRotateInsert(BinaryTreeNode* xPP);

// LeftLeftRotate(xP)
static void LeftLeftRotate(BinaryTreeNode* xP);

// LeftRightRotate(x)
// LeftRightRotate(xP)
static void LeftRightRotateInsert(BinaryTreeNode* x);
static void LeftRightRotateDelete(BinaryTreeNode* xP);

// LeftRightLeftRotate(xP)
static void LeftRightLeftRotate(BinaryTreeNode* xP);

#include "binleft.cpp"
#include "binleftleft.cpp"
#include "binleftright.cpp"
#include "binleftrightleft.cpp"

// RightRotate(xP)
// RightRotate(xPP)
static void RightRotateDelete1(BinaryTreeNode* xP);
static void RightRotateDelete2(BinaryTreeNode* xP);
static void RightRotateInsert(BinaryTreeNode* xPP);

// RightRightRotate(xP)
static void RightRightRotate(BinaryTreeNode* xP);

// RightLeftRotate(x)
// RightLeftRotate(xP)
static void RightLeftRotateInsert(BinaryTreeNode* x);
static void RightLeftRotateDelete(BinaryTreeNode* xP);

// RightLeftRightRotate(xP)
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
  {
    x = y;
  }

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

//
// GetGreatest - An int which if TRUE, causes the greatest POTYPE
//               to be returned.  If FALSE, it causes the the least POTYPE
//               value to be returned.
//

// integrated for root sentinel
int bintree::getExtrema(int GetGreatest, void* objectReturn)
{
  BinaryTree* tree = (BinaryTree*)this;

  BinaryTreeNode* node = 0;

  if( !tree || (GetGreatest != TRUE && GetGreatest != FALSE) )
  {
    // BinGetExtrema(...) bad params
    _log("error");
    return RETURN_ERROR;
  }

  if(GetGreatest == FALSE)
  {
    node = TreeMinimum(GETROOTFROMTREE(tree) );
  }
  else /* GetGreatest == TRUE */
  {
    node = TreeMaximum(GETROOTFROMTREE(tree) );
  }

  if( !node)
  {
    // BinGetExtrema(...) empty tree
    return RETURN_ERROR;
  }

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
    // BinTreeFind(...) bad params
    _log("error");
    return RETURN_ERROR;
  }

  if(EqualTo)
    tree->EqualTo = EqualTo;

  if( !tree->EqualTo)
  {
    // BinTreeFind(...) NIL binaryTreeEquivalence function
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
    char* Memory = (char*)tree->TraverseArrayStart;

    int MemoryArrayPointerSize = sizeof(char*) * tree->MaxNumberOfNodes;

    int loop = 0;

    tree->NumberOfNodes = 0;

    Memory += MemoryArrayPointerSize;

    tree->MemoryManagerArrayCurrent = (char**)Memory;

    Memory += MemoryArrayPointerSize;

    for(loop = 0; loop < tree->MaxNumberOfNodes; loop++)
    {
      tree->MemoryManagerArrayCurrent[loop] = Memory;

      Memory += tree->SizeOfClientAligned + sizeof(BinaryTreeNode);
    }

    SETROOTFROMTREE(tree, 0);

    return RETURN_OK;
  }

  // BinTreeReset(...) bad params
  _log("error");
  return RETURN_ERROR;
}

// integrated for root sentinel
int bintree::isEmpty(int* NumberOfClientObjects)
{
  BinaryTree* tree = (BinaryTree*)this;

  if( !tree)
  {
    // BinTreeIsEmpty(...) bad params
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
    // bintree::depthTree(...) bad params
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
    // bintree::depthStack(...) bad params
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
    // bintree::depthQueue(...) bad params
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
    memset(tree, 0, tree->MemoryTotalSize);

    free(tree);

    return RETURN_OK;
  }

  // BinTreeTerminate(...) bad params
  _log("error");
  return RETURN_ERROR;
}

// integrated for root sentinel
bintree* bintree::init(int MaxNumberOfObjects, int SizeOfEachObjectExact, binaryTreeCompare LessThan)
{
///////////////////////////////////////////////////////////////////////////////////////////////////////
  BinaryTree* tree = 0;

  char* Memory = 0;

  int MemoryArrayPointerSize = 0;
  int MemoryPoolSize = 0;
  int MemoryTotalSize = 0;

  int SizeOfEachObjectAligned = 0;

  int loop = 0;
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
  if(MaxNumberOfObjects <= 0 || SizeOfEachObjectExact <= 0 || !LessThan)
  {
    // BinTreeInit(...) bad params
    _log("error");
    return 0;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
  // Align the client memory (sizeof(void*) byte alignment, also known as granularity alignment)
  SizeOfEachObjectAligned = SizeOfEachObjectExact;

  if(SizeOfEachObjectAligned % sizeof(void*) )
    SizeOfEachObjectAligned += sizeof(void*) - (SizeOfEachObjectAligned % sizeof(void*) );

  // We need the pointer pools for the traversing stack and for the memory manager stack.
  MemoryArrayPointerSize = sizeof(char*) * MaxNumberOfObjects;

  // We need the nodel pool for the memory manager, with the size of the nodes
  // expanded to include the granularity aligned client object sizes.
  MemoryPoolSize = (SizeOfEachObjectAligned + sizeof(BinaryTreeNode) ) * MaxNumberOfObjects;
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
  // Need enough memory for the head
  MemoryTotalSize = sizeof(BinaryTree);

  // Need two pointer pools, one for the memory manager, and another pool for the traversing stack;
  MemoryTotalSize += MemoryArrayPointerSize * 2;

  // Add the actual node pool to the total required allocation size.
  MemoryTotalSize += MemoryPoolSize;

  // Make sure the memory allocation is a multiple of sizeof(void*) for quicker zero-ing of the
  // memory in the BinTreeTerm(...) function (a couple microseconds faster).
  if(MemoryTotalSize % sizeof(void*) )
    MemoryTotalSize += sizeof(void*) - (MemoryTotalSize % sizeof(void*) );
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
  // Actually allocate the memory we need
  tree = (BinaryTree*)malloc(MemoryTotalSize);

  if( !tree)
  {
    // BinTreeInit(...) bad memory allocation
    _log("error");
    return 0;
  }

  memset(tree, 0, MemoryTotalSize);
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
  Memory = (char*)tree;

  Memory += sizeof(BinaryTree);

  tree->TraverseArrayStart = (BinaryTreeNode**)Memory;

  Memory += MemoryArrayPointerSize;

  tree->MemoryManagerArrayCurrent = (char**)Memory;

  Memory += MemoryArrayPointerSize;

  for(loop = 0; loop < MaxNumberOfObjects; loop++)
  {
    tree->MemoryManagerArrayCurrent[loop] = Memory;

    Memory += SizeOfEachObjectAligned + sizeof(BinaryTreeNode);
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
  tree->LessThan = LessThan;

  tree->MaxNumberOfNodes = MaxNumberOfObjects;

  tree->SizeOfClientExact = SizeOfEachObjectExact;
  tree->SizeOfClientAligned = SizeOfEachObjectAligned;

  tree->MemoryTotalSize = MemoryTotalSize;
///////////////////////////////////////////////////////////////////////////////////////////////////////

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
