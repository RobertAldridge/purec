
// File Name: binright.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

#if 0
// RightRotate(xP)
// RightRotate(xPP)
static void RightRotate(BinaryTreeNode* x);

// RightRightRotate(xP)
static void RightRightRotate(BinaryTreeNode* xP);

// RightLeftInsertRotate(x)
static void RightLeftInsertRotate(BinaryTreeNode* x);

// RightLeftDeleteRotate(xP)
static void RightLeftDeleteRotate(BinaryTreeNode* xP);

// RightLeftRightRotate(xP)
static void RightLeftRightRotate(BinaryTreeNode* xP);
#endif

// x
// xL = x->left

// x 0 2 4 5
// x->left xL 0 1 4 4 6
// x->left->right 1 2 5
// x->left->right->parent 2
// x->left->parent 3
// x->parent 3 6
// x->parent->left 4
// x->parent->right 4 4
// 
// integrated for root sentinel
void RightRotate(BinaryTreeNode* x)
{
  BinaryTreeNode* xL = x->left;

  // 1 of 6
  x->left = xL->right;

  // 2 of 6
  if(xL->right)
    xL->right->parent = x;

  // 3 of 6
  xL->parent = x->parent;

  // 4 of 6
  if(x == x->parent->right)
    x->parent->right = xL;
  else /* x == x->parent->left */
    x->parent->left = xL;

  // 5 of 6
  xL->right = x;

  // 6 of 6
  x->parent = xL;
}
