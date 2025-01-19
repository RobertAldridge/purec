
// deCasteljau.cpp
//
// Digipen Week 01 -- Mon, Apr 30th - to - Sun, Jun 06th
// Digipen Week 02 -- Mon, May 07th - to - Sun, May 13th
// Digipen Week 03 -- Mon, May 14th - to - Sun, May 20th
// Digipen Week 04 -- Mon, May 21st - to - Sun, May 27th
// Digipen Week 05 -- Mon, May 28th - to - Sun, Jun 03rd
//
// Mon, May 28th, 2001 10:00pm to 02:00am -> 04:00 hrs | 04:00 hrs cum
//
// Tue, May 29th, 2001 11:00am to 02:00pm -> 03:00 hrs | 07:00 hrs cum
// Tue, May 29th, 2001 05:00pm to 01:00am -> 08:00 hrs | 15:00 hrs cum
//
// Wed, May 30th, 2001 09:00pm to 02:00am -> 05:00 hrs | 20:00 hrs cum
//
// Thr, May 31th, 2001 12:00pm to 02:00pm -> 02:00 hrs | 22:00 hrs cum
//
// Digipen Week 06 -- Mon, Jun 04th - to - Sun, Jun 10th
// Digipen Week 07 -- Mon, Jun 11th - to - Sun, Jun 17th
//
// Thr, Jun 14th, 2001 06:00pm to 08:00pm -> 02:00 hrs | 24:00 hrs cum
// Thr, Jun 14th, 2001 11:00pm to 02:00am -> 03:00 hrs | 27:00 hrs cum
//
// Sat, Jun 16th, 2001 12:00am to 02:00am -> 02:00 hrs | 29:00 hrs cum
// Sat, Jun 16th, 2001 05:00pm to 06:00pm -> 01:00 hr  | 30:00 hrs cum
// Sat, Jun 16th, 2001 10:00pm to 05:00am -> 07:00 hrs | 37:00 hrs cum
//
// Sun, Jun 17th, 2001 01:00pm to 06:00pm -> 05:00 hrs | 42:00 hrs cum
// Sun, Jun 17th, 2001 11:00pm to 07:00am -> 08:00 hrs | 50:00 hrs cum
//
// Digipen Week 08 -- Mon, Jun 18th - to - Sun, Jun 24th
//
// Emailed to Michael Jahn Mon, Jun 18th, 2001 11:00 am VERSION 1.0
//
// Fri, Jun 22nd, 2001 03:00pm to 05:00pm -> 02:00 hrs | 52:00 hrs cum
// Sun, Jun 24th, 2001 07:00pm to 02:00am -> 07:00 hrs | 59:00 hrs cum
//
// Digipen Week 09 -- Mon, Jun 25th - to - Sun, Jul 01st
//
// Mon, Jun 25th, 2001 09:00pm to 12:00am -> 03:00 hrs | 62:00 hrs cum
// Wed, Jun 27th, 2001 02:00am to 05:00am -> 03:00 hrs | 65:00 hrs cum
//
// Digipen Week 10 -- Mon, Jul 02nd - to - Sun, Jul 08th
//
// Tue, Jul 03rd, 2001 01:00pm to 02:00pm -> 01:00 hr  | 66:00 hrs cum
//
// Digipen Week 11 -- Mon, Jul 09th - to - Sun, Jul 15th
// Digipen Week 12 -- Mon, Jul 16th - to - Sun, Jul 22nd
// Digipen Week 13 -- Mon, Jul 23rd - to - Sun, Jul 29th
//
// Emailed to Michael Jahn Wed, Jul 25th, 2001 02:00 pm VERSION 1.1
//
// Digipen Week 14 -- Mon, Jul 30rd - to - Sun, Aug 05th
//
// Emailed to Michael Jahn Mon, Jul 30th, 2001 12:00 pm VERSION 1.2

//#include <cassert>
//#include <cmath>
//#include <ctime>
//#include <cstdarg>

//#include <iostream>
#include <deque>
#include <queue>

using std::deque;
using std::pair;
using std::queue;

extern void* operator new(size_t size);

extern void* operator new[](size_t size);

extern void operator delete(void* ptr);

extern void operator delete[](void* ptr);

#if 0
// Epsilon:
//    If num - floor(num)<= E, then num = floor(num).
//    If ceiling(num) - num <= E, then num = ceiling(num).
//
// Both are always true, even when truncating from double to int.
const double E = 0.000001;

// function convert float to int
static int fti(double f) // int deCasteljau::fti(double f)
{
  return ( (f - floor(f) <= E) ? ( (int)floor(f) ) : ( (ceil(f) - f <= E) ? ( (int)ceil(f) ) : ( (int)f) ) );

}

// A little 2D point class, makes stuff easier.
class point // class deCasteljau::point
{

public:

// x and y coordinates of a 2D point with respect to the standard origin.
double x;
double y;

// Easy way to create a point from 2 doubles
point(double _x = 0, double _y = 0) : x(_x), y(_y)
{
}

// Easy way to calculate the Euclidean distance between two points.
double dist(point& pt) const
{
  return sqrt( (x - pt.x) * (x - pt.x) + (y - pt.y) * (y - pt.y) );
}

// Easy way to check if two points correspond to the same pixel.
bool operator== (point& pt)const
{
  return fti(x) == fti(pt.x) && fti(y) == fti(pt.y);
}

bool operator!= (point& pt) const
{
  return fti(x) != fti(pt.x) || fti(y) != fti(pt.y);
}

}; // class deCasteljau::point
#endif

