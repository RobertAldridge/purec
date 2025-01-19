
// ssSetLeft.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void SsSetRotateLeftErase1Level4(ssSet* _this, SsSetNode* xP)
{
  SsSetNode* xPR = xP->right;

  xP->right = xPR->left;

  if(xPR->left)
    xPR->left->parent = xP, _this->debug[0] ++;
  else
    _this->debug[1] ++; // never reached through empirical testing

  xPR->parent = xP->parent;

  if(xP == xP->parent->left)
    xP->parent->left = xPR, _this->debug[40] ++;
  else
    xP->parent->right = xPR, _this->debug[41] ++;

  xPR->left = xP;

  xP->parent = xPR;
}

// integrated for root sentinel
void SsSetRotateLeftErase2Level4(ssSet* _this, SsSetNode* xP)
{
  SsSetNode* xPR = xP->right;

  xP->right = xPR->left;

  if(xPR->left)
    xPR->left->parent = xP, _this->debug[2] ++;
  else
    _this->debug[3] ++;

  xPR->parent = xP->parent;

  if(xP == xP->parent->left)
    xP->parent->left = xPR, _this->debug[42] ++;
  else
    xP->parent->right = xPR, _this->debug[43] ++;

  xPR->left = xP;

  xP->parent = xPR;
}

// integrated for root sentinel
void SsSetRotateLeftInsertLevel3(ssSet* _this, SsSetNode* xPP)
{
  SsSetNode* xPPR = xPP->right;

  xPP->right = xPPR->left;

  if(xPPR->left)
    xPPR->left->parent = xPP, _this->debug[4] ++;
  else
    _this->debug[5] ++;

  xPPR->parent = xPP->parent;

  if(xPP == xPP->parent->left)
    xPP->parent->left = xPPR, _this->debug[44] ++;
  else
    xPP->parent->right = xPPR, _this->debug[45] ++;

  xPPR->left = xPP;

  xPP->parent = xPPR;
}
