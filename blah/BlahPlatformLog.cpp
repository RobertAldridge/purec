
// BlahAlloc.cpp
// Robert Aldridge

#if defined(_MSC_VER)
  #include <windows.h>
#endif

#include "BlahPlatformLog.h"

bool BlahPlatformLogIsEnabled()
{
  bool result = false;

#if defined(_MSC_VER)
  result = true;
#endif

  return result;
}

void BlahPlatformLog(const char* output)
{
#if defined(_MSC_VER)
  OutputDebugStringA(output);
#endif
}
