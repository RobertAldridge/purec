
// file name binpriv.h

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

  SsSetCompare lessThan;

  //SsSetEquivalence equalTo;

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
};
