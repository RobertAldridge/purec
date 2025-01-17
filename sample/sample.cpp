
// sample.cpp

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

// int thrd_sleep(const struct timespec* duration, struct timespec* remaining)
//#include <threads.h>

#include "ssMm.h"
#include "ssArray.h"
#include "ssStack.h"
#include "ssQueue.h"

#include "ssSet.h"

#include "BlahAlloc.h"

#include "BlahLog.h"

//#include <windows.h>

#define BLAH_KEEP 0

#define G1000ENABLE 0

// 3,324,924,966

// PRIiMAX
// PRIuMAX
// BlahLog("%lli\n", signedValue);
// BlahLog("%llu\n", unsignedValue);

// x_n_plus_1 = a * x_n + c

//void qsort(void* base, size_t nmemb, size_t size, int(*compar)(const void*, const void*) )
static int qsortCompare(const void* lhsRef, const void* rhsRef)
{
  int result = 0;

  uint64_t lhs = *(const uint64_t*)lhsRef;
  uint64_t rhs = *(const uint64_t*)rhsRef;

  if(lhs < rhs)
    result = -1;
  else if(lhs > rhs)
    result = 1;

  return result;
}

static uint64_t random64(uint64_t factor, uint64_t previous, uint64_t term)
{
  uint64_t multB = (uint32_t)factor;
  uint64_t multD = (uint32_t)previous;

  uint64_t a_times_d = (factor >> 32) * multD;
  uint64_t b_times_c = multB * (previous >> 32);
  uint64_t b_times_d = multB * multD;

  return ( (a_times_d + b_times_c) << 32) + b_times_d + term;
}

struct blahRandom
{
  uint64_t factor;
  uint64_t previous;
  uint64_t term;
};

static bool BlahRandomConstructCustom(blahRandom* _this, uint64_t factor, uint64_t seed, uint64_t term)
{
  bool result = false;

  if( !_this)
    goto label_return;

  _this->factor = factor;
  _this->previous = seed;
  _this->term = term;

  result = true;

label_return:
  return result;
}

static bool BlahRandomConstructDefault(blahRandom* _this)
{
  return BlahRandomConstructCustom(_this, 2862933555777941757ULL, (uint64_t)time(0), 3037000493ULL);
}

static bool BlahRandomDestruct(blahRandom* _this)
{
  bool result = false;

  if( !_this)
    goto label_return;

  // nop

  result = true;

label_return:
  return result;
}

static bool BlahRandomIterate(blahRandom* _this)
{
  bool result = false;

  if( !_this)
    goto label_return;

  _this->previous = random64(_this->factor, _this->previous, _this->term);

  result = true;

label_return:
  return result;
}

static bool BlahRandomGet(blahRandom* _this, uint64_t* current)
{
  bool result = false;

  if( !_this || !current)
    goto label_return;

  *current = _this->previous;

  result = true;

label_return:
  return result;
}

// 5.13 gigabytes == ~5,254 megabytes
#define BLAH_SIZE 5254

#define BLAH_QUEUE_SIZE 5

