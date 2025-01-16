
// BlahLog.cpp
// Robert Aldridge

#include <cctype>
#include <cstdarg>
#include <cstdio>
#include <cstring>

using namespace std;

// tolower
// snprintf
// strncat_s
// va_list
// va_start
// va_end
// vsnprintf_s

#include "BlahLog.h"

#include "BlahPlatformLog.h"

int Error(const char* const errorString);
int Warning(const char* const warningString);
int Verbose(const char* const verboseString);

void BlahLog1Level2(const char* file, int line, const char* format, ...)
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

if(BlahPlatformLogIsEnabled() )
//BlahPlatformLog(destination);
//Warning(destination);
  Verbose(destination);
else
  printf("%s", destination);
}

void BlahLog2Level2(const char* file, int line, const char* format, ...)
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

if(BlahPlatformLogIsEnabled() )
  BlahPlatformLog(destination);
else
  printf("%s", destination);
}