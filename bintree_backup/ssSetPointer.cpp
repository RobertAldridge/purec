
// File Name: ptrtrack.cpp
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

#include "ptrtrack.h"

typedef struct __BINTREE_HEAD * PBINTREE_HEAD;

typedef int INDEX_TYPE;
typedef INDEX_TYPE * PINDEX_TYPE;

#include "ptrpriv.h"
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

const int ptrtrack::ok = 0;
const int ptrtrack::error = -1;

const int ptrtrack::empty = 1;

__forceinline
static
void
__fastcall
TreeInsert
(
   PBINTREE_HEAD T,
   PBINTREE_NODE z
)
{
   PBINTREE_NODE x = T->Root;
   PBINTREE_NODE y = 0;

   while( x )
   {
      y = x;

      if( z->Object < x->Object )
      {
         x = x->LeftChild;
      }
      else
      {
         x = x->RightChild;
      }
   }

   z->Parent = y;

   if( !y )
   {
      T->Root = z;
   }
   else if( z->Object < y->Object )
   {
      y->LeftChild = z;
   }
   else
   {
      y->RightChild = z;
   }
}

__forceinline
static
void
__fastcall
LeftRotate
(
   PBINTREE_HEAD T,
   PBINTREE_NODE x
)
{
   PBINTREE_NODE y = x->RightChild;

   // 1 of 6
   x->RightChild = y->LeftChild;

   // 2 of 6
   if( y->LeftChild )
   {
      y->LeftChild->Parent = x;
   }

   // 3 of 6
   y->Parent = x->Parent;

   // 4 of 6
   if( !x->Parent )
   {
      T->Root = y;
   }
   else if( x == x->Parent->LeftChild )
   {
      x->Parent->LeftChild = y;
   }
   else /* x == x->Parent->RightChild */
   {
      x->Parent->RightChild = y;
   }

   // 5 of 6
   y->LeftChild = x;

   // 6 of 6
   x->Parent = y;
}

__forceinline
static
void
__fastcall
RightRotate
(
   PBINTREE_HEAD T,
   PBINTREE_NODE x
)
{
   PBINTREE_NODE y = x->LeftChild;

   // 1 of 6
   x->LeftChild = y->RightChild;

   // 2 of 6
   if( y->RightChild )
   {
      y->RightChild->Parent = x;
   }

   // 3 of 6
   y->Parent = x->Parent;

   // 4 of 6
   if( !x->Parent )
   {
      T->Root = y;
   }
   else if( x == x->Parent->RightChild )
   {
      x->Parent->RightChild = y;
   }
   else /* x == x->Parent->LeftChild */
   {
      x->Parent->LeftChild = y;
   }

   // 5 of 6
   y->RightChild = x;

   // 6 of 6
   x->Parent = y;
}

__forceinline
static
void
__fastcall
LeftRight1InsertRotate
(
   PBINTREE_HEAD T,
   PBINTREE_NODE x
)
{
   PBINTREE_NODE xP  = x->Parent;
   PBINTREE_NODE xPP = xP->Parent;

   // 1 of 10
   if( x->LeftChild )
   {
      x->LeftChild->Parent = xP;
   }

   // 2 of 10
   xP->RightChild = x->LeftChild;

   // 3 of 10
   if( x->RightChild )
   {
      x->RightChild->Parent = xPP;
   }

   // 4 of 10
   xPP->LeftChild = x->RightChild;

   // 5 of 10
   if( !xPP->Parent )
   {
      T->Root = x;
   }
   else if( xPP == xPP->Parent->RightChild )
   {
      xPP->Parent->RightChild = x;
   }
   else /* xPP == xPP->Parent->LeftChild */
   {
      xPP->Parent->LeftChild = x;
   }

   // 6 of 10
   x->LeftChild = xP;

   // 7 of 10
   x->RightChild = xPP;

   // 8 of 10
   x->Parent = xPP->Parent;

   // 9 of 10
   xP->Parent = x;

   // 10 of 10
   xPP->Parent = x;
}

