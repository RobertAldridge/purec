
// File Name: binpriv.h

//#if !defined(BINPRIV)
//#define BINPRIV

//#ifdef __cplusplus
//  extern "C" {
//#endif

struct BinaryTreeNode;
struct BinaryTree;

#if defined(_MSC_VER)
  #pragma warning (disable: 4200)
//  #pragma warning (disable: 4201)
#endif

// This is a function pointer used to compare the keys of two objects.
// If you call a function and pass a compare function and an object to
// check against, the object you pass will be on the left hand side.
//
// The role of the compare function cannot change for the same list unless it is
// reset, otherwise the list will lose its sorted state.
//
// return zero if object 1 >= object 2
// return non-zero if object 1 < object 2
typedef int(*binaryTreeCompare)(void* keyObject, void* treeObject);

// This is a function pointer when traversing a tree in the dump function.
// Every object in a tree is visited in a particular order, this function pointer
// will be called and passed every object, unless the client terminates traversal
// early.
//
// return zero to continue traversal
// return non-zero to terminate traversal
typedef int(*binaryTreeEvaluate)(void* treeObject);

// This function checks if two objects are equal, and should be based on their keys.
// It is used in the find, remove, and other functions.  The left hand side is the
// object passed to the function.
//
// return zero if object 1 != object 2
// return non-zero if object 1 == object 2
typedef int(*binaryTreeEquivalence)(void* keyObject, void* treeObject);

struct BinaryTreeNode
{
  BinaryTreeNode* left;
  BinaryTreeNode* right;
  BinaryTreeNode* parent;

  int color;
};

struct BinaryTree
{
  BinaryTreeNode sentinelRoot;

  BinaryTreeNode sentinelLeaf;

  binaryTreeCompare LessThan;

  binaryTreeEquivalence EqualTo;

  binaryTreeEvaluate ClientEvaluate;

  int MaxNumberOfNodes;

  int NumberOfNodes;

  ////////////////////////////////////
  int SizeOfClientAligned;

  int SizeOfClientExact;

  int MemoryTotalSize;
  ////////////////////////////////////

  ////////////////////////////////////
  // buffer used to facilitate iterative traversal
  //
  // used as either stack or queue based on the order of traversal
  BinaryTreeNode** TraverseArrayStart;

  int maxStack;
  int maxQueue;
  ////////////////////////////////////

  ////////////////////////////////////
  char** MemoryManagerArrayCurrent;

  char MemoryManagerNodePoolArrayStart[];
  ////////////////////////////////////
};

#if defined(_MSC_VER)
//  #pragma warning (default: 4201)
  #pragma warning (default: 4200)
#endif

//#ifdef __cplusplus
//  }
//#endif

//#endif
