
/*
 *  File:       list.h
 *
 *  Function:   Holds public interface definitions for a First Class
 *              ADT list package.
 *
 *  Author:     Interface : Bruce McQuistan (brucemc@digipen.edu)

 *  Author:     Robert Aldridge (raldridg@digipen.edu)
 *  Author:     Bruce McQuistan (brucemc@digipen.edu)
 *  Author:     Robert Sedgewick (author of Algorithms in C)
 *                 ~Sedgewick needs to come out with pts. 5-8 for his 3rd edition!~
 *              Special thanks to Robert Tarjan (author of Data Structures and Network Algorithms)
 *                 ~According to Bruce, Tarjan proved generic sorting can be no faster
 *                 than N lg N, that's cool!~
 *
 *              Half of the comments before each function were by Bruce,
 *              since he wrote the interface.  I updated his comments when
 *              I added extra features to the engine.  The implementation details
 *              are all my comments since I implemented the functions.  The double
 *              sorting method is from Bruce and Sedgewick.  Many thanks to them
 *              for their hard work.  Bruce, you should write a book!
 *
 *  Revision History:
 *              I implemented the functions in October 2000 for
 *              my advanced Algorithm Analysis class (cs330). Robert Aldridge
 *
 *              The last known bug fix was in February 2000 when
 *              I was using my list routines in my 3D engine for
 *              my 3D class (cs250). Robert Aldridge
 *
 *              The last revision was in May 2001 while organizing
 *              the list library into a DLL for an online resume. Robert Aldridge
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

//
//  Function pointer typedefs to be used to define contract between client
//  and this ADT. First is a compare function, second is an evaluate
//  function.
//

typedef INDEX_TYPE(*CLIENT_COMPARE)(CLIENT_POTYPE ClientObject1, CLIENT_POTYPE ClientObject2);

typedef INDEX_TYPE(*CLIENT_EVALUATE)(CLIENT_POTYPE* ClientObject1);

typedef INDEX_TYPE(*CLIENT_EQUIVALENCE)(CLIENT_POTYPE ClientObject1, CLIENT_POTYPE ClientObject2);

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
//      A LIST_HEAD* object which must be passed to all other functions
//      in this list interface. It will be NULL if the memory cannot
//      be allocated for the list.
//
//  Implementation Details:
//    O ( N ) - Upper bounds on runtime proportional to the guessed maximum number
//    of objects because of memory allocation and zeroing the memory out.
//
//
//

LIST_HEAD*
ListInit
(
  CLIENT_COMPARE ClientCompare,
  INDEX_TYPE     MaxNumberOfObjects
);

//
//  The Check if empty routine
//
//  Arguments:
//      Head   - The LIST_HEAD* referring to a particular instance of
//               the list ADT.
//
//      NumberOfClientObjects - An optional INDEX_TYPE pointer, may be NULL.
//                              It will be set to the number of client objects
//                              in the list if it is not NULL
//
//  Returns:
//      1 if list is empty, 0 otherwise.
//
//  Implementation Details:
//    O ( C ) - Upper bounds on runtime constant because the number of
//    calculations are the same no matter the size of the list.
//
//
//

INDEX_TYPE
ListIsEmpty
(
  LIST_HEAD* Head,
  INDEX_TYPE *NumberOfClientObjects
);

//
//  The POTYPE insertion routine.
//
//  Arguments:
//      Head   - The LIST_HEAD* referring to a particular instance of
//               the list ADT.
//
//      ClientObject - The object to be inserted into the list.
//
//      ClientCompare - An optional permanent COMPARE function pointer, may be NULL.
//
//  Returns:
//      0 if successful, nonzero otherwise.
//
//  Implementation Details:
//    O ( C ) - Upper bounds on runtime constant because the number of
//    calculations are the same no matter the size of the list.
//
//      O ( N ) - If extra memory allocation is required, upper bounds on runtime
//    proportional to the number of objects currently in the list because of memory
//    allocation, and zeroing the memory out, and copying it over. Only happens when
//      the number of items in the list is equal to the guessed maximum number passed
//      into ListInit, in which case the guessed maximum number will be doubled.
//    After that the runtime will only be O( N ) every time the array doubles its size.
//    Since this only happens every time the array doubles, O( lg N ) is the upper
//    bounds on the amount of times this will happen.
//
//
//

INDEX_TYPE
ListInsert
(
  LIST_HEAD*     Head,
  CLIENT_POTYPE  ClientObject,
  CLIENT_COMPARE ClientCompare
);

//
//  The Remove routine.
//
//  Arguments:
//      Head   -            The LIST_HEAD* referring to a particular instance
//                          of the list ADT.
//
//      ClientEquality -    An optional temporary EQUIVALENCE function pointer which only
//                          returns 1 if the objects are considered equivalent.
//                          It returns 0 otherwise. If this is NULL, the first
//                          element in the list is removed.
//
//      ClientObject -      A required POTYPE* specifying both the object to be
//                          found and is used as an out parameter.
//
//  Returns:
//      0 if successful, nonzero otherwise.
//
//  Implementation Details:
//    O ( N ) - Upper bounds on runtime proportional to the number of objects currently
//    in the list because of list traversal.
//
//  Note: ListGetNext is reset automatically when ListRemove returns successfully.
//
//
//

INDEX_TYPE
ListRemove
(
  LIST_HEAD*         Head,
  CLIENT_EQUIVALENCE ClientEquality,
  CLIENT_POTYPE*     ClientObject
);

//
//  The Find routine.
//
//  Arguments:
//      Head   -            The LIST_HEAD* referring to a particular instance
//                          of the list ADT.
//
//      ClientEquality -    An optional temporary EQUIVALENCE function pointer which only
//                          returns 1 if the objects are considered equivalent.
//                          It returns 0 otherwise. If this is NULL, the first
//                          element in the list is returned.
//
//      ClientObject -      A required POTYPE* specifying both the object to be
//                          found and is used as an out parameter.
//
//  Returns:
//      0 if successful, nonzero otherwise.
//
//  Implementation Details:
//    O ( N ) - Upper bounds on runtime proportional to the number of objects currently
//    in the list because of list traversal.
//
//
//

INDEX_TYPE
ListFind
(
  LIST_HEAD*         Head,
  CLIENT_EQUIVALENCE ClientEquality,
  CLIENT_POTYPE*     ClientObject
);

//
//  The GetNext routine.
//
//  Arguments:
//      Head         -      The LIST_HEAD* referring to a particular instance
//                          of the list ADT.
//
//      ClientObject -      A required POTYPE* where the next object is to be placed
//
//      Reset        -      A BOOL when TRUE, will reset the search to begin
//                          at the start of the list.
//
//  Returns:
//      0 if successful, nonzero otherwise.
//
//  Implementation Details:
//    O ( C ) - Upper bounds on runtime constant because the number of
//    calculations are the same no matter the size of the list.
//
//  Note: ListGetNext is reset automatically when ListRemove returns successfully.
//
//
//

INDEX_TYPE
ListGetNext
(
  LIST_HEAD*     Head,
  CLIENT_POTYPE* ClientObject,
  INDEX_TYPE     Reset
);

//
//  The terminate routine.
//
//  Arguments:
//      Head   - The LIST_HEAD* referring to a particular instance of
//               the list ADT.
//
//  Returns:
//      void
//
//  Implementation Details:
//    O ( C ) - Upper bounds on runtime constant because the number of
//    calculations are the same no matter the size of the list.
//
//
//

void
ListTerminate
(
  LIST_HEAD* Head
);

//
//  A sort routine.
//
//  Arguments:
//      Head    -   The LIST_HEAD* referring to a particular instance of
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
//    O( N lg N ) - This sorts the list using an algorithm whose upper bounds
//    on runtime is proportional to the number of objects currently
//    in the list times the log base 2 of the number of objects currently
//    in the list.
//

void
ListSort
(
  LIST_HEAD*     Head,
  CLIENT_COMPARE ClientCompare
);

//
//  A get extrema routine.
//
//  Arguments:
//      Head         -  The LIST_HEAD* referring to a particular instance of
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
//  Implementation Details:
//    O ( N ) - Upper bounds on runtime proportional to the number of objects currently
//    in the list because of list traversal.
//
//
//

CLIENT_POTYPE
ListGetExtrema
(
  LIST_HEAD*     Head,
  CLIENT_COMPARE ClientCompare,
  INDEX_TYPE     GetGreatest
);

//
//  A list dump routine.
//
//  Arguments:
//      Head   - The LIST_HEAD* referring to a particular instance of
//               the list ADT.
//
//      ClientEvaluate - An optional temporary EVALUATE function provided by the client.
//
//      Reverse - If TRUE, dump list in reverse order.
//
//  Returns:
//      0 if successful and there was a full dump,
//      1 if successful and the dump was abruptly terminated,
//      nonzero and nonone otherwise.
//
//  Remark: if the ClientEvaluate function does not return 0, the dump will abruptly terminate
//
//  Implementation Details:
//    O ( N ) - Upper bounds on runtime proportional to the number of objects currently
//    in the list because of list traversal.
//
//
//

INDEX_TYPE
ListDump
(
  LIST_HEAD*      Head,
  CLIENT_EVALUATE ClientEvaluate,
  INDEX_TYPE      Reverse
);
