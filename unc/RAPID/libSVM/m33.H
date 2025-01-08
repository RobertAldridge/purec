#ifndef M33_H
#define M33_H

#include <math.h>
#include <stdio.h>

#include "angle.H"
#include "v3.H"

class m33
{
public:


  double m[3][3];
  
  void
    fprintf(FILE *fp, const char *fmt);
  
  void
    print() { fprintf(stdout, "%lf "); } 
  
  m33(const m33 &m1);

  m33(double m00, double m10, double m20, 
      double m01, double m11, double m21, 
      double m02, double m12, double m22);
  
  m33();

  void make_identity();
  
  m33 T() const;
  m33 inverse() const;
  
  v3 col(int c) const;

  v3 row(int r) const;
};


m33
operator+(const m33 &m1, const m33 &m2);

m33
operator-(const m33 &m1, const m33 &m2);

m33
operator*(const m33 &m1, const m33 &m2);

m33 
operator*(const m33 &m1, const double &s);
m33 
operator*(const double &s, const m33 &m1);

m33
T(m33 M);

m33
Identity();

m33
Rx(radians t);

m33
Ry(radians t);

m33
Rz(radians t);

m33
R(double dx, double dy, double dz, radians t);


#endif
/* M33_H */






