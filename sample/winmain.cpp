
// winmain.cpp

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
// 9) Call a client defined init function, passing it some parameters
//
// 10) Handle input every program loop, supplying it to a client
//
// 11) Start initial termination on:
//
// hitting ESC key
// on clicking the window close x button
// when any client function returns anything besides 0
//
// ...these next items will be called after initial termination
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
extern int init(double halfWidth, double halfHeight, GraphicsClient* _graphics, FontClient* _font);

// We want to stick with basic types here,
// so pass 3 floating points.
extern int main(int inputEvent, double x, double y, double B, double halfWidth, double halfHeight, GraphicsClient* _graphics, FontClient* _font);

// The return value of term isn't used for much
// since initial termination must have already taken
// place for the function to be called. It will
// still be logged as a warning if the return value
// of the function is not 0.
extern int term();

#define ENABLE_DIRECTDRAW 1

//#include <d3d12.h>
//#include <d2d1.h>
//#include <d2d1_1.h>

//#include <crtdbg.h>

//#include <cassert> // assert
//#include <cstdint> // int64_t, uint32_t
//#include <cstdio> // FILE
//#include <cstdlib> // free, malloc
//#include <cstring> // memcpy, memset
//#include <cfloat>
//#include <cmath>
//#include <ctime>

//#include <iostream>
//#include <string>
//#include <queue>

//using namespace std;

//using std::bad_alloc;
//using std::pair;
//using std::queue;

//using std::calloc;
//using std::FILE;
//using std::fopen;
//using std::int64_t;
//using std::memcpy;
//using std::memset;
//using std::uint32_t;

#include "listObject.h"
#include "list.h"

//#include "ssSet.h"
//#include "ssStack.h"
#include "ssQueue.h"

#include "font.h"

#include "particle.h"

#include "memory.h"

#include "resourceHeaders.h"

#include "BlahLog.h"

#include "BlahAlloc.h"

#if 0//defined(_MSC_VER)

#pragma warning (disable : 4820)
#define INITGUID
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <windows.h>

#if ENABLE_DIRECTDRAW
#include <ddraw.h>
#include <dxgi.h>
#include <d3d9.h>
#endif
#pragma warning (default : 4820)

#else

extern "C"
{

#define _CRTDBG_LEAK_CHECK_DF 0x20
#define _CRTDBG_REPORT_FLAG -1

#define BI_RGB 0L

#define DIB_RGB_COLORS 0

#define BLACKNESS 0x00000042UL
#define SRCCOPY 0x00CC0020UL

#define COLOR_WINDOW 5

#define CS_DBLCLKS 0x0008
#define CS_HREDRAW 0x0002
#define CS_VREDRAW 0x0001

#define DISP_CHANGE_BADDUALVIEW -6
#define DISP_CHANGE_BADFLAGS -4
#define DISP_CHANGE_BADMODE -2
#define DISP_CHANGE_BADPARAM -5
#define DISP_CHANGE_FAILED -1
#define DISP_CHANGE_NOTUPDATED -3
#define DISP_CHANGE_RESTART 1
#define DISP_CHANGE_SUCCESSFUL 0

#define DM_BITSPERPEL 0x00040000L
#define DM_DISPLAYFREQUENCY 0x00400000L
#define DM_PELSHEIGHT 0x00100000L
#define DM_PELSWIDTH 0x00080000L

#define ERROR_ALREADY_EXISTS 183L
#define ERROR_NO_MORE_FILES 18L

#define ERROR_SUCCESS 0L

#define GDI_ERROR 0xFFFFFFFFL

#define HTCAPTION 2

#define IDCANCEL 2
#define IDOK 1

#define IMAGE_BITMAP 0
#define IMAGE_ICON 1
#define IMAGE_CURSOR 2

#define LR_CREATEDIBSECTION 0x00002000
#define LR_DEFAULTSIZE 0x00000040
#define LR_LOADFROMFILE 0x00000010
#define LR_LOADTRANSPARENT 0x00000020
#define LR_SHARED 0x00008000

#define MB_ICONERROR MB_ICONHAND
#define MB_ICONHAND 0x00000010L
#define MB_OK 0x00000000L

#define PM_REMOVE 0x0001

#define SC_MAXIMIZE 0xF030
#define SC_MINIMIZE 0xF020

#define SIZE_MAXHIDE 4
#define SIZE_MAXIMIZED 2
#define SIZE_MAXSHOW 3
#define SIZE_MINIMIZED 1
#define SIZE_RESTORED 0

#define SW_SHOW 5

#define HORZRES 8
#define VERTRES 10
#define BITSPIXEL 12

#define VK_ADD 0x6B
#define VK_ESCAPE 0x1B
#define VK_F1 0x70
#define VK_F10 0x79
#define VK_F2 0x71
#define VK_F3 0x72
#define VK_F4 0x73
#define VK_F5 0x74
#define VK_F6 0x75
#define VK_F7 0x76
#define VK_F8 0x77
#define VK_F9 0x78
#define VK_NUMPAD1 0x61
#define VK_NUMPAD2 0x62
#define VK_NUMPAD3 0x63
#define VK_NUMPAD4 0x64
#define VK_NUMPAD5 0x65
#define VK_NUMPAD6 0x66
#define VK_NUMPAD7 0x67
#define VK_NUMPAD8 0x68
#define VK_NUMPAD9 0x69
#define VK_RETURN 0x0D
#define VK_SUBTRACT 0x6D

#define WM_CAPTURECHANGED 0x0215
#define WM_CLOSE 0x0010
#define WM_COMMAND 0x0111
#define WM_CREATE 0x0001
#define WM_DESTROY 0x0002
#define WM_DISPLAYCHANGE 0x007E
#define WM_ERASEBKGND 0x0014
#define WM_INITDIALOG 0x0110
#define WM_KEYDOWN 0x0100
#define WM_KILLFOCUS 0x0008
#define WM_LBUTTONDOWN 0x0201
#define WM_LBUTTONUP 0x0202
#define WM_MOUSEMOVE 0x0200
#define WM_MOVE 0x0003
#define WM_MOVING 0x0216
#define WM_NCLBUTTONDBLCLK 0x00A3
#define WM_PAINT 0x000F
#define WM_QUIT 0x0012
#define WM_RBUTTONDOWN 0x0204
#define WM_RBUTTONUP 0x0205
#define WM_SETFOCUS 0x0007
#define WM_SIZE 0x0005
#define WM_SIZING 0x0214
#define WM_SYSCOMMAND 0x0112
#define WM_SYSKEYDOWN 0x0104

#define WS_CAPTION 0x00C00000L
#define WS_MAXIMIZEBOX 0x00010000L
#define WS_MINIMIZEBOX 0x00020000L
#define WS_OVERLAPPED 0x00000000L
#define WS_POPUP 0x80000000L
#define WS_SYSMENU 0x00080000L
#define WS_THICKFRAME 0x00040000L

#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)
//#define WS_POPUPWINDOW (WS_POPUP | WS_BORDER | WS_SYSMENU)

//WINDOWSTYLE_FULLSCREEN
//WINDOWSTYLE_WINDOW

//WM_SETWIDTHHEIGHT
//WM_CHANGEWINDOWSTYLE

#define INVALID_HANDLE_VALUE (void*)0xFFFFFFFFFFFFFFFFLL

#define MAKEINTRESOURCEA(idc) ( (char*) ( (unsigned long long) ( (unsigned short)idc) ) )

#define LOWORD(l) ( (unsigned short) ( ( (unsigned long long)l) & 0xffff) )
#define HIWORD(l) ( (unsigned short) ( ( ( (unsigned long long)l) >> 16) & 0xffff) )

typedef void* HANDLE;

typedef void* HGDIOBJ;

struct HBITMAP__
{
 int unused;
};

typedef struct HBITMAP__* HBITMAP;

struct HBRUSH__
{
 int unused;
};

typedef struct HBRUSH__* HBRUSH;

struct HDC__
{
 int unused;
};

typedef struct HDC__* HDC;

struct HICON__
{
 int unused;
};

typedef struct HICON__* HICON;

struct HINSTANCE__
{
 int unused;
};

typedef struct HINSTANCE__* HINSTANCE;

struct HMENU__
{
 int unused;
};

typedef struct HMENU__* HMENU;

struct HWND__
{
 int unused;
};

typedef struct HWND__* HWND;

struct tagPOINT
{
 long x;
 long y;
};

typedef struct tagPOINT POINT;

struct _POINTL
{
 long x;
 long y;
};

typedef struct _POINTL POINTL;

struct tagRECT
{
 long left;
 long top;
 long right;
 long bottom;
};

typedef struct tagRECT RECT;

struct tagRGBQUAD
{
 unsigned char rgbBlue;
 unsigned char rgbGreen;
 unsigned char rgbRed;
 unsigned char rgbReserved;
};

typedef struct tagRGBQUAD RGBQUAD;

typedef HICON HCURSOR;

struct _FILETIME
{
 unsigned long dwLowDateTime;
 unsigned long dwHighDateTime;
};

typedef struct _FILETIME FILETIME;

union _LARGE_INTEGER
{
 struct
 {
 unsigned long LowPart;
 long HighPart;

 }DUMMYSTRUCTNAME;

 struct
 {
 unsigned long LowPart;
 long HighPart;

 }u;

 long long QuadPart;
};

typedef union _LARGE_INTEGER LARGE_INTEGER;

struct _SECURITY_ATTRIBUTES
{
 unsigned long nLength;
 unsigned char padding1[4];
 void* lpSecurityDescriptor;
 int bInheritHandle;
 unsigned char padding2[4];
};

typedef struct _SECURITY_ATTRIBUTES SECURITY_ATTRIBUTES;

#pragma pack(push, 1)
struct tagBITMAPFILEHEADER
{
 unsigned short bfType;
 unsigned long bfSize;
 unsigned short bfReserved1;
 unsigned short bfReserved2;
 unsigned long bfOffBits;
};
#pragma pack(pop)

typedef struct tagBITMAPFILEHEADER BITMAPFILEHEADER;

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

struct tagBITMAPINFO
{
 BITMAPINFOHEADER bmiHeader;
 RGBQUAD bmiColors[1];
};

typedef struct tagBITMAPINFO BITMAPINFO;
typedef struct tagBITMAPINFO* LPBITMAPINFO;
typedef struct tagBITMAPINFO* PBITMAPINFO;

struct tagCREATESTRUCTA
{
 void* lpCreateParams;
 HINSTANCE hInstance;
 HMENU hMenu;
 HWND hwndParent;
 int cy;
 int cx;
 int y;
 int x;
 long style;
 unsigned char padding1[4];
 const char* lpszName;
 const char* lpszClass;
 unsigned long dwExStyle;
 unsigned char padding2[4];
};

typedef struct tagCREATESTRUCTA CREATESTRUCTA;

struct _devicemodeA
{
 unsigned char dmDeviceName[32];
 unsigned short dmSpecVersion;
 unsigned short dmDriverVersion;
 unsigned short dmSize;
 unsigned short dmDriverExtra;
 unsigned long dmFields;

 union
 {
 struct
 {
 short dmOrientation;
 short dmPaperSize;
 short dmPaperLength;
 short dmPaperWidth;
 short dmScale;
 short dmCopies;
 short dmDefaultSource;
 short dmPrintQuality;

 }DUMMYSTRUCTNAME;

 struct
 {
 POINTL dmPosition;
 unsigned long dmDisplayOrientation;
 unsigned long dmDisplayFixedOutput;

 }DUMMYSTRUCTNAME2;

 }DUMMYUNIONNAME;

 short dmColor;
 short dmDuplex;
 short dmYResolution;
 short dmTTOption;
 short dmCollate;
 unsigned char dmFormName[32];
 unsigned short dmLogPixels;
 unsigned long dmBitsPerPel;
 unsigned long dmPelsWidth;
 unsigned long dmPelsHeight;

 union
 {
 unsigned long dmDisplayFlags;
 unsigned long dmNup;

 }DUMMYUNIONNAME2;

 unsigned long dmDisplayFrequency;

 unsigned long dmICMMethod;
 unsigned long dmICMIntent;
 unsigned long dmMediaType;
 unsigned long dmDitherType;
 unsigned long dmReserved1;
 unsigned long dmReserved2;

 unsigned long dmPanningWidth;
 unsigned long dmPanningHeight;
};

typedef struct _devicemodeA DEVMODEA;

struct tagMSG
{
 HWND hwnd;
 unsigned int message;
 unsigned char padding1[4];
 unsigned long long wParam;
 long long lParam;
 unsigned long time;
 POINT pt;
 unsigned char padding2[4];
};

typedef struct tagMSG MSG;

struct _WIN32_FIND_DATAA
{
 unsigned long dwFileAttributes;
 FILETIME ftCreationTime;
 FILETIME ftLastAccessTime;
 FILETIME ftLastWriteTime;
 unsigned long nFileSizeHigh;
 unsigned long nFileSizeLow;
 unsigned long dwReserved0;
 unsigned long dwReserved1;
 char cFileName[260];
 char cAlternateFileName[14];
 unsigned char padding1[2];
};

typedef struct _WIN32_FIND_DATAA WIN32_FIND_DATAA;

typedef long long (__stdcall * DLGPROC)(HWND, unsigned int, unsigned long long, long long);

typedef long long (__stdcall * WNDPROC)(HWND, unsigned int, unsigned long long, long long);

struct tagWNDCLASSA
{
 unsigned int style;
 unsigned char padding1[4];
 WNDPROC lpfnWndProc;
 int cbClsExtra;
 int cbWndExtra;
 HINSTANCE hInstance;
 HICON hIcon;
 HCURSOR hCursor;
 HBRUSH hbrBackground;
 const char* lpszMenuName;
 const char* lpszClassName;
};

typedef struct tagWNDCLASSA WNDCLASSA;

__declspec(dllimport) int __cdecl _CrtSetDbgFlag(int _NewFlag);

__declspec(dllimport) int __stdcall AdjustWindowRect(RECT* lpRect, unsigned long dwStyle, int bMenu);

__declspec(dllimport) int __stdcall BitBlt(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, unsigned long rop);

__declspec(dllimport) long __stdcall ChangeDisplaySettingsA(DEVMODEA* lpDevMode, unsigned long dwFlags);

__declspec(dllimport) int __stdcall ClientToScreen(HWND hWnd, POINT* lpPoint);

__declspec(dllimport) int __stdcall CloseHandle(HANDLE hObject);

__declspec(dllimport) HDC __stdcall CreateCompatibleDC(HDC hdc);

__declspec(dllimport) HBITMAP __stdcall CreateDIBSection(HDC hdc, const BITMAPINFO* pbmi, unsigned int usage, void** ppvBits, HANDLE hSection, unsigned long offset);

__declspec(dllimport) HANDLE __stdcall CreateMutexA(SECURITY_ATTRIBUTES* lpMutexAttributes, int bInitialOwner, const char* lpName);

__declspec(dllimport) HWND __stdcall CreateWindowExA(unsigned long dwExStyle, const char* lpClassName, const char* lpWindowName, unsigned long dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, void* lpParam);

__declspec(dllimport) long long __stdcall DefWindowProcA(HWND hWnd, unsigned int Msg, unsigned long long wParam, long long lParam);

__declspec(dllimport) int __stdcall DeleteDC(HDC hdc);

__declspec(dllimport) int __stdcall DeleteObject(HGDIOBJ ho);

__declspec(dllimport) int __stdcall DestroyWindow(HWND hWnd);

__declspec(dllimport) long long __stdcall DialogBoxParamA(HINSTANCE hInstance, const char* lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, long long dwInitParam);

__declspec(dllimport) long long __stdcall DispatchMessageA(const MSG* lpMsg);

__declspec(dllimport) int __stdcall EndDialog(HWND hDlg, long long nResult);

__declspec(dllimport) int __stdcall EnumDisplaySettingsA(const char* lpszDeviceName, unsigned long iModeNum, DEVMODEA* lpDevMode);

__declspec(dllimport) int __stdcall FindClose(HANDLE hFindFile);

__declspec(dllimport) HANDLE __stdcall FindFirstFileA(const char* lpFileName, WIN32_FIND_DATAA* lpFindFileData);

__declspec(dllimport) int __stdcall FindNextFileA(HANDLE hFindFile, WIN32_FIND_DATAA* lpFindFileData);

__declspec(dllimport) int __stdcall GdiFlush();

__declspec(dllimport) int __stdcall GetCursorPos(POINT* lpPoint);

__declspec(dllimport) HDC __stdcall GetDC(HWND hWnd);

__declspec(dllimport) int __stdcall GetDeviceCaps(HDC hdc, int index);

__declspec(dllimport) unsigned int __stdcall GetDlgItemTextA(HWND hDlg, int nIDDlgItem, char* lpString, int cchMax);

__declspec(dllimport) unsigned long __stdcall GetLastError();

//__declspec(dllimport) long long __stdcall GetWindowLongPtrA(HWND hWnd, int nIndex);
__declspec(dllimport) unsigned long long __stdcall GetWindowLongPtrA(HWND hWnd, int nIndex);

__declspec(dllimport) HCURSOR __stdcall LoadCursorA(HINSTANCE hInstance, const char* lpCursorName);

__declspec(dllimport) HANDLE __stdcall LoadImageA(HINSTANCE hInst, const char* name, unsigned int type, int cx, int cy, unsigned int fuLoad);

__declspec(dllimport) int __stdcall MessageBoxA(HWND hWnd, const char* lpText, const char* lpCaption, unsigned int uType);

__declspec(dllimport) int __stdcall PeekMessageA(MSG* lpMsg, HWND hWnd, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax, unsigned int wRemoveMsg);

__declspec(dllimport) int __stdcall PostMessageA(HWND hWnd, unsigned int Msg, unsigned long long wParam, long long lParam);

__declspec(dllimport) void __stdcall PostQuitMessage(int nExitCode);

__declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount);

__declspec(dllimport) int __stdcall QueryPerformanceFrequency(LARGE_INTEGER* lpFrequency);

__declspec(dllimport) unsigned short __stdcall RegisterClassA(const WNDCLASSA *lpWndClass);

__declspec(dllimport) int __stdcall ReleaseCapture();

__declspec(dllimport) int __stdcall ReleaseDC(HWND hWnd, HDC hDC);

__declspec(dllimport) int __stdcall ScreenToClient(HWND hWnd, POINT* lpPoint);

__declspec(dllimport) HGDIOBJ __stdcall SelectObject(HDC hdc, HGDIOBJ h);

__declspec(dllimport) HWND __stdcall SetCapture(HWND hWnd);

__declspec(dllimport) int __stdcall SetDlgItemTextA(HWND hDlg, int nIDDlgItem, const char* lpString);

__declspec(dllimport) void __stdcall SetLastError(unsigned long dwErrCode);

//__declspec(dllimport) long long __stdcall SetWindowLongPtrA(HWND hWnd, int nIndex, long long dwNewLong);
__declspec(dllimport) unsigned long long __stdcall SetWindowLongPtrA(HWND hWnd, int nIndex, unsigned long long dwNewLong);

__declspec(dllimport) int __stdcall ShowWindow(HWND hWnd, int nCmdShow);

__declspec(dllimport) void __stdcall Sleep(unsigned long dwMilliseconds);

__declspec(dllimport) int __stdcall StretchBlt(HDC hdcDest, int xDest, int yDest, int wDest, int hDest, HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, unsigned long rop);

__declspec(dllimport) int __stdcall TranslateMessage(const MSG* lpMsg);

__declspec(dllimport) int __stdcall UnregisterClassA(const char* lpClassName, HINSTANCE hInstance);

__declspec(dllimport) unsigned int __stdcall WinExec(const char* lpCmdLine, unsigned int uCmdShow);

typedef void* HANDLE;

typedef struct HWND__* HWND;

typedef struct _DDCAPS_DX7 DDCAPS_DX7;

typedef DDCAPS_DX7 DDCAPS;

typedef DDCAPS* LPDDCAPS;

typedef struct IDirectDrawPalette* LPDIRECTDRAWPALETTE;
typedef struct IDirectDrawClipper* LPDIRECTDRAWCLIPPER;

struct tagPALETTEENTRY
{
 unsigned char peRed;
 unsigned char peGreen;
 unsigned char peBlue;
 unsigned char peFlags;
};

struct _GUID
{
 unsigned long Data1;
 unsigned short Data2;
 unsigned short Data3;
 unsigned char Data4[8];
};

typedef struct _GUID GUID;

typedef GUID IID;

typedef struct tagPALETTEENTRY PALETTEENTRY;
typedef struct tagPALETTEENTRY* PPALETTEENTRY;
typedef struct tagPALETTEENTRY* LPPALETTEENTRY;

struct _DDSCAPS
{
 unsigned long dwCaps;
};

typedef struct _DDSCAPS DDSCAPS;

typedef DDSCAPS* LPDDSCAPS;

struct _DDPIXELFORMAT
{
 unsigned long dwSize;
 unsigned long dwFlags;
 unsigned long dwFourCC;

 union
 {
 unsigned long dwRGBBitCount;
 unsigned long dwYUVBitCount;
 unsigned long dwZBufferBitDepth;
 unsigned long dwAlphaBitDepth;
 unsigned long dwLuminanceBitCount;
 unsigned long dwBumpBitCount;
 unsigned long dwPrivateFormatBitCount;

 };

 union
 {
 unsigned long dwRBitMask;
 unsigned long dwYBitMask;
 unsigned long dwStencilBitDepth;
 unsigned long dwLuminanceBitMask;
 unsigned long dwBumpDuBitMask;
 unsigned long dwOperations;

 };

 union
 {
 unsigned long dwGBitMask;
 unsigned long dwUBitMask;
 unsigned long dwZBitMask;
 unsigned long dwBumpDvBitMask;

 struct
 {
 unsigned short wFlipMSTypes;
 unsigned short wBltMSTypes;

 }MultiSampleCaps;

 };

 union
 {
 unsigned long dwBBitMask;
 unsigned long dwVBitMask;
 unsigned long dwStencilBitMask;
 unsigned long dwBumpLuminanceBitMask;

 };

 union
 {
 unsigned long dwRGBAlphaBitMask;
 unsigned long dwYUVAlphaBitMask;
 unsigned long dwLuminanceAlphaBitMask;
 unsigned long dwRGBZBitMask;
 unsigned long dwYUVZBitMask;

 };
};

typedef struct _DDPIXELFORMAT DDPIXELFORMAT;

struct _DDCOLORKEY
{
 unsigned long dwColorSpaceLowValue;
 unsigned long dwColorSpaceHighValue;
};

typedef struct _DDCOLORKEY DDCOLORKEY;

typedef DDCOLORKEY* LPDDCOLORKEY;

struct _DDSURFACEDESC
{
 unsigned long dwSize;
 unsigned long dwFlags;
 unsigned long dwHeight;
 unsigned long dwWidth;

 union
 {
 long lPitch;
 unsigned long dwLinearSize;

 };

 unsigned long dwBackBufferCount;

 union
 {
 unsigned long dwMipMapCount;
 unsigned long dwZBufferBitDepth;
 unsigned long dwRefreshRate;
 };

 unsigned long dwAlphaBitDepth;
 unsigned long dwReserved;
 void* lpSurface;
 DDCOLORKEY ddckCKDestOverlay;
 DDCOLORKEY ddckCKDestBlt;
 DDCOLORKEY ddckCKSrcOverlay;
 DDCOLORKEY ddckCKSrcBlt;
 DDPIXELFORMAT ddpfPixelFormat;
 DDSCAPS ddsCaps;
};

typedef struct _DDSURFACEDESC DDSURFACEDESC;

typedef struct _DDSURFACEDESC* LPDDSURFACEDESC;

typedef struct IDirectDraw* LPDIRECTDRAW;

typedef struct IDirectDrawSurface* LPDIRECTDRAWSURFACE;

typedef long (__stdcall * LPDDENUMMODESCALLBACK)(LPDDSURFACEDESC, void*);

typedef long (__stdcall * LPDDENUMSURFACESCALLBACK)(LPDIRECTDRAWSURFACE, LPDDSURFACEDESC, void*);

struct __declspec(novtable) IDirectDraw // : public struct IUnknown
{

virtual __declspec(nothrow) long __stdcall QueryInterface(const IID&, void** ) = 0;
virtual __declspec(nothrow) unsigned long __stdcall AddRef() = 0;
virtual __declspec(nothrow) unsigned long __stdcall Release() = 0;

virtual __declspec(nothrow) long __stdcall Compact() = 0;
virtual __declspec(nothrow) long __stdcall CreateClipper(unsigned long, LPDIRECTDRAWCLIPPER*, struct IUnknown* ) = 0;
virtual __declspec(nothrow) long __stdcall CreatePalette(unsigned long, LPPALETTEENTRY, LPDIRECTDRAWPALETTE*, struct IUnknown* ) = 0;
virtual __declspec(nothrow) long __stdcall CreateSurface(DDSURFACEDESC*, LPDIRECTDRAWSURFACE*, struct IUnknown* ) = 0;
virtual __declspec(nothrow) long __stdcall DuplicateSurface(LPDIRECTDRAWSURFACE, LPDIRECTDRAWSURFACE* ) = 0;
virtual __declspec(nothrow) long __stdcall EnumDisplayModes(unsigned long, LPDDSURFACEDESC, void*, LPDDENUMMODESCALLBACK) = 0;
virtual __declspec(nothrow) long __stdcall EnumSurfaces(unsigned long, LPDDSURFACEDESC, void*, LPDDENUMSURFACESCALLBACK) = 0;
virtual __declspec(nothrow) long __stdcall FlipToGDISurface() = 0;
virtual __declspec(nothrow) long __stdcall GetCaps(LPDDCAPS, LPDDCAPS) = 0;
virtual __declspec(nothrow) long __stdcall GetDisplayMode(LPDDSURFACEDESC) = 0;
virtual __declspec(nothrow) long __stdcall GetFourCCCodes(unsigned long*, unsigned long*) = 0;
virtual __declspec(nothrow) long __stdcall GetGDISurface(LPDIRECTDRAWSURFACE*) = 0;
virtual __declspec(nothrow) long __stdcall GetMonitorFrequency(unsigned long*) = 0;
virtual __declspec(nothrow) long __stdcall GetScanLine(unsigned long*) = 0;
virtual __declspec(nothrow) long __stdcall GetVerticalBlankStatus(int*) = 0;
virtual __declspec(nothrow) long __stdcall Initialize(GUID*) = 0;
virtual __declspec(nothrow) long __stdcall RestoreDisplayMode() = 0;
virtual __declspec(nothrow) long __stdcall SetCooperativeLevel(HWND, unsigned long) = 0;
virtual __declspec(nothrow) long __stdcall SetDisplayMode(unsigned long, unsigned long, unsigned long) = 0;
virtual __declspec(nothrow) long __stdcall WaitForVerticalBlank(unsigned long, void* ) = 0;

};

