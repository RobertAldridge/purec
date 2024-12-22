
// File Name: binleftleft.cpp
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
void LeftLeftRotate(BinaryTreeNode* xP)
{
  BinaryTreeNode* xPR = xP->right;
  BinaryTreeNode* xPRL = xPR->left;

  // 1 of 6
  if(xPRL->left)
    xPRL->left->parent = xP;

  // 2 of 6
  xP->right = xPRL->left;

  // 3 of 6
  if(xP == xP->parent->left)
    xP->parent->left = xPR;
  else /* xP == xP->parent->right */
    xP->parent->right = xPR;

  // 4 of 6
  xPR->parent = xP->parent;

  // 5 of 6
  xP->parent = xPRL;

  // 6 of 6
  xPRL->left = xP;
}
