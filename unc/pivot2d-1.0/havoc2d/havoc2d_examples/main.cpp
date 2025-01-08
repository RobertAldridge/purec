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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "pts.hpp"
#include "voronoi.hpp"
#include "voronoi_sites.hpp"
#include "voronoi_site_pt.hpp"
#include "voronoi_site_line.hpp"
#include "voronoi_site_polyline.hpp"
#include "voronoi_site_polygon.hpp"
#include "voronoi_site_bezier.hpp"
#include "voronoi_adaptive.hpp"
#include "voronoi_site_cull.hpp"
#include "voronoi_draw_gl.hpp"

int WW=512, WH=512;
float FillGeomRatio=0.5f;  // IN (0,1), HIGHER VALUES INCREASE FILL REQUIREMENTS AND REDUCE GEOMETRY
float MaxDist = 0.4f;
VoronoiSites *vSites=NULL;

float *Pts, *VelPts;
int NumPts;

int AnimationOn=0;
int UsingAdaptiveStrategy=0;
int CullingOn=1;
int DrawMinMaxBoxes=0;
int DrawCullBoxes=0;

// VORONOI DIAGRAM DIST ERROR BOUND
float DistError = 0.005f;

// WINDOW BOUNDING BOX
float mX=0.4f,mY=0.4f,MX=0.6f,MY=0.6f;

// NAVIGATION
int LeftButtonDown=0;        // MOUSE STUFF
int RightButtonDown=0;
int CtrlPressed=0;
int OldX,OldY,NewX,NewY;
float CntrX=0.5f, CntrY=0.5f;
float Scale=2.0f;

void myDisplay(void)
{
  int ResX, ResY;

  vSites->SetAllIsActiveFlags(1);
  if (CullingOn) CullSites_MinMax(vSites,MaxDist,mX,mY,MX,MY);

  if (UsingAdaptiveStrategy)
    vdCompute_Adaptive(vSites, mX,mY,MX,MY, MaxDist, DistError,FillGeomRatio, &ResX,&ResY,
                       1.0f/sqrt(vSites->NumSites),0.5f/sqrt(vSites->NumSites));
  else
    vdCompute(vSites, mX,mY,MX,MY, MaxDist, DistError,FillGeomRatio, &ResX,&ResY);

//printf("%d x %d\n",ResX,ResY);

  GLuint TexID = vdCreateTextureObjFromColorBuffer(ResX,ResY);

  glClear(GL_COLOR_BUFFER_BIT);
  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(Scale,Scale,0);
    glTranslatef(-CntrX,-CntrY,0);

  vdDrawTextureObj(mX,mY,MX,MY,TexID,ResX,ResY);
  glDeleteTextures(1,&TexID);

  glColor3f(1,1,1);
  glLineWidth(1);
  glPointSize(2);
  for (int i=0; i<vSites->NumSites; i++)
    vSites->Sites[i]->DrawSite();
  
  if (DrawMinMaxBoxes)
  {
    float mx,my,Mx,My;
    for (int i=0; i<vSites->NumSites; i++)
    {
      vSites->Sites[i]->CalcMinMax(&mx,&my,&Mx,&My);
      glLineWidth(1);
      glColor3f(1,1,1);
      glBegin(GL_LINE_LOOP);
        glVertex2f(mx,my); glVertex2f(Mx,my); glVertex2f(Mx,My); glVertex2f(mx,My);
      glEnd();
      if (DrawCullBoxes)
      {
        glColor3f(0.5f,0.5f,0.5f);
        glBegin(GL_LINE_LOOP);
          glVertex2f(mx-MaxDist,my-MaxDist); 
          glVertex2f(Mx+MaxDist,my-MaxDist); 
          glVertex2f(Mx+MaxDist,My+MaxDist);
          glVertex2f(mx-MaxDist,My+MaxDist);
        glEnd();
      }
    }
  }

  glutSwapBuffers();
  if (AnimationOn) AnimatePts(Pts,VelPts,NumPts);
}

void myReshape(int w, int h)
{
  glViewport(0, 0, w, h);
  WW=w;
  WH=h;
}

void myMouseFunc(int button, int state, int x, int y)
{
  CtrlPressed = glutGetModifiers() & GLUT_ACTIVE_CTRL;

  if (button==GLUT_LEFT_BUTTON && !CtrlPressed)
  {
    LeftButtonDown=!LeftButtonDown;
    NewX=x; NewY=y;
  }
  else if (button==GLUT_RIGHT_BUTTON && !CtrlPressed)
  {
    RightButtonDown=!RightButtonDown;
    OldX=x; OldY=y;
  }
  else if (button==GLUT_RIGHT_BUTTON && CtrlPressed)
  {
    RightButtonDown=!RightButtonDown;
    NewX=x; NewY=y;
  }
}

