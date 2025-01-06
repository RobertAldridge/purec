
// File Name: bininsert.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

#if 0
lessThan(lhs, rhs) return compare(lhs, rhs)
greaterThan(lhs, rhs) return compare(rhs, lhs)
equalTo(lhs, rhs) return !lessThan(lhs, rhs) && !greaterThan(lhs, rhs)
lessThanOrEqualTo(lhs, rhs) return lessThan(lhs, rhs) || !greaterThan(lhs, rhs)
greaterThanOrEqualTo(lhs, rhs) return greaterThan(lhs, rhs) || !lessThan(lhs, rhs)
#endif

// integrated for root sentinel
void TreeInsert(BinaryTree* tree, BinaryTreeNode* insert)
{
  BinaryTreeNode* parent = GETSENTINELFROMTREE(tree);

  for(BinaryTreeNode* child = GETROOTFROMTREE(tree); child; /*nop*/)
  {
    bool isLessThan = tree->LessThan(GETCLIENT(insert), GETCLIENT(child) );

    parent = child;

    child = isLessThan ? child->left : child->right;
  }

  insert->parent = parent;

  if(LESSTHANWRAPPER(tree, GETCLIENT(insert), parent) )
    parent->left = insert;
  else
    parent->right = insert;
}

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
void rb-insert(BinaryTree* tree, BinaryTreeNode* x)
{
  tree-insert(tree, x)

  x->color = red

  while x != tree->root && x->parent->color == red
  {
    if x->parent == x->parent->parent->left
    {
      BinaryTreeNode* y = x->parent->parent->right;

      // case 1
      if y->color == red
      {
        x->parent->color = black // 1A
        y->color = black // 1B
        x->parent->parent->color = red // 1C
        x = x->parent->parent // 1D
      }
      else
      {
        // case 2
        if x == x->parent->right
        {
          x = x->parent // 2A
          left-rotate(tree, x) // 2B
        }

        // case 3
        x->parent->color = black // 3A
        x->parent->parent->color = red // 3B
        right-rotate(tree, x->parent->parent) // 3C
      }
    }
    else /*if x->parent == x->parent->parent->right*/
    {
      BinaryTreeNode* y = x->parent->parent->left;

      // case 1
      if y->color == red
      {
        x->parent->color = black // 1A
        y->color = black // 1B
        x->parent->parent->color = red // 1C
        x = x->parent->parent // 1D
      }
      else
      {
        // case 2
        if x == x->parent->left
        {
          x = x->parent // 2A
          right-rotate(tree, x) // 2B
        }

        // case 3
        x->parent->color = black // 3A
        x->parent->parent->color = red // 3B
        left-rotate(tree, x->parent->parent) // 3C
      }
    }
  }
}

left (delete) 2
left (insert) 1
left-right (delete) 1
left-right (insert) 1

right (delete) 2
right (insert) 1
right-left (delete) 1
right-left (insert) 1
#endif

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

      // case 1
      if(y && y->color == RED)
      {
        // 1A x->parent->color = black
        // 1B y->color = black
        // 1C x->parent->parent->color = red
        // 1D x = x->parent->parent

        xP->color = BLACK; // 1A

        y->color = BLACK; // 1B

        xP->parent->color = RED; // 1C

        x = xP->parent; // 1D
      }
      // case 2 + 3
      else if(x == xP->right)
      {
        // 2A x = x->parent
        // 2B left-rotate(tree, x)

        // 3A x->parent->color = black
        // 3B x->parent->parent->color = red
        // 3C right-rotate(tree, x->parent->parent)

        x->color = BLACK; // x->parent->color = black transformed, out of order 3A

        xP->parent->color = RED; // out of order 3B

        LeftRightRotateInsert(x); // left-rotate(tree, x) -> right-rotate(tree, x->parent->parent) transformed 2B -> 3C

        x = x->left; // x = x->parent transformed, out of order 2A
      }
      // case 3
      else
      {
        // 3A x->parent->color = black
        // 3B x->parent->parent->color = red
        // 3C right-rotate(tree, x->parent->parent)

        xP->parent->color = RED;

        xP->color = BLACK;

        RightRotateInsert(xP->parent);
      }
    }
    else/* if(xP == xP->parent->right)*/
    {
      y = xP->parent->left;

      // case 1
      if(y && y->color == RED)
      {
        // 1A x->parent->color = black
        // 1B y->color = black
        // 1C x->parent->parent->color = red
        // 1D x = x->parent->parent

        xP->color = BLACK; // 1A

        y->color = BLACK; // 1B

        xP->parent->color = RED; // 1C

        x = xP->parent; // 1D
      }
      // case 2 + 3
      else if(x == xP->left)
      {
        // 2A x = x->parent
        // 2B right-rotate(tree, x)

        // 3A x->parent->color = black
        // 3B x->parent->parent->color = red
        // 3C left-rotate(tree, x->parent->parent)

        x->color = BLACK; // x->parent->color = black transformed, out of order 3A

        xP->parent->color = RED; // out of order 3B

        RightLeftRotateInsert(x); // right-rotate(tree, x) -> left-rotate(tree, x->parent->parent) transformed 2B -> 3C

        x = x->right; // x = x->parent transformed, out of order 2A
      }
      // case 3
      else
      {
        // 3A x->parent->color = black
        // 3B x->parent->parent->color = red
        // 3C left-rotate(tree, x->parent->parent)

        xP->color = BLACK; // 3A

        xP->parent->color = RED; // 3B

        LeftRotateInsert(xP->parent); // 3C
      }
    }
  }

  SETROOTCOLORFROMTREE(tree, BLACK);
}

// integrated for root sentinel
int bintree::insert(void* object, binaryTreeCompare LessThan)
{
  BinaryTree* T = (BinaryTree*)this;

  BinaryTreeNode* x = 0;

  if( !T || !object || T->NumberOfNodes >= T->MaxNumberOfNodes)
  {
    // BinTreeInsert(...) bad params
    _log("error");
    return RETURN_ERROR;
  }

  if(LessThan)
    T->LessThan = LessThan;

  if( !T->LessThan)
  {
    // BinTreeInsert(...) NIL binaryTreeCompare function
    _log("error");
    return RETURN_ERROR;
  }

  //x = (BinaryTreeNode*)(*T->MemoryManagerArrayCurrent++);
  x = (BinaryTreeNode*)SsmmAlloc(T->nodeAllocator);

  if( !x)
  {
    // BinTreeInsert(...) bad memory allocation
    _log("error");
    return RETURN_ERROR;
  }

  x->left = 0;
  x->right = 0;

  memcpy(GETCLIENT(x), object, T->SizeOfClientExact);

  BinInsert(T, x);

  T->NumberOfNodes++;

  return RETURN_OK;
}
