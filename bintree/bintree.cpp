
// File Name: bintree.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

//#include "../../general.h"

#if defined(_MSC_VER)
  #pragma warning (push, 4)
#endif

#undef DEBUG
#undef _DEBUG
#undef NDEBUG
#define NDEBUG

#include <malloc.h>
#include <memory.h>

#include "ptrtrack.h"

#include "bintree.h"

typedef int ORDER;

#define PREORDER preorder
#define INORDER inorder
#define POSTORDER postorder
#define LEVELORDER levelorder

#include "binpriv.h"
//#include "../debugutils/log.h"

//#ifdef __cplusplus
//  extern "C" {
//#endif

#if defined(_MSC_VER)
  #pragma warning (disable: 4127)
  #pragma warning (disable: 4711)
#endif

#undef TRUE
#define TRUE 1

#undef FALSE
#define FALSE 0

#define RED 1
#define BLACK 2

#define RETURN_OK 0
#define RETURN_ERROR -1

#if !defined(_MSC_VER)
  #define __forceinline inline
#endif

#define GETCLIENT(node) (void*)(node + 1)

#define GETACTUALROOT(tree) (tree->sentinelRoot.left)
#define SETACTUALROOT(tree, node) (tree->sentinelRoot.left = node)

#define GETPARENTOFACTUALROOT(tree) ( &tree->sentinelRoot)

#define _log(blah) {}

const int bintree::ok = 0;
const int bintree::error = -1;

const int bintree::empty = 1;

const int bintree::preorder = 0;
const int bintree::inorder = 1;
const int bintree::postorder = 2;
const int bintree::levelorder = 3;

static void TreeInsert(BinaryTree* tree, BinaryTreeNode* insert)
{
  BinaryTreeNode* root = GETACTUALROOT(tree);

  // actual root's parent is sentinel
  BinaryTreeNode* parent = GETPARENTOFACTUALROOT(tree);

  binaryTreeCompare LessThan = tree->LessThan;

  for(BinaryTreeNode* child = root; child; /*nop*/)
  {
    bool isLessThan = LessThan(GETCLIENT(insert), GETCLIENT(child) );

    parent = child;

    child = isLessThan ? child->left : child->right;
  }

  insert->parent = parent;

  if(LessThan(GETCLIENT(insert), GETCLIENT(parent) ) )
    parent->left = insert;
  else
    parent->right = insert;
}

// swap a node with its right child

//                        x->parent
//                       /  ^      \
//                      v  /        v
//       x; x->parent->left          ...
//      /  ^            ^  \
//     v  /              \  v
// x->left                y = x->right
//                       /  ^      ^  \
//                      v  /        \  v
//           x->right->left          x->right->right
//
//                                   x->parent
//                                  /  ^      \
//                                 v  /        v
//                        y = x->right          ...
//                       /  ^      ^  \
//                      v  /        \  v
//       x; x->parent->left          x->right->right
//      /  ^            ^  \
//     v  /              \  v
// x->left                x->right->left

// or

//      x->parent
//     /      ^  \
//    v        \  v
// ...          x; x->parent->right
//             /  ^             ^  \
//            v  /               \  v
//        x->left                 y = x->right
//                               /  ^      ^  \
//                              v  /        \  v
//                   x->right->left          x->right->right
//
//                x->parent
//               /      ^  \
//              v        \  v
//           ...          y = x->right
//                       /  ^      ^  \
//                      v  /        \  v
//       x; x->parent->right          x->right->right
//      /  ^            ^  \
//     v  /              \  v
// x->left                x->right->left

