
// ssSet_rightleft.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void RightLeftRotateInsert(SsSetNode* x)
{
  SsSetNode* xP = x->parent;
  SsSetNode* xPP = xP->parent;

  if(x->right)
    x->right->parent = xP, gDebugRotate[28]++;
  else
    gDebugRotate[29]++;

  xP->left = x->right;

  if(x->left)
    x->left->parent = xPP, gDebugRotate[30]++;
  else
    gDebugRotate[31]++;

  xPP->right = x->left;

  if(xPP == xPP->parent->left)
    xPP->parent->left = x, gDebugRotate[62]++;
  else
    xPP->parent->right = x, gDebugRotate[63]++;

  x->right = xP;

  x->left = xPP;

  x->parent = xPP->parent;

  xP->parent = x;

  xPP->parent = x;
}

// integrated for root sentinel
void RightLeftRotateDelete(SsSetNode* xP)
{
  SsSetNode* xPR = xP->right;
  SsSetNode* xPRL = xPR->left;

  if(xPRL->left)
    xPRL->left->parent = xP, gDebugRotate[32]++;
  else
    gDebugRotate[33]++;

  xP->right = xPRL->left;

  if(xPRL->right)
    xPRL->right->parent = xPR, gDebugRotate[34]++;
  else
    gDebugRotate[35]++;

  xPR->left = xPRL->right;

  xPR->parent = xPRL;

  xPRL->right = xPR;

  if(xP == xP->parent->left)
    xP->parent->left = xPRL, gDebugRotate[64]++;
  else
    xP->parent->right = xPRL, gDebugRotate[65]++;

  xPRL->parent = xP->parent;

  xP->parent = xPRL;

  xPRL->left = xP;
}
