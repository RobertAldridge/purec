/******************************************************************************\

  Copyright 2004 The University of North Carolina at Chapel Hill.
  All Rights Reserved.

  Permission to use, copy, modify and distribute this software and its
  documentation for educational, research and non-profit purposes, without
  fee, and without a written agreement is hereby granted, provided that the
  above copyright notice and the following three paragraphs appear in all
  copies. Any use in a commercial organization requires a separate license.

  IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL BE LIABLE
  TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
  DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND
  ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF NORTH CAROLINA HAVE BEEN
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.


  Permission to use, copy, modify and distribute this software and its
  documentation for educational, research and non-profit purposes, without
  fee, and without a written agreement is hereby granted, provided that the
  above copyright notice and the following three paragraphs appear in all
  copies.

  THE UNIVERSITY OF NORTH CAROLINA SPECIFICALLY DISCLAIM ANY WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
  FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN
  "AS IS" BASIS, AND THE UNIVERSITY OF NORTH CAROLINA HAS NO OBLIGATION TO
  PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.


   ---------------------------------
  |Please send all BUG REPORTS to:  |
  |                                 |
  |   geom@cs.unc.edu               |
  |                                 |
   ---------------------------------


  The authors may be contacted via:

  US Mail:         K. Hoff, M. Foskey, A. Sud, M. Lin or D. Manocha
                       Department of Computer Science
                       Sitterson Hall, CB #3175
                       University of N. Carolina
                       Chapel Hill, NC 27599-3175

  Phone:               (919)962-1749


\*****************************************************************************/

//============================================================================
// line_distmesh_grad.cpp
//============================================================================

#include "line_distmesh_grad.hpp"

#include <math.h>
#include <GL/glut.h>

#include "grad_utilities.hpp"
#include "pt_distmesh_grad.hpp"
#include "sitecull.hpp"

#ifdef STATS_ON
  extern int VertCount;
  extern int TriCount;
#endif

//----------------------------------------------------------------------------
// Given a starting point on the hyperbola defined as (x0,sqrt(x0^2+D^2)),
// an DistError, and a MaxDist value, computes the next x value x1 so that the 
// line segments between points at x0 and x1 on the hyperbola is <= DistError
// away from the actual hyperbola in the y direction. x0, D, DistError, and
// MaxDist >= 0. Check is made to avoid degenerate cases: if starting point
// is within DistError of the asymptotes (y=x) then the x value for a hyperbola
// of MaxDist is returned: MaxDist=sqrt(x^2+d^2), so x=sqrt(MaxDist^2-D^2).
// Returns (0) if x1 can be arbitrarily large, computes x1 that gives values
// of MaxDist on hyperbola. Returns (1) if smaller steps must still be taken.
// Also used in line_distmesh_grad.cpp.
//----------------------------------------------------------------------------
int
Hyperbola_CalcNextX_Grad(double x0, double *x1, double D, double DistError, float MaxDist)
{

  // Foskey 5/23/02
  // If x0 == 0 automatically take a small step; this avoids problems
  // with the gradient computation.
  if (x0 == 0.0f) { *x1=DistError; return(1); }

  // Stupid hack to get more accurate gradients
  *x1 = x0 + 2 * DistError; return 1;

  double a,b,c,m,discr,t,y0,x02,D2,x02_D2;

  // SOME PRECOMPUTED VALUES
  x02=x0*x0;
  D2 = D*D;
  x02_D2=x02+D2;
  y0=sqrt(x02_D2);

  // CHECK IF THE STARTING POINT IS ALREADY WITHIN DistError OF THE ASYMPTOTES (y=x line).
  // IF SO, RETURN NEXT X THAT GIVES HYPERBOLA VALUE OF MaxDist.
  if (y0-x0 < DistError) { *x1=sqrt(MaxDist*MaxDist-D2); return(0); }

  // COMPUTE SLOPE OF LINE WHOSE MAX ERROR EQUALS EPSILON
  t = y0-DistError;
  a = x02_D2;
  b = -2*x0*t;
  c = t*t - D2;
  discr = b*b - 4*a*c;
  m = (-b + sqrt(discr) ) / (2*a);

  // COMPUTE INTERSECTION OF LINE WITH SLOPE m WITH HYPERBOLA
  t = y0-m*x0;
  a = m*m - 1;
  b = 2*m*t;
  c = t*t - D2;
  discr = b*b - 4*a*c;
  *x1 = (-b - sqrt(discr) ) / (2*a);

  return(1);
}

