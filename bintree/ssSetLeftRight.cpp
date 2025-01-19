
// ssSetLeftRight.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void SsSetRotateLeftRightInsertLevel3(ssSet* _this, SsSetNode* x)
{
  SsSetNode* xP = x->parent;
  SsSetNode* xPP = xP->parent;

  if(x->left)
    x->left->parent = xP, _this->debug[8] ++;
  else
    _this->debug[9] ++;

  xP->right = x->left;

  if(x->right)
    x->right->parent = xPP, _this->debug[10] ++;
  else
    _this->debug[11] ++;

  xPP->left = x->right;

  if(xPP == xPP->parent->right)
    xPP->parent->right = x, _this->debug[48] ++;
  else
    xPP->parent->left = x, _this->debug[49] ++;

  x->left = xP;

  x->right = xPP;

  x->parent = xPP->parent;

  xP->parent = x;

  xPP->parent = x;
}

// integrated for root sentinel
void SsSetRotateLeftRightEraseLevel4(ssSet* _this, SsSetNode* xP)
{
  SsSetNode* xPL = xP->left;
  SsSetNode* xPLR = xPL->right;

  if(xPLR->right)
    xPLR->right->parent = xP, _this->debug[12] ++;
  else
    _this->debug[13] ++;

  xP->left = xPLR->right;

  if(xPLR->left)
    xPLR->left->parent = xPL, _this->debug[14] ++;
  else
    _this->debug[15] ++;

  xPL->right = xPLR->left;

  xPL->parent = xPLR;

  xPLR->left = xPL;

  if(xP == xP->parent->right)
    xP->parent->right = xPLR, _this->debug[50] ++;
  else
    xP->parent->left = xPLR, _this->debug[51] ++;

  xPLR->parent = xP->parent;

  xP->parent = xPLR;

  xPLR->right = xP;
}
