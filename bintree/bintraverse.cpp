
// File Name: bintraverse.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// 24.2.7.1

// 175
// The insert, insert_range, and emplace members shall not affect the validity of iterators and references to
// the container, and the erase members shall invalidate only iterators and references to the erased elements.

// 176
// The extract members invalidate only iterators to the removed element; pointers and references to the
// removed element remain valid. However, accessing the element through such pointers and references while
// the element is owned by a node_type is undefined behavior. References and pointers to an element obtained
// while it is owned by a node_type are invalidated if the element is successfully inserted.

// 177
// The fundamental property of iterators of associative containers is that they iterate through the containers
// in the non-descending order of keys where non-descending is defined by the comparison that was used to
// construct them. For any two dereferenceable iterators i and j such that distance from i to j is positive, the
// following condition holds:
//
//   value_comp(*j, *i) == false

// 178
// For associative containers with unique keys the stronger condition holds:
//
//   value_comp(*i, *j) != false

// pre order
//
// stack

// in order
//
// stack

// post order
//
// stack

// level order
//
// queue

// Preorder is fully optimized
//
// integrated for root sentinel
void IterativePreorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate)
{
  // PSTACK Stack = InitStack()
  //BinaryTreeNode** StackTraverseArrayStart = tree->TraverseArrayStart;
  //BinaryTreeNode** StackTraverseArrayCurrentTop = StackTraverseArrayStart;

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
        //*StackTraverseArrayCurrentTop++ = RightChild;
        if( !SsmmStackPush(tree->stackAllocator, RightChild) )
          break;
        
        //ptrdiff_t stackSize = StackTraverseArrayCurrentTop - StackTraverseArrayStart;
        ptrdiff_t stackSize = SsmmNum(tree->stackAllocator);
        if(stackSize >= 0 && stackSize > tree->maxStack)
          tree->maxStack = (int)stackSize;

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
      //if(StackTraverseArrayCurrentTop == StackTraverseArrayStart)
      if(SsmmNum(tree->stackAllocator) <= 0)
        break;

      // node = Stack->Pop()
      //node = *( --StackTraverseArrayCurrentTop);
      node = (BinaryTreeNode*)SsmmStackPop(tree->stackAllocator);
      if( !node)
        break;
    }
  }

  while(SsmmNum(tree->stackAllocator) > 0)
  {
    if( !SsmmStackPop(tree->stackAllocator) )
      break;
  }
}

// pre order
//
// set 'node' to root
//
// label pushLeftAllTheWayDown:
//
// start at 'node' push the lefts all the way down
//
// 'node' <= pop the deepest left, which we know has a null left
//
// evaluate 'node'
//
// if 'node' has a non-null right
//   'node' <= 'node'->right and goto label pushLeftAllTheWayDown

// Inorder requires one extra optimization-
// When the left nodes are pushed on the stack,
// a left node is immediately popped off of the stack
// after you break out of the inner loop.
//
// integrated for root sentinel
void IterativeInorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate)
{
  // PSTACK Stack = InitStack()
  //BinaryTreeNode** StackTraverseArrayStart = tree->TraverseArrayStart;
  //BinaryTreeNode** StackTraverseArrayCurrentTop = StackTraverseArrayStart;

  while(1)
  {
// label pushLeftAllTheWayDown:

    while(node)
    {
      // Stack->Push(node)
      //*StackTraverseArrayCurrentTop++ = node;
      if( !SsmmStackPush(tree->stackAllocator, node) )
        break;

      node = node->left;
    }
    
    //ptrdiff_t stackSize = StackTraverseArrayCurrentTop - StackTraverseArrayStart;
    ptrdiff_t stackSize = SsmmNum(tree->stackAllocator);
    if(stackSize >= 0 && stackSize > tree->maxStack)
      tree->maxStack = (int)stackSize;

    // if(Stack->Empty() == TRUE)
    //if(StackTraverseArrayCurrentTop == StackTraverseArrayStart)
    if(SsmmNum(tree->stackAllocator) <= 0)
      break;

    // node = Stack->Pop()
    //node = *( --StackTraverseArrayCurrentTop);
    node = (BinaryTreeNode*)SsmmStackPop(tree->stackAllocator);
    if( !node)
      break;

    if(ClientEvaluate(GETCLIENT(node) ) )
      break;

    node = node->right;
  }

  while(SsmmNum(tree->stackAllocator) > 0)
  {
    if( !SsmmStackPop(tree->stackAllocator) )
      break;
  }
}

