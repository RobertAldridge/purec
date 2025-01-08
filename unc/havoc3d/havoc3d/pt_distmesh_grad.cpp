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
// pt_distmesh_grad.cpp
//============================================================================

#include <algorithm>

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "sitecull.hpp"

#define SCALEBIAS(x) ((unsigned char)((((x)*0.5f)+0.5f)*255.0f)) // [-1, 1]==>[0, 255] 

static inline void
ComputeGradient(const float dx, const float dy, const float dz, 
                float *gx, float *gy, float *gz)
{
  float invl = (float)(1.0/sqrt(dx*dx + dy*dy + dz*dz));
  *gx = dx*invl;
  *gy = dy*invl;
  *gz = dz*invl;
}

static inline void
ComputeTriangleDirectionVectors(const float Tri[9], float D,
                                float DirectionVectors[9])
{
  float MagS[3];
  for (int i = 0; i < 3; i++) {
    const float* V = &Tri[3 * i];
    MagS[i] = V[0] * V[0] + V[1] * V[1] + D * D;
  }
  float Scale = float(1.0 / sqrt(*std::max_element(MagS, MagS+3)));
  DirectionVectors[0] = -Tri[0] * Scale;
  DirectionVectors[1] = -Tri[1] * Scale;
  DirectionVectors[3] = -Tri[3] * Scale;
  DirectionVectors[4] = -Tri[4] * Scale;
  DirectionVectors[6] = -Tri[6] * Scale;
  DirectionVectors[7] = -Tri[7] * Scale;
  DirectionVectors[8] = DirectionVectors[5] = DirectionVectors[2] = D * Scale;
}

unsigned char _AlphaColor_;

#ifdef STATS_ON
  extern int VertCount;
  extern int TriCount;
#endif

// Utility routine.  Computes colors for normals at vertices and draws
// triangle.  As this function is used, each color is computed and
// sent twice.  This can be optimized.
static inline void
DrawDistMeshConeTriFar(const float Angle1, const float Angle2, const float Radius, const float D)
{

  float cAng = cos(Angle1);
  float sAng = sin(Angle1);
  glColor4ub(255-SCALEBIAS(cAng), 255-SCALEBIAS(sAng), SCALEBIAS(0.0f), _AlphaColor_);
  glVertex3f(cAng * Radius, sAng * Radius, Radius);

  cAng = cos(Angle2);
  sAng = sin(Angle2);
  glColor4ub(255-SCALEBIAS(cAng), 255-SCALEBIAS(sAng), SCALEBIAS(0.0f), _AlphaColor_);
  glVertex3f(cAng * Radius, sAng * Radius, Radius);

  float MidAng = (Angle1 + Angle2) * 0.5f;
  cAng = cos(MidAng);
  sAng = sin(MidAng);
  glColor4ub(255-SCALEBIAS(cAng), 255-SCALEBIAS(sAng), SCALEBIAS(0.0f), _AlphaColor_);
  glVertex3f(0, 0, D);

}

// Utility routine.  Computes colors for normals at vertices and draws
// triangle.  As this function is used, each color is computed and
// sent twice.  This can be optimized.
static inline void
DrawDistMeshConeTriNear(const float Angle1, const float Angle2,
                        const float Radius, const float D, const float dz)
{
  float Tri[9];
  float Vecs[9];
  Tri[0] = cos(Angle1) * Radius;
  Tri[1] = sin(Angle1) * Radius;
  Tri[2] = Radius;
  Tri[3] = cos(Angle2) * Radius;
  Tri[4] = sin(Angle2) * Radius;
  Tri[5] = Radius;
  Tri[6] = 0.0;
  Tri[7] = 0.0;
  Tri[8] = D;

  ComputeTriangleDirectionVectors(Tri, dz, Vecs);

  glColor4ub(SCALEBIAS(Vecs[0]), SCALEBIAS(Vecs[1]),
             SCALEBIAS(Vecs[2]), _AlphaColor_);
  glVertex3f(Tri[0], Tri[1], Tri[2]);
  glColor4ub(SCALEBIAS(Vecs[3]), SCALEBIAS(Vecs[4]),
             SCALEBIAS(Vecs[5]), _AlphaColor_);
  glVertex3f(Tri[3], Tri[4], Tri[5]);
  glColor4ub(SCALEBIAS(Vecs[6]), SCALEBIAS(Vecs[7]),
             SCALEBIAS(Vecs[8]), _AlphaColor_);
  glVertex3f(Tri[6], Tri[7], Tri[8]);

}

