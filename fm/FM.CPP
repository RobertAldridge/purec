
// File Name: fm.cpp
// Robert Aldridge

#include "../../general.h"

#if defined( _MSC_VER )
   #pragma warning ( push, 4 )
#endif

#include < memory.h >
#include < stdio.h >
#include < string.h >

#include "../redblack/bintree.h"
#include "fm.h"
#include "fmpub.h"
#undef fileLoad
#include "fmpriv.h"
#include "../debugutils/log.h"
#include "../debugutils/memleak.h"
#include "../mm/mm.h"

struct filePriv
{
   #if defined( _DEBUG ) && !defined( NDEBUG )
      char filename[ 261 ];
      int linenumber;
   #endif

   char pathAndFileName[ 261 ];

   char * fileMemory;
   int fileMemorySize;

   int filePos;
   int fileSize;
   bool readOnly;

   double timeStamp;
};

struct fileCounter
{
   char pathAndFileName[ 261 ];

   char * fileMemory;

   int fileSize;

   int numClients;
   double timeStamp;
};

static char gfilename[ 261 ] = { 0 };
static int glinenumber = 0;

// for debugging
void
filePub::setCodeOrigin
(
   const char * filename,
   int linenumber
)
{
   memcpy( gfilename, filename, strlen( filename ) + 1 );
   glinenumber = linenumber;
}

// creates an instance of filePub
// loads a file into the new client
filePub *
filePub::fileLoad
(
   // specify file to load
   char * pathAndFileName,
   // specify whether to load the file in read only
   // mode or read/write mode
   //
   // read only mode allows multiple clients
   // to share the same file memory
   // (between clients in read only mode )
   bool readOnly,
   // flag overwrites old file when not in readOnly == false
   bool destroyOldFile
)
{
   filePriv * fileData;

   FILE * file;
   
   if( readOnly == false )
   {
      if( destroyOldFile == true )
      {
         file = fopen( pathAndFileName, "wb" );
      }
      else
      {
         file = fopen( pathAndFileName, "rb" );
      }
   }
   else if( readOnly == true )
   {
      filePriv tempFileData;

      if( fileManagement::loadFile( pathAndFileName, &tempFileData ) != 0 )
      {
         file = fopen( pathAndFileName, "rb" );
      }
      else
      {
         if( fileManagement::allocateClient( &fileData,
                                             pathAndFileName,
                                             tempFileData.fileMemory,
                                             tempFileData.fileSize
                                           ) != 0
           )
         {
            _log( "error" );
            return 0;
         }

         fileData->filePos = 0;
         fileData->readOnly = readOnly;

         #if defined( _DEBUG ) && !defined( NDEBUG )
            memcpy( fileData->filename, gfilename, strlen( gfilename ) + 1 );
            fileData->linenumber = glinenumber;
         #endif

         fileManagement::lockClient( fileData );
         return ( filePub * ) fileData;
      }
   }

   if( !file )
   {
      if( readOnly == true )
      {
         _log( "error" );
         return 0;
      }
      else
      {
         file = fopen( pathAndFileName, "wb" );

         if( !file )
         {
            _log( "error" );
            return 0;
         }

         if( fileManagement::allocateClient( &fileData, pathAndFileName, 0, 0 ) != 0 )
         {
            fclose( file );
            _log( "error" );
            return 0;
         }

         fileData->filePos = 0;
         fileData->readOnly = readOnly;
      }
   }
   else
   {
      if( fseek( file, 0, SEEK_SET ) != 0 )
      {
         fclose( file );
         _log( "error" );
         return 0;
      }

      long fileSize = ftell( file );

      if( fileSize < 0 )
      {
         fclose( file );
         _log( "error" );
         return 0;
      }

      if( fseek( file, 0, SEEK_END ) != 0 )
      {
         fclose( file );
         _log( "error" );
         return 0;
      }

      fileSize = ftell( file ) - fileSize;

      if( fileSize <= 0 )
      {
         fclose( file );
         _log( "error" );
         return 0;
      }

      if( fseek( file, 0, SEEK_SET ) != 0 )
      {
         fclose( file );
         _log( "error" );
         return 0;
      }

      if( fileManagement::allocateClient( &fileData, pathAndFileName, 0, fileSize ) != 0 )
      {
         fclose( file );
         _log( "error" );
         return 0;
      }

      if( ( int ) fread( fileData->fileMemory, 1, fileSize, file ) != fileSize )
      {
         fileManagement::deallocateClient( &fileData );
         fclose( file );
         _log( "error" );
         return 0;
      }

      if( readOnly == true )
      {
         if( fileManagement::addFile( pathAndFileName, fileData ) != 0 )
         {
            fileManagement::deallocateClient( &fileData );
            fclose( file );
            _log( "error" );
            return 0;
         }
      }

      fileData->filePos = 0;
      fileData->readOnly = readOnly;
   }

   #if defined( _DEBUG ) && !defined( NDEBUG )
      memcpy( fileData->filename, gfilename, strlen( gfilename ) + 1 );
      fileData->linenumber = glinenumber;
   #endif

   if( fclose( file ) != 0 )
   {
      _log( "error" );
   }

   if( fileManagement::lockClient( fileData ) != 0 )
   {
      _log( "error" );
   }
   
   return ( filePub * ) fileData;
}

