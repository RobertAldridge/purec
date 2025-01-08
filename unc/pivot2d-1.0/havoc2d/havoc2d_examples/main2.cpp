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
#include "voronoi_pixel_error.hpp"
#include "voronoi_sites.hpp"
#include "voronoi_site_pt.hpp"
#include "voronoi_site_line.hpp"
#include "voronoi_site_polyline.hpp"
#include "voronoi_site_polygon.hpp"
#include "voronoi_site_bezier.hpp"
#include "voronoi_adaptive.hpp"

int WW=512, WH=512;
float FillGeomRatio=0.5f;  // IN (0,1), HIGHER VALUES INCREASE FILL REQUIREMENTS AND REDUCE GEOMETRY
VoronoiSites *vSites=NULL;

float *Pts, *VelPts;
int NumPts;

int AnimationOn=1;
int DrawSitesOn=1;
int UsingAdaptiveStrategy=0;

// NAVIGATION
int LeftButtonDown=0;        // MOUSE STUFF
int RightButtonDown=0;
int OldX,OldY,NewX,NewY;
float CntrX=0.5f, CntrY=0.5f;
float HalfWidth=0.5f;

void myDisplay(void)
{
  int VW=WW/4, VH=WH/4;  // DIMENSIONS OF THE COMPUTED VORONOI DIAGRAM

  // WINDOW BOUNDING BOX
  float mX,mY,MX,MY;
  float HalfHeight = HalfWidth*((float)WH/WW);
  mX=CntrX-HalfWidth;
  MX=CntrX+HalfWidth;
  mY=CntrY-HalfHeight;
  MY=CntrY+HalfHeight;

  if (UsingAdaptiveStrategy)
    vdCompute_Adaptive(vSites, mX,mY,MX,MY, 1.415f, FillGeomRatio, VW,VH,
                       1.0f/sqrt(vSites->NumSites),0.5f/sqrt(vSites->NumSites));
  else
    vdCompute(vSites, mX,mY,MX,MY, 1.415f, FillGeomRatio, VW,VH);

  if (DrawSitesOn) 
  { 
    glColor3f(1,1,1);
    glLineWidth(1);
    glPointSize(1);
    vdDrawSites(vSites, mX,mY,MX,MY, VW,VH);
  }

  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(mX,MX,mY,MY);  
  glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  glColor3f(0,1,0);
  glLineWidth(2);
  glPointSize(5);
  for (int i=0; i<vSites->NumSites; i++)
    vSites->Sites[i]->DrawSite();
  glBegin(GL_LINE_LOOP);
    glVertex2f(0,0);
    glVertex2f(1,0);
    glVertex2f(1,1);
    glVertex2f(0,1);
  glEnd();

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
    CntrX -= (RelX*HalfWidth*2);
    float HalfHeight = HalfWidth*((float)WH/WW);
    CntrY += (RelY*HalfHeight*2);
  }
}

void KeyInputHandler(unsigned char Key, int x, int y)
{
  switch(Key)
  {
    case '`': DrawSitesOn=!DrawSitesOn; break;
    case ' ': UsingAdaptiveStrategy=!UsingAdaptiveStrategy; break;
    case '\\': AnimationOn=!AnimationOn; break;
    case ',': HalfWidth*=0.9f; break;
    case '.': HalfWidth*=1.1f; break;
    case 27: exit(0);
  };
}

void main(void)
{
  int NumPtSites=1000;
  int NumLineSites=2;
  int NumPolylineSites=0;
  int NumTriSites=0;
  int NumBezierSites=0;

  // CREATE ANIMATED POINTS
  NumPts = NumPtSites + NumLineSites*2 + NumTriSites*3 + NumBezierSites*4;
  Pts = CreatePts(NumPts);
  VelPts = CreateVelocityPts(NumPts,0.005f);

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
    PolylineSite = new VoronoiPolylineSite(&(Pts[iPts]),3,0);
    vSites->Add(PolylineSite);
  }
  for (i=0; i<NumTriSites; i++, iPts+=6)
  {
    TriSite = new VoronoiPolygonSite(&(Pts[iPts]),3,0);
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

  glShadeModel(GL_FLAT);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glDisable(GL_DITHER);
  glPixelStorei(GL_PACK_ALIGNMENT,1); 

  glutMainLoop();
}
