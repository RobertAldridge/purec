
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

//#include "ptrtrack.h"

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

  #pragma warning (disable: 6011)
  #pragma warning (disable: 28182)
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

//#define GETROOTFROMSENTINEL(sentinel) (sentinel->left)
//#define SETROOTFROMSENTINEL(sentinel, node) (sentinel->left = node)

#define GETROOTFROMTREE(tree) (tree->sentinelRoot.left)
#define SETROOTFROMTREE(tree, node) (tree->sentinelRoot.left = node)

#define SETROOTCOLORFROMTREE(tree, value) (tree->sentinelRoot.left->color = value)

#define GETSENTINELFROMTREE(tree) ( &tree->sentinelRoot)

#define LESSTHANWRAPPER(tree, client, node) \
  (node == GETSENTINELFROMTREE(tree) ? 1 : tree->LessThan(client, GETCLIENT(node) ) )

//#define EQUALTOWRAPPER(tree, client, node) \
//  (node == GETSENTINELFROMTREE(tree) ? 0 : tree->EqualTo(client, GETCLIENT(node) ) )

//#define CLIENTEVALUATEWRAPPER(tree, node) \
//  (node == GETSENTINELFROMTREE(tree) ? 0 : tree->ClientEvaluate(GETCLIENT(node) ) )

#define _log(blah) {}

const int bintree::ok = 0;
const int bintree::error = -1;

const int bintree::empty = 1;

const int bintree::preorder = 0;
const int bintree::inorder = 1;
const int bintree::postorder = 2;
const int bintree::levelorder = 3;

// swap a node with its right child

// x
// xR = x->right

// x 0 2 4 5
// x->right 0 1 4 4 6
// x->right->left 1 2 5
// x->right->left->parent 2
// x->right->parent 3
// x->parent 3 6
// x->parent->left 4 4
// x->parent->right 4

// 0
// 1
// 2 2
// 3 3
//
// 0
// 1
// 2 2
// 3 3

//                                            x->parent 0
//                                           v  P
//                                          v  ^
//                                         L  ^
//        x; x->right->parent; x->parent->left 1
//       v  P                              P  v
//      v  ^                                ^  v
//     L  ^                                  ^  R
// x->left 2                                  xR = x->right; x->right->left->parent 2
//                                           v  P                               P  v
//                                          v  ^                                 ^  v
//                                         L  ^                                   ^  R
//                              x->right->left 3                                   x->right->right 3
//
//                                                                                 x->parent 0
//                                                                                v  P
//                                                                               v  ^
//                                                                              L  ^
//                                            xR = x->right; x->right->left->parent 1
//                                           v  P                               P  v
//                                          v  ^                                 ^  v
//                                         L  ^                                   ^  R
//        x; x->right->parent; x->parent->left 2                                   x->right->right 2
//       v  P                              P  v
//      v  ^                                ^  v
//     L  ^                                  ^  R
// x->left 3                                  x->right->left 3

// or

// x->parent 0
//       P  v
//        ^  v
//         ^  R
//          x; x->right->parent; x->parent->right 1
//         v  P                               P  v
//        v  ^                                 ^  v
//       L  ^                                   ^  R
//   x->left 2                                   xR = x->right; x->right->left->parent 2
//                                              v  P                               P  v
//                                             v  ^                                 ^  v
//                                            L  ^                                   ^  R
//                                 x->right->left 3                                   x->right->right 3
//
//                                    x->parent 0
//                                          P  v
//                                           ^  v
//                                            ^  R
//                                             xR = x->right; x->right->left->parent 1
//                                            v  P                               P  v
//                                           v  ^                                 ^  v
//                                          L  ^                                   ^  R
//        x; x->right->parent; x->parent->right 2                                   x->right->right 2
//       v  P                               P  v
//      v  ^                                 ^  v
//     L  ^                                   ^  R
// x->left 3                                   x->right->left 3

// integrated for root sentinel
static void LeftRotate(BinaryTreeNode* x)
{
  BinaryTreeNode* xR = x->right;

//                                            x->parent
//                                           v  P
//                                          v  ^
//                                         L  ^
//        x; x->right->parent; x->parent->left
//       v  P                              P  v
//      v  ^                                ^  v
//     L  ^                                  ^  R
// x->left                                    xR = x->right; x->right->left->parent
//                                           v  P                               P  v
//                                          v  ^                                 ^  v
//                                         L  ^                                   ^  R
//                              x->right->left                                     x->right->right

// or

// x->parent
//       P  v
//        ^  v
//         ^  R
//          x; x->right->parent; x->parent->right
//         v  P                               P  v
//        v  ^                                 ^  v
//       L  ^                                   ^  R
//   x->left                                     xR = x->right; x->right->left->parent
//                                              v  P                               P  v
//                                             v  ^                                 ^  v
//                                            L  ^                                   ^  R
//                                 x->right->left                                     x->right->right

  // 1 of 6
  x->right = xR->left;

//                                            x->parent
//                                           v  P
//                                          v  ^
//                                         L  ^
//        x; x->right->parent; x->parent->left
//       v  P                         v    P
//      v  ^                          v     ^
//     L  ^                           v      ^
// x->left                            v       xR = x->right; x->right->left->parent
//                                    v      v  P                               P  v
//                                    v     v  ^                                 ^  v
//                                    R    L  ^                                   ^  R
//                              x->right->left                                     x->right->right

// or

// x->parent
//       P  v
//        ^  v
//         ^  R
//          x; x->right->parent; x->parent->right
//         v  P                          v    P
//        v  ^                           v     ^
//       L  ^                            v      ^
//   x->left                             v       xR = x->right; x->right->left->parent
//                                       v      v  P                               P  v
//                                       v     v  ^                                 ^  v
//                                       R    L  ^                                   ^  R
//                                 x->right->left                                     x->right->right

  // 2 of 6
  if(xR->left)
    xR->left->parent = x;

//                                            x->parent
//                                           v  P
//                                          v  ^
//                                         L  ^
//        x; x->right->parent; x->parent->left
//       v  P                      P  v    P
//      v  ^                       ^  v     ^
//     L  ^                        ^  v      ^
// x->left                         ^  v       xR = x->right; x->right->left->parent
//                                 ^  v      v                                  P  v
//                                 ^  v     v                                    ^  v
//                                 ^  R    L                                      ^  R
//                              x->right->left                                     x->right->right

// or

// x->parent
//       P  v
//        ^  v
//         ^  R
//          x; x->right->parent; x->parent->right
//         v  P                       P  v    P
//        v  ^                        ^  v     ^
//       L  ^                         ^  v      ^
//   x->left                          ^  v       xR = x->right; x->right->left->parent
//                                    ^  v      v                                  P  v
//                                    ^  v     v                                    ^  v
//                                    ^  R    L                                      ^  R
//                                 x->right->left                                     x->right->right

  // 3 of 6
  xR->parent = x->parent;

//                                            x->parent
//                                           v  P     P
//                                          v  ^      ^
//                                         L  ^       ^
//        x; x->right->parent; x->parent->left        ^
//       v  P                      P  v               ^
//      v  ^                       ^  v               ^
//     L  ^                        ^  v               ^
// x->left                         ^  v       xR = x->right; x->right->left->parent
//                                 ^  v      v                                  P  v
//                                 ^  v     v                                    ^  v
//                                 ^  R    L                                      ^  R
//                              x->right->left                                     x->right->right

// or

//       <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//       v                                              ^
//       P                                              ^
// x->parent                                            ^
//       P  v                                           ^
//        ^  v                                          ^
//         ^  R                                         ^
//          x; x->right->parent; x->parent->right       ^
//         v  P                       P  v              ^
//        v  ^                        ^  v              ^
//       L  ^                         ^  v              ^
//   x->left                          ^  v       xR = x->right; x->right->left->parent
//                                    ^  v      v                                  P  v
//                                    ^  v     v                                    ^  v
//                                    ^  R    L                                      ^  R
//                                 x->right->left                                     x->right->right

  // 4 of 6
  if(x == x->parent->left)
    x->parent->left = xR;
  else /* x == x->parent->right */
    x->parent->right = xR;

//                                            x->parent
//                                              P  v  P
//                                             ^   v  ^
//                                            ^    v  ^
//        x; x->right->parent; x->parent->left     v  ^
//       v  P                      P  v            v  ^
//      v  ^                       ^  v            v  ^
//     L  ^                        ^  v            L  ^
// x->left                         ^  v       xR = x->right; x->right->left->parent
//                                 ^  v      v                                  P  v
//                                 ^  v     v                                    ^  v
//                                 ^  R    L                                      ^  R
//                              x->right->left                                     x->right->right

// or

//       <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//       v                                              ^
//       P                                              ^
// x->parent >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ^
//       P                                           v  ^
//        ^                                          v  ^
//         ^                                         v  ^
//          x; x->right->parent; x->parent->right    v  ^
//         v  P                       P  v           v  ^
//        v  ^                        ^  v           v  ^
//       L  ^                         ^  v           R  ^
//   x->left                          ^  v       xR = x->right; x->right->left->parent
//                                    ^  v      v                                  P  v
//                                    ^  v     v                                    ^  v
//                                    ^  R    L                                      ^  R
//                                 x->right->left                                     x->right->right

  // 5 of 6
  xR->left = x;

//                                            x->parent
//                                              P  v  P
//                                             ^   v  ^
//                                            ^    v  ^
//        x; x->right->parent; x->parent->left     v  ^
//       v  P                      P  v       L    v  ^
//      v  ^                       ^  v        ^   v  ^
//     L  ^                        ^  v         ^  L  ^
// x->left                         ^  v       xR = x->right; x->right->left->parent
//                                 ^  v                                         P  v
//                                 ^  v                                          ^  v
//                                 ^  R                                           ^  R
//                              x->right->left                                     x->right->right

// or

//       <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//       v                                              ^
//       P                                              ^
// x->parent >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ^
//       P                                           v  ^
//        ^                                          v  ^
//         ^                                         v  ^
//          x; x->right->parent; x->parent->right    v  ^
//         v  P                       P  v      L    v  ^
//        v  ^                        ^  v       ^   v  ^
//       L  ^                         ^  v        ^  R  ^
//   x->left                          ^  v       xR = x->right; x->right->left->parent
//                                    ^  v                                         P  v
//                                    ^  v                                          ^  v
//                                    ^  R                                           ^  R
//                                 x->right->left                                     x->right->right

  // 6 of 6
  x->parent = xR;

// 0
// 1
// 2 2
// 3 3

//                                            x->parent 0
//                                                 v  P
//                                                 v  ^
//                                                 v  ^
//        x; x->right->parent; x->parent->left 2   v  ^
//       v  P                      P  v    v  L    v  ^
//      v  ^                       ^  v     v  ^   v  ^
//     L  ^                        ^  v      P  ^  L  ^
// x->left 3                       ^  v       xR = x->right; x->right->left->parent 1
//                                 ^  v                                         P  v
//                                 ^  v                                          ^  v
//                                 ^  R                                           ^  R
//                              x->right->left 3                                   x->right->right 2
//
// to
//
//                                                                                 x->parent 0
//                                                                                v  P
//                                                                               v  ^
//                                                                              L  ^
//                                            xR = x->right; x->right->left->parent 1
//                                           v  P                               P  v
//                                          v  ^                                 ^  v
//                                         L  ^                                   ^  R
//        x; x->right->parent; x->parent->left 2                                   x->right->right 2
//       v  P                              P  v
//      v  ^                                ^  v
//     L  ^                                  ^  R
// x->left 3                                  x->right->left 3

// or

//       <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//       v                                              ^
//       P                                              ^
// x->parent 0 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ^
//                                                   v  ^
//                                                   v  ^
//                                                   v  ^
//          x; x->right->parent; x->parent->right 2  v  ^
//         v  P                       P  v    v L    v  ^
//        v  ^                        ^  v     v ^   v  ^
//       L  ^                         ^  v      P ^  R  ^
//   x->left 3                        ^  v       xR = x->right; x->right->left->parent 1
//                                    ^  v                                         P  v
//                                    ^  v                                          ^  v
//                                    ^  R                                           ^  R
//                                 x->right->left 3                                   x->right->right 2
//
// to
//
//                                    x->parent 0
//                                          P  v
//                                           ^  v
//                                            ^  R
//                                             xR = x->right; x->right->left->parent 1
//                                            v  P                               P  v
//                                           v  ^                                 ^  v
//                                          L  ^                                   ^  R
//        x; x->right->parent; x->parent->right 2                                   x->right->right 2
//       v  P                               P  v
//      v  ^                                 ^  v
//     L  ^                                   ^  R
// x->left 3                                   x->right->left 3
}

