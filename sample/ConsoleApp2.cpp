
// ConsoleApp2.cpp

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#define CPP_STUFF 0

#if CPP_STUFF
#include <new>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::bad_alloc;
using std::set;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;
#else
#include <new>
using std::bad_alloc;
#endif

#define YDEBUG 0

#define countof(x) (sizeof(x) / sizeof(x[0] ) )

#if CPP_STUFF
typedef struct NodeType Node;

static void nodeRemove(Node* /*current*/)
{
}

#include "stack.cpp"
#include "queue.cpp"
#include "list.cpp"
#endif

#if 0
struct NodeType
{
    int key;

    struct NodeType* previous;
    struct NodeType* next;
};

typedef struct NodeType Node;

struct ListType
{
    int index;
    int capacity;

    Node sentinelUsed;
    Node sentinelFree;

    Node* memory;
};

typedef struct ListType List;

static void nodeRemove(Node* current)
{
    if (current)
    {
        Node* previous = current->previous;
        Node* next = current->next;

        if (previous && next)
        {
            previous->next = next;
            next->previous = previous;

            current->previous = 0;
            current->next = 0;
        }
    }
}

static void nodeInsertNext(Node* previous, Node* insert)
{
    // current is already detached
    if (previous && insert)
    {
        Node* next = previous->next;

        if (next)
        {
            previous->next = insert;
            insert->previous = previous;

            insert->next = next;
            next->previous = insert;
        }
    }
}

static void nodeInsertPrevious(Node* insert, Node* next)
{
    // current is already detached
    if (insert && next)
    {
        Node* previous = next->previous;

        if (previous)
        {
            previous->next = insert;
            insert->previous = previous;

            insert->next = next;
            next->previous = insert;
        }
    }
}

static Node* nodeAllocate(Node* sentinel, int count)
{
    Node* nodeList = 0;

    if (!sentinel || count < 0)
        goto returnLabel;

    sentinel->key = INT_MAX;

    if (count > 0)
    {
        nodeList = (Node*)blah_aligned_alloc(sizeof(Node) * count, 0, false);
        memset(nodeList, 0, sizeof(Node) * count);

        for (int index = 0; index < count; index++)
        {
            nodeList[index].key = 0; // or -1, INT_MAX

            if (index > 0)
                nodeList[index].previous = &nodeList[index - 1];

            if (index < (count - 1))
                nodeList[index].next = &nodeList[index + 1];
        }

        sentinel->next = &nodeList[0];
        nodeList[0].previous = sentinel;

        nodeList[count - 1].next = sentinel;
        sentinel->previous = &nodeList[count - 1];
    }
    else // if(count == 0)
    {
        sentinel->next = sentinel;
        sentinel->previous = sentinel;
    }

returnLabel:

    return nodeList;
}

static List* listInitialize(int count)
{
    List* daList = 0;

    if (count >= 0)
    {
        daList = (List*)blah_aligned_alloc(sizeof(List), 0, false);
        memset(daList, 0, sizeof(List));

        daList->index = 0;
        daList->capacity = count;

        daList->memory = nodeAllocate(&daList->sentinelFree, count);

        nodeAllocate(&daList->sentinelUsed, 0);
    }
    // ignore if count < 0

    return daList;
}

static void ListTerminate(List* daList)
{
    if (daList)
    {
        if (daList->capacity > 0)
        {
            memset(daList->memory, 0, sizeof(Node) * daList->capacity);
            blah_free_aligned_sized(daList->memory, 0, 0);
        }

        memset(daList, 0, sizeof(List));
        blah_free_aligned_sized(daList, 0, 0);
    }
}

struct CacheType
{
    int value;

    Node* current;
};

typedef struct CacheType Cache;

static Node* listAddData(List* daList, int data, unordered_map<int, Cache>& cacheHashTable)
{
    Node* current = 0;

    if (daList)
    {
        // no checking for duplicate key

        if (daList->index < daList->capacity)
        {
            // remove from front of free list
            current = daList->sentinelFree.previous;
            nodeRemove(current);

            // set data
            current->key = data;

            // put in front of used list
            Node* next = &daList->sentinelUsed;
            nodeInsertPrevious(current, next);

            daList->index++;
        }
        else if(daList->index == daList->capacity)
        {
            // remove from back of used list
            current = daList->sentinelUsed.next;
            nodeRemove(current);

            // replace data
            printf("eject %i\n", current->key);
            cacheHashTable.erase(current->key);
            current->key = data;

            // put in front of used list
            Node* next = &daList->sentinelUsed;
            nodeInsertPrevious(current, next);

            // daList->index unchanged
        }
        // ignore if daList->index > daList->capacity
    }

    return current;
}

