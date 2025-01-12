//font.cpp
//Robert Aldridge
//all code by Robert

#pragma warning(push,3)

#include <windowsx.h>
#include <ddraw.h>
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

#include "stdtypes.h"

#include "font.h"

#include "font_util.h"

#pragma warning(push,4)

#define FI __forceinline

//ascii contains source rect of characters on font image
static RECT ascii[ 256 ];
//width is screen_width-1, height is screen_height-1
static s32 font_width, font_height, width, height;

static s32 actualWidth, actualHeight, idealWidth, idealHeight;

static s8** backbuffer_array_pointer;

static s8** ( *_backBufferFunction ) ( );

static s8** text_white_array_pointer;

static s8*  text_white;

// FOR DEBUGGING
#ifndef NDEBUG
	static FILE *file       = fopen( "TextOutDebug.txt", "wb" );

	static u32  numErrors   = 0;

	static u32  numWarnings = 0;
#endif
//

#define ROBS_FONT

#include "font_util.cpp"

#undef ROBS_FONT

static FI const u32 GetIdealFontWidth () { return 10; }
static FI const u32 GetIdealFontHeight() { return 14; }

extern "C" extern void TextOutInitSystem( s8** ( *__backBufferFunction ) ( ),
							              const u32 _width,
							              const u32 _height,
							              const u32 _idealWidth,
							              const u32 _idealHeight
							            )
{
	s32 Column = 0, Row = 0;

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

	actualWidth  = _width;
	actualHeight = _height;

	idealWidth  = _idealWidth;
	idealHeight = _idealHeight;

	width  = _width  - 1;
	height = _height - 1;

	font_width  = ( GetIdealFontWidth()  * actualWidth  ) / idealWidth;
	font_height = ( GetIdealFontHeight() * actualHeight ) / idealHeight;

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

static const u8 CharTrivialAcceptance( const s32 x, const s32 y )
{
	if( x >= 0 && y >= 0 &&
        x + ( font_width - 1 ) <= width && y + ( font_height - 1 ) <= height
      )
	{
		return 1;
	}

	return 0;
}

static void _TextOut( s32 x, s32 y, const s8 * const dest_buffer )
{
	s8 *text = 0;

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

	text = (s8*) dest_buffer;

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
								    &ascii[ (u8) ( ( (s16) (*text) ) + 128 ) ]
								  );
		}
		// clip and blit
		else
		{
			RECT SrcRect = ascii[ (u8) ( ( (s16) (*text) ) + 128 ) ];

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

extern "C" extern void TextOut( s32 x,
					            s32 y,
					            const s8 * const format,...
				              )
{
	s8      dest_buffer[ 514 ] = { 0 };

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

static const RECT _TextOutRect( s32 x, s32 y, const s8 * const dest_buffer )
{
	s8   *text = 0;

	u32  num_newline = 1, chars_per_line = 0, max_chars_per_line = 0;

	RECT output_rect = { -1, -1, -1, -1 };

	if( !backbuffer_array_pointer )
	{
		#ifndef NDEBUG
			Error( " _TextOutRect -> !GetBackBuffer() " );
		#endif

		return output_rect;
	}

	text = (s8*) dest_buffer;

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

	output_rect.left   = x;
	output_rect.top    = y;
	output_rect.right  = x + font_width  * max_chars_per_line - 1;
	output_rect.bottom = y + font_height * num_newline        - 1;

	return output_rect;
}

extern "C" extern const RECT TextOutRect( s32 x,
							              s32 y,
						                  const s8 * const format,...
							            )
{
	s8      dest_buffer[ 514 ] = { 0 };

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