
// font.h
// Robert Aldridge

// Creates a white font
// when RobsTextOutInitSystem is first called.
//
// Currently works for 32 bit ARGB only.


// None of the RobsTextOut functions handle tabs.

// The maximum string length that will be handled is always
// 512.  Longer strings will be truncated.

// Initializes the font system.
//
// By default, RobsTextOutInitSystem does not load any fonts.
//
// Any fonts which were released by a previous call to RobsTextOutTermSystem
// will be allocated again.
//
// The ideal_backbuffer_width and ideal_backbuffer_height specify
// the width and height of the program's viewport in which the text
// output on the screen matches pixel for pixel with the source font
// image width and height.
//
// When the actual and ideal match, it means no scaling occurs when loading
// font images from disk.  It also means exact pixel for pixel equality.
//
// When the actual and ideal do not match, the font images will be scaled
// during font initialization to match the original aspect ratio of
// font size to screen size.  All input and output is in the ideal frame of
// reference.  Coordinate conversion is handled internally by RobsTextOut.
extern FontBlah* RobsTextOutInitSystem(uint8_t** (*backBufferFunction)(), const uint32_t width, const uint32_t height, const uint32_t idealWidth, const uint32_t idealHeight);

// The main RobsTextOut function prints clipped characters
// to the backbuffer.  Characters do not wrap to the next line.
// Use newline for that.

// The x and y specify the upper-left corner pixel of the first
// character being printed.  The format string works just like
// printf
//
// If the type has not been allocated, it will be when RobsTextOut
// is called.  RobsTextOut will do nothing if RobsTextOutInitSystem
// has not been called.
extern void RobsTextOut(void* _this, int32_t x, int32_t y, const char* const format, ...);

// Returns a rect with the upper left and lower right pixel coordinates
// that contain the text which would be printed if RobsTextOut were called
// with the same arguments.
//
// The rect is in pixel coordinates, so a 10 by 10 at (100,100)
// would be {100,100,109,109}
//
// To get the current font's width and height, call rect = RobsTextOutRect(0,0," ").
// Then the contents of the rect will be {0,0,currentFontWidth-1,currentFontHeight-1}.
//
// RobsTextOutRect will return { -1, -1, -1, -1} if RobsTextOutInitSystem
// has not been called.
extern rect RobsTextOutRect(FontBlah* _this, int32_t x, int32_t y, const char* const format, ...);

// Terminates the font system and releases all allocated fonts.
//
// All released fonts will be reloaded on the next call to RobsTextOutInitSystem
extern void RobsTextOutTermSystem(FontBlah** _this);