//----------------------------------------------------------------------------
// For a line in the XZ-plane through the points (Ax, 0, Az), (Bx, 0,
// Bz), (1) compute the gradient of the distance field for the line at
// a point (x, y, z) not on the line, and (2) rotate the gradient
// vector around the Z axis by Ztheta, as determined by cosZtheta and
// sinZtheta.  Return the resulting vector in (gx, gy, gz).  The
// rotation corrects for the original rotation of the problem into the
// XZ-plane.
//----------------------------------------------------------------------------
void
ComputeGradientGeneral(const float Ax, const float Az, const float Bx, const float Bz,
                const float x, const float y, const float z,
                const float sinZtheta, const float cosZtheta,
                float* gx, float* gy, float* gz)
{
  // Algorithm: Let AB be the vector from A to B, and V be a vector
  // from any point on the line to (x, y, z).  Then an unnormalized
  // vector in the proper direction is
  //   AB cross (V cross AB) = (AB . AB) V - (AB . V) AB.
  // This vector is computed and then rotated and normalized.

  float ABx = Bx - Ax;
  float ABz = Bz - Az;

  // Compute the vector V. Choose vector from nearest endpoint for stability.
  float dxA = x - Ax;
  float dzA = z - Az;
  float dxB = x - Bx;
  float dzB = z - Bz;
  float SqLA = dxA*dxA + y*y + dzA*dzA;
  float SqLB = dxB*dxB + y*y + dzB*dzB;
  float Vx = (SqLA < SqLB ? dxA : dxB);
  float Vy = y;
  float Vz = (SqLA < SqLB ? dzA : dzB);

  // Compute (nrx, nry, nrz) that still requires normalization and rotation.
  float ABdotAB = ABx*ABx + ABz*ABz;
  float ABdotV = ABx * Vx + ABz * Vz;
  float nrx = ABdotV * ABx - ABdotAB * Vx;
  float nry = -ABdotAB * Vy;
  float nrz = ABdotV * ABz - ABdotAB * Vz;

  // Rotate and normalize.
  float OneOverL = 1.0f / (float) sqrt(nrx*nrx + nry*nry + nrz*nrz);
  *gx = (cosZtheta * nrx - sinZtheta * nry) * OneOverL;
  *gy = (sinZtheta * nrx + cosZtheta * nry) * OneOverL;
  *gz = nrz * OneOverL;

}

inline void
ComputeGradient(const float Ax, const float Az, const float Bx, const float Bz,
                const float x, const float y, const float z,
                const float sinZtheta, const float cosZtheta,
                float* gx, float* gy, float* gz)
{
  ComputeGradientGeneral(Ax, Az, Bx, Bz, x, y, 0, sinZtheta, cosZtheta, gx, gy, gz);
}