// integrated for root sentinel
static void RightRotate(BinaryTreeNode* x)
{
  BinaryTreeNode* xL = x->left;

  // 1 of 6
  x->left = xL->right;

  // 2 of 6
  if(xL->right)
    xL->right->parent = x;

  // 3 of 6
  xL->parent = x->parent;

  // 4 of 6
  if(x == x->parent->right)
    x->parent->right = xL;
  else /* x == x->parent->left */
    x->parent->left = xL;

  // 5 of 6
  xL->right = x;

  // 6 of 6
  x->parent = xL;
}

// integrated for root sentinel
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

// integrated for root sentinel
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

// xP; x->parent
// xPR; x->parent->right
// xPRL; x->parent->right->left
// xPRLL; x->parent->right->left->left

// x 0
// x->parent 0 2 7 10
// x->parent->right 0 1 7 7 12
// x->parent->right->left 0 4 6 11
// x->parent->right->left->left 0 3 5 9 11
// x->parent->right->left->left->left 1 2 10
// x->parent->right->left->left->left->parent 2
// x->parent->right->left->left->right 3 4 6
// x->parent->right->left->left->right->parent 4
// x->parent->right->left->left->parent 12
// x->parent->right->left->parent 5
// x->parent->right->parent 8
// x->parent->parent 8 9
// x->parent->parent->left 7 7
// x->parent->parent->right 7

// 0
// 1 1
// 2 2
// 3
// 4
// 5 5
//
// 0
// 1 1
// 2
// 3 3
// 4 4 4

//                                                                                                                                                                                                                                   x->parent->parent 0
//                                                                                                                                                                                                                                  v  P           P  v
//                                                                                                                                                                                                                                 v  ^             ^  v
//                                                                                                                                                                                                                                L  ^               ^  R
//                                                                                                                                                                  xP = x->parent; x->parent->right->parent; x->parent->parent->left 1               x->parent->parent->right 1
//                                                                                                                                                                 v  P                                                           P  v
//                                                                                                                                                                v  ^                                                             ^  v
//                                                                                                                                                               L  ^                                                               ^  R
//                                                                                                                                                   x->parent->left 2                                                               xPR = x->parent->right; x->parent->right->left->parent 2
//                                                                                                                                                                                                                                  v  P
//                                                                                                                                                                                                                                 v  ^
//                                                                                                                                                                                                                                L  ^
//                                                                                                                                                                xPRL = x->parent->right->left; x->parent->right->left->left->parent 3
//                                                                                                                                                               v  P
//                                                                                                                                                              v  ^
//                                                                                                                                                             L  ^
//                                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent 4
//                                  v  P                                                                                                                       P  v
//                                 v  ^                                                                                                                         ^  v
//                                L  ^                                                                                                                           ^  R
// x->parent->right->left->left->left 5                                                                                                                            x->parent->right->left->left->right 5
//
//                                                                                                                                                                                                                                                                    x->parent->parent 0
//                                                                                                                                                                                                                                                                   v  P           P  v
//                                                                                                                                                                                                                                                                  v  ^             ^  v
//                                                                                                                                                                                                                                                                 L  ^               ^  R
//                                                                                                                                                                                                              xPR = x->parent->right; x->parent->right->left->parent 1               x->parent->parent->right 1
//                                                                                                                                                                                                             v  P
//                                                                                                                                                                                                            v  ^
//                                                                                                                                                                                                           L  ^
//                                                                                 xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent 2
//                                                                                v  P                                                                                                                       P  v
//                                                                               v  ^                                                                                                                         ^  v
//                                                                              L  ^                                                                                                                           ^  R
//                xP = x->parent; x->parent->right->parent; x->parent->parent->left 3                                                                                                                           xPRL = x->parent->right->left; x->parent->right->left->left->parent 3
//               v  P                                                           P  v                                                                                                                           v  P
//              v  ^                                                             ^  v                                                                                                                         v  ^
//             L  ^                                                               ^  R                                                                                                                       L  ^
// x->parent->left 4                                                               x->parent->right->left->left->left 4                                                      x->parent->right->left->left->right 4

// or

