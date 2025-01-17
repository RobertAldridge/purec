
// fontUtil.cpp

#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstdint>
#include <cstring>

#include "font.h"
#include "fontUtil.h"

#include "BlahAlloc.h"
#include "BlahLog.h"

#if 0/*defined(_MSC_VER)*/

#include <windows.h>

#else

extern "C"
{

#define IMAGE_BITMAP 0

#define LR_LOADFROMFILE 0x00000010

#define LR_CREATEDIBSECTION 0x00002000

#define GDI_ERROR 0xFFFFFFFFL

#define SRCCOPY 0x00CC0020UL

#define BI_RGB 0L

#define DIB_RGB_COLORS 0

struct HDC__
{
  int unused;
};

typedef struct HDC__* HDC;

struct HBITMAP__
{
  int unused;
};

typedef struct HBITMAP__* HBITMAP;

typedef void* HGDIOBJ;

struct HINSTANCE__
{
  int unused;
};

typedef struct HINSTANCE__* HINSTANCE;

typedef void* HANDLE;

struct tagBITMAPINFOHEADER
{
  unsigned long biSize;
  long biWidth;
  long biHeight;
  unsigned short biPlanes;
  unsigned short biBitCount;
  unsigned long biCompression;
  unsigned long biSizeImage;
  long biXPelsPerMeter;
  long biYPelsPerMeter;
  unsigned long biClrUsed;
  unsigned long biClrImportant;
};

typedef struct tagBITMAPINFOHEADER BITMAPINFOHEADER;
typedef struct tagBITMAPINFOHEADER* LPBITMAPINFOHEADER;
typedef struct tagBITMAPINFOHEADER* PBITMAPINFOHEADER;

struct tagRGBQUAD
{
  unsigned char rgbBlue;
  unsigned char rgbGreen;
  unsigned char rgbRed;
  unsigned char rgbReserved;
};

typedef struct tagRGBQUAD RGBQUAD;

struct tagBITMAPINFO
{
  BITMAPINFOHEADER bmiHeader;
  RGBQUAD bmiColors[1];
};

typedef struct tagBITMAPINFO BITMAPINFO;
typedef struct tagBITMAPINFO* LPBITMAPINFO;
typedef struct tagBITMAPINFO* PBITMAPINFO;

__declspec(dllimport) HDC __stdcall CreateCompatibleDC(HDC hdc);

__declspec(dllimport) HANDLE __stdcall LoadImageA(HINSTANCE hInst, const char* name, unsigned int type, int cx, int cy, unsigned int fuLoad);

__declspec(dllimport) int __stdcall DeleteDC(HDC hdc);

__declspec(dllimport) HGDIOBJ __stdcall SelectObject(HDC hdc, HGDIOBJ h);

__declspec(dllimport) int __stdcall DeleteObject(HGDIOBJ ho);

__declspec(dllimport) int __stdcall BitBlt(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, unsigned long rop);

__declspec(dllimport) HBITMAP __stdcall CreateDIBSection(HDC hdc, const BITMAPINFO* pbmi, unsigned int usage, void** ppvBits, HANDLE hSection, unsigned long offset);

}

#endif

struct FontBlah
{
  // ascii contains source rect of characters on font image
  rect ascii[256];

  // width is screen_width - 1
  // height is screen_height - 1

  int32_t font_width;
  int32_t font_height;

  int32_t width;
  int32_t height;

  int32_t actualWidth;
  int32_t actualHeight;

  int32_t idealWidth;
  int32_t idealHeight;

  uint8_t** backbuffer_array_pointer;

  uint8_t** (*_backBufferFunction)();

  uint8_t** text_white_array_pointer;

  uint8_t* text_white;
};

