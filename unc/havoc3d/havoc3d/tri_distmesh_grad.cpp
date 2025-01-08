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

#include <math.h>
#include <GL/glut.h>
#include "pt_distmesh_grad.hpp"
#include "line_distmesh_grad.hpp"
#include "sitecull.hpp"

#define SCALEBIAS(x) ((unsigned char)((((x)*0.5f)+0.5f)*255.0f)) // [-1, 1]==>[0, 255] 

#ifdef STATS_ON
  extern int VertCount;
  extern int TriCount;
#endif

//----------------------------------------------------------------------------
// Given an arbitrary triangle ABC in 3-space, the min/max window on the z=0
// plane, the desired distance error tolerance, and a bound on the distance,
// constructs the distance mesh corresponding to the z=0 2D planar slice of the
// 3D distance function of the triangle.
//----------------------------------------------------------------------------
void DrawDistMesh_Tri(float A[3], float B[3], float C[3], 
                      float mx, float my, float Mx, float My,
                      float DistError, float MaxDist,
                      unsigned char AlphaColor)
{
  // COMPUTE TRIANGLE NORMALIZED NORMAL
  float AB[] = { B[0]-A[0],B[1]-A[1],B[2]-A[2] };
  float AC[] = { C[0]-A[0],C[1]-A[1],C[2]-A[2] };
  float N[]  = { AB[1]*AC[2]-AB[2]*AC[1], AB[2]*AC[0]-AB[0]*AC[2], AB[0]*AC[1]-AB[1]*AC[0] };
  float l    = (float)sqrt(N[0]*N[0]+N[1]*N[1]+N[2]*N[2]);
  N[0]/=l; N[1]/=l; N[2]/=l;

  // COMPUTE DISTANCES BETWEEN VERTICES AND PROJECTED VERTICES. TRIANGLE VERTICES
  // ARE PROJECTED ONTO THE Z=0 PLANE IN THE TRIANGLE'S NORMAL DIRECTION
  float ta=-A[2]/N[2], tb=-B[2]/N[2], tc=-C[2]/N[2];

  // COMPUTE PROJECTED VERTICES AND DISTANCES
  float a[] = { A[0]+N[0]*ta, A[1]+N[1]*ta, (ta<0)?-ta:ta };
  float b[] = { B[0]+N[0]*tb, B[1]+N[1]*tb, (tb<0)?-tb:tb };
  float c[] = { C[0]+N[0]*tc, C[1]+N[1]*tc, (tc<0)?-tc:tc };

  // TRY FOR TRIVIAL REJECTION BASED ON MIN/MAX EXTENTS OF PROJECTION
  // USE XY MIN/MAX BOUNDING BOX OF PROJECTED VERTICES CULL IF
  // BOUNDING BOX DOES NOT INTERSECT THE MIN/MAX WINDOW OF THE Z=0
  // SLICE AND TRIANGLE DOES NOT INTERSECT THE SLICE PERPENDICULARLY
  // (ABS(NORMAL Z COMPONENT)<EPSILON)
  int TriangleNotIntersectingSlice = A[2]*B[2]>=0 && B[2]*C[2]>=0 && C[2]*A[2]>=0;
  if ( ((a[0]<mx && b[0]<mx && c[0]<mx) || (a[0]>Mx && b[0]>Mx && c[0]>Mx) || 
        (a[1]<my && b[1]<my && c[1]<my) || (a[1]>My && b[1]>My && c[1]>My)) &&
       (TriangleNotIntersectingSlice || N[2]<-DistError || N[2]>DistError) ) {
    return;
  }

  // Convert N to byte for color representation of gradient vector
  unsigned char gx = SCALEBIAS(N[0]);
  unsigned char gy = SCALEBIAS(N[1]);
  unsigned char gz = SCALEBIAS(N[2]);

  // TRIANGLE NOT INTERSECTING THE SLICE
  if (TriangleNotIntersectingSlice)
  {
    // CULL IF ALL DISTANCES ARE GREATER THAN MaxDist
    if (a[2]>MaxDist && b[2]>MaxDist && c[2]>MaxDist) return;

    // ENSURE THAT GRADIENT VECTOR POINTS AWAY FROM z=0 PLANE
    if (A[2] * N[2] < 0) { gx = 255 - gx; gy = 255 - gy; gz = 255 - gz; }

    glColor4ub(gx, gy, gz, AlphaColor);
    glBegin(GL_TRIANGLES);
      glVertex3fv(a);
      glVertex3fv(b);
      glVertex3fv(c);
    glEnd();
#ifdef STATS_ON
  VertCount+=3;
  TriCount++;
#endif
  }

  // TRIANGLE INTERSECTING THE SLICE
  else
  {
    // ONLY TWO EDGES CAN CROSS THE SLICE, DETERMINE WHICH VERTEX IS ISOLATED AND SORT
    // VERTICES SO THAT A IS THE ISOLATED VERTEX AND B AND C ARE ON THE OTHER SIDE.
    // EDGE AB AND AC INTERSECT THE SLICE.
    float *tA, *tB, *tC, *ta, *tb, *tc;
         if (A[2]*B[2]>=0) { tA=C; tB=A; tC=B; ta=c; tb=a; tc=b; }
    else if (B[2]*C[2]>=0) { tA=A; tB=B; tC=C; ta=a; tb=b; tc=c; }
    else if (C[2]*A[2]>=0) { tA=B; tB=C; tC=A; ta=b; tb=c; tc=a; }

    // FIND PARAMETRIC VALUE FOR EDGE INTERSECCTIONS
    float tAB=-tA[2]/(tB[2]-tA[2]), tAC=-tA[2]/(tC[2]-tA[2]);

    // CHECK IF TRIANGLE IS NEARLY PARALLEL TO Z=0 PLANE
    if (tAB<0 || tAB>1 || tAC<0 || tAC>1)
    {
      // Can't determine sign of vector; just assume it's right
      glColor4ub(gx, gy, gz, AlphaColor);
      glBegin(GL_TRIANGLES);
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
      glEnd();
#ifdef STATS_ON
  VertCount+=3;
  TriCount++;
#endif
      return;
    }

    // COMPUTE XY INTERSECTION BETWEEN EDGES AND SLICE (z=0 plane)
    float iAB[] = { tA[0]+(tB[0]-tA[0])*tAB, tA[1]+(tB[1]-tA[1])*tAB };
    float iAC[] = { tA[0]+(tC[0]-tA[0])*tAC, tA[1]+(tC[1]-tA[1])*tAC };

    // COMPUTE VECTOR BETWEEN INTERSECTION POINTS AND ITS LENGTH
    float D[]={iAC[0]-iAB[0],iAC[1]-iAB[1]};
    float l = (float)sqrt(D[0]*D[0]+D[1]*D[1]);

    // CHECK IF TRIANGLE IS NEARLY PERPENDICULAR TO THE PLANE
    // TRIANGLE COLLAPSES TO 2D LINE SITE IN SLICE, DRAW QUAD TENT
    // AVOID DEGENERATE CASE OF BARELY INTERSECTING BY CHECKING DIST BETWEEN INTERSECTION PTS
    if (N[2]>=-DistError && N[2]<=DistError)
    {
      // COMPUTE OFFSET IN DIRECTION PERPENDICULAR TO EDGE BETWEEN INTERSECTION PTS
      float Scale = MaxDist/l;
      D[0]*=Scale;
      D[1]*=Scale;
      float t=D[0];
      D[0]=D[1];
      D[1]=-t;

      if (N[0] * D[0] + N[1] * D[1] < 0) {
          gx = 255 - gx;
          gy = 255 - gy;
          gz = 255 - gz;
      }

      // CONSTRUCT QUAD MESH
      glBegin(GL_QUAD_STRIP);
        glVertex3f(iAC[0]-D[0],iAC[1]-D[1],MaxDist);
        glVertex3f(iAB[0]-D[0],iAB[1]-D[1],MaxDist);
        glVertex2fv(iAC);
        glColor4ub(gx, gy, gz, AlphaColor);
        glVertex2fv(iAB);
        glVertex3f(iAC[0]+D[0],iAC[1]+D[1],MaxDist);
        glColor4ub(255-gx, 255-gy, 255-gz, AlphaColor);
        glVertex3f(iAB[0]+D[0],iAB[1]+D[1],MaxDist);
      glEnd();

#ifdef STATS_ON
  VertCount+=6;
  TriCount+=4;
#endif
    }

    // GENERIC CASE, SPLIT TRIANGLE WITH SLICE AND DRAW BOTH SIDES
    else
    {

      // Get gradient vector pointing the right direction
      // (Only do for generic orientation)
      if (tA[2] * N[2] < 0) { gx = 255 - gx; gy = 255 - gy; gz = 255 - gz; }

      glBegin(GL_TRIANGLE_STRIP);
        glVertex3fv(ta);
        glVertex2fv(iAB);
        glColor4ub(gx, gy, gz, AlphaColor);
        glVertex2fv(iAC);
        glColor4ub(255-gx, 255-gy, 255-gz, AlphaColor);
        glVertex3fv(tb);
        glVertex3fv(tc);
      glEnd();

#if 0
      // Fix crack  (I think this is a GL bug) 
      glBegin(GL_QUADS);
        // glColor4ub(gx, gy, gz, AlphaColor);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(iAC[0] - 0.001f, iAC[1]);
        glVertex2f(iAB[0] - 0.001f, iAB[1]);
        glVertex2f(iAB[0] + 0.001f, iAB[1]);
        glVertex2f(iAC[0] + 0.001f, iAC[1]);
      glEnd();
#endif // 0

#ifdef STATS_ON
  VertCount+=5;
  TriCount+=3;
#endif
    }
  }
}

