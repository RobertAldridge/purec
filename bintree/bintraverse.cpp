
// File Name: bintraverse.cpp
// Ming C. Lin
// Robert B. Aldridge III
// Charlie H. Burns III

// Preorder is fully optimized
//
// integrated for root sentinel
void IterativePreorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate)
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
void IterativeInorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate)
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
void IterativePostorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate)
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
void IterativeLevelorderTreeTraverse(BinaryTree* tree, BinaryTreeNode* node, binaryTreeEvaluate ClientEvaluate)
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
