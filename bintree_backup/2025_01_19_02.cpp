
// 2025_01_19_02.cpp



struct GraphicsClient
{

long long __stdcall AboutDlgProc(HWND hDlg, unsigned int msg, unsigned long long wParam, long long lParam);

long long __stdcall InputDlgProc(HWND hDlg, unsigned int msg, unsigned long long wParam, long long lParam);

long long __stdcall WindowProc(HWND hwnd, unsigned int msg, unsigned long long wParam, long long lParam);

void _RenderPoint32(GraphicsClient* _graphics, int x0, int y0, int c0);
void RenderPoint32(GraphicsClient* _graphics, int x0, int y0, int c0);

void _RenderLine32(GraphicsClient* _graphics, int x0, int y0, int x1, int y1, int c0, int c1);
void RenderLine32(GraphicsClient* _graphics, int x0, int y0, int x1, int y1, int c0, int c1);

void _RenderCircle32(GraphicsClient* _graphics, int x0, int y0, int r0, int c0, int c1);
void RenderCircle32(GraphicsClient* _graphics, int x0, int y0, int r0, int c0, int c1);

enum GRAPHICS_IMPLEMENTATION graphicsImplementation(GraphicsClient* _graphics)

void graphicsSafeMode(GraphicsClient* _graphics)

bool graphicsIsModeChangeActive(GraphicsClient* _graphics)

int graphicsWidth(GraphicsClient* _graphics)

int graphicsHeight(GraphicsClient* _graphics)

int graphicsClientWidth(GraphicsClient* _graphics)

int graphicsClientHeight(GraphicsClient* _graphics)

uint8_t** graphicsBackBufferFunction(GraphicsClient* _graphics)

int graphicsUnlockBackBuffer(GraphicsClient* _graphics)

int graphicsLockBackBuffer(GraphicsClient* _graphics)

int graphicsClearBackBuffer(GraphicsClient* _graphics)

int graphicsDrawBackBufferToScreen(GraphicsClient* _graphics, HWND hWindow)

int graphicsSaveOldMode(GraphicsClient* _graphics)

int graphicsRestoreOldMode(GraphicsClient* _graphics)

int graphicsSetBitDepthTo32(GraphicsClient* _graphics)

int graphicsLoadBitmap(GraphicsClient* _graphics, HDC destination, int destinationWidth, int destinationHeight, char* sourceFileName)

int graphicsTermScreenAndBackBufferGDI(GraphicsClient* _graphics)

int graphicsTermScreenAndBackBufferDIRECTDRAW(GraphicsClient* _graphics)

int graphicsTermScreenAndBackBuffer(GraphicsClient* _graphics)

int graphicsInitScreenAndBackBufferGDI(GraphicsClient* _graphics, HWND hWindow)

int graphicsInitScreenAndBackBufferDIRECTDRAW(GraphicsClient* _graphics, HWND hWindow)

int graphicsInitScreenAndBackBuffer(GraphicsClient* _graphics, HWND hWindow)

int graphicsCheckIsFullScreen(GraphicsClient* _graphics)

};