static bool blahTestStack()
{
  bool result = false;

  ssStack* blahStack = 0;

  blahStack = SsStackConstruct(sizeof(int64_t), 10, 1000, 10);

  if( !blahStack)
    goto label_return;

  BlahLog("\n");

  for(int64_t index = 1; index <= 5; index++)
  {
    if( !SsStackPush(blahStack, &index) )
      goto label_return;
  }

  for(int64_t index = 0; index < 2; index++)
  {
    int64_t getStackData = 0;

    if( !SsStackPop(blahStack, &getStackData) )
      goto label_return;
  }

  for(int64_t index = 6; index <= 11; index++)
  {
    if( !SsStackPush(blahStack, &index) )
      goto label_return;
  }

  for(int64_t index = 12; index <= 21; index++)
  {
    if( !SsStackPush(blahStack, &index) )
      goto label_return;
  }

  for(int64_t index = 0; index < 3; index++)
  {
    int64_t getStackData = 0;

    if( !SsStackPop(blahStack, &getStackData) )
      goto label_return;
  }

  for(int64_t index = 22; index <= 25; index++)
  {
    if( !SsStackPush(blahStack, &index) )
      goto label_return;
  }

  for(int64_t index = 5; index >= 1; index--)
  {
    if( !SsStackPush(blahStack, &index) )
      goto label_return;
  }

  for(int64_t index = 26; index <= 30; index++)
  {
    if( !SsStackPush(blahStack, &index) )
      goto label_return;
  }

  for(int64_t index = 31; index <= 41; index++)
  {
    if( !SsStackPush(blahStack, &index) )
      goto label_return;
  }

  for(int64_t index = 0; index >= -20; index--)
  {
    if( !SsStackPush(blahStack, &index) )
      goto label_return;
  }

  SsStackDestruct( &blahStack);

  result = true;

label_return:
  return result;
}

static bool blahTestQueue()
{
  bool result = false;

  ssQueue* blahQueue = 0;

  blahQueue = SsQueueConstruct(sizeof(int64_t), 10, 1000, 10);

  if( !blahQueue)
    goto label_return;

  BlahLog("\n");

  for(int64_t index = 1; index <= 5; index++)
  {
    if( !SsQueuePushBack(blahQueue, &index) )
      goto label_return;
  }

  for(int64_t index = 0; index < 2; index++)
  {
    int64_t getQueueData = 0;

    if( !SsQueuePopFront(blahQueue, &getQueueData) )
      goto label_return;
  }

  for(int64_t index = 6; index <= 11; index++)
  {
    if( !SsQueuePushBack(blahQueue, &index) )
      goto label_return;
  }

  for(int64_t index = 12; index <= 21; index++)
  {
    if( !SsQueuePushBack(blahQueue, &index) )
      goto label_return;
  }

  for(int64_t index = 0; index < 3; index++)
  {
    int64_t getQueueData = 0;

    if( !SsQueuePopFront(blahQueue, &getQueueData) )
      goto label_return;
  }

  for(int64_t index = 22; index <= 25; index++)
  {
    if( !SsQueuePushBack(blahQueue, &index) )
      goto label_return;
  }

  for(int64_t index = 5; index >= 1; index--)
  {
    if( !SsQueuePushFront(blahQueue, &index) )
      goto label_return;
  }

  for(int64_t index = 26; index <= 30; index++)
  {
    if( !SsQueuePushBack(blahQueue, &index) )
      goto label_return;
  }

  for(int64_t index = 31; index <= 41; index++)
  {
    if( !SsQueuePushBack(blahQueue, &index) )
      goto label_return;
  }

  for(int64_t index = 0; index >= -20; index--)
  {
    if( !SsQueuePushFront(blahQueue, &index) )
      goto label_return;
  }

  SsQueueDestruct( &blahQueue);

  result = true;

label_return:
  return result;
}

static const uint32_t myFatalError = 0xFFFFFFFFUL;

//typedef uint32_t(*SsSetCompare)(void*, void*);
static uint32_t lessThan(void* lhs, void* rhs)
{
  uint32_t result = 0;

  // return non-zero if lhs < rhs
  if( *(uint32_t*)lhs < *(uint32_t*)rhs)
    result = 1;

  // return zero if lhs >= lhs

  return result;
}

//typedef uint32_t(*SsSetEvaluate)(void*);
static uint32_t check(void* lhs)
{
  uint32_t result = 0;

#if BLAH_KEEP
  BlahLog("%i ", *(uint32_t*)lhs);
#endif

  // return non-zero to terminate traversal
  if( *(uint32_t*)lhs == myFatalError)
  {
    BlahLog("\ndump - object found %u\n", myFatalError);

    result = 1;
  }

  // return zero to continue traversal

  return result;
}

static uint32_t calculateLogBase2(int64_t number)
{
  uint32_t result = 0;

  while(number)
  {
    result++;

    number /= 2;
  }

  return result;
}