//----------------------------------------------------------------------------
// For points with distance D to slice < DistError, we use the 2D point cone
// mesh approximation with error = DistError - D/2 and with apex at depth
// D/2 and base at depth MaxDist.
//----------------------------------------------------------------------------
static void DrawDistMeshCone(float dz, float disterror, float MaxDist)
{
  float D = dz<0?-dz:dz;
  float HalfD = D*0.5f;
  float DistError = disterror - HalfD;
  float SiteRadius = MaxDist + HalfD;
  float SiteMaxAng = 0.5f * acos( (SiteRadius-DistError) / SiteRadius );
  int NumSides = (2*3.1415927f) / SiteMaxAng;
  float AngIncr = (2*3.1415927f) / (float)NumSides;
  float DShrink = 1.0f - 1.0f / 32.0f;
  glBegin(GL_TRIANGLES);
    DrawDistMeshConeTriFar(0, AngIncr, SiteRadius, D);
    DrawDistMeshConeTriNear(0, AngIncr, 4 * DistError, D * DShrink, dz);
    for (int i=1; i<NumSides-1; i++)
    {
      DrawDistMeshConeTriFar(i * AngIncr, (i+1) * AngIncr, SiteRadius, D);
      DrawDistMeshConeTriNear(i * AngIncr, (i+1) * AngIncr, 4 * DistError,
                              D * DShrink, dz);
    }
    DrawDistMeshConeTriFar(-AngIncr, 0, SiteRadius, D);
    DrawDistMeshConeTriNear(-AngIncr, 0, 4 * DistError, D * DShrink, dz);
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
  double a, b, c, m, r, discr, D2, t;

  D2 = D*D;

  // COMPUTE SLOPE OF LINE WHOSE MAX ERROR EQUALS EPSILON
  t = y0-DistError;
  a = x0*x0 + D2;
  b = -2*x0*t;
  c = t*t - D2;
  discr = b*b - 4*a*c;
if (discr<0) {
    printf("m: discr<0: discr=%g, t=%g, a=%g, b=%g, c=%g!\n", discr, t, a, b, c);
}
  m = (-b + sqrt(discr) ) / (2*a);

  // SLOPE COMPUTED ALONG CENTER RADIAL LINE OF TRIANGLE FAN, MUST ADJUST FOR
  // SLOPE ALONG EDGES SO THAT PROPER RADIUS IS COMPUTED
  m = m*cos(TriRadAng*0.5f);
if (m>=1)
{
  printf("m>=1: m=%g, t=%g, a=%g, b=%g, c=%g\n", m, t, a, b, c);
  printf("      discr=%g, x0=%g, y0=%g, eps=%g\n", discr, x0, y0, DistError);
}
  // COMPUTE INTERSECTION OF LINE WITH SLOPE m WITH HYPERBOLA
  t = y0-m*x0;
  a = m*m - 1;
  b = 2*m*t;
  c = t*t - D2;
  discr = b*b - 4*a*c;
if (discr<0) printf("r: discr<0: discr=%g, t=%g, a=%g, b=%g, c=%g!\n", discr, t, a, b, c);
  r = (-b - sqrt(discr) ) / (2*a);
if (r<0) printf("r<0: r=%g, t=%g, a=%g, b=%g, c=%g\n     discr=%g, m=%g\n", r, t, a, b, c, discr, m);
  return(r);
}

