
// header.h

#define countof(x) (sizeof(x) / sizeof(x[0] ) )

//typedef struct HDC__* HDC;

struct FontBlah;

struct LIST_HEAD;

union CLIENT_POTYPE;

struct PARTICLE;

struct EMITTER;

struct PARTICLE_SYSTEMS_HEAD;

struct COLOR;

struct VECTOR;

struct point
{
  int x;
  int y;
};

struct rect
{
  int left;
  int top;
  int right;
  int bottom;

};
