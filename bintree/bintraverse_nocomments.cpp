
// File Name: bintraverse.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
void IterativePreorderTreeTraverse(ssSet* tree, SsSetNode* node, binaryTreeEvaluate ClientEvaluate)
{
  uint32_t stackSize = 0;

  // PSTACK Stack = InitStack()
  SsStackReset(tree->stack);

  SsSetNode* LeftChild = 0;
  SsSetNode* RightChild = 0;

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

        stackSize = 0;
        if(SsStackNum(tree->stack, &stackSize) && stackSize > tree->maxStack)
          tree->maxStack = stackSize;

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
      stackSize = 0;
      // if(Stack->Empty() == TRUE)
      if( !SsStackNum(tree->stack, &stackSize) || !stackSize)
        break;

      // node = Stack->Pop()
      if( !SsStackPop(tree->stack, &node) )
        break;
    }
  }
}

// integrated for root sentinel
void IterativeInorderTreeTraverse(ssSet* tree, SsSetNode* node, binaryTreeEvaluate ClientEvaluate)
{
  uint32_t stackSize = 0;

  // PSTACK Stack = InitStack()
  SsStackReset(tree->stack);

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

    stackSize = 0;
    if(SsStackNum(tree->stack, &stackSize) && stackSize > tree->maxStack)
      tree->maxStack = stackSize;

    // if(Stack->Empty() )
    if( !stackSize)
      break;

    // node = Stack->Pop()
    if( !SsStackPop(tree->stack, &node) )
      break;

    if(ClientEvaluate(GETCLIENT(node) ) )
      break;

    node = node->right;
  }
}

// integrated for root sentinel
void IterativePostorderTreeTraverse(ssSet* tree, SsSetNode* node, binaryTreeEvaluate ClientEvaluate)
{
  uint32_t stackSize = 0;

  // PSTACK Stack = InitStack()
  SsStackReset(tree->stack);

  SsSetNode* NodePushed = 0;
  SsSetNode* RightChild = 0;

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

    stackSize = 0;
    if(SsStackNum(tree->stack, &stackSize) && stackSize > tree->maxStack)
      tree->maxStack = stackSize;

    // if(Stack->Empty() )
    if( !stackSize)
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
}

// integrated for root sentinel
void IterativeLevelorderTreeTraverse(ssSet* tree, SsSetNode* node, binaryTreeEvaluate ClientEvaluate)
{
  uint32_t queueSize = 0;

  // PQUEUE Queue = InitQueue()
  SsQueueReset(tree->queue);

  SsSetNode* LeftChild = 0;
  SsSetNode* RightChild = 0;

  // Queue->Put( &node)
  if( !SsQueuePushBack(tree->queue, &node) )
    goto error;

  queueSize = 0;

  // while( !Queue->Empty() )
  while(SsQueueNum(tree->queue, &queueSize) && queueSize)
  {
    if(queueSize > tree->maxQueue)
      tree->maxQueue = queueSize;

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

    queueSize = 0;
  }

error:
  return;
}

// integrated for root sentinel
bool SsSetDump(ssSet* _this, SsSetEvaluate evaluate, int order)
{
  bool result = false;

  SsSetNode* root = 0;

  if( !_this || order < SsSetPreorder || order > SsSetLevelorder)
  {
    _log("error");
    goto error;
  }

  if( !evaluate && !_this->evaluate)
  {
    _log("error");
    goto error;
  }

  if(evaluate)
    _this->evaluate = evaluate;

  root = GETROOTFROMTREE(_this);

  if(root)
  {
    switch(order)
    {
    case SsSetPreorder: IterativePreorderTreeTraverse(_this, root, _this->evaluate); break;
    case SsSetInorder: IterativeInorderTreeTraverse(_this, root, _this->evaluate); break;
    case SsSetPostorder: IterativePostorderTreeTraverse(_this, root, _this->evaluate); break;
    case SsSetLevelorder: IterativeLevelorderTreeTraverse(_this, root, _this->evaluate); break;
    }
  }

  result = true;

error:
  return result;
}
