

#ifndef NDEBUG
	static void Error( const s8 * const errorString );

	static void Warning( const s8 * const warningString );
#endif

static void
LoadBitmap(
		  );

static unsigned char
ClipSpecial( int  *StartX, // input is old dest x, output is new dest x
			 int  *StartY, // input is old dest y, output is new dest y
		     int  width,
			 int  height,
			 RECT *rect    // input is old source rect, output is new source rect
		   );

#define CharClip(x,y,rect) ClipSpecial( x, y, width, height, rect )