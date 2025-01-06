
// File Name: bininsert.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void TreeInsert(BinaryTree* tree, BinaryTreeNode* insert)
{
  BinaryTreeNode* parent = GETSENTINELFROMTREE(tree);

  for(BinaryTreeNode* child = GETROOTFROMTREE(tree); child; /*nop*/)
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
void BinInsert(BinaryTree* tree, BinaryTreeNode* x)
{
  BinaryTreeNode* y = 0;

  TreeInsert(tree, x);

  x->color = RED;

  for(BinaryTreeNode* xP = x->parent; xP->color == RED; xP = x->parent)
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
int bintree::insert(void* object, binaryTreeCompare lessThan)
{
  BinaryTree* tree = (BinaryTree*)this;

  BinaryTreeNode* x = 0;

  if( !tree || !object)
  {
    _log("error");
    return RETURN_ERROR;
  }

  if(lessThan)
    tree->lessThan = lessThan;

  if( !tree->lessThan)
  {
    _log("error");
    return RETURN_ERROR;
  }

  //x = (BinaryTreeNode*)(*tree->MemoryManagerArrayCurrent++);
  x = (BinaryTreeNode*)SsmmAlloc(tree->allocator);

  if( !x)
  {
    _log("error");
    return RETURN_ERROR;
  }

  x->left = 0;
  x->right = 0;

  memcpy(GETCLIENT(x), object, (size_t)tree->sizeOfClient);

  BinInsert(tree, x);

  tree->numberOfNodes++;

  return RETURN_OK;
}