// destroys an instance of filePub
// unloads the file that is loaded into the client
// saving the file is optional
int
filePub::fileUnload
(
   // specify path and name if file is being saved
   char * pathAndFileName,
   bool saveFile
)
{   
   filePriv * fileData = ( filePriv * ) this;

   if( fileManagement::checkDoesClientExist( fileData ) != 0 )
   {
      _log( "error" );
      return -1;
   }

   if( fileManagement::unlockClient( fileData ) != 0 )
   {
      _log( "error" );
      return -1;
   }

   int error = 0;

   if( saveFile == true )
   {
      if( !pathAndFileName )
      {
         pathAndFileName = fileData->pathAndFileName;
      }

      FILE * file = fopen( pathAndFileName, "wb" );

      if( !file )
      {
         _log( "error" );
         error = -1;
      }
      else
      {
         if( ( int ) fwrite( fileData->fileMemory, 1, fileData->fileSize, file ) != fileData->fileSize )
         {
            _log( "error" );
            error = -1;
         }

         if( fclose( file ) != 0 )
         {
            _log( "error" );
            error = -1;
         }
      }
   }

   if( fileManagement::deallocateClient( &fileData ) != 0 )
   {
      _log( "error" );
      error = -1;
   }

   return error;
}

// writes some bytes from a buffer to a file
int
filePub::write
(
   char * sourceBuf,
   int numBytes,
   bool moveFilePtr
)
{
   int error = 0;

   filePriv * fileData = ( filePriv * ) this;

   if( !sourceBuf || numBytes <= 0 )
   {
      _log( "error" );
      return -1;
   }

   if( fileManagement::checkDoesClientExist( fileData ) != 0 )
   {
      _log( "error" );
      return -1;
   }

   if( fileManagement::unlockClient( fileData ) != 0 )
   {
      _log( "error" );
      return -1;
   }

   if( fileData->readOnly == true )
   {
      _log( "error" );
      error = -1;
   }
   else if( fileData->filePos + numBytes <= fileData->fileSize )
   {
      memcpy( &fileData->fileMemory[fileData->filePos], sourceBuf, numBytes );

      if( moveFilePtr == true )
      {
         fileData->filePos += numBytes;
      }
   }
   else if( fileData->filePos + numBytes <= fileData->fileMemorySize )
   {
      memcpy( &fileData->fileMemory[fileData->filePos], sourceBuf, numBytes );

      fileData->fileSize = fileData->filePos + numBytes;

      if( moveFilePtr == true )
      {
         fileData->filePos += numBytes;
      }
   }
   else
   {
      int oldPos = fileData->filePos;

      if( this->setpos( fileData->filePos + numBytes ) != 0 )
      {
         _log( "error" );
         error = -1;
      }
      else
      {
         fileData->filePos = oldPos;

         memcpy( &fileData->fileMemory[fileData->filePos], sourceBuf, numBytes );

         fileData->fileSize = fileData->filePos + numBytes;

         if( moveFilePtr == true )
         {
            fileData->filePos += numBytes;
         }
      }
   }

   if( fileManagement::lockClient( fileData ) != 0 )
   {
      _log( "error" );
      error = -1;
   }

   return error;
}

