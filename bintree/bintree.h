
// File Name: bintree.h
// Robert Aldridge
// to do: internal pointer tracker, memory locking, nested function tracking
//        add comments about nested functions being bad

// Red-Black Tree (First Class Abstract Data Type) Implementation
//
// Maintains huge lists of objects that are sorted as they are inserted.
//
// Use in replace of STL map<> when memory efficiency is critical
// or when multiple keys are necessary.
//
// Also no one has been able to beat the speed of my implementation.

// Special thanks to Charlie Burns for his initial ideas for the internal memory management,
// and for his continued support while we were working on the efficiency of our implementations.

#if !defined( BINTREE )
#define BINTREE

#ifdef __cplusplus
   extern "C" {
#endif

/*
   Sample Code:

   // #include < stdio.h >
   #include "bintree.h"

   static const int myFatalError = -1;

   struct myStruct
   {
      int testInt;
   };

   int lessThan( myStruct * keyObject, myStruct * treeObject )
   {
      // return non-zero if object 1 < object 2
      if( keyObject->testInt < treeObject->testInt )
         return 1;

      // return zero if object 1 >= object 2
      return 0;
   }

   int check( myStruct * treeObject )
   {
      // return non-zero to terminate traversal
      if( treeObject->testInt == myFatalError )
      {
         // printf( "fatal error\n" );
         return 1;
      }
         
      // return zero to continue traversal
      return 0;
   }

   int equal( myStruct * keyObject, myStruct * treeObject )
   {
      // return non-zero if object 1 == object 2
      if( keyObject->testInt == treeObject->testInt )
         return 1;

      // return zero if object 1 != object 2
      return 0;
   }

   bintree * myTree = bintree::init( 100, sizeof( myStruct ), ( bintree::compare ) lessThan );

   static const int numData = 5;
   myStruct data[ numData ] = { { -2 }, { -1 }, { 0 }, { 1 }, { 2 } };

   for( int loop = 0; loop < numData; loop++ )
      myTree->insert( &data[loop], 0 );

   myTree->dump( ( bintree::evaluate ) check, bintree::inorder );

   myStruct keyObject = { 2 };
   if( myTree->find( &keyObject, ( bintree::equivalence ) equal, 0 ) == bintree::ok )
   {
      // printf( "object found\n" );
   }

   myTree->term();
*/

#if 0
key
value
allocator
key_compare
value_compare

map
multimap
  iterator rbegin() x
  iterator rend() x
  iterator lower_bound(key) o
  terator lower_bound(?) o
  iterator upper_bound(key) o
  iterator upper_bound(?) o

unordered_map
unordered_multimap
// bucket interface
size_type bucket_count() const noexcept;
size_type max_bucket_count() const noexcept;
size_type bucket_size(size_type n) const;
size_type bucket(const key_type& k) const;
local_iterator begin(size_type n);
local_iterator end(size_type n);
// hash policy
float load_factor() const noexcept;
float max_load_factor() const noexcept;
void max_load_factor(float z);
void rehash(size_type n);
void reserve(size_type n);
  
map
unordered_map
multimap
unordered_multimap
  iterator begin() x
  iterator end() x
  bool empty() x
  int size() x
  iterator insert(iterator, key, value) o // inserted as close as possible to the position just prior to iterator
  iterator insert(iterator, ?)
  node extract(iterator) o
  node extract(key) o
  node extract(?)
  iterator insert(iterator, node) o
  erase(iterator) x
  erase(key) x
  erase(?)
  clear() x
  iterator find(key) x
  iterator find(?)
  int count(key) o
  int count(?)
  bool contains(key) x
  bool contains(?)
  <iterator, iterator> equal_range(key)
  <iterator, iterator> equal_range(?)

map
unordered_map
  value operator[key] x
  value at(key) x
  <iterator, bool> insert(key, value) x // inserts if key is not found
  <iterator, bool> insert(?)
  <iterator, bool, node> insert(node) o
  <iterator, bool> insert_or_assign(key, ?);
  iterator insert_or_assign(iterator, key, ?);

multimap
unordered_multimap
  iterator insert(key, value) o // inserts at the end of equivalent keys
  iterator insert(?)
  iterator insert(node) o
#endif

class bintree
{

public:

   // This is a function pointer used to compare the keys of two objects.
   // If you call a function and pass a compare function and an object to
   // check against, the object you pass will be on the left hand side.
   //
   // The role of the compare function cannot change for the same list unless it is
   // reset, otherwise the list will lose its sorted state.
   //
   // return zero if object 1 >= object 2
   // return non-zero if object 1 < object 2
   typedef
   int
   ( * compare )
   (
      void * keyObject,
      void * treeObject
   );

   // This is a function pointer when traversing a tree in the dump function.
   // Every object in a tree is visited in a particular order, this function pointer
   // will be called and passed every object, unless the client terminates traversal
   // early.
   //
   // return zero to continue traversal
   // return non-zero to terminate traversal
   typedef
   int
   ( * evaluate )
   (
      void * treeObject
   );

   // This function checks if two objects are equal, and should be based on their keys.
   // It is used in the find, remove, and other functions.  The left hand side is the
   // object passed to the function.
   //
   // return zero if object 1 != object 2
   // return non-zero if object 1 == object 2
   typedef
   int
   ( * equivalence )
   (
      void * keyObject,
      void * treeObject
   );

   static const int ok; // ok == 0
   static const int error; // error == -1

   static const int empty; // empty == 1

   static const int preorder;   // preorder == 0 // preorder == depth-first
   static const int inorder;    // inorder == 1
   static const int postorder;  // postorder == 2
   static const int levelorder; // levelorder == 3 // levelorder == breadth-first

   // returns a valid non-null (bintree::treeHead) instance if successful
   // returns null if failure
   //
   // init is the only bintree function that allocates memory
   static
   bintree *
   __fastcall
   init // O( n ) + O( internal OS-dependent memory allocation function for one chunk )
   (
      int     maxNumberOfObjects, // memory allocation only occurs once,
                                  // inserting more that max elements will
                                  // silently fail and return an error

      int     sizeOfEachObject, // size of each element in bytes

      compare lessThan // pointer to function for comparison of keys used to sort tree
                       // can be null as long as compare is set before it is needed
   );

   // returns 1 (bintree::empty) if empty, returns -1 (bintree::error) if failure
   //
   // a return value of 0 (bintree::ok) indicates that the bin tree was
   // not empty and there was no error
   int
   __fastcall
   isEmpty // O( 1 )
   (
      int numberOfClientObjects[ 1 ] // pointer to int to store number of elements in tree
   );

   // returns 0 (bintree::ok) if successful, -1 (bintree::error) if failure
   //
   // inserting more that max elements will
   // silently fail and return -1 (bintree::error)
   //
   // the order of the objects that contain the same key is based on how complicated
   // the compare function is, it can not always be guaranteed for equal keys.
   //
   // I have not tested to see if the sort is stable.
   int
   __fastcall
   insert // O( lg( n ) )
   (
      void *  object, // new client object to insert into tree
                      // if null then funtion will return -1 (bintree::error)

      compare lessThan // pointer to function for comparison of keys used to sort tree
                       // can be null as long as compare was set previously
   );

   // returns 0 (bintree::ok) if successful, -1 (bintree::error) if failure
   //
   // Trying to remove an element that is not in the tree is considered an error,
   // call find first if you do not want an error logged.
   //
   // The first object that is found with the right key will be removed,
   // so be mindful of objects with the same key value.
   int
   __fastcall
   remove // O( lg( n ) )
   (
      void *      keyObject, // client object that contains the key of the object
                             // the client is looking to delete

      equivalence equalTo, // client callback function that checks if the tree object
                           // contains the same key as the object passed to remove
                           // can be null as long as equivalence was set previously

      void *      objectReturn // if not null then will be filled with the contents of the object found
                               // before it is deleted, objects with the same key may have other
                               // variables which are different
   );

   // returns 0 (bintree::ok) if successful, -1 (bintree::error) if failure
   //
   // a non-successful return value indicates either
   // that there was an error or that the bin tree was empty (considered an error)
   //
   // be mindful of objects with the same key value for this function
   int
   __fastcall
   getExtrema // O( lg( n ) )
   (
      int    getGreatest, // if GetGreatest == TRUE (1) then the function will return
                          // the element that has the largest key value
                          //
                          // if GetGreatest == FALSE (0) then the function will return
                          // the element that has the smallest key value
                          //
                          // does not require any compare function

      void * objectReturn // if not null then will be filled with the contents of the object found
   );

   // returns 0 (bintree::ok) if successful, -1 (bintree::error) if failure
   //
   // a return value of 0 (bintree::ok) indicates that the node was found
   // and that the function was completely successful
   //
   // even thought the function will return an error if nothing was found,
   // this is the only error that is not logged, so it is safe to search for
   // something that is not in the list, but don't do it for the delete function
   //
   // a return value which is not zero indicates either
   // that there was an error or that the object was
   // not found in the bin tree
   //
   // be mindful of objects with the same key value for this function
   int
   __fastcall
   find // O( lg( n ) )
   (
      void *      keyObject, // client object that contains the key of the object
                             // the client is looking for

      equivalence equalTo, // client callback function that checks if the tree object
                           // contains the same key as the object passed to find
                           // can be null as long as equivalence was set previously

      void *      objectReturn // if not null then will be filled with the contents of the object found
   );

   // returns 0 (bintree::ok) if successful, -1 (bintree::error) if failure
   //
   // tree is reset so that it contains 0 client objects
   int
   __fastcall
   reset // O( n )
   (
   );

   // returns 0 (bintree::ok) if successful, -1 (bintree::error) if failure
   //
   // frees all memory used by this instance of (bintree::treeHead)
   //
   // term is the only bintree function that frees memory
   int
   __fastcall
   term // O( 1 ) + O( internal OS-dependent memory freeing function for one chunk )
   (
   );

   // returns 0 (bintree::ok) if successful, -1 (bintree::error) if failure
   //
   // the success of this function is not determined by whether or not
   // the client terminates the traversal early
   //
   // be mindful of objects with the same key value for this function
   //
   // all nodes will be dumped by default, but a client may terminate early at the
   // wrong time without visiting all the nodes that he wanted to if they are
   // not careful with objects with the same key value
   int
   __fastcall
   dump // O( n )
   (
      evaluate clientEvaluate, // the client callback function for each client object in tree
                               // can be null as long as evaluate was set previously

      int      traversalOrder // indicates what order to traverse client objects in tree
                              //
                              // valid values are the 4 traversal constants:
                              //   preorder (depth-first)
                              //   inorder
                              //   postorder
                              //   levelorder (breadth-first)
   );

private:

   bintree
   (
   );

   bintree
   (
      bintree &
   );

   virtual
   ~bintree
   (
   ) = 0;

   bintree &
   operator=
   (
      bintree &
   );
};

#ifdef __cplusplus
   }
#endif

#endif