
// font_util.cpp

#include <windowsx.h>

#pragma warning (disable : 4820)
#include <ddraw.h>
#pragma warning (default : 4820)

#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstdint>

#include "font.h"

#include "font_util.h"

#include "BlahAlloc.h"

struct FontBlah
{

//ascii contains source rect of characters on font image
rect ascii[ 256 ];
//width is screen_width-1, height is screen_height-1
int32_t font_width, font_height, width, height;

int32_t actualWidth, actualHeight, idealWidth, idealHeight;

uint8_t** backbuffer_array_pointer;

uint8_t** ( *_backBufferFunction ) ( );

uint8_t** text_white_array_pointer;

uint8_t*  text_white;

// FOR DEBUGGING
#ifndef NDEBUG
  FILE* file;

  uint32_t  numErrors;

  uint32_t  numWarnings;
#endif
//

};

#ifndef NDEBUG
int FontUtilError(FontBlah* _this, const char* const errorString)
{
  if( _this && _this->file )
  {
    ++_this->numErrors;

    fprintf( _this->file, " FontUtilError#  : %i\n",   _this->numErrors );

    fprintf( _this->file, " FontUtilError   : %s\n\n", errorString );
  }

  return 0;
}

int FontUtilWarning(FontBlah* _this, const char* const warningString)
{
  if( _this && _this->file )
  {
    ++_this->numWarnings;

    fprintf( _this->file, " FontUtilWarning#: %i\n",   _this->numWarnings   );

    fprintf( _this->file, " FontUtilWarning : %s\n\n", warningString );
  }

  return 0;
}
#endif

unsigned char
FontUtilClipSpecial( int  *StartX, // input is old dest x, output is new dest x
       int  *StartY, // input is old dest y, output is new dest y
       int  _width,
       int  _height,
       rect *_rect    // input is old source rect, output is new source rect
       )
{
  #define StartX (*StartX)
  #define StartY (*StartY)

  int SrcWidth         = _rect->right  - _rect->left + 1;
  int SrcHeight        = _rect->bottom - _rect->top  + 1;
  //
  int DestWidth        = SrcWidth;
  int DestHeight       = SrcHeight;
  int SourceWidth      = 0;
  int Xstart           = 0;
  int Ystart           = 0;
  int BackBufferWidth  = _width  + 1;
  int BackBufferHeight = _height + 1;

  // trivial reject
  if( StartX <= -SrcWidth  || StartX > BackBufferWidth  - 1 ||
        StartY <= -SrcHeight || StartY > BackBufferHeight - 1
      )
  {
    StartX       = -1;
    StartY       = -1;
    _rect->left   = -1;
    _rect->top    = -1;
    _rect->right  = -1;
    _rect->bottom = -1;

    return FALSE;
  }

  if (StartX < 0)
  {
    Xstart     = -StartX;
    DestWidth -=  Xstart;
  }

  if( StartY < 0 )
  {
    Ystart      = -StartY;
    DestHeight -=  Ystart;
  }

  if( SrcWidth + StartX > BackBufferWidth )
  {
    DestWidth   -= ( SrcWidth + StartX ) - BackBufferWidth;
    SourceWidth  = ( SrcWidth + StartX ) - BackBufferWidth;
  }

  if( SrcHeight + StartY > BackBufferHeight )
  {
    DestHeight -= ( SrcHeight + StartY ) - BackBufferHeight;
  }

  if( StartX < 0 )
  {
        StartX = 0;
  }

  if( StartY < 0 )
  {
    StartY = 0;
  }

  #undef StartY
  #undef StartX

  _rect->left += Xstart;
  _rect->top  += Ystart;

  _rect->right  = _rect->left + DestWidth  - 1;
  _rect->bottom = _rect->top  + DestHeight - 1;

  return TRUE;
}

