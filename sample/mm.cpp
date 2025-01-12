
// File Name: mm.cpp
// Robert Aldridge

#include "../../general.h"

#if defined( _MSC_VER )
   #pragma warning ( push, 4 )
   #pragma warning ( disable: 4100 )
   #pragma warning ( disable: 4310 )
#endif

#ifdef __cplusplus
   extern "C" {
#endif

#include < memory.h >
#include < string.h >

#include "../debugutils/log.h"
#include "../debugutils/memleak.h"
#include "mm.h"
#include "mmpriv.h"
#undef allocateMemoryChunk
#undef setMemoryChunkWriteOnly

#if defined( _DEBUG ) && !defined( NDEBUG )

   #if defined( _MSC_VER )

      #pragma warning( disable: 4201 )

      #if defined( _DLL ) && defined( _MSC_VER )
         #define __import __declspec( dllimport )
      #else
         #define __import extern
      #endif

      typedef struct _SYSTEM_INFO
      {
         union
         {
            unsigned long dwOemId;

            struct
            {
               unsigned short wProcessorArchitecture;
               unsigned short wReserved;
            };
         };

         unsigned long dwPageSize;
         void * lpMinimumApplicationAddress;
         void * lpMaximumApplicationAddress;
         unsigned long dwActiveProcessorMask;
         unsigned long dwNumberOfProcessors;
         unsigned long dwProcessorType;
         unsigned long dwAllocationGranularity;
         unsigned short wProcessorLevel;
         unsigned short wProcessorRevision;

      } SYSTEM_INFO, * LPSYSTEM_INFO;

      __import
      void
      __stdcall
      GetSystemInfo
      (
         LPSYSTEM_INFO lpSystemInfo
      );

      #define MEM_RESERVE 0x2000
      #define MEM_COMMIT 0x1000
      #define MEM_DECOMMIT 0x4000
      #define MEM_RELEASE 0x8000

      #define PAGE_NOACCESS 0x01
      #define PAGE_READONLY 0x02
      #define PAGE_READWRITE 0x04

      __import
      void *
      __stdcall
      VirtualAlloc
      (
         void * lpAddress,
         unsigned long dwSize,
         unsigned long flAllocationType,
         unsigned long flProtect
      );

      __import
      int
      __stdcall
      VirtualFree
      (
         void * lpAddress,
         unsigned long dwSize,
         unsigned long dwFreeType
      );

      __import
      int
      __stdcall
      VirtualProtect
      (
         void * lpAddress,
         unsigned long dwSize,
         unsigned long flNewProtect,
         unsigned long * lpflOldProtect
      );

   #endif

   #include "../redblack/bintree.h"

   struct noMansLand
   {
      int pad1;
      void * userData;
      unsigned int clientSize;
      unsigned int actualSize;
      int blockType;
      char filename[ 261 ];
      int linenumber;
      bool canRead;
      bool canWrite;
      int * pad3;
      int pad2;
   };

   static bintree * gmemList = 0;
   static bool binTreeRemoveFlag = true;

   static
   int
   lessThan
   (
      noMansLand ** object1,
      noMansLand ** object2
   )
   {
      if( mm::unlockTheShiza( object1[0] + 1 ) != 0 )
      {
         _log( "error" );
         return 0;
      }

      if( mm::unlockTheShiza( object2[0] + 1 ) != 0 )
      {
         _log( "error" );

         if( mm::lockTheShiza( object1[0] + 1 ) != 0 )
         {
            _log( "error" );
         }

         return 0;
      }

      if( object1[0]->userData < object2[0]->userData )
      {
         return 1;
      }

      if( mm::lockTheShiza( object1[0] + 1 ) != 0 )
      {
         _log( "error" );
      }

      if( mm::lockTheShiza( object2[0] + 1 ) != 0 )
      {
         _log( "error" );
      }

      return 0;
   }

   static
   int
   dump
   (
      noMansLand ** object1
   )
   {
      if( mm::unlockTheShiza( object1[0] + 1 ) != 0 )
      {
         _log( "error" );
         return 0;
      }

      _log( "warning, memory not freed by client\nPointer Value: %p\nSize Of Allocation: %u\n"
            "Memory Block Type: %d\nFile Name Allocation Originated From: %s\nFile Line Number: %d\n",
            object1[0]->userData,
            object1[0]->clientSize,
            object1[0]->blockType,
            object1[0]->filename,
            object1[0]->linenumber
          );

      if( mm::deallocateMemoryChunk( object1[0] + 1 ) != 0 )
      {
         _log( "error" );
      }

      return 0;
   }

   static
   int
   equal
   (
      noMansLand ** object1,
      noMansLand ** object2
   )
   {
      if( mm::unlockTheShiza( object1[0] + 1 ) != 0 )
      {
         _log( "error" );
         return 0;
      }

      if( mm::unlockTheShiza( object2[0] + 1 ) != 0 )
      {
         _log( "error" );

         if( mm::lockTheShiza( object1[0] + 1 ) != 0 )
         {
            _log( "error" );
         }

         return 0;
      }

      if( object1[0]->userData == object2[0]->userData )
      {
         return 1;
      }

      if( mm::lockTheShiza( object1[0] + 1 ) != 0 )
      {
         _log( "error" );
      }

      if( mm::lockTheShiza( object2[0] + 1 ) != 0 )
      {
         _log( "error" );
      }

      return 0;
   }

   bool dMemoryManagement::enter = false;

   void
   dMemoryManagement::dMemoryManagementInit
   (
   )
   {
      loginit();

      if( !gmemList )
      {
         gmemList = bintree::init( 1000, sizeof( noMansLand * ), ( bintree::compare ) lessThan );

         if( !gmemList )
         {
            _log( "error, BinTreeInit failure" );
            return;
         }
      }

      dMemoryManagement::enter = true;
   }

   void
   dMemoryManagement::dMemoryManagementTerm
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

            binTreeRemoveFlag = false;

            if( gmemList->dump( ( bintree::evaluate ) dump, bintree::inorder ) != 0 )
            {
               _log( "warning, BinTreeDump error" );
            }

            binTreeRemoveFlag = true;
         }

         if( gmemList->term() != 0 )
         {
            _log( "warning, BinTreeTerm error" );
         }

         gmemList = 0;
      }

      logterm();
      dMemoryManagement::enter = false;
   }
