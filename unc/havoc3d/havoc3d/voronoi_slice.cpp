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
// voronoi_slice.cpp
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

#include <stdio.h>
#include <GL/glut.h>
#include "voronoi_slice.hpp"

//----------------------------------------------------------------------------
// Clears the depth and color of a portion of the screen using polygon
// drawing (avoids call to glClear) given starting pixel and width and height.
// Clears color to black and depth to far distance.
//----------------------------------------------------------------------------
static void FastClear(int StartX, int StartY, int Width, int Height)
{
  glPushAttrib(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
  glPushAttrib(GL_VIEWPORT_BIT);
    glViewport(StartX,StartY,Width,Height);
    glDepthRange(0,1);
  glMatrixMode(GL_PROJECTION); 
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1,1,-1,1,-1,0);
  glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
      glColor4f(0,0,0,0);
      glRectf(-1,-1,1,1);
  glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
  glMatrixMode(GL_PROJECTION); 
    glPopMatrix();
  glPopAttrib(); // GL_VIEWPORT_BIT
  glPopAttrib(); // GL_DEPTH_BUFFER_BIT
}

//----------------------------------------------------------------------------
// The main routine that computes a 2D slice of the 3D voronoi diagram.
// The user specifies a min/max bounding box window 
// in world (voronoi site) space on the Z=SliceZ plane, the min and max 
// distances from the sites that should be included in the Voronoi computation
// (MinDist is usually 0 and MaxDist should cover the entire
// bounding box (except under special situations where a bounded distance
// function is appropriate; this will give major speedups)).
// The dimensions (width/height) of the Voronoi diagram are specified and the
// Voronoi diagram image resides in the lower-left corner of the current
// draw buffer (usually GL_BACK). User can specify whether or not to auto
// clear the color and depth buffers. Some apps may not want to clear the
// buffers (incremental update, etc). // MeshDistError is the error 
// tolerance for mesh approximation of distance function (independent from 
// sampling resolution distance error).
// Total DistError = PixelDistError + MeshDistError. PixelDistError is determined
// by the specified resolution. MeshDistError is often the same as PixelDistError.
//----------------------------------------------------------------------------
void vdComputeSlice_Begin(const float m[2], const float M[2],
                          int Width, int Height,
                          float MaxDist,
                          int ClearBuffersOn)
{
  // MAKE SURE WINDOW IS LARGE ENOUGH
  int WW = (int)glutGet((GLenum)GLUT_WINDOW_WIDTH);
  int WH = (int)glutGet((GLenum)GLUT_WINDOW_HEIGHT);
  if (Width>WW || Height>WH) printf("Voronoi error: window not large enough, need %dx%d\n",Width,Height);

  // CHECK FOR REQUIRED BUFFERS
  int NumBits;
  glGetIntegerv(GL_DEPTH_BITS,&NumBits);
  if (NumBits<16) printf("ERROR: no depth buffer! Add GLUT_DEPTH!\n");
  
  glClearColor(0,0,0,0);
  if (ClearBuffersOn==1)      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  else if (ClearBuffersOn==2) FastClear(0,0,Width,Height);
    
  glPushAttrib(GL_VIEWPORT_BIT);
    glViewport(0,0,Width,Height);
  glPushAttrib(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
  glMatrixMode(GL_PROJECTION); 
    glPushMatrix();
    glLoadIdentity();
    glOrtho(m[0],M[0],m[1],M[1],0,-MaxDist);  // NEGATE NEAR/FAR SO DIST-MESH Z-VALUES CAN BE POSITIVE
  glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

void vdComputeSlice_End()
{
  glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
  glMatrixMode(GL_PROJECTION); 
    glPopMatrix();
  glPopAttrib(); // GL_DEPTH_BUFFER_BIT
  glPopAttrib(); // GL_VIEWPORT_BIT
}

//----------------------------------------------------------------------------
// Routines for drawing the distance meshes (only for display purposes)
//----------------------------------------------------------------------------
void vdDrawDistMeshes_Begin(float SliceZ)
{
  glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,0,SliceZ);
    glScalef(1,1,-1);
}

void vdDrawDistMeshes_End()
{
  glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
