
// ssSetRightLeft.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void SsSetRotateRightLeftInsertLevel3(SsSetNode* x)
{
  SsSetNode* xP = x->parent;
  SsSetNode* xPP = xP->parent;

  if(x->right)
    x->right->parent = xP, gSsSetDebug[28]++;
  else
    gSsSetDebug[29]++;

  xP->left = x->right;

  if(x->left)
    x->left->parent = xPP, gSsSetDebug[30]++;
  else
    gSsSetDebug[31]++;

  xPP->right = x->left;

  if(xPP == xPP->parent->left)
    xPP->parent->left = x, gSsSetDebug[62]++;
  else
    xPP->parent->right = x, gSsSetDebug[63]++;

  x->right = xP;

  x->left = xPP;

  x->parent = xPP->parent;

  xP->parent = x;

  xPP->parent = x;
}

// integrated for root sentinel
void SsSetRotateRightLeftEraseLevel4(SsSetNode* xP)
{
  SsSetNode* xPR = xP->right;
  SsSetNode* xPRL = xPR->left;

  if(xPRL->left)
    xPRL->left->parent = xP, gSsSetDebug[32]++;
  else
    gSsSetDebug[33]++;

  xP->right = xPRL->left;

  if(xPRL->right)
    xPRL->right->parent = xPR, gSsSetDebug[34]++;
  else
    gSsSetDebug[35]++;

  xPR->left = xPRL->right;

  xPR->parent = xPRL;

  xPRL->right = xPR;

  if(xP == xP->parent->left)
    xP->parent->left = xPRL, gSsSetDebug[64]++;
  else
    xP->parent->right = xPRL, gSsSetDebug[65]++;

  xPRL->parent = xP->parent;

  xP->parent = xPRL;

  xPRL->left = xP;
}
