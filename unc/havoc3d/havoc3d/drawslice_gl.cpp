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
// vdDrawSlice_gl.cpp
//============================================================================

#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <GL/glut.h>

//----------------------------------------------------------------------------
// CALCULATE MAX TEX-COORDS (FOR NON-SQUARE, NON POWER-OF-2 TEXTURES)
// FIND SMALLEST SQUARE POWER-OF-2 THAT CONTAINS ResX x ResY IMAGE
//----------------------------------------------------------------------------
int CalcTexRes(int ResX, int ResY)
{
  #define LOG2(x) (log((float)x)/log(2.0f))
  int MaxRes = (ResX>ResY)?ResX:ResY;
  float flog2MaxRes = LOG2(MaxRes);
  int ilog2MaxRes = (int)flog2MaxRes;
  float Frac = flog2MaxRes - (float)ilog2MaxRes;
  if (Frac>0) ilog2MaxRes++;
  int TexRes = 1<<ilog2MaxRes;
  return(TexRes);
}

//----------------------------------------------------------------------------
// Routine used just for debugging and depth range verification
//----------------------------------------------------------------------------
static void PrintMinMax(GLfloat *Depth, int W, int H)
{
  float Min,Max;
  Min=Max=Depth[0];
  for (int i=0; i<(W*H); i++)
    if (Depth[i]<Min) Min=Depth[i]; else if (Depth[i]>Max) Max=Depth[i];
  printf("[%g,%g]\n",Min,Max);
}

//----------------------------------------------------------------------------
// Creates an RGBA texture from a given color image (any dimensions).
//----------------------------------------------------------------------------
GLuint vdCreateTextureObjFromColorBuffer(GLubyte *Color, int Width, int Height,
                                         GLfloat WrapMode, GLfloat InterpMode)
{
  // BE SURE THAT GIVEN BUFFER IS SQUARE, POWER-OF-2 IMAGE
  int TexRes = CalcTexRes(Width,Height);
  GLubyte *NewColor=Color;
  if (TexRes!=Width || TexRes!=Height)
  {
    NewColor = new GLubyte[TexRes*TexRes*4];
    GLubyte *Src=Color, *Dst=NewColor;
    int SrcWidth=Width*4, DstWidth=TexRes*4;
    for (int i=0; i<Height; i++, Src+=SrcWidth, Dst+=DstWidth)
      memcpy(Dst,Src,SrcWidth);
  }

  GLuint TexID;
  glGenTextures(1,&TexID);             
  glBindTexture(GL_TEXTURE_2D,TexID);  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapMode);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapMode);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, InterpMode); 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, InterpMode); 
  glTexImage2D(GL_TEXTURE_2D,0,3,TexRes,TexRes,0,GL_RGBA,GL_UNSIGNED_BYTE,NewColor);

  if (TexRes!=Width || TexRes!=Height) delete[] NewColor;
  return( TexID );
}

GLuint vdCreateTextureObjFromColorBuffer(int Width, int Height, GLint ReadBuffer,
                                         GLfloat WrapMode, GLfloat InterpMode)
{
  int TexRes = CalcTexRes(Width,Height);
  GLuint TexID;
  glGenTextures(1,&TexID);             
  glBindTexture(GL_TEXTURE_2D,TexID);  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapMode);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapMode);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, InterpMode); 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, InterpMode); 
  GLint OldReadBuffer;
  glGetIntegerv(GL_READ_BUFFER,&OldReadBuffer);
  glReadBuffer(ReadBuffer);
  glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,0,0,TexRes,TexRes,0);
  glReadBuffer(OldReadBuffer);
  return( TexID );
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
GLuint vdCreateTextureObjFromDepthBuffer(GLfloat *Depth, int Width, int Height,
                                         GLfloat WrapMode, GLfloat InterpMode)
{
  // BE SURE THAT GIVEN BUFFER IS SQUARE, POWER-OF-2 IMAGE
  int TexRes = CalcTexRes(Width,Height);
  GLfloat *NewDepth=Depth;
  if (TexRes!=Width || TexRes!=Height)
  {
    NewDepth = new GLfloat[TexRes*TexRes];
    GLfloat *Src=Depth, *Dst=NewDepth;
    for (int i=0; i<Height; i++, Src+=Width, Dst+=TexRes)
      memcpy(Dst,Src,Width*4);
  }
  GLuint TexID;
  glGenTextures(1,&TexID);             
  glBindTexture(GL_TEXTURE_2D,TexID);  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapMode);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapMode);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, InterpMode); 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, InterpMode); 
  glTexImage2D(GL_TEXTURE_2D,0,GL_LUMINANCE,TexRes,TexRes,0,GL_LUMINANCE,GL_FLOAT,NewDepth);

  if (TexRes!=Width || TexRes!=Height) delete[] NewDepth;
  return( TexID );
}

