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
// drawslice_gl.hpp
//============================================================================

#include <GL/glut.h>

int CalcTexRes(int ResX, int ResY);

GLuint vdCreateTextureObjFromColorBuffer(GLubyte *Color, int Width, int Height,
                                         GLfloat WrapMode, GLfloat InterpMode);
GLuint vdCreateTextureObjFromDepthBuffer(GLfloat *Depth, int Width, int Height,
                                         GLfloat WrapMode, GLfloat InterpMode);

GLuint vdCreateTextureObjFromColorBuffer(int Width, int Height, GLint ReadBuffer,
                                         GLfloat WrapMode, GLfloat InterpMode);
GLuint vdCreateTextureObjFromDepthBuffer(int Width, int Height, GLint ReadBuffer, 
                                         GLfloat WrapMode, GLfloat InterpMode);
                                       
void vdDrawSliceWithTexture(float SliceZ, float MinX, float MinY, float MaxX, float MaxY,
                            GLuint TexID, int ResX, int ResY);

void vdDrawSliceVoronoi3D(unsigned char *Color, float SliceZ, 
                          float MinX, float MinY, float MaxX, float MaxY, int ResX, int ResY);
void vdDrawSliceVoronoi3D(float *Depth, float SliceZ, 
                          float MinX, float MinY, float MaxX, float MaxY, int ResX, int ResY);
