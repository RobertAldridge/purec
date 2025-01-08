#include "m33.H"
#include "angle.H"
#include <math.h>

void
m33::fprintf(FILE *fp, const char *fmt)
{
  int i,j;
  for(i=0; i<3; i++) 
    {
      for(j=0; j<3; j++)
	{
	  ::fprintf(fp, fmt, m[i][j]);
	}
      ::fprintf(fp, "\n");
    }
  return;
}

m33::m33(const m33 &m1)
{
  int i,j;
  for(i=0; i<3; i++) for(j=0; j<3; j++) m[i][j] = m1.m[i][j];
}


m33::m33(double m00, double m10, double m20, 
	 double m01, double m11, double m21, 
	 double m02, double m12, double m22)
{
  m[0][0] = m00;
  m[0][1] = m01;
  m[0][2] = m02;
  m[1][0] = m10;
  m[1][1] = m11;
  m[1][2] = m12;
  m[2][0] = m20;
  m[2][1] = m21;
  m[2][2] = m22;
}

m33::m33()
{
  make_identity();
}

void
m33::make_identity()
{
  int i,j;
  for(i=0; i<3; i++) for(j=0; j<3; j++) m[i][j] = (i == j) ? 1.0 : 0.0;
}

m33
m33::T() const
{
  m33 m2;
  
  int i,j;
  for(i=0; i<3; i++) for(j=0; j<3; j++) m2.m[i][j] = m[j][i];

  return m2;
}


m33 
m33::inverse() const
{
  // basic application of Kramer's rule.  This is probably unstable or 
  // something, but I need a inverter now! 

  m33 I;
  int i,j;

  double det = m[0][0]*m[1][1]*m[2][2] +
               m[0][1]*m[1][2]*m[2][0] +
               m[0][2]*m[1][0]*m[2][1] -
               m[0][2]*m[1][1]*m[2][0] -
               m[0][1]*m[1][0]*m[2][2] -
	       m[0][0]*m[1][2]*m[2][1];

  if (det == 0.0)
    {
      ::fprintf(stderr, "m33.C: inverse() -- singular matrix!\n");
      ::fflush(stderr);
      return Identity();
    }
  
  for(i=0; i<3; i++)
    for(j=0; j<3; j++)
      {
	int i1 = (i+1)%3;
	int i2 = (i+2)%3;
	int j1 = (j+1)%3;
	int j2 = (j+2)%3;
	I.m[i][j] = (m[j1][i1]*m[j2][i2] - m[j1][i2]*m[j2][i1]) / det;
      }

  return I;
}


m33
T(m33 m1)
{
  m33 m2;
  
  int i,j;
  for(i=0; i<3; i++) for(j=0; j<3; j++) m2.m[i][j] = m1.m[j][i];

  return m2;
}

m33
operator+(const m33 &m1, const m33 &m2)
{
  m33 m3;
  
  int i,j;
  for(i=0; i<3; i++) for(j=0; j<3; j++) m3.m[i][j] = m1.m[i][j] + m2.m[i][j];
  
  return m3;
}


m33
operator-(const m33 &m1, const m33 &m2)
{
  m33 m3;
  
  int i,j;
  for(i=0; i<3; i++) for(j=0; j<3; j++) m3.m[i][j] = m1.m[i][j] - m2.m[i][j];
  
  return m3;
}


m33
operator*(const m33 &m1, const m33 &m2)
{
  m33 m3;
  
  int i,j;
  for(i=0; i<3; i++) for(j=0; j<3; j++) 
    {
      double s;
      
      s = 0.0;
      
      int k;
      for(k=0; k<3; k++) s += m1.m[i][k] * m2.m[k][j];

      m3.m[i][j] = s;
    }
  
  return m3;
}

m33
operator*(const m33 &m1, const double &s)
{
  m33 m3;
  
  int i,j;
  for(i=0; i<3; i++) for(j=0; j<3; j++) 
      m3.m[i][j] = m1.m[i][j] * s;
  
  return m3;
}


m33
operator*(const double &s, const m33 &m1)
{
  m33 m3;
  
  int i,j;
  for(i=0; i<3; i++) for(j=0; j<3; j++) 
      m3.m[i][j] = s * m1.m[i][j];
  
  return m3;
}




m33
Identity()
{
  m33 m1;
  m1.m[0][0] = m1.m[1][1] = m1.m[2][2] = 1.0;
  m1.m[1][0] = m1.m[2][1] = m1.m[0][2] = 0.0;
  m1.m[0][1] = m1.m[1][2] = m1.m[2][0] = 0.0;
  return m1;
}



m33
Rx(radians t)
{
  m33 m1;
  
  m1.m[0][0] = 1.0;
  m1.m[1][0] = m1.m[2][0] = m1.m[0][1] = m1.m[0][2] = 0.0;
  m1.m[1][1] = m1.m[2][2] = cos(t);
  m1.m[1][2] = -(m1.m[2][1] = sin(t));

  return m1;
}

m33
Ry(radians t)
{
  m33 m1;
  
  m1.m[1][1] = 1.0;
  m1.m[0][1] = m1.m[2][1] = m1.m[1][0] = m1.m[1][2] = 0.0;
  m1.m[0][0] = m1.m[2][2] = cos(t);
  m1.m[2][0] = -(m1.m[0][2] = sin(t));

  return m1;
}

m33
Rz(radians t)
{
  m33 m1;
  
  m1.m[2][2] = 1.0;
  m1.m[0][2] = m1.m[1][2] = m1.m[2][0] = m1.m[2][1] = 0.0;
  m1.m[0][0] = m1.m[1][1] = cos(t);
  m1.m[0][1] = -(m1.m[1][0] = sin(t));

  return m1;
}


m33
R(double dx, double dy, double dz, radians t)
{
  m33 m1;
  double r[3];
  
  double l = sqrt(dx*dx + dy*dy + dz*dz);

  r[0] = dx/l;
  r[1] = dy/l;
  r[2] = dz/l;
  
  m1.m[0][0] = r[0]*r[0] + cos(t)*(1.0 - r[0]*r[0]);
  m1.m[1][1] = r[1]*r[1] + cos(t)*(1.0 - r[1]*r[1]);
  m1.m[2][2] = r[2]*r[2] + cos(t)*(1.0 - r[2]*r[2]);
  
  m1.m[1][0] = r[1]*r[0] - cos(t)*r[1]*r[0] + r[2]*sin(t);
  m1.m[0][1] = r[0]*r[1] - cos(t)*r[0]*r[1] - r[2]*sin(t);
  
  m1.m[2][0] = r[2]*r[0] - cos(t)*r[2]*r[0] - r[1]*sin(t);
  m1.m[0][2] = r[0]*r[2] - cos(t)*r[0]*r[2] + r[1]*sin(t);
  
  m1.m[2][1] = r[2]*r[1] - cos(t)*r[2]*r[1] + r[0]*sin(t);
  m1.m[1][2] = r[1]*r[2] - cos(t)*r[1]*r[2] - r[0]*sin(t);
  
  return m1;
}

m33
Mat(double M[3][3])
{
  m33 m3;
  
  int i,j;
  for(i=0; i<3; i++) for(j=0; j<3; j++) 
      m3.m[i][j] = M[i][j];
  
  return m3;
}

v3
m33::col(int c) const
{
  v3 V;
  V.v[0] = m[0][c];
  V.v[1] = m[1][c];
  V.v[2] = m[2][c];
  return V;
}

v3
m33::row(int r) const
{
  v3 V;
  V.v[0] = m[r][0];
  V.v[1] = m[r][1];
  V.v[2] = m[r][2];
  return V;
}





