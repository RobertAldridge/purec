
// File Name: binremove.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

#if 0
// case 1
// 1A
// 1B
// 1C
// 1D

// case 2
// 2A
// 2B

// case 3
// 3A
// 3B
// 3C
// 3D

// case 4
// 4A
// 4B
// 4C
// 4D
// 4E
void rb-delete-fixup(BinaryTree* tree, BinaryTreeNode* x)
{
  while x != tree->root && x->color == black
  {
    if x == x->parent->left
    {
      BinaryTreeNode* w = x->parent->right

      // case 1
      if w->color == red
      {
        w->color = black // 1A
        x->parent->color = red // 1B
        left-rotate(tree, x->parent) // 1C
        w = x->parent->right // 1D
      }

      // case 2
      if w->left->color == black && w->right->color == black
      {
        w->color = red // 2A
        x = x->parent // 2B
      }

      else
      {
        // case 3
        if w->right->color == black
        {
          w->left->color = black // 3A
          w->color = red // 3B
          right-rotate(tree, w) // 3C
          w = x->parent->right // 3D
        }

        // case 4
        w->color = x->parent->color // 4A
        x->parent->color = black // 4B
        w->right->color = black // 4C
        left-rotate(tree, x->parent) // 4D
        x = tree->root // 4E
      }
    }
    else(same with "right" and "left" exchanged) // if x == x->parent->right
    {
      BinaryTreeNode* w = x->parent->left

      // case 1
      if w->color == red
      {
        w->color = black // 1A
        x->parent->color = red // 1B
        right-rotate(tree, x->parent) // 1C
        w = x->parent->left // 1D
      }

      // case 2
      if w->right->color == black && w->left->color == black
      {
        w->color = red // 2A
        x = x->parent // 2B
      }

      else
      {
        // case 3
        if w->left->color == black
        {
          w->right->color = black // 3A
          w->color = red // 3B
          left-rotate(tree, w) // 3C
          w = x->parent->left // 3D
        }

        // case 4
        w->color = x->parent->color // 4A
        x->parent->color = black // 4B
        w->left->color = black // 4C
        right-rotate(tree, x->parent) // 4D
        x = tree->root // 4E
      }
    }
  }
}

left (delete) 2
left (insert) 1
left-left (delete) 1
left-right (delete) 1
left-right (insert) 1
left-right-left (delete) 1

right (delete) 2
right (insert) 1
right-right (delete) 1
right-left (delete) 1
right-left (insert) 1
right-left-right (delete) 1
#endif

