
// ssSet_leftrightleft.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void SsSetRotateLeftRightLeftEraseLevel4(SsSetNode* xP)
{
  SsSetNode* xPR = xP->right;
  SsSetNode* xPRL = xPR->left;
  SsSetNode* xPRLL = xPRL->left;

  xP->right = xPRLL->left;

  if(xPRLL->left)
    xPRLL->left->parent = xP, gSsSetDebug[16]++;
  else
    gSsSetDebug[17]++;

  xPRL->left = xPRLL->right;

  if(xPRLL->right)
    xPRLL->right->parent = xPRL, gSsSetDebug[18]++;
  else
    gSsSetDebug[19]++;

  xPRL->parent = xPRLL;

  xPRLL->right = xPRL;

  if(xP == xP->parent->left)
    xP->parent->left = xPR, gSsSetDebug[52]++;
  else
    xP->parent->right = xPR, gSsSetDebug[53]++;

  xPR->parent = xP->parent;

  xP->parent = xPRLL;

  xPRLL->left = xP;

  xPR->left = xPRLL;

  xPRLL->parent = xPR;
}