#else
   bool dMemoryManagement::enter = false;

   void
   dMemoryManagement::dMemoryManagementInit
   (
   )
   {
      loginit();
      dMemoryManagement::enter = true;
   }

   void
   dMemoryManagement::dMemoryManagementTerm
   (
   )
   {
      logterm();
      dMemoryManagement::enter = false;
   }
#endif

static int gblockType;
static char gfilename[ 261 ] = { 0 };
static int glinenumber = 0;

// for debugging
void *
mm::setCodeOrigin
(
   int blockType,
   const char * filename,
   int linenumber,
   unsigned int minSize

)
{
   gblockType = blockType;
   memcpy( gfilename, filename, strlen( filename ) + 1 );
   glinenumber = linenumber;

   return mm::allocateMemoryChunk( minSize );
}

void *
mm::allocateMemoryChunk
(
   unsigned int minSize
)
{
   if( !minSize )
   {
      loginit();
      _log( "error, invalid parameters" );
      return 0;
   }

   if( dMemoryManagement::enter == false )
   {
      loginit();
      _log( "error, special allocation cannot occur before program entry" );
      return 0;
   }

   #if defined( _DEBUG ) && !defined( NDEBUG )

      #if defined( _MSC_VER )
         // debug MSC
         // -> call virtual alloc for allocation size plus padding and structure
         noMansLand * header = 0;
         SYSTEM_INFO SystemInfo = { 0 };
         GetSystemInfo( &SystemInfo );

         int size = sizeof( noMansLand ) + minSize + sizeof( int );
         size += size % SystemInfo.dwPageSize;

         header = ( noMansLand * ) VirtualAlloc( 0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
         memset( header, 0, size );

         if( !header )
         {
            _log( "error, VirtualAlloc returns 0" );
            return 0;
         }
      #else
         // debug OS-Independent
         // -> call malloc for double the allocation size plus padding and structure
         noMansLand * header = 0;
         int size = sizeof( noMansLand ) + minSize * 2 + sizeof( int );

         header = ( noMansLand * ) malloc( size );
         memset( header, 0, size );

         if( !header )
         {
            _log( "error, malloc returns 0" );
            return 0;
         }
      #endif

      memset( &header->pad1, 0xff, sizeof( int ) );
      header->userData = ( char * ) header + sizeof( noMansLand );
      header->clientSize = minSize;
      header->actualSize = size;
      header->blockType = gblockType;
      strcpy( header->filename, gfilename );
      header->linenumber = glinenumber;
      header->canRead = true;
      header->canWrite = true;
      header->pad3 = ( int * ) ( ( char * ) ( header->userData ) + minSize );
      memset( header->pad3, 0xff, sizeof( int ) );
      memset( &header->pad2, 0xff, sizeof( int ) );

      if( !gmemList )
      {
         _log( "error, gmemList is NULL" );
         return header->userData;
      }

      if( gmemList->insert( &header, 0 ) != 0 )
      {
         _log( "error, BinTreeInsert failure" );
      }

      return header->userData;

   #else
      // release mode
      // -> call malloc
      return malloc( minSize );
   #endif
}

int
mm::deallocateMemoryChunk
(
   void * mem
)
{
   if( !mem )
   {
      loginit();
      _log( "error, invalid parameters" );
      return -1;
   }

   if( dMemoryManagement::enter == false )
   {
      loginit();
      _log( "error, special deallocation cannot occur before program entry" );
      return -1;
   }

   #if defined( _DEBUG ) && !defined( NDEBUG )

      noMansLand * header = ( noMansLand * ) ( mem ) - 1;

      if( gmemList->find( &header, ( bintree::equivalence ) equal, 0 ) != 0 )
      {
         _log( "error, block not in list" );
         return -1;
      }

      if( mm::unlockTheShiza( mem ) != 0 )
      {
         _log( "error" );
         return -1;
      }

      mm::integrityMemoryCheck( mem );

      if( binTreeRemoveFlag == true && gmemList->remove( &header, ( bintree::equivalence ) equal, 0 ) != 0 )
      {
         _log( "error, block not removed from list \n%p %d", header->userData, header->blockType );
      }

      #if defined( _MSC_VER )
         // debug MSC
         // -> call virtual free
         int result = VirtualFree( header, header->actualSize, MEM_DECOMMIT );

         if( !result )
         {
            _log( "error, VirtualFree Decommit error" );
            return -1;
         }

         result = VirtualFree( header, 0, MEM_RELEASE );

         if( !result )
         {
            _log( "error, VirtualFree Release error" );
            return -1;
         }

         return 0;
      #else
         // debug OS-Independent
         // -> call free
         free( header );
         return 0;
      #endif

   #else
      // release mode
      // -> call free
      free( mem );
      return 0;
   #endif
}

void
mm::integrityMemoryCheck
(
   void * mem
)
{
   #if defined( _DEBUG ) && !defined( NDEBUG )

      noMansLand * header = ( noMansLand * ) ( mem ) - 1;

      // check three ints
      int pad;
      memset( &pad, 0xff, sizeof( int ) );

      if( header->pad1 != pad || header->pad2 != pad || header->pad3[0] != pad )
      {
         _log( "error, mem padding invalidated\nPointer Value: %p\nSize Of Allocation: %u\n"
               "Memory Block Type: %d\nFile Name Allocation Originated From: %s\nFile Line Number: %d\n",
               header->userData,
               header->clientSize,
               header->blockType,
               header->filename,
               header->linenumber
             );

         header->pad1 = pad;
         header->pad2 = pad;
         header->pad3[0] = pad;
      }

      #if defined( _MSC_VER )
         // debug MSC
         // check 3 int pads
      #else
         // debug OS-Independent
         // previous mode:
         //
         // no write
         // check 3 int pads
         // check if client is different from buffer, log if so
         if( header->canWrite == false )
         {
            char * userData = ( char * ) header->userData;

            char * bufferData = ( char * ) ( userData );
            bufferData += header->clientSize + sizeof( int );

            if( header->canRead == true )
            {
               if( memcmp( userData, bufferData, header->clientSize ) != 0 )
               {
                  _log( "error, mem written to when it was read only\nPointer Value: %p\nSize Of Allocation: %u\n"
                        "Memory Block Type: %d\nFile Name Allocation Originated From: %s\nFile Line Number: %d\n",
                        userData,
                        header->clientSize,
                        header->blockType,
                        header->filename,
                        header->linenumber
                      );

                  memcpy( userData, bufferData, header->clientSize );
               }
            }
            else
            {
               for( int loop = 0; loop < ( int ) ( header->clientSize ); loop++ )
               {
                  if( userData[loop] != ( char ) 0xff )
                  {
                     _log( "error, mem written to when it was no read no write\nPointer Value: %p\nSize Of Allocation: %u\n"
                           "Memory Block Type: %d\nFile Name Allocation Originated From: %s\nFile Line Number: %d\n",
                           userData,
                           header->clientSize,
                           header->blockType,
                           header->filename,
                           header->linenumber
                         );

                     memset( userData, 0xff, header->clientSize );
                     break;
                  }
               }
            }
         }
         //
         // no read
         // check 3 int pads
         // copy garbage into client again
         if( header->canWrite == true )
         {
            if( header->canRead == false )
            {
               for( int loop = 0; loop < ( int ) ( header->clientSize ); loop++ )
               {
                  if( ( ( char * ) ( header->userData ) )[loop] != ( char ) 0xff )
                  {
                     memset( header->userData, 0xff, header->clientSize );

                     _log( "error, mem written to directly when it was write only\nPointer Value: %p\nSize Of Allocation: %u\n"
                           "Memory Block Type: %d\nFile Name Allocation Originated From: %s\nFile Line Number: %d\n"
                           "write calls for write only OS-Independent mode must be re-routed to the\n"
                           "memoryChunkWriteOnlyWrite function, now overwriting data\n",
                           header->userData,
                           header->clientSize,
                           header->blockType,
                           header->filename,
                           header->linenumber
                         );

                     memset( header->userData, 0xff, header->clientSize );
                     break;
                  }
               }
            }
            else
            {
               // do nothing
            }
         }
         //
         //
         // no read / write
         // check 3 int pads
         // check if client is different from buffer, log if so
         // copy garbage into client again
      #endif

   #else
      // release mode
      // do nothing
   #endif
}

int
mm::unlockTheShiza
(
   void * mem
)
{
   #if defined( _DEBUG ) && !defined( NDEBUG )

      #if defined( _MSC_VER )
         // debug MSC
         // call VirtualProtect
         noMansLand * header = ( noMansLand * ) ( mem ) - 1;

         unsigned long oldValue = 0;
         int value = VirtualProtect( header, sizeof( noMansLand ), PAGE_READWRITE, &oldValue );

         if( !value )
         {
            _log( "error, unlockTheShiza VirtualProtect PAGE_READWRITE error" );
            return -1;
         }

         oldValue = 0;
         value = VirtualProtect( header, header->actualSize, PAGE_READWRITE, &oldValue );

         if( !value )
         {
            _log( "error, unlockTheShiza VirtualProtect PAGE_READWRITE error" );
            return -1;
         }
      #else
         // debug OS-Independent
         // do nothing
      #endif

   #else
      // release mode
      // do nothing
   #endif

   return 0;
}

void
mm::changeTheShiza
(
   void * mem,
   bool newCanRead,
   bool newCanWrite
)
{
   #if defined( _DEBUG ) && !defined( NDEBUG )

      noMansLand * header = ( noMansLand * ) ( mem ) - 1;

      #if defined( _MSC_VER )
         // debug MSC
         // do nothing
         header->canRead = newCanRead;
         header->canWrite = newCanWrite;
      #else
         // debug OS-Independent
         char * bufferData = ( char * ) ( header->userData );
         bufferData += header->clientSize + sizeof( int );

         if( header->canRead == false )
         {
            memcpy( header->userData, bufferData, header->clientSize );
         }
         else
         {
            // do nothing
         }

         header->canRead = newCanRead;
         header->canWrite = newCanWrite;

         if( header->canRead == false || header->canWrite == false )
         {
            memcpy( bufferData, header->userData, header->clientSize );
            memset( header->userData, 0xff, header->clientSize );
         }
         else
         {
            // do nothing
         }
      #endif

   #else
      // release mode
      // do nothing
   #endif
}

int
mm::lockTheShiza
(
   void * mem
)
{
   #if defined( _DEBUG ) && !defined( NDEBUG )

      #if defined( _MSC_VER )
         // debug MSC
         // call VirtualProtect
         noMansLand * header = ( noMansLand * ) ( mem ) - 1;

         unsigned long newValue = 0;

         if( header->canRead == true )
         {
            if( header->canWrite == true )
            {
               newValue = PAGE_READWRITE;
            }
            else if( header->canWrite == false )
            {
               newValue = PAGE_READONLY;
            }
         }
         else if( header->canWrite == false )
         {
            newValue = PAGE_NOACCESS;
         }
         else
         {
            _log( "error, lockTheShiza" );
            return -1;
         }

         unsigned long oldValue = 0;
         int value = VirtualProtect( header, sizeof( noMansLand ), newValue, &oldValue );

         if( !value )
         {
            _log( "error, lockTheShiza VirtualProtect error" );
            return -1;
         }
      #else
         // debug OS-Independent
         // do nothing
      #endif

   #else
      // release mode
      // do nothing
   #endif

   return 0;
}

int
mm::setMemoryChunkReadWrite
(
   void * mem
)
{
   if( !mem )
   {
      loginit();
      _log( "error, invalid parameters" );
      return -1;
   }

   if( dMemoryManagement::enter == false )
   {
      loginit();
      _log( "error, function setMemoryChunkReadWrite cannot occur before program entry" );
      return -1;
   }

   #if defined( _DEBUG ) && !defined( NDEBUG )

      noMansLand * header = ( noMansLand * ) mem - 1;

      if( gmemList->find( &header, ( bintree::equivalence ) equal, 0 ) != 0 )
      {
         _log( "error, block not in list" );
         return -1;
      }

      if( mm::unlockTheShiza( mem ) != 0 )
      {
         _log( "error" );
         return -1;
      }

      mm::integrityMemoryCheck( mem );

      mm::changeTheShiza( mem, true, true );

      if( mm::lockTheShiza( mem ) != 0 )
      {
         _log( "error" );
         return -1;
      }

      #if defined( _MSC_VER )
         // debug MSC
         // call virtual protect
      #else
         // debug OS-Independent
      #endif

   #else
      // release mode
      // do nothing
   #endif

   return 0;
}

int
mm::setMemoryChunkNoReadWrite
(
   void * mem
)
{
   if( !mem )
   {
      loginit();
      _log( "error, invalid parameters" );
      return -1;
   }

   if( dMemoryManagement::enter == false )
   {
      loginit();
      _log( "error, function setMemoryChunkNoReadWrite cannot occur before program entry" );
      return -1;
   }

   #if defined( _DEBUG ) && !defined( NDEBUG )

      noMansLand * header = ( noMansLand * ) mem - 1;

      if( gmemList->find( &header, ( bintree::equivalence ) equal, 0 ) != 0 )
      {
         _log( "error, block not in list" );
         return -1;
      }

      if( mm::unlockTheShiza( mem ) != 0 )
      {
         _log( "error" );
         return -1;
      }

      mm::integrityMemoryCheck( mem );

      mm::changeTheShiza( mem, false, false );

      if( mm::lockTheShiza( mem ) != 0 )
      {
         _log( "error" );
         return -1;
      }

      #if defined( _MSC_VER )
         // debug MSC
         // call virtual protect
      #else
         // debug OS-Independent
      #endif

   #else
      // release mode
      // do nothing
   #endif

   return 0;
}

int
mm::setMemoryChunkReadOnly
(
   void * mem
)
{
   if( !mem )
   {
      loginit();
      _log( "error, invalid parameters" );
      return -1;
   }

   if( dMemoryManagement::enter == false )
   {
      loginit();
      _log( "error, function setMemoryChunkReadOnly cannot occur before program entry" );
      return -1;
   }

   #if defined( _DEBUG ) && !defined( NDEBUG )

      noMansLand * header = ( noMansLand * ) mem - 1;

      if( gmemList->find( &header, ( bintree::equivalence ) equal, 0 ) != 0 )
      {
         _log( "error, block not in list" );
         return -1;
      }

      if( mm::unlockTheShiza( mem ) != 0 )
      {
         _log( "error" );
         return -1;
      }

      mm::integrityMemoryCheck( mem );

      mm::changeTheShiza( mem, true, false );

      if( mm::lockTheShiza( mem ) != 0 )
      {
         _log( "error" );
         return -1;
      }

      #if defined( _MSC_VER )
         // debug MSC
         // call virtual protect
      #else
         // debug OS-Independent
      #endif

   #else
      // release mode
      // do nothing
   #endif

   return 0;
}

mm::mm
(
)
{
}

mm::mm
(
   mm &
)
{
}

mm &
mm::operator=
(
   mm &
)
{
   return this[0];
}

#ifdef __cplusplus
   }
#endif