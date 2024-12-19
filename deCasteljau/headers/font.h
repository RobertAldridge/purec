// font.h
// Robert Aldridge

#undef TextOut
#define TextOut RobsTextOut

#ifdef __cplusplus
	extern "C" {
#endif

// Creates a white font
// when TextOutInitSystem is first called.
//
// Currently works for 32 bit ARGB only.


// None of the TextOut functions handle tabs.

// The maximum string length that will be handled is always
// 512.  Longer strings will be truncated.

// Initializes the font system.
//
// By default, TextOutInitSystem does not load any fonts.
//
// Any fonts which were released by a previous call to TextOutTermSystem
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
// reference.  Coordinate conversion is handled internally by TextOut.
extern void TextOutInitSystem( char** ( *backBufferFunction ) ( ),
							   const unsigned int actual_backbuffer_width,
							   const unsigned int actual_backbuffer_height,
							   const unsigned int ideal_backbuffer_width,
							   const unsigned int ideal_backbuffer_height
							 );

// The main TextOut function prints clipped characters
// to the backbuffer.  Characters do not wrap to the next line.
// Use newline for that.

// The x and y specify the upper-left corner pixel of the first
// character being printed.  The format string works just like
// printf.
//
// If the type has not been allocated, it will be when TextOut
// is called.  TextOut will do nothing if TextOutInitSystem
// has not been called.
extern void TextOut( int x,
					 int y,
					 const char * const format,...
				   );

// Returns a RECT with the upper left and lower right pixel coordinates
// that contain the text which would be printed if TextOut were called
// with the same arguments.
//
// The RECT is in pixel coordinates, so a 10 by 10 at (100,100)
// would be {100,100,109,109}
//
// To get the current font's width and height, call rect = TextOutRect(0,0," ").
// Then the contents of the rect will be {0,0,currentFontWidth-1,currentFontHeight-1}.
//
// TextOutRect will return {-1,-1,-1,-1} if TextOutInitSystem
// has not been called.
extern const RECT TextOutRect( int x,
							   int y,
						      const char * const format,...
							 );

// Terminates the font system and releases all allocated fonts.
//
// All released fonts will be reloaded on the next call to TextOutInitSystem
extern void TextOutTermSystem(
							 );

#ifdef __cplusplus
	}
#endif