void FontUtilCopyBitmap(FontBlah* _this, HDC Source,
                      int sourceWidth,
                      int sourceHeight
                      )
{
  HDC   BltDC;

  HBITMAP BltHB;

  HGDIOBJ CleanUp;

  if( !_this)
    return;

  BltDC = CreateCompatibleDC( 0 );

  if( BltDC == NULL )
  {
    #ifndef NDEBUG
      FontUtilError(_this, " ( BltDC = CreateCompatibleDC(...) ) == NULL " );
    #endif

    return;
  }

  BltHB = (HBITMAP) LoadImageA( NULL,
                 "ascii_white.bmp",
                 IMAGE_BITMAP,
                 0,
                 0,
                 LR_LOADFROMFILE | LR_CREATEDIBSECTION
                 );

  if( BltHB == NULL )
  {
    #ifndef NDEBUG
      FontUtilError(_this, " ( BltHB = LoadImage(...) ) == NULL " );
    #endif

    if( !DeleteDC( BltDC ) )
    {
      #ifndef NDEBUG
        FontUtilError(_this, " DeleteDC(...) function failure " );
      #endif
    }

    return;
  }

  CleanUp = SelectObject( BltDC, BltHB );

  if( CleanUp == NULL || CleanUp == (void*)GDI_ERROR )
  {
    #ifndef NDEBUG
      FontUtilError(_this, " ( CleanUp = SelectObject(...) ) == NULL " );
    #endif

    if( !DeleteObject( BltHB ) )
    {
      #ifndef NDEBUG
        FontUtilError(_this, " DeleteObject(..) function failure " );
      #endif
    }

    if( !DeleteDC( BltDC ) )
    {
      #ifndef NDEBUG
        FontUtilError(_this, " DeleteDC(...) function failure " );
      #endif
    }

    return;
  }

  if(     !BitBlt
        (
        Source,
        0,
        0,
        sourceWidth,
        sourceHeight,
        BltDC,
        0,
        0,
        SRCCOPY
      )
    )
  {
    #ifndef NDEBUG
      FontUtilError(_this, " BitBlt failure " );
    #endif
  }

  HGDIOBJ deviceTempCleanUp = 0;

  if( BltDC != 0 )
  {
    /* free all gdi */

    deviceTempCleanUp = SelectObject( BltDC, CleanUp );

    if( deviceTempCleanUp == NULL || deviceTempCleanUp == (void*)GDI_ERROR )
    {
      #ifndef NDEBUG
        FontUtilError(_this, " ( deviceTempCleanUp = SelectObject(...) ) == NULL " );
      #endif
    }

    if( !DeleteObject( BltHB ) )
    {
      #ifndef NDEBUG
        FontUtilError(_this, " DeleteObject(..) function failure " );
      #endif
    }

    if( !DeleteDC( BltDC ) )
    {
      #ifndef NDEBUG
        FontUtilError(_this, " DeleteDC(...) function failure " );
      #endif
    }
  }
}

