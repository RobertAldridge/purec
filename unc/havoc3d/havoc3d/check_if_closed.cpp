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
// check_if_closed.cpp :
//============================================================================

#include <stdio.h>
#include <GL/glut.h>

void CheckIfClosed_Begin(float *m, float *M)
{
  GLint NumStencilBits;
  glGetIntegerv(GL_STENCIL_BITS,&NumStencilBits);
  if (NumStencilBits<1) printf("No stencil buffer available! Add GLUT_STENCIL!\n");

  int ResX=(int)glutGet((GLenum)GLUT_WINDOW_WIDTH), ResY=(int)glutGet((GLenum)GLUT_WINDOW_HEIGHT);

  glPushAttrib(GL_POLYGON_BIT);
    glDisable(GL_CULL_FACE);
  glPushAttrib(GL_VIEWPORT_BIT);
    glViewport(0,0,ResX,ResY);
  glPushAttrib(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(0);
  glPushAttrib(GL_COLOR_BUFFER_BIT);
    glColorMask(0,0,0,0);
  glPushAttrib(GL_STENCIL_BUFFER_BIT);
    glEnable(GL_STENCIL_TEST);
    glStencilMask(255);
    glStencilFunc(GL_ALWAYS,0,0);
    glStencilOp(GL_KEEP,GL_INVERT,GL_INVERT);
  glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
  glMatrixMode(GL_PROJECTION); 
    glPushMatrix();
    glLoadIdentity();
    glOrtho(m[0],M[0],m[1],M[1],-M[2],-m[2]);

  glClearStencil(0);
  glClear(GL_STENCIL_BUFFER_BIT);
  glBegin(GL_TRIANGLES);
}

void CheckIfClosed_AddTri(float *A, float *B, float *C)
{
  glVertex3fv(A);
  glVertex3fv(B);
  glVertex3fv(C);
}

int CheckIfClosed_End()
{
  glEnd();

  glMatrixMode(GL_PROJECTION); 
    glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
  glPopAttrib();   // GL_STENCIL_BUFFER_BIT
  glPopAttrib();   // GL_COLOR_BUFFER_BIT
  glPopAttrib();   // GL_DEPTH_BUFFER_BIT
  glPopAttrib();   // GL_VIEWPORT_BIT
  glPopAttrib();   // GL_POLYGON_BIT

  glFinish();

  int ResX=(int)glutGet((GLenum)GLUT_WINDOW_WIDTH), ResY=(int)glutGet((GLenum)GLUT_WINDOW_HEIGHT);
  unsigned char *Stencil = new unsigned char[ResX*ResY];
  glReadPixels(0,0,ResX,ResY,GL_STENCIL_INDEX,GL_UNSIGNED_BYTE,Stencil);

  int NumPts=0;
  unsigned char *LastAddr_1 = &(Stencil[ResX*ResY-1]) + 1;
  for (unsigned char *s=Stencil; s!=LastAddr_1; s++) NumPts+=(*s>0);

  if (NumPts>0) return(0);
  return(1);
}
