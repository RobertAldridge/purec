
// deBoor.cpp
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

//#include <cassert>
//#include <cmath>
//#include <ctime>
//#include <cstdarg>

//#include <iostream>
//#include <deque>
///#include <list>
//#include <queue>
//#include <vector>

#include "ssArray.h"
#include "ssStack.h"
#include "ssQueue.h"
#include "ssSet.h"

#include "BlahLog.h"

//using namespace std;

//using std::deque;
//using std::list;
//using std::vector;

extern void* operator new(size_t size);

extern void* operator new[](size_t size);

extern void operator delete(void* ptr);

extern void operator delete[](void* ptr);

static uint32_t deBoorListSsSetCompare(void* lhsRef, void* rhsRef);

static uint32_t doubleSsSetCompare(void* lhsRef, void* rhsRef);

class deBoor // deBoor
{

// Epsilon:
//    If num - floor(num) <= E, then num = floor(num).
//    If ceiling(num) - num <= E, then num = ceiling(num).
//
// Both are always true, even when truncating from double to int.
static const double E;

// function convert float to int
static int fti(double f) // deBoor::fti
{
  return (f - floor(f) <= E) ? (int)floor(f) : ( (ceil(f) - f <= E) ? (int)ceil(f) : (int)f);

} // deBoor::fti

static int eq(double a, double b) // deBoor::eq
{
  return fabs(a - b) <= E;

} // deBoor::eq

// A little 2D point class, makes stuff easier.
class point // point
{

public:

// x, y, and z coordinates of a 3D point with respect to the standard origin.
double x;
double y;
double z;

// Easy way to create a point from 3 doubles
point(double _x = 0, double _y = 0, double _z = 1) : x(_x), y(_y), z(_z) // point::point
{
  /* nop */

} // point::point

#if 0
double dist2D(const point &pt) const // point::dist2D
{
  double result = -3.402823466e+38;

  if(isProjectable() && pt.isProjectable() )
  {
    double _x = x / z - pt.x / pt.z;
    double _y = y / z - pt.y / pt.z;

    result = sqrt(_x * _x + _y * _y);
  }

  return result;

} // point::dist2D
#endif

// Easy way to calculate the Euclidean distance between two points.
double dist(const point &pt) const // point::dist
{
  return sqrt( (x - pt.x) * (x - pt.x) + (y - pt.y) * (y - pt.y) + (z - pt.z) * (z - pt.z) );

} // point::dist

bool isProjectable() const // point::isProjectable
{
  bool result = false;

  if(z > 1 || eq(z, 1) )
    result = true;

  return result;

} // point::isProjectable

point projectTo2D() const // point::projectTo2D
{
  point result = {0};

  if(eq(z, 0) )
  {
    result = point( -1, -1, -1);
  }
  else
  {
    result = point(x / z, y / z, 1);
  }

  return result;

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

#if 0
point operator*(const point& rhs) const // point::operator*(point, point)
{
  return point(x * rhs.x, y * rhs.y, z * rhs.z);

} // point::operator*(point, point)
#endif

point operator*(const double rhs) const // point::operator*(point, double)
{
  return point(x * rhs, y * rhs, z * rhs);

} // point::operator*(point, double)

friend point operator*(const double lhs, const point& rhs) // point::operator*(double, point)
{
  return point(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);

} // point::operator*(double, point)

}; // point

friend point;

struct pairQS
{
  point first;
  point second;
};

//typedef pair<point, point> pairQS;
//typedef queue<pairQS> queueS;

//typedef deque<point> dequeP;
//typedef dequeP::iterator iteratorDP;

//typedef vector<point> vectorP;
//typedef vectorP::iterator iteratorVP;

//typedef vector<double> vectorK;
//typedef vectorK::iterator iteratorVK;

// This variable t is used to describe F(t), which is
// the point on the curve that shells are shown for,
// the very same point that the program user can choose.
//
// This default value 0.5 is halfway through the curve.
double t;

// r and s define the affine frame (r, s).
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

// The maximum degree of each piece-wise polynomial curve.
int blahDegree;

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

uint8_t padding[5];

// A marker, used to tell the subdivision algorithm which part of
// the curve to render next.  Most importantly, this variable is
// used to iteratively render curve segments less than r and
// greater that s.
double minMaxT;

// This is temp memory used for iterative shell computations for t of f(t).
//dequeP shelPt;

// The transformed control points are stored in this list.
//dequeP tranPt;
//vectorP tranPt;
ssArray* tranPt;

// This is temp memory used for computing intermediate de Boor stage points.
//dequeP tempPt;
//vectorP tempPt;
ssArray* tempPt;

// This is the knot list associated with the de Boor control points.
//vectorK knots;
ssStack* knots;

// Iterative subdivision queue.
//queueS subdWt;
ssQueue* subdWt;

// The current input position.  Used when calculating the drag distance
// when manipulating control points.  The contents of this variable are
// not always updated/valid, unless needed by the algorithm.
point inputCur;
point inputPrv;

// The minimum and maximum values for t of F(t), used to normalize input for t
// from [minPt, maxPt] to [0, 1], when the user wants to see shells
// for a certain point.  Values are not always current/valid.
//
// Currently only the x coordinate of the points { inputPT, minPt, maxPt } are
// used to determine the actual value of t of F(t).
point minPt;
point maxPt;

// The different colors used for each shell and control point (in RGB).
int colors0[100];
int colors1[100];

double halfWidth;
double halfHeight;

// The function pointer for capture functions, used when the user is
// manipulating the curve.
//
// Currently valid/used when manipulating either the control points or the t value for F(t).
void(deBoor::*captureAction)();

GraphicsClient* graphics;

FontClient* font;

public:

// Initialize the de Boor algorithm when the user inputs the
// first control point.
deBoor(int _degree = 3, int _iterateConstant = 16) : t(0.5), frameR(0), frameS(1), capturedControlPt(0), numControlPts(0), iterateConstant(_iterateConstant), blahDegree(_degree), dimension(3), shellT(0), shellBl(true), ctrlBl(true), dispK(true), padding{0}, minMaxT(0), /*shelPt(), */tranPt(0), tempPt(0), knots(0), subdWt(0), inputCur(0, 0), inputPrv(0, 0), minPt(0, 0), maxPt(0, 0), halfWidth(0.5), halfHeight(0.5), captureAction(0), graphics(0), font(0) // deBoor::deBoor
{
  int degree = blahDegree;

  if(degree <= 0)
    degree = 1;

  BlahLog2("deBoor %i\n", (int)sizeof(deBoor) );

  tempPt = SsArrayConstruct(sizeof(point), 10, 4000000000, 10000);

  // temp m + 1 container
  for(int loop = 0; loop <= degree; loop++)
  {
    point blahPoint = {0};
    SsArrayPush(tempPt, &blahPoint);
  }

  if(iterateConstant < 1)
    iterateConstant = 1;

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

  tranPt = SsArrayConstruct(sizeof(point), 10, 4000000000, 10000);

  knots = SsStackConstruct(sizeof(double), 10, 4000000000, 10000);

  subdWt = SsQueueConstruct(sizeof(pairQS), 20 * (uint32_t)_iterateConstant, 4000000000, 10000);

} // deBoor::deBoor

// Free dynamic memory allocations when destroying the algorithm instance.
~deBoor() // deBoor::~deBoor
{
  //if( !shelPt.empty() )
  //  shelPt.clear();

  //if(SsArrayNum(tranPt) > 0)
  //  SsArrayReset(tranPt);

  if(tranPt)
    SsArrayDestruct( &tranPt);

  //if(SsArrayNum(tempPt) > 0)
  //  SsArrayReset(tempPt);

  if(tempPt)
    SsArrayDestruct( &tempPt);

  //if(SsStackNum(knots) > 0)
  //  SsStackReset(knots);

  if(knots)
    SsStackDestruct( &knots);

  //if(SsQueueNum(subdWt) > 0)
  //  SsQueueReset(subdWt);

  if(subdWt)
    SsQueueDestruct( &subdWt);

//memset(this, 0, sizeof(deBoor) );

} // deBoor::~deBoor

// This function must be called by the client in order for the algorithm to
// visually output the curve F(x), the control points, and the shells for F(t).
void setPrimitiveDrawingFunctions(double _halfWidth, double _halfHeight, GraphicsClient* _graphics, FontClient* _font) // deBoor::setPrimitiveDrawingFunctions(double, double, void(*)(int, int, int, int, int), void(*)(int, int, int, int, int, int), void(*)(int, int, int), FontClient*)
{
  halfWidth = _halfWidth;
  halfHeight = _halfHeight;

  //if(_graphics)
    graphics = _graphics;

  //if(_font)
    font = _font;

} // // deBoor::setPrimitiveDrawingFunctions(double, double, void(*)(int, int, int, int, int), void(*)(int, int, int, int, int, int), void(*)(int, int, int), FontClient*)

void setPrimitiveDrawingFunctions(deBoor& rhs, GraphicsClient* _graphics, FontClient* _font) // deBoor::setPrimitiveDrawingFunctions(deBoor)
{
  halfWidth = rhs.halfWidth;
  halfHeight = rhs.halfHeight;

  //if(_graphics)
    graphics = _graphics;

  //if(_font)
    font = _font;

} // deBoor::setPrimitiveDrawingFunctions(deBoor)

enum INPUT_EVENT // deBoor::INPUT_EVENT
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
  // are sent to the deBoor::updateInput() function.

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
  ADD_deBoor_CURVE = 2048,

