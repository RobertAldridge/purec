
// ssSetRight.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void SsSetRotateRightErase1Level4(ssSet* _this, SsSetNode* xP)
{
  SsSetNode* xPL = xP->left;

  xP->left = xPL->right;

  if(xPL->right)
    xPL->right->parent = xP, _this->debug[20] ++;
  else
    _this->debug[21] ++; // never reached through empirical testing

  xPL->parent = xP->parent;

  if(xP == xP->parent->right)
    xP->parent->right = xPL, _this->debug[54] ++;
  else
    xP->parent->left = xPL, _this->debug[55] ++;

  xPL->right = xP;

  xP->parent = xPL;
}

// integrated for root sentinel
void SsSetRotateRightErase2Level4(ssSet* _this, SsSetNode* xP)
{
  SsSetNode* xPL = xP->left;

  xP->left = xPL->right;

  if(xPL->right)
    xPL->right->parent = xP, _this->debug[22] ++;
  else
    _this->debug[23] ++;

  xPL->parent = xP->parent;

  if(xP == xP->parent->right)
    xP->parent->right = xPL, _this->debug[56] ++;
  else
    xP->parent->left = xPL, _this->debug[57] ++;

  xPL->right = xP;

  xP->parent = xPL;
}

// integrated for root sentinel
void SsSetRotateRightInsertLevel3(ssSet* _this, SsSetNode* xPP)
{
  SsSetNode* xPPL = xPP->left;

  xPP->left = xPPL->right;

  if(xPPL->right)
    xPPL->right->parent = xPP, _this->debug[24] ++;
  else
    _this->debug[25] ++;

  xPPL->parent = xPP->parent;

  if(xPP == xPP->parent->right)
    xPP->parent->right = xPPL, _this->debug[58] ++;
  else
    xPP->parent->left = xPPL, _this->debug[59] ++;

  xPPL->right = xPP;

  xPP->parent = xPPL;
}
