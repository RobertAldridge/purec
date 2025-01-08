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
// sitecull.cpp : rejects a site with respect to an AABB or a 2D axis-aligned
//   rectangle on the Z=SliceZ plane if it is farther than MaxDist away.
//============================================================================

int vdCullPtAABB(const float *p, const float *m, const float *M, const float MaxDist)
{
  float dx = (p[0]<m[0]) ? m[0]-p[0] : (p[0]>M[0]) ? p[0]-M[0] : 0;
  float dy = (p[1]<m[1]) ? m[1]-p[1] : (p[1]>M[1]) ? p[1]-M[1] : 0;
  float dz = (p[2]<m[2]) ? m[2]-p[2] : (p[2]>M[2]) ? p[2]-M[2] : 0;
  return ( (dx*dx+dy*dy+dz*dz) > (MaxDist*MaxDist) );
}

int vdCullLineAABB(const float *a, const float *b, const float *m, const float *M, const float MaxDist)
{
  float L;
  L=m[0]-MaxDist;    if (a[0]<L && b[0]<L) return(1);
  L=M[0]+MaxDist;    if (a[0]>L && b[0]>L) return(1);
  L=m[1]-MaxDist;    if (a[1]<L && b[1]<L) return(1);
  L=M[1]+MaxDist;    if (a[1]>L && b[1]>L) return(1);
  L=m[2]-MaxDist;    if (a[2]<L && b[2]<L) return(1);
  L=M[2]+MaxDist;    if (a[2]>L && b[2]>L) return(1);
  return(0);
}

int vdCullTriAABB(const float *a, const float *b, const float *c, const float *m, const float *M, const float MaxDist)
{
  float L;
  L=m[0]-MaxDist;    if (a[0]<L && b[0]<L && c[0]<L) return(1);
  L=M[0]+MaxDist;    if (a[0]>L && b[0]>L && c[0]>L) return(1);
  L=m[1]-MaxDist;    if (a[1]<L && b[1]<L && c[1]<L) return(1);
  L=M[1]+MaxDist;    if (a[1]>L && b[1]>L && c[1]>L) return(1);
  L=m[2]-MaxDist;    if (a[2]<L && b[2]<L && c[2]<L) return(1);
  L=M[2]+MaxDist;    if (a[2]>L && b[2]>L && c[2]>L) return(1);
  return(0);
}

int vdCullPtRect(const float *p, const float *m, const float *M, const float SliceZ, const float MaxDist)
{
  float dx = (p[0]<m[0]) ? m[0]-p[0] : (p[0]>M[0]) ? p[0]-M[0] : 0;
  float dy = (p[1]<m[1]) ? m[1]-p[1] : (p[1]>M[1]) ? p[1]-M[1] : 0;
  float dz = SliceZ-p[2];
  return ( (dx*dx+dy*dy+dz*dz) > (MaxDist*MaxDist) );
}

int vdCullLineRect(const float *a, const float *b, const float *m, const float *M, const float SliceZ, const float MaxDist)
{
  float L;
  L=m[0]-MaxDist;    if (a[0]<L && b[0]<L) return(1);
  L=M[0]+MaxDist;    if (a[0]>L && b[0]>L) return(1);
  L=m[1]-MaxDist;    if (a[1]<L && b[1]<L) return(1);
  L=M[1]+MaxDist;    if (a[1]>L && b[1]>L) return(1);
  L=SliceZ-MaxDist;   if (a[2]<L && b[2]<L) return(1);
  L=SliceZ+MaxDist;   if (a[2]>L && b[2]>L) return(1);
  return(0);
}

int vdCullTriRect(const float *a, const float *b, const float *c, const float *m, const float *M, const float SliceZ, float MaxDist)
{
  float L;
  L=m[0]-MaxDist;    if (a[0]<L && b[0]<L && c[0]<L) return(1);
  L=M[0]+MaxDist;    if (a[0]>L && b[0]>L && c[0]>L) return(1);
  L=m[1]-MaxDist;    if (a[1]<L && b[1]<L && c[1]<L) return(1);
  L=M[1]+MaxDist;    if (a[1]>L && b[1]>L && c[1]>L) return(1);
  L=SliceZ-MaxDist;   if (a[2]<L && b[2]<L && c[2]<L) return(1);
  L=SliceZ+MaxDist;   if (a[2]>L && b[2]>L && c[2]>L) return(1);
  return(0);
}