typedef struct IDirectDrawSurface* LPDIRECTDRAWSURFACE;



struct _DDBLTFX
{
 unsigned long dwSize;
 unsigned long dwDDFX;
 unsigned long dwROP;
 unsigned long dwDDROP;
 unsigned long dwRotationAngle;
 unsigned long dwZBufferOpCode;
 unsigned long dwZBufferLow;
 unsigned long dwZBufferHigh;
 unsigned long dwZBufferBaseDest;
 unsigned long dwZDestConstBitDepth;

 union
 {
 unsigned long dwZDestConst;
 LPDIRECTDRAWSURFACE lpDDSZBufferDest;

 };

 unsigned long dwZSrcConstBitDepth;

 union
 {
 unsigned long dwZSrcConst;
 LPDIRECTDRAWSURFACE lpDDSZBufferSrc;

 };

 unsigned long dwAlphaEdgeBlendBitDepth;
 unsigned long dwAlphaEdgeBlend;
 unsigned long dwReserved;
 unsigned long dwAlphaDestConstBitDepth;

 union
 {
 unsigned long dwAlphaDestConst;
 LPDIRECTDRAWSURFACE lpDDSAlphaDest;

 };

 unsigned long dwAlphaSrcConstBitDepth;

 union
 {
 unsigned long dwAlphaSrcConst;
 LPDIRECTDRAWSURFACE lpDDSAlphaSrc;

 };

 union
 {
 unsigned long dwFillColor;
 unsigned long dwFillDepth;
 unsigned long dwFillPixel;
 LPDIRECTDRAWSURFACE lpDDSPattern;

 };

 DDCOLORKEY ddckDestColorkey;
 DDCOLORKEY ddckSrcColorkey;
};

typedef struct _DDBLTFX DDBLTFX;

typedef DDBLTFX* LPDDBLTFX;

struct _DDBLTBATCH
{
 RECT* lprDest;
 LPDIRECTDRAWSURFACE lpDDSSrc;
 RECT* lprSrc;
 unsigned long dwFlags;
 DDBLTFX* lpDDBltFx;

};

typedef struct _DDBLTBATCH DDBLTBATCH;

typedef DDBLTBATCH* LPDDBLTBATCH;



struct _DDOVERLAYFX
{
  unsigned long dwSize;
  unsigned long dwAlphaEdgeBlendBitDepth;
  unsigned long dwAlphaEdgeBlend;
  unsigned long dwReserved;
  unsigned long dwAlphaDestConstBitDepth;

  union
  {
    unsigned long dwAlphaDestConst;
    LPDIRECTDRAWSURFACE lpDDSAlphaDest;
  };

  unsigned long dwAlphaSrcConstBitDepth;

  union
  {
    unsigned long dwAlphaSrcConst;
    LPDIRECTDRAWSURFACE lpDDSAlphaSrc;
  };

  DDCOLORKEY dckDestColorkey;
  DDCOLORKEY dckSrcColorkey;
  unsigned long dwDDFX;
  unsigned long dwFlags;
};

typedef struct _DDOVERLAYFX DDOVERLAYFX;

typedef DDOVERLAYFX* LPDDOVERLAYFX;

struct __declspec(novtable) IDirectDrawSurface // : public struct IUnknown
{

virtual __declspec(nothrow) long __stdcall QueryInterface(const IID&, void** ) = 0;
virtual __declspec(nothrow) unsigned long __stdcall AddRef() = 0;
virtual __declspec(nothrow) unsigned long __stdcall Release() = 0;

virtual __declspec(nothrow) long __stdcall AddAttachedSurface(LPDIRECTDRAWSURFACE) = 0;
virtual __declspec(nothrow) long __stdcall AddOverlayDirtyRect(RECT*) = 0;
virtual __declspec(nothrow) long __stdcall Blt(RECT*, LPDIRECTDRAWSURFACE, RECT*, unsigned long, LPDDBLTFX) = 0;
virtual __declspec(nothrow) long __stdcall BltBatch(LPDDBLTBATCH, unsigned long, unsigned long ) = 0;
virtual __declspec(nothrow) long __stdcall BltFast(unsigned long, unsigned long, LPDIRECTDRAWSURFACE, RECT*, unsigned long) = 0;
virtual __declspec(nothrow) long __stdcall DeleteAttachedSurface(unsigned long, LPDIRECTDRAWSURFACE) = 0;
virtual __declspec(nothrow) long __stdcall EnumAttachedSurfaces(void*, LPDDENUMSURFACESCALLBACK) = 0;
virtual __declspec(nothrow) long __stdcall EnumOverlayZOrders(unsigned long, void*, LPDDENUMSURFACESCALLBACK) = 0;
virtual __declspec(nothrow) long __stdcall Flip(LPDIRECTDRAWSURFACE, unsigned long) = 0;
virtual __declspec(nothrow) long __stdcall GetAttachedSurface(DDSCAPS*, LPDIRECTDRAWSURFACE*) = 0;
virtual __declspec(nothrow) long __stdcall GetBltStatus(unsigned long) = 0;
virtual __declspec(nothrow) long __stdcall GetCaps(LPDDSCAPS) = 0;
virtual __declspec(nothrow) long __stdcall GetClipper(LPDIRECTDRAWCLIPPER*) = 0;
virtual __declspec(nothrow) long __stdcall GetColorKey(unsigned long, DDCOLORKEY*) = 0;
virtual __declspec(nothrow) long __stdcall GetDC(HDC*) = 0;
virtual __declspec(nothrow) long __stdcall GetFlipStatus(unsigned long) = 0;
virtual __declspec(nothrow) long __stdcall GetOverlayPosition(long*, long* ) = 0;
virtual __declspec(nothrow) long __stdcall GetPalette(LPDIRECTDRAWPALETTE*) = 0;
virtual __declspec(nothrow) long __stdcall GetPixelFormat(DDPIXELFORMAT*) = 0;
virtual __declspec(nothrow) long __stdcall GetSurfaceDesc(DDSURFACEDESC*) = 0;
virtual __declspec(nothrow) long __stdcall Initialize(LPDIRECTDRAW, DDSURFACEDESC*) = 0;
virtual __declspec(nothrow) long __stdcall IsLost() = 0;
virtual __declspec(nothrow) long __stdcall Lock(RECT*, DDSURFACEDESC*, unsigned long, HANDLE) = 0;
virtual __declspec(nothrow) long __stdcall ReleaseDC(HDC) = 0;
virtual __declspec(nothrow) long __stdcall Restore() = 0;
virtual __declspec(nothrow) long __stdcall SetClipper(LPDIRECTDRAWCLIPPER) = 0;
virtual __declspec(nothrow) long __stdcall SetColorKey(unsigned long, DDCOLORKEY*) = 0;
virtual __declspec(nothrow) long __stdcall SetOverlayPosition(long, long) = 0;
virtual __declspec(nothrow) long __stdcall SetPalette(LPDIRECTDRAWPALETTE) = 0;
virtual __declspec(nothrow) long __stdcall Unlock(void*) = 0;
virtual __declspec(nothrow) long __stdcall UpdateOverlay(RECT*, LPDIRECTDRAWSURFACE, RECT*, unsigned long, DDOVERLAYFX*) = 0;
virtual __declspec(nothrow) long __stdcall UpdateOverlayDisplay(unsigned long) = 0;
virtual __declspec(nothrow) long __stdcall UpdateOverlayZOrder(unsigned long, LPDIRECTDRAWSURFACE) = 0;

};

struct _RGNDATAHEADER
{
  unsigned long dwSize;
  unsigned long iType;
  unsigned long nCount;
  unsigned long nRgnSize;
  RECT rcBound;
};

typedef struct _RGNDATAHEADER RGNDATAHEADER;

typedef struct _RGNDATAHEADER* PRGNDATAHEADER;

struct _RGNDATA
{
  RGNDATAHEADER rdh;
  char Buffer[1];
};

typedef struct _RGNDATA RGNDATA;
typedef struct _RGNDATA* PRGNDATA;
typedef struct _RGNDATA* NPRGNDATA;
typedef struct _RGNDATA* LPRGNDATA;

struct __declspec(novtable) IDirectDrawClipper // : public IUnknown
{

virtual __declspec(nothrow) long __stdcall QueryInterface(const IID&, void** ) = 0;
virtual __declspec(nothrow) unsigned long __stdcall AddRef() = 0;
virtual __declspec(nothrow) unsigned long __stdcall Release() = 0;

virtual __declspec(nothrow) long __stdcall GetClipList(RECT*, LPRGNDATA, unsigned long*) = 0;
virtual __declspec(nothrow) long __stdcall GetHWnd(HWND*) = 0;
virtual __declspec(nothrow) long __stdcall Initialize(LPDIRECTDRAW, unsigned long) = 0;
virtual __declspec(nothrow) long __stdcall IsClipListChanged(int*) = 0;
virtual __declspec(nothrow) long __stdcall SetClipList(LPRGNDATA, unsigned long) = 0;
virtual __declspec(nothrow) long __stdcall SetHWnd(unsigned long, HWND) = 0;

};

#if 0
struct _DDSURFACEDESC
{
 unsigned long dwSize;
 unsigned long dwFlags;
 unsigned long dwHeight;
 unsigned long dwWidth;

 union
 {
 long lPitch;
 unsigned long dwLinearSize;

 };

 unsigned long dwBackBufferCount;

 union
 {
 unsigned long dwMipMapCount;
 unsigned long dwZBufferBitDepth;
 unsigned long dwRefreshRate;

 };

 unsigned long dwAlphaBitDepth;
 unsigned long dwReserved;
 void* lpSurface;
 DDCOLORKEY ddckCKDestOverlay;
 DDCOLORKEY ddckCKDestBlt;
 DDCOLORKEY ddckCKSrcOverlay;
 DDCOLORKEY ddckCKSrcBlt;
 DDPIXELFORMAT ddpfPixelFormat;
 DDSCAPS ddsCaps;
};
#endif

typedef struct _DDSURFACEDESC DDSURFACEDESC;

#define DDBLT_COLORFILL 0x00000400l
#define DDBLT_WAIT 0x01000000l

#define DDLOCK_SURFACEMEMORYPTR 0x00000000L
#define DDLOCK_WAIT 0x00000001L

#define DDSD_WIDTH 0x00000004l
#define DDSD_HEIGHT 0x00000002l
#define DDSD_CAPS 0x00000001l

#define DDSCL_NORMAL 0x00000008l

#define DDSCAPS_OFFSCREENPLAIN 0x00000040l
#define DDSCAPS_PRIMARYSURFACE 0x00000200l
#define DDSCAPS_VIDEOMEMORY 0x00004000l

//LoadLibraryA
__declspec(dllimport) HINSTANCE __stdcall LoadLibraryA(const char* lpLibFileName);

// GetProcAddress
typedef long long (__stdcall * FARPROC)();
__declspec(dllimport) FARPROC __stdcall GetProcAddress(HINSTANCE hModule, const char* lpProcName);

// FreeLibrary
__declspec(dllimport) int __stdcall FreeLibrary(HINSTANCE hLibModule);

#define SUCCEEDED(hResult) ( (long)hResult >= 0)

#define FAILED(hResult) ( (long)hResult < 0)

}

#endif

#define IDC_ARROW_A MAKEINTRESOURCEA(32512)

#define IDC_IBEAM_A MAKEINTRESOURCEA(32513)

int Error(const char* const errorString);
int Warning(const char* const warningString);
int Verbose(const char* const verboseString);

static int mainTerm(HWND hwnd);

static int RemoveHeapAllocation(void* heapAllocation);

static void* InsertHeapAllocation(size_t numBytesToAllocate);

static int InsertHandle(void* handle);

static int RemoveHandle(void* handle);

void* Allocate(size_t Size)
{
 return calloc(1, Size);
}

void DeAllocate(void* Memory)
{
 return free(Memory);
}

void TermAllocate()
{
}

void
ParticleSystemsInitGraphics
(
 void* /*backBufferPixelPointer*/,
 int /*backBufferViewPortWidth*/,
 int /*backBufferViewPortHeight*/,
 int /*backBufferBitDepth*/,
 int /*backBufferPitch*/
)
{
}

static INDEX_TYPE TestObjectEquivalent(CLIENT_POTYPE ClientObject1, CLIENT_POTYPE ClientObject2)
{
 INDEX_TYPE result = 0;

 if( !ClientObject1.object || !ClientObject2.object)
 {
 Error("ClientObject.object == 0");
 }
 else if(ClientObject1.object == ClientObject2.object)
 {
 result = 1;
 }

 return result;
}

static FontClient* _font = 0;

#if ENABLE_DIRECTDRAW

#if 0
struct _GUID
{
 unsigned long Data1;
 unsigned short Data2;
 unsigned short Data3;
 unsigned char Data4[8];
};

typedef struct _GUID GUID;
#endif

typedef long (__stdcall * LPDIRECTDRAWCREATE7)(GUID*, struct IDirectDraw**, struct IUnknown*);
#endif

struct GraphicsBlah
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

// Here we keep track of the current graphics mode
// we are in.
//
// We will try for Direct Draw, but
// that never works anyway, so the solid
// GRAPHICS_IMPLEMENTATION::GDI foundation is always there to catch us.
enum GRAPHICS_IMPLEMENTATION Implementation;

// If we want to be nice then we won't try to change
// the bit depth on the user.
bool beNice;

// If we are not nice and really mean we can
// try to force full screen mode onto the user.
bool forceFullScreen;

bool isModeChangeActive;

unsigned char padding1[1];

int width;
int height;
int bitDepth;

int oldWidth;
int oldHeight;
int oldBitDepth;

uint8_t** backbufferArray;

HDC backbufferDC;
HBITMAP backbufferBitmapHB;
HGDIOBJ backbufferCleanUp;

HWND _hWindow;

#if ENABLE_DIRECTDRAW
HINSTANCE hInstDDraw7;
LPDIRECTDRAWCREATE7 dDCreate7;
struct IDirectDraw* ddraw_obj;
struct IDirectDrawClipper* ddraw_screenclipper;
struct IDirectDrawSurface* ddraw_screen;
struct IDirectDrawSurface* ddraw_backbuffer;
#endif

};

static GraphicsBlah/*GraphicsClient*/* _graphics = 0;

// statics are initialized to 0, I explicitly type it here
// for readability and emphasis
static FILE* file = 0;

static int numErrors = 0;
static int numWarnings = 0;

static int ErrorBox(const char* const errorString)
{
 int result = -1;

 char ErrorString1[514] = {0};
 char ErrorString2[514] = {0};

 if( !errorString || !errorString[0] )
 {
 assert("ErrorBox -- errorString" && 0);
 goto label_return;
 }

 ++numErrors;

 if(snprintf(ErrorString1, 512, "Error# : %i\n", numErrors) < 0)
 {
 assert("_snprintf(...) failure -- fatal low level system error" && 0);
 goto label_return;
 }

 if(snprintf(ErrorString2, 512, "Error : %s\n\n", errorString) < 0)
 {
 assert("_snprintf(...) failure -- fatal low level system error" && 0);
 goto label_return;
 }

 if(MessageBoxA(0, ErrorString2, ErrorString1, MB_ICONERROR | MB_OK) == 0)
 {
 assert("MessageBox(...) failure" && 0);
 }

 result = 0;

label_return:
 return result;
}

int Error(const char* const errorString)
{
 int result = -1;

 if(file && file != (FILE*)0xff)
 {
 if( !errorString || !errorString[0] )
 {
 assert("Error -- errorString" && 0);
 goto label_return;
 }

 ++numErrors;

 if(fprintf(file, "Error# : %i\n", numErrors) < 0)
 {
 --numErrors;

 ErrorBox(errorString);

 ErrorBox("fprintf(...) failure -- fatal low level system error");

 goto label_return;
 }

 if(fprintf(file, "Error : %s\n\n", errorString) < 0)
 {
 --numErrors;

 ErrorBox(errorString);

 ErrorBox("fprintf(...) failure -- fatal low level system error");
 }
 }

#ifndef NDEBUG
 else
 {
 ErrorBox("Error -- file == 0");

 ErrorBox(errorString);
 }
#endif

 result = 0;

label_return:
 return result;
}

int Warning(const char* const warningString)
{
 int result = -1;

 if(file && file != (FILE*)0xff)
 {
 if( !warningString || !warningString[0] )
 {
 assert("Warning -- warningString" && 0);
 goto label_return;
 }

 ++numWarnings;

 if(fprintf(file, "Warning# : %i\n", numWarnings) < 0)
 {
 --numWarnings;

 // If fprintf fails load up the warning as an error
 ErrorBox(warningString);

 ErrorBox("fprintf(...) failure -- fatal low level system error");

 goto label_return;
 }

 if(fprintf(file, "Warning : %s\n\n", warningString) < 0)
 {
 --numWarnings;

 // If fprintf fails load up the warning as an error.
 ErrorBox(warningString);

 ErrorBox("fprintf(...) failure -- fatal low level system error");
 }
 }

#ifndef NDEBUG
 else
 {
 ErrorBox("Error -- file == 0");

 // If file == 0 then treat the warning as an error
 ErrorBox(warningString);
 }
#endif

 result = 0;

label_return:
 return result;
}

int Verbose(const char* const verboseString)
{
 int result = -1;

 if(file && file != (FILE*)0xff)
 {
 if( !verboseString || !verboseString[0] )
 goto label_return;

 fprintf(file, "%s\n\n", verboseString);
 }

 result = 0;

label_return:
 return result;
}

#if 0
enum class GRAPHICS_IMPLEMENTATION
{
 GDI = 0,
 DIRECTDRAW

}GRAPHICS_IMPLEMENTATION;
#endif

//struct graphicsComInternal
//{
// void* _this;
//};

struct WindowStyle
{

enum
{
#if 0
 WINDOWSTYLE_ERROR = Graphics::GRAPHICS_ERROR,
 WINDOWSTYLE_OK = Graphics::GRAPHICS_OK,
 WINDOWSTYLE_WINDOW = Graphics::GRAPHICS_WINDOW,
 WINDOWSTYLE_FULLSCREEN = Graphics::GRAPHICS_FULLSCREEN
#else
 WINDOWSTYLE_ERROR = 0xffffffff,
 WINDOWSTYLE_OK = 0,
 WINDOWSTYLE_WINDOW = 1,
 WINDOWSTYLE_FULLSCREEN = 2
#endif
};

static pointInteger origin;

static pointInteger size;

static rectInteger menu;

static int style;

// These function prototypes are used to stop class instantiation.

static pointInteger getOrigin() // pointInteger WindowStyle::getOrigin()
{
 return origin;
}

static pointInteger getSize(GraphicsClient* _this, bool clamp) // pointInteger WindowStyle::getSize(bool clamp)
{
 pointInteger temporary = {0, 0};

 if( !clamp || style == WINDOWSTYLE_FULLSCREEN)
 {
 temporary = size;
 goto label_return;
 }

 temporary.x = size.x + menu.left + menu.right;
 temporary.y = size.y + menu.top + menu.bottom;

 if(temporary.x >= _this->GraphicsOldWidth(_this) )
 {
 temporary.x = _this->GraphicsOldWidth(_this) - menu.left - menu.right - 1;
 }

 if(temporary.y >= _this->GraphicsOldHeight(_this) )
 {
 temporary.y = _this->GraphicsOldHeight(_this) - menu.top - menu.bottom - 1;
 }

 temporary.x -= menu.left + menu.right;
 temporary.y -= menu.top + menu.bottom;

label_return:
 return temporary;
}

static rectInteger getMenuRect() // rectInteger WindowStyle::getMenuRect()
{
 return menu;
}

static int getStyle() // int WindowStyle::getStyle()
{
 return style;
}

static pointInteger setOrigin(int x, int y) // pointInteger WindowStyle::setOrigin(int x, int y)
{
 origin.x = x;
 origin.y = y;

 return origin;
}

static int setSize(GraphicsClient* _this, int width, int height) // int WindowStyle::setSize(int width, int height)
{
 width += menu.left + menu.right;
 height += menu.top + menu.bottom;

 if(width <= 0 || height <= 0)
 goto label_return;

 if(width >= _this->GraphicsOldWidth(_this) || height >= _this->GraphicsOldHeight(_this) )
 {
 style = WINDOWSTYLE_FULLSCREEN;
 goto label_return;
 }

 size.x = width - menu.left - menu.right;
 size.y = height - menu.top - menu.bottom;

label_return:
 return style;
}

static rectInteger setMenuRect(int leftEdgeMenuThickness, int topEdgeMenuThickness, int rightEdgeMenuThickness, int bottomEdgeMenuThickness) // rectInteger WindowStyle::setMenuRect(int leftEdgeMenuThickness, int topEdgeMenuThickness, int rightEdgeMenuThickness, int bottomEdgeMenuThickness)
{
 menu.left = leftEdgeMenuThickness;
 menu.top = topEdgeMenuThickness;
 menu.right = rightEdgeMenuThickness;
 menu.bottom = bottomEdgeMenuThickness;

 return menu;
}

static int setStyle() // int WindowStyle::setStyle()
{
 if(style == WINDOWSTYLE_WINDOW)
 {
 style = WINDOWSTYLE_FULLSCREEN;
 }
 else if(style == WINDOWSTYLE_FULLSCREEN)
 {
 style = WINDOWSTYLE_WINDOW;
 }

 return style;
}

}; // class WindowStyle

// Give the WindowStyle class static variables default values.
pointInteger WindowStyle::origin = {-1, -1};
pointInteger WindowStyle::size = {-1, -1};

rectInteger WindowStyle::menu = {-1, -1, -1, -1};

int WindowStyle::style = WINDOWSTYLE_WINDOW;
// End initialization of WindowStyle class static variables.

enum
{
 GRAPHICS_ERROR = 0xffffffff,
 GRAPHICS_OK = 0,
 GRAPHICS_WINDOW = 1,
 GRAPHICS_FULLSCREEN = 2
};

//struct GraphicsClient
//{
//};

static long long __stdcall GraphicsAboutDlgProc(HWND hDlg, unsigned int msg, unsigned long long wParam, long long lParam);

static long long __stdcall GraphicsInputDlgProc(HWND hDlg, unsigned int msg, unsigned long long wParam, long long lParam);

static long long __stdcall GraphicsWindowProc(HWND hwnd, unsigned int msg, unsigned long long wParam, long long lParam);

static long long GraphicsAboutDlgProcWrapper(GraphicsClient* /*_this*/, HWND hDlg, unsigned int msg, unsigned long long wParam, long long lParam)
{
 return GraphicsAboutDlgProc(hDlg, msg, wParam, lParam);
}

static long long GraphicsInputDlgProcWrapper(GraphicsClient* /*_this*/, HWND hDlg, unsigned int msg, unsigned long long wParam, long long lParam)
{
 return GraphicsInputDlgProc(hDlg, msg, wParam, lParam);
}

static long long GraphicsWindowProcWrapper(GraphicsClient* /*_this*/, HWND hwnd, unsigned int msg, unsigned long long wParam, long long lParam)
{
 return GraphicsWindowProc(hwnd, msg, wParam, lParam);
}

static void _GraphicsRenderPoint32(GraphicsClient* _this, int x0, int y0, int c0);
static void GraphicsRenderPoint32(GraphicsClient* _this, int x0, int y0, int c0);

static void _GraphicsRenderLine32(GraphicsClient* _this, int x0, int y0, int x1, int y1, int c0, int c1);
static void GraphicsRenderLine32(GraphicsClient* _this, int x0, int y0, int x1, int y1, int c0, int c1);

static void _GraphicsRenderCircle32(GraphicsClient* _this, int x0, int y0, int r0, int c0, int c1);
static void GraphicsRenderCircle32(GraphicsClient* _this, int x0, int y0, int r0, int c0, int c1);

static enum GRAPHICS_IMPLEMENTATION GraphicsImplementation(GraphicsClient* reference)
{
 enum GRAPHICS_IMPLEMENTATION implementation = GRAPHICS_IMPLEMENTATION::GDI;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 implementation = _this->Implementation;

label_return:
 return implementation;
}

static void GraphicsSafeMode(GraphicsClient* reference)
{
 unsigned short widthHeight[2] = {0};

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 if( !_this->_hWindow)
 goto label_return;

 _this->GraphicsTermScreenAndBackBuffer(reference);

 widthHeight[0] = (unsigned short)_this->oldWidth;
 widthHeight[1] = (unsigned short)_this->oldHeight;

 _this->Implementation = GRAPHICS_IMPLEMENTATION::GDI;
 BlahLog2("GRAPHICS_IMPLEMENTATION::GDI\n");

 GraphicsWindowProc(_this->_hWindow, WM_DISPLAYCHANGE, (unsigned long long)_this->oldBitDepth, *(unsigned long*)widthHeight);

label_return:
 return;
}

static bool GraphicsIsModeChangeActive(GraphicsClient* reference)
{
 bool isModeChangeActive = false;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 isModeChangeActive = _this->isModeChangeActive;

label_return:
 return isModeChangeActive;
}

static int GraphicsWidth(GraphicsClient* reference)
{
 int width = -1;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 width = _this->width;

label_return:
 return width;
}

static int GraphicsHeight(GraphicsClient* reference)
{
 int height = -1;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 height = _this->height;

label_return:
 return height;
}

