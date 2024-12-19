
// File Name: log.h
// Robert Aldridge

// LOG START
#if !defined( LOG )
#define LOG

#ifdef __cplusplus
   extern "C" {
#endif

#if defined( _MSC_VER )
   #pragma warning ( disable: 4003 )
   #pragma warning ( disable: 4127 )
#endif

#if defined( _DEBUG ) && !defined( NDEBUG )
   #if !defined( _INC_CRTDBG )
      #if defined( _MSC_VER )

         #if defined( _DLL )
            #define __import __declspec( dllimport )
         #else
            #define __import extern
         #endif

         __import
         int
         __cdecl
         _CrtSetReportMode
         (
            int reportType,
            int reportMode
         );

         __import
         int
         __cdecl
         _CrtDbgReport
         (
            int reportType,
            const char * filename,
            int linenumber,
            const char * moduleName,
            const char * format,
            ...
         );

         __import
         int
         __cdecl
         _vsnprintf
         (
            char *,
            unsigned int,
            const char *,
            char *
         );
      #else
         #include < stdarg.h >
         #include < stdio.h >

         extern
         int
         __cdecl
         _CrtSetReportMode
         (
            int reportType,
            int reportMode
         );

         extern
         int
         __cdecl
         _CrtDbgReport
         (
            int reportType,
            const char * filename,
            int linenumber,
            const char * moduleName,
            const char * format,
            ...
         );
      #endif
   #endif

   #define loginit() _CrtSetReportMode( 1, 2 )

   #define logterm()

   #define __log( s )                                                  \
      do                                                               \
      {                                                                \
         _CrtDbgReport( 1, __FILE__, __LINE__, "client.exe", s "\n" ); \
                                                                       \
      }while( 0 )

   #define log_assert( s, t )                                                          \
      do                                                                               \
      {                                                                                \
         if( !( s ) )                                                                  \
         {                                                                             \
            _CrtDbgReport( 1, __FILE__, __LINE__, "client.exe", "assert" " " t "\n" ); \
         }                                                                             \
                                                                                       \
      }while( 0 )

   #define log_assert_return( s, t, u )                                                       \
      do                                                                                      \
      {                                                                                       \
         if( !( s ) )                                                                         \
         {                                                                                    \
            _CrtDbgReport( 1, __FILE__, __LINE__, "client.exe", "assert_return" " " u "\n" ); \
                                                                                              \
            return( t );                                                                      \
         }                                                                                    \
                                                                                              \
      }while( 0 )

   extern
   void
   __cdecl
   _logVars
   (
      const char * filename,
      int linenumber
   );

   extern
   void
   __cdecl
   _log
   (
      char * format,
      ...
   );

   #define _log _logVars( __FILE__, __LINE__ ); _log
#elif defined( NDEBUG )
   #if defined( _MSC_VER )
      #pragma warning ( disable: 4505 )
      #pragma warning ( disable: 4514 )
      #pragma warning ( disable: 4553 )
   #endif

   #define loginit()

   #define logterm()

   #define __log( s ) s

   #define log_assert( s, t ) s

   #define log_assert_return( s, t, u ) s

   #if !defined( _MSC_VER )
      #define __forceinline inline
   #endif

   static
   void
   __cdecl
   _log
   (
      char *,
      ...
   )
   {
   }
#endif

#ifdef __cplusplus
   }
#endif

#endif
// LOG END