
// File Name: binrightleftright.cpp
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
void RightLeftRightRotate(BinaryTreeNode* xP)
{
  BinaryTreeNode* xPL = xP->left;
  BinaryTreeNode* xPLR = xPL->right;
  BinaryTreeNode* xPLRR = xPLR->right;

  // 1 of 12
  xP->left = xPLRR->right;

  // 2 of 12
  if(xPLRR->right)
    xPLRR->right->parent = xP, gDebugRotate[36]++;
  else
    gDebugRotate[37]++;

  // 3 of 12
  xPLR->right = xPLRR->left;

  // 4 of 12
  if(xPLRR->left)
    xPLRR->left->parent = xPLR, gDebugRotate[38]++;
  else
    gDebugRotate[39]++;

  // 5 of 12
  xPLR->parent = xPLRR;

  // 6 of 12
  xPLRR->left = xPLR;

  // 7 of 12
  if(xP == xP->parent->right)
    xP->parent->right = xPL, gDebugRotate[66]++;
  else /* xP == xP->parent->left */
    xP->parent->left = xPL, gDebugRotate[67]++;

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
