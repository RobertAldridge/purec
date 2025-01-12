//
// Filename: de_boor.cpp
//
// Start summer session
//
// Digipen Week 01 -- Mon, Apr 30th - to - Sun, Jun 06th
// Digipen Week 02 -- Mon, May 07th - to - Sun, May 13th
// Digipen Week 03 -- Mon, May 14th - to - Sun, May 20th
// Digipen Week 04 -- Mon, May 21st - to - Sun, May 27th
// Digipen Week 05 -- Mon, May 28th - to - Sun, Jun 03rd
//
// -- START DE CASTELJAU --
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
// Digipen Week 14 -- Mon, Jul 30th - to - Sun, Aug 05th
//
// Emailed to Michael Jahn Mon, Jul 30th, 2001 12:00 pm VERSION 1.2
//
// -- START DE BOOR --
//
// Mon, Jul 30th, 2001 01:00pm to 04:00pm -> 03:00 hr  | 69:00 hrs cum
//
// Wed, Aug 01st, 2001 04:00pm to 08:00pm -> 04:00 hr  | 73:00 hrs cum
// Wed, Aug 01st, 2001 11:00pm to 12:00am -> 01:00 hr  | 74:00 hrs cum
//
// Thr, Aug 02nd, 2001 12:00am to 01:00pm -> 12:00 hr  | 86:00 hrs cum
// Thr, Aug 02nd, 2001 03:00pm to 10:00pm -> 07:00 hr  | 93:00 hrs cum
//
// Digipen Week 15 -- Mon, Aug 06th - to - Sun, Aug 12th
//
// End summer session
//

#pragma warning (push, 3)

#pragma warning (disable: 4710)

#pragma warning (disable: 4786)

#include <cassert>
#include <cmath>
#include <ctime>
#include <cstdarg>

#include <iostream>
#include <deque>
#include <list>
#include <queue>

using namespace std;

extern void* operator new(size_t size) throw(bad_alloc);

extern void* operator new[](size_t size) throw(bad_alloc);

extern void operator delete(void* ptr) throw();

extern void operator delete[](void* ptr) throw();

class de_boor
{

// Epsilon:
//    If num - floor(num) <= E, then num = floor(num).
//    If ceiling(num) - num <= E, then num = ceiling(num).
//
// Both are always true, even when truncating from double to int.
static const double E;

// function convert float to int
static int fti(double f) // de_boor::fti
{
  return (f - floor(f) <= E)? (int)floor(f) : ( (ceil(f) - f <= E)? (int)ceil(f) : (int)f);

} // de_boor::fti

static int eq(double a, double b) // de_boor::eq
{
  return fabs(a - b) <= E;

} // de_boor::eq

// A little 2D point class, makes stuff easier.
class point
{

public:

// x, y, and z coordinates of a 3D point with respect to the standard origin.
double x, y, z;

// Easy way to create a point from 3 doubles
point(double _x = 0, double _y = 0, double _z = 1): x(_x), y(_y), z(_z) // point::point
{
  /* nop */

} // point::point

double dist2D(const point &pt) const // point::dist2D
{
  if(isProjectable() == true && pt.isProjectable() == true)
  {
    double _x = x / z - pt.x / pt.z;

    double _y = y / z - pt.y / pt.z;

    return sqrt(_x * _x + _y * _y);
  }

  return -3.402823466e+38;

} // point::dist2D

// Easy way to calculate the Euclidean distance between two points.
double dist(const point &pt) const // point::dist
{
  return sqrt( (x - pt.x) * (x - pt.x) + (y - pt.y) * (y - pt.y) + (z - pt.z) * (z - pt.z) );

} // point::dist

bool isProjectable() const // point::isProjectable
{
  if(z > 1 || eq(z, 1) )
  {
    return true;
  }

  return false;

} // point::isProjectable

point projectTo2D() const // point::projectTo2D
{
  if(eq(z, 0) )
  {
    return point(-1, -1, -1);
  }

  return point(x / z, y / z, 1);

} // point::projectTo2D

// Easy way to check if two points correspond to the same pixel.
bool operator==(const point& pt) const // point::operator==
{
  return fti(x) == fti(pt.x) && fti(y) == fti(pt.y) && fti(z) == fti(pt.z);

} // point::operator==

bool operator!=(const point& pt) const // point::operator!=
{
  return fti(x) != fti(pt.x) || fti(y) != fti(pt.y) || fti(z) != fti(pt.z);

} // point::operator!=

point operator+(const point& rhs) const // point::operator+
{
  return point(x + rhs.x, y + rhs.y, z + rhs.z);

} // point::operator+

point operator+=(const point& rhs) // point::operator+=
{
  *this = *this + rhs;

  return *this;

} // point::operator+=

point operator-(const point& rhs) const // point::operator-
{
  return point(x - rhs.x, y - rhs.y, z - rhs.z);

} // point::operator-

point operator*(const point& rhs) const // point::operator* 1
{
  return point(x * rhs.x, y * rhs.y, z * rhs.z);

} // point::operator* 1

point operator*(const double rhs) const // point::operator* 2
{
  return point(x * rhs, y * rhs, z * rhs);

} // point::operator* 2

friend point operator*(const double lhs, const point& rhs) // point::operator* 3
{
  return point(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);

} // point::operator* 3

}; // class point

friend point;

typedef pair<point, point> pairQS;
typedef queue<pairQS> queueS;

typedef deque<point> dequeP;
typedef dequeP::iterator iteratorDP;

typedef vector<double> vectorK;
typedef vectorK::iterator iterVK;

// This variable t is used to describe F(t), which is
// the point on the curve that shells are shown for,
// the very same point that the program user can choose.
//
// This default value 0.5 is halfway through the curve.
double t;

// r and s define the affine frame (r, s).
double r;
double s;

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

// The maximum degree of each piece-wise polynomial curve.
int degree;

// The maximum dimension of the space that the spline curve lives in (currently forced to 3).
int dimension;

// The current de Boor stage iteration that must be computed
// for the t of f(t) shells.
int shellT;

// If the shells are visible then this variable is set to true.
bool shellBl;

// If the control points are visible then this variable is set to true.
bool ctrlBl;

// If the knot values are displayed next to the control points,
// then this variable is set to true.
bool dispK;

// A marker, used to tell the subdivision algorithm which part of
// the curve to render next.  Most importantly, this variable is
// used to iteratively render curve segments less than r and
// greater that s.
double minMaxT;

// This is temp memory used for iterative shell computations for t of f(t).
dequeP shelPt;

// The transformed control points are stored in this list.
dequeP tranPt;

// This is temp memory used for computing intermediate de Boor stage points.
dequeP tempPt;

// This is the knot list associated with the de Boor control points.
vectorK knots;

// Iterative subdivision queue.
queueS subdWt;

// The current input position.  Used when calculating the drag distance
// when manipulating control points.  The contents of this variable are
// not always updated/valid, unless needed by the algorithm.
point inputCur;
point inputPrv;

// The minimum and maximum values for t of F(t), used to normalize input for t
// from [ minPt, maxPt ] to [ 0, 1 ], when the user wants to see shells
// for a certain point.  Values are not always current/valid.
//
// Currently only the x coordinate of the points { inputPT, minPt, maxPt } are
// used to determine the actual value of t of F(t).
point minPt, maxPt;

// The different colors used for each shell and control point (in RGB).
int colors0[100];
int colors1[100];

double halfWidth;
double halfHeight;

// The function pointer for capture functions, used when the user is
// manipulating the curve.
//
// Currently valid/used when manipulating either the control points or the t value for F(t).
void(de_Boor::*captureAction)();

// A pointer to a client supplied circle drawing function, set in setPrimitiveDrawingFunctions().
void(*circleDrawingPrimitive)(int xCenter, int yCenter, int radius, int color0RGB, int color1RGB);

// A pointer to a client supplied line segment drawing function, set in setPrimitiveDrawingFunctions().

void(*lineDrawingPrimitive)(int x0, int y0, int x1, int y1, int color0RGB, int color1RGB);

// A pointer to a client supplied point drawing function, set in setPrimitiveDrawingFunctions().
void(*pointDrawingPrimitive)(int x0, int y0, int color0RGB);

// A pointer to a client supplied text drawing function, set in setPrimitiveDrawingFunctions().
void(*textDrawingPrimitive)(int x0, int y0, const char* const, ...);

public:

