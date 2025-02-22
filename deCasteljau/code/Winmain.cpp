

// We want this module to handle all os dependant code
//
// 1) Prestep -
//
// 2) Prestep -
//
// 3) Prestep -
//
// 4) Prestep -
//
// 5) Prestep -
//
//
// 6) Initialize code that checks for memory leaks in debug mode
//
// 7) Create an application with a client area width by height
//
// 8) Create a dib section which will be the backbuffer
//
// 9) Call a client defined init function, passing it some parameters.
//
// 10) Handle input every program loop, supplying it to a client.
//
// 11) Start initial termination on:
//
//     hitting ESC key
//     on clicking the window close x button
//     when any client function returns anything besides 0
//
//     ...these next items will be called after initial termination
//
// 12) Call the client defined term function for client cleanup
//
// 13) Clean up dib stuff
//
// 14) Do any other clean up here
//
// 15) Close application
//
//
// 16) Check return errors for memory leaks

// Client functions must always return 0 when succesful. Any
// other return value will cause initial termination and a
// warning log.
extern "C" extern int init( double halfWidth,
                            double halfHeight,
                            void ( *circleDrawingPrimitive )( int, int, int, int, int ),
                            void ( *lineDrawingPrimitive )( int, int, int, int, int, int ),
                            void ( *pointDrawingPrimitive )( int, int, int )
                          );

// We want to stick with basic types here,
// so pass 3 floating points.
extern "C" extern int main( int inputEvent,
                            double x,
                            double y,
                           
                            double halfWidth,
                            double halfHeight
                          );

// The return value of term isn't used for much
// since initial termination must have already taken
// place for the function to be called.  It will
// still be logged as a warning if the return value
// of the function is not 0.
extern "C" extern int term(
                          );

#ifdef DEBUG

   #undef DEBUG

#endif

#ifdef NDEBUG

   #undef NDEBUG

#endif

#define DEBUG 1

#pragma warning ( push, 3 )

#pragma warning ( disable: 4710 )

#include < windows.h >

#include < ddraw.h   >

#include < cassert  >
#include < crtdbg.h >
#include < cfloat   >
#include < cmath    >
#include < cstdio   >
#include < ctime    >

#include < iostream >
#include < string   >
#include < queue    >

using namespace std;

#include "list object.h"
#include "list client.h"

#include "font.h"

#include "particle client.h"

// We do not care about inlining, so turn off the warning
// that tells us that functions have not been inlined.
#pragma warning ( disable : 4710 )

static int Error( const char * const errorString
                );

static int mainTerm( HWND hwnd
                   );

static int RemoveHeapAllocation( void *heapAllocation
                               );

static void* InsertHeapAllocation( size_t numBytesToAllocate
                                 );

static int InsertHandle( void *handle
                       );

static int RemoveHandle( void *handle
                       );

static INDEX_TYPE TestObject( CLIENT_POTYPE ClientObject1,
                              CLIENT_POTYPE ClientObject2
                            )
{
   if( ClientObject1.object == 0 || ClientObject2.object == 0 )
   {
      Error( " ClientObject.object == NULL " );
      
      return 0;
   }
   else if( ClientObject1.object == ClientObject2.object )
   {
      return 1;
   }
   
   return 0;
}

// statics are initialized to 0, I explicitly type it here
// for readability and emphasis
static FILE *file = 0;

static int numErrors = 0, numWarnings = 0;

static int ErrorBox( const char * const errorString
                   )
{
   char ErrorString1[ 514 ] = { 0 };
   char ErrorString2[ 514 ] = { 0 };
   
   if( ( !errorString ) || ( !( *errorString ) ) )
   {
      assert( " ErrorBox -- errorString " && 0 );
      
      return -1;
   }
   
   ++numErrors;
   
   if( _snprintf( ErrorString1, 512, "Error#  : %i\n",   numErrors   ) < 0 )
   {
      assert( " _snprintf(...) failure -- fatal low level system error " && 0 );
      
      return -1;
   }
   
   if( _snprintf( ErrorString2, 512, "Error   : %s\n\n", errorString ) < 0 )
   {
      assert( " _snprintf(...) failure -- fatal low level system error " && 0 );
      
      return -1;
   }
   
   if( MessageBox( 0,
                   ErrorString2,
                   ErrorString1,
                   MB_ICONERROR | MB_OK
                 ) == 0
     )
   {
      assert( " MessageBox(...) failure " && 0 );
   }
   
   return 0;
}

static int Error( const char * const errorString
                )
{
   if( file && file != ( (FILE*) 0xff ) )
   {	
      if( ( !errorString ) || ( !( *errorString ) ) )
      {
         assert( " Error -- errorString " && 0 );
         
         return -1;
      }
      
      ++numErrors;
      
      if( fprintf( file, "Error#  : %i\n",  numErrors   ) < 0 )
      {
         --numErrors;
         
         ErrorBox( errorString );
         
         ErrorBox( " fprintf(...) failure -- fatal low level system error " );
         
         return -1;
      }
      
      if( fprintf( file, "Error   : %s\n\n", errorString ) < 0 )
      {
         --numErrors;
         
         ErrorBox( errorString );
         
         ErrorBox( " fprintf(...) failure -- fatal low level system error " );
      }
   }

#ifndef NDEBUG

   else
   {
      ErrorBox( " Error -- file == NULL " );
      
      ErrorBox( errorString );
   }

#endif
   
   return 0;
}

static int Warning( const char * const warningString
                  )
{
   if( file && file != ( (FILE*) 0xff ) )
   {	
      if( ( !warningString ) || ( !( *warningString ) ) )
      {
         assert( " Warning -- warningString " && 0 );
         
         return -1;
      }
      
      ++numWarnings;
      
      if( fprintf( file, "Warning#  : %i\n",  numWarnings   ) < 0 )
      {
         --numWarnings;
         
         // If fprintf fails load up the warning as an error.
         ErrorBox( warningString );
         
         ErrorBox( " fprintf(...) failure -- fatal low level system error " );
         
         return -1;
      }
      
      if( fprintf( file, "Warning   : %s\n\n", warningString ) < 0 )
      {
         --numWarnings;
         
         // If fprintf fails load up the warning as an error.
         ErrorBox( warningString );
         
         ErrorBox( " fprintf(...) failure -- fatal low level system error " );
      }
   }

#ifndef NDEBUG

   else
   {
      ErrorBox( " Error -- file == NULL " );
      
      // If file == NULL then treat the warning as an error.
      ErrorBox( warningString );
   }

#endif
   
   return 0;
}


class Graphics
{
   friend class WindowStyle;

public:
   
   enum
   {
      GRAPHICS_ERROR  = 0xffffffff,
      GRAPHICS_OK     = 0,
      GRAPHICS_WINDOW,
      GRAPHICS_FULLSCREEN
   };

   static BOOL CALLBACK AboutDlgProc( HWND hDlg,
                                      UINT msg,
                                      WPARAM wParam,
                                      LPARAM lParam
                                    );
   
   static BOOL CALLBACK InputDlgProc( HWND hDlg,
                                      UINT msg,
                                      WPARAM wParam,
                                      LPARAM lParam
                                    );
   
   static LRESULT CALLBACK WindowProc( HWND   hwnd,
                                       UINT   msg,
                                       WPARAM wParam,
                                       LPARAM lParam
                                     );
   
   static void RenderPoint32( int x0,
                              int y0,
                              int c0
                            );
   
   static void RenderLine32( int x0,
                             int y0,
                             int x1,
                             int y1,
                             int c0,
                             int c1
                           );
   
   static void RenderCircle32( int x0,
                               int y0,
                               int r0,
                               int c0,
                               int c1
                             );
   
private:
   
   typedef enum GRAPHICS_IMPLEMENTATION
   {
      GDI = 0,
      DIRECTDRAW
         
   }GRAPHICS_IMPLEMENTATION;
   
   // Here we keep track of the current graphics mode
   // we are in.
   //
   // We will try for Direct Draw, but
   // that never works anyway, so the solid
   // GDI foundation is always there to catch us.
   static Graphics::GRAPHICS_IMPLEMENTATION Implementation;
   
   
   static IDirectDraw *ddraw_obj;
   
   static IDirectDrawClipper *ddraw_screenclipper;
   
   static IDirectDrawSurface *ddraw_screen;
   
   static IDirectDrawSurface *ddraw_backbuffer;
   
   
   // If we want to be nice then we won't try to change
   // the bit depth on the user.
   static bool beNice;
   
   // If we are not nice and really mean we can
   // try to force full screen mode onto the user.
   static bool forceFullScreen;
   
   static bool isModeChangeActive;
   
   static int width, height, bitDepth;
   
   static int oldWidth, oldHeight, oldBitDepth;
   
   static char **backbufferArray;
   
   
   static HDC     backbufferDC;
   static HBITMAP backbufferBitmapHB;
   static HGDIOBJ backbufferCleanUp;
   
   
   static HWND    _hWindow;
   
   
   // These function prototypes are used to stop class instantiation.
   Graphics(
           )
   {
   }

   Graphics( Graphics&
           )
   {
   }

   virtual ~Graphics(
                    ) = 0;

   virtual Graphics& operator=( Graphics&
                              ) = 0;
   //////////////////////////////////////////////////////////////////
   
   static GRAPHICS_IMPLEMENTATION graphicsImplementation(
                                                        )
   {
      return Implementation;
   }
   
   static void graphicsSafeMode(
                               )
   {
      unsigned short widthHeight[ 2 ] = { 0 };
      
      if( !( Graphics::_hWindow ) )
      {
         return;
      }
      
      Graphics::graphicsTermScreenAndBackBuffer();
      
      widthHeight[ 0 ] = (unsigned short) Graphics::oldWidth;
      widthHeight[ 1 ] = (unsigned short) Graphics::oldHeight;
      
      Graphics::Implementation = GDI;
      
      Graphics::WindowProc( Graphics::_hWindow,
                            WM_DISPLAYCHANGE,
                            Graphics::oldBitDepth,
                            *( (unsigned long*) widthHeight )
                          );
   }
   
public:
   
   static bool graphicsIsModeChangeActive(
                                         )
   {
      return isModeChangeActive;
   }
   
   static int graphicsWidth(
                           )
   {
      return width;
   }

   static int graphicsHeight(
                            )
   {
      return height;
   }
   
   static int graphicsClientWidth(
                                 )
   {
      return width;
   }

   static int graphicsClientHeight(
                                  )
   {
      return height;
   }
   
   static char** graphicsBackBufferFunction(
                                           )
   {
      return backbufferArray;
   }

   
   static int graphicsUnlockBackBuffer(
                                      )
   {
      switch( graphicsImplementation() )
      {
      case GDI:
         {
            return GRAPHICS_OK;
         }

      case DIRECTDRAW:
         {
            HRESULT hResult = 0;
            
            hResult = ddraw_backbuffer->Unlock( backbufferArray[ 0 ] );
            
            if( FAILED( hResult ) )
            {
               Error( " IDirectDrawSurface::Unlock(...) has failed for the back buffer. " );
               
               graphicsSafeMode();
               
               return GRAPHICS_ERROR;
            }

            return GRAPHICS_OK;
         }
      }
      
      Error( " The OS code is using an invalid graphics implementation. " );
      
      return GRAPHICS_ERROR;
   }
   
   static int graphicsLockBackBuffer(
                                    )
   {
      switch( graphicsImplementation() )
      {
      case GDI:
         {
            // Flush GDI before testing the back buffer.
            if( !GdiFlush() )
            {
               Error( " GdiFlush(...) function failure " );
               
               return GRAPHICS_ERROR;
            }

            return GRAPHICS_OK;
         }
         
      case DIRECTDRAW:
         {
            int loop = 0;
            
            DDSURFACEDESC ddsd = { 0 };
            
            HRESULT hResult = 0;
            
            ddsd.dwSize = sizeof(DDSURFACEDESC);
            
            hResult = ddraw_backbuffer->Lock( 0,
                                              &ddsd,
                                              DDLOCK_SURFACEMEMORYPTR |
                                              DDLOCK_WAIT,
                                              0
                                            );

            if( FAILED( hResult ) )
            {
               Error( " IDirectDrawSurface::Lock(...) has failed for the back buffer. " );
               
               graphicsSafeMode();
               
               return GRAPHICS_ERROR;
            }
            
            if( backbufferArray[ 0 ] != ddsd.lpSurface ||
                backbufferArray[ 1 ] != ( (char*) ddsd.lpSurface ) + ddsd.lPitch
              )
            {
               backbufferArray[ 0 ] = (char*) ddsd.lpSurface;
               
               loop = 1;
               
               do
               {
                  backbufferArray[ loop ] = backbufferArray[ loop - 1 ] + ddsd.lPitch;
                  
               }while( ++loop != graphicsClientHeight() );
            }

            return GRAPHICS_OK;
         }
      }
      
      Error( " The OS code is using an invalid graphics implementation. " );
      
      return GRAPHICS_ERROR;
   }
   
   static int graphicsClearBackBuffer(
                                     )
   {
      switch( graphicsImplementation() )
      {
      case GDI:
         {
            // Clear back buffer.
            if( !BitBlt( backbufferDC,
                         0,
                         0,
                         graphicsClientWidth(),
                         graphicsClientHeight(),
                         0,
                         0,
                         0,
                         BLACKNESS
                       )
              )
            {
               Error( " BitBlt(...) function failure " );
               
               return GRAPHICS_ERROR;
            }

            return GRAPHICS_OK;
         }

      case DIRECTDRAW:
         {
            DDBLTFX ddfx = { 0 };
            
            HRESULT hResult = 0;
            
            ddfx.dwSize = sizeof(DDBLTFX);
            
            ddfx.dwFillColor = 0x00000000;
            
            hResult = ddraw_backbuffer->Blt( 0, 0, 0, DDBLT_COLORFILL | DDBLT_WAIT, &ddfx );
            
            if( FAILED( hResult ) )
            {
               Error( " ddraw_backbuffer->Blt(...) function failure " );
               
               graphicsSafeMode();
               
               return GRAPHICS_ERROR;
            }

            return GRAPHICS_OK;
         }
      }
      
      Error( " The OS code is using an invalid graphics implementation. " );
      
      return GRAPHICS_ERROR;
   }
   
   static int graphicsDrawBackBufferToScreen( HWND hWindow
                                            )
   {
      switch( graphicsImplementation() )
      {
      case GDI:
         {
            HDC screen = 0;
            
            // Get the screen handle so we can blt to the screen.
            screen = GetDC( hWindow );
            
            if( screen == NULL )
            {
               Error( " ( screen = GetDC( hWindow ) ) == NULL " );
               
               return GRAPHICS_ERROR;
            }
            
            if( !StretchBlt( screen,
                             0,
                             0,
                             graphicsWidth(),
                             graphicsHeight(),
                             backbufferDC,
                             0,
                             0,
                             graphicsClientWidth(),
                             graphicsClientHeight(),
                             SRCCOPY
                           )
              )
            {
               Error( " StretchBlt(...) function failure " );
               
               if( ReleaseDC( hWindow, screen ) != 1 )
               {
                  Error( " ReleaseDC(...) function failure " );
               }
               
               return GRAPHICS_ERROR;
            }
            
            // Release the screen handle.
            if( ReleaseDC( hWindow, screen ) != 1 )
            {
               Error( " ReleaseDC(...) function failure " );
               
               return GRAPHICS_ERROR;
            }

            return GRAPHICS_OK;
         }
         
      case DIRECTDRAW:
         {
            RECT rectBackBuffer = { 0 }, rectScreen = { 0 };
            
            HRESULT hResult = 0;
            
            if( !ClientToScreen( hWindow, (POINT*) &rectScreen ) )
            {
               Error( " The function ClientToScreen(...) has failed. " );
               
               return GRAPHICS_ERROR;
            }
            
            rectBackBuffer.right  = graphicsClientWidth();
            rectBackBuffer.bottom = graphicsClientHeight();
            
            rectScreen.left   = rectScreen.left;
            rectScreen.top    = rectScreen.top;
            
            rectScreen.right  = rectScreen.left + graphicsWidth();
            rectScreen.bottom = rectScreen.top  + graphicsHeight();
            
            hResult = ddraw_screen->Blt( &rectScreen, ddraw_backbuffer, &rectBackBuffer, DDBLT_WAIT, 0 );
            
            if( FAILED( hResult ) )
            {
               Error( " ddraw_screen->Blt(...) function failure " );
               
               graphicsSafeMode();
               
               return GRAPHICS_ERROR;
            }

            return GRAPHICS_OK;
         }
      }
      
      Error( " The OS code is using an invalid graphics implementation. " );
      
      return GRAPHICS_ERROR;
   }
   
private:
   
   static int graphicsSaveOldMode(
                                 )
   {
      HDC screen = 0;
      
      screen = GetDC( 0 );
      
      if( screen == NULL )
      {
         Error( " ( screen = GetDC( 0 ) ) == NULL " );
         
         return GRAPHICS_ERROR;
      }
      
      oldWidth    = GetDeviceCaps( screen, HORZRES );
      
      oldHeight   = GetDeviceCaps( screen, VERTRES );
      
      oldBitDepth = GetDeviceCaps( screen, BITSPIXEL );
      
      bitDepth = oldBitDepth;
      
      if( ReleaseDC( 0, screen ) != 1 )
      {
         Error( " ReleaseDC(...) function failure " );
      }
      
      if( oldWidth <= 0 || oldHeight <= 0 )
      {
         return GRAPHICS_ERROR;
      }
      
      return GRAPHICS_OK;
   }
      
   static int graphicsRestoreOldMode(
                                    )
   {
      DEVMODE DMode      = { 0 };
      
      DMode.dmSize       = sizeof( DEVMODE );
      
      DMode.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
      
      DMode.dmBitsPerPel = oldBitDepth;
      DMode.dmPelsWidth  = oldWidth;
      DMode.dmPelsHeight = oldHeight;
      
      isModeChangeActive = true;
      
      if( ChangeDisplaySettings( &DMode, 0 ) != DISP_CHANGE_SUCCESSFUL )
      {
         Error( " The function ChangeDisplaySettings(...) has failed. " );
         
         isModeChangeActive = false;
         
         return GRAPHICS_ERROR;
      }
      
      isModeChangeActive = false;
      
      return GRAPHICS_OK;
   }
   
