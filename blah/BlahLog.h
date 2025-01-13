
// BlahLog.h

void BlahLogLevel2(const char* file, int line, const char* format, ...);

#define BlahLog(...) BlahLogLevel2(__FILE__, (int)__LINE__, __VA_ARGS__)