// fully optimized
//
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
        // prestep
        w = w->left;

        // case 1 + 2
        if( ( !w->left || w->left->color == BLACK) && ( !w->right || w->right->color == BLACK) )
        {
          // prestep
          w = xP->right;

          // 1A w->color = black
          // 1B x->parent->color = red
          // 1C left-rotate(tree, x->parent)
          // 1D w = x->parent-right

          // 2A w->color = red
          // 2B x = x->parent

          // case 1
          w->color = BLACK; // 1A

          xP->color = RED; // 1B

          LeftRotateDelete1(xP); // 1C

          w = xP->right; // 1D

          // case 2
          w->color = RED; // 2A

          x = xP; // 2B
        }
        // case 1 + 3 + 4
        else if( !w->right || w->right->color == BLACK)
        {
          // prestep
          w = xP->right;

          // 1A w->color = black
          // 1B x->parent->color = red
          // 1C left-rotate(tree, x->parent)
          // 1D w = x->parent-right

          // 3A w->left->color = black
          // 3B w->color = red
          // 3C right-rotate(tree, w)
          // 3D w = x->parent->right

          // 4A w->color = x->parent->color
          // 4B x->parent->color = black
          // 4C w->right->color = black
          // 4D left-rotate(tree, x->parent)
          // 4E x = tree->root

          // case 1
          w->color = BLACK; // 1A

          xP->color = RED; // 1B

          // case 1 -> 3 -> 4
          LeftRightLeftRotate(xP); // left-rotate(tree, x->parent) -> right-rotate(tree, w) -> left-rotate(tree, x->parent) transformed 1C -> 3C -> 4D

          // w = x->parent->right missing 1D

          // w->left->color = black missing 3A
          // w->color = red missing 3B

          // case 3
          w = xP->parent; // w = x->parent->right transformed 3D

          // case 4
          w->color = xP->color; // 4A

          xP->color = BLACK; // 4B

          w->right->color = BLACK; // 4C

          x = GETROOTFROMTREE(tree); // 4E
        }
        // case 1 + 4
        else
        {
          // prestep
          w = xP->right;

          // 1A w->color = black
          // 1B x->parent->color = red
          // 1C left-rotate(tree, x->parent)
          // 1D w = x->parent-right

          // 4A w->color = x->parent->color
          // 4B x->parent->color = black
          // 4C w->right->color = black
          // 4D left-rotate(tree, x->parent)
          // 4E x = tree->root

          // case 1
          w->color = BLACK; // 1A

          xP->color = RED; // 1B

          // case 1 -> 4
          LeftLeftRotate(xP); // left-rotate(tree, x->parent) -> left-rotate(tree, x->parent) transformed 1C -> 4D

          w = xP->parent; // w = x->parent->right transformed 1D

          // case 4
          w->color = xP->color; // 4A

          xP->color = BLACK; // 4B

          w->right->color = BLACK; // 4C

          x = GETROOTFROMTREE(tree); // 4E
        }
      }
      else /* w->color == BLACK */
      {
        // case 2
        if( ( !w->left || w->left->color == BLACK) && ( !w->right || w->right->color == BLACK) )
        {
          // 2A w->color = red
          // 2B x = x->parent

          // case 2
          w->color = RED; // 2A

          x = xP; // 2B
        }
        // case 3 + 4
        else if( !w->right || w->right->color == BLACK)
        {
          // 3A w->left->color = black
          // 3B w->color = red
          // 3C right-rotate(tree, w)
          // 3D w = x->parent->right

          // 4A w->color = x->parent->color
          // 4B x->parent->color = black
          // 4C w->right->color = black
          // 4D left-rotate(tree, x->parent)
          // 4E x = tree->root

          // case 3
          w->left->color = BLACK; // 3A

          w->color = RED; // 3B

          // case 3 -> 4
          RightLeftRotateDelete(xP); // right-rotate(tree, w) -> left-rotate(tree, x->parent) transformed 3C -> 4D

          w = xP->parent; // w = x->parent->right transformed 3D

          // case 4
          w->color = xP->color; // 4A

          xP->color = BLACK; // 4B

          w->right->color = BLACK; // 4C

          x = GETROOTFROMTREE(tree); // 4E
        }
        // case 4
        else
        {
          // 4A w->color = x->parent->color
          // 4B x->parent->color = black
          // 4C w->right->color = black
          // 4D left-rotate(tree, x->parent)
          // 4E x = tree->root

          // case 4
          w->color = xP->color; // 4A

          xP->color = BLACK; // 4B

          w->right->color = BLACK; // 4C

          LeftRotateDelete2(xP); // 4D

          x = GETROOTFROMTREE(tree); // 4E
        }
      }
    }
    else /* x == xP->right */
    {
      w = xP->left;

      if(w->color == RED)
      {
        // prestep
        w = w->right;

        // case 1 + 2
        if( ( !w->right || w->right->color == BLACK) && ( !w->left || w->left->color == BLACK) )
        {
          // prestep
          w = xP->left;

          // 1A w->color = black
          // 1B x->parent->color = red
          // 1C right-rotate(tree, x->parent)
          // 1D w = x->parent-left

          // 2A w->color = red
          // 2B x = x->parent

          // case 1
          w->color = BLACK; // 1A

          xP->color = RED; // 1B

          RightRotateDelete1(xP); // 1C

          w = xP->left; // 1D

          // case 2
          w->color = RED; // 2A

          x = xP; // 2B
        }
        // case 1 + 3 + 4
        else if( !w->left || w->left->color == BLACK)
        {
          // prestep
          w = xP->left;

          // 1A w->color = black
          // 1B x->parent->color = red
          // 1C right-rotate(tree, x->parent)
          // 1D w = x->parent-left

          // 3A w->right->color = black
          // 3B w->color = red
          // 3C left-rotate(tree, w)
          // 3D w = x->parent->left

          // 4A w->color = x->parent->color
          // 4B x->parent->color = black
          // 4C w->left->color = black
          // 4D right-rotate(tree, x->parent)
          // 4E x = tree->root

          // case 1
          w->color = BLACK; // 1A

          xP->color = RED; // 1B

          // case 1 -> 3 -> 4
          RightLeftRightRotate(xP); // right-rotate(tree, x->parent) -> left-rotate(tree, w) -> right-rotate(tree, x->parent) transformed 1C -> 3C -> 4D

          // w = x->parent->left missing 1D

          // w->right->color = black missing 3A
          // w->color = red missing 3B

          // case 3
          w = xP->parent; // w = x->parent->left transformed 3D

          // case 4
          w->color = xP->color; // 4A

          xP->color = BLACK; // 4B

          w->left->color = BLACK; // 4C

          x = GETROOTFROMTREE(tree); // 4E
        }
        // case 1 + 4
        else
        {
          // prestep
          w = xP->left;

          // 1A w->color = black
          // 1B x->parent->color = red
          // 1C right-rotate(tree, x->parent)
          // 1D w = x->parent-left

          // 4A w->color = x->parent->color
          // 4B x->parent->color = black
          // 4C w->left->color = black
          // 4D right-rotate(tree, x->parent)
          // 4E x = tree->root

          // case 1
          w->color = BLACK; // 1A

          xP->color = RED; // 1B

          // case 1 -> 4
          RightRightRotate(xP); // right-rotate(tree, x->parent) -> right-rotate(tree, x->parent) transformed 1C -> 4D

          w = xP->parent; // w = x->parent-left transformed 1D

          // case 4
          w->color = xP->color; // 4A

          xP->color = BLACK; // 4B

          w->left->color = BLACK; // 4C

          x = GETROOTFROMTREE(tree); // 4E
        }
      }
      else /* w->color == BLACK */
      {
        // case 2
        if( ( !w->right || w->right->color == BLACK) && ( !w->left || w->left->color == BLACK) )
        {
          // 2A w->color = red
          // 2B x = x->parent

          // case 2
          w->color = RED; // 2A

          x = xP; // 2B
        }
        // case 3 + 4
        else if( !w->left || w->left->color == BLACK)
        {
          // 3A w->right->color = black
          // 3B w->color = red
          // 3C left-rotate(tree, w)
          // 3D w = x->parent->left

          // 4A w->color = x->parent->color
          // 4B x->parent->color = black
          // 4C w->left->color = black
          // 4D right-rotate(tree, x->parent)
          // 4E x = tree->root

          // case 3
          w->right->color = BLACK; // 3A

          w->color = RED; // 3B

          // case 3 -> 4
          LeftRightRotateDelete(xP); // left-rotate(tree, w) -> right-rotate(tree, x->parent) transformed 3C -> 4D

          w = xP->parent; // w = x->parent->left transformed 3D

          // case 4
          w->color = xP->color; // 4A

          xP->color = BLACK; // 4B

          w->left->color = BLACK; // 4C

          x = GETROOTFROMTREE(tree); // 4E
        }
        // case 4
        else
        {
          // 4A w->color = x->parent->color
          // 4B x->parent->color = black
          // 4C w->left->color = black
          // 4D right-rotate(tree, x->parent)
          // 4E x = tree->root

          // case 4
          w->color = xP->color; // 4A

          xP->color = BLACK; // 4B

          w->left->color = BLACK; // 4C

          RightRotateDelete2(xP); // 4D

          x = GETROOTFROMTREE(tree); // 4E
        }
      }
    }
  }

  x->color = BLACK;
}

