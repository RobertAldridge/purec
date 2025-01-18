
// ssSetDump.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// integrated for root sentinel
int64_t SsSetDumpLevel2preorder(ssSet* _this, SsSetNode* node, SsSetEvaluate evaluate)
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
      if(left) // if node->left && node->right
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
      else // if !node->left && node->right
      {
        // stack->push( &right)
        // node = stack->pop()
        node = right;
      }
    }
    else if(left) // if node->left && !node->right
    {
      // stack->push( &left)
      // node = stack->pop()
      node = left;
    }
    else // if !node->left && !node->right
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
  return result ? (int64_t)callback : SsSetError;
}

// integrated for root sentinel
int64_t SsSetDumpLevel2inorder(ssSet* _this, SsSetNode* node, SsSetEvaluate evaluate)
{
  bool result = false;

  uint32_t callback = 0;

  int64_t stackNum = 0;

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

  if(stackNum < 0)
    goto label_return;

  result = true;

label_return:
  return result ? (int64_t)callback : SsSetError;
}

// integrated for root sentinel
int64_t SsSetIsBegin(ssSet* _this)
{
  bool result = false;

  int begin = 0;

  if( !_this)
    goto label_return;

  // check for index bounds
  if(_this->index < 0 || _this->index > _this->num)
    goto label_return;
  
  // check for end iterator conditions; both conditions must be true
  if(_this->iterator == &_this->end && _this->index == _this->num)
    goto label_num;
  
  // if not end iterator then verify neither condition is true
  if(_this->iterator == &_this->end || _this->index == _this->num)
    goto label_return;
  
  // if we get here then we are at a valid index and current must be valid

  // verify current is valid
  if( !_this->current)
    goto label_return;

  // check whether we are at begin
  if( !_this->index)
    begin = 1;

label_num:
  result = true;

label_return:
  return result ? begin : SsSetError;
}

// integrated for root sentinel
int64_t SsSetIsEnd(ssSet* _this)
{
  bool result = false;

  int end = 1;

  if( !_this)
    goto label_return;

  // check for index bounds
  if(_this->index < 0 || _this->index > _this->num)
    goto label_return;
  
  // check for end iterator conditions; both conditions must be true
  if(_this->iterator == &_this->end && _this->index == _this->num)
    goto label_num;
  
  // if not end iterator then verify neither condition is true
  if(_this->iterator == &_this->end || _this->index == _this->num)
    goto label_return;
  
  // if we get here then we are at a valid index and current must be valid

  // verify current is valid
  if( !_this->current)
    goto label_return;
  
  end = 0;

label_num:
  result = true;

label_return:
  return result ? end : SsSetError;
}

// integrated for root sentinel
int64_t SsSetGetCurrent(ssSet* _this, void* client)
{
  bool result = false;

  int end = 1;

  if( !_this || !client)
    goto label_return;

  // check for index bounds
  if(_this->index < 0 || _this->index > _this->num)
    goto label_return;
  
  // check for end iterator conditions; both conditions must be true
  if(_this->iterator == &_this->end && _this->index == _this->num)
    goto label_num;
  
  // if not end iterator then verify neither condition is true
  if(_this->iterator == &_this->end || _this->index == _this->num)
    goto label_return;
  
  // if we get here then we are at a valid index and current must be valid

  // verify current is valid
  if( !_this->current)
    goto label_return;

  end = 0;

  memcpy(client, GETCLIENT(_this->current), _this->sizeOf);

label_num:
  result = true;

label_return:
  return result ? end : SsSetError;
}

