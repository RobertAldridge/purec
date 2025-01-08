/*************************************************************************\

  Copyright 1995 The University of North Carolina at Chapel Hill.
  All Rights Reserved.

  Permission to use, copy, modify and distribute this software and its
  documentation for educational, research and non-profit purposes, without
  fee, and without a written agreement is hereby granted, provided that the
  above copyright notice and the following three paragraphs appear in all
  copies.

  IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL BE
  LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR
  CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE
  USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY
  OF NORTH CAROLINA HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGES.


  Permission to use, copy, modify and distribute this software and its
  documentation for educational, research and non-profit purposes, without
  fee, and without a written agreement is hereby granted, provided that the
  above copyright notice and the following three paragraphs appear in all
  copies.

  THE UNIVERSITY OF NORTH CAROLINA SPECIFICALLY DISCLAIM ANY
  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE
  PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND THE UNIVERSITY OF
  NORTH CAROLINA HAS NO OBLIGATIONS TO PROVIDE MAINTENANCE, SUPPORT,
  UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

  The authors may be contacted via:

  US Mail:             S. Gottschalk
                       Department of Computer Science
                       Sitterson Hall, CB #3175
                       University of N. Carolina
                       Chapel Hill, NC 27599-3175

  Phone:               (919)962-1749

  EMail:              {gottscha}@cs.unc.edu


\**************************************************************************/



// triangle intersection

// -DDOUBLE => double precision, else single
// -DPIVOT => perform partial pivoting
// -DTEST => test for accuracy of intersection points

/*
 csg (SGI@250MHz)
 g++ -O2 Intersect.cc
 pixie a.out
 a.out.pixie
 prof -pixie a.out
-- no optimisation, intersect = 8.02us
-- -mcpu=r4400 -mips2 -O1, 4.40us
-- -mcpu=r4400 -mips2 -O2, 3.64us
-- -O2, 3.53us
 neumann (HP@150MHz)
 g++ -O3 -mpa-risc-1-1 Intersect.cc
 */

#include <assert.h>
#include <math.h>
#include <iostream.h>

#include "Intersect.H"

#ifdef gnu

#ifdef DOUBLE

#ifdef hppa
#define myfabs(x) \
 ({double __value, __arg = (x); \
   asm("fabs,dbl %1, %0": "=f" (__value): "f" (__arg)); \
   __value; \
});
#endif

#ifdef mips
#define myfabs(x) \
 ({double __value, __arg = (x); \
   asm("abs.d %0, %1": "=f" (__value): "f" (__arg)); \
   __value; \
});
#endif

#else

#ifdef hppa
#define myfabs(x) \
 ({float __value, __arg = (x); \
   asm("fabs,sgl %1, %0": "=f" (__value): "f" (__arg)); \
   __value; \
});
#endif

#ifdef mips
#define myfabs(x) \
 ({float __value, __arg = (x); \
   asm("abs.s %0, %1": "=f" (__value): "f" (__arg)); \
   __value; \
});
#endif

#endif
// DOUBLE

#else

#define myfabs(x) (fabs(x)) 

#endif


#ifdef TEST

#ifdef DOUBLE
#define EPSILON (.00000000001)
#else
#define EPSILON (.0001)
#endif

Triple v0, v1;
  
#define errorTEST(a0,a1,a2,b0,b1,s,t,u) \
{\
  for (int ij = 0; ij < 3; ++ ij)\
  {\
    v0[ij] = s * a0[ij] + t * a1[ij] + (1 - s - t) * a2[ij];\
    v1[ij] = (1 - u) * b0[ij] + u * b1[ij];\
  }\
  if ((fabs (v0[0] - v1[0]) > EPSILON) || (fabs (v0[1] - v1[1]) > EPSILON) ||\
      (fabs (v0[2] - v1[2]) > EPSILON))\
  {\
    cerr << '(' << v0[0] << ", " << v0[1] << ", " << v0[2] << ") != (" <<\
      v1[0] << ", " << v1[1] << ", " << v1[2] << ") by (" <<\
      fabs (v0[0] - v1[0]) << ", " << fabs (v0[1] - v1[1]) << ", " <<\
      fabs (v0[2] - v1[2]) << ')' << endl;\
  }\
}

#else

#define errorTEST(a0,a1,a2,b0,b1,s,t,u)

#endif