static void LeftRotate(BinaryTreeNode* x)
{
  BinaryTreeNode* y = x->right;

//                        x->parent
//                       /  ^      \
//                      v  /        v
//       x; x->parent->left          ...
//      /  ^            ^  \
//     v  /              \  v
// x->left                y = x->right
//                       /  ^      ^  \
//                      v  /        \  v
//           x->right->left          x->right->right

  // 1 of 6
  x->right = y->left;

//                        x->parent
//                       /  ^      \
//                      v  /        v
//       x; x->parent->left          ...
//      /  ^       |    ^
//     v  /        |     \
// x->left         |      y = x->right
//                 |     /  ^      ^  \
//                 v    v  /        \  v
//           x->right->left          x->right->right

  // 2 of 6
  if(y->left)
    y->left->parent = x;

//                        x->parent
//                       /  ^      \
//                      v  /        v
//       x; x->parent->left          ...
//      /  ^    ^  |    ^
//     v  /     |  |     \
// x->left      |  |      y = x->right
//              |  |     /         ^  \
//              |  v    v           \  v
//           x->right->left          x->right->right

  // 3 of 6
  y->parent = x->parent;

//                        x->parent
//                       /  ^   ^  \
//                      v  /    |   v
//       x; x->parent->left     |    ...
//      /  ^    ^  |            |
//     v  /     |  |            |
// x->left      |  |      y = x->right
//              |  |     /         ^  \
//              |  v    v           \  v
//           x->right->left          x->right->right

  // 4 of 6
  if(x == x->parent->left)
    x->parent->left = y;

//                        x->parent
//                          ^ |  ^ \
//                         /  |  |  v
//       x; x->parent->left   |  |   ...
//      /  ^    ^  |          |  |
//     v  /     |  |          v  |
// x->left      |  |      y = x->right
//              |  |     /         ^  \
//              |  v    v           \  v
//           x->right->left          x->right->right

  else /* x == x->parent->right */
    x->parent->right = y;

  // 5 of 6
  y->left = x;

//                        x->parent
//                          ^ |  ^ \
//                         /  |  |  v
//       x; x->parent->left   |  |   ...
//      /  ^    ^  |      ^   |  |
//     v  /     |  |       \  v  |
// x->left      |  |      y = x->right
//              |  |               ^  \
//              |  v                \  v
//           x->right->left          x->right->right

  // 6 of 6
  x->parent = y;

//                        x->parent
//                            |  ^ \
//                            |  |  v
//       x; x->parent->left   |  |   ...
//      /  ^    ^  |    \ ^   |  |
//     v  /     |  |     v \  v  |
// x->left      |  |      y = x->right
//              |  |               ^  \
//              |  v                \  v
//           x->right->left          x->right->right

//                                   x->parent
//                                  /  ^      \
//                                 v  /        v
//                        y = x->right          ...
//                       /  ^      ^  \
//                      v  /        \  v
//       x; x->parent->left          x->right->right
//      /  ^            ^  \
//     v  /              \  v
// x->left                x->right->left
}

static void RightRotate(BinaryTreeNode* x)
{
  BinaryTreeNode* y = x->left;

  // 1 of 6
  x->left = y->right;

  // 2 of 6
  if(y->right)
    y->right->parent = x;

  // 3 of 6
  y->parent = x->parent;

  // 4 of 6
  if(x == x->parent->right)
    x->parent->right = y;
  else /* x == x->parent->left */
    x->parent->left = y;

  // 5 of 6
  y->right = x;

  // 6 of 6
  x->parent = y;
}

static void LeftRightInsertRotate(BinaryTreeNode* x)
{
  BinaryTreeNode* xP = x->parent;
  BinaryTreeNode* xPP = xP->parent;

  // 1 of 10
  if(x->left)
    x->left->parent = xP;

  // 2 of 10
  xP->right = x->left;

  // 3 of 10
  if(x->right)
    x->right->parent = xPP;

  // 4 of 10
  xPP->left = x->right;

  // 5 of 10
  if(xPP == xPP->parent->right)
    xPP->parent->right = x;
  else /* xPP == xPP->parent->left */
    xPP->parent->left = x;

  // 6 of 10
  x->left = xP;

  // 7 of 10
  x->right = xPP;

  // 8 of 10
  x->parent = xPP->parent;

  // 9 of 10
  xP->parent = x;

  // 10 of 10
  xPP->parent = x;
}

static void RightLeftInsertRotate(BinaryTreeNode* x)
{
  BinaryTreeNode* xP = x->parent;
  BinaryTreeNode* xPP = xP->parent;

  // 1 of 10
  if(x->right)
    x->right->parent = xP;

  // 2 of 10
  xP->left = x->right;

  // 3 of 10
  if(x->left)
    x->left->parent = xPP;

  // 4 of 10
  xPP->right = x->left;

  // 5 of 10
  if(xPP == xPP->parent->left)
    xPP->parent->left = x;
  else /* xPP == xPP->parent->right */
    xPP->parent->right = x;

  // 6 of 10
  x->right = xP;

  // 7 of 10
  x->left = xPP;

  // 8 of 10
  x->parent = xPP->parent;

  // 9 of 10
  xP->parent = x;

  // 10 of 10
  xPP->parent = x;
}

static void LeftRightLeftRotate(BinaryTreeNode* xP)
{
  BinaryTreeNode* xPR = xP->right;
  BinaryTreeNode* xPRL = xPR->left;
  BinaryTreeNode* xPRLL = xPRL->left;

  // 1 of 12
  xP->right = xPRLL->left;

  // 2 of 12
  if(xPRLL->left)
    xPRLL->left->parent = xP;

  // 3 of 12
  xPRL->left = xPRLL->right;

  // 4 of 12
  if(xPRLL->right)
    xPRLL->right->parent = xPRL;

  // 5 of 12
  xPRL->parent = xPRLL;

  // 6 of 12
  xPRLL->right = xPRL;

  // 7 of 12
  if(xP == xP->parent->left)
    xP->parent->left = xPR;
  else /* xP == xP->parent->right */
    xP->parent->right = xPR;

  // 8 of 12
  xPR->parent = xP->parent;

  // 9 of 12
  xP->parent = xPRLL;

  // 10 of 12
  xPRLL->left = xP;

  // 11 of 12
  xPR->left = xPRLL;

  // 12 of 12
  xPRLL->parent = xPR;
}

