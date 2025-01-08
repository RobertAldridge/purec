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
// pts.cpp
//============================================================================
#include <stdlib.h>

#define RAND() (float)(rand()/(float)RAND_MAX)             // NORMALIZED RAND FUNCTION [0,1]
#define RAND2() (float)(rand()*(2.0f/(float)RAND_MAX)-1.0) // NORMALIZED RAND FUNCTION [-1,1]

float* CreatePts(int NumPts)
{
  float *pts = new float[2*NumPts];
  for (int k=0; k<2*NumPts; k++)
    pts[k]=RAND();
  return(pts);
}

float *CreateVelocityPts(int NumPts, float SpeedScale)
{
  float *pts = new float[2*NumPts];
  for (int k=0; k<2*NumPts; k++)
    pts[k]=RAND2()*SpeedScale;
  return(pts);
}

void AnimatePts(float *Pts, float *VelPts, int NumPts)
{
  for (int k=0; k<2*NumPts; k++)
  {
    Pts[k]+=VelPts[k];
    if (Pts[k]>1 || Pts[k]<0) { VelPts[k]=-VelPts[k]; Pts[k]+=VelPts[k]; };
  }
}

void ScaleVelocityPts(float *VelPts, int NumPts, float Scale)
{
  for (int k=0; k<2*NumPts; k++)
    VelPts[k]*=Scale;
}

float *CreateZeroVelocityPts(int NumPts)
{
  float *pts = new float[2*NumPts];
  for (int k=0; k<2*NumPts; k++)
    pts[k]=0;
  return(pts);
}

