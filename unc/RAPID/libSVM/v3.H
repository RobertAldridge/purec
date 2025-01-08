#ifndef V3_H
#define V3_H

#include <math.h>
#include <stdio.h>

class v3
{
public:
  
  double v[3];
  
  void fprintf(FILE *fp, const char *fmt);
  
  void print() { fprintf(stdout, "%lf "); } 
  
  v3(const v3 &va) { v[0]=va.v[0]; v[1]=va.v[1]; v[2]=va.v[2]; } 

  v3(const double d[3]) { v[0]=d[0]; v[1]=d[1]; v[2]=d[2]; }
  
  v3(double x, double y, double z) { v[0]=x; v[1]=y; v[2]=z; }
  
  v3() { v[0]=0.0; v[1]=0.0; v[2]=0.0; }

  void set(double x, double y, double z) { v[0]=x; v[1]=y; v[2]=z; } 
  void set(double *x) { v[0]=x[0]; v[1]=x[1]; v[2]=x[2]; } 

  void normalize() 
    {
      double s = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
      v[0] /= s;
      v[1] /= s;
      v[2] /= s;
    }
  
};


v3
operator+(const v3 &va, const v3 &vb);

v3
operator-(const v3 &va, const v3 &vb);

v3
operator*(const v3 &va, const double &s);

v3
operator*(const double &s, const v3 &va);

double
operator*(const v3 &va, const v3 &vb);

double
dotp(const v3 &va, const v3 &vb);

v3
crossp(const v3 &va, const v3 &vb);

#endif
/* V3_H */
