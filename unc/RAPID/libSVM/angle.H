#ifndef ANGLE_H
#define ANGLE_H

#include <math.h>

class degrees;
class radians;

class radians
{
public:
  double r;

  radians() { r = 0; } 
  radians(double t) : r(t) {} 
  operator double() const { return r; } 
  operator degrees() const;
  
};


class degrees
{
public:
  double d;

  degrees() { d = 0; }
  degrees(double t) : d(t) {} 
  operator double() const { return d; } 
  operator radians() const;
};

double sin(radians t);
double cos(radians t);


#endif
/* ANGLE_H */