static void swapInt(uint32_t& lhs, uint32_t& rhs)
{
  uint32_t temporary = lhs;

  lhs = rhs;
  rhs = temporary;
}

#if G1000ENABLE
static uint32_t g1000fullCount = 0;
static uint32_t g1000modCount = 0;
static uint32_t g1000sizeOf = 0;

#define G1000NUMERATOR 1000
#define G1000DIVISOR 200

static bool DebugAllocate(uint32_t* data[G1000NUMERATOR], uint32_t count)
{
  bool result = false;

  if(count % G1000DIVISOR)
    goto label_return;

  if(count < G1000DIVISOR)
    goto label_return;

  g1000fullCount = count;

  count /= G1000DIVISOR;

  g1000modCount = count;

  g1000sizeOf = sizeof(uint32_t) * count;

  for(uint32_t index = 0; index < G1000DIVISOR; index++)
  {
    data[index] = (uint32_t*)BlahAlloc(g1000sizeOf, true);

    if( !data[index] )
      goto label_return;
  }

  result = true;

label_return:
  return result;
}

static uint32_t DebugGet(uint32_t* data[G1000NUMERATOR], uint32_t index)
{
  return data[index / g1000modCount][index % g1000modCount];
}

static void DebugSet(uint32_t* data[G1000NUMERATOR], uint32_t index, uint32_t value)
{
  data[index / g1000modCount][index % g1000modCount] = value;
}

static void DebugFree(uint32_t* data[G1000NUMERATOR] )
{
  for(uint32_t index = G1000DIVISOR; index > 0; index--)
  {
    BlahFree(data[index - 1], g1000sizeOf, true);
    data[index - 1] = 0;
  }
}
#else
static uint32_t g1000sizeOf = 0;

#define G1000NUMERATOR 1

static bool DebugAllocate(uint32_t* data[G1000NUMERATOR], uint32_t count)
{
  bool result = false;

  g1000sizeOf = sizeof(uint32_t) * count;

  data[0] = (uint32_t*)BlahAlloc(g1000sizeOf, true);

  if( !data[0] )
    goto label_return;

  result = true;

label_return:
  return result;
}

static uint32_t DebugGet(uint32_t* data[G1000NUMERATOR], uint32_t index)
{
  return data[0][index];
}

static void DebugSet(uint32_t* data[G1000NUMERATOR], uint32_t index, uint32_t value)
{
  data[0][index] = value;
}

static void DebugFree(uint32_t* data[G1000NUMERATOR] )
{
  BlahFree(data[0], g1000sizeOf, true);
  data[0] = 0;
}
#endif

// ssSet* SsSetConstruct(uint32_t sizeOf, uint32_t minimum, int64_t maximum, uint32_t resize, SsSetCompare lessThan)
// int64_t SsSetDestruct(ssSet* _this)
// int64_t SsSetNum(ssSet* _this)
// int64_t SsSetReset(ssSet* _this)
// int64_t SsSetInsert(ssSet* _this, void* key, SsSetCompare lessThan, void* client)
// int64_t SsSetErase(ssSet* _this, void* key, SsSetCompare lessThan, void* client)
// int64_t SsSetGetExtrema(ssSet* _this, bool maximum, void* client)
// int64_t SsSetFind(ssSet* _this, void* key, SsSetCompare lessThan, void* client)
// int64_t SsSetDump(ssSet* _this, SsSetEvaluate evaluate, int order)
// int64_t SsSetDepthTree(ssSet* _this)
// int64_t SsSetMaxStack(ssSet* _this)
// int64_t SsSetMaxQueue(ssSet* _this)

