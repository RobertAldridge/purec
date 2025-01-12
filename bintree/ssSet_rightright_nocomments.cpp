
// ssSet_rightright.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void SsSetRotateRightRightErase(SsSetNode* xP)
{
  SsSetNode* xPL = xP->left;
  SsSetNode* xPLR = xPL->right;

  if(xPLR->right)
    xPLR->right->parent = xP, gSsSetDebug[26]++;
  else
    gSsSetDebug[27]++;

  xP->left = xPLR->right;

  if(xP == xP->parent->right)
    xP->parent->right = xPL, gSsSetDebug[60]++;
  else
    xP->parent->left = xPL, gSsSetDebug[61]++;

  xPL->parent = xP->parent;

  xP->parent = xPLR;

  xPLR->right = xP;
}
