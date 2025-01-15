
// font.cpp
// Robert Aldridge
// all code by Robert

//#include <windowsx.h>

//#pragma warning (disable : 4820)
//#include <ddraw.h>
//#pragma warning (default : 4820)

#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstdint>
#include <cstring>

#include "font.h"

#include "font_util.h"

#include "BlahAlloc.h"

struct FontBlah
{

//ascii contains source rect of characters on font image
rect ascii[ 256 ];
//width is screen_width-1, height is screen_height-1
int32_t font_width, font_height, width, height;

int32_t actualWidth, actualHeight, idealWidth, idealHeight;

uint8_t** backbuffer_array_pointer;

uint8_t** ( *_backBufferFunction ) ( );

uint8_t** text_white_array_pointer;

uint8_t*  text_white;

// FOR DEBUGGING
#ifndef NDEBUG
	FILE* file;

	uint32_t  numErrors;

	uint32_t  numWarnings;
#endif
//

};

static uint32_t GetIdealFontWidth() { return 10; }
static uint32_t GetIdealFontHeight() { return 14; }

extern FontBlah* RobsTextOutInitSystem( uint8_t** ( *__backBufferFunction ) ( ),
							              const uint32_t _width,
							              const uint32_t _height,
							              const uint32_t _idealWidth,
							              const uint32_t _idealHeight
							            )
{
	int32_t Column = 0;
  int32_t Row = 0;

  FontBlah* _this = 0;
  
  _this = (FontBlah*)BlahAlloc(sizeof(FontBlah), true);
  if( !_this)
    goto label_error;

#ifndef NDEBUG
  _this->file = fopen( "TextOutDebug.txt", "wb" );
  if( !_this->file )
    goto label_error;
#endif

  if( (!__backBufferFunction) )
  {
#ifndef NDEBUG
    FontUtilError(_this, " TextOutInitSystem -> !__backBufferFunction " );
#endif
    goto label_error;
  }

  if( _width <= 0 )
  {
#ifndef NDEBUG
    FontUtilError(_this, " TextOutInitSystem -> _width <= 0 " );
#endif
    goto label_error;
  }

  if( _height <= 0 )
  {
#ifndef NDEBUG
    FontUtilError(_this, " TextOutInitSystem -> _height <= 0 " );
#endif
    goto label_error;
  }

	_this->_backBufferFunction = __backBufferFunction;

	_this->backbuffer_array_pointer = _this->_backBufferFunction();

	_this->actualWidth  = (int32_t)_width;
	_this->actualHeight = (int32_t)_height;

	_this->idealWidth  = (int32_t)_idealWidth;
	_this->idealHeight = (int32_t)_idealHeight;

	_this->width  = (int32_t)_width  - 1;
	_this->height = (int32_t)_height - 1;

	_this->font_width  = ( (int32_t)GetIdealFontWidth()  * _this->actualWidth  ) / _this->idealWidth;
	_this->font_height = ( (int32_t)GetIdealFontHeight() * _this->actualHeight ) / _this->idealHeight;

	FontUtilLoadBitmap(_this);

	Row = 0;

	do
	{
		Column = 0;

		do
		{
			_this->ascii[ Row * 16 + Column ].left   = Column * _this->font_width;

			_this->ascii[ Row * 16 + Column ].top    = Row    * _this->font_height;

			_this->ascii[ Row * 16 + Column ].right  = Column * _this->font_width  + _this->font_width;

			_this->ascii[ Row * 16 + Column ].bottom = Row    * _this->font_height + _this->font_height;

		}while( ++Column != 16 );

	}while( ++Row != 16 );

  goto label_return;
  
label_error:
  if(_this)
  {
#ifndef NDEBUG
    if(_this->file)
    {
      fclose(_this->file);
      _this->file = 0;
    }
#endif

    //BlahFree(_this, sizeof(FontBlah), true);
    _this = 0;
  }

label_return:
  return _this;
}

static uint8_t CharTrivialAcceptance( FontBlah* _this, const int32_t x, const int32_t y )
{
  if( !_this)
    return 0;
  
	if( x >= 0 && y >= 0 &&
        x + ( _this->font_width - 1 ) <= _this->width && y + ( _this->font_height - 1 ) <= _this->height
      )
	{
		return 1;
	}

	return 0;
}

static void _RobsTextOut(FontBlah* _this, int32_t x, int32_t y, const char * const dest_buffer )
{
	char *text = 0;
  
  if( !_this)
    return;

	if( !_this->_backBufferFunction )
	{
		#ifndef NDEBUG
			FontUtilError(_this, " TextOutLightGray -> !_backBufferFunction() " );
		#endif

		return;
	}

	_this->backbuffer_array_pointer = _this->_backBufferFunction();

	if( (!_this->backbuffer_array_pointer) || ( !(*_this->backbuffer_array_pointer) ) )
	{
		#ifndef NDEBUG
			FontUtilError(_this, " TextOutLightGray -> !GetBackBuffer() " );
		#endif

		return;
	}

	if( (!_this->text_white) || (!_this->text_white_array_pointer) || ( !(*_this->text_white_array_pointer) ) )
	{
		#ifndef NDEBUG
			FontUtilError(_this, " TextOutLightGray -> !GetTextLightGrayBuffer() " );
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

			y += _this->font_height;

			++text;

			continue;
		}
		// trivial rejection
		if( y > _this->height )
			return;
		// trivial rejection
		if( x > _this->width || x + ( _this->font_width - 1 ) < 0 || y + ( _this->font_height - 1 ) < 0 )
		{
			x += _this->font_width;

			++text;

			continue;
		}
		// trivial acceptance and blit
		else if( CharTrivialAcceptance( _this, x, y ) )
		{
			FontUtilCharAntiAliasColorBlit( _this->backbuffer_array_pointer,
								    _this->text_white_array_pointer,
								    x,
								    y,
								    &_this->ascii[ (uint8_t) ( ( (int16_t) (*text) ) + 128 ) ]
								  );
		}
		// clip and blit
		else
		{
			rect SrcRect = _this->ascii[ (uint8_t) ( ( (int16_t) (*text) ) + 128 ) ];

			// checks output from FontUtilClipSpecial
			if(FontUtilClipSpecial( &x, &y, _this->width, _this->height, &SrcRect) )
			{
				FontUtilCharAntiAliasColorBlit( _this->backbuffer_array_pointer,
									    _this->text_white_array_pointer,
										x,
										y,
										&SrcRect
									  );
			}
		}

		x += _this->font_width;

		++text;
	}
}

