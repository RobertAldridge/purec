
// File Name: bintree.h
// Robert Aldridge

class bintree
{
public:
  typedef int(*compare)(void* keyObject, void* treeObject);

  typedef int(*evaluate)(void* treeObject);

  typedef int(*equivalence)(void* keyObject, void* treeObject);

  static const int ok; // ok == 0
  static const int error; // error == -1

  static const int empty; // empty == 1

  static const int preorder; // preorder == 0; preorder == depth-first
  static const int inorder; // inorder == 1
  static const int postorder; // postorder == 2
  static const int levelorder; // levelorder == 3; levelorder == breadth-first

  static bintree* init(int initialCapacity, int sizeOfEachObject, compare lessThan);
  
  int isEmpty(int numberOfClientObjects[1] );
  
  int insert(void* object, compare lessThan);
  
  int remove(void* keyObject, equivalence equalTo, void* objectReturn);
  
  int getExtrema(int getGreatest, void* objectReturn);
  
  int find(void* keyObject, equivalence equalTo, void* objectReturn);
  
  int reset();

  int term();

  int dump(evaluate clientEvaluate, int traversalOrder);

  int depthTree();

  int depthStack();

  int depthQueue();

private:
  bintree();

  bintree(bintree& );

  virtual ~bintree() = 0;

  bintree& operator=(bintree& );
};
