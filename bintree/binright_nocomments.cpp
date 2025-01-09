
// File Name: binright.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void RightRotateDelete1(SsSetNode* xP)
{
  SsSetNode* xPL = xP->left;

  xP->left = xPL->right;

  if(xPL->right)
    xPL->right->parent = xP, gDebugRotate[20]++;
  else
    gDebugRotate[21]++; // never reached through empirical testing

  xPL->parent = xP->parent;

  if(xP == xP->parent->right)
    xP->parent->right = xPL, gDebugRotate[54]++;
  else
    xP->parent->left = xPL, gDebugRotate[55]++;

  xPL->right = xP;

  xP->parent = xPL;
}

// integrated for root sentinel
void RightRotateDelete2(SsSetNode* xP)
{
  SsSetNode* xPL = xP->left;

  xP->left = xPL->right;

  if(xPL->right)
    xPL->right->parent = xP, gDebugRotate[22]++;
  else
    gDebugRotate[23]++;

  xPL->parent = xP->parent;

  if(xP == xP->parent->right)
    xP->parent->right = xPL, gDebugRotate[56]++;
  else
    xP->parent->left = xPL, gDebugRotate[57]++;

  xPL->right = xP;

  xP->parent = xPL;
}

// integrated for root sentinel
void RightRotateInsert(SsSetNode* xPP)
{
  SsSetNode* xPPL = xPP->left;

  xPP->left = xPPL->right;

  if(xPPL->right)
    xPPL->right->parent = xPP, gDebugRotate[24]++;
  else
    gDebugRotate[25]++;

  xPPL->parent = xPP->parent;

  if(xPP == xPP->parent->right)
    xPP->parent->right = xPPL, gDebugRotate[58]++;
  else
    xPP->parent->left = xPPL, gDebugRotate[59]++;

  xPPL->right = xPP;

  xPP->parent = xPPL;
}
