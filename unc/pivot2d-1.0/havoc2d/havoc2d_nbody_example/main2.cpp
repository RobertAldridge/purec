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
#include <time.h>
#include <GL/glut.h>
#include "gltext.hpp"
#include "voronoi.hpp"
#include "voronoi_pixel_error.hpp"
#include "voronoi_sites.hpp"
#include "voronoi_site_polygon.hpp"
#include "voronoi_queries.hpp"
#include "voronoi_draw_gl.hpp"
#include "polygon_object.hpp"

#define RAND() (float)(rand()/(float)RAND_MAX)             // NORMALIZED RAND FUNCTION [0,1]

int ResX=512, ResY=512;
float FillGeomRatio=0.5f;  // IN (0,1), HIGHER VALUES INCREASE FILL REQUIREMENTS AND REDUCE GEOMETRY
VoronoiSites *vSites=NULL;
float DistError;
float MaxDist=2.83f; // sqrt(8.0f);
//float MaxDist=0.1f;

int FullScreenModeOn=1;
int AnimationOn=1;
int DrawSitesOn=1;
int DrawMinMaxBoxesOn=0;
int DrawOverlappingRegionsOn=0;
int ComputeVoronoiOn=1;
int UseFastClear=1;
int TimerOn=1;
int ShowDepth=0;

// NAVIGATION
int LeftButtonDown=0;        // MOUSE STUFF
int RightButtonDown=0;
int CtrlPressed=0;
int OldX,OldY,NewX,NewY;
int iSelectedSite;

#define NUMPOLYS 5
PolygonObject *Polys[NUMPOLYS];

struct VoronoiOverlap
{
  GLuint TexID;
  float mx, my, Mx, My;
  int ResX, ResY;
};

void DrawMinMaxBox(float mx, float my, float Mx, float My)
{
  glBegin(GL_LINE_LOOP);
    glVertex2f(mx,my); 
    glVertex2f(Mx,my); 
    glVertex2f(Mx,My); 
    glVertex2f(mx,My);
  glEnd();
}

// OVERLAPPING MIN/MAX BOX WILL BE MIN = max of mins, MAX = min of maxs
// IF MIN/MAX DOES NOT FORM A VALID MIN/MAX BOX (MAX<MIN), THEN A AND B DO NOT OVERLAP
// IF 0 IS RETURNED, (mx,my,Mx,My) IS INVALID
static inline int MinMaxBoxOverlap(const float Amx, const float Amy, const float AMx, const float AMy,
                                   const float Bmx, const float Bmy, const float BMx, const float BMy,
                                   float *mx, float *my, float *Mx, float *My)
{
  *mx = (Amx>Bmx)?Amx:Bmx;
  *Mx = (AMx<BMx)?AMx:BMx;
  if (*Mx<*mx) return(0);
  *my = (Amy>Bmy)?Amy:Bmy;
  *My = (AMy<BMy)?AMy:BMy;
  if (*My<*my) return(0);
  return(1);
}

void DrawMinMaxOverlaps(PolygonObject* *Polys, int NumPolys)
{
  int i;
  float Amx, Amy, AMx, AMy, Bmx, Bmy, BMx, BMy, mx, my, Mx, My;
  for (i=0; i<(NumPolys-1); i++)
  {
    Polys[i]->ComputeMinMaxBox(&Amx,&Amy,&AMx,&AMy);
    for (int j=i+1; j<NumPolys; j++)
    {
      Polys[j]->ComputeMinMaxBox(&Bmx,&Bmy,&BMx,&BMy);
      if (MinMaxBoxOverlap(Amx,Amy,AMx,AMy,Bmx,Bmy,BMx,BMy,&mx,&my,&Mx,&My))
        DrawMinMaxBox(mx,my,Mx,My);
    }
  }
}

