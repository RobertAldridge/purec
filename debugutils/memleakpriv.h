
// File Name: memleakpriv.h
// Robert Aldridge

#ifdef __cplusplus
   extern "C" {
#endif

#if defined( _DEBUG ) && !defined( NDEBUG ) && !defined( _MSC_VER )

#define _malloc_dbg _malloc_dbg_CodeWarrior
#define _free_dbg _free_dbg_CodeWarrior

class dMemoryLeak
{

private:

   friend
   extern
   void *
   __cdecl
   _malloc_dbg
   (
      unsigned int size,
      int blockType,
      const char * filename,
      int linenumber
   );

   friend
   extern
   void
   __cdecl
   _free_dbg
   (
      void * mem,
      int blockType
   );

   friend class dInitGlobalData;

   static bool enter;

   static
   void
   dMemoryLeakInit
   (
   );

   static
   void
   dMemoryLeakTerm
   (
   );
};

#endif

#ifdef __cplusplus
   }
#endif