// int* _StartX; input is old dest x, output is new dest x
// int* _StartY; input is old dest y, output is new dest y
// rect *_rect; input is old source rect, output is new source rect
bool FontUtilClipSpecial(int* _StartX, int* _StartY, int _width, int _height, rect* _rect)
{
  bool result = false;

  int StartX = 0;
  int StartY = 0;

  int SrcWidth = 0;
  int SrcHeight = 0;
  //
  int DestWidth = 0;
  int DestHeight = 0;
  int SourceWidth = 0;
  int Xstart = 0;
  int Ystart = 0;
  int BackBufferWidth = 0;
  int BackBufferHeight = 0;

  if( !_StartX || !_StartY || !_rect)
    goto label_return;

  StartX = *_StartX;
  StartY = *_StartY;

  SrcWidth = _rect->right - _rect->left + 1;
  SrcHeight = _rect->bottom - _rect->top + 1;
  //
  DestWidth = SrcWidth;
  DestHeight = SrcHeight;
  BackBufferWidth = _width + 1;
  BackBufferHeight = _height + 1;

  // trivial reject
  if(StartX <= -SrcWidth || StartX > BackBufferWidth - 1 || StartY <= -SrcHeight || StartY > BackBufferHeight - 1)
  {
    *_StartX = -1;
    *_StartY = -1;

    _rect->left = -1;
    _rect->top = -1;
    _rect->right  = -1;
    _rect->bottom = -1;

    goto label_return;
  }

  if(StartX < 0)
  {
    Xstart = -StartX;
    DestWidth -= Xstart;
  }

  if(StartY < 0)
  {
    Ystart = -StartY;
    DestHeight -= Ystart;
  }

  if( (SrcWidth + StartX) > BackBufferWidth)
  {
    DestWidth -= (SrcWidth + StartX) - BackBufferWidth;
    SourceWidth = (SrcWidth + StartX) - BackBufferWidth;
  }

  if( (SrcHeight + StartY) > BackBufferHeight)
    DestHeight -= (SrcHeight + StartY) - BackBufferHeight;

  if(StartX < 0)
    StartX = 0;

  if(StartY < 0)
    StartY = 0;

  _rect->left += Xstart;
  _rect->top += Ystart;

  _rect->right = _rect->left + DestWidth - 1;
  _rect->bottom = _rect->top + DestHeight - 1;

  *_StartX = StartX;
  *_StartY = StartY;

  result = true;

label_return:
  return result;
}

