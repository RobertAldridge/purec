

// list.cpp
//
// Function: Holds private interface definitions for a First Class
//           ADT list package.
//
// Author: Bruce McQuistan (brucemc@digipen.edu) and Robert Aldridge (raldridg@digipen.edu)
//
// Revision History:
//   5/3/99 - Created. brucemc.
//   4/13/00 - List sort using mergesort added. brucemc.

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>

#define ERROR -1

#define NO_ERROR 0

#include "list.h"

#include "listObject.h"

struct LIST_HEAD
{
  int CurrentIndex;

  int CurrentTraverseIndex;

  int MaxNumberOfObjects;

  // Recursion test variables
  unsigned char Dump;

  unsigned char Find;

  unsigned char GetExtrema;

  unsigned char Remove;

  unsigned char Sort;
  //

  unsigned char padding[7];

  CLIENT_EVALUATE ClientEvaluate;

  CLIENT_EQUIVALENCE ClientEquality;

  CLIENT_COMPARE ClientCompare;

  // needs to be a seperate allocation for dynamic growth
  CLIENT_POTYPE* ObjectArray;
};

// The initialization routine.
//
// Arguments:
//   ClientCompare - An optional permanent COMPARE function provided by the client.
//                   May be 0.
//
//   MaxNumberOfObjects - An optional hint at the maximal number of
//                        objects the client wishes to put in the list.
//
// Returns:
//   A LIST_HEAD* object which must be passed to all other functions
//   in this list interface. It will be 0 if the memory cannot
//   be allocated for the list.
//
// Implementation Details:
//   O(N) - Upper bounds on runtime proportional to the guessed maximum number
//   of objects because of memory allocation and zeroing the memory out.

LIST_HEAD* ListInit(CLIENT_COMPARE ClientCompare, INDEX_TYPE MaxNumberOfObjects)
{
  LIST_HEAD* Head = 0;

  if(MaxNumberOfObjects < 0)
    goto label_return;

  Head = (LIST_HEAD*)calloc(1, sizeof(LIST_HEAD) );
  if( !Head)
    goto label_return;

  // times 2 for the buffer for the sorting routine
  Head->ObjectArray = (CLIENT_POTYPE*)calloc(1, sizeof(CLIENT_POTYPE) * (MaxNumberOfObjects * 2) );
  if( !Head->ObjectArray)
  {
    free(Head);
    Head = 0;

    goto label_return;
  }

  Head->ClientCompare = ClientCompare;
  Head->MaxNumberOfObjects = MaxNumberOfObjects;

label_return:
  return Head;
}

// The Check if empty routine
//
// Arguments:
//   Head - The LIST_HEAD* referring to a particular instance of
//          the list ADT.
//
//   NumberOfClientObjects - An optional INDEX_TYPE pointer, may be 0.
//                           It will be set to the number of client objects
//                           in the list if it is not 0
//
// Returns:
//   1 if list is empty, 0 otherwise.
//
// Implementation Details:
//   O(C) - Upper bounds on runtime constant because the number of
//   calculations are the same no matter the size of the list.

INDEX_TYPE ListIsEmpty(LIST_HEAD* Head, INDEX_TYPE* NumberOfClientObjects)
{
  INDEX_TYPE result = 0;

  if( !Head || !Head->ObjectArray)
    goto label_return;

  if(NumberOfClientObjects)
    *NumberOfClientObjects = Head->CurrentIndex;

  result = ( !Head->CurrentIndex);

label_return:
  return result;
}

// The POTYPE insertion routine.
//
// Arguments:
//   Head - The LIST_HEAD* referring to a particular instance of
//          the list ADT.
//
//   ClientObject - The object to be inserted into the list.
//
//   ClientCompare - An optional permanent COMPARE function pointer, may be 0.
//
// Returns:
//   0 if successful, nonzero otherwise.
//
// Implementation Details:
//   O(C) - Upper bounds on runtime constant because the number of
//   calculations are the same no matter the size of the list.
//
//   O(N) - If extra memory allocation is required, upper bounds on runtime
//   proportional to the number of objects currently in the list because of memory
//   allocation, and zeroing the memory out, and copying it over. Only happens when
//   the number of items in the list is equal to the guessed maximum number passed
//   into ListInit, in which case the guessed maximum number will be doubled.
//   After that the runtime will only be O( N ) every time the array doubles its size.
//   Since this only happens every time the array doubles, O( lg N ) is the upper
//   bounds on the amount of times this will happen.

