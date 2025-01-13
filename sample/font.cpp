//font.cpp
//Robert Aldridge
//all code by Robert

#include <windowsx.h>

#pragma warning (disable : 4820)
#include <ddraw.h>
#pragma warning (default : 4820)

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>

#include "font.h"

#include "font_util.h"

//ascii contains source rect of characters on font image
static RECT ascii[ 256 ];
//width is screen_width-1, height is screen_height-1
static int32_t font_width, font_height, width, height;

static int32_t actualWidth, actualHeight, idealWidth, idealHeight;

static uint8_t** backbuffer_array_pointer;

static uint8_t** ( *_backBufferFunction ) ( );

static uint8_t** text_white_array_pointer;

static uint8_t*  text_white;

// FOR DEBUGGING
#ifndef NDEBUG
	static FILE *file       = fopen( "TextOutDebug.txt", "wb" );

	static uint32_t  numErrors   = 0;

	static uint32_t  numWarnings = 0;
#endif
//

#define ROBS_FONT

#include "font_util.cpp"

#undef ROBS_FONT

static uint32_t GetIdealFontWidth() { return 10; }
static uint32_t GetIdealFontHeight() { return 14; }

extern "C" extern void TextOutInitSystem( uint8_t** ( *__backBufferFunction ) ( ),
							              const uint32_t _width,
							              const uint32_t _height,
							              const uint32_t _idealWidth,
							              const uint32_t _idealHeight
							            )
{
	int32_t Column = 0, Row = 0;

	#ifndef NDEBUG
		if( !file )
			return;

		if( (!__backBufferFunction) )
		{
			Error( " TextOutInitSystem -> !__backBufferFunction " );
			return;
		}
		if( _width <= 0 )
		{
			Error( " TextOutInitSystem -> _width <= 0 " );
			return;
		}
		if( _height <= 0 )
		{
			Error( " TextOutInitSystem -> _height <= 0 " );
			return;
		}
	#else
		if( (!__backBufferFunction) || _width <= 0 || _height <= 0 )
			return;
	#endif

	_backBufferFunction = __backBufferFunction;

	backbuffer_array_pointer = _backBufferFunction();

	actualWidth  = (int32_t)_width;
	actualHeight = (int32_t)_height;

	idealWidth  = (int32_t)_idealWidth;
	idealHeight = (int32_t)_idealHeight;

	width  = (int32_t)_width  - 1;
	height = (int32_t)_height - 1;

	font_width  = ( (int32_t)GetIdealFontWidth()  * actualWidth  ) / idealWidth;
	font_height = ( (int32_t)GetIdealFontHeight() * actualHeight ) / idealHeight;

	LoadBitmap();


	Row = 0;

	do
	{
		Column = 0;

		do
		{
			ascii[ Row * 16 + Column ].left   = Column * font_width;

			ascii[ Row * 16 + Column ].top    = Row    * font_height;

			ascii[ Row * 16 + Column ].right  = Column * font_width  + font_width;

			ascii[ Row * 16 + Column ].bottom = Row    * font_height + font_height;

		}while( ++Column != 16 );

	}while( ++Row != 16 );
}

static uint8_t CharTrivialAcceptance( const int32_t x, const int32_t y )
{
	if( x >= 0 && y >= 0 &&
        x + ( font_width - 1 ) <= width && y + ( font_height - 1 ) <= height
      )
	{
		return 1;
	}

	return 0;
}

static void _TextOut( int32_t x, int32_t y, const char * const dest_buffer )
{
	char *text = 0;

	if( !_backBufferFunction )
	{
		#ifndef NDEBUG
			Error( " TextOutLightGray -> !_backBufferFunction() " );
		#endif

		return;
	}

	backbuffer_array_pointer = _backBufferFunction();

	if( (!backbuffer_array_pointer) || ( !(*backbuffer_array_pointer) ) )
	{
		#ifndef NDEBUG
			Error( " TextOutLightGray -> !GetBackBuffer() " );
		#endif

		return;
	}

	if( (!text_white) || (!text_white_array_pointer) || ( !(*text_white_array_pointer) ) )
	{
		#ifndef NDEBUG
			Error( " TextOutLightGray -> !GetTextLightGrayBuffer() " );
		#endif

		return;
	}

	text = (char*) dest_buffer;

	while( *text != 0 )
	{
		// newline character
		if( *text == 10 )
		{
			x = 0;

			y += font_height;

			++text;

			continue;
		}
		// trivial rejection
		if( y > height )
			return;
		// trivial rejection
		if( x > width || x + ( font_width - 1 ) < 0 || y + ( font_height - 1 ) < 0 )
		{
			x += font_width;

			++text;

			continue;
		}
		// trivial acceptance and blit
		else if( CharTrivialAcceptance( x, y ) )
		{
			CharAntiAliasColorBlit( backbuffer_array_pointer,
								    text_white_array_pointer,
								    x,
								    y,
								    &ascii[ (uint8_t) ( ( (int16_t) (*text) ) + 128 ) ]
								  );
		}
		// clip and blit
		else
		{
			RECT SrcRect = ascii[ (uint8_t) ( ( (int16_t) (*text) ) + 128 ) ];

			// checks output from CharClip
			if( CharClip( &x, &y, &SrcRect ) )
			{
				CharAntiAliasColorBlit( backbuffer_array_pointer,
									    text_white_array_pointer,
										x,
										y,
										&SrcRect
									  );
			}
		}

		x += font_width;

		++text;
	}
}