void FontUtilCopyBitmap(FontBlah* _this, void* _Source, int sourceWidth, int sourceHeight)
{
  HDC BltDC = {0};

  HBITMAP BltHB = {0};

  HGDIOBJ CleanUp = 0;

  HDC Source = (HDC)_Source;

  if( !_this)
    goto label_return;

  BltDC = CreateCompatibleDC(0);

  if( !BltDC)
  {
    BlahLog("Error ( BltDC = CreateCompatibleDC(...) ) == 0");
    goto label_return;
  }

  BltHB = (HBITMAP)LoadImageA(0, "asciiWhite.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

  if( !BltHB)
  {
    BlahLog("Error ( BltHB = LoadImage(...) ) == 0");

    if( !DeleteDC( BltDC) )
      BlahLog("Error DeleteDC(...) function failure");

    goto label_return;
  }

  CleanUp = SelectObject(BltDC, BltHB);

  if( !CleanUp || CleanUp == (void*)GDI_ERROR)
  {
    BlahLog("Error ( CleanUp = SelectObject(...) ) == 0");

    if( !DeleteObject(BltHB) )
      BlahLog("Error  DeleteObject(..) function failure");

    if( !DeleteDC(BltDC) )
      BlahLog("Error  DeleteDC(...) function failure");

    goto label_return;
  }

  if( !BitBlt(Source, 0, 0, sourceWidth, sourceHeight, BltDC, 0, 0, SRCCOPY) )
    BlahLog("Error BitBlt failure");

  if(BltDC)
  {
    HGDIOBJ deviceTemporaryCleanUp = 0;

    // free all gdi

    deviceTemporaryCleanUp = SelectObject(BltDC, CleanUp);

    if( !deviceTemporaryCleanUp || deviceTemporaryCleanUp == (void*)GDI_ERROR)
      BlahLog("Error ( deviceTemporaryCleanUp = SelectObject(...) ) == 0");

    if( !DeleteObject( BltHB ) )
      BlahLog("Error DeleteObject(..) function failure");

    if( !DeleteDC( BltDC ) )
      BlahLog("Error DeleteDC(...) function failure");
  }

label_return:
  return;
}

void FontUtilLoadBitmap(FontBlah* _this)
{
  int loop = 0;

  int* tempMem = 0;

  BITMAPINFO bInfo = { {0}, { {0} } };

  HDC deviceIndependentDC = {0};

  HBITMAP deviceIndependentBitmapHB = {0};

  HGDIOBJ deviceIndependentCleanUp = 0;

  if( !_this)
    goto label_return;

  bInfo.bmiHeader.biBitCount = 32;
  bInfo.bmiHeader.biWidth = 160;
  bInfo.bmiHeader.biHeight = 224;
  bInfo.bmiHeader.biPlanes = 1;
  bInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bInfo.bmiHeader.biCompression = BI_RGB;

  // create the permanent container

  deviceIndependentDC = CreateCompatibleDC(0);

  if( !deviceIndependentDC)
  {
    BlahLog("Error ( deviceIndependentDC = CreateCompatibleDC(...) ) == 0");
    goto label_return;
  }

  // create bitmap

  if( !_this->text_white)
    _this->text_white = (uint8_t*)BlahAlloc(sizeof(uint8_t) * 160 * 224 * 4, true);

  if( !_this->text_white_array_pointer)
    _this->text_white_array_pointer = (uint8_t**)BlahAlloc(sizeof(uint8_t*) * 224, true);

  if( !_this->text_white || !_this->text_white_array_pointer)
  {
    BlahLog("Error malloc(...) == 0");

    if( !DeleteDC(deviceIndependentDC) )
      BlahLog("Error DeleteDC(...) function failure");

    if(_this->text_white)
    {
      BlahFree(_this->text_white, sizeof(uint8_t) * 160 * 224 * 4, true);
      _this->text_white = 0;
    }

    if(_this->text_white_array_pointer)
    {
      BlahFree(_this->text_white_array_pointer, sizeof(uint8_t*) * 224, true);
      _this->text_white_array_pointer = 0;
    }

    deviceIndependentDC = 0;

    goto label_return;
  }

  deviceIndependentBitmapHB = CreateDIBSection(deviceIndependentDC, &bInfo, DIB_RGB_COLORS, (void**) &tempMem, 0, 0);

  if( !deviceIndependentBitmapHB || !tempMem)
  {
    BlahLog("Error ( deviceIndependentBitmapHB = CreateDIBSection(...) ) == 0");

    if( !DeleteDC(deviceIndependentDC) )
      BlahLog("Error DeleteDC(...) function failure");

    if(_this->text_white)
    {
      BlahFree(_this->text_white, sizeof(uint8_t) * 160 * 224 * 4, true);
      _this->text_white = 0;
    }

    if(_this->text_white_array_pointer)
    {
      BlahFree(_this->text_white_array_pointer, sizeof(uint8_t*) * 224, true);
      _this->text_white_array_pointer = 0;
    }

    deviceIndependentDC = 0;

    goto label_return;
  }

  // permanent container

  deviceIndependentCleanUp = SelectObject(deviceIndependentDC, deviceIndependentBitmapHB);

  if( !deviceIndependentCleanUp || deviceIndependentCleanUp == (void*)GDI_ERROR)
  {
    BlahLog("Error ( deviceIndependentCleanUp = SelectObject(...) ) == 0");

    if( !DeleteObject(deviceIndependentBitmapHB) )
      BlahLog("Error DeleteObject(..) function failure");

    if( !DeleteDC(deviceIndependentDC) )
      BlahLog("Error DeleteDC(...) function failure");

    if(_this->text_white)
    {
      BlahFree(_this->text_white, sizeof(uint8_t) * 160 * 224 * 4, true);
      _this->text_white = 0;
    }

    if(_this->text_white_array_pointer)
    {
      BlahFree(_this->text_white_array_pointer, sizeof(uint8_t*) * 224, true);
      _this->text_white_array_pointer = 0;
    }

    deviceIndependentDC = 0;
    deviceIndependentBitmapHB = 0;

    goto label_return;
  }

  FontUtilCopyBitmap(_this, deviceIndependentDC, 160, 224);

  memcpy(_this->text_white, tempMem, (size_t)160 * 224 * 4);

  _this->text_white_array_pointer[223] = _this->text_white;

  // Set up the text buffer pointer array.
  for(loop = 224 - 2; loop >= 0; loop--)
    _this->text_white_array_pointer[loop] = _this->text_white_array_pointer[loop + 1] + 160 * 4;

  if(deviceIndependentDC)
  {
    HGDIOBJ deviceTemporaryCleanUp = 0;

    // free all gdi

    deviceTemporaryCleanUp = SelectObject(deviceIndependentDC, deviceIndependentCleanUp);

    if( !deviceTemporaryCleanUp || deviceTemporaryCleanUp == (void*)GDI_ERROR)
      BlahLog("Error ( deviceTemporaryCleanUp = SelectObject(...) ) == 0");

    if( !DeleteObject(deviceIndependentBitmapHB) )
      BlahLog("Error DeleteObject(..) function failure");

    if( !DeleteDC(deviceIndependentDC) )
      BlahLog("Error DeleteDC(...) function failure");

    deviceIndependentDC = 0;
    deviceIndependentCleanUp = 0;
    deviceIndependentBitmapHB = 0;
  }

label_return:
  return;
}

void FontUtilCharAntiAliasColorBlit(uint8_t** backbuffer, uint8_t** textbuffer, int xDst, int yDst, rect* _RectSrc)
{
  uint8_t* Dst = 0;
  uint8_t* Src = 0;

  unsigned long SrcRed = 0;
  unsigned long SrcGreen = 0;
  unsigned long SrcBlue = 0;

  unsigned long ColorSrc = 0;
  unsigned long DstRatio = 0;
  unsigned long SrcRatio = 0;

  short HeightLoop = 0;
  short Width = 0;
  short WidthLoop = 0;

  rect RectDst = {0};
  rect RectSrc = {0};

  RectSrc = *_RectSrc;

  RectDst.left = xDst;
  RectDst.top = yDst;
  RectDst.right = xDst + (RectSrc.right - RectSrc.left);
  RectDst.bottom = yDst + (RectSrc.bottom - RectSrc.top);

  backbuffer = &backbuffer[RectDst.top];
  textbuffer = &textbuffer[RectSrc.top];

  HeightLoop = (short) (RectDst.bottom - RectDst.top);
  Width = (short) (RectDst.right - RectDst.left);

  do
  {
    WidthLoop = Width;

    int rectDstLeft = RectDst.left << 2;
    int rectSrcLeft = RectSrc.left << 2;

    Dst = (uint8_t*)backbuffer[0] + rectDstLeft;
    Src = (uint8_t*)textbuffer[0] + rectSrcLeft;

    do
    {
      SrcRatio = ( *(unsigned long*)Src) & 0xff;

      Src += 4;

      if( !SrcRatio)
      {
        Dst += 4;
      }
      else if(SrcRatio == 0xff)
      {
        *(unsigned long*)Dst = 0x00ffffff;

        Dst += 4;
      }
      else
      {
        ColorSrc = *(unsigned long*)Dst;

        SrcRed = (ColorSrc << 8) >> 24;
        SrcGreen = (ColorSrc << 16) >> 24;
        SrcBlue = (ColorSrc << 24) >> 24;

        DstRatio = 0xff - SrcRatio;

        SrcRatio *= 0xff;

        *(unsigned long*)Dst = ( (SrcRatio + (SrcRed * DstRatio) ) / 0xff) << 16 | ( (SrcRatio + (SrcGreen * DstRatio) ) / 0xff) << 8 | (SrcRatio + (SrcBlue * DstRatio) ) / 0xff;

        Dst += 4;
      }

    }while( --WidthLoop > 0);

    ++backbuffer;
    ++textbuffer;

  }while( --HeightLoop > 0);
}
