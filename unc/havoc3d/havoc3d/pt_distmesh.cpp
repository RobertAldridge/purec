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
// pt_distmesh.cpp
//============================================================================

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "sitecull.hpp"

#ifdef STATS_ON
  extern int VertCount;
  extern int TriCount;
#endif

//----------------------------------------------------------------------------
// For points with distance D to slice < DistError, we use the 2D point cone
// mesh approximation with error = DistError - D/2 and with apex at depth
// D/2 and base at depth MaxDist.
//----------------------------------------------------------------------------
static void DrawDistMeshCone(float D, float disterror, float MaxDist)
{
  float HalfD = D*0.5f;
  float DistError = disterror - HalfD;
  float SiteRadius = MaxDist + HalfD;
  float SiteMaxAng = 2.0f * acos( (SiteRadius-DistError) / SiteRadius );
  int NumSides = (2*3.1415927f) / SiteMaxAng;
  float AngIncr = (2*3.1415927f) / (float)NumSides;
  float Ang = AngIncr;
  glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,HalfD);
    glVertex3f(SiteRadius,0,SiteRadius);
    for (int i=1; i<NumSides; i++, Ang+=AngIncr)
    {
      glVertex3f(cos(Ang)*SiteRadius,sin(Ang)*SiteRadius,SiteRadius);
#ifdef STATS_ON
  VertCount++;
  TriCount++;
#endif
    }
    glVertex3f(SiteRadius,0,SiteRadius);
#ifdef STATS_ON
  VertCount+=3;
  TriCount++;
#endif
  glEnd();
}

//----------------------------------------------------------------------------
// Given bound on the distance error (DistError) and the angle of the cone
// fan triangle, calculates the maximum radius of the triangle fan cone mesh
// that will not violate the error bound
//----------------------------------------------------------------------------
static float CalcRadiusForCone(float TriRadAng, float DistError)
{
  return( DistError / (1.0f-cos(TriRadAng*0.5f)) );
}

//----------------------------------------------------------------------------
// Calculates the radius of a fan triangle with angle TriRadAng such that the
// maximum error along the fan triangle center line (emanating from apex) is
// DistError. The triangle plane crosses through at a radius of x0 with a depth
// of y0. D is the distance between the point site and the slice sampling plane.
//----------------------------------------------------------------------------
static double CalcRadius(double TriRadAng, double x0, double y0, double D, double DistError)
{
  double a,b,c,m,r,discr,D2,t;

  D2 = D*D;

  // COMPUTE SLOPE OF LINE WHOSE MAX ERROR EQUALS EPSILON
  t = y0-DistError;
  a = x0*x0 + D2;
  b = -2*x0*t;
  c = t*t - D2;
  discr = b*b - 4*a*c;
if (discr<0) printf("m: discr<0: discr=%g, t=%g, a=%g, b=%g, c=%g!\n",discr,t,a,b,c);
  m = (-b + sqrt(discr) ) / (2*a);

  // SLOPE COMPUTED ALONG CENTER RADIAL LINE OF TRIANGLE FAN, MUST ADJUST FOR
  // SLOPE ALONG EDGES SO THAT PROPER RADIUS IS COMPUTED
  m = m*cos(TriRadAng*0.5f);
if (m>=1)
{
  printf("m>=1: m=%g, t=%g, a=%g, b=%g, c=%g\n",m,t,a,b,c);
  printf("      discr=%g, x0=%g, y0=%g, eps=%g\n",discr,x0,y0,DistError);
}
  // COMPUTE INTERSECTION OF LINE WITH SLOPE m WITH HYPERBOLA
  t = y0-m*x0;
  a = m*m - 1;
  b = 2*m*t;
  c = t*t - D2;
  discr = b*b - 4*a*c;
if (discr<0) printf("r: discr<0: discr=%g, t=%g, a=%g, b=%g, c=%g!\n",discr,t,a,b,c);
  r = (-b - sqrt(discr) ) / (2*a);
if (r<0) printf("r<0: r=%g, t=%g, a=%g, b=%g, c=%g\n     discr=%g, m=%g\n",r,t,a,b,c,discr,m);
  return(r);
}

