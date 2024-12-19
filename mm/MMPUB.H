
// File Name: mmpub.h
// Robert Aldridge

#ifdef __cplusplus
   extern "C" {
#endif

class mm
{

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