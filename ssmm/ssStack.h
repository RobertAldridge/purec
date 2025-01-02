
// ssStack.h
// single size stack blah

#if 0
struct SsStackPool
{
  SsStackPool* previous;
  SsStackPool* next;

  //uint8_t* alloc;
  int unaligned;

  int num;

  // uint8_t chunk[]
};

struct ssStack
{
  SsStackPool* current;

  SsStackPool* head;
  SsStackPool* tail;

  int numPools;

  int numChunks;
  int index;
  int max;
  
  int counter;

  int resize;
  int capacity;

  int sizeOfRef;
  int sizeOf;
  
  int padding;
};
#endif

struct ssStack;

ssStack* SsStackConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize);

int SsStackDestruct(ssStack** _this);

int SsStackNum(ssStack* _this);

int SsStackReset(ssStack* _this);

bool SsStackPush(ssStack* _this, void* chunk);

/*bool SsStackGet(ssStack* _this, void* chunk) todo*/

bool SsStackPop(ssStack* _this, void* chunk);