static void listRemoveNode(List* daList, Node* daNode)
{
    if (daList && daNode && daList->index > 0 && daList->index <= daList->capacity)
    {
        // can add optional check here if daNode is in used list
        // (no check for now)

        // assumed to be a removal from used list
        Node* current = daNode;
        nodeRemove(current);

        // clear data
        current->key = 0; // or -1, INT_MAX

        // put in back of free list
        Node* previous = &daList->sentinelFree;
        nodeInsertNext(previous, current);

        daList->index--;
    }
}

static void listMoveToFrontUsedNode(List* daList, Node* daNode)
{
    if (daList && daNode && daList->index > 0 && daList->index <= daList->capacity)
    {
        // can add optional check here if daNode is in used list
        // (no check for now)

        // assumed to be a removal from used list
        Node* current = daNode;
        nodeRemove(current);

        // current->value unchanged; data unchanged
        printf("promote %i\n", current->key);

        // put in front of used list
        Node* next = &daList->sentinelUsed;
        nodeInsertPrevious(current, next);

        // daList->index unchanged
    }
}

static void cachePut(unordered_map<int, Cache>& cacheHashTable, List* cacheList, int key, int value)
{
    printf("put start %i %i\n", key, value);

    if (cacheHashTable.count(key))
    {
        Cache& cacheHit = cacheHashTable.at(key);

        // update value of key_value pair
        cacheHit.value = value;

        listMoveToFrontUsedNode(cacheList, cacheHit.current);
    }
    else
    {
        Node* current = listAddData(cacheList, key, cacheHashTable);

        Cache cacheMiss = { value, current };

        cacheHashTable[key] = cacheMiss;
    }

    printf("put finish %i %i\n", key, value);

    for (Node* cacheEntry = cacheList->sentinelUsed.next; cacheEntry != &cacheList->sentinelUsed; cacheEntry = cacheEntry->next)
    {
        printf("%i %i; ", cacheEntry->key, cacheHashTable[cacheEntry->key].value);
    }
    printf("\n\n");

    return;
}

static int cacheGet(unordered_map<int, Cache>& cacheHashTable, List* cacheList, int key)
{
    int value = -1;

    printf("get start %i\n", key);

    if (cacheHashTable.count(key))
    {
        Cache& cacheHit = cacheHashTable.at(key);

        value = cacheHit.value;

        listMoveToFrontUsedNode(cacheList, cacheHit.current);
    }

    printf("get finish %i %i\n", key, value);

    for (Node* cacheEntry = cacheList->sentinelUsed.next; cacheEntry != &cacheList->sentinelUsed; cacheEntry = cacheEntry->next)
    {
        printf("%i %i; ", cacheEntry->key, cacheHashTable[cacheEntry->key].value);
    }
    printf("\n\n");

    return value;
}
#endif

#define BLAH_KEEP 0

#define BLAH_BINTREE 1

// 3,324,924,966

// PRIiMAX
// PRIuMAX
// printf("%lli\n", signedValue);
// printf("%llu\n", unsignedValue);

// x_n_plus_1 = a * x_n + c

static int qsortCompare(const void* lhsRef, const void* rhsRef)
{
  uint64_t lhs = *(const uint64_t*)lhsRef;
  uint64_t rhs = *(const uint64_t*)rhsRef;

  if(lhs < rhs)
    return -1;

  if(lhs > rhs)
    return 1;

  return 0;
}