// reads some bytes from a file to a buffer
int
filePub::read
(
   char * destBuf,
   int numBytes,
   bool moveFilePtr
)
{
   int error = 0;

   filePriv * fileData = ( filePriv * ) this;

   if( !destBuf || numBytes <= 0 )
   {
      _log( "error" );
      return -1;
   }

   if( fileManagement::checkDoesClientExist( fileData ) != 0 )
   {
      _log( "error" );
      return -1;
   }

   if( fileManagement::unlockClient( fileData ) != 0 )
   {
      _log( "error" );
      return -1;
   }

   if( fileData->filePos + numBytes <= fileData->fileSize )
   {
      memcpy( destBuf, &fileData->fileMemory[fileData->filePos], numBytes );

      if( moveFilePtr == true )
      {
         fileData->filePos += numBytes;
      }

      fileManagement::lockClient( fileData );
      return 0;
   }
   else
   {
      _log( "error" );
      error = -1;
   }

   if( fileManagement::lockClient( fileData ) != 0 )
   {
      _log( "error" );
      return -1;
   }

   return error;
}

// gets the current position of the file pointer,
// in bytes, from the start of the file
int
filePub::getpos
(
   int * destNumBytesFromOrigin
)
{
   filePriv * fileData = ( filePriv * ) this;

   if( !destNumBytesFromOrigin )
   {
      _log( "error" );
      return -1;
   }

   if( fileManagement::checkDoesClientExist( fileData ) != 0 )
   {
      _log( "error" );
      return -1;
   }

   if( fileManagement::unlockClient( fileData ) != 0 )
   {
      _log( "error" );
      return -1;
   }

   destNumBytesFromOrigin[0] = fileData->filePos;

   if( fileManagement::lockClient( fileData ) != 0 )
   {
      _log( "error" );
      return -1;
   }

   return 0;
}

// sets the position of the file pointer
// ( relative to the start of the file, units is bytes )
int
filePub::setpos
(
   int newNumBytesFromOrigin
)
{
   filePriv * fileData = ( filePriv * ) this;

   if( newNumBytesFromOrigin < 0 )
   {
      _log( "error" );
      return -1;
   }

   if( fileManagement::checkDoesClientExist( fileData ) != 0 )
   {
      _log( "error" );
      return -1;
   }

   if( fileManagement::unlockClient( fileData ) != 0 )
   {
      _log( "error" );
      return -1;
   }

   if( newNumBytesFromOrigin >= fileData->fileSize )
   {
      if( fileData->readOnly == true )
      {
         fileManagement::lockClient( fileData );
         _log( "error" );
         return -1;
      }
      else if( newNumBytesFromOrigin < fileData->fileMemorySize )
      {
         fileData->filePos = newNumBytesFromOrigin;
      }
      else
      {
         int newFileMemorySize = fileData->fileMemorySize * 2;

         while( newNumBytesFromOrigin >= newFileMemorySize )
         {
            newFileMemorySize = fileData->fileMemorySize * 2;
         }

         char * newFileMemory = ( char * ) mm::allocateMemoryChunk( newFileMemorySize );

         if( !newFileMemory )
         {
            fileManagement::lockClient( fileData );
            _log( "error" );
            return -1;
         }

         memcpy( newFileMemory, fileData->fileMemory, fileData->fileSize );

         if( mm::deallocateMemoryChunk( fileData->fileMemory ) != 0 )
         {
            _log( "error" );
         }

         fileData->fileMemory = newFileMemory;
         fileData->fileMemorySize = newFileMemorySize;
      }
   }

   fileData->filePos = newNumBytesFromOrigin;
   fileManagement::lockClient( fileData );
   return 0;
}

