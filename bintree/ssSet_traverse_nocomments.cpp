
// file name bintraverse.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
int64_t IterativePreorderTreeTraverse(ssSet* _this, SsSetNode* node, SsSetEvaluate evaluate)
{
  bool result = false;

  uint32_t callback = 0;

  int64_t stackNum = 0;

  if( !node)
    goto label_num;

  // Stack* stack = StackInit()
  if(SsStackReset(_this->stack) < 0)
    goto label_return;

  while(1)
  {
    SsSetNode* left = 0;
    SsSetNode* right = 0;

    callback = evaluate(GETCLIENT(node) );
    if(callback)
      break;

    left = node->left;
    right = node->right;

    if(right)
    {
      if(left)
      {
        if( !SsStackPush(_this->stack, &right) )
          goto label_return;

        // we only get num here for debugging in non-production so ignore error
        stackNum = SsStackNum(_this->stack);
        if(stackNum > _this->maxStack)
          _this->maxStack = stackNum;

        // stack->push( &left)
        // node = stack->pop()
        node = left;
      }
      else /* !node->left */
      {
        // stack->push( &right)
        // node = stack->pop()
        node = right;
      }
    }
    else if(left)
    {
      // stack->push( &left)
      // node = stack->pop()
      node = left;
    }
    else
    {
      // if(stack->empty() )
      stackNum = SsStackNum(_this->stack);
      if(stackNum <= 0)
        break;

      if( !SsStackPop(_this->stack, &node) )
        goto label_return;
    }
  }

label_num:
  if(stackNum < 0)
    goto label_return;

  result = true;

label_return:
  return result ? (int64_t)callback : -1;
}

// integrated for root sentinel
int64_t IterativeInorderTreeTraverse(ssSet* _this, SsSetNode* node, SsSetEvaluate evaluate)
{
  bool result = false;

  uint32_t callback = 0;

  int64_t stackNum = 0;

  if( !node)
    goto label_num;

  // Stack* stack = StackInit()
  if(SsStackReset(_this->stack) < 0)
    goto label_return;

  while(1)
  {
    while(node)
    {
      if( !SsStackPush(_this->stack, &node) )
        goto label_return;

      node = node->left;
    }

    // if(stack->empty() )
    stackNum = SsStackNum(_this->stack);
    if(stackNum <= 0)
      break;

    // debugging in non-production
    if(stackNum > _this->maxStack)
      _this->maxStack = stackNum;

    if( !SsStackPop(_this->stack, &node) )
      goto label_return;

    callback = evaluate(GETCLIENT(node) );
    if(callback)
      break;

    node = node->right;
  }

label_num:
  if(stackNum < 0)
    goto label_return;

  result = true;

label_return:
  return result ? (int64_t)callback : -1;
}

// integrated for root sentinel
int64_t IterativePostorderTreeTraverse(ssSet* _this, SsSetNode* node, SsSetEvaluate evaluate)
{
  bool result = false;

  uint32_t callback = 0;

  int64_t stackNum = 0;

  SsSetNode* parent = 0;

  if( !node)
    goto label_num;

  // Stack* stack = StackInit()
  if(SsStackReset(_this->stack) < 0)
    goto label_return;

  while(1)
  {
    SsSetNode* right = 0;

    do
    {
      if( !SsStackPush(_this->stack, &node) )
        goto label_return;

      node = node->left;

    }while(node);

    do
    {
      // if(stack->empty() )
      stackNum = SsStackNum(_this->stack);
      if(stackNum <= 0)
        goto label_num;

      // debugging in non-production
      if(stackNum > _this->maxStack)
        _this->maxStack = stackNum;

      if( !SsStackPop(_this->stack, &node) )
        goto label_return;

      right = node->right;

      if(right && right != parent)
      {
        if( !SsStackPush(_this->stack, &node) )
          goto label_return;

        parent = right;
        node = right;
      }
      else
      {
        callback = evaluate(GETCLIENT(node) );
        if(callback)
          goto label_num;

        parent = node;
        node = 0;
      }

    }while( !node);
  }

label_num:
  if(stackNum < 0)
    goto label_return;

  result = true;

label_return:
  return result ? (int64_t)callback : -1;
}