//                                                                                                                                                x->parent->parent 0
//                                                                                                                                               v  P           P  v
//                                                                                                                                              v  ^             ^  v
//                                                                                                                                             L  ^               ^  R
//                                                                                                                         x->parent->parent->left 1               xP = x->parent; x->parent->right->parent; x->parent->parent->right 1
//                                                                                                                                                                v  P                                                            P  v
//                                                                                                                                                               v  ^                                                              ^  v
//                                                                                                                                                              L  ^                                                                ^  R
//                                                                                                                                                  x->parent->left 2                                                                xPR = x->parent->right; x->parent->right->left->parent 2
//                                                                                                                                                                                                                                  v  P
//                                                                                                                                                                                                                                 v  ^
//                                                                                                                                                                                                                                L  ^
//                                                                                                                                                                xPRL = x->parent->right->left; x->parent->right->left->left->parent 3
//                                                                                                                                                               v  P
//                                                                                                                                                              v  ^
//                                                                                                                                                             L  ^
//                                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent 4
//                                  v  P                                                                                                                       P  v
//                                 v  ^                                                                                                                         ^  v
//                                L  ^                                                                                                                           ^  R
// x->parent->right->left->left->left 5                                                                                                                            x->parent->right->left->left->right 5
//
//                                                                                                                                                                                                                                      x->parent->parent 0
//                                                                                                                                                                                                                                     v  P           P  v
//                                                                                                                                                                                                                                    v  ^             ^  v
//                                                                                                                                                                                                                                   L  ^               ^  R
//                                                                                                                                                                                                               x->parent->parent->left 1               xPR = x->parent->right; x->parent->right->left->parent 1
//                                                                                                                                                                                                                                                      v  P
//                                                                                                                                                                                                                                                     v  ^
//                                                                                                                                                                                                                                                    L  ^
//                                                                                                                          xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent 2
//                                                                                                                         v  P                                                                                                                       P  v
//                                                                                                                        v  ^                                                                                                                         ^  v
//                                                                                                                       L  ^                                                                                                                           ^  R
//                                                        xP = x->parent; x->parent->right->parent; x->parent->parent->right 3                                                                                                                           xPRL = x->parent->right->left; x->parent->right->left->left->parent 3
//                                                       v  P                                                            P  v                                                                                                                           v  P
//                                                      v  ^                                                              ^  v                                                                                                                         v  ^
//                                                     L  ^                                                                ^  R                                                                                                                       L  ^
//                                         x->parent->left 4                                                                x->parent->right->left->left->left 4                                                      x->parent->right->left->left->right 4