static bool SsSetTest(blahRandom* /*random*/)
{
  bool result = false;

  //ssMm* ssMmBlah = SsMmConstruct(sizeof(void*), 100, false);
  //SsMmSetResize(ssMmBlah, -1);

#if 0
  uint32_t cacheCapacity = 2;

  List* cacheList = listInitialize(cacheCapacity);

  unordered_map<uint32_t, Cache> cacheHashTable;

  cachePut(cacheHashTable, cacheList, 1, 1);
  cachePut(cacheHashTable, cacheList, 2, 2);

  cacheGet(cacheHashTable, cacheList, 1);

  cachePut(cacheHashTable, cacheList, 3, 3);
  //cachePut(cacheHashTable, cacheList, 3, 4);

  cacheGet(cacheHashTable, cacheList, 2);

  cachePut(cacheHashTable, cacheList, 4, 4);

  cacheGet(cacheHashTable, cacheList, 1);

  cacheGet(cacheHashTable, cacheList, 3);
  cacheGet(cacheHashTable, cacheList, 4);
#endif

// limit of memory allocation near 30,000,000
//uint32_t numData = 30000000;

//BlahLog("%i\n\n", blah_get_number() );
//2097152

  double queueMaximumPercentage = 0;

//uint32_t numData = 10000000;

  int64_t ssSetDebug[88] = {0};

for(uint32_t numData = 10; numData <= 100; numData += 1)
{
  double percentageQueue = 0;

//ssSet* SsSetConstruct(uint32_t sizeOf, uint32_t minimum, int64_t maximum, uint32_t resize, SsSetCompare lessThan)
  ssSet* mySet = SsSetConstruct(sizeof(uint32_t), numData <= 5000000 ? numData : 5000000, 4100000000, 10000000, lessThan);
  if( !mySet)
  {
    BlahLog("error");
    goto label_return;
  }

  //uint32_t data[numData] = { {0}, {1}, {2}, {3}, {4} };
  uint32_t* datablah[G1000NUMERATOR] = {0};
  if( !DebugAllocate(datablah, numData) )
  {
    BlahLog("error");
    goto label_return;
  }

  uint32_t keyObject = myFatalError;
  uint32_t resultObject = 0;
  int64_t findResult = 0;
  int64_t eraseResult = 0;

  srand(1);

//int64_t SsSetInsert(ssSet* _this, void* key, SsSetCompare lessThan, void* client)

  //for(uint32_t loop = 0; loop < numData; loop++)
  //  SsSetInsert(mySet, &data[loop], 0, 0);

// check for inserting into tree
//   keys already sorted
//   keys alread reverse sorted
//   all the same key
  for(uint32_t index = 0; index < numData; index++)
  {
    DebugSet(datablah, index, index);//numData - index
  }

  for(uint32_t index = 0; index < (numData - 1); index++)
  {
    // if index == 0, modulus == numData - 1, indexToSwap in range [0, numData - 2], swapInt rhs index range is [1, numData - 1]
    // if index == 1, modulus == numData - 2, indexToSwap in range [0, numData - 3], swapInt rhs index range is [2, numData - 1]
    // if index == numData - 2, modulus == 1, indexToSwap in range [0, 0], swapInt rhs index range is [numData - 1, numData - 1]

    uint32_t modulus = (numData - index) - 1;

    //uint64_t randomValue = 0;
    //BlahRandomIterate(random);
    //BlahRandomGet(random, &randomValue);

    //uint32_t indexToSwap = (uint32_t)(randomValue % (uint64_t)modulus);
    uint32_t indexToSwap = (uint32_t)rand() % modulus;

    uint32_t lhs = DebugGet(datablah, index);
    uint32_t rhs = DebugGet(datablah, (index + 1) + indexToSwap);

    //swapInt(data[index], data[ (index + 1) + indexToSwap] );
    DebugSet(datablah, index, rhs);
    DebugSet(datablah, (index + 1) + indexToSwap, lhs);
  }

#if BLAH_KEEP
  BlahLog("\ndump original list shuffled before insertion\n");
#endif
  for(uint32_t index = 0; index < numData; index++)
  {
#if BLAH_KEEP
    BlahLog("%i ", data[index] );
#endif
  }
#if BLAH_KEEP
  BlahLog("\n\n");
#endif

//int64_t SsSetNum(ssSet* _this)
  int64_t numSet = SsSetNum(mySet);
  if(numSet)
  {
    BlahLog("blah b\n");
  }

  for(uint32_t index = 0; index < numData; index++)
  {
    uint32_t data1 = DebugGet(datablah, index);

//int64_t SsSetInsert(ssSet* _this, void* key, SsSetCompare lessThan, void* client)
    if(SsSetInsert(mySet, &data1, 0, 0) < 0)
    {
      BlahLog("error");
      goto label_return;
    }

//int64_t SsSetNum(ssSet* _this)
    numSet = SsSetNum(mySet);
    if(numSet < 0 || numSet != ( (int64_t)index + 1) )
    {
      BlahLog("error");
      goto label_return;
    }

#if BLAH_KEEP
//int64_t SsSetDepthTree(ssSet* _this)
    int64_t height = SsSetDepthTree(mySet);

    if(height <= 0 || height > 2 * (int64_t)calculateLogBase2(numSet + 1) )
    {
      BlahLog("error");
      goto label_return;
    }
    else
    {
      BlahLog("%lli %lli %u\n", numSet, height, 2 * calculateLogBase2(numSet + 1) );
    }
#endif

//int64_t SsSetFind(ssSet* _this, void* key, SsSetCompare lessThan, void* client)

#if BLAH_KEEP
    resultObject = 0;
    findResult = SsSetFind(mySet, &keyObject, lessThan, &resultObject);
    if(findResult < 0)
    {
      BlahLog("error");
      goto label_return;
    }
    else if( !findResult && resultObject == keyObject)
    {
      //BlahLog("find - object found\n");
    }
    else if(findResult == SsSetNotFound && resultObject != keyObject)
    {
      //BlahLog("find - object not found\n");
    }
    else
    {
      BlahLog("error");
      goto label_return;
    }
#endif
  }

//int64_t SsSetNum(ssSet* _this)
  numSet = SsSetNum(mySet);
  if(numSet < 0 || numSet != (int64_t)numData)
  {
    BlahLog("error");
    goto label_return;
  }

#if BLAH_KEEP
  BlahLog("dump preorder\n");
#endif
//int64_t SsSetDump(ssSet* _this, SsSetEvaluate evaluate, int order)
  if(SsSetDump(mySet, check, SsSetPreorder) )
  {
    BlahLog("error");
    goto label_return;
  }
#if BLAH_KEEP
  BlahLog("\n\n");
#endif

#if BLAH_KEEP
  BlahLog("dump inorder\n");
#endif
//int64_t SsSetDump(ssSet* _this, SsSetEvaluate evaluate, int order)
  if(SsSetDump(mySet, check, SsSetInorder) )
  {
    BlahLog("error");
    goto label_return;
  }
#if BLAH_KEEP
  BlahLog("\n\n");
#endif

#if BLAH_KEEP
  BlahLog("dump postorder\n");
#endif
//int64_t SsSetDump(ssSet* _this, SsSetEvaluate evaluate, int order)
  if(SsSetDump(mySet, check, SsSetPostorder) )
  {
    BlahLog("error");
    goto label_return;
  }
#if BLAH_KEEP
  BlahLog("\n\n");
#endif

#if BLAH_KEEP
  BlahLog("dump levelorder\n");
#endif
//int64_t SsSetDump(ssSet* _this, SsSetEvaluate evaluate, int order)
  if(SsSetDump(mySet, check, SsSetLevelorder) )
  {
    BlahLog("error");
    goto label_return;
  }
#if BLAH_KEEP
  BlahLog("\n\n");
#endif

  if(1)
  {
//int64_t SsSetDepthTree(ssSet* _this)
    int64_t height = SsSetDepthTree(mySet);

    if(height <= 0 || height > 2 * (int64_t)calculateLogBase2(numSet + 1) )
    {
      BlahLog("error");
      goto label_return;
    }
    else
    {
#if BLAH_KEEP
//int64_t SsSetMaxStack(ssSet* _this)
      int64_t maxStack = SsSetMaxStack(mySet);
#endif

//int64_t SsSetMaxQueue(ssSet* _this)
      int64_t maxQueue = SsSetMaxQueue(mySet);

#if BLAH_KEEP
      uint32_t maxHeight = 2 * calculateLogBase2(numSet + 1);
#endif

      percentageQueue = (double)maxQueue / (double)numSet;

#if BLAH_KEEP
      BlahLog("size %lli current height %lli stack %lli queue %lli %f max height %u\n", numSet, height, maxStack, maxQueue, percentageQueue, maxHeight);
#endif

      if(percentageQueue > queueMaximumPercentage)
        queueMaximumPercentage = percentageQueue;

      //BlahLog("%f\n", percentageQueue);
    }
  }

//int64_t SsSetFind(ssSet* _this, void* key, SsSetCompare lessThan, void* client)

  resultObject = 0;
  findResult = SsSetFind(mySet, &keyObject, lessThan, &resultObject);
  if(findResult < 0)
  {
    BlahLog("error");
    goto label_return;
  }
  else if( !findResult && resultObject == keyObject)
  {
#if BLAH_KEEP
    BlahLog("\nfind - object found\n\n");
#endif
  }
  else if(findResult == SsSetNotFound && resultObject != keyObject)
  {
#if BLAH_KEEP
    BlahLog("\nfind - object not found\n\n");
#endif
  }
  else
  {
    BlahLog("error");
    goto label_return;
  }

  for(uint32_t index = 0; index < (numData - 1); index++)
  {
    // if index == 0, modulus == numData - 1, indexToSwap in range [0, numData - 2], swapInt rhs index range is [1, numData - 1]
    // if index == 1, modulus == numData - 2, indexToSwap in range [0, numData - 3], swapInt rhs index range is [2, numData - 1]
    // if index == numData - 2, modulus == 1, indexToSwap in range [0, 0], swapInt rhs index range is [numData - 1, numData - 1]

    uint32_t modulus = (numData - index) - 1;

    //uint64_t randomValue = 0;
    //BlahRandomIterate(random);
    //BlahRandomGet(random, &randomValue);

    //uint32_t indexToSwap = (uint32_t)(randomValue % (uint64_t)modulus);
    uint32_t indexToSwap = (uint32_t)rand() % modulus;

    uint32_t lhs = DebugGet(datablah, index);
    uint32_t rhs = DebugGet(datablah, (index + 1) + indexToSwap);

    //swapInt(data[index], data[ (index + 1) + indexToSwap] );
    DebugSet(datablah, index, rhs);
    DebugSet(datablah, (index + 1) + indexToSwap, lhs);
  }

#if BLAH_KEEP
  BlahLog("dump original list reshuffled before deletion\n");
#endif
  for(uint32_t index = 0; index < numData; index++)
  {
#if BLAH_KEEP
    BlahLog("%i ", data[index] );
#endif
  }
#if BLAH_KEEP
  BlahLog("\n\n");
#endif

  for(uint32_t index = 0; index < numData; index++)
  {
//int64_t SsSetNum(ssSet* _this)
    numSet = SsSetNum(mySet);
    if(numSet < 0 || numSet != ( (int64_t)numData - (int64_t)index) )
    {
      BlahLog("error");
      goto label_return;
    }

#if BLAH_KEEP
//int64_t SsSetDepthTree(ssSet* _this)
    int64_t height = SsSetDepthTree(mySet);

    if(height <= 0 || height > 2 * (int64_t)calculateLogBase2(numSet + 1) )
    {
      BlahLog("error");
      goto label_return;
    }
    else
    {
      //BlahLog("%lli %lli %u\n", numSet, height, 2 * calculateLogBase2(numSet + 1) );
    }
#endif

    uint32_t data1 = DebugGet(datablah, index);

//int64_t SsSetErase(ssSet* _this, void* key, SsSetCompare lessThan, void* client)

    resultObject = 0;
    eraseResult = SsSetErase(mySet, &data1, lessThan, &resultObject);

    if(eraseResult || resultObject != data1)
    {
      BlahLog("error");
      goto label_return;
    }

//int64_t SsSetFind(ssSet* _this, void* key, SsSetCompare lessThan, void* client)

#if BLAH_KEEP
    resultObject = 0;
    findResult = SsSetFind(mySet, &keyObject, lessThan, &resultObject);

    if(findResult < 0)
    {
      BlahLog("error");
      goto label_return;
    }
    else if( !findResult && resultObject == keyObject)
    {
      //BlahLog("find - object found\n");
    }
    else if(findResult == SsSetNotFound && resultObject != keyObject)
    {
      //BlahLog("find - object not found\n");
    }
    else
    {
      BlahLog("error");
      goto label_return;
    }
#endif
  }

//int64_t SsSetNum(ssSet* _this)
  numSet = SsSetNum(mySet);
  if(numSet)
  {
    BlahLog("error");
    goto label_return;
  }

  if(1)
  {
//int64_t SsSetDepthTree(ssSet* _this)
    int64_t height = SsSetDepthTree(mySet);
    if(height)
    {
      BlahLog("error");
      goto label_return;
    }
    else
    {
      //BlahLog("%lli %lli %u\n", numSet, height, 2 * calculateLogBase2(numSet + 1) );
    }
  }

  //BlahLog("log2 %i %u\n", 1048576, calculateLogBase2(1048576) );
  //BlahLog("log2 %i %u\n", 1048575, calculateLogBase2(1048575) );

//int64_t SsSetDestruct(ssSet* _this)
  if(SsSetDestruct(mySet) < 0)
  {
    BlahLog("error");
    goto label_return;
  }

  DebugFree(datablah);

  if(numData >= 86)
  {
    for(uint32_t index = 0; index < countof(ssSetDebug); index++)
    {
      ssSetDebug[index] += SsSetGetDebug(mySet, index);
//BlahLog("debug rotate %u %lli\n", index, ssSetDebug[index] );
    }

    for(uint32_t index = 0; index < countof(ssSetDebug); index++)
    {
      if(index == 1 || index == 21 || index == 68 || index == 69 || index == 78 || index == 79 || index == 80)
      {
        if(ssSetDebug[index] )
          BlahLog("debug rotate %u %lli\n", index, ssSetDebug[index] );
      }
      else if( !ssSetDebug[index] )
      {
        BlahLog("debug rotate %u %lli\n", index, ssSetDebug[index] );
      }
    }
  }

//BlahLog("queue %u %f\n", numData, percentageQueue);

#if BLAH_KEEP
  BlahLog("end\n");
#endif
}

  BlahLog("\nqueue max %f\n", queueMaximumPercentage);

  result = true;

label_return:
  return result;
}

extern "C" static int mainLevel2()
{
  int result = -1;

  blahRandom random = {0};

  struct timespec sleep_time = {0};

  if( !BlahRandomConstructDefault( &random) )
    goto label_return;

  if( !BlahRandomIterate( &random) )
    goto label_return;

  if( !blahTestStack() )
    goto label_return;

  if( !blahTestQueue() )
    goto label_return;

  sleep_time.tv_sec = 1;

//thrd_sleep( &sleep_time, 0);

  if( !SsSetTest( &random) )
    goto label_return;

  BlahRandomDestruct( &random);

  result = 0;

label_return:
  return result;
}

#if 0
extern "C" int __stdcall WinMain
(
  HINSTANCE /*hInstance*/, // handle to current instance
  HINSTANCE /*hPrevInstance*/, // handle to previous instance
  char* /*lpCmdLine*/, // pointer to command line
  int /*nCmdShow*/ // show state of window
)
{
  int result = -1;

  BlahLog("blah %s %i\n", "blah", 1);

  result = mainLevel2();

  return result;
}
#endif

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