//----------------------------------------------------------------------------
// ASSUMES WE ARE MESHING A SINGLE OCTANT OF THE POINT DISTANCE FUNCTION.
// APPROPRIATE FLIPPING OCCURS TO FILL OUT OTHER 7.
// Recursive routine to mesh point site distance function radiating out from 
// a single fan triangle starting at the apex. Given the (x, y) of the base
// vertices, the depth of the fan base, the radius of the fan, 
// the radian angle of the triangle fan, and the distance D between the point
// and the slice sampling plane, this routine expands the fan out one level 
// adding three new triangles that approximate the distance function to with 
// the given DistError. Recursion ends when the depth of the base vertices 
// exceeds the given MaxDist.
//----------------------------------------------------------------------------
static void RecursiveDrawDistMesh(float Ax, float Ay, float Bx, float By, float depth, 
                                  float radius, float Ang, float dz, float DistError, float MaxDist)
{
  float D = dz<0?-dz:dz;
  float Scale;

  // COMPUTE STARTING (x, y) VALUE ALONG RADIAL LINE
  float HalfAng = Ang*0.5;
  float CosHalfAng = cos(HalfAng);
  float x0 = radius*CosHalfAng;
  float y0 = depth;
  float NextRadius, NextDepth;

  // CHECK IF MESH APPROXIMATION IS WITHIN DistError OF THE
  // ASYMPTOTES. IF SO, AVOID NUMERICAL ERRORS BY SIMPLY USING THE
  // RIGHT-CIRCULAR CONE APPROXIMATION FROM HERE OUT (BASED ON
  // ASSUMPTION THAT DistError IS MUCH LARGER THAN MACHINE EPSILON
  // (reasonable)
  if (y0-x0 < DistError)  // DEVIATION OF START POINT FROM ASYMPTOTES
                          // IS LESS THAN DistError
  { 
    // COMPUTE RADIUS/DEPTH OF NEXT LEVEL FROM RIGHT CIRCULAR CONE
    // MESH APPROX TO THE ASYMPTOTES
    //printf(".");
    NextRadius = CalcRadiusForCone(Ang, DistError);
    NextDepth = NextRadius;
  }
  else
  {
    // OTHERWISE, COMPUTE RADIUS/DEPTH OF NEXT LEVEL
    NextRadius = CalcRadius(Ang, x0, y0, D, DistError);
    NextRadius *= CosHalfAng;
    NextDepth = sqrt(NextRadius*NextRadius + D*D);
  }

  // CORRECT NEXT DEPTH AND NEXT RADIUS SO THAT IT DOES NOT GO PAST MaxDepth
  // SET TERMINATION FLAG, IF MaxDepth HAS BEEN REACHED
  int MaxDepthReached=0;
  if (NextDepth>=MaxDist)
  {
    NextDepth=MaxDist;
    NextRadius = sqrt(NextDepth*NextDepth - D*D);
    MaxDepthReached=1;
  }

if (NextDepth<=depth) { printf("nonincreasing depth: %g %g\n", depth, NextDepth); return; }
if (NextRadius<=radius) { printf("nonincreasing radius: %g->%g!\n", radius, NextRadius); return; }

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

  // DRAW THE TRIANGLE FAN WITH THE APEX AT THE NEW MIDDLE POINT
  // PERFORM OCTANT FLIPPING FOR EFFICIENCY

  float gx, gy, gz;
  ComputeGradient(-ABx, -ABy, dz, &gx, &gy, &gz);
  unsigned char ABgx=SCALEBIAS(gx), ABgy=SCALEBIAS(gy), ABgz=SCALEBIAS(gz);
  ComputeGradient(-B2x, -B2y, dz, &gx, &gy, &gz);
  unsigned char B2gx=SCALEBIAS(gx), B2gy=SCALEBIAS(gy), B2gz=SCALEBIAS(gz);
  ComputeGradient(-Bx, -By, dz, &gx, &gy, &gz);
  unsigned char Bgx=SCALEBIAS(gx), Bgy=SCALEBIAS(gy), Bgz=SCALEBIAS(gz);
  ComputeGradient(-Ax, -Ay, dz, &gx, &gy, &gz);
  unsigned char Agx=SCALEBIAS(gx), Agy=SCALEBIAS(gy), Agz=SCALEBIAS(gz);
  ComputeGradient(-A2x, -A2y, dz, &gx, &gy, &gz);
  unsigned char A2gx=SCALEBIAS(gx), A2gy=SCALEBIAS(gy), A2gz=SCALEBIAS(gz);

  glBegin(GL_TRIANGLE_FAN);          // QUADRANT 1
    glColor4ub(ABgx, ABgy, ABgz, _AlphaColor_);
    glVertex3f(ABx, ABy, NextDepth);
    glColor4ub(B2gx, B2gy, B2gz, _AlphaColor_);
    glVertex3f(B2x, B2y, NextDepth);
    glColor4ub(Bgx, Bgy, Bgz, _AlphaColor_);
    glVertex3f(Bx, By, depth);
    glColor4ub(Agx, Agy, Agz, _AlphaColor_);
    glVertex3f(Ax, Ay, depth);
    glColor4ub(A2gx, A2gy, A2gz, _AlphaColor_);
    glVertex3f(A2x, A2y, NextDepth);
  glEnd();
  glBegin(GL_TRIANGLE_FAN);
    glColor4ub(ABgy, ABgx, ABgz, _AlphaColor_);
    glVertex3f(ABy, ABx, NextDepth);
    glColor4ub(A2gy, A2gx, A2gz, _AlphaColor_);
    glVertex3f(A2y, A2x, NextDepth);
    glColor4ub(Agy, Agx, Agz, _AlphaColor_);
    glVertex3f(Ay, Ax, depth);
    glColor4ub(Bgy, Bgx, Bgz, _AlphaColor_);
    glVertex3f(By, Bx, depth);
    glColor4ub(B2gy, B2gx, B2gz, _AlphaColor_);
    glVertex3f(B2y, B2x, NextDepth);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);          // QUADRANT 2
    glColor4ub(255-ABgx, ABgy, ABgz, _AlphaColor_);
    glVertex3f(-ABx, ABy, NextDepth);
    glColor4ub(255-A2gx, A2gy, A2gz, _AlphaColor_);
    glVertex3f(-A2x, A2y, NextDepth);
    glColor4ub(255-Agx, Agy, Agz, _AlphaColor_);
    glVertex3f(-Ax, Ay, depth);
    glColor4ub(255-Bgx, Bgy, Bgz, _AlphaColor_);
    glVertex3f(-Bx, By, depth);
    glColor4ub(255-B2gx, B2gy, B2gz, _AlphaColor_);
    glVertex3f(-B2x, B2y, NextDepth);
  glEnd();
  glBegin(GL_TRIANGLE_FAN);
    glColor4ub(255-ABgy, ABgx, ABgz, _AlphaColor_);
    glVertex3f(-ABy, ABx, NextDepth);
    glColor4ub(255-B2gy, B2gx, B2gz, _AlphaColor_);
    glVertex3f(-B2y, B2x, NextDepth);
    glColor4ub(255-Bgy, Bgx, Bgz, _AlphaColor_);
    glVertex3f(-By, Bx, depth);
    glColor4ub(255-Agy, Agx, Agz, _AlphaColor_);
    glVertex3f(-Ay, Ax, depth);
    glColor4ub(255-A2gy, A2gx, A2gz, _AlphaColor_);
    glVertex3f(-A2y, A2x, NextDepth);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);          // QUADRANT 3
    glColor4ub(255-ABgx, 255-ABgy, ABgz, _AlphaColor_);
    glVertex3f(-ABx, -ABy, NextDepth);
    glColor4ub(255-B2gx, 255-B2gy, B2gz, _AlphaColor_);
    glVertex3f(-B2x, -B2y, NextDepth);
    glColor4ub(255-Bgx, 255-Bgy, Bgz, _AlphaColor_);
    glVertex3f(-Bx, -By, depth);
    glColor4ub(255-Agx, 255-Agy, Agz, _AlphaColor_);
    glVertex3f(-Ax, -Ay, depth);
    glColor4ub(255-A2gx, 255-A2gy, A2gz, _AlphaColor_);
    glVertex3f(-A2x, -A2y, NextDepth);
  glEnd();
  glBegin(GL_TRIANGLE_FAN);
    glColor4ub(255-ABgy, 255-ABgx, ABgz, _AlphaColor_);
    glVertex3f(-ABy, -ABx, NextDepth);
    glColor4ub(255-A2gy, 255-A2gx, A2gz, _AlphaColor_);
    glVertex3f(-A2y, -A2x, NextDepth);
    glColor4ub(255-Agy, 255-Agx, Agz, _AlphaColor_);
    glVertex3f(-Ay, -Ax, depth);
    glColor4ub(255-Bgy, 255-Bgx, Bgz, _AlphaColor_);
    glVertex3f(-By, -Bx, depth);
    glColor4ub(255-B2gy, 255-B2gx, B2gz, _AlphaColor_);
    glVertex3f(-B2y, -B2x, NextDepth);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);          // QUADRANT 4
    glColor4ub(ABgx, 255-ABgy, ABgz, _AlphaColor_);
    glVertex3f(ABx, -ABy, NextDepth);
    glColor4ub(A2gx, 255-A2gy, A2gz, _AlphaColor_);
    glVertex3f(A2x, -A2y, NextDepth);
    glColor4ub(Agx, 255-Agy, Agz, _AlphaColor_);
    glVertex3f(Ax, -Ay, depth);
    glColor4ub(Bgx, 255-Bgy, Bgz, _AlphaColor_);
    glVertex3f(Bx, -By, depth);
    glColor4ub(B2gx, 255-B2gy, B2gz, _AlphaColor_);
    glVertex3f(B2x, -B2y, NextDepth);
  glEnd();
  glBegin(GL_TRIANGLE_FAN);
    glColor4ub(ABgy, 255-ABgx, ABgz, _AlphaColor_);
    glVertex3f(ABy, -ABx, NextDepth);
    glColor4ub(B2gy, 255-B2gx, B2gz, _AlphaColor_);
    glVertex3f(B2y, -B2x, NextDepth);
    glColor4ub(Bgy, 255-Bgx, Bgz, _AlphaColor_);
    glVertex3f(By, -Bx, depth);
    glColor4ub(Agy, 255-Agx, Agz, _AlphaColor_);
    glVertex3f(Ay, -Ax, depth);
    glColor4ub(A2gy, 255-A2gx, A2gz, _AlphaColor_);
    glVertex3f(A2y, -A2x, NextDepth);
  glEnd();