// integrated for root sentinel
static void LeftRightLeftRotate(BinaryTreeNode* xP)
{
  BinaryTreeNode* xPR = xP->right;
  BinaryTreeNode* xPRL = xPR->left;
  BinaryTreeNode* xPRLL = xPRL->left;

//                                                                                                                                                                                                                                   x->parent->parent
//                                                                                                                                                                                                                                  v  P           P  v
//                                                                                                                                                                                                                                 v  ^             ^  v
//                                                                                                                                                                                                                                L  ^               ^  R
//                                                                                                                                                                  xP = x->parent; x->parent->right->parent; x->parent->parent->left                 x->parent->parent->right
//                                                                                                                                                                 v  P                                                           P  v
//                                                                                                                                                                v  ^                                                             ^  v
//                                                                                                                                                               L  ^                                                               ^  R
//                                                                                                                                                   x->parent->left                                                                 xPR = x->parent->right; x->parent->right->left->parent
//                                                                                                                                                                                                                                  v  P
//                                                                                                                                                                                                                                 v  ^
//                                                                                                                                                                                                                                L  ^
//                                                                                                                                                                xPRL = x->parent->right->left; x->parent->right->left->left->parent
//                                                                                                                                                               v  P
//                                                                                                                                                              v  ^
//                                                                                                                                                             L  ^
//                                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent
//                                  v  P                                                                                                                       P  v
//                                 v  ^                                                                                                                         ^  v
//                                L  ^                                                                                                                           ^  R
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

// or

//                                                                                                                                                x->parent->parent
//                                                                                                                                               v  P           P  v
//                                                                                                                                              v  ^             ^  v
//                                                                                                                                             L  ^               ^  R
//                                                                                                                         x->parent->parent->left                 xP = x->parent; x->parent->right->parent; x->parent->parent->right
//                                                                                                                                                                v  P                                                            P  v
//                                                                                                                                                               v  ^                                                              ^  v
//                                                                                                                                                              L  ^                                                                ^  R
//                                                                                                                                                  x->parent->left                                                                  xPR = x->parent->right; x->parent->right->left->parent
//                                                                                                                                                                                                                                  v  P
//                                                                                                                                                                                                                                 v  ^
//                                                                                                                                                                                                                                L  ^
//                                                                                                                                                                xPRL = x->parent->right->left; x->parent->right->left->left->parent
//                                                                                                                                                               v  P
//                                                                                                                                                              v  ^
//                                                                                                                                                             L  ^
//                                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent
//                                  v  P                                                                                                                       P  v
//                                 v  ^                                                                                                                         ^  v
//                                L  ^                                                                                                                           ^  R
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

  // 1 of 12
  xP->right = xPRLL->left;

//                                                                                                                                                                                                                                   x->parent->parent
//               <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<                                  v  P           P  v
//               v                                                                                                                                                                               ^                                 v  ^             ^  v
//               v                                                                                                                                                                               ^                                L  ^               ^  R
//               v                                                                                                                                                  xP = x->parent; x->parent->right->parent; x->parent->parent->left                 x->parent->parent->right
//               v                                                                                                                                                 v  P                                                           P
//               v                                                                                                                                                v  ^                                                             ^
//               v                                                                                                                                               L  ^                                                               ^
//               v                                                                                                                                   x->parent->left                                                                 xPR = x->parent->right; x->parent->right->left->parent
//               v                                                                                                                                                                                                                  v  P
//               v                                                                                                                                                                                                                 v  ^
//               v                                                                                                                                                                                                                L  ^
//               v                                                                                                                                                xPRL = x->parent->right->left; x->parent->right->left->left->parent
//               v                                                                                                                                               v  P
//               v                                                                                                                                              v  ^
//               v                                                                                                                                             L  ^
//               v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent
//               v                  v  P                                                                                                                       P  v
//               v                 v  ^                                                                                                                         ^  v
//               R                L  ^                                                                                                                           ^  R
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

// or

//               <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//               v                                                                                                                                                                              ^
//               v                                                                                                                                                                              ^
//               v                                                                                                                                                                              ^
//               v                                                                                                                                                                              ^
//               v                                                                                                                                x->parent->parent                             ^
//               v                                                                                                                               v  P           P  v                            ^
//               v                                                                                                                              v  ^             ^  v                           ^
//               v                                                                                                                             L  ^               ^  R                          ^
//               v                                                                                                         x->parent->parent->left                 xP = x->parent; x->parent->right->parent; x->parent->parent->right
//               v                                                                                                                                                v  P                                                            P
//               v                                                                                                                                               v  ^                                                              ^
//               v                                                                                                                                              L  ^                                                                ^
//               v                                                                                                                                  x->parent->left                                                                  xPR = x->parent->right; x->parent->right->left->parent
//               v                                                                                                                                                                                                                  v  P
//               v                                                                                                                                                                                                                 v  ^
//               v                                                                                                                                                                                                                L  ^
//               v                                                                                                                                                xPRL = x->parent->right->left; x->parent->right->left->left->parent
//               v                                                                                                                                               v  P
//               v                                                                                                                                              v  ^
//               v                                                                                                                                             L  ^
//               v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent
//               v                  v  P                                                                                                                       P  v
//               v                 v  ^                                                                                                                         ^  v
//               R                L  ^                                                                                                                           ^  R
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

  // 2 of 12
  if(xPRLL->left)
    xPRLL->left->parent = xP;

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                     v                                x->parent->parent
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v                               v  P           P  v
//            ^  v                                                                                                                                                                               ^  v                              v  ^             ^  v
//            ^  v                                                                                                                                                                               ^  P                             L  ^               ^  R
//            ^  v                                                                                                                                                  xP = x->parent; x->parent->right->parent; x->parent->parent->left                 x->parent->parent->right
//            ^  v                                                                                                                                                 v  P                                                           P
//            ^  v                                                                                                                                                v  ^                                                             ^
//            ^  v                                                                                                                                               L  ^                                                               ^
//            ^  v                                                                                                                                   x->parent->left                                                                 xPR = x->parent->right; x->parent->right->left->parent
//            ^  v                                                                                                                                                                                                                  v  P
//            ^  v                                                                                                                                                                                                                 v  ^
//            ^  v                                                                                                                                                                                                                L  ^
//            ^  v                                                                                                                                                xPRL = x->parent->right->left; x->parent->right->left->left->parent
//            ^  v                                                                                                                                               v  P
//            ^  v                                                                                                                                              v  ^
//            ^  v                                                                                                                                             L  ^
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent
//            ^  v                  v                                                                                                                          P  v
//            ^  v                 v                                                                                                                            ^  v
//            ^  R                L                                                                                                                              ^  R
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

// or

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                    v
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                x->parent->parent                             ^  v
//            ^  v                                                                                                                               v  P           P  v                            ^  v
//            ^  v                                                                                                                              v  ^             ^  v                           ^  v
//            ^  v                                                                                                                             L  ^               ^  R                          ^  P
//            ^  v                                                                                                         x->parent->parent->left                 xP = x->parent; x->parent->right->parent; x->parent->parent->right
//            ^  v                                                                                                                                                v  P                                                            P
//            ^  v                                                                                                                                               v  ^                                                              ^
//            ^  v                                                                                                                                              L  ^                                                                ^
//            ^  v                                                                                                                                  x->parent->left                                                                  xPR = x->parent->right; x->parent->right->left->parent
//            ^  v                                                                                                                                                                                                                  v  P
//            ^  v                                                                                                                                                                                                                 v  ^
//            ^  v                                                                                                                                                                                                                L  ^
//            ^  v                                                                                                                                                xPRL = x->parent->right->left; x->parent->right->left->left->parent
//            ^  v                                                                                                                                               v  P
//            ^  v                                                                                                                                              v  ^
//            ^  v                                                                                                                                             L  ^
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent
//            ^  v                  v                                                                                                                          P  v
//            ^  v                 v                                                                                                                            ^  v
//            ^  R                L                                                                                                                              ^  R
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

  // 3 of 12
  xPRL->left = xPRLL->right;

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                     v                                x->parent->parent
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v                               v  P           P  v
//            ^  v                                                                                                                                                                               ^  v                              v  ^             ^  v
//            ^  v                                                                                                                                                                               ^  P                             L  ^               ^  R
//            ^  v                                                                                                                                                  xP = x->parent; x->parent->right->parent; x->parent->parent->left                 x->parent->parent->right
//            ^  v                                                                                                                                                 v  P                                                           P
//            ^  v                                                                                                                                                v  ^                                                             ^
//            ^  v                                                                                                                                               L  ^                                                               ^
//            ^  v                                                                                                                                   x->parent->left                                                                 xPR = x->parent->right; x->parent->right->left->parent
//            ^  v                                                                                                                                                                                                                  v  P
//            ^  v                                                                                                                                                                                                                 v  ^
//            ^  v                                                                                                                                                                                                                L  ^
//            ^  v                                                                                                                                                xPRL = x->parent->right->left; x->parent->right->left->left->parent
//            ^  v                                                                                                                                                  P    v
//            ^  v                                                                                                                                                 ^     v
//            ^  v                                                                                                                                                ^      v
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent       v
//            ^  v                  v                                                                                                                          P  v      v
//            ^  v                 v                                                                                                                            ^  v     v
//            ^  R                L                                                                                                                              ^  R    L
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

// or

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                    v
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                x->parent->parent                             ^  v
//            ^  v                                                                                                                               v  P           P  v                            ^  v
//            ^  v                                                                                                                              v  ^             ^  v                           ^  v
//            ^  v                                                                                                                             L  ^               ^  R                          ^  P
//            ^  v                                                                                                         x->parent->parent->left                 xP = x->parent; x->parent->right->parent; x->parent->parent->right
//            ^  v                                                                                                                                                v  P                                                            P
//            ^  v                                                                                                                                               v  ^                                                              ^
//            ^  v                                                                                                                                              L  ^                                                                ^
//            ^  v                                                                                                                                  x->parent->left                                                                  xPR = x->parent->right; x->parent->right->left->parent
//            ^  v                                                                                                                                                                                                                  v  P
//            ^  v                                                                                                                                                                                                                 v  ^
//            ^  v                                                                                                                                                                                                                L  ^
//            ^  v                                                                                                                                                xPRL = x->parent->right->left; x->parent->right->left->left->parent
//            ^  v                                                                                                                                                  P    v
//            ^  v                                                                                                                                                 ^     v
//            ^  v                                                                                                                                                ^      v
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent       v
//            ^  v                  v                                                                                                                          P  v      v
//            ^  v                 v                                                                                                                            ^  v     v
//            ^  R                L                                                                                                                              ^  R    L
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

  // 4 of 12
  if(xPRLL->right)
    xPRLL->right->parent = xPRL;

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                     v                                x->parent->parent
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v                               v  P           P  v
//            ^  v                                                                                                                                                                               ^  v                              v  ^             ^  v
//            ^  v                                                                                                                                                                               ^  P                             L  ^               ^  R
//            ^  v                                                                                                                                                  xP = x->parent; x->parent->right->parent; x->parent->parent->left                 x->parent->parent->right
//            ^  v                                                                                                                                                 v  P                                                           P
//            ^  v                                                                                                                                                v  ^                                                             ^
//            ^  v                                                                                                                                               L  ^                                                               ^
//            ^  v                                                                                                                                   x->parent->left                                                                 xPR = x->parent->right; x->parent->right->left->parent
//            ^  v                                                                                                                                                                                                                  v  P
//            ^  v                                                                                                                                                                                                                 v  ^
//            ^  v                                                                                                                                                                                                                L  ^
//            ^  v                                                                                                                                                xPRL = x->parent->right->left; x->parent->right->left->left->parent
//            ^  v                                                                                                                                                  P    v  P
//            ^  v                                                                                                                                                 ^     v  ^
//            ^  v                                                                                                                                                ^      v  ^
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent       v  ^
//            ^  v                  v                                                                                                                             v      v  ^
//            ^  v                 v                                                                                                                               v     v  ^
//            ^  R                L                                                                                                                                 R    L  ^
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

// or

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                    v
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                x->parent->parent                             ^  v
//            ^  v                                                                                                                               v  P           P  v                            ^  v
//            ^  v                                                                                                                              v  ^             ^  v                           ^  v
//            ^  v                                                                                                                             L  ^               ^  R                          ^  P
//            ^  v                                                                                                         x->parent->parent->left                 xP = x->parent; x->parent->right->parent; x->parent->parent->right
//            ^  v                                                                                                                                                v  P                                                            P
//            ^  v                                                                                                                                               v  ^                                                              ^
//            ^  v                                                                                                                                              L  ^                                                                ^
//            ^  v                                                                                                                                  x->parent->left                                                                  xPR = x->parent->right; x->parent->right->left->parent
//            ^  v                                                                                                                                                                                                                  v  P
//            ^  v                                                                                                                                                                                                                 v  ^
//            ^  v                                                                                                                                                                                                                L  ^
//            ^  v                                                                                                                                                xPRL = x->parent->right->left; x->parent->right->left->left->parent
//            ^  v                                                                                                                                                  P    v  P
//            ^  v                                                                                                                                                 ^     v  ^
//            ^  v                                                                                                                                                ^      v  ^
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent       v  ^
//            ^  v                  v                                                                                                                             v      v  ^
//            ^  v                 v                                                                                                                               v     v  ^
//            ^  R                L                                                                                                                                 R    L  ^
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

  // 5 of 12
  xPRL->parent = xPRLL;

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                     v                                x->parent->parent
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v                               v  P           P  v
//            ^  v                                                                                                                                                                               ^  v                              v  ^             ^  v
//            ^  v                                                                                                                                                                               ^  P                             L  ^               ^  R
//            ^  v                                                                                                                                                  xP = x->parent; x->parent->right->parent; x->parent->parent->left                 x->parent->parent->right
//            ^  v                                                                                                                                                 v  P                                                           P
//            ^  v                                                                                                                                                v  ^                                                             ^
//            ^  v                                                                                                                                               L  ^                                                               ^
//            ^  v                                                                                                                                   x->parent->left                                                                 xPR = x->parent->right; x->parent->right->left->parent
//            ^  v                                                                                                                                                                                                                  v
//            ^  v                                                                                                                                                                                                                 v
//            ^  v                                                                                                                                                                                                                L
//            ^  v                                                                                                                          <<<<<<<<<<<<<<<<<<<<< xPRL = x->parent->right->left; x->parent->right->left->left->parent
//            ^  v                                                                                                                          v                       P    v  P
//            ^  v                                                                                                                          v                      ^     v  ^
//            ^  v                                                                                                                          P                     ^      v  ^
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent       v  ^
//            ^  v                  v                                                                                                                             v      v  ^
//            ^  v                 v                                                                                                                               v     v  ^
//            ^  R                L                                                                                                                                 R    L  ^
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

// or

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                    v
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                x->parent->parent                             ^  v
//            ^  v                                                                                                                               v  P           P  v                            ^  v
//            ^  v                                                                                                                              v  ^             ^  v                           ^  v
//            ^  v                                                                                                                             L  ^               ^  R                          ^  P
//            ^  v                                                                                                         x->parent->parent->left                 xP = x->parent; x->parent->right->parent; x->parent->parent->right
//            ^  v                                                                                                                                                v  P                                                            P
//            ^  v                                                                                                                                               v  ^                                                              ^
//            ^  v                                                                                                                                              L  ^                                                                ^
//            ^  v                                                                                                                                  x->parent->left                                                                  xPR = x->parent->right; x->parent->right->left->parent
//            ^  v                                                                                                                                                                                                                  v
//            ^  v                                                                                                                                                                                                                 v
//            ^  v                                                                                                                                                                                                                L
//            ^  v                                                                                                                          <<<<<<<<<<<<<<<<<<<<< xPRL = x->parent->right->left; x->parent->right->left->left->parent
//            ^  v                                                                                                                          v                       P    v  P
//            ^  v                                                                                                                          v                      ^     v  ^
//            ^  v                                                                                                                          P                     ^      v  ^
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent       v  ^
//            ^  v                  v                                                                                                                             v      v  ^
//            ^  v                 v                                                                                                                               v     v  ^
//            ^  R                L                                                                                                                                 R    L  ^
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

  // 6 of 12
  xPRLL->right = xPRL;

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                     v                                x->parent->parent
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v                               v  P           P  v
//            ^  v                                                                                                                                                                               ^  v                              v  ^             ^  v
//            ^  v                                                                                                                                                                               ^  P                             L  ^               ^  R
//            ^  v                                                                                                                                                  xP = x->parent; x->parent->right->parent; x->parent->parent->left                 x->parent->parent->right
//            ^  v                                                                                                                                                 v  P                                                           P
//            ^  v                                                                                                                                                v  ^                                                             ^
//            ^  v                                                                                                                                               L  ^                                                               ^
//            ^  v                                                                                                                                   x->parent->left                                                                 xPR = x->parent->right; x->parent->right->left->parent
//            ^  v                                                                                                                                                                                                                  v
//            ^  v                                                                                                                                                                                                                 v
//            ^  v                                                                                                                                                                                                                L
//            ^  v                                                                                                                          <<<<<<<<<<<<<<<<<<<<< xPRL = x->parent->right->left; x->parent->right->left->left->parent
//            ^  v                                                                                                                          v                    R  P    v  P
//            ^  v                                                                                                                          v                   ^  ^     v  ^
//            ^  v                                                                                                                          P                  ^  ^      v  ^
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent       v  ^
//            ^  v                  v                                                                                                                                    v  ^
//            ^  v                 v                                                                                                                                     v  ^
//            ^  R                L                                                                                                                                      L  ^
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

// or

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                    v
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                x->parent->parent                             ^  v
//            ^  v                                                                                                                               v  P           P  v                            ^  v
//            ^  v                                                                                                                              v  ^             ^  v                           ^  v
//            ^  v                                                                                                                             L  ^               ^  R                          ^  P
//            ^  v                                                                                                         x->parent->parent->left                 xP = x->parent; x->parent->right->parent; x->parent->parent->right
//            ^  v                                                                                                                                                v  P                                                            P
//            ^  v                                                                                                                                               v  ^                                                              ^
//            ^  v                                                                                                                                              L  ^                                                                ^
//            ^  v                                                                                                                                  x->parent->left                                                                  xPR = x->parent->right; x->parent->right->left->parent
//            ^  v                                                                                                                                                                                                                  v
//            ^  v                                                                                                                                                                                                                 v
//            ^  v                                                                                                                                                                                                                L
//            ^  v                                                                                                                          <<<<<<<<<<<<<<<<<<<<< xPRL = x->parent->right->left; x->parent->right->left->left->parent
//            ^  v                                                                                                                          v                    R  P    v  P
//            ^  v                                                                                                                          v                   ^  ^     v  ^
//            ^  v                                                                                                                          P                  ^  ^      v  ^
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent       v  ^
//            ^  v                  v                                                                                                                                    v  ^
//            ^  v                 v                                                                                                                                     v  ^
//            ^  R                L                                                                                                                                      L  ^
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

  // 7 of 12
  if(xP == xP->parent->left)
    xP->parent->left = xPR;
  else /* xP == xP->parent->right */
    xP->parent->right = xPR;

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                     v                                x->parent->parent
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v                                  P    v      P  v
//            ^  v                                                                                                                                                                               ^  v                                 ^     v       ^  v
//            ^  v                                                                                                                                                                               ^  P                                ^      v        ^  R
//            ^  v                                                                                                                                                  xP = x->parent; x->parent->right->parent; x->parent->parent->left       v         x->parent->parent->right
//            ^  v                                                                                                                                                 v  P                                                           P         v
//            ^  v                                                                                                                                                v  ^                                                             ^        v
//            ^  v                                                                                                                                               L  ^                                                               ^       L
//            ^  v                                                                                                                                   x->parent->left                                                                 xPR = x->parent->right; x->parent->right->left->parent
//            ^  v                                                                                                                                                                                                                  v
//            ^  v                                                                                                                                                                                                                 v
//            ^  v                                                                                                                                                                                                                L
//            ^  v                                                                                                                          <<<<<<<<<<<<<<<<<<<<< xPRL = x->parent->right->left; x->parent->right->left->left->parent
//            ^  v                                                                                                                          v                    R  P    v  P
//            ^  v                                                                                                                          v                   ^  ^     v  ^
//            ^  v                                                                                                                          P                  ^  ^      v  ^
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent       v  ^
//            ^  v                  v                                                                                                                                    v  ^
//            ^  v                 v                                                                                                                                     v  ^
//            ^  R                L                                                                                                                                      L  ^
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

// or

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                    v
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                x->parent->parent >>>>>>>>>>>>>>>>>>>>>>>>>>> ^  v >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^  v                                                                                                                               v  P           P                               ^  v                                             v
//            ^  v                                                                                                                              v  ^             ^                              ^  v                                             v
//            ^  v                                                                                                                             L  ^               ^                             ^  P                                             v
//            ^  v                                                                                                         x->parent->parent->left                 xP = x->parent; x->parent->right->parent; x->parent->parent->right            v
//            ^  v                                                                                                                                                v  P                                                            P              v
//            ^  v                                                                                                                                               v  ^                                                              ^             v
//            ^  v                                                                                                                                              L  ^                                                                ^            R
//            ^  v                                                                                                                                  x->parent->left                                                                  xPR = x->parent->right; x->parent->right->left->parent
//            ^  v                                                                                                                                                                                                                  v
//            ^  v                                                                                                                                                                                                                 v
//            ^  v                                                                                                                                                                                                                L
//            ^  v                                                                                                                          <<<<<<<<<<<<<<<<<<<<< xPRL = x->parent->right->left; x->parent->right->left->left->parent
//            ^  v                                                                                                                          v                    R  P    v  P
//            ^  v                                                                                                                          v                   ^  ^     v  ^
//            ^  v                                                                                                                          P                  ^  ^      v  ^
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent       v  ^
//            ^  v                  v                                                                                                                                    v  ^
//            ^  v                 v                                                                                                                                     v  ^
//            ^  R                L                                                                                                                                      L  ^
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

  // 8 of 12
  xPR->parent = xP->parent;

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                     v                                x->parent->parent
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v                                  P    v  P   P  v
//            ^  v                                                                                                                                                                               ^  v                                 ^     v  ^    ^  v
//            ^  v                                                                                                                                                                               ^  P                                ^      v  ^     ^  R
//            ^  v                                                                                                                                                  xP = x->parent; x->parent->right->parent; x->parent->parent->left       v  ^      x->parent->parent->right
//            ^  v                                                                                                                                                 v  P                                                                     v  ^
//            ^  v                                                                                                                                                v  ^                                                                      v  ^
//            ^  v                                                                                                                                               L  ^                                                                       L  ^
//            ^  v                                                                                                                                   x->parent->left                                                                 xPR = x->parent->right; x->parent->right->left->parent
//            ^  v                                                                                                                                                                                                                  v
//            ^  v                                                                                                                                                                                                                 v
//            ^  v                                                                                                                                                                                                                L
//            ^  v                                                                                                                          <<<<<<<<<<<<<<<<<<<<< xPRL = x->parent->right->left; x->parent->right->left->left->parent
//            ^  v                                                                                                                          v                    R  P    v  P
//            ^  v                                                                                                                          v                   ^  ^     v  ^
//            ^  v                                                                                                                          P                  ^  ^      v  ^
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent       v  ^
//            ^  v                  v                                                                                                                                    v  ^
//            ^  v                 v                                                                                                                                     v  ^
//            ^  R                L                                                                                                                                      L  ^
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

// or

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                    v
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                           <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ^  v <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//            ^  v                                                                                                                                           v                                  ^  v                                                ^
//            ^  v                                                                                                                                           P                                  ^  v                                                ^
//            ^  v                                                                                                                                x->parent->parent >>>>>>>>>>>>>>>>>>>>>>>>>>> ^  v >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ^
//            ^  v                                                                                                                               v  P           P                               ^  v                                             v  ^
//            ^  v                                                                                                                              v  ^             ^                              ^  v                                             v  ^
//            ^  v                                                                                                                             L  ^               ^                             ^  P                                             v  ^
//            ^  v                                                                                                         x->parent->parent->left                 xP = x->parent; x->parent->right->parent; x->parent->parent->right            v  ^
//            ^  v                                                                                                                                                v  P                                                                           v  ^
//            ^  v                                                                                                                                               v  ^                                                                            v  ^
//            ^  v                                                                                                                                              L  ^                                                                             R  ^
//            ^  v                                                                                                                                  x->parent->left                                                                  xPR = x->parent->right; x->parent->right->left->parent
//            ^  v                                                                                                                                                                                                                  v
//            ^  v                                                                                                                                                                                                                 v
//            ^  v                                                                                                                                                                                                                L
//            ^  v                                                                                                                          <<<<<<<<<<<<<<<<<<<<< xPRL = x->parent->right->left; x->parent->right->left->left->parent
//            ^  v                                                                                                                          v                    R  P    v  P
//            ^  v                                                                                                                          v                   ^  ^     v  ^
//            ^  v                                                                                                                          P                  ^  ^      v  ^
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent       v  ^
//            ^  v                  v                                                                                                                                    v  ^
//            ^  v                 v                                                                                                                                     v  ^
//            ^  R                L                                                                                                                                      L  ^
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

  // 9 of 12
  xP->parent = xPRLL;

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                     v                                x->parent->parent
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v                                       v  P   P  v
//            ^  v                                                                                                                                                                               ^  v                                       v  ^    ^  v
//            ^  v                                                                                                                                                                               ^  P                                       v  ^     ^  R
//            ^  v                                                                                                  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< xP = x->parent; x->parent->right->parent; x->parent->parent->left       v  ^      x->parent->parent->right
//            ^  v                                                                                                  v                                              v  P                                                                     v  ^
//            ^  v                                                                                                  v                                             v  ^                                                                      v  ^
//            ^  v                                                                                                  v                                            L  ^                                                                       L  ^
//            ^  v                                                                                                  v                                x->parent->left                                                                 xPR = x->parent->right; x->parent->right->left->parent
//            ^  v                                                                                                  v                                                                                                               v
//            ^  v                                                                                                  v                                                                                                              v
//            ^  v                                                                                                  v                                                                                                             L
//            ^  v                                                                                                  v                       <<<<<<<<<<<<<<<<<<<<< xPRL = x->parent->right->left; x->parent->right->left->left->parent
//            ^  v                                                                                                  v                       v                    R  P    v  P
//            ^  v                                                                                                  v                       v                   ^  ^     v  ^
//            ^  v                                                                                                  P                       P                  ^  ^      v  ^
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent       v  ^
//            ^  v                  v                                                                                                                                    v  ^
//            ^  v                 v                                                                                                                                     v  ^
//            ^  R                L                                                                                                                                      L  ^
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

// or

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                    v
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                           <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ^  v <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//            ^  v                                                                                                                                           v                                  ^  v                                                ^
//            ^  v                                                                                                                                           P                                  ^  v                                                ^
//            ^  v                                                                                                                                x->parent->parent >>>>>>>>>>>>>>>>>>>>>>>>>>> ^  v >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ^
//            ^  v                                                                                                                               v  P                                           ^  v                                             v  ^
//            ^  v                                                                                                                              v  ^                                            ^  v                                             v  ^
//            ^  v                                                                                                                             L  ^                                             ^  P                                             v  ^
//            ^  v                                                                                                         x->parent->parent->left       <<<<<<<<< xP = x->parent; x->parent->right->parent; x->parent->parent->right            v  ^
//            ^  v                                                                                                                                       v        v  P                                                                           v  ^
//            ^  v                                                                                                  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<       v  ^                                                                            v  ^
//            ^  v                                                                                                  v                                           L  ^                                                                             R  ^
//            ^  v                                                                                                  v                               x->parent->left                                                                  xPR = x->parent->right; x->parent->right->left->parent
//            ^  v                                                                                                  v                                                                                                               v
//            ^  v                                                                                                  v                                                                                                              v
//            ^  v                                                                                                  v                                                                                                             L
//            ^  v                                                                                                  v                       <<<<<<<<<<<<<<<<<<<<< xPRL = x->parent->right->left; x->parent->right->left->left->parent
//            ^  v                                                                                                  v                       v                    R  P    v  P
//            ^  v                                                                                                  v                       v                   ^  ^     v  ^
//            ^  v                                                                                                  P                       P                  ^  ^      v  ^
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent       v  ^
//            ^  v                  v                                                                                                                                    v  ^
//            ^  v                 v                                                                                                                                     v  ^
//            ^  R                L                                                                                                                                      L  ^
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

  // 10 of 12
  xPRLL->left = xP;

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                     v                                x->parent->parent
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v                                       v  P   P  v
//            ^  v                                                                                                                                                                               ^  v                                       v  ^    ^  v
//            ^  v                                                                                                                                                                               ^  P                                       v  ^     ^  R
//            ^  v                                                                                                  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< xP = x->parent; x->parent->right->parent; x->parent->parent->left       v  ^      x->parent->parent->right
//            ^  v                                                                                                  v                                              v  P      L                                                              v  ^
//            ^  v                                                                                                  v                                             v  ^       ^                                                              v  ^
//            ^  v                                                                                                  v                                            L  ^        ^                                                              L  ^
//            ^  v                                                                                                  v                                x->parent->left         ^                                                       xPR = x->parent->right; x->parent->right->left->parent
//            ^  v                                                                                                  v                                                        ^                                                      v
//            ^  v                                                                                                  v          >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                                                     v
//            ^  v                                                                                                  v          ^                                                                                                  L
//            ^  v                                                                                                  v          ^            <<<<<<<<<<<<<<<<<<<<< xPRL = x->parent->right->left; x->parent->right->left->left->parent
//            ^  v                                                                                                  v          ^            v                    R  P    v  P
//            ^  v                                                                                                  v          ^            v                   ^  ^     v  ^
//            ^  v                                                                                                  P          ^            P                  ^  ^      v  ^
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent       v  ^
//            ^  v                                                                                                                                                       v  ^
//            ^  v                                                                                                                                                       v  ^
//            ^  R                                                                                                                                                       L  ^
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

// or

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                    v
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                           <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ^  v <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//            ^  v                                                                                                                                           v                                  ^  v                                                ^
//            ^  v                                                                                                                                           P                                  ^  v                                                ^
//            ^  v                                                                                                                                x->parent->parent >>>>>>>>>>>>>>>>>>>>>>>>>>> ^  v >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ^
//            ^  v                                                                                                                               v  P                                           ^  v                                             v  ^
//            ^  v                                                                                                                              v  ^                                            ^  v                                             v  ^
//            ^  v                                                                                                                             L  ^                                             ^  P                                             v  ^
//            ^  v                                                                                                         x->parent->parent->left       <<<<<<<<< xP = x->parent; x->parent->right->parent; x->parent->parent->right            v  ^
//            ^  v                                                                                                                                       v        v  P      L                                                                    v  ^
//            ^  v                                                                                                  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<       v  ^       ^                                                                    v  ^
//            ^  v                                                                                                  v                                           L  ^        ^                                                                    R  ^
//            ^  v                                                                                                  v                               x->parent->left         ^                                                        xPR = x->parent->right; x->parent->right->left->parent
//            ^  v                                                                                                  v                                                       ^                                                       v
//            ^  v                                                                                                  v          >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                                                      v
//            ^  v                                                                                                  v          ^                                                                                                  L
//            ^  v                                                                                                  v          ^            <<<<<<<<<<<<<<<<<<<<< xPRL = x->parent->right->left; x->parent->right->left->left->parent
//            ^  v                                                                                                  v          ^            v                    R  P    v  P
//            ^  v                                                                                                  v          ^            v                   ^  ^     v  ^
//            ^  v                                                                                                  P          ^            P                  ^  ^      v  ^
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent       v  ^
//            ^  v                                                                                                                                                       v  ^
//            ^  v                                                                                                                                                       v  ^
//            ^  R                                                                                                                                                       L  ^
// x->parent->right->left->left->left                                                                                                                             x->parent->right->left->left->right

  // 11 of 12
  xPR->left = xPRLL;

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                     v                                x->parent->parent
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v                                       v  P   P  v
//            ^  v                                                                                                                                                                               ^  v                                       v  ^    ^  v
//            ^  v                                                                                                                                                                               ^  P                                       v  ^     ^  R
//            ^  v                                                                                                  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< xP = x->parent; x->parent->right->parent; x->parent->parent->left       v  ^      x->parent->parent->right
//            ^  v                                                                                                  v                                              v  P      L                                                              v  ^
//            ^  v                                                                                                  v                                             v  ^       ^                                                              v  ^
//            ^  v                                                                                                  v                                            L  ^        ^                                                              L  ^
//            ^  v                                                                                                  v                                x->parent->left         ^                                                       xPR = x->parent->right; x->parent->right->left->parent
//            ^  v                                                                                                  v                                                        ^                                                                v
//            ^  v                                                                                                  v          >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                                                                v
//            ^  v                                                                                                  v          ^                                                                                                              v
//            ^  v                                                                                                  v          ^            <<<<<<<<<<<<<<<<<<<<< xPRL = x->parent->right->left; x->parent->right->left->left->parent         v
//            ^  v                                                                                                  v          ^            v                    R  P    v  P                                                                 v
//            ^  v                                                                                                  v          ^            v                   ^  ^     v  ^                                                                 v
//            ^  v                                                                                                  P          ^            P                  ^  ^      v  ^                                                                 v
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent       v  ^                                                                 v
//            ^  v                                                                                                                    L                                  v  ^                                                                 v
//            ^  v                                                                                                                    ^                                  v  ^                                                                 v
//            ^  R                                                                                                                    ^                                  L  ^                                                                 v
// x->parent->right->left->left->left                                                                                                 ^                           x->parent->right->left->left->right                                         v
//                                                                                                                                    ^                                                                                                       v
//                                                                                                                                    <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// or

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                    v
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                           <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ^  v <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//            ^  v                                                                                                                                           v                                  ^  v                                                ^
//            ^  v                                                                                                                                           P                                  ^  v                                                ^
//            ^  v                                                                                                                                x->parent->parent >>>>>>>>>>>>>>>>>>>>>>>>>>> ^  v >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ^
//            ^  v                                                                                                                               v  P                                           ^  v                                             v  ^
//            ^  v                                                                                                                              v  ^                                            ^  v                                             v  ^
//            ^  v                                                                                                                             L  ^                                             ^  P                                             v  ^
//            ^  v                                                                                                         x->parent->parent->left       <<<<<<<<< xP = x->parent; x->parent->right->parent; x->parent->parent->right            v  ^
//            ^  v                                                                                                                                       v        v  P      L                                                                    v  ^
//            ^  v                                                                                                  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<       v  ^       ^                                                                    v  ^
//            ^  v                                                                                                  v                                           L  ^        ^                                                                    R  ^
//            ^  v                                                                                                  v                               x->parent->left         ^                                                        xPR = x->parent->right; x->parent->right->left->parent
//            ^  v                                                                                                  v                                                       ^                                                                 v
//            ^  v                                                                                                  v          >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                                                                 v
//            ^  v                                                                                                  v          ^                                                                                                              v
//            ^  v                                                                                                  v          ^            <<<<<<<<<<<<<<<<<<<<< xPRL = x->parent->right->left; x->parent->right->left->left->parent         v
//            ^  v                                                                                                  v          ^            v                    R  P    v  P                                                                 v
//            ^  v                                                                                                  v          ^            v                   ^  ^     v  ^                                                                 v
//            ^  v                                                                                                  P          ^            P                  ^  ^      v  ^                                                                 v
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent       v  ^                                                                 v
//            ^  v                                                                                                                    L                                  v  ^                                                                 v
//            ^  v                                                                                                                    ^                                  v  ^                                                                 v
//            ^  R                                                                                                                    ^                                  L  ^                                                                 v
// x->parent->right->left->left->left                                                                                                 ^                           x->parent->right->left->left->right                                         v
//                                                                                                                                    ^                                                                                                       v
//                                                                                                                                    <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  // 12 of 12
  xPRLL->parent = xPR;

// 0
// 1 1
// 2
// 3 3
// 4 4 4

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                     v                                x->parent->parent 0
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v                                       v  P   P  v
//            ^  v                                                                                                                                                                               ^  v                                       v  ^    ^  v
//            ^  v                                                                                                                                                                               ^  P                                       v  ^     ^  R
//            ^  v                                                                                                  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< xP = x->parent; x->parent->right->parent; x->parent->parent->left 3     v  ^      x->parent->parent->right 1
//            ^  v                                                                                                  v                                              v  P      L                                                              v  ^
//            ^  v                                                                                                  v                                             v  ^       ^                                                              v  ^
//            ^  v                                                                                                  v                                            L  ^        ^                                                              L  ^
//            ^  v                                                                                                  v                                x->parent->left 4       ^                                                       xPR = x->parent->right; x->parent->right->left->parent 1
//            ^  v                                                                                                  v                                                        ^                                                                v  P
//            ^  v                                                                                                  v          >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                                                                v  ^
//            ^  v                                                                                                  v          ^                                                                                                              v  ^
//            ^  v                                                                                                  v          ^            <<<<<<<<<<<<<<<<<<<<< xPRL = x->parent->right->left; x->parent->right->left->left->parent 3       v  ^
//            ^  v                                                                                                  v          ^            v                    R       v  P                                                                 v  ^
//            ^  v                                                                                                  v          ^            v                   ^        v  ^                                                                 v  ^
//            ^  v                                                                                                  P          ^            P                  ^         v  ^                                                                 v  ^
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent 2     v  ^                                                                 v  ^
//            ^  v                                                                                                        v           L                                  v  ^                                                                 v  ^
//            ^  v                                                                                                        v           ^                                  v  ^                                                                 v  ^
//            ^  R                                                                                                        v           ^                                  L  ^                                                                 v  ^
// x->parent->right->left->left->left 4                                                                                   v           ^                           x->parent->right->left->left->right 4                                       v  ^
//                                                                                                                        v           ^                                                                                                       v  ^
//                                                                                                                        v           <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  ^
//                                                                                                                        v                                                                                                                      ^
//                                                                                                                        >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
// to
//
//                                                                                                                                                                                                                                                                    x->parent->parent 0
//                                                                                                                                                                                                                                                                   v  P           P  v
//                                                                                                                                                                                                                                                                  v  ^             ^  v
//                                                                                                                                                                                                                                                                 L  ^               ^  R
//                                                                                                                                                                                                              xPR = x->parent->right; x->parent->right->left->parent 1               x->parent->parent->right 1
//                                                                                                                                                                                                             v  P
//                                                                                                                                                                                                            v  ^
//                                                                                                                                                                                                           L  ^
//                                                                                 xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent 2
//                                                                                v  P                                                                                                                       P  v
//                                                                               v  ^                                                                                                                         ^  v
//                                                                              L  ^                                                                                                                           ^  R
//                xP = x->parent; x->parent->right->parent; x->parent->parent->left 3                                                                                                                           xPRL = x->parent->right->left; x->parent->right->left->left->parent 3
//               v  P                                                           P  v                                                                                                                           v  P
//              v  ^                                                             ^  v                                                                                                                         v  ^
//             L  ^                                                               ^  R                                                                                                                       L  ^
// x->parent->left 4                                                               x->parent->right->left->left->left 4                                                      x->parent->right->left->left->right 4

// or

//            >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//            ^                                                                                                                                                                                    v
//            ^  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  v
//            ^  v                                                                                                                                                                              ^  v
//            ^  v                                                                                                                                           <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ^  v <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//            ^  v                                                                                                                                           v                                  ^  v                                                ^
//            ^  v                                                                                                                                           P                                  ^  v                                                ^
//            ^  v                                                                                                                                x->parent->parent 0 >>>>>>>>>>>>>>>>>>>>>>>>> ^  v >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ^
//            ^  v                                                                                                                               v  P                                           ^  v                                             v  ^
//            ^  v                                                                                                                              v  ^                                            ^  v                                             v  ^
//            ^  v                                                                                                                             L  ^                                             ^  P                                             v  ^
//            ^  v                                                                                                         x->parent->parent->left 1     <<<<<<<<< xP = x->parent; x->parent->right->parent; x->parent->parent->right 3          v  ^
//            ^  v                                                                                                                                       v        v  P      L                                                                    v  ^
//            ^  v                                                                                                  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<       v  ^       ^                                                                    v  ^
//            ^  v                                                                                                  v                                           L  ^        ^                                                                    R  ^
//            ^  v                                                                                                  v                               x->parent->left 4       ^                                                        xPR = x->parent->right; x->parent->right->left->parent 1
//            ^  v                                                                                                  v                                                       ^                                                                 v  P
//            ^  v                                                                                                  v          >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                                                                 v  ^
//            ^  v                                                                                                  v          ^                                                                                                              v  ^
//            ^  v                                                                                                  v          ^            <<<<<<<<<<<<<<<<<<<<< xPRL = x->parent->right->left; x->parent->right->left->left->parent 3       v  ^
//            ^  v                                                                                                  v          ^            v                    R       v  P                                                                 v  ^
//            ^  v                                                                                                  v          ^            v                   ^        v  ^                                                                 v  ^
//            ^  v                                                                                                  P          ^            P                  ^         v  ^                                                                 v  ^
//            ^  v                   xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent 2     v  ^                                                                 v  ^
//            ^  v                                                                                                        v           L                                  v  ^                                                                 v  ^
//            ^  v                                                                                                        v           ^                                  v  ^                                                                 v  ^
//            ^  R                                                                                                        v           ^                                  L  ^                                                                 v  ^
// x->parent->right->left->left->left 4                                                                                   v           ^                           x->parent->right->left->left->right 4                                       v  ^
//                                                                                                                        v           ^                                                                                                       v  ^
//                                                                                                                        v           <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  ^
//                                                                                                                        v                                                                                                                      ^
//                                                                                                                        >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
// to
//
//                                                                                                                                                                                                                                      x->parent->parent 0
//                                                                                                                                                                                                                                     v  P           P  v
//                                                                                                                                                                                                                                    v  ^             ^  v
//                                                                                                                                                                                                                                   L  ^               ^  R
//                                                                                                                                                                                                               x->parent->parent->left 1               xPR = x->parent->right; x->parent->right->left->parent 1
//                                                                                                                                                                                                                                                      v  P
//                                                                                                                                                                                                                                                     v  ^
//                                                                                                                                                                                                                                                    L  ^
//                                                                                                                          xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent 2
//                                                                                                                         v  P                                                                                                                       P  v
//                                                                                                                        v  ^                                                                                                                         ^  v
//                                                                                                                       L  ^                                                                                                                           ^  R
//                                                        xP = x->parent; x->parent->right->parent; x->parent->parent->right 3                                                                                                                           xPRL = x->parent->right->left; x->parent->right->left->left->parent 3
//                                                       v  P                                                            P  v                                                                                                                           v  P
//                                                      v  ^                                                              ^  v                                                                                                                         v  ^
//                                                     L  ^                                                                ^  R                                                                                                                       L  ^
//                                         x->parent->left 4                                                                x->parent->right->left->left->left 4                                                      x->parent->right->left->left->right 4
}

