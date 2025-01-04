
// blah_aligned_alloc.cpp
// Robert Aldridge

#include <cstddef> // ptrdiff_t, size_t
#include <cstdint> // uint8_t
#include <cstdlib> // malloc
#include <cstring> // memset

#include <new> // bad_alloc
using std::bad_alloc;
using std::malloc;
using std::memset;
using std::ptrdiff_t;
using std::size_t;
using std::uint8_t;

#include "blah_aligned_alloc.h"

// alignment is typically sizeof(void*)
// assumes size is already a multiple of alignment
// pass result of malloc_size_padded as size parameter to malloc to allow for post-malloc alignment
static size_t malloc_size_padded(size_t size)
{
  size_t result = size + (sizeof(void*) - 1);

  return result;
}

// alignment is typically sizeof(void*)
// assumes the parameter passed to malloc is sufficiently padded
// ptr is of type uint8_t*
// 'address' is of type ptrdiff_t, assigned to the value (uint8_t*)ptr - (uint8_t*)0
// pass return value of malloc to malloc_return_align (pass stored value not the literal malloc call)
static uint8_t* malloc_return_align(uint8_t* unaligned, ptrdiff_t address)
{
  uint8_t* result = 0;
  
  if(address % sizeof(void*) )
  {
    result = unaligned + (sizeof(void*) - address % sizeof(void*) );
  }
  else
  {
    result = unaligned;
  }
  
  return result;
}

// when you're forced to use a compiler/runtime that claims to conform yet
// doesn't implement aligned_alloc (*cough* microsoft)
//   void* aligned_alloc(size_t alignment, size_t size)
//
// in this case assume alignment is sizeof(void*)
uint8_t* blah_aligned_alloc(size_t size, uint8_t** reference, bool clear)
{
  uint8_t* aligned = 0;
  uint8_t* unaligned = 0;

  ptrdiff_t address = 0;

  if( !size || !reference)
    goto error;

  // fail if size is not a multiple of alignment
  if(size % sizeof(void*) )
    goto error;

  size = malloc_size_padded(size);

  try
  {
    unaligned = (uint8_t*)malloc(size);
  }
  catch(bad_alloc& )
  {
    unaligned = 0;
  }

  if( !unaligned)
    goto error;

  *reference = unaligned;

  address = (uint8_t*)unaligned - (uint8_t*)0;

  aligned = malloc_return_align(unaligned, address);
  
  if(clear)
    memset(aligned, 0, size);

error:
  return aligned;
}
