
// File Name: binleftright.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void LeftRightRotateInsert(SsSetNode* x)
{
  SsSetNode* xP = x->parent;
  SsSetNode* xPP = xP->parent;

  if(x->left)
    x->left->parent = xP, gDebugRotate[8]++;
  else
    gDebugRotate[9]++;

  xP->right = x->left;

  if(x->right)
    x->right->parent = xPP, gDebugRotate[10]++;
  else
    gDebugRotate[11]++;

  xPP->left = x->right;

  if(xPP == xPP->parent->right)
    xPP->parent->right = x, gDebugRotate[48]++;
  else
    xPP->parent->left = x, gDebugRotate[49]++;

  x->left = xP;

  x->right = xPP;

  x->parent = xPP->parent;

  xP->parent = x;

  xPP->parent = x;
}

// integrated for root sentinel
void LeftRightRotateDelete(SsSetNode* xP)
{
  SsSetNode* xPL = xP->left;
  SsSetNode* xPLR = xPL->right;

  if(xPLR->right)
    xPLR->right->parent = xP, gDebugRotate[12]++;
  else
    gDebugRotate[13]++;

  xP->left = xPLR->right;

  if(xPLR->left)
    xPLR->left->parent = xPL, gDebugRotate[14]++;
  else
    gDebugRotate[15]++;

  xPL->right = xPLR->left;

  xPL->parent = xPLR;

  xPLR->left = xPL;

  if(xP == xP->parent->right)
    xP->parent->right = xPLR, gDebugRotate[50]++;
  else
    xP->parent->left = xPLR, gDebugRotate[51]++;

  xPLR->parent = xP->parent;

  xP->parent = xPLR;

  xPLR->right = xP;
}
