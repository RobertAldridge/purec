

#ifdef ROBS_FONT

// UTILITY FUNCTIONS TO COMPILE LIBRARY

#ifndef NDEBUG
	static void Error( const s8 * const errorString
					 )
	{
		if( file )
		{	
			++numErrors;
			
			fprintf( file, " Error#  : %i\n",   numErrors );

			fprintf( file, " Error   : %s\n\n", errorString );
		}
	}

	static void Warning( const s8 * const warningString
					   )
	{
		if( file )
		{	
			++numWarnings;
			
			fprintf( file, " Warning#: %i\n",   numWarnings   );

			fprintf( file, " Warning : %s\n\n", warningString );
		}
	}
#endif

static unsigned char
ClipSpecial( int  *StartX, // input is old dest x, output is new dest x
			 int  *StartY, // input is old dest y, output is new dest y
			 int  width,
			 int  height,
			 RECT *rect    // input is old source rect, output is new source rect
		   )
{
	#define StartX (*StartX)
	#define StartY (*StartY)

	int SrcWidth         = rect->right  - rect->left + 1;
	int SrcHeight        = rect->bottom - rect->top  + 1;
	//
	int DestWidth        = SrcWidth;
	int DestHeight       = SrcHeight;
	int SourceWidth      = 0;
	int Xstart           = 0;
	int Ystart           = 0;
	int BackBufferWidth  = width  + 1;
	int BackBufferHeight = height + 1;

	// trivial reject
	if( StartX <= -SrcWidth  || StartX > BackBufferWidth  - 1 ||
        StartY <= -SrcHeight || StartY > BackBufferHeight - 1
      )
	{
		StartX       = -1;
		StartY       = -1;
		rect->left   = -1;
		rect->top    = -1;
		rect->right  = -1;
		rect->bottom = -1;

		return FALSE;
	}

	if (StartX < 0) 
	{
		Xstart     = -StartX;
		DestWidth -=  Xstart;
	}

	if( StartY < 0 )
	{
		Ystart      = -StartY;
		DestHeight -=  Ystart;
	}
	
	if( SrcWidth + StartX > BackBufferWidth )
	{
		DestWidth   -= ( SrcWidth + StartX ) - BackBufferWidth;
		SourceWidth  = ( SrcWidth + StartX ) - BackBufferWidth;
	}

	if( SrcHeight + StartY > BackBufferHeight )
	{
		DestHeight -= ( SrcHeight + StartY ) - BackBufferHeight;
	}

	if( StartX < 0 )
	{
        StartX = 0;
	}

	if( StartY < 0 )
	{
		StartY = 0;
	}

	#undef StartY
	#undef StartX

	rect->left += Xstart;
	rect->top  += Ystart;

	rect->right  = rect->left + DestWidth  - 1;
	rect->bottom = rect->top  + DestHeight - 1;

	return TRUE;
}

static void CopyBitmap( HDC Source,
	                    int sourceWidth,
	                    int sourceHeight
                      )
{
	HDC		BltDC;

	HBITMAP BltHB;

	HGDIOBJ CleanUp;

	BltDC = CreateCompatibleDC( 0 );

	if( BltDC == NULL )
	{
		#ifndef NDEBUG
			Error( " ( BltDC = CreateCompatibleDC(...) ) == NULL " );
		#endif

		return;
	}

	BltHB = (HBITMAP) LoadImage( NULL,
								 "ascii_white.bmp",
								 IMAGE_BITMAP,
								 0,
								 0,
								 LR_LOADFROMFILE | LR_CREATEDIBSECTION
							   );

	if( BltHB == NULL )
	{
		#ifndef NDEBUG
			Error( " ( BltHB = LoadImage(...) ) == NULL " );
		#endif

		if( !DeleteDC( BltDC ) )
		{
			#ifndef NDEBUG
				Error( " DeleteDC(...) function failure " );
			#endif
		}

		return;
	}

	CleanUp = SelectObject( BltDC, BltHB );

	if( CleanUp == NULL || ( (const unsigned long) CleanUp ) == GDI_ERROR )
	{
		#ifndef NDEBUG
			Error( " ( CleanUp = SelectObject(...) ) == NULL " );
		#endif

		if( !DeleteObject( BltHB ) )
		{
			#ifndef NDEBUG
				Error( " DeleteObject(..) function failure " );
			#endif
		}

		if( !DeleteDC( BltDC ) )
		{
			#ifndef NDEBUG
				Error( " DeleteDC(...) function failure " );
			#endif
		}

		return;
	}

	if(     !BitBlt
		    (
				Source,
				0,
				0,
				sourceWidth,
				sourceHeight,
				BltDC,
				0,
				0,
				SRCCOPY
			)
	  )
	{
		#ifndef NDEBUG
			Error( " BitBlt failure " );
		#endif
	}

	HGDIOBJ deviceTempCleanUp = 0;

	if( BltDC != 0 )
	{
		/* free all gdi */

		deviceTempCleanUp = SelectObject( BltDC, CleanUp );

		if( deviceTempCleanUp == NULL || ( (const unsigned long) deviceTempCleanUp ) == GDI_ERROR )
		{
			#ifndef NDEBUG
				Error( " ( deviceTempCleanUp = SelectObject(...) ) == NULL " );
			#endif
		}

		if( !DeleteObject( BltHB ) )
		{
			#ifndef NDEBUG	
				Error( " DeleteObject(..) function failure " );
			#endif
		}

		if( !DeleteDC( BltDC ) )
		{
			#ifndef NDEBUG
				Error( " DeleteDC(...) function failure " );
			#endif
		}
	}	
}

