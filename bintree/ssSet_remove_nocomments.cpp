
// ssSet_remove.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void SsSetNodeEraseFixup(ssSet* _this, SsSetNode* x)
{
  SsSetNode* w = 0;
  SsSetNode* xP = 0;

  while(x != GETROOTFROMTREE(_this) && x->color == SsSetBlack)
  {
    xP = x->parent;

    if(x == xP->left)
    {
      w = xP->right;

      if(w->color == SsSetRed)
      {
        w = w->left;

        if( ( !w->left || w->left->color == SsSetBlack) && ( !w->right || w->right->color == SsSetBlack) )
        {
          w = xP->right;

          w->color = SsSetBlack;

          xP->color = SsSetRed;

          LeftRotateDelete1(xP);

          w = xP->right;

          w->color = SsSetRed;

          x = xP;
        }
        else if( !w->right || w->right->color == SsSetBlack)
        {
          w = xP->right;

          w->color = SsSetBlack;

          xP->color = SsSetRed;

          LeftRightLeftRotate(xP);

          w = xP->parent;

          w->color = xP->color;

          xP->color = SsSetBlack;

          w->right->color = SsSetBlack;

          x = GETROOTFROMTREE(_this);
        }
        else
        {
          w = xP->right;

          w->color = SsSetBlack;

          xP->color = SsSetRed;

          LeftLeftRotate(xP);

          w = xP->parent;

          w->color = xP->color;

          xP->color = SsSetBlack;

          w->right->color = SsSetBlack;

          x = GETROOTFROMTREE(_this);
        }
      }
      else
      {
        if( ( !w->left || w->left->color == SsSetBlack) && ( !w->right || w->right->color == SsSetBlack) )
        {
          w->color = SsSetRed;

          x = xP;
        }
        else if( !w->right || w->right->color == SsSetBlack)
        {
          w->left->color = SsSetBlack;

          w->color = SsSetRed;

          RightLeftRotateDelete(xP);

          w = xP->parent;

          w->color = xP->color;

          xP->color = SsSetBlack;

          w->right->color = SsSetBlack;

          x = GETROOTFROMTREE(_this);
        }
        else
        {
          w->color = xP->color;

          xP->color = SsSetBlack;

          w->right->color = SsSetBlack;

          LeftRotateDelete2(xP);

          x = GETROOTFROMTREE(_this);
        }
      }
    }
    else
    {
      w = xP->left;

      if(w->color == SsSetRed)
      {
        w = w->right;

        if( ( !w->right || w->right->color == SsSetBlack) && ( !w->left || w->left->color == SsSetBlack) )
        {
          w = xP->left;

          w->color = SsSetBlack;

          xP->color = SsSetRed;

          RightRotateDelete1(xP);

          w = xP->left;

          w->color = SsSetRed;

          x = xP;
        }
        else if( !w->left || w->left->color == SsSetBlack)
        {
          w = xP->left;

          w->color = SsSetBlack;

          xP->color = SsSetRed;

          RightLeftRightRotate(xP);

          w = xP->parent;

          w->color = xP->color;

          xP->color = SsSetBlack;

          w->left->color = SsSetBlack;

          x = GETROOTFROMTREE(_this);
        }
        else
        {
          w = xP->left;

          w->color = SsSetBlack;

          xP->color = SsSetRed;

          RightRightRotate(xP);

          w = xP->parent;

          w->color = xP->color;

          xP->color = SsSetBlack;

          w->left->color = SsSetBlack;

          x = GETROOTFROMTREE(_this);
        }
      }
      else
      {
        if( ( !w->right || w->right->color == SsSetBlack) && ( !w->left || w->left->color == SsSetBlack) )
        {
          w->color = SsSetRed;

          x = xP;
        }
        else if( !w->left || w->left->color == SsSetBlack)
        {
          w->right->color = SsSetBlack;

          w->color = SsSetRed;

          LeftRightRotateDelete(xP);

          w = xP->parent;

          w->color = xP->color;

          xP->color = SsSetBlack;

          w->left->color = SsSetBlack;

          x = GETROOTFROMTREE(_this);
        }
        else
        {
          w->color = xP->color;

          xP->color = SsSetBlack;

          w->left->color = SsSetBlack;

          RightRotateDelete2(xP);

          x = GETROOTFROMTREE(_this);
        }
      }
    }
  }

  //if(x == GETROOTFROMTREE(_this) )
  //  gDebugRotate[68]++;

  x->color = SsSetBlack;
}

// integrated for root sentinel as long as y is never sentinelRoot
SsSetNode* SsSetTreeErase(ssSet* _this, SsSetNode* z)
{
  uint32_t color = 0;

// Sentinel {
  SsSetNode* t_nil = &_this->leaf;
// Sentinel }

  SsSetNode* x = 0;
  SsSetNode* y = 0;

  if( !z->left || !z->right)
    y = z;
  else
    y = TreeSuccessor(z);
  
  if( !y)
    goto label_return;
  
  // check if y is ever sentinelRoot
  if(y == GETSENTINELFROMTREE(_this) )
  {
    y = 0;
    
    goto label_return;
  }

// check if y is ever sentinelRoot

// Sentinel {
  t_nil->left = 0; // todo
  t_nil->right = 0; // todo

  t_nil->parent = y;

  t_nil->color = SsSetBlack;

  if( !y->left)
    y->left = t_nil;

  if( !y->right)
    y->right = t_nil;
// Sentinel }

// Sentinel {
  if(y->left != t_nil)
// Sentinel }
    x = y->left;
  else
    x = y->right;

  x->parent = y->parent;

  if(y == y->parent->left)
    y->parent->left = x;
  else
    y->parent->right = x;

  color = y->color;

  if(y != z)
  {
    // copy all fields besides left right parent color
    memcpy(GETCLIENT(z), GETCLIENT(y), _this->sizeOf); // todo - 2nd copy in delete
  }

  if(color == SsSetBlack)
    SsSetNodeEraseFixup(_this, x);

// Sentinel {
  if(t_nil->parent->left == t_nil)
    t_nil->parent->left = 0;
  else if(t_nil->parent->right == t_nil)
    t_nil->parent->right = 0;

  t_nil->left = 0; // todo
  t_nil->right = 0; // todo
// Sentinel }

label_return:
  return y;
}

// integrated for root sentinel
int64_t SsSetErase(ssSet* _this, void* key, SsSetCompare lessThan, void* client)
{
  bool result = false;

  int empty = 1;

  SsSetNode* t = 0;
  SsSetNode* z = 0;

  if( !_this || !key || !_this->num)
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
  // equalTo
  // evaluate
  // stack
  // queue
  // maxStack
  // maxQueue
  // sizeOf

  // touched in this function
  // -----
  // root SsSetTreeErase
  // leaf SsSetTreeErase
  // lessThan
  // allocator SsMmFree
  // num

  if(lessThan)
    _this->lessThan = lessThan;

  z = TreeSearch(GETROOTFROMTREE(_this), key, _this->lessThan);

  if(z)
  {
    empty = 0;

    if(client)
      memcpy(client, GETCLIENT(z), _this->sizeOf);

    t = SsSetTreeErase(_this, z);
    if( !t)
    {
      _log("error");
      goto label_return;
    }

    z = t;

    if( !SsMmFree(_this->allocator, (void**)&z) )
    {
      _log("error");
      goto label_return;
    }

    _this->num--;
  }

  result = true;

label_return:
  return result ? empty : SsSetError;
}
