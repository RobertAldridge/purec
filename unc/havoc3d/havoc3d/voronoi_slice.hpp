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

#ifndef _VORONOI_SLICE_H_
#define _VORONOI_SLICE_H_
//============================================================================
// voronoi_slice.hpp : simply draw distance meshes between begin/end pairs.
//
// Computing Voronoi diagram for a slice through Z=SliceZ plane (user
//   specifies a color for each site (could use routines in color_ids.cpp):
//
//    vdComputeSlice_Begin(m,M,ResX,ResY,MaxDist);
//      glColor3f(1,0,0);
//      vdDrawDistMesh_Pt(P,SliceZ,m,M,MeshDistError,MaxDist);
//      glColor3f(0,1,0);
//      vdDrawDistMesh_LineSegment(La,Lb,SliceZ,m,M,MeshDistError,MaxDist,1);
//      glColor3f(0,0,1);
//      vdDrawDistMesh_Tri(Ta,Tb,Tc,SliceZ,m,M,MeshDistError,MaxDist,1);
//    vdComputeSlice_End();
//
// To drawing the distance meshes, simply use the alternative begin/end pairs.
//
// The entire volume 3D voronoi diagram can be computed as follows:
//
//    for (int iZ=0; iZ<ResZ; iZ++)
//    {
//      float SliceZ = m[2] + (((float)iZ+0.5f)/ResZ)*(M[2]-m[2]);
//      vdComputeSlice_Begin(m,M,ResX,ResY,MaxDist);
//      myDrawDistanceMeshes(m,M,ResX,ResY,MaxDist,MeshDistError,SliceZ);
//      vdComputeSlice_End();
//    }
//
//============================================================================

void vdComputeSlice_Begin(const float m[2], const float M[2],
                          int Width, int Height,
                          float MaxDist,
                          int ClearBuffersOn=1);
void vdComputeSlice_End();

void vdDrawDistMeshes_Begin(float SliceZ);
void vdDrawDistMeshes_End();

#endif
