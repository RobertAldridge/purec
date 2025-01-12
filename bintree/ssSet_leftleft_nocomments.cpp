
// ssSet_leftleft.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void SsSetRotateLeftLeftErase(SsSetNode* xP)
{
  SsSetNode* xPR = xP->right;
  SsSetNode* xPRL = xPR->left;

  if(xPRL->left)
    xPRL->left->parent = xP, gSsSetDebug[6]++;
  else
    gSsSetDebug[7]++;

  xP->right = xPRL->left;

  if(xP == xP->parent->left)
    xP->parent->left = xPR, gSsSetDebug[46]++;
  else
    xP->parent->right = xPR, gSsSetDebug[47]++;

  xPR->parent = xP->parent;

  xP->parent = xPRL;

  xPRL->left = xP;
}