class deCasteljau // class deCasteljau
{

public:

// Epsilon:
//    If num - floor(num)<= E, then num = floor(num).
//    If ceiling(num) - num <= E, then num = ceiling(num).
//
// Both are always true, even when truncating from double to int.
static const double E;

// function convert float to int
static int fti(double f) // int deCasteljau::fti(double f)
{
  return ( (f - floor(f) <= E) ? ( (int)floor(f) ) : ( (ceil(f) - f <= E) ? ( (int)ceil(f) ) : ( (int)f) ) );

} // int deCasteljau::fti(double f)

// A little 2D point class, makes stuff easier.
class point // class deCasteljau::point
{

public:

// x and y coordinates of a 2D point with respect to the standard origin.
double x;
double y;

// Easy way to create a point from 2 doubles
point(double _x = 0, double _y = 0) : x(_x), y(_y)
{
}

// Easy way to calculate the Euclidean distance between two points.
double dist(point& pt) const
{
  return sqrt( (x - pt.x) * (x - pt.x) + (y - pt.y) * (y - pt.y) );
}

// Easy way to check if two points correspond to the same pixel.
bool operator== (point& pt)const
{
  return fti(x) == fti(pt.x) && fti(y) == fti(pt.y);
}

bool operator!= (point& pt) const
{
  return fti(x) != fti(pt.x) || fti(y) != fti(pt.y);
}

}; // class deCasteljau::point

friend point;

typedef pair<point, point> pairQS;
typedef queue<pairQS> queueS;

typedef deque<point> dequeP;
typedef dequeP::iterator iteratorDP;

// This variable t is used to describe F(t), which is
// the point on the curve that shells are shown for,
// the very same point that the program user can choose.
//
// This default value 0.5 is halfway through the curve.
double t;

// r and s define the affine frame(r, s).
double frameR;
double frameS;

// This variable tells the program which control point the user is
// manipulating.  The value can range from 1 to N, N being the current
// number of control points.  The variable contains valid data only
// when the user is manipulating a control point.
int capturedControlPt;

// The number of control points which the user has entered
// is stored in this variable.
int numControlPts;

// How much work to do each update loop is stored in this variable.
int iterateConstant;

// The current de Casteljau stage iteration that must be computed
// for the t of f(t)shells.
int shellT;

// If the shells are visible then this variable is set to true.
bool shellBl;

// If the control points are visible then this variable is set to true.
bool ctrlBl;

unsigned char padding1[6];

// A marker, used to tell the subdivision algorithm which part of
// the curve to render next.  Most importantly, this variable is
// used to iteratively render curve segments less than r and
// greater that s.
double minMaxT;

// This is temp memory used for iterative shell computations for t of f(t).
dequeP shelPt;

// The transformed control points are stored in this list.
dequeP tranPt;

// This is temp memory used for computing intermediate de Casteljau stage points.
dequeP tempPt;

// Iterative subdivision queue.
queueS subdWt;

// The current input position.  Used when calculating the drag distance
// when manipulating control points.  The contents of this variable are
// not always updated/valid, unless needed by the algorithm.
point inputCur;
point inputPrv;

// The minimum and maximum values for t of F(t), used to normalize input for t
// from[minPt, maxPt]to[0, 1], when the user wants to see shells
// for a certain point.  Values are not always current/valid.
//
// Currently only the x coordinate of the points { inputPT, minPt, maxPt } are
// used to determine the actual value of t of F(t).
point minPt;
point maxPt;

// The different colors used for each shell and control point(in RGB).
int colors0[100];
int colors1[100];

double halfWidth;
double halfHeight;

// The function pointer for capture functions, used when the user is
// manipulating the curve.
//
// Currently valid/used when manipulating either the control points or the t value for F(t).
void(deCasteljau::*captureAction)();

// A pointer to a client supplied circle drawing function, set in setPrimitiveDrawingFunctions().
void(*circleDrawingPrimitive)(int xCenter, int yCenter, int radius, int color0RGB, int color1RGB);

// A pointer to a client supplied line segment drawing function, set in setPrimitiveDrawingFunctions().
void(*lineDrawingPrimitive)(int x0, int y0, int x1, int y1, int color0RGB, int color1RGB);

// A pointer to a client supplied point drawing function, set in setPrimitiveDrawingFunctions().
void(*pointDrawingPrimitive)(int x0, int y0, int color0RGB);

//public:

// Initialize the de Casteljau algorithm when the user inputs the
// first control point.
deCasteljau() : t(0.5), frameR(0), frameS(1), capturedControlPt(0), numControlPts(0), iterateConstant(16), shellT(0), shellBl(true), ctrlBl(true), padding1{0}, minMaxT(0), shelPt(), tranPt(), tempPt(), subdWt(), inputCur(0, 0), inputPrv(0, 0), minPt(0, 0), maxPt(0, 0), halfWidth(0.5), halfHeight(0.5), captureAction(0), circleDrawingPrimitive(0), lineDrawingPrimitive(0), pointDrawingPrimitive(0) // deCasteljau::deCasteljau()
{
  // Create some different colors to view the shells and control points with.
  for(int i = 0, c0 = 0, c1 = 0; i < 100; i++)
  {
    do
    {
      // Create random RGB colors, so things look pretty.
      c0 = (rand() % 256) | ( (rand() % 256) << 8) | ( (rand() % 256) << 16);
      c1 = (rand() % 256) | ( (rand() % 256) << 8) | ( (rand() % 256) << 16);

      // Check to make sure the color is not too dark.

    }while( ( (c0 & 0xff) < 0x80 && (c0 & 0xff00) < 0x8000 && (c0 & 0xff0000) < 0x800000) || ( (c1 & 0xff) < 0x80 && (c1 & 0xff00) < 0x8000 && (c1 & 0xff0000) < 0x800000) );

    colors0[i] = c0;
    colors1[i] = c1;
  }

  colors1[0] = colors0[0];

} // deCasteljau::deCasteljau()

// Free dynamic memory allocations when destroying the algorithm instance.
~deCasteljau() // deCasteljau::~deCasteljau()
{
  while( !shelPt.empty() )
  {
    shelPt.clear();
  }

  while( !tranPt.empty() )
  {
    tranPt.clear();
  }

  while( !tempPt.empty() )
  {
    tempPt.clear();
  }

  while( !subdWt.empty() )
  {
    subdWt.pop();
  }

} // deCasteljau::~deCasteljau()

// This function must be called by the client in order for the algorithm to
// visually output the curve F(x), the control points, and the shells for F(t).
void setPrimitiveDrawingFunctions(double _halfWidth, double _halfHeight, void(*_circleDrawingPrimitive)(int, int, int, int, int), void(*_lineDrawingPrimitive)(int, int, int, int, int, int), void(*_pointDrawingPrimitive)(int, int, int) ) // void deCasteljau::setPrimitiveDrawingFunctions(double _halfWidth, double _halfHeight, void(*_circleDrawingPrimitive)(int, int, int, int, int), void(*_lineDrawingPrimitive)(int, int, int, int, int, int), void(*_pointDrawingPrimitive)(int, int, int) )
{
  halfWidth = _halfWidth;
  halfHeight = _halfHeight;

  if(_circleDrawingPrimitive)
  {
    circleDrawingPrimitive = _circleDrawingPrimitive;
  }

  if(_lineDrawingPrimitive)
  {
    lineDrawingPrimitive = _lineDrawingPrimitive;
  }

  if(_pointDrawingPrimitive)
  {
    pointDrawingPrimitive = _pointDrawingPrimitive;
  }

} // void deCasteljau::setPrimitiveDrawingFunctions(double _halfWidth, double _halfHeight, void(*_circleDrawingPrimitive)(int, int, int, int, int), void(*_lineDrawingPrimitive)(int, int, int, int, int, int), void(*_pointDrawingPrimitive)(int, int, int) )

void setPrimitiveDrawingFunctions(deCasteljau& rhs) // void deCasteljau::setPrimitiveDrawingFunctions(deCasteljau & rhs)
{
  halfWidth = rhs.halfWidth;
  halfHeight = rhs.halfHeight;

  if(rhs.circleDrawingPrimitive)
  {
    circleDrawingPrimitive = rhs.circleDrawingPrimitive;
  }

  if(rhs.lineDrawingPrimitive)
  {
    lineDrawingPrimitive = rhs.lineDrawingPrimitive;
  }

  if(rhs.pointDrawingPrimitive)
  {
    pointDrawingPrimitive = rhs.pointDrawingPrimitive;
  }

} // void deCasteljau::setPrimitiveDrawingFunctions(deCasteljau & rhs)

enum INPUT_EVENT // enum deCasteljau::INPUT_EVENT
{
  // When there are no commands being sent to the algorithm,
  // make sure at the very least UPDATE_INPUT is sent with
  // the current input point every update cycle.
  UPDATE_INPUT = 0,

