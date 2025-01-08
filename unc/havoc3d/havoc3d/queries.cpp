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
// voronoi_queries.cpp
//============================================================================

#include <stdio.h>
#include <GL/glut.h>

//----------------------------------------------------------------------------
// Read back the ID buffer (color buffer) as a 1D array of unsigned char or
// as translated integer IDs (original values). If IDs array is set to NULL,
// memory is allocated automatically. 
// It is assumed that the Voronoi diagram has been correctly computed into
// the current readbuffer (usually GL_BACK). The user must specify the width
// and height (in pixels) of the Voronoi diagram computed.
// Integer IDs version is much slower since each pixel color value has to be 
// translated back into the user ID; however, it may be useful when many
// query accesses to the buffer are required and the overhead of repeated
// color/ID conversions will overwhelm the constant overhead of this routine.
// NOTE: be sure to set glReadBuffer to the buffer containing the Voronoi
// diagram (usually GL_BACK).
//----------------------------------------------------------------------------
void vdReadbackIDs(unsigned char* &IDs, int W, int H)
{
  if (IDs==NULL) IDs = new unsigned char[W*H*4];
  GLint OldPackAlignment;
  glGetIntegerv(GL_PACK_ALIGNMENT,&OldPackAlignment); 
  glPixelStorei(GL_PACK_ALIGNMENT,1);
    glReadPixels(0,0,W,H, GL_RGBA, GL_UNSIGNED_BYTE, IDs);
  glPixelStorei(GL_PACK_ALIGNMENT,OldPackAlignment);
}

//----------------------------------------------------------------------------
// Read back the distance buffer into a 1D array of floats from the current
// glReadBuffer (usually GL_BACK). The user must provide the MaxDist (or
// MaxMaxDist if more general routine is being used) of the depth values so
// that the properly scaled distance values are returned. The scaling is done
// by the hardware using the scale/bias routines. Again, if Dists is NULL,
// automatic allocation occurs.
//----------------------------------------------------------------------------
void vdReadbackDists(float* &Dists, int W, int H, float MaxDist)
{
  if (Dists==NULL) Dists = new float[W*H];

  GLint OldPackAlignment;
  glGetIntegerv(GL_PACK_ALIGNMENT,&OldPackAlignment); 
  glPixelStorei(GL_PACK_ALIGNMENT,1);
    glReadPixels(0,0,W,H, GL_DEPTH_COMPONENT,GL_FLOAT,Dists);
  glPixelStorei(GL_PACK_ALIGNMENT,OldPackAlignment);

  for (int i=0; i<W*H; i++)
    Dists[i]*=MaxDist;
}

//----------------------------------------------------------------------------
// Read back the ID (or color) at a particular pixel location (Px,Py). As in the
// whole buffer version, there are 2 versions: one that returns the actual
// RGB unsigned char color and one that translate the color into the site
// ID.
//----------------------------------------------------------------------------
void vdReadbackID(unsigned char *ID, int Px, int Py)
{
  GLint OldPackAlignment;
  glGetIntegerv(GL_PACK_ALIGNMENT,&OldPackAlignment); 
  glPixelStorei(GL_PACK_ALIGNMENT,1);
    glReadPixels(Px,Py,1,1, GL_RGBA, GL_UNSIGNED_BYTE, ID);
  glPixelStorei(GL_PACK_ALIGNMENT,OldPackAlignment);
}

//----------------------------------------------------------------------------
// Read back the distance value at a particular pixel location (Px,Py).
// The user must specify the MaxDist so the depth can be properly scaled.
//----------------------------------------------------------------------------
void vdReadbackDist(float *Dist, int Px, int Py, float MaxDist)
{
  GLint OldPackAlignment;
  glGetIntegerv(GL_PACK_ALIGNMENT,&OldPackAlignment); 
  glPixelStorei(GL_PACK_ALIGNMENT,1);
    glReadPixels(Px,Py,1,1, GL_DEPTH_COMPONENT,GL_FLOAT,Dist);
  glPixelStorei(GL_PACK_ALIGNMENT,OldPackAlignment);

  *Dist *= MaxDist;
}

//----------------------------------------------------------------------------
// The following routines allow a user to specify an arbitrary (floating point)
// location in the Min/Max box and query for the NEAREST ID or distance value.
// The versions provided are the same as the pixel-level queries above.
// NOTE: the (wx,wy) point is clamped to lie in the Min/Max box.
//----------------------------------------------------------------------------
void vdNearestPixel(float wx, float wy,                              // WORLD POSITION IN MIN/MAX BOX
                    float MinX, float MinY, float MaxX, float MaxY,  // MIN/MAX BOX
                    int W, int H,                                    // PIXEL DIMENSION OF VOR DIAG
                    int &px, int &py)                                // RETURNED NEAREST PIXEL LOCATION
{
  float s = (wx-MinX) / (MaxX-MinX);
  float t = (wy-MinY) / (MaxY-MinY);
  px = (int)(s*W);
  py = (int)(t*H);
  if (px<0) px=0; else if (px>=W) px=W-1;
  if (py<0) py=0; else if (py>=H) py=H-1;
}                

void vdReadbackID(unsigned char *ID, 
                  float wx, float wy,
                  float MinX, float MinY, float MaxX, float MaxY,
                  int W, int H)
{
  int px, py;
  vdNearestPixel(wx,wy,MinX,MinY,MaxX,MaxY,W,H, px,py);
  vdReadbackID(ID,px,py);
}

void vdReadbackDist(float *Dist, float MaxDist,
                    float wx, float wy,
                    float MinX, float MinY, float MaxX, float MaxY,
                    int W, int H)
{
  int px, py;
  vdNearestPixel(wx,wy,MinX,MinY,MaxX,MaxY,W,H, px,py);
  vdReadbackDist(Dist,px,py,MaxDist);
}