void DrawMinMaxBoxes(PolygonObject* *Polys, int NumPolys)
{
  float mx, my, Mx, My;
  for (int i=0; i<NumPolys; i++)
  {
    Polys[i]->ComputeMinMaxBox(&mx,&my,&Mx,&My);
    DrawMinMaxBox(mx,my,Mx,My);
  }
}

void ComputeVoronoiOverlaps(VoronoiSites* vSites, PolygonObject* *Polys, int NumPolys,
                            VoronoiOverlap* &VorOverlaps, int &NumOverlaps, int ReadDepth=0)
{
  int i;

  if (VorOverlaps==NULL) VorOverlaps = new VoronoiOverlap[NumPolys*NumPolys];
  NumOverlaps=0;

  float Amx, Amy, AMx, AMy, Bmx, Bmy, BMx, BMy, mx, my, Mx, My;
  for (i=0; i<(NumPolys-1); i++)
  {
    Polys[i]->ComputeMinMaxBox(&Amx,&Amy,&AMx,&AMy);
    for (int j=i+1; j<NumPolys; j++)
    {
      Polys[j]->ComputeMinMaxBox(&Bmx,&Bmy,&BMx,&BMy);
      if (MinMaxBoxOverlap(Amx,Amy,AMx,AMy,Bmx,Bmy,BMx,BMy,&mx,&my,&Mx,&My))
      {
        VoronoiSites* tmp_vSites = new VoronoiSites();
        tmp_vSites->Add(vSites->Sites[i],vSites->Sites[i]->SiteID);
        tmp_vSites->Add(vSites->Sites[j],vSites->Sites[j]->SiteID);

        vdCompute(tmp_vSites, mx,my,Mx,My, MaxDist, DistError,FillGeomRatio, 
                  &(VorOverlaps[NumOverlaps].ResX), &(VorOverlaps[NumOverlaps].ResY),UseFastClear?2:1);
        if (ReadDepth)
          VorOverlaps[NumOverlaps].TexID = vdCreateTextureObjFromDepthBuffer(VorOverlaps[NumOverlaps].ResX,VorOverlaps[NumOverlaps].ResY,GL_CLAMP,GL_NEAREST,1);
        else
          VorOverlaps[NumOverlaps].TexID = vdCreateTextureObjFromColorBuffer(VorOverlaps[NumOverlaps].ResX,VorOverlaps[NumOverlaps].ResY,GL_CLAMP,GL_NEAREST);
        VorOverlaps[NumOverlaps].mx=mx;
        VorOverlaps[NumOverlaps].my=my;
        VorOverlaps[NumOverlaps].Mx=Mx;
        VorOverlaps[NumOverlaps].My=My;
        NumOverlaps++;

        tmp_vSites->NumSites=0;
        delete tmp_vSites;
      }
    }
  }
}

void DrawVoronoiOverlaps(VoronoiOverlap *VorOverlaps, int NumOverlaps)
{
  for (int i=0; i<NumOverlaps; i++)
    vdDrawTextureObj(VorOverlaps[i].mx,VorOverlaps[i].my,VorOverlaps[i].Mx,VorOverlaps[i].My,
                     VorOverlaps[i].TexID,VorOverlaps[i].ResX,VorOverlaps[i].ResY);
}

void DeleteVoronoiOverlaps(VoronoiOverlap* &VorOverlaps, int &NumOverlaps)
{
  for (int i=0; i<NumOverlaps; i++)
    glDeleteTextures(1,&(VorOverlaps[i].TexID));
  delete[] VorOverlaps;
  VorOverlaps=NULL;
  NumOverlaps=0;
}

void Pixel2Eye(float px, float py, float *ex, float *ey)
{
  int VP[4];
  glGetIntegerv(GL_VIEWPORT,VP);
  int W=VP[2], H=VP[3];  
  *ex=(px/W)*2.0f-1.0f;
  *ey=(1.0f-py/H)*2.0f-1.0f;
}