  // Initialize the de Boor algorithm when the user inputs the
  // first control point.
  de_Boor(int _degree = 3, int _iterateConstant = 16): t(0.5), r(0), s(1), capturedControlPt(0), numControlPts(0), iterateConstant(_iterateConstant), degree(_degree), dimension(3), shellT(0), shellBl(true), ctrlBl(true), dispK(true), minMaxT(0), shelPt(), tranPt(), tempPt(), knots(), subdWt(), inputCur(0, 0), inputPrv(0, 0), minPt(0, 0), maxPt(0, 0), halfWidth(0.5), halfHeight(0.5), captureAction(0), circleDrawingPrimitive(0), lineDrawingPrimitive(0), pointDrawingPrimitive(0), textDrawingPrimitive(0) // de_Boor::de_Boor
  {
    if(degree <= 0)
    {
      degree = 1;
    }

    // temp m + 1 container
    for(int loop = 0; loop <= degree; loop++)
    {
      tempPt.push_back(point(0, 0) );
    }

    if(iterateConstant < 1)
    {
      iterateConstant = 1;
    }

    // Create some different colors to view the shells and control points with.
    for(int i = 0, c0 = 0, c1 = 0; i < 100; i++)
    {
      do
      {
        // Create random RGB colors, so things look pretty
        c0 = (rand() % 256) | ( (rand() % 256) << 8) | ( (rand() % 256) << 16);
        c1 = (rand() % 256) | ( (rand() % 256) << 8) | ( (rand() % 256) << 16);

        // Check to make sure the color is not too dark
      }while( ( (c0 & 0xff) < 0xa0 && (c0 & 0xff00) < 0xa000 && (c0 & 0xff0000) < 0xa00000) || ( (c1 & 0xff) < 0xa0 && (c1 & 0xff00) < 0xa000 && (c1 & 0xff0000) < 0xa00000) );

      colors0[i] = c0;
      colors1[i] = c1;
    }

    colors1[0] = colors0[0];

  } // de_Boor::de_Boor

  // Free dynamic memory allocations when destroying the algorithm instance.
  ~de_Boor() // de_Boor::~de_Boor
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

    while( !knots.empty() )
    {
      knots.clear();
    }

    while( !subdWt.empty() )
    {
      subdWt.pop();
    }

  } // de_Boor::~de_Boor

  // This function must be called by the client in order for the algorithm to
  // visually output the curve F(x), the control points, and the shells for F(t).
