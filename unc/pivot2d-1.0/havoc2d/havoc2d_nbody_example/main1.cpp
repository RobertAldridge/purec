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
#include "voronoi.hpp"
#include "voronoi_sites.hpp"
#include "voronoi_site_pt.hpp"
#include "voronoi_site_line.hpp"
#include "voronoi_site_bezier.hpp"
#include "voronoi_queries.hpp"

#define RAND() (float)(rand()/(float)RAND_MAX)             // NORMALIZED RAND FUNCTION [0,1]
#define RAND2() (float)(rand()*(2.0f/(float)RAND_MAX)-1.0) // NORMALIZED RAND FUNCTION [-1,1]

int Res=512;
float FillGeomRatio=0.5f;  // IN (0,1), HIGHER VALUES INCREASE FILL REQUIREMENTS AND REDUCE GEOMETRY
VoronoiSites *vSites=NULL;

int AnimationOn=1;

// NAVIGATION
int LeftButtonDown=0;        // MOUSE STUFF
int RightButtonDown=0;
int CtrlPressed=0;
int OldX,OldY,NewX,NewY;
int iSelectedSite;

class BezierObject
{
  public:

    float oA[2], oB[2], oC[2], oD[2];  // OBJ-SPACE CTRL PT COORDS
    float wA[2], wB[2], wC[2], wD[2];  // WORLD-SPACE CTRL PT COORDS
    float OrigX, OrigY, Angle;
    float dOrigX, dOrigY, dAngle;
  
    BezierObject(float ax, float ay, float bx, float by, float cx, float cy, float dx, float dy,
                 float ox, float oy, float ang)
    {
      oA[0]=ax; oA[1]=ay;
      oB[0]=bx; oB[1]=by;
      oC[0]=cx; oC[1]=cy;
      oD[0]=dx; oD[1]=dy;
      OrigX=ox; OrigY=oy;
      Angle=ang;
    }

    BezierObject(float mx, float my, float Mx, float My,      // OBJ-SPACE MIN/MAX
                 float wmx, float wmy, float wMx, float wMy,  // WORLD-SPACE MIN/MAX
                 float TransSpeed, float RotSpeed)
    {
      float dx=Mx-mx, dy=My-my;
      oA[0] = mx + dx*RAND();   oA[1] = my + dy*RAND();
      oB[0] = mx + dx*RAND();   oB[1] = my + dy*RAND();
      oC[0] = mx + dx*RAND();   oC[1] = my + dy*RAND();
      oD[0] = mx + dx*RAND();   oD[1] = my + dy*RAND();
      OrigX = wmx + (wMx-wmx)*RAND();
      OrigY = wmy + (wMy-wmy)*RAND();
      Angle = RAND()*360.0f;
      dOrigX = RAND2()*TransSpeed;
      dOrigY = RAND2()*TransSpeed;
      dAngle = RAND2()*RotSpeed;
    }

    void ComputeWorldCoords()
    {
      float rAng = Angle*0.01745329f;  // DEG 2 RAD
      float ca=(float)cos(rAng), sa=(float)sin(rAng);
      wA[0] = ca*oA[0] - sa*oA[1] + OrigX;
      wA[1] = sa*oA[0] + ca*oA[1] + OrigY;
      wB[0] = ca*oB[0] - sa*oB[1] + OrigX;
      wB[1] = sa*oB[0] + ca*oB[1] + OrigY;
      wC[0] = ca*oC[0] - sa*oC[1] + OrigX;
      wC[1] = sa*oC[0] + ca*oC[1] + OrigY;
      wD[0] = ca*oD[0] - sa*oD[1] + OrigX;
      wD[1] = sa*oD[0] + ca*oD[1] + OrigY;
    }

    void Animate(float wmx, float wmy, float wMx, float wMy)
    {
      OrigX+=dOrigX; if (OrigX>wMx || OrigX<wmx) { dOrigX=-dOrigX; OrigX+=dOrigX; };
      OrigY+=dOrigY; if (OrigY>wMy || OrigY<wmy) { dOrigY=-dOrigY; OrigY+=dOrigY; };
      Angle+=dAngle; if (Angle>360) Angle-=360; else if (Angle<-360) Angle+=360;
    }
};

