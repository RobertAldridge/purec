
// File Name: binremove.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void BinDeleteFixup(BinaryTree* tree, BinaryTreeNode* x)
{
  BinaryTreeNode* w = 0;
  BinaryTreeNode* xP = 0;

  while(x != GETROOTFROMTREE(tree) && x->color == BLACK)
  {
    xP = x->parent;

    if(x == xP->left)
    {
      w = xP->right;

      if(w->color == RED)
      {
        w = w->left;

        if( ( !w->left || w->left->color == BLACK) && ( !w->right || w->right->color == BLACK) )
        {
          w = xP->right;

          w->color = BLACK;

          xP->color = RED;

          LeftRotateDelete1(xP);

          w = xP->right;

          w->color = RED;

          x = xP;
        }
        else if( !w->right || w->right->color == BLACK)
        {
          w = xP->right;

          w->color = BLACK;

          xP->color = RED;

          LeftRightLeftRotate(xP);

          w = xP->parent;

          w->color = xP->color;

          xP->color = BLACK;

          w->right->color = BLACK;

          x = GETROOTFROMTREE(tree);
        }
        else
        {
          w = xP->right;

          w->color = BLACK;

          xP->color = RED;

          LeftLeftRotate(xP);

          w = xP->parent;

          w->color = xP->color;

          xP->color = BLACK;

          w->right->color = BLACK;

          x = GETROOTFROMTREE(tree);
        }
      }
      else
      {
        if( ( !w->left || w->left->color == BLACK) && ( !w->right || w->right->color == BLACK) )
        {
          w->color = RED;

          x = xP;
        }
        else if( !w->right || w->right->color == BLACK)
        {
          w->left->color = BLACK;

          w->color = RED;

          RightLeftRotateDelete(xP);

          w = xP->parent;

          w->color = xP->color;

          xP->color = BLACK;

          w->right->color = BLACK;

          x = GETROOTFROMTREE(tree);
        }
        else
        {
          w->color = xP->color;

          xP->color = BLACK;

          w->right->color = BLACK;

          LeftRotateDelete2(xP);

          x = GETROOTFROMTREE(tree);
        }
      }
    }
    else
    {
      w = xP->left;

      if(w->color == RED)
      {
        w = w->right;

        if( ( !w->right || w->right->color == BLACK) && ( !w->left || w->left->color == BLACK) )
        {
          w = xP->left;

          w->color = BLACK;

          xP->color = RED;

          RightRotateDelete1(xP);

          w = xP->left;

          w->color = RED;

          x = xP;
        }
        else if( !w->left || w->left->color == BLACK)
        {
          w = xP->left;

          w->color = BLACK;

          xP->color = RED;

          RightLeftRightRotate(xP);

          w = xP->parent;

          w->color = xP->color;

          xP->color = BLACK;

          w->left->color = BLACK;

          x = GETROOTFROMTREE(tree);
        }
        else
        {
          w = xP->left;

          w->color = BLACK;

          xP->color = RED;

          RightRightRotate(xP);

          w = xP->parent;

          w->color = xP->color;

          xP->color = BLACK;

          w->left->color = BLACK;

          x = GETROOTFROMTREE(tree);
        }
      }
      else
      {
        if( ( !w->right || w->right->color == BLACK) && ( !w->left || w->left->color == BLACK) )
        {
          w->color = RED;

          x = xP;
        }
        else if( !w->left || w->left->color == BLACK)
        {
          w->right->color = BLACK;

          w->color = RED;

          LeftRightRotateDelete(xP);

          w = xP->parent;

          w->color = xP->color;

          xP->color = BLACK;

          w->left->color = BLACK;

          x = GETROOTFROMTREE(tree);
        }
        else
        {
          w->color = xP->color;

          xP->color = BLACK;

          w->left->color = BLACK;

          RightRotateDelete2(xP);

          x = GETROOTFROMTREE(tree);
        }
      }
    }
  }

  x->color = BLACK;
}

// integrated for root sentinel as long as y is never sentinelRoot
BinaryTreeNode* BinDelete(BinaryTree* tree, BinaryTreeNode* z)
{
  uint32_t Color = 0;

// Sentinel {
  BinaryTreeNode* T_Nil = &tree->sentinelLeaf;
// Sentinel }

  BinaryTreeNode* x = 0;
  BinaryTreeNode* y = 0;

  if( !z->left || !z->right)
    y = z;
  else
    y = TreeSuccessor(z);

// check if y is ever sentinelRoot

// Sentinel {
  T_Nil->left = 0; // todo
  T_Nil->right = 0; // todo

  T_Nil->parent = y;

  T_Nil->color = BLACK;

  if( !y->left)
    y->left = T_Nil;

  if( !y->right)
    y->right = T_Nil;
// Sentinel }

// Sentinel {
  if(y->left != T_Nil)
// Sentinel }
    x = y->left;
  else
    x = y->right;

  x->parent = y->parent;

  if(y == y->parent->left)
    y->parent->left = x;
  else
    y->parent->right = x;

  Color = y->color;

  if(y != z)
  {
    // copy all fields besides left right parent color
    memcpy(GETCLIENT(z), GETCLIENT(y), tree->sizeOfClient); // todo - 2nd copy in delete
  }

  if(Color == BLACK)
    BinDeleteFixup(tree, x);

// Sentinel {
  if(T_Nil->parent->left == T_Nil)
    T_Nil->parent->left = 0;
  else if(T_Nil->parent->right == T_Nil)
    T_Nil->parent->right = 0;

  T_Nil->left = 0; // todo
  T_Nil->right = 0; // todo
// Sentinel }

// check if y is ever sentinelRoot todo

  return y;
}

// integrated for root sentinel
int bintree::remove(void* objectKey, binaryTreeEquivalence equalTo, void* objectResult)
{
  BinaryTree* tree = (BinaryTree*)this;

  int result = RETURN_ERROR;

  BinaryTreeNode* t = 0;
  BinaryTreeNode* z = 0;

  if( !tree || !objectKey || tree->numberOfNodes <= 0)
  {
    _log("error");
    goto error;
  }

  if(equalTo)
    tree->equalTo = equalTo;

  if( !tree->equalTo)
  {
    _log("error");
    goto error;
  }

  z = TreeSearch(GETROOTFROMTREE(tree), objectKey, tree->lessThan, tree->equalTo);

  if( !z)
  {
    _log("error");
    goto error;
  }

  if(objectResult)
    memcpy(objectResult, GETCLIENT(z), tree->sizeOfClient);

  t = BinDelete(tree, z);

  z = t;

  if( !z)
  {
    _log("error");
    goto error;
  }

  //*( --tree->MemoryManagerArrayCurrent) = (char*)z;
  if( !SsmmFree(tree->allocator, (void**)&z) )
  {
    _log("error");
    goto error;
  }

  tree->numberOfNodes--;

  result = RETURN_OK;

error:
  return result;
}
