
// File Name: binrightleft.cpp
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
void RightLeftInsertRotate(BinaryTreeNode* x)
{
  BinaryTreeNode* xP = x->parent;
  BinaryTreeNode* xPP = xP->parent;

  // 1 of 10
  if(x->right)
    x->right->parent = xP;

  // 2 of 10
  xP->left = x->right;

  // 3 of 10
  if(x->left)
    x->left->parent = xPP;

  // 4 of 10
  xPP->right = x->left;

  // 5 of 10
  if(xPP == xPP->parent->left)
    xPP->parent->left = x;
  else /* xPP == xPP->parent->right */
    xPP->parent->right = x;

  // 6 of 10
  x->right = xP;

  // 7 of 10
  x->left = xPP;

  // 8 of 10
  x->parent = xPP->parent;

  // 9 of 10
  xP->parent = x;

  // 10 of 10
  xPP->parent = x;
}

// integrated for root sentinel
void RightLeftDeleteRotate(BinaryTreeNode* xP)
{
  BinaryTreeNode* xPR = xP->right;
  BinaryTreeNode* xPRL = xPR->left;

  // 1 of 10
  if(xPRL->left)
    xPRL->left->parent = xP;

  // 2 of 10
  xP->right = xPRL->left;

  // 3 of 10
  if(xPRL->right)
    xPRL->right->parent = xPR;

  // 4 of 10
  xPR->left = xPRL->right;

  // 5 of 10
  xPR->parent = xPRL;

  // 6 of 10
  xPRL->right = xPR;

  // 7 of 10
  if(xP == xP->parent->left)
    xP->parent->left = xPRL;
  else /* xP == xP->parent->right */
    xP->parent->right = xPRL;

  // 8 of 10
  xPRL->parent = xP->parent;

  // 9 of 10
  xP->parent = xPRL;

  // 10 of 10
  xPRL->left = xP;
}