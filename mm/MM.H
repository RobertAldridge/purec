
// File Name: mm.h
// Robert Aldridge

#ifdef __cplusplus
   extern "C" {
#endif

class mm
{

private:

   #if defined( _DEBUG ) && !defined( NDEBUG )
      friend
      static
      int
      dump
      (
         struct noMansLand ** object1
      );

      friend
      static
      int
      equal
      (
         struct noMansLand ** object1,
         struct noMansLand ** object2
      );

      friend
      static
      int
      lessThan
      (
         struct noMansLand ** object1,
         struct noMansLand ** object2
      );
   #endif

   static
   void
   integrityMemoryCheck
   (
      void * mem
   );

   static
   int
   unlockTheShiza
   (
      void * mem
   );

   static
   void
   changeTheShiza
   (
      void * mem,
      bool newCanRead,
      bool newCanWrite
   );

   static
   int
   lockTheShiza
   (
      void * mem
   );

public:

   #ifndef _CLIENT_BLOCK
      #define _CLIENT_BLOCK 4
   #endif

   // for debugging, don't ever call it directly, let the define do it
   static
   void *
   setCodeOrigin
   (
      int blockType,
      const char * filename,
      int linenumber,
      unsigned int minSize
   );

   // automatically memsets memory
   static
   void *
   allocateMemoryChunk
   (
      unsigned int minSize
   );

   #define allocateMemoryChunk( size ) \
      setCodeOrigin( _CLIENT_BLOCK, __FILE__, __LINE__, size )

   static
   int
   deallocateMemoryChunk
   (
      void * mem
   );

   static
   int
   setMemoryChunkReadWrite
   (
      void * mem
   );

   static
   int
   setMemoryChunkNoReadWrite
   (
      void * mem
   );

   static
   int
   setMemoryChunkReadOnly
   (
      void * mem
   );

   // there is no write only function

private:

   mm
   (
   );

   mm
   (
      mm &
   );

   virtual
   ~mm
   (
   ) = 0;

   mm &
   operator=
   (
      mm &
   );
};

#ifdef __cplusplus
   }
#endif