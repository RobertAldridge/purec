
// ssSet_rightleftright.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void SsSetRotateRightLeftRightEraseLevel4(SsSetNode* xP)
{
  SsSetNode* xPL = xP->left;
  SsSetNode* xPLR = xPL->right;
  SsSetNode* xPLRR = xPLR->right;

  xP->left = xPLRR->right;

  if(xPLRR->right)
    xPLRR->right->parent = xP, gSsSetDebug[36]++;
  else
    gSsSetDebug[37]++;

  xPLR->right = xPLRR->left;

  if(xPLRR->left)
    xPLRR->left->parent = xPLR, gSsSetDebug[38]++;
  else
    gSsSetDebug[39]++;

  xPLR->parent = xPLRR;

  xPLRR->left = xPLR;

  if(xP == xP->parent->right)
    xP->parent->right = xPL, gSsSetDebug[66]++;
  else
    xP->parent->left = xPL, gSsSetDebug[67]++;

  xPL->parent = xP->parent;

  xP->parent = xPLRR;

  xPLRR->right = xP;

  xPL->right = xPLRR;

  xPLRR->parent = xPL;
}
