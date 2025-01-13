
// blah_alloc.cpp
// Robert Aldridge

//#include <cctype>
//#include <cstdarg>
#include <cstdio>

#if defined(_MSC_VER)
  #include <windows.h>
#endif

#include "BlahLog.h"

void BlahLogLevel2(const char* file, int line, const char* format, ...)
{
  char source[514] = {0};
  char destination[514] = {0};

  va_list args;
  va_start(args, format);

  vsnprintf_s(source, countof(source), format, args);

  va_end(args);

  snprintf/*snprintf_s*/(destination, countof(destination), "%s %i ", file, line);

  for(int index = 0; destination[index]; index++)
    destination[index] = (char)tolower(destination[index] );

  strncat_s(destination, countof(destination), source, countof(source) );

#if defined(_MSC_VER)
  OutputDebugStringA(destination);
#else
  printf(destination);
#endif
}
