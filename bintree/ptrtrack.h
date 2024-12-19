
// File Name: ptrtrack.h
// Robert Aldridge

// internal pointer tracker class, uses red-black binary tree
//
// noes not support locked memory
//
// the pointer tracker cannot track it's own pointers either, so be careful,
// only use this class for the lowest level routines and make sure you know
// what you are passing it
//
// the class code must be recompiled when the size of a pointer changes

#if !defined( PTRTRACK )
#define PTRTRACK

#ifdef __cplusplus
   extern "C" {
#endif

/*
   Sample Code:

   // #include < stdio.h >
   #include "ptrtrack.h"

   struct myStruct
   {
      int testInt;
   };

   ptrtrack * myTree = ptrtrack::init( 100 );

   static const int numPtrs = 5;
   myStruct data[ 5 ] = { { -2 }, { -1 }, { 0 }, { 1 }, { 2 } };
   myStruct * ptrs[ 5 ] = { &data[0], &data[1], &data[2], &data[3], &data[4] };

   for( int loop = 0; loop < numPtrs; loop++ )
      myTree->insert( ptrs[loop] );

   myStruct * keyPointer = ptrs[2];
   if( myTree->find( keyPointer ) == ptrtrack::ok )
   {
      // printf( "object found\n" );
   }

   myTree->term();
*/

class ptrtrack
{

public:

   static const int ok;
   static const int error;

   static const int empty;

   // returns a valid non-null ptrtrack class pointer if successful
   // returns null if an error occurs
   //
   // init is the only ptrtrack function that allocates memory
   static
   ptrtrack *
   __fastcall
   init // O( n ) + O( internal OS-dependent memory allocation function for one chunk )
   (
      int maxNumberOfPointers // memory allocation only occurs once,
                              // inserting more that max elements will
                              // fail and return (ptrtrack::error)
   );

   // returns the number of pointers in the tree ( num >= 0 )
   // returns (ptrtrack::error) if an error occurs
   int
   __fastcall
   isEmpty // O( 1 )
   (
   );

   // returns (ptrtrack::ok) if successful
   // returns (ptrtrack::error) if an error occurs
   //
   // inserting more that max elements will
   // fail and return (ptrtrack::error)
   //
   // inserting the same pointer more than once will
   // fail and return (ptrtrack::error)
   int
   __fastcall
   insert // O( lg( n ) )
   (
      void * pointer // new client pointer to insert into tree
                     // if null then funtion will return (bintree::error)
   );

   // returns (ptrtrack::ok) if successful removal occurs
   // returns (ptrtrack::empty) if pointer was not in tree
   // returns (ptrtrack::error) if an error occurs
   int
   __fastcall
   remove // O( lg( n ) )
   (
      void * keyPointer // client pointer the client wants to delete
   );

   // returns (ptrtrack::ok) if pointer was successfully found
   // returns (ptrtrack::empty) if pointer was not in tree
   // returns (ptrtrack::error) if an error occurs
   int
   __fastcall
   find // O( lg( n ) )
   (
      void * keyPointer // client pointer the client is looking for
   );

   // returns (ptrtrack::ok) if successful
   // returns (ptrtrack::error) if an error occurs
   //
   // tree is reset so that it contains 0 client pointers
   int
   __fastcall
   reset // O( n )
   (
   );

   // returns (ptrtrack::ok) if successful
   // returns (ptrtrack::error) if an error occurs
   //
   // frees all memory used by this instance of ptrtrack
   //
   // term is the only ptrtrack function that frees memory
   int
   __fastcall
   term // O( 1 ) + O( internal OS-dependent memory freeing function for one chunk )
   (
   );

private:

   ptrtrack
   (
   );

   ptrtrack
   (
      ptrtrack &
   );

   virtual
   ~ptrtrack
   (
   ) = 0;

   ptrtrack &
   operator=
   (
      ptrtrack &
   );
};

#ifdef __cplusplus
   }
#endif

#endif