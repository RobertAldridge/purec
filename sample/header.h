
// header.h

#define countof(x) (sizeof(x) / sizeof(x[0] ) )

#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <cwctype>

//#include <stdnoreturn.h>
//#include <threads.h>

struct pointInteger
{
  int x;
  int y;
};

struct rectInteger
{
  int left;
  int top;
  int right;
  int bottom;
};

struct FontClient
{
  FontClient* ( *TextOutInitSystem)(FontClient* _this, uint8_t** ( *backBufferFunction)(), uint32_t width, uint32_t height, uint32_t idealWidth, uint32_t idealHeight);

  void ( *T1xtOut)(FontClient* _this, int32_t x, int32_t y, const char* format, ...);

  rectInteger ( *TextOutRect)(FontClient* _this, int32_t x, int32_t y, const char* format, ...);

  void ( *TextOutTermSystem)(FontClient** _this);
};

struct LIST_HEAD;

union CLIENT_POTYPE;

struct PARTICLE;

struct EMITTER;

struct PARTICLE_SYSTEMS_HEAD;

struct COLOR;

struct VECTOR;

#pragma warning(disable: 4191)
#pragma warning(disable: 4365)
#pragma warning(disable: 4514)

typedef void* HANDLE;
typedef void* HGDIOBJ;

typedef struct HBITMAP__* HBITMAP;
typedef struct HBRUSH__* HBRUSH;
typedef struct HDC__* HDC;
typedef struct HICON__* HICON;
typedef struct HINSTANCE__* HINSTANCE;
typedef struct HMENU__* HMENU;
typedef struct HWND__* HWND;

typedef HICON HCURSOR;

namespace
{

enum class GRAPHICS_IMPLEMENTATION
{
  GDI = 0,
  DIRECTDRAW

}GRAPHICS_IMPLEMENTATION;

}

struct GraphicsClient
{

GraphicsClient* ( *GraphicsClientConstruct)(GraphicsClient* _this);

int64_t ( *GraphicsClientDestruct)(GraphicsClient** _this);

long long ( *GraphicsAboutDlgProcWrapper)(GraphicsClient* _this, HWND hDlg, unsigned int msg, unsigned long long wParam, long long lParam);
long long ( *GraphicsInputDlgProcWrapper)(GraphicsClient* _this, HWND hDlg, unsigned int msg, unsigned long long wParam, long long lParam);
long long ( *GraphicsWindowProcWrapper)(GraphicsClient* _this, HWND hwnd, unsigned int msg, unsigned long long wParam, long long lParam);

void ( *_GraphicsRenderPoint32)(GraphicsClient* _this, int x0, int y0, int c0);
void ( *GraphicsRenderPoint32)(GraphicsClient* _this, int x0, int y0, int c0);

void ( *_GraphicsRenderLine32)(GraphicsClient* _this, int x0, int y0, int x1, int y1, int c0, int c1);
void ( *GraphicsRenderLine32)(GraphicsClient* _this, int x0, int y0, int x1, int y1, int c0, int c1);

void ( *_GraphicsRenderCircle32)(GraphicsClient* _this, int x0, int y0, int r0, int c0, int c1);
void ( *GraphicsRenderCircle32)(GraphicsClient* _this, int x0, int y0, int r0, int c0, int c1);

enum GRAPHICS_IMPLEMENTATION ( *GraphicsImplementation)(GraphicsClient* _this);

void ( *GraphicsSafeMode)(GraphicsClient* _this);

bool ( *GraphicsIsModeChangeActive)(GraphicsClient* _this);

int ( *GraphicsWidth)(GraphicsClient* _this);
int ( *GraphicsHeight)(GraphicsClient* _this);
int ( *GraphicsBitDepth)(GraphicsClient* _this);

int ( *GraphicsClientWidth)(GraphicsClient* _this);
int ( *GraphicsClientHeight)(GraphicsClient* _this);
int ( *GraphicsClientBitDepth)(GraphicsClient* _this);

int ( *GraphicsOldWidth)(GraphicsClient* _this);
int ( *GraphicsOldHeight)(GraphicsClient* _this);
int ( *GraphicsOldBitDepth)(GraphicsClient* _this);

uint8_t** ( *GraphicsBackBufferFunction)(GraphicsClient* _this);

int ( *GraphicsUnlockBackBuffer)(GraphicsClient* _this);

int ( *GraphicsLockBackBuffer)(GraphicsClient* _this);

int ( *GraphicsClearBackBuffer)(GraphicsClient* _this);

int ( *GraphicsDrawBackBufferToScreen)(GraphicsClient* _this, HWND hWindow);

int ( *GraphicsSaveOldMode)(GraphicsClient* _this);

int ( *GraphicsRestoreOldMode)(GraphicsClient* _this);

int ( *GraphicsSetBitDepthTo32)(GraphicsClient* _this);

int ( *GraphicsLoadBitmap)(GraphicsClient* _this, HDC destination, int destinationWidth, int destinationHeight, char* sourceFileName);

int ( *GraphicsTermScreenAndBackBufferGDI)(GraphicsClient* _this);

int ( *GraphicsTermScreenAndBackBufferDIRECTDRAW)(GraphicsClient* _this);

int ( *GraphicsTermScreenAndBackBuffer)(GraphicsClient* _this);

int ( *GraphicsInitScreenAndBackBufferGDI)(GraphicsClient* _this, HWND hWindow);

int ( *GraphicsInitScreenAndBackBufferDIRECTDRAW)(GraphicsClient* _this, HWND hWindow);

int ( *GraphicsInitScreenAndBackBuffer)(GraphicsClient* _this, HWND hWindow);

int ( *GraphicsCheckIsFullScreen)(GraphicsClient* _this);

};