extern "C" extern void TextOut( int32_t x,
					            int32_t y,
					            const char * const format,...
				              )
{
	char      dest_buffer[ 514 ] = { 0 };

	va_list argptr = 0;

	#ifndef NDEBUG
		if( !format )
		{
			Error( " TextOut -> !format " );
			return;
		}
		if( !(*format) )
		{
			Warning( " TextOut -> !(*format) " );
			return;
		}
	#else
		if( !format || !(*format) )
			return;
	#endif

	va_start( argptr, format );

	// convert format string and argument list into one string
	_vsnprintf( dest_buffer, 512, format, argptr );

	x = ( x * actualWidth  ) / idealWidth;
	y = ( y * actualHeight ) / idealHeight;

	_TextOut( x, y, dest_buffer );
}

static const RECT _TextOutRect( int32_t x, int32_t y, const char * const dest_buffer )
{
	char   *text = 0;

	uint32_t  num_newline = 1, chars_per_line = 0, max_chars_per_line = 0;

	RECT output_rect = { -1, -1, -1, -1 };

	if( !backbuffer_array_pointer )
	{
		#ifndef NDEBUG
			Error( " _TextOutRect -> !GetBackBuffer() " );
		#endif

		return output_rect;
	}

	text = (char*) dest_buffer;

	while( *text != 0 )
	{
		// newline character
		if( *text == 10 )
		{
			++num_newline;

			if( chars_per_line > max_chars_per_line )
				max_chars_per_line = chars_per_line;

			chars_per_line = 0;
		}
		else
			++chars_per_line;

		++text;
	}

	if( chars_per_line > max_chars_per_line )
		max_chars_per_line = chars_per_line;

	output_rect.left = x;
	output_rect.top = y;
	output_rect.right = (long)(x + font_width * max_chars_per_line - 1);
	output_rect.bottom = (long)(y + font_height * num_newline - 1);

	return output_rect;
}

extern "C" extern const RECT TextOutRect( int32_t x,
							              int32_t y,
						                  const char * const format,...
							            )
{
	char dest_buffer[ 514 ] = { 0 };

	va_list argptr = 0;

	RECT    output_rect = { -1, -1, -1, -1 };

	#ifndef NDEBUG
		if( !format )
		{
			Error( " TextOutRect -> !format " );
			return output_rect;
		}
		if( !(*format) )
		{
			Warning( " TextOutRect -> !(*format) " );
			return output_rect;
		}
	#else
		if( !format || !(*format) )
			return output_rect;
	#endif

	va_start( argptr, format );

	// convert format string and argument list into one string
	_vsnprintf( dest_buffer, 512, format, argptr );

	x = ( x * actualWidth  ) / idealWidth;
	y = ( y * actualHeight ) / idealHeight;

	output_rect = _TextOutRect( x, y, dest_buffer );

	if( output_rect.left  == -1 && output_rect.top    == -1 &&
	    output_rect.right == -1 && output_rect.bottom == -1
      )
	{
		#ifndef NDEBUG
			Warning( " TextOutRect -> output_rect == {-1,-1,-1,-1} ( output_rect is off screen ) " );
		#endif

		return output_rect;
	}

	output_rect.left  = ( output_rect.left  * idealWidth ) / actualWidth;
	output_rect.right = ( output_rect.right * idealWidth ) / actualWidth;

	output_rect.top    = ( output_rect.top    * idealHeight ) / actualHeight;
	output_rect.bottom = ( output_rect.bottom * idealHeight ) / actualHeight;

	return output_rect;
}

extern "C" extern void TextOutTermSystem(
							            )
{
	if( text_white_array_pointer )
	{
		free( text_white_array_pointer );

		text_white_array_pointer = 0;
	}
	#ifndef NDEBUG
		else
			Error( " TextOutTermSystem -> text_white_array_pointer == NULL " );
	#endif

	if( text_white )
	{
		free( text_white );

		text_white = 0;
	}
	#ifndef NDEBUG
		else
			Error( " TextOutTermSystem -> text_white == NULL " );
	#endif

	if( backbuffer_array_pointer )
	{
	    backbuffer_array_pointer = 0;
	}
	#ifndef NDEBUG
		else
			Error( " TextOutTermSystem -> backbuffer_array_pointer == NULL " );
	#endif
	
}