#if 1
uint64_t random64(uint64_t factor, uint64_t previous, uint64_t term)
{
  uint64_t multB = (uint32_t)factor;
  uint64_t multD = (uint32_t)previous;

  uint64_t a_times_d = (factor >> 32) * multD << 32;
  uint64_t b_times_c = multB * (previous >> 32) << 32;
  uint64_t b_times_d = multB * multD;

  return a_times_d + b_times_c + b_times_d + term;
}
#else
uint64_t multiplyTwoPlusOneUint64(uint64_t lhs, uint64_t rhs, uint64_t blah)
{
  uint64_t multA = lhs >> 32;
  uint64_t multB = lhs & 0xFFFFFFFFULL;

  uint64_t multC = rhs >> 32;
  uint64_t multD = rhs & 0xFFFFFFFFULL;

  uint64_t a_times_c_lower = multA * multC & 0xFFFFFFFFULL;
  uint64_t a_times_c_upper = multA * multC >> 32;

  uint64_t a_times_d_lower = multA * multD & 0xFFFFFFFFULL;
  uint64_t a_times_d_upper = multA * multD >> 32;

  uint64_t b_times_c_lower = multB * multC & 0xFFFFFFFFULL;
  uint64_t b_times_c_upper = multB * multC >> 32;

  uint64_t b_times_d_lower = multB * multD & 0xFFFFFFFFULL;
  uint64_t b_times_d_upper = multB * multD >> 32;

  uint64_t result0 = b_times_d_lower + (blah & 0xFFFFFFFFULL);

  uint64_t result32 = a_times_d_lower + b_times_c_lower + b_times_d_upper + (blah >> 32);

  uint64_t result64 = a_times_c_lower + a_times_d_upper + b_times_c_upper;

  uint64_t result96 = a_times_c_upper;

  uint64_t result128 = 0;

  result32 += result0 >> 32;
  result0 &= 0xFFFFFFFFULL;

  result64 += result32 >> 32;
  result32 &= 0xFFFFFFFFULL;

  result96 += result64 >> 32;
  result64 &= 0xFFFFFFFFULL;

  result128 += result96 >> 32;
  result96 &= 0xFFFFFFFFULL;

  uint64_t result_lower = (result32 << 32) + result0;
  uint64_t result_upper = (result96 << 32) + result64;
  uint64_t carry = result128;

  //printf("%llu %llu %llu ", lhs, rhs, blah);
  //printf("%llu %llu %llu\n\n", carry, result_upper, result_lower);

  return result_lower;
}
#endif

struct blahRandom
{
  uint64_t factor;
  uint64_t previous;
  uint64_t term;
};

bool BlahRandomConstructCustom(blahRandom* _this, uint64_t factor, uint64_t seed, uint64_t term)
{
  bool result = false;

  if( !_this)
    goto error;

  _this->factor = factor;
  _this->previous = seed;
  _this->term = term;

  result = true;

error:
  return result;
}

bool BlahRandomConstructDefault(blahRandom* _this)
{
  return BlahRandomConstructCustom(_this, 2862933555777941757ULL, (uint64_t)time(0), 3037000493ULL);
}

bool BlahRandomDestruct(blahRandom* _this)
{
  bool result = false;

  if( !_this)
    goto error;

  // nop

  result = true;

error:
  return result;
}

bool BlahRandomIterate(blahRandom* _this)
{
  bool result = false;

  if( !_this)
    goto error;

  _this->previous = random64(_this->factor, _this->previous, _this->term);

  result = true;

error:
  return result;
}

bool BlahRandomGet(blahRandom* _this, uint64_t* current)
{
  bool result = false;

  if( !_this || !current)
    goto error;

  *current = _this->previous;

  result = true;

error:
  return result;
}

#include <threads.h>
// int thrd_sleep(const struct timespec* duration, struct timespec* remaining);

// 5.13 gigabytes == ~5,254 megabytes
#define BLAH_SIZE 5254

#define BLAH_QUEUE_SIZE 5

#include "ssmm_nocomments.h"
#include "ssArray_nocomments.h"
#include "ssStack_nocomments.h"
#include "ssQueue_nocomments.h"

#include "bintree_nocomments.h"

#include "blah_aligned_alloc.h"

#if 0
ssStack* SsStackConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize);

int SsStackDestruct(ssStack** _this/*reference*/);

int SsStackNum(ssStack* _this);

int SsStackReset(ssStack* _this);

bool SsStackPush(ssStack* _this, void* client);
bool SsStackPop(ssStack* _this, void* client);

bool SsStackGet(ssStack* _this, void* client);
bool SsStackSet(ssStack* _this, void* client);

bool SsStackGetAt(ssStack* _this, int index, void* client);
bool SsStackSetAt(ssStack* _this, int index, void* client);


ssQueue* SsQueueConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize);