static void LeftLeftRotate(BinaryTreeNode* xP)
{
  BinaryTreeNode* xPR = xP->right;
  BinaryTreeNode* xPRL = xPR->left;

  // 1 of 6
  if(xPRL->left)
    xPRL->left->parent = xP;

  // 2 of 6
  xP->right = xPRL->left;

  // 3 of 6
  if(xP == xP->parent->left)
    xP->parent->left = xPR;
  else /* xP == xP->parent->right */
    xP->parent->right = xPR;

  // 4 of 6
  xPR->parent = xP->parent;

  // 5 of 6
  xP->parent = xPRL;

  // 6 of 6
  xPRL->left = xP;
}

static void RightLeftDeleteRotate(BinaryTreeNode* xP)
{
  BinaryTreeNode* xPR = xP->right;
  BinaryTreeNode* xPRL = xPR->left;

  // 1 of 10
  if(xPRL->left)
    xPRL->left->parent = xP;

  // 2 of 10
  xP->right = xPRL->left;

  // 3 of 10
  if(xPRL->right)
    xPRL->right->parent = xPR;

  // 4 of 10
  xPR->left = xPRL->right;

  // 5 of 10
  xPR->parent = xPRL;

  // 6 of 10
  xPRL->right = xPR;

  // 7 of 10
  if(xP == xP->parent->left)
    xP->parent->left = xPRL;
  else /* xP == xP->parent->right */
    xP->parent->right = xPRL;

  // 8 of 10
  xPRL->parent = xP->parent;

  // 9 of 10
  xP->parent = xPRL;

  // 10 of 10
  xPRL->left = xP;
}

static void RightLeftRightRotate(BinaryTreeNode* xP)
{
  BinaryTreeNode* xPL = xP->left;
  BinaryTreeNode* xPLR = xPL->right;
  BinaryTreeNode* xPLRR = xPLR->right;

  // 1 of 12
  xP->left = xPLRR->right;

  // 2 of 12
  if(xPLRR->right)
    xPLRR->right->parent = xP;

  // 3 of 12
  xPLR->right = xPLRR->left;

  // 4 of 12
  if(xPLRR->left)
    xPLRR->left->parent = xPLR;

  // 5 of 12
  xPLR->parent = xPLRR;

  // 6 of 12
  xPLRR->left = xPLR;

  // 7 of 12
  if(xP == xP->parent->right)
    xP->parent->right = xPL;
  else /* xP == xP->parent->left */
    xP->parent->left = xPL;

  // 8 of 12
  xPL->parent = xP->parent;

  // 9 of 12
  xP->parent = xPLRR;

  // 10 of 12
  xPLRR->right = xP;

  // 11 of 12
  xPL->right = xPLRR;

  // 12 of 12
  xPLRR->parent = xPL;
}

static void RightRightRotate(BinaryTreeNode* xP)
{
  BinaryTreeNode* xPL = xP->left;
  BinaryTreeNode* xPLR = xPL->right;

  // 1 of 6
  if(xPLR->right)
    xPLR->right->parent = xP;

  // 2 of 6
  xP->left = xPLR->right;

  // 3 of 6
  if(xP == xP->parent->right)
    xP->parent->right = xPL;
  else /* xP == xP->parent->left */
    xP->parent->left = xPL;

  // 4 of 6
  xPL->parent = xP->parent;

  // 5 of 6
  xP->parent = xPLR;

  // 6 of 6
  xPLR->right = xP;
}

static void LeftRightDeleteRotate(BinaryTreeNode* xP)
{
  BinaryTreeNode* xPL = xP->left;
  BinaryTreeNode* xPLR = xPL->right;

  // 1 of 10
  if(xPLR->right)
    xPLR->right->parent = xP;

  // 2 of 10
  xP->left = xPLR->right;

  // 3 of 10
  if(xPLR->left)
    xPLR->left->parent = xPL;

  // 4 of 10
  xPL->right = xPLR->left;

  // 5 of 10
  xPL->parent = xPLR;

  // 6 of 10
  xPLR->left = xPL;

  // 7 of 10
  if(xP == xP->parent->right)
    xP->parent->right = xPLR;
  else /* xP == xP->parent->left */
    xP->parent->left = xPLR;

  // 8 of 10
  xPLR->parent = xP->parent;

  // 9 of 10
  xP->parent = xPLR;

  // 10 of 10
  xPLR->right = xP;
}

