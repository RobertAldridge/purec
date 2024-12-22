
// File Name: binrightleftright.cpp
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
void RightLeftRightRotate(BinaryTreeNode* xP)
{
  BinaryTreeNode* xPL = xP->left;
  BinaryTreeNode* xPLR = xPL->right;
  BinaryTreeNode* xPLRR = xPLR->right;

  // 1 of 12
  xP->left = xPLRR->right;

  // 2 of 12
  if(xPLRR->right)
    xPLRR->right->parent = xP;

  // 3 of 12
  xPLR->right = xPLRR->left;

  // 4 of 12
  if(xPLRR->left)
    xPLRR->left->parent = xPLR;

  // 5 of 12
  xPLR->parent = xPLRR;

  // 6 of 12
  xPLRR->left = xPLR;

  // 7 of 12
  if(xP == xP->parent->right)
    xP->parent->right = xPL;
  else /* xP == xP->parent->left */
    xP->parent->left = xPL;

  // 8 of 12
  xPL->parent = xP->parent;

  // 9 of 12
  xP->parent = xPLRR;

  // 10 of 12
  xPLRR->right = xP;

  // 11 of 12
  xPL->right = xPLRR;

  // 12 of 12
  xPLRR->parent = xPL;
}
