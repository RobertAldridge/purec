
// File Name: binleftrightleft.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

#if 0
// LeftRotate(xP)
// LeftRotate(xPP)
static void LeftRotateDelete1(BinaryTreeNode* xP);
static void LeftRotateDelete2(BinaryTreeNode* xP);
static void LeftRotateInsert(BinaryTreeNode* xPP);

// LeftLeftRotate(xP)
static void LeftLeftRotate(BinaryTreeNode* xP);

// LeftRightRotate(x)
// LeftRightRotate(xP)
static void LeftRightRotateInsert(BinaryTreeNode* x);
static void LeftRightRotateDelete(BinaryTreeNode* xP);

// LeftRightLeftRotate(xP)
static void LeftRightLeftRotate(BinaryTreeNode* xP);
#endif

// integrated for root sentinel
void LeftRightLeftRotate(BinaryTreeNode* xP)
{
  BinaryTreeNode* xPR = xP->right;
  BinaryTreeNode* xPRL = xPR->left;
  BinaryTreeNode* xPRLL = xPRL->left;

  // 1 of 12
  xP->right = xPRLL->left;

  // 2 of 12
  if(xPRLL->left)
    xPRLL->left->parent = xP, gDebugRotate[16]++;
  else
    gDebugRotate[17]++;

  // 3 of 12
  xPRL->left = xPRLL->right;

  // 4 of 12
  if(xPRLL->right)
    xPRLL->right->parent = xPRL, gDebugRotate[18]++;
  else
    gDebugRotate[19]++;

  // 5 of 12
  xPRL->parent = xPRLL;

  // 6 of 12
  xPRLL->right = xPRL;

  // 7 of 12
  if(xP == xP->parent->left)
    xP->parent->left = xPR, gDebugRotate[52]++;
  else /* xP == xP->parent->right */
    xP->parent->right = xPR, gDebugRotate[53]++;

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

#if 0
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
//                                                                                                                                                                                              x->parent->parent 0
//                                                                                                                                                                                             v  P           P  v
//                                                                                                                                                                                            v  ^             ^  v
//                                                                                                                                                                                           L  ^               ^  R
//                                                                                                                                                                       x->parent->parent->left 1               xPR = x->parent->right; x->parent->right->left->parent 1
//                                                                                                                                                                                                              v  P
//                                                                                                                                                                                                             v  ^
//                                                                                                                                                                                                            L  ^
//                                                                                  xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent 2
//                                                                                 v  P                                                                                                                       P  v
//                                                                                v  ^                                                                                                                         ^  v
//                                                                               L  ^                                                                                                                           ^  R
//                xP = x->parent; x->parent->right->parent; x->parent->parent->right 3                                                                                                                           xPRL = x->parent->right->left; x->parent->right->left->left->parent 3
//               v  P                                                            P  v                                                                                                                           v  P
//              v  ^                                                              ^  v                                                                                                                         v  ^
//             L  ^                                                                ^  R                                                                                                                       L  ^
// x->parent->left 4                                                                x->parent->right->left->left->left 4                                                      x->parent->right->left->left->right 4

// integrated for root sentinel
void LeftRightLeftRotate(BinaryTreeNode* xP)
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
//                                                                                                                                                                                              x->parent->parent 0
//                                                                                                                                                                                             v  P           P  v
//                                                                                                                                                                                            v  ^             ^  v
//                                                                                                                                                                                           L  ^               ^  R
//                                                                                                                                                                       x->parent->parent->left 1               xPR = x->parent->right; x->parent->right->left->parent 1
//                                                                                                                                                                                                              v  P
//                                                                                                                                                                                                             v  ^
//                                                                                                                                                                                                            L  ^
//                                                                                  xPRLL = x->parent->right->left->left; x->parent->right->left->left->left->parent; x->parent->right->left->left->right->parent 2
//                                                                                 v  P                                                                                                                       P  v
//                                                                                v  ^                                                                                                                         ^  v
//                                                                               L  ^                                                                                                                           ^  R
//                xP = x->parent; x->parent->right->parent; x->parent->parent->right 3                                                                                                                           xPRL = x->parent->right->left; x->parent->right->left->left->parent 3
//               v  P                                                            P  v                                                                                                                           v  P
//              v  ^                                                              ^  v                                                                                                                         v  ^
//             L  ^                                                                ^  R                                                                                                                       L  ^
// x->parent->left 4                                                                x->parent->right->left->left->left 4                                                      x->parent->right->left->left->right 4
}
#endif