static void BinInsert(BinaryTree* T, BinaryTreeNode* x)
{
  BinaryTreeNode* y = 0;
  BinaryTreeNode* xP = 0;

  TreeInsert(T, x);

  x->color = RED;

  while(x != T->root && (xP = x->parent)->color == RED) // todo
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
      else
      {
        xP->parent->color = RED;

        if(x == xP->right)
        {
          x->color = BLACK;

          LeftRightInsertRotate(x);

          x = x->left;
        }
        else
        {
          xP->color = BLACK;

          RightRotate(xP->parent);
        }
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
      else
      {
        xP->parent->color = RED;

        if(x == xP->left)
        {
          x->color = BLACK;

          RightLeftInsertRotate(x);

          x = x->right;
        }
        else
        {
          xP->color = BLACK;

          LeftRotate(xP->parent);
        }
      }
    }
  }

  T->root->color = BLACK;
}

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

  x = (BinaryTreeNode*)(*T->MemoryManagerArrayCurrent++);

  x->left = 0;
  x->right = 0;

  if( !x)
  {
    // BinTreeInsert(...) bad memory allocation
    _log("error");
    return RETURN_ERROR;
  }

  memcpy(GETCLIENT(x), object, T->SizeOfClientExact);

  BinInsert(T, x);

  T->NumberOfNodes++;

  return RETURN_OK;
}

static BinaryTreeNode* TreeMinimum(BinaryTreeNode* x)
{
  while(x->left)
    x = x->left;

  return x;
}

static BinaryTreeNode* TreeMaximum(BinaryTreeNode* x)
{
  while(x->right)
    x = x->right;

  return x;
}

//
// GetGreatest - An int which if TRUE, causes the greatest POTYPE
//               to be returned.  If FALSE, it causes the the least POTYPE
//               value to be returned.
//

int bintree::getExtrema(int GetGreatest, void* objectReturn)
{
  BinaryTree* Head = (BinaryTree*)this;

  BinaryTreeNode* Node = 0;

  if( !Head || (GetGreatest != TRUE && GetGreatest != FALSE) )
  {
    // BinGetExtrema(...) bad params
    _log("error");
    return RETURN_ERROR;
  }

  if(GetGreatest == FALSE)
  {
    if(Head->root)
      Node = TreeMinimum(Head->root);
  }
  else /* GetGreatest == TRUE */
  {
    if(Head->root)
      Node = TreeMaximum(Head->root);
  }

  if( !Node)
  {
    // BinGetExtrema(...) empty tree
    return RETURN_ERROR;
  }

  if(objectReturn)
    memcpy(objectReturn, GETCLIENT(Node), Head->SizeOfClientExact);

  return RETURN_OK;
}

static BinaryTreeNode* TreeSuccessor(BinaryTreeNode* x)
{
  BinaryTreeNode* y = 0;

  if(x->right)
    return TreeMinimum(x->right);

  y = x->parent;

  while(y && x == y->right)
  {
    x = y;

    y = y->parent;
  }

  return y;
}

#if 0
rb-delete-fixup
{
  while x != tree->root && x->color == black
  {
    if x == x->parent->left
    {
      w = x->parent->right

      // case 1
      if w->color == red
      {
        w->color = black
        x->parent->color = red
        left-rotate(tree, x->parent)
        w = x->parent->right
      }

      // case 2
      if w->left->color == black && w->right->color == black
      {
        w->color = red
        x = x->parent
      }

      // case 3
      else
      {
        if w->right->color == black
        {
          w->left->color = black
          w->color = red
          right-rotate(tree, w)
          w = x->parent->right
        }

        // case 4
        w->color = x->parent->color
        x->parent->color = black
        w->right->color = black
        left-rotate(tree, x->parent)
        x = tree->root
      }
    }
    else(same with "right" and "left" exchanged) // if x == x->parent->right
    {
      w = x->parent->left

      // case 1
      if w->color == red
      {
        w->color = black
        x->parent->color = red
        right-rotate(tree, x->parent)
        w = x->parent->left
      }

      // case 2
      if w->right->color == black && w->left->color == black
      {
        w->color = red
        x = x->parent
      }

      // case 3
      else
      {
        if w->left->color == black
        {
          w->right->color = black
          w->color = red
          left-rotate(tree, w)
          w = x->parent->left
        }

        // case 4
        w->color = x->parent->color
        x->parent->color = black
        w->left->color = black
        right-rotate(tree, x->parent)
        x = tree->root
      }
    }
  }
}

