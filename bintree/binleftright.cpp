
// File Name: binleftright.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

#if 0
// LeftRotate(xP)
// LeftRotate(xPP)
static void LeftRotate(BinaryTreeNode* x);

// LeftLeftRotate(xP)
static void LeftLeftRotate(BinaryTreeNode* xP);

// LeftRightInsertRotate(x)
static void LeftRightInsertRotate(BinaryTreeNode* x);

// LeftRightDeleteRotate(xP)
static void LeftRightDeleteRotate(BinaryTreeNode* xP);

// LeftRightLeftRotate(xP)
static void LeftRightLeftRotate(BinaryTreeNode* xP);
#endif

// integrated for root sentinel
void LeftRightInsertRotate(BinaryTreeNode* x)
{
  BinaryTreeNode* xP = x->parent;
  BinaryTreeNode* xPP = xP->parent;

  // 1 of 10
  if(x->left)
    x->left->parent = xP;

  // 2 of 10
  xP->right = x->left;

  // 3 of 10
  if(x->right)
    x->right->parent = xPP;

  // 4 of 10
  xPP->left = x->right;

  // 5 of 10
  if(xPP == xPP->parent->right)
    xPP->parent->right = x;
  else /* xPP == xPP->parent->left */
    xPP->parent->left = x;

  // 6 of 10
  x->left = xP;

  // 7 of 10
  x->right = xPP;

  // 8 of 10
  x->parent = xPP->parent;

  // 9 of 10
  xP->parent = x;

  // 10 of 10
  xPP->parent = x;
}

// integrated for root sentinel
void LeftRightDeleteRotate(BinaryTreeNode* xP)
{
  BinaryTreeNode* xPL = xP->left;
  BinaryTreeNode* xPLR = xPL->right;

  // 1 of 10
  if(xPLR->right)
    xPLR->right->parent = xP;

  // 2 of 10
  xP->left = xPLR->right;

  // 3 of 10
  if(xPLR->left)
    xPLR->left->parent = xPL;

  // 4 of 10
  xPL->right = xPLR->left;

  // 5 of 10
  xPL->parent = xPLR;

  // 6 of 10
  xPLR->left = xPL;

  // 7 of 10
  if(xP == xP->parent->right)
    xP->parent->right = xPLR;
  else /* xP == xP->parent->left */
    xP->parent->left = xPLR;

  // 8 of 10
  xPLR->parent = xP->parent;

  // 9 of 10
  xP->parent = xPLR;

  // 10 of 10
  xPLR->right = xP;
}