// integrated for root sentinel
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

// integrated for root sentinel
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

// integrated for root sentinel
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

// integrated for root sentinel
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

// integrated for root sentinel
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

#if 0
lessThan(lhs, rhs) return compare(lhs, rhs)
greaterThan(lhs, rhs) return compare(rhs, lhs)
equalTo(lhs, rhs) return !lessThan(lhs, rhs) && !greaterThan(lhs, rhs)
lessThanOrEqualTo(lhs, rhs) return lessThan(lhs, rhs) || !greaterThan(lhs, rhs)
greaterThanOrEqualTo(lhs, rhs) return greaterThan(lhs, rhs) || !lessThan(lhs, rhs)
#endif

// integrated for root sentinel
static void TreeInsert(BinaryTree* tree, BinaryTreeNode* insert)
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
static void BinInsert(BinaryTree* tree, BinaryTreeNode* x)
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

        LeftRightInsertRotate(x); // left-rotate(tree, x) -> right-rotate(tree, x->parent->parent) transformed 2B -> 3C

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

        RightRotate(xP->parent);
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

        RightLeftInsertRotate(x); // right-rotate(tree, x) -> left-rotate(tree, x->parent->parent) transformed 2B -> 3C

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

        LeftRotate(xP->parent); // 3C
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

// integrated for root sentinel
static BinaryTreeNode* TreeMinimum(BinaryTreeNode* node)
{
  for(BinaryTreeNode* left = node; left; left = left->left)
    node = left;

  return node;
}

