
// File Name: binrightright.cpp
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

// integrated for root sentinel
void RightRightRotate(BinaryTreeNode* xP)
{
  BinaryTreeNode* xPL = xP->left;
  BinaryTreeNode* xPLR = xPL->right;

  // 1 of 6
  if(xPLR->right)
    xPLR->right->parent = xP;

  // 2 of 6
  xP->left = xPLR->right;

  // 3 of 6
  if(xP == xP->parent->right)
    xP->parent->right = xPL;
  else /* xP == xP->parent->left */
    xP->parent->left = xPL;

  // 4 of 6
  xPL->parent = xP->parent;

  // 5 of 6
  xP->parent = xPLR;

  // 6 of 6
  xPLR->right = xP;
}