#define sectTEST(b0,b1,p00,p01,p02,p03,p10,p11,p12,p13,p20,p21,p22,p23) \
{\
  m02 = b0[0] - b1[0];\
  m12 = b0[1] - b1[1];\
  m22 = b0[2] - b1[2];\
\
  m03 = b0[0] - a[2][0];\
  m13 = b0[1] - a[2][1];\
  m23 = b0[2] - a[2][2];\
\
  p12 -= p02 * r0;\
  p13 -= p03 * r0;\
\
  p22 -= p02 * r1;\
  p23 -= p03 * r1;\
\
  p22 -= p12 * r2;\
  p23 -= p13 * r2;\
\
  u = p23 / p22;\
  if ((u >= 0) && (u <= 1))\
  {\
    t = (p13 - p12 * u) / p11;\
    if ((t >= 0) && (t <= 1))\
    {\
      s = (p03 - p02 * u - p01 * t) / p00;\
      if ((s >= 0) && (s + t <= 1))\
      {\
	errorTEST (a[0], a[1], a[2], b0, b1, s, t, u);\
	return 1;\
      }\
    }\
  }\
}

#define fullSECT(p00,p01,p02,p03,p10,p11,p12,p13,p20,p21,p22,p23) \
{\
  r0 = p10 / p00;\
  p11 -= p01 * r0;\
  r1 = p20 / p00;\
  p21 -= p01 * r1;\
  r2 = p21 / p11;\
\
  sectTEST (b[0], b[1], p00, p01, p02, p03, p10, p11, p12, p13, p20, p21, p22, p23);\
  sectTEST (b[1], b[2], p00, p01, p02, p03, p10, p11, p12, p13, p20, p21, p22, p23);\
  sectTEST (b[2], b[0], p00, p01, p02, p03, p10, p11, p12, p13, p20, p21, p22, p23);\
}


// if any b edge intersects a
int intersect (double *p1, double *p2, double *p3,
	       double *q1, double *q2, double *q3) 
{
  Triple a[3], b[3];
  
  a[0][0] = p1[0];
  a[0][1] = p1[1];
  a[0][2] = p1[2];
  a[1][0] = p2[0];
  a[1][1] = p2[1];
  a[1][2] = p2[2];
  a[2][0] = p3[0];
  a[2][1] = p3[1];
  a[2][2] = p3[2];
  
  b[0][0] = q1[0];
  b[0][1] = q1[1];
  b[0][2] = q1[2];
  b[1][0] = q2[0];
  b[1][1] = q2[1];
  b[1][2] = q2[2];
  b[2][0] = q3[0];
  b[2][1] = q3[1];
  b[2][2] = q3[2];

  SectType m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23;
  SectType f00, f10, f20, f01, f11, f21;
  SectType r0, r1, r2, s, t, u;
  
  m00 = a[0][0] - a[2][0];
  m10 = a[0][1] - a[2][1];
  m20 = a[0][2] - a[2][2]; // 3

  m01 = a[1][0] - a[2][0];
  m11 = a[1][1] - a[2][1];
  m21 = a[1][2] - a[2][2]; // 3

#ifdef PIVOT

  f00 = myfabs(m00);
  f10 = myfabs(m10);
  f20 = myfabs(m20);

  if (f00 > f10)
  {
    f11 = myfabs (m11);
    if (f00 > f20)
    {
      f21 = myfabs (m21);
      if (f11 >= f21)
      {
	// 012
	fullSECT (m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23);
      }
      else
      {
	// 021
	fullSECT (m00, m01, m02, m03, m20, m21, m22, m23, m10, m11, m12, m13);
      }
    }
    else
    {
      f01 = myfabs (m01);
      if (f01 >= f11)
      {
	// 201
	fullSECT (m20, m21, m22, m23, m00, m01, m02, m03, m10, m11, m12, m13);
      }
      else
      {
	// 210
	fullSECT (m20, m21, m22, m23, m10, m11, m12, m13, m00, m01, m02, m03);
      }
    }
  }
  else
  {
    f01 = myfabs (m01);
    if (f10 > f20)
    {
      f21 = myfabs (m21);
      if (f01 >= f21)
      {
	// 102
	fullSECT (m10, m11, m12, m13, m00, m01, m02, m03, m20, m21, m22, m23);
      }
      else
      {
	// 120
	fullSECT (m10, m11, m12, m13, m20, m21, m22, m23, m00, m01, m02, m03);
      }
    }
    else
    {
      f11 = myfabs (m11);
      if (f01 >= f11)
      {
	// 201
	fullSECT (m20, m21, m22, m23, m00, m01, m02, m03, m10, m11, m12, m13);
      }
      else
      {
	// 210
	fullSECT (m20, m21, m22, m23, m10, m11, m12, m13, m00, m01, m02, m03);
      }
    }
  }

#else

  fullSECT (m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23);

#endif

  return 0;
}