   static int graphicsSetBitDepthTo32(
                                     )
   {
      DEVMODE DMode  = { 0 };
      
      if( ( oldWidth >= graphicsWidth() || oldHeight >= graphicsHeight() ) &&
          oldBitDepth == 32 && forceFullScreen == false
        )
      {
         return GRAPHICS_OK;
      }
      
      DMode.dmSize   = sizeof(DEVMODE);
      
      DMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
      
      if(  oldWidth <= graphicsWidth() && oldHeight <= graphicsHeight() )
      {
         DMode.dmPelsWidth  = graphicsWidth();
         DMode.dmPelsHeight = graphicsHeight();
      }
      else
      {
         if( forceFullScreen == true )
         {
            DMode.dmPelsWidth  = graphicsWidth();
            DMode.dmPelsHeight = graphicsHeight();
         }
         else
         {
            DMode.dmPelsWidth  = oldWidth;
            DMode.dmPelsHeight = oldHeight;
         }
      }
      
      DMode.dmBitsPerPel = 32;
      
      isModeChangeActive = true;
      
      if( ChangeDisplaySettings( &DMode, 0 ) != DISP_CHANGE_SUCCESSFUL )
      {
         Warning( " The function ChangeDisplaySettings(...) has failed for 32 bit pixel depth. " );
         
         isModeChangeActive = false;
         
         return GRAPHICS_ERROR;
      }
      
      bitDepth = 32;
      
      isModeChangeActive = false;
      
      return GRAPHICS_OK;
   }
      
   static int graphicsLoadBitmap( HDC destination,
                                  int destinationWidth,
                                  int destinationHeight,
                                  char *sourceFileName
                                )
   {
      int error = GRAPHICS_OK;
   
      int sourceWidth  = 0,
          sourceHeight = 0;
   
      FILE *file = 0;
   
      BITMAPFILEHEADER BHeader = { 0 };
      BITMAPINFO       BInfo   = { 0 };
   
      HDC     BltDC   = 0;
   
      HBITMAP BltHB   = 0;
   
      HGDIOBJ CleanUp = 0;
   
   
      BltDC = CreateCompatibleDC( 0 );
   
      InsertHandle( BltDC );
   
      if( BltDC == NULL )
      {
         Error( " ( BltDC = CreateCompatibleDC(...) ) == NULL " );
      
         return GRAPHICS_ERROR;
      }
   
   
      file = fopen( sourceFileName, "rb" );
   
      InsertHandle( file );
   
      if( !file )
      {
         Error( " ( file = fopen(...) ) == NULL " );
      
         if( !DeleteDC( BltDC ) )
         {
            Error( " DeleteDC(...) function failure " );
         }
         else
         {
            RemoveHandle( BltDC );
         }
      
         return GRAPHICS_ERROR;
      }
   
      if( fread( &BHeader, sizeof(BITMAPFILEHEADER), 1, file ) != 1 )
      {
         Error( " fread(...) error " );
      
         if( fclose( file ) != 0 )
         {
            Error( " fclose(...) error " );
         }
         else
         {
            RemoveHandle( file );
         }
      
         if( !DeleteDC( BltDC ) )
         {
            Error( " DeleteDC(...) function failure " );
         }
         else
         {
            RemoveHandle( BltDC );
         }
      
         return GRAPHICS_ERROR;
      }
   
      if( fread( &BInfo, sizeof(BITMAPINFO), 1, file ) != 1 )
      {
         Error( " fread(...) error " );
      
         if( fclose( file ) != 0 )
         {
            Error( " fclose(...) error " );
         }
         else
         {
            RemoveHandle( file );
         }
      
         if( !DeleteDC( BltDC ) )
         {
            Error( " DeleteDC(...) function failure " );
         }
         else
         {
            RemoveHandle( BltDC );
         }
      
         return GRAPHICS_ERROR;
      }
   
      sourceWidth  = BInfo.bmiHeader.biWidth;
      sourceHeight = BInfo.bmiHeader.biHeight;
   
      if( sourceWidth <= 0 || sourceHeight <= 0 )
      {
         Error( " fread(...) error " );
      
         if( fclose( file ) != 0 )
         {
            Error( " fclose(...) error " );
         }
         else
         {
            RemoveHandle( file );
         }
      
         if( !DeleteDC( BltDC ) )
         {
            Error( " DeleteDC(...) function failure " );
         }
         else
         {
            RemoveHandle( BltDC );
         }
      
         return GRAPHICS_ERROR;
      }
   
      if( fclose( file ) != 0 )
      {
         Error( " fclose(...) error " );
      
         error = GRAPHICS_ERROR;
      }
      else
      {
         RemoveHandle( file );
      }

   
      BltHB = (HBITMAP) LoadImage( NULL,
                                   sourceFileName,
                                   IMAGE_BITMAP,
                                   0,
                                   0,
                                   LR_LOADFROMFILE | LR_CREATEDIBSECTION
								         );
   
      InsertHandle( BltHB );
   
      if( BltHB == NULL )
      {
         Error( " ( BltHB = LoadImage(...) ) == NULL " );
      
         if( !DeleteDC( BltDC ) )
         {
            Error( " DeleteDC(...) function failure " );
         }
         else
         {
            RemoveHandle( BltDC );
         }
      
         return GRAPHICS_ERROR;
      }
   
      CleanUp = SelectObject( BltDC, BltHB );
   
      InsertHandle( CleanUp );
   
      if( CleanUp == NULL || ( (const unsigned long) CleanUp ) == GDI_ERROR )
      {
         Error( " ( CleanUp = SelectObject(...) ) == NULL " );
      
         if( !DeleteObject( BltHB ) )
         {
            Error( " DeleteObject(..) function failure " );
         }
      
         if( !DeleteDC( BltDC ) )
         {
            Error( " DeleteDC(...) function failure " );
         }
         else
         {
            RemoveHandle( BltDC );
         }
      
         return GRAPHICS_ERROR;
      }
   
      if( !StretchBlt( destination,
                       0,
                       0,
                       destinationWidth,
                       destinationHeight,
                       BltDC,
                       0,
                       0,
                       sourceWidth,
                       sourceHeight,
                       SRCCOPY
                     )
        )
      {
         Error( " StretchBlt failure " );
      
         error = GRAPHICS_ERROR;
      }
   
      HGDIOBJ deviceTempCleanUp = 0;
   
      if( BltDC != 0 )
      {
         // Free all the GDI objects.
         deviceTempCleanUp = SelectObject( BltDC, CleanUp );
      
         if( deviceTempCleanUp == NULL || ( (const unsigned long) deviceTempCleanUp ) == GDI_ERROR )
         {
            Error( " ( deviceTempCleanUp = SelectObject(...) ) == NULL " );
         
            error = GRAPHICS_ERROR;
         }
         else
         {
            RemoveHandle( CleanUp );
         }
      
         if( !DeleteObject( BltHB ) )
         {
            Error( " DeleteObject(..) function failure " );
         
            error = GRAPHICS_ERROR;
         }
         else
         {
            RemoveHandle( BltHB );
         }
      
         if( !DeleteDC( BltDC ) )
         {
            Error( " DeleteDC(...) function failure " );
         
            error = GRAPHICS_ERROR;
         }
         else
         {
            RemoveHandle( BltDC );
         }
      }	
   
      return error;
   }
   
   static int graphicsTermScreenAndBackBufferGDI(
                                                )
   {
      int error = GRAPHICS_OK;
      
      HGDIOBJ TempCleanUp = 0;
      
      if( backbufferDC != 0 )
      {
         // Free all the GDI objects.
         TempCleanUp = SelectObject( backbufferDC, backbufferCleanUp );
         
         if( TempCleanUp == NULL || ( (const unsigned long) TempCleanUp ) == GDI_ERROR )
         {
            Error( " ( TempCleanUp = SelectObject(...) ) == NULL " );
            
            error = GRAPHICS_ERROR;
         }
         else
         {
            RemoveHandle( backbufferCleanUp );
         }
         
         if( !DeleteObject( backbufferBitmapHB ) )
         {
            Error( " DeleteObject(..) function failure " );
            
            error = GRAPHICS_ERROR;
         }
         else
         {
            RemoveHandle( backbufferBitmapHB );
         }
         
         if( !DeleteDC( backbufferDC ) )
         {
            Error( " DeleteDC(...) function failure " );
            
            error = GRAPHICS_ERROR;
         }
         else
         {
            RemoveHandle( backbufferDC );
         }
         
         backbufferDC       = 0;
         backbufferCleanUp  = 0;
         backbufferBitmapHB = 0;
      }
      
      return error;
   }
   
   static int graphicsTermScreenAndBackBufferDIRECTDRAW(
                                                       )
   {
      int error = GRAPHICS_OK;
      
      HRESULT hResult = 0;
      
      if( ddraw_backbuffer )
      {
         hResult = ddraw_backbuffer->Release();
         
         ddraw_backbuffer = 0;
         
         if( FAILED( hResult ) )
         {
            Error( " The DirectDraw back buffer object failed to release correctly. " );
            
            error = GRAPHICS_ERROR;
         }
      }
      
      if( ddraw_screen )
      {
         hResult = ddraw_screen->Release();
         
         ddraw_screen = 0;
         
         if( FAILED( hResult ) )
         {
            Error( " The DirectDraw screen object failed to release correctly. " );
            
            error = GRAPHICS_ERROR;
         }
      }
      
      if( ddraw_screenclipper )
      {
         hResult = ddraw_screenclipper->Release();
         
         ddraw_screenclipper = 0;
         
         if( FAILED( hResult ) )
         {
            Error( " The DirectDraw screen clipper object failed to release correctly. " );
            
            error = GRAPHICS_ERROR;
         }
      }
      
      if( ddraw_obj )
      {
         hResult = ddraw_obj->Release();
         
         ddraw_obj = 0;
         
         if( FAILED( hResult ) )
         {
            Error( " The DirectDraw main object failed to release correctly. " );
            
            error = GRAPHICS_ERROR;
         }
      }
      
      return error;
   }
      
public:
   
   static int graphicsTermScreenAndBackBuffer(
                                             )
   {
      int error = GRAPHICS_OK;
      
      switch( graphicsImplementation() )
      {
      case GDI:
         {
            error = graphicsTermScreenAndBackBufferGDI();
            
            graphicsRestoreOldMode();
            
            if( backbufferArray )
            {
               RemoveHeapAllocation( backbufferArray );
               
               backbufferArray = 0;
            }
            
            return error;
         }
         
      case DIRECTDRAW:
         {
            error = graphicsTermScreenAndBackBufferDIRECTDRAW();
            
            graphicsRestoreOldMode();
            
            if( backbufferArray )
            {
               RemoveHeapAllocation( backbufferArray );
               
               backbufferArray = 0;
            }
            
            return error;
         }
      }
      
      Error( " The OS code is using an invalid graphics implementation. " );
      
      return GRAPHICS_ERROR;
   }
      
private:
      
   static int graphicsInitScreenAndBackBufferGDI( HWND hWindow
                                                )
   {
      int        loop   =   0;
      
      BITMAPINFO bInfo  = { 0 };
      
      if( backbufferDC || backbufferCleanUp || backbufferBitmapHB )
      {
         return 0;
      }
      
      bInfo.bmiHeader.biBitCount	   = 32;
      bInfo.bmiHeader.biWidth		   = graphicsClientWidth();
      bInfo.bmiHeader.biHeight	   = graphicsClientHeight();
      bInfo.bmiHeader.biPlanes	   = 1;
      bInfo.bmiHeader.biSize		   = sizeof( BITMAPINFOHEADER );
      bInfo.bmiHeader.biCompression = BI_RGB;
      
      // Create the permanent container for the bitmap.
      backbufferDC = CreateCompatibleDC( 0 );
      
      if( backbufferDC == NULL )
      {
         Error( " ( backbufferDC = CreateCompatibleDC(...) ) == NULL " );
         
         return GRAPHICS_ERROR;
      }
      
      InsertHandle( backbufferDC );
      
      // Create the bitmap, which will be used as the backbuffer.
      backbufferBitmapHB = CreateDIBSection( backbufferDC, 
                                             &bInfo,
                                             DIB_RGB_COLORS,
                                             (void**) &backbufferArray[ graphicsClientHeight() - 1 ],
                                             0,
                                             0
                                           );
      
      if( backbufferBitmapHB == NULL || backbufferArray[ graphicsClientHeight() - 1 ] == NULL )
      {
         Error( " ( backbufferBitmapHB = CreateDIBSection(...) ) == NULL " );
         
         if( !DeleteDC( backbufferDC ) )
         {
            Error( " DeleteDC(...) function failure " );
         }
         else
         {
            RemoveHandle( backbufferDC );
         }
         
         backbufferDC = 0;
         
         return GRAPHICS_ERROR;
      }
      
      InsertHandle( backbufferBitmapHB );
      
      // Keep the clean up object, so we can store it back
      // into the container when we take the bitmap out.
      backbufferCleanUp = SelectObject( backbufferDC, backbufferBitmapHB );
      
      if( backbufferCleanUp == NULL || ( (const unsigned long) backbufferCleanUp ) == GDI_ERROR )
      {
         Error( " ( backbufferCleanUp = SelectObject(...) ) == NULL " );
         
         if( !DeleteObject( backbufferBitmapHB ) )
         {
            Error( " DeleteObject(..) function failure " );
         }
         else
         {
            RemoveHandle( backbufferBitmapHB );
         }
         
         if( !DeleteDC( backbufferDC ) )
         {
            Error( " DeleteDC(...) function failure " );
         }
         else
         {
            RemoveHandle( backbufferDC );
         }
         
         backbufferDC       = 0;
         backbufferBitmapHB = 0;
         
         return GRAPHICS_ERROR;
      }
      
      InsertHandle( backbufferCleanUp );
      
      // Set up the back buffer pointer array.
      for( loop = graphicsClientHeight() - 2; loop >= 0; loop-- )
      {
         backbufferArray[ loop ] = backbufferArray[ loop + 1 ] + graphicsClientWidth() * 4;
      }
      
      graphicsClearBackBuffer();

      TextOutInitSystem( Graphics::graphicsBackBufferFunction,
                         Graphics::graphicsClientWidth(),
                         Graphics::graphicsClientHeight(),
                         Graphics::graphicsWidth(),
                         Graphics::graphicsHeight()
					        );
   
      ParticleSystemsInitGraphics( Graphics::graphicsBackBufferFunction()[ 0 ],
                                   Graphics::graphicsClientWidth(),
                                   Graphics::graphicsClientHeight(),
                                   32,
                                   -( ( Graphics::graphicsClientWidth() * 4 + 3 ) & ~3 )
                                 );
      
      graphicsLockBackBuffer();

      TextOut( 10, 10, "Press F8 for help" );
      
      graphicsUnlockBackBuffer();
      
      graphicsDrawBackBufferToScreen( hWindow );
      
      return GRAPHICS_OK;
   }
      