  // The input shown for each command is an example,
  // and not required for the algorithm.
  //
  // Whatever means the client uses for the algorithm input
  // works just fine, as long as the corresponding messages
  // are sent to the deCasteljau::updateInput()function.

  // For F1 mouse commands
  CAPTURE_CONTROL_POINT = 8, // For the F1 mouse left click
  ADD_CONTROL_POINT = 16,    // For the F1 mouse right click

  // For F2 commands
  CAPTURE_T_OF_F_OF_T = 8 | 1,      // For the F2 mouse left click
  DUMP_ALL_CONTROL_POINTS = 16 | 1, // For the F2 mouse right click

  // For F3 commands
  CAPTURE_TRANSLATE = 8 | 2, // For the F3 mouse left click
  CAPTURE_SCALE = 16 | 2,    // For the F3 mouse right click

  // For F4 commands
  CAPTURE_ROTATE = 8 | 4,        // For the F4 mouse left click
  REMOVE_CONTROL_POINT = 16 | 4, // For the F4 mouse right click

  // The F5 command
  TOGGLE_SHELLS = 32,

  // The F6 command
  DUMP_ALL_CAPTURES = 64,

  // The F7 command
  MENU_INPUT = 128,

  // The F8 command may be some helpful popup text
  // describing the algorithm and how to use the program.

  // The F9 command may be some popup text, telling the
  // version of the program and some other stuff.

  // The F10 command may be some undocumented popup text.

  // The #1 undocumented numpad 1 command
  TOGGLE_CONTROL_POINTS = 256,

  // The #2 undocumented numpad + command
  INCREASE_ITERATION_CONSTANT = 512,

  // The #3 undocumented numpad - command
  DECREASE_ITERATION_CONSTANT = 1024,

  // The #4 undocumented numpad 2 command
  ADD_DE_CASTELJAU_CURVE = 2048,

  // The #5 undocumented numpad 3 command
  REMOVE_DE_CASTELJAU_CURVE = 4096,

