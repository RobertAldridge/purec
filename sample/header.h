
// header.h

#define countof(x) (sizeof(x) / sizeof(x[0] ) )

struct FontBlah;

struct LIST_HEAD;

union CLIENT_POTYPE;

struct PARTICLE;

struct EMITTER;

struct PARTICLE_SYSTEMS_HEAD;

struct COLOR;

struct VECTOR;

struct rect
{
  int left;
  int top;
  int right;
  int bottom;
};

#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <cwctype>

//#include <stdnoreturn.h>
//#include <threads.h>
