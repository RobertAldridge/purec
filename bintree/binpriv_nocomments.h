
// File Name: binpriv.h

struct BinaryTreeNode;
struct BinaryTree;

typedef int(*binaryTreeCompare)(void* keyObject, void* treeObject);

typedef int(*binaryTreeEvaluate)(void* treeObject);

typedef int(*binaryTreeEquivalence)(void* keyObject, void* treeObject);

struct BinaryTreeNode
{
  BinaryTreeNode* left;
  BinaryTreeNode* right;
  BinaryTreeNode* parent;

  int32_t color;
  int32_t padding;
};

struct BinaryTree
{
  BinaryTreeNode sentinelRoot;

  BinaryTreeNode sentinelLeaf;

  binaryTreeCompare LessThan;

  binaryTreeEquivalence EqualTo;

  binaryTreeEvaluate ClientEvaluate;
  
  // main allocator for BinaryTree nodes
  ssmm* allocator;

  // for interative pre-order, in-order, post-order traversal
  ssStack* stack;
  ssQueue* queue;

  int32_t NumberOfNodes;

  int32_t SizeOfClientAligned;

  int32_t SizeOfClientExact;

  int32_t padding;
};