GLuint vdCreateTextureObjFromDepthBuffer(int Width, int Height, GLint ReadBuffer,
                                         GLfloat WrapMode, GLfloat InterpMode)
{
  int TexRes = CalcTexRes(Width,Height);
  GLint OldReadBuffer;
  glGetIntegerv(GL_READ_BUFFER,&OldReadBuffer);
  glReadBuffer(ReadBuffer);

  GLfloat *Depth = new GLfloat[TexRes*TexRes];
  GLint OldPackAlignment;
  glGetIntegerv(GL_PACK_ALIGNMENT,&OldPackAlignment); 
  glPixelStorei(GL_PACK_ALIGNMENT,1);
    glReadPixels(0,0,TexRes,TexRes, GL_DEPTH_COMPONENT, GL_FLOAT, Depth);
  glPixelStorei(GL_PACK_ALIGNMENT,OldPackAlignment);
  GLuint TexID = vdCreateTextureObjFromDepthBuffer(Depth,TexRes,TexRes,WrapMode,InterpMode);
  delete[] Depth;

  glReadBuffer(OldReadBuffer);

  return( TexID );
}

//----------------------------------------------------------------------------
// DRAW THE RECTANGULAR SLICE WITH THE VORONOI DIAGRAM TEXTURE-MAPPED ONTO IT
// Handles textures that are non-square and not a power of 2.
//----------------------------------------------------------------------------
void vdDrawSliceWithTexture(float SliceZ, float MinX, float MinY, float MaxX, float MaxY,
                            GLuint TexID, int ResX, int ResY) 
{
  int TexRes = CalcTexRes(ResX,ResY);
  float MaxS = (float)ResX / TexRes;
  float MaxT = (float)ResY / TexRes;

  glPushAttrib(GL_POLYGON_BIT);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,TexID);  
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    glBegin(GL_QUADS);
      glTexCoord2f(0,0);       glVertex3f(MinX,MinY,SliceZ);
      glTexCoord2f(MaxS,0);    glVertex3f(MaxX,MinY,SliceZ);
      glTexCoord2f(MaxS,MaxT); glVertex3f(MaxX,MaxY,SliceZ);
      glTexCoord2f(0,MaxT);    glVertex3f(MinX,MaxY,SliceZ);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  glPopAttrib(); // GL_POLYGON_BIT
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void vdDrawSliceVoronoi3D(unsigned char *Color, float SliceZ, 
                          float MinX, float MinY, float MaxX, float MaxY, int ResX, int ResY)
{
  GLuint TexID = vdCreateTextureObjFromColorBuffer(Color,ResX,ResY,GL_CLAMP,GL_NEAREST);
  vdDrawSliceWithTexture(SliceZ,MinX,MinY,MaxX,MaxY,TexID,ResX,ResY);
  glDeleteTextures(1,&TexID);
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void vdDrawSliceVoronoi3D(float *Depth, float SliceZ, 
                          float MinX, float MinY, float MaxX, float MaxY, int ResX, int ResY)
{
  GLuint TexID = vdCreateTextureObjFromDepthBuffer(Depth,ResX,ResY,GL_CLAMP,GL_NEAREST);
  vdDrawSliceWithTexture(SliceZ,MinX,MinY,MaxX,MaxY,TexID,ResX,ResY);
  glDeleteTextures(1,&TexID);
}
