
// ssArray.h
// single size array blah

#if 0
struct SsArrayPool
{
  // only need previous if supports pop/remove
  SsArrayPool* next;

  //uint8_t* alloc;
  int unaligned;

  int num;

  // uint8_t chunk[]
};

struct ssArray
{
  SsArrayPool* current;

  SsArrayPool* head;
  SsArrayPool* tail;

  int numPools;

  int numChunks;
  int index;
  int max;

  int resize;
  int capacity;

  int sizeOfRef;
  int sizeOf;
};
#endif

struct ssArray;

ssArray* SsArrayConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize);

int SsArrayDestruct(ssArray** _this);

int SsArrayNum(ssArray* _this);

int SsArrayReset(ssArray* _this);

// appends to end of array
bool SsArrayPush(ssArray* _this, void* chunk);

// get or set element at end of array
bool SsArrayGet(ssArray* _this, void* chunk);
bool SsArraySet(ssArray* _this, void* chunk);

// get or set element at arbitrary valid index
//
// cannot append to array so index must be in the range
// 0 <= index < SsArrayNum(...)
bool SsArrayGetAt(ssArray* _this, int index, void* chunk);
bool SsArraySetAt(ssArray* _this, int index, void* chunk);