   static int graphicsInitScreenAndBackBufferDIRECTDRAW( HWND hWindow
                                                       )
   {
      DDSURFACEDESC ddsd = { 0 };
      
      HRESULT hResult = 0;
      
      ddsd.dwSize = sizeof(DDSURFACEDESC);
      
      if( ddraw_obj || ddraw_screen || ddraw_screenclipper || ddraw_backbuffer )
      {
         return GRAPHICS_OK;
      }
      
      // Initialize the direct draw interface.
      hResult = DirectDrawCreate( 0, &ddraw_obj, 0 );
      
      if( FAILED( hResult ) )
      {
         Error( " The function DirectDrawCreate(...) has failed. " );
         
         return GRAPHICS_ERROR;
      }
      
      hResult = ddraw_obj->SetCooperativeLevel( hWindow, DDSCL_NORMAL );
      
      if( FAILED( hResult ) )
      {
         Error( " The function SetCooperativeLevel(...) has failed. " );
         
         hResult = ddraw_obj->Release();
         
         ddraw_obj = 0;
         
         if( FAILED( hResult ) )
         {
            Error( " The DirectDraw main object failed to release correctly. " );
         }
         
         return GRAPHICS_ERROR;
      }
      
      // Gain access to the screen surface.
      ddsd.dwFlags        = DDSD_CAPS;
      
      ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
      
      hResult = ddraw_obj->CreateSurface( &ddsd, &ddraw_screen, 0 );
      
      if( FAILED( hResult ) )
      {
         Error( " The function CreateSurface(...) has failed while trying to create the screen surface. " );
         
         hResult = ddraw_obj->Release();
         
         ddraw_obj = 0;
         
         if( FAILED( hResult ) )
         {
            Error( " The DirectDraw main object failed to release correctly. " );
         }
         
         return GRAPHICS_ERROR;
      }
      
      // Create the clipper object which will be used on the screen surface.
      hResult = ddraw_obj->CreateClipper( 0, &ddraw_screenclipper, 0 );
      
      if( FAILED( hResult ) )
      {
         Error( " The function CreateClipper(...) has failed while trying to create the screen clipper object. " );
         
         hResult = ddraw_screen->Release();
         
         ddraw_screen = 0;
         
         if( FAILED( hResult ) )
         {
            Error( " The DirectDraw screen object failed to release correctly. " );
         }
         
         hResult = ddraw_obj->Release();
         
         ddraw_obj = 0;
         
         if( FAILED( hResult ) )
         {
            Error( " The DirectDraw main object failed to release correctly. " );
         }
         
         return GRAPHICS_ERROR;
      }
      
      // Associate the clipper to our client window.
      hResult = ddraw_screenclipper->SetHWnd( 0, hWindow );
      
      if( FAILED( hResult ) )
      {
         Error( " The function SetHWnd(...) has failed for the screen clipper object. " );
         
         hResult = ddraw_screenclipper->Release();
         
         ddraw_screenclipper = 0;
         
         if( FAILED( hResult ) )
         {
            Error( " The DirectDraw screen clipper object failed to release correctly. " );
         }
         
         hResult = ddraw_screen->Release();
         
         ddraw_screen = 0;
         
         if( FAILED( hResult ) )
         {
            Error( " The DirectDraw screen object failed to release correctly. " );
         }
         
         hResult = ddraw_obj->Release();
         
         ddraw_obj = 0;
         
         if( FAILED( hResult ) )
         {
            Error( " The DirectDraw main object failed to release correctly. " );
         }
         
         return GRAPHICS_ERROR;
      }
      
      // Clip the screen surface to the client window.
      hResult = ddraw_screen->SetClipper( ddraw_screenclipper );
      
      if( FAILED( hResult ) )
      {
         Error( " The function SetClipper(...) has failed for the screen surface. " );
         
         hResult = ddraw_screenclipper->Release();
         
         ddraw_screenclipper = 0;
         
         if( FAILED( hResult ) )
         {
            Error( " The DirectDraw screen clipper object failed to release correctly. " );
         }
         
         hResult = ddraw_screen->Release();
         
         ddraw_screen = 0;
         
         if( FAILED( hResult ) )
         {
            Error( " The DirectDraw screen object failed to release correctly. " );
         }
         
         hResult = ddraw_obj->Release();
         
         ddraw_obj = 0;
         
         if( FAILED( hResult ) )
         {
            Error( " The DirectDraw main object failed to release correctly. " );
         }
         
         return GRAPHICS_ERROR;
      }
      
      // Create the backbuffer surface.
      ddsd.dwFlags        = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
      
      ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
      
      ddsd.dwWidth        = graphicsClientWidth();
      
      ddsd.dwHeight       = graphicsClientHeight();
      
      hResult = ddraw_obj->CreateSurface( &ddsd, &ddraw_backbuffer, 0 );
      
      if( FAILED( hResult ) || FAILED( ddraw_backbuffer->GetSurfaceDesc( &ddsd ) ) )
      {
         Error( " The function CreateSurface(...) has failed while trying to create the back buffer surface. " );
         
         hResult = ddraw_screen->Release();
         
         ddraw_screen = 0;
         
         if( FAILED( hResult ) )
         {
            Error( " The DirectDraw screen object failed to release correctly. " );
         }
         
         hResult = ddraw_screenclipper->Release();
         
         ddraw_screenclipper = 0;
         
         if( FAILED( hResult ) )
         {
            Error( " The DirectDraw screen clipper object failed to release correctly. " );
         }
         
         hResult = ddraw_obj->Release();
         
         ddraw_obj = 0;
         
         if( FAILED( hResult ) )
         {
            Error( " The DirectDraw main object failed to release correctly. " );
         }
         
         return GRAPHICS_ERROR;
      }
      
      graphicsClearBackBuffer();

      TextOutInitSystem( Graphics::graphicsBackBufferFunction,
                         Graphics::graphicsClientWidth(),
                         Graphics::graphicsClientHeight(),
                         Graphics::graphicsWidth(),
                         Graphics::graphicsHeight()
					        );
   
      ParticleSystemsInitGraphics( Graphics::graphicsBackBufferFunction()[ 0 ],
                                   Graphics::graphicsClientWidth(),
                                   Graphics::graphicsClientHeight(),
                                   32,
                                   ddsd.lPitch
                                 );
      
      graphicsLockBackBuffer();

      TextOut( 10, 10, "Press F8 for help" );
      
      graphicsUnlockBackBuffer();
      
      graphicsDrawBackBufferToScreen( hWindow );
      
      return GRAPHICS_OK;
   }
      
public:
      
   static int graphicsInitScreenAndBackBuffer( HWND hWindow
                                             )
   {
      Graphics::_hWindow = hWindow;
      
      graphicsSaveOldMode();
      
      if( beNice == false )
      {
         graphicsSetBitDepthTo32();
      }
      
      if( bitDepth != 32 )
      {
         Implementation = GDI;
      }
      
      if( bitDepth <= 0 )
      {
         bitDepth = oldBitDepth;
      }
      
      if( !backbufferArray )
      {
         backbufferArray = (char**) InsertHeapAllocation( sizeof(char*) * graphicsClientHeight() );
      }
      
      if( !backbufferArray )
      {
         return GRAPHICS_ERROR;
      }
      
      switch( graphicsImplementation() )
      {
      case GDI:
         {
            return graphicsInitScreenAndBackBufferGDI( hWindow );
         }
         
      case DIRECTDRAW:
         {
            if( graphicsInitScreenAndBackBufferDIRECTDRAW( hWindow ) != 0 )
            {
               Implementation = GDI;
               
               return graphicsInitScreenAndBackBuffer( hWindow );
            }
            else
            {
               return GRAPHICS_OK;
            }
         }
      }
      
      Error( " The OS code is using an invalid graphics implementation. " );
      
      return GRAPHICS_ERROR;
   }
      
   static int graphicsCheckIsFullScreen(
                                       )
   {
      int screenWidth    = 0,
          screenHeight   = 0,
          screenBitDepth = 0;
      
      HDC screen = 0;
      
      screen = GetDC( 0 );
      
      if( screen == NULL )
      {
         Error( " ( screen = GetDC( 0 ) ) == NULL " );
         
         return GRAPHICS_ERROR;
      }
      
      screenWidth    = GetDeviceCaps( screen, HORZRES );
      
      screenHeight   = GetDeviceCaps( screen, VERTRES );
      
      screenBitDepth = GetDeviceCaps( screen, BITSPIXEL );
      
      if( ReleaseDC( 0, screen ) != 1 )
      {
         Error( " ReleaseDC(...) function failure " );
      }
      
      if( screenWidth  <= 0 || screenHeight <= 0 || screenBitDepth <= 0 )
      {
         return GRAPHICS_ERROR;
      }
      
      if( ( screenWidth <= graphicsWidth() && screenHeight <= graphicsHeight() ) ||
          ( beNice == false && forceFullScreen == true )
        )
      {
         int  modeTestCounter = 0;
         
         bool modeTest        = false;
         
         
         DEVMODE DMode      = { 0 };
         
         DMode.dmSize       = sizeof(DEVMODE);
         
         DMode.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
         
         DMode.dmPelsWidth  = graphicsWidth();
         DMode.dmPelsHeight = graphicsHeight();
         
         DMode.dmBitsPerPel = 32;
         
         modeTestCounter = -1;
         
         while( EnumDisplaySettings( 0, ++modeTestCounter, &DMode ) != 0 )
         {
            if( DMode.dmPelsWidth  == (unsigned int) graphicsWidth()  &&
                DMode.dmPelsHeight == (unsigned int) graphicsHeight() &&
                DMode.dmBitsPerPel == 32
              )
            {
               modeTest = true;
            }
         }
         
         if( modeTest == true )
         {
            return GRAPHICS_FULLSCREEN;
         }
         
         DMode.dmPelsWidth  = graphicsWidth();
         DMode.dmPelsHeight = graphicsHeight();
         
         DMode.dmBitsPerPel = screenBitDepth;
         
         modeTestCounter = -1;
         
         while( EnumDisplaySettings( 0, ++modeTestCounter, &DMode ) != 0 )
         {
            if( DMode.dmPelsWidth  == (unsigned int) graphicsWidth()  &&
                DMode.dmPelsHeight == (unsigned int) graphicsHeight() &&
                DMode.dmBitsPerPel == (unsigned int) screenBitDepth
              )
            {
               modeTest = true;
            }
         }
         
         if( modeTest == true )
         {
            return GRAPHICS_FULLSCREEN;
         }
         
         forceFullScreen = false;
         
         return GRAPHICS_WINDOW;
      }
      
      return GRAPHICS_WINDOW;
   }
};

// Give the Graphics class static variables default values.
Graphics::GRAPHICS_IMPLEMENTATION Graphics::Implementation = Graphics::DIRECTDRAW;

int Graphics::width  = 640;
int Graphics::height = 480;

bool Graphics::beNice = true;

bool Graphics::forceFullScreen = false;

IDirectDraw* Graphics::ddraw_obj = 0;

IDirectDrawClipper* Graphics::ddraw_screenclipper = 0;

IDirectDrawSurface* Graphics::ddraw_screen = 0;

IDirectDrawSurface* Graphics::ddraw_backbuffer = 0;

bool Graphics::isModeChangeActive = false;

int Graphics::bitDepth = -1;

int Graphics::oldWidth    = -1;
int Graphics::oldHeight   = -1;
int Graphics::oldBitDepth = -1;

char** Graphics::backbufferArray = 0;


HDC     Graphics::backbufferDC       = 0;
HBITMAP Graphics::backbufferBitmapHB = 0;
HGDIOBJ Graphics::backbufferCleanUp  = 0;


HWND    Graphics::_hWindow = 0;
// End initialization of Graphics class static variables.


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// special function for de Casteljau algorithm

#define S 8

#define f( v ) ( ( v >> S ) << S  )
#define i( v )   ( v >> S )
#define r( v ) ( ( v >> S ) << 16 )
#define g( v ) ( ( v >> S ) << 8  )
#define b( v )   ( v >> S )

#define pixelx( x, y ) *( bb[ i( y ) ] +    x   )
#define pixely( x, y ) *( bb[    y   ] + i( x ) )

void Graphics::RenderPoint32( int x0,
                              int y0,
                              int c0
                            )
{
   if( x0 >= 0 &&
       y0 >= 0 &&
       x0 <  Graphics::graphicsClientWidth() &&
       y0 <  Graphics::graphicsClientHeight()
     )
   {
      int *pixel = (int*) ( ( Graphics::graphicsBackBufferFunction() )[ y0 ] );
      
      *( pixel + x0 ) = c0;
   }
}

void Graphics::RenderLine32( int x0,
                             int y0,
                             int x1,
                             int y1,
                             int xi,
                             int yi
                           )
{
   int count,
       dx, dxstep, dxabs,
       dy, dystep, dyabs,
       r0, g0, b0, r1, g1, b1, ri, gi, bi,
       **bb;
   
   int left = 0, right,
       top  = 0, bottom;

   double t;
   
   r0 = ( xi >> 16 ) & 0xff;
   g0 = ( xi >> 8  ) & 0xff;
   b0 = xi & 0xff;
   
   r1 = ( yi >> 16 ) & 0xff;
   g1 = ( yi >> 8  ) & 0xff;
   b1 = yi & 0xff;

   right  = Graphics::graphicsClientWidth()  - 1;
   bottom = Graphics::graphicsClientHeight() - 1;

   bb = (int**) Graphics::graphicsBackBufferFunction();
   
   // left clip
   // out - out
   if( x0 < left && x1 < left )
   {
      return;
   }
   // in - in
   else if( x0 >= left && x1 >= left )
   {
   }
   // out - in
   else if( x0 < left && x1 >= left )
   {
      t = (double) ( left - x0 ) / (double) ( x1 - x0 );
      
      r0 = r0 + (int) ( (double) ( r1 - r0 ) * t );
      g0 = g0 + (int) ( (double) ( g1 - g0 ) * t );
      b0 = b0 + (int) ( (double) ( b1 - b0 ) * t );
      
      y0 = y0 + (int) ( (double) ( y1 - y0 ) * t );
      
      x0 = left;
   }
   // in - out
   else if( x0 >= left && x1 < left )
   {
      t = (double) ( left - x1 ) / (double) ( x0 - x1 );
      
      r1 = r1 + (int) ( (double) ( r0 - r1 ) * t );
      g1 = g1 + (int) ( (double) ( g0 - g1 ) * t );
      b1 = b1 + (int) ( (double) ( b0 - b1 ) * t );
      
      y1 = y1 + (int) ( (double) ( y0 - y1 ) * t );
      
      x1 = left;
   }
   
   // right clip
   // out - out
   if( x0 > right && x1 > right )
   {
      return;
   }
   // in - in
   else if( x0 <= right && x1 <= right )
   {
   }
   // out - in
   else if( x0 > right && x1 <= right )
   {
      t = (double) ( x0 - right ) / (double) ( x0 - x1 );
      
      r0 = r0 + (int) ( (double) ( r1 - r0 ) * t );
      g0 = g0 + (int) ( (double) ( g1 - g0 ) * t );
      b0 = b0 + (int) ( (double) ( b1 - b0 ) * t );
      
      y0 = y0 + (int) ( (double) ( y1 - y0 ) * t );
      
      x0 = right;
   }
   // in - out
   else if( x0 <= right && x1 > right )
   {
      t = (double) ( x1 - right ) / (double) ( x1 - x0 );
      
      r1 = r1 + (int) ( (double) ( r0 - r1 ) * t );
      g1 = g1 + (int) ( (double) ( g0 - g1 ) * t );
      b1 = b1 + (int) ( (double) ( b0 - b1 ) * t );
      
      y1 = y1 + (int) ( (double) ( y0 - y1 ) * t );
      
      x1 = right;
   }
   
   // top clip
   // out - out
   if( y0 < top && y1 < top )
   {
      return;
   }
   // in - in
   else if( y0 >= top && y1 >= top )
   {
   }
   // out - in
   else if( y0 < top && y1 >= top )
   {
      t = (double) ( top - y0 ) / (double) ( y1 - y0 );
      
      r0 = r0 + (int) ( (double) ( r1 - r0 ) * t );
      g0 = g0 + (int) ( (double) ( g1 - g0 ) * t );
      b0 = b0 + (int) ( (double) ( b1 - b0 ) * t );
      
      x0 = x0 + (int) ( (double) ( x1 - x0 ) * t );
      
      y0 = top;
   }
   // in - out
   else if( y0 >= top && y1 < top )
   {
      t = (double) ( top - y1 ) / (double) ( y0 - y1 );
      
      r1 = r1 + (int) ( (double) ( r0 - r1 ) * t );
      g1 = g1 + (int) ( (double) ( g0 - g1 ) * t );
      b1 = b1 + (int) ( (double) ( b0 - b1 ) * t );
      
      x1 = x1 + (int) ( (double) ( x0 - x1 ) * t );
      
      y1 = top;
   }
   
   // bottom clip
   // out - out
   if( y0 > bottom && y1 > bottom )
   {
      return;
   }
   // in - in
   else if( y0 <= bottom && y1 <= bottom )
   {
   }
   // out - in
   else if( y0 > bottom && y1 <= bottom )
   {
      t = (double) ( y0 - bottom ) / (double) ( y0 - y1 );
      
      r0 = r0 + (int) ( (double) ( r1 - r0 ) * t );
      g0 = g0 + (int) ( (double) ( g1 - g0 ) * t );
      b0 = b0 + (int) ( (double) ( b1 - b0 ) * t );
      
      x0 = x0 + (int) ( (double) ( x1 - x0 ) * t );
      
      y0 = bottom;
   }
   // in - out
   else if( y0 <= bottom && y1 > bottom )
   {
      t = (double) ( y1 - bottom ) / (double) ( y1 - y0 );
      
      r1 = r1 + (int) ( (double) ( r0 - r1 ) * t );
      g1 = g1 + (int) ( (double) ( g0 - g1 ) * t );
      b1 = b1 + (int) ( (double) ( b0 - b1 ) * t );
      
      x1 = x1 + (int) ( (double) ( x0 - x1 ) * t );
      
      y1 = bottom;
   }
   
   xi = ( r0 << 16 ) | ( g0 << 8 ) | b0;
   yi = ( r1 << 16 ) | ( g1 << 8 ) | b1;
   
   if( x0 < left || x0 > right  ||
       x1 < left || x1 > right  ||
       y0 < top  || y0 > bottom ||
       y1 < top  || y1 > bottom ||
       r0 < 0    || r0 > 255    ||
       g0 < 0    || g0 > 255    ||
       b0 < 0    || b0 > 255    ||
       r1 < 0    || r1 > 255    ||
       g1 < 0    || g1 > 255    ||
       b1 < 0    || b1 > 255
     )
   {
      return;
   }
   
   x0 <<= 8; x1 <<= 8;
   y0 <<= 8; y1 <<= 8;
   
   r0 = ( xi >> 8 ) & 0xff00; g0 = xi & 0xff00; b0 = ( xi & 0xff ) << 8;
   r1 = ( yi >> 8 ) & 0xff00; g1 = yi & 0xff00; b1 = ( yi & 0xff ) << 8;
   
   dx = x1 - x0;

   if( dx >= 0)
   {
      dxstep = 1; dxabs = dx;
   }
   else
   {
      dxstep = -1; dxabs = -dx;
   }
   
   dy = y1 - y0;

   if( dy >= 0 )
   {
      dystep = 1; dyabs = dy;
   }
   else
   {
      dystep = -1; dyabs = -dy;
   }
   
   if( dxabs >= dyabs )
   {
      count = i( dxabs );
      
      if( count == 0 )
      {
         yi = 0; ri = 0; gi = 0; bi = 0;
      }
      else
      {
         yi = ( ( y1 - y0 ) << S ) / dxabs;
         ri = ( ( r1 - r0 ) << S ) / dxabs;
         gi = ( ( g1 - g0 ) << S ) / dxabs;
         bi = ( ( b1 - b0 ) << S ) / dxabs;
      }
      
      x0    = i( x0 );
      x1    = i( x1 );
      dxabs = x1 - x0;
      
      if( dxabs < 0 )
      {
         dxabs =- dxabs;
      }
      
      if( count > 0 )
      {
         do
         {
            pixelx( x0, y0 ) = r( r0 ) | g( g0 ) | b( b0 );
            
            r0 += ri; g0 += gi; b0 += bi;
            
            x0 += dxstep;
            y0 += yi;
            
         }while( --count != 0 );
      }
   }
   else
   {
      count = i( dyabs );
      
      if( count == 0 )
      {
         xi = 0; ri = 0; gi = 0; bi = 0;
      }
      else
      {
         xi = ( ( x1 - x0 ) << S ) / dyabs;
         ri = ( ( r1 - r0 ) << S ) / dyabs;
         gi = ( ( g1 - g0 ) << S ) / dyabs;
         bi = ( ( b1 - b0 ) << S ) / dyabs;
      }
      
      y0    = i( y0 );
      y1    = i( y1 );
      dyabs = y1 - y0;
      
      if( dyabs < 0 )
      {
         dyabs =- dyabs;
      }
      
      if( count > 0 )
      {
         do
         {
            pixely( x0, y0 ) = r( r0 ) | g( g0 ) | b( b0 );
            
            r0 += ri; g0 += gi; b0 += bi;
            
            y0 += dystep;
            x0 += xi;
            
         }while( --count != 0 );
      }
   }
}