__forceinline
static
void
__fastcall
RightLeft2InsertRotate
(
   PBINTREE_HEAD T,
   PBINTREE_NODE x
)
{
   PBINTREE_NODE xP  = x->Parent;
   PBINTREE_NODE xPP = xP->Parent;

   // 1 of 10
   if( x->RightChild )
   {
      x->RightChild->Parent = xP;
   }

   // 2 of 10
   xP->LeftChild = x->RightChild;

   // 3 of 10
   if( x->LeftChild )
   {
      x->LeftChild->Parent = xPP;
   }

   // 4 of 10
   xPP->RightChild = x->LeftChild;

   // 5 of 10
   if( !xPP->Parent )
   {
      T->Root = x;
   }
   else if( xPP == xPP->Parent->LeftChild )
   {
      xPP->Parent->LeftChild = x;
   }
   else /* xPP == xPP->Parent->RightChild */
   {
      xPP->Parent->RightChild = x;
   }

   // 6 of 10
   x->RightChild = xP;

   // 7 of 10
   x->LeftChild = xPP;

   // 8 of 10
   x->Parent = xPP->Parent;

   // 9 of 10
   xP->Parent = x;

   // 10 of 10
   xPP->Parent = x;
}

__forceinline
static
void
__fastcall
LeftRightLeft1DeleteRotate
(
   PBINTREE_HEAD T,
   PBINTREE_NODE xP
)
{
   PBINTREE_NODE xPR   = xP->RightChild;
   PBINTREE_NODE xPRL  = xPR->LeftChild;
   PBINTREE_NODE xPRLL = xPRL->LeftChild;

   // 1 of 12
   xP->RightChild = xPRLL->LeftChild;

   // 2 of 12
   if( xPRLL->LeftChild )
   {
      xPRLL->LeftChild->Parent = xP;
   }

   // 3 of 12
   xPRL->LeftChild = xPRLL->RightChild;

   // 4 of 12
   if( xPRLL->RightChild )
   {
      xPRLL->RightChild->Parent = xPRL;
   }

   // 5 of 12
   xPRL->Parent = xPRLL;

   // 6 of 12
   xPRLL->RightChild = xPRL;

   // 7 of 12
   if( !xP->Parent )
   {
      T->Root = xPR;
   }
   else if( xP == xP->Parent->LeftChild )
   {
      xP->Parent->LeftChild = xPR;
   }
   else /* xP == xP->Parent->RightChild */
   {
      xP->Parent->RightChild = xPR;
   }

   // 8 of 12
   xPR->Parent = xP->Parent;

   // 9 of 12
   xP->Parent = xPRLL;

   // 10 of 12
   xPRLL->LeftChild = xP;

   // 11 of 12
   xPR->LeftChild = xPRLL;

   // 12 of 12
   xPRLL->Parent = xPR;
}

__forceinline
static
void
__fastcall
LeftLeft1DeleteRotate
(
   PBINTREE_HEAD T,
   PBINTREE_NODE xP
)
{
   PBINTREE_NODE xPR  = xP->RightChild;
   PBINTREE_NODE xPRL = xPR->LeftChild;

   // 1 of 6
   if( xPRL->LeftChild )
   {
      xPRL->LeftChild->Parent = xP;
   }

   // 2 of 6
   xP->RightChild = xPRL->LeftChild;

   // 3 of 6
   if( !xP->Parent )
   {
      T->Root = xPR;
   }
   else if( xP == xP->Parent->LeftChild )
   {
      xP->Parent->LeftChild = xPR;
   }
   else /* xP == xP->Parent->RightChild */
   {
      xP->Parent->RightChild = xPR;
   }

   // 4 of 6
   xPR->Parent = xP->Parent;

   // 5 of 6
   xP->Parent = xPRL;

   // 6 of 6
   xPRL->LeftChild = xP;
}

