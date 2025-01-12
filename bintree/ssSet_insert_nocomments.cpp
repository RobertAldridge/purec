
// ssSet_insert.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
bool SsSetInsertLevel3(ssSet* _this, SsSetNode* insert, SsSetCompare lessThan)
{
  bool duplicate = false;

  SsSetNode* parent = GETSENTINELFROMTREE(_this);

  for(SsSetNode* child = GETROOTFROMTREE(_this); child; /*nop*/)
  {
    parent = child;

    // if less than
    if(lessThan(GETCLIENT(insert), GETCLIENT(child) ) )
    {
      child = child->left;
    }
    // if greater than or equivalent
    else
    {
      // if !lessThan(a, b) && !lessThan(b, a) then a == b
      //
      // if equivalent we set the duplicate flag
      if( !duplicate && !lessThan(GETCLIENT(child), GETCLIENT(insert) ) )
        duplicate = true;

      // if equivalent we still traverse the right child so that we insert as the chronologically latest
      child = child->right;
    }
  }

  insert->parent = parent;

  if(LESSTHANWRAPPER(_this, GETCLIENT(insert), parent, lessThan) )
    parent->left = insert;
  else
    parent->right = insert;

  return duplicate;
}

// integrated for root sentinel
bool SsSetInsertLevel2(ssSet* _this, SsSetNode* x, SsSetCompare lessThan)
{
  bool duplicate = false;

  SsSetNode* y = 0;

  duplicate = SsSetInsertLevel3(_this, x, lessThan);

  x->color = SsSetRed;

  // fixup
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

        SsSetRotateLeftRightInsert(x);

        x = x->left;
      }
      else
      {
        xP->parent->color = SsSetRed;

        xP->color = SsSetBlack;

        SsSetRotateRightInsert(xP->parent);
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

        SsSetRotateRightLeftInsert(x);

        x = x->right;
      }
      else
      {
        xP->color = SsSetBlack;

        xP->parent->color = SsSetRed;

        SsSetRotateLeftInsert(xP->parent);
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

  if( !_this || !key)
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
  // evaluate
  // stack
  // queue
  // maxStack
  // maxQueue
  // sizeOf

  // touched in this function
  // -----
  // root SsSetInsertLevel2
  // lessThan
  // allocator SsMmAlloc
  // num

  if( !lessThan)
    lessThan = _this->lessThan;

  x = (SsSetNode*)SsMmAlloc(_this->allocator);

  if( !x)
  {
    _log("error");
    goto label_return;
  }

  x->left = 0;
  x->right = 0;

  memcpy(GETCLIENT(x), key, _this->sizeOf);

  if(SsSetInsertLevel2(_this, x, lessThan) )
    duplicate = 1;

  if(client)
    memcpy(GETCLIENT(x), client, _this->sizeOf);

  _this->num++;

  // verify sentinel root right child is null and color is zero
  // if(_this->root.right || _this->root.color)
  //   gSsSetDebug[68]++;

  result = true;

label_return:
  return result ? duplicate : SsSetError;
}