#define r0( c0 ) ( ( c0 >> 8 ) & 0xff00 )
#define g0( c0 ) ( c0 & 0xff00 )
#define b0( c0 ) ( ( c0 & 0xff ) << 8 )

void Graphics::RenderCircle32( int xcen,
                               int ycen,
                               int r,
                               int c0,
                               int c1
                             )
{
   int d, de, dse, x, y;
   
   int r8, g8, b8,
       s1rs, s2rs, s3rs, s4rs, s1re, s2re, s3re, s4re, ri, r_cur,
       s1gs, s2gs, s3gs, s4gs, s1ge, s2ge, s3ge, s4ge, gi, g_cur,
       s1bs, s2bs, s3bs, s4bs, s1be, s2be, s3be, s4be, bi, b_cur,
       num_pixels, pi;

   int *dt, **bb;
   int local_length, local_ri, local_gi, local_bi;
   
   int width, height;

   width  = Graphics::graphicsClientWidth();
   height = Graphics::graphicsClientHeight();
   
   if( xcen + r < 0 || xcen - r >= width ||
       ycen + r < 0 || ycen - r >= height
     )
   {
      return;
   }

   pi = 804 << ( S - 8 );

   bb = (int**) Graphics::graphicsBackBufferFunction();
   
   num_pixels = ( pi * ( r << S ) ) >> S;
   
   d = 1 - r; de = 3; dse = -( r * 2 ) + 5; x = 0; y = r;
   
   r8 =( r0( c1 ) - r0( c0 ) ) / 4;
   g8 =( g0( c1 ) - g0( c0 ) ) / 4;
   b8 =( b0( c1 ) - b0( c0 ) ) / 4;
   
   if( ( num_pixels / 4 ) == 0 )
   {
      ri = 0; gi = 0; bi = 0;
   }
   else
   {
      ri = ( r8 << ( S - 1 ) ) / ( num_pixels / 4 );
      gi = ( g8 << ( S - 1 ) ) / ( num_pixels / 4 );
      bi = ( b8 << ( S - 1 ) ) / ( num_pixels / 4 );
   }
   
   s1rs = r0( c0 );      s1re = r0( c0 ) + ( r8 * 4 ),
   s2rs = r0( c0 ) + r8; s2re = r0( c0 ) + ( r8 * 2 ) + r8,
   s3rs = s2rs;          s3re = s2re,
   s4rs = s2rs + r8;     s4re = s2rs + r8,
      
   s1gs = g0( c0 );      s1ge = g0( c0 ) + ( g8 * 4 ),
   s2gs = g0( c0 ) + g8; s2ge = g0( c0 ) + ( g8 * 2 ) + g8,
   s3gs = s2gs;          s3ge = s2ge,
   s4gs = s2gs + g8;     s4ge = s2gs + g8,
      
   s1bs = b0( c0 );      s1be = b0( c0 ) + ( b8 * 4 ),
   s2bs = b0( c0 ) + b8; s2be = b0( c0 ) + ( b8 * 2 ) + b8,
   s3bs = s2bs;          s3be = s2be,
   s4bs = s2bs + b8;     s4be = s2bs + b8;
   
   if( r < 0 )
   {
      y =- r;
   }
   else if( r == 0 )
   {
      if( xcen >= 0 && ycen >= 0 && xcen < width && ycen < height )
      {
         *( bb[ ycen ] + xcen ) = r( ( ( s2rs / 2 ) + ( s2re / 2 ) ) )|
                                  g( ( ( s2gs / 2 ) + ( s2ge / 2 ) ) )|
                                  b( ( ( s2bs / 2 ) + ( s2be / 2 ) ) );
      }
      
      return;
   }
   
   do
   {
      r_cur = s4rs;
      g_cur = s4gs;
      b_cur = s4bs;

      local_length = x * 2;
      
      if( local_length == 0 )
      {
         local_ri = 0; local_gi = 0; local_bi = 0;
      }
      else
      {
         local_ri = ( s4re - s4rs ) / local_length;
         local_gi = ( s4ge - s4gs ) / local_length;
         local_bi = ( s4be - s4bs ) / local_length;
      }
      
      if( ycen + y >= 0 && ycen + y < height )
      {
         dt = bb[ ycen + y ] + xcen - x;
         
         c0 = xcen-x;
         
         while( --local_length > 0 )
         {
            if( c0 >= 0 && c0 < width )
            {
               *dt = r( r_cur ) | g( g_cur ) | b( b_cur );
            }
            
            c0++;
            dt++;

            r_cur += local_ri;
            g_cur += local_gi;
            b_cur += local_bi;
         }
      }
      
      r_cur = s1rs;
      g_cur = s1gs;
      b_cur = s1bs;

      local_length = x * 2;
      
      if( local_length == 0 )
      {
         local_ri = 0; local_gi = 0; local_bi = 0;
      }
      else
      {
         local_ri = ( s1re - s1rs ) / local_length;
         local_gi = ( s1ge - s1gs ) / local_length;
         local_bi = ( s1be - s1bs ) / local_length;
      }
      
      if( ycen - y >= 0 && ycen - y < height )
      {
         dt = bb[ ycen - y ] + xcen - x;
         
         c0 = xcen - x;
         
         while( --local_length > 0 )
         {
            if( c0 >= 0 && c0 < width )
            {
               *dt = r( r_cur ) | g( g_cur ) | b( b_cur );
            }
            
            c0++;
            dt++;

            r_cur += local_ri;
            g_cur += local_gi;
            b_cur += local_bi;
         }
      }
      
      r_cur = s2rs;
      g_cur = s2gs;
      b_cur = s2bs;

      local_length = y * 2;
      
      if( local_length == 0 )
      {
         local_ri = 0; local_gi = 0; local_bi = 0;
      }
      else
      {
         local_ri = ( s2re - s2rs ) / local_length;
         local_gi = ( s2ge - s2gs ) / local_length;
         local_bi = ( s2be - s2bs ) / local_length;
      }
      
      if( ycen - x >= 0 && ycen - x < height )
      {
         dt = bb[ ycen - x ] + xcen - y;
         
         c0 = xcen - y;
         
         while( --local_length > 0 )
         {
            if( c0 >= 0 && c0 < width )
            {
               *dt = r( r_cur ) | g( g_cur ) | b( b_cur );
            }
            
            c0++;
            dt++;

            r_cur += local_ri;
            g_cur += local_gi;
            b_cur += local_bi;
         }
      }
      
      r_cur = s3rs;
      g_cur = s3gs;
      b_cur = s3bs;

      local_length = y * 2;
      
      if( local_length == 0 )
      {
         local_ri = 0; local_gi = 0; local_bi = 0;
      }
      else
      {
         local_ri = ( s3re - s3rs ) / local_length;
         local_gi = ( s3ge - s3gs ) / local_length;
         local_bi = ( s3be - s3bs ) / local_length;
      }
      
      if( ycen + x >= 0 && ycen + x < height )
      {
         dt = bb[ ycen + x ] + xcen - y;
         
         c0 = xcen - y;
         
         while( --local_length > 0 )
         {
            if( c0 >= 0 && c0 < width )
            {
               *dt = r( r_cur ) | g( g_cur ) | b( b_cur );
            }
            
            c0++;
            dt++;

            r_cur += local_ri;
            g_cur += local_gi;
            b_cur += local_bi;
         }
      }
      
      s1rs += ri; s1re -= ri;
      s2rs -= ri; s2re += ri;
      s3rs += ri; s3re -= ri;
      s4rs -= ri; s4re += ri;
      
      s1gs += gi; s1ge -= gi;
      s2gs -= gi; s2ge += gi;
      s3gs += gi; s3ge -= gi;
      s4gs -= gi; s4ge += gi;
      
      s1bs += bi; s1be -= bi;
      s2bs -= bi; s2be += bi;
      s3bs += bi; s3be -= bi;
      s4bs -= bi; s4be += bi;
      
      if( d < 0 )
      {
         d += de; de += 2; dse += 2;
      }
      else
      {
         d += dse; de += 2; dse += 4; --y;
      }
      
   }while( ++x <= y );
}

#undef S
#undef f
#undef i
#undef r
#undef g
#undef b
#undef pixelx
#undef pixely
#undef copy
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const char appClassName[] = "de Casteljau Algorithm -- Hit F10 for the Extra Box! --";
static const char appName[]      = "de Casteljau Algorithm -- Hit F10 for the Extra Box! --";

// used to disable the warning when exit( 0 ) is called
#pragma warning ( disable: 4702 )

// Boolean variable, set to true when the application is top most,
// set to false when the application is not top most.
//
// The application will perform a sleep( 1 ) every message loop
// if the application is not top most, to give other applications
// more processor time.
//
// If our application is top most, it will hog as much processor
// power as it can while still being a stable windows application.
// It doesn't make much difference, unless the user wants extra
// time for background applications.  Every applications gets a
// small fair chunk of processor time.  Other applications can take
// center stage when they are top most.
static bool IsApplicationTopMost   = true;

static bool IsApplicationMinimized = false;

static bool IsLeftMouseButtonDown  = false;
static bool IsRightMouseButtonDown = false;

static bool IsWindowStyleChanging  = false;

static bool isMenuActive           = false;

static POINT mousePointCurrent  = { -1, -1 };
static POINT mousePointPrevious = { -1, -1 };

static double angleTheta = 0,
              angleFee   = 0,
              velocity   = 0;

typedef pair< POINT, int > pairQI;
typedef queue< pairQI > queueI;

static queueI *input = 0;

static int orInput;

static double menuArray[ 13 ];

enum INPUT_EVENT
{ 
   UPDATE_INPUT = 0,

   CAPTURE_CONTROL_POINT = 8,
   ADD_CONTROL_POINT = 16,

   CAPTURE_T_OF_F_OF_T = 8|1,
   DUMP_ALL_CONTROL_POINTS = 16|1,

   CAPTURE_TRANSLATE = 8|2,
   CAPTURE_SCALE = 16|2,

   CAPTURE_ROTATE = 8|4,
   REMOVE_CONTROL_POINT = 16|4,

   TOGGLE_SHELLS = 32,

   DUMP_ALL_CAPTURES = 64,

   MENU_INPUT = 128,

   TOGGLE_CONTROL_POINTS = 256,

   INCREASE_ITERATION_CONSTANT = 512,

   DECREASE_ITERATION_CONSTANT = 1024,

   ADD_DE_CASTELJAU_CURVE = 2048,

   REMOVE_DE_CASTELJAU_CURVE = 4096,

   TRAVERSE_DE_CASTELJAU_CURVE_LIST = 8192
};

BOOL CALLBACK Graphics::AboutDlgProc( HWND hDlg,
                                      UINT msg,
                                      WPARAM wParam,
                                      LPARAM lParam
                                    )
{
   switch( msg )
   {
   case WM_INITDIALOG:

      isMenuActive = true;
      
      return TRUE;
      
   case WM_COMMAND:
      
      switch( LOWORD( wParam ) )
      {
      case IDOK:
      case IDCANCEL:
         
         EndDialog( hDlg, 0 );

         isMenuActive = false;
         
         return TRUE;
      }
      
      break;
   }
   
   if( Graphics::_hWindow &&
       Graphics::graphicsIsModeChangeActive() == false &&
       IsApplicationMinimized == false
     )
   {
      POINT mousePt;
      
      GetCursorPos( &mousePt );
      ScreenToClient( Graphics::_hWindow, &mousePt );
      
      main( UPDATE_INPUT,
            mousePt.x,
            mousePt.y,
            (double) Graphics::graphicsClientWidth() * 0.5,
            (double) Graphics::graphicsClientHeight() * 0.5
          );
      
      Graphics::graphicsDrawBackBufferToScreen( Graphics::_hWindow );
      
      Sleep( 1 );
   }
   
   return FALSE;
}

#include "resource.h"

static bool checkString( char *string
                       )
{
   char charCur = *string;
   
   int stringI = 1;
   
   if( charCur == '+' || charCur == '-' )
   {
   }
   else if( charCur >= '0' && charCur <= '9' )
   {
   }
   else
   {
      return false;
   }
   
   for( charCur = string[ 1 ]; charCur != 0 && stringI < 256; charCur = string[ ++stringI ] )
   {
      if( charCur >= '0' && charCur <= '9' )
      {
      }
      else
      {
         return false;
      }
   }
   
   return true;
}

static void plusDecimal( double &lhs,
                         double rhs
                       )
{
   if( lhs < 0 )
   {
      lhs -= rhs;
   }
   else
   {
      lhs += rhs;
   }
}

