
// ssSetRightLeftRight.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void SsSetRotateRightLeftRightEraseLevel4(ssSet* _this, SsSetNode* xP)
{
  SsSetNode* xPL = xP->left;
  SsSetNode* xPLR = xPL->right;
  SsSetNode* xPLRR = xPLR->right;

  xP->left = xPLRR->right;

  if(xPLRR->right)
    xPLRR->right->parent = xP, _this->debug[36] ++;
  else
    _this->debug[37] ++;

  xPLR->right = xPLRR->left;

  if(xPLRR->left)
    xPLRR->left->parent = xPLR, _this->debug[38] ++;
  else
    _this->debug[39] ++;

  xPLR->parent = xPLRR;

  xPLRR->left = xPLR;

  if(xP == xP->parent->right)
    xP->parent->right = xPL, _this->debug[66] ++;
  else
    xP->parent->left = xPL, _this->debug[67] ++;

  xPL->parent = xP->parent;

  xP->parent = xPLRR;

  xPLRR->right = xP;

  xPL->right = xPLRR;

  xPLRR->parent = xPL;
}