int SsQueueDestruct(ssQueue** _this/*reference*/);

int SsQueueNum(ssQueue* _this);

int SsQueueReset(ssQueue* _this);

bool SsQueuePushBack(ssQueue* _this, void* client);
bool SsQueuePopBack(ssQueue* _this, void* client);

bool SsQueuePushFront(ssQueue* _this, void* client);
bool SsQueuePopFront(ssQueue* _this, void* client);

bool SsQueueGetBack(ssQueue* _this, void* client);
bool SsQueueSetBack(ssQueue* _this, void* client);

bool SsQueueGetFront(ssQueue* _this, void* client);
bool SsQueueSetFront(ssQueue* _this, void* client);

bool SsQueueGetAt(ssQueue* _this, int index, void* client);
bool SsQueueSetAt(ssQueue* _this, int index, void* client);
#endif

bool blahTestStack()
{
  bool result = false;

  ssStack* blahStack = 0;

  blahStack = SsStackConstruct(sizeof(int64_t), 10, 1000, 10);

  if( !blahStack)
    goto error;

  printf("\n");

  for(int64_t index = 1; index <= 5; index++)
  {
    if( !SsStackPush(blahStack, &index) )
      goto error;
  }

  for(int64_t index = 0; index < 2; index++)
  {
    int64_t getStackData = 0;

    if( !SsStackPop(blahStack, &getStackData) )
      goto error;
  }

  for(int64_t index = 6; index <= 11; index++)
  {
    if( !SsStackPush(blahStack, &index) )
      goto error;
  }

  for(int64_t index = 12; index <= 21; index++)
  {
    if( !SsStackPush(blahStack, &index) )
      goto error;
  }

  for(int64_t index = 0; index < 3; index++)
  {
    int64_t getStackData = 0;

    if( !SsStackPop(blahStack, &getStackData) )
      goto error;
  }

  for(int64_t index = 22; index <= 25; index++)
  {
    if( !SsStackPush(blahStack, &index) )
      goto error;
  }

  for(int64_t index = 5; index >= 1; index--)
  {
    if( !SsStackPush(blahStack, &index) )
      goto error;
  }

  for(int64_t index = 26; index <= 30; index++)
  {
    if( !SsStackPush(blahStack, &index) )
      goto error;
  }

  for(int64_t index = 31; index <= 41; index++)
  {
    if( !SsStackPush(blahStack, &index) )
      goto error;
  }

  for(int64_t index = 0; index >= -20; index--)
  {
    if( !SsStackPush(blahStack, &index) )
      goto error;
  }

  SsStackDestruct( &blahStack);

  result = true;

error:
  return result;
}

bool blahTestQueue()
{
  bool result = false;

  ssQueue* blahQueue = 0;

  blahQueue = SsQueueConstruct(sizeof(int64_t), 10, 1000, 10);

  if( !blahQueue)
    goto error;

  printf("\n");

  for(int64_t index = 1; index <= 5; index++)
  {
    if( !SsQueuePushBack(blahQueue, &index) )
      goto error;
  }

  for(int64_t index = 0; index < 2; index++)
  {
    int64_t getQueueData = 0;

    if( !SsQueuePopFront(blahQueue, &getQueueData) )
      goto error;
  }

  for(int64_t index = 6; index <= 11; index++)
  {
    if( !SsQueuePushBack(blahQueue, &index) )
      goto error;
  }

  for(int64_t index = 12; index <= 21; index++)
  {
    if( !SsQueuePushBack(blahQueue, &index) )
      goto error;
  }

  for(int64_t index = 0; index < 3; index++)
  {
    int64_t getQueueData = 0;

    if( !SsQueuePopFront(blahQueue, &getQueueData) )
      goto error;
  }

  for(int64_t index = 22; index <= 25; index++)
  {
    if( !SsQueuePushBack(blahQueue, &index) )
      goto error;
  }

  for(int64_t index = 5; index >= 1; index--)
  {
    if( !SsQueuePushFront(blahQueue, &index) )
      goto error;
  }

  for(int64_t index = 26; index <= 30; index++)
  {
    if( !SsQueuePushBack(blahQueue, &index) )
      goto error;
  }

  for(int64_t index = 31; index <= 41; index++)
  {
    if( !SsQueuePushBack(blahQueue, &index) )
      goto error;
  }

  for(int64_t index = 0; index >= -20; index--)
  {
    if( !SsQueuePushFront(blahQueue, &index) )
      goto error;
  }

  SsQueueDestruct( &blahQueue);

  result = true;

error:
  return result;
}

