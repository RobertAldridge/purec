
// File Name: binrightleftright.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void RightLeftRightRotate(BinaryTreeNode* xP)
{
  BinaryTreeNode* xPL = xP->left;
  BinaryTreeNode* xPLR = xPL->right;
  BinaryTreeNode* xPLRR = xPLR->right;

  xP->left = xPLRR->right;

  if(xPLRR->right)
    xPLRR->right->parent = xP, gDebugRotate[36]++;
  else
    gDebugRotate[37]++;

  xPLR->right = xPLRR->left;

  if(xPLRR->left)
    xPLRR->left->parent = xPLR, gDebugRotate[38]++;
  else
    gDebugRotate[39]++;

  xPLR->parent = xPLRR;

  xPLRR->left = xPLR;

  if(xP == xP->parent->right)
    xP->parent->right = xPL, gDebugRotate[66]++;
  else
    xP->parent->left = xPL, gDebugRotate[67]++;

  xPL->parent = xP->parent;

  xP->parent = xPLRR;

  xPLRR->right = xP;

  xPL->right = xPLRR;

  xPLRR->parent = xPL;
}