// Utility routine.  Computes colors for normals at vertices and draws
// triangle.  As this function is used, each color is computed and
// sent twice.  This can be optimized.
static inline void
DrawEllipticalConeTri(const float Angle1, const float Angle2, const float RadiusX,
                      const float RadiusY, const float LineAx, const float LineAz,
                      const float LineBx, const float LineBz, const float MaxDist,
                      const float sinZtheta, const float cosZtheta, unsigned char AlphaColor)
{
  float Ax = cos(Angle1) * RadiusX;
  float Ay = sin(Angle1) * RadiusY;
  float Az = MaxDist;
  float Bx = cos(Angle2) * RadiusX;
  float By = sin(Angle2) * RadiusY;
  float Bz = MaxDist;

  // Compute gradient vectors at A and B.
  float Agx, Agy, Agz, Bgx, Bgy, Bgz;
  ComputeGradient(LineAx, LineAz, LineBx, LineBz, Ax, Ay, Az, 
                  sinZtheta, cosZtheta, &Agx, &Agy, &Agz);
  ComputeGradient(LineAx, LineAz, LineBx, LineBz, Bx, By, Bz, 
                  sinZtheta, cosZtheta, &Bgx, &Bgy, &Bgz);

  // Linearly interpolate to get gradient at origin.  (Can't use
  // ComputeGradient() there since line passes through origin.)
  float Ogx = (Agx + Bgx) * 0.5f;
  float Ogy = (Agy + Bgy) * 0.5f;
  float Ogz = (Agz + Bgz) * 0.5f;

  // Draw triangle
  glColor4ub(SCALEBIAS(Agx), SCALEBIAS(Agy), SCALEBIAS(Agz), AlphaColor);
  glVertex3f(Ax, Ay, Az);
  glColor4ub(SCALEBIAS(Bgx), SCALEBIAS(Bgy), SCALEBIAS(Bgz), AlphaColor);
  glVertex3f(Bx, By, Bz);
  glColor4ub(SCALEBIAS(Ogx), SCALEBIAS(Ogy), SCALEBIAS(Ogz), AlphaColor);
  glVertex3f(0, 0, 0);

#ifdef STATS_ON
  VertCount+=3;
  TriCount+=1;
#endif
}

//----------------------------------------------------------------------------
// Core routine 1 (PERPENDICULAR CASE): for an infinite line in the XZ-plane with 
//   slope m (dz/dx) that intersects the origin (line equation = z=mx). Distance 
//   function defined over points (x,y) in the z=0 plane. The planar slice of
//   the distance function is the z=0 plane. Arbitrary lines must be transformed 
//   into this case. The slope is specified by dz and dx directly to avoid problems 
//   with computing the slope (infinity when dx=0).
//     X scale factor = sqrt(1+m*m)/m = sqrt(dx^2+dz^2)/dz^2
//   There is still a problem when slope is near 0: dz too small, Xscale->infinity. 
//   The shape of the distance function is not an elliptical cone, but a quad-tent.
//   Use Core routine 2 for this case. This routine does no sanity checking,
//   if the line is too close to being parallel to the XY-plane, then it will fail.
//----------------------------------------------------------------------------
static void
DrawDistMesh_Line_Origin(float dx, float dz, float DistError, float MaxDist,
                         float sinZtheta, float cosZtheta, unsigned char AlphaColor)
{
  float ScaleX = (float)(sqrt(dx*dx+dz*dz)/dz);
  ScaleX = (ScaleX<0)?-ScaleX:ScaleX;
  float RadiusY = MaxDist;
  float RadiusX = MaxDist*ScaleX;
  float MaxAng = 0.5f * acos( (MaxDist-DistError) / MaxDist );
  int NumSides = (int)((2*3.1415927f)/MaxAng)+1;
  float AngIncr = (2*3.1415927f) / (float)NumSides;
  glBegin(GL_TRIANGLES);
  {
    DrawEllipticalConeTri(0, AngIncr, RadiusX, RadiusY, 0, 0, dx, dz,
                          MaxDist, sinZtheta, cosZtheta, AlphaColor);
    for (int i=1; i<NumSides-1; i++)
    {
      DrawEllipticalConeTri(i * AngIncr, (i+1) * AngIncr, RadiusX, RadiusY,
                            0, 0, dx, dz, MaxDist, sinZtheta, cosZtheta, AlphaColor);
    }
    DrawEllipticalConeTri(-AngIncr, 0, RadiusX, RadiusY, 0, 0, dx, dz,
                          MaxDist, sinZtheta, cosZtheta, AlphaColor);
  }
  glEnd();
}