BOOL CALLBACK Graphics::InputDlgProc( HWND hDlg,
                                      UINT msg,
                                      WPARAM wParam,
                                      LPARAM lParam
                                    )
{
   char item[ 256 ] = { 0 };

   switch( msg )
   {
   case WM_INITDIALOG:

      isMenuActive = true;
      
      SetDlgItemText( hDlg, EDITX3_INT, "0" );
      SetDlgItemText( hDlg, EDITX3_DEC, "0" );
      SetDlgItemText( hDlg, EDITX2_INT, "0" );
      SetDlgItemText( hDlg, EDITX2_DEC, "0" );
      SetDlgItemText( hDlg, EDITX1_INT, "0" );
      SetDlgItemText( hDlg, EDITX1_DEC, "0" );
      SetDlgItemText( hDlg, EDITX0_INT, "0" );
      SetDlgItemText( hDlg, EDITX0_DEC, "0" );
      
      SetDlgItemText( hDlg, EDITY3_INT, "0" );
      SetDlgItemText( hDlg, EDITY3_DEC, "0" );
      SetDlgItemText( hDlg, EDITY2_INT, "0" );
      SetDlgItemText( hDlg, EDITY2_DEC, "0" );
      SetDlgItemText( hDlg, EDITY1_INT, "0" );
      SetDlgItemText( hDlg, EDITY1_DEC, "0" );
      SetDlgItemText( hDlg, EDITY0_INT, "0" );
      SetDlgItemText( hDlg, EDITY0_DEC, "0" );
      
      SetDlgItemText( hDlg, EDITR_INT, "0" );
      SetDlgItemText( hDlg, EDITR_DEC, "0" );
      
      SetDlgItemText( hDlg, EDITS_INT, "1" );
      SetDlgItemText( hDlg, EDITS_DEC, "0" );
      
      return TRUE;
      
   case WM_COMMAND:
      
      switch( LOWORD( wParam ) )
      {
      case IDOK:

         menuArray[ 0 ] = 3;

         //////////////////////////////////////////////////
         memset( item, 0, sizeof( char ) * 256 );
         GetDlgItemText( hDlg, EDITX3_INT, item, 255 );
         
         if( checkString( item ) == false )
         {
            goto _IDCANCEL;
         }
         
         menuArray[ 4 ] = atof( item );
         
         memset( item, 0, sizeof( char ) * 256 );
         item[ 0 ] = '.';
         GetDlgItemText( hDlg, EDITX3_DEC, item + 1, 254 );
         plusDecimal( menuArray[ 4 ], atof( item ) );
         
         //////////////////////////////////////////////////
         memset( item, 0, sizeof( char ) * 256 );
         GetDlgItemText( hDlg, EDITX2_INT, item, 255 );
         
         if( checkString( item ) == false )
         {
            goto _IDCANCEL;
         }
         
         menuArray[ 3 ] = atof( item );
         
         memset( item, 0, sizeof( char ) * 256 );
         item[ 0 ] = '.';
         GetDlgItemText( hDlg, EDITX2_DEC, item + 1, 254 );
         plusDecimal( menuArray[ 3 ], atof( item ) );
         
         //////////////////////////////////////////////////
         memset( item, 0, sizeof( char ) * 256 );
         GetDlgItemText( hDlg, EDITX1_INT, item, 255 );
         
         if( checkString( item ) == false )
         {
            goto _IDCANCEL;
         }
         
         menuArray[ 2 ] = atof( item );
         
         memset( item, 0, sizeof( char ) * 256 );
         item[ 0 ] = '.';
         GetDlgItemText( hDlg, EDITX1_DEC, item + 1, 254 );
         plusDecimal( menuArray[ 2 ], atof( item ) );
         
         //////////////////////////////////////////////////
         memset( item, 0, sizeof( char ) * 256 );
         GetDlgItemText( hDlg, EDITX0_INT, item, 255 );
         
         if( checkString( item ) == false )
         {
            goto _IDCANCEL;
         }
         
         menuArray[ 1 ] = atof( item );
         
         memset( item, 0, sizeof( char ) * 256 );
         item[ 0 ] = '.';
         GetDlgItemText( hDlg, EDITX0_DEC, item + 1, 254 );
         plusDecimal( menuArray[ 1 ], atof( item ) );
         
         //////////////////////////////////////////////////
         memset( item, 0, sizeof( char ) * 256 );
         GetDlgItemText( hDlg, EDITY3_INT, item, 255 );
         
         if( checkString( item ) == false )
         {
            goto _IDCANCEL;
         }
         
         menuArray[ 8 ] = atof( item );
         
         memset( item, 0, sizeof( char ) * 256 );
         item[ 0 ] = '.';
         GetDlgItemText( hDlg, EDITY3_DEC, item + 1, 254 );
         plusDecimal( menuArray[ 8 ], atof( item ) );
         
         //////////////////////////////////////////////////
         memset( item, 0, sizeof( char ) * 256 );
         GetDlgItemText( hDlg, EDITY2_INT, item, 255 );
         
         if( checkString( item ) == false )
         {
            goto _IDCANCEL;
         }
         
         menuArray[ 7 ] = atof( item );
         
         memset( item, 0, sizeof( char ) * 256 );
         item[ 0 ] = '.';
         GetDlgItemText( hDlg, EDITY2_DEC, item + 1, 254 );
         plusDecimal( menuArray[ 7 ], atof( item ) );
         
         //////////////////////////////////////////////////
         memset( item, 0, sizeof( char ) * 256 );
         GetDlgItemText( hDlg, EDITY1_INT, item, 255 );
         
         if( checkString( item ) == false )
         {
            goto _IDCANCEL;
         }
         
         menuArray[ 6 ] = atof( item );
         
         memset( item, 0, sizeof( char ) * 256 );
         item[ 0 ] = '.';
         GetDlgItemText( hDlg, EDITY1_DEC, item + 1, 254 );
         plusDecimal( menuArray[ 6 ], atof( item ) );
         
         //////////////////////////////////////////////////
         memset( item, 0, sizeof( char ) * 256 );
         GetDlgItemText( hDlg, EDITY0_INT, item, 255 );
         
         if( checkString( item ) == false )
         {
            goto _IDCANCEL;
         }
         
         menuArray[ 5 ] = atof( item );
         
         memset( item, 0, sizeof( char ) * 256 );
         item[ 0 ] = '.';
         GetDlgItemText( hDlg, EDITY0_DEC, item + 1, 254 );
         plusDecimal( menuArray[ 5 ], atof( item ) );
         
         //////////////////////////////////////////////////
         memset( item, 0, sizeof( char ) * 256 );
         GetDlgItemText( hDlg, EDITR_INT, item, 255 );
         
         if( checkString( item ) == false )
         {
            goto _IDCANCEL;
         }
         
         menuArray[ 9 ] = atof( item );
         
         memset( item, 0, sizeof( char ) * 256 );
         item[ 0 ] = '.';
         GetDlgItemText( hDlg, EDITR_DEC, item + 1, 254 );
         plusDecimal( menuArray[ 9 ], atof( item ) );
         
         //////////////////////////////////////////////////
         memset( item, 0, sizeof( char ) * 256 );
         GetDlgItemText( hDlg, EDITS_INT, item, 255 );
         
         if( checkString( item ) == false )
         {
            goto _IDCANCEL;
         }
         
         menuArray[ 10 ] = atof( item );
         
         memset( item, 0, sizeof( char ) * 256 );
         item[ 0 ] = '.';
         GetDlgItemText( hDlg, EDITS_DEC, item + 1, 254 );
         plusDecimal( menuArray[ 10 ], atof( item ) );
         
         //////////////////////////////////////////////////
         EndDialog( hDlg, 0 );

         isMenuActive = false;
      
         return TRUE;
      
      case IDCANCEL:
         
_IDCANCEL:
         
         EndDialog( hDlg, -1 );

         isMenuActive = false;
         
         return TRUE;
         
      case IDEX1:
         
         SetDlgItemText( hDlg, EDITX3_INT, "0" );
         SetDlgItemText( hDlg, EDITX3_DEC, "0" );
         SetDlgItemText( hDlg, EDITX2_INT, "0" );
         SetDlgItemText( hDlg, EDITX2_DEC, "0" );
         SetDlgItemText( hDlg, EDITX1_INT, "3" );
         SetDlgItemText( hDlg, EDITX1_DEC, "0" );
         SetDlgItemText( hDlg, EDITX0_INT, "0" );
         SetDlgItemText( hDlg, EDITX0_DEC, "0" );
         
         SetDlgItemText( hDlg, EDITY3_INT, "3" );
         SetDlgItemText( hDlg, EDITY3_DEC, "0" );
         SetDlgItemText( hDlg, EDITY2_INT, "0" );
         SetDlgItemText( hDlg, EDITY2_DEC, "0" );
         SetDlgItemText( hDlg, EDITY1_INT, "-3" );
         SetDlgItemText( hDlg, EDITY1_DEC, "0" );
         SetDlgItemText( hDlg, EDITY0_INT, "0" );
         SetDlgItemText( hDlg, EDITY0_DEC, "0" );
         
         SetDlgItemText( hDlg, EDITR_INT, "-1" );
         SetDlgItemText( hDlg, EDITR_DEC, "0" );
         
         SetDlgItemText( hDlg, EDITS_INT, "1" );
         SetDlgItemText( hDlg, EDITS_DEC, "0" );
         
         return FALSE;
         
      case IDEX2:
         
         SetDlgItemText( hDlg, EDITX3_INT, "0" );
         SetDlgItemText( hDlg, EDITX3_DEC, "0" );
         SetDlgItemText( hDlg, EDITX2_INT, "3" );
         SetDlgItemText( hDlg, EDITX2_DEC, "0" );
         SetDlgItemText( hDlg, EDITX1_INT, "-6" );
         SetDlgItemText( hDlg, EDITX1_DEC, "0" );
         SetDlgItemText( hDlg, EDITX0_INT, "9" );
         SetDlgItemText( hDlg, EDITX0_DEC, "0" );
         
         SetDlgItemText( hDlg, EDITY3_INT, "3" );
         SetDlgItemText( hDlg, EDITY3_DEC, "0" );
         SetDlgItemText( hDlg, EDITY2_INT, "-6" );
         SetDlgItemText( hDlg, EDITY2_DEC, "0" );
         SetDlgItemText( hDlg, EDITY1_INT, "9" );
         SetDlgItemText( hDlg, EDITY1_DEC, "0" );
         SetDlgItemText( hDlg, EDITY0_INT, "0" );
         SetDlgItemText( hDlg, EDITY0_DEC, "0" );
         
         SetDlgItemText( hDlg, EDITR_INT, "0" );
         SetDlgItemText( hDlg, EDITR_DEC, "0" );
         
         SetDlgItemText( hDlg, EDITS_INT, "1" );
         SetDlgItemText( hDlg, EDITS_DEC, "0" );
         
         return FALSE;
         
      case IDEX3:
         
         SetDlgItemText( hDlg, EDITX3_INT, "0" );
         SetDlgItemText( hDlg, EDITX3_DEC, "0" );
         SetDlgItemText( hDlg, EDITX2_INT, "3" );
         SetDlgItemText( hDlg, EDITX2_DEC, "0" );
         SetDlgItemText( hDlg, EDITX1_INT, "-12" );
         SetDlgItemText( hDlg, EDITX1_DEC, "0" );
         SetDlgItemText( hDlg, EDITX0_INT, "15" );
         SetDlgItemText( hDlg, EDITX0_DEC, "0" );
         
         SetDlgItemText( hDlg, EDITY3_INT, "3" );
         SetDlgItemText( hDlg, EDITY3_DEC, "0" );
         SetDlgItemText( hDlg, EDITY2_INT, "-12" );
         SetDlgItemText( hDlg, EDITY2_DEC, "0" );
         SetDlgItemText( hDlg, EDITY1_INT, "15" );
         SetDlgItemText( hDlg, EDITY1_DEC, "0" );
         SetDlgItemText( hDlg, EDITY0_INT, "0" );
         SetDlgItemText( hDlg, EDITY0_DEC, "0" );
         
         SetDlgItemText( hDlg, EDITR_INT, "0" );
         SetDlgItemText( hDlg, EDITR_DEC, "0" );
         
         SetDlgItemText( hDlg, EDITS_INT, "2" );
         SetDlgItemText( hDlg, EDITS_DEC, "0" );
         
         return FALSE;
         
      case IDEX4:
         
         SetDlgItemText( hDlg, EDITX3_INT, "0" );
         SetDlgItemText( hDlg, EDITX3_DEC, "0" );
         SetDlgItemText( hDlg, EDITX2_INT, "3" );
         SetDlgItemText( hDlg, EDITX2_DEC, "0" );
         SetDlgItemText( hDlg, EDITX1_INT, "-6" );
         SetDlgItemText( hDlg, EDITX1_DEC, "0" );
         SetDlgItemText( hDlg, EDITX0_INT, "3" );
         SetDlgItemText( hDlg, EDITX0_DEC, "0" );
         
         SetDlgItemText( hDlg, EDITY3_INT, "3" );
         SetDlgItemText( hDlg, EDITY3_DEC, "0" );
         SetDlgItemText( hDlg, EDITY2_INT, "-6" );
         SetDlgItemText( hDlg, EDITY2_DEC, "0" );
         SetDlgItemText( hDlg, EDITY1_INT, "3" );
         SetDlgItemText( hDlg, EDITY1_DEC, "0" );
         SetDlgItemText( hDlg, EDITY0_INT, "0" );
         SetDlgItemText( hDlg, EDITY0_DEC, "0" );
         
         SetDlgItemText( hDlg, EDITR_INT, "0" );
         SetDlgItemText( hDlg, EDITR_DEC, "0" );
         
         SetDlgItemText( hDlg, EDITS_INT, "2" );
         SetDlgItemText( hDlg, EDITS_DEC, "0" );
         
         return FALSE;
         
      case IDEX5:
         
         SetDlgItemText( hDlg, EDITX3_INT, "0" );
         SetDlgItemText( hDlg, EDITX3_DEC, "0" );
         SetDlgItemText( hDlg, EDITX2_INT, "0" );
         SetDlgItemText( hDlg, EDITX2_DEC, "75" );
         SetDlgItemText( hDlg, EDITX1_INT, "-1" );
         SetDlgItemText( hDlg, EDITX1_DEC, "5" );
         SetDlgItemText( hDlg, EDITX0_INT, "-2" );
         SetDlgItemText( hDlg, EDITX0_DEC, "25" );
         
         SetDlgItemText( hDlg, EDITY3_INT, "0" );
         SetDlgItemText( hDlg, EDITY3_DEC, "75" );
         SetDlgItemText( hDlg, EDITY2_INT, "-1" );
         SetDlgItemText( hDlg, EDITY2_DEC, "5" );
         SetDlgItemText( hDlg, EDITY1_INT, "-2" );
         SetDlgItemText( hDlg, EDITY1_DEC, "25" );
         SetDlgItemText( hDlg, EDITY0_INT, "0" );
         SetDlgItemText( hDlg, EDITY0_DEC, "0" );
         
         SetDlgItemText( hDlg, EDITR_INT, "-1" );
         SetDlgItemText( hDlg, EDITR_DEC, "0" );
         
         SetDlgItemText( hDlg, EDITS_INT, "3" );
         SetDlgItemText( hDlg, EDITS_DEC, "0" );
         
         return FALSE;
      }
      
      break;
   }
   
   if( Graphics::_hWindow &&
       Graphics::graphicsIsModeChangeActive() == false &&
       IsApplicationMinimized == false
     )
   {
      POINT mousePt;
      
      GetCursorPos( &mousePt );
      ScreenToClient( Graphics::_hWindow, &mousePt );
      
      main( UPDATE_INPUT,
            mousePt.x,
            mousePt.y,
            (double) Graphics::graphicsClientWidth() * 0.5,
            (double) Graphics::graphicsClientHeight() * 0.5
          );
      
      Graphics::graphicsDrawBackBufferToScreen( Graphics::_hWindow );
      
      Sleep( 1 );
   }
   
   return FALSE;
}

class WindowStyle
{
   enum
   {
      WINDOWSTYLE_ERROR      = Graphics::GRAPHICS_ERROR,
      WINDOWSTYLE_OK         = Graphics::GRAPHICS_OK,
      WINDOWSTYLE_WINDOW     = Graphics::GRAPHICS_WINDOW,
      WINDOWSTYLE_FULLSCREEN = Graphics::GRAPHICS_FULLSCREEN
   };
   
   static POINT origin;

   static POINT size;

   static RECT menu;

   static int style;

   // These function prototypes are used to stop class instantiation.
   //////////////////////////////////////////////////////////////////
   WindowStyle(
              )
   {
   }

   WindowStyle( WindowStyle&
              )
   {
   }

   virtual ~WindowStyle(
                       ) = 0;

   virtual WindowStyle& operator=( WindowStyle&
                                 ) = 0;
   //////////////////////////////////////////////////////////////////

public:

   static POINT getOrigin(
                         )
   {
      return origin;
   }

   static POINT getSize( bool clamp
                       )
   {
      if( clamp == false || style == WINDOWSTYLE_FULLSCREEN )
      {
         return size;
      }

      POINT temp = { size.x + menu.left + menu.right,
                     size.y + menu.top + menu.bottom
                   };
      
      if( temp.x >= Graphics::oldWidth )
      {
         temp.x = Graphics::oldWidth - menu.left - menu.right - 1;
      }

      if( temp.y >= Graphics::oldHeight )
      {
         temp.y = Graphics::oldHeight - menu.top - menu.bottom - 1;
      }

      temp.x -= menu.left + menu.right;
      temp.y -= menu.top + menu.bottom;

      return temp;
   }

   static RECT getMenuRect(
                          )
   {
      return menu;
   }

   static int getStyle(
                      )
   {
      return style;
   }

   static POINT setOrigin( int x,
                           int y
                         )
   {
      origin.x = x;
      origin.y = y;

      return origin;
   }

   static int setSize( int width,
                       int height
                     )
   {
      width += menu.left + menu.right;
      height += menu.top + menu.bottom;

      if( width <= 0 || height <= 0 )
      {
         return style;
      }

      if( width >= Graphics::oldWidth ||
          height >= Graphics::oldHeight
        )
      {
         style = WINDOWSTYLE_FULLSCREEN;

         return style;
      }

      size.x = width - menu.left - menu.right;
      size.y = height - menu.top - menu.bottom;

      return style;
   }

   static RECT setMenuRect( int leftEdgeMenuThickness,
                            int topEdgeMenuThickness,
                            int rightEdgeMenuThickness,
                            int bottomEdgeMenuThickness
                          )
   {
      menu.left   = leftEdgeMenuThickness;
      menu.top    = topEdgeMenuThickness;
      menu.right  = rightEdgeMenuThickness;
      menu.bottom = bottomEdgeMenuThickness;

      return menu;
   }

   static int setStyle(
                      )
   {
      if( style == WINDOWSTYLE_WINDOW )
      {
         style = WINDOWSTYLE_FULLSCREEN;
      }
      else if( style == WINDOWSTYLE_FULLSCREEN )
      {
         style = WINDOWSTYLE_WINDOW;
      }

      return style;
   }
};

// Give the WindowStyle class static variables default values.
POINT WindowStyle::origin = { -1, -1 };
POINT WindowStyle::size   = { -1, -1 };

RECT WindowStyle::menu = { -1, -1, -1, -1 };

int WindowStyle::style = WINDOWSTYLE_WINDOW;
// End initialization of WindowStyle class static variables.

static int updateTime(
                     );

static double timeInSeconds(
                           );

static const int WM_SETWIDTHHEIGHT    = 0xff000000;
static const int WM_CHANGEWINDOWSTYLE = 0xff000001;

static HWND hWindow = 0;

static bool IsApplicationEntry = false;

