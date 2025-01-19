
// BlahPlatformLog.cpp
// Robert Aldridge

#if 0/*defined(_MSC_VER) */

#include <windows.h>

#else

extern "C"
{

__declspec(dllimport) void __stdcall OutputDebugStringA(const char* lpOutputString);

}

#endif

#include "BlahPlatformLog.h"

bool BlahPlatformLogIsEnabled()
{
  bool result = false;

  result = true;

  return result;
}

void BlahPlatformLog(const char* output)
{
  OutputDebugStringA(output);
}