left
left
left-left
left-right
left-right-left

right
right
right-right
right-left
right-left-right
#endif

// fully optimized
static void BinDeleteFixup(BinaryTreeNode* root, BinaryTreeNode* x)
{
  BinaryTreeNode* w = 0;
  BinaryTreeNode* xP = 0;

  while(x != root && x->color == BLACK)
  {
    xP = x->parent;

    if(x == xP->left)
    {
      w = xP->right;

      if(w->color == RED)
      {
        // prestep
        w = w->left;

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

          LeftRotate(xP); // 1C

          w = xP->right; // 1D

          // case 2
          w->color = RED; // 2A

          x = xP; // 2B
        }
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
          LeftRightLeftRotate(xP); // 1C 3C 4D

          // w = x->parent->right 1D

          // w->left->color = black 3A
          // w->color = red 3B

          // case 3
          w = xP->parent; // w = x->parent->right transformed 3D

          // case 4
          w->color = xP->color; // 4A

          xP->color = BLACK; // 4B

          w->right->color = BLACK; // 4C

          x = root; // 4E
        }
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
          LeftLeftRotate(xP); // 1C 4D

          w = xP->parent; // w = x->parent->right transformed 1D

          // case 4
          w->color = xP->color; // 4A

          xP->color = BLACK; // 4B

          w->right->color = BLACK; // 4C

          x = root; // 4E
        }
      }
      else /* w->color == BLACK */
      {
        if( ( !w->left || w->left->color == BLACK) && ( !w->right || w->right->color == BLACK) )
        {
          // 2A w->color = red
          // 2B x = x->parent

          // case 2
          w->color = RED; // 2A

          x = xP; // 2B
        }
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
          RightLeftDeleteRotate(xP); // 3C 4D

          w = xP->parent; // w = x->parent->right transformed 3D

          // case 4
          w->color = xP->color; // 4A

          xP->color = BLACK; // 4B

          w->right->color = BLACK; // 4C

          x = root; // 4E
        }
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

          LeftRotate(xP); // 4D

          x = root; // 4E
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

          RightRotate(xP); // 1C

          w = xP->left; // 1D

          // case 2
          w->color = RED; // 2A

          x = xP; // 2B
        }
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
          RightLeftRightRotate(xP); // 1C 3C 4D

          // w = x->parent->left 1D

          // w->right->color = black 3A
          // w->color = red 3B

          // case 3
          w = xP->parent; // w = x->parent->left transformed 3D

          // case 4
          w->color = xP->color; // 4A

          xP->color = BLACK; // 4B

          w->left->color = BLACK; // 4C

          x = root; // 4E
        }
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
          RightRightRotate(xP); // 1C 4D

          w = xP->parent; // w = x->parent-left transformed 1D

          // case 4
          w->color = xP->color; // 4A

          xP->color = BLACK; // 4B

          w->left->color = BLACK; // 4C

          x = root; // 4E
        }
      }
      else /* w->color == BLACK */
      {
        if( ( !w->right || w->right->color == BLACK) && ( !w->left || w->left->color == BLACK) )
        {
          // 2A w->color = red
          // 2B x = x->parent

          // case 2
          w->color = RED; // 2A

          x = xP; // 2B
        }
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
          LeftRightDeleteRotate(xP); // 3C 4D

          w = xP->parent; // w = x->parent->left transformed 3D

          // case 4
          w->color = xP->color; // 4A

          xP->color = BLACK; // 4B

          w->left->color = BLACK; // 4C

          x = root; // 4E
        }
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

          RightRotate(xP); // 4D

          x = root; // 4E
        }
      }
    }
  }

  x->color = BLACK;
}

#if 0
rb-delete(tree, z)
{
  if z->left == nil || z->right == nil
    y = z
  else
    y = tree-successor(z)

  if y->left != nil
    x = y->left
  else
    x = y->right

  x->parent = y->parent

  if y->parent == nil
    root = x
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

static BinaryTreeNode* BinDelete(BinaryTree* tree, BinaryTreeNode* z)
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
    memcpy(GETCLIENT(z), GETCLIENT(y), tree->SizeOfClientAligned);
  }

  if(Color == BLACK)
    BinDeleteFixup(GETACTUALROOT(tree), x);

// Sentinel {
  if(T_Nil->parent->left == T_Nil)
    T_Nil->parent->left = 0;
  else if(T_Nil->parent->right == T_Nil)
    T_Nil->parent->right = 0;

  T_Nil->left = 0; // todo
  T_Nil->right = 0; // todo
// Sentinel }

  return y;
}