INDEX_TYPE ListInsert(LIST_HEAD* Head, CLIENT_POTYPE ClientObject, CLIENT_COMPARE ClientCompare)
{
  INDEX_TYPE result = ERROR;

  CLIENT_POTYPE* GrowArray = 0;

  if( !Head || !Head->ObjectArray || Head->Sort || Head->Remove)
    goto label_return;

  if(ClientCompare)
    Head->ClientCompare = ClientCompare;

  if( Head->CurrentIndex >= (Head->MaxNumberOfObjects - 1) )
  {
    if(Head->Dump || Head->GetExtrema || Head->Find)
    {
      // If assert is triggered the client needs to increase the
      // guessed maximum passed into ListInit, or call
      // ListInsert outside of a list traversal routine.

      assert("ListInsert is trying to grow from within a list traversal routine." && 0);

      goto label_return;
    }

    GrowArray = (CLIENT_POTYPE*)calloc(1, sizeof(CLIENT_POTYPE) * (Head->MaxNumberOfObjects * 4) );
    if( !GrowArray)
      goto label_return;

    memcpy(GrowArray, Head->ObjectArray, sizeof(CLIENT_POTYPE) * Head->CurrentIndex);

    Head->MaxNumberOfObjects += Head->MaxNumberOfObjects;

    free(Head->ObjectArray);

    Head->ObjectArray = GrowArray;
  }

  Head->ObjectArray[Head->CurrentIndex++ ] = ClientObject;

  result = NO_ERROR;

label_return:
  return result;
}

// The Remove routine.
//
// Arguments:
//   Head - The LIST_HEAD* referring to a particular instance
//          of the list ADT.
//
//   ClientEquality - An optional temporary EQUIVALENCE function pointer which only
//                    returns 1 if the objects are considered equivalent.
//                    It returns 0 otherwise. If this is 0, the first
//                    element in the list is removed.
//
//   ClientObject - A required POTYPE* specifying both the object to be
//                  found and is used as an out parameter.
//
// Returns:
//   0 if successful, nonzero otherwise.
//
// Implementation Details:
//   O(N) - Upper bounds on runtime proportional to the number of objects currently
//   in the list because of list traversal.

INDEX_TYPE ListRemove(LIST_HEAD* Head, CLIENT_EQUIVALENCE ClientEquality, CLIENT_POTYPE* ClientObject)
{
  INDEX_TYPE result = ERROR;

  int loop = 0;
  int Num = 0;

  if( !Head || !Head->ObjectArray || !ClientObject || Head->Remove || Head->Sort || Head->Dump || Head->GetExtrema || Head->Find )
    goto label_return;

  Num = Head->CurrentIndex;

  if(ClientEquality)
    Head->ClientEquality = ClientEquality;

  if(Num < 1)
    goto label_return;

  if( !ClientEquality)
  {
    *ClientObject = Head->ObjectArray[0];

    if( --Head->CurrentIndex > 0)
      memcpy( &Head->ObjectArray[0], &Head->ObjectArray[1], sizeof(CLIENT_POTYPE) * Head->CurrentIndex);

    memset( &Head->ObjectArray[Head->CurrentIndex], 0, sizeof(CLIENT_POTYPE) );

    Head->CurrentTraverseIndex = 0;

    result = NO_ERROR;

    goto label_return;
  }

  do
  {
    Head->Remove = 1;

    if(ClientEquality( *ClientObject, Head->ObjectArray[loop] ) )
    {
      memcpy(ClientObject, &Head->ObjectArray[loop], sizeof(CLIENT_POTYPE) );

      if( --Head->CurrentIndex > 0)
        memcpy( &Head->ObjectArray[loop], &Head->ObjectArray[loop + 1], sizeof(CLIENT_POTYPE) * ( (size_t)Head->CurrentIndex - loop) );

      memset( &Head->ObjectArray[Head->CurrentIndex], 0, sizeof(CLIENT_POTYPE) );

      Head->CurrentTraverseIndex = 0;

      Head->Remove = 0;

      result = NO_ERROR;

      goto label_return;
    }

  }while( ++loop != Num);

  Head->Remove = 0;

label_return:
  return result;
}