LRESULT CALLBACK Graphics::WindowProc( HWND   hwnd,
                                       UINT   msg,
                                       WPARAM wParam,
                                       LPARAM lParam
                                     )
{
   POINT mousePt = { 0, 0 };
   
   static POINT prevPt = { 0, 0 };
   
   static HINSTANCE hInstance = 0;
   
   GetCursorPos( &mousePt );
   ScreenToClient( hwnd, &mousePt );
   
   switch( msg )
   {
   case WM_CREATE:

      hInstance = ( (LPCREATESTRUCT) lParam )->hInstance;
      
      return 0;

   case WM_SETWIDTHHEIGHT:
      {
         HDC screen = GetDC( 0 );

         if( !screen )
         {
            Error( " WindowProc(...) GetDC(...) error " );
         }
         else
         {
            Graphics::width  = GetDeviceCaps( screen, HORZRES ) / 2;
            Graphics::height = GetDeviceCaps( screen, VERTRES ) / 2;

            if( ReleaseDC( 0, screen ) != 1 )
            {
               Error( " WindowProc(...) ReleaseDC(...) error " );
            }
         }

         return 0;
      }

   case WM_CHANGEWINDOWSTYLE:

      if( IsApplicationMinimized == false )
      {
         IsWindowStyleChanging = true;

         if( !DestroyWindow( hwnd ) )
         {
            Error( " The function DestroyWindow(...) has failed in the function WindowProc(...). " );
         }

         RemoveHandle( hwnd );

         if( WindowStyle::getStyle() == Graphics::GRAPHICS_WINDOW )
         {
            POINT origin = WindowStyle::getOrigin();

            POINT size = WindowStyle::getSize( true );

            RECT menu = WindowStyle::getMenuRect();

            assert( size.x > 0 && size.y > 0 && " size.x > 0 && size.y > 0 " );

            hWindow = CreateWindow( appClassName,
                                    appName,
                                    WS_OVERLAPPEDWINDOW,
                                    origin.x - menu.left,
                                    origin.y - menu.top,
                                    size.x + menu.left + menu.right,
                                    size.y + menu.top + menu.bottom,
                                    0,
                                    0,
                                    hInstance,
                                    0
                                  );

            Graphics::width = size.x;
            Graphics::height = size.y;
         }
         else
         {
            hWindow = CreateWindow( appClassName,
                                    appName,
                                    WS_POPUP,
                                    0,
                                    0,
                                    Graphics::oldWidth,
                                    Graphics::oldHeight,
                                    0,
                                    0,
                                    hInstance,
                                    0
                                  );

            Graphics::width = Graphics::oldWidth;
            Graphics::height = Graphics::oldHeight;
         }

         ShowWindow( hWindow, SW_SHOW );

         hwnd = hWindow;

         Graphics::_hWindow = hWindow;

         InsertHandle( hwnd );

         unsigned short widthHeight[ 2 ] = { 0 };
      
         widthHeight[ 0 ] = (unsigned short) Graphics::oldWidth;
         widthHeight[ 1 ] = (unsigned short) Graphics::oldHeight;

         IsApplicationMinimized = false;

         WindowProc( hwnd,
                     WM_DISPLAYCHANGE,
                     Graphics::oldBitDepth,
                     *( (unsigned long*) widthHeight )
                   );

         IsWindowStyleChanging = false;
      }

      return 0;
      
   case WM_MOUSEMOVE:
      
      input->push( pairQI( mousePt, UPDATE_INPUT ) );
      
      prevPt = mousePt;
      
      return 0;
      
   case WM_LBUTTONDOWN:
      
      IsLeftMouseButtonDown = true;
      
      input->push( pairQI( mousePt, 8 | orInput ) );
      
      SetCapture( hwnd );
      
      return 0;
      
   case WM_LBUTTONUP:
      
      IsLeftMouseButtonDown = false;
      
      input->push( pairQI( mousePt, DUMP_ALL_CAPTURES ) );
      
      ReleaseCapture();
      
      return 0;
      
   case WM_RBUTTONDOWN:
      
      IsRightMouseButtonDown = true;
      
      input->push( pairQI( mousePt, 16 | orInput ) );
      
      SetCapture( hwnd );
      
      return 0;
      
   case WM_RBUTTONUP:
      
      IsRightMouseButtonDown = false;
      
      input->push( pairQI( mousePt, DUMP_ALL_CAPTURES ) );
      
      ReleaseCapture();
      
      return 0;
      
   case WM_SETFOCUS:
      
      IsApplicationTopMost = true;
      
      return 0;
      
   case WM_KILLFOCUS:
      
      IsApplicationTopMost = false;
      
      IsLeftMouseButtonDown = false;
      IsRightMouseButtonDown = false;
      
      ReleaseCapture();
      
   case WM_CAPTURECHANGED:
      
      return 0;

   case WM_SYSCOMMAND:

      if( ( wParam & 0xfff0 ) != SC_MAXIMIZE )
      {
         // We need help from DefWindowProc(...).
         break;
      }

      WindowStyle::setStyle();

      WindowProc( hwnd, WM_CHANGEWINDOWSTYLE, 0, 0 );

      return 0;

   case WM_NCLBUTTONDBLCLK:

      if( wParam != HTCAPTION )
      {
         // We need help from DefWindowProc(...).
         break;
      }

      WindowStyle::setStyle();

      WindowProc( hwnd, WM_CHANGEWINDOWSTYLE, 0, 0 );

      return 0;

   case WM_SYSKEYDOWN:

      if( wParam == VK_RETURN && ( lParam & ( 1 << 29 ) ) )
      {
         WindowStyle::setStyle();

         WindowProc( hwnd, WM_CHANGEWINDOWSTYLE, 0, 0 );
      }
      else if( wParam == VK_F10 )
      {
         DialogBox( hInstance, "ExtraBox", hwnd, AboutDlgProc );

         // WinExec( "de_Casteljau ExtraBox.exe", 0 );

         return 0;
      }

      break;
      
   case WM_KEYDOWN:
      
      switch( wParam )
      {
      case VK_ESCAPE:
         
         Warning( " escape key hit - quitting application " );
         
         PostMessage( hwnd, WM_DESTROY, 0, 0 );
         
         return 0;
         
      case VK_F1:
         
         orInput = 0;
         
         return 0;
         
      case VK_F2:
         
         orInput = 1;
         
         return 0;
         
      case VK_F3:
         
         orInput = 2;
         
         return 0;
         
      case VK_F4:
         
         orInput = 4;
         
         return 0;
         
      case VK_F5:
         
         IsLeftMouseButtonDown = false;
         IsRightMouseButtonDown = false;
         
         input->push( pairQI( mousePt, TOGGLE_SHELLS ) );
         
         ReleaseCapture();
         
         return 0;
         
      case VK_F6:
         
         IsLeftMouseButtonDown = false;
         IsRightMouseButtonDown = false;
         
         input->push( pairQI( mousePt, DUMP_ALL_CAPTURES ) );
         
         ReleaseCapture();
         
         return 0;
         
      case VK_F7:
         
         if( DialogBox( hInstance, "InputBox", hwnd, InputDlgProc ) == 0 )
         {
            IsLeftMouseButtonDown = false;
            IsRightMouseButtonDown = false;
            
            union
            {
               double *p;
               double f;
               POINT pt;
               
            }menu;
            
            union
            {
               double *p;
               double f;
               
            }menu2;
            
            assert( sizeof( menu ) == sizeof( menu2 ) );
            
            memset( &menu, 0, sizeof( menu ) );
            memset( &menu2, 0, sizeof( menu2 ) );
            
            menu.p = menuArray;
            
            menuArray[ 11 ] = mousePt.x;
            menuArray[ 12 ] = mousePt.y;
            
            input->push( pairQI( menu.pt, MENU_INPUT ) );
            
            //////////////////////////////////////////////////////////////////
            input->push( pairQI( mousePt, UPDATE_INPUT ) );
            
            input->push( pairQI( mousePt, CAPTURE_TRANSLATE ) );
            
            POINT transPt = { mousePt.x + Graphics::graphicsClientWidth() / 2,
                              mousePt.y + Graphics::graphicsClientHeight() / 2
                            };
            
            input->push( pairQI( transPt, UPDATE_INPUT ) );
            
            input->push( pairQI( transPt, DUMP_ALL_CAPTURES ) );
            
            //////////////////////////////////////////////////////////////////
            input->push( pairQI( mousePt, UPDATE_INPUT ) );
            
            input->push( pairQI( mousePt, CAPTURE_SCALE ) );
            
            POINT scalePt = { mousePt.x + Graphics::graphicsClientWidth() / 2,
                              mousePt.y + Graphics::graphicsClientWidth() / 2
                            };
            
            input->push( pairQI( scalePt, UPDATE_INPUT ) );
            
            int loop = 0;
            
            while( ++loop < 8 )
            {
               scalePt.x += Graphics::graphicsClientWidth() / 2;
               scalePt.y += Graphics::graphicsClientWidth() / 2;
               
               input->push( pairQI( scalePt, UPDATE_INPUT ) );
            }
            
            input->push( pairQI( scalePt, DUMP_ALL_CAPTURES ) );
            //////////////////////////////////////////////////////////////////
            
            input->push( pairQI( mousePt, UPDATE_INPUT ) );
            
            ReleaseCapture();
         }
         
         return 0;
         
      case VK_F8:

         DialogBox( hInstance, "HelpBox", hwnd, AboutDlgProc );

         // WinExec( "de_Casteljau HelpBox.exe", 0 );
         
         return 0;
         
      case VK_F9:

         DialogBox( hInstance, "AboutBox", hwnd, AboutDlgProc );

         // WinExec( "de_Casteljau AboutBox.exe", 0 );
         
         return 0;

      case 49:
      case VK_NUMPAD1:

         IsLeftMouseButtonDown = false;
         IsRightMouseButtonDown = false;
         
         input->push( pairQI( mousePt, TOGGLE_CONTROL_POINTS ) );
         
         ReleaseCapture();

         return 0;

      case 50:
      case VK_NUMPAD2:

         IsLeftMouseButtonDown = false;
         IsRightMouseButtonDown = false;
         
         input->push( pairQI( mousePt, ADD_DE_CASTELJAU_CURVE ) );
         
         ReleaseCapture();

         return 0;

      case 51:
      case VK_NUMPAD3:
         
         input->push( pairQI( mousePt, REMOVE_DE_CASTELJAU_CURVE ) );
         
         ReleaseCapture();

         return 0;

      case 52:
      case VK_NUMPAD4:

         IsLeftMouseButtonDown = false;
         IsRightMouseButtonDown = false;
         
         input->push( pairQI( mousePt, TRAVERSE_DE_CASTELJAU_CURVE_LIST ) );
         
         ReleaseCapture();

         return 0;

      case 53:
      case VK_NUMPAD5:

         return 0;

      case 54:
      case VK_NUMPAD6:

         return 0;

      case 55:
      case VK_NUMPAD7:

         return 0;

      case 56:
      case VK_NUMPAD8:

         return 0;

      case 57:
      case VK_NUMPAD9:

         return 0;

      case VK_ADD:

         IsLeftMouseButtonDown = false;
         IsRightMouseButtonDown = false;
         
         input->push( pairQI( mousePt, INCREASE_ITERATION_CONSTANT ) );
         
         ReleaseCapture();

         return 0;

      case VK_SUBTRACT:

         IsLeftMouseButtonDown = false;
         IsRightMouseButtonDown = false;
         
         input->push( pairQI( mousePt, DECREASE_ITERATION_CONSTANT ) );
         
         ReleaseCapture();

         return 0;
      }
      
      return 0;

   case WM_MOVE:
   case WM_MOVING:

      if( Graphics::graphicsBackBufferFunction() &&
          Graphics::graphicsIsModeChangeActive() == false  &&
          WindowStyle::getStyle() != Graphics::GRAPHICS_FULLSCREEN &&
          IsWindowStyleChanging == false
        )
      {
         POINT trans = { 0, 0 };

         BOOL returnVal = ClientToScreen( hwnd, &trans );

         WindowStyle::setOrigin( trans.x, trans.y );

         main( UPDATE_INPUT,
               mousePt.x,
               mousePt.y,
               (double) Graphics::graphicsClientWidth() * 0.5,
               (double) Graphics::graphicsClientHeight() * 0.5
             );
      
         Graphics::graphicsDrawBackBufferToScreen( hwnd );
      
         Sleep( 1 );
      }
      
      // We need help from DefWindowProc(...).
      break;

   case WM_SIZE:

	   if( wParam == SIZE_MAXHIDE   ||
		    wParam == SIZE_MAXIMIZED ||
		    wParam == SIZE_MAXSHOW   ||
		    wParam == SIZE_MINIMIZED
		  )
	   {
         if( wParam == SIZE_MINIMIZED )
         {
            IsApplicationMinimized = true;

            // We need help from DefWindowProc(...).
            break;
         }

		   Error( " Incorrect WM_SIZE message in WindowProc(...) " );

         assert( 0 && " Incorrect WM_SIZE message in WindowProc(...) " );

         return 0;
	   }

      if( wParam == SIZE_RESTORED && IsApplicationMinimized == true )
      {
         unsigned short widthHeight[ 2 ] = { 0 };
      
         widthHeight[ 0 ] = (unsigned short) Graphics::oldWidth;
         widthHeight[ 1 ] = (unsigned short) Graphics::oldHeight;

         IsApplicationMinimized = false;

         WindowProc( hwnd,
                     WM_DISPLAYCHANGE,
                     Graphics::oldBitDepth,
                     *( (unsigned long*) widthHeight )
                   );

         // We need help from DefWindowProc(...).
         break;
      }

   case WM_SIZING:

      if( Graphics::graphicsBackBufferFunction() &&
          Graphics::graphicsIsModeChangeActive() == false &&
          IsWindowStyleChanging == false
        )
      {
         static double scaleTime = 0;

         RECT *rect = (LPRECT) lParam;

         if( msg == WM_SIZE )
         {
            rect = (RECT*) InsertHeapAllocation( sizeof( RECT ) );

            if( rect == 0 )
            {
               Error( " WM_SIZE new RECT allocation failure " );

               // We need help from DefWindowProc(...).
               break;
            }

            rect->left = 0;
            rect->top  = 0;

            rect->right = LOWORD( lParam );
            rect->bottom = HIWORD( lParam );
         }
         else
         {
            updateTime();

            if( scaleTime > timeInSeconds() )
            {
               // We need help from DefWindowProc(...).
               break;
            }

            scaleTime = timeInSeconds() + 0.5;
         }

         WindowStyle::setSize( rect->right - rect->left,
                               rect->bottom - rect->top
                             );

         if( rect->right - rect->left <= 0 ||
             rect->bottom - rect->top <= 0
           )
         {
            IsApplicationMinimized = true;

            if( msg == WM_SIZE )
            {
               RemoveHeapAllocation( rect );
            }

            PostMessage( hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0 );

            // We need help from DefWindowProc(...).
            break;
         }
         else if( WindowStyle::getStyle() == Graphics::GRAPHICS_FULLSCREEN )
         {
            if( msg == WM_SIZE )
            {
               RemoveHeapAllocation( rect );
            }

            WindowProc( hwnd, WM_CHANGEWINDOWSTYLE, 0, 0 );

            return 0;
         }

         main( DUMP_ALL_CAPTURES,
               mousePt.x,
               mousePt.y,
               (double) Graphics::graphicsClientWidth() * 0.5,
               (double) Graphics::graphicsClientHeight() * 0.5
             );

         TextOutTermSystem();
         
         RemoveHandle( TextOutInitSystem );

         Graphics::graphicsTermScreenAndBackBuffer();

         Graphics::width = rect->right - rect->left;
         Graphics::height = rect->bottom - rect->top;

         if( Graphics::graphicsInitScreenAndBackBuffer( hwnd ) != Graphics::GRAPHICS_OK )
         {
            Error( " Graphics::graphicsInitScreenAndBackBuffer(...) != Graphics::GRAPHICS_OK " );
            
            if( !DestroyWindow( hwnd ) )
            {
               Error( " The function DestroyWindow(...) has failed in the function WindowProc(...). " );
            }

            if( msg == WM_SIZE )
            {
               RemoveHeapAllocation( rect );
            }
            
            // There is an error, so we do not need held from DefWindowProc(...).
            return 0;
         }

         InsertHandle( TextOutInitSystem );

         Sleep( 1 );

         if( msg == WM_SIZE )
         {
            RemoveHeapAllocation( rect );
         }
      }

      // We need help from DefWindowProc(...).
      break;
      
      // MSDN:
      // An application sends the WM_PAINT message when the system or another
      // application makes a request to paint a portion of an application's window.
      // The message is sent when the UpdateWindow or RedrawWindow function is called,
      // or by theDispatchMessage function when the application obtains a WM_PAINT
      // message by using theGetMessage orPeekMessage function.
      //
      // An application returns zero if it processes this message.
   case WM_PAINT:

      return 0;
      
      // MSDN:
      // An application sends the WM_ERASEBKGND message when the window background
      // must be erased (for example, when a window is resized). The message is sent
      // to prepare an invalidated portion of a window for painting.
      //
      // An application should return nonzero if it erases the background;
      // otherwise, it should return zero.
   case WM_ERASEBKGND:
      // return nonzero to make believe the background was erased
      return 1;
      
   case WM_DISPLAYCHANGE:
      
      if( Graphics::graphicsIsModeChangeActive() == false )
      {
         if( IsApplicationMinimized == true )
         {
            Graphics::oldBitDepth = wParam;
            Graphics::oldWidth    = LOWORD( lParam );
            Graphics::oldHeight   = HIWORD( lParam );

            return 0;
         }

         TextOutTermSystem();
         
         RemoveHandle( TextOutInitSystem );

         if( Graphics::width  != Graphics::oldWidth ||
             Graphics::height != Graphics::oldHeight
           )
         {
            if( WindowStyle::getStyle() == Graphics::GRAPHICS_FULLSCREEN )
            {
               WindowStyle::setStyle();
            }
         }
         
         Graphics::oldBitDepth = wParam;
         Graphics::oldWidth    = LOWORD( lParam );
         Graphics::oldHeight   = HIWORD( lParam );
         
         Graphics::graphicsTermScreenAndBackBuffer();

         if( WindowStyle::getStyle() == Graphics::GRAPHICS_FULLSCREEN )
         {
            Graphics::width = Graphics::oldWidth;

            Graphics::height = Graphics::oldHeight;
         }
         else if( WindowStyle::getSize( false ).x + WindowStyle::getMenuRect().left + WindowStyle::getMenuRect().right >= Graphics::oldWidth ||
                  WindowStyle::getSize( false ).y + WindowStyle::getMenuRect().top + WindowStyle::getMenuRect().bottom >= Graphics::oldHeight
                )
         {
            WindowStyle::setStyle();

            WindowProc( hwnd, WM_CHANGEWINDOWSTYLE, 0, 0 );

            return 0;
         }
         
         if( Graphics::graphicsInitScreenAndBackBuffer( hwnd ) != Graphics::GRAPHICS_OK )
         {
            Error( " Graphics::graphicsInitScreenAndBackBuffer(...) != Graphics::GRAPHICS_OK " );
            
            if( !DestroyWindow( hwnd ) )
            {
               Error( " The function DestroyWindow(...) has failed in the function WindowProc(...). " );
            }
            
            return 0;
         }
         
         InsertHandle( TextOutInitSystem );

         if( isMenuActive == true )
         {
            main( DUMP_ALL_CAPTURES,
                  mousePt.x,
                  mousePt.y,
                  (double) Graphics::graphicsClientWidth() * 0.5,
                  (double) Graphics::graphicsClientHeight() * 0.5
                );
         }
         else
         {
            input->push( pairQI( mousePt, DUMP_ALL_CAPTURES ) );
         }
      }
      
      return 0;
      
      // MSDN:
      // The WM_CLOSE message is sent as a signal
      // that a window or an application should terminate.
      //
      // The DefWindowProc function calls the DestroyWindow
      // function to destroy the window ( since I handle it, I call it myself ).
      //
      // If an application processes this message, it should return zero.
   case WM_CLOSE:
      // MSDN:
      // The DestroyWindow function destroys the specified window.
      // The function sends WM_DESTROY and WM_NCDESTROY messages to the window.
      if( !DestroyWindow( hwnd ) )
      {
         Error( " The function DestroyWindow(...) has failed in the function WindowProc(...). " );
      }
      
      return 0;
      
      // MSDN:
      // The WM_DESTROY message is sent when a window is being destroyed.
      //
      // If an application processes this message, it should return zero.
   case WM_DESTROY:

      if( IsWindowStyleChanging == true )
      {
         return 0;
      }

      mainTerm( hwnd );
      
      // MSDN:
      // The PostQuitMessage function indicates to the system
      // that a thread has made a request to terminate (quit).
      // It is typically used in response to a WM_DESTROY message.
      //
      // Parameters -> nExitCode:
      //     Specifies an application exit code. This value is used
      //     as the wParam parameter of the WM_QUIT message.
      PostQuitMessage( 0 );

      IsApplicationEntry = false;
      
      // MSDN:
      // Terminate the calling process after cleanup
      //
      // Performs complete C library termination procedures, terminates
      // the process, and exits with the supplied status code.
      exit( 0 );
      
      return 0;
      
      // MSDN:
      // The WM_QUIT message indicates a request to terminate an application and
      // is generated when the application calls the PostQuitMessage function.
      // It causes the GetMessage function to return zero.
      //
      // This message does not have a return value, because it causes
      // the message loop to terminate before the message is sent to the
      // application's window procedure.
   case WM_QUIT:
      
      return wParam;
   }
    
    // MSDN:
    // The DefWindowProc function calls the default window procedure
    // to provide default processing for any window messages that an
    // application does not process. This function ensures that every
    // message is processed. DefWindowProc is called with the same
    // parameters received by the window procedure.
    //
    // The return value is the result of the message
    // processing and depends on the message.
    return DefWindowProc( hwnd, msg, wParam, lParam );
}

