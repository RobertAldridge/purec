
// File Name: fmpub.h
// Robert Aldridge
// to do: file unloading based off of time stamping

// File Management:
//   The bare-bones essentials.  I am quite sure that this in not what people had in mind when I
//   got put on file management, but this is the base class, it can be derived for more functionality.
//
// The class is rock solid.  Let me explain (reasons to use this class):
//
// Reason #1:  All instances of file are put into a list, and everytime a function is
//             called, the function validates its own this pointer to make sure it
//             is a valid file instantiation.
//
// Reason #2:  The class cannot be constructed, so there is no guessing if there was an error in the
//             class constructor.  The singleton access returns an error code, letting the user know
//             if creation/load was successful, if not then there will be no garbage to worry about.
//             Similarly for the function that destroys the instance, it nulls out the pointer as well.
//
// Reason #3:  Memory Protection.  Yes that's right folks.  This class has the unique priviledge of
//             being able to lock its own memory.  So the pointer that fileLoad returns points to locked
//             memory, and it is never unlocked, only inside of filePub functions does the memory become
//             usable.  So no more memory overwriting!
//
// Reason #4   Fast access.  The file is loaded into memory when a file is instantiated.
//             Read and Writing to a memory buffer has speed advantages.
//
// Reason #5   Shared Memory.  If the same file is opened by multiple instantiations of file, there will
//             only be one copy of the file loaded, shared by the file instances.  This is only for
//             instances in read-only mode.  This extra feature is due to another list that keeps track
//             of files open for read only, with a pointer to the memory and a ref-count.
//
// Reason #6   OS-Independent Interface and Implementation
//
// Reason #7   More debugging features!  The file name and line number of the client who instantiates
//             a file is saved in that instance of file, and if the file is not unloaded by the time the
//             scope of the executable leaves the main function, then an error is logged with info
//             on the file that was still loaded and info on the client that loaded it, and it is
//             automatically unloaded for you.  No more memory leaks!
//
// Reason #8   Smart Read/Write.  If you load the file instance in Read/Write mode, you can seamlessly
//             switch between the two without worry, unlike typical file operations.  And the instance
//             knows when to increase the size of the file as you write past the original end of file,
//             creating a new end of file, as needed.
//
// Reason #9   These functions have such extensive error checking that they will never crash,
//             error checking and error handling is always done gracefully.  Any internal errors
//             will be logged and can be tracked down for easier debugging, increasing production.

#if !defined( FMPUB )
#define FMPUB

#ifdef __cplusplus
   extern "C" {
#endif

/*
   Sample Code:

   #include "filepub.h"

   filePub * newFile = filePub::fileLoad( &newFile, "bob.txt" );

   char array[ 256 ] = { 0 };
   int size;

   newFile->size( &size );

   if( size > 256 )
      size = 256;

   newFile->read( array, size );

   newFile->unload();
*/

class filePub
{

public:

   // for debugging, don't ever call it directly, let the define do it
   static
   void
   setCodeOrigin
   (
      const char * filename,
      int linenumber
   );

   // all functions return 0 for success and -1 for failure

   // creates an instance of filePub
   // loads a file into the new client
   static
   filePub *
   fileLoad
   (
      // specify file to load
      char * pathAndFileName,
      // specify whether to load the file in read only
      // mode or read/write mode
      //
      // read only mode allows multiple clients
      // to share the same file memory
      // (between clients in read only mode )
      bool readOnly = true,
      // flag overwrites old file when not in readOnly == false
      bool destroyOldFile = false
   );

   #define fileLoad \
      setCodeOrigin( __FILE__, __LINE__ ); filePub::fileLoad

   // destroys an instance of filePub
   // unloads the file that is loaded into the client
   // saving the file is optional
   int
   fileUnload
   (
      // specify path and name if file is being saved
      char * pathAndFileName = 0,
      bool saveFile = false
   );

   // writes some bytes from a buffer to a file
   int
   write
   (
      char * sourceBuf,
      int numBytes,
      bool moveFilePtr = true
   );

   // reads some bytes from a file to a buffer
   int
   read
   (
      char * destBuf,
      int numBytes,
      bool moveFilePtr = true
   );

   // gets the current position of the file pointer,
   // in bytes, from the start of the file
   int
   getpos
   (
      int * destNumBytesFromOrigin
   );

   // sets the position of the file pointer
   // ( relative to the start of the file, units is bytes )
   int
   setpos
   (
      int newNumBytesFromOrigin
   );

   // gets the size of a file, in bytes
   int
   size
   (
      int * destSizeInBytes
   );

private:

   filePub
   (
   );

   filePub
   (
      filePub &
   );

   virtual
   ~filePub
   (
   ) = 0;

   filePub &
   operator=
   (
      filePub &
   );
};

#ifdef __cplusplus
   }
#endif

#endif