void
FontUtilLoadBitmap(FontBlah* _this
      )
{
  int        loop     =   0;

  int        *tempMem =   0;

  BITMAPINFO bInfo    = { {0}, { {0} } };

  HDC     deviceIndependentDC       = 0;

  HBITMAP deviceIndependentBitmapHB = 0;

  HGDIOBJ deviceIndependentCleanUp  = 0;

  if( !_this)
    return;

  bInfo.bmiHeader.biBitCount    = 32;
  bInfo.bmiHeader.biWidth     = 160;
  bInfo.bmiHeader.biHeight    = 224;
  bInfo.bmiHeader.biPlanes    = 1;
  bInfo.bmiHeader.biSize      = sizeof( BITMAPINFOHEADER );
  bInfo.bmiHeader.biCompression = BI_RGB;

  /* create the permanent container */

  deviceIndependentDC = CreateCompatibleDC( 0 );

  if( deviceIndependentDC == NULL )
  {
    #ifndef NDEBUG
      FontUtilError(_this, " ( deviceIndependentDC = CreateCompatibleDC(...) ) == NULL " );
    #endif

    return;
  }

  /* create bitmap */

  if( !_this->text_white)
    _this->text_white = (uint8_t*)BlahAlloc(sizeof(uint8_t) * 160 * 224 * 4, true);

  if( !_this->text_white_array_pointer)
    _this->text_white_array_pointer = (uint8_t**)BlahAlloc(sizeof(uint8_t*) * 224, true);

  if( (!_this->text_white) || (!_this->text_white_array_pointer) )
  {
    #ifndef NDEBUG
      FontUtilError(_this, " malloc(...) == NULL " );
    #endif

    if( !DeleteDC( deviceIndependentDC ) )
    {
      #ifndef NDEBUG
        FontUtilError(_this, " DeleteDC(...) function failure " );
      #endif
    }

    if( _this->text_white )
    {
      BlahFree(_this->text_white, sizeof(uint8_t) * 160 * 224 * 4, true);
      _this->text_white = 0;
    }

    if( _this->text_white_array_pointer )
    {
      BlahFree(_this->text_white_array_pointer, sizeof(uint8_t*) * 224, true);
      _this->text_white_array_pointer = 0;
    }

    deviceIndependentDC = 0;

    return;
  }

  deviceIndependentBitmapHB = CreateDIBSection( deviceIndependentDC,
                          &bInfo,
                          DIB_RGB_COLORS,
                          (void**) &tempMem,
                          0,
                          0
                        );

  if( deviceIndependentBitmapHB == NULL || tempMem == NULL )
  {
    #ifndef NDEBUG
      FontUtilError(_this, " ( deviceIndependentBitmapHB = CreateDIBSection(...) ) == NULL " );
    #endif

    if( !DeleteDC( deviceIndependentDC ) )
    {
      #ifndef NDEBUG
        FontUtilError(_this, " DeleteDC(...) function failure " );
      #endif
    }

    if( _this->text_white )
    {
      BlahFree(_this->text_white, sizeof(uint8_t) * 160 * 224 * 4, true);
      _this->text_white = 0;
    }

    if( _this->text_white_array_pointer )
    {
      BlahFree(_this->text_white_array_pointer, sizeof(uint8_t*) * 224, true);
      _this->text_white_array_pointer = 0;
    }

    deviceIndependentDC = 0;

    return;
  }

  /* permanent container */

  deviceIndependentCleanUp = SelectObject( deviceIndependentDC,
                                         deviceIndependentBitmapHB
                       );

  if( deviceIndependentCleanUp == NULL || deviceIndependentCleanUp == (void*)GDI_ERROR )
  {
    #ifndef NDEBUG
      FontUtilError(_this, " ( deviceIndependentCleanUp = SelectObject(...) ) == NULL " );
    #endif

    if( !DeleteObject( deviceIndependentBitmapHB ) )
    {
      #ifndef NDEBUG
        FontUtilError(_this, " DeleteObject(..) function failure " );
      #endif
    }

    if( !DeleteDC( deviceIndependentDC ) )
    {
      #ifndef NDEBUG
        FontUtilError(_this, " DeleteDC(...) function failure " );
      #endif
    }

    if( _this->text_white )
    {
      BlahFree(_this->text_white, sizeof(uint8_t) * 160 * 224 * 4, true);
      _this->text_white = 0;
    }

    if( _this->text_white_array_pointer )
    {
      BlahFree(_this->text_white_array_pointer, sizeof(uint8_t*) * 224, true);
      _this->text_white_array_pointer = 0;
    }

    deviceIndependentDC       = 0;
    deviceIndependentBitmapHB = 0;

    return;
  }

  FontUtilCopyBitmap( _this, deviceIndependentDC, 160, 224 );

  memcpy( _this->text_white, tempMem, 160 * 224 * 4 );

  _this->text_white_array_pointer[ 223 ] = _this->text_white;

  // Set up the text buffer pointer array.
  for( loop = 224 - 2; loop >= 0; loop-- )
  {
    _this->text_white_array_pointer[ loop ] =
      _this->text_white_array_pointer[ loop + 1 ] + 160 * 4;
  }

  HGDIOBJ deviceTempCleanUp = 0;

  if( deviceIndependentDC != 0 )
  {
    /* free all gdi */

    deviceTempCleanUp = SelectObject( deviceIndependentDC, deviceIndependentCleanUp );

    if( deviceTempCleanUp == NULL || deviceTempCleanUp == (void*)GDI_ERROR )
    {
      #ifndef NDEBUG
        FontUtilError(_this, " ( deviceTempCleanUp = SelectObject(...) ) == NULL " );
      #endif
    }

    if( !DeleteObject( deviceIndependentBitmapHB ) )
    {
      #ifndef NDEBUG
        FontUtilError(_this, " DeleteObject(..) function failure " );
      #endif
    }

    if( !DeleteDC( deviceIndependentDC ) )
    {
      #ifndef NDEBUG
        FontUtilError(_this, " DeleteDC(...) function failure " );
      #endif
    }

    deviceIndependentDC       = 0;
    deviceIndependentCleanUp  = 0;
    deviceIndependentBitmapHB = 0;
  }
}