// The Find routine.
//
// Arguments:
//   Head - The LIST_HEAD* referring to a particular instance
//          of the list ADT.
//
//   ClientEquality - An optional temporary EQUIVALENCE function pointer which only
//                    returns 1 if the objects are considered equivalent.
//                    It returns 0 otherwise. If this is 0, the first
//                    element in the list is returned.
//
//   ClientObject - A required POTYPE* specifying both the object to be
//                  found and is used as an out parameter.
//
// Returns:
//   0 if successful, nonzero otherwise.
//
// Implementation Details:
//   O(N) - Upper bounds on runtime proportional to the number of objects currently
//   in the list because of list traversal.

INDEX_TYPE ListFind(LIST_HEAD* Head, CLIENT_EQUIVALENCE ClientEquality, CLIENT_POTYPE* ClientObject)
{
  INDEX_TYPE result = ERROR;

  int loop = 0;
  int Num = 0;

  if( !Head || !Head->ObjectArray || !ClientObject || Head->Find || Head->Sort)
    goto label_return;

  Num = Head->CurrentIndex;

  if(ClientEquality)
    Head->ClientEquality = ClientEquality;

  if(Num < 1)
    goto label_return;

  if( !ClientEquality)
  {
    *ClientObject = Head->ObjectArray[0];

    result = NO_ERROR;

    goto label_return;
  }

  do
  {
    if( Head->Dump || Head->GetExtrema || Head->Remove)
      goto label_return;

    Head->Find = 1;

    if(ClientEquality( *ClientObject, Head->ObjectArray[loop] ) )
    {
      *ClientObject = Head->ObjectArray[loop];

      Head->Find = 0;

      result = NO_ERROR;

      goto label_return;
    }

  }while( ++loop != Num);

  Head->Find = 0;

label_return:
  return result;
}

// The GetNext routine.
//
// Arguments:
//   Head - The LIST_HEAD* referring to a particular instance
//          of the list ADT.
//
//   ClientObject - A required POTYPE* where the next object is to be placed
//
//   Reset - A bool when true, will reset the search to begin
//           at the start of the list.
//
// Returns:
//   0 if successful, nonzero otherwise.
//
// Implementation Details:
//   O(C) - Upper bounds on runtime constant because the number of
//   calculations are the same no matter the size of the list.

INDEX_TYPE ListGetNext(LIST_HEAD* Head, CLIENT_POTYPE* ClientObject, bool Reset)
{
  INDEX_TYPE result = ERROR;

  if( !Head || !Head->ObjectArray || !ClientObject)
    goto label_return;

  if(Reset)
    Head->CurrentTraverseIndex = 0;

  if(Head->CurrentIndex < 1 || !ClientObject || Head->CurrentTraverseIndex >= (Head->MaxNumberOfObjects - 1) )
    goto label_return;

  *ClientObject = Head->ObjectArray[Head->CurrentTraverseIndex++ ];

  result = NO_ERROR;

label_return:
  return result;
}

// The terminate routine.
//
// Arguments:
//   Head - The LIST_HEAD* referring to a particular instance of
//          the list ADT.
//
// Returns:
//   void
//
// Implementation Details:
//   O(C) - Upper bounds on runtime constant because the number of
//   calculations are the same no matter the size of the list.

void ListTerminate(LIST_HEAD* Head)
{
  if(Head && !Head->Dump && !Head->GetExtrema && !Head->Find && !Head->Remove && !Head->Sort)
  {
    if(Head->ObjectArray)
    {
      free(Head->ObjectArray);
      Head->ObjectArray = 0;
    }

    free(Head);
    Head = 0;
  }
}

// A sort routine.
//
// Arguments:
//   Head - The LIST_HEAD* referring to a particular instance of
//          the list ADT.
//
//   ClientCompare - An optional temporary COMPARE function pointer. If not 0, it
//                   overrides the default COMPARE function specified at
//                   init time.
//
// Returns:
//   void
//
// Implementation Details:
//   O(N lg(N) ) - This sorts the list using an algorithm whose upper bounds
//   on runtime is proportional to the number of objects currently
//   in the list times the log base 2 of the number of objects currently
//   in the list.