// post order
//
// set 'node' to root
//
// label pushLeftAllTheWayDown:
//
// start at 'node' push the lefts all the way down
//
// label popOneOffStack:
//
// 'node' <= pop the deepest left, which we know has a null left
//
// if 'node' has a non-null right
//   push 'node' back on (even though we've just popped it off)
//   'node' <= 'node'->right and goto label pushLeftAllTheWayDown
// else if 'node' has a null right
//   evaluate 'node' and goto popOneOffStack

// ! I have no idea if Postorder is fully optimized or not!
// I optimized it alot, but I am still not sure if it is fully optimized.
// Function courtesy of Bruce Mcquistan ( brucemc@digipen.edu )
//
// integrated for root sentinel
void IterativePostorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate)
{
  // PSTACK Stack = InitStack()
  //BinaryTreeNode** StackTraverseArrayStart = tree->TraverseArrayStart;
  //BinaryTreeNode** StackTraverseArrayCurrentTop = StackTraverseArrayStart;

  BinaryTreeNode* NodePushed = 0;
  BinaryTreeNode* RightChild = 0;

  while(1)
  {
// label pushLeftAllTheWayDown:

    do
    {
      // Stack->Push(node)
      //*StackTraverseArrayCurrentTop++ = node;
      if( !SsmmStackPush(tree->stackAllocator, node) )
        break;

      node = node->left;

    }while(node);

popOneOffStack:

    //ptrdiff_t stackSize = StackTraverseArrayCurrentTop - StackTraverseArrayStart;
    ptrdiff_t stackSize = SsmmNum(tree->stackAllocator);
    if(stackSize >= 0 && stackSize > tree->maxStack)
      tree->maxStack = (int)stackSize;

    // if(Stack->Empty() == TRUE)
    //if(StackTraverseArrayCurrentTop == StackTraverseArrayStart)
    if(SsmmNum(tree->stackAllocator) <= 0)
      break;

    // node = Stack->Pop()
    //node = *( --StackTraverseArrayCurrentTop);
    node = (BinaryTreeNode*)SsmmStackPop(tree->stackAllocator);
    if( !node)
      break;

    RightChild = node->right;

    if(RightChild && RightChild != NodePushed)
    {
      // Stack->Push(node)
      //*StackTraverseArrayCurrentTop++ = node;
      if( !SsmmStackPush(tree->stackAllocator, node) )
        break;

      NodePushed = RightChild;

      node = RightChild;

      continue;
    }
    else
    {
      if(ClientEvaluate(GETCLIENT(node) ) )
        break;

      NodePushed = node;

      node = 0;

      goto popOneOffStack;
    }
  }

  while(SsmmNum(tree->stackAllocator) > 0)
  {
    if( !SsmmStackPop(tree->stackAllocator) )
      break;
  }
}

// Levelorder is fully optimized
//
// integrated for root sentinel
void IterativeLevelorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate)
{
  // PQUEUE Queue = InitQueue()
  BinaryTreeNode** QueueTraverseArrayCurrentFront = tree->TraverseArrayStart;
  BinaryTreeNode** QueueTraverseArrayCurrentBack = QueueTraverseArrayCurrentFront;

  BinaryTreeNode* LeftChild = 0;
  BinaryTreeNode* RightChild = 0;

  // Queue->Put(node)
  *QueueTraverseArrayCurrentBack++ = node;

  // while(Queue->Empty() != TRUE)
  while(QueueTraverseArrayCurrentFront != QueueTraverseArrayCurrentBack)
  {
    ptrdiff_t queueSize = QueueTraverseArrayCurrentBack - QueueTraverseArrayCurrentFront;
    if(queueSize > tree->maxQueue)
      tree->maxQueue = (int)queueSize;

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
