
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

  binaryTreeCompare lessThan;

  binaryTreeEquivalence equalTo;

  binaryTreeEvaluate clientEvaluate;

  uint8_t* unaligned;

  // main allocator for BinaryTree nodes
  ssmm* allocator;

  // for interative pre-order, in-order, post-order traversal
  ssStack* stack;
  ssQueue* queue;

  int32_t maxStack;
  int32_t maxQueue;

  int32_t numberOfNodes;

  int32_t sizeOfClient;
};