//----------------------------------------------------------------------------
// Core routine 3 ("NEARLY" PARALLEL CASE): for an infinite line in the XZ-plane that
//   is parallel (or nearly) to the XY-plane NOT necessarily through the origin. 
//   Constructs the distance mesh within the domain x=[x0,x1], 
//   y=[-MaxDist,MaxDist], x0<=x1. The user provides two points on the line A and B.
//   This routine, like core routine 1, is fairly general, but it cannot handle
//   lines that are nearly perpendicular to the XY-plane. This routine
//   works best with slopes of dz/dx<1. The domain [x0,x1] is normally computed
//   from the projection of points A and B on the line as follows: 
//     dx=Bx-Ax, dz=Bz-Az, dzx=dz/dx;
//     dAx=Az*dzx, dBx=Bz*dzx;
//     x0=Ax+dAx, x1=Bx+dBx;
//----------------------------------------------------------------------------
static void
DrawDistMesh_Line(float Ax, float Az, float Bx, float Bz, float x0, float x1,
                  float DistError, float MaxDist,
                  float sinZtheta, float cosZtheta, unsigned char AlphaColor)
{
  float t;
  #define SWAP(a,b,t) t=a,a=b,b=t

  // RECOMPUTE (Ax,Az) AND (Bx,Bz) SO THAT THEY CORRESPOND TO DOMAIN [x0,x1] WHEN PROJECTED ONTO LINE AB
  // FIND THE PERPENDICULAR DISTANCES TO THE LINE FROM THESE BOUNDARY POINTS (dx0,dx1)
  float dx=Bx-Ax, dz=Bz-Az, l=(float)sqrt(dx*dx+dz*dz);
  dx/=l; dz/=l;
  float x0Ax=x0-Ax, x1Ax=x1-Ax;
  float Azdx=Az*dx, dx0=x0Ax*dz+Azdx, dx1=x1Ax*dz+Azdx;
  dx0=(dx0<0)?-dx0:dx0;
  dx1=(dx1<0)?-dx1:dx1;
  float Azdz=Az*dz, x0factor=x0Ax*dx-Azdz, x1factor=x1Ax*dx-Azdz;
  Bx = Ax + x1factor*dx;
  Bz = Az + x1factor*dz;
  Ax += x0factor*dx;
  Az += x0factor*dz;

  // SORT POINTS BY Z VALUE Az<=Bz (A SHOULD BE CLOSEST TO Z=0 PLANE AND THE INTERSECTION POINT)
  if (dx0>dx1) { SWAP(Ax,Bx,t); SWAP(Az,Bz,t); SWAP(x0,x1,t); SWAP(dx0,dx1,t); }

  // IF CLOSE ENOUGH TO LYING IN THE PLANE APPROXIMATE WITH QUAD-TENT
  // if (dx0<=DistError && dx1<=DistError)
  // Foskey -- Don't approximate with quad tent; leads to inaccurate
  // direction vectors.
  if (0)
  {
    if (x0>x1) { t=x0; x0=x1; x1=t; t=dx0; dx0=dx1; dx1=t; };  // SORT IN X
    float gx, gy, gz;
    ComputeGradient(Ax, Az, Bx, Bz, x0, -MaxDist, MaxDist, sinZtheta, cosZtheta, &gx, &gy, &gz);
    unsigned char ubgx = SCALEBIAS(gx), ubgy = SCALEBIAS(gy), ubgz = SCALEBIAS(gz);
    glBegin(GL_QUADS);
      glColor4ub(ubgx, ubgy, ubgz, AlphaColor);
      glVertex3f(x0,-MaxDist,MaxDist);
      glVertex3f(x1,-MaxDist,MaxDist);
      glVertex3f(x0,0,dx0);
      glVertex3f(x1,0,dx1);
      glColor4ub(255-ubgx, 255-ubgy, ubgz, AlphaColor);
      glVertex3f(x0,0,dx0);
      glVertex3f(x1,0,dx1);
      glVertex3f(x0,MaxDist,MaxDist);
      glVertex3f(x1,MaxDist,MaxDist);
    glEnd();
#ifdef STATS_ON
  VertCount+=6;
  TriCount+=4;
#endif
    return;
  }

  // IF THE ENDPOINTS HAVE OPPOSITE SIGN Z VALUES, THEN THE DOMAIN CONTAINS INTERSECTION POINT
  // IF ENDPOINT DISTANCES ARE NOT <= DistError, THEN IT CANNOT BE APPROXIMATED WITH A QUAD TENT.
  // MUST BE APPROXIMATED WITH AN ELLIPTICAL CONE.
  // COMPUTE SCALE FACTOR FOR COMPUTING STEPS IN Y ALONG x=x0 FROM STEPS ALONG x=x1
  // IF THE SCALE FACTOR IS "TOO SMALL", THE INTERSECTION POINT IS TOO CLOSE TO THE
  // LINE SEGMENT. THIS WOULD BE BETTER APPROXIMATED BY AN ELLIPTICAL CONE
  float x0_Yscale = Az/Bz;
  if (Az*Bz<0 || x0_Yscale<DistError)
  {
    // NEED TO ADD CLIPPING PLANES TO RESTRICT TO DOMAIN x=[x0,x1]
    if (x0>x1) { SWAP(x0,x1,t); }
    GLdouble P0[]={1,0,0,-x0}, P1[]={-1,0,0,x1};
    glEnable(GL_CLIP_PLANE0);
    glEnable(GL_CLIP_PLANE1);
    glClipPlane(GL_CLIP_PLANE0,P0);
    glClipPlane(GL_CLIP_PLANE1,P1);

    // APEX OF ELLIPTICAL CONE IS THE INTERSECTION BETWEEN LINE AND XY-PLANE
    // LINE MUST BE TRANSLATED TO LINE THROUGH ORIGIN
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(Ax-Az*(dx/dz),0,0);
      DrawDistMesh_Line_Origin(dx,dz,DistError,MaxDist, sinZtheta, cosZtheta, AlphaColor);
    glPopMatrix();

    glDisable(GL_CLIP_PLANE0);
    glDisable(GL_CLIP_PLANE1);
    return;
  }

  // IF DISTANCES TO LINE ARE ALREADY GREATER THAN MaxDist, QUIT! CHECK MUST BE PERFORMED
  // AFTER OPPOSITE SIGNS TEST
  if (dx0>MaxDist) return;

  // NOW WE HAVE TWO HYPERBOLIC CROSS-SECTIONS IN THE PLANES PERPENDICULAR TO THE
  // LINE THAT INTERSECT THE ENDPOINTS. WE CONSTRUCT A QUAD-MESH BY FINDING STEPS
  // IN Y ALONG THE x=x1 LINE THAT FITS THE HYPERBOLA (FARTHEST LINE FROM INTERSECTION POINT).
  // THE STARTING POINTS FOR EACH HALF ARE (x0,y0,z0)=(x0,0,dx0) AND (x1,y1,z1)=(x1,0,dx1)
  int StillGoing;
  double y0,y1;
  float z0,z1,dx02,dx12,MaxDist2;
  dx02=dx0*dx0;
  dx12=dx1*dx1;
  MaxDist2=MaxDist*MaxDist;

  // TOP HALF
  y0=y1=0;
  z0=dx0;
  z1=dx1;
  float gx, gy, gz;
  glBegin(GL_QUAD_STRIP);
    StillGoing=1;
    do {
      ComputeGradient(Ax, Az, Bx, Bz, x0, y0, z0, sinZtheta, cosZtheta, &gx, &gy, &gz);
      glColor4ub(SCALEBIAS(gx), SCALEBIAS(gy), SCALEBIAS(gz), AlphaColor);
      glVertex3f(x0,y0,z0);
      ComputeGradient(Ax, Az, Bx, Bz, x1, y1, z1, sinZtheta, cosZtheta, &gx, &gy, &gz);
      glColor4ub(SCALEBIAS(gx), SCALEBIAS(gy), SCALEBIAS(gz), AlphaColor);
      glVertex3f(x1,y1,z1);
#ifdef STATS_ON
  VertCount+=2;
  TriCount+=2;
#endif
      StillGoing=Hyperbola_CalcNextX_Grad(y1,&y1,dx1,DistError,MaxDist);
      y0=y1*x0_Yscale;
      z0=(float)sqrt(y0*y0+dx02);
      z1=(float)sqrt(y1*y1+dx12);
    } while(StillGoing && z0<MaxDist);
    y0=sqrt(MaxDist2-dx02);                     // ANCHOR LAST "X0" VERTEX AT z=MaxDist POSITION
    y1=y0/x0_Yscale;                            // FIND ASSOCIATED "X1" VERTEX
    ComputeGradient(Ax, Az, Bx, Bz, x0, y0, MaxDist, sinZtheta, cosZtheta, &gx, &gy, &gz);
    glColor4ub(SCALEBIAS(gx), SCALEBIAS(gy), SCALEBIAS(gz), AlphaColor);
    glVertex3f(x0,y0,MaxDist);
    z1 = sqrt(y1*y1+dx12);
    ComputeGradient(Ax, Az, Bx, Bz, x1, y1, z1, sinZtheta, cosZtheta, &gx, &gy, &gz);
    glColor4ub(SCALEBIAS(gx), SCALEBIAS(gy), SCALEBIAS(gz), AlphaColor);
    glVertex3f(x1,y1,z1);
#ifdef STATS_ON
  VertCount+=2;
#endif
  glEnd();

  // BOTTOM HALF
  y0=y1=0;
  z0=dx0;
  z1=dx1;
  glBegin(GL_QUAD_STRIP);
    StillGoing=1;
    do {
      ComputeGradient(Ax, Az, Bx, Bz, x0, -y0, z0, sinZtheta, cosZtheta, &gx, &gy, &gz);
      glColor4ub(SCALEBIAS(gx), SCALEBIAS(gy), SCALEBIAS(gz), AlphaColor);
      glVertex3f(x0,-y0,z0);
      ComputeGradient(Ax, Az, Bx, Bz, x1, -y1, z1, sinZtheta, cosZtheta, &gx, &gy, &gz);
      glColor4ub(SCALEBIAS(gx), SCALEBIAS(gy), SCALEBIAS(gz), AlphaColor);
      glVertex3f(x1,-y1,z1);
#ifdef STATS_ON
  VertCount+=2;
  TriCount+=2;
#endif
      StillGoing=Hyperbola_CalcNextX_Grad(y1,&y1,dx1,DistError,MaxDist);
      y0=y1*x0_Yscale;
      z0=(float)sqrt(y0*y0+dx02);
      z1=(float)sqrt(y1*y1+dx12);
    } while(StillGoing && z0<MaxDist);
    y0=sqrt(MaxDist2-dx02);                     // ANCHOR LAST "X0" VERTEX AT z=MaxDist POSITION
    y1=y0/x0_Yscale;                            // FIND ASSOCIATED "X1" VERTEX
    ComputeGradient(Ax, Az, Bx, Bz, x0, -y0, MaxDist, sinZtheta, cosZtheta, &gx, &gy, &gz);
    glColor4ub(SCALEBIAS(gx), SCALEBIAS(gy), SCALEBIAS(gz), AlphaColor);
    glVertex3f(x0,-y0,MaxDist);
    z1 = sqrt(y1*y1+dx12);
    ComputeGradient(Ax, Az, Bx, Bz, x1, -y1, z1, sinZtheta, cosZtheta, &gx, &gy, &gz);
    glColor4ub(SCALEBIAS(gx), SCALEBIAS(gy), SCALEBIAS(gz), AlphaColor);
    glVertex3f(x1,-y1,z1);
#ifdef STATS_ON
  VertCount+=2;
#endif
  glEnd();
}

