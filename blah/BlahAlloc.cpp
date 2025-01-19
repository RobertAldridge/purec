
// BlahAlloc.cpp
// Robert Aldridge

//#include <cstdint> // uint32_t
//#include <cstdlib> // free, malloc
//#include <cstring> // memset

//using std::free;
//using std::malloc;
//using std::memset;
//using std::uint32_t;

#include "BlahAlloc.h"

#include "BlahPlatformAlloc.h"

#include "BlahLog.h"

uint32_t BlahAlignedOfValue(uint32_t alignmentOf, uint32_t sizeOf)
{
  return (sizeOf % alignmentOf) ? sizeOf + (alignmentOf - sizeOf % alignmentOf) : sizeOf;
}

void* BlahAlloc(uint32_t sizeOf, bool zero)
{
  void* pointer = 0;

  if( !sizeOf)
    goto label_return;

  if(BlahPlatformAllocIsEnabled() && BlahPlatformAllocIsAcceptable(sizeOf) )
  {
    pointer = BlahPlatformAlloc(sizeOf, zero);
  }
  else
  {
    pointer = malloc(BlahAlignedOfValue(sizeof(void*), sizeOf) );
    if( !pointer)
      goto label_return;

    if(zero)
      memset(pointer, 0, sizeOf);
  }

BlahLog2("1 %i %llu\n", (int)BlahAlignedOfValue(sizeof(void*), sizeOf), (uint64_t)pointer);

label_return:
  return pointer;
}

bool BlahFree(void* pointer, uint32_t sizeOf, bool zero)
{
  bool result = false;

  if( !pointer || !sizeOf)
    goto label_return;

  if(zero)
    memset(pointer, 0, sizeOf);

  if(BlahPlatformAllocIsEnabled() && BlahPlatformAllocIsAcceptable(sizeOf) )
  {
    result = BlahPlatformFree(pointer, sizeOf);
  }
  else
  {
    free(pointer);

    result = true;
  }

label_return:
  return result;
}