static int GraphicsBitDepth(GraphicsClient* reference)
{
 int bitDepth = -1;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 bitDepth = _this->bitDepth;

label_return:
 return bitDepth;
}

static int GraphicsClientWidth(GraphicsClient* reference)
{
 int width = -1;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 width = _this->width;

label_return:
 return width;
}

static int GraphicsClientHeight(GraphicsClient* reference)
{
 int height = -1;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 height = _this->height;

label_return:
 return height;
}

static int GraphicsClientBitDepth(GraphicsClient* reference)
{
 int bitDepth = -1;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 bitDepth = _this->bitDepth;

label_return:
 return bitDepth;
}

static int GraphicsOldWidth(GraphicsClient* reference)
{
 int oldWidth = -1;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 oldWidth = _this->oldWidth;

label_return:
 return oldWidth;
}

static int GraphicsOldHeight(GraphicsClient* reference)
{
 int oldHeight = -1;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 oldHeight = _this->oldHeight;

label_return:
 return oldHeight;
}

static int GraphicsOldBitDepth(GraphicsClient* reference)
{
 int oldBitDepth = -1;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 oldBitDepth = _this->oldBitDepth;

label_return:
 return oldBitDepth;
}

static uint8_t** GraphicsBackBufferFunction(GraphicsClient* reference)
{
 uint8_t** backbufferArray = 0;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 backbufferArray = _this->backbufferArray;

label_return:
 return backbufferArray;
}

static int GraphicsUnlockBackBuffer(GraphicsClient* reference)
{
 int result = GRAPHICS_ERROR;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 switch(_this->GraphicsImplementation(reference) ) // switch(graphicsImplementation() )
 {

 case GRAPHICS_IMPLEMENTATION::GDI: // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::GDI
 {
 result = GRAPHICS_OK;
 }
 break; // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::GDI

 case GRAPHICS_IMPLEMENTATION::DIRECTDRAW: // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::DIRECTDRAW
 {
#if ENABLE_DIRECTDRAW
 long hResult = 0;

 hResult = _this->ddraw_backbuffer->Unlock(_this->backbufferArray[0] );

 if(FAILED(hResult) )
 {
 Error("IDirectDrawSurface::Unlock(...) has failed for the back buffer");

 _this->GraphicsSafeMode(reference);

 goto label_return;
 }

 result = GRAPHICS_OK;
#endif
 }
 break; // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::DIRECTDRAW

 } // switch(graphicsImplementation() )

label_return:
 if(result == GRAPHICS_ERROR)
 {
 Error("The OS code is using an invalid graphics implementation");
 }

 return result;
}

static int GraphicsLockBackBuffer(GraphicsClient* reference)
{
 int result = GRAPHICS_ERROR;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 switch(_this->GraphicsImplementation(reference) ) // switch(graphicsImplementation() )
 {

 case GRAPHICS_IMPLEMENTATION::GDI: // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::GDI
 {
 // Flush GRAPHICS_IMPLEMENTATION::GDI before testing the back buffer
 if( !GdiFlush() )
 {
 Error("GdiFlush(...) function failure");

 goto label_return;
 }

 result = GRAPHICS_OK;
 }
 break; // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::GDI

 case GRAPHICS_IMPLEMENTATION::DIRECTDRAW: // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::DIRECTDRAW
 {
#if ENABLE_DIRECTDRAW
 DDSURFACEDESC ddsd = {0};

 long hResult = 0;

 ddsd.dwSize = sizeof(DDSURFACEDESC);

 hResult = _this->ddraw_backbuffer->Lock(0, &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, 0);

 if(FAILED(hResult) )
 {
 Error("IDirectDrawSurface::Lock(...) has failed for the back buffer");

 _this->GraphicsSafeMode(reference);

 goto label_return;
 }

 if(_this->backbufferArray[0] != ddsd.lpSurface || _this->backbufferArray[1] != (uint8_t*)ddsd.lpSurface + ddsd.lPitch)
 {
 uint8_t* surface = (uint8_t*)ddsd.lpSurface;

 for(int index = 0; index < _this->GraphicsClientHeight(reference); index++)
 {
 _this->backbufferArray[index] = surface + index * (int)ddsd.lPitch;
 }
 }

 result = GRAPHICS_OK;
#endif
 }
 break; // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::DIRECTDRAW

 } // switch(graphicsImplementation() )

label_return:
 if(result == GRAPHICS_ERROR)
 {
 Error("The OS code is using an invalid graphics implementation");
 }

 return result;
}

static int GraphicsClearBackBuffer(GraphicsClient* reference)
{
 int result = GRAPHICS_ERROR;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 switch(_this->GraphicsImplementation(reference) ) // switch(graphicsImplementation() )
 {

 case GRAPHICS_IMPLEMENTATION::GDI: // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::GDI
 {
 // Clear back buffer
 if( !BitBlt(_this->backbufferDC, 0, 0, _this->GraphicsClientWidth(reference), _this->GraphicsClientHeight(reference), 0, 0, 0, BLACKNESS) )
 {
 Error("BitBlt(...) function failure");

 goto label_return;
 }

 result = GRAPHICS_OK;
 }
 break; // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::GDI

 case GRAPHICS_IMPLEMENTATION::DIRECTDRAW: // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::DIRECTDRAW
 {
#if ENABLE_DIRECTDRAW
 DDBLTFX ddfx = {0};

 long hResult = 0;

 ddfx.dwSize = sizeof(DDBLTFX);

 ddfx.dwFillColor = 0x00000000;

 hResult = _this->ddraw_backbuffer->Blt(0, 0, 0, DDBLT_COLORFILL | DDBLT_WAIT, &ddfx);

 if(FAILED(hResult) )
 {
 Error("ddraw_backbuffer->Blt(...) function failure");

 _this->GraphicsSafeMode(reference);

 goto label_return;
 }

 result = GRAPHICS_OK;
#endif
 }
 break; // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::DIRECTDRAW

 } // switch(graphicsImplementation() )

label_return:
 if(result == GRAPHICS_ERROR)
 {
 Error("The OS code is using an invalid graphics implementation");
 }

 return result;
}

static int GraphicsDrawBackBufferToScreen(GraphicsClient* reference, HWND hWindow)
{
 int result = GRAPHICS_ERROR;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 switch(_this->GraphicsImplementation(reference) ) // switch(graphicsImplementation() )
 {

 case GRAPHICS_IMPLEMENTATION::GDI: // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::GDI
 {
 HDC screen = 0;

 // Get the screen handle so we can blt to the screen
 screen = GetDC(hWindow);

 if( !screen)
 {
 Error("(screen = GetDC(hWindow) ) == 0");

 goto label_return;
 }

 if( !StretchBlt(screen, 0, 0, _this->GraphicsWidth(reference), _this->GraphicsHeight(reference), _this->backbufferDC, 0, 0, _this->GraphicsClientWidth(reference), _this->GraphicsClientHeight(reference), SRCCOPY) )
 {
 Error("StretchBlt(...) function failure");

 if(ReleaseDC(hWindow, screen) != 1)
 {
 Error("ReleaseDC(...) function failure");
 }

 goto label_return;
 }

 // Release the screen handle
 if(ReleaseDC(hWindow, screen) != 1)
 {
 Error("ReleaseDC(...) function failure");

 goto label_return;
 }

 result = GRAPHICS_OK;
 }
 break; // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::GDI

 case GRAPHICS_IMPLEMENTATION::DIRECTDRAW: // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::DIRECTDRAW
 {
#if ENABLE_DIRECTDRAW
 rectInteger rectBackBuffer = {0};
 rectInteger rectScreen = {0};

 long hResult = 0;

 if( !ClientToScreen(hWindow, (POINT*) &rectScreen) )
 {
 Error("The function ClientToScreen(...) has failed");

 goto label_return;
 }

 rectBackBuffer.right = _this->GraphicsClientWidth(reference);
 rectBackBuffer.bottom = _this->GraphicsClientHeight(reference);

 rectScreen.left = rectScreen.left;
 rectScreen.top = rectScreen.top;

 rectScreen.right = rectScreen.left + _this->GraphicsWidth(reference);
 rectScreen.bottom = rectScreen.top + _this->GraphicsHeight(reference);

 hResult = _this->ddraw_screen->Blt( (RECT*) &rectScreen, _this->ddraw_backbuffer, (RECT*) &rectBackBuffer, DDBLT_WAIT, 0);

 if(FAILED(hResult) )
 {
 Error("ddraw_screen->Blt(...) function failure");

 _this->GraphicsSafeMode(reference);

 goto label_return;
 }

 result = GRAPHICS_OK;
#endif
 }
 break; // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::DIRECTDRAW

 } // switch(graphicsImplementation() )

label_return:
 if(result == GRAPHICS_ERROR)
 {
 Error("The OS code is using an invalid graphics implementation");
 }

 return result;
}

static int GraphicsSaveOldMode(GraphicsClient* reference)
{
 int result = GRAPHICS_ERROR;

 HDC screen = 0;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 screen = GetDC(0);

 if( !screen)
 {
 Error("(screen = GetDC(0) ) == 0");

 goto label_return;
 }

 _this->oldWidth = GetDeviceCaps(screen, HORZRES);

 _this->oldHeight = GetDeviceCaps(screen, VERTRES);

 _this->oldBitDepth = GetDeviceCaps(screen, BITSPIXEL);

 _this->bitDepth = _this->oldBitDepth;

 if(ReleaseDC(0, screen) != 1)
 {
 Error("ReleaseDC(...) function failure");
 }

 if(_this->oldWidth <= 0 || _this->oldHeight <= 0)
 {
 goto label_return;
 }

 result = GRAPHICS_OK;

label_return:
 return result;
}

static int GraphicsRestoreOldMode(GraphicsClient* reference)
{
 int result = GRAPHICS_ERROR;

 long changeDisplaySettingsResult = 0;

 long index = 0;

 DEVMODEA DMode = {0};

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 //DMode.dmSize = sizeof(DEVMODEA);

 //DMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

 //DMode.dmBitsPerPel = (unsigned long)oldBitDepth;
 //DMode.dmPelsWidth = (unsigned long)oldWidth;
 //DMode.dmPelsHeight = (unsigned long)oldHeight;

 //DMode.dmBitsPerPel = 32;

 //DMode.dmDisplayFrequency = 60;

 _this->isModeChangeActive = true;

 index = -2;

 for(int sdfgdfg = 1; sdfgdfg; index++)
 {
 DEVMODEA blahDisplaySettings;
 memset( &blahDisplaySettings, 0, sizeof(DEVMODEA) );

 sdfgdfg = EnumDisplaySettingsA(0, *(unsigned long*) &index/*ENUM_CURRENT_SETTINGS*/, &blahDisplaySettings);

 // DM_BITSPERPEL Use the dmBitsPerPel value.
 // DM_PELSWIDTH Use the dmPelsWidth value.
 // DM_PELSHEIGHT Use the dmPelsHeight value.
 // DM_DISPLAYFLAGS Use the dmDisplayFlags value.
 // DM_DISPLAYFREQUENCY Use the dmDisplayFrequency value.
 // DM_POSITION Use the dmPosition value.

 //BlahLog("%i %i %i %i %i %i %i", index, blahDisplaySettings.dmBitsPerPel, blahDisplaySettings.dmPelsWidth, blahDisplaySettings.dmPelsHeight, blahDisplaySettings.dmDisplayFlags, blahDisplaySettings.dmDisplayFrequency, blahDisplaySettings.dmPosition);

 if(sdfgdfg == 198)
 {
 memcpy( &DMode, &blahDisplaySettings, sizeof(DEVMODEA) );

 break;
 }
 }

 DMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

 changeDisplaySettingsResult = ChangeDisplaySettingsA( &DMode, 0);

 // DISP_CHANGE_SUCCESSFUL the settings change was successful
 // DISP_CHANGE_BADDUALVIEW the settings change was unsuccessful because the system is DualView capable
 // DISP_CHANGE_BADFLAGS an invalid set of flags was passed in
 // DISP_CHANGE_BADMODE the graphics mode is not supported
 // DISP_CHANGE_BADPARAM an invalid parameter was passed in. This can include an invalid flag or combination of flags
 // DISP_CHANGE_FAILED the display driver failed the specified graphics mode
 // DISP_CHANGE_NOTUPDATED unable to write settings to the registry
 // DISP_CHANGE_RESTART the computer must be restarted for the graphics mode to work

 switch(changeDisplaySettingsResult)
 {
 case DISP_CHANGE_SUCCESSFUL: /*Verbose("DISP_CHANGE_SUCCESSFUL");*/ break;
 case DISP_CHANGE_BADDUALVIEW: Verbose("DISP_CHANGE_BADDUALVIEW"); break;
 case DISP_CHANGE_BADFLAGS: Verbose("DISP_CHANGE_BADFLAGS"); break;
 case DISP_CHANGE_BADMODE: Verbose("DISP_CHANGE_BADMODE"); break;
 case DISP_CHANGE_BADPARAM: Verbose("DISP_CHANGE_BADPARAM"); break;
 case DISP_CHANGE_FAILED: Verbose("DISP_CHANGE_FAILED"); break;
 case DISP_CHANGE_NOTUPDATED: Verbose("DISP_CHANGE_NOTUPDATED"); break;
 case DISP_CHANGE_RESTART: Verbose("DISP_CHANGE_RESTART"); break;
 default: Verbose("DISP_CHANGE_BLAH"); break;
 }

 if(changeDisplaySettingsResult != DISP_CHANGE_SUCCESSFUL)
 {
 Error("The function ChangeDisplaySettings(...) has failed");

 _this->isModeChangeActive = false;

 goto label_return;
 }

 _this->isModeChangeActive = false;

 result = GRAPHICS_OK;

label_return:
 return result;
}

static int GraphicsSetBitDepthTo32(GraphicsClient* reference)
{
 int result = GRAPHICS_ERROR;

 long changeDisplaySettingsResult = 0;

 long index = 0;

 DEVMODEA DMode;
 memset( &DMode, 0, sizeof(DEVMODEA) );

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 if( (_this->oldWidth >= _this->GraphicsWidth(reference) || _this->oldHeight >= _this->GraphicsHeight(reference) ) && _this->oldBitDepth == 32 && !_this->forceFullScreen)
 {
 result = GRAPHICS_OK;

 goto label_return;
 }

 //DMode.dmSize = sizeof(DEVMODEA);

 //DMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

 if(_this->oldWidth <= _this->GraphicsWidth(reference) && _this->oldHeight <= _this->GraphicsHeight(reference) )
 {
 DMode.dmPelsWidth = (unsigned long)_this->GraphicsWidth(reference);
 DMode.dmPelsHeight = (unsigned long)_this->GraphicsHeight(reference);
 }
 else
 {
 if(_this->forceFullScreen)
 {
 DMode.dmPelsWidth = (unsigned long)_this->GraphicsWidth(reference);
 DMode.dmPelsHeight = (unsigned long)_this->GraphicsHeight(reference);
 }
 else
 {
 DMode.dmPelsWidth = (unsigned long)_this->oldWidth;
 DMode.dmPelsHeight = (unsigned long)_this->oldHeight;
 }
 }

 //DMode.dmBitsPerPel = 32;

 //DMode.dmDisplayFrequency = 60;

 _this->isModeChangeActive = true;

 index = -2;

 for(int sdfgdfg = 1; sdfgdfg; index++)
 {
 DEVMODEA blahDisplaySettings;
 memset( &blahDisplaySettings, 0, sizeof(DEVMODEA) );

 sdfgdfg = EnumDisplaySettingsA(0, *(unsigned long*) &index/*ENUM_CURRENT_SETTINGS*/, &blahDisplaySettings);

 // DM_BITSPERPEL Use the dmBitsPerPel value.
 // DM_PELSWIDTH Use the dmPelsWidth value.
 // DM_PELSHEIGHT Use the dmPelsHeight value.
 // DM_DISPLAYFLAGS Use the dmDisplayFlags value.
 // DM_DISPLAYFREQUENCY Use the dmDisplayFrequency value.
 // DM_POSITION Use the dmPosition value.

 //BlahLog("%i %i %i %i %i %i %i", index, blahDisplaySettings.dmBitsPerPel, blahDisplaySettings.dmPelsWidth, blahDisplaySettings.dmPelsHeight, blahDisplaySettings.dmDisplayFlags, blahDisplaySettings.dmDisplayFrequency, blahDisplaySettings.dmPosition);

 if(sdfgdfg == 198)
 {
 memcpy( &DMode, &blahDisplaySettings, sizeof(DEVMODEA) );

 break;
 }
 }

 DMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

 changeDisplaySettingsResult = ChangeDisplaySettingsA( &DMode, 0);

 // DISP_CHANGE_SUCCESSFUL the settings change was successful
 // DISP_CHANGE_BADDUALVIEW the settings change was unsuccessful because the system is DualView capable
 // DISP_CHANGE_BADFLAGS an invalid set of flags was passed in
 // DISP_CHANGE_BADMODE the graphics mode is not supported
 // DISP_CHANGE_BADPARAM an invalid parameter was passed in. This can include an invalid flag or combination of flags
 // DISP_CHANGE_FAILED the display driver failed the specified graphics mode
 // DISP_CHANGE_NOTUPDATED unable to write settings to the registry
 // DISP_CHANGE_RESTART the computer must be restarted for the graphics mode to work

 switch(changeDisplaySettingsResult)
 {
 case DISP_CHANGE_SUCCESSFUL: /*Verbose("DISP_CHANGE_SUCCESSFUL");*/ break;
 case DISP_CHANGE_BADDUALVIEW: Verbose("DISP_CHANGE_BADDUALVIEW"); break;
 case DISP_CHANGE_BADFLAGS: Verbose("DISP_CHANGE_BADFLAGS"); break;
 case DISP_CHANGE_BADMODE: Verbose("DISP_CHANGE_BADMODE"); break;
 case DISP_CHANGE_BADPARAM: Verbose("DISP_CHANGE_BADPARAM"); break;
 case DISP_CHANGE_FAILED: Verbose("DISP_CHANGE_FAILED"); break;
 case DISP_CHANGE_NOTUPDATED: Verbose("DISP_CHANGE_NOTUPDATED"); break;
 case DISP_CHANGE_RESTART: Verbose("DISP_CHANGE_RESTART"); break;
 default: Verbose("DISP_CHANGE_BLAH"); break;
 }

 if(changeDisplaySettingsResult != DISP_CHANGE_SUCCESSFUL)
 {
 Error("The function ChangeDisplaySettings(...) has failed for 32 bit pixel depth");

 _this->isModeChangeActive = false;

 goto label_return;
 }

 _this->bitDepth = 32;

 _this->isModeChangeActive = false;

 result = GRAPHICS_OK;

label_return:
 return result;
}