//----------------------------------------------------------------------------
// General line segment defined by endpoints A and B. We have two cases: lines nearly
// parallel to the XY-plane and those that are not. Most cases are handled by
// Core Routine 1. The general line is transformed into a line in the XZ-plane
// through the origin by a rotation about the Z-axis and a translation in the 
// XY-plane. We must check for nearly parallel lines and send them to Core
// Routine 3. Only the rotation will be performed for these lines (the apex of
// the cone corresponds to the intersection of the line with the plane, which
// is difficult to find in the parallel case).
//----------------------------------------------------------------------------
static void DrawDistMesh_LineSegment_Grad(float A[3], float B[3], 
                              float mx, float my, float Mx, float My,
                              float DistError, float MaxDist, unsigned char AlphaColor)
{
  // *** TRIVIAL REJECTION/ACCEPTANCE TESTING: CHECK IF MIN/MAX BOX ON XY-PLANE INTERSECTS 
  // SLAB FORMED BY PARALLEL PLANES THROUGH LINE SEG ENDPOINTS AND PERPENDICULAR TO LINE SEG
  float dx=B[0]-A[0],dy=B[1]-A[1], dz=B[2]-A[2];
  int NumPtsInA, NumPtsInB;
  NumPtsInA  = ( ((mx-A[0])*dx + (My-A[1])*dy - A[2]*dz) > 0 );
  NumPtsInA += ( ((mx-A[0])*dx + (my-A[1])*dy - A[2]*dz) > 0 );
  NumPtsInA += ( ((Mx-A[0])*dx + (my-A[1])*dy - A[2]*dz) > 0 );
  NumPtsInA += ( ((Mx-A[0])*dx + (My-A[1])*dy - A[2]*dz) > 0 );
  if (NumPtsInA==0) return;                                       // TRIVIALLY REJECT BASED ON PLANE THROUGH A
  NumPtsInB  = ( ((B[0]-mx)*dx - (My-B[1])*dy + B[2]*dz) > 0 );
  NumPtsInB += ( ((B[0]-mx)*dx - (my-B[1])*dy + B[2]*dz) > 0 );
  NumPtsInB += ( ((B[0]-Mx)*dx - (my-B[1])*dy + B[2]*dz) > 0 );
  NumPtsInB += ( ((B[0]-Mx)*dx - (My-B[1])*dy + B[2]*dz) > 0 );
  if (NumPtsInB==0) return;                                       // TRIVIALLY REJECT BASED ON PLANE THROUGH B
  int TriviallyAccept = (NumPtsInA==4 && NumPtsInB==4);           // TRIVIALLY ACCEPT (ENTIRE MIN/MAX DOMAIN)

  // *** FIND XY-PLANE TRANSLATION (T) AND ROTATION ABOUT Z-AXIS (Ztheta) TO TRANSFORM
  // LINE INTO XZ-PLANE. FIND XZ-PLANE LINE SEGMENT ENDPOINTS (Ax,Az), (Bx,Bz)
  // NOTE: TRANSLATION IN XY-PLANE AND ROTATIONS ABOUT Z DO NOT CHANGE SHAPE OF DISTANCE
  // FUNCTION. Az AND Bz STAY THE SAME, Ax BECOMES 0, Bx IS COMPUTED FROM ROTATION
  // TRANSLATE BY (-Ax,-Ay,0)
  double Ztheta=atan2(dy,dx), cosZtheta=cos(Ztheta), sinZtheta=sin(Ztheta);
  float Bx=(float)(dx*cosZtheta+dy*sinZtheta);  // ROTATE NEG Ztheta

  // *** FIND THE DOMAIN ALONG THE X-AXIS OF THE DISTANCE MESH FOR THE LINE SEGMENT IN THE XZ-PLANE

  // TRANSLATE MIN/MAX WINDOW IN XY-PLANE SO THAT VERTEX (Ax,Ay) IS AT THE ORIGIN
  mx-=A[0]; my-=A[1];
  Mx-=A[0]; My-=A[1];

  // ROTATE MIN/MAX EXTENTS TO FIND CORRECT MIN/MAX IN XZ-PLANE
  // USE UNIT VECTOR IN Ztheta DIR (SAME AS dx,dy EXCEPT WHEN PERPENDICULAR) 
  // TO FIND EXTREMAL MIN/MAX BOX VERTS (ONLY ROTATE THESE)
  // PROJECT THESE ONTO THIS VECTOR TO FIND MinX/MaxX EXTENTS [x0,x1]
  float MinX, MinY, MaxX, MaxY, x0, x1;
  dx=cosZtheta;  // CORRECT BOTH TO BE IN Ztheta DIR (in case ==0)
  dy=sinZtheta;
  if (dx>0) { MinX=mx; MaxX=Mx; } else { MinX=Mx; MaxX=mx; }
  if (dy>0) { MinY=my; MaxY=My; } else { MinY=My; MaxY=my; }
  x0=MinX*dx+MinY*dy;  // EXTENTS IN X-AXIS DOMAIN FOR ROTATED GIVEN MIN/MAX WINDOW
  x1=MaxX*dx+MaxY*dy;

  // COMPUTE EXTENTS IN X-AXIS OF "SLAB" OF LINE SEGMENT IN XZ-PLANE
  // ONLY NECESSARY IF ENTIRE WINDOW IS NOT ALREADY CONTAINED WITHIN "SLAB"
  if (!TriviallyAccept)
  {
    // PROJECT XZ-PLANE ENDPOINTS ONTO X-AXIS IN DIR PERPENDICULAR TO LINE SEGMENT
    // PROJECTION IS USED TO COMPUTE DOMAIN [x0,x1] FOR LINE SEGMENT
    float dzx=dz/Bx, X0=A[2]*dzx, X1=Bx+B[2]*dzx;
    if (X0>X1) { float t=X0; X0=X1; X1=t; }       // MAKE SURE x0<=x1

    // FIND DOMAIN FROM INTERSECTION BETWEEN [x0,x1] AND [X0,X1]
    // IF NO INTERSECTION, THEN LINE SEGMENT CAN BE CULLED
    x0=(x0>X0)?x0:X0;  // MIN = MAX OF MINs
    x1=(x1<X1)?x1:X1;  // MAX = MIN OF MAXs
    if (x0>x1) return; // TRIVIALLY REJECT: NO INTERSECTION BETWEEN INTERVALS. (TEST SHOULDN'T BE NECESSARY)
  }

  // *** DRAW THE DISTANCE MESH (MESH WILL HAVE TO BE TRANSFORMED BACK INTO LINE NOT IN XZ-PLANE)
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(A[0],A[1],0);
  glRotatef((float)(Ztheta*57.29577951308232),0,0,1);

  // MESH FOR LINE SEGMENT IN XZ-PLANE (0,A[2]),(Bx,B[2])
  // CHECK IF LINE SEGMENT IS NEARLY PARALLEL TO THE XY-PLANE
  float m=dz/Bx;      // COMPUTE SLOPE
  m=(m<0)?-m:m;
  if (m<1)            // NEARLY PARALLEL CASE
  {
    DrawDistMesh_Line(0,A[2],Bx,B[2],x0,x1,DistError,MaxDist, sinZtheta, cosZtheta, AlphaColor);
  }
  else                // NORMAL CASE
  {
    // ADD CLIPPING PLANES FOR DOMAIN OF LINE SEGMENT
    GLdouble P0[]={1,0,0,-x0}, P1[]={-1,0,0,x1};
    glEnable(GL_CLIP_PLANE0);
    glEnable(GL_CLIP_PLANE1);
    glClipPlane(GL_CLIP_PLANE0,P0);
    glClipPlane(GL_CLIP_PLANE1,P1);

    // APEX OF ELLIPTICAL CONE IS THE INTERSECTION BETWEEN LINE AND XY-PLANE
    // LINE MUST BE TRANSLATED TO LINE THROUGH ORIGIN
    glTranslatef(-A[2]*(Bx/dz),0,0);
    DrawDistMesh_Line_Origin(Bx,dz,DistError,MaxDist, sinZtheta, cosZtheta, AlphaColor);

    glDisable(GL_CLIP_PLANE0);
    glDisable(GL_CLIP_PLANE1);
  }

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

//----------------------------------------------------------------------------
// Distance mesh for general line segment for slice at z=SliceZ.
//----------------------------------------------------------------------------
void vdDrawDistMesh_LineSegment_Grad(float A[3], float B[3], 
                                     float SliceZ, float m[2], float M[2],
                                     float DistError, float MaxDist,
                                     unsigned char AlphaColor,
                                     int IncludeEndpoints)
{
  // if (vdCullLineRect(A,B,m,M,SliceZ,MaxDist)) return;

  // TRANSLATE LINE SEGMENT SO SLICE IS AT Z=0
  float a[]={A[0],A[1],A[2]-SliceZ}, b[]={B[0],B[1],B[2]-SliceZ};

  // DRAW LINE SEGMENT DISTANCE MESH FOR SLICE THROUGH z=0
  DrawDistMesh_LineSegment_Grad(a,b,m[0],m[1],M[0],M[1],DistError,MaxDist, AlphaColor);

  if (IncludeEndpoints)
  {
    // DRAW ENDPOINT DISTANCE MESHES
    vdDrawDistMesh_Pt_Grad(a,0,m,M,DistError,MaxDist);
    vdDrawDistMesh_Pt_Grad(b,0,m,M,DistError,MaxDist);
  }
}
