
// ssSetLeftRightLeft.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void SsSetRotateLeftRightLeftEraseLevel4(ssSet* _this, SsSetNode* xP)
{
  SsSetNode* xPR = xP->right;
  SsSetNode* xPRL = xPR->left;
  SsSetNode* xPRLL = xPRL->left;

  xP->right = xPRLL->left;

  if(xPRLL->left)
    xPRLL->left->parent = xP, _this->debug[16]++;
  else
    _this->debug[17]++;

  xPRL->left = xPRLL->right;

  if(xPRLL->right)
    xPRLL->right->parent = xPRL, _this->debug[18]++;
  else
    _this->debug[19]++;

  xPRL->parent = xPRLL;

  xPRLL->right = xPRL;

  if(xP == xP->parent->left)
    xP->parent->left = xPR, _this->debug[52]++;
  else
    xP->parent->right = xPR, _this->debug[53]++;

  xPR->parent = xP->parent;

  xP->parent = xPRLL;

  xPRLL->left = xP;

  xPR->left = xPRLL;

  xPRLL->parent = xPR;
}