#pragma warning ( default: 4702 )

static HANDLE    mutexHandle =   0;
static HINSTANCE _hInstance  =   0;
static WNDCLASS  windowClass = { 0 };

// Keep track of how many handles have been opened
static PLIST_HEAD listOfHandles = 0;

// Keep track of how many allocations there are on the heap
static PLIST_HEAD listOfHeapAllocations = 0;

static int RemoveHeapAllocation( void *heapAllocation
                               )
{
   int           functionReturnValue =   0;
   CLIENT_POTYPE Object              = { 0 };
   
   if( ( !heapAllocation ) || ( heapAllocation == ( (void*) 0xffffffff ) ) )
   {
      Error( " RemoveHeapAllocation -- heapAllocation == NULL " );
      
      return -1;
   }
   
   if( !listOfHeapAllocations )
   {
      Error( " RemoveHeapAllocation -- listOfHeapAllocations == NULL " );
      
      return -1;
   }
   
   Object.object = heapAllocation;
   
   functionReturnValue = ListRemove( listOfHeapAllocations, TestObject, &Object );
   
   if( !( functionReturnValue == 0 && Object.object == heapAllocation ) )
   {
      Error( " ListRemove failure -- unknown heap allocation " );
      
      return -1;
   }
   else
   {
      free( heapAllocation );
   }
   
   return 0;
}

static int RemoveHandle( void *handle
                       )
{
   int           functionReturnValue =   0;
   CLIENT_POTYPE Object              = { 0 };
   
   if( !handle )
   {
      Error( " RemoveHandle -- handle == NULL " );
      
      return -1;
   }
   
   if( !listOfHandles )
   {
      Error( " RemoveHandle -- listOfHandles == NULL " );
      
      return -1;
   }
   
   Object.object = handle;
   
   functionReturnValue = ListRemove( listOfHandles, TestObject, &Object );
   
   if( !( functionReturnValue == 0 && Object.object == handle ) )
   {
      Error( " ListRemove failure -- unknown handle " );
      
      return -1;
   }
   
   return 0;
}

extern void* operator new( size_t size
                         ) throw( bad_alloc )
{
   if( IsApplicationEntry == false )
   {
      return malloc( size );
   }

	void *new_memory = InsertHeapAllocation( size );

	return( new_memory );
}

extern void* operator new[]( size_t size
                           ) throw( bad_alloc )
{
   if( IsApplicationEntry == false )
   {
      return malloc( size );
   }

	void *new_memory = InsertHeapAllocation( size );

	return( new_memory );
}

extern void operator delete( void* ptr
                           ) throw()
{
   if( IsApplicationEntry == false )
   {
      free( ptr );

      return;
   }

	if( ptr )
   {
      RemoveHeapAllocation( ptr );
   }
}

extern void operator delete[]( void* ptr
                             ) throw()
{
   if( IsApplicationEntry == false )
   {
      free( ptr );

      return;
   }

	if( ptr )
   {
	   RemoveHeapAllocation( ptr );
   }
}

const unsigned int HEAP_ALLOCATION_ERROR = 0xffffffff;

static void* InsertHeapAllocation( size_t numBytesToAllocate
                                 )
{
   int           functionReturnValue =   0;
   void          *heapAllocation     =   0;
   
   CLIENT_POTYPE Object              = { 0 };
   
   SetLastError( HEAP_ALLOCATION_ERROR );
   
   if( !listOfHeapAllocations )
   {
      Error( " InsertHeapAllocation -- listOfHeapAllocations == NULL " );
      
      return 0;
   }
   
   heapAllocation = calloc( numBytesToAllocate, 1 );
   
   if( !heapAllocation )
   {
      Error( " InsertHeapAllocation -- heapAllocation == NULL " );
      
      return 0;
   }
   
   Object.object = heapAllocation;
   
   functionReturnValue = ListInsert( listOfHeapAllocations, Object, 0 );
   
   if( functionReturnValue != 0 )
   {
      Error( " ListInsert failure -- heap allocation not inserted and freed " );
      
      free( heapAllocation );
   }
   else
   {
      SetLastError( ERROR_SUCCESS );
      
      return heapAllocation;
   }
   
   Error( " InsertHeapAllocation -- should never get to this line of code. " );
   
   return 0;
}

static int InsertHandle( void *handle
                       )
{
   int           functionReturnValue =   0;
   
   CLIENT_POTYPE Object              = { 0 };
   
   if( !handle )
   {
      Error( " InsertHandle -- handle == NULL " );
      
      return -1;
   }
   
   if( !listOfHandles )
   {
      Error( " InsertHandle -- listOfHandles == NULL " );
      
      return -1;
   }
   
   Object.object = handle;
   
   functionReturnValue = ListInsert( listOfHandles, Object, 0 );
   
   if( functionReturnValue != 0 )
   {
      Error( " ListInsert failure -- handle not inserted " );
      
      return -1;
   }
   
   return 0;
}

static int mainTerm( HWND hwnd
                   )
{
   int           error               =   0;
   
   int           numberOfObjects     =   0;
   
   int           functionReturnValue =   0;
   
   CLIENT_POTYPE Object              = { 0 };


   while( !input->empty() )
   {
      input->pop();
   }

   delete input;

   input = 0;

   
   if( term() != 0 )
   {
      Warning( " Client term(...) function returns nonzero value. " );
   }
   
   RemoveHandle( hwnd );
   
   TextOutTermSystem();
   
   RemoveHandle( TextOutInitSystem );
   
   Graphics::graphicsTermScreenAndBackBuffer();
   
   // Unregister the class.
   // All window classes that an application registers
   // are unregistered when it terminates!!!!!
   //
   // UnregisterClass will always fail since the window will
   // always still be open.  By the time I have the ability
   // to unregister the class, it has already been done for
   // me by the OS, as is stated in MSDN.
   //
   // Remove the class handle from the list, we do not
   // need to call UnregisterClass, nor can we.
   //
   // If unregister class works, remove the class handle
   // from the handle list.
   //
   // As long as the window is properly destroyed, the class
   // will always be unregistered automatically.
   RemoveHandle( (void*) &windowClass );
   
   if( !CloseHandle( mutexHandle ) )
   {
      Error( " CloseHandle(...) failure " );
      
      error = -1;
   }
   // If CloseHandle works, remove the handle
   // from the handle list.
   else
   {
      RemoveHandle( (void*) mutexHandle );
   }
   
   
   functionReturnValue = ListIsEmpty( listOfHeapAllocations, &numberOfObjects );
   
   // At the time we call ListIsEmpty, all heap allocated variables
   // should have been freed.  listOfHeapAllocations should be empty.
   if( !( functionReturnValue == 1 && numberOfObjects == 0 ) )
   {
      // Error( " listOfHeapAllocations is not empty " );

      CLIENT_POTYPE object = { 0 };
      
      while( ListGetNext( listOfHeapAllocations, &object, 1 ) == 0 )
      {
         if( RemoveHeapAllocation( object.object ) != 0 )
         {
            Error( " RemoveHeapAllocation(...) function failure " );
         }
      }
      
      error = -1;
   }
   
   
   // Check if the three handles that should be in the handle list are
   // really in the handle list.
   
   Object.object = file;
   
   functionReturnValue = ListFind( listOfHandles, TestObject, &Object );
   
   if( !( functionReturnValue == 0 && Object.object == file ) )
   {
      Error( " listOfHandles -- file not in handle list -- why not? " );
      
      error = -1;
   }
   
   Object.object = listOfHandles;
   
   functionReturnValue = ListFind( listOfHandles, TestObject, &Object );
   
   if( !( functionReturnValue == 0 && Object.object == listOfHandles ) )
   {
      Error( " listOfHandles -- listOfHandles not in handle list -- why not? " );
      
      error = -1;
   }
   
   Object.object = listOfHeapAllocations;
   
   functionReturnValue = ListFind( listOfHandles, TestObject, &Object );
   
   if( !( functionReturnValue == 0 && Object.object == listOfHeapAllocations ) )
   {
      Error( " listOfHandles -- listOfHeapAllocations not in handle list -- why not? " );
      
      error = -1;
   }
   
   
   functionReturnValue = ListIsEmpty( listOfHandles, &numberOfObjects );
   
   // At the time we call ListIsEmpty, there should be 3 handles left:
   // file, listOfHandles, and listOfHeapAllocations.
   if( !( functionReturnValue == 0 && numberOfObjects == 3 ) )
   {
      Error( " listOfHandles is not empty " );
      
      error = -1;
   }
   
   
   if( file != ( (FILE*) 0xff ) )
   {
      if( fclose( file ) != 0 )
      {
         Error( " fclose(...) failure " );
         
         error = -1;
      }
   }
   
   ListTerminate( listOfHeapAllocations );
   
   ListTerminate( listOfHandles );
   
   return error;
}

static double _timeTicksPerSecond = 0,
              _timeInSeconds      = 0,
              _timeDelta          = 0,
              _timeStart          = 0;

static double timeDeltaInSeconds(
                                )
{
   return _timeDelta;
}

static double timeInSeconds(
                           )
{
   return _timeInSeconds;
}

static int initTime(
                   )
{
   int error = 0;
   
   LARGE_INTEGER temp = { 0 };
   
   if( !QueryPerformanceFrequency( &temp ) )
   {
      Error( " QueryPerformanceFrequency(...) function failure " );
      
      error = -1;
   }
   
   _timeTicksPerSecond = (double) temp.LowPart;
   
   if( !QueryPerformanceCounter( &temp ) )
   {
      Error( " QueryPerformanceCounter(...) function failure " );
      
      error = -1;
   }
   
   _timeInSeconds  = (double) temp.LowPart;
   
   _timeInSeconds /= _timeTicksPerSecond;
   
   _timeStart      = _timeInSeconds;
   
   return error;
}

static int updateTime(
                     )
{
   int           error        =   0;
   
   double        previousTime =   0;
   
   LARGE_INTEGER temp         = { 0 };
   
   if( !QueryPerformanceCounter( &temp ) )
   {
      Error( " QueryPerformanceCounter(...) function failure " );
      
      error = -1;
   }
   
   previousTime    = _timeInSeconds;
   
   _timeInSeconds  = (double) temp.LowPart;
   
   _timeInSeconds /= _timeTicksPerSecond;
   
   _timeDelta      = _timeInSeconds - previousTime;
   
   return error;
}

// MSDN
// hPrevInstance 
//     Handle to the previous instance of the application. For a Win32-based
//     application, this parameter is always NULL.
//
//     If you need to detect whether another instance already exists, create a
//     uniquely named mutex using the CreateMutex function. CreateMutex will
//     succeed even if the mutex already exists, but the GetLastError function
//     will return ERROR_ALREADY_EXISTS. This indicates that another instance of
//     your application exists, because it created the mutex first.