  // The #6 undocumented numpad 4 command
  TRAVERSE_DE_CASTELJAU_CURVE_LIST = 8192

}; // enum deCasteljau::INPUT_EVENT

// Call this function whenever there is input,
// to update the de Casteljau algorithm.
int updateInput(int inputEvent, double x, double y) // int deCasteljau::updateInput(int inputEvent, double x, double y)
{
  int retVal = 0;

  if( !numControlPts && inputEvent != ADD_CONTROL_POINT && inputEvent != MENU_INPUT)
    goto label_return;

  if(inputEvent != MENU_INPUT)
  {
    inputPrv = inputCur;

    inputCur = point(x, y);
  }

  // Check the input event ; perform input actions
  switch(inputEvent) // switch(inputEvent)
  {

  case UPDATE_INPUT: // switch(inputEvent) UPDATE_INPUT
  {
  }
  break; // switch(inputEvent) UPDATE_INPUT

  case CAPTURE_CONTROL_POINT: // switch(inputEvent) CAPTURE_CONTROL_POINT
  {
    retVal = 1;
    dumpAllCaptures();
    captureControlPoint();
  }
  break; // switch(inputEvent) CAPTURE_CONTROL_POINT

  case ADD_CONTROL_POINT: // switch(inputEvent) ADD_CONTROL_POINT
  {
    retVal = 1;
    dumpAllCaptures();
    addControlPoint();
  }
  break; // switch(inputEvent) ADD_CONTROL_POINT

  case CAPTURE_T_OF_F_OF_T: // switch(inputEvent) CAPTURE_T_OF_F_OF_T
  {
    retVal = 1;
    dumpAllCaptures();
    capture_t_of_F_of_t();
  }
  break; // switch(inputEvent) CAPTURE_T_OF_F_OF_T

  case DUMP_ALL_CONTROL_POINTS: // switch(inputEvent) DUMP_ALL_CONTROL_POINTS
  {
    retVal = 1;
    dumpAllCaptures();
    clearAllControlPoint();
  }
  break; // switch(inputEvent) DUMP_ALL_CONTROL_POINTS

  case CAPTURE_TRANSLATE: // switch(inputEvent) CAPTURE_TRANSLATE
  {
    retVal = 1;
    dumpAllCaptures();
    captureAction = &deCasteljau::dragTranslate;
  }
  break; // switch(inputEvent) CAPTURE_TRANSLATE

  case CAPTURE_SCALE: // switch(inputEvent) CAPTURE_SCALE
  {
    retVal = 1;
    dumpAllCaptures();
    captureAction = &deCasteljau::dragScale;
  }
  break; // switch(inputEvent) CAPTURE_SCALE

  case CAPTURE_ROTATE: // switch(inputEvent) CAPTURE_ROTATE
  {
    retVal = 1;
    dumpAllCaptures();
    captureAction = &deCasteljau::dragRotate;
  }
  break; // switch(inputEvent) CAPTURE_ROTATE

  case REMOVE_CONTROL_POINT: // switch(inputEvent) REMOVE_CONTROL_POINT
  {
    retVal = 1;
    dumpAllCaptures();
    removeControlPoint();
  }
  break; // switch(inputEvent) REMOVE_CONTROL_POINT

  case TOGGLE_SHELLS: // switch(inputEvent) TOGGLE_SHELLS
  {
    retVal = 1;
    dumpAllCaptures();

    if(shellBl)
    {
      shellBl = false;
    }
    else
    {
      shellBl = true;
    }
  }
  break; // switch(inputEvent) TOGGLE_SHELLS

  case MENU_INPUT: // switch(inputEvent) MENU_INPUT
  {
    retVal = 1;
    dumpAllCaptures();
    clearAllControlPoint();

    union
    {
      double* p;
      double f;

    }menu;

    memset( &menu, 0, sizeof(menu) );

#define f menu.f
#define p menu.p
    f = y;

    // p[0] == degree
    //
    // if degree == 3
    // Fx(t) = a * t^3 + b * t^2 + c * t^1 + d * t^0
    // fx(t1, t2, t3) = a * t1 * t2 * t3 +
    //                    b * (t1 * t2 + t1 * t3 + t2 * t3) / 3 +
    //                    c * (t1 + t2 + t3) +
    //                    d * t^0
    //
    // p[1] == d
    // p[2] == c
    // p[3] == b
    // p[4] == a
    //
    // if degree == 3
    // Fy(t) = e * t^3 + f * t^2 + g * t^1 + h * t^0
    // fy(t1, t2, t3) = e * t1 * t2 * t3 +
    //                    f * (t1 * t2 + t1 * t3 + t2 * t3) / 3 +
    //                    g * (t1 + t2 + t3) +
    //                    h * t^0
    //
    // p[5] == h
    // p[6] == g
    // p[7] == f
    // p[8] == e
    //
    // affine frame(r, s)
    // p[9] == r
    // p[10] == s

    // input point(x, y)
    // p[11] == x
    // p[12] == y

    int degree = fti(p[0] );

    if(degree < 0 || degree > 3)
    {
      break;
    }

    frameR = p[9];
    frameS = p[10];

    t = (frameS - frameR) / 2.0;

    inputPrv = inputCur;

    point inputTemp = point(p[11], p[12] );

    inputCur = inputTemp;

    switch(degree) // switch(inputEvent) MENU_INPUT switch(degree)
    {

    case 0: // switch(inputEvent) MENU_INPUT switch(degree) 0
    {
      // Fx() = d * t^0
      // Fy() = h * t^0
      //
      // fx() = d
      // fy() = h
      //
      // p0 = (fx(), fy() )

      inputCur.x = blossom(0, p[1] );
      inputCur.y = -blossom(0, p[5] );

      addControlPoint();

      inputCur = inputTemp;
    }
    break; // switch(inputEvent) MENU_INPUT switch(degree) 0

    case 1: // switch(inputEvent) MENU_INPUT switch(degree) 1
    {
      // Fx(t) = c * t^1 + d * t^0
      // Fy(t) = g * t^1 + h * t^0
      //
      // fx(t1) = c * t1 + d
      // fy(t1) = g * t1 + h
      //
      // p0 = (fx(r), fy(r) )
      // p1 = (fx(s), fy(s) )

      inputCur.x = blossom(1, p[2], p[1], frameR);
      inputCur.y = -blossom(1, p[6], p[5], frameR);

      addControlPoint();

      inputCur.x = blossom(1, p[2], p[1], frameS);
      inputCur.y = -blossom(1, p[6], p[5], frameS);

      addControlPoint();

      inputCur = inputTemp;
    }
    break; // switch(inputEvent) MENU_INPUT switch(degree) 1

    case 2: // switch(inputEvent) MENU_INPUT switch(degree) 2
    {
      // Fx(t) = b * t^2 + c * t^1 + d * t^0
      // Fy(t) = f * t^2 + g * t^1 + h * t^0
      //
      // fx(t1, t2) = b * t1 * t2 + c * (t1 + t2) / 2 + d
      // fy(t1, t2) = f * t1 * t2 + g * (t1 + t2) / 2 + h
      //
      // p0 = (fx(r, r), fy(r, r) )
      // p1 = (fx(r, s), fy(r, s) )
      // p2 = (fx(s, s), fy(s, s) )

      inputCur.x = blossom(2, p[3], p[2], p[1], frameR, frameR);
      inputCur.y = -blossom(2, p[7], p[6], p[5], frameR, frameR);

      addControlPoint();

      inputCur.x = blossom(2, p[3], p[2], p[1], frameR, frameS);
      inputCur.y = -blossom(2, p[7], p[6], p[5], frameR, frameS);

      addControlPoint();

      inputCur.x = blossom(2, p[3], p[2], p[1], frameS, frameS);
      inputCur.y = -blossom(2, p[7], p[6], p[5], frameS, frameS);

      addControlPoint();

      inputCur = inputTemp;
    }
    break; // switch(inputEvent) MENU_INPUT switch(degree) 2

    case 3: // switch(inputEvent) MENU_INPUT switch(degree) 3
    {
      // Fx(t) = a * t^3 + b * t^2 + c * t^1 + d * t^0
      // Fy(t) = e * t^3 + f * t^2 + g * t^1 + h * t^0
      //
      // fx(t1, t2, t3) = a * t1 * t2 * t3 +
      //                    b * (t1 * t2 + t1 * t3 + t2 * t3) / 3 +
      //                    c * (t1 + t2 + t3) / 3 +
      //                    d
      // fy(t1, t2, t3) = e * t1 * t2 * t3 +
      //                    f * (t1 * t2 + t1 * t3 + t2 * t3) / 3 +
      //                    g * (t1 + t2 + t3) / 3 +
      //                    h
      //
      // p0 = (fx(r, r, r), fy(r, r, r) )
      // p1 = (fx(r, r, s), fy(r, r, s) )
      // p2 = (fx(r, s, s), fy(r, s, s) )
      // p3 = (fx(s, s, s), fy(s, s, s) )

      inputCur.x = blossom(3, p[4], p[3], p[2], p[1], frameR, frameR, frameR);
      inputCur.y = -blossom(3, p[8], p[7], p[6], p[5], frameR, frameR, frameR);

      addControlPoint();

      inputCur.x = blossom(3, p[4], p[3], p[2], p[1], frameR, frameR, frameS);
      inputCur.y = -blossom(3, p[8], p[7], p[6], p[5], frameR, frameR, frameS);

      addControlPoint();

      inputCur.x = blossom(3, p[4], p[3], p[2], p[1], frameR, frameS, frameS);
      inputCur.y = -blossom(3, p[8], p[7], p[6], p[5], frameR, frameS, frameS);

      addControlPoint();

      inputCur.x = blossom(3, p[4], p[3], p[2], p[1], frameS, frameS, frameS);
      inputCur.y = -blossom(3, p[8], p[7], p[6], p[5], frameS, frameS, frameS);

      addControlPoint();

      inputCur = inputTemp;
    }
    break; // switch(inputEvent) MENU_INPUT switch(degree) 3

    } // switch(inputEvent) MENU_INPUT switch(degree)
#undef p
#undef f
  }
  break; // switch(inputEvent) MENU_INPUT

  case DUMP_ALL_CAPTURES: // switch(inputEvent) DUMP_ALL_CAPTURES
  {
    retVal = 1;
    dumpAllCaptures();
  }
  break; // switch(inputEvent) DUMP_ALL_CAPTURES

  case TOGGLE_CONTROL_POINTS: // switch(inputEvent) TOGGLE_CONTROL_POINTS
  {
    retVal = 1;
    dumpAllCaptures();

    if(ctrlBl)
    {
      ctrlBl = false;
    }
    else
    {
      ctrlBl = true;
    }
  }
  break; // switch(inputEvent) TOGGLE_CONTROL_POINTS

  case INCREASE_ITERATION_CONSTANT: // switch(inputEvent) INCREASE_ITERATION_CONSTANT
  {
    ++iterateConstant;
  }
  break; // switch(inputEvent) INCREASE_ITERATION_CONSTANT

  case DECREASE_ITERATION_CONSTANT: // switch(inputEvent) DECREASE_ITERATION_CONSTANT
  {
    if(iterateConstant > 0)
    {
      --iterateConstant;
    }
  }
  break; // switch(inputEvent) DECREASE_ITERATION_CONSTANT

  default: // switch(inputEvent) default
  {
  }
  goto label_return; // switch(inputEvent) default

  } // switch(inputEvent)

  if( !numControlPts)
    goto label_return;

  // Call capture action function pointer.
  if(captureAction && inputPrv != inputCur)
  {
    minMaxT = 0;
    shellT = 0;

    retVal = 1;

    (this->*captureAction)();
  }

label_return:
  return retVal;

} // int deCasteljau::updateInput(int inputEvent, double x, double y)

// Call every program loop to draw F(x), the control points,
// F(t), and the shells for F(t).
void updateDraw() // void deCasteljau::updateDraw()
{
  point p0, p1;

  point weight;

  int loop = -1;

  if( !numControlPts)
    goto label_return;

  if(numControlPts == 1)
  {
    drawCircle(tranPt[0], (0 == (capturedControlPt - 1) ) ? 15 : 10, 1);

    goto label_return;
  }

  if( !fti(minMaxT) )
  {
    while( !subdWt.empty() )
    {
      subdWt.pop();
    }

    p1 = do_deCasteljau(0.5);

    subdWt.push(pairQS(p1, point(0.5, 0.5 + 0.125 * (double)iterateConstant) ) );

    drawPoint(p1, 0);

    minMaxT = 1;
  }

  while(++loop < 40 * (1 + iterateConstant) )
  {
    // get parent point
    p0 = subdWt.front().first;

    // get parent point's weight
    weight = subdWt.front().second;

    // Remove the parent point from the subdivision tree.
    subdWt.pop();

    // See if the left/right child point is the same as the parent point,
    // if it is then stop subdivision for that branch of the curve tree.
    //
    // Otherwise continue subdivision, inputting the child point into the
    // tree for further branching.

    // Left Child's weight == weight.x - weight.y * 0.5.
    p1 = do_deCasteljau(weight.x - weight.y * 0.5);

    // Check if the left child is the same point as the parent
    if(p0 == p1)
    {
      // Do not do anything if they are the same point.
    }
    else
    {
      // Draw and branch out the left child if the points are different.
      drawPoint(p1, 0);

      subdWt.push(pairQS(p1, point(weight.x - weight.y * 0.5, weight.y * 0.5) ) );
    }

    // Right Child's weight == weight.x + weight.y * 0.5.
    p1 = do_deCasteljau(weight.x + weight.y * 0.5);

    // Check if the right child is the same point as the parent
    if(p0 == p1)
    {
      // Do not do anything if they are the same point.
    }
    else
    {
      // Draw and branch out the right child if the points are different.
      drawPoint(p1, 0);

      subdWt.push(pairQS(p1, point(weight.x + weight.y * 0.5, weight.y * 0.5) ) );
    }

    if(subdWt.empty() )
    {
      subdWt.push(pairQS(p1, point(0.5 - minMaxT, 0.5) ) );
      subdWt.push(pairQS(p1, point(0.5 + minMaxT, 0.5) ) );

      minMaxT += 1;
    }
  }

  loop = -1;

  if( !shellT)
  {
    ++loop;

    shellT = 2;

    if(shellBl)
    {
      iteratorDP a = shelPt.begin();
      iteratorDP b = tranPt.begin();

      // Copy the transformed points into the shel list.
      //
      // This is the equivalent of stage 0 of the de Casteljau algorithm.
      //
      // This is used for iterative shell drawing of t of f(t).
      for(int index = 0; index < numControlPts - 1; index++, a++, b++)
      {
        a->x = (1.0 - t) * b->x + t * (b + 1) ->x;
        a->y = (1.0 - t) * b->y + t * (b + 1) ->y;

        drawLine( *b, *(b + 1), 1);
      }
    }

    if(ctrlBl)
    {
      for(int currentPtIndex = 0; currentPtIndex < numControlPts; currentPtIndex++)
      {
        drawCircle(tranPt[ (uint32_t)currentPtIndex], (currentPtIndex == (capturedControlPt - 1) ) ? 15 : 10, currentPtIndex + 1);
      }
    }

    // Calculate/draw shells and F(t) (for F(t) from the user-inputted t).
    p0 = do_deCasteljau(t);

    drawCircle(p0, 5, 0);
  }

  while(++loop < 1 + iterateConstant)
  {
    if(shellBl && shellT >= 2 && shellT <= numControlPts - 1)
    {
      int size;
      int index;

      iteratorDP a;
      iteratorDP b;

      size = numControlPts - shellT;

      // index refers to the current point in the current stage,
      // the number of points in the current stage always equal to
      // size.
      for(index = 0, a = shelPt.begin(); index < size; index++, a++)
      {
        b = a + 1;

        drawLine(*a, *b, numControlPts - size);

        a->x = (1.0 - t) * a->x + t * b->x;
        a->y = (1.0 - t) * a->y + t * b->y;
      }

      shellT++;
    }
  }

label_return:
  return;

} // void deCasteljau::updateDraw()

private:

// The blossom is used to compute the control points when receiving menu input.
//
// Possible inputs:
// blossom(0, d);
// blossom(1, c, d, t1);
// blossom(2, b, c, d, t1, t2);
// blossom(3, a, b, c, d, t1, t2, t3);
double blossom(int degree, ...) // double deCasteljau::blossom(int degree, ...)
{
  double result = 0;

  double a = 0;
  double b = 0;
  double c = 0;
  double d = 0;

  double t1 = 0;
  double t2 = 0;
  double t3 = 0;

  if(degree < 0 || degree > 3)
  {
    assert(0 && "bad blossom degree");
  }

  va_list argptr = 0;

  va_start(argptr, degree);

  switch(degree) // switch(degree)
  {

  case 0: // switch(degree) 0
  {
    d = va_arg(argptr, double);

    va_end(argptr);

    result = d;
  }
  break; // switch(degree) 0

  case 1: // switch(degree) 1
  {
    c = va_arg(argptr, double);
    d = va_arg(argptr, double);

    t1 = va_arg(argptr, double);

    va_end(argptr);

    result = c * t1 + d;
  }
  break; // switch(degree) 1

  case 2: // switch(degree) 2
  {
    b = va_arg(argptr, double);
    c = va_arg(argptr, double);
    d = va_arg(argptr, double);

    t1 = va_arg(argptr, double);
    t2 = va_arg(argptr, double);

    va_end(argptr);

    result = b * t1 * t2 + c * (t1 + t2) / 2.0 + d;
  }
  break; // switch(degree) 2

  case 3: // switch(degree) 3
  {
    a = va_arg(argptr, double);
    b = va_arg(argptr, double);
    c = va_arg(argptr, double);
    d = va_arg(argptr, double);

    t1 = va_arg(argptr, double);
    t2 = va_arg(argptr, double);
    t3 = va_arg(argptr, double);

    va_end(argptr);

    result = a * t1 * t2 * t3 + b * (t1 * t2 + t1 * t3 + t2 * t3) / 3.0 + c * (t1 + t2 + t3) / 3.0 + d;
  }
  break; // switch(degree) 3

  default: // switch(degree) default
  {
    assert(0 && "bad blossom degree");
  }
  break; // switch(degree) default

  } // switch(degree)

  return result;

} // double deCasteljau::blossom(int degree, ...)

point do_deCasteljau(double dt) // point deCasteljau::do_deCasteljau(double dt)
{
  int index;
  int size;

  iteratorDP a = tempPt.begin();
  iteratorDP b = tranPt.begin();

  // Copy the transformed points into the temp list.
  //
  // This is the equivalent of stage 0 of the de Casteljau algorithm.
  for(index = 0; index < numControlPts; index++, a++, b++)
    *a = *b;

  // size refers to the number of points in the current stage.
  //
  // Stage 0 has size == numControlPts, but we start at stage 1,
  // which has size == numControlPts - 1.
  for(size = numControlPts - 1; size > 0; size--)
  {
    // index refers to the current point in the current stage,
    // the number of points in the current stage always equal to
    // size.
    for(index = 0, a = tempPt.begin(); index < size; index++, a++)
    {
      b = a + 1;

      a->x = (1.0 - dt) * a->x + dt * b->x;
      a->y = (1.0 - dt) * a->y + dt * b->y;
    }
  }

  return *tempPt.begin();

} // point deCasteljau::do_deCasteljau(double dt)

// Wrapper for easily calling circleDrawingPrimitive().
void drawCircle(point center, int radius, int currentNum) // void deCasteljau::drawCircle(point center, int radius, int currentNum)
{
  if(circleDrawingPrimitive)
  {
    if(center.x < -2000000000 || center.x > 2000000000 || center.y < -2000000000 || center.y > 2000000000)
      goto label_return;

    circleDrawingPrimitive(fti(center.x), fti(center.y), radius, colors0[currentNum % 100], colors1[currentNum % 100] );
  }

label_return:
  return;

}  // void deCasteljau::drawCircle(point center, int radius, int currentNum)

// Wrapper for easily calling lineDrawingPrimitive().
void drawLine(point start, point end, int currentNum) // void deCasteljau::drawLine(point start, point end, int currentNum)
{
  if(lineDrawingPrimitive)
  {
    if(start.x < -2000000000 || start.x > 2000000000 || start.y < -2000000000 || start.y > 2000000000 || end.x < -2000000000 || end.x > 2000000000 || end.y < -2000000000 || end.y > 2000000000)
      goto label_return;

    lineDrawingPrimitive(fti(start.x), fti(start.y), fti(end.x), fti(end.y), colors0[currentNum % 100], colors1[currentNum % 100] );
  }

label_return:
  return;

} // void deCasteljau::drawLine(point start, point end, int currentNum)

// Wrapper for easily calling pointDrawingPrimitive().
void drawPoint(point center, int currentNum) // void deCasteljau::drawPoint(point center, int currentNum)
{
  if(pointDrawingPrimitive)
  {
    if(center.x < -2000000000 || center.x > 2000000000 || center.y < -2000000000 || center.y > 2000000000)
      goto label_return;

    pointDrawingPrimitive(fti(center.x), fti(center.y), colors0[currentNum % 100] );
  }

label_return:
  return;

} // void deCasteljau::drawPoint(point center, int currentNum)

// When the user adds another control point, add that control point in the
// list right after the previous control point.
//
// Also add an extra point to the end of the list, used as temporary storage
// while evaluating the de Casteljau algorithm.
void addControlPoint() // void deCasteljau::addControlPoint()
{
  // Add the new control point to the list.
  numControlPts++;

  shelPt.push_back(inputCur);
  tempPt.push_back(inputCur);
  tranPt.push_back(inputCur);

} // void deCasteljau::addControlPoint()

// Captures the closest control point, for user manipulation.
void captureControlPoint() // void deCasteljau::captureControlPoint()
{
  double distMin;

  // Starting with the first control point, and doing the same with all ctrl pts,
  // calculate the distance between the input pt and each ctrl pt.
  //
  // The ctrl pt that is closest to the input pt is the pt that is captured.
  // The index of the closest ctrl pt is stored in capturedControlPt,
  // and the captureAction()function is activated to point to the dragControlPoint()
  // function.
  capturedControlPt = 0;
  distMin = inputCur.dist(tranPt[ (uint32_t)capturedControlPt] );

  for(int currentPtIndex = 1; currentPtIndex < numControlPts; currentPtIndex++)
  {
    if(distMin > inputCur.dist(tranPt[ (uint32_t)currentPtIndex] ) )
    {
      distMin = inputCur.dist(tranPt[ (uint32_t)currentPtIndex] );

      capturedControlPt = currentPtIndex;
    }
  }

  capturedControlPt++;

  captureAction = &deCasteljau::dragControlPoint;

} // void deCasteljau::captureControlPoint()

// Captures t of F(t)
void capture_t_of_F_of_t() // void deCasteljau::capture_t_of_F_of_t()
{
  // Find the minimum and maximum values of the coordinate pts,
  // which are needed to normalize input.
  minPt.x = tranPt[0].x;
  maxPt.x = tranPt[0].x;

  minPt.y = 0;
  maxPt.y = 0;

  for(int currentPtIndex = 1; currentPtIndex < numControlPts; currentPtIndex++)
  {
    if(minPt.x > tranPt[ (uint32_t)currentPtIndex].x)
    {
      minPt.x = tranPt[ (uint32_t)currentPtIndex].x;
    }

    if(maxPt.x < tranPt[ (uint32_t)currentPtIndex].x)
    {
      maxPt.x = tranPt[ (uint32_t)currentPtIndex].x;
    }
  }

  // Once t can be normalized, activate the captureAction()function to
  // point to the drag_t_of_F_of_t()function.
  //
  // The new t will be calculated in the drag_t_of_F_of_t()function.
  captureAction = &deCasteljau::drag_t_of_F_of_t;

} // void deCasteljau::capture_t_of_F_of_t()

// When the user chooses to clear all ctrl pts, to start a new curve,
// erase all elements in the control point list.
void clearAllControlPoint() // void deCasteljau::clearAllControlPoint()
{
  shelPt.clear();
  tranPt.clear();
  tempPt.clear();

  while( !subdWt.empty() )
  {
    subdWt.pop();
  }

  numControlPts = 0;

} // void deCasteljau::clearAllControlPoint()

// This function is called thru the captureAction()function, when the user wants
// to manipulate t of F(t).
void drag_t_of_F_of_t() // void deCasteljau::drag_t_of_F_of_t()
{
  t = (inputCur.x - minPt.x) / fabs(maxPt.x - minPt.x);

} // void deCasteljau::drag_t_of_F_of_t()

// This function is called thru the captureAction()function, when the user wants
// to manipulate a control pt.
void dragControlPoint() // void deCasteljau::dragControlPoint()
{
  // Drag the captured ctrl pt relative to input movement between
  // the current input pt and the previous input pt.
  tranPt[ (int64_t)capturedControlPt - 1].x += inputCur.x - inputPrv.x;
  tranPt[ (int64_t)capturedControlPt - 1].y += inputCur.y - inputPrv.y;

} // void deCasteljau::dragControlPoint()

// When a new user request has occured, flush any older user requests
// currently being processed.
void dumpAllCaptures() // void deCasteljau::dumpAllCaptures()
{
  capturedControlPt = 0;
  captureAction = 0;

  minMaxT = 0;
  shellT = 0;

} // void deCasteljau::dumpAllCaptures()

void dragTranslate() // void deCasteljau::dragTranslate()
{
  point p;

  iteratorDP a = tranPt.begin();

  for(int index = 0; index < numControlPts; index++, a++)
  {
    p = *a;

    a->x = p.x + (inputCur.x - inputPrv.x);
    a->y = p.y + (inputCur.y - inputPrv.y);
  }

} // void deCasteljau::dragTranslate()

void dragScale() // void deCasteljau::dragScale()
{
  double scale = 1.0 + (inputCur.y - inputPrv.y) / (halfWidth * 2);

  double tx = (1 - scale) * halfWidth;
  double ty = (1 - scale) * halfHeight;

  point p;

  iteratorDP a = tranPt.begin();

  for(int index = 0; index < numControlPts; index++, a++)
  {
    p = *a;

    a->x = p.x * scale + tx;
    a->y = p.y * scale + ty;
  }

} // void deCasteljau::dragScale()

void dragRotate() // void deCasteljau::dragRotate()
{
  double angle = (inputCur.x - inputPrv.x) / 180.0;

  double cosine = cos(angle);
  double sine = sin(angle);

  double tx = (1 - cosine) * halfWidth + sine * halfHeight;
  double ty = -sine * halfWidth + (1 - cosine) * halfHeight;

  point p;

  iteratorDP a = tranPt.begin();

  for(int index = 0; index < numControlPts; index++, a++)
  {
    p = *a;

    a->x = p.x * cosine + p.y * -sine + tx;
    a->y = p.x * sine + p.y * cosine + ty;
  }

} // void deCasteljau::dragRotate()

void removeControlPoint() // void deCasteljau::removeControlPoint()
{
  int ctrlPt;

  double distMin;

  // Starting with the first control point, and doing the same with all ctrl pts,
  // calculate the distance between the input pt and each ctrl pt.
  //
  // The ctrl pt that is closest to the input pt is the pt that is deleted.
  ctrlPt = 0;
  distMin = inputCur.dist(tranPt[ (uint32_t)ctrlPt] );

  for(int currentPtIndex = 1; currentPtIndex < numControlPts; currentPtIndex++)
  {
    if(distMin > inputCur.dist(tranPt[ (uint32_t)currentPtIndex] ) )
    {
      distMin = inputCur.dist(tranPt[ (uint32_t)currentPtIndex] );

      ctrlPt = currentPtIndex;
    }
  }

  shelPt.erase(shelPt.begin() + ctrlPt);
  tempPt.erase(tempPt.begin() + ctrlPt);
  tranPt.erase(tranPt.begin() + ctrlPt);

  --numControlPts;

} // void deCasteljau::removeControlPoint()

}; // class deCasteljau

