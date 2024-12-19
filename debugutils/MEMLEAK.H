
// File Name: memleak.h
// Drew Canitz
// modified by Robert Aldridge

// overrides critical memory allocation functions in debug mode
// include in all code files

// overrides:
//   malloc
//   calloc
//   realloc
//   free
//   new
//   delete

// otherwise don't look at this header file (below this line is crazy header stuff), nothing to see here folks

#if !defined( MEMLEAK )
#define MEMLEAK

#ifdef __cplusplus
   extern "C" {
#endif

/* This header file was written by Drew Canitz 01/03/2002 */
/* OS-Independent code modifications by Robert Aldridge 06/20/2002 */

// if we're in debug mode
#if defined( _DEBUG ) && !defined( NDEBUG )

   #if defined( _DLL ) && defined( _MSC_VER )
      #define __import __declspec( dllimport )
   #else
      #define __import extern
   #endif

   #if !defined( _MSC_VER )
      #define _malloc_dbg _malloc_dbg_CodeWarrior
      #define _calloc_dbg _calloc_dbg_CodeWarrior
      #define _realloc_dbg _realloc_dbg_CodeWarrior
      #define _free_dbg _free_dbg_CodeWarrior
   #endif

   __import
   void *
   __cdecl
   _malloc_dbg
   (
      unsigned int,
      int,
      const char *,
      int
   );

   __import
   void *
   __cdecl
   _calloc_dbg
   (
      unsigned int,
      unsigned int,
      int,
      const char *,
      int
   );

   __import
   void *
   __cdecl
   _realloc_dbg
   (
      void *,
      unsigned int,
      int,
      const char *,
      int
   );

   __import
   void
   __cdecl
   _free_dbg
   (
      void *,
      int
   );

   inline
   void
   __cdecl
   operator
   delete
   (
      void * _P,
      int cb,
      const char *,
      int
   )
   {
      _free_dbg( _P, cb );
   }

   inline
   void *
   __cdecl
   operator new
   (
      unsigned int s,
      int cb,
      const char * file,
      int line
   )
   {
      if( s == 0 )
      {
         return _malloc_dbg( 1, cb, file, line );
      }

      return _malloc_dbg( s, cb, file, line );
   }

   #if defined( _MSC_VER )
      #define _CRTDBG_LEAK_CHECK_DF 0x20
      #define _CRTDBG_REPORT_FLAG -1
      #define _CLIENT_BLOCK 4

      __import
      int
      __cdecl
      _CrtSetDbgFlag
      (
         int
      );

      // set the debug flags so they report at program termination
      static int _static_dbg_flags =
         _CrtSetDbgFlag( _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG ) | _CRTDBG_LEAK_CHECK_DF );

      // override the memory allocation functions to allow the heap detection
   #else
      #define _CLIENT_BLOCK 4
   #endif

   #define new new( _CLIENT_BLOCK, __FILE__, __LINE__ )
   #define malloc( n ) _malloc_dbg( ( n ), _CLIENT_BLOCK, __FILE__, __LINE__ )
   #define calloc( n, d ) _calloc_dbg( ( n ), ( d ), _CLIENT_BLOCK, __FILE__, __LINE__ )
   #define realloc( p, n ) _realloc_dbg( ( p ), ( n ), _CLIENT_BLOCK, __FILE__, __LINE__ )

   // override the memory freeing functions for heap detection
   #define free( n ) _free_dbg( ( n ), _CLIENT_BLOCK )
#elif defined( NDEBUG )
   #include < malloc.h >

   inline
   void *
   __cdecl
   operator new
   (
      unsigned int s,
      int,
      const char *,
      int
   )
   {
      if( s == 0 )
      {
         return malloc( 1 );
      }

      return malloc( s );
   }

   inline
   void
   __cdecl
   operator delete
   (
      void * _P,
      int,
      const char *,
      int
   )
   {
      free( _P );
   }
#endif /* _DEBUG NDEBUG */

#ifdef __cplusplus
   }
#endif

#endif /* MEMLEAK */