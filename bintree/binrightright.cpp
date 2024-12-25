
// File Name: binrightright.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

#if 0
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
#endif

// integrated for root sentinel
void RightRightRotate(BinaryTreeNode* xP)
{
  BinaryTreeNode* xPL = xP->left;
  BinaryTreeNode* xPLR = xPL->right;

  // 1 of 6
  if(xPLR->right)
    xPLR->right->parent = xP, gDebugRotate[26]++;
  else
    gDebugRotate[27]++;

  // 2 of 6
  xP->left = xPLR->right;

  // 3 of 6
  if(xP == xP->parent->right)
    xP->parent->right = xPL, gDebugRotate[60]++;
  else /* xP == xP->parent->left */
    xP->parent->left = xPL, gDebugRotate[61]++;

  // 4 of 6
  xPL->parent = xP->parent;

  // 5 of 6
  xP->parent = xPLR;

  // 6 of 6
  xPLR->right = xP;
}
