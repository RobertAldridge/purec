
// BlahLog.h

void BlahLog1Level2(const char* file, int line, const char* format, ...);

void BlahLog2Level2(const char* file, int line, const char* format, ...);

#define BlahLog(...) BlahLog1Level2(__FILE__, (int)__LINE__, __VA_ARGS__)

#define BlahLog2(...) BlahLog2Level2(__FILE__, (int)__LINE__, __VA_ARGS__)