  // The #5 undocumented numpad 3 command
  REMOVE_deBoor_CURVE = 4096,

  // The #6 undocumented numpad 4 command
  TRAVERSE_deBoor_CURVE_LIST = 8192,

  // The #7 undocumented numpad 5 command
  TOGGLE_CONTROL_POINT_TEXT = 16384

}; // deBoor::INPUT_EVENT

// Call this function whenever there is input,
// to update the de Boor algorithm.
int updateInput(int inputEvent, double xB, double yB, double B) // deBoor::updateInput
{
  int result = 0;

  if(numControlPts == 0 && inputEvent != ADD_CONTROL_POINT && inputEvent != MENU_INPUT)
    goto label_return;

  if(inputEvent != MENU_INPUT)
  {
    inputPrv = inputCur;

    inputCur = point(xB, yB, B);
  }

  // Check the input event ; perform input actions
  switch(inputEvent) // switch(inputEvent)
  {

  case UPDATE_INPUT: // switch(inputEvent) - UPDATE_INPUT
  {
    /* nop */
  }
  break; // switch(inputEvent) - UPDATE_INPUT

  case CAPTURE_CONTROL_POINT: // switch(inputEvent) - CAPTURE_CONTROL_POINT
  {
    result = 1;
    dumpAllCaptures();
    captureControlPoint();
  }
  break; // switch(inputEvent) - CAPTURE_CONTROL_POINT

  case ADD_CONTROL_POINT: // switch(inputEvent) - ADD_CONTROL_POINT
  {
    result = 1;
    dumpAllCaptures();
    addControlPoint();
  }
  break; // switch(inputEvent) - ADD_CONTROL_POINT

  case CAPTURE_T_OF_F_OF_T: // switch(inputEvent) - CAPTURE_T_OF_F_OF_T
  {
    result = 1;
    dumpAllCaptures();
    capture_t_of_F_of_t();
  }
  break; // switch(inputEvent) - CAPTURE_T_OF_F_OF_T

  case DUMP_ALL_CONTROL_POINTS: // switch(inputEvent) - DUMP_ALL_CONTROL_POINTS
  {
    result = 1;
    dumpAllCaptures();
    clearAllControlPoint();
  }
  break; // switch(inputEvent) - DUMP_ALL_CONTROL_POINTS

  case CAPTURE_TRANSLATE: // switch(inputEvent) - CAPTURE_TRANSLATE
  {
    result = 1;
    dumpAllCaptures();
    captureAction = &deBoor::dragTranslate;
  }
  break; // switch(inputEvent) - CAPTURE_TRANSLATE

  case CAPTURE_SCALE: // switch(inputEvent) - CAPTURE_SCALE
  {
    result = 1;
    dumpAllCaptures();
    captureAction = &deBoor::dragScale;
  }
  break; // switch(inputEvent) - CAPTURE_SCALE

  case CAPTURE_ROTATE: // switch(inputEvent) - CAPTURE_ROTATE
  {
    result = 1;
    dumpAllCaptures();
    captureAction = &deBoor::dragRotate;
  }
  break; // switch(inputEvent) - CAPTURE_ROTATE

  case REMOVE_CONTROL_POINT: // switch(inputEvent) - REMOVE_CONTROL_POINT
  {
    result = 1;
    dumpAllCaptures();
    removeControlPoint();
  }
  break; // switch(inputEvent) - REMOVE_CONTROL_POINT

  case TOGGLE_SHELLS: // switch(inputEvent) - TOGGLE_SHELLS
  {
    result = 1;
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
  break; // switch(inputEvent) - TOGGLE_SHELLS

  case MENU_INPUT: // switch(inputEvent) - MENU_INPUT
  {
    result = 1;
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
    // p[9] == h
    // p[10] == g
    // p[11] == f
    // p[12] == e
    //
    // p[13] == pointer to unordered array of doubles (the knot list)
    // p[14] == the number of knots
    //
    // affine frame (r, s)
    // p[15] == r
    // p[16] == s

    // input point (x * B, y * B, B)
    // p[17] == x
    // p[18] == y
    // p[19] == B

    int degree = fti(p[0] );

    if(degree < 0 || degree > 3)
    {
      break;
    }

    frameR = p[15];
    frameS = p[16];

    double* _knotList = *(double**) &p[13];

    int _numKnots = (int)(p[14] + 0.5); // cast todo

    if(_knotList && _numKnots > 0)
    {
      // Put the knots in ascending order, and make sure that there
      // are no knots with multiplicity greater that degree + 1.

      ssSet* sort = SsSetConstruct(sizeof(double), (uint32_t)_numKnots, 4000000000, 10000, doubleSsSetCompare);

      double knotValue = 0;

      int knotMultiplicity = 0;

      // Put the knots in ascending order.
      for(int loop = 0; loop < _numKnots; loop++)
        SsSetInsert(sort, &_knotList[loop], 0, 0);

      BlahLog2("MENU_INPUT\n");

      // Check for multiplicity greater than degree + 1 as the knots
      // are inserted into the active knot list.
      for(int loop = 0; loop < _numKnots; loop++)
      {
        double sort_front = 0;

        if( !loop)
        {
          SsSetGetNext(sort, true, &sort_front);

          knotValue = sort_front;
        }
        else
        {
          SsSetGetNext(sort, false, &sort_front);
        }

        if(eq(sort_front, knotValue) )
        {
          knotMultiplicity++;
        }
        else
        {
          knotValue = sort_front;

          knotMultiplicity = 1;
        }

        if(knotMultiplicity <= degree + 1)
          SsStackPush(knots, &sort_front);
      }

      SsSetDestruct( &sort);
    }

    while(SsStackNum(knots) < 5)
    {
      double knots_back_p1 = 0;
      SsStackGet(knots, &knots_back_p1);
      knots_back_p1 += 1;

      SsStackPush(knots, &knots_back_p1);
    }

    {
      double knots_degree = 0;
      SsStackGetAt(knots, (uint32_t)degree, &knots_degree);

      double knots_back = 0;
      SsStackGet(knots, &knots_back);

      t = knots_degree + (knots_back - knots_degree) * 0.5;
    }

    inputPrv = inputCur;

    point inputTemp = point(p[17] * p[19], p[18] * p[19], p[19] );

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

      inputCur = point(blossom(0, p[1] ), -blossom(0, p[5] ), blossom(0, p[9] ) );

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

      inputCur = point(blossom(1, p[2], p[1], frameR), -blossom(1, p[6], p[5], frameR), blossom(1, p[10], p[9], frameR) );

      addControlPoint();

      inputCur = point(blossom(1, p[2],  p[1], frameS), -blossom(1, p[6],  p[5], frameS), blossom(1, p[10], p[9], frameS) );

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

      inputCur = point(blossom(2, p[3], p[2], p[1], frameR, frameR), -blossom(2, p[7], p[6], p[5], frameR, frameR), blossom(2, p[11], p[10], p[9], frameR, frameR) );

      addControlPoint();

      inputCur = point(blossom(2, p[3], p[2], p[1], frameR, frameS), -blossom(2, p[7], p[6], p[5], frameR, frameS), blossom(2, p[11], p[10], p[9], frameR, frameS) );

      addControlPoint();

      inputCur = point(blossom(2, p[3], p[2], p[1], frameS, frameS), -blossom(2, p[7], p[6], p[5], frameS, frameS), blossom(2, p[11], p[10], p[9], frameS, frameS)
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

      inputCur = point(blossom(3, p[4], p[3], p[2], p[1], frameR, frameR, frameR), -blossom(3, p[8], p[7], p[6], p[5], frameR, frameR, frameR), blossom(3, p[8], p[7], p[6], p[5], frameR, frameR, frameR) );

      addControlPoint();

      inputCur = point(blossom(3, p[4], p[3], p[2], p[1], frameR, frameR, frameS), -blossom(3, p[8], p[7], p[6], p[5], frameR, frameR, frameS), blossom(3, p[12], p[11], p[10], p[9], frameR, frameR, frameS) );

      addControlPoint();

      inputCur = point(blossom(3, p[4], p[3], p[2], p[1], frameR, frameS, frameS), -blossom(3, p[8], p[7], p[6], p[5], frameR, frameS, frameS), blossom(3, p[12], p[11], p[10], p[9], frameR, frameS, frameS) );

      addControlPoint();

      inputCur = point(blossom(3, p[4], p[3], p[2], p[1], frameS, frameS, frameS), -blossom(3, p[8], p[7], p[6], p[5], frameS, frameS, frameS), blossom(3, p[12], p[11], p[10], p[9], frameS, frameS, frameS) );

      addControlPoint();

      inputCur = inputTemp;
    }
    break; // switch(inputEvent) - MENU_INPUT; switch(degree) - 3

    } // switch(inputEvent) - MENU_INPUT; switch(degree)
#undef p
#undef f
  }
  break; // switch(inputEvent) - MENU_INPUT

  case DUMP_ALL_CAPTURES: // switch(inputEvent) - DUMP_ALL_CAPTURES
  {
    result = 1;
    dumpAllCaptures();
  }
  break; // switch(inputEvent) - DUMP_ALL_CAPTURES

  case TOGGLE_CONTROL_POINTS: // switch(inputEvent) - TOGGLE_CONTROL_POINTS
  {
    result = 1;
    dumpAllCaptures();

    if(ctrlBl)
      ctrlBl = false;
    else
      ctrlBl = true;
  }
  break; // switch(inputEvent) - TOGGLE_CONTROL_POINTS

  case INCREASE_ITERATION_CONSTANT: // switch(inputEvent) - INCREASE_ITERATION_CONSTANT
  {
    ++iterateConstant;
  }
  break; // switch(inputEvent) - INCREASE_ITERATION_CONSTANT

  case DECREASE_ITERATION_CONSTANT: // switch(inputEvent) - DECREASE_ITERATION_CONSTANT
  {
    if(iterateConstant > 1)
      --iterateConstant;
  }
  break; // switch(inputEvent) - DECREASE_ITERATION_CONSTANT

  case TOGGLE_CONTROL_POINT_TEXT: // switch(inputEvent) - TOGGLE_CONTROL_POINT_TEXT
  {
    result = 1;
    dumpAllCaptures();

    if(dispK)
      dispK = false;
    else
      dispK = true;
  }
  break; // switch(inputEvent) - TOGGLE_CONTROL_POINT_TEXT

  default: // switch(inputEvent) - default
  {
    /* nop */
  }
  goto label_return; // switch(inputEvent) - default

  } // switch(inputEvent)

  if( !numControlPts)
    goto label_return;

  // Call capture action function pointer.
  if(captureAction && inputPrv != inputCur)
  {
    minMaxT = 0;
    shellT = 0;

    result = 1;

    (this->*captureAction)();
  }

label_return:
  return result;

} // deBoor::updateInput

// Call every program loop to draw F(x), the control points,
// F(t), and the shells for F(t).
void updateDraw() // deBoor::updateDraw
{
  int degree = 0;

  int loop = 0;

  if( !numControlPts)
    goto label_return;

  degree = blahDegree;

  if(numControlPts < 2 * degree + 1)
  {
    if(ctrlBl && fti(minMaxT) == 0)
    {
      point _temp;

      for(loop = 0; loop < numControlPts; loop++)
      {
        memset( &_temp, 0, sizeof(point) );
        SsArrayGetAt(tranPt, (uint32_t)loop, &_temp);

        drawCircle(_temp, (loop == (capturedControlPt - 1) ) ? 15: 10, loop + 1);

        if(dispK && _temp.isProjectable() )
        {
          _temp = _temp.projectTo2D();

          font->T1xtOut(font, (int)(_temp.x + 0.5) /*cast todo*/, (int)(_temp.y + 0.5) /*cast todo*/, "d0,%i", (int)loop);

          _temp.y += 14.0;

          {
            double knots_loop_p1 = 0;
            SsStackGetAt(knots, (uint32_t)loop + 1, &knots_loop_p1);

            font->T1xtOut(font, (int)(_temp.x + 0.5) /*cast todo*/, (int)(_temp.y + 0.5) /*cast todo*/, "%i", (int)knots_loop_p1);
          }

          int loopDegree = 0;

          while(++loopDegree != degree)
          {
            _temp.y += 14.0;

            double knots_loop_degree_p1 = 0;
            SsStackGetAt(knots, ( (uint32_t)loop + loopDegree) + 1, &knots_loop_degree_p1);

            font->T1xtOut(font, (int)(_temp.x + 0.5) /*cast todo*/, (int)(_temp.y + 0.5) /*cast todo*/, "%i", (int)knots_loop_degree_p1);
          }
        }
      }
    }

    minMaxT = 1;

    goto label_return;
  }

  if(fti(minMaxT) == 0)
  {
    if(SsQueueNum(subdWt) > 0)
      SsQueueReset(subdWt);

    double knots_degree = 0;
    SsStackGetAt(knots, (uint32_t)degree, &knots_degree);

    double knots_back = 0;
    SsStackGet(knots, &knots_back);

    double _double_Weight = (knots_back - knots_degree) * 0.5;

    point p1 = do_deBoor(knots_degree + _double_Weight);

    knots_degree = 0;
    SsStackGetAt(knots, (uint32_t)degree, &knots_degree);

    pairQS client = {p1, point(knots_degree + _double_Weight, _double_Weight) };
    SsQueuePushBack(subdWt, &client);

    minMaxT = 1;
  }

  loop = -1;

  while(SsQueueNum(subdWt) > 0 && ++loop < 20 * (1 + iterateConstant) )
  {
    pairQS client = { {0}, {0} };
    SsQueuePopFront(subdWt, &client);

    // get parent point
    point p0 = client.first;

    // get parent point's weight
    point _point_weight = client.second;

    // Remove the parent point from the subdivision tree (done above)

    // See if the left/right child point is the same as the parent point,
    // if it is then stop subdivision for that branch of the curve tree.
    //
    // Otherwise continue subdivision, inputting the child point into the
    // tree for further branching.

    // Left Child's weight == weight.x - weight.y * 0.5.
    point p1 = do_deBoor(_point_weight.x - _point_weight.y * 0.5);

    // Check if the left child is the same point as the parent
    if(p0 == p1)
    {
      // Do not do anything if they are the same point.
    }
    else
    {
      client.first = p1;
      client.second = point(_point_weight.x - _point_weight.y * 0.5, _point_weight.y * 0.5);

      // Draw and branch out the left child if the points are different.
      SsQueuePushBack(subdWt, &client);
    }

    // Right Child's weight == weight.x + weight.y * 0.5.
    p1 = do_deBoor(_point_weight.x + _point_weight.y * 0.5);

    // Check if the right child is the same point as the parent
    if(p0 == p1)
    {
      // Do not do anything if they are the same point.
    }
    else
    {
      client.first = p1;
      client.second = point(_point_weight.x + _point_weight.y * 0.5, _point_weight.y * 0.5);

      // Draw and branch out the right child if the points are different.
      SsQueuePushBack(subdWt, &client);
    }
  }

  loop = -1;

  if(shellT == 0)
  {
    ++loop;

    shellT = 2;

    if(shellBl)
    {
      int u1 = 0;

      point d0; // init todo
      point d1; // init todo

      for(int d = 0; d < numControlPts - 1; d++)
      {
        //d0 = tranPt[ (uint32_t)d];
        memset( &d0, 0, sizeof(point) );
        SsArrayGetAt(tranPt, (uint32_t)d, &d0);

        //d1 = tranPt[ (uint32_t)d + 1];
        memset( &d1, 0, sizeof(point) );
        SsArrayGetAt(tranPt, (uint32_t)d + 1, &d1);

        u1 = d + degree + 1;

        if(u1 >= (int)SsStackNum(knots) )
        {
          u1 = (int)SsStackNum(knots) - 1;
        }

        for(int u = d + 1; u < u1; u++)
        {
          double knots_u = 0;
          SsStackGetAt(knots, (uint32_t)u, &knots_u);

          double knots_u_p1 = 0;
          SsStackGetAt(knots, (uint32_t)u + 1, &knots_u_p1);

          if(u + 1 < (int)SsStackNum(knots) && !eq(knots_u, knots_u_p1) )
          {
            double knots_d_p1 = 0;
            SsStackGetAt(knots, (uint32_t)d + 1, &knots_d_p1);

            double knots_u1 = 0;
            SsStackGetAt(knots, (uint32_t)u1, &knots_u1);

            drawLine(d0 + (d1 - d0) * ( (knots_u - knots_d_p1) / (knots_u1 - knots_d_p1) ), d0 + (d1 - d0) * ( (knots_u_p1 - knots_d_p1) / (knots_u1 - knots_d_p1) ), u);
          }
        }
      }
    }

    if(ctrlBl)
    {
      point _temp; // init todo

      for(int currentIndex = 0; currentIndex < numControlPts; currentIndex++)
      {
        //_temp = tranPt[ (uint32_t)currentIndex];
        memset( &_temp, 0, sizeof(point) );
        SsArrayGetAt(tranPt, (uint32_t)currentIndex, &_temp);

        drawCircle(_temp, (currentIndex == (capturedControlPt - 1) ) ? 15 : 10, currentIndex + 1);

        if(dispK && _temp.isProjectable() )
        {
          _temp = _temp.projectTo2D();

          font->T1xtOut(font, (int)(_temp.x + 0.5) /*cast todo*/, (int)(_temp.y + 0.5) /*cast todo*/, "d0,%i", (int)currentIndex);

          _temp.y += 14.0;

          double knots_ci_p1 = 0;
          SsStackGetAt(knots, (uint32_t)currentIndex + 1, &knots_ci_p1);

          font->T1xtOut(font, (int)(_temp.x + 0.5) /*cast todo*/, (int)(_temp.y + 0.5) /*cast todo*/, "%i", (int)knots_ci_p1);

          int loopDegree = 0;

          while(++loopDegree != degree)
          {
            _temp.y += 14.0;

            double knots_ci_ld_p1 = 0;
            SsStackGetAt(knots, ( (uint32_t)currentIndex + loopDegree) + 1, &knots_ci_ld_p1);

            font->T1xtOut(font, (int)(_temp.x + 0.5) /*cast todo*/, (int)(_temp.y + 0.5) /*cast todo*/, "%i", (int)knots_ci_ld_p1);
          }
        }
      }
    }

    // Calculate/draw shells and F(t) (for F(t) from the user-inputted t).
    do_deBoor(t, true);
  }

label_return:
  return;

} // deBoor::updateDraw

private:

// The blossom is used to compute the control points when receiving menu input.
//
// Possible inputs:
// blossom(0, d);
// blossom(1, c, d, t1);
// blossom(2, b, c, d, t1, t2);
// blossom(3, a, b, c, d, t1, t2, t3);
double blossom(int degree, ...) // deBoor::blossom
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

