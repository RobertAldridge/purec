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
// voronoi_adaptive.cpp
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "voronoi.hpp"
#include "voronoi_pixel_error.hpp"

//----------------------------------------------------------------------------
// Given the Voronoi diagram color buffer, determines which sites are still
// touching empty space (black) and which are finished growing. The IsActive
// flags are marked accordingly.
//----------------------------------------------------------------------------
static int FindSitesToGrow(VoronoiSites *VS, unsigned char* &C, const int W, const int H)
{
  if (C==NULL) C = new unsigned char[W*H*3];
  glReadPixels(0,0,W,H, GL_RGB, GL_UNSIGNED_BYTE, C);
  
  VS->SetAllIsActiveFlags(0);
  
  unsigned char *A, *B;
  int FoundOne=0;
  for (int j=0; j<(W*H*3); j+=(W*3))
    for (int i=j; i<(j+(W*3)-3); i+=3)
    {
      A=&(C[i]);
      B=&(C[i+3]);
      if (*A==0 && *(A+1)==0 && *(A+2)==0)
      {
        if (*B!=0 || *(B+1)!=0 || *(B+2)!=0)
        {
          FoundOne=1;
          VS->SetSiteIsActiveFlag(B,1);
        }
      }
      else if (*B==0 && *(B+1)==0 && *(B+2)==0)
      {
        if (*A!=0 || *(A+1)!=0 || *(A+2)!=0)
        {
          FoundOne=1;
          VS->SetSiteIsActiveFlag(A,1);
        }
      }
    }
  return(FoundOne);
}

float vdCompute_Adaptive(VoronoiSites *VS, 
                         float MinX, float MinY, float MaxX, float MaxY,
                         float MaxDist,
                         float FillGeomRatio,
                         int Width, int Height,
                         float StartRadius, float RadiusIncr)
{                                                
  unsigned char *C = NULL;
  float Radius=StartRadius;

  VS->SetAllIsActiveFlags(1);
  float DistError = vdCompute(VS,MinX,MinY,MaxX,MaxY,0,Radius,MaxDist,FillGeomRatio,Width,Height);

  while( Radius<MaxDist && FindSitesToGrow(VS,C,Width,Height) )
  {
    Radius+=RadiusIncr;
    vdCompute(VS,MinX,MinY,MaxX,MaxY,Radius-RadiusIncr,Radius+DistError,MaxDist,FillGeomRatio,Width,Height,0);
//for (int NumUpdated=0,i=0; i<VS->NumSites; i++)
//  if (VS->Sites[i]->IsActive) NumUpdated++;
//printf("%d ", NumUpdated);
  }
//printf("\n");

  delete[] C;
  VS->SetAllIsActiveFlags(1);
  return(DistError);
}

void vdCompute_Adaptive(VoronoiSites *VS, 
                        float MinX, float MinY, float MaxX, float MaxY,
                        float MaxDist,
                        float DistError, float FillGeomRatio,
                        int *Width, int *Height,
                        float StartRadius, float RadiusIncr)
{                                                
  vdCalcResolution(MinX,MinY,MaxX,MaxY,DistError,FillGeomRatio,Width,Height);
  vdCompute_Adaptive(VS,MinX,MinY,MaxX,MaxY,MaxDist,FillGeomRatio,
                              *Width,*Height,StartRadius,RadiusIncr);
}