void FontUtilCharAntiAliasColorBlit( uint8_t **backbuffer,
                        uint8_t **textbuffer,
                        int  xDst,
                        int  yDst,
                        rect *_RectSrc
                      )
{
  uint8_t  *Dst = 0,
           *Src = 0;

  unsigned long SrcRed, SrcGreen, SrcBlue;
  unsigned long ColorSrc;
  unsigned long DstRatio;
  unsigned long SrcRatio;

  short          HeightLoop,
               Width,
               WidthLoop;

  rect           RectDst,
           RectSrc;

  RectSrc = *_RectSrc;

  RectDst.left   = xDst;
  RectDst.top    = yDst;
  RectDst.right  = xDst + ( RectSrc.right  - RectSrc.left );
  RectDst.bottom = yDst + ( RectSrc.bottom - RectSrc.top  );

  backbuffer = &backbuffer[ RectDst.top ];
  textbuffer = &textbuffer[ RectSrc.top ];

  HeightLoop = (short) ( RectDst.bottom - RectDst.top  );
  Width      = (short) ( RectDst.right  - RectDst.left );

  do
  {
    WidthLoop = Width;

    int rectDstLeft = RectDst.left << 2;
    int rectSrcLeft = RectSrc.left << 2;

    Dst       = ( (uint8_t*) (*backbuffer) ) + rectDstLeft;
    Src       = ( (uint8_t*) (*textbuffer) ) + rectSrcLeft;

    do
    {
      SrcRatio = ( *( (unsigned long*) Src ) ) & 0xff;

      Src += 4;

      if( SrcRatio == 0 )
        Dst += 4;

      else if( SrcRatio == 0xff )
      {
        *( (unsigned long*) Dst ) =  0x00ffffff;

        Dst += 4;
      }

      else
      {
        ColorSrc = *( (unsigned long*) Dst );

        SrcRed   = ( ( ColorSrc << 8  ) >> 24 );
        SrcGreen = ( ( ColorSrc << 16 ) >> 24 );
        SrcBlue  = ( ( ColorSrc << 24 ) >> 24 );

        DstRatio = 0xff - SrcRatio;

        SrcRatio *= 0xff;

        *( (unsigned long*) Dst ) =
          ( ( ( SrcRatio + ( SrcRed   * DstRatio ) ) / 0xff ) << 16 ) |
          ( ( ( SrcRatio + ( SrcGreen * DstRatio ) ) / 0xff ) << 8  ) |
            ( ( SrcRatio + ( SrcBlue  * DstRatio ) ) / 0xff );

        Dst += 4;
      }

    }while( --WidthLoop > 0 );

    ++backbuffer;
    ++textbuffer;

  }while( --HeightLoop > 0 );
}
