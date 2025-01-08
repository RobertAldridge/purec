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
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include "pts.hpp"
#include <color_ids.hpp>
#include <drawslice_gl.hpp>
#include <pt_distmesh.hpp>
#include <line_distmesh.hpp>
#include <tri_distmesh.hpp>
#include <voronoi_slice.hpp>
#include <pixel_error.hpp>
#include <queries.hpp>

int ResX=256, ResY=256, ResZ=256;
//int ResX=472, ResY=236, ResZ=90;

unsigned char *SliceColor=NULL;  // SLICE STORAGE FOR BRUTE-FORCE APPROACH
float *SliceDist=NULL;

int iSlice=0;
int AnimationOn=1;
int DrawSitesOn=1;
int DrawColor=1;
int UseBruteForce=0;
int TimerOn=0;
int SliceOn=1;
int DrawDistMeshesOn=0;

int LeftButtonDown=0;        // MOUSE STUFF
int RightButtonDown=0;
int OldX,OldY,NewX,NewY;
float Elevation=0;
float Azimuth=0;

float m[] = {0.0f,0.0f,0.0f};
float M[] = {1.0f,1.0f,1.0f};

float MaxDist = 0.1f;

// FULL VOLUME COMPUTATION
unsigned char* *Colors=NULL;
float* *Dists=NULL;
int Full3DComputationOn=0;

#define RAND() (float)(rand()/(float)RAND_MAX)  // NORMALIZED RAND FUNCTION [0,1]

float *Pts=NULL, *VelPts=NULL;
int NumPts=0;
int NumPtSites, NumLineSites, NumTriSites;

void CreateRandomSites(int numptsites, int numlinesites, int numtrisites)
{
  if (Pts) delete[] Pts;
  if (VelPts) delete[] VelPts;

  NumPtSites=numptsites;
  NumLineSites=numlinesites;
  NumTriSites=numtrisites;

  // CREATE ANIMATED POINTS
  NumPts = NumPtSites + NumLineSites*2 + NumTriSites*3;
  Pts = CreatePts(NumPts);
  VelPts = CreateVelocityPts(NumPts,0.005f);
}

void NormalizeDepth(GLfloat *Depth, int W, int H, float MaxDist)
{
  float invMaxDist = 1.0f/MaxDist;
  for (int i=0; i<(W*H); i++)
    Depth[i] *= invMaxDist;
}

void myDrawDistanceMeshes(float m[2], float M[2],
                          int Width, int Height,
                          float MaxDist, float MeshDistError, float SliceZ)
{
  int i, j=0, iPts=0;
  unsigned char SiteID[4];
  for (i=0; i<NumPtSites; i++, iPts+=3, j++)
  {
    glColor4ubv(vdINT2RGBA(j,SiteID));
    vdDrawDistMesh_Pt(&(Pts[iPts]),SliceZ,m,M,MeshDistError,MaxDist);
  }
  for (i=0; i<NumLineSites; i++, iPts+=6, j++)
  {
    glColor4ubv(vdINT2RGBA(j,SiteID));
    vdDrawDistMesh_LineSegment(&(Pts[iPts]),&(Pts[iPts+3]),SliceZ,m,M,MeshDistError,MaxDist,0);
  }
  for (i=0; i<NumTriSites; i++, iPts+=9, j++)
  {
    glColor4ubv(vdINT2RGBA(j,SiteID));
    vdDrawDistMesh_Tri(&(Pts[iPts]),&(Pts[iPts+3]),&(Pts[iPts+6]),SliceZ,m,M,MeshDistError,MaxDist,0);
  }
}

void DrawSiteGeometry()
{
  int i, j=0, iPts=0;
  glBegin(GL_POINTS);
  for (i=0; i<NumPtSites; i++, iPts+=3, j++)
    glVertex3fv(&(Pts[iPts]));
  glEnd();
  glBegin(GL_LINES);
  for (i=0; i<NumLineSites; i++, iPts+=6, j++)
  {
    glVertex3fv(&(Pts[iPts]));
    glVertex3fv(&(Pts[iPts+3]));
  }
  glEnd();
  glBegin(GL_TRIANGLES);
  for (i=0; i<NumTriSites; i++, iPts+=9, j++)
  {
    glVertex3fv(&(Pts[iPts]));
    glVertex3fv(&(Pts[iPts+3]));
    glVertex3fv(&(Pts[iPts+6]));
  }
  glEnd();
}