void myMotionFunc(int x, int y)
{
  if (LeftButtonDown && !CtrlPressed) 
  { 
    OldX=NewX; OldY=NewY;
    NewX=x;    NewY=y;
    float RelX = (NewX-OldX) / (float)glutGet((GLenum)GLUT_WINDOW_WIDTH);
    float RelY = (NewY-OldY) / (float)glutGet((GLenum)GLUT_WINDOW_HEIGHT);
    CntrX -= ((2.0f*RelX)/Scale);
    CntrY += ((2.0f*RelY)/Scale);
  }
  else if (RightButtonDown && !CtrlPressed)
  {
    NewX=x;    NewY=y;
    int W = glutGet((GLenum)GLUT_WINDOW_WIDTH);
    int H = glutGet((GLenum)GLUT_WINDOW_HEIGHT);
    mX = ((float)OldX/W)*2.0f - 1.0f;
    mY = -(((float)OldY/H)*2.0f - 1.0f);
    MX = ((float)NewX/W)*2.0f - 1.0f;
    MY = -(((float)NewY/H)*2.0f - 1.0f);
    mX = mX/Scale + CntrX;
    mY = mY/Scale + CntrY;
    MX = MX/Scale + CntrX;
    MY = MY/Scale + CntrY;
    float t;
    if (MX<mX) { t=MX; MX=mX; mX=t; }
    if (MY<mY) { t=MY; MY=mY; mY=t; }
  }
  else if (RightButtonDown && CtrlPressed) 
  { 
    OldX=NewX; OldY=NewY;
    NewX=x;    NewY=y;
    float RelX = (NewX-OldX) / (float)glutGet((GLenum)GLUT_WINDOW_WIDTH);
    float RelY = (NewY-OldY) / (float)glutGet((GLenum)GLUT_WINDOW_HEIGHT);
    float TransX = ((2.0f*RelX)/Scale);
    float TransY = ((2.0f*RelY)/Scale);
    mX+=TransX; MX+=TransX;
    mY-=TransY; MY-=TransY;
  }
}

void KeyInputHandler(unsigned char Key, int x, int y)
{
  switch(Key)
  {
    case 'a': UsingAdaptiveStrategy=!UsingAdaptiveStrategy; break;
    case '\\': AnimationOn=!AnimationOn; break;
    case '-': Scale*=0.9f; break;
    case '+': Scale*=1.1f; break;
    case ';': MaxDist-=0.01f; if (MaxDist<0) MaxDist=0; printf("MaxDist=%g\n",MaxDist); break;
    case '\'': MaxDist+=0.01f; printf("MaxDist=%g\n",MaxDist); break;
    case 'c': CullingOn=!CullingOn; printf("CullingOn=%d\n",CullingOn); break;
    case 'b': DrawMinMaxBoxes=!DrawMinMaxBoxes; break;
    case 'B': DrawCullBoxes=!DrawCullBoxes; break;
    case '[': DistError*=0.9f; printf("DistError=%g\n",DistError); break;
    case ']': DistError*=1.1f; printf("DistError=%g\n",DistError); break;
    case 27: exit(0);
  };
}

void main(void)
{
  int NumPtSites=100;
  int NumLineSites=0;
  int NumPolylineSites=0;
  int NumTriSites=0;
  int NumBezierSites=2;

  // CREATE ANIMATED POINTS
  NumPts = NumPtSites + NumLineSites*2 + NumTriSites*3 + NumBezierSites*4;
  Pts = CreatePts(NumPts);
  VelPts = CreateVelocityPts(NumPts,0.002f);

  // CREATE LIST OF VORONOI SITES (LINK SITES TO ANIMATED POINTS)
  vSites = new VoronoiSites();
  VoronoiPointSite *PtSite;
  VoronoiLineSite *LineSite;
  VoronoiPolylineSite *PolylineSite;
  VoronoiPolygonSite *TriSite;
  VoronoiBezierSite *BezSite;
  int i, iPts=0;
  for (i=0; i<NumPtSites; i++, iPts+=2)
  {
    PtSite = new VoronoiPointSite(&(Pts[iPts]),&(Pts[iPts+1]));
    vSites->Add(PtSite);
  }
  for (i=0; i<NumLineSites; i++, iPts+=4)
  {
    LineSite = new VoronoiLineSite(&(Pts[iPts]),&(Pts[iPts+1]),&(Pts[iPts+2]),&(Pts[iPts+3]));
    vSites->Add(LineSite);
  }
  for (i=0; i<NumPolylineSites; i++, iPts+=6)
  {
    PolylineSite = new VoronoiPolylineSite(&(Pts[iPts]),3);
    vSites->Add(PolylineSite);
  }
  for (i=0; i<NumTriSites; i++, iPts+=6)
  {
    TriSite = new VoronoiPolygonSite(&(Pts[iPts]),3);
    vSites->Add(TriSite);
  }
  for (i=0; i<NumBezierSites; i++, iPts+=8)
  {
    BezSite = new VoronoiBezierSite(&(Pts[iPts]),&(Pts[iPts+1]),
                                    &(Pts[iPts+2]),&(Pts[iPts+3]),
                                    &(Pts[iPts+4]),&(Pts[iPts+5]),
                                    &(Pts[iPts+6]),&(Pts[iPts+7]),
                                    16);
    vSites->Add(BezSite);
  }

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(WW,WH);
  glutInitWindowPosition(180,100);
  glutCreateWindow("Kenny's New and Improved 2D Voronoi Diagrams");

  glutKeyboardFunc(KeyInputHandler);
  glutReshapeFunc(myReshape);
  glutDisplayFunc(myDisplay);
  glutIdleFunc(myDisplay);
  glutMouseFunc(myMouseFunc);
  glutMotionFunc(myMotionFunc);

  glDisable(GL_DEPTH_TEST);

  // DEFAULT STATE FOR VORONOI SYSTEM
  glShadeModel(GL_FLAT);
  glDisable(GL_CULL_FACE);
  glDisable(GL_DITHER);
  glPixelStorei(GL_PACK_ALIGNMENT,1); 
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);

  glutMainLoop();
}
