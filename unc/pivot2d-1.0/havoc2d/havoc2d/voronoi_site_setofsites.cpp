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
// voronoi_site_setofsites.hpp
//============================================================================

#include "voronoi_site_setofsites.hpp"

VoronoiSetOfSites::VoronoiSetOfSites()
{
}

void VoronoiSetOfSites::DrawDistMesh(const float SiteRadius, const float SiteMaxAng, const int OutsideOnly)
{
  for (int i=0; i<NumSites; i++)
    Sites[i]->DrawDistMesh(SiteRadius,SiteMaxAng,OutsideOnly);
}

void VoronoiSetOfSites::DrawSite()
{
  for (int i=0; i<NumSites; i++)
    Sites[i]->DrawSite();
}

void VoronoiSetOfSites::DrawSiteFilled()
{
  for (int i=0; i<NumSites; i++)
    Sites[i]->DrawSiteFilled();
}

void VoronoiSetOfSites::CalcMinMax(float *MinX, float *MinY, float *MaxX, float *MaxY)
{
  if (NumSites<1) return;
  float mx,my,Mx,My;
  Sites[0]->CalcMinMax(MinX,MinY,MaxX,MaxY);
  for (int i=1; i<NumSites; i++)
  {
    Sites[i]->CalcMinMax(&mx,&my,&Mx,&My);
    if (mx<*MinX) *MinX=mx;
    if (Mx>*MaxX) *MaxX=Mx;
    if (my<*MinY) *MinY=my;
    if (My>*MaxY) *MaxY=My;
  }
}