static int binTreeTest();

int main()
{
  blahRandom random = {0};

  struct timespec sleep_time = {0};

  EnableLargePageSupport();

//uint8_t** randomArray = 0;

  if( !BlahRandomConstructDefault( &random) )
    goto errorLabel;

  if( !blahTestStack() )
    goto errorLabel;

  if( !blahTestQueue() )
    goto errorLabel;

#if 0
  //printf("%llu\n", (uint64_t)time(0) );

  uint64_t* randomArray = (uint64_t*)blah_aligned_alloc(sizeof(uint64_t) * BLAH_SIZE, 0, false);
  memset(randomArray, 0, sizeof(uint64_t) * BLAH_SIZE);
#endif

  sleep_time.tv_sec = 30;

#if 0
  try
  {
    randomArray = (uint8_t**)blah_aligned_alloc(sizeof(uint8_t*) * BLAH_SIZE, 0, false);
  }
  catch(bad_alloc& )
  {
    goto errorLabel;
  }

  if( !randomArray)
    goto errorLabel;

  memset(randomArray, 0, sizeof(uint8_t*) * BLAH_SIZE);

  for(int index = 0; index < BLAH_SIZE; index++)
  {
    try
    {
      randomArray[index] = (uint8_t*)blah_aligned_alloc(sizeof(uint8_t) * 1024 * 1024, 0, false);
    }
    catch(bad_alloc& )
    {
      goto errorLabel;
    }
    
    if( !randomArray[index] )
      goto errorLabel;

    for(int indexByte = 0; indexByte < 1024 * 1024; indexByte++)
    {
      randomArray[index][indexByte] = (uint8_t)(random.previous & 0xFF);

      if( !BlahRandomIterate( &random) )
        goto errorLabel;
    }

    printf("%i\n", index);
  }

  thrd_sleep( &sleep_time, 0);

  for(int index = BLAH_SIZE - 1; index >= 0; index--)
  {
    try
    {
      blah_free_aligned_sized(randomArray[index], 0, 0);
      randomArray[index] = 0;
    }
    catch(bad_alloc& )
    {
      goto errorLabel;
    }
  }
#endif

  if(binTreeTest() )
    goto errorLabel;

  goto successLabel;

errorLabel:
  printf("error\n");
  return -1;

successLabel:
  printf("success\n");
  return 0;

#if 0
  uint64_t result1 = 0;
  uint64_t result2 = 0;

  result2 = random;

  do
  {
    result1 = result2;

    result2 = randomIterate(result1);

  }while(result2 == result1);

  randomArray[0] = result2;

  for(int index = 1; index < BLAH_SIZE; index++)
  {
    randomArray[index] = randomIterate(randomArray[index - 1] );

    //printf("%llu\n", randomArray[index] );
  }

  // void qsort(void* base, size_t nmemb, size_t size, int(*compar)(const void*, const void*) )
  qsort(randomArray, BLAH_SIZE, sizeof(uint64_t), qsortCompare);

  for(int index = 0; index < BLAH_SIZE; index++)
  {
    printf("%llu %u\n", randomArray[index], (int)(randomArray[index] / (UINT64_MAX / 1000) ) );
  }

  // (a + b) * (c + d) ==
  // a * c + a * d + b * c + b * d

  blah_free_aligned_sized(randomArray, 0, 0);
  randomArray = 0;

  return 0;
#endif
}

#if BLAH_BINTREE

// #include < stdio.h >
//#include "bintree.h"

//static const int myFatalError = -1;
static const int myFatalError = -200;

struct myStruct
{
  int testInt;
};

static int lessThan(myStruct* keyObject, myStruct* treeObject)
{
  // return non-zero if object 1 < object 2
  if(keyObject->testInt < treeObject->testInt)
    return 1;

  // return zero if object 1 >= object 2
  return 0;
}

static int check(myStruct* treeObject)
{
#if BLAH_KEEP
  printf("%i ", treeObject->testInt);
#endif

  // return non-zero to terminate traversal
  if(treeObject->testInt == myFatalError)
  {
    printf("\ndump - object found %i\n", myFatalError);
    //return 1;
  }

  // return zero to continue traversal
  return 0;
}

