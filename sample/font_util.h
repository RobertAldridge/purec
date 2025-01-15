
// font_util.h

typedef struct HDC__* HDC;

#ifndef NDEBUG
int FontUtilError(FontBlah* _this, const char* const errorString);

int FontUtilWarning(FontBlah* _this, const char* const warningString);
#endif

// StartX; input is old dest x, output is new dest x
// StartY; input is old dest y, output is new dest y
// rect; input is old source rect, output is new source rect
unsigned char FontUtilClipSpecial(int* StartX, int* StartY, int _width, int _height, rect* rect);

void FontUtilCopyBitmap(FontBlah* _this, HDC Source, int sourceWidth, int sourceHeight);

void FontUtilLoadBitmap(FontBlah* _this);

void FontUtilCharAntiAliasColorBlit(uint8_t** backbuffer, uint8_t** textbuffer, int xDst, int yDst, rect* _RectSrc);
