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

#ifndef _VORONOI_COLLIDE_
#define _VORONOI_COLLIDE_

#include <voronoi_site.hpp>

void ComputeVoronoiOverlap(VoronoiSite *vSite1, VoronoiSite *vSite2, float mx, float my, float Mx, float My,
                           float MaxDist, float DistError, float FillGeomRatio, int *Width, int *Height,
                           int UseFastClear);

void ComputeVoronoiOverlaps(VoronoiSite* *vSites, int NumSites,
                            float MaxDist, float DistError, float FillGeomRatio, int UseFastClear,
                            void (*VoronoiOverlapCallback)(float mx, float my, float Mx, float My, VoronoiSite *A, VoronoiSite *B));

void ComputeBoundaryContactPts(float mx, float my, float Mx, float My, int ResX, int ResY, float MaxDist, float Epsilon,
                               float* &Pts, int &NumPts);

void ComputePenetratingPts(VoronoiSite *A, VoronoiSite *B,
                           float MaxDist, float DistError, float FillGeomRatio,
                           float* &Pts, int &NumPts, int BoundaryOnly, int UseFastClear);

void ComputePenetratingPts(float *A, int NumPtsA, float *B, int NumPtsB,
                           float MaxDist, float DistError, float FillGeomRatio,
                           float* &Pts, int &NumPts, int BoundaryOnly, int UseFastClear);

void ComputePenetratingPtsWithGradients(VoronoiSite *A, VoronoiSite *B,
                                        float MaxDist, float DistError, float FillGeomRatio,
                                        float* &Pts, float *&Dists, float* &Grads, int &NumPts, int BoundaryOnly, int UseFastClear,
                                        float &mx, float &my, float &Mx, float &My, int &W, int &H);

void ComputePenetratingPtsWithGradients(float *A, int NumPtsA, float *B, int NumPtsB,
                                        float MaxDist, float DistError, float FillGeomRatio,
                                        float* &Pts, float *&Dists, float* &Grads, int &NumPts, int BoundaryOnly, int UseFastClear,
                                        float &mx, float &my, float &Mx, float &My, int &W, int &H);

#endif