static int equal(myStruct* keyObject, myStruct* treeObject)
{
  // return non-zero if object 1 == object 2
  if(keyObject->testInt == treeObject->testInt)
    return 1;

  // return zero if object 1 != object 2
  return 0;
}

static int calculateLogBase2(int number)
{
  int result = 0;

  while(number)
  {
    result++;

    number /= 2;
  }

  return result;
}

static void swapInt(int& lhs, int& rhs)
{
  int temporary = lhs;

  lhs = rhs;
  rhs = temporary;
}

#include "ssmm.h"

extern ssmm* SsmmConstruct(int sizeOf, int initialCapacity, bool isTentative);
extern bool SsmmSetResize(ssmm* _this, int resize);

extern int gDebugRotate[69];

static int gFullCount = 0;
static int gModCount = 0;

static bool DebugAllocate(int* data[1000], int count)
{
  bool result = false;

  if(count % 200)
    goto error;

  if(count < 200)
    goto error;

  gFullCount = count;

  count /= 200;

  gModCount = count;

  for(int index = 0; index < 200; index++)
  {
    data[index] = (int*)blah_aligned_alloc(sizeof(int) * count, 0, false);

    if( !data[index] )
      goto error;
  }

  result = true;

error:
  return result;
}

static int DebugGet(int* data[1000], int index)
{
  return data[index / gModCount][index % gModCount];
}

static void DebugSet(int* data[1000], int index, int value)
{
  data[index / gModCount][index % gModCount] = value;
}

static void DebugFree(int* data[1000] )
{
  for(int index = 199; index >= 0; index--)
  {
    blah_free_aligned_sized(data[index], 0, 0);
    data[index] = 0;
  }
}

