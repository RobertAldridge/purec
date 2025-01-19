
// fontUtil.h

// StartX; input is old dest x, output is new dest x
// StartY; input is old dest y, output is new dest y
// _rect; input is old source rectInteger, output is new source rectInteger
extern bool FontUtilClipSpecial(int* StartX, int* StartY, int width, int height, rectInteger* _rect);

extern void FontUtilCopyBitmap(FontBlah* _this, void* Source, int sourceWidth, int sourceHeight);

extern void FontUtilLoadBitmap(FontBlah* _this);

extern void FontUtilCharAntiAliasColorBlit(uint8_t** backbuffer, uint8_t** textbuffer, int xDst, int yDst, rectInteger* _RectSrc);
