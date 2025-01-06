
// File Name: binrightright.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void RightRightRotate(BinaryTreeNode* xP)
{
  BinaryTreeNode* xPL = xP->left;
  BinaryTreeNode* xPLR = xPL->right;

  if(xPLR->right)
    xPLR->right->parent = xP, gDebugRotate[26]++;
  else
    gDebugRotate[27]++;

  xP->left = xPLR->right;

  if(xP == xP->parent->right)
    xP->parent->right = xPL, gDebugRotate[60]++;
  else
    xP->parent->left = xPL, gDebugRotate[61]++;

  xPL->parent = xP->parent;

  xP->parent = xPLR;

  xPLR->right = xP;
}