int binTreeTest()
{
  //ssmm* ssmmBlah = SsmmConstruct(sizeof(void*), 100, false);
  //SsmmSetResize(ssmmBlah, -1);

#if 0
    int cacheCapacity = 2;

    List* cacheList = listInitialize(cacheCapacity);

    unordered_map<int, Cache> cacheHashTable;

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
//static const int numData = 30000000;

//printf("%i\n\n", blah_get_number() );
//2097152

double queueMaximumPercentage = 0;

int numData = 2000000000;

//for(int numData = 100; numData <= 1000; numData++)
{
    memset(gDebugRotate, 0, sizeof(gDebugRotate) );

    bintree* myTree = bintree::init(5000000, sizeof(myStruct), (bintree::compare)lessThan);
    if( !myTree)
      return -1;

    //myStruct data[numData] = { {-2}, {-1}, {0}, {1}, {2} };
    int* datablah[1000] = {0};
    if( !DebugAllocate(datablah, numData) )
      return -1;

    int keyObject = myFatalError;
    int resultObject = 0;
    int findResult = 0;

    srand(1);

    //for(int loop = 0; loop < numData; loop++)
    //  myTree->insert( &data[loop], 0);

// check for inserting into tree
//   keys already sorted
//   keys alread reverse sorted
//   all the same key
    for(int index = 0; index < numData; index++)
    {
      DebugSet(datablah, index, index);//numData - index
    }

    for(int index = 0; index < (numData - 1); index++)
    {
      // if index == 0, modulus == numData - 1, indexToSwap in range [0, numData - 2], swapInt rhs index range is [1, numData - 1]
      // if index == 1, modulus == numData - 2, indexToSwap in range [0, numData - 3], swapInt rhs index range is [2, numData - 1]
      // if index == numData - 2, modulus == 1, indexToSwap in range [0, 0], swapInt rhs index range is [numData - 1, numData - 1]

      int modulus = (numData - index) - 1;

      int indexToSwap = rand() % modulus;
      
      int lhs = DebugGet(datablah, index);
      int rhs = DebugGet(datablah, (index + 1) + indexToSwap);
      
      //swapInt(data[index], data[ (index + 1) + indexToSwap] );
      DebugSet(datablah, index, rhs);
      DebugSet(datablah, (index + 1) + indexToSwap, lhs);
    }

    if( !myTree)
    {
      printf("blah a\n");
    }

#if BLAH_KEEP
    printf("\ndump original list shuffled before insertion\n");
#endif
    for(int index = 0; index < numData; index++)
    {
#if BLAH_KEEP
      printf("%i ", data[index] );
#endif
    }
#if BLAH_KEEP
    printf("\n\n");
#endif

    int numberOfClientObject = 0;

    if(myTree->isEmpty( &numberOfClientObject) != bintree::empty)
    {
      printf("blah b\n");
    }

    for(int index = 0; index < numData; index++)
    {
      int data1 = DebugGet(datablah, index);

      if(myTree->insert( &data1, 0) != bintree::ok)
      {
        printf("blah c\n");
      }

      numberOfClientObject = 0;

      if(myTree->isEmpty( &numberOfClientObject) != bintree::ok || numberOfClientObject != (index + 1) )
      {
        printf("blah d\n");
      }

#if BLAH_KEEP
      int height = myTree->depthTree();

      if(height <= 0 || height > 2 * calculateLogBase2(numberOfClientObject + 1) )
      {
        printf("blah e\n");
      }
      else
      {
        printf("%i %i %i\n", numberOfClientObject, height, 2 * calculateLogBase2(numberOfClientObject + 1) );
      }
#endif

#if BLAH_KEEP
      resultObject = -1;
      findResult = myTree->find( &keyObject, (bintree::equivalence)equal, &resultObject);
      if(findResult != bintree::ok && findResult != bintree::empty)
      {
        printf("blah f\n");
      }

      if(findResult == bintree::ok && resultObject == keyObject)
      {
        //printf("find - object found\n");
      }
      else if(findResult == bintree::empty && resultObject != keyObject)
      {
        //printf("find - object not found\n");
      }
      else
      {
        printf("blah g\n");
      }
#endif
    }

    numberOfClientObject = 0;

    if(myTree->isEmpty( &numberOfClientObject) != bintree::ok || numberOfClientObject != numData)
    {
      printf("blah h\n");
    }

#if BLAH_KEEP
    printf("dump preorder\n");
#endif
    if(myTree->dump( (bintree::evaluate)check, bintree::preorder) != bintree::ok)
    {
#if BLAH_KEEP
      printf("blah i\n");
#endif
    }
#if BLAH_KEEP
    printf("\n\n");
#endif

#if BLAH_KEEP
    printf("dump inorder\n");
#endif
    if(myTree->dump( (bintree::evaluate)check, bintree::inorder) != bintree::ok)
    {
#if BLAH_KEEP
      printf("blah i\n");
#endif
    }
#if BLAH_KEEP
    printf("\n\n");
#endif

#if BLAH_KEEP
    printf("dump postorder\n");
#endif
    if(myTree->dump( (bintree::evaluate)check, bintree::postorder) != bintree::ok)
    {
#if BLAH_KEEP
      printf("blah i\n");
#endif
    }
#if BLAH_KEEP
    printf("\n\n");
#endif

#if BLAH_KEEP
    printf("dump levelorder\n");
#endif
    if(myTree->dump( (bintree::evaluate)check, bintree::levelorder) != bintree::ok)
    {
#if BLAH_KEEP
      printf("blah i\n");
#endif
    }
#if BLAH_KEEP
    printf("\n\n");
#endif

    if(1)
    {
      int height = myTree->depthTree();

      if(height <= 0 || height > 2 * calculateLogBase2(numberOfClientObject + 1) )
      {
        printf("blah e\n");
      }
      else
      {
#if BLAH_KEEP
        printf("size %i current height %i stack %i queue %i %f max height %i\n", numberOfClientObject, height, myTree->depthStack(), myTree->depthQueue(), myTree->depthQueue() / (double)numberOfClientObject, 2 * calculateLogBase2(numberOfClientObject + 1) );
#endif
        double queuePercentage = myTree->depthQueue() / (double)numberOfClientObject;
        if(queuePercentage > queueMaximumPercentage)
          queueMaximumPercentage = queuePercentage;

        //printf("%f\n", queuePercentage);
      }
    }

    resultObject = -1;
    findResult = myTree->find( &keyObject, (bintree::equivalence)equal, &resultObject);
    if(findResult != bintree::ok && findResult != bintree::empty)
    {
      printf("blah j\n");
    }

    if(findResult == bintree::ok && resultObject == keyObject)
    {
#if BLAH_KEEP
      printf("\nfind - object found\n\n");
#endif
    }
    else if(findResult == bintree::empty && resultObject != keyObject)
    {
#if BLAH_KEEP
      printf("\nfind - object not found\n\n");
#endif
    }
    else
    {
      printf("blah k\n");
    }

    for(int index = 0; index < (numData - 1); index++)
    {
      // if index == 0, modulus == numData - 1, indexToSwap in range [0, numData - 2], swapInt rhs index range is [1, numData - 1]
      // if index == 1, modulus == numData - 2, indexToSwap in range [0, numData - 3], swapInt rhs index range is [2, numData - 1]
      // if index == numData - 2, modulus == 1, indexToSwap in range [0, 0], swapInt rhs index range is [numData - 1, numData - 1]

      int modulus = (numData - index) - 1;

      int indexToSwap = rand() % modulus;

      int lhs = DebugGet(datablah, index);
      int rhs = DebugGet(datablah, (index + 1) + indexToSwap);

      //swapInt(data[index], data[ (index + 1) + indexToSwap] );
      DebugSet(datablah, index, rhs);
      DebugSet(datablah, (index + 1) + indexToSwap, lhs);
    }

#if BLAH_KEEP
    printf("dump original list reshuffled before deletion\n");
#endif
    for(int index = 0; index < numData; index++)
    {
#if BLAH_KEEP
      printf("%i ", data[index] );
#endif
    }
#if BLAH_KEEP
    printf("\n\n");
#endif

    for(int index = 0; index < numData; index++)
    {
      numberOfClientObject = 0;

      if(myTree->isEmpty( &numberOfClientObject) != bintree::ok || numberOfClientObject != (numData - index) )
      {
        printf("blah l\n");
      }

#if BLAH_KEEP
      int height = myTree->depthTree();

      if(height <= 0 || height > 2 * calculateLogBase2(numberOfClientObject + 1) )
      {
        printf("blah m\n");
      }
      else
      {
        //printf("%i %i %i\n", numberOfClientObject, height, 2 * calculateLogBase2(numberOfClientObject + 1) );
      }
#endif

      resultObject = 0;

      int data1 = DebugGet(datablah, index);

      int result = myTree->remove( &data1, (bintree::equivalence)equal, &resultObject);

      if(result != bintree::ok || resultObject != data1)
      {
        printf("blah n\n");
      }

#if BLAH_KEEP
      resultObject = -1;
      findResult = myTree->find( &keyObject, (bintree::equivalence)equal, &resultObject);
      if(findResult != bintree::ok && findResult != bintree::empty)
      {
        printf("blah f\n");
      }

      if(findResult == bintree::ok && resultObject == keyObject)
      {
        //printf("find - object found\n");
      }
      else if(findResult == bintree::empty && resultObject != keyObject)
      {
        //printf("find - object not found\n");
      }
      else
      {
        printf("blah g\n");
      }
#endif
    }

    numberOfClientObject = 0;

    if(myTree->isEmpty( &numberOfClientObject) != bintree::empty)
    {
      printf("blah o\n");
    }

    if(1)
    {
      int height = myTree->depthTree();

      if(height != 0)
      {
        printf("blah m\n");
      }
      else
      {
        //printf("%i %i %i\n", numberOfClientObject, height, 2 * calculateLogBase2(numberOfClientObject + 1) );
      }
    }

    //printf("log2 %i %i\n", 1048576, calculateLogBase2(1048576) );
    //printf("log2 %i %i\n", 1048575, calculateLogBase2(1048575) );

    myTree->term();
    myTree = 0;

    DebugFree(datablah);

#if BLAH_KEEP
    for(int index = 0; index < countof(gDebugRotate); index++)
    {
//printf("debug rotate %i %i\n", index, gDebugRotate[index] );
    }
    printf("\n");

    for(int index = 0; index < (countof(gDebugRotate) - 1); index++)
    {
      if(index == 1 || index == 21)
      {
        if(gDebugRotate[index] )
          printf("debug rotate %i %i\n", index, gDebugRotate[index] );
      }
      else if( !gDebugRotate[index] )
      {
        printf("debug rotate %i %i\n", index, gDebugRotate[index] );
      }
    }
    printf("\n");
#endif

#if BLAH_KEEP
    printf("end\n");
#endif
}

    printf("\nqueue max %f\n", queueMaximumPercentage);

    return 0;
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
