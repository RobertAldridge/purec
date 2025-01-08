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

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <voronoi_slice.hpp>
#include <pt_distmesh.hpp>
#include <line_distmesh.hpp>
#include <tri_distmesh.hpp>
#include <drawslice_gl.hpp>
#include <pixel_error.hpp>
#include <color_ids.hpp>

int LeftButtonDown=0;        // MOUSE STUFF
int RightButtonDown=0;
int OldX,OldY,NewX,NewY;
float Elevation=0;
float Azimuth=0;
int iSlice=0;
float MaxDist = (float)sqrt(3.0f);
int DrawDistMeshesOn=0;
int SliceOn=1;
int DrawColor=1;
int ResZ=256;

// PT, LINE, AND TRI VORONOI SITE GEOMETRY
float P1[]={0.5f,0.9f,0.5f};
float P2[]={-0.7f,-0.5f,-0.5f};
float La[]={0.5f,0.9f,0.5f}, Lb[]={-0.7f,-0.5f,-0.5f};
float Ta[]={-0.5f,0.3f,0.8f}, Tb[]={-0.8f,0.8f,0}, Tc[]={0.1f,-0.8f,0.1f};
//float Ta[]={0.1f,0.1f,0.1f}, Tb[]={0.5f,0.2f,0.3f}, Tc[]={0.3f,0.8f,0.4f};

void myDisplay(void)
{
  // VORONOI DIAGRAM PARAMETERS
  float m[]={-1,-1,-1}, M[]={1,1,1};
  int ResX=512, ResY=512;
  float MeshDistError = vdCalcPixelDistError3D(m[0],m[1],m[2],M[0],M[1],M[2],ResX,ResY,ResZ);
  float SliceZ = m[2] + (M[2]-m[2])*(((float)iSlice+0.5f)/ResZ);
  
  // COMPUTE VORONOI DIAGRAM AND STORE IN TEXTURE
  vdComputeSlice_Begin(m,M,ResX,ResY,MaxDist);
    glColor3f(1,0,0);
    vdDrawDistMesh_Pt(P1,SliceZ,m,M,MeshDistError,MaxDist);
    vdDrawDistMesh_Pt(P2,SliceZ,m,M,MeshDistError,MaxDist);
    glColor3f(0,1,0);
    vdDrawDistMesh_LineSegment(La,Lb,SliceZ,m,M,MeshDistError,MaxDist,0);
    //glColor3f(0,0,1);
    //vdDrawDistMesh_Tri(Ta,Tb,Tc,SliceZ,m,M,MeshDistError,MaxDist,0);
  vdComputeSlice_End();

  // GRAB VORONOI DIAGRAM FROM FRAMEBUFFER TO CREATE TEXTURE
  GLuint TexID1 = vdCreateTextureObjFromColorBuffer(ResX,ResY,GL_BACK,GL_CLAMP,GL_NEAREST);
  GLuint TexID2 = vdCreateTextureObjFromDepthBuffer(ResX,ResY,GL_BACK,GL_CLAMP,GL_NEAREST);

  // 3D VIEW
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glRotatef(Elevation,1,0,0);
  glRotatef(Azimuth,0,1,0);

    //vdDrawSliceWithTexture(SliceZ,m[0],m[1],M[0],M[1],TexID,ResX,ResY);
      // DRAW VORONOI SLICE
      if (SliceOn)
      {
          if (DrawColor) vdDrawSliceWithTexture(SliceZ,m[0],m[1],M[0],M[1],TexID1,ResX,ResY);
          else           vdDrawSliceWithTexture(SliceZ,m[0],m[1],M[0],M[1],TexID2,ResX,ResY);
      }
    glDeleteTextures(1,&TexID1);
    glDeleteTextures(1,&TexID2);

    glPointSize(3);
    glLineWidth(2);
    glColor3f(1,1,1);
    glBegin(GL_POINTS); glVertex3fv(P1); glVertex3fv(P2); glEnd();
    glBegin(GL_LINES); glVertex3fv(La); glVertex3fv(Lb); glEnd();
    //glBegin(GL_TRIANGLES); glVertex3fv(Ta); glVertex3fv(Tb); glVertex3fv(Tc); glEnd();

      // DRAW DISTANCE MESHES
      if (DrawDistMeshesOn)
      {
        vdDrawDistMeshes_Begin(SliceZ);
        //myDrawDistanceMeshes(m,M,ResX,ResY,MaxDist,MeshDistError,SliceZ);
          glColor3f(1,0,0);
          vdDrawDistMesh_Pt(P1,SliceZ,m,M,MeshDistError,MaxDist);
          vdDrawDistMesh_Pt(P2,SliceZ,m,M,MeshDistError,MaxDist);
          glColor3f(0,1,0);
          vdDrawDistMesh_LineSegment(La,Lb,SliceZ,m,M,MeshDistError,MaxDist,0);
          //glColor3f(0,0,1);
          //vdDrawDistMesh_Tri(Ta,Tb,Tc,SliceZ,m,M,MeshDistError,MaxDist,0);
        vdDrawDistMeshes_End();
      }

     // DRAW BOUNDED REGION CUBE (IN WHICH WE ARE COMPUTING THE VORONOI DIAGRAM)
    glLineWidth(1);
    glColor3f(1,1,1);
    glutWireCube(2);

  glPopMatrix();

  glutSwapBuffers();
}

