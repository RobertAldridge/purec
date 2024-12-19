/*
 *  File:       listpub.h
 *
 *  Function:   Holds public interface definitions for a First Class
 *              ADT list package.
 *
 *  Author:     Bruce McQuistan (brucemc@digipen.edu)
 *
 *  Revision History:
 *              5/3/99  - Created. brucemc.
 *              4/13/00 - List sort using mergesort added. brucemc.
 *
 */

#ifdef __cplusplus
	extern "C" {
#endif

///////////////////////////////////////////////////////////////
//
//  Typedef the index
//

typedef int INDEX_TYPE;

//
//  Opaque type for head object
//

typedef struct __LIST_HEAD * PLIST_HEAD;

//
//  Function pointer typedefs to be used to define contract between client
//  and this ADT. First is a compare function, second is an evaluate
//  function.
//

typedef
INDEX_TYPE
(*CLIENT_COMPARE)
(
    CLIENT_POTYPE ClientObject1,
    CLIENT_POTYPE ClientObject2
);

typedef
INDEX_TYPE
(*CLIENT_EVALUATE)
(
	CLIENT_PPOTYPE ClientObject1
);

typedef
INDEX_TYPE
(*CLIENT_EQUIVALENCE)
(
	CLIENT_POTYPE ClientObject1,
	CLIENT_POTYPE ClientObject2
);

//
//  The initialization routine.
//
//  Arguments:
//      ClientCompare - An optional permanent COMPARE function provided by the client.
//                      May be NULL.
//
//      MaxNumberOfObjects - An optional hint at the maximal number of
//                           objects the client wishes to put in the list.
//
//  Returns:
//      A PLIST_HEAD object which must be passed to all other functions
//      in this list interface. It will be NULL if the memory cannot
//      be allocated for the list.
//
//	Implementation Details:
//		O ( N ) - Upper bounds on runtime proportional to the guessed maximum number
//		of objects because of memory allocation and zeroing the memory out.
//
//
//

PLIST_HEAD
ListInit
(
	CLIENT_COMPARE ClientCompare,
	INDEX_TYPE     MaxNumberOfObjects
);

//
//  The Check if empty routine
//
//  Arguments:
//      Head   - The PLIST_HEAD referring to a particular instance of
//               the list ADT.
//
//      NumberOfClientObjects - An optional INDEX_TYPE pointer, may be NULL.
//                              It will be set to the number of client objects
//                              in the list if it is not NULL
//
//  Returns:
//      1 if list is empty, 0 otherwise.
//
//	Implementation Details:
//		O ( C ) - Upper bounds on runtime constant because the number of
//		calculations are the same no matter the size of the list.
//
//
//

INDEX_TYPE
ListIsEmpty
(
	PLIST_HEAD Head,
	INDEX_TYPE *NumberOfClientObjects
);

//
//  The POTYPE insertion routine.
//
//  Arguments:
//      Head   - The PLIST_HEAD referring to a particular instance of
//               the list ADT.
//
//      ClientObject - The object to be inserted into the list.
//
//      ClientCompare - An optional permanent COMPARE function pointer, may be NULL.
//
//  Returns:
//      0 if successful, nonzero otherwise.
//
//	Implementation Details:
//		O ( C ) - Upper bounds on runtime constant because the number of
//		calculations are the same no matter the size of the list.
//
//	    O ( N ) - If extra memory allocation is required, upper bounds on runtime
//		proportional to the number of objects currently in the list because of memory
//		allocation, and zeroing the memory out, and copying it over. Only happens when
//      the number of items in the list is equal to the guessed maximum number passed
//      into ListInit, in which case the guessed maximum number will be doubled.
//		After that the runtime will only be O( N ) every time the array doubles its size.
//		Since this only happens every time the array doubles, O( lg N ) is the upper
//		bounds on the amount of times this will happen.
//
//
//

INDEX_TYPE
ListInsert
(
	PLIST_HEAD     Head,
	CLIENT_POTYPE  ClientObject,
	CLIENT_COMPARE ClientCompare
);

//
//  The Remove routine.
//
//  Arguments:
//      Head   -            The PLIST_HEAD referring to a particular instance
//                          of the list ADT.
//
//      ClientEquality -    An optional temporary EQUIVALENCE function pointer which only
//                          returns 1 if the objects are considered equivalent.
//                          It returns 0 otherwise. If this is NULL, the first
//                          element in the list is removed.
//
//      ClientObject -      A required PPOTYPE specifying both the object to be
//                          found and is used as an out parameter.
//
//  Returns:
//      0 if successful, nonzero otherwise.
//
//	Implementation Details:
//		O ( N ) - Upper bounds on runtime proportional to the number of objects currently
//		in the list because of list traversal.
//
//  Note: ListGetNext is reset automatically when ListRemove returns successfully.
//
//
//

INDEX_TYPE
ListRemove
(
	PLIST_HEAD         Head,
	CLIENT_EQUIVALENCE ClientEquality,
	CLIENT_PPOTYPE     ClientObject
);

//
//  The Find routine.
//
//  Arguments:
//      Head   -            The PLIST_HEAD referring to a particular instance
//                          of the list ADT.
//
//      ClientEquality -    An optional temporary EQUIVALENCE function pointer which only
//                          returns 1 if the objects are considered equivalent.
//                          It returns 0 otherwise. If this is NULL, the first
//                          element in the list is returned.
//
//      ClientObject -      A required PPOTYPE specifying both the object to be
//                          found and is used as an out parameter.
//
//  Returns:
//      0 if successful, nonzero otherwise.
//
//	Implementation Details:
//		O ( N ) - Upper bounds on runtime proportional to the number of objects currently
//		in the list because of list traversal.
//
//
//

INDEX_TYPE
ListFind
(
	PLIST_HEAD         Head,
	CLIENT_EQUIVALENCE ClientEquality,
	CLIENT_PPOTYPE     ClientObject
);

//
//  The GetNext routine.
//
//  Arguments:
//      Head         -      The PLIST_HEAD referring to a particular instance
//                          of the list ADT.
//
//      ClientObject -      A required PPOTYPE where the next object is to be placed
//
//      Reset        -      A BOOL when TRUE, will reset the search to begin
//                          at the start of the list.
//
//  Returns:
//      0 if successful, nonzero otherwise.
//
//	Implementation Details:
//		O ( C ) - Upper bounds on runtime constant because the number of
//		calculations are the same no matter the size of the list.
//
//  Note: ListGetNext is reset automatically when ListRemove returns successfully.
//
//
//

INDEX_TYPE
ListGetNext
(
	PLIST_HEAD     Head,
	CLIENT_PPOTYPE ClientObject,
	INDEX_TYPE     Reset
);

//
//  The terminate routine.
//
//  Arguments:
//      Head   - The PLIST_HEAD referring to a particular instance of
//               the list ADT.
//
//  Returns:
//      void
//
//	Implementation Details:
//		O ( C ) - Upper bounds on runtime constant because the number of
//		calculations are the same no matter the size of the list.
//
//
//

void
ListTerminate
(
	PLIST_HEAD Head
);

//
//  A sort routine.
//
//  Arguments:
//      Head    -   The PLIST_HEAD referring to a particular instance of
//                  the list ADT.
//
//      ClientCompare -   An optional temporary COMPARE function pointer. If not NULL, it
//                        overrides the default COMPARE function specified at
//                        init time.
//
//  Returns:
//      void.
//
//  Implementation Details:
//		O( N lg N ) - This sorts the list using an algorithm whose upper bounds
//		on runtime is proportional to the number of objects currently
//		in the list times the log base 2 of the number of objects currently
//		in the list.
//

void
ListSort
(
	PLIST_HEAD     Head,
	CLIENT_COMPARE ClientCompare
);

//
//  A get extrema routine.
//
//  Arguments:
//      Head         -  The PLIST_HEAD referring to a particular instance of
//                      the list ADT.
//
//      ClientCompare      -  An optional temporary COMPARE function pointer.
//
//      GetGreatest  -  An int which if TRUE, causes the greatest POTYPE
//                      to be returned. If FALSE, it causes the the least POTYPE
//                      value to be returned.
//
//  Returns:
//      POTYPE.
//
//	Implementation Details:
//		O ( N ) - Upper bounds on runtime proportional to the number of objects currently
//		in the list because of list traversal.
//
//
//

CLIENT_POTYPE
ListGetExtrema
(
	PLIST_HEAD     Head,
	CLIENT_COMPARE ClientCompare,
	INDEX_TYPE     GetGreatest
);

//
//  A list dump routine.
//
//  Arguments:
//      Head   - The PLIST_HEAD referring to a particular instance of
//               the list ADT.
//
//      ClientEvaluate - An optional temporary EVALUATE function provided by the client.
//
//      Reverse - If TRUE, dump list in reverse order.
//
//  Returns:
//      0 if successful and there was a full dump,
//      1 if successful	and the dump was abruptly terminated,
//      nonzero and nonone otherwise.
//
//  Remark: if the ClientEvaluate function does not return 0, the dump will abruptly terminate
//
//	Implementation Details:
//		O ( N ) - Upper bounds on runtime proportional to the number of objects currently
//		in the list because of list traversal.
//
//
//

INDEX_TYPE
ListDump
(
	PLIST_HEAD      Head,
	CLIENT_EVALUATE ClientEvaluate,
	INDEX_TYPE      Reverse
);

#ifdef __cplusplus
	}
#endif