static void
LoadBitmap(
		  )
{
	int        loop     =   0;

	int        *tempMem =   0;

	BITMAPINFO bInfo    = { 0 };

	HDC     deviceIndependentDC       = 0;

	HBITMAP deviceIndependentBitmapHB = 0;

	HGDIOBJ deviceIndependentCleanUp  = 0;

	bInfo.bmiHeader.biBitCount	  = 32;
	bInfo.bmiHeader.biWidth		  = 160;
	bInfo.bmiHeader.biHeight	  = 224;
	bInfo.bmiHeader.biPlanes	  = 1;
	bInfo.bmiHeader.biSize		  = sizeof( BITMAPINFOHEADER );
	bInfo.bmiHeader.biCompression = BI_RGB;

	/* create the permanent container */

	deviceIndependentDC = CreateCompatibleDC( 0 );

	if( deviceIndependentDC == NULL )
	{
		#ifndef NDEBUG
			Error( " ( deviceIndependentDC = CreateCompatibleDC(...) ) == NULL " );
		#endif

		return;
	}

	/* create bitmap */

	text_white = (char*) malloc( 160 * 224 * 4 );

	text_white_array_pointer = (char**) malloc( sizeof(char*) * 224 );

	if( (!text_white) || (!text_white_array_pointer) )
	{
		#ifndef NDEBUG
			Error( " malloc(...) == NULL " );
		#endif

		if( !DeleteDC( deviceIndependentDC ) )
		{
			#ifndef NDEBUG
				Error( " DeleteDC(...) function failure " );
			#endif
		}

		if( text_white )
		{
			free( text_white );

			text_white = 0;
		}

		if( text_white_array_pointer )
		{
			free( text_white_array_pointer );

			text_white_array_pointer = 0;
		}

		deviceIndependentDC = 0;

		return;
	}

	deviceIndependentBitmapHB = CreateDIBSection( deviceIndependentDC, 
												  &bInfo,
												  DIB_RGB_COLORS,
												  (void**) &tempMem,
												  0,
												  0
												);

	if( deviceIndependentBitmapHB == NULL || tempMem == NULL )
	{
		#ifndef NDEBUG
			Error( " ( deviceIndependentBitmapHB = CreateDIBSection(...) ) == NULL " );
		#endif

		if( !DeleteDC( deviceIndependentDC ) )
		{
			#ifndef NDEBUG
				Error( " DeleteDC(...) function failure " );
			#endif
		}

		if( text_white )
		{
			free( text_white );

			text_white = 0;
		}

		if( text_white_array_pointer )
		{
			free( text_white_array_pointer );

			text_white_array_pointer = 0;
		}

		deviceIndependentDC = 0;

		return;
	}

	/* permanent container */

	deviceIndependentCleanUp = SelectObject( deviceIndependentDC,
		                                     deviceIndependentBitmapHB
										   );

	if( deviceIndependentCleanUp == NULL || ( (const unsigned long) deviceIndependentCleanUp ) == GDI_ERROR )
	{
		#ifndef NDEBUG
			Error( " ( deviceIndependentCleanUp = SelectObject(...) ) == NULL " );
		#endif

		if( !DeleteObject( deviceIndependentBitmapHB ) )
		{
			#ifndef NDEBUG
				Error( " DeleteObject(..) function failure " );
			#endif
		}

		if( !DeleteDC( deviceIndependentDC ) )
		{
			#ifndef NDEBUG
				Error( " DeleteDC(...) function failure " );
			#endif
		}

		if( text_white )
		{
			free( text_white );

			text_white = 0;
		}

		if( text_white_array_pointer )
		{
			free( text_white_array_pointer );

			text_white_array_pointer = 0;
		}

		deviceIndependentDC       = 0;
		deviceIndependentBitmapHB = 0;

		return;
	}

	CopyBitmap( deviceIndependentDC, 160, 224 );

	memcpy( text_white, tempMem, 160 * 224 * 4 );

	text_white_array_pointer[ 223 ] = text_white;

	// Set up the text buffer pointer array.
	for( loop = 224 - 2; loop >= 0; loop-- )
	{
		text_white_array_pointer[ loop ] =
			text_white_array_pointer[ loop + 1 ] + 160 * 4;
	}

	HGDIOBJ deviceTempCleanUp = 0;

	if( deviceIndependentDC != 0 )
	{
		/* free all gdi */

		deviceTempCleanUp = SelectObject( deviceIndependentDC, deviceIndependentCleanUp );

		if( deviceTempCleanUp == NULL || ( (const unsigned long) deviceTempCleanUp ) == GDI_ERROR )
		{
			#ifndef NDEBUG
				Error( " ( deviceTempCleanUp = SelectObject(...) ) == NULL " );
			#endif
		}

		if( !DeleteObject( deviceIndependentBitmapHB ) )
		{
			#ifndef NDEBUG	
				Error( " DeleteObject(..) function failure " );
			#endif
		}

		if( !DeleteDC( deviceIndependentDC ) )
		{
			#ifndef NDEBUG
				Error( " DeleteDC(...) function failure " );
			#endif
		}

		deviceIndependentDC       = 0;
		deviceIndependentCleanUp  = 0;
		deviceIndependentBitmapHB = 0;
	}
}