void myReshape(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45,(float)w/(float)h,0.01,10);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0,0,4, 0,0,0, 0,1,0);
}

void myMouseFunc(int button, int state, int x, int y)
{
  NewX=x; NewY=y;
  if (button==GLUT_LEFT_BUTTON)
    LeftButtonDown=!LeftButtonDown;
}


void KeyInputHandler(unsigned char Key, int x, int y)
{
  switch(Key)
  {
    case '-': iSlice--; if (iSlice<0) iSlice=0; break;
    case '+': iSlice++; if (iSlice>=ResZ) iSlice=ResZ-1; break;
    //case '`': DrawSitesOn=!DrawSitesOn; break;
    case 'd': DrawColor=!DrawColor; break;
    case 's': SliceOn=!SliceOn; break;
    case 'D': DrawDistMeshesOn=!DrawDistMeshesOn; break;
    case ';': MaxDist-=0.01f; if (MaxDist<0) MaxDist=0; printf("MaxDist=%g\n",MaxDist); break;
    case '\'': MaxDist+=0.01f; printf("MaxDist=%g\n",MaxDist); break;
    case 'w': 
     { int State[2];
       glGetIntegerv(GL_POLYGON_MODE,State);
       if (State[0]==GL_LINE) glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
       else glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); }
     break;
    case 27: exit(0);
  };
}

void myMotionFunc(int x, int y)
{
  OldX=NewX; OldY=NewY;
  NewX=x;    NewY=y;
  float RelX = (NewX-OldX) / (float)glutGet((GLenum)GLUT_WINDOW_WIDTH);
  float RelY = (NewY-OldY) / (float)glutGet((GLenum)GLUT_WINDOW_HEIGHT);
  if (LeftButtonDown) 
  { 
    Azimuth += (RelX*180);
    Elevation += (RelY*180);
  }
  glutPostRedisplay();
}

void main(void)
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(512,512);
  glutInitWindowPosition(180,100);
  glutCreateWindow("Kenny's New and Improved 3D Voronoi Diagrams");

  glutReshapeFunc(myReshape);
  glutDisplayFunc(myDisplay);
  glutIdleFunc(myDisplay);
  glutMouseFunc(myMouseFunc);
  glutMotionFunc(myMotionFunc);
  glutKeyboardFunc(KeyInputHandler);

  glEnable(GL_DEPTH_TEST);

  glutMainLoop();
}