const double deCasteljau::E = 0.000001;

typedef deque<deCasteljau*> dequeC;
typedef dequeC::iterator iteratorDC;

static dequeC* deCastList = 0;
static iteratorDC deCastIter;

enum
{
  ERROR = -1,
  OK = 0
};

extern "C" int init2(double _halfWidth, double _halfHeight, void(*_circleDrawingPrimitive)(int, int, int, int, int), void(*_lineDrawingPrimitive)(int, int, int, int, int, int), void(*_pointDrawingPrimitive)(int, int, int) ) // int init(double _halfWidth, double _halfHeight, void(*_circleDrawingPrimitive)(int, int, int, int, int), void(*_lineDrawingPrimitive)(int, int, int, int, int, int), void(*_pointDrawingPrimitive)(int, int, int) )
{
  int result = ERROR;

  // Initialize the random number generator.
  srand( (unsigned int)time(0) );

  if( !deCastList)
  {
    if(_halfWidth <= 0 || _halfHeight <= 0 || !_circleDrawingPrimitive || !_lineDrawingPrimitive || !_pointDrawingPrimitive)
      goto label_return;

    deCastList = new dequeC;

    if( !deCastList)
      goto label_return;

    deCastList->push_back(new deCasteljau);

    if( !( *deCastList)[0] )
      goto label_return;

    ( *deCastList)[0]->setPrimitiveDrawingFunctions(_halfWidth, _halfHeight, _circleDrawingPrimitive, _lineDrawingPrimitive, _pointDrawingPrimitive);

    deCastIter = deCastList->begin();
  }

  if( !( *deCastList)[0] || deCastIter != deCastList->begin() )
    goto label_return;

  result = OK;

label_return:
  return result;

} // int init(double _halfWidth, double _halfHeight, void(*_circleDrawingPrimitive)(int, int, int, int, int), void(*_lineDrawingPrimitive)(int, int, int, int, int, int), void(*_pointDrawingPrimitive)(int, int, int) )

