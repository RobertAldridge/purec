
// File Name: bininsert.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void TreeInsert(ssSet* tree, SsSetNode* insert)
{
  SsSetNode* parent = GETSENTINELFROMTREE(tree);

  for(SsSetNode* child = GETROOTFROMTREE(tree); child; /*nop*/)
  {
    bool isLessThan = (bool)tree->lessThan(GETCLIENT(insert), GETCLIENT(child) );

    parent = child;

    child = isLessThan ? child->left : child->right;
  }

  insert->parent = parent;

  if(LESSTHANWRAPPER(tree, GETCLIENT(insert), parent) )
    parent->left = insert;
  else
    parent->right = insert;
}

// integrated for root sentinel
void BinInsert(ssSet* tree, SsSetNode* x)
{
  SsSetNode* y = 0;

  TreeInsert(tree, x);

  x->color = RED;

  for(SsSetNode* xP = x->parent; xP->color == RED; xP = x->parent)
  {
    if(xP == xP->parent->left)
    {
      y = xP->parent->right;

      if(y && y->color == RED)
      {
        xP->color = BLACK;

        y->color = BLACK;

        xP->parent->color = RED;

        x = xP->parent;
      }
      else if(x == xP->right)
      {
        x->color = BLACK;

        xP->parent->color = RED;

        LeftRightRotateInsert(x);

        x = x->left;
      }
      else
      {
        xP->parent->color = RED;

        xP->color = BLACK;

        RightRotateInsert(xP->parent);
      }
    }
    else
    {
      y = xP->parent->left;

      if(y && y->color == RED)
      {
        xP->color = BLACK;

        y->color = BLACK;

        xP->parent->color = RED;

        x = xP->parent;
      }
      else if(x == xP->left)
      {
        x->color = BLACK;

        xP->parent->color = RED;

        RightLeftRotateInsert(x);

        x = x->right;
      }
      else
      {
        xP->color = BLACK;

        xP->parent->color = RED;

        LeftRotateInsert(xP->parent);
      }
    }
  }

  SETROOTCOLORFROMTREE(tree, BLACK);
}

// integrated for root sentinel
bool SsSetInsert(ssSet* _this, void* key, SsSetCompare lessThan, void* client)
{
  ssSet* tree = (ssSet*)this;
  
  int result = RETURN_ERROR;

  SsSetNode* x = 0;

  if( !tree || !object)
  {
    _log("error");
    goto error;
  }

  if(lessThan)
    tree->lessThan = lessThan;

  if( !tree->lessThan)
  {
    _log("error");
    goto error;
  }

  //x = (SsSetNode*)(*tree->MemoryManagerArrayCurrent++);
  x = (SsSetNode*)SsMmAlloc(tree->allocator);

  if( !x)
  {
    _log("error");
    goto error;
  }

  x->left = 0;
  x->right = 0;

  memcpy(GETCLIENT(x), object, tree->sizeOfClient);

  BinInsert(tree, x);

  tree->numberOfNodes++;
  
  result = RETURN_OK;

error:
  return result;
}
