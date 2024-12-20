
// File Name: bintree.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

#include "../../general.h"

#if defined( _MSC_VER )
   #pragma warning ( push, 4 )
#endif

#undef DEBUG
#undef _DEBUG
#undef NDEBUG
#define NDEBUG

#include < malloc.h >
#include < memory.h >

#include "ptrtrack.h"

#include "bintree.h"

typedef int ORDER;

#define PREORDER preorder
#define INORDER inorder
#define POSTORDER postorder
#define LEVELORDER levelorder

#include "binpriv.h"
#include "../debugutils/log.h"

#ifdef __cplusplus
   extern "C" {
#endif

#if defined( _MSC_VER )
   #pragma warning ( disable: 4127 )
   #pragma warning ( disable: 4711 )
#endif

#undef TRUE
#define TRUE 1

#undef FALSE
#define FALSE 0

#define RED 1
#define BLACK 2

#define RETURN_OK 0
#define RETURN_ERROR -1

#if !defined( _MSC_VER )
   #define __forceinline inline
#endif

const int bintree::ok = 0;
const int bintree::error = -1;

const int bintree::empty = 1;

const int bintree::preorder   = 0;
const int bintree::inorder    = 1;
const int bintree::postorder  = 2;
const int bintree::levelorder = 3;

__forceinline
static
void
__fastcall
TreeInsert
(
   binaryTree* T,
   BinaryTreeNode* z
)
{
   BinaryTreeNode* x = T->root;
   BinaryTreeNode* y = 0;

   binaryTreeCompare LessThan = T->LessThan;

   while( x )
   {
      y = x;

      if( LessThan( z->object, x->object ) )
      {
         x = x->left;
      }
      else
      {
         x = x->right;
      }
   }

   z->parent = y;

   if( !y )
   {
      T->root = z;
   }
   else if( LessThan( z->object, y->object ) )
   {
      y->left = z;
   }
   else
   {
      y->right = z;
   }
}

// swap a node with its right child
//
// it is possible for x->parent to be root

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

static void LeftRotate(binaryTree* T, BinaryTreeNode* x)
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
   if( !x->parent )
      T->root = y;

   else if( x == x->parent->left )
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

__forceinline
static
void
__fastcall
RightRotate
(
   binaryTree* T,
   BinaryTreeNode* x
)
{
   BinaryTreeNode* y = x->left;

   // 1 of 6
   x->left = y->right;

   // 2 of 6
   if( y->right )
   {
      y->right->parent = x;
   }

   // 3 of 6
   y->parent = x->parent;

   // 4 of 6
   if( !x->parent )
   {
      T->root = y;
   }
   else if( x == x->parent->right )
   {
      x->parent->right = y;
   }
   else /* x == x->parent->left */
   {
      x->parent->left = y;
   }

   // 5 of 6
   y->right = x;

   // 6 of 6
   x->parent = y;
}

__forceinline
static
void
__fastcall
LeftRight1InsertRotate
(
   binaryTree* T,
   BinaryTreeNode* x
)
{
   BinaryTreeNode* xP  = x->parent;
   BinaryTreeNode* xPP = xP->parent;

   // 1 of 10
   if( x->left )
   {
      x->left->parent = xP;
   }

   // 2 of 10
   xP->right = x->left;

   // 3 of 10
   if( x->right )
   {
      x->right->parent = xPP;
   }

   // 4 of 10
   xPP->left = x->right;

   // 5 of 10
   if( !xPP->parent )
   {
      T->root = x;
   }
   else if( xPP == xPP->parent->right )
   {
      xPP->parent->right = x;
   }
   else /* xPP == xPP->parent->left */
   {
      xPP->parent->left = x;
   }

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

__forceinline
static
void
__fastcall
RightLeft2InsertRotate
(
   binaryTree* T,
   BinaryTreeNode* x
)
{
   BinaryTreeNode* xP  = x->parent;
   BinaryTreeNode* xPP = xP->parent;

   // 1 of 10
   if( x->right )
   {
      x->right->parent = xP;
   }

   // 2 of 10
   xP->left = x->right;

   // 3 of 10
   if( x->left )
   {
      x->left->parent = xPP;
   }

   // 4 of 10
   xPP->right = x->left;

   // 5 of 10
   if( !xPP->parent )
   {
      T->root = x;
   }
   else if( xPP == xPP->parent->left )
   {
      xPP->parent->left = x;
   }
   else /* xPP == xPP->parent->right */
   {
      xPP->parent->right = x;
   }

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

__forceinline
static
void
__fastcall
LeftRightLeft1DeleteRotate
(
   binaryTree* T,
   BinaryTreeNode* xP
)
{
   BinaryTreeNode* xPR   = xP->right;
   BinaryTreeNode* xPRL  = xPR->left;
   BinaryTreeNode* xPRLL = xPRL->left;

   // 1 of 12
   xP->right = xPRLL->left;

   // 2 of 12
   if( xPRLL->left )
   {
      xPRLL->left->parent = xP;
   }

   // 3 of 12
   xPRL->left = xPRLL->right;

   // 4 of 12
   if( xPRLL->right )
   {
      xPRLL->right->parent = xPRL;
   }

   // 5 of 12
   xPRL->parent = xPRLL;

   // 6 of 12
   xPRLL->right = xPRL;

   // 7 of 12
   if( !xP->parent )
   {
      T->root = xPR;
   }
   else if( xP == xP->parent->left )
   {
      xP->parent->left = xPR;
   }
   else /* xP == xP->parent->right */
   {
      xP->parent->right = xPR;
   }

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

__forceinline
static
void
__fastcall
LeftLeft1DeleteRotate
(
   binaryTree* T,
   BinaryTreeNode* xP
)
{
   BinaryTreeNode* xPR  = xP->right;
   BinaryTreeNode* xPRL = xPR->left;

   // 1 of 6
   if( xPRL->left )
   {
      xPRL->left->parent = xP;
   }

   // 2 of 6
   xP->right = xPRL->left;

   // 3 of 6
   if( !xP->parent )
   {
      T->root = xPR;
   }
   else if( xP == xP->parent->left )
   {
      xP->parent->left = xPR;
   }
   else /* xP == xP->parent->right */
   {
      xP->parent->right = xPR;
   }

   // 4 of 6
   xPR->parent = xP->parent;

   // 5 of 6
   xP->parent = xPRL;

   // 6 of 6
   xPRL->left = xP;
}

__forceinline
static
void
__fastcall
RightLeft1DeleteRotate
(
   binaryTree* T,
   BinaryTreeNode* xP
)
{
   BinaryTreeNode* xPR  = xP->right;
   BinaryTreeNode* xPRL = xPR->left;

   // 1 of 10
   if( xPRL->left )
   {
      xPRL->left->parent = xP;
   }

   // 2 of 10
   xP->right = xPRL->left;

   // 3 of 10
   if( xPRL->right )
   {
      xPRL->right->parent = xPR;
   }

   // 4 of 10
   xPR->left = xPRL->right;

   // 5 of 10
   xPR->parent = xPRL;

   // 6 of 10
   xPRL->right = xPR;

   // 7 of 10
   if( !xP->parent )
   {
      T->root = xPRL;
   }
   else if( xP == xP->parent->left )
   {
      xP->parent->left = xPRL;
   }
   else /* xP == xP->parent->right */
   {
      xP->parent->right = xPRL;
   }

   // 8 of 10
   xPRL->parent = xP->parent;

   // 9 of 10
   xP->parent = xPRL;

   // 10 of 10
   xPRL->left = xP;
}

__forceinline
static
void
__fastcall
RightLeftRight2DeleteRotate
(
   binaryTree* T,
   BinaryTreeNode* xP
)
{
   BinaryTreeNode* xPL   = xP->left;
   BinaryTreeNode* xPLR  = xPL->right;
   BinaryTreeNode* xPLRR = xPLR->right;

   // 1 of 12
   xP->left = xPLRR->right;

   // 2 of 12
   if( xPLRR->right )
   {
      xPLRR->right->parent = xP;
   }

   // 3 of 12
   xPLR->right = xPLRR->left;

   // 4 of 12
   if( xPLRR->left )
   {
      xPLRR->left->parent = xPLR;
   }

   // 5 of 12
   xPLR->parent = xPLRR;

   // 6 of 12
   xPLRR->left = xPLR;

   // 7 of 12
   if( !xP->parent )
   {
      T->root = xPL;
   }
   else if( xP == xP->parent->right )
   {
      xP->parent->right = xPL;
   }
   else /* xP == xP->parent->left */
   {
      xP->parent->left = xPL;
   }

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

__forceinline
static
void
__fastcall
RightRight2DeleteRotate
(
   binaryTree* T,
   BinaryTreeNode* xP
)
{
   BinaryTreeNode* xPL  = xP->left;
   BinaryTreeNode* xPLR = xPL->right;

   // 1 of 6
   if( xPLR->right )
   {
      xPLR->right->parent = xP;
   }

   // 2 of 6
   xP->left = xPLR->right;

   // 3 of 6
   if( !xP->parent )
   {
      T->root = xPL;
   }
   else if( xP == xP->parent->right )
   {
      xP->parent->right = xPL;
   }
   else /* xP == xP->parent->left */
   {
      xP->parent->left = xPL;
   }

   // 4 of 6
   xPL->parent = xP->parent;

   // 5 of 6
   xP->parent = xPLR;

   // 6 of 6
   xPLR->right = xP;
}

__forceinline
static
void
__fastcall
LeftRight2DeleteRotate
(
   binaryTree* T,
   BinaryTreeNode* xP
)
{
   BinaryTreeNode* xPL  = xP->left;
   BinaryTreeNode* xPLR = xPL->right;

   // 1 of 10
   if( xPLR->right )
   {
      xPLR->right->parent = xP;
   }

   // 2 of 10
   xP->left = xPLR->right;

   // 3 of 10
   if( xPLR->left )
   {
      xPLR->left->parent = xPL;
   }

   // 4 of 10
   xPL->right = xPLR->left;

   // 5 of 10
   xPL->parent = xPLR;

   // 6 of 10
   xPLR->left = xPL;

   // 7 of 10
   if( !xP->parent )
   {
      T->root = xPLR;
   }
   else if( xP == xP->parent->right )
   {
      xP->parent->right = xPLR;
   }
   else /* xP == xP->parent->left */
   {
      xP->parent->left = xPLR;
   }

   // 8 of 10
   xPLR->parent = xP->parent;

   // 9 of 10
   xP->parent = xPLR;

   // 10 of 10
   xPLR->right = xP;
}

__forceinline
static
void
__fastcall
BinInsert
(
   binaryTree* T,
   BinaryTreeNode* x
)
{
   BinaryTreeNode* y;
   BinaryTreeNode* xP;

   TreeInsert( T, x );

   x->color = RED;

   while( x != T->root && ( xP = x->parent )->color == RED )
   {
      if( xP == xP->parent->left )
      {
         y = xP->parent->right;

         if( y && y->color == RED )
         {
            xP->color = BLACK;

            y->color = BLACK;

            xP->parent->color = RED;

            x = xP->parent;
         }
         else
         {
            xP->parent->color = RED;

            if( x == xP->right )
            {
               x->color = BLACK;

               LeftRight1InsertRotate( T, x );

               x = x->left;
            }
            else
            {            
               xP->color = BLACK;   

               RightRotate( T, xP->parent );
            }
         }
      }
      else
      {
         y = xP->parent->left;

         if( y && y->color == RED )
         {
            xP->color = BLACK;

            y->color = BLACK;

            xP->parent->color = RED;

            x = xP->parent;
         }
         else
         {
            xP->parent->color = RED;

            if( x == xP->left )
            {
               x->color = BLACK;

               RightLeft2InsertRotate( T, x );

               x = x->right;
            }
            else
            {
               xP->color = BLACK;

               LeftRotate( T, xP->parent );
            }
         }
      }
   }

   T->root->color = BLACK;
}

int
__fastcall
bintree::insert
(
   void *  Object,
   binaryTreeCompare LessThan
)
{
   binaryTree* T = ( binaryTree* ) this;

   BinaryTreeNode* x;

   if( !T || !Object || T->NumberOfNodes >= T->MaxNumberOfNodes )
   {
      // BinTreeInsert(...) bad params
      _log( "error" );
      return RETURN_ERROR;
   }

   if( LessThan )
   {
      T->LessThan = LessThan;
   }

   if( !T->LessThan )
   {
      // BinTreeInsert(...) NIL binaryTreeCompare function
      _log( "error" );
      return RETURN_ERROR;
   }

   x = ( BinaryTreeNode* ) ( *T->MemoryManagerArrayCurrent++ );

   x->left  = 0;
   x->right = 0;

   if( !x )
   {
      // BinTreeInsert(...) bad memory allocation
      _log( "error" );
      return RETURN_ERROR;
   }

   memcpy( x->object, Object, T->SizeOfClientExact );

   BinInsert( T, x );

   T->NumberOfNodes++;

   return RETURN_OK;
}

__forceinline
static
BinaryTreeNode*
__fastcall
TreeMinimum
(
   BinaryTreeNode* x
)
{
   while( x->left )
   {
      x = x->left;
   }

   return x;
}

__forceinline
static
BinaryTreeNode*
__fastcall
TreeMaximum
(
   BinaryTreeNode* x
)
{
   while( x->right )
   {
      x = x->right;
   }

   return x;
}

//
// GetGreatest - An int which if TRUE, causes the greatest POTYPE
//               to be returned.  If FALSE, it causes the the least POTYPE
//               value to be returned.
//

int
__fastcall
bintree::getExtrema
(
   int GetGreatest,
   void *     ObjectReturn
)
{
   binaryTree* Head = ( binaryTree* ) this;

   BinaryTreeNode* Node = 0;

   if( !Head || ( GetGreatest != TRUE && GetGreatest != FALSE ) )
   {
      // BinGetExtrema(...) bad params
      _log( "error" );
      return RETURN_ERROR;
   }

   if( GetGreatest == FALSE )
   {
      if( Head->root )
      {
         Node = TreeMinimum( Head->root );
      }
   }
   else /* GetGreatest == TRUE */
   {
      if( Head->root )
      {
         Node = TreeMaximum( Head->root );
      }
   }

   if( !Node )
   {
      // BinGetExtrema(...) empty tree
      return RETURN_ERROR;
   }

   if( ObjectReturn )
   {
      memcpy( ObjectReturn, Node->object, Head->SizeOfClientExact );
   }

   return RETURN_OK;
}

__forceinline
static
BinaryTreeNode*
__fastcall
TreeSuccessor
(
   BinaryTreeNode* x
)
{
   BinaryTreeNode* y;

   if( x->right )
   {
      return TreeMinimum( x->right );
   }

   y = x->parent;

   while( y && x == y->right )
   {
      x = y;

      y = y->parent;
   }

   return y;
}

__forceinline
static
void
__fastcall
BinDeleteFixup
(
   binaryTree* T,
   BinaryTreeNode* x
)
{
   BinaryTreeNode* w;
   BinaryTreeNode* xP;

   while( x != T->root && x->color == BLACK )
   {
      xP = x->parent;

      if( x == xP->left )
      {
         w = xP->right;

         if( w->color == RED )
         {
            // prestep
            w = w->left;

            if( ( !w->left || w->left->color == BLACK ) &&
                ( !w->right || w->right->color == BLACK )
              )
            {
               // prestep
               w = xP->right;

               // step 1 of 2
               w->color = BLACK;

               xP->color = RED;

               LeftRotate( T, xP );

               w = xP->right;

               // step 2 of 2
               w->color = RED;

               x = xP;
            }
            else if( !w->right || w->right->color == BLACK )
            {
               // prestep
               w = xP->right;

               // step 1 of 4
               w->color = BLACK;

               xP->color = RED;

               // step 2 of 4
               LeftRightLeft1DeleteRotate( T, xP );

               // step 3 of 4
               w = xP->parent;

               w->color = xP->color;

               xP->color = BLACK;

               w->right->color = BLACK;

               // step 4 of 4
               x = T->root;
            }
            else
            {
               // prestep
               w = xP->right;

               // step 1 of 3
               w->color = BLACK;

               xP->color = RED;

               LeftLeft1DeleteRotate( T, xP );

               w = xP->parent;

               // step 2 of 3
               w->color = xP->color;

               xP->color = BLACK;

               w->right->color = BLACK;

               // step 3 of 3
               x = T->root;
            }
         }
         else /* w->color == BLACK */
         {
            if( ( !w->left || w->left->color == BLACK ) &&
                ( !w->right || w->right->color == BLACK )
              )
            {
               // step 1 of 1
               w->color = RED;

               x = xP;
            }
            else if( !w->right || w->right->color == BLACK )
            {
               // step 1 of 3
               w->left->color = BLACK;

               w->color = RED;

               RightLeft1DeleteRotate( T, xP );

               w = xP->parent;

               // step 2 of 3
               w->color = xP->color;

               xP->color = BLACK;

               w->right->color = BLACK;

               // step 3 of 3
               x = T->root;
            }
            else
            {
               // step 1 of 2
               w->color = xP->color;

               xP->color = BLACK;

               w->right->color = BLACK;

               LeftRotate( T, xP );

               // step 2 of 2
               x = T->root;
            }
         }
      }
      else /* x == xP->right */
      {
         w = xP->left;

         if( w->color == RED )
         {
            // prestep
            w = w->right;

            if( ( !w->right || w->right->color == BLACK ) &&
                ( !w->left || w->left->color == BLACK )
              )
            {
               // prestep
               w = xP->left;

               // step 1 of 2
               w->color = BLACK;

               xP->color = RED;

               RightRotate( T, xP );

               w = xP->left;

               // step 2 of 2
               w->color = RED;

               x = xP;
            }
            else if( !w->left || w->left->color == BLACK )
            {
               // prestep
               w = xP->left;

               // step 1 of 4
               w->color = BLACK;

               xP->color = RED;

               // step 2 of 4
               RightLeftRight2DeleteRotate( T, xP );

               // step 3 of 4
               w = xP->parent;

               w->color = xP->color;

               xP->color = BLACK;

               w->left->color = BLACK;

               // step 4 of 4
               x = T->root;
            }
            else
            {
               // prestep
               w = xP->left;

               // step 1 of 3
               w->color = BLACK;

               xP->color = RED;

               RightRight2DeleteRotate( T, xP );

               w = xP->parent;

               // step 2 of 3
               w->color = xP->color;

               xP->color = BLACK;

               w->left->color = BLACK;

               // step 3 of 3
               x = T->root;
            }
         }
         else /* w->color == BLACK */
         {
            if( ( !w->right || w->right->color == BLACK ) &&
                ( !w->left || w->left->color == BLACK )
              )
            {
               // step 1 of 1
               w->color = RED;

               x = xP;
            }
            else if( !w->left || w->left->color == BLACK )
            {
               // step 1 of 3
               w->right->color = BLACK;

               w->color = RED;

               LeftRight2DeleteRotate( T, xP );

               w = xP->parent;

               // step 2 of 3
               w->color = xP->color;

               xP->color = BLACK;

               w->left->color = BLACK;

               // step 3 of 3
               x = T->root;
            }
            else
            {
               // step 1 of 2
               w->color = xP->color;

               xP->color = BLACK;

               w->left->color = BLACK;

               RightRotate( T, xP );

               // step 2 of 2
               x = T->root;
            }
         }
      }
   }

   x->color = BLACK;
}

// we are swapping which node will be removed from the tree, so there's no rotation
static bool BinSwapNodes(binaryTree* tree, BinaryTreeNode* remove, BinaryTreeNode* insert)
{
	bool result = false;

	if( !tree || !remove || !insert || insert == remove)
		goto returnLabel;

	if( remove->parent )
	{
		if( remove == remove->parent->left )
		{
			remove->parent->left = insert;
		}
		else
		{
			remove->parent->right = insert;
		}
	}

	if( remove->left )
	{
		remove->left->parent = insert;
	}

	if( remove->right )
	{
		remove->right->parent = insert;
	}

	// god why no sentinel
	if( remove == tree->root )
	{
		tree->root = insert;
	}

	insert->parent = remove->parent;
	insert->left  = remove->left;
	insert->right = remove->right;

	insert->color = remove->color;
	
	result = true;

returnLabel:

	return result;
}

__forceinline
static
BinaryTreeNode*
__fastcall
BinDelete
(
   binaryTree* T,
   BinaryTreeNode* z
)
{
   int Color;

   // Sentinel {
   BinaryTreeNode* T_Nil = T->nil;
   // Sentinel }

   BinaryTreeNode* x;
   BinaryTreeNode* y;

   if( !z->left || !z->right )
   {
      y = z;
   }
   else
   {
      y = TreeSuccessor( z );
   }

   // Sentinel {
   T_Nil->parent = y;

   T_Nil->color = BLACK;

   if( !y->left )
   {
      y->left = T_Nil;
   }

   if( !y->right )
   {
      y->right = T_Nil;
   }
   // Sentinel }

   // Sentinel {
   if( y->left != T_Nil )
   // Sentinel }
   {
      x = y->left;
   }
   else
   {
      x = y->right;
   }

   x->parent = y->parent;

   if( !y->parent )
   {
      T->root = x;
   }
   else if( y == y->parent->left )
   {
      y->parent->left = x;
   }
   else
   {
      y->parent->right = x;
   }

   Color = y->color;

   if( y != z )
   {
      // the condition for when to swap nodes instead of copying client data
	  // should be based on empirical testing, otherwise it is arbitrary
      bool swapNodesInsteadOfCopyingClientData =
	     (T->SizeOfClientAligned > sizeof( BinaryTreeNode ) * 4);

      // swap nodes instead of copying client data, so we are O(1) instead of
	  // O(SizeOfClient)
      if(swapNodesInsteadOfCopyingClientData && BinSwapNodes(T, z/*remove*/, y/*insert*) )
      {
         y = z;
      }
      else // copyClientDataInsteadOfSwappingNodes
      {
         // copy all fields besides left right parent color
         memcpy( z->object, y->object, T->SizeOfClientAligned );
      }
   }

   if( Color == BLACK )
   {
      BinDeleteFixup( T, x );
   }

   if( T->NumberOfNodes == 1 )
   {
      T->root = 0;
   }
   // Sentinel {
   else if( T_Nil->parent->left == T_Nil )
   {
      T_Nil->parent->left = 0;
   }
   else if( T_Nil->parent->right == T_Nil )
   {
      T_Nil->parent->right = 0;
   }

   T_Nil->left  = 0;
   T_Nil->right = 0;
   // Sentinel }

   return y;
}

__forceinline
static
BinaryTreeNode*
__fastcall
TreeSearch
(
   BinaryTreeNode* x,
   void *        k,
   binaryTreeCompare       LessThan,
   binaryTreeEquivalence   EqualTo
)
{
   while( x && !EqualTo( k, x->object ) )
   {
      if( LessThan( k, x->object ) )
      {
         x = x->left;
      }
      else
      {
         x = x->right;
      }
   }

   return x;
}

int
__fastcall
bintree::remove
(
   void *      Object1,
   binaryTreeEquivalence EqualTo,
   void *      ObjectReturn
)
{
   binaryTree* T = ( binaryTree* ) this;

   BinaryTreeNode* t;
   BinaryTreeNode* z;

   if( !T || !Object1 || T->NumberOfNodes <= 0 )
   {
      // BinTreeRemove(...) bad params
      _log( "error" );
      return RETURN_ERROR;
   }

   if( EqualTo )
   {
      T->EqualTo = EqualTo;
   }

   if( !T->EqualTo )
   {
      // BinTreeRemove(...) NIL binaryTreeEquivalence function
      _log( "error" );
      return RETURN_ERROR;
   }

   z = TreeSearch( T->root, Object1, T->LessThan, T->EqualTo );

   if( !z )
   {
      // BinTreeRemove(...) TreeSearch(...) cannot find Object in tree
      _log( "error" );
      return RETURN_ERROR;
   }

   if( ObjectReturn )
   {
      memcpy( ObjectReturn, z->object, T->SizeOfClientExact );
   }

   t = BinDelete( T, z );

   z = t;

   if( !z )
   {
      // BinTreeRemove(...) BINDelete(...) cannot find Object in tree
      _log( "error" );
      return RETURN_ERROR;
   }

   * ( --T->MemoryManagerArrayCurrent ) = ( char * ) z;

   T->NumberOfNodes--;

   return RETURN_OK;
}

int
__fastcall
bintree::find
(
   void *      Object1,
   binaryTreeEquivalence EqualTo,
   void *      ObjectReturn
)
{
   binaryTree* Head = ( binaryTree* ) this;

   BinaryTreeNode* Node;

   if( !Head || !Object1 )
   {
      // BinTreeFind(...) bad params
      _log( "error" );
      return RETURN_ERROR;
   }

   if( EqualTo )
   {
      Head->EqualTo = EqualTo;
   }

   if( !Head->EqualTo )
   {
      // BinTreeFind(...) NIL binaryTreeEquivalence function
      _log( "error" );
      return RETURN_ERROR;
   }

   Node = TreeSearch( Head->root, Object1, Head->LessThan, Head->EqualTo );

   if( Node )
   {
      if( ObjectReturn )
      {
         memcpy( ObjectReturn, Node->object, Head->SizeOfClientExact );
      }

      return RETURN_OK;
   }

   return RETURN_ERROR;
}

int
__fastcall
bintree::reset
(
)
{
   binaryTree* Head = ( binaryTree* ) this;

   if( Head )
   {
      char * Memory = ( char * ) Head->TraverseArrayStart;

      int MemoryArrayPointerSize = sizeof( char * ) * Head->MaxNumberOfNodes;

      int loop;

      Head->NumberOfNodes = 0;

      Memory += MemoryArrayPointerSize;

      Head->MemoryManagerArrayCurrent = ( char ** ) Memory;

      Memory += MemoryArrayPointerSize;

      for( loop = 0; loop < Head->MaxNumberOfNodes; loop++ )
      {
         Head->MemoryManagerArrayCurrent[ loop ] = Memory;

         Memory += Head->SizeOfClientAligned + sizeof( BinaryTreeNode );
      }

      Head->root = 0;
      
      return RETURN_OK;
   }

	// BinTreeReset(...) bad params
   _log( "error" );
   return RETURN_ERROR;
}

int
__fastcall
bintree::term
(
)
{
   binaryTree* Head = ( binaryTree* ) this;

   if( Head )
   {
      memset( Head, 0, Head->MemoryTotalSize );

      free( Head );

      return RETURN_OK;
   }

   // BinTreeTerminate(...) bad params
   _log( "error" );
   return RETURN_ERROR;
}

// Preorder is fully optimized
__forceinline
static
void
__fastcall
IterativePreorderTreeTraverse
(
   binaryTree* Head,
   BinaryTreeNode* Node,
   binaryTreeEvaluate      ClientEvaluate
)
{
   // PSTACK Stack = InitStack( );
   BinaryTreeNode** StackTraverseArrayStart = Head->TraverseArrayStart;
   BinaryTreeNode** StackTraverseArrayCurrentTop = StackTraverseArrayStart;

   BinaryTreeNode* LeftChild = 0;
   BinaryTreeNode* RightChild = 0;

   while( 1 )
   {
      if( ClientEvaluate( Node->object ) )
      {
         break;
      }

      LeftChild = Node->left;
      RightChild = Node->right;

      if( RightChild )
      {
         if( LeftChild )
         {
            // Stack->Push( RightChild );
            *StackTraverseArrayCurrentTop++ = RightChild;

            // Stack->Push( LeftChild );
            // Node = Stack->Pop( );
            Node = LeftChild;
         }
         else /* !Node->left */
         {
            // Stack->Push( RightChild );
            // Node = Stack->Pop( );
            Node = RightChild;
         }
      }
      else if( LeftChild )
      {
         // Stack->Push( LeftChild );
         // Node = Stack->Pop( );
         Node = LeftChild;
      }
      else
      {
         // if ( Stack->Empty( ) == TRUE )
         if( StackTraverseArrayCurrentTop == StackTraverseArrayStart )
         {
            break;
         }

         // Node = Stack->Pop( );
         Node = * ( --StackTraverseArrayCurrentTop );
      }
   }
}

// Inorder requires one extra optimization-
// When the left nodes are pushed on the stack,
// a left node is immediately popped off of the stack
// after you break out of the inner loop.
__forceinline
static
void
__fastcall
IterativeInorderTreeTraverse
(
   binaryTree* Head,
   BinaryTreeNode* Node,
   binaryTreeEvaluate      ClientEvaluate
)
{
   // PSTACK Stack = InitStack( );
   BinaryTreeNode** StackTraverseArrayStart = Head->TraverseArrayStart;
   BinaryTreeNode** StackTraverseArrayCurrentTop = StackTraverseArrayStart;

   while( 1 )
   {
      while( Node )
      {
         // Stack->Push( Node );
         *StackTraverseArrayCurrentTop++ = Node;

         Node = Node->left;
      }

      // if ( Stack->Empty( ) == TRUE )
      if( StackTraverseArrayCurrentTop == StackTraverseArrayStart )
      {
         break;
      }

      // Node = Stack->Pop( );
      Node = * ( --StackTraverseArrayCurrentTop );

      if( ClientEvaluate( Node->object ) )
      {
         break;
      }

      Node = Node->right;
   }
}

// ! I have no idea if Postorder is fully optimized or not!
// I optimized it alot, but I am still not sure if it is fully optimized.
// Function courtesy of Bruce Mcquistan ( brucemc@digipen.edu )
__forceinline
static
void
__fastcall
IterativePostorderTreeTraverse
(
   binaryTree* Head,
   BinaryTreeNode* Node,
   binaryTreeEvaluate      ClientEvaluate
)
{
   // PSTACK Stack = InitStack( );
   BinaryTreeNode** StackTraverseArrayStart = Head->TraverseArrayStart;
   BinaryTreeNode** StackTraverseArrayCurrentTop = StackTraverseArrayStart;

   BinaryTreeNode* NodePushed = 0
   BinaryTreeNode* RightChild = 0;

   while( 1 )
   {
      postorder1:

      do
      {
         // Stack->Push( Node );
         *StackTraverseArrayCurrentTop++ = Node;

         Node = Node->left;

      }while( Node );

      postorder2:

      // if ( Stack->Empty( ) == TRUE )
      if( StackTraverseArrayCurrentTop == StackTraverseArrayStart )
      {
         break;
      }

      // Node = Stack->Pop( );
      Node = * ( --StackTraverseArrayCurrentTop );

      RightChild = Node->right;

      if( RightChild && ( RightChild != NodePushed ) )
      {
         // Stack->Push( Node );
         *StackTraverseArrayCurrentTop++ = Node;

         NodePushed = RightChild;

         Node = RightChild;

         goto postorder1;
      }
      else
      {
         if( ClientEvaluate( Node->object ) )
         {
            break;
         }

         NodePushed = Node;

         Node = 0;

         goto postorder2;
      }
   }
}

// Levelorder is fully optimized
__forceinline
static
void
__fastcall
IterativeLevelorderTreeTraverse
(
   binaryTree* Head,
   BinaryTreeNode* Node,
   binaryTreeEvaluate      ClientEvaluate
)
{
   // PQUEUE Queue = InitQueue( );
   BinaryTreeNode** QueueTraverseArrayCurrentFront = Head->TraverseArrayStart;
   BinaryTreeNode** QueueTraverseArrayCurrentBack = QueueTraverseArrayCurrentFront;

   BinaryTreeNode* LeftChild = 0;
   BinaryTreeNode* RightChild = 0;

   *QueueTraverseArrayCurrentBack++ = Node;

   // while( Queue->Empty() != TRUE )
   while( QueueTraverseArrayCurrentFront != QueueTraverseArrayCurrentBack )
   {
      // Queue->Get()
      Node = *QueueTraverseArrayCurrentFront++;

      if( ClientEvaluate( Node->object ) )
      {
         break;
      }

      LeftChild = Node->left;
      RightChild = Node->right;

      if( LeftChild )
      {
         // Queue->Put( LeftChild );
         *QueueTraverseArrayCurrentBack++ = LeftChild;
      }

      if( RightChild )
      {
         // Queue->Put( RightChild );
         *QueueTraverseArrayCurrentBack++ = RightChild;
      }
   }
}

int
__fastcall
bintree::dump
(
   binaryTreeEvaluate ClientEvaluate,
   ORDER    TraversalOrder
)
{
   binaryTree* Head = ( binaryTree* ) this;

   if( ( !Head ) ||
       ( ( !ClientEvaluate ) && ( !Head->ClientEvaluate ) ) ||
       ( TraversalOrder < PREORDER ) ||
       ( TraversalOrder > LEVELORDER )
     )
   {
      // BinTreeDump(...) bad params
      _log( "error" );
      return RETURN_ERROR;
   }

   if( ClientEvaluate )
   {
      Head->ClientEvaluate = ClientEvaluate;
   }

   if( Head->root )
   {
      switch( TraversalOrder )
      {
         case PREORDER:   IterativePreorderTreeTraverse( Head, Head->root, Head->ClientEvaluate ); break;
         case INORDER:    IterativeInorderTreeTraverse( Head, Head->root, Head->ClientEvaluate ); break;
         case POSTORDER:  IterativePostorderTreeTraverse( Head, Head->root, Head->ClientEvaluate ); break;
         case LEVELORDER: IterativeLevelorderTreeTraverse( Head, Head->root, Head->ClientEvaluate ); break;
      }
   }

   return RETURN_OK;
}

int
__fastcall
bintree::isEmpty
(
   int* NumberOfClientObjects
)
{
   binaryTree* Head = ( binaryTree* ) this;

   if( !Head )
   {
      // BinTreeIsEmpty(...) bad params
      _log( "error" );
      return RETURN_ERROR;
   }

   if( NumberOfClientObjects )
   {
      *NumberOfClientObjects = Head->NumberOfNodes;
   }

   return Head->NumberOfNodes == 0;
}

bintree *
__fastcall
bintree::init
(
   int MaxNumberOfObjects,
   int SizeOfEachObjectExact,
   binaryTreeCompare    LessThan
)
{

///////////////////////////////////////////////////////////////////////////////////////////////////////
   binaryTree* Head;

   char * Memory;

   int MemoryArrayPointerSize;
   int MemoryPoolSize;
   int MemoryTotalSize;

   int SizeOfEachObjectAligned;

   int loop;
///////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////
   if( MaxNumberOfObjects <= 0 || SizeOfEachObjectExact <= 0 || !LessThan )
   {
      // BinTreeInit(...) bad params
      _log( "error" );
      return 0;
   }
///////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////
   // Align the client memory (4 byte alignment, also known as granularity alignment)
   SizeOfEachObjectAligned = SizeOfEachObjectExact + SizeOfEachObjectExact % 4;

   // We need the pointer pools for the traversing stack and for the memory manager stack.
   MemoryArrayPointerSize = sizeof( char * ) * MaxNumberOfObjects;

   // We need the Node pool for the memory manager, with the size of the nodes
   // expanded to include the granularity aligned client object sizes.
   MemoryPoolSize = ( SizeOfEachObjectAligned + sizeof( BinaryTreeNode ) ) * MaxNumberOfObjects;
///////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////
   // Need enough memory for the head and the sentinel node
   MemoryTotalSize = sizeof( binaryTree ) + sizeof( BinaryTreeNode );

   // Need two pointer pools, one for the memory manager, and another pool for the traversing stack;
   MemoryTotalSize += MemoryArrayPointerSize * 2;

   // Add the actual node pool to the total required allocation size.
   MemoryTotalSize += MemoryPoolSize;

   // Make sure the memory allocation is a multiple of 8 for quicker zero-ing of the
   // memory in the BinTreeTerm(...) function (a couple microseconds faster).
   MemoryTotalSize += MemoryTotalSize % 8;
///////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////
   // Actually allocate the memory we need
   Head = ( binaryTree* ) malloc( MemoryTotalSize );

   if( !Head )
   {
      // BinTreeInit(...) bad memory allocation
      _log( "error" );
      return 0;
   }

   memset( Head, 0, MemoryTotalSize );
///////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////
   Memory = ( char* ) Head;

   Memory += sizeof( binaryTree );

   Head->nil = ( BinaryTreeNode* ) Memory;

   Memory += sizeof( BinaryTreeNode );

   Head->TraverseArrayStart = ( BinaryTreeNode** ) Memory;

   Memory += MemoryArrayPointerSize;

   Head->MemoryManagerArrayCurrent = ( char ** ) Memory;

   Memory += MemoryArrayPointerSize;

   for( loop = 0; loop < MaxNumberOfObjects; loop++ )
   {
      Head->MemoryManagerArrayCurrent[ loop ] = Memory;

      Memory += SizeOfEachObjectAligned + sizeof( BinaryTreeNode );
   }
///////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////
   Head->LessThan = LessThan;

   Head->MaxNumberOfNodes = MaxNumberOfObjects;

   Head->SizeOfClientExact   = SizeOfEachObjectExact;
   Head->SizeOfClientAligned = SizeOfEachObjectAligned;

   Head->MemoryTotalSize = MemoryTotalSize;
///////////////////////////////////////////////////////////////////////////////////////////////////////


   return ( bintree * ) Head;
}

bintree::bintree
(
)
{
}

bintree::bintree
(
   bintree &
)
{
}

bintree &
bintree::operator=
(
   bintree &
)
{
   return this[0];
}

#ifdef __cplusplus
   }
#endif