__forceinline
static
void
__fastcall
RightLeft1DeleteRotate
(
   PBINTREE_HEAD T,
   PBINTREE_NODE xP
)
{
   PBINTREE_NODE xPR  = xP->RightChild;
   PBINTREE_NODE xPRL = xPR->LeftChild;

   // 1 of 10
   if( xPRL->LeftChild )
   {
      xPRL->LeftChild->Parent = xP;
   }

   // 2 of 10
   xP->RightChild = xPRL->LeftChild;

   // 3 of 10
   if( xPRL->RightChild )
   {
      xPRL->RightChild->Parent = xPR;
   }

   // 4 of 10
   xPR->LeftChild = xPRL->RightChild;

   // 5 of 10
   xPR->Parent = xPRL;

   // 6 of 10
   xPRL->RightChild = xPR;

   // 7 of 10
   if( !xP->Parent )
   {
      T->Root = xPRL;
   }
   else if( xP == xP->Parent->LeftChild )
   {
      xP->Parent->LeftChild = xPRL;
   }
   else /* xP == xP->Parent->RightChild */
   {
      xP->Parent->RightChild = xPRL;
   }

   // 8 of 10
   xPRL->Parent = xP->Parent;

   // 9 of 10
   xP->Parent = xPRL;

   // 10 of 10
   xPRL->LeftChild = xP;
}

__forceinline
static
void
__fastcall
RightLeftRight2DeleteRotate
(
   PBINTREE_HEAD T,
   PBINTREE_NODE xP
)
{
   PBINTREE_NODE xPL   = xP->LeftChild;
   PBINTREE_NODE xPLR  = xPL->RightChild;
   PBINTREE_NODE xPLRR = xPLR->RightChild;

   // 1 of 12
   xP->LeftChild = xPLRR->RightChild;

   // 2 of 12
   if( xPLRR->RightChild )
   {
      xPLRR->RightChild->Parent = xP;
   }

   // 3 of 12
   xPLR->RightChild = xPLRR->LeftChild;

   // 4 of 12
   if( xPLRR->LeftChild )
   {
      xPLRR->LeftChild->Parent = xPLR;
   }

   // 5 of 12
   xPLR->Parent = xPLRR;

   // 6 of 12
   xPLRR->LeftChild = xPLR;

   // 7 of 12
   if( !xP->Parent )
   {
      T->Root = xPL;
   }
   else if( xP == xP->Parent->RightChild )
   {
      xP->Parent->RightChild = xPL;
   }
   else /* xP == xP->Parent->LeftChild */
   {
      xP->Parent->LeftChild = xPL;
   }

   // 8 of 12
   xPL->Parent = xP->Parent;

   // 9 of 12
   xP->Parent = xPLRR;

   // 10 of 12
   xPLRR->RightChild = xP;

   // 11 of 12
   xPL->RightChild = xPLRR;

   // 12 of 12
   xPLRR->Parent = xPL;
}

__forceinline
static
void
__fastcall
RightRight2DeleteRotate
(
   PBINTREE_HEAD T,
   PBINTREE_NODE xP
)
{
   PBINTREE_NODE xPL  = xP->LeftChild;
   PBINTREE_NODE xPLR = xPL->RightChild;

   // 1 of 6
   if( xPLR->RightChild )
   {
      xPLR->RightChild->Parent = xP;
   }

   // 2 of 6
   xP->LeftChild = xPLR->RightChild;

   // 3 of 6
   if( !xP->Parent )
   {
      T->Root = xPL;
   }
   else if( xP == xP->Parent->RightChild )
   {
      xP->Parent->RightChild = xPL;
   }
   else /* xP == xP->Parent->LeftChild */
   {
      xP->Parent->LeftChild = xPL;
   }

   // 4 of 6
   xPL->Parent = xP->Parent;

   // 5 of 6
   xP->Parent = xPLR;

   // 6 of 6
   xPLR->RightChild = xP;
}

__forceinline
static
void
__fastcall
LeftRight2DeleteRotate
(
   PBINTREE_HEAD T,
   PBINTREE_NODE xP
)
{
   PBINTREE_NODE xPL  = xP->LeftChild;
   PBINTREE_NODE xPLR = xPL->RightChild;

   // 1 of 10
   if( xPLR->RightChild )
   {
      xPLR->RightChild->Parent = xP;
   }

   // 2 of 10
   xP->LeftChild = xPLR->RightChild;

   // 3 of 10
   if( xPLR->LeftChild )
   {
      xPLR->LeftChild->Parent = xPL;
   }

   // 4 of 10
   xPL->RightChild = xPLR->LeftChild;

   // 5 of 10
   xPL->Parent = xPLR;

   // 6 of 10
   xPLR->LeftChild = xPL;

   // 7 of 10
   if( !xP->Parent )
   {
      T->Root = xPLR;
   }
   else if( xP == xP->Parent->RightChild )
   {
      xP->Parent->RightChild = xPLR;
   }
   else /* xP == xP->Parent->LeftChild */
   {
      xP->Parent->LeftChild = xPLR;
   }

   // 8 of 10
   xPLR->Parent = xP->Parent;

   // 9 of 10
   xP->Parent = xPLR;

   // 10 of 10
   xPLR->RightChild = xP;
}

