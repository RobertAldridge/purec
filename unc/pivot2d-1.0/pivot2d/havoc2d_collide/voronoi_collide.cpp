/*************************************************************************\
>
> Copyright 2001 The University of North Carolina at Chapel Hill.
> All Rights Reserved.
>
> Permission to use, copy, modify OR distribute this software and its
> documentation for educational, research and non-profit purposes, without
> fee, and without a written agreement is hereby granted, provided that the
> above copyright notice and the following three paragraphs appear in all
> copies.
>
> IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL BE
> LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR
> CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE
> USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY
> OF NORTH CAROLINA HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH
> DAMAGES.
>
> THE UNIVERSITY OF NORTH CAROLINA SPECIFICALLY DISCLAIM ANY
> WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
> MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE SOFTWARE
> PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND THE UNIVERSITY OF
> NORTH CAROLINA HAS NO OBLIGATIONS TO PROVIDE MAINTENANCE, SUPPORT,
> UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
>
> The authors may be contacted via:
>
> US Mail: K. Hoff, A. Zaferakis, M. Lin, D. Manocha
> Department of Computer Science
> Sitterson Hall, CB #3175
> University of N. Carolina
> Chapel Hill, NC 27599-3175
>
> Phone: (919) 962-1749
>
> EMail: 
> geom@cs.unc.edu 	<mailto:geom@cs.unc.edu>
> hoff@cs.unc.edu 	<mailto:hoff@cs.unc.edu>
> andrewz@cs.unc.edu 	<mailto:andrewz@cs.unc.edu>
> lin@cs.unc.edu 		<mailto:lin@cs.unc.edu>
> dm@cs.unc.edu 		<mailto:dm@cs.unc.edu>
>
\**************************************************************************/

//============================================================================
// voronoi_collide.cpp
//============================================================================

#include <stdio.h>
#include <memory.h>
#include <GL/glut.h>
#include <voronoi.hpp>
#include <voronoi_queries.hpp>
#include <voronoi_site_polygon.hpp>
#include <voronoi_color_ids.hpp>
#include <voronoi_pixel_error.hpp>
#include "hier_collide_poly.hpp"

int IntersectionFound;

struct MinMaxBox
{
  float mx,my,Mx,My;
};

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static inline void GrowFloatArray(float* &A, const int N, int &NumAlloced)
{
  if (N<NumAlloced) return;  // NO NEED TO GROW IF ALREADY HAVE ENOUGH ALLOCED
  NumAlloced*=2;
  float *NewA = new float[NumAlloced];
  memcpy(NewA,A,N*sizeof(float));
  delete[] A;
  A=NewA;
}

static inline void PackFloatArray(float* &A, const int N)
{
  float *NewA = new float[N];
  memcpy(NewA,A,N*sizeof(float));
  delete[] A;
  A=NewA;
}

//----------------------------------------------------------------------------
// OVERLAPPING MIN/MAX BOX WILL BE MIN = max of mins, MAX = min of maxs
// IF MIN/MAX DOES NOT FORM A VALID MIN/MAX BOX (MAX<MIN), THEN A AND B DO NOT OVERLAP
// IF 0 IS RETURNED, (mx,my,Mx,My) IS INVALID
//----------------------------------------------------------------------------
static inline int MinMaxBoxOverlap(const float Amx, const float Amy, const float AMx, const float AMy,
                                   const float Bmx, const float Bmy, const float BMx, const float BMy,
                                   float *mx, float *my, float *Mx, float *My)
{
  *mx = (Amx>Bmx)?Amx:Bmx;
  *Mx = (AMx<BMx)?AMx:BMx;
  if (*Mx<*mx) return(0);
  *my = (Amy>Bmy)?Amy:Bmy;
  *My = (AMy<BMy)?AMy:BMy;
  if (*My<*my) return(0);
  return(1);
}

