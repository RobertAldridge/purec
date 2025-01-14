/*
 *  File:       client.c
 *
 *  Function:   Test code for List Package
 *
 *  Author:     Bruce McQuistan (brucemc@digipen.edu) and Robert Aldridge (raldridg@digipen.edu)
 *
 */

#include <windows.h>
#include <winbase.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <crtdbg.h>

#include "client_potype.h"
#include "listpub.h"

#define WIN32_LEAN_AND_MEAN

int
Evaluate(
    CLIENT_POTYPE*  Object
    )
{
    printf("This object is %d\n", Object->integer);
	return 0;
}

int
LessThan(
    CLIENT_POTYPE  Arg1,
    CLIENT_POTYPE  Arg2
    )
{
    return (Arg1.integer > Arg2.integer);
}

int
GreaterThan(
    CLIENT_POTYPE  Arg1,
    CLIENT_POTYPE  Arg2
    )
{
    return (Arg1.integer > Arg2.integer);
}

int AreEqual(CLIENT_POTYPE Arg1, CLIENT_POTYPE Arg2)
{
	return(Arg1.integer == Arg2.integer);
}

//#define NUMBER 16384
#define NUMBER 1024



void
ProcessList(
    PLIST_HEAD    ListHead,
    CLIENT_POTYPE InputArray[NUMBER],
    const char     *    IdentifierString
    )
{
    unsigned int    count;
    unsigned long   insertTime, sortTime;
    LARGE_INTEGER   t0, t1;

    //
    //  Time insertions
    //

    QueryPerformanceCounter(&t0);
    for(count = 0; count < NUMBER; ++count)
        ListInsert(ListHead, InputArray[count], LessThan);

    QueryPerformanceCounter(&t1);

    insertTime = t1.LowPart - t0.LowPart;

    //
    //  Time sorting
    //

    QueryPerformanceCounter(&t0);
    ListSort(ListHead, GreaterThan);
    QueryPerformanceCounter(&t1);
    sortTime = t1.LowPart - t0.LowPart;

    ListDump(ListHead, Evaluate, 0);

    printf("InsertTime taken is %i microseconds for %s \n",
           (int)insertTime,
           IdentifierString);

    printf("SortTime taken is %i microseconds for %s\n",
            (int)sortTime,
            IdentifierString);
}

int
mainListTest(
    void
    )
{
	long          OldValue;
    unsigned int  count;
	PLIST_HEAD    listHead;
    CLIENT_POTYPE input[NUMBER];

	#ifndef NDEBUG
		OldValue = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
		_CrtSetDbgFlag(OldValue|_CRTDBG_LEAK_CHECK_DF);
	#else
		OldValue = OldValue;
	#endif

    listHead = ListInit(LessThan, NUMBER);

    srand(12345);

    for(count = 0; count < NUMBER; ++count)
        input[count].integer = rand();

    ProcessList(listHead, input, "Random input");

    for(count = 0; count < NUMBER; ++count)
        ListRemove(listHead, AreEqual, &(input[count]));

    for(count = 0; count < NUMBER; ++count)
        input[count].integer = (int) ( (2 * count + (input[count].integer / 16385) ) / 2);

    ProcessList(listHead, input, "QuasiInverse input");

    ListTerminate(listHead);

    return 0;
}
