/*
 *  File:       listpub.h
 *
 *  Function:   Holds public interface definitions for a First Class
 *              ADT list package.
 *
 *  Author:     Interface : Bruce McQuistan (brucemc@digipen.edu)

 *  Author:     Implementation : Bruce McQuistan  (brucemc@digipen.edu)
 *  Author:     Implementation : Robert Aldridge  (raldridg@digipen.edu)
 *  Author:     Implementation : Robert Sedgewick
 *
 *  Revision History:
 *              5/3/99  - Interface File Created. brucemc.
 *
 */

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
//                      objects the client wishes to put in the list.
//
//  Returns:
//      A PLIST_HEAD object which must be passed to all other functions
//      in this list interface. It will be NULL if the memory cannot
//      be allocated for the list.
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
//                  overrides the default COMPARE function specified at
//                  init time.
//
//  Returns:
//      void.
//
//  Remark: this sorts the list using an O(nlogn) algorithm.
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
//      void.
//
//  Remark: if the ClientEvaluate function does not return 0, the dump will terminate
//

INDEX_TYPE
ListDump
(
  PLIST_HEAD      Head,
  CLIENT_EVALUATE ClientEvaluate,
  INDEX_TYPE      Reverse
);