__forceinline
static
void
__fastcall
BinInsert
(
   PBINTREE_HEAD T,
   PBINTREE_NODE x
)
{
   PBINTREE_NODE y;
   PBINTREE_NODE xP;

   TreeInsert( T, x );

   x->Color = RED;

   while( x != T->Root && ( xP = x->Parent )->Color == RED )
   {
      if( xP == xP->Parent->LeftChild )
      {
         y = xP->Parent->RightChild;

         if( y && y->Color == RED )
         {
            xP->Color = BLACK;

            y->Color = BLACK;

            xP->Parent->Color = RED;

            x = xP->Parent;
         }
         else
         {
            xP->Parent->Color = RED;

            if( x == xP->RightChild )
            {
               x->Color = BLACK;

               LeftRight1InsertRotate( T, x );

               x = x->LeftChild;
            }
            else
            {
               xP->Color = BLACK;

               RightRotate( T, xP->Parent );
            }
         }
      }
      else
      {
         y = xP->Parent->LeftChild;

         if( y && y->Color == RED )
         {
            xP->Color = BLACK;

            y->Color = BLACK;

            xP->Parent->Color = RED;

            x = xP->Parent;
         }
         else
         {
            xP->Parent->Color = RED;

            if( x == xP->LeftChild )
            {
               x->Color = BLACK;

               RightLeft2InsertRotate( T, x );

               x = x->RightChild;
            }
            else
            {
               xP->Color = BLACK;

               LeftRotate( T, xP->Parent );
            }
         }
      }
   }

   T->Root->Color = BLACK;
}

INDEX_TYPE
__fastcall
ptrtrack::insert
(
   void * Object
)
{
   PBINTREE_HEAD T = ( PBINTREE_HEAD ) this;

   PBINTREE_NODE x;

   if( !T || !Object || T->NumberOfNodes >= T->MaxNumberOfNodes )
   {
      // BinTreeInsert(...) bad params
      _log( "error" );
      return RETURN_ERROR;
   }

   x = ( PBINTREE_NODE ) ( *T->MemoryManagerArrayCurrent++ );

   x->LeftChild  = 0;
   x->RightChild = 0;

   if( !x )
   {
      // BinTreeInsert(...) bad memory allocation
      _log( "error" );
      return RETURN_ERROR;
   }

   x->Object = Object;

   BinInsert( T, x );

   T->NumberOfNodes++;

   return RETURN_OK;
}

__forceinline
static
PBINTREE_NODE
__fastcall
TreeMinimum
(
   PBINTREE_NODE x
)
{
   while( x->LeftChild )
   {
      x = x->LeftChild;
   }

   return x;
}

__forceinline
static
PBINTREE_NODE
__fastcall
TreeSuccessor
(
   PBINTREE_NODE x
)
{
   PBINTREE_NODE y;

   if( x->RightChild )
   {
      return TreeMinimum( x->RightChild );
   }

   y = x->Parent;

   while( y && x == y->RightChild )
   {
      x = y;

      y = y->Parent;
   }

   return y;
}