int SelectSite(float px, float py, PolygonObject* *Polys, int NumPolys)
{
  if (NumPolys<1) return(-1);

  float ex,ey;
  Pixel2Eye(px,py,&ex,&ey);

  int iSelected=0;
  float mx, my, Mx, My, cx, cy, dx, dy, Dist2, MinDist2;
  Polys[0]->ComputeMinMaxBox(&mx,&my,&Mx,&My);
  cx=(mx+Mx)*0.5f;   cy=(my+My)*0.5f;
  dx=cx-ex;          dy=cy-ey;
  MinDist2 = dx*dx+dy*dy;
  for (int i=1; i<NumPolys; i++)
  {
    Polys[i]->ComputeMinMaxBox(&mx,&my,&Mx,&My);
    cx=(mx+Mx)*0.5f;   cy=(my+My)*0.5f;
    dx=cx-ex;          dy=cy-ey;
    Dist2 = dx*dx+dy*dy;
    if (Dist2<MinDist2) { MinDist2=Dist2; iSelected=i; }
  }
  return(iSelected);
}

void ErrorCheckGL()
{
  GLenum errCode;
  if ((errCode=glGetError()) != GL_NO_ERROR)
    fprintf(stderr,"OpenGL error: %s\n",gluErrorString(errCode));
}

void myDisplay_Overlaps(void)
{
  clock_t StartTime;
  if (TimerOn) StartTime=clock();

  VoronoiOverlap *VorOverlaps=NULL;
  int NumOverlaps=0;
  ComputeVoronoiOverlaps(vSites,Polys,NUMPOLYS,VorOverlaps,NumOverlaps,ShowDepth);

  glClear(GL_COLOR_BUFFER_BIT);
  DrawVoronoiOverlaps(VorOverlaps,NumOverlaps);
  DeleteVoronoiOverlaps(VorOverlaps,NumOverlaps);

  // DRAW VORONOI SITES
  if (DrawSitesOn)
  {
    glColor3f(0.75f,0.75f,0.75f);
    vdDrawSites(vSites, -1,-1,1,1, ResX,ResY);
  }

  // DRAW BOUNDING BOXES
  if (DrawMinMaxBoxesOn)
  {
    glColor3f(0,0,1);
    DrawMinMaxBoxes(Polys,NUMPOLYS);
  }

  if (TimerOn) { glColor3f(1,1,1); Text(0,0,"%4.1f fps", (float)CLOCKS_PER_SEC/(clock()-StartTime)); }

  glutSwapBuffers();
ErrorCheckGL();
}

void myDisplay(void)
{
  clock_t StartTime;
  if (TimerOn) StartTime=clock();

  int i;

  // COMPUTE WORLD COORDS OF SITES
  for (i=0; i<NUMPOLYS; i++)
    Polys[i]->UpdateWorldPts();

  // COMPUTE VORONOI DIAGRAM
  if (ComputeVoronoiOn)
    vdCompute(vSites, -1,-1,1,1, MaxDist, FillGeomRatio, ResX,ResY, UseFastClear?2:1);
  else
    glClear(GL_COLOR_BUFFER_BIT);

  // DRAW VORONOI SITES
  if (DrawSitesOn)
  {
    glColor3f(0.75f,0.75f,0.75f);
    vdDrawSites(vSites, -1,-1,1,1, ResX,ResY);
  }

  // DRAW BOUNDING BOXES
  if (DrawMinMaxBoxesOn)
  {
    glColor3f(0,0,1);
    DrawMinMaxBoxes(Polys,NUMPOLYS);
  }

  // DRAW OVERLAPPING REGIONS
  if (DrawOverlappingRegionsOn)
  {
    glColor3f(1,0,0);
    DrawMinMaxOverlaps(Polys,NUMPOLYS);
  }

  if (TimerOn) { glColor3f(1,1,1); Text(0,0,"%4.1f fps", (float)CLOCKS_PER_SEC/(clock()-StartTime)); }

  glutSwapBuffers();
ErrorCheckGL();
}