static BinaryTreeNode* TreeSearch(BinaryTreeNode* x, void* objectKey, binaryTreeCompare LessThan, binaryTreeEquivalence EqualTo)
{
  while(x && !EqualTo(objectKey, GETCLIENT(x) ) )
  {
    if(LessThan(objectKey, GETCLIENT(x) ) )
      x = x->left;
    else
      x = x->right;
  }

  return x;
}

int bintree::remove(void* objectKey, binaryTreeEquivalence EqualTo, void* objectResult)
{
  BinaryTree* T = (BinaryTree*)this;

  BinaryTreeNode* t = 0;
  BinaryTreeNode* z = 0;

  if( !T || !objectKey || T->NumberOfNodes <= 0)
  {
    // BinTreeRemove(...) bad params
    _log("error");
    return RETURN_ERROR;
  }

  if(EqualTo)
    T->EqualTo = EqualTo;

  if( !T->EqualTo)
  {
    // BinTreeRemove(...) NIL binaryTreeEquivalence function
    _log("error");
    return RETURN_ERROR;
  }

  z = TreeSearch(T->root, objectKey, T->LessThan, T->EqualTo);

  if( !z)
  {
    // BinTreeRemove(...) TreeSearch(...) cannot find Object in tree
    _log("error");
    return RETURN_ERROR;
  }

  if(objectResult)
    memcpy(objectResult, GETCLIENT(z), T->SizeOfClientExact);

  t = BinDelete(T, z);

  z = t;

  if( !z)
  {
    // BinTreeRemove(...) BINDelete(...) cannot find Object in tree
    _log("error");
    return RETURN_ERROR;
  }

  *( --T->MemoryManagerArrayCurrent) = (char*)z;

  T->NumberOfNodes--;

  return RETURN_OK;
}

int bintree::find(void* Object1, binaryTreeEquivalence EqualTo, void* ObjectReturn)
{
  BinaryTree* Head = (BinaryTree*)this;

  BinaryTreeNode* node = 0;

  if( !Head || !Object1)
  {
    // BinTreeFind(...) bad params
    _log("error");
    return RETURN_ERROR;
  }

  if(EqualTo)
    Head->EqualTo = EqualTo;

  if( !Head->EqualTo)
  {
    // BinTreeFind(...) NIL binaryTreeEquivalence function
    _log("error");
    return RETURN_ERROR;
  }

  node = TreeSearch(Head->root, Object1, Head->LessThan, Head->EqualTo);

  if(node)
  {
    if(ObjectReturn)
      memcpy(ObjectReturn, GETCLIENT(node), Head->SizeOfClientExact);

    return RETURN_OK;
  }

  return RETURN_ERROR;
}

int bintree::reset()
{
  BinaryTree* tree = (BinaryTree*)this;

  if(tree)
  {
    char* Memory = (char*)tree->TraverseArrayStart;

    int MemoryArrayPointerSize = sizeof(char*) * tree->MaxNumberOfNodes;

    int loop = 0;

    tree->NumberOfNodes = 0;

    Memory += MemoryArrayPointerSize;

    tree->MemoryManagerArrayCurrent = (char**)Memory;

    Memory += MemoryArrayPointerSize;

    for(loop = 0; loop < tree->MaxNumberOfNodes; loop++)
    {
      tree->MemoryManagerArrayCurrent[loop] = Memory;

      Memory += tree->SizeOfClientAligned + sizeof(BinaryTreeNode);
    }

    SETACTUALROOT(tree, 0);

    return RETURN_OK;
  }

  // BinTreeReset(...) bad params
  _log("error");
  return RETURN_ERROR;
}

int bintree::term()
{
  BinaryTree* tree = (BinaryTree*)this;

  if(tree)
  {
    memset(tree, 0, tree->MemoryTotalSize);

    free(tree);

    return RETURN_OK;
  }

  // BinTreeTerminate(...) bad params
  _log("error");
  return RETURN_ERROR;
}

// Preorder is fully optimized
static void IterativePreorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate)
{
  // PSTACK Stack = InitStack()
  BinaryTreeNode** StackTraverseArrayStart = tree->TraverseArrayStart;
  BinaryTreeNode** StackTraverseArrayCurrentTop = StackTraverseArrayStart;

  BinaryTreeNode* LeftChild = 0;
  BinaryTreeNode* RightChild = 0;

  while(1)
  {
    if(ClientEvaluate(GETCLIENT(node) ) )
      break;

    LeftChild = node->left;
    RightChild = node->right;

    if(RightChild)
    {
      if(LeftChild)
      {
        // Stack->Push(RightChild)
        *StackTraverseArrayCurrentTop++ = RightChild;

        // Stack->Push(LeftChild)
        // node = Stack->Pop()
        node = LeftChild;
      }
      else /* !node->left */
      {
        // Stack->Push(RightChild)
        // node = Stack->Pop()
        node = RightChild;
      }
    }
    else if(LeftChild)
    {
      // Stack->Push(LeftChild)
      // node = Stack->Pop()
      node = LeftChild;
    }
    else
    {
      // if(Stack->Empty() == TRUE)
      if(StackTraverseArrayCurrentTop == StackTraverseArrayStart)
        break;

      // node = Stack->Pop()
      node = *( --StackTraverseArrayCurrentTop);
    }
  }
}