#ifdef STATS_ON
  VertCount+=40;
  TriCount+=24;
#endif

  // RECURSE ON TWO NEW BASE TRIANGLES (UNLESS MaxDist ALREADY EXCEEDED)
  if (MaxDepthReached) return;
  RecursiveDrawDistMesh(A2x, A2y, ABx, ABy, NextDepth, NextRadius, HalfAng, dz, DistError, MaxDist);
  RecursiveDrawDistMesh(ABx, ABy, B2x, B2y, NextDepth, NextRadius, HalfAng, dz, DistError, MaxDist);
}

// ---------------------------------------------------------------------------
// Core routine : for a point along the positive Z-axis distance |D|
// away from the XY-plane (point (0, 0, |D|)). Constructs a distance
// mesh begining with a fan of 8 triangles (octant flipping)
// originating at the point.  The sign of D is used to indicate
// direction of the site-direction vector (negated gradient).
// ---------------------------------------------------------------------------
static void DrawDistMesh_Pt(float dz, float DistError, float MaxDist)
{
  #define PI 3.14159265358979323846

  float D = dz<0?-dz:dz;

  if (D>=MaxDist) return;

  if (D<DistError)
  {
    // DRAW 2D CONE WITH DistError=DistError-D*0.5 WITH APEX AT DEPTH OF D*0.5
    DrawDistMeshCone(dz, DistError, MaxDist);
    return;
  }

  // COMPUTE FIRST SHELL
  float FanAng=(float)(PI*0.25);          // ANGLE SUBTENDED BY EACH FAN TRI
  float Radius = CalcRadius(FanAng, 0, D, D, DistError); 
  if (Radius > 8 * DistError) Radius = 8 * DistError;
  float Radius2 = Radius*Radius;          // (SQUARED) RADIUS OF FIRST SHELL
  float Depth = sqrt(Radius2 + D*D);      // DEPTH ON FIRST SHELL
  float CornerCoords = sqrt(Radius2*0.5f); // VERTICES AT FOUR CORNERS

  float gx, gy, gz;

  // DRAW FIRST SHELL
  glBegin(GL_TRIANGLE_FAN);

    ComputeGradient(0, 0, dz, &gx, &gy, &gz);
    glColor4ub(SCALEBIAS(gx), SCALEBIAS(gy), SCALEBIAS(gz), _AlphaColor_);
    glVertex3f(0, 0, D);

    ComputeGradient(-Radius, 0, dz, &gx, &gy, &gz);
    glColor4ub(SCALEBIAS(gx), SCALEBIAS(gy), SCALEBIAS(gz), _AlphaColor_);
    glVertex3f(Radius, 0, Depth);

    ComputeGradient(-CornerCoords, -CornerCoords, dz, &gx, &gy, &gz);
    glColor4ub(SCALEBIAS(gx), SCALEBIAS(gy), SCALEBIAS(gz), _AlphaColor_);
    glVertex3f(CornerCoords, CornerCoords, Depth);

    ComputeGradient(0, -Radius, dz, &gx, &gy, &gz);
    glColor4ub(SCALEBIAS(gx), SCALEBIAS(gy), SCALEBIAS(gz), _AlphaColor_);
    glVertex3f(0, Radius, Depth);

    ComputeGradient(CornerCoords, -CornerCoords, dz, &gx, &gy, &gz);
    glColor4ub(SCALEBIAS(gx), SCALEBIAS(gy), SCALEBIAS(gz), _AlphaColor_);
    glVertex3f(-CornerCoords, CornerCoords, Depth);

    ComputeGradient(Radius, 0, dz, &gx, &gy, &gz);
    glColor4ub(SCALEBIAS(gx), SCALEBIAS(gy), SCALEBIAS(gz), _AlphaColor_);
    glVertex3f(-Radius, 0, Depth);
    
    ComputeGradient(CornerCoords, CornerCoords, dz, &gx, &gy, &gz);
    glColor4ub(SCALEBIAS(gx), SCALEBIAS(gy), SCALEBIAS(gz), _AlphaColor_);
    glVertex3f(-CornerCoords, -CornerCoords, Depth);

    ComputeGradient(0, Radius, dz, &gx, &gy, &gz);
    glColor4ub(SCALEBIAS(gx), SCALEBIAS(gy), SCALEBIAS(gz), _AlphaColor_);
    glVertex3f(0, -Radius, Depth);

    ComputeGradient(-CornerCoords, CornerCoords, dz, &gx, &gy, &gz);
    glColor4ub(SCALEBIAS(gx), SCALEBIAS(gy), SCALEBIAS(gz), _AlphaColor_);
    glVertex3f(CornerCoords, -CornerCoords, Depth);

    ComputeGradient(-Radius, 0, dz, &gx, &gy, &gz);
    glColor4ub(SCALEBIAS(gx), SCALEBIAS(gy), SCALEBIAS(gz), _AlphaColor_);
    glVertex3f(Radius, 0, Depth);

  glEnd();
#ifdef STATS_ON
  VertCount+=10;
  TriCount+=8;
#endif

  // SEE IF ONLY THE FIRST SHELL IS NEEDED, OTHERWISE, DRAW SUBSEQUENT SHELLS
  if (Depth>=MaxDist) return;

  // RECURSIVELY DRAW SUBSEQUENT SHELLS (USE ONLY FIRST OCTANT FAN TRIANGLE)
  RecursiveDrawDistMesh(Radius, 0, CornerCoords, CornerCoords, Depth, Radius, FanAng, dz, DistError, MaxDist);
}

//----------------------------------------------------------------------------
// Routine for an arbitrary point (x, y, z) and a planar slice Z=SliceZ. Just
// transform into the (0, 0, D) point case.
//----------------------------------------------------------------------------
void vdDrawDistMesh_Pt_Grad(float P[3], 
                            float SliceZ, float m[2], float M[2], 
                            float DistError, float MaxDist, 
                            unsigned char AlphaColor)
{
  if (vdCullPtRect(P, m, M, SliceZ, MaxDist)) return;

  _AlphaColor_ = AlphaColor;

  float dz=P[2]-SliceZ;

  glPushAttrib(GL_POLYGON_BIT);
    glShadeModel(GL_SMOOTH);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(P[0], P[1], 0);

    DrawDistMesh_Pt(dz, DistError, MaxDist);

  glPopMatrix();
  glPopAttrib();  // GL_POLYGON_BIT
}
