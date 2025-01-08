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
#include "voronoi_pixel_error.hpp"

int ResX=512, ResY=512;
float DistError=0.01f;
float FillGeomRatio=0.5f;  // IN (0,1), HIGHER VALUES INCREASE FILL REQUIREMENTS AND REDUCE GEOMETRY
float MaxDist = 1.415f;
VoronoiSites *vSites=NULL;

float MinX=0,MinY=0,MaxX=1,MaxY=1;

float *Pts, *VelPts;
int NumPts;

int AnimationOn=1;
int DrawSitesOn=1;
int UsingAdaptiveStrategy=0;

void myDisplay(void)
{
  if (UsingAdaptiveStrategy)
    vdCompute_Adaptive(vSites, MinX,MinY,MaxX,MaxY, MaxDist, DistError,FillGeomRatio, ResX,ResY,
                       1.0f/sqrt(vSites->NumSites),0.5f/sqrt(vSites->NumSites));
  else
    vdCompute(vSites, MinX,MinY,MaxX,MaxY, MaxDist, DistError,FillGeomRatio, ResX,ResY);

  if (DrawSitesOn) 
  { 
    glColor3f(1,1,1);
    glPointSize(3);
    vdDrawSites(vSites, 0,0,1,1, DistError,FillGeomRatio);
  }

  glutSwapBuffers();
  if (AnimationOn) AnimatePts(Pts,VelPts,NumPts);
}

void myReshape(int w, int h)
{
  glViewport(0, 0, w, h);
  printf("%d x %d...\n", w,h);
}

void myMouseFunc(int button, int state, int x, int y)
{
}

void myMotionFunc(int x, int y)
{
}

void KeyInputHandler(unsigned char Key, int x, int y)
{
  switch(Key)
  {
    case '`': DrawSitesOn=!DrawSitesOn; break;
    case '\\': AnimationOn=!AnimationOn; break;
    case ' ': UsingAdaptiveStrategy=!UsingAdaptiveStrategy; break;
    case 'w': 
     { int State[2];
       glGetIntegerv(GL_POLYGON_MODE,State);
       if (State[0]==GL_LINE) glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
       else glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); }
     break;
    case ';': MaxDist-=0.02f; if (MaxDist<0) MaxDist=0; printf("MaxDist=%g\n",MaxDist); break;
    case '\'': MaxDist+=0.02f; printf("MaxDist=%g\n",MaxDist); break;
    case '[': FillGeomRatio-=0.01f; if (FillGeomRatio<0.01f) FillGeomRatio=0.01f; printf("FillGeomRatio=%g\n",FillGeomRatio); break;
    case ']': FillGeomRatio+=0.01f; if (FillGeomRatio>0.99f) FillGeomRatio=0.99f; printf("FillGeomRatio=%g\n",FillGeomRatio); break;
    case '-': DistError-=0.001f; if (DistError<0.001f) DistError=0.001f; printf("DistError=%g\n",DistError); break;
    case '+': DistError+=0.001f; printf("DistError=%g\n",DistError); break;
    case 27: exit(0);
  };
}

void main(void)
{
  int NumPtSites=3;
  int NumLineSites=1;
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
  glutInitWindowSize(ResX,ResY);
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