void myIdle()
{
  for (int i=0; i<NUMPOLYS; i++)
    Polys[i]->Animate(-1,-1,1,1);
  glutPostRedisplay();
}

void myReshape(int w, int h)
{
  glViewport(0, 0, w, h);
  ResX=w;
  ResY=h;

  // COMPUTE DistError BASED ON CURRENT RESOLUTION OF WINDOW SO FULL-SCREEN AND OVERLAP
  // VORONOI REGIONS ARE THE SAME RESOLUTION
  DistError = vdCalcDistError(-1,-1,1,1,ResX,ResY,FillGeomRatio);
}

void myMouseFunc(int button, int state, int x, int y)
{
  CtrlPressed = glutGetModifiers() & GLUT_ACTIVE_CTRL;

  if (button==GLUT_LEFT_BUTTON)
  {
    LeftButtonDown=!LeftButtonDown;
    NewX=x; NewY=y;
//    vdReadbackID(&iSelectedSite,x,(glutGet((GLenum)GLUT_WINDOW_HEIGHT)-1)-y,vSites);
    iSelectedSite = SelectSite(x,y,Polys,NUMPOLYS);
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
      Polys[iSelectedSite]->OrigX += (2.0f*RelX);
      Polys[iSelectedSite]->OrigY -= (2.0f*RelY);
    }
    else
    {
      Polys[iSelectedSite]->Angle += (400.0f*RelY);
    }
    Polys[iSelectedSite]->WorldPtsUpdated=0;
  }
  else if (RightButtonDown && !CtrlPressed)
  {
  }
  else if (RightButtonDown && CtrlPressed) 
  { 
  }
  glutPostRedisplay();
}

void KeyInputHandler(unsigned char Key, int x, int y)
{
  switch(Key)
  {
    case '`': DrawSitesOn=!DrawSitesOn; break;
    case '\\': AnimationOn=!AnimationOn; 
               if (AnimationOn) glutIdleFunc(myIdle); else glutIdleFunc(0);
               break;
    case ' ': FullScreenModeOn=!FullScreenModeOn;
      if (FullScreenModeOn)
        glutDisplayFunc(myDisplay);
      else
        glutDisplayFunc(myDisplay_Overlaps);
      break;
    case 'r': DrawOverlappingRegionsOn=!DrawOverlappingRegionsOn; break;
    case 'v': ComputeVoronoiOn=!ComputeVoronoiOn; break;
    case 'c': UseFastClear=!UseFastClear; break;
    case 't': TimerOn=!TimerOn; break;
    case 'b': DrawMinMaxBoxesOn=!DrawMinMaxBoxesOn; break;
    case 'd': ShowDepth=!ShowDepth; break;
    case 27: exit(0);
  };
  glutPostRedisplay();
}

void main(void)
{
  int i;

  // CREATE LIST OF POLYGON OBJECTS
  for (i=0; i<NUMPOLYS; i++)
    Polys[i] = new PolygonObject(-0.3f,-0.3f,0.3f,0.3f,-1,-1,1,1, RAND()*10+3,0.01f,2);

  // CREATE LIST OF VORONOI SITES (LINK SITES TO ANIMATED POINTS)
  vSites = new VoronoiSites();
  VoronoiPolygonSite *PolySite;

  for (i=0; i<NUMPOLYS; i++)
  {
    PolySite = new VoronoiPolygonSite(Polys[i]->wPts,Polys[i]->NumPts);
    vSites->Add(PolySite);
  }

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(ResX,ResY);
  glutInitWindowPosition(180,100);
  glutCreateWindow("Kenny's Voronoi-based Collisions");

  glutKeyboardFunc(KeyInputHandler);
  glutReshapeFunc(myReshape);
  glutDisplayFunc(myDisplay);
  glutIdleFunc(myIdle);
  glutMouseFunc(myMouseFunc);
  glutMotionFunc(myMotionFunc);

  glShadeModel(GL_FLAT);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glDisable(GL_DITHER);

  glutMainLoop();
}