// integrated for root sentinel
int64_t SsSetGetNext(ssSet* _this, bool reset, void* client)
{
  bool result = false;

  int end = 1;

  if( !_this || !client)
    goto label_return;
  
  // check for index bounds
  if(_this->index < 0 || _this->index > _this->num)
    goto label_return;

  // we stay at end unless forced to reset, but it's also not an error
  //
  // we refuse the request to reset if the set is empty, but it's also not an error
  if(reset && _this->num > 0)
  {
    if(SsStackReset(_this->stack) < 0)
      goto label_return;
    
    _this->iterator = GETROOTFROMTREE(_this);
    _this->current = 0;
    _this->index = -1;
  }
  // check for end iterator conditions; both conditions must be true
  else if(_this->iterator == &_this->end && _this->index == _this->num)
  {
    goto label_num;
  }
  // if not end iterator then verify neither condition is true
  else if(_this->iterator == &_this->end || _this->index == _this->num)
  {
    goto label_return;
  }
  // if we get here then we are at a valid index and current must be valid
  //
  // verify current is valid
  else if( !_this->current)
  {
    goto label_return;
  }
  // if the previous iteration ended at the last element, then set end
  else if(_this->index == (int64_t)_this->num - 1)
  {
    _this->iterator = &_this->end;
    _this->current = 0;
    _this->index = _this->num;
    goto label_num;
  }

  // _this->iterator != null
  // _this->iterator != &_this->end
  // _this->index >= -1
  // _this->index < _this->num - 1

  do
  {
    SsSetNode* node = _this->iterator;

    while(node)
    {
      if( !SsStackPush(_this->stack, &node) )
        goto label_return;

      node = node->left;
    }

    // in this context it is also considered an error if the stack is empty
    if(SsStackNum(_this->stack) <= 0)
      goto label_return;

    if( !SsStackPop(_this->stack, &node) )
      goto label_return;

    memcpy(client, GETCLIENT(node), _this->sizeOf);
    
    _this->current = node;

    node = node->right;

    _this->iterator = node;

    _this->index++;

    end = 0;

  }while(0);

label_num:
  result = true;

  // _this->iterator != null
  // _this->iterator != &_this->end
  // _this->index >= 0
  // _this->index < _this->num

label_return:
  if( !result)
    BlahLog2("error\n");
  
  return result ? end : SsSetError;
}

// integrated for root sentinel
int64_t SsSetDumpLevel2postorder(ssSet* _this, SsSetNode* node, SsSetEvaluate evaluate)
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
  return result ? (int64_t)callback : SsSetError;
}

// integrated for root sentinel
int64_t SsSetDumpLevel2levelorder(ssSet* _this, SsSetNode* node, SsSetEvaluate evaluate)
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
  return result ? (int64_t)callback : SsSetError;
}

// integrated for root sentinel
int64_t SsSetDump(ssSet* _this, SsSetEvaluate evaluate, int order)
{
  bool result = false;

  int64_t dump = 0;

  SsSetNode* root = 0;

  if( !_this || order < SsSetPreorder || order > SsSetLevelorder)
  {
    BlahLog("error");
    goto label_return;
  }

  if( !evaluate && !_this->evaluate)
  {
    BlahLog("error");
    goto label_return;
  }

  // root
  // leaf
  // lessThan
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
  // allocator
  // num
  // sizeOf

  // touched in this function
  // -----
  // evaluate
  // stack SsSetDumpLevel2preorder SsSetDumpLevel2inorder SsSetDumpLevel2postorder
  // queue SsSetDumpLevel2levelorder
  // maxStack SsSetDumpLevel2preorder SsSetDumpLevel2inorder SsSetDumpLevel2postorder
  // maxQueue SsSetDumpLevel2levelorder

  if(evaluate)
    _this->evaluate = evaluate;

  root = GETROOTFROMTREE(_this);

  switch(order)
  {
  case SsSetPreorder: dump = SsSetDumpLevel2preorder(_this, root, evaluate); break;
  case SsSetInorder: dump = SsSetDumpLevel2inorder(_this, root, evaluate); break;
  case SsSetPostorder: dump = SsSetDumpLevel2postorder(_this, root, evaluate); break;
  case SsSetLevelorder: dump = SsSetDumpLevel2levelorder(_this, root, evaluate); break;
  }

  if(dump < 0)
  {
    BlahLog("error");
    goto label_return;
  }

  result = true;

label_return:
  return result ? dump : SsSetError;
}