void setPrimitiveDrawingFunctions(double _halfWidth, double _halfHeight, void(*_circleDrawingPrimitive)(int, int, int, int, int), void(*_lineDrawingPrimitive)(int, int, int, int, int, int), void(*_pointDrawingPrimitive)(int, int, int), void(*_textDrawingPrimitive)(int, int, const char* const, ...) ) // de_boor::setPrimitiveDrawingFunctions 1
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

    if(_textDrawingPrimitive)
    {
      textDrawingPrimitive = _textDrawingPrimitive;
    }

  } // de_boor::setPrimitiveDrawingFunctions 1

  void setPrimitiveDrawingFunctions(de_Boor& rhs) // de_boor::setPrimitiveDrawingFunctions 2
  {
    halfWidth = rhs.halfWidth;
    halfHeight = rhs.halfHeight;

    if(rhs.circleDrawingPrimitive)
    {
      circleDrawingPrimitive = rhs.circleDrawingPrimitive;
    }

    if(rhs.lineDrawingPrimitive)
    {
      lineDrawingPrimitive   = rhs.lineDrawingPrimitive;
    }

    if(rhs.pointDrawingPrimitive)
    {
      pointDrawingPrimitive  = rhs.pointDrawingPrimitive;
    }

    if(rhs.textDrawingPrimitive)
    {
      textDrawingPrimitive   = rhs.textDrawingPrimitive;
    }

  } // de_boor::setPrimitiveDrawingFunctions 2

  enum INPUT_EVENT // de_boor::INPUT_EVENT
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
    // are sent to the de_Boor::updateInput() function.

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
    ADD_DE_BOOR_CURVE = 2048,

    // The #5 undocumented numpad 3 command
    REMOVE_DE_BOOR_CURVE = 4096,

    // The #6 undocumented numpad 4 command
    TRAVERSE_DE_BOOR_CURVE_LIST = 8192,

    // The #7 undocumented numpad 5 command
    TOGGLE_CONTROL_POINT_TEXT = 16384

  }; // de_boor::INPUT_EVENT

  // Call this function whenever there is input,
  // to update the de Boor algorithm.
  int updateInput(int inputEvent, double xB, double yB, double B) // de_boor::updateInput
  {
    int retVal = 0;

    if(numControlPts == 0 && inputEvent != ADD_CONTROL_POINT && inputEvent != MENU_INPUT)
    {
      return retVal;
    }

    if(inputEvent != MENU_INPUT)
    {
      inputPrv = inputCur;

      inputCur = point(xB, yB, B);
    }

    // Check the input event ; perform input actions
    switch(inputEvent) // switch(inputEvent)
    {

    ////////////////////////////////////////////////////////
    case UPDATE_INPUT: // switch(inputEvent) - UPDATE_INPUT
    {
      /* nop */
    }
    break; // switch(inputEvent) - UPDATE_INPUT

    ////////////////////////////////////////////////////////
    case CAPTURE_CONTROL_POINT: // switch(inputEvent) - CAPTURE_CONTROL_POINT
    {
      retVal = 1;
      dumpAllCaptures();
      captureControlPoint();
    }
    break; // switch(inputEvent) - CAPTURE_CONTROL_POINT

    case ADD_CONTROL_POINT: // switch(inputEvent) - ADD_CONTROL_POINT
    {
      retVal = 1;
      dumpAllCaptures();
      addControlPoint();
    }
    break; // switch(inputEvent) - ADD_CONTROL_POINT

    ////////////////////////////////////////////////////////
    case CAPTURE_T_OF_F_OF_T: // switch(inputEvent) - CAPTURE_T_OF_F_OF_T
    {
      retVal = 1;
      dumpAllCaptures();
      capture_t_of_F_of_t();
    }
    break; // switch(inputEvent) - CAPTURE_T_OF_F_OF_T

    case DUMP_ALL_CONTROL_POINTS: // switch(inputEvent) - DUMP_ALL_CONTROL_POINTS
    {
      retVal = 1;
      dumpAllCaptures();
      clearAllControlPoint();
    }
    break; // switch(inputEvent) - DUMP_ALL_CONTROL_POINTS

    ////////////////////////////////////////////////////////
    case CAPTURE_TRANSLATE: // switch(inputEvent) - CAPTURE_TRANSLATE
    {
      retVal = 1;
      dumpAllCaptures();
      captureAction = dragTranslate;
    }
    break; // switch(inputEvent) - CAPTURE_TRANSLATE

    case CAPTURE_SCALE: // switch(inputEvent) - CAPTURE_SCALE
    {
      retVal = 1;
      dumpAllCaptures();
      captureAction = dragScale;
    }
    break; // switch(inputEvent) - CAPTURE_SCALE

    ////////////////////////////////////////////////////////
    case CAPTURE_ROTATE: // switch(inputEvent) - CAPTURE_ROTATE
    {
      retVal = 1;
      dumpAllCaptures();
      captureAction = dragRotate;
    }
    break; // switch(inputEvent) - CAPTURE_ROTATE

    case REMOVE_CONTROL_POINT: // switch(inputEvent) - REMOVE_CONTROL_POINT
    {
      retVal = 1;
      dumpAllCaptures();
      removeControlPoint();
    }
    break; // switch(inputEvent) - REMOVE_CONTROL_POINT
    ////////////////////////////////////////////////////////
    case TOGGLE_SHELLS: // switch(inputEvent) - TOGGLE_SHELLS
    {
      retVal = 1;
      dumpAllCaptures();

      if(shellBl == true)
      {
        shellBl = false;
      }
      else
      {
        shellBl = true;
      }
    }
    break; // switch(inputEvent) - TOGGLE_SHELLS

    ////////////////////////////////////////////////////////
    case MENU_INPUT: // switch(inputEvent) - MENU_INPUT
    {
      retVal = 1;
      dumpAllCaptures();
      clearAllControlPoint();

      union
      {
      double *p;
      double f;

      }menu;

      memset( &menu, 0, sizeof(menu) );

#define f menu.f
#define p menu.p

      f = yB;

      // p[0] == degree
      //
      // if degree == 3
      // Fx(t) = a * t^3 + b * t^2 + c * t^1 + d * t^0
      // fx(t1, t2, t3) = a * t1 * t2 * t3 +
      //                    b * (t1 * t2 + t1 * t3 + t2 * t3) / 3 +
      //                    c * (t1 + t2 + t3) +
      //                    d * t^0
      //
      // p[ 1 ] == d
      // p[ 2 ] == c
      // p[ 3 ] == b
      // p[ 4 ] == a
      //
      // if degree == 3
      // Fy(t) = e * t^3 + f * t^2 + g * t^1 + h * t^0
      // fy(t1, t2, t3) = e * t1 * t2 * t3 +
      //                    f * (t1 * t2 + t1 * t3 + t2 * t3) / 3 +
      //                    g * (t1 + t2 + t3) +
      //                    h * t^0
      //
      // p[ 5 ] == h
      // p[ 6 ] == g
      // p[ 7 ] == f
      // p[ 8 ] == e
      //
      // p[ 9  ] == h
      // p[ 10 ] == g
      // p[ 11 ] == f
      // p[ 12 ] == e
      //
      // p[ 13 ] == pointer to unordered array of doubles (the knot list)
      // p[ 14 ] == the number of knots
      //
      // affine frame (r, s)
      // p[ 15 ] == r
      // p[ 16 ] == s

      // input point (x * B, y * B, B)
      // p[ 17 ] == x
      // p[ 18 ] == y
      // p[ 19 ] == B

      int degree = fti(p[0] );

      if(degree < 0 || degree > 3)
      {
      break;
      }

      r = p[ 15 ];
      s = p[ 16 ];

      double *_knotList = * ( (double**) ( &p[ 13 ] ) );

      int _numKnots = p[ 14 ];

      if(_knotList && _numKnots > 0)
      {
      // Put the knots in ascending order, and make sure that there
      // are no knots with multiplicity greater that degree + 1.
      list< double > sort;

      int loop = 0;

      // Put the knots in ascending order.
      for(loop = 0; loop != _numKnots; loop++)
      {
      sort.push_back(_knotList[ loop ] );
      }

      sort.sort();

      double knotValue = sort.front();

      int knotMultiplicity = 0;

      // Check for multiplicity greater than degree + 1 as the knots
      // are inserted into the active knot list.
      for(loop = 0; loop != _numKnots; loop++)
      {
      if(eq(sort.front(), knotValue) )
      {
      knotMultiplicity++;
      }
      else
      {
      knotValue = sort.front();

      knotMultiplicity = 1;
      }

      if(knotMultiplicity <= degree + 1)
      {
      knots.push_back(sort.front() );
      }

      sort.pop_front();
      }

      if( !sort.empty() )
      {
      sort.clear();
      }
      }

      while(knots.size() < 5)
      {
      knots.push_back(knots.back() + 1);
      }

      t = knots[ degree ] + (knots.back() - knots[ degree ] ) * 0.5;

      inputPrv = inputCur;

      point inputTemp = point(p[ 17 ] * p[ 19 ], p[ 18 ] * p[ 19 ], p[ 19 ] );

      inputCur = inputTemp;

      switch(degree) // switch(inputEvent) - MENU_INPUT; switch(degree)
      {

      case 0: // switch(inputEvent) - MENU_INPUT; switch(degree) - 0
      {
        // Fx() = d * t^0
        // Fy() = h * t^0
        //
        // fx() = d
        // fy() = h
        //
        // p0 = (fx(), fy() )

        inputCur = point(blossom(0, p[ 1 ] ),
        -blossom(0, p[ 5 ] ),
        blossom(0, p[ 9 ] )
        );

        addControlPoint();

        inputCur = inputTemp;
      }
      break; // switch(inputEvent) - MENU_INPUT; switch(degree) - 0

      case 1: // switch(inputEvent) - MENU_INPUT; switch(degree) - 1
      {
        // Fx(t) = c * t^1 + d * t^0
        // Fy(t) = g * t^1 + h * t^0
        //
        // fx(t1) = c * t1 + d
        // fy(t1) = g * t1 + h
        //
        // p0 = (fx(r), fy(r) )
        // p1 = (fx(s), fy(s) )

        inputCur = point(blossom(1, p[ 2  ], p[ 1 ], r),
        -blossom(1, p[ 6  ], p[ 5 ], r),
        blossom(1, p[ 10 ], p[ 9 ], r)
        );

        addControlPoint();

        inputCur = point(blossom(1, p[ 2 ],  p[ 1 ], s),
        -blossom(1, p[ 6 ],  p[ 5 ], s),
        blossom(1, p[ 10 ], p[ 9 ], s)
        );

        addControlPoint();

        inputCur = inputTemp;
      }
      break; // switch(inputEvent) - MENU_INPUT; switch(degree) - 1

      case 2: // switch(inputEvent) - MENU_INPUT; switch(degree) - 2
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

        inputCur = point(blossom(2, p[ 3  ], p[ 2  ], p[ 1 ], r, r),
        -blossom(2, p[ 7  ], p[ 6  ], p[ 5 ], r, r),
        blossom(2, p[ 11 ], p[ 10 ], p[ 9 ], r, r)
        );

        addControlPoint();

        inputCur = point(blossom(2, p[ 3  ], p[ 2  ], p[ 1 ], r, s),
        -blossom(2, p[ 7  ], p[ 6  ], p[ 5 ], r, s),
        blossom(2, p[ 11 ], p[ 10 ], p[ 9 ], r, s)
        );

        addControlPoint();

        inputCur = point(blossom(2, p[ 3  ], p[ 2  ], p[ 1 ], s, s),
        -blossom(2, p[ 7  ], p[ 6  ], p[ 5 ], s, s),
        blossom(2, p[ 11 ], p[ 10 ], p[ 9 ], s, s)
        );

        addControlPoint();

        inputCur = inputTemp;
      }
      break; // switch(inputEvent) - MENU_INPUT; switch(degree) - 2

      case 3: // switch(inputEvent) - MENU_INPUT; switch(degree) - 3
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

        inputCur = point(blossom(3, p[ 4 ], p[ 3 ], p[ 2 ], p[ 1 ], r, r, r),
        -blossom(3, p[ 8 ], p[ 7 ], p[ 6 ], p[ 5 ], r, r, r),
        blossom(3, p[ 8 ], p[ 7 ], p[ 6 ], p[ 5 ], r, r, r)
        );

        addControlPoint();

        inputCur = point(blossom(3, p[ 4  ], p[ 3  ], p[ 2  ], p[ 1 ], r, r, s),
        -blossom(3, p[ 8  ], p[ 7  ], p[ 6  ], p[ 5 ], r, r, s),
        blossom(3, p[ 12 ], p[ 11 ], p[ 10 ], p[ 9 ], r, r, s)
        );

        addControlPoint();

        inputCur = point(blossom(3, p[ 4  ], p[ 3  ], p[ 2  ], p[ 1 ], r, s, s),
        -blossom(3, p[ 8  ], p[ 7  ], p[ 6  ], p[ 5 ], r, s, s),
        blossom(3, p[ 12 ], p[ 11 ], p[ 10 ], p[ 9 ], r, s, s)
        );

        addControlPoint();

        inputCur = point(blossom(3, p[ 4  ], p[ 3  ], p[ 2  ], p[ 1 ], s, s, s),
        -blossom(3, p[ 8  ], p[ 7  ], p[ 6  ], p[ 5 ], s, s, s),
        blossom(3, p[ 12 ], p[ 11 ], p[ 10 ], p[ 9 ], s, s, s)
        );

        addControlPoint();

        inputCur = inputTemp;
      }
      break; // switch(inputEvent) - MENU_INPUT; switch(degree) - 3

      } // switch(inputEvent) - MENU_INPUT; switch(degree)

#undef p
#undef f
    }
    break; // switch(inputEvent) - MENU_INPUT

    ////////////////////////////////////////////////////////
    case DUMP_ALL_CAPTURES: // switch(inputEvent) - DUMP_ALL_CAPTURES
    {
      retVal = 1;
      dumpAllCaptures();
    }
    break; // switch(inputEvent) - DUMP_ALL_CAPTURES
    
    ////////////////////////////////////////////////////////
    case TOGGLE_CONTROL_POINTS: // switch(inputEvent) - TOGGLE_CONTROL_POINTS
    {
      retVal = 1;
      dumpAllCaptures();

      if(ctrlBl == true)
      {
      ctrlBl = false;
      }
      else
      {
      ctrlBl = true;
      }
    }
    break; // switch(inputEvent) - TOGGLE_CONTROL_POINTS
    
    ////////////////////////////////////////////////////////
    case INCREASE_ITERATION_CONSTANT: // switch(inputEvent) - INCREASE_ITERATION_CONSTANT
    {
      ++iterateConstant;
    }
    break; // switch(inputEvent) - INCREASE_ITERATION_CONSTANT

    ////////////////////////////////////////////////////////
    case DECREASE_ITERATION_CONSTANT: // switch(inputEvent) - DECREASE_ITERATION_CONSTANT
    {
      if(iterateConstant > 1)
      {
      --iterateConstant;
      }
    }
    break; // switch(inputEvent) - DECREASE_ITERATION_CONSTANT

    ////////////////////////////////////////////////////////
    case TOGGLE_CONTROL_POINT_TEXT: // switch(inputEvent) - TOGGLE_CONTROL_POINT_TEXT
    {
      retVal = 1;
      dumpAllCaptures();

      if(dispK == true)
      {
      dispK = false;
      }
      else
      {
      dispK = true;
      }
    }
    break; // switch(inputEvent) - TOGGLE_CONTROL_POINT_TEXT

    ////////////////////////////////////////////////////////
    default: // switch(inputEvent) - default
    {
    }
    return retVal; // switch(inputEvent) - default

    ////////////////////////////////////////////////////////

    } // switch(inputEvent)

    if(numControlPts == 0)
    {
      return retVal;
    }

    // Call capture action function pointer.
    if(captureAction && inputPrv != inputCur)
    {
      minMaxT = 0;
      shellT = 0;

      retVal = 1;

      (this->*captureAction)();
    }

    return retVal;

  } // de_boor::updateInput

  // Call every program loop to draw F(x), the control points,
  // F(t), and the shells for F(t).
  void updateDraw() // de_boor::updateDraw
  {
    if(numControlPts == 0)
    {
      return;
    }

    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    if(numControlPts < 2 * degree + 1)
    {
      if(ctrlBl == true && fti(minMaxT) == 0)
      {
        point _temp;

        for(int loop = 0; loop < numControlPts; loop++)
        {
          _temp = tranPt[ loop ];

          drawCircle(_temp, (loop == (capturedControlPt - 1) )? 15: 10, loop + 1);

          if(dispK == true && _temp.isProjectable() )
          {
            _temp = _temp.projectTo2D();

            textDrawingPrimitive(_temp.x, _temp.y, "d0,%i", (int) loop);

            _temp.y += 14.0;

            textDrawingPrimitive(_temp.x, _temp.y, "%i", (int) knots[ loop + 1 ] );

            int loopDegree = 0;

            while(++loopDegree != degree)
            {
              _temp.y += 14.0;

              textDrawingPrimitive(_temp.x, _temp.y, "%i", (int) knots[ loop + loopDegree + 1 ] );
            }
          }
        }
      }

      minMaxT = 1;

      return;
    }

    point p0, p1;

    point weight;

    if(fti(minMaxT) == 0)
    {
      while( !subdWt.empty() )
      {
        subdWt.pop();
      }

      double weight = (knots.back() - knots[ degree ] ) * 0.5;

      p1 = do_de_Boor(knots[ degree ] + weight);

      subdWt.push(pairQS(p1, point(knots[ degree ] + weight, weight) ) );

      minMaxT = 1;
    }

    int loop = -1;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    while( !subdWt.empty() && ++loop < 20 * (1 + iterateConstant) )
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
      p1 = do_de_Boor(weight.x - weight.y * 0.5);

      // Check if the left child is the same point as the parent
      if(p0 == p1)
      {
        // Do not do anything if they are the same point.
      }
      else
      {
        // Draw and branch out the left child if the points are different.
        subdWt.push(pairQS(p1, point(weight.x - weight.y * 0.5, weight.y * 0.5) ) );
      }

      // Right Child's weight == weight.x + weight.y * 0.5.
      p1 = do_de_Boor(weight.x + weight.y * 0.5);

      // Check if the right child is the same point as the parent
      if(p0 == p1)
      {
        // Do not do anything if they are the same point.
      }
      else
      {
        // Draw and branch out the right child if the points are different.
        subdWt.push(pairQS(p1, point(weight.x + weight.y * 0.5, weight.y * 0.5) ) );
      }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////

    loop = -1;

    if(shellT == 0)
    {
      ++loop;

      shellT = 2;

      if(shellBl == true)
      {
        int u1 = 0;

        point d0, d1;

        for(int d = 0; d < numControlPts - 1; d++)
        {
          d0 = tranPt[ d ];

          d1 = tranPt[ d + 1 ];

          u1 = d + degree + 1;

          if(u1 >= knots.size() )
          {
            u1 = knots.size() - 1;
          }

          for(int u = d + 1; u < u1; u++)
          {
            if(u + 1 < knots.size() && !eq(knots[ u ], knots[ u + 1 ] ) )
            {
              drawLine(d0 + (d1 - d0) * ( (knots[ u ] - knots[ d + 1 ] ) / (knots[ u1 ] - knots[ d + 1 ] ) ), d0 + (d1 - d0) * ( (knots[ u + 1 ] - knots[ d + 1 ] ) / (knots[ u1 ] - knots[ d + 1 ] ) ), u);
            }
          }
        }
      }

      if(ctrlBl == true)
      {
        point _temp;

        for(int currentPtIndex = 0; currentPtIndex < numControlPts; currentPtIndex++)
        {
          _temp = tranPt[ currentPtIndex ];

          drawCircle(_temp, (currentPtIndex == (capturedControlPt - 1) )? 15 : 10, currentPtIndex + 1);

          if(dispK == true && _temp.isProjectable() )
          {
            _temp = _temp.projectTo2D();

            textDrawingPrimitive(_temp.x, _temp.y, "d0,%i", (int) currentPtIndex);

            _temp.y += 14.0;

            textDrawingPrimitive(_temp.x, _temp.y, "%i", (int) knots[ currentPtIndex + 1 ] );

            int loopDegree = 0;

            while(++loopDegree != degree)
            {
              _temp.y += 14.0;

              textDrawingPrimitive(_temp.x, _temp.y, "%i", (int) knots[ currentPtIndex + loopDegree + 1 ] );
            }
          }
        }
      }

      // Calculate/draw shells and F(t) (for F(t) from the user-inputted t).
      do_de_Boor(t, true);
    }

  } // de_boor::updateDraw

  private:

  // The blossom is used to compute the control points when receiving menu input.
  //
  // Possible inputs:
  // blossom(0, d);
  // blossom(1, c, d, t1);
  // blossom(2, b, c, d, t1, t2);
  // blossom(3, a, b, c, d, t1, t2, t3);
  double blossom(int degree, ...) // de_boor::blossom
  {
    double a = 0, b = 0, c = 0, d = 0;

    double t1 = 0, t2 = 0, t3 = 0;

    if(degree < 0 || degree > 3)
    {
      assert(0 && "Bad blossom() degree");
    }

    va_list argptr = 0;

    va_start(argptr, degree);

    switch(degree) // switch(degree)
    {

    case 0: // switch(degree) - 0
    {
      d = va_arg(argptr, double);

      va_end(argptr);
    }
    return d; // switch(degree) - 0

    case 1: // switch(degree) - 1
    {
      c = va_arg(argptr, double);
      d = va_arg(argptr, double);

      t1 = va_arg(argptr, double);

      va_end(argptr);
    }
    return c * t1 + d; // switch(degree) - 1

    case 2: // switch(degree) - 2
    {
      b = va_arg(argptr, double);
      c = va_arg(argptr, double);
      d = va_arg(argptr, double);

      t1 = va_arg(argptr, double);
      t2 = va_arg(argptr, double);

      va_end(argptr);
    }
    return b * t1 * t2 + c * (t1 + t2) / 2.0 + d; // switch(degree) - 2

    case 3: // switch(degree) - 3
    {
      a = va_arg(argptr, double);
      b = va_arg(argptr, double);
      c = va_arg(argptr, double);
      d = va_arg(argptr, double);

      t1 = va_arg(argptr, double);
      t2 = va_arg(argptr, double);
      t3 = va_arg(argptr, double);

      va_end(argptr);
    }
    return a * t1 * t2 * t3 + b * (t1 * t2 + t1 * t3 + t2 * t3) / 3.0 + c * (t1 + t2 + t3) / 3.0 + d; // switch(degree) - 3

    } // switch(degree)

    assert(0 && "Bad blossom() degree");

    return 0;

  } // de_boor::blossom

  point do_de_Boor(double dt, bool draw = false) // de_boor::do_de_Boor
  {
    point temp(-1, -1);

    if(dt < knots.front() || dt > knots.back() || eq(dt, knots.back() ) )
    {
      return temp;
    }

    if(knots.size() < degree + 1 || tranPt.size() < degree + 1)
    {
      return temp;
    }

    // get the middle interval of the knots
    // get k of [ u(k), u(k+1) )
    int I = -1;

    // binary search, i is left, j is right, k is middle
    int i = 0, j = knots.size() - 1, k = 0;

    while(j >= i)
    {
      k = (i + j) / 2;

      if( (knots[ k ] < dt || eq(knots[ k ], dt) ) && dt < knots[ k + 1 ] )
      {
        I = k;

        break;
      }

      if(dt < knots[ k ] )
      {
        j = k - 1;
      }
      else
      {
        i = k + 1;
      }
    }

    if(I - degree < 0)
    {
      return temp;
    }

    int r = 0;

    if(eq(dt, knots[I] ) )
    {
      // get the multiplicity of the knot
      r = 1;

      if(I > 0)
      {
        i = I - 1;

        while(i >= 0)
        {
          if(eq(dt, knots[i] ) )
          {
            r++;
          }
          else
          {
            break;
          }

          i--;
        }
      }

      if(knots.size() > I + 1)
      {
        j = I + 1;

        while(knots.size() > j)
        {
          if(eq(dt, knots[j] ) )
          {
            r++;
          }
          else
          {
            break;
          }

          j++;
        }
      }

      if(r < 1 || r > degree + 1)
      {
        return temp;
      }
    }

    for(i = I - degree, j = 0; i <= I - r; i++, j++)
    {
      tempPt[j] = tranPt[i];
    }

    for(j = 1; j <= degree - r; j++)
    {
      for(i = I - degree + j, k = 0; i <= I - r; i++, k++)
      {
        tempPt[k] = ( (knots[degree + i - j + 1] - dt) / (knots[degree + i - j + 1] - knots[i] ) ) * tempPt[k] + ( (dt - knots[i] ) / (knots[degree + i - j + 1] - knots[i] ) ) * tempPt[k + 1];
      }

      if(draw == true)
      {
        for(i = I - degree + j, k = 0; i <= I - r - 1; i++, k++)
        {
          drawLine(tempPt[k], tempPt[k + 1], I);
        }
      }
    }

    temp = tempPt[0];

    if(draw == true)
    {
      drawCircle(temp, 5, I);
    }
    else
    {
      drawPoint(temp, I);
    }

    return temp;

  } // de_boor::do_de_Boor

  // Wrapper for easily calling circleDrawingPrimitive().
  void drawCircle(point center, int radius, int knotIndex) // de_boor::drawCircle
  {
    if(circleDrawingPrimitive)
    {
      if(center.x < -2000000000 || center.x > 2000000000 || center.y < -2000000000 || center.y > 2000000000)
      {
        return;
      }

      if(center.isProjectable() == true)
      {
        center = center.projectTo2D();

        circleDrawingPrimitive(fti(center.x), fti(center.y), radius, colors0[ (int)knots[knotIndex % 100] % 100], colors0[ (int)knots[knotIndex % 100] % 100] );
      }
    }

  } // de_boor::drawCircle

  // Wrapper for easily calling lineDrawingPrimitive().
  void drawLine(point start, point end, int knotIndex) // de_boor::drawLine
  {
    if(lineDrawingPrimitive)
    {
      if(start.x < -2000000000 || start.x > 2000000000 || start.y < -2000000000 || start.y > 2000000000 || end.x < -2000000000 || end.x > 2000000000 || end.y < -2000000000 || end.y > 2000000000)
      {
        return;
      }

      if(start.isProjectable() == true && end.isProjectable() == true)
      {
        start = start.projectTo2D();

        end = end.projectTo2D();

        lineDrawingPrimitive(fti(start.x), fti(start.y), fti(end.x), fti(end.y), colors0[ (int)knots[knotIndex % 100] % 100], colors0[ (int)knots[knotIndex % 100] % 100] );
      }
    }

  } // de_boor::drawLine

  // Wrapper for easily calling pointDrawingPrimitive().
  void drawPoint(point center, int knotIndex) // de_boor::drawPoint
  {
    if(pointDrawingPrimitive)
    {
      if(center.x < -2000000000 || center.x > 2000000000 || center.y < -2000000000 || center.y > 2000000000)
      {
        return;
      }

      if(center.isProjectable() == true)
      {
        center = center.projectTo2D();

        pointDrawingPrimitive(fti(center.x), fti(center.y), colors0[ (int)knots[knotIndex % 100] % 100] );
      }
    }

  } // de_boor::drawPoint

  // When the user adds another control point, add that control point in the
  // list right after the previous control point.
  //
  // Also add an extra point to the end of the list, used as temporary storage
  // while evaluating the de Boor algorithm.
  void addControlPoint() // de_boor::addControlPoint
  {
    // Add the new control point to the list.
    numControlPts++;

    shelPt.push_back(inputCur);
    tranPt.push_back(inputCur);

    int loop;

    if(numControlPts > degree + 1)
    {
      for(loop = 0; loop < degree; loop++)
      {
        knots.pop_back();
      }

      knots.push_back(knots.back() + 1);

      for(loop = 0; loop < degree; loop++)
      {
        knots.push_back(knots.back() );
      }
    }
    else if(numControlPts == 1)
    {
      for(loop = 0; loop < degree + 1; loop++)
      {
        knots.push_back(0);
      }

      for(loop = 0; loop < degree + 1; loop++)
      {
        knots.push_back(1);
      }
    }

  } // de_boor::addControlPoint

  // Captures the closest control point, for user manipulation.
  void captureControlPoint() // de_boor::captureControlPoint
  {
    double distMin;

    // Starting with the first control point, and doing the same with all ctrl pts,
    // calculate the distance between the input pt and each ctrl pt.
    //
    // The ctrl pt that is closest to the input pt is the pt that is captured.
    // The index of the closest ctrl pt is stored in capturedControlPt,
    // and the captureAction() function is activated to point to the dragControlPoint()
    // function.
    capturedControlPt = 0;
    distMin = inputCur.dist(tranPt[capturedControlPt] );

    for(int currentPtIndex = 1; currentPtIndex < numControlPts; currentPtIndex++)
    {
      if(distMin > inputCur.dist(tranPt[currentPtIndex] ) )
      {
        distMin = inputCur.dist(tranPt[currentPtIndex] );

        capturedControlPt = currentPtIndex;
      }
    }

    capturedControlPt++;

    captureAction = dragControlPoint;

  } // de_boor::captureControlPoint

  // Captures t of F(t)
  void capture_t_of_F_of_t() // de_boor::capture_t_of_F_of_t
  {
    // Find the minimum and maximum values of the coordinate pts,
    // which are needed to normalize input.
    minPt.x = maxPt.x = tranPt[0].x;
    minPt.y = maxPt.y = 0;

    for(int currentPtIndex = 1; currentPtIndex < numControlPts; currentPtIndex++)
    {
      if(minPt.x > tranPt[currentPtIndex].x)
      {
        minPt.x = tranPt[currentPtIndex].x;
      }

      if(maxPt.x < tranPt[currentPtIndex].x)
      {
        maxPt.x = tranPt[currentPtIndex].x;
      }
    }

    // Once t can be normalized, activate the captureAction() function to
    // point to the drag_t_of_F_of_t() function.
    //
    // The new t will be calculated in the drag_t_of_F_of_t() function.
    captureAction = drag_t_of_F_of_t;

  } // de_boor::capture_t_of_F_of_t

  // When the user chooses to clear all ctrl pts, to start a new curve,
  // erase all elements in the control point list.
  void clearAllControlPoint() // de_boor::clearAllControlPoint
  {
    shelPt.clear();
    tranPt.clear();

    knots.clear();

    while( !subdWt.empty() )
    {
      subdWt.pop();
    }

    numControlPts = 0;

  } // de_boor::clearAllControlPoint

  // This function is called thru the captureAction() function, when the user wants
  // to manipulate t of F(t).
  void drag_t_of_F_of_t() // de_boor::drag_t_of_F_of_t
  {
    if(inputCur.x <= minPt.x)
    {
      inputCur.x = minPt.x + 1;
    }

    if(inputCur.x >= maxPt.x)
    {
      inputCur.x = maxPt.x - 1;
    }

    t = (inputCur.x - minPt.x) / fabs(maxPt.x - minPt.x);

    // Scale the t value to the magnitude of the knot sequence values.
    t *= (knots.back() - knots[degree] );

    // Translate t to start at the smallest knot value.
    t += knots[degree];

  } // de_boor::drag_t_of_F_of_t

  // This function is called thru the captureAction() function, when the user wants
  // to manipulate a control pt.
  void dragControlPoint() // de_boor::dragControlPoint
  {
    // Drag the captured ctrl pt relative to input movement between
    // the current input pt and the previous input pt.
    tranPt[capturedControlPt - 1] += inputCur - inputPrv;

  } // de_boor::dragControlPoint

  // When a new user request has occured, flush any older user requests
  // currently being processed.
  void dumpAllCaptures() // de_boor::dumpAllCaptures
  {
    capturedControlPt = 0;
    captureAction = 0;

    minMaxT = 0;
    shellT = 0;

  } // de_boor::dumpAllCaptures

  void dragTranslate() // de_boor::dragTranslate
  {
    point p;

    iteratorDP a = tranPt.begin();

    for(int index = 0; index < numControlPts; index++, a++)
    {
      p = *a;

      a->x = p.x + (inputCur.x - inputPrv.x);
      a->y = p.y + (inputCur.y - inputPrv.y);
      a->z = p.z;
    }

  } // de_boor::dragTranslate

  void dragScale() // de_boor::dragScale
  {
    double s = 1.0 + (inputCur.y - inputPrv.y) / (halfWidth * 2);

    double tx = (1 - s) * halfWidth;
    double ty = (1 - s) * halfHeight;

    point p;

    iteratorDP a = tranPt.begin();

    for(int index = 0; index < numControlPts; index++, a++)
    {
      p = *a;

      a->x = p.x * s + tx;
      a->y = p.y * s + ty;
      a->z = p.z;
    }

  } // de_boor::dragScale

  void dragRotate() // de_boor::dragRotate
  {
    double angle = (inputCur.x - inputPrv.x) / 180.0;

    double c = cos(angle);
    double s = sin(angle);

    double tx = halfWidth;
    double ty = halfHeight;

    point p;

    iteratorDP a = tranPt.begin();

    for(int index = 0; index < numControlPts; index++, a++)
    {
      p = *a;

      a->x = s * (-p.y + ty) + c * (p.x - tx) + tx;
      a->y = s * (p.x - tx) + c * (p.y - ty) + ty;
      a->z = p.z;
    }

  } // de_boor::dragRotate

  void removeControlPoint() // de_boor::removeControlPoint
  {
    int ctrlPt;

    double distMin;

    // Starting with the first control point, and doing the same with all ctrl pts,
    // calculate the distance between the input pt and each ctrl pt.
    //
    // The ctrl pt that is closest to the input pt is the pt that is deleted.
    ctrlPt = 0;
    distMin = inputCur.dist(tranPt[ctrlPt] );

    for(int currentPtIndex = 1; currentPtIndex < numControlPts; currentPtIndex++)
    {
      if(distMin > inputCur.dist(tranPt[currentPtIndex] ) )
      {
        distMin = inputCur.dist(tranPt[currentPtIndex] );

        ctrlPt = currentPtIndex;
      }
    }

    shelPt.erase(shelPt.begin() + ctrlPt);
    tranPt.erase(tranPt.begin() + ctrlPt);

    --numControlPts;

    // Now create new knot list

    // example old knot list (for cubic)
    // u0 u1 u2 u3 u4 u5 u6 u7 u8 u9
    //          d0 d1 d2 d3 d4 d5 d6...
    // F0: [u3,u4) {d0,d1,d2,d3}
    // F1: [u4,u5) {d1,d2,d3,d4}
    // F2: [u5,u6) {d2,d3,d4,d5}
    // F3: [u6,u7) {d3,d4,d5,d6}

    // Step 1) If you remove control point di,
    // then remove knot ui.  The multiples of ui
    // also stay.
    //
    // Step 2)
    //     a: If ui had a multiplicity greater than 1, you are done.
    //
    //     b: If ui was a simple knot, then all knots with values greater
    //        that ui have their values reduced by 1.

    // example: delete control point d3
    // 0  0  1  2  2  3  4  5  6  7
    // u0 u1 u2 u3 u4 u5 u6 u7 u8 u9
    //          d0 d1 d2 d3 d4 d5 d6...
    // becomes:
    // 0      0      1      2      3      4      5      6      7
    // u0'=u0 u1'=u1 u2'=u2 u3'=u4 u4'=u5 u5'=u6 u6'=u6 u7'=u8 u8'=u9
    //                      d0'=d0 d1'=d1 d2'=d2 d3'=d4 d4'=d5 d5'=d6...

    // example: delete control point d2
    // 0  0  1  2  2  3  4  5  6  7
    // u0 u1 u2 u3 u4 u5 u6 u7 u8 u9
    //          d0 d1 d2 d3 d4 d5 d6...
    // becomes:
    // 0      0      2=1+1    3=2+1    3=2+1    4=3+1    5=4+1    6=5+1    7=6+1
    // u0'=u0 u1'=u1 u2'=u3+1 u3'=u4+1 u4'=u5+1 u5'=u6+1 u6'=u6+1 u7'=u8+1 u8'=u9+1
    //                        d0'=d0   d1'=d1   d2'=d3   d3'=d4   d4'=d5   d5'=d6...
    if(ctrlPt > 0 && eq(knots[ctrlPt - 1], knots[ctrlPt] ) )
    {
      // Just remove the knot ui since the multiplicity is greater than one.
    }
    else if(knots.size() > ctrlPt + 1 && eq(knots[ctrlPt], knots[ctrlPt + 1] ) )
    {
      // Just remove the knot ui since the multiplicity is greater than one.
    }
    else
    {
      // The knot ui has multiplicity 1, so increment all knots with values
      // greater than ui by one (increment their values by one).
      for(iterVK knot = knots.begin() + ctrlPt + 1; knot != knots.end(); knot++)
      {
        *knot += 1;
      }

      // Then remove the knot ui.
    }

    knots.erase(knots.begin() + ctrlPt);

  } // de_boor::removeControlPoint

}; // class de_boor

