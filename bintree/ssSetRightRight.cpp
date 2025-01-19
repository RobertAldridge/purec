
// ssSetRightRight.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void SsSetRotateRightRightEraseLevel4(ssSet* _this, SsSetNode* xP)
{
  SsSetNode* xPL = xP->left;
  SsSetNode* xPLR = xPL->right;

  if(xPLR->right)
    xPLR->right->parent = xP, _this->debug[26]++;
  else
    _this->debug[27]++;

  xP->left = xPLR->right;

  if(xP == xP->parent->right)
    xP->parent->right = xPL, _this->debug[60]++;
  else
    xP->parent->left = xPL, _this->debug[61]++;

  xPL->parent = xP->parent;

  xP->parent = xPLR;

  xPLR->right = xP;
}