//----------------------------------------------------------------------------
// ASSUMES WE ARE MESHING A SINGLE OCTANT OF THE POINT DISTANCE FUNCTION.
// APPROPRIATE FLIPPING OCCURS TO FILL OUT OTHER 7.
// Recursive routine to mesh point site distance function radiating out from 
// a single fan triangle starting at the apex. Given the (x,y) of the base
// vertices, the depth of the fan base, the radius of the fan, 
// the radian angle of the triangle fan, and the distance D between the point
// and the slice sampling plane, this routine expands the fan out one level 
// adding three new triangles that approximate the distance function to with 
// the given DistError. Recursion ends when the depth of the base vertices 
// exceeds the given MaxDist.
//----------------------------------------------------------------------------
static void RecursiveDrawDistMesh(float Ax, float Ay, float Bx, float By, float depth,
                                  float radius, float Ang, float D, float DistError, float MaxDist,
                                  const float m[2], const float M[2])
{
  float Scale;

  // COMPUTE STARTING (x,y) VALUE ALONG RADIAL LINE
  float HalfAng = Ang*0.5;
  float CosHalfAng = cos(HalfAng);
  float x0 = radius*CosHalfAng;
  float y0 = depth;
  float NextRadius, NextDepth;

  // CHECK IF MESH APPROXIMATION IS WITHIN DistError OF THE ASYMPTOTES. IF SO, AVOID NUMERICAL
  // ERRORS BY SIMPLY USING THE RIGHT-CIRCULAR CONE APPROXIMATION FROM HERE OUT (BASED ON
  // ASSUMPTION THAT DistError IS MUCH LARGER THAN MACHINE EPSILON (reasonable)
  if (y0-x0 < DistError)  // DEVIATION OF START POINT FROM ASYMPTOTES IS LESS THAN DistError
  { 
    // COMPUTE RADIUS/DEPTH OF NEXT LEVEL FROM RIGHT CIRCULAR CONE MESH APPROX TO THE ASYMPTOTES
    //printf(".");
    NextRadius = CalcRadiusForCone(Ang,DistError);
    NextDepth = NextRadius;
  }
  else
  {
    // OTHERWISE, COMPUTE RADIUS/DEPTH OF NEXT LEVEL
    NextRadius = CalcRadius(Ang,x0,y0,D,DistError);
    NextRadius *= CosHalfAng;
    NextDepth = sqrt(NextRadius*NextRadius + D*D);
  }

  // CORRECT NEXT DEPTH AND NEXT RADIUS SO THAT IT DOES NOT GO PASSED MaxDepth
  // SET TERMINATION FLAG, IF MaxDepth HAS BEEN REACHED
  int MaxDepthReached=0;
  if (NextDepth>=MaxDist)
  {
    NextDepth=MaxDist;
    NextRadius = sqrt(NextDepth*NextDepth - D*D);
    MaxDepthReached=1;
  }

if (NextDepth<=depth) { printf("nonincreasing depth: %g %g\n",depth,NextDepth); return; }
if (NextRadius<=radius) { printf("nonincreasing radius: %g->%g!\n",radius,NextRadius); return; }

  // COMPUTE POINTS ALONG LINES THROUGH BASE POINTS A AND B
  Scale = NextRadius/radius;
  float A2x = Ax * Scale;
  float A2y = Ay * Scale;
  float B2x = Bx * Scale;
  float B2y = By * Scale;

  // COMPUTE NEW "MIDDLE" FAN POINT
  float ABx = (Ax+Bx)*0.5;
  float ABy = (Ay+By)*0.5;
  Scale = NextRadius / (radius*cos(HalfAng)); // DENOM IS DISTANCE OUT TO MIDPOINT
  ABx *= Scale;
  ABy *= Scale;

  // COMPUTE BOUNDING BOX OF FAN. USE TO CULL AGAINST WINDOW FOR EACH OCTANT
  float tm[2]={Ax,Ay}, tM[2]={Ax,Ay};
  if (Bx<tm[0])  tm[0]=Bx;  else if (Bx>tM[0])  tM[0]=Bx;
  if (ABx<tm[0]) tm[0]=ABx; else if (ABx>tM[0]) tM[0]=ABx;
  if (A2x<tm[0]) tm[0]=A2x; else if (A2x>tM[0]) tM[0]=A2x;
  if (B2x<tm[0]) tm[0]=B2x; else if (B2x>tM[0]) tM[0]=B2x;
  if (By<tm[1])  tm[1]=By;  else if (By>tM[1])  tM[1]=By;
  if (ABy<tm[1]) tm[1]=ABy; else if (ABy>tM[1]) tM[1]=ABy;
  if (A2y<tm[1]) tm[1]=A2y; else if (A2y>tM[1]) tM[1]=A2y;
  if (B2y<tm[1]) tm[1]=B2y; else if (B2y>tM[1]) tM[1]=B2y;


  // DRAW THE TRIANGLE FAN WITH THE APEX AT THE NEW MIDDLE POINT
  // PERFORM OCTANT FLIPPING FOR EFFICIENCY

  // QUADRANT 1
  if (!(tm[0]>M[0] || tm[1]>M[1] || tM[0]<m[0] || tM[1]<m[1]))
  {
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(ABx,ABy,NextDepth);
      glVertex3f(B2x,B2y,NextDepth);
      glVertex3f(Bx,By,depth);
      glVertex3f(Ax,Ay,depth);
      glVertex3f(A2x,A2y,NextDepth);
    glEnd();
  }
  if (!(tm[1]>M[0] || tm[0]>M[1] || tM[1]<m[0] || tM[0]<m[1]))
  {
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(ABy,ABx,NextDepth);
      glVertex3f(A2y,A2x,NextDepth);
      glVertex3f(Ay,Ax,depth);
      glVertex3f(By,Bx,depth);
      glVertex3f(B2y,B2x,NextDepth);
    glEnd();
  }

  // QUADRANT 2
  if (!(-tM[0]>M[0] || tm[1]>M[1] || -tm[0]<m[0] || tM[1]<m[1]))
  {
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(-ABx,ABy,NextDepth);
      glVertex3f(-A2x,A2y,NextDepth);
      glVertex3f(-Ax,Ay,depth);
      glVertex3f(-Bx,By,depth);
      glVertex3f(-B2x,B2y,NextDepth);
    glEnd();
  }
  if (!(-tM[1]>M[0] || tm[0]>M[1] || -tm[1]<m[0] || tM[0]<m[1]))
  {
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(-ABy,ABx,NextDepth);
      glVertex3f(-B2y,B2x,NextDepth);
      glVertex3f(-By,Bx,depth);
      glVertex3f(-Ay,Ax,depth);
      glVertex3f(-A2y,A2x,NextDepth);
    glEnd();
  }

  // QUADRANT 3
  if (!(-tM[0]>M[0] || -tM[1]>M[1] || -tm[0]<m[0] || -tm[1]<m[1]))
  {
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(-ABx,-ABy,NextDepth);
      glVertex3f(-B2x,-B2y,NextDepth);
      glVertex3f(-Bx,-By,depth);
      glVertex3f(-Ax,-Ay,depth);
      glVertex3f(-A2x,-A2y,NextDepth);
    glEnd();
  }
  if (!(-tM[1]>M[0] || -tM[0]>M[1] || -tm[1]<m[0] || -tm[0]<m[1]))
  {
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(-ABy,-ABx,NextDepth);
      glVertex3f(-A2y,-A2x,NextDepth);
      glVertex3f(-Ay,-Ax,depth);
      glVertex3f(-By,-Bx,depth);
      glVertex3f(-B2y,-B2x,NextDepth);
    glEnd();
  }

  // QUADRANT 4
  if (!(tm[0]>M[0] || -tM[1]>M[1] || tM[0]<m[0] || -tm[1]<m[1]))
  {
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(ABx,-ABy,NextDepth);
      glVertex3f(A2x,-A2y,NextDepth);
      glVertex3f(Ax,-Ay,depth);
      glVertex3f(Bx,-By,depth);
      glVertex3f(B2x,-B2y,NextDepth);
    glEnd();
  }
  if (!(tm[1]>M[0] || -tM[0]>M[1] || tM[1]<m[0] || -tm[0]<m[1]))
  {
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(ABy,-ABx,NextDepth);
      glVertex3f(B2y,-B2x,NextDepth);
      glVertex3f(By,-Bx,depth);
      glVertex3f(Ay,-Ax,depth);
      glVertex3f(A2y,-A2x,NextDepth);
    glEnd();
  }

#ifdef STATS_ON
  VertCount+=40;
  TriCount+=24;
#endif

  // RECURSE ON TWO NEW BASE TRIANGLES (UNLESS MaxDist ALREADY EXCEEDED)
  if (MaxDepthReached) return;
  RecursiveDrawDistMesh(A2x,A2y,ABx,ABy,NextDepth,NextRadius,HalfAng,D,DistError,MaxDist,m,M);
  RecursiveDrawDistMesh(ABx,ABy,B2x,B2y,NextDepth,NextRadius,HalfAng,D,DistError,MaxDist,m,M);
}

