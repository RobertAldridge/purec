
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
  uint8_t* chunk;

  SsArrayPool* current;

  SsArrayPool* head;
  SsArrayPool* tail;

  int numPools;

  int numChunks;
  int max;

  int counter;

  int resize;
  int capacity;

  int sizeOfRef;
  int sizeOf;
};
#endif

struct ssArray;

ssArray* SsArrayConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize);

// returns the number of elements previously in the array or -1 on error
int SsArrayDestruct(ssArray** _this/*reference*/);

int SsArrayNum(ssArray* _this);

// returns the number of nodes previously held by client or -1 on error
int SsArrayReset(ssArray* _this);

// appends to end of array
bool SsArrayPush(ssArray* _this, void* client);

// get or set element at end of array
//
// there will be at least one element in the current pool, so we never have to
// walk backwards to the previous pool to get/set the element at the end of the
// array

bool SsArrayGet(ssArray* _this, void* client);
bool SsArraySet(ssArray* _this, void* client);

// get or set element at arbitrary valid index
//
// cannot append to array so index must be in the range
// 0 <= index < SsArrayNum(...)

bool SsArrayGetAt(ssArray* _this, int index, void* client);
bool SsArraySetAt(ssArray* _this, int index, void* client);
