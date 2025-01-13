// video.h
//
// video utility functions
//
// Robert Aldridge

// OS DEPENDANT CODE

// ALWAYS CALL LinearFrameBufferOSSetBackBuffer AT START OF PROGRAM
// AND WHEN RELOADING BETWEEN SCREEN MODES

#ifdef __cplusplus
	extern "C" {
#endif

extern void __LinearFrameBufferOSSetBackBuffer( uint8_t** ( *backBufferFunction ) ( ),
											    unsigned short BackBufferViewPortWidth,
											    unsigned short BackBufferViewPortHeight
											  );

extern __forceinline const unsigned short __LinearFrameBufferGetWidth();
extern __forceinline const unsigned short __LinearFrameBufferGetHeight();

#ifdef __cplusplus
	}
#endif