// Inorder requires one extra optimization-
// When the left nodes are pushed on the stack,
// a left node is immediately popped off of the stack
// after you break out of the inner loop.
static void IterativeInorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate)
{
  // PSTACK Stack = InitStack()
  BinaryTreeNode** StackTraverseArrayStart = tree->TraverseArrayStart;
  BinaryTreeNode** StackTraverseArrayCurrentTop = StackTraverseArrayStart;

  while(1)
  {
    while(node)
    {
      // Stack->Push(node)
      *StackTraverseArrayCurrentTop++ = node;

      node = node->left;
    }

    // if(Stack->Empty() == TRUE)
    if(StackTraverseArrayCurrentTop == StackTraverseArrayStart)
      break;

    // node = Stack->Pop()
    node = * ( --StackTraverseArrayCurrentTop);

    if(ClientEvaluate(GETCLIENT(node) ) )
      break;

    node = node->right;
  }
}

// ! I have no idea if Postorder is fully optimized or not!
// I optimized it alot, but I am still not sure if it is fully optimized.
// Function courtesy of Bruce Mcquistan ( brucemc@digipen.edu )
static void IterativePostorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate)
{
  // PSTACK Stack = InitStack()
  BinaryTreeNode** StackTraverseArrayStart = tree->TraverseArrayStart;
  BinaryTreeNode** StackTraverseArrayCurrentTop = StackTraverseArrayStart;

  BinaryTreeNode* NodePushed = 0;
  BinaryTreeNode* RightChild = 0;

  while(1)
  {
postorder1:

    do
    {
      // Stack->Push(node)
      *StackTraverseArrayCurrentTop++ = node;

      node = node->left;

    }while(node);

postorder2:

    // if(Stack->Empty() == TRUE)
    if(StackTraverseArrayCurrentTop == StackTraverseArrayStart)
      break;

    // node = Stack->Pop()
    node = *( --StackTraverseArrayCurrentTop);

    RightChild = node->right;

    if(RightChild && RightChild != NodePushed)
    {
      // Stack->Push(node)
      *StackTraverseArrayCurrentTop++ = node;

      NodePushed = RightChild;

      node = RightChild;

      goto postorder1;
    }
    else
    {
      if(ClientEvaluate(GETCLIENT(node) ) )
        break;

      NodePushed = node;

      node = 0;

      goto postorder2;
    }
  }
}

// Levelorder is fully optimized
static void IterativeLevelorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate)
{
  // PQUEUE Queue = InitQueue()
  BinaryTreeNode** QueueTraverseArrayCurrentFront = tree->TraverseArrayStart;
  BinaryTreeNode** QueueTraverseArrayCurrentBack = QueueTraverseArrayCurrentFront;

  BinaryTreeNode* LeftChild = 0;
  BinaryTreeNode* RightChild = 0;

  *QueueTraverseArrayCurrentBack++ = node;

  // while(Queue->Empty() != TRUE)
  while(QueueTraverseArrayCurrentFront != QueueTraverseArrayCurrentBack)
  {
    // Queue->Get()
    node = *QueueTraverseArrayCurrentFront++;

    if(ClientEvaluate(GETCLIENT(node) ) )
      break;

    LeftChild = node->left;
    RightChild = node->right;

    if(LeftChild)
    {
      // Queue->Put(LeftChild)
      *QueueTraverseArrayCurrentBack++ = LeftChild;
    }

    if(RightChild)
    {
      // Queue->Put(RightChild)
      *QueueTraverseArrayCurrentBack++ = RightChild;
    }
  }
}

