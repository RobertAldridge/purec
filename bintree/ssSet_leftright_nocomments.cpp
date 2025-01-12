
// ssSet_leftright.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void SsSetRotateLeftRightInsert(SsSetNode* x)
{
  SsSetNode* xP = x->parent;
  SsSetNode* xPP = xP->parent;

  if(x->left)
    x->left->parent = xP, gSsSetDebug[8]++;
  else
    gSsSetDebug[9]++;

  xP->right = x->left;

  if(x->right)
    x->right->parent = xPP, gSsSetDebug[10]++;
  else
    gSsSetDebug[11]++;

  xPP->left = x->right;

  if(xPP == xPP->parent->right)
    xPP->parent->right = x, gSsSetDebug[48]++;
  else
    xPP->parent->left = x, gSsSetDebug[49]++;

  x->left = xP;

  x->right = xPP;

  x->parent = xPP->parent;

  xP->parent = x;

  xPP->parent = x;
}

// integrated for root sentinel
void SsSetRotateLeftRightErase(SsSetNode* xP)
{
  SsSetNode* xPL = xP->left;
  SsSetNode* xPLR = xPL->right;

  if(xPLR->right)
    xPLR->right->parent = xP, gSsSetDebug[12]++;
  else
    gSsSetDebug[13]++;

  xP->left = xPLR->right;

  if(xPLR->left)
    xPLR->left->parent = xPL, gSsSetDebug[14]++;
  else
    gSsSetDebug[15]++;

  xPL->right = xPLR->left;

  xPL->parent = xPLR;

  xPLR->left = xPL;

  if(xP == xP->parent->right)
    xP->parent->right = xPLR, gSsSetDebug[50]++;
  else
    xP->parent->left = xPLR, gSsSetDebug[51]++;

  xPLR->parent = xP->parent;

  xP->parent = xPLR;

  xPLR->right = xP;
}