#define NUMBEZS 10
BezierObject *Bezs[NUMBEZS];

void myDisplay(void)
{
  int i;

  // COMPUTE WORLD COORDS OF SITES
  for (i=0; i<NUMBEZS; i++)
    Bezs[i]->ComputeWorldCoords();

  // COMPUTE VORONOI DIAGRAM
  vdCompute(vSites, -1,-1,1,1, 1.415f, FillGeomRatio, Res,Res);

  // DRAW VORONOI SITES
  glColor3f(1,1,1);
  vdDrawSites(vSites, -1,-1,1,1, Res,Res);

  glutSwapBuffers();

  if (AnimationOn)
    for (i=0; i<NUMBEZS; i++)
      Bezs[i]->Animate(-1,-1,1,1);
}

void myReshape(int w, int h)
{
  glViewport(0, 0, w, h);
}

void myMouseFunc(int button, int state, int x, int y)
{
  CtrlPressed = glutGetModifiers() & GLUT_ACTIVE_CTRL;

  if (button==GLUT_LEFT_BUTTON)
  {
    LeftButtonDown=!LeftButtonDown;
    NewX=x; NewY=y;
    vdReadbackID(&iSelectedSite,x,(glutGet((GLenum)GLUT_WINDOW_HEIGHT)-1)-y,vSites);
  }
  else if (button==GLUT_RIGHT_BUTTON && !CtrlPressed)
  {
    RightButtonDown=!RightButtonDown;
  }
  else if (button==GLUT_RIGHT_BUTTON && CtrlPressed)
  {
    RightButtonDown=!RightButtonDown;
  }
}

void myMotionFunc(int x, int y)
{
  if (LeftButtonDown) 
  { 
    OldX=NewX; OldY=NewY;
    NewX=x;    NewY=y;
    float RelX = (NewX-OldX) / (float)glutGet((GLenum)GLUT_WINDOW_WIDTH);
    float RelY = (NewY-OldY) / (float)glutGet((GLenum)GLUT_WINDOW_HEIGHT);
    if (!CtrlPressed)
    {
      Bezs[iSelectedSite]->OrigX += (2.0f*RelX);
      Bezs[iSelectedSite]->OrigY -= (2.0f*RelY);
    }
    else
    {
      Bezs[iSelectedSite]->Angle += (400.0f*RelY);
    }
  }
  else if (RightButtonDown && !CtrlPressed)
  {
  }
  else if (RightButtonDown && CtrlPressed) 
  { 
  }
}

void KeyInputHandler(unsigned char Key, int x, int y)
{
  switch(Key)
  {
    case '\\': AnimationOn=!AnimationOn; break;
    case 27: exit(0);
  };
}

void main(void)
{
  int i;

  // CREATE LIST OF BEZIER OBJECTS
  for (i=0; i<NUMBEZS; i++)
    Bezs[i] = new BezierObject(-0.5f,-0.5f,0.5f,0.5f,-1,-1,1,1, 0.01f,2);

  // CREATE LIST OF VORONOI SITES (LINK SITES TO ANIMATED POINTS)
  vSites = new VoronoiSites();
  VoronoiBezierSite *BezSite;

  for (i=0; i<NUMBEZS; i++)
  {
    BezSite = new VoronoiBezierSite(&(Bezs[i]->wA[0]),&(Bezs[i]->wA[1]),
                                    &(Bezs[i]->wB[0]),&(Bezs[i]->wB[1]),
                                    &(Bezs[i]->wC[0]),&(Bezs[i]->wC[1]),
                                    &(Bezs[i]->wD[0]),&(Bezs[i]->wD[1]),
                                    32);
    vSites->Add(BezSite,i);
  }

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(Res,Res);
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

  glutMainLoop();
}