int bintree::dump(binaryTreeEvaluate ClientEvaluate, ORDER TraversalOrder)
{
  BinaryTree* tree = (BinaryTree*)this;
  
  BinaryTreeNode* root = 0;

  if( !tree || TraversalOrder < PREORDER || TraversalOrder > LEVELORDER)
  {
    // BinTreeDump(...) bad params
    _log("error");
    return RETURN_ERROR;
  }

  if( !ClientEvaluate && !tree->ClientEvaluate)
  {
    // BinTreeDump(...) bad params
    _log("error");
    return RETURN_ERROR;
  }

  if(ClientEvaluate)
    tree->ClientEvaluate = ClientEvaluate;
  
  root = GETACTUALROOT(tree);

  if(root)
  {
    switch(TraversalOrder)
    {
    case PREORDER: IterativePreorderTreeTraverse( tree, root, tree->ClientEvaluate ); break;
    case INORDER: IterativeInorderTreeTraverse( tree, root, tree->ClientEvaluate ); break;
    case POSTORDER: IterativePostorderTreeTraverse( tree, root, tree->ClientEvaluate ); break;
    case LEVELORDER: IterativeLevelorderTreeTraverse( tree, root, tree->ClientEvaluate ); break;
    }
  }

  return RETURN_OK;
}

int bintree::isEmpty(int* NumberOfClientObjects)
{
  BinaryTree* tree = (BinaryTree*)this;

  if( !tree)
  {
    // BinTreeIsEmpty(...) bad params
    _log("error");
    return RETURN_ERROR;
  }

  if(NumberOfClientObjects)
    *NumberOfClientObjects = tree->NumberOfNodes;

  return !tree->NumberOfNodes;
}

bintree* bintree::init(int MaxNumberOfObjects, int SizeOfEachObjectExact, binaryTreeCompare LessThan)
{
///////////////////////////////////////////////////////////////////////////////////////////////////////
  BinaryTree* tree = 0;

  char* Memory = 0;

  int MemoryArrayPointerSize = 0;
  int MemoryPoolSize = 0;
  int MemoryTotalSize = 0;

  int SizeOfEachObjectAligned = 0;

  int loop = 0;
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
  if(MaxNumberOfObjects <= 0 || SizeOfEachObjectExact <= 0 || !LessThan)
  {
    // BinTreeInit(...) bad params
    _log("error");
    return 0;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
  // Align the client memory (sizeof(void*) byte alignment, also known as granularity alignment)
  SizeOfEachObjectAligned = SizeOfEachObjectExact;

  if(SizeOfEachObjectAligned % sizeof(void*) )
    SizeOfEachObjectAligned += sizeof(void*) - (SizeOfEachObjectAligned % sizeof(void*) );

  // We need the pointer pools for the traversing stack and for the memory manager stack.
  MemoryArrayPointerSize = sizeof(char*) * MaxNumberOfObjects;

  // We need the Node pool for the memory manager, with the size of the nodes
  // expanded to include the granularity aligned client object sizes.
  MemoryPoolSize = (SizeOfEachObjectAligned + sizeof(BinaryTreeNode) ) * MaxNumberOfObjects;
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
  // Need enough memory for the head
  MemoryTotalSize = sizeof(BinaryTree);

  // Need two pointer pools, one for the memory manager, and another pool for the traversing stack;
  MemoryTotalSize += MemoryArrayPointerSize * 2;

  // Add the actual node pool to the total required allocation size.
  MemoryTotalSize += MemoryPoolSize;

  // Make sure the memory allocation is a multiple of sizeof(void*) for quicker zero-ing of the
  // memory in the BinTreeTerm(...) function (a couple microseconds faster).
  if(MemoryTotalSize % sizeof(void*) )
    MemoryTotalSize += sizeof(void*) - (MemoryTotalSize % sizeof(void*) );
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
  // Actually allocate the memory we need
  tree = (BinaryTree*)malloc(MemoryTotalSize);

  if( !tree)
  {
    // BinTreeInit(...) bad memory allocation
    _log("error");
    return 0;
  }

  memset(tree, 0, MemoryTotalSize);
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
  Memory = (char*)tree;

  Memory += sizeof(BinaryTree);

  tree->TraverseArrayStart = (BinaryTreeNode**)Memory;

  Memory += MemoryArrayPointerSize;

  tree->MemoryManagerArrayCurrent = (char**)Memory;

  Memory += MemoryArrayPointerSize;

  for(loop = 0; loop < MaxNumberOfObjects; loop++)
  {
    tree->MemoryManagerArrayCurrent[loop] = Memory;

    Memory += SizeOfEachObjectAligned + sizeof(BinaryTreeNode);
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
  tree->LessThan = LessThan;

  tree->MaxNumberOfNodes = MaxNumberOfObjects;

  tree->SizeOfClientExact = SizeOfEachObjectExact;
  tree->SizeOfClientAligned = SizeOfEachObjectAligned;

  tree->MemoryTotalSize = MemoryTotalSize;
///////////////////////////////////////////////////////////////////////////////////////////////////////

  return (bintree*)tree;
}

bintree::bintree()
{
}

bintree::bintree(bintree& )
{
}

bintree& bintree::operator=(bintree& )
{
  return *this;
}

//#ifdef __cplusplus
//  }
//#endif