// gets the size of a file, in bytes
int
filePub::size
(
   int * destSizeInBytes
)
{
   filePriv * fileData = ( filePriv * ) this;

   if( !destSizeInBytes )
   {
      _log( "error" );
      return -1;
   }

   if( fileManagement::checkDoesClientExist( fileData ) != 0 )
   {
      _log( "error" );
      return -1;
   }

   if( fileManagement::unlockClient( fileData ) != 0 )
   {
      _log( "error" );
      return -1;
   }

   destSizeInBytes[0] = fileData->fileSize;

   if( fileManagement::lockClient( fileData ) != 0 )
   {
      _log( "error" );
      return -1;
   }

   return 0;
}

filePub::filePub
(
)
{
}

filePub::filePub
(
   filePub &
)
{
}

filePub &
filePub::operator=
(
   filePub &
)
{
   return this[0];
}

// contains the list of all clients currently loaded
bintree * fileManagement::fileInstance = 0;

// contains the list of all files in the archive
//
// has a refcount for every file of how many clients
// are using it for read/write mode
//
// has a refcount for every file of how many clients
// are using it for read only mode
//
// contains a pointer for each file that is set
// when a client loads that file in read only mode
bintree * fileManagement::archive = 0;

static
int
lessThanStruct
(
   fileCounter * object1,
   fileCounter * object2
)
{
   if( strcmp( object1->pathAndFileName, object2->pathAndFileName ) < 0 )
   {
      return 1;
   }

   return 0;
}

static
int
lessThanPtr
(
   filePriv ** object1,
   filePriv ** object2
)
{
   if( object1[0] < object2[0] )
   {
      return 1;
   }

   return 0;
}

static
int
equalStruct
(
   fileCounter * object1,
   fileCounter * object2
)
{
   if( strcmp( object1->pathAndFileName, object2->pathAndFileName ) == 0 )
   {
      return 1;
   }

   return 0;
}

static
int
equalPtr
(
   filePriv ** object1,
   filePriv ** object2
)
{
   if( object1[0] == object2[0] )
   {
      return 1;
   }

   return 0;
}

static
int
dumpStruct
(
   fileCounter * object1
)
{
   _log( "warning, file not unloaded by client\nPointer Value: %p\nSize Of Allocation: %d\n"
         "File Name: %s\nNumber of clients using it: %d\n",
         object1->fileMemory,
         object1->fileSize,
         object1->pathAndFileName,
         object1->numClients
       );

   if( mm::deallocateMemoryChunk( object1->fileMemory ) != 0 )
   {
      _log( "error" );
   }

   return 0;
}

static
int
dumpPtr
(
   filePriv ** object1
)
{
   if( fileManagement::unlockClient( object1[0] ) != 0 )
   {
      _log( "error" );
      return 0;
   }

   #if defined( _DEBUG ) && !defined( NDEBUG )
      _log( "warning, file not unloaded by client\nPointer Value: %p\nSize Of Allocation: %d\n"
            "File Name: %s\nFile Name File Creation Originated From: %s\nFile Line Number: %d\n",
            object1[0]->fileMemory,
            object1[0]->fileSize,
            object1[0]->pathAndFileName,
            object1[0]->filename,
            object1[0]->linenumber
          );
   #else
      _log( "warning, file not unloaded by client\nPointer Value: %p\nSize Of Allocation: %d\n"
            "File Name: %s\n",
            object1[0]->fileMemory,
            object1[0]->fileSize,
            object1[0]->pathAndFileName
          );
   #endif

   if( ( ( filePub * ) ( object1[0] ) )->fileUnload() != 0 )
   {
      object1[0] = 0;
      _log( "error" );
      return 0;
   }

   object1[0] = 0;
   return 0;
}

static bool binTreeRemoveFlag = true;

bool dFileManagement::enter = false;

void
dFileManagement::dFileManagementInit
(
)
{
   loginit();

   if( !fileManagement::fileInstance )
   {
      fileManagement::fileInstance = bintree::init( 1000, sizeof( filePriv * ), ( bintree::compare ) lessThanPtr );

      if( !fileManagement::fileInstance )
      {
         _log( "error, BinTreeInit failure" );
         return;
      }
   }

   if( !fileManagement::archive )
   {
      fileManagement::archive = bintree::init( 20, sizeof( fileCounter ), ( bintree::compare ) lessThanStruct );

      if( !fileManagement::archive )
      {
         fileManagement::fileInstance->bintree::term();
         _log( "error, BinTreeInit failure" );
         return;
      }
   }

   dFileManagement::enter = true;
}