  case 0: // switch(degree) - 0
  {
    d = va_arg(argptr, double);

    va_end(argptr);

    result = d;
  }
  break; // switch(degree) - 0

  case 1: // switch(degree) - 1
  {
    c = va_arg(argptr, double);
    d = va_arg(argptr, double);

    t1 = va_arg(argptr, double);

    va_end(argptr);

    result = c * t1 + d;
  }
  break; // switch(degree) - 1

  case 2: // switch(degree) - 2
  {
    b = va_arg(argptr, double);
    c = va_arg(argptr, double);
    d = va_arg(argptr, double);

    t1 = va_arg(argptr, double);
    t2 = va_arg(argptr, double);

    va_end(argptr);

    result = b * t1 * t2 + c * (t1 + t2) / 2.0 + d;
  }
  break; // switch(degree) - 2

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

    result = a * t1 * t2 * t3 + b * (t1 * t2 + t1 * t3 + t2 * t3) / 3.0 + c * (t1 + t2 + t3) / 3.0 + d;
  }
  break; // switch(degree) - 3

  default:
  {
    assert(0 && "bad blossom degree");
  }
  break;

  } // switch(degree)

  return result;

} // deBoor::blossom

point do_deBoor(double dt, bool draw = false) // deBoor::do_deBoor
{
  int degree = blahDegree;

  point temporary( -1, -1);

  double knots_front = 0;
  SsStackGetAt(knots, 0, &knots_front);

  double knots_back = 0;
  SsStackGet(knots, &knots_back);

  int I = -1;

  int i = 0;
  int j = 0;
  int k = 0;

  int r = 0;

  double knots_I = 0;

  if(dt < knots_front || dt > knots_back || eq(dt, knots_back) )
    goto label_return;

  if( (int)SsStackNum(knots) < degree + 1 || (int)SsArrayNum(tranPt) < degree + 1)
    goto label_return;

  // get the middle interval of the knots
  // get k of [u(k), u(k+1) )
  I = -1;

  // binary search, i is left, j is right, k is middle
  i = 0;
  j = (int)SsStackNum(knots) - 1;
  k = 0;

  while(j >= i)
  {
    k = (i + j) / 2;

    double knots_k = 0;
    SsStackGetAt(knots, (uint32_t)k, &knots_k);

    double knots_k_p1 = 0;
    SsStackGetAt(knots, (uint32_t)k + 1, &knots_k_p1);

    if( (knots_k < dt || eq(knots_k, dt) ) && dt < knots_k_p1)
    {
      I = k;

      break;
    }

    if(dt < knots_k)
    {
      j = k - 1;
    }
    else
    {
      i = k + 1;
    }
  }

  if(I - degree < 0)
    goto label_return;

  r = 0;

  knots_I = 0;
  SsStackGetAt(knots, (uint32_t)I, &knots_I);

  if(eq(dt, knots_I) )
  {
    // get the multiplicity of the knot
    r = 1;

    if(I > 0)
    {
      i = I - 1;

      while(i >= 0)
      {
        double knots_i = 0;
        SsStackGetAt(knots, (uint32_t)i, &knots_i);

        if(eq(dt, knots_i) )
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

    if( (int)SsStackNum(knots) > I + 1)
    {
      j = I + 1;

      while( (int)SsStackNum(knots) > j)
      {
        double knots_j = 0;
        SsStackGetAt(knots, (uint32_t)j, &knots_j);

        if(eq(dt, knots_j) )
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
      goto label_return;
  }

  for(i = I - degree, j = 0; i <= I - r; i++, j++)
  {
    point blahPoint = {0};
    SsArrayGetAt(tranPt, (uint32_t)i, &blahPoint);

    SsArraySetAt(tempPt, (uint32_t)j, &blahPoint);
  }

  for(j = 1; j <= degree - r; j++)
  {
    for(i = I - degree + j, k = 0; i <= I - r; i++, k++)
    {
      point tempPt_k = {0};
      SsArrayGetAt(tempPt, (uint32_t)k, &tempPt_k);

      point tempPt_k_p1 = {0};
      SsArrayGetAt(tempPt, (uint32_t)k + 1, &tempPt_k_p1);

      double knots_dij1 = 0;
      SsStackGetAt(knots, ( ( (uint32_t)degree + i) - j) + 1, &knots_dij1);

      double knots_i = 0;
      SsStackGetAt(knots, (uint32_t)i, &knots_i);

      point tempPt_k_prime = ( (knots_dij1 - dt) / (knots_dij1 - knots_i) ) * tempPt_k + ( (dt - knots_i) / (knots_dij1 - knots_i) ) * tempPt_k_p1;

      SsArraySetAt(tempPt, (uint32_t)k, &tempPt_k_prime);
    }

    if(draw)
    {
      for(i = I - degree + j, k = 0; i <= I - r - 1; i++, k++)
      {
        point tempPt_k = {0};
        SsArrayGetAt(tempPt, (uint32_t)k, &tempPt_k);

        point tempPt_k_p1 = {0};
        SsArrayGetAt(tempPt, (uint32_t)k + 1, &tempPt_k_p1);

        drawLine(tempPt_k, tempPt_k_p1, I);
      }
    }
  }

  memset( &temporary, 0, sizeof(point) );
  SsArrayGetAt(tempPt, 0, &temporary);

  if(draw)
  {
    drawCircle(temporary, 5, I);
  }
  else
  {
    drawPoint(temporary, I);
  }

label_return:
  return temporary;

} // deBoor::do_deBoor

// Wrapper for easily calling circleDrawingPrimitive().
void drawCircle(point center, int radius, int knotIndex) // deBoor::drawCircle
{
  if(graphics)
  {
    if(center.x < -2000000000 || center.x > 2000000000 || center.y < -2000000000 || center.y > 2000000000)
      goto label_return;

    if(center.isProjectable() )
    {
      center = center.projectTo2D();

      double knots_ki = 0;
      SsStackGetAt(knots, (uint32_t)(knotIndex % 100), &knots_ki);

      graphics->GraphicsRenderCircle32(graphics, fti(center.x), fti(center.y), radius, colors0[ (int)knots_ki % 100], colors1[ (int)knots_ki % 100] );
    }
  }

label_return:
  return;

} // deBoor::drawCircle

// Wrapper for easily calling lineDrawingPrimitive().
void drawLine(point start, point end, int knotIndex) // deBoor::drawLine
{
  if(graphics)
  {
    if(start.x < -2000000000 || start.x > 2000000000 || start.y < -2000000000 || start.y > 2000000000 || end.x < -2000000000 || end.x > 2000000000 || end.y < -2000000000 || end.y > 2000000000)
      goto label_return;

    if(start.isProjectable() && end.isProjectable() )
    {
      start = start.projectTo2D();

      end = end.projectTo2D();

      double knots_ki = 0;
      SsStackGetAt(knots, (uint32_t)(knotIndex % 100), &knots_ki);

      graphics->GraphicsRenderLine32(graphics, fti(start.x), fti(start.y), fti(end.x), fti(end.y), colors0[ (int)knots_ki % 100], colors1[ (int)knots_ki % 100] );
    }
  }

label_return:
  return;

} // deBoor::drawLine

// Wrapper for easily calling pointDrawingPrimitive().
void drawPoint(point center, int knotIndex) // deBoor::drawPoint
{
  if(graphics)
  {
    if(center.x < -2000000000 || center.x > 2000000000 || center.y < -2000000000 || center.y > 2000000000)
      goto label_return;

    if(center.isProjectable() )
    {
      center = center.projectTo2D();

      double knots_ki = 0;
      SsStackGetAt(knots, (uint32_t)(knotIndex % 100), &knots_ki);

      graphics->GraphicsRenderPoint32(graphics, fti(center.x), fti(center.y), colors0[ (int)knots_ki % 100] );
    }
  }

label_return:
  return;

} // deBoor::drawPoint

// When the user adds another control point, add that control point in the
// list right after the previous control point.
//
// Also add an extra point to the end of the list, used as temporary storage
// while evaluating the de Boor algorithm.
void addControlPoint() // deBoor::addControlPoint
{
  int loop = 0;

  int degree = blahDegree;

  // Add the new control point to the list.
  numControlPts++;

  //shelPt.push_back(inputCur);
  //tranPt.push_back(inputCur);
  SsArrayPush(tranPt, &inputCur);

  if(numControlPts > degree + 1)
  {
    for(loop = 0; loop < degree; loop++)
    {
      double blahPop = 0;
      SsStackPop(knots, &blahPop);
    }

    double knots_back_p1 = 0;
    SsStackGet(knots, &knots_back_p1);
    knots_back_p1 += 1;

    SsStackPush(knots, &knots_back_p1);

    for(loop = 0; loop < degree; loop++)
    {
      double knots_back = 0;
      SsStackGet(knots, &knots_back);

      SsStackPush(knots, &knots_back);
    }
  }
  else if(numControlPts == 1)
  {
    for(loop = 0; loop < degree + 1; loop++)
    {
      double knots_push = 0;
      SsStackPush(knots, &knots_push);
    }

    for(loop = 0; loop < degree + 1; loop++)
    {
      double knots_push = 1;
      SsStackPush(knots, &knots_push);
    }
  }

} // deBoor::addControlPoint

// Captures the closest control point, for user manipulation.
void captureControlPoint() // deBoor::captureControlPoint
{
  double distMin = 0;

  // Starting with the first control point, and doing the same with all ctrl pts,
  // calculate the distance between the input pt and each ctrl pt.
  //
  // The ctrl pt that is closest to the input pt is the pt that is captured.
  // The index of the closest ctrl pt is stored in capturedControlPt,
  // and the captureAction() function is activated to point to the dragControlPoint()
  // function.
  capturedControlPt = 0;

  {
    point temporaryPoint = {0};
    SsArrayGetAt(tranPt, (uint32_t)capturedControlPt, &temporaryPoint);

    distMin = inputCur.dist(temporaryPoint);
  }

  for(int currentPtIndex = 1; currentPtIndex < numControlPts; currentPtIndex++)
  {
    point temporaryPoint = {0};
    SsArrayGetAt(tranPt, (uint32_t)currentPtIndex, &temporaryPoint);

    if(distMin > inputCur.dist(temporaryPoint) )
    {
      distMin = inputCur.dist(temporaryPoint);

      capturedControlPt = currentPtIndex;
    }
  }

  capturedControlPt++;

  captureAction = &deBoor::dragControlPoint;

} // deBoor::captureControlPoint

// Captures t of F(t)
void capture_t_of_F_of_t() // deBoor::capture_t_of_F_of_t
{
  {
    point temporaryPoint = {0};
    SsArrayGetAt(tranPt, 0, &temporaryPoint);

    // Find the minimum and maximum values of the coordinate pts,
    // which are needed to normalize input.
    minPt.x = maxPt.x = temporaryPoint.x;
    minPt.y = maxPt.y = 0;
  }

  for(int currentIndex = 1; currentIndex < numControlPts; currentIndex++)
  {
    point temporaryPoint = {0};
    SsArrayGetAt(tranPt, (uint32_t)currentIndex, &temporaryPoint);

    if(minPt.x > temporaryPoint.x)
    {
      minPt.x = temporaryPoint.x;
    }

    if(maxPt.x < temporaryPoint.x)
    {
      maxPt.x = temporaryPoint.x;
    }
  }

  // Once t can be normalized, activate the captureAction() function to
  // point to the drag_t_of_F_of_t() function.
  //
  // The new t will be calculated in the drag_t_of_F_of_t() function.
  captureAction = &deBoor::drag_t_of_F_of_t;

} // deBoor::capture_t_of_F_of_t

// When the user chooses to clear all ctrl pts, to start a new curve,
// erase all elements in the control point list.
void clearAllControlPoint() // deBoor::clearAllControlPoint
{
  int degree = blahDegree;

  //if( !shelPt.empty() )
  //  shelPt.clear();

  if(SsArrayNum(tranPt) > 0)
    SsArrayReset(tranPt);

  if(SsArrayNum(tempPt) > 0)
    SsArrayReset(tempPt);

  for(int loop = 0; loop <= degree; loop++)
  {
    point blahPoint = {0};
    SsArrayPush(tempPt, &blahPoint);
  }

  if(SsStackNum(knots) > 0)
    SsStackReset(knots);

  if(SsQueueNum(subdWt) > 0)
    SsQueueReset(subdWt);

  numControlPts = 0;

} // deBoor::clearAllControlPoint

// This function is called thru the captureAction() function, when the user wants
// to manipulate t of F(t).
void drag_t_of_F_of_t() // deBoor::drag_t_of_F_of_t
{
  int degree = blahDegree;

  if(inputCur.x <= minPt.x)
  {
    inputCur.x = minPt.x + 1;
  }

  if(inputCur.x >= maxPt.x)
  {
    inputCur.x = maxPt.x - 1;
  }

  t = (inputCur.x - minPt.x) / fabs(maxPt.x - minPt.x);

  double knots_degree = 0;
  SsStackGetAt(knots, (uint32_t)degree, &knots_degree);

  double knots_back = 0;
  SsStackGet(knots, &knots_back);

  // Scale the t value to the magnitude of the knot sequence values.
  t *= (knots_back - knots_degree);

  // Translate t to start at the smallest knot value.
  t += knots_degree;

} // deBoor::drag_t_of_F_of_t

// This function is called thru the captureAction() function, when the user wants
// to manipulate a control pt.
void dragControlPoint() // deBoor::dragControlPoint
{
  // Drag the captured ctrl pt relative to input movement between
  // the current input pt and the previous input pt.

  point temporaryPoint = {0};
  SsArrayGetAt(tranPt, (uint32_t)capturedControlPt - 1, &temporaryPoint);

  temporaryPoint += inputCur - inputPrv;
  SsArraySetAt(tranPt, (uint32_t)capturedControlPt - 1, &temporaryPoint);

} // deBoor::dragControlPoint

// When a new user request has occured, flush any older user requests
// currently being processed.
void dumpAllCaptures() // deBoor::dumpAllCaptures
{
  capturedControlPt = 0;
  captureAction = 0;

  minMaxT = 0;
  shellT = 0;

} // deBoor::dumpAllCaptures

void dragTranslate() // deBoor::dragTranslate
{
  point p = {0}; // init todo

  for(int index = 0; index < numControlPts; index++)
  {
    memset( &p, 0, sizeof(point) );
    SsArrayGetAt(tranPt, (uint32_t)index, &p);

    p.x += inputCur.x - inputPrv.x;
    p.y += inputCur.y - inputPrv.y;
    //p.z = p.z;

    SsArraySetAt(tranPt, (uint32_t)index, &p);
  }

} // deBoor::dragTranslate

void dragScale() // deBoor::dragScale
{
  double scale = 1.0 + (inputCur.y - inputPrv.y) / (halfWidth * 2);

  double tx = (1 - scale) * halfWidth;
  double ty = (1 - scale) * halfHeight;

  point p = {0}; // init todo

  for(int index = 0; index < numControlPts; index++)
  {
    memset( &p, 0, sizeof(point) );
    SsArrayGetAt(tranPt, (uint32_t)index, &p);

    p.x = p.x * scale + tx;
    p.y = p.y * scale + ty;
    //p.z = p.z;

    SsArraySetAt(tranPt, (uint32_t)index, &p);
  }

} // deBoor::dragScale

void dragRotate() // deBoor::dragRotate
{
  double angle = (inputCur.x - inputPrv.x) / 180.0;

  double cosine = cos(angle);
  double sine = sin(angle);

  double tx = halfWidth;
  double ty = halfHeight;

  point p; // init todo

  for(int index = 0; index < numControlPts; index++)
  {
    point a = {0};

    memset( &p, 0, sizeof(point) );
    SsArrayGetAt(tranPt, (uint32_t)index, &p);

    a.x = sine * ( -p.y + ty) + cosine * (p.x - tx) + tx;
    a.y = sine * (p.x - tx) + cosine * (p.y - ty) + ty;
    a.z = p.z;

    SsArraySetAt(tranPt, (uint32_t)index, &a);
  }

} // deBoor::dragRotate

void removeControlPoint() // deBoor::removeControlPoint
{
  int ctrlPt = 0;

  double distMin = 0;

  // Starting with the first control point, and doing the same with all ctrl pts,
  // calculate the distance between the input pt and each ctrl pt.
  //
  // The ctrl pt that is closest to the input pt is the pt that is deleted.
  ctrlPt = 0;

  {
    point temporaryPoint = {0};
    SsArrayGetAt(tranPt, (uint32_t)ctrlPt, &temporaryPoint);

    distMin = inputCur.dist(temporaryPoint);
    BlahLog2("distance1 %f\n", distMin);
  }

  BlahLog2("chosen index %i\n", ctrlPt);

  for(int currentIndex = 1; currentIndex < numControlPts; currentIndex++)
  {
    point temporaryPoint = {0};
    SsArrayGetAt(tranPt, (uint32_t)currentIndex, &temporaryPoint);

    double distanceTwo = inputCur.dist(temporaryPoint);
    BlahLog2("distance2 %f\n", distanceTwo);

    if(distanceTwo < distMin)
    {
      distMin = distanceTwo;

      ctrlPt = currentIndex;
      BlahLog2("chosen index %i\n", ctrlPt);
    }
  }

  //shelPt.erase(shelPt.begin() + ctrlPt);
  //tranPt.erase(tranPt.begin() + ctrlPt);

  {
    ssArray* temporaryArray = SsArrayConstruct(sizeof(point), 10, 4000000000, 10000);

    for(int currentIndex = 0; currentIndex < numControlPts; currentIndex++)
    {
      if(currentIndex != ctrlPt)
      {
        point temporaryPoint = {0};
        SsArrayGetAt(tranPt, (uint32_t)currentIndex, &temporaryPoint);

        SsArrayPush(temporaryArray, &temporaryPoint);
      }
    }

    clearAllControlPoint();

    for(int currentIndex = 0; currentIndex < (int)SsArrayNum(temporaryArray); currentIndex++)
    {
      //inputCur = temporaryArray[currentIndex];
      //memcpy( &inputCur, &temporaryArray[currentIndex], sizeof(point) );

      point temporaryPoint = {0};
      SsArrayGetAt(temporaryArray, (uint32_t)currentIndex, &inputCur);

      addControlPoint();
    }

    SsArrayDestruct( &temporaryArray);
  }

#if 0
  --numControlPts;

// todo found an edge case bug when deleting control points.  the source of the bug smells of knots.
// possibly in the remaining portion of this function

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

  double knots_ctrlpt_m1 = 0;
  SsStackGetAt(knots, (uint32_t)ctrlPt - 1, &knots_ctrlpt_m1);

  double knots_ctrlpt = 0;
  SsStackGetAt(knots, (uint32_t)ctrlPt, &knots_ctrlpt);

  double knots_ctrlpt_p1 = 0;
  SsStackGetAt(knots, (uint32_t)ctrlPt + 1, &knots_ctrlpt_p1);

  if(ctrlPt > 0 && (int)SsStackNum(knots) > ctrlPt && eq(knots_ctrlpt_m1, knots_ctrlpt) )
  {
    // Just remove the knot ui since the multiplicity is greater than one.
  }
  else if( (int)SsStackNum(knots) > ctrlPt + 1 && eq(knots_ctrlpt, knots_ctrlpt_p1) )
  {
    // Just remove the knot ui since the multiplicity is greater than one.
  }
  else if( (int)SsStackNum(knots) > ctrlPt + 1)
  {
    // The knot ui has multiplicity 1, so increment all knots with values
    // greater than ui by one (increment their values by one).
    for(iterVK knot = knots.begin() + ctrlPt + 1; knot != knots.end(); knot++)
    {
      *knot += 1;
    }

    // Then remove the knot ui.
  }

  //knots.erase(knots.begin() + ctrlPt);

  {
    ssArray* temporaryK = SsArrayConstruct(sizeof(double), 10, 4000000000, 10000);

    for(int currentIndex = 0; currentIndex < (int)SsStackNum(knots); currentIndex++)
    {
      if(currentIndex != ctrlPt)
      {
        double value = 0;
        SsStackGetAt(knots, currentIndex, &value);

        SsArrayPush(temporaryK, &value);
      }
    }

    if(SsStackNum(knots) > 0)
      SsStackReset(knots);

    for(int currentIndex = 0; currentIndex < (int)SsArrayNum(temporaryK); currentIndex++)
    {
      double value = 0;
      SsArrayGetAt(temporaryK, currentIndex, &value);

      SsStackPush(knots, &value);
    }

    SsArrayDestruct( &temporaryK);
  }
#endif

} // deBoor::removeControlPoint

}; // deBoor

const double deBoor::E = 0.000001;

struct pairDI
{
  deBoor* first;
  int64_t second;
};

uint32_t deBoorListSsSetCompare(void* lhsRef, void* rhsRef)
{
  bool result = false;

  pairDI* lhs = (pairDI*)lhsRef;
  pairDI* rhs = (pairDI*)rhsRef;

  if(lhs->second < rhs->second)
    result = true;

  return result;
}

uint32_t doubleSsSetCompare(void* lhsRef, void* rhsRef)
{
  bool result = false;

  double* lhs = (double*)lhsRef;
  double* rhs = (double*)rhsRef;

  if(*lhs < *rhs)
    result = true;

  return result;
}

//typedef deque<deBoor*> dequeB;
//typedef dequeB::iterator iteratorDB;

//static dequeB* deBoorList = 0;
static ssSet* deBoorList = 0;

//static iteratorDB deBoorIter;
pairDI deBoorIter = {0, 0};

enum
{
  ERROR = -1,
  OK = 0
};

int init(double _halfWidth, double _halfHeight, GraphicsClient* _graphics, FontClient* _font) // init
{
  int result = ERROR;

  // Initialize the random number generator.
  srand( (uint32_t)time(0) );

  if( !deBoorList)
  {
    if(_halfWidth <= 0 || _halfHeight <= 0 || !_graphics || !_font)
      goto label_return;

    BlahLog2("create root deBoorList before\n");

    //deBoorList = new dequeB;
    deBoorList = SsSetConstruct(sizeof(pairDI), 10, 4000000000, 10000, deBoorListSsSetCompare);

    BlahLog2("create root deBoorList after\n");

    if( !deBoorList)
      goto label_return;

    //deBoorList->push_back(new de_Boor);
    deBoorIter.first = new deBoor;
    deBoorIter.second = 0;
    SsSetInsert(deBoorList, &deBoorIter, 0, 0);

    //if( !(*deBoorList)[0] )
    if( !deBoorIter.first)
      goto label_return;

    //(*deBoorList)[0]->setPrimitiveDrawingFunctions
    deBoorIter.first->setPrimitiveDrawingFunctions(_halfWidth, _halfHeight, _graphics, _font);

    //deBoorIter = deBoorList->begin();
    deBoorIter.first = 0;
    deBoorIter.second = 0;
    SsSetGetNext(deBoorList, true, &deBoorIter);
  }

  //if( !(*deBoorList)[0] || deBoorIter != deBoorList->begin() )
  if( !deBoorIter.first || !SsSetIsBegin(deBoorList) )
    goto label_return;

  result = OK;

label_return:
  return result;

} // init

int main(int inputEvent, double x, double y, double B, double _halfWidth, double _halfHeight, GraphicsClient* _graphics, FontClient* _font) // main
{
  int result = OK;

  pairDI loop = {0, 0};

  // if( !deBoorList || deBoorList->size() == 0)
  if( !deBoorList || !SsSetNum(deBoorList) || !deBoorIter.first)
  {
    result = ERROR;
    goto label_return;
  }

#if 0
  //if(deBoorIter == deBoorList->end() || *deBoorIter == 0)
  if(SsSetIsEnd(deBoorList) == SsSetEnd || !deBoorIter.first)
  {
    //deBoorIter = deBoorList->begin();
    deBoorIter.first = 0;
    deBoorIter.second = 0;
    SsSetGetNext(deBoorList, true, &deBoorIter);
  }
#endif

  if(_halfWidth <= 0 || _halfHeight <= 0)
  {
    result = ERROR;
    goto label_return;
  }

  //deBoorIter.first->setPrimitiveDrawingFunctions(_halfWidth, _halfHeight, _graphics, _font);

  //iteratorDB temp; // init todo

  switch(inputEvent) // switch(inputEvent)
  {

  case deBoor::ADD_deBoor_CURVE: // switch(inputEvent) - deBoor::ADD_deBoor_CURVE
  {
    pairDI curve = {new deBoor, SsSetNum(deBoorList) };

    if( !curve.first)
    {
      result = ERROR;
      goto label_return;
    }

    //curve->setPrimitiveDrawingFunctions(**deBoorIter);
    curve.first->setPrimitiveDrawingFunctions(*deBoorIter.first, _graphics, _font);

    //deBoorList->push_back(curve);
    SsSetInsert(deBoorList, &curve, 0, 0);

    deBoorIter.first = 0;
    deBoorIter.second = 0;
    SsSetGetNext(deBoorList, true, &deBoorIter);

    while(deBoorIter.first != curve.first)
    {
      deBoorIter.first = 0;
      deBoorIter.second = 0;
      SsSetGetNext(deBoorList, false, &deBoorIter);
    }

    //deBoorIter = deBoorList->end() - 1;
  }
  break; // switch(inputEvent) - deBoor::ADD_deBoor_CURVE

  case deBoor::REMOVE_deBoor_CURVE: // switch(inputEvent) - deBoor::REMOVE_deBoor_CURVE
  {
    //if(deBoorList->size() == 1)
    if(SsSetNum(deBoorList) == 1)
    {
      inputEvent = deBoor::DUMP_ALL_CONTROL_POINTS;
    }
    else
    {
      int found = 0;

      pairDI current = {deBoorIter.first, deBoorIter.second};

      //deBoorIter = deBoorList->begin();
      deBoorIter.first = 0;
      deBoorIter.second = 0;
      SsSetGetNext(deBoorList, true, &deBoorIter);

      while(deBoorIter.first != current.first)
      {
        found++;

        deBoorIter.first = 0;
        deBoorIter.second = 0;
        SsSetGetNext(deBoorList, false, &deBoorIter);
      }

      //deBoorList->erase(deBoorIter);
      SsSetErase(deBoorList, &deBoorIter, 0, 0);

      delete deBoorIter.first;
      deBoorIter.first = 0;

      if(found == SsSetNum(deBoorList) )
        found = 0;

      int index = 0;

      deBoorIter.first = 0;
      deBoorIter.second = 0;
      SsSetGetNext(deBoorList, true, &deBoorIter);

      while(index != found)
      {
        index++;

        deBoorIter.first = 0;
        deBoorIter.second = 0;
        SsSetGetNext(deBoorList, false, &deBoorIter);
      }

      result |= 1;

      inputEvent = deBoor::DUMP_ALL_CAPTURES;
    }
  }
  break; // switch(inputEvent) - deBoor::REMOVE_deBoor_CURVE

  case deBoor::TRAVERSE_deBoor_CURVE_LIST: // switch(inputEvent) - deBoor::TRAVERSE_deBoor_CURVE_LIST
  {
    //++deBoorIter;
    deBoorIter.first = 0;
    deBoorIter.second = 0;
    SsSetGetNext(deBoorList, false, &deBoorIter);

    if(SsSetIsEnd(deBoorList) == SsSetEnd)
    {
      //deBoorIter = deBoorList->begin();
      deBoorIter.first = 0;
      deBoorIter.second = 0;
      SsSetGetNext(deBoorList, true, &deBoorIter);
    }
  }
  break; // switch(inputEvent) - deBoor::TRAVERSE_deBoor_CURVE_LIST

  } // switch(inputEvent)

  deBoorIter.first->setPrimitiveDrawingFunctions(_halfWidth, _halfHeight, _graphics, _font);

  deBoorIter.first->updateDraw();

  result |= deBoorIter.first->updateInput(inputEvent, x * B, y * B, B);

  //loop = deBoorList->begin()
  loop.first = 0;
  loop.second = 0;
  SsSetGetNext(deBoorList, true, &loop);

  //for(loop = deBoorList->begin(); loop != deBoorList->end(); loop++)
  while( !SsSetIsEnd(deBoorList) )
  {
    if(loop.first != deBoorIter.first)
    {
      loop.first->setPrimitiveDrawingFunctions(_halfWidth, _halfHeight, _graphics, _font);

      loop.first->updateDraw();
    }

    if( (result || inputEvent == deBoor::DUMP_ALL_CAPTURES) && loop.first != deBoorIter.first)
    {
      result |= loop.first->updateInput(deBoor::DUMP_ALL_CAPTURES, x * B, y * B, B);
    }

    loop.first = 0;
    loop.second = 0;
    SsSetGetNext(deBoorList, false, &loop);
  }

  loop.first = deBoorIter.first;
  loop.second = deBoorIter.second;
  SsSetGetNext(deBoorList, true, &loop);

  while(loop.first != deBoorIter.first)
  {
    loop.first = deBoorIter.first;
    loop.second = deBoorIter.second;
    SsSetGetNext(deBoorList, false, &loop);
  }

label_return:
  return result;

} // main

int term() // term
{
  int result = ERROR;

  //int count = 0;

  pairDI ksdhfkoslh = {0, 0};

  //iteratorDB loop;

  if( !deBoorList)
  {
    BlahLog2("error\n");
    goto label_return;
  }

  if(deBoorList)
  {
    pairDI loop = {0, 0};

    //deBoorIter = deBoorList->end();
    deBoorIter.first = 0;
    deBoorIter.second = 0;

    SsSetGetNext(deBoorList, true, &loop);

    //for(loop = deBoorList->begin(); loop != deBoorList->end(); loop++)
    for(int count = 1; count <= SsSetNum(deBoorList); count++)
    {
      if(loop.first)
      {
        delete loop.first;
        loop.first = 0;
      }

      loop.first = 0;
      loop.second = 0;
      SsSetGetNext(deBoorList, false, &loop);
    }

    //deBoorList->clear();

    //if(SsSetNum(deBoorList) > 0)
    //  SsSetReset(deBoorList);

    BlahLog2("destroy root deBoorList before\n");

    //delete deBoorList;
    //deBoorList = 0;
    SsSetDestruct( &deBoorList);

    BlahLog2("destroy root deBoorList after\n");
  }

  result = OK;

label_return:
  return result;

} // term