extern void RobsTextOut(void* reference, int32_t x,
					            int32_t y,
					            const char * const format,...
				              )
{
  FontBlah* _this = (FontBlah*)reference;
  
  if( !_this)
    return;

	char dest_buffer[514] = {0};

	va_list argptr = 0;

	#ifndef NDEBUG
		if( !format )
		{
			FontUtilError(_this, " TextOut -> !format " );
			return;
		}
		if( !(*format) )
		{
			FontUtilWarning(_this, " TextOut -> !(*format) " );
			return;
		}
	#else
		if( !format || !(*format) )
			return;
	#endif

	va_start( argptr, format );

	// convert format string and argument list into one string
	vsnprintf( dest_buffer, 512, format, argptr );

	x = ( x * _this->actualWidth  ) / _this->idealWidth;
	y = ( y * _this->actualHeight ) / _this->idealHeight;

	_RobsTextOut( _this, x, y, dest_buffer );
}

static const rect _RobsTextOutRect( FontBlah* _this, int32_t x, int32_t y, const char * const dest_buffer )
{
	char   *text = 0;

	uint32_t  num_newline = 1, chars_per_line = 0, max_chars_per_line = 0;

	rect output_rect = { -1, -1, -1, -1 };
  
  if( !_this)
    return output_rect;

	if( !_this->backbuffer_array_pointer )
	{
		#ifndef NDEBUG
			FontUtilError(_this, " _TextOutRect -> !GetBackBuffer() " );
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
	output_rect.right = (long)(x + _this->font_width * max_chars_per_line - 1);
	output_rect.bottom = (long)(y + _this->font_height * num_newline - 1);

	return output_rect;
}

extern const rect RobsTextOutRect( FontBlah* _this, int32_t x,
							              int32_t y,
						                  const char * const format,...
							            )
{
	char dest_buffer[ 514 ] = { 0 };

	va_list argptr = 0;

	rect    output_rect = { -1, -1, -1, -1 };
  
  if( !_this)
    return output_rect;

	#ifndef NDEBUG
		if( !format )
		{
			FontUtilError(_this, " TextOutRect -> !format " );
			return output_rect;
		}
		if( !(*format) )
		{
			FontUtilWarning(_this, " TextOutRect -> !(*format) " );
			return output_rect;
		}
	#else
		if( !format || !(*format) )
			return output_rect;
	#endif

	va_start( argptr, format );

	// convert format string and argument list into one string
	_vsnprintf( dest_buffer, 512, format, argptr );

	x = ( x * _this->actualWidth  ) / _this->idealWidth;
	y = ( y * _this->actualHeight ) / _this->idealHeight;

	output_rect = _RobsTextOutRect( _this, x, y, dest_buffer );

	if( output_rect.left  == -1 && output_rect.top    == -1 &&
	    output_rect.right == -1 && output_rect.bottom == -1
      )
	{
		#ifndef NDEBUG
			FontUtilWarning(_this, " TextOutRect -> output_rect == {-1,-1,-1,-1} ( output_rect is off screen ) " );
		#endif

		return output_rect;
	}

	output_rect.left  = ( output_rect.left  * _this->idealWidth ) / _this->actualWidth;
	output_rect.right = ( output_rect.right * _this->idealWidth ) / _this->actualWidth;

	output_rect.top    = ( output_rect.top    * _this->idealHeight ) / _this->actualHeight;
	output_rect.bottom = ( output_rect.bottom * _this->idealHeight ) / _this->actualHeight;

	return output_rect;
}

extern void RobsTextOutTermSystem(FontBlah** reference
							            )
{
  FontBlah* _this = 0;
  
  if( !reference)
    return;
  
  _this = reference[0];
  
  if( !_this)
    return;
  
	if( _this->text_white_array_pointer )
	{
    BlahFree(_this->text_white_array_pointer, sizeof(uint8_t*) * 224, true);
		_this->text_white_array_pointer = 0;
	}
	#ifndef NDEBUG
  else
  {
    FontUtilError(_this, " TextOutTermSystem -> text_white_array_pointer == NULL " );
  }
	#endif

	if( _this->text_white )
	{
    BlahFree(_this->text_white, sizeof(uint8_t) * 160 * 224 * 4, true);
		_this->text_white = 0;
	}
	#ifndef NDEBUG
  else
  {
    FontUtilError(_this, " TextOutTermSystem -> text_white == NULL " );
  }
	#endif

	if( _this->backbuffer_array_pointer )
	{
	    _this->backbuffer_array_pointer = 0;
	}
	#ifndef NDEBUG
  else
  {
    FontUtilError(_this, " TextOutTermSystem -> backbuffer_array_pointer == NULL " );
  }
	#endif
	
  #ifndef NDEBUG
  if(_this->file)
  {
    fclose(_this->file);
    _this->file = 0;
  }
  #endif
  
  BlahFree(_this, sizeof(FontBlah), true);
  _this = 0;
  
  reference[0] = 0;
}