// local function used in ListSort
// from McQuistan
static void insertion(CLIENT_POTYPE* ObjectArray, INDEX_TYPE StartIndex, INDEX_TYPE EndIndex, CLIENT_COMPARE ClientCompare)
{
  INDEX_TYPE outerCount = 0;
  INDEX_TYPE innerCount = 0;

  CLIENT_POTYPE sentinel;
  memset( &sentinel, 0, sizeof(CLIENT_POTYPE) );

  CLIENT_POTYPE temporary;
  memset( &temporary, 0, sizeof(CLIENT_POTYPE) );

  // Put the smallest element in the entire array in the zeroth slot.

  for(outerCount = StartIndex + 1; outerCount <= EndIndex; ++outerCount)
  {
    if(ClientCompare(ObjectArray[outerCount], ObjectArray[StartIndex] ) )
    {
      temporary = ObjectArray[outerCount];

      ObjectArray[outerCount] = ObjectArray[StartIndex];
      ObjectArray[StartIndex] = temporary;
    }
  }

  for(outerCount = StartIndex + 2; outerCount <= EndIndex; ++outerCount)
  {
    // Set aside the item at the start+1 of the unsorted subarray.

    sentinel = ObjectArray[outerCount];

    innerCount = outerCount;

    // While the sentinel is less than other entries, transpose
    // these other entries. At some point, the index will take
    // the comparisons into the sorted subarray every element
    // of which is less than the sentinel, so the condition will
    // fail.

    while(ClientCompare(sentinel, ObjectArray[innerCount - 1] ) )
    {
      // Move the items to the right.

      ObjectArray[innerCount] = ObjectArray[innerCount - 1];

      --innerCount;
    }

    // Now the smallest item of those covered is in the left most slot.
    // So the sub array to the left is sorted.

    ObjectArray[innerCount] = sentinel;

    // For this implementation, the number of comparisons is n * ( n + 1) / 4
  }
}

// local function used in ListSort
// from SedgeWick
static void mergeAB(CLIENT_POTYPE* c, CLIENT_POTYPE* a, INDEX_TYPE N, CLIENT_POTYPE* b, INDEX_TYPE M, CLIENT_COMPARE ClientCompare)
{
  INDEX_TYPE i = 0;
  INDEX_TYPE j = 0;
  INDEX_TYPE k = 0;

  for(i = 0, j = 0, k = 0; k < N + M; k++)
  {
    if(i == N)
    {
      c[k] = b[j++ ];
      continue;
    }

    if(j == M)
    {
      c[k] = a[i++ ];
      continue;
    }

    c[k] = ClientCompare(a[i], b[j] ) ? a[i++ ] : b[j++ ];
  }
}

// local function used in ListSort
// from SedgeWick
static void mergesortABr(CLIENT_POTYPE* a, CLIENT_POTYPE* b, INDEX_TYPE l, INDEX_TYPE r, CLIENT_POTYPE* aux, CLIENT_COMPARE ClientCompare)
{
  INDEX_TYPE m = (l + r) / 2;

  if(r - l <= 10)
  {
    insertion(a, l, r, ClientCompare);

    goto label_return;
  }

  mergesortABr(b, a, l, m, aux, ClientCompare);

  mergesortABr(b, a, m + 1, r, aux, ClientCompare);

  mergeAB(a + 1, b + 1, m - l + 1, b + m + 1, r - m, ClientCompare);

label_return:
  return;
}

// local function used in ListSort
// from SedgeWick
static void mergesortAB(LIST_HEAD* Head, INDEX_TYPE l, INDEX_TYPE r)
{
  INDEX_TYPE i = 0;

  CLIENT_POTYPE* a = Head->ObjectArray;

  CLIENT_POTYPE* aux = a + Head->MaxNumberOfObjects;

  for(i = l; i <= r; i++)
    aux[i] = a[i];

  mergesortABr(a, aux, l, r, aux, Head->ClientCompare);
}

void ListSort(LIST_HEAD* Head, CLIENT_COMPARE ClientCompare)
{
  CLIENT_COMPARE TempClientCompare = 0;

  if( !Head || !Head->ObjectArray || Head->Dump || Head->Find || Head->GetExtrema || Head->Remove || Head->Sort)
    goto label_return;

  TempClientCompare = Head->ClientCompare;

  if(ClientCompare)
    Head->ClientCompare = ClientCompare;

  if( !Head->ClientCompare || Head->CurrentIndex <= 1)
  {
    Head->ClientCompare = TempClientCompare;

    goto label_num;
  }

  Head->Sort = 1;

  mergesortAB(Head, 0, Head->CurrentIndex - 1);

  Head->ClientCompare=TempClientCompare;

  Head->Sort = 0;

label_num:

label_return:
  return;
}

