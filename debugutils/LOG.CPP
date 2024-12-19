
// FileName: log.cpp
// Robert Aldridge

#include "../../general.h"

#if defined( _MSC_VER )
   #pragma warning ( push, 4 )
#endif

#include < stdlib.h >
#include < string.h >

#include "log.h"
#undef _log

#ifdef __cplusplus
   extern "C" {
#endif

#if defined( _DEBUG ) && !defined( NDEBUG )
   #if !defined( _INC_CRTDBG ) && !defined( _MSC_VER )
      #include < stdarg.h >
      #include < stdio.h >

      static int greportType = 0;
      static int greportMode = 0;

      extern
      int
      __cdecl
      _CrtSetReportMode
      (
         int reportType,
         int reportMode
      )
      {
         int oldreportType = greportType;
         greportType = reportType;
         greportMode = reportMode;
         return oldreportType;
      }

      static int greportNumber = 0;

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
      )
      {
         char buffer[ 501 ] = { 0 };
         char * token;

         greportNumber++;

         strcat( buffer, "ReportNumber: " );
         token = buffer + strlen( "ReportNumber: " );
         _itoa( greportNumber, token, 10 );
         strcat( token, "\n" );

         if( filename && filename[0] != 0 )
         {
            strcat( token, "FileName: " );
            strcat( token, filename );
            strcat( token, "\n" );
         }

         strcat( token, "LineNumber: " );
         token = token + strlen( token );
         _itoa( linenumber, token, 10 );
         strcat( token, "\n" );

         if( moduleName && moduleName[0] != 0 )
         {
            strcat( token, "ModuleName: " );
            strcat( token, moduleName );
            strcat( token, "\n" );
         }

         if( format && format[0] != 0 )
         {
            strcat( token, "ClientInfo: " );
            strcat( token, format );
            strcat( token, "\n" );
         }

         printf( buffer );
         return 0;
      }
   #endif

   static char gfilename[ 261 ] = { 0 };
   static int glinenumber = 0;

   extern
   void
   __cdecl
   _logVars
   (
      const char * filename,
      int linenumber
   )
   {
      memcpy( gfilename, filename, strlen( filename ) + 1 );
      glinenumber = linenumber;
   }

   extern
   void
   __cdecl
   _log
   (
      char * format,
      ...
   )
   {
      char dest_buffer[ 514 ] = { 0 };
      char * argptr = 0;

      argptr = ( char * ) &format + ( ( ( sizeof( format ) + sizeof( int ) - 1 ) & ~( sizeof( int ) - 1 ) ) );

      _vsnprintf( dest_buffer, 512, format, argptr );
      strcat( dest_buffer, "\n" );

      _CrtDbgReport( 1, gfilename, glinenumber, "client.exe", dest_buffer );
   }
#endif

#ifdef __cplusplus
   }
#endif