// integrated for root sentinel
int64_t IterativeLevelorderTreeTraverse(ssSet* _this, SsSetNode* node, SsSetEvaluate evaluate)
{
  bool result = false;

  uint32_t callback = 0;

  int64_t queueNum = 0;

  if( !node)
    goto label_num;

  // Queue* queue = QueueInit()
  if(SsQueueReset(_this->queue) < 0)
    goto label_return;

  if( !SsQueuePushBack(_this->queue, &node) )
    goto label_return;

  // do { } while( !queue->empty() )
  do
  {
    SsSetNode* left = 0;
    SsSetNode* right = 0;

    // we only get num here for debugging in non-production so ignore error
    queueNum = SsQueueNum(_this->queue);
    if(queueNum > _this->maxQueue)
      _this->maxQueue = queueNum;

    if( !SsQueuePopFront(_this->queue, &node) )
      goto label_return;

    callback = evaluate(GETCLIENT(node) );
    if(callback)
      break;

    left = node->left;
    right = node->right;

    if(left)
    {
      if( !SsQueuePushBack(_this->queue, &left) )
        goto label_return;
    }

    if(right)
    {
      if( !SsQueuePushBack(_this->queue, &right) )
        goto label_return;
    }

    queueNum = SsQueueNum(_this->queue);

  }while(queueNum > 0);

label_num:
  if(queueNum < 0)
    goto label_return;

  result = true;

label_return:
  return result ? (int64_t)callback : -1;
}

#if 0
static int64_t(*gSsSetIterativeTreeTraverse)(ssSet* _this, SsSetNode* node, SsSetEvaluate evaluate)[4] =
{
  IterativePreorderTreeTraverse,
  IterativeInorderTreeTraverse,
  IterativePostorderTreeTraverse,
  IterativeLevelorderTreeTraverse
};
#endif

// integrated for root sentinel
int64_t SsSetDump(ssSet* _this, SsSetEvaluate evaluate, int order)
{
  bool result = false;

  int64_t dump = 0;

  SsSetNode* root = 0;

  if( !_this || order < SsSetPreorder || order > SsSetLevelorder)
  {
    _log("error");
    goto label_return;
  }

  if( !evaluate && !_this->evaluate)
  {
    _log("error");
    goto label_return;
  }

  // root
  // leaf
  // lessThan
  // equalTo
  // evaluate
  // allocator
  // stack
  // queue
  // maxStack
  // maxQueue
  // num
  // sizeOf

  // no change
  // -----
  // root
  // leaf
  // lessThan
  // equalTo
  // allocator
  // num
  // sizeOf

  // touched in this function
  // -----
  // evaluate
  // stack IterativePreorderTreeTraverse IterativeInorderTreeTraverse IterativePostorderTreeTraverse
  // queue IterativeLevelorderTreeTraverse
  // maxStack IterativePreorderTreeTraverse IterativeInorderTreeTraverse IterativePostorderTreeTraverse
  // maxQueue IterativeLevelorderTreeTraverse

  if(evaluate)
    _this->evaluate = evaluate;

  root = GETROOTFROMTREE(_this);

  switch(order)
  {
  case SsSetPreorder: dump = IterativePreorderTreeTraverse(_this, root, _this->evaluate); break;
  case SsSetInorder: dump = IterativeInorderTreeTraverse(_this, root, _this->evaluate); break;
  case SsSetPostorder: dump = IterativePostorderTreeTraverse(_this, root, _this->evaluate); break;
  case SsSetLevelorder: dump = IterativeLevelorderTreeTraverse(_this, root, _this->evaluate); break;
  }

  if(dump < 0)
  {
    _log("error");
    goto label_return;
  }

  result = true;

label_return:
  return result ? dump : -1;
}