void myDisplay(void)
{
  clock_t StartTime;
  if (TimerOn) StartTime=clock();

  float SliceZ = m[2] + (M[2]-m[2])*(((float)iSlice+0.5f)/ResZ);
  float MeshDistError = vdCalcPixelDistError2D(m[0],m[1],M[0],M[1],ResX,ResY);

  // COMPUTE A SLICE OF THE VORONOI DIAGRAM
  if (SliceOn)
  {
    vdComputeSlice_Begin(m,M,ResX,ResY,MaxDist);
    myDrawDistanceMeshes(m,M,ResX,ResY,MaxDist,MeshDistError,SliceZ);
    vdComputeSlice_End();
  }

  if (TimerOn) printf("%g seconds\n", (clock()-StartTime)/(float)CLOCKS_PER_SEC);

  // GENERATE TEXTURE FROM COLOR OR DEPTH BUFFER (IF NOT BRUTE-FORCE)
  GLuint TexID;
  if (SliceOn)
  {
    if (DrawColor)
      TexID = vdCreateTextureObjFromColorBuffer(ResX,ResY,GL_BACK,GL_CLAMP,GL_NEAREST);
    else
      TexID = vdCreateTextureObjFromDepthBuffer(ResX,ResY,GL_BACK,GL_CLAMP,GL_NEAREST);
  }

  // 3D VIEW
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushAttrib(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glRotatef(Elevation,1,0,0);
  glRotatef(Azimuth,0,1,0);

    // DRAW STUFF (IN UNIT CUBE [0,1], MUST SCALE TO FIT [-1,1])
    glPushMatrix();
    glTranslatef(-1,-1,-1);
    glScalef(2,2,2);

      // DRAW VORONOI SLICE
      if (SliceOn)
      {
        vdDrawSliceWithTexture(SliceZ,m[0],m[1],M[0],M[1],TexID,ResX,ResY);
        glDeleteTextures(1,&TexID);
      }

      // DRAW SITES
      if (DrawSitesOn) 
      {
        glColor3f(1,1,1);
        DrawSiteGeometry();
      }

      // DRAW DISTANCE MESHES
      if (DrawDistMeshesOn)
      {
        vdDrawDistMeshes_Begin(SliceZ);
        myDrawDistanceMeshes(m,M,ResX,ResY,MaxDist,MeshDistError,SliceZ);
        vdDrawDistMeshes_End();
      }

      // DRAW BOUNDED REGION CUBE (IN WHICH WE ARE COMPUTING THE VORONOI DIAGRAM)
      glPushMatrix();
        float dX=M[0]-m[0], dY=M[1]-m[1], dZ=M[2]-m[2];
        glTranslatef(m[0],m[1],m[2]);
        glScalef(dX,dY,dZ);
        glTranslatef(0.5f,0.5f,0.5f);
        glColor3f(0,1,0);
        glutWireCube(1);
      glPopMatrix();
    
    glPopMatrix();

    // DRAW BOUNDED REGION CUBE (IN WHICH WE ARE COMPUTING THE VORONOI DIAGRAM)
    glLineWidth(1);
    glColor3f(1,1,1);
    glutWireCube(2);

  glPopMatrix();
  glPopAttrib(); // GL_DEPTH_BUFFER_BIT

  glutSwapBuffers();

  if (AnimationOn) AnimatePts(Pts,VelPts,NumPts);
}

void myDisplay_EntireVolume(void)
{
  float MeshDistError = vdCalcPixelDistError3D(m[0],m[1],m[2],M[0],M[1],M[2],ResX,ResY,ResZ);

  // COMPUTE ENTIRE 3D VORONOI DIAGRAM
  if (Colors==NULL && Dists==NULL)
  {
    printf("computing entire 3D Voronoi diagram...\n");
    clock_t StartTime=clock();

    Colors = new unsigned char*[ResZ];
    Dists = new float*[ResZ];

    for (int iZ=0; iZ<ResZ; iZ++)
    {
      float SliceZ = m[2] + (((float)iZ+0.5f)/ResZ)*(M[2]-m[2]);
      vdComputeSlice_Begin(m,M,ResX,ResY,MaxDist);
      myDrawDistanceMeshes(m,M,ResX,ResY,MaxDist,MeshDistError,SliceZ);
      vdComputeSlice_End();

      Colors[iZ]=NULL;
      Dists[iZ]=NULL;
      vdReadbackIDs(Colors[iZ],ResX,ResY);
      vdReadbackDists(Dists[iZ],ResX,ResY,MaxDist);
    }

    printf("  %g seconds\n", (clock()-StartTime)/(float)CLOCKS_PER_SEC);
  }

  // 3D VIEW
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glRotatef(Elevation,1,0,0);
  glRotatef(Azimuth,0,1,0);

    // DRAW STUFF (IN UNIT CUBE [0,1], MUST SCALE TO FIT [-1,1])
    glPushMatrix();
    glTranslatef(-1,-1,-1);
    glScalef(2,2,2);

      // DRAW VORONOI SLICE
      if (SliceOn)
      {
          float SliceZ = m[2] + (M[2]-m[2])*(((float)iSlice+0.5f)/ResZ);
          if (DrawColor) vdDrawSliceVoronoi3D(Colors[iSlice],SliceZ,m[0],m[1],M[0],M[1],ResX,ResY);
          else           vdDrawSliceVoronoi3D(Dists[iSlice],SliceZ,m[0],m[1],M[0],M[1],ResX,ResY);
      }

      // DRAW SITES
      if (DrawSitesOn) 
      {
        glColor3f(1,1,1);
        DrawSiteGeometry();
      }

      // DRAW BOUNDED REGION CUBE (IN WHICH WE ARE COMPUTING THE VORONOI DIAGRAM)
      glPushMatrix();
        float dX=M[0]-m[0], dY=M[1]-m[1], dZ=M[2]-m[2];
        glTranslatef(m[0],m[1],m[2]);
        glScalef(dX,dY,dZ);
        glTranslatef(0.5f,0.5f,0.5f);
        glColor3f(0,1,0);
        glutWireCube(1);
      glPopMatrix();
    
    glPopMatrix();

    // DRAW BOUNDED REGION CUBE (IN WHICH WE ARE COMPUTING THE VORONOI DIAGRAM)
    glColor3f(1,1,1);
    glLineWidth(1);
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
}

void KeyInputHandler(unsigned char Key, int x, int y)
{
  switch(Key)
  {
    case '-': iSlice--; if (iSlice<0) iSlice=0; break;
    case '+': iSlice++; if (iSlice>=ResZ) iSlice=ResZ-1; break;
    case '`': DrawSitesOn=!DrawSitesOn; break;
    case '\\': AnimationOn=!AnimationOn; break;
    case 'd': DrawColor=!DrawColor; break;
    case 't': TimerOn=!TimerOn; break;
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
    case '3': Full3DComputationOn=!Full3DComputationOn;
      if (Full3DComputationOn)
      {
        printf("full volume mode!\n");
        glutDisplayFunc(myDisplay_EntireVolume);
        glutIdleFunc(myDisplay_EntireVolume);
      }
      else
      {
        printf("single slice mode!\n");
        glutDisplayFunc(myDisplay);
        glutIdleFunc(myDisplay);
        if (Colors!=NULL && Dists!=NULL)
        {
          for (int i=0; i<ResZ; i++)
          {
            delete[] Colors[i];
            delete[] Dists[i];
          }
          delete[] Colors;
          delete[] Dists;
          Colors=NULL;
          Dists=NULL;
        }
      }
      break;
    case 27: exit(0);
  };
}

void PrintVisualInfo()
{
  GLint i;
  GLboolean j;
  printf("GRAPHICS VISUAL INFO (# bits of each):\n");
  glGetIntegerv(GL_RED_BITS,&i);    printf("RGBA: %d ", i);
  glGetIntegerv(GL_GREEN_BITS,&i);  printf("%d ", i);
  glGetIntegerv(GL_BLUE_BITS,&i);   printf("%d ", i);
  glGetIntegerv(GL_ALPHA_BITS,&i);  printf("%d\n", i);
  glGetIntegerv(GL_ACCUM_RED_BITS,&i);    printf("Accum RGBA: %d ", i);
  glGetIntegerv(GL_ACCUM_GREEN_BITS,&i);  printf("%d ", i);
  glGetIntegerv(GL_ACCUM_BLUE_BITS,&i);   printf("%d ", i);
  glGetIntegerv(GL_ACCUM_ALPHA_BITS,&i);  printf("%d\n", i);
  glGetIntegerv(GL_INDEX_BITS,&i);  printf("Color Index: %d\n", i);
  glGetIntegerv(GL_DEPTH_BITS,&i);  printf("Depth: %d\n", i);
  glGetIntegerv(GL_STENCIL_BITS,&i);  printf("Stencil: %d\n", i);
  glGetBooleanv(GL_DOUBLEBUFFER,&j); printf("Double Buffer?  %d\n", j);
  glGetBooleanv(GL_STEREO,&j); printf("Stereo Buffer?  %d\n", j);
  glGetIntegerv(GL_AUX_BUFFERS,&i);  printf("# Aux Buffers: %d\n", i);
}

void main(void)
{
  CreateRandomSites(0,1,0);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);
  glutInitWindowSize(512,512);
  glutInitWindowPosition(180,100);
  glutCreateWindow("Kenny's New and Improved 3D Voronoi Diagrams");

  glutKeyboardFunc(KeyInputHandler);
  glutReshapeFunc(myReshape);
  glutDisplayFunc(myDisplay);
  glutIdleFunc(myDisplay);
  glutMouseFunc(myMouseFunc);
  glutMotionFunc(myMotionFunc);

  PrintVisualInfo();

  glEnable(GL_DEPTH_TEST);

  glutMainLoop();
}
