
// ssSet_right.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void SsSetRotateRightErase1Level4(SsSetNode* xP)
{
  SsSetNode* xPL = xP->left;

  xP->left = xPL->right;

  if(xPL->right)
    xPL->right->parent = xP, gSsSetDebug[20]++;
  else
    gSsSetDebug[21]++; // never reached through empirical testing

  xPL->parent = xP->parent;

  if(xP == xP->parent->right)
    xP->parent->right = xPL, gSsSetDebug[54]++;
  else
    xP->parent->left = xPL, gSsSetDebug[55]++;

  xPL->right = xP;

  xP->parent = xPL;
}

// integrated for root sentinel
void SsSetRotateRightErase2Level4(SsSetNode* xP)
{
  SsSetNode* xPL = xP->left;

  xP->left = xPL->right;

  if(xPL->right)
    xPL->right->parent = xP, gSsSetDebug[22]++;
  else
    gSsSetDebug[23]++;

  xPL->parent = xP->parent;

  if(xP == xP->parent->right)
    xP->parent->right = xPL, gSsSetDebug[56]++;
  else
    xP->parent->left = xPL, gSsSetDebug[57]++;

  xPL->right = xP;

  xP->parent = xPL;
}

// integrated for root sentinel
void SsSetRotateRightInsertLevel3(SsSetNode* xPP)
{
  SsSetNode* xPPL = xPP->left;

  xPP->left = xPPL->right;

  if(xPPL->right)
    xPPL->right->parent = xPP, gSsSetDebug[24]++;
  else
    gSsSetDebug[25]++;

  xPPL->parent = xPP->parent;

  if(xPP == xPP->parent->right)
    xPP->parent->right = xPPL, gSsSetDebug[58]++;
  else
    xPP->parent->left = xPPL, gSsSetDebug[59]++;

  xPPL->right = xPP;

  xPP->parent = xPPL;
}