int WINAPI WinMain( HINSTANCE    hInstance,        // handle to current instance
                    HINSTANCE /* hPrevInstance */, // handle to previous instance
                    char*     /* lpCmdLine     */, // pointer to command line
                    int          nCmdShow          // show state of window
                  )
{
   int   currentFrameNumber =   0;
   
   int   retVal             =   0;
   
   int   windowType         =   0;
   
   RECT  windowRect         = { 0 };
   
   MSG   Message            = { 0 };
   
   _hInstance = hInstance;

   IsApplicationEntry = true;
   
   // Only allow one instance of the application at a time.  Use CreateMutex
   // to test if an instance of the application already exists, quit if
   // another instance exists or if CreateMutex returns NULL.
   mutexHandle = CreateMutex( 0, FALSE, "FunkyLovinNicoleSugarDaddy" );
   
   if( !mutexHandle )
   {
      // Use MessageBox until we make sure that this is the only instance
      // of the application.  Then we can set up the log file.
      ErrorBox( " ( MutexHandle = CreateMutex(...) ) == NULL " );

      IsApplicationEntry = false;
      
      return 0;
   }
   
   if( GetLastError() == ERROR_ALREADY_EXISTS )
   {
      if( !CloseHandle( mutexHandle ) )
      {
         ErrorBox( " CloseHandle(...) failure " );
      }

      IsApplicationEntry = false;

      return 0;
   }
   
   // 1) Initialize the log file for logging warnings and errors.
   file = fopen( "cs250_os_debug.txt", "wb" );
   
#ifndef NDEBUG

   // Quit if the log file handle was not created.
   if( !file )
   {
      if( !CloseHandle( mutexHandle ) )
      {
         ErrorBox( " CloseHandle(...) failure " );
      }
      
      ErrorBox( " ( file = fopen(...) ) == NULL " );

      IsApplicationEntry = false;
      
      return 0;
   }

#else

   if( !file )
   {
      file = ( (FILE*) 0xff );
   }

#endif
   
   // Copyright 1999-2000 Bruce Dawson. ~ start
   // Bruce Dawson, a man of integrity.
   
   // 6) Set _CrtSetDbgFlag to keep track of allocations on the heap
   _CrtSetDbgFlag( _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG ) | _CRTDBG_LEAK_CHECK_DF );
   
   // Enable floating point exceptions to track down bad floating point usage.
   // _controlfp( 0, _EM_ZERODIVIDE | _EM_INVALID );
   
   // Copyright 1999-2000 Bruce Dawson. ~ end
   
   listOfHandles         = ListInit( 0, 20 );
   listOfHeapAllocations = ListInit( 0, 20 );
   
   if( !listOfHandles )
   {
      Error( " ( listOfHandles = ListInit(...) ) == NULL " );
      
      if( !CloseHandle( mutexHandle ) )
      {
         Error( " CloseHandle(...) failure " );
      }
      
      if( file != ( (FILE*) 0xff ) )
      {
         if( fclose( file ) != 0 )
         {
            Error( " fclose(...) failure " );
         }
      }

      IsApplicationEntry = false;
      
      return 0;
   }
   
   if( !listOfHeapAllocations )
   {
      ListTerminate( listOfHandles );
      
      Error( " ( listOfHeapAllocations = ListInit(...) ) == NULL " );
      
      if( !CloseHandle( mutexHandle ) )
      {
         Error( " CloseHandle(...) failure " );
      }
      
      if( file != ( (FILE*) 0xff ) )
      {
         if( fclose( file ) != 0 )
         {
            Error( " fclose(...) failure " );
         }
      }

      IsApplicationEntry = false;
      
      return 0;
   }
   
   // -1-
   InsertHandle( listOfHandles         );
   // -2-
   InsertHandle( listOfHeapAllocations );
   // -3-
   InsertHandle( mutexHandle           );
   // -4-
   InsertHandle( file                  );
   
   // 7) Create an application with a client area 640 by 480
   //    using RegisterClass and CreateWindow
   windowClass.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
   windowClass.lpfnWndProc   = Graphics::WindowProc;
   windowClass.cbClsExtra    = 0;
   windowClass.cbWndExtra    = 0;
   windowClass.hInstance     = hInstance;
   windowClass.hIcon         = LoadIcon( hInstance, "HELL_ON_EARTH_ICON" );
   windowClass.hCursor       = LoadCursor( NULL, IDC_ARROW );
   windowClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
   windowClass.lpszMenuName  = 0;
   windowClass.lpszClassName = appClassName;
   
   if ( !RegisterClass( &windowClass ) )
   {
      int numberOfObjects = 0;
      
      Error( " RegisterClass(...) == 0 " );
      
      if( !CloseHandle( mutexHandle ) )
      {
         Error( " CloseHandle(...) failure " );
      }
      else
      {
         RemoveHandle( mutexHandle );
      }
      
      if( file != ( (FILE*) 0xff ) )
      {
         if( fclose( file ) != 0 )
         {
            Error( " fclose(...) failure " );
         }
         else
         {
            RemoveHandle( file );
         }
      }
      else
      {
         RemoveHandle( file );
      }
      
      if( ListIsEmpty( listOfHeapAllocations, 0 ) != 1 )
      {
         Error( " listOfHeapAllocations is not empty " );
      }
      
      ListTerminate( listOfHeapAllocations );
      
      
      RemoveHandle( listOfHeapAllocations );
      
      ListIsEmpty( listOfHandles, &numberOfObjects );
      
      if( numberOfObjects != 1 )
      {
         Error( " listOfHandles is not empty " );
      }
      
      ListTerminate( listOfHandles );

      IsApplicationEntry = false;
      
      return 0;
   }
   
   // -5-
   InsertHandle( &windowClass );

   Graphics::WindowProc( 0, WM_SETWIDTHHEIGHT, 0, 0 );
   
   windowRect.left   = 0;
   windowRect.top    = 0;
   windowRect.right  = Graphics::graphicsClientWidth();
   windowRect.bottom = Graphics::graphicsClientHeight();
   
   windowType = Graphics::graphicsCheckIsFullScreen();
   
   if( windowType == Graphics::GRAPHICS_ERROR ||
       (
         !( windowType == Graphics::GRAPHICS_WINDOW ||
            windowType == Graphics::GRAPHICS_FULLSCREEN
          )
       )
     )
   {
      int numberOfObjects = 0;
      
      Error( " graphicsCheckIsFullScreen(...) == GRAPHICS_ERROR " );
      
      if( !UnregisterClass( appClassName, _hInstance ) )
      {
         Error( " UnregisterClass(...) failure " );
      }
      else
      {
         RemoveHandle( &windowClass );
      }
      
      if( !CloseHandle( mutexHandle ) )
      {
         Error( " CloseHandle(...) failure " );
      }
      else
      {
         RemoveHandle( mutexHandle );
      }
      
      if( file != ( (FILE*) 0xff ) )
      {
         if( fclose( file ) != 0 )
         {
            Error( " fclose(...) failure " );
         }
         else
         {
            RemoveHandle( file );
         }
      }
      else
      {
         RemoveHandle( file );
      }
      
      if( ListIsEmpty( listOfHeapAllocations, 0 ) != 1 )
      {
         Error( " listOfHeapAllocations is not empty " );
      }
      
      ListTerminate( listOfHeapAllocations );
      
      
      RemoveHandle( listOfHeapAllocations );
      
      ListIsEmpty( listOfHandles, &numberOfObjects );
      
      if( numberOfObjects != 1 )
      {
         Error( " listOfHandles is not empty " );
      }
      
      ListTerminate( listOfHandles );

      IsApplicationEntry = false;
      
      return 0;
   }
   
   if( windowType == Graphics::GRAPHICS_WINDOW )
   {
      windowType = WS_OVERLAPPEDWINDOW;
   }
   else if( windowType == Graphics::GRAPHICS_FULLSCREEN )
   {
      windowType = WS_POPUP;
   }
   
   if ( !AdjustWindowRect( &windowRect,
                           windowType,
                           FALSE
                         )
      )
   {
      int numberOfObjects = 0;
      
      Error( " AdjustWindowRect(...) == 0 " );
      
      if( !UnregisterClass( appClassName, _hInstance ) )
      {
         Error( " UnregisterClass(...) failure " );
      }
      else
      {
         RemoveHandle( &windowClass );
      }
      
      if( !CloseHandle( mutexHandle ) )
      {
         Error( " CloseHandle(...) failure " );
      }
      else
      {
         RemoveHandle( mutexHandle );
      }
      
      if( file != ( (FILE*) 0xff ) )
      {
         if( fclose( file ) != 0 )
         {
            Error( " fclose(...) failure " );
         }
         else
         {
            RemoveHandle( file );
         }
      }
      else
      {
         RemoveHandle( file );
      }
      
      if( ListIsEmpty( listOfHeapAllocations, 0 ) != 1 )
      {
         Error( " listOfHeapAllocations is not empty " );
      }
      
      ListTerminate( listOfHeapAllocations );
      
      
      RemoveHandle( listOfHeapAllocations );
      
      ListIsEmpty( listOfHandles, &numberOfObjects );
      
      if( numberOfObjects != 1 )
      {
         Error( " listOfHandles is not empty " );
      }
      
      ListTerminate( listOfHandles );

      IsApplicationEntry = false;
      
      return 0;
   }

   WindowStyle::setMenuRect( -windowRect.left,
                             -windowRect.top,
                             windowRect.right - Graphics::graphicsClientWidth(),
                             windowRect.bottom - Graphics::graphicsClientHeight()
                           );
   
   // The left and top of WindowRect will be less than or equal to
   // zero.  Reposition the window so that WindowRect starts at 0, 0.
   
   if( windowRect.left   >  0 ||
       windowRect.top    >  0 ||
       windowRect.right  <= 0 ||
       windowRect.bottom <= 0
     )
   {
      int numberOfObjects = 0;
      
      Error( " bad windowRect values " );
      
      if( !UnregisterClass( appClassName, _hInstance ) )
      {
         Error( " UnregisterClass(...) failure " );
      }
      else
      {
         RemoveHandle( &windowClass );
      }
      
      if( !CloseHandle( mutexHandle ) )
      {
         Error( " CloseHandle(...) failure " );
      }
      else
      {
         RemoveHandle( mutexHandle );
      }
      
      if( file != ( (FILE*) 0xff ) )
      {
         if( fclose( file ) != 0 )
         {
            Error( " fclose(...) failure " );
         }
         else
         {
            RemoveHandle( file );
         }
      }
      else
      {
         RemoveHandle( file );
      }
      
      if( ListIsEmpty( listOfHeapAllocations, 0 ) != 1 )
      {
         Error( " listOfHeapAllocations is not empty " );
      }
      
      ListTerminate( listOfHeapAllocations );
      
      
      RemoveHandle( listOfHeapAllocations );
      
      ListIsEmpty( listOfHandles, &numberOfObjects );
      
      if( numberOfObjects != 1 )
      {
         Error( " listOfHandles is not empty " );
      }
      
      ListTerminate( listOfHandles );

      IsApplicationEntry = false;
      
      return 0;
   }
   
   if( windowRect.left < 0 )
   {
      windowRect.left = -windowRect.left;
   }
   
   if( windowRect.top < 0 )
   {
      windowRect.top = -windowRect.top;
   }
   
   windowRect.right  += windowRect.left;
   windowRect.bottom += windowRect.top;
   
   windowRect.left    = 0;
   windowRect.top     = 0;

   POINT origin = { ( Graphics::graphicsClientWidth() * 2 - windowRect.right ) / 2,
                    ( Graphics::graphicsClientHeight() * 2 - windowRect.bottom ) / 2
                  };
   
   WindowStyle::setOrigin( origin.x + WindowStyle::getMenuRect().left,
                           origin.y + WindowStyle::getMenuRect().top
                         );

   input = new queueI;

   hWindow = CreateWindow( appClassName,      // Window class name
                           appName,           // Window text (title)
                           windowType,        // Window style
                           origin.x,          // Window top left x pos
                           origin.y,          // Window top left y pos
                           windowRect.right,  // Window x width
                           windowRect.bottom, // Window y height
                           0,                 // No parent window
                           0,                 // No menu
                           hInstance,         // App's HINSTANCE
                           0                  // No data to WM_CREATE
                         );
   
   if( !hWindow || !input )
   {
      int numberOfObjects = 0;
      
      Error( " ( hWindow = CreateWindow(...) ) == NULL " );
      
      if( !UnregisterClass( appClassName, _hInstance ) )
      {
         Error( " UnregisterClass(...) failure " );
      }
      else
      {
         RemoveHandle( &windowClass );
      }
      
      if( !CloseHandle( mutexHandle ) )
      {
         Error( " CloseHandle(...) failure " );
      }
      else
      {
         RemoveHandle( mutexHandle );
      }
      
      if( file != ( (FILE*) 0xff ) )
      {
         if( fclose( file ) != 0 )
         {
            Error( " fclose(...) failure " );
         }
         else
         {
            RemoveHandle( file );
         }
      }
      else
      {
         RemoveHandle( file );
      }
      
      if( ListIsEmpty( listOfHeapAllocations, 0 ) != 1 )
      {
         Error( " listOfHeapAllocations is not empty " );
      }
      
      ListTerminate( listOfHeapAllocations );
      
      
      RemoveHandle( listOfHeapAllocations );
      
      ListIsEmpty( listOfHandles, &numberOfObjects );
      
      if( numberOfObjects != 1 )
      {
         Error( " listOfHandles is not empty " );
      }
      
      ListTerminate( listOfHandles );

      IsApplicationEntry = false;
      
      return 0;
   }
   
   // -6-
   InsertHandle( hWindow );
   
   initTime();
   
   updateTime();
   
   // MSDN:
   // The ShowWindow function sets the specified window's show state.
   //
   // ... the first time ShowWindow is called, the value ( 2nd parameter ) should be
   // the value obtained by the WinMain function in its nCmdShow parameter.
   if( ShowWindow( hWindow, nCmdShow ) != 0 )
   {
      Error( " ShowWindow(...) != 0 " );
      
      goto main_term;
   }
   
   if( Graphics::graphicsInitScreenAndBackBuffer( hWindow ) != Graphics::GRAPHICS_OK )
   {
      Error( " Graphics::graphicsInitScreenAndBackBuffer(...) != Graphics::GRAPHICS_OK " );
      
      goto main_term;
   }
   
   InsertHandle( TextOutInitSystem );
   
   Graphics::graphicsLockBackBuffer();

   WindowStyle::setSize( Graphics::graphicsClientWidth(),
                         Graphics::graphicsClientHeight()
                       );
   
   if( init( (double) Graphics::graphicsClientWidth() * 0.5,
             (double) Graphics::graphicsClientHeight() * 0.5,
             Graphics::RenderCircle32,
             Graphics::RenderLine32,
             Graphics::RenderPoint32
           ) != 0
     )
   {
      Warning( " Client init(...) function returns nonzero value, quitting abruptly. " );
      
      Graphics::graphicsUnlockBackBuffer();
      
      goto main_term;
   }
   
   Graphics::graphicsUnlockBackBuffer();
   
   PeekMessage( &Message, hWindow, 0, 0, PM_REMOVE );
   
   // MSDN:
   // The GetMessage function retrieves a message from the calling thread's
   // message queue and places it in the specified structure. This function
   // can retrieve both messages associated with a specified window and thread
   // messages posted via the PostThreadMessage function. The function retrieves
   // messages that lie within a specified range of message values.
   //
   // If the function retrieves a message other than WM_QUIT, the return value is nonzero.
   // If the function retrieves the WM_QUIT message, the return value is zero. 
   // If there is an error, the return value is -1.
   //
   // An application typically uses the return value to determine
   // whether to end the main message loop and exit the program.
   //
   // GetMessage does not remove WM_PAINT messages from the queue.
   // The messages remain in the queue until processed.
   //
   // Note that the function return value can be nonzero, zero, or -1.
   // Thus, you should avoid code like this:
   //     while (GetMessage( lpMsg, hWnd, 0, 0)) ...
   // The possibility of a -1 return value means that such code can lead to fatal application errors.
   while( Message.message != WM_QUIT )
   {
      PeekMessage( &Message, hWindow, 0, 0, PM_REMOVE );

      updateTime();
      
      // MSDN:
      // The TranslateMessage function translates virtual-key messages into character messages.
      // The character messages are posted to the calling thread's message queue,
      // to be read the next time the thread calls the GetMessage or PeekMessage function.
      //
      // The TranslateMessage function does not modify the message pointed to by the lpMsg parameter.
      //
      // WM_KEYDOWN and WM_KEYUP combinations produce a WM_CHAR or WM_DEADCHAR message.
      // WM_SYSKEYDOWN and WM_SYSKEYUP combinations produce a WM_SYSCHAR or WM_SYSDEADCHAR message.
      //
      // TranslateMessage can only be used to translate messages received from calls to GetMessage or PeekMessage.
      TranslateMessage( &Message );
      
      // MSDN:
      // The DispatchMessage function dispatches a message to a window procedure.
      // It is typically used to dispatch a message retrieved by the GetMessage function.
      //
      // The MSG structure must contain valid message values.
      // If the lpmsg parameter points to a WM_TIMER message and the lParam parameter of the WM_TIMER
      // message is not NULL, lParam points to a function that is called instead of the window procedure.
      DispatchMessage( &Message );
      
      if( IsApplicationMinimized == true )
      {
         Sleep( 2 );
         
         continue;
      }

      currentFrameNumber++;
      
      Graphics::graphicsLockBackBuffer();
      
      if( input->size() <= 0 )
      {
         POINT mousePt;
         
         GetCursorPos( &mousePt );
         ScreenToClient( hWindow, &mousePt );
         
         retVal = main( UPDATE_INPUT,
                        mousePt.x,
                        mousePt.y,
                        (double) Graphics::graphicsClientWidth() * 0.5,
                        (double) Graphics::graphicsClientHeight() * 0.5
                      );
         
         if( retVal == 1 )
         {
            Graphics::graphicsUnlockBackBuffer();
            
            Graphics::graphicsClearBackBuffer();
            
            Graphics::graphicsLockBackBuffer();
            
            TextOut( 10, 10, "Press F8 for help" );
            
            main( UPDATE_INPUT,
                  mousePt.x,
                  mousePt.y,
                  (double) Graphics::graphicsClientWidth() * 0.5,
                  (double) Graphics::graphicsClientHeight() * 0.5
                );
         }
         else if( retVal != 0 )
         {
            Warning( " Client main(...) function returns nonzero value, quitting abruptly. " );
            
            Graphics::graphicsUnlockBackBuffer();
            
            goto main_term;
         }
      }
      
      while( input->size() > 0 )
      {
         if( input->front().second == MENU_INPUT )
         {
            union
            {
               double *p;
               double f;
               POINT pt;
               
            }menu;
            
            memset( &menu, 0, sizeof( menu ) );
            
            menu.pt = input->front().first;
            
            retVal = main( MENU_INPUT,
                           0,
                           menu.f,
                           (double) Graphics::graphicsClientWidth() * 0.5,
                           (double) Graphics::graphicsClientHeight() * 0.5
                         );
         }
         else
         {
            retVal = main( input->front().second,
                           input->front().first.x,
                           input->front().first.y,
                           (double) Graphics::graphicsClientWidth() * 0.5,
                           (double) Graphics::graphicsClientHeight() * 0.5
                         );
         }
         
         if( retVal == 1 )
         {
            Graphics::graphicsUnlockBackBuffer();
            
            Graphics::graphicsClearBackBuffer();
            
            Graphics::graphicsLockBackBuffer();
            
            TextOut( 10, 10, "Press F8 for help" );
            
            main( UPDATE_INPUT,
                  input->front().first.x,
                  input->front().first.y,
                  (double) Graphics::graphicsClientWidth() * 0.5,
                  (double) Graphics::graphicsClientHeight() * 0.5
                );
         }
         else if( retVal != 0 )
         {
            Warning( " Client main(...) function returns nonzero value, quitting abruptly. " );
            
            Graphics::graphicsUnlockBackBuffer();
            
            goto main_term;
         }
         
         input->pop();
      }
      
      Graphics::graphicsUnlockBackBuffer();
      
      if( _timeInSeconds - _timeStart > 2 )
      {
         currentFrameNumber = 0;
         
         _timeStart = _timeInSeconds;
      }
      
      Graphics::graphicsDrawBackBufferToScreen( hWindow );
      
      Sleep( 1 );
   }
   
main_term:
   
   PostMessage( hWindow, WM_DESTROY, 0, 0 );

   IsApplicationEntry = false;
   
   return Message.wParam;
}

extern int GetFilesNamed( char *folderPath,
                          int *howManyOutput,
                          PLIST_HEAD fileList
                        )
{
   CLIENT_POTYPE object = { 0 };
   
   int result = 0, loop = 0, tempStore = 0;
   
   WIN32_FIND_DATAA data = { 0 };
   
   HANDLE Search = 0;
   
   if( ( !folderPath ) || ( !howManyOutput ) || ( !fileList ) )
   {
      Error( " The function GetFilesNamed(...) has received an invalid function parameter list. " );
      
      return -1;
   }
   
   *howManyOutput = 0;
   
   Search = FindFirstFile( folderPath, &data );
   
   if( Search == INVALID_HANDLE_VALUE )
   {
      Error( " The function FindFirstFile(...) has failed in the function GetFilesNamed(...). " );
      
      return -1;
   }
   
   tempStore++;
   
   SetLastError( ERROR_SUCCESS );
   
   result = FindNextFile( Search, &data );
   
   while( result && GetLastError() == ERROR_SUCCESS )
   {
      tempStore++;
      
      result = FindNextFile( Search, &data );
   }
   
   if( !( ( !result ) && GetLastError() == ERROR_NO_MORE_FILES ) )
   {
      Error( " The function FindNextFile(...) in the function GetFilesNamed(...) has indicated an error. " );
      
      return -1;
   }
   
   if( !FindClose( Search ) )
   {
      Error( " The function FindClose(..) has failed in the function GetFilesNamed(...). " );
      
      return -1;
   }
   
   Search = FindFirstFile( folderPath, &data );
   
   if( Search == INVALID_HANDLE_VALUE )
   {
      Error( " The function FindFirstFile(...) has failed in the function GetFilesNamed(...). " );
      
      return -1;
   }
   
   SetLastError( ERROR_SUCCESS );
   
   strcpy( object.name, data.cFileName );
   
   if( GetLastError() != ERROR_SUCCESS )
   {
      Error( " The function strcpy(...) has indicated an error through GetLastError(...) in GetFilesNamed(...). " );
      
      FindClose( Search );
      
      return -1;
   }
   
   ListInsert( fileList, object, 0 );
   
   for( loop = 1; loop < tempStore; loop++ )
   {
      if( !FindNextFile( Search, &data ) )
      {
         Error( " The function FindNextFile(...) has failed in the function GetFilesNamed(...). " );
         
         FindClose( Search );
         
         return -1;
      }
      
      SetLastError( ERROR_SUCCESS );
      
      strcpy( object.name, data.cFileName );
      
      if( GetLastError() != ERROR_SUCCESS )
      {
         Error( " The function strcpy(...) has indicated an error through GetLastError(...) in GetFilesNamed(...). " );
         
         FindClose( Search );
         
         return -1;
      }
      
      if( ListInsert( fileList, object, 0 ) != 0 )
      {
         Error( " The function ListInsert(...) has failed in the function GetFilesNamed(...). " );
         
         FindClose( Search );
         
         return -1;
      }
   }
   
   *howManyOutput = tempStore;
   
   if( !FindClose( Search ) )
   {
      Error( " The function FindClose(...) has failed at the end of the function GetFilesNamed(...). " );
      
      return -1;
   }
   
   return 0;
}