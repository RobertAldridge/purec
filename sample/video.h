// video.h
//
// video utility functions
//
// Robert Aldridge

// OS DEPENDANT CODE

// ALWAYS CALL LinearFrameBufferOSSetBackBuffer AT START OF PROGRAM
// AND WHEN RELOADING BETWEEN SCREEN MODES

extern void __LinearFrameBufferOSSetBackBuffer( uint8_t** ( *__backBufferFunction ) ( ),
                          uint16_t BackBufferViewPortWidth,
                          uint16_t BackBufferViewPortHeight
                        );

extern unsigned short __LinearFrameBufferGetWidth();
extern unsigned short __LinearFrameBufferGetHeight();