#if 0
BinaryTreeNode* rb-delete(BinaryTree* tree, BinaryTreeNode* z)
{
  BinaryTreeNode* x = 0;
  BinaryTreeNode* y = 0;

  if z->left == tree->nil || z->right == tree->nil
    y = z
  else
    y = tree-successor(z)

  if y->left != tree->nil
    x = y->left
  else
    x = y->right

  x->parent = y->parent

  if y->parent == tree->nil
    tree->root = x
  else if y == y->parent->left
    y->parent->left = x
  else
    y->parent->right = x

  if y != z
    z->key = y->key

  if y->color == black
    rb-delete-fixup(tree, x)

  return y
}
#endif

// integrated for root sentinel as long as y is never sentinelRoot
BinaryTreeNode* BinDelete(BinaryTree* tree, BinaryTreeNode* z)
{
  int Color = 0;

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
    memcpy(GETCLIENT(z), GETCLIENT(y), tree->SizeOfClientAligned); // todo - 2nd copy in delete
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
int bintree::remove(void* objectKey, binaryTreeEquivalence EqualTo, void* objectResult)
{
  BinaryTree* tree = (BinaryTree*)this;

  BinaryTreeNode* t = 0;
  BinaryTreeNode* z = 0;

  if( !tree || !objectKey || tree->NumberOfNodes <= 0)
  {
    // BinTreeRemove(...) bad params
    _log("error");
    return RETURN_ERROR;
  }

  if(EqualTo)
    tree->EqualTo = EqualTo;

  if( !tree->EqualTo)
  {
    // BinTreeRemove(...) NIL binaryTreeEquivalence function
    _log("error");
    return RETURN_ERROR;
  }

  z = TreeSearch(GETROOTFROMTREE(tree), objectKey, tree->LessThan, tree->EqualTo);

  if( !z)
  {
    // BinTreeRemove(...) TreeSearch(...) cannot find Object in tree
    _log("error");
    return RETURN_ERROR;
  }

  if(objectResult)
    memcpy(objectResult, GETCLIENT(z), tree->SizeOfClientExact);

  t = BinDelete(tree, z);

  z = t;

  if( !z)
  {
    // BinTreeRemove(...) BINDelete(...) cannot find Object in tree
    _log("error");
    return RETURN_ERROR;
  }

  //*( --tree->MemoryManagerArrayCurrent) = (char*)z;
  if( !SsmmFree(tree->nodeAllocator, (void**)&z) )
  {
    _log("error");
    return RETURN_ERROR;
  }

  tree->NumberOfNodes--;

  return RETURN_OK;
}
