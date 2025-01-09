
// File Name: binleftleft.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void LeftLeftRotate(SsSetNode* xP)
{
  SsSetNode* xPR = xP->right;
  SsSetNode* xPRL = xPR->left;

  if(xPRL->left)
    xPRL->left->parent = xP, gDebugRotate[6]++;
  else
    gDebugRotate[7]++;

  xP->right = xPRL->left;

  if(xP == xP->parent->left)
    xP->parent->left = xPR, gDebugRotate[46]++;
  else
    xP->parent->right = xPR, gDebugRotate[47]++;

  xPR->parent = xP->parent;

  xP->parent = xPRL;

  xPRL->left = xP;
}