const double de_Boor::E = 0.000001;

typedef deque< de_Boor* > dequeB;
typedef dequeB::iterator iteratorDB;

static dequeB *deBoorList = 0;
static iteratorDB deBoorIter;

enum
{
  ERROR = -1,
  OK = 0
};

extern "C" extern int init(double _halfWidth, double _halfHeight, void(*_circleDrawingPrimitive)(int, int, int, int, int), void(*_lineDrawingPrimitive)(int, int, int, int, int, int), void(*_pointDrawingPrimitive)(int, int, int), void(*_textDrawingPrimitive)(int, int, const char* const, ...) )
{
  // Initialize the random number generator.
  srand(time(0) );

  if( !deBoorList)
  {
    if(_halfWidth <= 0 || _halfHeight <= 0 || !_circleDrawingPrimitive || !_lineDrawingPrimitive || !_pointDrawingPrimitive || !_textDrawingPrimitive)
    {
      return ERROR;
    }

    deBoorList = new dequeB;

    if( !deBoorList)
    {
      return ERROR;
    }

    deBoorList->push_back(new de_Boor);

    if( !(*deBoorList)[0] )
    {
      return ERROR;
    }

    (*deBoorList)[0]->setPrimitiveDrawingFunctions(_halfWidth, _halfHeight, _circleDrawingPrimitive, _lineDrawingPrimitive, _pointDrawingPrimitive, _textDrawingPrimitive);

    deBoorIter = deBoorList->begin();
  }

  if( !(*deBoorList)[0] || deBoorIter != deBoorList->begin() )
  {
    return ERROR;
  }

  return OK;
}