//----------------------------------------------------------------------------
// Given two voronoi sites, a min/max window in which to compute the voronoi diagram,
// an upper bound on the distance, the maximum allowable error in the distance evaluation,
// a ratio between pixel fill and geometry (see voronoi.hpp), computes the Voronoi diagram
// of the two sites within the min/max window and returns the width and height of the
// final computed Voronoi diagram in pixels. The Voronoi diagram is in the framebuffer with
// lower corner (mx,my) is at pixel location (0,0).
//----------------------------------------------------------------------------
void ComputeVoronoiOverlap(VoronoiSite *vSite1, VoronoiSite *vSite2, float mx, float my, float Mx, float My,
                           float MaxDist, float DistError, float FillGeomRatio, int *Width, int *Height,
                           int UseFastClear)
{
  VoronoiSites* VS = new VoronoiSites();
  VS->Add(vSite1,vSite1->SiteID);
  VS->Add(vSite2,vSite2->SiteID);
  vdCompute(VS, mx,my,Mx,My, MaxDist, DistError,FillGeomRatio, Width,Height, UseFastClear?2:1);
  VS->SetDestroySitesFlag(0);
  delete VS;
}

//----------------------------------------------------------------------------
// Given an array of Voronoi sites, computes the pairwise Voronoi diagrams
// in the min/max box overlapping regions between all sites. Each Voronoi diagram
// results in a call to a callback function that will given the dimensions of
// the Voronoi diagram that is currently in the framebuffer, the overlapping
// min/max box in which it was computed, and the IDs of the sites that were
// in contact.
//----------------------------------------------------------------------------
void ComputeVoronoiOverlaps(VoronoiSite* *vSites, int NumSites,
                            float MaxDist, float DistError, float FillGeomRatio, int UseFastClear,
                            void (*VoronoiOverlapCallback)(float mx, float my, float Mx, float My, VoronoiSite *A, VoronoiSite *B))
{
  MinMaxBox* B = new MinMaxBox[NumSites];
  for (int k=0; k<NumSites; k++) vSites[k]->CalcMinMax(&(B[k].mx),&(B[k].my),&(B[k].Mx),&(B[k].My));

  float mx, my, Mx, My;
  for (int i=0; i<NumSites-1; i++)
    for (int j=i+1; j<NumSites; j++)
      if (MinMaxBoxOverlap(B[i].mx,B[i].my,B[i].Mx,B[i].My,B[j].mx,B[j].my,B[j].Mx,B[j].My,&mx,&my,&Mx,&My))
        (*VoronoiOverlapCallback)(mx,my,Mx,My,vSites[i],vSites[j]);
  delete[] B;
}

//----------------------------------------------------------------------------
// Given a min/max box and the Voronoi diagram distance buffer computed within it (current in depth buffer),
// compute intersection points on the Voronoi boundaries that are within epsilon of the object boundaries.
// For every 2x2 pixels, the center is a boundary point if there are at least 2 outgoing edges and the average
// depth values of the 4 pixels is <= epsilon. The contact points are returned in an array.
//----------------------------------------------------------------------------
void ComputeBoundaryContactPts(float mx, float my, float Mx, float My, int ResX, int ResY, float MaxDist, float Epsilon,
                               float* &Pts, int &NumPts)
{
  unsigned char *Colors = NULL;
  float *Dists = NULL;
  vdReadbackIDs(Colors,ResX,ResY);
  vdReadbackDists(Dists,ResX,ResY,1); // JUST READ BACK NORMALIZED DEPTH VALUES, SCALE EPSILON ACCORDINGLY

  Pts = new float[2];
  int iNumPts=0;
  int NumAlloced=2;

  float dx=(Mx-mx)/ResX,dy=(My-my)/ResY;
  unsigned char *C=Colors, *D;
  float *Z=Dists;
  int EdgeSum;
  float sEps4 = (Epsilon*4.0f)/MaxDist;  // DEPTH VALUES SHOULD BE IN [0,MaxDist], SCALE EPSILON INSTEAD AND USE [0,1]
  for (int y=1; y<ResY; y++, C+=3, Z++)
  {
    D = C+(ResX*3);
    for (int x=1; x<ResX; x++, C+=3, D+=3, Z++)
    {
      EdgeSum = (C[0]==C[3] && C[1]==C[4] && C[2]==C[5]) +  // BOTTOM
                (D[0]==D[3] && D[1]==D[4] && D[2]==D[5]) +  // TOP
                (C[0]==D[0] && C[1]==D[1] && C[2]==D[2]) +  // LEFT
                (C[3]==D[3] && C[4]==D[4] && C[5]==D[5]);   // RIGHT
      if (EdgeSum<=2)
        if (Z[0]+Z[1]+Z[ResX]+Z[ResX+1] <= sEps4)
        {
          GrowFloatArray(Pts,iNumPts,NumAlloced);
          Pts[iNumPts]   = mx+dx*x;
          Pts[iNumPts+1] = my+dy*y;
          iNumPts+=2;
        }
    }
  }

  PackFloatArray(Pts,iNumPts);
  NumPts = iNumPts/2;
  if (NumPts==0) { delete[] Pts; Pts=NULL; }
  delete[] Colors;
  delete[] Dists;
}