__forceinline
static
void
__fastcall
BinDeleteFixup
(
   PBINTREE_HEAD T,
   PBINTREE_NODE x
)
{
   PBINTREE_NODE w;
   PBINTREE_NODE xP;

   while( x != T->Root && x->Color == BLACK )
   {
      xP = x->Parent;

      if( x == xP->LeftChild )
      {
         w = xP->RightChild;

         if( w->Color == RED )
         {
            // prestep
            w = w->LeftChild;

            if( ( !w->LeftChild || w->LeftChild->Color == BLACK ) &&
                ( !w->RightChild || w->RightChild->Color == BLACK )
              )
            {
               // prestep
               w = xP->RightChild;

               // step 1 of 2
               w->Color = BLACK;

               xP->Color = RED;

               LeftRotate( T, xP );

               w = xP->RightChild;

               // step 2 of 2
               w->Color = RED;

               x = xP;
            }
            else if( !w->RightChild || w->RightChild->Color == BLACK )
            {
               // prestep
               w = xP->RightChild;

               // step 1 of 4
               w->Color = BLACK;

               xP->Color = RED;

               // step 2 of 4
               LeftRightLeft1DeleteRotate( T, xP );

               // step 3 of 4
               w = xP->Parent;

               w->Color = xP->Color;

               xP->Color = BLACK;

               w->RightChild->Color = BLACK;

               // step 4 of 4
               x = T->Root;
            }
            else
            {
               // prestep
               w = xP->RightChild;

               // step 1 of 3
               w->Color = BLACK;

               xP->Color = RED;

               LeftLeft1DeleteRotate( T, xP );

               w = xP->Parent;

               // step 2 of 3
               w->Color = xP->Color;

               xP->Color = BLACK;

               w->RightChild->Color = BLACK;

               // step 3 of 3
               x = T->Root;
            }
         }
         else /* w->Color == BLACK */
         {
            if( ( !w->LeftChild || w->LeftChild->Color == BLACK ) &&
                ( !w->RightChild || w->RightChild->Color == BLACK )
              )
            {
               // step 1 of 1
               w->Color = RED;

               x = xP;
            }
            else if( !w->RightChild || w->RightChild->Color == BLACK )
            {
               // step 1 of 3
               w->LeftChild->Color = BLACK;

               w->Color = RED;

               RightLeft1DeleteRotate( T, xP );

               w = xP->Parent;

               // step 2 of 3
               w->Color = xP->Color;

               xP->Color = BLACK;

               w->RightChild->Color = BLACK;

               // step 3 of 3
               x = T->Root;
            }
            else
            {
               // step 1 of 2
               w->Color = xP->Color;

               xP->Color = BLACK;

               w->RightChild->Color = BLACK;

               LeftRotate( T, xP );

               // step 2 of 2
               x = T->Root;
            }
         }
      }
      else /* x == xP->RightChild */
      {
         w = xP->LeftChild;

         if( w->Color == RED )
         {
            // prestep
            w = w->RightChild;

            if( ( !w->RightChild || w->RightChild->Color == BLACK ) &&
                ( !w->LeftChild || w->LeftChild->Color == BLACK )
              )
            {
               // prestep
               w = xP->LeftChild;

               // step 1 of 2
               w->Color = BLACK;

               xP->Color = RED;

               RightRotate( T, xP );

               w = xP->LeftChild;

               // step 2 of 2
               w->Color = RED;

               x = xP;
            }
            else if( !w->LeftChild || w->LeftChild->Color == BLACK )
            {
               // prestep
               w = xP->LeftChild;

               // step 1 of 4
               w->Color = BLACK;

               xP->Color = RED;

               // step 2 of 4
               RightLeftRight2DeleteRotate( T, xP );

               // step 3 of 4
               w = xP->Parent;

               w->Color = xP->Color;

               xP->Color = BLACK;

               w->LeftChild->Color = BLACK;

               // step 4 of 4
               x = T->Root;
            }
            else
            {
               // prestep
               w = xP->LeftChild;

               // step 1 of 3
               w->Color = BLACK;

               xP->Color = RED;

               RightRight2DeleteRotate( T, xP );

               w = xP->Parent;

               // step 2 of 3
               w->Color = xP->Color;

               xP->Color = BLACK;

               w->LeftChild->Color = BLACK;

               // step 3 of 3
               x = T->Root;
            }
         }
         else /* w->Color == BLACK */
         {
            if( ( !w->RightChild || w->RightChild->Color == BLACK ) &&
                ( !w->LeftChild || w->LeftChild->Color == BLACK )
              )
            {
               // step 1 of 1
               w->Color = RED;

               x = xP;
            }
            else if( !w->LeftChild || w->LeftChild->Color == BLACK )
            {
               // step 1 of 3
               w->RightChild->Color = BLACK;

               w->Color = RED;

               LeftRight2DeleteRotate( T, xP );

               w = xP->Parent;

               // step 2 of 3
               w->Color = xP->Color;

               xP->Color = BLACK;

               w->LeftChild->Color = BLACK;

               // step 3 of 3
               x = T->Root;
            }
            else
            {
               // step 1 of 2
               w->Color = xP->Color;

               xP->Color = BLACK;

               w->LeftChild->Color = BLACK;

               RightRotate( T, xP );

               // step 2 of 2
               x = T->Root;
            }
         }
      }
   }

   x->Color = BLACK;
}