//----------------------------------------------------------------------------
// Core routine : for a point along the positive Z-axis distance D away from 
//   the XY-plane (point (0,0,D)). Constructs a distance mesh begining with a 
//   fan of 8 triangles (octant flipping) originating at the point.
//----------------------------------------------------------------------------
static void DrawDistMesh_Pt(float D, float DistError, float MaxDist, float m[2], float M[2])
{
  #define PI 3.14159265358979323846

  if (D>=MaxDist) return;

  if (D<DistError)
  {
    // DRAW 2D CONE WITH DistError=DistError-D*0.5 WITH APEX AT DEPTH OF D*0.5
    DrawDistMeshCone(D,DistError,MaxDist);
    return;
  }

  // COMPUTE FIRST SHELL
  float FanAng=(float)(PI*0.25);                    // ANGLE SUBTENDED BY EACH FAN TRI
  float Radius = CalcRadius(FanAng,0,D,D,DistError);  // RADIUS OF FIRST SHELL
  float Radius2 = Radius*Radius;
  float Depth = sqrt(Radius2 + D*D);                // DEPTH ON FIRST SHELL
  float CornerCoords = sqrt(Radius2*0.5f);          // VERTICES AT FOUR CORNERS

  // DRAW FIRST SHELL. DRAW SHELL ONLY IF TOUCHES WINDOW (USE AABB OF FAN)
  if (!(Radius<m[0] || Radius<m[1] || -Radius>M[0] || -Radius>M[1]))
  {
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(0,0,D);
      glVertex3f(Radius,0,Depth);
      glVertex3f(CornerCoords,CornerCoords,Depth);
      glVertex3f(0,Radius,Depth);
      glVertex3f(-CornerCoords,CornerCoords,Depth);
      glVertex3f(-Radius,0,Depth);
      glVertex3f(-CornerCoords,-CornerCoords,Depth);
      glVertex3f(0,-Radius,Depth);
      glVertex3f(CornerCoords,-CornerCoords,Depth);
      glVertex3f(Radius,0,Depth);
    glEnd();
  }

#ifdef STATS_ON
  VertCount+=10;
  TriCount+=8;
#endif

  // SEE IF ONLY THE FIRST SHELL IS NEEDED, OTHERWISE, DRAW SUBSEQUENT SHELLS
  if (Depth>=MaxDist) return;

  // RECURSIVELY DRAW SUBSEQUENT SHELLS (USE ONLY FIRST OCTANT FAN TRIANGLE)
  RecursiveDrawDistMesh(Radius,0,CornerCoords,CornerCoords,Depth,Radius,FanAng,D,DistError,MaxDist,m,M);
}

//----------------------------------------------------------------------------
// Routine for an arbitrary point (x,y,z) and a planar slice Z=SliceZ. Just
// transform into the (0,0,D) point case.
//----------------------------------------------------------------------------
void vdDrawDistMesh_Pt(const float P[3], 
                       float SliceZ, const float m[2], const float M[2],
                       float DistError, float MaxDist)
{
  if (vdCullPtRect(P,m,M,SliceZ,MaxDist)) return;

  float tm[]={m[0]-P[0],m[1]-P[1]}, tM[]={M[0]-P[0],M[1]-P[1]};  // CREATE WINDOW WITH RESPECT TO POINT AT ORIGIN

  float dz=P[2]-SliceZ;
  float D = (dz<0)?-dz:dz;

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(P[0],P[1],0);

    DrawDistMesh_Pt(D,DistError,MaxDist,tm,tM);

  glPopMatrix();
}
