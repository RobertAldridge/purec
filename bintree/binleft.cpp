
// File Name: binleft.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

#if 0
// LeftRotate(xP)
// LeftRotate(xPP)
static void LeftRotate(BinaryTreeNode* x);

// LeftLeftRotate(xP)
static void LeftLeftRotate(BinaryTreeNode* xP);

// LeftRightInsertRotate(x)
static void LeftRightInsertRotate(BinaryTreeNode* x);

// LeftRightDeleteRotate(xP)
static void LeftRightDeleteRotate(BinaryTreeNode* xP);

// LeftRightLeftRotate(xP)
static void LeftRightLeftRotate(BinaryTreeNode* xP);
#endif

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
void LeftRotate(BinaryTreeNode* x)
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