// A get extrema routine.
//
// Arguments:
//   Head - The LIST_HEAD* referring to a particular instance of
//          the list ADT.
//
//   ClientCompare - An optional temporary COMPARE function pointer.
//
//   GetGreatest - A bool which if true, causes the greatest POTYPE
//                 to be returned. If false, it causes the the least POTYPE
//                 value to be returned.
//
// Returns:
//   POTYPE.
//
// Implementation Details:
//   O(N) - Upper bounds on runtime proportional to the number of objects currently
//   in the list because of list traversal.

CLIENT_POTYPE ListGetExtrema(LIST_HEAD* Head, CLIENT_COMPARE ClientCompare, bool GetGreatest)
{
  CLIENT_POTYPE result;
  memset( &result, 0, sizeof(CLIENT_POTYPE) );

  int loop = 0;
  int Num = 0;

  if( !Head || !Head->ObjectArray || Head->Dump || Head->Find || Head->GetExtrema || Head->Remove || Head->Sort )
    goto label_return;

  Num = Head->CurrentIndex;

  if(Num < 1)
    goto label_return;

  if( !ClientCompare)
    ClientCompare = Head->ClientCompare;

  if( !ClientCompare)
    goto label_return;

  result = Head->ObjectArray[loop++ ];

  Head->GetExtrema = 1;

  if(GetGreatest)
  {
    do
    {
      if( !ClientCompare(result, Head->ObjectArray[loop] ) )
        result = Head->ObjectArray[loop];

    }while( ++loop != Num);
  }
  else
  {
    do
    {
      if( ClientCompare(result, Head->ObjectArray[loop] ) )
        result = Head->ObjectArray[loop];

    }while( ++loop != Num);
  }

  Head->GetExtrema = 0;

label_return:
  return result;
}

// A list dump routine.
//
// Arguments:
//   Head - The LIST_HEAD* referring to a particular instance of
//          the list ADT.
//
//   ClientEvaluate - An optional temporary EVALUATE function provided by the client.
//
//   Reverse - If true, dump list in reverse order.
//
// Returns:
//   0 if successful and there was a full dump,
//   1 if successful and the dump was abruptly terminated,
//   nonzero and nonone otherwise.
//
// Remark: if the ClientEvaluate function does not return 0, the dump will abruptly terminate
//
// Implementation Details:
//   O(N) - Upper bounds on runtime proportional to the number of objects currently
//   in the list because of list traversal.

INDEX_TYPE ListDump(LIST_HEAD* Head, CLIENT_EVALUATE ClientEvaluate, bool Reverse)
{
  INDEX_TYPE result = ERROR;

  int loop = 0;
  int Num = 0;

  if( !Head || !Head->ObjectArray || Head->Dump || Head->Find || Head->GetExtrema || Head->Remove || Head->Sort)
    goto label_return;

  if( !ClientEvaluate && !Head->ClientEvaluate)
    goto label_return;

  Num = Head->CurrentIndex;

  if(Num < 1)
    goto label_num;

  if(ClientEvaluate)
    Head->ClientEvaluate = ClientEvaluate;
  else
    ClientEvaluate = Head->ClientEvaluate;

  Head->Dump = 1;

  if(Reverse)
  {
    --Num;

    do
    {
      if(ClientEvaluate( &Head->ObjectArray[Num] ) )
      {
        Head->Dump = 0;

        // return true if there is no error but
        // the client wants to abruptly stop dump
        result = true;

        goto label_num;
      }

    }while(Num-- );
  }
  else
  {
    do
    {
      if(ClientEvaluate( &Head->ObjectArray[loop] ) )
      {
        Head->Dump = 0;

        // return true if there is no error but
        // the client wants to abruptly stop dump
        result = true;

        goto label_num;
      }

    }while( ++loop != Num);
  }

  Head->Dump = 0;

label_num:
  if(result == ERROR)
    result = NO_ERROR;

label_return:
  return result;
}