//----------------------------------------------------------------------------
// Given two Voronoi sites A and B, find points on A (within DistError accuracy)
// that are "inside" (defined by CCW winding order) polygon B. User can specify
// whether we want point in entire volume of A inside B or just points on the
// boundary of A inside B.
//----------------------------------------------------------------------------
void ComputePenetratingPts(VoronoiSite *A, VoronoiSite *B,
                           float MaxDist, float DistError, float FillGeomRatio,
                           float* &Pts, int &NumPts, int BoundaryOnly, int UseFastClear)
{
  // COMPUTE MIN/MAX BOXES FOR A AND B AND COMPUTE OVERLAPPING BOX
  float Amx,Amy,AMx,AMy,Bmx,Bmy,BMx,BMy,mx,my,Mx,My;
  A->CalcMinMax(&Amx,&Amy,&AMx,&AMy);
  B->CalcMinMax(&Bmx,&Bmy,&BMx,&BMy);
  if (!MinMaxBoxOverlap(Amx,Amy,AMx,AMy,Bmx,Bmy,BMx,BMy,&mx,&my,&Mx,&My))
    { NumPts=0; return; }

  // CALCULATE RESOLUTION NEEDED TO OBTAIN DISTANCE ERROR BOUNDS
  int W,H;
  vdCalcResolution(mx,my,Mx,My,DistError,FillGeomRatio,&W,&H);

  // ENLARGE MIN/MAX BOX TO ALLOW FOR POINTS DIRECTLY ON BOUNDARY OF MIN/MAX BOX
  vdEnlargeMinMaxBox(&mx,&my,&Mx,&My,&W,&H,DistError,FillGeomRatio,1);

  // DRAW BOUNDARY OF OBJECT A INTO VORONOI DIAGRAM OF B (ONLY IN NEGATIVE-SIGNED STENCILED REGION (==1))
  // PART OF OBJECT A THAT INTERSECT OBJECT B HAVE STENCIL VALUES OF 2
  if (UseFastClear) vdFastClear(0,0,W,H,1);
  else glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glPushAttrib(GL_VIEWPORT_BIT);
    glViewport(0,0,W,H);
  glMatrixMode(GL_PROJECTION); 
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(mx,Mx,my,My);
  glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
  glPushAttrib(GL_COLOR_BUFFER_BIT);   // DISABLE WRITING TO THE COLOR BUFFER
    glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
  glPushAttrib(GL_DEPTH_BUFFER_BIT);   // DISABLE WRITING TO THE DEPTH BUFFER
    glDisable(GL_DEPTH_TEST);
  glPushAttrib(GL_STENCIL_BUFFER_BIT); // SET ALL COVERED PIXELS' STENCIL VALS TO 1 (ASSUMED TO ALREADY BE CLEARED)
    glEnable(GL_STENCIL_TEST);

    glStencilFunc(GL_ALWAYS,1,1);
    glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
    B->DrawSiteFilled();

    glStencilFunc(GL_EQUAL,1,1);
    glStencilOp(GL_KEEP,GL_INCR,GL_INCR);
    if (BoundaryOnly) A->DrawSite(); else A->DrawSiteFilled();

  glPopAttrib(); // GL_STENCIL_BUFFER_BIT
  glPopAttrib(); // GL_DEPTH_BUFFER_BIT
  glPopAttrib(); // GL_COLOR_BUFFER_BIT
  glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
  glMatrixMode(GL_PROJECTION); 
    glPopMatrix();
  glPopAttrib(); // GL_VIEWPORT_BIT

  // READ BACK DEPTH AND STENCIL BUFFER OF VORONOI DIAGRAM OF B
  unsigned char *Stencils = new unsigned char[W*H];
  glReadPixels(0,0,W,H,GL_STENCIL_INDEX,GL_UNSIGNED_BYTE,Stencils);

  // FIND ALL POINTs OF A THAT ARE IN THE NEGATIVE-DISTANCE REGION OF B (PIXELS IN STENCIL BUFFER WITH
  // THE VALUE 2. THESE POINTS ARE PENETRATING. QUERY INTO DEPTH BUFFER IN THE VORONOI DIAGRAM OF B
  // TO FIND THE PENETRATION DEPTH
  Pts = new float[2];
  NumPts=0;
  int NumPtsAlloced=2, px,py;
  float x,y, Sx=(Mx-mx)/W, Sy=(My-my)/H;
  for(int i=0; i<(W*H); i++)
    if (Stencils[i]>1)
    {
      px = (i%W);
      py = (i/W);
      x = (float)px + 0.5f;
      y = (float)py + 0.5f;
      GrowFloatArray(Pts,NumPts,NumPtsAlloced);
      Pts[NumPts]   = mx+x*Sx;
      Pts[NumPts+1] = my+y*Sy;
      NumPts+=2;
    }
  NumPts/=2;

  delete[] Stencils;
  if (NumPts==0) { delete[] Pts; Pts=NULL; } else { PackFloatArray(Pts,NumPts*2); }
}

