
// File Name: binright.cpp
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
void RightRotateDelete1(BinaryTreeNode* xP)
{
  BinaryTreeNode* xPL = xP->left;

  // 1 of 6
  xP->left = xPL->right;

  // 2 of 6
  if(xPL->right)
    xPL->right->parent = xP, gDebugRotate[20]++;
  else
    gDebugRotate[21]++; // never reached through empirical testing

  // 3 of 6
  xPL->parent = xP->parent;

  // 4 of 6
  if(xP == xP->parent->right)
    xP->parent->right = xPL, gDebugRotate[54]++;
  else /* xP == xP->parent->left */
    xP->parent->left = xPL, gDebugRotate[55]++;

  // 5 of 6
  xPL->right = xP;

  // 6 of 6
  xP->parent = xPL;
}

// integrated for root sentinel
void RightRotateDelete2(BinaryTreeNode* xP)
{
  BinaryTreeNode* xPL = xP->left;

  // 1 of 6
  xP->left = xPL->right;

  // 2 of 6
  if(xPL->right)
    xPL->right->parent = xP, gDebugRotate[22]++;
  else
    gDebugRotate[23]++;

  // 3 of 6
  xPL->parent = xP->parent;

  // 4 of 6
  if(xP == xP->parent->right)
    xP->parent->right = xPL, gDebugRotate[56]++;
  else /* xP == xP->parent->left */
    xP->parent->left = xPL, gDebugRotate[57]++;

  // 5 of 6
  xPL->right = xP;

  // 6 of 6
  xP->parent = xPL;
}

// integrated for root sentinel
void RightRotateInsert(BinaryTreeNode* xPP)
{
  BinaryTreeNode* xPPL = xPP->left;

  // 1 of 6
  xPP->left = xPPL->right;

  // 2 of 6
  if(xPPL->right)
    xPPL->right->parent = xPP, gDebugRotate[24]++;
  else
    gDebugRotate[25]++;

  // 3 of 6
  xPPL->parent = xPP->parent;

  // 4 of 6
  if(xPP == xPP->parent->right)
    xPP->parent->right = xPPL, gDebugRotate[58]++;
  else /* xPP == xPP->parent->left */
    xPP->parent->left = xPPL, gDebugRotate[59]++;

  // 5 of 6
  xPPL->right = xPP;

  // 6 of 6
  xPP->parent = xPPL;
}
