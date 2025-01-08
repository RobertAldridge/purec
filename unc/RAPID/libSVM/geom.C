#include "geom.H"
#include "m33.H"
#include "v3.H"
#include "m33v3.H"

v3
point_closest_to_lines(v3 *p, v3 *d, int n)
{
  int k;
  int i,j;

  // n lines.  The k'th line originates at p[k] with heading d[k].
  // The d[k]'s are expected to be unit length.

  m33 I = Identity();

  double *A = new double[3*3*n];
  double *b = new double[3*n];
  
  // create the A matrix and the b vector.

  for(k=0; k<n; k++) for(i=0; i<3; i++)
    {
      int l = 3*k+i;
      b[l] = (p[k]*d[k])*d[k].v[i]-p[k].v[i];
      for(j=0; j<3; j++)
	  A[3*l+j] = I.m[i][j] - d[k].v[i]*d[k].v[j];
    }

  // form pseudo inverse

  m33 AtA;
  for(i=0; i<3; i++)
    for(j=0; j<3; j++)
      {
	AtA.m[i][j] = 0.0;
	for(k=0; k<(3*n); k++)
	  AtA.m[i][j] += A[3*k+i] * A[3*k+j];
      }

  // compute b transformed by At

  v3 c;
  for(i=0; i<3; i++)
    {
      c.v[i] = 0.0;
      for(k=0; k<(3*n); k++)
	c.v[i] += A[3*k+i] * b[k];
    }
  
  // compute q
  v3 q = AtA.inverse() * c * -1.0;

  delete [] A;
  delete [] b;
  
  return q;
}
