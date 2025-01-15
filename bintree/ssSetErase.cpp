
// ssSetErase.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void SsSetEraseLevel3(ssSet* _this, SsSetNode* x)
{
  SsSetNode* w = 0;
  SsSetNode* xP = 0;

  // fixup
  while(x != GETROOTFROMTREE(_this) && x->color == SsSetBlack)
  {
    xP = x->parent;

    if(x == xP->left)
    {
      w = xP->right;

      if(w->color == SsSetRed)
      {
        w = w->left;

        if( !w->left)
          gSsSetDebug[70]++;

        if( !w->right)
          gSsSetDebug[71]++;

        if( ( !w->left || w->left->color == SsSetBlack) && ( !w->right || w->right->color == SsSetBlack) )
        {
          w = xP->right;

          w->color = SsSetBlack;

          xP->color = SsSetRed;

          SsSetRotateLeftErase1Level4(xP);

          w = xP->right;

          w->color = SsSetRed;

          x = xP;
        }
        else if( !w->right || w->right->color == SsSetBlack)
        {
          w = xP->right;

          w->color = SsSetBlack;

          xP->color = SsSetRed;

          SsSetRotateLeftRightLeftEraseLevel4(xP);

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

          SsSetRotateLeftLeftEraseLevel4(xP);

          w = xP->parent;

          w->color = xP->color;

          xP->color = SsSetBlack;

          w->right->color = SsSetBlack;

          x = GETROOTFROMTREE(_this);
        }
      }
      else
      {
        if( !w->left)
          gSsSetDebug[72]++;

        if( !w->right)
          gSsSetDebug[73]++;

        if( ( !w->left || w->left->color == SsSetBlack) && ( !w->right || w->right->color == SsSetBlack) )
        {
          w->color = SsSetRed;

          x = xP;
        }
        else if( !w->right || w->right->color == SsSetBlack)
        {
          w->left->color = SsSetBlack;

          w->color = SsSetRed;

          SsSetRotateRightLeftEraseLevel4(xP);

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

          SsSetRotateLeftErase2Level4(xP);

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

        if( !w->left)
          gSsSetDebug[74]++;

        if( !w->right)
          gSsSetDebug[75]++;

        if( ( !w->right || w->right->color == SsSetBlack) && ( !w->left || w->left->color == SsSetBlack) )
        {
          w = xP->left;

          w->color = SsSetBlack;

          xP->color = SsSetRed;

          SsSetRotateRightErase1Level4(xP);

          w = xP->left;

          w->color = SsSetRed;

          x = xP;
        }
        else if( !w->left || w->left->color == SsSetBlack)
        {
          w = xP->left;

          w->color = SsSetBlack;

          xP->color = SsSetRed;

          SsSetRotateRightLeftRightEraseLevel4(xP);

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

          SsSetRotateRightRightEraseLevel4(xP);

          w = xP->parent;

          w->color = xP->color;

          xP->color = SsSetBlack;

          w->left->color = SsSetBlack;

          x = GETROOTFROMTREE(_this);
        }
      }
      else
      {
        if( !w->left)
          gSsSetDebug[76]++;

        if( !w->right)
          gSsSetDebug[77]++;

        if( ( !w->right || w->right->color == SsSetBlack) && ( !w->left || w->left->color == SsSetBlack) )
        {
          w->color = SsSetRed;

          x = xP;
        }
        else if( !w->left || w->left->color == SsSetBlack)
        {
          w->right->color = SsSetBlack;

          w->color = SsSetRed;

          SsSetRotateLeftRightEraseLevel4(xP);

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

          SsSetRotateRightErase2Level4(xP);

          x = GETROOTFROMTREE(_this);
        }
      }
    }
  }

  x->color = SsSetBlack;
}

// integrated for root sentinel as long as y is never sentinelRoot
SsSetNode* SsSetEraseLevel2(ssSet* _this, SsSetNode* z)
{
  uint32_t color = 0;

// Sentinel {
  SsSetNode* t_nil = &_this->leaf;
// Sentinel }

  SsSetNode* x = 0;
  SsSetNode* y = 0;

  if( !z->left || !z->right)
  {
    y = z;
  }
  else // z->left && z->right
  {
    // hierarchical leftmost from z->right; earliest successor to z
    for(SsSetNode* left = z->right; left; left = left->left)
      y = left;
  }

  if( !y)
    goto label_return;

  // check if y is ever sentinelRoot (should never get here)
  if(y == GETSENTINELFROMTREE(_this) )
    gSsSetDebug[79]++;

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

  // x not root sentinel
  // y not root sentinel
  // z not root sentinel

  if(x == y)
    gSsSetDebug[86]++;

  if(x == z)
    gSsSetDebug[87]++;

  // swap nodes instead of swapping clients.  we have use cases where it's important for the lifetime of the node to
  // match the lifetime of the client data.  for example if the client is a sentinel.
  //
  // since client data can be of arbitrary size it may compromise our BigO guarantee.  swapping nodes instead of
  // swapping clients avoids the issue
  if(y != z)
  {
    SsSetNode* blahOld = z;
    SsSetNode* blahNew = y;

    SsSetNode* parent = blahOld->parent;
    SsSetNode* left = blahOld->left;
    SsSetNode* right = blahOld->right;

    if( !parent)
      gSsSetDebug[83]++;

    if( !left)
      gSsSetDebug[84]++;

    if( !right)
      gSsSetDebug[85]++;

    //     parent
    //      | ^
    //      | |
    //      v |
    //    blahOld
    //    ^ / \ ^
    //   / /   \ \
    //  / v     v \
    // left     right
    //
    // and color

    //     parent
    //
    //
    //
    //    blahNew
    //
    //
    //
    // left     right

    if(parent)
    {
      if(blahOld == parent->left)
        parent->left = blahNew;
      else
        parent->right = blahNew;
    }
    //     parent
    //      |
    //      |
    //      v
    //    blahNew
    //
    //
    //
    // left     right

    if(left)
      left->parent = blahNew;
    //     parent
    //      |
    //      |
    //      v
    //    blahNew
    //    ^
    //   /
    //  /
    // left     right

    if(right)
      right->parent = blahNew;
    //     parent
    //      |
    //      |
    //      v
    //    blahNew
    //    ^     ^
    //   /       \
    //  /         \
    // left     right

    blahNew->parent = parent;
    //     parent
    //      | ^
    //      | |
    //      v |
    //    blahNew
    //    ^     ^
    //   /       \
    //  /         \
    // left     right

    blahNew->left = left;
    //     parent
    //      | ^
    //      | |
    //      v |
    //    blahNew
    //    ^ /   ^
    //   / /     \
    //  / v       \
    // left     right

    blahNew->right = right;
    //     parent
    //      | ^
    //      | |
    //      v |
    //    blahNew
    //    ^ / \ ^
    //   / /   \ \
    //  / v     v \
    // left     right

    blahNew->color = blahOld->color;
    //     parent
    //      | ^
    //      | |
    //      v |
    //    blahNew
    //    ^ / \ ^
    //   / /   \ \
    //  / v     v \
    // left     right
    //
    // and color

    // y becomes the node to give back to the memory manager
    y = blahOld;

    // besides the return, y and z are no longer referenced

    // copy all fields besides left right parent color
    //memcpy(GETCLIENT(z), GETCLIENT(y), _this->sizeOf);
  }

  if(color == SsSetBlack)
    SsSetEraseLevel3(_this, x);

// Sentinel {
  if(t_nil->parent->left == t_nil)
    t_nil->parent->left = 0;
  else if(t_nil->parent->right == t_nil)
    t_nil->parent->right = 0;

  t_nil->left = 0; // todo
  t_nil->right = 0; // todo
// Sentinel }

  if(y == GETSENTINELFROMTREE(_this) )
    gSsSetDebug[80]++;

label_return:
  return y;
}

// integrated for root sentinel
int64_t SsSetErase(ssSet* _this, void* key, SsSetCompare lessThan, void* client)
{
  bool result = false;

  int notFound = 1;

  SsSetNode* node = 0;

  if( !_this || !key || !_this->num)
  {
    BlahLog("error");
    goto label_return;
  }

  if( !lessThan && !_this->lessThan)
  {
    BlahLog("error");
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
  // lessThan
  // evaluate
  // stack
  // queue
  // maxStack
  // maxQueue
  // sizeOf

  // touched in this function
  // -----
  // root SsSetEraseLevel2
  // leaf SsSetEraseLevel2
  // allocator SsMmFree
  // num

  if( !lessThan)
    lessThan = _this->lessThan;

  node = SsSetTreeSearchLevel2(GETROOTFROMTREE(_this), key, lessThan);

  if(node)
  {
    notFound = 0;

    if(client)
      memcpy(client, GETCLIENT(node), _this->sizeOf);

    node = SsSetEraseLevel2(_this, node);
    if( !node)
    {
      BlahLog("error");
      goto label_return;
    }

    if( !SsMmFree(_this->allocator, (void**)&node) )
    {
      BlahLog("error");
      goto label_return;
    }

    _this->num--;

    // verify sentinel root right child is null and color is zero
    if(_this->root.right || _this->root.color)
    {
      BlahLog("erase");
      gSsSetDebug[69]++;
    }
  }

  result = true;

label_return:
  return result ? notFound : SsSetError;
}