extern "C" int main2(int inputEvent, double x, double y, double _halfWidth, double _halfHeight) // int main(int inputEvent, double x, double y, double _halfWidth, double _halfHeight)
{
  int result = OK;

  iteratorDC temp;

  deCasteljau* curve = 0;

  iteratorDC loop;

  if( !deCastList || !deCastList->size() )
  {
    result = ERROR;
    goto label_return;
  }

  if(deCastIter == deCastList->end() || !deCastIter[0] )
    deCastIter = deCastList->begin();

  if(_halfWidth <= 0 || _halfHeight <= 0)
  {
    result = ERROR;
    goto label_return;
  }

  switch(inputEvent) // switch(inputEvent)
  {

  case deCasteljau::ADD_DE_CASTELJAU_CURVE: // switch(inputEvent) ADD_DE_CASTELJAU_CURVE
  {
    curve = new deCasteljau;
    if( !curve)
    {
      result = ERROR;
      goto label_return;
    }

    curve->setPrimitiveDrawingFunctions( **deCastIter);

    deCastList->push_back(curve);

    deCastIter = deCastList->end() - 1;
  }
  break; // switch(inputEvent) ADD_DE_CASTELJAU_CURVE

  case deCasteljau::REMOVE_DE_CASTELJAU_CURVE: // switch(inputEvent) REMOVE_DE_CASTELJAU_CURVE
  {
    if(deCastList->size() == 1)
    {
      inputEvent = deCasteljau::DUMP_ALL_CONTROL_POINTS;
    }
    else
    {
      delete *deCastIter;

      deCastList->erase(deCastIter);

      deCastIter = deCastList->begin();

      result |= 1;

      inputEvent = deCasteljau::DUMP_ALL_CAPTURES;
    }
  }
  break; // switch(inputEvent) REMOVE_DE_CASTELJAU_CURVE

  case deCasteljau::TRAVERSE_DE_CASTELJAU_CURVE_LIST: // switch(inputEvent) TRAVERSE_DE_CASTELJAU_CURVE_LIST
  {
    ++deCastIter;

    if(deCastIter == deCastList->end() )
      deCastIter = deCastList->begin();
  }
  break; // switch(inputEvent) TRAVERSE_DE_CASTELJAU_CURVE_LIST

  } // switch(inputEvent)

  deCastIter[0]->setPrimitiveDrawingFunctions(_halfWidth, _halfHeight, 0, 0, 0);

  deCastIter[0]->updateDraw();

  result |= deCastIter[0]->updateInput(inputEvent, x, y);

  for(loop = deCastList->begin(); loop != deCastList->end(); loop++)
  {
    if(loop != deCastIter)
    {
      loop[0]->setPrimitiveDrawingFunctions(_halfWidth, _halfHeight, 0, 0, 0);

      loop[0]->updateDraw();
    }

    if( (result || inputEvent == deCasteljau::DUMP_ALL_CAPTURES) && loop != deCastIter)
      result |= loop[0]->updateInput(deCasteljau::DUMP_ALL_CAPTURES, x, y);
  }

label_return:
  return result;

} // int main(int inputEvent, double x, double y, double _halfWidth, double _halfHeight)

extern "C" int term2() // int term()
{
  int result = ERROR;

  iteratorDC loop;

  if(deCastList)
  {
    deCastIter = deCastList->end();

    for(loop = deCastList->begin(); loop != deCastList->end(); loop++)
    {
      if( *loop)
      {
        delete *loop;
        *loop = 0;
      }
    }

    deCastList->clear();

    delete deCastList;
    deCastList = 0;
  }

  result = OK;

  return result;

} // int term()
