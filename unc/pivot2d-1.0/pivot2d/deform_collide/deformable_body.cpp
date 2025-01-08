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
// deformable_body.cpp
//============================================================================

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "deformable_body.hpp"
#include <float.h>

DeformableBody::DeformableBody(int numpts, float kgrav, float kdrag, float kcollide, float kfriction, float kspring, float kspringdamp)
{
  NumPts=0;
  NumPtsAlloced=numpts;
  Pts    = new float[NumPtsAlloced*2];
  Vels   = new float[NumPtsAlloced*2];
  Forces = new float[NumPtsAlloced*2];
  RestingLengths = new float[(NumPtsAlloced*(NumPtsAlloced-1))/2];  // O(N^2) RESTING LENGTHS
  kGrav=kgrav;
  kDrag=kdrag;
  kCollide=kcollide;
  kFriction=kfriction;
  kSpring=kspring;
  kSpringDamp=kspringdamp;
}

DeformableBody::~DeformableBody()
{
  delete[] Pts;
  delete[] Vels;
  delete[] Forces;
  delete[] RestingLengths;
}

void DeformableBody::AddPt(float x, float y)
{
  if (NumPts==NumPtsAlloced) printf("ERROR: Cannot add any more points!\n");
  int i=NumPts*2;
  Pts[i]=x;
  Pts[i+1]=y;
  Vels[i]=0;
  Vels[i+1]=0;
  Forces[i]=0;
  Forces[i+1]=0;
  NumPts++;
  if (NumPts==NumPtsAlloced)
    ComputeRestingLengths();
}

void DeformableBody::ComputeRestingLengths()
{
  float dx,dy;
  int k=0;
  for (int i=0; i<(NumPts-1)*2; i+=2)
    for (int j=i+2; j<NumPts*2; j+=2)
    {
      dx = Pts[i] - Pts[j];
      dy = Pts[i+1] - Pts[j+1];
      RestingLengths[k] = (float)sqrt(dx*dx+dy*dy);
      k++;
    }
}

void DeformableBody::ComputeForces()
{
  int i,j,k;
  float pdx,pdy,vdx,vdy,l,vDOTpDIVl,lDiff,Mag,fx,fy;

  for (i=0; i<NumPts*2; i++)      // CLEAR OUT FORCE ACCUMULATORS
    Forces[i]=0;

  for (i=1; i<NumPts*2; i+=2)     // GRAVITY (ACTS ON Y COMPONENT ONLY)
    Forces[i]+=-kGrav;

  for (i=0; i<NumPts*2; i+=2)     // VISCOUS DRAG (ACTS IN NEGATIVE VELOCITY DIRECTION)
  {
    Forces[i]   -= (kDrag*Vels[i]);
    Forces[i+1] -= (kDrag*Vels[i+1]);
  }

  k=0;                            // N^2 SPRING RESTORING FORCES
  for (i=0; i<(NumPts-1)*2; i+=2)
    for (j=i+2; j<NumPts*2; j+=2)
    {
      pdx = Pts[i] - Pts[j];
      pdy = Pts[i+1] - Pts[j+1];
      l = (float)sqrt(pdx*pdx+pdy*pdy);
      vdx = Vels[i] - Vels[j];
      vdy = Vels[i+1] - Vels[j+1];
      vDOTpDIVl = (vdx*pdx + vdy*pdy) / l;
      lDiff = l - RestingLengths[k];
      Mag = -(kSpring*lDiff + kSpringDamp*vDOTpDIVl) / l;
      fx = Mag*pdx;
      fy = Mag*pdy;
if (!_finite((double)fx)) { printf("ComputeForces: fx: %f\n",fx); fx=0; }
if (!_finite((double)fy)) { printf("ComputeForces: fy: %f\n",fy); fy=0; }
      Forces[i]   += fx;
      Forces[i+1] += fy;
      Forces[j]   -= fx;
      Forces[j+1] -= fy;
      k++;
    }
}

void DeformableBody::TakeEulerStep(float dt)
{
  for (int i=0; i<NumPts*2; i+=2)
  {
    Pts[i]   += Vels[i]*dt;
    Pts[i+1] += Vels[i+1]*dt;

    // COLLISION DETECTION (GROUND PLANE, SIDE WALLS) AND GROUND FRICTION
    if (Pts[i]<-1 || Pts[i]>1) { Vels[i]=-Vels[i]; Pts[i]+=Vels[i]*dt; Vels[i]*=kCollide; }
    if (Pts[i+1]<-1) { Vels[i+1]=-Vels[i+1]; Pts[i+1]+=Vels[i+1]*dt; Vels[i+1]*=kCollide; Vels[i]*=kFriction; }
    else if (Pts[i+1]>1) { Vels[i+1]=-Vels[i+1]; Pts[i+1]+=Vels[i+1]*dt; Vels[i+1]*=kCollide; }

if (!_finite((double)Forces[i])) printf("TakeEulerStep: Fx: %f\n",Forces[i]);
if (!_finite((double)Forces[i+1])) printf("TakeEulerStep: Fy: %f\n",Forces[i+1]);
if (Forces[i]*Forces[i]+Forces[i+1]*Forces[i+1]<0)
{ 
  Forces[i]=0; Forces[i+1]=0; 
  printf("yikes! Negative Discriminant!\n"); 
}

    Vels[i]   += Forces[i]*dt;
    Vels[i+1] += Forces[i+1]*dt;
  }
}

