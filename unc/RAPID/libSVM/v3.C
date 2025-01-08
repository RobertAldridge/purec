#include "v3.H"
#include "angle.H"

void
v3::fprintf(FILE *fp, const char *fmt)
{
  int i;
  for(i=0; i<3; i++) 
    {
      ::fprintf(fp, fmt, v[i]);
    }
  ::fprintf(fp, "\n");

  return;
}

v3
operator+(const v3 &va, const v3 &vb)
{
  v3 vc;
  
  int i;
  for(i=0; i<3; i++) vc.v[i] = va.v[i] + vb.v[i];
  
  return vc;
}


v3
operator-(const v3 &va, const v3 &vb)
{
  v3 vc;
  
  int i;
  for(i=0; i<3; i++) vc.v[i] = va.v[i] - vb.v[i];
  
  return vc;
}


v3
operator*(const v3 &va, const double &s)
{
  v3 vb;
  
  int i;
  for(i=0; i<3; i++)
      vb.v[i] = va.v[i] * s;
  
  return vb;
}


v3
operator*(const double &s, const v3 &va)
{
  v3 vb;
  
  int i;
  for(i=0; i<3; i++)
      vb.v[i] = s * va.v[i];
  
  return vb;
}


double
operator*(const v3 &va, const v3 &vb)
{
  int i;
  
  double s = 0.0;
  
  for(i=0;i<3; i++) s += va.v[i]*vb.v[i];

  return s;
}


double
dotp(const v3 &va, const v3 &vb)
{
  int i;
  
  double s = 0.0;
  
  for(i=0;i<3; i++) s += va.v[i]*vb.v[i];

  return s;
}



v3
crossp(const v3 &va, const v3 &vb)
{
  v3 vc;
  
  vc.v[0] = va.v[1] * vb.v[2] - va.v[2] * vb.v[1];
  vc.v[1] = va.v[2] * vb.v[0] - va.v[0] * vb.v[2];
  vc.v[2] = va.v[0] * vb.v[1] - va.v[1] * vb.v[0];
  
  return vc;
}








