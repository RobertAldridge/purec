
// File Name: binpriv.h

struct BinaryTreeNode;
struct BinaryTree;

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
  int padding;

  // minimum client size
  // uint8_t client[8];
  //
  // minimum node size for 8 byte pointer and 4 byte int
  // 40 bytes
  //
  // number of minimum size nodes to fit into 1 gigabyte of memory
  // not counting head, traversal stack, traversal queue, or client-side copy of client objects
  // 26,843,545
  //
  // number of minimum size nodes to fit into 4 gigabytes of memory
  // not counting head, traversal stack, traversal queue, or client-side copy of client objects
  // 107,374,182
  //
  // rough memory requirement for traversal stack, traversal queue, and client-side copy of client objects
  // when number of client objects is 107,374,182
  //
  // traversal stack 216 bytes
  // traversal queue 343,597,383 bytes
  // client-side copy of client objects 858,993,456 bytes
  //
  // total 1,202,591,055 bytes == ~1.13 gigabytes
  //
  // total with tree nodes == ~5.13 gigabytes
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

  ssmm* nodeAllocator; // main allocator for bintree nodes

  ssmm* stackAllocator; // pointer stack for interative pre-order, in-order, post-order traversal

  ////////////////////////////////////
//char** MemoryManagerArrayCurrent;
//char MemoryManagerNodePoolArrayStart[];
  ////////////////////////////////////
};