// integrated for root sentinel
static BinaryTreeNode* TreeMaximum(BinaryTreeNode* node)
{
  for(BinaryTreeNode* right = node; right; right = right->right)
    node = right;

  return node;
}

//
// GetGreatest - An int which if TRUE, causes the greatest POTYPE
//               to be returned.  If FALSE, it causes the the least POTYPE
//               value to be returned.
//

// integrated for root sentinel
int bintree::getExtrema(int GetGreatest, void* objectReturn)
{
  BinaryTree* tree = (BinaryTree*)this;

  BinaryTreeNode* node = 0;

  if( !tree || (GetGreatest != TRUE && GetGreatest != FALSE) )
  {
    // BinGetExtrema(...) bad params
    _log("error");
    return RETURN_ERROR;
  }

  if(GetGreatest == FALSE)
  {
    node = TreeMinimum(GETROOTFROMTREE(tree) );
  }
  else /* GetGreatest == TRUE */
  {
    node = TreeMaximum(GETROOTFROMTREE(tree) );
  }

  if( !node)
  {
    // BinGetExtrema(...) empty tree
    return RETURN_ERROR;
  }

  if(objectReturn)
    memcpy(objectReturn, GETCLIENT(node), tree->SizeOfClientExact);

  return RETURN_OK;
}

