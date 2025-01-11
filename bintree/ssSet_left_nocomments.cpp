
// ssSet_left.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void LeftRotateDelete1(SsSetNode* xP)
{
  SsSetNode* xPR = xP->right;

  xP->right = xPR->left;

  if(xPR->left)
    xPR->left->parent = xP, gDebugRotate[0]++;
  else
    gDebugRotate[1]++; // never reached through empirical testing

  xPR->parent = xP->parent;

  if(xP == xP->parent->left)
    xP->parent->left = xPR, gDebugRotate[40]++;
  else
    xP->parent->right = xPR, gDebugRotate[41]++;

  xPR->left = xP;

  xP->parent = xPR;
}

// integrated for root sentinel
void LeftRotateDelete2(SsSetNode* xP)
{
  SsSetNode* xPR = xP->right;

  xP->right = xPR->left;

  if(xPR->left)
    xPR->left->parent = xP, gDebugRotate[2]++;
  else
    gDebugRotate[3]++;

  xPR->parent = xP->parent;

  if(xP == xP->parent->left)
    xP->parent->left = xPR, gDebugRotate[42]++;
  else
    xP->parent->right = xPR, gDebugRotate[43]++;

  xPR->left = xP;

  xP->parent = xPR;
}

// integrated for root sentinel
void LeftRotateInsert(SsSetNode* xPP)
{
  SsSetNode* xPPR = xPP->right;

  xPP->right = xPPR->left;

  if(xPPR->left)
    xPPR->left->parent = xPP, gDebugRotate[4]++;
  else
    gDebugRotate[5]++;

  xPPR->parent = xPP->parent;

  if(xPP == xPP->parent->left)
    xPP->parent->left = xPPR, gDebugRotate[44]++;
  else
    xPP->parent->right = xPPR, gDebugRotate[45]++;

  xPPR->left = xPP;

  xPP->parent = xPPR;
}
