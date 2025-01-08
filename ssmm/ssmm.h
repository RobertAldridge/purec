
// ssmm.h
// single size memory manager

#if 0
struct SsmmNode
{
  SsmmNode* next;
};

struct SsmmPool
{
  SsmmPool* next;
  //uint8_t* alloc;
  int unaligned;
  int num;
  //uint8_t chunk[]
};

struct ssmm
{
  SsmmNode* chunk;

  SsmmPool* current;

  SsmmPool* head;
  SsmmPool* tail;

  uint8_t* alloc;
  //int unaligned;

  int numPools;

  int numChunks;
  int most;
  int max;

  int resize;
  int capacity;

  int sizeOf;
};
#endif

struct ssmm;

ssmm* SsmmConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize);

bool SsmmDestruct(ssmm** _this);

bool SsmmNum(ssmm* _this, uint32_t* num);

bool SsmmReset(ssmm* _this);

void* SsmmAlloc(ssmm* _this);

bool SsmmFree(ssmm* _this, void** chunk);
