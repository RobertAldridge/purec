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
// waves1d.cpp
//============================================================================

#include <math.h>
#include <memory.h>
#include "waves1d.hpp"

Waves1D::Waves1D(int NumElements, float kdamp, int UseWrapAround)
{
  N = NumElements;
  P = new float[N];
  V = new float[N];
  F = new float[N];
  for (int i=0; i<N; i++) P[i]=V[i]=0;
  WrapAroundBoundary=UseWrapAround;
  kDamp=kdamp;
}

Waves1D::~Waves1D()
{
  delete[] P;
  delete[] V;
  delete[] F;
}

void Waves1D::MakeBump(int iCntr, int Radius, float Height)
{
  int L=iCntr-Radius,R=iCntr+Radius;
  #define PI 3.1415927f
  float x=-PI, dx=PI/Radius;
  if (WrapAroundBoundary)
  {
    if (L<0) L+=N;
    if (R>N-1) R-=N;
  }
  else
  {
    if (L<0) { L=0; x-=(L*dx); }
    if (R>N-1) R=N-1;
  }
  for (int i=L; i!=R; i=(i+1)%N, x+=dx)
    P[i]=((((float)cos(x))+1.0f)*0.5f)*Height;
  P[i]=((((float)cos(x))+1.0f)*0.5f)*Height;
}

void Waves1D::CalcForces()
{
  memset(F,0,sizeof(float)*N);
  float t;
  for (int i=0; i<N-1; i++)
  {
    t      = P[i+1]-P[i];
    F[i]   += t;
    F[i+1] -= t;
  }
  if (WrapAroundBoundary)
  {
    t      = P[0]-P[N-1];
    F[N-1] += t;
    F[0]   -= t;
  }
}

void Waves1D::TakeEulerStep(float dt)
{
   float Scale=dt*kDamp;
   for (int i=0; i<N; i++)
   {
     V[i]+=(F[i]*dt);
     P[i]+=V[i];
     P[i]-=(P[i]*Scale);  // DAMPING TOWARDS ZERO HEIGHT (REPLACES VISCOUS DRAG)
   }
}

void Waves1D::Simulate(float dt)
{
  CalcForces();
  TakeEulerStep(dt);
}
