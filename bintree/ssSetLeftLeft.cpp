
// ssSetLeftLeft.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void SsSetRotateLeftLeftEraseLevel4(ssSet* _this, SsSetNode* xP)
{
  SsSetNode* xPR = xP->right;
  SsSetNode* xPRL = xPR->left;

  if(xPRL->left)
    xPRL->left->parent = xP, _this->debug[6] ++;
  else
    _this->debug[7] ++;

  xP->right = xPRL->left;

  if(xP == xP->parent->left)
    xP->parent->left = xPR, _this->debug[46] ++;
  else
    xP->parent->right = xPR, _this->debug[47] ++;

  xPR->parent = xP->parent;

  xP->parent = xPRL;

  xPRL->left = xP;
}
