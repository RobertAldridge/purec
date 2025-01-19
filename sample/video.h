
// video.h
//
// video utility functions
//
// Robert Aldridge

// os dependant code

// always call __LinearFrameBufferOSSetBackBuffer at start of program
// and when reloading between screen modes

extern void __LinearFrameBufferOSSetBackBuffer(uint8_t** ( *__backBufferFunction )(), uint16_t BackBufferViewPortWidth, uint16_t BackBufferViewPortHeight);

extern unsigned short __LinearFrameBufferGetWidth();

extern unsigned short __LinearFrameBufferGetHeight();
