
// File Name: memleak.cpp
// Robert Aldridge

#include "../../general.h"

#if defined( _MSC_VER )
   #pragma warning ( push, 4 )
   #pragma warning ( disable: 4514 )
#endif

#include < malloc.h >
#include < memory.h >
#include < string.h >

#include "memleakpriv.h"
#include "memleak.h"
#undef new
#undef malloc
#undef calloc
#undef realloc
#undef free

#ifdef __cplusplus
   extern "C" {
#endif

#if defined( _DEBUG ) && !defined( NDEBUG ) && !defined( _MSC_VER )
   #include "../redblack/bintree.h"
   #include "log.h"

   struct binData
   {
      void * userData;
      unsigned int size;
      int blockType;
      char filename[ 261 ];
      int linenumber;
   };

   static bintree * gmemList = 0;

   static
   int
   lessThan
   (
      binData * object1,
      binData * object2
   )
   {
      if( object1->userData < object2->userData )
      {
         return 1;
      }

      return 0;
   }

   static
   int
   dump
   (
      binData * object1
   )
   {
      _log( "warning, memory not freed by client\nPointer Value: %p\nSize Of Allocation: %u\n"
            "Memory Block Type: %d\nFile Name Allocation Originated From: %s\nFile Line Number: %d\n",
            object1->userData,
            object1->size,
            object1->blockType,
            object1->filename,
            object1->linenumber
          );

      free( object1->userData );

      return 0;
   }

   static
   int
   equal
   (
      binData * object1,
      binData * object2
   )
   {
      if( object1->userData == object2->userData )
      {
         return 1;
      }

      return 0;
   }

   bool dMemoryLeak::enter = false;

   void
   dMemoryLeak::dMemoryLeakInit
   (
   )
   {
      loginit();

      if( !gmemList )
      {
         gmemList = bintree::init( 1000, sizeof( binData ), ( bintree::compare ) lessThan );

         if( !gmemList )
         {
            _log( "error, BinTreeInit failure" );
         }
      }

      dMemoryLeak::enter = true;
   }

   void
   dMemoryLeak::dMemoryLeakTerm
   (
   )
   {
      loginit();

      if( !gmemList )
      {
         _log( "error" );
      }
      else
      {
         if( gmemList->isEmpty( 0 ) != 1 )
         {
            _log( "warning, memory not freed by client\n" );

            if( gmemList->dump( ( bintree::evaluate ) dump, bintree::inorder ) != 0 )
            {
               _log( "warning, BinTreeDump error" );
            }
         }

         if( gmemList->term() != 0 )
         {
            _log( "warning, BinTreeTerm error" );
         }

         gmemList = 0;
      }

      logterm();
      dMemoryLeak::enter = false;
   }

   extern
   void *
   __cdecl
   _malloc_dbg
   (
      unsigned int size,
      int blockType,
      const char * filename,
      int linenumber
   )
   {
      char * userData = 0;

      if( !size )
      {
         loginit();
         _log( "error, invalid parameters" );
         return 0;
      }

      if( !gmemList )
      {
         if( dMemoryLeak::enter == true )
         {
            _log( "warning" );

            userData = ( char * ) malloc( size + sizeof( int ) * 2 );

            if( !userData )
            {
               _log( "error, malloc return 0" );
               return 0;
            }

            memset( userData, 0xff, sizeof( int ) );
            memset( userData + size + sizeof( int ), 0xff, sizeof( int ) );
            return userData + sizeof( int );
         }

         loginit();
         
         userData = ( char * ) malloc( size + sizeof( int ) * 3 + sizeof( unsigned int ) );

         if( !userData )
         {
            _log( "error, malloc return 0" );
            return 0;
         }

         memset( userData, 0xff, sizeof( int ) );
         memcpy( userData + sizeof( int ), &size, sizeof( unsigned int ) );
         memset( userData + sizeof( int ) + sizeof( unsigned int ), 0xff, sizeof( int ) );
         memset( userData + size + sizeof( int ) * 2 + sizeof( unsigned int ), 0xff, sizeof( int ) );
         return userData + sizeof( int ) * 2 + sizeof( unsigned int );
      }

      userData = ( char * ) malloc( size + sizeof( int ) * 2 );

      if( !userData )
      {
         _log( "error, malloc return 0" );
         return 0;
      }

      binData object = { 0 };
      object.userData = userData;
      object.size = size;
      object.blockType = blockType;
      strcpy( object.filename, filename );
      object.linenumber = linenumber;

      if( gmemList->insert( &object, 0 ) != 0 )
      {
         _log( "error, BinTreeInsert failure" );
      }
      
      memset( userData, 0xff, sizeof( int ) );
      memset( userData + size + sizeof( int ), 0xff, sizeof( int ) );
      return userData + sizeof( int );
   }

   extern
   void *
   __cdecl
   _calloc_dbg
   (
      unsigned int num,
      unsigned int size,
      int blockType,
      const char * filename,
      int linenumber
   )
   {
      void * userData = _malloc_dbg( num * size, blockType, filename, linenumber );
      memset( userData, 0, num * size );
      return userData;
   }

   extern
   void *
   __cdecl
   _realloc_dbg
   (
      void * userData,
      unsigned int newSize,
      int blockType,
      const char * filename,
      int linenumber
   )
   {
      if( userData )
      {
         _free_dbg( userData, blockType );
      }

      userData = _malloc_dbg( newSize, blockType, filename, linenumber );
      return userData;
   }

   extern
   void
   __cdecl
   _free_dbg
   (
      void * mem,
      int blockType
   )
   {
      char * userData = ( char * ) mem;

      if( !gmemList )
      {
         if( dMemoryLeak::enter == true )
         {
            _log( "warning, %p %d", userData, blockType );
            userData -= sizeof( int );
            mem = userData;

            loginit();

            if( !userData )
            {
               _log( "error" );
               return;
            }

            int pad;
            memset( &pad, 0xff, sizeof( int ) );

            int mCheckPad1 = ( ( int * ) userData )[0];

            if( mCheckPad1 != pad )
            {
               _log( "error, mem padding invalidated" );
            }

            free( mem );
            return;
         }

         userData -= sizeof( int ) * 2 + sizeof( unsigned int );
         mem = userData;

         loginit();

         if( !userData )
         {
            _log( "error" );
            return;
         }

         int pad;
         memset( &pad, 0xff, sizeof( int ) );

         int mCheckPad1 = ( ( int * ) userData )[0];
         userData += sizeof( int );

         unsigned int mCheckSize2 = ( ( unsigned int * ) userData )[0];
         userData += sizeof( unsigned int );

         int mCheckPad3 = ( ( int * ) userData )[0];
         userData += mCheckSize2 + sizeof( int );

         int mCheckPad4 = ( ( int * ) userData )[0];

         if( mCheckPad1 != pad || mCheckPad3 != pad || mCheckPad4 != pad )
         {
            _log( "error, mem padding invalidated" );
         }

         free( mem );
         return;
      }

      userData -= sizeof( int );
      mem = userData;

      binData object = { 0 };
      object.userData = userData;

      if( gmemList->find( &object, ( bintree::equivalence ) equal, 0 ) != 0 )
      {
         _log( "error, block not in list \n%p %d", userData, blockType );
         return;
      }

      if( gmemList->remove( &object, ( bintree::equivalence ) equal, &object ) != 0 )
      {
         _log( "error, block not removed from list \n%p %d", userData, blockType );
      }

      int pad;
      memset( &pad, 0xff, sizeof( int ) );

      int mCheckPad1 = ( ( int * ) userData )[0];
      userData += object.size + sizeof( int );

      int mCheckPad2 = ( ( int * ) userData )[0];

      if( mCheckPad1 != pad || mCheckPad2 != pad )
      {
         _log( "error, mem padding invalidated" );
      }

      free( mem );
   }
#endif

#ifdef __cplusplus
   }
#endif