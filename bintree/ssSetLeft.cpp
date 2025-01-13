
// ssSet_left.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void SsSetRotateLeftErase1Level4(SsSetNode* xP)
{
  SsSetNode* xPR = xP->right;

  xP->right = xPR->left;

  if(xPR->left)
    xPR->left->parent = xP, gSsSetDebug[0]++;
  else
    gSsSetDebug[1]++; // never reached through empirical testing

  xPR->parent = xP->parent;

  if(xP == xP->parent->left)
    xP->parent->left = xPR, gSsSetDebug[40]++;
  else
    xP->parent->right = xPR, gSsSetDebug[41]++;

  xPR->left = xP;

  xP->parent = xPR;
}

// integrated for root sentinel
void SsSetRotateLeftErase2Level4(SsSetNode* xP)
{
  SsSetNode* xPR = xP->right;

  xP->right = xPR->left;

  if(xPR->left)
    xPR->left->parent = xP, gSsSetDebug[2]++;
  else
    gSsSetDebug[3]++;

  xPR->parent = xP->parent;

  if(xP == xP->parent->left)
    xP->parent->left = xPR, gSsSetDebug[42]++;
  else
    xP->parent->right = xPR, gSsSetDebug[43]++;

  xPR->left = xP;

  xP->parent = xPR;
}

// integrated for root sentinel
void SsSetRotateLeftInsertLevel3(SsSetNode* xPP)
{
  SsSetNode* xPPR = xPP->right;

  xPP->right = xPPR->left;

  if(xPPR->left)
    xPPR->left->parent = xPP, gSsSetDebug[4]++;
  else
    gSsSetDebug[5]++;

  xPPR->parent = xPP->parent;

  if(xPP == xPP->parent->left)
    xPP->parent->left = xPPR, gSsSetDebug[44]++;
  else
    xPP->parent->right = xPPR, gSsSetDebug[45]++;

  xPPR->left = xPP;

  xPP->parent = xPPR;
}