void
dFileManagement::dFileManagementTerm
(
)
{
   loginit();

   if( fileManagement::fileInstance )
   {
      if( fileManagement::fileInstance->isEmpty( 0 ) != 1 )
      {
         _log( "warning, memory not freed by client\n" );

         binTreeRemoveFlag = false;

         if( fileManagement::fileInstance->dump( ( bintree::evaluate ) dumpPtr, bintree::inorder ) != 0 )
         {
            _log( "warning, BinTreeDump error" );
         }

         binTreeRemoveFlag = true;
      }

      if( fileManagement::fileInstance->term() != 0 )
      {
         _log( "warning, BinTreeTerm error" );
      }

      fileManagement::fileInstance = 0;
   }

   if( fileManagement::archive )
   {
      if( fileManagement::archive->isEmpty( 0 ) != 1 )
      {
         _log( "warning, memory not freed by client\n" );

         binTreeRemoveFlag = false;

         if( fileManagement::archive->dump( ( bintree::evaluate ) dumpStruct, bintree::inorder ) != 0 )
         {
            _log( "warning, BinTreeDump error" );
         }

         binTreeRemoveFlag = true;
      }

      if( fileManagement::archive->term() != 0 )
      {
         _log( "warning, BinTreeTerm error" );
      }

      fileManagement::archive = 0;
   }

   logterm();
   dFileManagement::enter = false;
}

int
fileManagement::loop
(
)
{
   return 0;
}

int
fileManagement::deallocateClient
(
   struct filePriv ** client
)
{
   int error = 0;

   if( binTreeRemoveFlag == true )
   {
      error |= fileManagement::fileInstance->remove( &client[0], ( bintree::equivalence ) equalPtr, 0 );
   }

   if( client[0]->readOnly == true )
   {
      if( binTreeRemoveFlag == true )
      {
         error |= fileManagement::removeFile( client[0]->pathAndFileName, client[0] );
      }
      else
      {
         client[0]->fileMemory = 0;
      }
   }

   if( client[0]->fileMemory )
   {
      error |= mm::deallocateMemoryChunk( client[0]->fileMemory );
   }

   if( client[0] )
   {
      error |= mm::deallocateMemoryChunk( client[0] );
   }

   client[0] = 0;

   if( error != 0 )
   {
      _log( "error" );
   }

   return error;
}

int
fileManagement::allocateClient
(
   struct filePriv ** client,
   char * pathAndFileName,
   char * fileMemory,
   int fileSize
)
{
   if( !client || !pathAndFileName || fileSize < 0 )
   {
      _log( "error" );
      return -1;
   }

   client[0] = ( filePriv * ) mm::allocateMemoryChunk( sizeof( filePriv ) );
   
   if( !client[0] )
   {
      _log( "error" );
      goto allocate_free_client;
   }

   memcpy( client[0]->pathAndFileName, pathAndFileName, strlen( pathAndFileName ) );
   client[0]->fileSize = fileSize;
   client[0]->fileMemorySize = fileSize;

   if( fileSize > 0 )
   {
      if( fileMemory )
      {
         client[0]->fileMemory = fileMemory;
         
         if( fileManagement::addFile( pathAndFileName, client[0] ) != 0 )
         {
            if( client[0] )
            {
               free( client[0] );
               client[0] = 0;
            }

            _log( "error" );
            return -1;
         }
      }
      else
      {
         client[0]->fileMemory = ( char * ) mm::allocateMemoryChunk( fileSize );

         if( !client[0]->fileMemory )
         {
            _log( "error" );
            goto allocate_free_client;
         }
      }
   }

   if( fileManagement::fileInstance->insert( &client[0], ( bintree::compare ) lessThanPtr ) != 0 )
   {
      _log( "error" );
      goto allocate_free_client;
   }

   return 0;

allocate_free_client:

   if( client[0] && client[0]->fileMemory )
   {
      free( client[0]->fileMemory );
   }

   if( client[0] )
   {
      free( client[0] );
      client[0] = 0;
   }

   return -1;
}

