
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

  uint32_t color;
  uint32_t padding;
};

struct BinaryTree
{
  BinaryTreeNode sentinelRoot;

  BinaryTreeNode sentinelLeaf;

  binaryTreeCompare lessThan;

  binaryTreeEquivalence equalTo;

  binaryTreeEvaluate clientEvaluate;

  // main allocator for BinaryTree nodes
  ssmm* allocator;

  // for interative pre-order, in-order, post-order traversal
  ssStack* stack;
  ssQueue* queue;

  uint32_t maxStack;
  uint32_t maxQueue;

  uint32_t numberOfNodes;

  uint32_t sizeOfClient;
};
