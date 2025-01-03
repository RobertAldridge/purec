
// ssQueue.h
// single size queue blah

#if 0
struct SsQueueNode
{
  SsQueueNode* previous;
  SsQueueNode* next;

  uint8_t* chunk;

  int num;

  int padding;
};

struct SsQueuePool
{
  SsQueueNode front;
  SsQueueNode back;

  SsQueuePool* previous;
  SsQueuePool* next;

  //uint8_t* alloc;
  int unaligned;

  int num;

  // uint8_t chunk[]
};

struct ssQueue
{
  // if node list is circular then only need back and front
  SsQueueNode* back;
  SsQueueNode* front;

  // if node list is circular then don't need nodeHead or nodeTail
  //SsQueueNode* nodeHead;
  //SsQueueNode* nodeTail;

  SsQueuePool* head;
  SsQueuePool* tail;

  int numPools;

  int numChunks;
  int indexBack;
  int indexFront;
  int max;

  int counter;

  int resize;
  int capacity;

  int sizeOfRef;
  int sizeOf;
};
#endif

struct ssQueue;

ssQueue* SsQueueConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize);

int SsQueueDestruct(ssQueue** _this);

int SsQueueNum(ssQueue* _this);

int SsQueueReset(ssQueue* _this);

bool SsQueuePushBack(ssQueue* _this, void* chunk);
/*bool SsQueueGetBack(ssQueue* _this, void* chunk) todo*/
bool SsQueuePopBack(ssQueue* _this, void* chunk);

bool SsQueuePushFront(ssQueue* _this, void* chunk);
/*bool SsQueueGetFront(ssQueue* _this, void* chunk) todo*/
bool SsQueuePopFront(ssQueue* _this, void* chunk);
