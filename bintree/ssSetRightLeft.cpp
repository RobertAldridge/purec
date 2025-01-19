
// ssSetRightLeft.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void SsSetRotateRightLeftInsertLevel3(ssSet* _this, SsSetNode* x)
{
  SsSetNode* xP = x->parent;
  SsSetNode* xPP = xP->parent;

  if(x->right)
    x->right->parent = xP, _this->debug[28]++;
  else
    _this->debug[29]++;

  xP->left = x->right;

  if(x->left)
    x->left->parent = xPP, _this->debug[30]++;
  else
    _this->debug[31]++;

  xPP->right = x->left;

  if(xPP == xPP->parent->left)
    xPP->parent->left = x, _this->debug[62]++;
  else
    xPP->parent->right = x, _this->debug[63]++;

  x->right = xP;

  x->left = xPP;

  x->parent = xPP->parent;

  xP->parent = x;

  xPP->parent = x;
}

// integrated for root sentinel
void SsSetRotateRightLeftEraseLevel4(ssSet* _this, SsSetNode* xP)
{
  SsSetNode* xPR = xP->right;
  SsSetNode* xPRL = xPR->left;

  if(xPRL->left)
    xPRL->left->parent = xP, _this->debug[32]++;
  else
    _this->debug[33]++;

  xP->right = xPRL->left;

  if(xPRL->right)
    xPRL->right->parent = xPR, _this->debug[34]++;
  else
    _this->debug[35]++;

  xPR->left = xPRL->right;

  xPR->parent = xPRL;

  xPRL->right = xPR;

  if(xP == xP->parent->left)
    xP->parent->left = xPRL, _this->debug[64]++;
  else
    xP->parent->right = xPRL, _this->debug[65]++;

  xPRL->parent = xP->parent;

  xP->parent = xPRL;

  xPRL->left = xP;
}
