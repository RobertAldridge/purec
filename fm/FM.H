
// File Name: fm.h
// Robert Aldridge

#if !defined( FM )
#define FM

#if defined( _MSC_VER )
   #pragma warning ( disable: 4514 )
#endif

class fileManagement
{

private:

   friend class dFileManagement;

   // contains the list of all clients currently loaded
   static class bintree * fileInstance;

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
   static class bintree * archive;

public:

   static
   int
   loop
   (
   );

   static
   int
   deallocateClient
   (
      struct filePriv ** client
   );

   static
   int
   allocateClient
   (
      struct filePriv ** client,
      char * pathAndFileName,
      char * fileMemory,
      int fileSize
   );

   static
   int
   unlockClient
   (
      struct filePriv * Client
   );

   static
   int
   lockClient
   (
      struct filePriv * Client
   );

   static
   int
   checkDoesClientExist
   (
      struct filePriv * Client
   );

   static
   int
   checkIsFileLoaded
   (
      char * pathAndFileName,
      char ** destBuffer
   );

   static
   int
   addFile
   (
      char * pathAndFileName,
      struct filePriv * client
   );

   static
   int
   removeFile
   (
      char * pathAndFileName,
      struct filePriv * client
   );

   static
   int
   loadFile
   (
      char * fileName,
      struct filePriv * client
   );

private:

   fileManagement(){}
   fileManagement( fileManagement& ){}
   virtual ~fileManagement() = 0;
   fileManagement& operator=( fileManagement& ){}
};

#endif