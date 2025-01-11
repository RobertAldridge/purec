
// File Name bininsert.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
bool TreeInsert(ssSet* _this, SsSetNode* insert)
{
  bool duplicate = false;

  SsSetNode* parent = GETSENTINELFROMTREE(_this);

  for(SsSetNode* child = GETROOTFROMTREE(_this); child; /*nop*/)
  {
    parent = child;
    
    // if less than
    if(_this->lessThan(GETCLIENT(insert), GETCLIENT(child) ) )
    {
      child = child->left;
    }
    // if greater than or equivalent
    else
    {
      // if !lessThan(a, b) && !lessThan(b, a) then a == b
      //
      // if equivalent we set the duplicate flag
      if( !duplicate && !_this->lessThan(GETCLIENT(child), GETCLIENT(insert) ) )
        duplicate = true;

      // if equivalent we still traverse the right child so that we insert as the chronologically latest
      child = child->right;
    }
  }

  insert->parent = parent;

  if(LESSTHANWRAPPER(_this, GETCLIENT(insert), parent) )
    parent->left = insert;
  else
    parent->right = insert;

  return duplicate;
}

// integrated for root sentinel
bool BinInsert(ssSet* _this, SsSetNode* x)
{
  bool duplicate = false;

  SsSetNode* y = 0;

  duplicate = TreeInsert(_this, x);

  x->color = SsSetRed;

  for(SsSetNode* xP = x->parent; xP->color == SsSetRed; xP = x->parent)
  {
    if(xP == xP->parent->left)
    {
      y = xP->parent->right;

      if(y && y->color == SsSetRed)
      {
        xP->color = SsSetBlack;

        y->color = SsSetBlack;

        xP->parent->color = SsSetRed;

        x = xP->parent;
      }
      else if(x == xP->right)
      {
        x->color = SsSetBlack;

        xP->parent->color = SsSetRed;

        LeftRightRotateInsert(x);

        x = x->left;
      }
      else
      {
        xP->parent->color = SsSetRed;

        xP->color = SsSetBlack;

        RightRotateInsert(xP->parent);
      }
    }
    else
    {
      y = xP->parent->left;

      if(y && y->color == SsSetRed)
      {
        xP->color = SsSetBlack;

        y->color = SsSetBlack;

        xP->parent->color = SsSetRed;

        x = xP->parent;
      }
      else if(x == xP->left)
      {
        x->color = SsSetBlack;

        xP->parent->color = SsSetRed;

        RightLeftRotateInsert(x);

        x = x->right;
      }
      else
      {
        xP->color = SsSetBlack;

        xP->parent->color = SsSetRed;

        LeftRotateInsert(xP->parent);
      }
    }
  }

  SETROOTCOLORFROMTREE(_this, SsSetBlack);

  return duplicate;
}

// integrated for root sentinel
int64_t SsSetInsert(ssSet* _this, void* key, SsSetCompare lessThan, void* client)
{
  bool result = false;
  
  int duplicate = 0;

  SsSetNode* x = 0;

  if( !_this || !key || !client)
  {
    _log("error");
    goto label_return;
  }

  if( !lessThan && !_this->lessThan)
  {
    _log("error");
    goto label_return;
  }
  
  // set modified

  // root
  // leaf
  // lessThan
  // equalTo
  // evaluate
  // allocator
  // stack
  // queue
  // maxStack
  // maxQueue
  // num
  // sizeOf

  // no change
  // -----
  // leaf
  // equalTo
  // evaluate
  // stack
  // queue
  // maxStack
  // maxQueue
  // sizeOf

  // touched in this function
  // -----
  // root BinInsert
  // lessThan
  // allocator SsMmAlloc
  // num

  if(lessThan)
    _this->lessThan = lessThan;

  x = (SsSetNode*)SsMmAlloc(_this->allocator);

  if( !x)
  {
    _log("error");
    goto label_return;
  }

  x->left = 0;
  x->right = 0;

  memcpy(GETCLIENT(x), client, _this->sizeOf);

  if(BinInsert(_this, x) )
    duplicate = 1;

  _this->num++;
  
  result = true;

label_return:
  return result ? duplicate : -1;
}
