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
// voronoi_overlap.cpp
//============================================================================

#include <math.h>
#include <voronoi_draw_gl.hpp>
#include "voronoi_overlap.hpp"

VoronoiOverlap::VoronoiOverlap()
{
  APts=ADists=AGrads=0;
  BPts=BDists=BGrads=0;
  ANumPts=BNumPts=0;
  A.TexID=B.TexID=0;
  A.mx=A.my=A.Mx=A.My=0;
  B.mx=B.my=B.Mx=B.My=0;
}

VoronoiOverlap::~VoronoiOverlap()
{
  if (APts)   delete[] APts;
  if (ADists) delete[] ADists;
  if (AGrads) delete[] AGrads;
  if (BPts)   delete[] BPts;
  if (BDists) delete[] BDists;
  if (BGrads) delete[] BGrads;
  if (glIsTexture(A.TexID)) glDeleteTextures(1,&(A.TexID));
  if (glIsTexture(B.TexID)) glDeleteTextures(1,&(B.TexID));
}

// WhichObject: 0:A, 1:B, 2:both
void VoronoiOverlap::Draw(int WhichObject, int TexOn, int PtsOn, int GradsOn, int BoxesOn) 
{
  int j;

  // DRAW TEXTURES
  if (TexOn)
  {
    if ((WhichObject==0 || WhichObject==2) && glIsTexture(A.TexID)) 
      vdDrawTextureObj(A.mx,A.my,A.Mx,A.My,A.TexID,A.W,A.H);
    if ((WhichObject==1 || WhichObject==2) && glIsTexture(B.TexID)) 
      vdDrawTextureObj(B.mx,B.my,B.Mx,B.My,B.TexID,B.W,B.H);
  }

  // DRAW PENETRATING POINTS
  if (PtsOn)
  {
    glPointSize(3);
    glBegin(GL_POINTS);
      glColor3f(1,0.7f,0);
      if ((WhichObject==0 || WhichObject==2) && APts) for (j=0; j<ANumPts*2; j+=2) glVertex2fv(&(APts[j]));
      glColor3f(1,0,0.7f);
      if ((WhichObject==1 || WhichObject==2) && BPts) for (j=0; j<BNumPts*2; j+=2) glVertex2fv(&(BPts[j]));
    glEnd();
  }

  // DRAW GRADIENTS
  if (GradsOn)
  {
    glBegin(GL_LINES);
      glColor3f(1,0.7f,0);
      if ((WhichObject==0 || WhichObject==2) && ADists && AGrads)
        for (j=0; j<ANumPts*2; j+=6)
        {
          glVertex2fv(&(APts[j]));
          float D[]={AGrads[j],AGrads[j+1]};
          float S = ADists[j/2] / (float)sqrt(D[0]*D[0] + D[1]*D[1]);
          D[0]*=S;
          D[1]*=S;
          glVertex2f(APts[j] - D[0], APts[j+1] - D[1]);
        }
      glColor3f(1,0,0.7f);
      if ((WhichObject==1 || WhichObject==2) && BDists && BGrads)
        for (j=0; j<BNumPts*2; j+=6)
        {
          glVertex2fv(&(BPts[j]));
          float D[]={BGrads[j],BGrads[j+1]};
          float S = BDists[j/2] / (float)sqrt(D[0]*D[0] + D[1]*D[1]);
          D[0]*=S;
          D[1]*=S;
          glVertex2f(BPts[j] - D[0], BPts[j+1] - D[1]);
        }
    glEnd();
  }

  // DRAW MIN/MAX BOXES
  if (BoxesOn)
  {
    if ((WhichObject==0 || WhichObject==2) && A.mx<A.Mx && A.my<A.My) 
    {
      glColor3f(1,0.7f,0.5f);
      glBegin(GL_LINE_LOOP);
        glVertex2f(A.mx,A.my); glVertex2f(A.Mx,A.my); glVertex2f(A.Mx,A.My); glVertex2f(A.mx,A.My);
      glEnd();
    }
    if ((WhichObject==1 || WhichObject==2) && B.mx<B.Mx && B.my<B.My) 
    {
      glColor3f(1,0.5f,0.7f);
      glBegin(GL_LINE_LOOP);
        glVertex2f(B.mx,B.my); glVertex2f(B.Mx,B.my); glVertex2f(B.Mx,B.My); glVertex2f(B.mx,B.My);
      glEnd();
    }
  }
}