__forceinline
static
PBINTREE_NODE
__fastcall
BinDelete
(
   PBINTREE_HEAD T,
   PBINTREE_NODE z
)
{
   INDEX_TYPE Color;

   // Sentinel {
   PBINTREE_NODE T_Nil = T->Nil;
   // Sentinel }

   PBINTREE_NODE x;
   PBINTREE_NODE y;

   if( !z->LeftChild || !z->RightChild )
   {
      y = z;
   }
   else
   {
      y = TreeSuccessor( z );
   }

   // Sentinel {
   T_Nil->Parent = y;

   T_Nil->Color = BLACK;

   if( !y->LeftChild )
   {
      y->LeftChild = T_Nil;
   }

   if( !y->RightChild )
   {
      y->RightChild = T_Nil;
   }
   // Sentinel }

   // Sentinel {
   if( y->LeftChild != T_Nil )
   // Sentinel }
   {
      x = y->LeftChild;
   }
   else
   {
      x = y->RightChild;
   }

   x->Parent = y->Parent;

   if( !y->Parent )
   {
      T->Root = x;
   }
   else if( y == y->Parent->LeftChild )
   {
      y->Parent->LeftChild = x;
   }
   else
   {
      y->Parent->RightChild = x;
   }

   Color = y->Color;

   if( y != z )
   {
      // If y has other fields, copy them, too.
      z->Object = y->Object;
   }

   if( Color == BLACK )
   {
      BinDeleteFixup( T, x );
   }

   if( T->NumberOfNodes == 1 )
   {
      T->Root = 0;
   }
   // Sentinel {
   else if( T_Nil->Parent->LeftChild == T_Nil )
   {
      T_Nil->Parent->LeftChild = 0;
   }
   else if( T_Nil->Parent->RightChild == T_Nil )
   {
      T_Nil->Parent->RightChild = 0;
   }

   T_Nil->LeftChild  = 0;
   T_Nil->RightChild = 0;
   // Sentinel }

   return y;
}

__forceinline
static
PBINTREE_NODE
__fastcall
TreeSearch
(
   PBINTREE_NODE x,
   void *        k
)
{
   while( x && k != x->Object )
   {
      if( k < x->Object )
      {
         x = x->LeftChild;
      }
      else
      {
         x = x->RightChild;
      }
   }

   return x;
}