static int GraphicsLoadBitmap(GraphicsClient* /*reference*/, HDC destination, int destinationWidth, int destinationHeight, char* sourceFileName)
{
 int result = GRAPHICS_ERROR;

 bool error = false;

 int sourceWidth = 0;
 int sourceHeight = 0;

 FILE* _file = 0;

 BITMAPFILEHEADER BHeader = {0};
 BITMAPINFO BInfo = { {0}, { {0} } };

 HDC BltDC = 0;
 HBITMAP BltHB = 0;
 HGDIOBJ CleanUp = 0;

 //GraphicsBlah* _this = (GraphicsBlah*)reference;
 //if( !_this)
 // goto label_return;

 BltDC = CreateCompatibleDC(0);

 HGDIOBJ deviceTempCleanUp = 0;

 InsertHandle(BltDC);

 if( !BltDC)
 {
 Error("(BltDC = CreateCompatibleDC(...) ) == 0");

 goto label_return;
 }

 _file = fopen(sourceFileName, "rb");

 InsertHandle(_file);

 if( !_file)
 {
 Error("(file = fopen(...) ) == 0");

 if( !DeleteDC(BltDC) )
 {
 Error("DeleteDC(...) function failure");
 }
 else
 {
 RemoveHandle(BltDC);
 }

 goto label_return;
 }

 if(fread( &BHeader, sizeof(BITMAPFILEHEADER), 1, _file) != 1)
 {
 Error("fread(...) error");

 if(fclose(_file) )
 {
 Error("fclose(...) error");
 }
 else
 {
 RemoveHandle(_file);
 }

 if( !DeleteDC(BltDC) )
 {
 Error("DeleteDC(...) function failure");
 }
 else
 {
 RemoveHandle(BltDC);
 }

 goto label_return;
 }

 if(fread( &BInfo, sizeof(BITMAPINFO), 1, _file) != 1)
 {
 Error("fread(...) error");

 if(fclose(_file) )
 {
 Error("fclose(...) error");
 }
 else
 {
 RemoveHandle(_file);
 }

 if( !DeleteDC(BltDC) )
 {
 Error("DeleteDC(...) function failure");
 }
 else
 {
 RemoveHandle(BltDC);
 }

 goto label_return;
 }

 sourceWidth = BInfo.bmiHeader.biWidth;
 sourceHeight = BInfo.bmiHeader.biHeight;

 if(sourceWidth <= 0 || sourceHeight <= 0)
 {
 Error("fread(...) error");

 if(fclose(_file) )
 {
 Error("fclose(...) error");
 }
 else
 {
 RemoveHandle(_file);
 }

 if( !DeleteDC(BltDC) )
 {
 Error("DeleteDC(...) function failure");
 }
 else
 {
 RemoveHandle(BltDC);
 }

 goto label_return;
 }

 if(fclose(_file) )
 {
 Error("fclose(...) error");

 error = true;
 }
 else
 {
 RemoveHandle(_file);
 }

 BltHB = (HBITMAP)LoadImageA(0, sourceFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

 InsertHandle(BltHB);

 if( !BltHB)
 {
 Error("(BltHB = LoadImage(...) ) == 0");

 if( !DeleteDC(BltDC) )
 {
 Error("DeleteDC(...) function failure");
 }
 else
 {
 RemoveHandle(BltDC);
 }

 goto label_return;
 }

 CleanUp = SelectObject(BltDC, BltHB);

 InsertHandle(CleanUp);

 if( !CleanUp || CleanUp == (void*)GDI_ERROR)
 {
 Error("(CleanUp = SelectObject(...) ) == 0");

 if( !DeleteObject(BltHB) )
 {
 Error("DeleteObject(..) function failure");
 }

 if( !DeleteDC(BltDC) )
 {
 Error("DeleteDC(...) function failure");
 }
 else
 {
 RemoveHandle(BltDC);
 }

 goto label_return;
 }

 if( !StretchBlt(destination, 0, 0, destinationWidth, destinationHeight, BltDC, 0, 0, sourceWidth, sourceHeight, SRCCOPY) )
 {
 Error("StretchBlt failure");

 error = true;
 }

 if(BltDC)
 {
 // Free all the GRAPHICS_IMPLEMENTATION::GDI objects
 deviceTempCleanUp = SelectObject(BltDC, CleanUp);

 if( !deviceTempCleanUp || deviceTempCleanUp == (void*)GDI_ERROR)
 {
 Error("(deviceTempCleanUp = SelectObject(...) ) == 0");

 error = true;
 }
 else
 {
 RemoveHandle(CleanUp);
 }

 if( !DeleteObject(BltHB) )
 {
 Error("DeleteObject(..) function failure");

 error = true;
 }
 else
 {
 RemoveHandle(BltHB);
 }

 if( !DeleteDC(BltDC) )
 {
 Error("DeleteDC(...) function failure");

 error = true;
 }
 else
 {
 RemoveHandle(BltDC);
 }
 }

 if( !error)
 result = GRAPHICS_OK;

label_return:
 return result;
}

static int GraphicsTermScreenAndBackBufferGDI(GraphicsClient* reference)
{
 int result = GRAPHICS_ERROR;

 bool error = false;

 HGDIOBJ TempCleanUp = 0;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 if(_this->backbufferDC)
 {
 // Free all the GRAPHICS_IMPLEMENTATION::GDI objects
 TempCleanUp = SelectObject(_this->backbufferDC, _this->backbufferCleanUp);

 if( !TempCleanUp || TempCleanUp == (void*)GDI_ERROR)
 {
 Error("(TempCleanUp = SelectObject(...) ) == 0");

 error = true;
 }
 else
 {
 RemoveHandle(_this->backbufferCleanUp);
 }

 if( !DeleteObject(_this->backbufferBitmapHB) )
 {
 Error("DeleteObject(..) function failure");

 error = true;
 }
 else
 {
 RemoveHandle(_this->backbufferBitmapHB);
 }

 if( !DeleteDC(_this->backbufferDC) )
 {
 Error("DeleteDC(...) function failure");

 error = true;
 }
 else
 {
 RemoveHandle(_this->backbufferDC);
 }

 _this->backbufferDC = 0;
 _this->backbufferCleanUp = 0;
 _this->backbufferBitmapHB = 0;
 }

 if( !error)
 result = GRAPHICS_OK;

label_return:
 return result;
}

#if ENABLE_DIRECTDRAW
static int GraphicsTermScreenAndBackBufferDIRECTDRAW(GraphicsClient* reference)
#else
static int GraphicsTermScreenAndBackBufferDIRECTDRAW(GraphicsClient* /*reference*/)
#endif
{
 int result = GRAPHICS_ERROR;

#if ENABLE_DIRECTDRAW
 bool error = false;

 long hResult = 0;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 if(_this->ddraw_backbuffer)
 {
 hResult = _this->ddraw_backbuffer->Release();

 _this->ddraw_backbuffer = 0;

 if(FAILED(hResult) )
 {
 Error("The DirectDraw back buffer object failed to release correctly.");

 error = true;
 }
 }

 if(_this->ddraw_screen)
 {
 hResult = _this->ddraw_screen->Release();

 _this->ddraw_screen = 0;

 if(FAILED(hResult) )
 {
 Error("The DirectDraw screen object failed to release correctly.");

 error = true;
 }
 }

 if(_this->ddraw_screenclipper)
 {
 hResult = _this->ddraw_screenclipper->Release();

 _this->ddraw_screenclipper = 0;

 if(FAILED(hResult) )
 {
 Error("The DirectDraw screen clipper object failed to release correctly.");

 error = true;
 }
 }

 if(_this->ddraw_obj)
 {
 hResult = _this->ddraw_obj->Release();

 _this->ddraw_obj = 0;

 if(FAILED(hResult) )
 {
 Error("The DirectDraw main object failed to release correctly.");

 error = true;
 }
 }

 if( !error)
 result = GRAPHICS_OK;
#endif

#if ENABLE_DIRECTDRAW
label_return:
#endif
 return result;
}

static int GraphicsTermScreenAndBackBuffer(GraphicsClient* reference)
{
 int result = GRAPHICS_OK;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 switch(_this->GraphicsImplementation(reference) ) // switch(graphicsImplementation() )
 {

 case GRAPHICS_IMPLEMENTATION::GDI: // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::GDI
 {
 result = _this->GraphicsTermScreenAndBackBufferGDI(reference);

 _this->GraphicsRestoreOldMode(reference);

 if(_this->backbufferArray)
 {
 RemoveHeapAllocation(_this->backbufferArray);

 _this->backbufferArray = 0;
 }
 }
 goto label_return; // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::GDI

 case GRAPHICS_IMPLEMENTATION::DIRECTDRAW: // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::DIRECTDRAW
 {
 result = _this->GraphicsTermScreenAndBackBufferDIRECTDRAW(reference);

 _this->GraphicsRestoreOldMode(reference);

 if(_this->backbufferArray)
 {
 RemoveHeapAllocation(_this->backbufferArray);

 _this->backbufferArray = 0;
 }
 }
 goto label_return; // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::DIRECTDRAW

 } // switch(graphicsImplementation() )

 result = GRAPHICS_ERROR;

label_return:
 if(result == GRAPHICS_ERROR)
 {
 Error("The OS code is using an invalid graphics implementation.");
 }

 return result;
}

static int GraphicsInitScreenAndBackBufferGDI(GraphicsClient* reference, HWND hWindow)
{
 int result = GRAPHICS_ERROR;

 int loop = 0;

 BITMAPINFO bInfo = { {0}, { {0} } };

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 if(_this->backbufferDC || _this->backbufferCleanUp || _this->backbufferBitmapHB)
 {
 result = 0;

 goto label_return;
 }

 bInfo.bmiHeader.biBitCount = 32;
 bInfo.bmiHeader.biWidth = _this->GraphicsClientWidth(reference);
 bInfo.bmiHeader.biHeight = _this->GraphicsClientHeight(reference);
 bInfo.bmiHeader.biPlanes = 1;
 bInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
 bInfo.bmiHeader.biCompression = BI_RGB;

 // Create the permanent container for the bitmap.
 _this->backbufferDC = CreateCompatibleDC(0);

 if( !_this->backbufferDC)
 {
 Error("(backbufferDC = CreateCompatibleDC(...) ) == 0");

 goto label_return;
 }

 InsertHandle(_this->backbufferDC);

 // Create the bitmap, which will be used as the backbuffer.
 _this->backbufferBitmapHB = CreateDIBSection(_this->backbufferDC, &bInfo, DIB_RGB_COLORS, (void**) &_this->backbufferArray[_this->GraphicsClientHeight(reference) - 1], 0, 0);

 if( !_this->backbufferBitmapHB || !_this->backbufferArray[_this->GraphicsClientHeight(reference) - 1] )
 {
 Error("(backbufferBitmapHB = CreateDIBSection(...) ) == 0");

 if( !DeleteDC(_this->backbufferDC) )
 {
 Error("DeleteDC(...) function failure");
 }
 else
 {
 RemoveHandle(_this->backbufferDC);
 }

 _this->backbufferDC = 0;

 goto label_return;
 }

 InsertHandle(_this->backbufferBitmapHB);

 // Keep the clean up object, so we can store it back
 // into the container when we take the bitmap out.
 _this->backbufferCleanUp = SelectObject(_this->backbufferDC, _this->backbufferBitmapHB);

 if( !_this->backbufferCleanUp || _this->backbufferCleanUp == (void*)GDI_ERROR)
 {
 Error("(backbufferCleanUp = SelectObject(...) ) == 0");

 if( !DeleteObject(_this->backbufferBitmapHB) )
 {
 Error("DeleteObject(..) function failure");
 }
 else
 {
 RemoveHandle(_this->backbufferBitmapHB);
 }

 if( !DeleteDC(_this->backbufferDC) )
 {
 Error("DeleteDC(...) function failure");
 }
 else
 {
 RemoveHandle(_this->backbufferDC);
 }

 _this->backbufferDC = 0;
 _this->backbufferBitmapHB = 0;

 goto label_return;
 }

 InsertHandle(_this->backbufferCleanUp);

 // Set up the back buffer pointer array.
 for(loop = _this->GraphicsClientHeight(reference) - 2; loop >= 0; loop--)
 {
 _this->backbufferArray[loop] = _this->backbufferArray[loop + 1] + _this->GraphicsClientWidth(reference) * 4;
 }

 _this->GraphicsClearBackBuffer(reference);

 if( !_font)
 _font = RobsTextOutInitSystem(0, reference, (unsigned int)_this->GraphicsClientWidth(reference), (unsigned int)_this->GraphicsClientHeight(reference), (unsigned int)_this->GraphicsWidth(reference), (unsigned int)_this->GraphicsHeight(reference) );

 ParticleSystemsInitGraphics(_this->GraphicsBackBufferFunction(reference)[0], _this->GraphicsClientWidth(reference), _this->GraphicsClientHeight(reference), 32, -( (_this->GraphicsClientWidth(reference) * 4 + 3) & ~3) );

 _this->GraphicsLockBackBuffer(reference);

 _font->T1xtOut(_font, 10, 10, "Press F8 for help");

 _this->GraphicsUnlockBackBuffer(reference);

 _this->GraphicsDrawBackBufferToScreen(reference, hWindow);

 result = GRAPHICS_OK;

label_return:
 return result;
}

#if ENABLE_DIRECTDRAW
static int GraphicsInitScreenAndBackBufferDIRECTDRAW(GraphicsClient* reference, HWND hWindow)
#else
static int GraphicsInitScreenAndBackBufferDIRECTDRAW(GraphicsClient* /*_this*/, HWND /*hWindow*/)
#endif
{
 int result = GRAPHICS_ERROR;

#if ENABLE_DIRECTDRAW
 DDSURFACEDESC ddsd = {0};

 long hResult = 0;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 ddsd.dwSize = sizeof(DDSURFACEDESC);

 if(_this->ddraw_obj || _this->ddraw_screen || _this->ddraw_screenclipper || _this->ddraw_backbuffer)
 {
 result = GRAPHICS_OK;

 goto label_return;
 }

 _this->hInstDDraw7 = LoadLibraryA("ddraw.dll");
 if( !_this->hInstDDraw7)
 goto label_return;

 _this->dDCreate7 = (LPDIRECTDRAWCREATE7)GetProcAddress(_this->hInstDDraw7, "DirectDrawCreate");
 if( !_this->dDCreate7)
 goto label_return;

 hResult = _this->dDCreate7(0, &_this->ddraw_obj, 0);

 if(FAILED(hResult) )
 {
 Error("The function DirectDrawCreate(...) has failed.");

 goto label_return;
 }

 hResult = _this->ddraw_obj->SetCooperativeLevel(hWindow, DDSCL_NORMAL);

 if(FAILED(hResult) )
 {
 Error("The function SetCooperativeLevel(...) has failed.");

 hResult = _this->ddraw_obj->Release();

 _this->ddraw_obj = 0;

 if(FAILED(hResult) )
 {
 Error("The DirectDraw main object failed to release correctly.");
 }

 goto label_return;
 }

 // Gain access to the screen surface.
 ddsd.dwFlags = DDSD_CAPS;

 ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

 hResult = _this->ddraw_obj->CreateSurface( &ddsd, &_this->ddraw_screen, 0);

 if(FAILED(hResult) )
 {
 Error("The function CreateSurface(...) has failed while trying to create the screen surface.");

 hResult = _this->ddraw_obj->Release();

 _this->ddraw_obj = 0;

 if(FAILED(hResult) )
 {
 Error("The DirectDraw main object failed to release correctly.");
 }

 goto label_return;
 }

 // Create the clipper object which will be used on the screen surface.
 hResult = _this->ddraw_obj->CreateClipper(0, &_this->ddraw_screenclipper, 0);

 if(FAILED(hResult) )
 {
 Error("The function CreateClipper(...) has failed while trying to create the screen clipper object.");

 hResult = _this->ddraw_screen->Release();

 _this->ddraw_screen = 0;

 if(FAILED(hResult) )
 {
 Error("The DirectDraw screen object failed to release correctly.");
 }

 hResult = _this->ddraw_obj->Release();

 _this->ddraw_obj = 0;

 if(FAILED(hResult) )
 {
 Error("The DirectDraw main object failed to release correctly.");
 }

 goto label_return;
 }

 // Associate the clipper to our client window.
 hResult = _this->ddraw_screenclipper->SetHWnd(0, hWindow);

 if(FAILED(hResult) )
 {
 Error("The function SetHWnd(...) has failed for the screen clipper object.");

 hResult = _this->ddraw_screenclipper->Release();

 _this->ddraw_screenclipper = 0;

 if(FAILED(hResult) )
 {
 Error("The DirectDraw screen clipper object failed to release correctly.");
 }

 hResult = _this->ddraw_screen->Release();

 _this->ddraw_screen = 0;

 if(FAILED(hResult) )
 {
 Error("The DirectDraw screen object failed to release correctly.");
 }

 hResult = _this->ddraw_obj->Release();

 _this->ddraw_obj = 0;

 if(FAILED(hResult) )
 {
 Error("The DirectDraw main object failed to release correctly.");
 }

 goto label_return;
 }

 // Clip the screen surface to the client window.
 hResult = _this->ddraw_screen->SetClipper(_this->ddraw_screenclipper);

 if(FAILED(hResult) )
 {
 Error("The function SetClipper(...) has failed for the screen surface.");

 hResult = _this->ddraw_screenclipper->Release();

 _this->ddraw_screenclipper = 0;

 if(FAILED(hResult) )
 {
 Error("The DirectDraw screen clipper object failed to release correctly.");
 }

 hResult = _this->ddraw_screen->Release();

 _this->ddraw_screen = 0;

 if(FAILED(hResult) )
 {
 Error("The DirectDraw screen object failed to release correctly.");
 }

 hResult = _this->ddraw_obj->Release();

 _this->ddraw_obj = 0;

 if(FAILED(hResult) )
 {
 Error("The DirectDraw main object failed to release correctly.");
 }

 goto label_return;
 }

 // Create the backbuffer surface.
 ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;

 ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;

 ddsd.dwWidth = _this->GraphicsClientWidth(reference);

 ddsd.dwHeight = _this->GraphicsClientHeight(reference);

 hResult = _this->ddraw_obj->CreateSurface( &ddsd, &_this->ddraw_backbuffer, 0);

 if(FAILED(hResult) || FAILED(_this->ddraw_backbuffer->GetSurfaceDesc( &ddsd) ) )
 {
 Error("The function CreateSurface(...) has failed while trying to create the back buffer surface.");

 hResult = _this->ddraw_screen->Release();

 _this->ddraw_screen = 0;

 if(FAILED(hResult) )
 {
 Error("The DirectDraw screen object failed to release correctly.");
 }

 hResult = _this->ddraw_screenclipper->Release();

 _this->ddraw_screenclipper = 0;

 if(FAILED(hResult) )
 {
 Error("The DirectDraw screen clipper object failed to release correctly.");
 }

 hResult = _this->ddraw_obj->Release();

 _this->ddraw_obj = 0;

 if(FAILED(hResult) )
 {
 Error("The DirectDraw main object failed to release correctly.");
 }

 goto label_return;
 }

 _this->GraphicsClearBackBuffer(reference);

 if( !_font)
 _font = RobsTextOutInitSystem(_font, reference, _this->GraphicsClientWidth(reference), _this->GraphicsClientHeight(reference), _this->GraphicsWidth(reference), _this->GraphicsHeight(reference) );

 ParticleSystemsInitGraphics(_this->GraphicsBackBufferFunction(reference)[0], _this->GraphicsClientWidth(reference), _this->GraphicsClientHeight(reference), 32, ddsd.lPitch);

 _this->GraphicsLockBackBuffer(reference);

 _font->T1xtOut(_font, 10, 10, "Press F8 for help");

 _this->GraphicsUnlockBackBuffer(reference);

 _this->GraphicsDrawBackBufferToScreen(reference, hWindow);

 result = GRAPHICS_OK;
#endif

#if ENABLE_DIRECTDRAW
label_return:
 if(result == GRAPHICS_ERROR && _this->hInstDDraw7)
 {
 FreeLibrary(_this->hInstDDraw7);
 _this->hInstDDraw7;
 }
#endif

 return result;
}

static int GraphicsInitScreenAndBackBuffer(GraphicsClient* reference, HWND hWindow)
{
 int result = GRAPHICS_ERROR;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 _this->_hWindow = hWindow;

 _this->GraphicsSaveOldMode(reference);

 if( !_this->beNice)
 {
 _this->GraphicsSetBitDepthTo32(reference);
 }

 if(_this->bitDepth != 32)
 {
 _this->Implementation = GRAPHICS_IMPLEMENTATION::GDI;
 BlahLog2("GRAPHICS_IMPLEMENTATION::GDI\n");
 }

 if(_this->bitDepth <= 0)
 {
 _this->bitDepth = _this->oldBitDepth;
 }

 if( !_this->backbufferArray)
 {
 _this->backbufferArray = (uint8_t**)InsertHeapAllocation(sizeof(uint8_t*) * _this->GraphicsClientHeight(reference) );
 }

 if( !_this->backbufferArray)
 goto label_return;

 switch(_this->GraphicsImplementation(reference) ) // switch(graphicsImplementation() )
 {

 case GRAPHICS_IMPLEMENTATION::GDI: // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::GDI
 {
 result = _this->GraphicsInitScreenAndBackBufferGDI(reference, hWindow);
 goto label_return;
 }
 break; // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::GDI

 case GRAPHICS_IMPLEMENTATION::DIRECTDRAW: // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::DIRECTDRAW
 {
 if(_this->GraphicsInitScreenAndBackBufferDIRECTDRAW(reference, hWindow) != 0)
 {
 _this->Implementation = GRAPHICS_IMPLEMENTATION::GDI;
 BlahLog2("GRAPHICS_IMPLEMENTATION::GDI\n");

 result = _this->GraphicsInitScreenAndBackBuffer(reference, hWindow);
 goto label_return;
 }
 else
 {
 result = GRAPHICS_OK;
 goto label_return;
 }
 }
 break; // switch(graphicsImplementation() ) - GRAPHICS_IMPLEMENTATION::DIRECTDRAW

 } // switch(graphicsImplementation() )

 Error("The OS code is using an invalid graphics implementation.");

 result = GRAPHICS_ERROR;

label_return:
 return result;
}

static int GraphicsCheckIsFullScreen(GraphicsClient* reference)
{
 int result = GRAPHICS_ERROR;

 int screenWidth = 0;
 int screenHeight = 0;
 int screenBitDepth = 0;

 HDC screen = 0;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 screen = GetDC(0);

 if( !screen)
 {
 Error("(screen = GetDC(0) ) == 0");
 goto label_return;
 }

 screenWidth = GetDeviceCaps(screen, HORZRES);

 screenHeight = GetDeviceCaps(screen, VERTRES);

 screenBitDepth = GetDeviceCaps(screen, BITSPIXEL);

 if(ReleaseDC(0, screen) != 1)
 Error("ReleaseDC(...) function failure");

 if(screenWidth <= 0 || screenHeight <= 0 || screenBitDepth <= 0)
 goto label_return;

 if( (screenWidth <= _this->GraphicsWidth(reference) && screenHeight <= _this->GraphicsHeight(reference) ) || ( !_this->beNice && _this->forceFullScreen) )
 {
 int modeTestCounter = 0;

 bool modeTest = false;

 DEVMODEA DMode = {0};

 DMode.dmSize = sizeof(DEVMODEA);

 DMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

 DMode.dmPelsWidth = (unsigned long)_this->GraphicsWidth(reference);
 DMode.dmPelsHeight = (unsigned long)_this->GraphicsHeight(reference);

 DMode.dmBitsPerPel = 32;

 modeTestCounter = -1;

 while(EnumDisplaySettingsA(0, (unsigned long)(++modeTestCounter), &DMode) )
 {
 if(DMode.dmPelsWidth == (unsigned int)_this->GraphicsWidth(reference) && DMode.dmPelsHeight == (unsigned int)_this->GraphicsHeight(reference) && DMode.dmBitsPerPel == 32)
 {
 modeTest = true;
 }
 }

 if(modeTest)
 {
 result = GRAPHICS_FULLSCREEN;
 goto label_return;
 }

 DMode.dmPelsWidth = (unsigned long)_this->GraphicsWidth(reference);
 DMode.dmPelsHeight = (unsigned long)_this->GraphicsHeight(reference);

 DMode.dmBitsPerPel = (unsigned long)screenBitDepth;

 modeTestCounter = -1;

 while(EnumDisplaySettingsA(0, (unsigned long)(++modeTestCounter), &DMode) )
 {
 if(DMode.dmPelsWidth == (unsigned int)_this->GraphicsWidth(reference) && DMode.dmPelsHeight == (unsigned int)_this->GraphicsHeight(reference) && DMode.dmBitsPerPel == (unsigned int)screenBitDepth)
 {
 modeTest = true;
 }
 }

 if(modeTest)
 {
 result = GRAPHICS_FULLSCREEN;
 goto label_return;
 }

 _this->forceFullScreen = false;
 }

 result = GRAPHICS_WINDOW;

label_return:
 return result;
}

#if 0

struct GraphicsBlah
{

// Here we keep track of the current graphics mode
// we are in.
//
// We will try for Direct Draw, but
// that never works anyway, so the solid
// GRAPHICS_IMPLEMENTATION::GDI foundation is always there to catch us.
//enum GRAPHICS_IMPLEMENTATION Implementation;

#if ENABLE_DIRECTDRAW
IDirectDraw* ddraw_obj;
IDirectDrawClipper* ddraw_screenclipper;
IDirectDrawSurface* ddraw_screen;
IDirectDrawSurface* ddraw_backbuffer;
#endif

// If we want to be nice then we won't try to change
// the bit depth on the user.
//bool beNice;

// If we are not nice and really mean we can
// try to force full screen mode onto the user.
//bool forceFullScreen;

//bool isModeChangeActive;

//int width
//height
//bitDepth;

//int oldWidth
//oldHeight
//oldBitDepth;

//uint8_t** backbufferArray;

//HDC backbufferDC;
//HBITMAP backbufferBitmapHB;
//HGDIOBJ backbufferCleanUp;

//HWND _hWindow;

};

#endif

int64_t GraphicsClientDestruct(GraphicsClient** reference);

// GraphicsClient* ( *GraphicsClientConstruct)(GraphicsClient* _this);

GraphicsClient* GraphicsClientConstruct(GraphicsClient* /*reference*/)
{
 GraphicsBlah* _this = (GraphicsBlah*)BlahAlloc(sizeof(GraphicsBlah), true);
 if( !_this)
 goto label_return;

 _this->Implementation = GRAPHICS_IMPLEMENTATION::DIRECTDRAW;
 BlahLog2("GRAPHICS_IMPLEMENTATION::DIRECTDRAW\n");

 _this->width = 3840;
 _this->height = 2160;

 _this->beNice = true;

 _this->forceFullScreen = false;

#if ENABLE_DIRECTDRAW
 _this->ddraw_obj = 0;

 _this->ddraw_screenclipper = 0;

 _this->ddraw_screen = 0;

 _this->ddraw_backbuffer = 0;
#endif

 _this->isModeChangeActive = false;

 _this->bitDepth = -1;

 _this->oldWidth = -1;
 _this->oldHeight = -1;
 _this->oldBitDepth = -1;

 _this->backbufferArray = 0;

 _this->backbufferDC = 0;
 _this->backbufferBitmapHB = 0;
 _this->backbufferCleanUp = 0;

 _this->_hWindow = 0;

 _this->GraphicsClientConstruct = GraphicsClientConstruct;

 _this->GraphicsClientDestruct = GraphicsClientDestruct;

 _this->GraphicsAboutDlgProcWrapper = GraphicsAboutDlgProcWrapper;
 _this->GraphicsInputDlgProcWrapper = GraphicsInputDlgProcWrapper;
 _this->GraphicsWindowProcWrapper = GraphicsWindowProcWrapper;

 _this->_GraphicsRenderPoint32 = _GraphicsRenderPoint32;
 _this->GraphicsRenderPoint32 = GraphicsRenderPoint32;

 _this->_GraphicsRenderLine32 = _GraphicsRenderLine32;
 _this->GraphicsRenderLine32 = GraphicsRenderLine32;

 _this->_GraphicsRenderCircle32 = _GraphicsRenderCircle32;
 _this->GraphicsRenderCircle32 = GraphicsRenderCircle32;

 _this->GraphicsImplementation = GraphicsImplementation;

 _this->GraphicsSafeMode = GraphicsSafeMode;

 _this->GraphicsIsModeChangeActive = GraphicsIsModeChangeActive;

 _this->GraphicsWidth = GraphicsWidth;
 _this->GraphicsHeight = GraphicsHeight;
 _this->GraphicsBitDepth = GraphicsBitDepth;

 _this->GraphicsClientWidth = GraphicsClientWidth;
 _this->GraphicsClientHeight = GraphicsClientHeight;
 _this->GraphicsClientBitDepth = GraphicsClientBitDepth;

 _this->GraphicsOldWidth = GraphicsOldWidth;
 _this->GraphicsOldHeight = GraphicsOldHeight;
 _this->GraphicsOldBitDepth = GraphicsOldBitDepth;

 _this->GraphicsBackBufferFunction = GraphicsBackBufferFunction;

 _this->GraphicsUnlockBackBuffer = GraphicsUnlockBackBuffer;

 _this->GraphicsLockBackBuffer = GraphicsLockBackBuffer;

 _this->GraphicsClearBackBuffer = GraphicsClearBackBuffer;

 _this->GraphicsDrawBackBufferToScreen = GraphicsDrawBackBufferToScreen;

 _this->GraphicsSaveOldMode = GraphicsSaveOldMode;

 _this->GraphicsRestoreOldMode = GraphicsRestoreOldMode;

 _this->GraphicsSetBitDepthTo32 = GraphicsSetBitDepthTo32;

 _this->GraphicsLoadBitmap = GraphicsLoadBitmap;

 _this->GraphicsTermScreenAndBackBufferGDI = GraphicsTermScreenAndBackBufferGDI;

 _this->GraphicsTermScreenAndBackBufferDIRECTDRAW = GraphicsTermScreenAndBackBufferDIRECTDRAW;

 _this->GraphicsTermScreenAndBackBuffer = GraphicsTermScreenAndBackBuffer;

 _this->GraphicsInitScreenAndBackBufferGDI = GraphicsInitScreenAndBackBufferGDI;

 _this->GraphicsInitScreenAndBackBufferDIRECTDRAW = GraphicsInitScreenAndBackBufferDIRECTDRAW;

 _this->GraphicsInitScreenAndBackBuffer = GraphicsInitScreenAndBackBuffer;

 _this->GraphicsCheckIsFullScreen = GraphicsCheckIsFullScreen;

label_return:
 return (GraphicsClient*)_this;
}

// int64_t ( *GraphicsClientDestruct)(GraphicsClient** _this);

int64_t GraphicsClientDestruct(GraphicsClient** reference)
{
 int result = 0;

 GraphicsBlah* _this = 0;

 if( !reference)
 goto label_return;

 _this = (GraphicsBlah*)reference[0];

 if( !_this)
 goto label_return;

#if ENABLE_DIRECTDRAW
 _this->dDCreate7 = 0;

 FreeLibrary(_this->hInstDDraw7);
 _this->hInstDDraw7 = 0;
#endif

 BlahFree(_this, sizeof(GraphicsBlah), true);

 reference[0] = 0;

label_return:
 return result;
}

// special function for de Casteljau algorithm

#define S 8

//#define f(v) ( (v >> S) << S)

#define i(v) (v >> S)

#define r(v) ( (v >> S) << 16)
#define g(v) ( (v >> S) << 8)
#define b(v) (v >> S)

#define pixelx(x, y) *(bb[i(y) ] + x)
#define pixely(x, y) *(bb[y] + i(x) )

#define r0(c0) ( (c0 >> 8) & 0xff00)
#define g0(c0) (c0 & 0xff00)
#define b0(c0) ( (c0 & 0xff) << 8)

void _GraphicsRenderPoint32(GraphicsClient* reference, int x0, int y0, int c0)
{
 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 if(x0 >= 0 && y0 >= 0 && x0 < _this->GraphicsClientWidth(reference) && y0 < _this->GraphicsClientHeight(reference) )
 {
 int* pixel = (int*) ( (_this->GraphicsBackBufferFunction(reference) )[y0] );

 *(pixel + x0) = c0;
 }

label_return:
 return;
}

void GraphicsRenderPoint32(GraphicsClient* reference, int _x0, int _y0, int c0)
{
 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 for(int y0 = _y0 - 1; y0 <= _y0 + 1; y0++)
 {
 for(int x0 = _x0 - 1; x0 <= _x0 + 1; x0++)
 {
 _this->_GraphicsRenderPoint32(reference, x0, y0, c0);
 }
 }

label_return:
 return;
}

void _GraphicsRenderLine32(GraphicsClient* reference, int x0, int y0, int x1, int y1, int xi, int yi)
{
 int count = 0;
 int dx = 0; int dxstep = 0; int dxabs = 0;
 int dy = 0; int dystep = 0; int dyabs = 0;
 int r0 = 0; int g0 = 0; int b0 = 0; int r1 = 0; int g1 = 0; int b1 = 0; int ri = 0; int gi = 0; int bi = 0;
 int** bb = 0;

 int left = 0; int right = 0;
 int top = 0; int bottom = 0;

 double t = 0;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 r0 = (xi >> 16) & 0xff;
 g0 = (xi >> 8) & 0xff;
 b0 = xi & 0xff;

 r1 = (yi >> 16) & 0xff;
 g1 = (yi >> 8) & 0xff;
 b1 = yi & 0xff;

 right = _this->GraphicsClientWidth(reference) - 1;
 bottom = _this->GraphicsClientHeight(reference) - 1;

 bb = (int**)_this->GraphicsBackBufferFunction(reference);

 // left clip
 // out - out
 if(x0 < left && x1 < left)
 {
 goto label_return;
 }
 // in - in
 else if(x0 >= left && x1 >= left)
 {
 /* nop */
 }
 // out - in
 else if(x0 < left && x1 >= left)
 {
 t = (double) (left - x0) / (double) (x1 - x0);

 r0 = r0 + (int) ( (double) (r1 - r0) * t);
 g0 = g0 + (int) ( (double) (g1 - g0) * t);
 b0 = b0 + (int) ( (double) (b1 - b0) * t);

 y0 = y0 + (int) ( (double) (y1 - y0) * t);

 x0 = left;
 }
 // in - out
 else if(x0 >= left && x1 < left)
 {
 t = (double) (left - x1) / (double) (x0 - x1);

 r1 = r1 + (int) ( (double) (r0 - r1) * t);
 g1 = g1 + (int) ( (double) (g0 - g1) * t);
 b1 = b1 + (int) ( (double) (b0 - b1) * t);

 y1 = y1 + (int) ( (double) (y0 - y1) * t);

 x1 = left;
 }

 // right clip
 // out - out
 if(x0 > right && x1 > right)
 {
 goto label_return;
 }
 // in - in
 else if(x0 <= right && x1 <= right)
 {
 /* nop */
 }
 // out - in
 else if(x0 > right && x1 <= right)
 {
 t = (double) (x0 - right) / (double) (x0 - x1);

 r0 = r0 + (int) ( (double) (r1 - r0) * t);
 g0 = g0 + (int) ( (double) (g1 - g0) * t);
 b0 = b0 + (int) ( (double) (b1 - b0) * t);

 y0 = y0 + (int) ( (double) (y1 - y0) * t);

 x0 = right;
 }
 // in - out
 else if(x0 <= right && x1 > right)
 {
 t = (double) (x1 - right) / (double) (x1 - x0);

 r1 = r1 + (int) ( (double) (r0 - r1) * t);
 g1 = g1 + (int) ( (double) (g0 - g1) * t);
 b1 = b1 + (int) ( (double) (b0 - b1) * t);

 y1 = y1 + (int) ( (double) (y0 - y1) * t);

 x1 = right;
 }

 // top clip
 // out - out
 if(y0 < top && y1 < top)
 {
 goto label_return;
 }
 // in - in
 else if(y0 >= top && y1 >= top)
 {
 /* nop */
 }
 // out - in
 else if(y0 < top && y1 >= top)
 {
 t = (double) (top - y0) / (double) (y1 - y0);

 r0 = r0 + (int) ( (double) (r1 - r0) * t);
 g0 = g0 + (int) ( (double) (g1 - g0) * t);
 b0 = b0 + (int) ( (double) (b1 - b0) * t);

 x0 = x0 + (int) ( (double) (x1 - x0) * t);

 y0 = top;
 }
 // in - out
 else if(y0 >= top && y1 < top)
 {
 t = (double) (top - y1) / (double) (y0 - y1);

 r1 = r1 + (int) ( (double) (r0 - r1) * t);
 g1 = g1 + (int) ( (double) (g0 - g1) * t);
 b1 = b1 + (int) ( (double) (b0 - b1) * t);

 x1 = x1 + (int) ( (double) (x0 - x1) * t);

 y1 = top;
 }

 // bottom clip
 // out - out
 if(y0 > bottom && y1 > bottom)
 {
 goto label_return;
 }
 // in - in
 else if(y0 <= bottom && y1 <= bottom)
 {
 }
 // out - in
 else if(y0 > bottom && y1 <= bottom)
 {
 t = (double) (y0 - bottom) / (double) (y0 - y1);

 r0 = r0 + (int) ( (double) (r1 - r0) * t);
 g0 = g0 + (int) ( (double) (g1 - g0) * t);
 b0 = b0 + (int) ( (double) (b1 - b0) * t);

 x0 = x0 + (int) ( (double) (x1 - x0) * t);

 y0 = bottom;
 }
 // in - out
 else if(y0 <= bottom && y1 > bottom)
 {
 t = (double) (y1 - bottom) / (double) (y1 - y0);

 r1 = r1 + (int) ( (double) (r0 - r1) * t);
 g1 = g1 + (int) ( (double) (g0 - g1) * t);
 b1 = b1 + (int) ( (double) (b0 - b1) * t);

 x1 = x1 + (int) ( (double) (x0 - x1) * t);

 y1 = bottom;
 }

 xi = (r0 << 16) | (g0 << 8) | b0;
 yi = (r1 << 16) | (g1 << 8) | b1;

 if(x0 < left || x0 > right || x1 < left || x1 > right || y0 < top || y0 > bottom || y1 < top || y1 > bottom || r0 < 0 || r0 > 255 || g0 < 0 || g0 > 255 || b0 < 0 || b0 > 255 || r1 < 0 || r1 > 255 || g1 < 0 || g1 > 255 || b1 < 0 || b1 > 255)
 {
 goto label_return;
 }

 x0 <<= 8;
 x1 <<= 8;

 y0 <<= 8;
 y1 <<= 8;

 r0 = (xi >> 8) & 0xff00;
 g0 = xi & 0xff00;
 b0 = (xi & 0xff) << 8;

 r1 = (yi >> 8) & 0xff00;
 g1 = yi & 0xff00;
 b1 = (yi & 0xff) << 8;

 dx = x1 - x0;

 if(dx >= 0)
 {
 dxstep = 1;
 dxabs = dx;
 }
 else
 {
 dxstep = -1;
 dxabs = -dx;
 }

 dy = y1 - y0;

 if(dy >= 0)
 {
 dystep = 1;
 dyabs = dy;
 }
 else
 {
 dystep = -1;
 dyabs = -dy;
 }

 if(dxabs >= dyabs)
 {
 count = i(dxabs);

 if(count == 0)
 {
 yi = 0;
 ri = 0;
 gi = 0;
 bi = 0;
 }
 else
 {
 yi = ( (y1 - y0) << S) / dxabs;
 ri = ( (r1 - r0) << S) / dxabs;
 gi = ( (g1 - g0) << S) / dxabs;
 bi = ( (b1 - b0) << S) / dxabs;
 }

 x0 = i(x0);
 x1 = i(x1);
 dxabs = x1 - x0;

 if(dxabs < 0)
 {
 dxabs =- dxabs;
 }

 if(count > 0)
 {
 do
 {
 pixelx(x0, y0) = r(r0) | g(g0) | b(b0);

 r0 += ri;
 g0 += gi;
 b0 += bi;

 x0 += dxstep;
 y0 += yi;

 }while( --count != 0);
 }
 }
 else
 {
 count = i(dyabs);

 if(count == 0)
 {
 xi = 0;
 ri = 0;
 gi = 0;
 bi = 0;
 }
 else
 {
 xi = ( (x1 - x0) << S) / dyabs;
 ri = ( (r1 - r0) << S) / dyabs;
 gi = ( (g1 - g0) << S) / dyabs;
 bi = ( (b1 - b0) << S) / dyabs;
 }

 y0 = i(y0);
 y1 = i(y1);
 dyabs = y1 - y0;

 if(dyabs < 0)
 {
 dyabs =- dyabs;
 }

 if(count > 0)
 {
 do
 {
 pixely(x0, y0) = r(r0) | g(g0) | b(b0);

 r0 += ri;
 g0 += gi;
 b0 += bi;

 y0 += dystep;
 x0 += xi;

 }while( --count != 0);
 }
 }

label_return:
 return;
}

void GraphicsRenderLine32(GraphicsClient* reference, int x0, int y0, int x1, int y1, int xi, int yi)
{
 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 _this->_GraphicsRenderLine32(reference, x0 - 1, y0, x1 - 1, y1, xi, yi);
 _this->_GraphicsRenderLine32(reference, x0 + 1, y0, x1 + 1, y1, xi, yi);

 _this->_GraphicsRenderLine32(reference, x0, y0 - 1, x1, y1 - 1, xi, yi);
 _this->_GraphicsRenderLine32(reference, x0, y0 + 1, x1, y1 + 1, xi, yi);

 _this->_GraphicsRenderLine32(reference, x0, y0, x1, y1, xi, yi);

label_return:
 return;
}

void _GraphicsRenderCircle32(GraphicsClient* reference, int xcen, int ycen, int r, int c0, int c1)
{
 int d = 0; int de = 0; int dse = 0; int x = 0; int y = 0;

 int r8 = 0; int g8 = 0; int b8 = 0;
 int s1rs = 0; int s2rs = 0; int s3rs = 0; int s4rs = 0; int s1re = 0; int s2re = 0; int s3re = 0; int s4re = 0; int ri = 0; int r_cur = 0;
 int s1gs = 0; int s2gs = 0; int s3gs = 0; int s4gs = 0; int s1ge = 0; int s2ge = 0; int s3ge = 0; int s4ge = 0; int gi = 0; int g_cur = 0;
 int s1bs = 0; int s2bs = 0; int s3bs = 0; int s4bs = 0; int s1be = 0; int s2be = 0; int s3be = 0; int s4be = 0; int bi = 0; int b_cur = 0;
 int num_pixels = 0; int pi = 0;

 int* dt = 0; int** bb = 0;
 int local_length = 0; int local_ri = 0; int local_gi = 0; int local_bi = 0;

 int _width = 0; int _height = 0;

 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 _width = _this->GraphicsClientWidth(reference);
 _height = _this->GraphicsClientHeight(reference);

 if(xcen + r < 0 || xcen - r >= _width || ycen + r < 0 || ycen - r >= _height)
 {
 goto label_return;
 }

 pi = 804 << (S - 8);

 bb = (int**)_this->GraphicsBackBufferFunction(reference);

 num_pixels = (pi * (r << S) ) >> S;

 d = 1 - r;
 de = 3;
 dse = -(r * 2) + 5;
 x = 0;
 y = r;

 r8 = (r0(c1) - r0(c0) ) / 4;
 g8 = (g0(c1) - g0(c0) ) / 4;
 b8 = (b0(c1) - b0(c0) ) / 4;

 if( (num_pixels / 4) == 0)
 {
 ri = 0;
 gi = 0;
 bi = 0;
 }
 else
 {
 ri = (r8 << (S - 1) ) / (num_pixels / 4);
 gi = (g8 << (S - 1) ) / (num_pixels / 4);
 bi = (b8 << (S - 1) ) / (num_pixels / 4);
 }

 s1rs = r0(c0);
 s1re = r0(c0) + (r8 * 4);
 //
 s2rs = r0(c0) + r8;
 s2re = r0(c0) + (r8 * 2) + r8;
 //
 s3rs = s2rs;
 s3re = s2re;
 //
 s4rs = s2rs + r8;
 s4re = s2rs + r8;

 s1gs = g0(c0);
 s1ge = g0(c0) + (g8 * 4);
 //
 s2gs = g0(c0) + g8;
 s2ge = g0(c0) + (g8 * 2) + g8;
 //
 s3gs = s2gs;
 s3ge = s2ge;
 //
 s4gs = s2gs + g8;
 s4ge = s2gs + g8;

 s1bs = b0(c0);
 s1be = b0(c0) + (b8 * 4);
 //
 s2bs = b0(c0) + b8;
 s2be = b0(c0) + (b8 * 2) + b8;
 //
 s3bs = s2bs;
 s3be = s2be;
 //
 s4bs = s2bs + b8;
 s4be = s2bs + b8;

 if(r < 0)
 {
 y =- r;
 }
 else if(r == 0)
 {
 if(xcen >= 0 && ycen >= 0 && xcen < _width && ycen < _height)
 *(bb[ycen] + xcen) = r( ( (s2rs / 2) + (s2re / 2) ) ) | g( ( (s2gs / 2) + (s2ge / 2) ) ) | b( ( (s2bs / 2) + (s2be / 2) ) );

 goto label_return;
 }

 do
 {
 r_cur = s4rs;
 g_cur = s4gs;
 b_cur = s4bs;

 local_length = x * 2;

 if(local_length == 0)
 {
 local_ri = 0;
 local_gi = 0;
 local_bi = 0;
 }
 else
 {
 local_ri = (s4re - s4rs) / local_length;
 local_gi = (s4ge - s4gs) / local_length;
 local_bi = (s4be - s4bs) / local_length;
 }

 if(ycen + y >= 0 && ycen + y < _height)
 {
 dt = bb[ycen + y] + xcen - x;

 c0 = xcen - x;

 while( --local_length > 0)
 {
 if(c0 >= 0 && c0 < _width)
 {
 *dt = r(r_cur) | g(g_cur) | b(b_cur);
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

 if(local_length == 0)
 {
 local_ri = 0;
 local_gi = 0;
 local_bi = 0;
 }
 else
 {
 local_ri = (s1re - s1rs) / local_length;
 local_gi = (s1ge - s1gs) / local_length;
 local_bi = (s1be - s1bs) / local_length;
 }

 if(ycen - y >= 0 && ycen - y < _height)
 {
 dt = bb[ycen - y] + xcen - x;

 c0 = xcen - x;

 while( --local_length > 0)
 {
 if(c0 >= 0 && c0 < _width)
 {
 *dt = r(r_cur) | g(g_cur) | b(b_cur);
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

 if(local_length == 0)
 {
 local_ri = 0;
 local_gi = 0;
 local_bi = 0;
 }
 else
 {
 local_ri = (s2re - s2rs) / local_length;
 local_gi = (s2ge - s2gs) / local_length;
 local_bi = (s2be - s2bs) / local_length;
 }

 if(ycen - x >= 0 && ycen - x < _height)
 {
 dt = bb[ycen - x] + xcen - y;

 c0 = xcen - y;

 while( --local_length > 0)
 {
 if(c0 >= 0 && c0 < _width)
 {
 *dt = r(r_cur) | g(g_cur) | b(b_cur);
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

 if(local_length == 0)
 {
 local_ri = 0;
 local_gi = 0;
 local_bi = 0;
 }
 else
 {
 local_ri = (s3re - s3rs) / local_length;
 local_gi = (s3ge - s3gs) / local_length;
 local_bi = (s3be - s3bs) / local_length;
 }

 if(ycen + x >= 0 && ycen + x < _height)
 {
 dt = bb[ycen + x] + xcen - y;

 c0 = xcen - y;

 while( --local_length > 0)
 {
 if(c0 >= 0 && c0 < _width)
 {
 *dt = r(r_cur) | g(g_cur) | b(b_cur);
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

 if(d < 0)
 {
 d += de;
 de += 2;
 dse += 2;
 }
 else
 {
 d += dse;
 de += 2;
 dse += 4;
 --y;
 }

 }while(++x <= y);

label_return:
 return;
}

void GraphicsRenderCircle32(GraphicsClient* reference, int xcen, int ycen, int r, int c0, int c1)
{
 GraphicsBlah* _this = (GraphicsBlah*)reference;
 if( !_this)
 goto label_return;

 _this->_GraphicsRenderCircle32(reference, xcen, ycen, 2 * r, c0, c1);

label_return:
 return;
}

#undef S

//#undef f

#undef i

#undef r
#undef g
#undef b

#undef pixelx
#undef pixely

//#undef copy

#undef r0
#undef g0
#undef b0

static const char appClassName[] = /*{'H', 0, 'e', 0, 'l', 0, 'l', 0, ' ', 0, 'o', 0, 'n', 0, ' ', 0, 'E', 0, 'a', 0, 'r', 0, 't', 0, 'h', 0, 0, 0}*/"Hell on Earth";

static const char appName[] = /*{'H', 0, 'e', 0, 'l', 0, 'l', 0, ' ', 0, 'o', 0, 'n', 0, ' ', 0, 'E', 0, 'a', 0, 'r', 0, 't', 0, 'h', 0, 0, 0}*/"Hell on Earth";

// used to disable the warning when exit(0) is called

// Boolean variable, set to true when the application is top most,
// set to false when the application is not top most.
//
// The application will perform a sleep(1) every message loop
// if the application is not top most, to give other applications
// more processor time.
//
// If our application is top most, it will hog as much processor
// power as it can while still being a stable windows application.
// It doesn't make much difference, unless the user wants extra
// time for background applications. Every applications gets a
// small fair chunk of processor time. Other applications can take
// center stage when they are top most.
static bool IsApplicationTopMost = true;

static bool IsApplicationMinimized = false;

static bool IsLeftMouseButtonDown = false;
static bool IsRightMouseButtonDown = false;

static bool IsWindowStyleChanging = false;

static bool isMenuActive = false;

static pointInteger mousePointCurrent = {-1, -1};
static pointInteger mousePointPrevious = {-1, -1};

static double angleTheta = 0;
static double angleFee = 0;
static double velocity = 0;

struct pairQI
{
 pointInteger first;
 int second;
};

//using pairQI = pair<pointInteger, int>;
//using queueI = queue<pairQI>;

//static queueI* input = 0;
static ssQueue* input = 0;

static int orInput = 0;

static double menuArray[13] = {0};

enum INPUT_EVENT
{
 UPDATE_INPUT = 0,

 CAPTURE_CONTROL_POINT = 8,
 ADD_CONTROL_POINT = 16,

 CAPTURE_T_OF_F_OF_T = 8 | 1,
 DUMP_ALL_CONTROL_POINTS = 16 | 1,

 CAPTURE_TRANSLATE = 8 | 2,
 CAPTURE_SCALE = 16 | 2,

 CAPTURE_ROTATE = 8 | 4,
 REMOVE_CONTROL_POINT = 16 | 4,

 TOGGLE_SHELLS = 32,

 DUMP_ALL_CAPTURES = 64,

 MENU_INPUT = 128,

 TOGGLE_CONTROL_POINTS = 256,

 INCREASE_ITERATION_CONSTANT = 512,

 DECREASE_ITERATION_CONSTANT = 1024,

 ADD_CURVE = 2048,

 REMOVE_CURVE = 4096,

 TRAVERSE_CURVE_LIST = 8192,

 TOGGLE_CONTROL_POINT_TEXT = 16384
};

long long __stdcall GraphicsAboutDlgProc(HWND hDlg, unsigned int msg, unsigned long long wParam, long long /*lParam*/)
{
 long long result = false;

 GraphicsClient* reference = (GraphicsClient*)_graphics;
 if( !reference)
 goto label_return;

 switch(msg) // switch(msg)
 {

 case WM_INITDIALOG: // switch(msg) - WM_INITDIALOG
 {
 isMenuActive = true;

 result = true;
 }
 goto label_return; // switch(msg) - WM_INITDIALOG

 case WM_COMMAND: // switch(msg) - WM_COMMAND
 {
 switch(LOWORD(wParam) ) // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) )
 {

 case IDOK: // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) ) - IDOK
 /* nop */
 case IDCANCEL: // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) ) - IDCANCEL
 {
 EndDialog(hDlg, 0);

 isMenuActive = false;

 result = true;
 }
 goto label_return; // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) ) - IDOK, case IDCANCEL

 } // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) )
 }
 break; // switch(msg) - WM_COMMAND

 } // switch(msg)

 if(_graphics->_hWindow && !_graphics->GraphicsIsModeChangeActive(reference) && !IsApplicationMinimized)
 {
 pointInteger mousePt = {0};

 GetCursorPos( (POINT*) &mousePt);
 ScreenToClient(_graphics->_hWindow, (POINT*) &mousePt);

 main(UPDATE_INPUT, mousePt.x, mousePt.y, 1, (double)_graphics->GraphicsClientWidth(reference) * 0.5, (double)_graphics->GraphicsClientHeight(reference) * 0.5, reference, _font);

 _graphics->GraphicsDrawBackBufferToScreen(reference, _graphics->_hWindow);

 Sleep(1);
 }

label_return:
 return result;
}

static bool checkString(char* string)
{
 bool result = false;

 char charCur = *string;

 int stringI = 1;

 if(charCur == '+' || charCur == '-')
 {
 /* nop */
 }
 else if(charCur >= '0' && charCur <= '9')
 {
 /* nop */
 }
 else
 {
 goto label_return;
 }

 for(charCur = string[1]; charCur != 0 && stringI < 256; charCur = string[ ++stringI] )
 {
 if(charCur >= '0' && charCur <= '9')
 {
 /* nop */
 }
 else
 {
 goto label_return;
 }
 }

 result = true;

label_return:
 return result;
}

static void plusDecimal(double& lhs, double rhs)
{
 if(lhs < 0)
 {
 lhs -= rhs;
 }
 else
 {
 lhs += rhs;
 }
}

long long __stdcall GraphicsInputDlgProc(HWND hDlg, unsigned int msg, unsigned long long wParam, long long /*lParam*/)
{
 long long result = false;

 char item[256] = {0};

 GraphicsClient* reference = (GraphicsClient*)_graphics;
 if( !reference)
 goto label_return;

 switch(msg) // switch(msg)
 {

 case WM_INITDIALOG: // switch(msg) - WM_INITDIALOG
 {
 isMenuActive = true;

 SetDlgItemTextA(hDlg, EDITX3_INT, "0");
 SetDlgItemTextA(hDlg, EDITX3_DEC, "0");
 SetDlgItemTextA(hDlg, EDITX2_INT, "0");
 SetDlgItemTextA(hDlg, EDITX2_DEC, "0");
 SetDlgItemTextA(hDlg, EDITX1_INT, "0");
 SetDlgItemTextA(hDlg, EDITX1_DEC, "0");
 SetDlgItemTextA(hDlg, EDITX0_INT, "0");
 SetDlgItemTextA(hDlg, EDITX0_DEC, "0");

 SetDlgItemTextA(hDlg, EDITY3_INT, "0");
 SetDlgItemTextA(hDlg, EDITY3_DEC, "0");
 SetDlgItemTextA(hDlg, EDITY2_INT, "0");
 SetDlgItemTextA(hDlg, EDITY2_DEC, "0");
 SetDlgItemTextA(hDlg, EDITY1_INT, "0");
 SetDlgItemTextA(hDlg, EDITY1_DEC, "0");
 SetDlgItemTextA(hDlg, EDITY0_INT, "0");
 SetDlgItemTextA(hDlg, EDITY0_DEC, "0");

 SetDlgItemTextA(hDlg, EDITZ3_INT, "0");
 SetDlgItemTextA(hDlg, EDITZ3_DEC, "0");
 SetDlgItemTextA(hDlg, EDITZ2_INT, "0");
 SetDlgItemTextA(hDlg, EDITZ2_DEC, "0");
 SetDlgItemTextA(hDlg, EDITZ1_INT, "0");
 SetDlgItemTextA(hDlg, EDITZ1_DEC, "0");
 SetDlgItemTextA(hDlg, EDITZ0_INT, "0");
 SetDlgItemTextA(hDlg, EDITZ0_DEC, "0");

 SetDlgItemTextA(hDlg, EDIT_KNOT, "0");

 SetDlgItemTextA(hDlg, EDITR_INT, "0");
 SetDlgItemTextA(hDlg, EDITR_DEC, "0");

 SetDlgItemTextA(hDlg, EDITS_INT, "1");
 SetDlgItemTextA(hDlg, EDITS_DEC, "0");

 result = true;
 }
 goto label_return; // switch(msg) - WM_INITDIALOG

 case WM_COMMAND: // switch(msg) - WM_COMMAND
 {
 switch(LOWORD(wParam) ) // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) )
 {

 case IDOK: // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) ) - IDOK
 {
 menuArray[0] = 3;

 //
 memset(item, 0, sizeof(char) * 256);
 GetDlgItemTextA(hDlg, EDITX3_INT, item, 255);

 if( !checkString(item) )
 goto _IDCANCEL;

 menuArray[4] = atof(item);

 memset(item, 0, sizeof(char) * 256);
 item[0] = '.';
 GetDlgItemTextA(hDlg, EDITX3_DEC, item + 1, 254);
 plusDecimal(menuArray[4], atof(item) );

 //
 memset(item, 0, sizeof(char) * 256);
 GetDlgItemTextA(hDlg, EDITX2_INT, item, 255);

 if( !checkString(item) )
 goto _IDCANCEL;

 menuArray[3] = atof(item);

 memset(item, 0, sizeof(char) * 256);
 item[0] = '.';
 GetDlgItemTextA(hDlg, EDITX2_DEC, item + 1, 254);
 plusDecimal(menuArray[3], atof(item) );

 //
 memset(item, 0, sizeof(char) * 256);
 GetDlgItemTextA(hDlg, EDITX1_INT, item, 255);

 if( !checkString(item) )
 goto _IDCANCEL;

 menuArray[2] = atof(item);

 memset(item, 0, sizeof(char) * 256);
 item[0] = '.';
 GetDlgItemTextA(hDlg, EDITX1_DEC, item + 1, 254);
 plusDecimal(menuArray[2], atof(item) );

 //
 memset(item, 0, sizeof(char) * 256);
 GetDlgItemTextA(hDlg, EDITX0_INT, item, 255);

 if( !checkString(item) )
 goto _IDCANCEL;

 menuArray[1] = atof(item);

 memset(item, 0, sizeof(char) * 256);
 item[0] = '.';
 GetDlgItemTextA(hDlg, EDITX0_DEC, item + 1, 254);
 plusDecimal(menuArray[1], atof(item) );

 //
 memset(item, 0, sizeof(char) * 256);
 GetDlgItemTextA(hDlg, EDITY3_INT, item, 255);

 if( !checkString(item) )
 goto _IDCANCEL;

 menuArray[8] = atof(item);

 memset(item, 0, sizeof(char) * 256);
 item[0] = '.';
 GetDlgItemTextA(hDlg, EDITY3_DEC, item + 1, 254);
 plusDecimal(menuArray[8], atof(item) );

 //
 memset(item, 0, sizeof(char) * 256);
 GetDlgItemTextA(hDlg, EDITY2_INT, item, 255);

 if( !checkString(item) )
 goto _IDCANCEL;

 menuArray[7] = atof(item);

 memset(item, 0, sizeof(char) * 256);
 item[0] = '.';
 GetDlgItemTextA(hDlg, EDITY2_DEC, item + 1, 254);
 plusDecimal(menuArray[7], atof(item) );

 //
 memset(item, 0, sizeof(char) * 256);
 GetDlgItemTextA(hDlg, EDITY1_INT, item, 255);

 if( !checkString(item) )
 goto _IDCANCEL;

 menuArray[6] = atof(item);

 memset(item, 0, sizeof(char) * 256);
 item[0] = '.';
 GetDlgItemTextA(hDlg, EDITY1_DEC, item + 1, 254);
 plusDecimal(menuArray[6], atof(item) );

 //
 memset(item, 0, sizeof(char) * 256);
 GetDlgItemTextA(hDlg, EDITY0_INT, item, 255);

 if( !checkString(item) )
 goto _IDCANCEL;

 menuArray[5] = atof(item);

 memset(item, 0, sizeof(char) * 256);
 item[0] = '.';
 GetDlgItemTextA(hDlg, EDITY0_DEC, item + 1, 254);
 plusDecimal(menuArray[5], atof(item) );

 //
 memset(item, 0, sizeof(char) * 256);
 GetDlgItemTextA(hDlg, EDITZ3_INT, item, 255);

 if( !checkString(item) )
 goto _IDCANCEL;

 menuArray[12] = atof(item);

 memset(item, 0, sizeof(char) * 256);
 item[0] = '.';
 GetDlgItemTextA(hDlg, EDITZ3_DEC, item + 1, 254);
 plusDecimal(menuArray[12], atof(item) );

 //
 memset(item, 0, sizeof(char) * 256);
 GetDlgItemTextA(hDlg, EDITZ2_INT, item, 255);

 if( !checkString(item) )
 goto _IDCANCEL;

 menuArray[11] = atof(item);

 memset(item, 0, sizeof(char) * 256);
 item[0] = '.';
 GetDlgItemTextA(hDlg, EDITZ2_DEC, item + 1, 254);
 plusDecimal(menuArray[11], atof(item) );

 //
 memset(item, 0, sizeof(char) * 256);
 GetDlgItemTextA(hDlg, EDITZ1_INT, item, 255);

 if( !checkString(item) )
 goto _IDCANCEL;

 menuArray[10] = atof(item);

 memset(item, 0, sizeof(char) * 256);
 item[0] = '.';
 GetDlgItemTextA(hDlg, EDITZ1_DEC, item + 1, 254);
 plusDecimal(menuArray[10], atof(item) );

 //
 memset(item, 0, sizeof(char) * 256);
 GetDlgItemTextA(hDlg, EDITZ0_INT, item, 255);

 if( !checkString(item) )
 goto _IDCANCEL;

 menuArray[9] = atof(item);

 memset(item, 0, sizeof(char) * 256);
 item[0] = '.';
 GetDlgItemTextA(hDlg, EDITZ0_DEC, item + 1, 254);
 plusDecimal(menuArray[9], atof(item) );

 //
 memset(item, 0, sizeof(char) * 256);
 GetDlgItemTextA(hDlg, EDITR_INT, item, 255);

 if( !checkString(item) )
 goto _IDCANCEL;

 menuArray[9] = atof(item);

 memset(item, 0, sizeof(char) * 256);
 item[0] = '.';
 GetDlgItemTextA(hDlg, EDITR_DEC, item + 1, 254);
 plusDecimal(menuArray[9], atof(item) );

 //
 memset(item, 0, sizeof(char) * 256);
 GetDlgItemTextA(hDlg, EDITS_INT, item, 255);

 if( !checkString(item) )
 goto _IDCANCEL;

 menuArray[10] = atof(item);

 memset(item, 0, sizeof(char) * 256);
 item[0] = '.';
 GetDlgItemTextA(hDlg, EDITS_DEC, item + 1, 254);
 plusDecimal(menuArray[10], atof(item) );

 //
 EndDialog(hDlg, 0);

 isMenuActive = false;

 result = true;
 }
 goto label_return; // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) ) - IDOK

 case IDCANCEL: // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) ) - IDCANCEL
 {
_IDCANCEL:
 EndDialog(hDlg, -1);

 isMenuActive = false;

 result = true;
 }
 goto label_return; // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) ) - IDCANCEL

 case IDEX1: // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) ) - IDEX1
 {
 SetDlgItemTextA(hDlg, EDITX3_INT, "0");
 SetDlgItemTextA(hDlg, EDITX3_DEC, "0");
 SetDlgItemTextA(hDlg, EDITX2_INT, "0");
 SetDlgItemTextA(hDlg, EDITX2_DEC, "0");
 SetDlgItemTextA(hDlg, EDITX1_INT, "3");
 SetDlgItemTextA(hDlg, EDITX1_DEC, "0");
 SetDlgItemTextA(hDlg, EDITX0_INT, "0");
 SetDlgItemTextA(hDlg, EDITX0_DEC, "0");

 SetDlgItemTextA(hDlg, EDITY3_INT, "3");
 SetDlgItemTextA(hDlg, EDITY3_DEC, "0");
 SetDlgItemTextA(hDlg, EDITY2_INT, "0");
 SetDlgItemTextA(hDlg, EDITY2_DEC, "0");
 SetDlgItemTextA(hDlg, EDITY1_INT, "-3");
 SetDlgItemTextA(hDlg, EDITY1_DEC, "0");
 SetDlgItemTextA(hDlg, EDITY0_INT, "0");
 SetDlgItemTextA(hDlg, EDITY0_DEC, "0");

 SetDlgItemTextA(hDlg, EDITR_INT, "-1");
 SetDlgItemTextA(hDlg, EDITR_DEC, "0");

 SetDlgItemTextA(hDlg, EDITS_INT, "1");
 SetDlgItemTextA(hDlg, EDITS_DEC, "0");
 }
 goto label_return; // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) ) - IDEX1

 case IDEX2: // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) ) - IDEX2
 {
 SetDlgItemTextA(hDlg, EDITX3_INT, "0");
 SetDlgItemTextA(hDlg, EDITX3_DEC, "0");
 SetDlgItemTextA(hDlg, EDITX2_INT, "3");
 SetDlgItemTextA(hDlg, EDITX2_DEC, "0");
 SetDlgItemTextA(hDlg, EDITX1_INT, "-6");
 SetDlgItemTextA(hDlg, EDITX1_DEC, "0");
 SetDlgItemTextA(hDlg, EDITX0_INT, "9");
 SetDlgItemTextA(hDlg, EDITX0_DEC, "0");

 SetDlgItemTextA(hDlg, EDITY3_INT, "3");
 SetDlgItemTextA(hDlg, EDITY3_DEC, "0");
 SetDlgItemTextA(hDlg, EDITY2_INT, "-6");
 SetDlgItemTextA(hDlg, EDITY2_DEC, "0");
 SetDlgItemTextA(hDlg, EDITY1_INT, "9");
 SetDlgItemTextA(hDlg, EDITY1_DEC, "0");
 SetDlgItemTextA(hDlg, EDITY0_INT, "0");
 SetDlgItemTextA(hDlg, EDITY0_DEC, "0");

 SetDlgItemTextA(hDlg, EDITR_INT, "0");
 SetDlgItemTextA(hDlg, EDITR_DEC, "0");

 SetDlgItemTextA(hDlg, EDITS_INT, "1");
 SetDlgItemTextA(hDlg, EDITS_DEC, "0");
 }
 goto label_return; // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) ) - IDEX2

 case IDEX3: // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) ) - IDEX3
 {
 SetDlgItemTextA(hDlg, EDITX3_INT, "0");
 SetDlgItemTextA(hDlg, EDITX3_DEC, "0");
 SetDlgItemTextA(hDlg, EDITX2_INT, "3");
 SetDlgItemTextA(hDlg, EDITX2_DEC, "0");
 SetDlgItemTextA(hDlg, EDITX1_INT, "-12");
 SetDlgItemTextA(hDlg, EDITX1_DEC, "0");
 SetDlgItemTextA(hDlg, EDITX0_INT, "15");
 SetDlgItemTextA(hDlg, EDITX0_DEC, "0");

 SetDlgItemTextA(hDlg, EDITY3_INT, "3");
 SetDlgItemTextA(hDlg, EDITY3_DEC, "0");
 SetDlgItemTextA(hDlg, EDITY2_INT, "-12");
 SetDlgItemTextA(hDlg, EDITY2_DEC, "0");
 SetDlgItemTextA(hDlg, EDITY1_INT, "15");
 SetDlgItemTextA(hDlg, EDITY1_DEC, "0");
 SetDlgItemTextA(hDlg, EDITY0_INT, "0");
 SetDlgItemTextA(hDlg, EDITY0_DEC, "0");

 SetDlgItemTextA(hDlg, EDITR_INT, "0");
 SetDlgItemTextA(hDlg, EDITR_DEC, "0");

 SetDlgItemTextA(hDlg, EDITS_INT, "2");
 SetDlgItemTextA(hDlg, EDITS_DEC, "0");
 }
 goto label_return; // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) ) - IDEX3

 case IDEX4: // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) ) - IDEX4
 {
 SetDlgItemTextA(hDlg, EDITX3_INT, "0");
 SetDlgItemTextA(hDlg, EDITX3_DEC, "0");
 SetDlgItemTextA(hDlg, EDITX2_INT, "3");
 SetDlgItemTextA(hDlg, EDITX2_DEC, "0");
 SetDlgItemTextA(hDlg, EDITX1_INT, "-6");
 SetDlgItemTextA(hDlg, EDITX1_DEC, "0");
 SetDlgItemTextA(hDlg, EDITX0_INT, "3");
 SetDlgItemTextA(hDlg, EDITX0_DEC, "0");

 SetDlgItemTextA(hDlg, EDITY3_INT, "3");
 SetDlgItemTextA(hDlg, EDITY3_DEC, "0");
 SetDlgItemTextA(hDlg, EDITY2_INT, "-6");
 SetDlgItemTextA(hDlg, EDITY2_DEC, "0");
 SetDlgItemTextA(hDlg, EDITY1_INT, "3");
 SetDlgItemTextA(hDlg, EDITY1_DEC, "0");
 SetDlgItemTextA(hDlg, EDITY0_INT, "0");
 SetDlgItemTextA(hDlg, EDITY0_DEC, "0");

 SetDlgItemTextA(hDlg, EDITR_INT, "0");
 SetDlgItemTextA(hDlg, EDITR_DEC, "0");

 SetDlgItemTextA(hDlg, EDITS_INT, "2");
 SetDlgItemTextA(hDlg, EDITS_DEC, "0");
 }
 goto label_return; // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) ) - IDEX4

 case IDEX5: // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) ) - IDEX5
 {
 SetDlgItemTextA(hDlg, EDITX3_INT, "0");
 SetDlgItemTextA(hDlg, EDITX3_DEC, "0");
 SetDlgItemTextA(hDlg, EDITX2_INT, "0");
 SetDlgItemTextA(hDlg, EDITX2_DEC, "75");
 SetDlgItemTextA(hDlg, EDITX1_INT, "-1");
 SetDlgItemTextA(hDlg, EDITX1_DEC, "5");
 SetDlgItemTextA(hDlg, EDITX0_INT, "-2");
 SetDlgItemTextA(hDlg, EDITX0_DEC, "25");

 SetDlgItemTextA(hDlg, EDITY3_INT, "0");
 SetDlgItemTextA(hDlg, EDITY3_DEC, "75");
 SetDlgItemTextA(hDlg, EDITY2_INT, "-1");
 SetDlgItemTextA(hDlg, EDITY2_DEC, "5");
 SetDlgItemTextA(hDlg, EDITY1_INT, "-2");
 SetDlgItemTextA(hDlg, EDITY1_DEC, "25");
 SetDlgItemTextA(hDlg, EDITY0_INT, "0");
 SetDlgItemTextA(hDlg, EDITY0_DEC, "0");

 SetDlgItemTextA(hDlg, EDITR_INT, "-1");
 SetDlgItemTextA(hDlg, EDITR_DEC, "0");

 SetDlgItemTextA(hDlg, EDITS_INT, "3");
 SetDlgItemTextA(hDlg, EDITS_DEC, "0");
 }
 goto label_return; // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) ) - IDEX5

 } // switch(msg) - WM_COMMAND; switch(LOWORD(wParam) )
 }
 break; // switch(msg) - WM_COMMAND

 } // switch(msg)

 if(_graphics->_hWindow && !_graphics->GraphicsIsModeChangeActive(reference) && !IsApplicationMinimized)
 {
 pointInteger mousePt = {0};

 GetCursorPos( (POINT*) &mousePt);
 ScreenToClient(_graphics->_hWindow, (POINT*) &mousePt);

 main(UPDATE_INPUT, mousePt.x, mousePt.y, 1, (double)_graphics->GraphicsClientWidth(reference) * 0.5, (double)_graphics->GraphicsClientHeight(reference) * 0.5, reference, _font);

 _graphics->GraphicsDrawBackBufferToScreen(reference, _graphics->_hWindow);

 Sleep(1);
 }

label_return:
 return result;
}

static int updateTime();

static double timeInSeconds();

static const int WM_SETWIDTHHEIGHT = 0xff000000;
static const int WM_CHANGEWINDOWSTYLE = 0xff000001;

static HWND hWindow = 0;

static bool IsApplicationEntry = false;

extern void* operator new(size_t size)
{
 void* memory = 0;

 if( !IsApplicationEntry)
 {
 memory = Allocate(size);

BlahLog2("3 %i %llu\n", (int)size, (uint64_t)memory);

 goto label_return;
 }

 memory = InsertHeapAllocation(size);

label_return:
 return memory;
}

extern void* operator new[](size_t size)
{
 void* memory = 0;

 if( !IsApplicationEntry)
 {
 memory = Allocate(size);
 goto label_return;
 }

 memory = InsertHeapAllocation(size);

label_return:
 return memory;
}

extern void operator delete(void* ptr)
{
 if( !IsApplicationEntry)
 {
 DeAllocate(ptr);
 goto label_return;
 }

 if(ptr)
 RemoveHeapAllocation(ptr);

label_return:
 return;
}

extern void operator delete[](void* ptr)
{
 if( !IsApplicationEntry)
 {
 DeAllocate(ptr);
 goto label_return;
 }

 if(ptr)
 {
 RemoveHeapAllocation(ptr);
 }

label_return:
 return;
}

long long __stdcall GraphicsWindowProc(HWND hwnd, unsigned int msg, unsigned long long wParam, long long lParam)
{
 long long result = 0;

 pointInteger mousePt = {0, 0};

 static pointInteger prevPt = {0, 0};

 static HINSTANCE hInstance = 0;

 static bool didIgetThePointer = false;

 GraphicsClient* reference = (GraphicsClient*)_graphics;
 if( !reference)
 goto label_return;

 if( !didIgetThePointer)
 {
 unsigned long long slkdjgasdlkjfg = (unsigned long long)GetWindowLongPtrA(hwnd, 0);

 if(slkdjgasdlkjfg == 0x1000000010000000ULL)
 {
 //BlahLog("pointer %llu %u\n", slkdjgasdlkjfg, msg);
 didIgetThePointer = true;
 }
 }

 GetCursorPos( (POINT*) &mousePt);
 ScreenToClient(hwnd, (POINT*) &mousePt);

 switch(msg) // switch(msg)
 {

 case WM_CREATE: // switch(msg) - WM_CREATE
 {
 //long long slkdjgasdlkjfg = GetWindowLongPtrA(hwnd, 0);
 //BlahLog2("abc %lli\n", slkdjgasdlkjfg);

 hInstance = ( (CREATESTRUCTA*)lParam) ->hInstance;
 }
 goto label_return; // switch(msg) - WM_CREATE

 case WM_SETWIDTHHEIGHT: // switch(msg) - WM_SETWIDTHHEIGHT
 {
 HDC screen = GetDC(0);

 if( !screen)
 {
 Error("WindowProc(...) GetDC(...) error");
 }
 else
 {
 _graphics->width = GetDeviceCaps(screen, HORZRES) / 2;
 _graphics->height = GetDeviceCaps(screen, VERTRES) / 2;

 if(ReleaseDC(0, screen) != 1)
 {
 Error("WindowProc(...) ReleaseDC(...) error");
 }
 }
 }
 goto label_return; // switch(msg) - WM_SETWIDTHHEIGHT

 case WM_CHANGEWINDOWSTYLE: // switch(msg) - WM_CHANGEWINDOWSTYLE
 {
 if( !IsApplicationMinimized)
 {
 IsWindowStyleChanging = true;

 if( !DestroyWindow(hwnd) )
 {
 Error("The function DestroyWindow(...) has failed in the function WindowProc(...).");
 }

 RemoveHandle(hwnd);

 if(WindowStyle::getStyle() == /*Graphics::*/GRAPHICS_WINDOW)
 {
 pointInteger origin = WindowStyle::getOrigin();

 pointInteger size = WindowStyle::getSize(reference, true);

 rectInteger menu = WindowStyle::getMenuRect();

 assert(size.x > 0 && size.y > 0 && "size.x > 0 && size.y > 0");

 hWindow = CreateWindowExA(0, appClassName, appName, WS_OVERLAPPEDWINDOW, origin.x - menu.left, origin.y - menu.top, size.x + menu.left + menu.right, size.y + menu.top + menu.bottom, 0, 0, hInstance, 0);

 _graphics->width = size.x;
 _graphics->height = size.y;
 }
 else
 {
 hWindow = CreateWindowExA(0, appClassName, appName, WS_POPUP, 0, 0, _graphics->oldWidth, _graphics->oldHeight, 0, 0, hInstance, 0);

 _graphics->width = _graphics->oldWidth;
 _graphics->height = _graphics->oldHeight;
 }

 ShowWindow(hWindow, SW_SHOW);

 hwnd = hWindow;

 _graphics->_hWindow = hWindow;

 InsertHandle(hwnd);

 unsigned short widthHeight[2] = {0};

 widthHeight[0] = (unsigned short)_graphics->oldWidth;
 widthHeight[1] = (unsigned short)_graphics->oldHeight;

 IsApplicationMinimized = false;

 GraphicsWindowProc(hwnd, WM_DISPLAYCHANGE, (unsigned long long)_graphics->oldBitDepth, *(unsigned long*)widthHeight);

 IsWindowStyleChanging = false;
 }
 }
 goto label_return; // switch(msg) - WM_CHANGEWINDOWSTYLE

 case WM_MOUSEMOVE: // switch(msg) - WM_MOUSEMOVE
 {
 pairQI client = {mousePt, UPDATE_INPUT};
 SsQueuePushBack(input, &client);

 prevPt = mousePt;
 }
 goto label_return; // switch(msg) - WM_MOUSEMOVE

 case WM_LBUTTONDOWN: // switch(msg) - WM_LBUTTONDOWN
 {
 IsLeftMouseButtonDown = true;

 pairQI client = {mousePt, 8 | orInput};
 SsQueuePushBack(input, &client);

 SetCapture(hwnd);
 }
 goto label_return; // switch(msg) - WM_LBUTTONDOWN

 case WM_LBUTTONUP: // switch(msg) - WM_LBUTTONUP
 {
 IsLeftMouseButtonDown = false;

 pairQI client = {mousePt, DUMP_ALL_CAPTURES};
 SsQueuePushBack(input, &client);

 ReleaseCapture();
 }
 goto label_return; // switch(msg) - WM_LBUTTONUP

 case WM_RBUTTONDOWN: // switch(msg) - WM_RBUTTONDOWN
 {
 IsRightMouseButtonDown = true;

 pairQI client = {mousePt, 16 | orInput};
 SsQueuePushBack(input, &client);

 SetCapture(hwnd);
 }
 goto label_return; // switch(msg) - WM_RBUTTONDOWN

 case WM_RBUTTONUP: // switch(msg) - WM_RBUTTONUP
 {
 IsRightMouseButtonDown = false;

 pairQI client = {mousePt, DUMP_ALL_CAPTURES};
 SsQueuePushBack(input, &client);

 ReleaseCapture();
 }
 goto label_return; // switch(msg) - WM_RBUTTONUP

 case WM_SETFOCUS: // switch(msg) - WM_SETFOCUS
 {
 IsApplicationTopMost = true;
 }
 goto label_return; // switch(msg) - WM_SETFOCUS

 case WM_KILLFOCUS: // switch(msg) - WM_KILLFOCUS
 {
 IsApplicationTopMost = false;

 IsLeftMouseButtonDown = false;
 IsRightMouseButtonDown = false;

 ReleaseCapture();
 }
 // ? are we supposed to pass through here ? verify todo
 goto label_return; // switch(msg) - WM_KILLFOCUS

 case WM_CAPTURECHANGED: // switch(msg) - WM_CAPTURECHANGED
 {
 /* nop */
 }
 goto label_return; // switch(msg) - WM_CAPTURECHANGED

 case WM_SYSCOMMAND: // switch(msg) - WM_SYSCOMMAND
 {
 if( (wParam & 0xfff0) != SC_MAXIMIZE)
 {
 // We need help from DefWindowProc(...).
 break;
 }

 WindowStyle::setStyle();

 GraphicsWindowProc(hwnd, (unsigned int)WM_CHANGEWINDOWSTYLE, 0, 0);
 }
 goto label_return; // switch(msg) - WM_SYSCOMMAND

 case WM_NCLBUTTONDBLCLK: // switch(msg) - WM_NCLBUTTONDBLCLK
 {
 if(wParam != HTCAPTION)
 {
 // We need help from DefWindowProc(...).
 break;
 }

 WindowStyle::setStyle();

 GraphicsWindowProc(hwnd, (unsigned int)WM_CHANGEWINDOWSTYLE, 0, 0);
 }
 goto label_return; // switch(msg) - WM_NCLBUTTONDBLCLK

 case WM_SYSKEYDOWN: // switch(msg) - WM_SYSKEYDOWN
 {
 uint32_t bit = 1 << 29;

 if(wParam == VK_RETURN && (lParam & bit) )
 {
 WindowStyle::setStyle();

 GraphicsWindowProc(hwnd, (unsigned int)WM_CHANGEWINDOWSTYLE, 0, 0);
 }
 else if(wParam == VK_F10)
 {
//DialogBoxParamA(hInstance, lpTemplate, hWndParent, lpDialogFunc, 0L)
//__declspec(dllimport) long long __stdcall DialogBoxParamA(HINSTANCE hInstance, const char* lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, long long dwInitParam);
//typedef long long(__stdcall * DLGPROC)(HWND, unsigned int, unsigned long long, long long);
 DialogBoxParamA(hInstance, "ExtraBox", hwnd, GraphicsAboutDlgProc, 0);

 WinExec("deBoorExtraBox.exe", 0);

 goto label_return;
 }
 }
 break; // switch(msg) - WM_SYSKEYDOWN

 case WM_KEYDOWN: // switch(msg) - WM_KEYDOWN
 {
 switch(wParam) // switch(msg) - WM_KEYDOWN; switch(wParam)
 {

 case VK_ESCAPE: // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_ESCAPE
 {
 Warning("escape key hit - quitting application");

 PostMessageA(hwnd, WM_DESTROY, 0, 0);
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_ESCAPE

 case VK_F1: // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_F1
 {
 orInput = 0;
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_F1

 case VK_F2: // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_F2
 {
 orInput = 1;
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_F2

 case VK_F3: // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_F3
 {
 orInput = 2;
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_F3

 case VK_F4: // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_F4
 {
 orInput = 4;
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_F4

 case VK_F5: // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_F5
 {
 IsLeftMouseButtonDown = false;
 IsRightMouseButtonDown = false;

 pairQI client = {mousePt, TOGGLE_SHELLS};
 SsQueuePushBack(input, &client);

 ReleaseCapture();
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_F5

 case VK_F6: // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_F6
 {
 IsLeftMouseButtonDown = false;
 IsRightMouseButtonDown = false;

 pairQI client = {mousePt, DUMP_ALL_CAPTURES};
 SsQueuePushBack(input, &client);

 ReleaseCapture();
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_F6

 case VK_F7: // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_F7
 {
 if(DialogBoxParamA(hInstance, "InputBox", hwnd, GraphicsInputDlgProc, 0) == 0)
 {
 IsLeftMouseButtonDown = false;
 IsRightMouseButtonDown = false;

 union
 {
 double* p;
 double f;
 pointInteger pt;

 }menu;

 union
 {
 double* p;
 double f;

 }menu2;

 assert(sizeof(menu) == sizeof(menu2) );

 memset( &menu, 0, sizeof(menu) );
 memset( &menu2, 0, sizeof(menu2) );

 menu.p = menuArray;

 menuArray[11] = mousePt.x;
 menuArray[12] = mousePt.y;

 pairQI client = {menu.pt, MENU_INPUT};
 SsQueuePushBack(input, &client);

 //

 client.first = mousePt;
 client.second = UPDATE_INPUT;
 SsQueuePushBack(input, &client);

 client.first = mousePt;
 client.second = CAPTURE_TRANSLATE;
 SsQueuePushBack(input, &client);

 pointInteger transPt = {mousePt.x + _graphics->GraphicsClientWidth(reference) / 2, mousePt.y + _graphics->GraphicsClientHeight(reference) / 2};

 client.first = transPt;
 client.second = UPDATE_INPUT;
 SsQueuePushBack(input, &client);

 client.first = transPt;
 client.second = DUMP_ALL_CAPTURES;
 SsQueuePushBack(input, &client);

 //

 client.first = mousePt;
 client.second = UPDATE_INPUT;
 SsQueuePushBack(input, &client);

 client.first = mousePt;
 client.second = CAPTURE_SCALE;
 SsQueuePushBack(input, &client);

 pointInteger scalePt = {mousePt.x + _graphics->GraphicsClientWidth(reference) / 2, mousePt.y + _graphics->GraphicsClientWidth(reference) / 2};

 client.first = scalePt;
 client.second = UPDATE_INPUT;
 SsQueuePushBack(input, &client);

 int loop = 0;

 while(++loop < 8)
 {
 scalePt.x += _graphics->GraphicsClientWidth(reference) / 2;
 scalePt.y += _graphics->GraphicsClientWidth(reference) / 2;

 client.first = scalePt;
 client.second = UPDATE_INPUT;
 SsQueuePushBack(input, &client);
 }

 client.first = scalePt;
 client.second = DUMP_ALL_CAPTURES;
 SsQueuePushBack(input, &client);

 //

 client.first = mousePt;
 client.second = UPDATE_INPUT;
 SsQueuePushBack(input, &client);

 ReleaseCapture();
 }
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_F7

 case VK_F8: // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_F8
 {
 DialogBoxParamA(hInstance, "HelpBox", hwnd, GraphicsAboutDlgProc, 0);

 WinExec("deBoorHelpBox.exe", 0);
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_F8

 case VK_F9: // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_F9
 {
 DialogBoxParamA(hInstance, "AboutBox", hwnd, GraphicsAboutDlgProc, 0);

 WinExec("deBoorAboutBox.exe", 0);
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_F9

 case 49: // switch(msg) - WM_KEYDOWN; switch(wParam) - 49
 /* nop */
 case VK_NUMPAD1: // switch(msg) - WM_KEYDOWN; switch(wParam) - 49, VK_NUMPAD1
 {
 IsLeftMouseButtonDown = false;
 IsRightMouseButtonDown = false;

 pairQI client = {mousePt, TOGGLE_CONTROL_POINTS};
 SsQueuePushBack(input, &client);

 ReleaseCapture();
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - 49, VK_NUMPAD1

 case 50: // switch(msg) - WM_KEYDOWN; switch(wParam) - 50
 /* nop */
 case VK_NUMPAD2: // switch(msg) - WM_KEYDOWN; switch(wParam) - 50, VK_NUMPAD2
 {
 IsLeftMouseButtonDown = false;
 IsRightMouseButtonDown = false;

 pairQI client = {mousePt, ADD_CURVE};
 SsQueuePushBack(input, &client);

 ReleaseCapture();
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - 50, VK_NUMPAD2

 case 51: // switch(msg) - WM_KEYDOWN; switch(wParam) - 51
 /* nop */
 case VK_NUMPAD3: // switch(msg) - WM_KEYDOWN; switch(wParam) - 51, VK_NUMPAD3
 {
 pairQI client = {mousePt, REMOVE_CURVE};
 SsQueuePushBack(input, &client);

 ReleaseCapture();
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - 51, VK_NUMPAD3

 case 52: // switch(msg) - WM_KEYDOWN; switch(wParam) - 52
 /* nop */
 case VK_NUMPAD4: // switch(msg) - WM_KEYDOWN; switch(wParam) - 52, VK_NUMPAD4
 {
 IsLeftMouseButtonDown = false;
 IsRightMouseButtonDown = false;

 pairQI client = {mousePt, TRAVERSE_CURVE_LIST};
 SsQueuePushBack(input, &client);

 ReleaseCapture();
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - 52, VK_NUMPAD4

 case 53: // switch(msg) - WM_KEYDOWN; switch(wParam) - 53
 /* nop */
 case VK_NUMPAD5: // switch(msg) - WM_KEYDOWN; switch(wParam) - 53, VK_NUMPAD5
 {
 IsLeftMouseButtonDown = false;
 IsRightMouseButtonDown = false;

 pairQI client = {mousePt, TOGGLE_CONTROL_POINT_TEXT};
 SsQueuePushBack(input, &client);

 ReleaseCapture();
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - 53, VK_NUMPAD5

 case 54: // switch(msg) - WM_KEYDOWN; switch(wParam) - 54
 /* nop */
 case VK_NUMPAD6: // switch(msg) - WM_KEYDOWN; switch(wParam) - 54, VK_NUMPAD6
 {
 /* nop */
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - 54, VK_NUMPAD6

 case 55: // switch(msg) - WM_KEYDOWN; switch(wParam) - 55
 /* nop */
 case VK_NUMPAD7: // switch(msg) - WM_KEYDOWN; switch(wParam) - 55, VK_NUMPAD7
 {
 /* nop */
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - 55, VK_NUMPAD7

 case 56: // switch(msg) - WM_KEYDOWN; switch(wParam) - 56
 /* nop */
 case VK_NUMPAD8: // switch(msg) - WM_KEYDOWN; switch(wParam) - 56, VK_NUMPAD8
 {
 /* nop */
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - 56, VK_NUMPAD8

 case 57: // switch(msg) - WM_KEYDOWN; switch(wParam) - 57
 /* nop */
 case VK_NUMPAD9: // switch(msg) - WM_KEYDOWN; switch(wParam) - 57, VK_NUMPAD9
 {
 /* nop */
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - 57, VK_NUMPAD9

 case VK_ADD: // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_ADD
 {
 IsLeftMouseButtonDown = false;
 IsRightMouseButtonDown = false;

 pairQI client = {mousePt, INCREASE_ITERATION_CONSTANT};
 SsQueuePushBack(input, &client);

 ReleaseCapture();
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_ADD

 case VK_SUBTRACT: // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_SUBTRACT
 {
 IsLeftMouseButtonDown = false;
 IsRightMouseButtonDown = false;

 pairQI client = {mousePt, DECREASE_ITERATION_CONSTANT};
 SsQueuePushBack(input, &client);

 ReleaseCapture();
 }
 goto label_return; // switch(msg) - WM_KEYDOWN; switch(wParam) - VK_SUBTRACT

 } // switch(msg) - WM_KEYDOWN; switch(wParam)
 }
 goto label_return; // switch(msg) - WM_KEYDOWN

 case WM_MOVE: // switch(msg) - WM_MOVE
 /* nop */
 case WM_MOVING: // switch(msg) - WM_MOVE, WM_MOVING
 {
 if(_graphics->GraphicsBackBufferFunction(reference) && !_graphics->GraphicsIsModeChangeActive(reference) && WindowStyle::getStyle() != /*Graphics::*/GRAPHICS_FULLSCREEN && !IsWindowStyleChanging)
 {
 pointInteger trans = {0, 0};

 /*int returnVal = */ClientToScreen(hwnd, (POINT*) &trans);

 WindowStyle::setOrigin(trans.x, trans.y);

 main(UPDATE_INPUT, mousePt.x, mousePt.y, 1, (double)_graphics->GraphicsClientWidth(reference) * 0.5, (double)_graphics->GraphicsClientHeight(reference) * 0.5, reference, _font);

 _graphics->GraphicsDrawBackBufferToScreen(reference, hwnd);

 Sleep(1);
 }
 }
 // We need help from DefWindowProc(...).
 break; // switch(msg) - WM_MOVE, WM_MOVING

// WM_SIZE
//
// Sent to a window after its size has changed.
//
// A window receives this message through its WindowProc function.
//
// wParam
// The type of resizing requested. This parameter can be one of the following values.
//
// SIZE_MAXHIDE Message is sent to all pop-up windows when some other window is maximized.
//
// SIZE_MAXIMIZED The window has been maximized.
//
// SIZE_MAXSHOW Message is sent to all pop-up windows when some other window has been restored to its former size.
//
// SIZE_MINIMIZED The window has been minimized.
//
// SIZE_RESTORED The window has been resized, but neither the SIZE_MINIMIZED nor SIZE_MAXIMIZED value applies.
//
// lParam
// The low-order word of lParam specifies the new width of the client area.
// The high-order word of lParam specifies the new height of the client area.
//
// Return value
// Type long long
//
// If an application processes this message, it should return zero.
//
// If the SetScrollPos or MoveWindow function is called for a child window as a result of the WM_SIZE message, the bRedraw or bRepaint parameter should be nonzero to cause the window to be repainted.
//
// Although the width and height of a window are 32-bit values, the lParam parameter contains only the low-order 16 bits of each.
//
// The DefWindowProc function sends the WM_SIZE and WM_MOVE messages when it processes the WM_WINDOWPOSCHANGED message. The WM_SIZE and WM_MOVE messages are not sent if an application handles the WM_WINDOWPOSCHANGED message without calling DefWindowProc.

 case WM_SIZE: // switch(msg) - WM_SIZE
 {
 // message is sent to all pop-up windows when some other window is maximized
 // or
 // the window has been minimized
 if(wParam == SIZE_MAXHIDE || wParam == SIZE_MINIMIZED)
 {
 if( !IsApplicationMinimized)
 {
 IsApplicationMinimized = true;

 // we need help from DefWindowProc(...)
 break;
 }
 }
 // the window has been maximized
 // or
 // message is sent to all pop-up windows when some other window has been restored to its former size
 // or
 // the window has been resized, but neither the SIZE_MINIMIZED nor SIZE_MAXIMIZED value applies
 else if(wParam == SIZE_MAXIMIZED || wParam == SIZE_MAXSHOW || wParam == SIZE_RESTORED)
 {
 if(IsApplicationMinimized)
 {
 unsigned short widthHeight[2] = {0};

 widthHeight[0] = (unsigned short)_graphics->oldWidth;
 widthHeight[1] = (unsigned short)_graphics->oldHeight;

 IsApplicationMinimized = false;

 GraphicsWindowProc(hwnd, WM_DISPLAYCHANGE, (unsigned long long)_graphics->oldBitDepth, *(unsigned long*)widthHeight);

 // we need help from DefWindowProc(...)
 break;
 }
 }
 }
 // ? are we supposed to pass through here ? verify todo
 goto label_return; // switch(msg) - WM_SIZE

// WM_SIZING
//
// Sent to a window that the user is resizing. By processing this message, an application can monitor the size and position of the drag rectangle and, if needed, change its size or position.
//
// A window receives this message through its WindowProc function.
//
// wParam
// The edge of the window that is being sized. This parameter can be one of the following values.
//
// WMSZ_BOTTOM Bottom edge
//
// WMSZ_BOTTOMLEFT Bottom-left corner
//
// WMSZ_BOTTOMRIGHT Bottom-right corner
//
// WMSZ_LEFT Left edge
//
// WMSZ_RIGHT Right edge
//
// WMSZ_TOP Top edge
//
// WMSZ_TOPLEFT Top-left corner
//
// WMSZ_TOPRIGHT Top-right corner
//
// lParam
// A pointer to a rectInteger structure with the screen coordinates of the drag rectangle. To change the size or position of the drag rectangle, an application must change the members of this structure.
//
// Return value
// Type long long
//
// An application should return true if it processes this message.

 case WM_SIZING: // switch(msg) - WM_SIZING
 {
 if(_graphics->GraphicsBackBufferFunction(reference) && !_graphics->GraphicsIsModeChangeActive(reference) && !IsWindowStyleChanging)
 {
 static double scaleTime = 0;

 rectInteger* _rect = (rectInteger*)lParam;

 if(msg == WM_SIZE)
 {
 _rect = (rectInteger*)InsertHeapAllocation(sizeof(rectInteger) );

 if(_rect == 0)
 {
 Error("WM_SIZE new rectInteger allocation failure");

 // We need help from DefWindowProc(...).
 break;
 }

 _rect->left = 0;
 _rect->top = 0;

 _rect->right = LOWORD(lParam);
 _rect->bottom = HIWORD(lParam);
 }
 else
 {
 updateTime();

 if(scaleTime > timeInSeconds() )
 {
 // We need help from DefWindowProc(...).
 break;
 }

 scaleTime = timeInSeconds() + 0.5;
 }

 WindowStyle::setSize(reference, _rect->right - _rect->left, _rect->bottom - _rect->top);

 if(_rect->right - _rect->left <= 0 || _rect->bottom - _rect->top <= 0)
 {
 IsApplicationMinimized = true;

 if(msg == WM_SIZE)
 {
 RemoveHeapAllocation(_rect);
 }

 PostMessageA(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);

 // We need help from DefWindowProc(...).
 break;
 }
 else if(WindowStyle::getStyle() == /*Graphics::*/GRAPHICS_FULLSCREEN)
 {
 if(msg == WM_SIZE)
 {
 RemoveHeapAllocation(_rect);
 }

 GraphicsWindowProc(hwnd, (unsigned int)WM_CHANGEWINDOWSTYLE, 0, 0);

 goto label_return;
 }

 main(DUMP_ALL_CAPTURES, mousePt.x, mousePt.y, 1, (double)_graphics->GraphicsClientWidth(reference) * 0.5, (double)_graphics->GraphicsClientHeight(reference) * 0.5, reference, _font);

 if(_font)
 _font->TextOutTermSystem( &_font);

 RemoveHandle(RobsTextOutInitSystem);

 _graphics->GraphicsTermScreenAndBackBuffer(reference);

 _graphics->width = _rect->right - _rect->left;
 _graphics->height = _rect->bottom - _rect->top;

 if(_graphics->GraphicsInitScreenAndBackBuffer(reference, hwnd) != /*Graphics::*/GRAPHICS_OK)
 {
 Error("Graphics::graphicsInitScreenAndBackBuffer(...) != /*Graphics::*/GRAPHICS_OK");

 if( !DestroyWindow(hwnd) )
 {
 Error("The function DestroyWindow(...) has failed in the function WindowProc(...).");
 }

 if(msg == WM_SIZE)
 {
 RemoveHeapAllocation(_rect);
 }

 // There is an error, so we do not need help from DefWindowProc(...).
 goto label_return;
 }

 InsertHandle(RobsTextOutInitSystem);

 Sleep(1);

 if(msg == WM_SIZE)
 {
 RemoveHeapAllocation(_rect);
 }
 }
 }
 // we need help from DefWindowProc(...)
 break; // switch(msg) - WM_SIZING

 // MSDN:
 // An application sends the WM_PAINT message when the system or another
 // application makes a request to paint a portion of an application's window.
 // The message is sent when the UpdateWindow or RedrawWindow function is called,
 // or by theDispatchMessage function when the application obtains a WM_PAINT
 // message by using theGetMessage orPeekMessage function.
 //
 // An application returns zero if it processes this message.
 case WM_PAINT: // switch(msg) - WM_PAINT
 {
 /* nop */
 }
 goto label_return; // switch(msg) - WM_PAINT

 // MSDN:
 // An application sends the WM_ERASEBKGND message when the window background
 // must be erased (for example, when a window is resized). The message is sent
 // to prepare an invalidated portion of a window for painting.
 //
 // An application should return nonzero if it erases the background;
 // otherwise, it should return zero.
 case WM_ERASEBKGND: // switch(msg) - WM_ERASEBKGND
 {
 result = 1;
 }
 // return nonzero to make believe the background was erased
 goto label_return; // switch(msg) - WM_ERASEBKGND

 case WM_DISPLAYCHANGE: // switch(msg) - WM_DISPLAYCHANGE
 {
 if( !_graphics->GraphicsIsModeChangeActive(reference) )
 {
 if(IsApplicationMinimized)
 {
 _graphics->oldBitDepth = (int)wParam;
 _graphics->oldWidth = LOWORD(lParam);
 _graphics->oldHeight = HIWORD(lParam);

 goto label_return;
 }

 if(_font)
 _font->TextOutTermSystem( &_font);

 RemoveHandle(RobsTextOutInitSystem);

 if(_graphics->width != _graphics->oldWidth || _graphics->height != _graphics->oldHeight)
 {
 if(WindowStyle::getStyle() == /*Graphics::*/GRAPHICS_FULLSCREEN)
 {
 WindowStyle::setStyle();
 }
 }

 _graphics->oldBitDepth = (int)wParam;
 _graphics->oldWidth = LOWORD(lParam);
 _graphics->oldHeight = HIWORD(lParam);

 _graphics->GraphicsTermScreenAndBackBuffer(reference);

 if(WindowStyle::getStyle() == /*Graphics::*/GRAPHICS_FULLSCREEN)
 {
 _graphics->width = _graphics->oldWidth;

 _graphics->height = _graphics->oldHeight;
 }
 else if(WindowStyle::getSize(reference, false).x + WindowStyle::getMenuRect().left + WindowStyle::getMenuRect().right >= _graphics->oldWidth || WindowStyle::getSize(reference, false).y + WindowStyle::getMenuRect().top + WindowStyle::getMenuRect().bottom >= _graphics->oldHeight)
 {
 WindowStyle::setStyle();

 GraphicsWindowProc(hwnd, (unsigned int)WM_CHANGEWINDOWSTYLE, 0, 0);

 goto label_return;
 }

 if(_graphics->GraphicsInitScreenAndBackBuffer(reference, hwnd) != /*Graphics::*/GRAPHICS_OK)
 {
 Error("Graphics::graphicsInitScreenAndBackBuffer(...) != /*Graphics::*/GRAPHICS_OK");

 if( !DestroyWindow(hwnd) )
 {
 Error("The function DestroyWindow(...) has failed in the function WindowProc(...).");
 }

 goto label_return;
 }

 InsertHandle(RobsTextOutInitSystem);

 if(isMenuActive)
 {
 main(DUMP_ALL_CAPTURES, mousePt.x, mousePt.y, 1, (double)_graphics->GraphicsClientWidth(reference) * 0.5, (double)_graphics->GraphicsClientHeight(reference) * 0.5, reference, _font);
 }
 else
 {
 pairQI client = {mousePt, DUMP_ALL_CAPTURES};
 SsQueuePushBack(input, &client);
 }
 }
 }
 goto label_return; // switch(msg) - WM_DISPLAYCHANGE

 // MSDN:
 // The WM_CLOSE message is sent as a signal
 // that a window or an application should terminate.
 //
 // The DefWindowProc function calls the DestroyWindow
 // function to destroy the window (since I handle it, I call it myself).
 //
 // If an application processes this message, it should return zero.
 case WM_CLOSE: // switch(msg) - WM_CLOSE
 {
 // MSDN:
 // The DestroyWindow function destroys the specified window.
 // The function sends WM_DESTROY and WM_NCDESTROY messages to the window.
 if( !DestroyWindow(hwnd) )
 {
 Error("The function DestroyWindow(...) has failed in the function WindowProc(...).");
 }
 }
 goto label_return; // switch(msg) - WM_CLOSE

 // MSDN:
 // The WM_DESTROY message is sent when a window is being destroyed.
 //
 // If an application processes this message, it should return zero.
 case WM_DESTROY: // switch(msg) - WM_DESTROY
 {
 if(IsWindowStyleChanging)
 goto label_return;

 mainTerm(hwnd);

 // MSDN:
 // The PostQuitMessage function indicates to the system
 // that a thread has made a request to terminate (quit).
 // It is typically used in response to a WM_DESTROY message.
 //
 // Parameters -> nExitCode:
 // Specifies an application exit code. This value is used
 // as the wParam parameter of the WM_QUIT message.
 PostQuitMessage(0);

 IsApplicationEntry = false;

 // MSDN:
 // Terminate the calling process after cleanup
 //
 // Performs complete C library termination procedures, terminates
 // the process, and exits with the supplied status code.
 exit(0);
 }
 //goto label_return; // switch(msg) - WM_DESTROY

 // MSDN:
 // The WM_QUIT message indicates a request to terminate an application and
 // is generated when the application calls the PostQuitMessage function.
 // It causes the GetMessage function to return zero.
 //
 // This message does not have a return value, because it causes
 // the message loop to terminate before the message is sent to the
 // application's window procedure.
 case WM_QUIT: // switch(msg) - WM_QUIT
 {
 result = (long long)wParam;
 }
 goto label_return; // switch(msg) - WM_QUIT

 } // switch(msg)

 // MSDN:
 // The DefWindowProc function calls the default window procedure
 // to provide default processing for any window messages that an
 // application does not process. This function ensures that every
 // message is processed. DefWindowProc is called with the same
 // parameters received by the window procedure.
 //
 // The return value is the result of the message
 // processing and depends on the message.
 result = DefWindowProcA(hwnd, msg, wParam, lParam);

label_return:
 return result;
}

static HANDLE mutexHandle = 0;
static HINSTANCE _hInstance = 0;
static WNDCLASSA windowClass = {0};

// Keep track of how many handles have been opened
static LIST_HEAD* listOfHandles = 0;

// Keep track of how many allocations there are on the heap
static LIST_HEAD* listOfHeapAllocations = 0;

static int RemoveHeapAllocation(void* heapAllocation)
{
 int result = -1;

 int functionReturnValue = 0;
 CLIENT_POTYPE Object = {0};

 if( !heapAllocation || heapAllocation == (void*)0xffffffff)
 {
 Error("RemoveHeapAllocation -- heapAllocation == 0");
 goto label_return;
 }

 if( !listOfHeapAllocations)
 {
 Error("RemoveHeapAllocation -- listOfHeapAllocations == 0");
 goto label_return;
 }

 Object.object = heapAllocation;

 functionReturnValue = ListRemove(listOfHeapAllocations, TestObjectEquivalent, &Object);

 if(functionReturnValue || Object.object != heapAllocation)
 {
 Error("ListRemove failure -- unknown heap allocation");
 goto label_return;
 }

 DeAllocate(heapAllocation);

 result = 0;

label_return:
 return result;
}

static int RemoveHandle(void* handle)
{
 int result = -1;

 int functionReturnValue = 0;
 CLIENT_POTYPE Object = {0};

 if( !handle)
 {
 Error("RemoveHandle -- handle == 0");
 goto label_return;
 }

 if( !listOfHandles)
 {
 Error("RemoveHandle -- listOfHandles == 0");
 goto label_return;
 }

 Object.object = handle;

 functionReturnValue = ListRemove(listOfHandles, TestObjectEquivalent, &Object);

 if(functionReturnValue || Object.object != handle)
 {
 Error("ListRemove failure -- unknown handle");
 goto label_return;
 }

 result = 0;

label_return:
 return result;
}

const unsigned int HEAP_ALLOCATION_ERROR = 0xffffffff;

static void* InsertHeapAllocation(size_t numBytesToAllocate)
{
 int functionReturnValue = 0;
 void* heapAllocation = 0;

 CLIENT_POTYPE Object = {0};

 SetLastError(HEAP_ALLOCATION_ERROR);

 if( !listOfHeapAllocations)
 {
 Error("InsertHeapAllocation -- listOfHeapAllocations == 0");
 goto label_return;
 }

 heapAllocation = Allocate(numBytesToAllocate);

BlahLog2("2 %i %llu\n", (int)numBytesToAllocate, (uint64_t)heapAllocation);

 if( !heapAllocation)
 {
 Error("InsertHeapAllocation -- heapAllocation == 0");
 goto label_return;
 }

 memset(heapAllocation, 0, numBytesToAllocate);

 Object.object = heapAllocation;

 functionReturnValue = ListInsert(listOfHeapAllocations, Object, 0);

 if(functionReturnValue)
 {
 Error("ListInsert failure -- heap allocation not inserted and freed");

 free(heapAllocation);
 heapAllocation = 0;

 goto label_return;
 }

 SetLastError(ERROR_SUCCESS);

label_return:
 return heapAllocation;
}

static int InsertHandle(void* handle)
{
 int result = -1;

 int functionReturnValue = 0;

 CLIENT_POTYPE Object = {0};

 if( !handle)
 {
 Error("InsertHandle -- handle == 0");
 goto label_return;
 }

 if( !listOfHandles)
 {
 Error("InsertHandle -- listOfHandles == 0");
 goto label_return;
 }

 Object.object = handle;

 functionReturnValue = ListInsert(listOfHandles, Object, 0);

 if(functionReturnValue)
 {
 Error("ListInsert failure -- handle not inserted");
 goto label_return;
 }

 result = 0;

label_return:
 return result;
}

static int mainTerm(HWND hwnd)
{
 int result = 0;

 int numberOfObjects = 0;

 int functionReturnValue = 0;

 CLIENT_POTYPE Object = {0};

 //while(SsQueueNum(input) > 0)
 //{
 // pairQI client = { {0}, 0};
 // SsQueuePopFront(input, &client);
 //}

 BlahLog2("destroy input before %lli\n", SsQueueNum(input) );

 SsQueueDestruct( &input);

 BlahLog2("destroy input after\n");

 //input = 0;

 if(term() )
 {
 Warning("Client term(...) function returns nonzero value.");
 }

 RemoveHandle(hwnd);

 if(_font)
 _font->TextOutTermSystem( &_font);

 RemoveHandle(RobsTextOutInitSystem);

 GraphicsTermScreenAndBackBuffer( (GraphicsClient*)_graphics);

 GraphicsClientDestruct( (GraphicsClient**)&_graphics);

 // Unregister the class.
 // All window classes that an application registers
 // are unregistered when it terminates!!!!!
 //
 // UnregisterClassA will always fail since the window will
 // always still be open. By the time I have the ability
 // to unregister the class, it has already been done for
 // me by the OS, as is stated in MSDN.
 //
 // Remove the class handle from the list, we do not
 // need to call UnregisterClassA, nor can we.
 //
 // If unregister class works, remove the class handle
 // from the handle list.
 //
 // As long as the window is properly destroyed, the class
 // will always be unregistered automatically.
 RemoveHandle( (void*) &windowClass);

 if( !CloseHandle(mutexHandle) )
 {
 Error("CloseHandle(...) failure");
 result = -1;
 }
 // If CloseHandle works, remove the handle
 // from the handle list.
 else
 {
 RemoveHandle( (void*)mutexHandle);
 }

 functionReturnValue = ListIsEmpty(listOfHeapAllocations, &numberOfObjects);

 // At the time we call ListIsEmpty, all heap allocated variables
 // should have been freed. listOfHeapAllocations should be empty.
 if(functionReturnValue != 1 || numberOfObjects)
 {
 /* Error("listOfHeapAllocations is not empty"); */

 CLIENT_POTYPE object = {0};

 while( !ListGetNext(listOfHeapAllocations, &object, 1) )
 {
 if(RemoveHeapAllocation(object.object) )
 Error("RemoveHeapAllocation(...) function failure");
 }

 result = -1;
 }

 // Check if the three handles that should be in the handle list are
 // really in the handle list.

 Object.object = file;

 functionReturnValue = ListFind(listOfHandles, TestObjectEquivalent, &Object);

 if(functionReturnValue || Object.object != file)
 {
 Error("listOfHandles -- file not in handle list -- why not?");
 result = -1;
 }

 Object.object = listOfHandles;

 functionReturnValue = ListFind(listOfHandles, TestObjectEquivalent, &Object);

 if(functionReturnValue || Object.object != listOfHandles)
 {
 Error("listOfHandles -- listOfHandles not in handle list -- why not?");
 result = -1;
 }

 Object.object = listOfHeapAllocations;

 functionReturnValue = ListFind(listOfHandles, TestObjectEquivalent, &Object);

 if(functionReturnValue || Object.object != listOfHeapAllocations)
 {
 Error("listOfHandles -- listOfHeapAllocations not in handle list -- why not?");
 result = -1;
 }

 functionReturnValue = ListIsEmpty(listOfHandles, &numberOfObjects);

 // At the time we call ListIsEmpty, there should be 3 handles left:
 // file, listOfHandles, and listOfHeapAllocations.
 if(functionReturnValue || numberOfObjects != 3)
 {
 Error("listOfHandles is not empty");
 result = -1;
 }


 if(file != (FILE*)0xff)
 {
 if(fclose(file) )
 {
 Error("fclose(...) failure");
 result = -1;
 }
 }

 ListTerminate(listOfHeapAllocations);

 ListTerminate(listOfHandles);

 return result;
}

static double _timeTicksPerSecond = 0;
static double _timeInSeconds = 0;
static double _timeDelta = 0;
static double _timeStart = 0;

static double timeDeltaInSeconds()
{
 return _timeDelta;
}

static double timeInSeconds()
{
 return _timeInSeconds;
}

static int initTime()
{
 int result = 0;

 uint64_t temporary = 0;
 if( !QueryPerformanceFrequency( (LARGE_INTEGER*) &temporary) )
 {
 Error("QueryPerformanceFrequency(...) function failure");
 result = -1;
 }

 _timeTicksPerSecond = (double)temporary;

 temporary = 0;
 if( !QueryPerformanceCounter( (LARGE_INTEGER*) &temporary) )
 {
 Error("QueryPerformanceCounter(...) function failure");
 result = -1;
 }

 _timeInSeconds = (double)temporary;

 _timeInSeconds /= _timeTicksPerSecond;

 _timeStart = _timeInSeconds;

 return result;
}

static int updateTime()
{
 int result = 0;

 double previousTime = 0;

 uint64_t temporary = 0;
 if( !QueryPerformanceCounter( (LARGE_INTEGER*) &temporary) )
 {
 Error("QueryPerformanceCounter(...) function failure");
 result = -1;
 }

 previousTime = _timeInSeconds;

 _timeInSeconds = (double)temporary;

 _timeInSeconds /= _timeTicksPerSecond;

 _timeDelta = _timeInSeconds - previousTime;

 return result;
}

// MSDN
// hPrevInstance
// Handle to the previous instance of the application. For a Win32-based
// application, this parameter is always 0.
//
// If you need to detect whether another instance already exists, create a
// uniquely named mutex using the CreateMutexA function. CreateMutexA will
// succeed even if the mutex already exists, but the GetLastError function
// will return ERROR_ALREADY_EXISTS. This indicates that another instance of
// your application exists, because it created the mutex first.
//
// int __stdcall WinMain(HINSTANCE currentInstance, HINSTANCE previousInstance, char* commandLine, int showStateOfWindow)

extern "C" int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, char* /*lpCmdLine*/, int nCmdShow)
{
 int currentFrameNumber = 0;

 int result = 0;

 int windowType = 0;

 rectInteger windowRect = {0};

 MSG Message = {0};

 pointInteger origin = {0};

 GraphicsClient* reference = 0;

 _hInstance = hInstance;

 IsApplicationEntry = true;

 // Only allow one instance of the application at a time. Use CreateMutexA
 // to test if an instance of the application already exists, quit if
 // another instance exists or if CreateMutexA returns 0.
 mutexHandle = CreateMutexA(0, false, "FunkyLovinSugarDaddy");

 if( !mutexHandle)
 {
 // Use MessageBox until we make sure that this is the only instance
 // of the application. Then we can set up the log file.
 ErrorBox("(MutexHandle = CreateMutexA(...) ) == 0");

 IsApplicationEntry = false;

 goto label_return;
 }

 if(GetLastError() == ERROR_ALREADY_EXISTS)
 {
 if( !CloseHandle(mutexHandle) )
 {
 ErrorBox("CloseHandle(...) failure");
 }

 IsApplicationEntry = false;

 goto label_return;
 }

 // 1) Initialize the log file for logging warnings and errors.
 file = fopen("cs250debug.txt", "wb");

#if !defined NDEBUG
 // Quit if the log file handle was not created.
 if( !file)
 {
 if( !CloseHandle(mutexHandle) )
 {
 ErrorBox("CloseHandle(...) failure");
 }

 ErrorBox("(file = fopen(...) ) == 0");

 IsApplicationEntry = false;

 goto label_return;
 }
#else
 if( !file)
 {
 file = (FILE*) 0xff;
 }
#endif

 // Copyright 1999-2000 Bruce Dawson. ~ start
 // Bruce Dawson, a man of integrity.

 // 6) Set _CrtSetDbgFlag to keep track of allocations on the heap
 _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

 // Enable floating _point exceptions to track down bad floating _point usage.
 /* _controlfp(0, _EM_ZERODIVIDE | _EM_INVALID); */

 // Copyright 1999-2000 Bruce Dawson. ~ end

 listOfHandles = ListInit(0, 20);
 listOfHeapAllocations = ListInit(0, 20);

 if( !listOfHandles)
 {
 Error("(listOfHandles = ListInit(...) ) == 0");

 if( !CloseHandle(mutexHandle) )
 {
 Error("CloseHandle(...) failure");
 }

 if(file != (FILE*)0xff)
 {
 if(fclose(file) )
 {
 Error("fclose(...) failure");
 }
 }

 IsApplicationEntry = false;

 goto label_return;
 }

 if( !listOfHeapAllocations)
 {
 ListTerminate(listOfHandles);

 Error("(listOfHeapAllocations = ListInit(...) ) == 0");

 if( !CloseHandle(mutexHandle) )
 {
 Error("CloseHandle(...) failure");
 }

 if(file != (FILE*)0xff)
 {
 if(fclose(file) )
 {
 Error("fclose(...) failure");
 }
 }

 IsApplicationEntry = false;

 goto label_return;
 }

 // -1-
 InsertHandle(listOfHandles);
 // -2-
 InsertHandle(listOfHeapAllocations);
 // -3-
 InsertHandle(mutexHandle);
 // -4-
 InsertHandle(file);

 _graphics = (GraphicsBlah*)GraphicsClientConstruct(0);

 reference = (GraphicsClient*)_graphics;

 // 7) Create an application with a client area 640 by 480
 // using RegisterClassA and CreateWindowA
 windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
 windowClass.lpfnWndProc = GraphicsWindowProc;
 windowClass.cbClsExtra = 8;
 windowClass.cbWndExtra = 8;
 windowClass.hInstance = hInstance;

 windowClass.hIcon = (HICON)LoadImageA(0, "hell.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE | LR_LOADTRANSPARENT | LR_SHARED);

 //windowClass.hCursor = LoadCursorA(0, IDC_ARROW_A/*IDC_IBEAM_A*/);
 windowClass.hCursor = (HCURSOR)LoadImageA(0, "hell.ico", IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE /*| LR_LOADTRANSPARENT */| LR_SHARED);

 windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
 windowClass.lpszMenuName = appClassName;
 windowClass.lpszClassName = appClassName;

 // windowClass.cbClsExtra = 8 GetClassLongPtrA SetClassLongPtrA
 // windowClass.cbWndExtra = 8 GetWindowLongPtrA SetWindowLongPtrA

 if( !RegisterClassA( &windowClass) )
 {
 int numberOfObjects = 0;

 Error("RegisterClassA(...) == 0");

 if( !CloseHandle(mutexHandle) )
 {
 Error("CloseHandle(...) failure");
 }
 else
 {
 RemoveHandle(mutexHandle);
 }

 if(file != (FILE*)0xff)
 {
 if(fclose(file) )
 {
 Error("fclose(...) failure");
 }
 else
 {
 RemoveHandle(file);
 }
 }
 else
 {
 RemoveHandle(file);
 }

 if(ListIsEmpty(listOfHeapAllocations, 0) != 1)
 {
 Error("listOfHeapAllocations is not empty");
 }

 ListTerminate(listOfHeapAllocations);


 RemoveHandle(listOfHeapAllocations);

 ListIsEmpty(listOfHandles, &numberOfObjects);

 if(numberOfObjects != 1)
 {
 Error("listOfHandles is not empty");
 }

 ListTerminate(listOfHandles);

 IsApplicationEntry = false;

 goto label_return;
 }

 // -5-
 InsertHandle( &windowClass);

 GraphicsWindowProc(0, (unsigned int)WM_SETWIDTHHEIGHT, 0, 0);

 windowRect.left = 0;
 windowRect.top = 0;
 windowRect.right = _graphics->GraphicsClientWidth(reference);
 windowRect.bottom = _graphics->GraphicsClientHeight(reference);

 windowType = _graphics->GraphicsCheckIsFullScreen(reference);

 if(windowType == /*Graphics::*/GRAPHICS_ERROR || (windowType != /*Graphics::*/GRAPHICS_WINDOW && windowType != /*Graphics::*/GRAPHICS_FULLSCREEN) )
 {
 int numberOfObjects = 0;

 Error("graphicsCheckIsFullScreen(...) == GRAPHICS_ERROR");

 if( !UnregisterClassA(appClassName, _hInstance) )
 {
 Error("UnregisterClassA(...) failure");
 }
 else
 {
 RemoveHandle( &windowClass);
 }

 if( !CloseHandle(mutexHandle) )
 {
 Error("CloseHandle(...) failure");
 }
 else
 {
 RemoveHandle(mutexHandle);
 }

 if(file != (FILE*)0xff)
 {
 if(fclose(file) )
 {
 Error("fclose(...) failure");
 }
 else
 {
 RemoveHandle(file);
 }
 }
 else
 {
 RemoveHandle(file);
 }

 if(ListIsEmpty(listOfHeapAllocations, 0) != 1)
 {
 Error("listOfHeapAllocations is not empty");
 }

 ListTerminate(listOfHeapAllocations);


 RemoveHandle(listOfHeapAllocations);

 ListIsEmpty(listOfHandles, &numberOfObjects);

 if(numberOfObjects != 1)
 {
 Error("listOfHandles is not empty");
 }

 ListTerminate(listOfHandles);

 IsApplicationEntry = false;

 goto label_return;
 }

 if(windowType == /*Graphics::*/GRAPHICS_WINDOW)
 {
 windowType = WS_OVERLAPPEDWINDOW;
 }
 else if(windowType == /*Graphics::*/GRAPHICS_FULLSCREEN)
 {
 windowType = WS_POPUP;
 }

 if( !AdjustWindowRect( (RECT*) &windowRect, (unsigned long)windowType, false) )
 {
 int numberOfObjects = 0;

 Error("AdjustWindowRect(...) == 0");

 if( !UnregisterClassA(appClassName, _hInstance) )
 {
 Error("UnregisterClassA(...) failure");
 }
 else
 {
 RemoveHandle( &windowClass);
 }

 if( !CloseHandle(mutexHandle) )
 {
 Error("CloseHandle(...) failure");
 }
 else
 {
 RemoveHandle(mutexHandle);
 }

 if(file != (FILE*)0xff)
 {
 if(fclose(file) )
 {
 Error("fclose(...) failure");
 }
 else
 {
 RemoveHandle(file);
 }
 }
 else
 {
 RemoveHandle(file);
 }

 if(ListIsEmpty(listOfHeapAllocations, 0) != 1)
 {
 Error("listOfHeapAllocations is not empty");
 }

 ListTerminate(listOfHeapAllocations);

 RemoveHandle(listOfHeapAllocations);

 ListIsEmpty(listOfHandles, &numberOfObjects);

 if(numberOfObjects != 1)
 {
 Error("listOfHandles is not empty");
 }

 ListTerminate(listOfHandles);

 IsApplicationEntry = false;

 goto label_return;
 }

 WindowStyle::setMenuRect( -windowRect.left, -windowRect.top, windowRect.right - _graphics->GraphicsClientWidth(reference), windowRect.bottom - _graphics->GraphicsClientHeight(reference) );

 // The left and top of WindowRect will be less than or equal to
 // zero. Reposition the window so that WindowRect starts at 0, 0.

 if(windowRect.left > 0 || windowRect.top > 0 || windowRect.right <= 0 || windowRect.bottom <= 0)
 {
 int numberOfObjects = 0;

 Error("bad windowRect values");

 if( !UnregisterClassA(appClassName, _hInstance) )
 {
 Error("UnregisterClassA(...) failure");
 }
 else
 {
 RemoveHandle( &windowClass);
 }

 if( !CloseHandle(mutexHandle) )
 {
 Error("CloseHandle(...) failure");
 }
 else
 {
 RemoveHandle(mutexHandle);
 }

 if(file != (FILE*)0xff)
 {
 if(fclose(file) )
 {
 Error("fclose(...) failure");
 }
 else
 {
 RemoveHandle(file);
 }
 }
 else
 {
 RemoveHandle(file);
 }

 if(ListIsEmpty(listOfHeapAllocations, 0) != 1)
 {
 Error("listOfHeapAllocations is not empty");
 }

 ListTerminate(listOfHeapAllocations);


 RemoveHandle(listOfHeapAllocations);

 ListIsEmpty(listOfHandles, &numberOfObjects);

 if(numberOfObjects != 1)
 {
 Error("listOfHandles is not empty");
 }

 ListTerminate(listOfHandles);

 IsApplicationEntry = false;

 goto label_return;
 }

 if(windowRect.left < 0)
 {
 windowRect.left = -windowRect.left;
 }

 if(windowRect.top < 0)
 {
 windowRect.top = -windowRect.top;
 }

 windowRect.right += windowRect.left;
 windowRect.bottom += windowRect.top;

 windowRect.left = 0;
 windowRect.top = 0;

 origin.x = (_graphics->GraphicsClientWidth(reference) * 2 - windowRect.right) / 2;
 origin.y = (_graphics->GraphicsClientHeight(reference) * 2 - windowRect.bottom) / 2;

 WindowStyle::setOrigin(origin.x + WindowStyle::getMenuRect().left, origin.y + WindowStyle::getMenuRect().top);

 BlahLog2("create input before\n");

 input = SsQueueConstruct(sizeof(pairQI), 100, 4000000000, 10000);

 BlahLog2("create input after\n");

// HWND CreateWindowA(const char* windowClassName, const char* windowsTitleText, unsigned long windowStyle, int windowTopLeftXpos, int windowTopLeftYpos, int windowXwidth, int windowYheight, HWND parentWindow, HMENU childMenu, HINSTANCE currentInstance, void* parameterToWmCreate)

 hWindow = CreateWindowExA(0, appClassName, appName, (unsigned long)windowType, origin.x, origin.y, windowRect.right, windowRect.bottom, 0, 0, hInstance, 0);

 if( !hWindow || !input)
 {
 int numberOfObjects = 0;

 Error("(hWindow = CreateWindowA(...) ) == 0");

 if( !UnregisterClassA(appClassName, _hInstance) )
 {
 Error("UnregisterClassA(...) failure");
 }
 else
 {
 RemoveHandle( &windowClass);
 }

 if( !CloseHandle(mutexHandle) )
 {
 Error("CloseHandle(...) failure");
 }
 else
 {
 RemoveHandle(mutexHandle);
 }

 if(file != (FILE*)0xff)
 {
 if(fclose(file) )
 {
 Error("fclose(...) failure");
 }
 else
 {
 RemoveHandle(file);
 }
 }
 else
 {
 RemoveHandle(file);
 }

 if(ListIsEmpty(listOfHeapAllocations, 0) != 1)
 {
 Error("listOfHeapAllocations is not empty");
 }

 ListTerminate(listOfHeapAllocations);

 RemoveHandle(listOfHeapAllocations);

 ListIsEmpty(listOfHandles, &numberOfObjects);

 if(numberOfObjects != 1)
 {
 Error("listOfHandles is not empty");
 }

 ListTerminate(listOfHandles);

 IsApplicationEntry = false;

 goto label_return;
 }

 // -6-
 InsertHandle(hWindow);

 initTime();

 updateTime();

 // MSDN:
 // The ShowWindow function sets the specified window's show state.
 //
 // ... the first time ShowWindow is called, the value (2nd parameter) should be
 // the value obtained by the WinMain function in its nCmdShow parameter.
 if(ShowWindow(hWindow, nCmdShow) )
 {
 Error("ShowWindow(...) != 0");

 goto label_num;
 }

 {
 SetLastError(0);
 unsigned long long wsejfediorhjgfodjht = (unsigned long long)SetWindowLongPtrA(hWindow, 0, 0x1000000010000000ULL);
 wsejfediorhjgfodjht = GetLastError();
 //BlahLog("SetWindowLongPtrA %llu\n", wsejfediorhjgfodjht);
 }

 if(0)
 {
 BlahLog("sizeof(SECURITY_ATTRIBUTES) %i\n", (int)sizeof(SECURITY_ATTRIBUTES) );
 BlahLog("sizeof(BITMAPFILEHEADER) %i\n", (int)sizeof(BITMAPFILEHEADER) );
 BlahLog("sizeof(CREATESTRUCTA) %i\n", (int)sizeof(CREATESTRUCTA) );
 BlahLog("sizeof(MSG) %i\n", (int)sizeof(MSG) );
 BlahLog("sizeof(WIN32_FIND_DATAA) %i\n", (int)sizeof(WIN32_FIND_DATAA) );
 BlahLog("sizeof(WNDCLASSA) %i\n", (int)sizeof(WNDCLASSA) );
 }

 if(_graphics->GraphicsInitScreenAndBackBuffer(reference, hWindow) != /*Graphics::*/GRAPHICS_OK)
 {
 Error("Graphics::graphicsInitScreenAndBackBuffer(...) != /*Graphics::*/GRAPHICS_OK");

 goto label_num;
 }

 InsertHandle(RobsTextOutInitSystem);

 _graphics->GraphicsLockBackBuffer(reference);

 WindowStyle::setSize(reference, _graphics->GraphicsClientWidth(reference), _graphics->GraphicsClientHeight(reference) );

 if(init( (double)_graphics->GraphicsClientWidth(reference) * 0.5, (double)_graphics->GraphicsClientHeight(reference) * 0.5, reference, _font) )
 {
 Warning("Client init(...) function returns nonzero value, quitting abruptly.");

 _graphics->GraphicsUnlockBackBuffer(reference);

 goto label_num;
 }

 _graphics->GraphicsUnlockBackBuffer(reference);

 PeekMessageA( &Message, hWindow, 0, 0, PM_REMOVE);

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
 // while (GetMessage(lpMsg, hWnd, 0, 0) ) ...
 // The possibility of a -1 return value means that such code can lead to fatal application errors.
 while(Message.message != WM_QUIT)
 {
 PeekMessageA( &Message, hWindow, 0, 0, PM_REMOVE);

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
 TranslateMessage( &Message);

 // MSDN:
 // The DispatchMessage function dispatches a message to a window procedure.
 // It is typically used to dispatch a message retrieved by the GetMessage function.
 //
 // The MSG structure must contain valid message values.
 // If the lpmsg parameter points to a WM_TIMER message and the lParam parameter of the WM_TIMER
 // message is not 0, lParam points to a function that is called instead of the window procedure.
 DispatchMessageA( &Message);

 if(IsApplicationMinimized)
 {
 Sleep(2);

 continue;
 }

 currentFrameNumber++;

 _graphics->GraphicsLockBackBuffer(reference);

 if( !SsQueueNum(input) )
 {
 pointInteger mousePt = {0};

 GetCursorPos( (POINT*) &mousePt);
 ScreenToClient(hWindow, (POINT*) &mousePt);

 result = main(UPDATE_INPUT, mousePt.x, mousePt.y, 1, (double)_graphics->GraphicsClientWidth(reference) * 0.5, (double)_graphics->GraphicsClientHeight(reference) * 0.5, reference, _font);

 if(result == 1)
 {
 _graphics->GraphicsUnlockBackBuffer(reference);

 _graphics->GraphicsClearBackBuffer(reference);

 _graphics->GraphicsLockBackBuffer(reference);

 _font->T1xtOut(_font, 10, 10, "Press F8 for help");

 main(UPDATE_INPUT, mousePt.x, mousePt.y, 1, (double)_graphics->GraphicsClientWidth(reference) * 0.5, (double)_graphics->GraphicsClientHeight(reference) * 0.5, reference, _font);
 }
 else if(result)
 {
 Warning("Client main(...) function returns nonzero value, quitting abruptly.");

 _graphics->GraphicsUnlockBackBuffer(reference);

 goto label_num;
 }
 }

 while(SsQueueNum(input) > 0)
 {
 pairQI client = { {0}, 0};
 SsQueuePopFront(input, &client);

 if(client.second == MENU_INPUT)
 {
 union
 {
 double* p;
 double f;
 pointInteger pt;

 }menu;

 memset( &menu, 0, sizeof(menu) );

 menu.pt = client.first;

 result = main(MENU_INPUT, 0, menu.f, 1, (double)_graphics->GraphicsClientWidth(reference) * 0.5, (double)_graphics->GraphicsClientHeight(reference) * 0.5, reference, _font);
 }
 else
 {
 result = main(client.second, client.first.x, client.first.y, 1, (double)_graphics->GraphicsClientWidth(reference) * 0.5, (double)_graphics->GraphicsClientHeight(reference) * 0.5, reference, _font);
 }

 if(result == 1)
 {
 _graphics->GraphicsUnlockBackBuffer(reference);

 _graphics->GraphicsClearBackBuffer(reference);

 _graphics->GraphicsLockBackBuffer(reference);

 _font->T1xtOut(_font, 10, 10, "Press F8 for help");

 main(UPDATE_INPUT, client.first.x, client.first.y, 1, (double)_graphics->GraphicsClientWidth(reference) * 0.5, (double)_graphics->GraphicsClientHeight(reference) * 0.5, reference, _font);
 }
 else if(result)
 {
 Warning("Client main(...) function returns nonzero value, quitting abruptly.");

 _graphics->GraphicsUnlockBackBuffer(reference);

 goto label_num;
 }

 //input->pop();
 }

 _graphics->GraphicsUnlockBackBuffer(reference);

 if(_timeInSeconds - _timeStart > 2)
 {
 currentFrameNumber = 0;

 _timeStart = _timeInSeconds;
 }

 _graphics->GraphicsDrawBackBufferToScreen(reference, hWindow);

 Sleep(1);
 }

label_num:
 PostMessageA(hWindow, WM_DESTROY, 0, 0);

 IsApplicationEntry = false;

 result = (int)Message.wParam;

label_return:
 return result;
}

extern int GetFilesNamed(char* folderPath, int* howManyOutput, LIST_HEAD* fileList)
{
 CLIENT_POTYPE object = {0};

 int result = 0;
 int loop = 0;
 int tempStore = 0;

 WIN32_FIND_DATAA data = {0};

 HANDLE Search = 0;

 if( !folderPath || !howManyOutput || !fileList)
 {
 Error("The function GetFilesNamed(...) has received an invalid function parameter list.");

 result = -1;
 goto label_return;
 }

 *howManyOutput = 0;

 Search = FindFirstFileA(folderPath, &data);

 if(Search == INVALID_HANDLE_VALUE)
 {
 Error("The function FindFirstFileA(...) has failed in the function GetFilesNamed(...).");

 result = -1;
 goto label_return;
 }

 tempStore++;

 SetLastError(ERROR_SUCCESS);

 result = FindNextFileA(Search, &data);

 while(result && GetLastError() == ERROR_SUCCESS)
 {
 tempStore++;

 result = FindNextFileA(Search, &data);
 }

 if(result || GetLastError() != ERROR_NO_MORE_FILES)
 {
 Error("The function FindNextFileA(...) in the function GetFilesNamed(...) has indicated an error.");

 result = -1;
 goto label_return;
 }

 if( !FindClose(Search) )
 {
 Error("The function FindClose(..) has failed in the function GetFilesNamed(...).");

 result = -1;
 goto label_return;
 }

 Search = FindFirstFileA(folderPath, &data);

 if(Search == INVALID_HANDLE_VALUE)
 {
 Error("The function FindFirstFileA(...) has failed in the function GetFilesNamed(...).");

 result = -1;
 goto label_return;
 }

 SetLastError(ERROR_SUCCESS);

 strcpy(object.name, data.cFileName);

 if(GetLastError() != ERROR_SUCCESS)
 {
 Error("The function strcpy(...) has indicated an error through GetLastError(...) in GetFilesNamed(...).");

 FindClose(Search);

 result = -1;
 goto label_return;
 }

 ListInsert(fileList, object, 0);

 for(loop = 1; loop < tempStore; loop++)
 {
 if( !FindNextFileA(Search, &data) )
 {
 Error("The function FindNextFileA(...) has failed in the function GetFilesNamed(...).");

 FindClose(Search);

 result = -1;
 goto label_return;
 }

 SetLastError(ERROR_SUCCESS);

 strcpy(object.name, data.cFileName);

 if(GetLastError() != ERROR_SUCCESS)
 {
 Error("The function strcpy(...) has indicated an error through GetLastError(...) in GetFilesNamed(...).");

 FindClose(Search);

 result = -1;
 goto label_return;
 }

 if(ListInsert(fileList, object, 0) )
 {
 Error("The function ListInsert(...) has failed in the function GetFilesNamed(...).");

 FindClose(Search);

 result = -1;
 goto label_return;
 }
 }

 *howManyOutput = tempStore;

 if( !FindClose(Search) )
 {
 Error("The function FindClose(...) has failed at the end of the function GetFilesNamed(...).");

 result = -1;
 goto label_return;
 }

 result = 0;

label_return:
 return result;
}