static BinaryTreeNode* TreeSuccessor(BinaryTreeNode* x)
{
  BinaryTreeNode* y = 0;

  if(x->right)
    return TreeMinimum(x->right);

  for(y = x->parent; y && x == y->right; y = y->parent)
  {
    x = y;
  }

  return y;
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
static void BinDeleteFixup(BinaryTree* tree, BinaryTreeNode* x)
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

          LeftRotate(xP); // 1C

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
          RightLeftDeleteRotate(xP); // right-rotate(tree, w) -> left-rotate(tree, x->parent) transformed 3C -> 4D

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

          LeftRotate(xP); // 4D

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

          RightRotate(xP); // 1C

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
          LeftRightDeleteRotate(xP); // left-rotate(tree, w) -> right-rotate(tree, x->parent) transformed 3C -> 4D

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

          RightRotate(xP); // 4D

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
    memcpy(GETCLIENT(z), GETCLIENT(y), tree->SizeOfClientAligned);
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

// check if y is ever sentinelRoot

  return y;
}

// integrated for root sentinel
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

  *( --tree->MemoryManagerArrayCurrent) = (char*)z;

  tree->NumberOfNodes--;

  return RETURN_OK;
}

// integrated for root sentinel
int bintree::find(void* Object1, binaryTreeEquivalence EqualTo, void* ObjectReturn)
{
  BinaryTree* tree = (BinaryTree*)this;

  BinaryTreeNode* node = 0;

  if( !tree || !Object1)
  {
    // BinTreeFind(...) bad params
    _log("error");
    return RETURN_ERROR;
  }

  if(EqualTo)
    tree->EqualTo = EqualTo;

  if( !tree->EqualTo)
  {
    // BinTreeFind(...) NIL binaryTreeEquivalence function
    _log("error");
    return RETURN_ERROR;
  }

  node = TreeSearch(GETROOTFROMTREE(tree), Object1, tree->LessThan, tree->EqualTo);

  if(node)
  {
    if(ObjectReturn)
      memcpy(ObjectReturn, GETCLIENT(node), tree->SizeOfClientExact);

    return RETURN_OK;
  }

  return RETURN_ERROR;
}

// integrated for root sentinel
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

    SETROOTFROMTREE(tree, 0);

    return RETURN_OK;
  }

  // BinTreeReset(...) bad params
  _log("error");
  return RETURN_ERROR;
}

// integrated for root sentinel
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
//
// integrated for root sentinel
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
//
// integrated for root sentinel
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
//
// integrated for root sentinel
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
//
// integrated for root sentinel
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

// integrated for root sentinel
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

  root = GETROOTFROMTREE(tree);

  if(root)
  {
    switch(TraversalOrder)
    {
    case PREORDER: IterativePreorderTreeTraverse(tree, root, tree->ClientEvaluate); break;
    case INORDER: IterativeInorderTreeTraverse(tree, root, tree->ClientEvaluate); break;
    case POSTORDER: IterativePostorderTreeTraverse(tree, root, tree->ClientEvaluate); break;
    case LEVELORDER: IterativeLevelorderTreeTraverse(tree, root, tree->ClientEvaluate); break;
    }
  }

  return RETURN_OK;
}

// integrated for root sentinel
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

  return tree->NumberOfNodes;
}

// integrated for root sentinel
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

  // We need the nodel pool for the memory manager, with the size of the nodes
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