INDEX_TYPE
__fastcall
ptrtrack::remove
(
   void * Object1
)
{
   PBINTREE_HEAD T = ( PBINTREE_HEAD ) this;

   PBINTREE_NODE t;
   PBINTREE_NODE z;

   if( !T || !Object1 || T->NumberOfNodes <= 0 )
   {
      // BinTreeRemove(...) bad params
      _log( "error" );
      return RETURN_ERROR;
   }

   z = TreeSearch( T->Root, Object1 );

   if( !z )
   {
      // BinTreeRemove(...) TreeSearch(...) cannot find Object in tree
      return 1;
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

INDEX_TYPE
__fastcall
ptrtrack::find
(
   void * Object1
)
{
   PBINTREE_HEAD Head = ( PBINTREE_HEAD ) this;

   PBINTREE_NODE Node;

   if( !Head || !Object1 )
   {
      // BinTreeFind(...) bad params
      _log( "error" );
      return RETURN_ERROR;
   }

   Node = TreeSearch( Head->Root, Object1 );

   if( !Node )
   {
      return 1;
   }

   return RETURN_OK;
}

INDEX_TYPE
__fastcall
ptrtrack::reset
(
)
{
   PBINTREE_HEAD Head = ( PBINTREE_HEAD ) this;

   if( Head )
   {
      char * Memory = ( char * ) Head->Nil;

      Memory += sizeof( BINTREE_NODE );

      int MemoryArrayPointerSize = sizeof( char * ) * Head->MaxNumberOfNodes;

      int loop;

      Head->NumberOfNodes = 0;

      Head->MemoryManagerArrayCurrent = ( char ** ) Memory;

      Memory += MemoryArrayPointerSize;

      for( loop = 0; loop < Head->MaxNumberOfNodes; loop++ )
      {
         Head->MemoryManagerArrayCurrent[ loop ] = Memory;

         Memory += sizeof( BINTREE_NODE );
      }

      Head->Root = 0;

      return RETURN_OK;
   }

  // BinTreeReset(...) bad params
   _log( "error" );
   return RETURN_ERROR;
}

INDEX_TYPE
__fastcall
ptrtrack::term
(
)
{
   PBINTREE_HEAD Head = ( PBINTREE_HEAD ) this;

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

INDEX_TYPE
__fastcall
ptrtrack::isEmpty
(
)
{
   PBINTREE_HEAD Head = ( PBINTREE_HEAD ) this;

   if( !Head )
   {
      // BinTreeIsEmpty(...) bad params
      _log( "error" );
      return RETURN_ERROR;
   }

   return Head->NumberOfNodes;
}

ptrtrack *
__fastcall
ptrtrack::init
(
   INDEX_TYPE MaxNumberOfObjects
)
{
///////////////////////////////////////////////////////////////////////////////////////////////////////
   PBINTREE_HEAD Head;

   char * Memory;

   int MemoryArrayPointerSize;
   int MemoryPoolSize;
   int MemoryTotalSize;

   int loop;
///////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////
   if( MaxNumberOfObjects <= 0 )
   {
      // BinTreeInit(...) bad params
      _log( "error" );
      return 0;
   }
///////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////
   // We need the pointer pool for the memory manager stack.
   MemoryArrayPointerSize = sizeof( char * ) * MaxNumberOfObjects;

   // We need the Node pool for the memory manager, with the size of the nodes
   // expanded to include the client pointer.
   MemoryPoolSize = sizeof( BINTREE_NODE ) * MaxNumberOfObjects;
///////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////
   // Need enough memory for the head and the sentinel node
   MemoryTotalSize = sizeof( BINTREE_HEAD ) + sizeof( BINTREE_NODE );

   // Need one pointer pool for the memory manager
   MemoryTotalSize += MemoryArrayPointerSize;

   // Add the actual node pool to the total required allocation size.
   MemoryTotalSize += MemoryPoolSize;

   // Make sure the memory allocation is a multiple of 8 for quicker zero-ing of the
   // memory in the BinTreeTerm(...) function (a couple microseconds faster).
   MemoryTotalSize += MemoryTotalSize % 8;
///////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////
   // Actually allocate the memory we need
   Head = ( PBINTREE_HEAD ) malloc( MemoryTotalSize );

   if( !Head )
   {
      // BinTreeInit(...) bad memory allocation
      _log( "error" );
      return 0;
   }

   memset( Head, 0, MemoryTotalSize );
///////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////
   Memory = ( char * ) Head;

   Memory += sizeof( BINTREE_HEAD );

   Head->Nil = ( PBINTREE_NODE ) Memory;

   Memory += sizeof( BINTREE_NODE );

   Head->MemoryManagerArrayCurrent = ( char ** ) Memory;

   Memory += MemoryArrayPointerSize;

   for( loop = 0; loop < MaxNumberOfObjects; loop++ )
   {
      Head->MemoryManagerArrayCurrent[ loop ] = Memory;

      Memory += sizeof( BINTREE_NODE );
   }
///////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////
   Head->MaxNumberOfNodes = MaxNumberOfObjects;

   Head->MemoryTotalSize = MemoryTotalSize;
///////////////////////////////////////////////////////////////////////////////////////////////////////


   return ( ptrtrack * ) Head;
}

ptrtrack::ptrtrack
(
)
{
}

ptrtrack::ptrtrack
(
   ptrtrack &
)
{
}

ptrtrack &
ptrtrack::operator=
(
   ptrtrack &
)
{
   return this[0];
}

#ifdef __cplusplus
   }
#endif