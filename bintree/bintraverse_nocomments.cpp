
// File Name: bintraverse.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void IterativePreorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate)
{
  // PSTACK Stack = InitStack()

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
        // Stack->Push( &RightChild)
        if( !SsStackPush(tree->stack, &RightChild) )
          break;

        ptrdiff_t stackSize = SsStackNum(tree->stack);
        if(stackSize >= 0 && stackSize > tree->maxStack)
          tree->maxStack = (int)stackSize;

        // Stack->Push( &LeftChild)
        // node = Stack->Pop()
        node = LeftChild;
      }
      else /* !node->left */
      {
        // Stack->Push( &RightChild)
        // node = Stack->Pop()
        node = RightChild;
      }
    }
    else if(LeftChild)
    {
      // Stack->Push( &LeftChild)
      // node = Stack->Pop()
      node = LeftChild;
    }
    else
    {
      // if(Stack->Empty() == TRUE)
      if(SsStackNum(tree->stack) <= 0)
        break;

      // node = Stack->Pop()
      if( !SsStackPop(tree->stack, &node) )
        break;
    }
  }

  SsStackReset(tree->stack);
}

// integrated for root sentinel
void IterativeInorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate)
{
  // PSTACK Stack = InitStack()

  while(1)
  {
// label pushLeftAllTheWayDown:

    while(node)
    {
      // Stack->Push( &node)
      if( !SsStackPush(tree->stack, &node) )
        break;

      node = node->left;
    }

    ptrdiff_t stackSize = SsStackNum(tree->stack);
    if(stackSize >= 0 && stackSize > tree->maxStack)
      tree->maxStack = (int)stackSize;

    // if(Stack->Empty() )
    if(SsStackNum(tree->stack) <= 0)
      break;

    // node = Stack->Pop()
    if( !SsStackPop(tree->stack, &node) )
      break;

    if(ClientEvaluate(GETCLIENT(node) ) )
      break;

    node = node->right;
  }

  SsStackReset(tree->stack);
}

// integrated for root sentinel
void IterativePostorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate)
{
  // PSTACK Stack = InitStack()

  BinaryTreeNode* NodePushed = 0;
  BinaryTreeNode* RightChild = 0;

  while(1)
  {
// label pushLeftAllTheWayDown:

    do
    {
      // Stack->Push( &node)
      if( !SsStackPush(tree->stack, &node) )
        break;

      node = node->left;

    }while(node);

popOneOffStack:

    ptrdiff_t stackSize = SsStackNum(tree->stack);
    if(stackSize >= 0 && stackSize > tree->maxStack)
      tree->maxStack = (int)stackSize;

    // if(Stack->Empty() )
    if(SsStackNum(tree->stack) <= 0)
      break;

    // node = Stack->Pop()
    if( !SsStackPop(tree->stack, &node) )
      break;

    RightChild = node->right;

    if(RightChild && RightChild != NodePushed)
    {
      // Stack->Push( &node)
      if( !SsStackPush(tree->stack, &node) )
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

  SsStackReset(tree->stack);
}

// integrated for root sentinel
void IterativeLevelorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate)
{
  // PQUEUE Queue = InitQueue()

  BinaryTreeNode* LeftChild = 0;
  BinaryTreeNode* RightChild = 0;

  // Queue->Put( &node)
  if( !SsQueuePushBack(tree->queue, &node) )
    goto error;

  // while( !Queue->Empty() )
  while(SsQueueNum(tree->queue) > 0)
  {
    ptrdiff_t queueSize = SsQueueNum(tree->queue);
    if(queueSize > tree->maxQueue)
      tree->maxQueue = (int)queueSize;

    // Queue->Get()
    if( !SsQueuePopFront(tree->queue, &node) )
      break;

    if(ClientEvaluate(GETCLIENT(node) ) )
      break;

    LeftChild = node->left;
    RightChild = node->right;

    if(LeftChild)
    {
      // Queue->Put( &LeftChild)
      if( !SsQueuePushBack(tree->queue, &LeftChild) )
        break;
    }

    if(RightChild)
    {
      // Queue->Put( &RightChild)
      if( !SsQueuePushBack(tree->queue, &RightChild) )
        break;
    }
  }

error:
  SsQueueReset(tree->queue);
}

// integrated for root sentinel
int bintree::dump(binaryTreeEvaluate clientEvaluate, ORDER TraversalOrder)
{
  BinaryTree* tree = (BinaryTree*)this;
  
  int result = RETURN_ERROR;

  BinaryTreeNode* root = 0;

  if( !tree || TraversalOrder < PREORDER || TraversalOrder > LEVELORDER)
  {
    _log("error");
    goto error;
  }

  if( !clientEvaluate && !tree->clientEvaluate)
  {
    _log("error");
    goto error;
  }

  if(clientEvaluate)
    tree->clientEvaluate = clientEvaluate;

  root = GETROOTFROMTREE(tree);

  if(root)
  {
    switch(TraversalOrder)
    {
    case PREORDER: IterativePreorderTreeTraverse(tree, root, tree->clientEvaluate); break;
    case INORDER: IterativeInorderTreeTraverse(tree, root, tree->clientEvaluate); break;
    case POSTORDER: IterativePostorderTreeTraverse(tree, root, tree->clientEvaluate); break;
    case LEVELORDER: IterativeLevelorderTreeTraverse(tree, root, tree->clientEvaluate); break;
    }
  }

  result = RETURN_OK;

error:
  return result;
}