void ComputePenetratingPts(float *A, int NumPtsA, float *B, int NumPtsB,
                           float MaxDist, float DistError, float FillGeomRatio,
                           float* &Pts, int &NumPts, int BoundaryOnly, int UseFastClear)
{
  VoronoiSite *PolyA = new VoronoiPolygonSite(A,NumPtsA);
  VoronoiSite *PolyB = new VoronoiPolygonSite(B,NumPtsB);
  ComputePenetratingPts(PolyA,PolyB,MaxDist,DistError,FillGeomRatio,Pts,NumPts,BoundaryOnly,UseFastClear);
  delete PolyA;
  delete PolyB;
}

//----------------------------------------------------------------------------
// Returns min/max box and resolution of Voronoi diagram needed to compute gradient.
//----------------------------------------------------------------------------
void ComputePenetratingPtsWithGradients(VoronoiSite *A, VoronoiSite *B,
                                        float MaxDist, float DistError, float FillGeomRatio,
                                        float* &Pts, float *&Dists, float* &Grads, int &NumPts, int BoundaryOnly, int UseFastClear,
                                        float &mx, float &my, float &Mx, float &My, int &W, int &H)
{
  int i,j;

  // COMPUTE POINTS OF A PENETRATING B
  ComputePenetratingPts(A,B,MaxDist,DistError,FillGeomRatio,Pts,NumPts,BoundaryOnly,UseFastClear);
  if (NumPts==0) { delete[] Dists; Dists=NULL; delete[] Grads;  Grads=NULL; return; }

  // CALCULATE MIN/MAX BOX OF PENETRATING POINTS
  mx=Mx=Pts[0];
  my=My=Pts[1];
  for (i=2; i<NumPts*2; i+=2)
  {
    if (Pts[i]<mx) mx=Pts[i]; else if (Pts[i]>Mx) Mx=Pts[i];
    if (Pts[i+1]<my) my=Pts[i+1]; else if (Pts[i+1]>My) My=Pts[i+1];
  }

  // ENLARGE MIN/MAX BOX TO ALLOW FOR GRADIENTS OF BOUNDARY POINTS
  vdCalcResolution(mx,my,Mx,My,DistError,FillGeomRatio,&W,&H);
  vdEnlargeMinMaxBox(&mx,&my,&Mx,&My,&W,&H,DistError,FillGeomRatio,2);  // ENLARGE BY 2 PIXELS FOR GRADIENT COMPUTATION

  // COMPUTE DISTANCE-BUFFER OF VORONOI DIAGRAM FOR SITE B
  glPushAttrib(GL_COLOR_BUFFER_BIT);   // DISABLE WRITING TO THE COLOR BUFFER
  glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
    VoronoiSites* VS = new VoronoiSites();
    VS->Add(B,B->SiteID);
    vdCompute(VS, mx,my,Mx,My, MaxDist, DistError,FillGeomRatio, &W,&H, 2,0,0);
  //vdCompute(VS, mx,my,Mx,My, MaxDist, DistError,FillGeomRatio, &W,&H, 2,0,2);
    VS->SetDestroySitesFlag(0);
    delete VS;
  glPopAttrib();

  // READ BACK DEPTH BUFFER OF VORONOI DIAGRAM OF B
  unsigned int *Depths = NULL;
  float DepthScale = vdReadbackDists(Depths,W,H,MaxDist);
//float *Depths = NULL;
//vdReadbackSignedDists_STENCIL(Depths,W,H,MaxDist);

  // COMPUTE PENETRATION DEPTHS AND GRADIENTS OF ALL PENETRATING POINTS
  Dists = new float[NumPts];
  Grads = new float[NumPts*2];

  int px, py;
  float gx, gy, sx=(float)W/(Mx-mx), sy=(float)H/(My-my);
  for (i=0, j=0; i<NumPts; i++, j+=2)
  {
    px = (int)((Pts[j]-mx)*sx);
    py = (int)((Pts[j+1]-my)*sy);
    if (vdComputeGradient(Depths,DepthScale,W,H,px,py,&gx,&gy))
//if (vdComputeGradient(Depths,W,H,Pts[j],Pts[j+1],mx,my,Mx,My,&gx,&gy))
    {
      Dists[i]   = DepthScale*Depths[py*W+px];
//Dists[i] = Depths[py*W+px];
      Grads[j]   = gx;
      Grads[j+1] = gy;
    }
else
{
  printf("Yikes! Gradient failed!\n");
  Dists[i]   = 0;
  Grads[j]   = 0;
  Grads[j+1] = 0;
}
  }

  delete[] Depths;
}

void IntersectCallback(float *a, float *b)
{
  IntersectionFound=1;
}

void ComputePenetratingPtsWithGradients(float *A, int NumPtsA, float *B, int NumPtsB,
                                        float MaxDist, float DistError, float FillGeomRatio,
                                        float* &Pts, float *&Dists, float* &Grads, int &NumPts, int BoundaryOnly, int UseFastClear,
                                        float &mx, float &my, float &Mx, float &My, int &W, int &H)
{
  IntersectionFound=0;
  Collide_Hierarchical(A,NumPtsA,B,NumPtsB,IntersectCallback);
  if (!IntersectionFound) { NumPts=0; return; }

  VoronoiSite *PolyA = new VoronoiPolygonSite(A,NumPtsA);
  VoronoiSite *PolyB = new VoronoiPolygonSite(B,NumPtsB);
  ComputePenetratingPtsWithGradients(PolyA,PolyB,MaxDist,DistError,FillGeomRatio,Pts,Dists,Grads,NumPts,BoundaryOnly,UseFastClear,
                                     mx,my,Mx,My,W,H);
  delete PolyA;
  delete PolyB;
}