extern "C" extern int main(int inputEvent, double x, double y, double B, double _halfWidth, double _halfHeight)
{
  if( !deBoorList || deBoorList->size() == 0)
  {
    return ERROR;
  }

  if(deBoorIter == deBoorList->end() || *deBoorIter == 0)
  {
    deBoorIter = deBoorList->begin();
  }

  if(_halfWidth <= 0 || _halfHeight <= 0)
  {
    return ERROR;
  }

  int retVal = 0;

  iteratorDB temp; // init todo

  de_Boor* curve = 0;

  switch(inputEvent) // switch(inputEvent)
  {

  case de_Boor::ADD_DE_BOOR_CURVE: // switch(inputEvent) - de_Boor::ADD_DE_BOOR_CURVE
  {
    curve = new de_Boor;

    if( !curve)
    {
      return ERROR;
    }

    curve->setPrimitiveDrawingFunctions(**deBoorIter);

    deBoorList->push_back(curve);

    deBoorIter = deBoorList->end() - 1;
  }
  break; // switch(inputEvent) - de_Boor::ADD_DE_BOOR_CURVE

  case de_Boor::REMOVE_DE_BOOR_CURVE: // switch(inputEvent) - de_Boor::REMOVE_DE_BOOR_CURVE
  {
    if(deBoorList->size() == 1)
    {
      inputEvent = de_Boor::DUMP_ALL_CONTROL_POINTS;
    }
    else
    {
      delete *deBoorIter;

      deBoorList->erase(deBoorIter);

      deBoorIter = deBoorList->begin();

      retVal |= 1;

      inputEvent = de_Boor::DUMP_ALL_CAPTURES;
    }
  }
  break; // switch(inputEvent) - de_Boor::REMOVE_DE_BOOR_CURVE

  case de_Boor::TRAVERSE_DE_BOOR_CURVE_LIST: // switch(inputEvent) - de_Boor::TRAVERSE_DE_BOOR_CURVE_LIST
  {
    ++deBoorIter;

    if(deBoorIter == deBoorList->end() )
    {
      deBoorIter = deBoorList->begin();
    }
  }
  break; // switch(inputEvent) - de_Boor::TRAVERSE_DE_BOOR_CURVE_LIST

  } // switch(inputEvent)

  iteratorDB loop;

  (*deBoorIter)->setPrimitiveDrawingFunctions(_halfWidth, _halfHeight, 0, 0, 0, 0);

  (*deBoorIter)->updateDraw();

  retVal |= (*deBoorIter)->updateInput(inputEvent, x * B, y * B, B);

  for(loop = deBoorList->begin(); loop != deBoorList->end(); loop++)
  {
    if(loop != deBoorIter)
    {
      (*loop)->setPrimitiveDrawingFunctions(_halfWidth, _halfHeight, 0, 0, 0, 0);

      (*loop)->updateDraw();
    }

    if( (retVal != 0 || inputEvent == de_Boor::DUMP_ALL_CAPTURES) && loop != deBoorIter)
    {
      retVal |= (*loop)->updateInput(de_Boor::DUMP_ALL_CAPTURES, x * B, y * B, B);
    }
  }

  return retVal;
}

extern "C" extern int term()
{
  iteratorDB loop;

  if(deBoorList)
  {
    deBoorIter = deBoorList->end();

    for(loop = deBoorList->begin(); loop != deBoorList->end(); loop++)
    {
      if(*loop)
      {
        delete *loop;
        *loop = 0;
      }
    }

    deBoorList->clear();

    delete deBoorList;
    deBoorList = 0;
  }

  return OK;
}