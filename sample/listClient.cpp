
// listClient.cpp
//
// Function: Test code for List Package
//
// Author: Bruce McQuistan (brucemc@digipen.edu) and Robert Aldridge (raldridg@digipen.edu)

//#include <cstdint>
//#include <cstdlib>
//#include <cstdio>
//#include <cstring>
//#include <ctime>

#include "listObject.h"
#include "list.h"

#if 0/*defined(_MSC_VER) */

//#include <crtdbg.h>

#include <windows.h>

#else

extern "C"
{

union _LARGE_INTEGER
{
  struct
  {
    unsigned long LowPart;
    long HighPart;

  }DUMMYSTRUCTNAME;

  struct
  {
    unsigned long LowPart;
    long HighPart;

  }u;

  long long QuadPart;

};

typedef union _LARGE_INTEGER LARGE_INTEGER;

__declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount);

__declspec(dllimport) int __stdcall QueryPerformanceFrequency(LARGE_INTEGER* lpFrequency);

}

#endif

static int Evaluate(CLIENT_POTYPE* Object)
{
  printf("This object is %d\n", Object->integer);
  return 0;
}

static int LessThan(CLIENT_POTYPE Arg1, CLIENT_POTYPE Arg2)
{
  return (Arg1.integer > Arg2.integer);
}

static int GreaterThan(CLIENT_POTYPE Arg1, CLIENT_POTYPE Arg2)
{
  return (Arg1.integer > Arg2.integer);
}

static int AreEqual(CLIENT_POTYPE Arg1, CLIENT_POTYPE Arg2)
{
  return (Arg1.integer == Arg2.integer);
}

//#define NUMBER 16384
//#define NUMBER 1024
#define NUMBER 1

static void ProcessList(LIST_HEAD* ListHead, CLIENT_POTYPE InputArray[NUMBER], const char* IdentifierString)
{
  unsigned int count = 0;

  unsigned long insertTime = 0;
  unsigned long sortTime = 0;

  uint64_t t0 = 0;
  uint64_t t1 = 0;

  // time insertions

  t0 = 0;
  QueryPerformanceCounter( (LARGE_INTEGER*) &t0);

  for(count = 0; count < NUMBER; ++count)
    ListInsert(ListHead, InputArray[count], LessThan);

  t1 = 0;
  QueryPerformanceCounter( (LARGE_INTEGER*) &t1);

  insertTime = (uint32_t)t1 - (uint32_t)t0;

  // time sorting

  t0 = 0;
  QueryPerformanceCounter( (LARGE_INTEGER*) &t0);

  ListSort(ListHead, GreaterThan);

  t1 = 0;
  QueryPerformanceCounter( (LARGE_INTEGER*) &t1);

  sortTime = (uint32_t)t1 - (uint32_t)t0;

  ListDump(ListHead, Evaluate, 0);

  printf("InsertTime taken is %i microseconds for %s\n", (int)insertTime, IdentifierString);

  printf("SortTime taken is %i microseconds for %s\n", (int)sortTime, IdentifierString);
}

static int mainListTest()
{
  //long oldValue = 0;

  unsigned int count = 0;
  LIST_HEAD* listHead = 0;

  CLIENT_POTYPE input[NUMBER];
  memset( &input, 0, NUMBER * sizeof(CLIENT_POTYPE) );

#ifndef NDEBUG
  //oldValue = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
  //_CrtSetDbgFlag(oldValue | _CRTDBG_LEAK_CHECK_DF);
#else
  //oldValue = oldValue;
#endif

  listHead = ListInit(LessThan, NUMBER);

  srand(12345);

  for(count = 0; count < NUMBER; ++count)
    input[count].integer = rand();

  ProcessList(listHead, input, "Random input");

  for(count = 0; count < NUMBER; ++count)
    ListRemove(listHead, AreEqual, &(input[count] ) );

  for(count = 0; count < NUMBER; ++count)
    input[count].integer = (int) ( (2 * count + (input[count].integer / 16385) ) / 2);

  ProcessList(listHead, input, "QuasiInverse input");

  ListTerminate(listHead);

  return 0;
}