static void CharAntiAliasColorBlit( char **backbuffer,
						            char **textbuffer,
						            int  xDst,
						            int  yDst,
						            RECT *_RectSrc
						          )
{
	unsigned char  *Dst = 0,
				   *Src = 0;

	unsigned long SrcRed, SrcGreen, SrcBlue;
	unsigned long ColorSrc;
	unsigned long DstRatio;
	unsigned long SrcRatio;

	short          HeightLoop,
		           Width,
		           WidthLoop;

	RECT           RectDst,
				   RectSrc;

	RectSrc = *_RectSrc;

	RectDst.left   = xDst;
	RectDst.top    = yDst;
	RectDst.right  = xDst + ( RectSrc.right  - RectSrc.left );
	RectDst.bottom = yDst + ( RectSrc.bottom - RectSrc.top  );

	backbuffer = &backbuffer[ RectDst.top ];
	textbuffer = &textbuffer[ RectSrc.top ];

	HeightLoop = (unsigned short) ( RectDst.bottom - RectDst.top  );
	Width      = (unsigned short) ( RectDst.right  - RectDst.left );

	do
	{
		WidthLoop = Width;

		Dst       = ( (unsigned char*) (*backbuffer) ) + ( RectDst.left << 2 );
		Src       = ( (unsigned char*) (*textbuffer) ) + ( RectSrc.left << 2 );
		
		do
		{
			SrcRatio = ( *( (unsigned long*) Src ) ) & 0xff;

			Src += 4;

			if( SrcRatio == 0 )
				Dst += 4;

			else if( SrcRatio == 0xff )
			{
				*( (unsigned long*) Dst ) =  0x00ffffff;

				Dst += 4;
			}

			else
			{
				ColorSrc = *( (unsigned long*) Dst );

				SrcRed   = ( ( ColorSrc << 8  ) >> 24 );
				SrcGreen = ( ( ColorSrc << 16 ) >> 24 );
				SrcBlue  = ( ( ColorSrc << 24 ) >> 24 );

				DstRatio = 0xff - SrcRatio;

				SrcRatio *= 0xff;

				*( (unsigned long*) Dst ) =
					( ( ( SrcRatio + ( SrcRed   * DstRatio ) ) / 0xff ) << 16 ) |
					( ( ( SrcRatio + ( SrcGreen * DstRatio ) ) / 0xff ) << 8  ) |
					  ( ( SrcRatio + ( SrcBlue  * DstRatio ) ) / 0xff );

				Dst += 4;
			}

		}while( --WidthLoop > 0 );

		++backbuffer;
		++textbuffer;

	}while( --HeightLoop > 0 );
}

#endif