int
fileManagement::unlockClient
(
   struct filePriv * client
)
{
   int error = 0;
   error |= mm::setMemoryChunkReadWrite( client );
   error |= mm::setMemoryChunkReadWrite( client->fileMemory );

   if( error != 0 )
   {
      _log( "error" );
   }

   return error;
}

int
fileManagement::lockClient
(
   struct filePriv * client
)
{
   int error = 0;
   error |= mm::setMemoryChunkNoReadWrite( client->fileMemory );
   error |= mm::setMemoryChunkNoReadWrite( client );

   if( error != 0 )
   {
      _log( "error" );
   }

   return error;
}

int
fileManagement::checkDoesClientExist
(
   struct filePriv * client
)
{
   if( fileManagement::fileInstance->find( &client, ( bintree::equivalence ) equalPtr, 0 ) != 0 )
   {
      _log( "error, block not in list" );
      return -1;
   }

   return 0;
}

int
fileManagement::addFile
(
   char * pathAndFileName,
   struct filePriv * client
)
{
   if( !pathAndFileName || !client )
   {
      _log( "error" );
      return -1;
   }

   fileCounter object = { 0 };
   memcpy( object.pathAndFileName, pathAndFileName, strlen( pathAndFileName ) );

   if( fileManagement::archive->find( &object, ( bintree::equivalence ) equalStruct, &object ) != 0 )
   {   
      object.fileMemory = client->fileMemory;
      object.fileSize = client->fileSize;
      object.numClients = 1;
      // object.timeStamp = currentTime();

      if( fileManagement::archive->insert( &object, ( bintree::compare ) lessThanStruct ) != 0 )
      {
         _log( "error" );
         return -1;
      }

      return 0;
   }

   if( fileManagement::archive->remove( &object, ( bintree::equivalence ) equalStruct, &object ) != 0 )
   {
      _log( "error" );
      return -1;
   }

   object.numClients++;
   // object.timeStamp = currentTime();

   if( fileManagement::archive->insert( &object, ( bintree::compare ) lessThanStruct ) != 0 )
   {
      _log( "error" );
      return -1;
   }

   return 0;
}

int
fileManagement::removeFile
(
   char * pathAndFileName,
   struct filePriv * client
)
{
   if( !pathAndFileName || !client )
   {
      _log( "error" );
      return -1;
   }

   fileCounter object = { 0 };
   memcpy( object.pathAndFileName, pathAndFileName, strlen( pathAndFileName ) );

   if( fileManagement::archive->find( &object, ( bintree::equivalence ) equalStruct, &object ) != 0 )
   {
      _log( "error" );
      return -1;
   }

   if( fileManagement::archive->remove( &object, ( bintree::equivalence ) equalStruct, &object ) != 0 )
   {
      _log( "error" );
      return -1;
   }

   object.numClients--;
   // object.timeStamp = currentTime();

   client->fileMemory = 0;

   if( object.numClients > 0 )
   {
      if( fileManagement::archive->insert( &object, ( bintree::compare ) lessThanStruct ) != 0 )
      {
         _log( "error" );
         return -1;
      }
   }
   else if( mm::deallocateMemoryChunk( object.fileMemory ) != 0 )
   {
      _log( "error" );
      return -1;
   }

   return 0;
}

int
fileManagement::loadFile
(
   char * pathAndFileName,
   struct filePriv * client
)
{
   if( !pathAndFileName || !client )
   {
      _log( "error" );
      return -1;
   }

   memset( client, 0, sizeof( filePriv ) );

   fileCounter object = { 0 };
   memcpy( object.pathAndFileName, pathAndFileName, strlen( pathAndFileName ) );

   if( fileManagement::archive->find( &object, ( bintree::equivalence ) equalStruct, &object ) != 0 )
   {
      return -1;
   }
   
   client->fileMemory = object.fileMemory;
   client->fileSize = object.fileSize;

   return 0;
}