#include <math.h>
#include "angle.H"

radians::operator degrees() const
{
  degrees d;
  
  d.d = (r / M_PI)*180.0;

  return d;
}

degrees::operator radians() const
{
  radians r;
  
  r.r = (d / 180.0)*M_PI;
  
  return r;
}

double sin(radians t)
{
  return sin(t.r);
}

double cos(radians t)
{
  return cos(t.r);
}