void vdDrawDistMesh_Tri_Grad(float A[3], float B[3], float C[3], 
                             float SliceZ, float m[2], float M[2],
                             float DistError, float MaxDist,
                             unsigned char AlphaColor,
                             int IncludeBoundaryFeatures)
{
  // if (vdCullTriRect(A,B,C,m,M,SliceZ,MaxDist)) return;

  // TRANSLATE SO SLICE IS AT Z=0
  float a[]={A[0],A[1],A[2]-SliceZ};
  float b[]={B[0],B[1],B[2]-SliceZ};
  float c[]={C[0],C[1],C[2]-SliceZ};

  // DRAW TRIANGLE FACE DISTANCE MESH
  glPushAttrib(GL_POLYGON_BIT);
  glShadeModel(GL_FLAT);
  DrawDistMesh_Tri(a,b,c,m[0],m[1],M[0],M[1],DistError,MaxDist,AlphaColor);
  glPopAttrib();  // GL_POLYGON_BIT

  if (IncludeBoundaryFeatures)
  {
    // DRAW EDGE DISTANCE MESHES
    vdDrawDistMesh_LineSegment_Grad(A,B,SliceZ,m,M,DistError,MaxDist,AlphaColor);
    vdDrawDistMesh_LineSegment_Grad(B,C,SliceZ,m,M,DistError,MaxDist,AlphaColor);
    vdDrawDistMesh_LineSegment_Grad(C,A,SliceZ,m,M,DistError,MaxDist,AlphaColor);

    // DRAW VERTEX DISTANCE MESHES
    vdDrawDistMesh_Pt_Grad(A,SliceZ,m,M,DistError,MaxDist,AlphaColor);
    vdDrawDistMesh_Pt_Grad(B,SliceZ,m,M,DistError,MaxDist,AlphaColor);
    vdDrawDistMesh_Pt_Grad(C,SliceZ,m,M,DistError,MaxDist,AlphaColor);

  }

}