void DeformableBody::Simulate(float dt)
{
  ComputeForces();
  TakeEulerStep(dt);
}

void DeformableBody::ApplyForceAtPt(float Px, float Py, float Fx, float Fy)
{
if (!_finite((double)Fx)) { printf("ApplyForceAtPt: Fx: %f\n",Fx); Fx=0; }
if (!_finite((double)Fy)) { printf("ApplyForceAtPt: Fy: %f\n",Fy); Fy=0; }

  // FIND NEAREST LINE SEGMENT TO POINT
  float t;
  int i = FindNearestLineSegment(Px,Py,&t);

  // DISTRIBUTE FORCES LINEARLY BETWEEN LINE SEGMENT ENDPOINTS
  if (t<=0)      // APPLY FORCES TO A
  {
    Forces[i]  +=Fx;
    Forces[i+1]+=Fy;
  }
  else if (t>=1) // APPLY FORCES TO B
  {
    Forces[(i+2)%(NumPts*2)]+=Fx;
    Forces[(i+3)%(NumPts*2)]+=Fy;
  }
  else           // DISTRIBUTE BETWEEN A AND B BASED ON t
  {
    float it = 1.0f-t;
    Forces[i]  +=(Fx*it);
    Forces[i+1]+=(Fy*it);
    Forces[(i+2)%(NumPts*2)]+=(Fx*t);
    Forces[(i+3)%(NumPts*2)]+=(Fy*t);
  }
}

float DeformableBody::PtLineSegDist2(float Px, float Py, float Ax, float Ay, float Bx, float By, float *t)
{
  float D[] = { Bx-Ax, By-Ay };
  float lD = 1.0f/(float)sqrt(D[0]*D[0]+D[1]*D[1]);
  D[0]*=lD;
  D[1]*=lD;
  float AP[] = { Px-Ax, Py-Ay };
  float APdotD = AP[0]*D[0] + AP[1]*D[1];
  float APdotDperp = AP[1]*D[0] - AP[0]*D[1];
  *t = APdotD;
  return( (APdotD<0 || APdotD>1) ?
          APdotD*APdotD+APdotDperp*APdotDperp : // CLOSEST TO ENDPOINTS
          APdotDperp*APdotDperp );              // CLOSEST TO EDGE AB
}

// RETURNS INDEX OF FIRST COMPONENT OF LINE AB IN PTS ARRAY, AND FRACTION t BETWEEN ENDPOINTS
int DeformableBody::FindNearestLineSegment(float Px, float Py, float *t)
{
  if (NumPts<2) { *t=0; return(0); }
  float MinDist = PtLineSegDist2(Px,Py,Pts[0],Pts[1],Pts[2],Pts[3],t), Dist;
  int iMinDist=0;
  float tMinDist=*t;
  for (int i=2; i<(NumPts-1)*2; i+=2)
  {
    Dist = PtLineSegDist2(Px,Py,Pts[i],Pts[i+1],Pts[i+2],Pts[i+3],t);
    if (Dist<MinDist) { MinDist=Dist; iMinDist=i; tMinDist=*t; }
  }
  Dist = PtLineSegDist2(Px,Py,Pts[NumPts*2-2],Pts[NumPts*2-1],Pts[0],Pts[1],t); // LAST SEG BETWEEN 1ST AND LAST PTS
  if (Dist<MinDist) { MinDist=Dist; iMinDist=i; tMinDist=*t; }
  *t=tMinDist;
  return(iMinDist);
}

void DeformableBody::ComputeMinMaxBox(float *mx, float *my, float *Mx, float *My)
{
  if (NumPts<1) return;
  (*mx)=(*Mx)=Pts[0];
  (*my)=(*My)=Pts[1];
  for (int i=2; i<NumPts*2; i+=2)
  {
    if (Pts[i]<(*mx)) (*mx)=Pts[i]; else if (Pts[i]>(*Mx)) (*Mx)=Pts[i];
    if (Pts[i+1]<(*my)) (*my)=Pts[i+1]; else if (Pts[i+1]>(*My)) (*My)=Pts[i+1];
  }
}

void DeformableBody::Display()
{
  glBegin(GL_LINE_LOOP);
  for (int i=0; i<NumPts*2; i+=2)
    glVertex2fv(&(Pts[i]));
  glEnd();
}

void DeformableBody::DisplayForces()
{
  glBegin(GL_LINES);
  for (int i=0; i<NumPts*2; i+=2)
  {
    glVertex2fv(&(Pts[i]));
    glVertex2f(Pts[i]+Forces[i]*10,Pts[i+1]+Forces[i+1]*10);
  }
  glEnd();
}

