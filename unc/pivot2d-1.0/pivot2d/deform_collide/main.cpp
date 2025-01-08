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
#include <time.h>
#include <GL/glut.h>
#include "gltext.hpp"
#include "voronoi.hpp"
#include "voronoi_pixel_error.hpp"
#include "voronoi_sites.hpp"
#include "voronoi_site_polygon.hpp"
#include "voronoi_queries.hpp"
#include "voronoi_draw_gl.hpp"
#include "deformable_body.hpp"
#include "voronoi_collide.hpp"
#include "voronoi_overlap.hpp"

#define RAND() (float)(rand()/(float)RAND_MAX)  // NORMALIZED RAND FUNCTION [0,1]

int ResX=512, ResY=512;
float FillGeomRatio=0.5f;  // IN (0,1), HIGHER VALUES INCREASE FILL REQUIREMENTS AND REDUCE GEOMETRY
VoronoiSites *vSites=NULL;
float DistError;
float MaxDist=2.83f; // sqrt(8.0f);

int FullScreenModeOn=0;
int AnimationOn=1;
int DrawSitesOn=1;
int DrawMinMaxBoxesOn=0;
int DrawOverlappingRegionsOn=0;
int ComputeVoronoiOn=0;
int UseFastClear=1;
int TimerOn=1;
int ShowDepth=1;
int DrawContactPtsOn=0;
int DrawPenetratingPtsOn=0;
int DrawGradientsOn=0;
int DrawBoxesOn=0;
int BoundaryPenetrationPtsOnly=1;
int CollisionResponseOn=0;
int GravOn=1;
int DrawForcesOn=0;
int WhichObject=0; // 0=A, 1=B, 2=BOTH

// NAVIGATION
int LeftButtonDown=0;        // MOUSE STUFF
int RightButtonDown=0;
int CtrlPressed=0;
float OldX,OldY,NewX,NewY;
int iSelectedSite;

DeformableBody* *DBs=NULL;
int NumBodies=2;
int NumPts=4;
float kGrav=0.005f, kDrag=0.05f, kCollide=0.99f, kFriction=0.8f, kSpring=0.1f, kSpringDamp=0.8f;

VoronoiOverlap *VorOverlaps=NULL;
int NumOverlaps=0;

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

void DrawMinMaxOverlaps(DeformableBody* *DBs, int NumDBs)
{
  int i;
  float Amx, Amy, AMx, AMy, Bmx, Bmy, BMx, BMy, mx, my, Mx, My;
  for (i=0; i<(NumDBs-1); i++)
  {
    DBs[i]->ComputeMinMaxBox(&Amx,&Amy,&AMx,&AMy);
    for (int j=i+1; j<NumDBs; j++)
    {
      DBs[j]->ComputeMinMaxBox(&Bmx,&Bmy,&BMx,&BMy);
      if (MinMaxBoxOverlap(Amx,Amy,AMx,AMy,Bmx,Bmy,BMx,BMy,&mx,&my,&Mx,&My))
        DrawMinMaxBox(mx,my,Mx,My);
    }
  }
}

void DrawMinMaxBoxes(DeformableBody* *DBs, int NumDBs)
{
  float mx, my, Mx, My;
  for (int i=0; i<NumDBs; i++)
  {
    DBs[i]->ComputeMinMaxBox(&mx,&my,&Mx,&My);
    DrawMinMaxBox(mx,my,Mx,My);
  }
}

void VoronoiOverlapCallback(float mx, float my, float Mx, float My, VoronoiSite *A, VoronoiSite *B)
{
  if (ComputeVoronoiOn || DrawBoxesOn || DrawGradientsOn || CollisionResponseOn)
  {
    if ((WhichObject==0 || WhichObject==2) || CollisionResponseOn)
    {
      ComputePenetratingPtsWithGradients(A,B,MaxDist,DistError,FillGeomRatio,VorOverlaps[NumOverlaps].APts,
                                         VorOverlaps[NumOverlaps].ADists,VorOverlaps[NumOverlaps].AGrads,
                                         VorOverlaps[NumOverlaps].ANumPts,1,UseFastClear,
                                         VorOverlaps[NumOverlaps].A.mx,VorOverlaps[NumOverlaps].A.my,
                                         VorOverlaps[NumOverlaps].A.Mx,VorOverlaps[NumOverlaps].A.My,
                                         VorOverlaps[NumOverlaps].A.W,VorOverlaps[NumOverlaps].A.H);
      if (ComputeVoronoiOn && VorOverlaps[NumOverlaps].ANumPts>0)
      {
        if (ShowDepth) VorOverlaps[NumOverlaps].A.TexID = vdCreateTextureObjFromDepthBuffer(VorOverlaps[NumOverlaps].A.W,VorOverlaps[NumOverlaps].A.H,1);
        else           VorOverlaps[NumOverlaps].A.TexID = vdCreateTextureObjFromColorBuffer(VorOverlaps[NumOverlaps].A.W,VorOverlaps[NumOverlaps].A.H);
      }
    }
    if ((WhichObject==1 || (WhichObject==2 && VorOverlaps[NumOverlaps].ANumPts>0)) || CollisionResponseOn)
    {
      ComputePenetratingPtsWithGradients(B,A,MaxDist,DistError,FillGeomRatio,VorOverlaps[NumOverlaps].BPts,
                                         VorOverlaps[NumOverlaps].BDists,VorOverlaps[NumOverlaps].BGrads,
                                         VorOverlaps[NumOverlaps].BNumPts,1,UseFastClear,
                                         VorOverlaps[NumOverlaps].B.mx,VorOverlaps[NumOverlaps].B.my,
                                         VorOverlaps[NumOverlaps].B.Mx,VorOverlaps[NumOverlaps].B.My,
                                         VorOverlaps[NumOverlaps].B.W,VorOverlaps[NumOverlaps].B.H);
      if (ComputeVoronoiOn && VorOverlaps[NumOverlaps].BNumPts>0)
      {
        if (ShowDepth) VorOverlaps[NumOverlaps].B.TexID = vdCreateTextureObjFromDepthBuffer(VorOverlaps[NumOverlaps].B.W,VorOverlaps[NumOverlaps].B.H,1);
        else           VorOverlaps[NumOverlaps].B.TexID = vdCreateTextureObjFromColorBuffer(VorOverlaps[NumOverlaps].B.W,VorOverlaps[NumOverlaps].B.H);
      }
    }
  }

  else if (DrawPenetratingPtsOn && !DrawGradientsOn)
  {
    if (BoundaryPenetrationPtsOnly)
    {
      if (WhichObject==0 || WhichObject==2)
        ComputePenetratingPts(A,B,MaxDist,DistError,FillGeomRatio,VorOverlaps[NumOverlaps].APts,
                              VorOverlaps[NumOverlaps].ANumPts,1,UseFastClear);
      if (WhichObject==1 || (WhichObject==2 && VorOverlaps[NumOverlaps].ANumPts>0))
        ComputePenetratingPts(B,A,MaxDist,DistError,FillGeomRatio,VorOverlaps[NumOverlaps].BPts,
                              VorOverlaps[NumOverlaps].BNumPts,1,UseFastClear);
    }
    else // COMPUTE ENTIRE VOLUME OF PENETRATION (SYMMETRIC!)
    {
      ComputePenetratingPts(A,B,MaxDist,DistError,FillGeomRatio,VorOverlaps[NumOverlaps].APts,
                            VorOverlaps[NumOverlaps].ANumPts,0,UseFastClear);
    }
  }

  VorOverlaps[NumOverlaps].SiteA=A;
  VorOverlaps[NumOverlaps].SiteB=B;
  NumOverlaps++;
}

void DrawVoronoiOverlaps(VoronoiOverlap *VorOverlaps, int NumOverlaps)
{
  for (int i=0; i<NumOverlaps; i++)
    VorOverlaps[i].Draw(WhichObject,ComputeVoronoiOn,DrawPenetratingPtsOn,DrawGradientsOn,DrawBoxesOn);
}

void DeleteVoronoiOverlaps(VoronoiOverlap* &VorOverlaps, int &NumOverlaps)
{
  delete[] VorOverlaps;
  VorOverlaps=NULL;
  NumOverlaps=0;
}

// RANDOM POINTS AROUND A CENTRAL POINT WITHIN MAX RADIUS (SIMPLE POLYGONS)
DeformableBody* CreateRandomDeformableBody(float cx, float cy, float r, int NumPts)
{
  DeformableBody *DB = new DeformableBody(NumPts,kGrav,kDrag,kCollide,kFriction,kSpring,kSpringDamp);
  float Ang=6.2831853f*RAND(), AngIncr=6.2831853f/NumPts, R;
  for (int i=0; i<NumPts; i++, Ang+=AngIncr)
  {
    R = r*RAND();
//R=r;
    DB->AddPt(cx+(float)cos(Ang)*R,cy+(float)sin(Ang)*R);
  }
  return(DB);
}

DeformableBody** CreateRandomDeformableBodies(int NumBodies, int NumPts)
{
  DeformableBody* *DBs = new DeformableBody*[NumBodies];
  float Size = 2.0f/NumBodies, R=Size*0.5f;
  float MinX=-1.0f, Cy=1.0f-R;
  for (int i=0; i<NumBodies; i++, MinX+=Size)
    DBs[i] = CreateRandomDeformableBody(MinX+R,Cy,R,NumPts);
  return(DBs);
}

void DeleteDeformableBodies(DeformableBody** &DBs, int NumBodies)
{
  for (int i=0; i<NumBodies; i++)
    delete DBs[i];
  delete[] DBs;
  DBs=NULL;
}

VoronoiSites* CreateVoronoiSites(DeformableBody* *DBs, int NumBodies)
{
  VoronoiSites *vSites = new VoronoiSites();
  VoronoiPolygonSite *PolySite;
  for (int i=0; i<NumBodies; i++)
  {
    PolySite = new VoronoiPolygonSite(DBs[i]->Pts,DBs[i]->NumPts);
    vSites->Add(PolySite);
  }
  return(vSites);
}

void ErrorCheckGL()
{
  GLenum errCode;
  if ((errCode=glGetError()) != GL_NO_ERROR)
    fprintf(stderr,"OpenGL error: %s\n",gluErrorString(errCode));
}

void ApplyCollisionForces(DeformableBody* *DBs, int NumBodies, VoronoiOverlap* VorOverlaps, int NumOverlaps, float kSpring)
{
  float Fx,Fy,D,S;
  for (int i=0; i<NumOverlaps; i++)
  {
    int iA = VorOverlaps[i].SiteA->SiteID;
    int iB = VorOverlaps[i].SiteB->SiteID;
    int j;
    for (j=0; j<VorOverlaps[i].ANumPts*2; j+=2) // APPLY FORCES TO A
    {
      D = VorOverlaps[i].ADists[j/2];
      Fx = -VorOverlaps[i].AGrads[j];
      Fy = -VorOverlaps[i].AGrads[j+1];
      S = D/(float)sqrt(Fx*Fx+Fy*Fy);
      S /= VorOverlaps[i].ANumPts;
      S *= kSpring;
      Fx*=S;
      Fy*=S;
      DBs[iA]->ApplyForceAtPt(VorOverlaps[i].APts[j],VorOverlaps[i].APts[j+1],Fx,Fy);
    }
    for (j=0; j<VorOverlaps[i].BNumPts*2; j+=2) // APPLY FORCES TO B
    {
      D = VorOverlaps[i].BDists[j/2];
      Fx = -VorOverlaps[i].BGrads[j];
      Fy = -VorOverlaps[i].BGrads[j+1];
      S = D/(float)sqrt(Fx*Fx+Fy*Fy);
      S /= VorOverlaps[i].BNumPts;
      S *= kSpring;
      Fx*=S;
      Fy*=S;
      DBs[iB]->ApplyForceAtPt(VorOverlaps[i].BPts[j],VorOverlaps[i].BPts[j+1],Fx,Fy);
    }
  }
}

void myDisplay_Overlaps(void)
{
  int i;
  clock_t StartTime;
  if (TimerOn) StartTime=clock();

  if (VorOverlaps==NULL) VorOverlaps = new VoronoiOverlap[(vSites->NumSites*(vSites->NumSites-1))/2];
  NumOverlaps=0;
  ComputeVoronoiOverlaps(vSites->Sites,vSites->NumSites,MaxDist,DistError,FillGeomRatio,UseFastClear,VoronoiOverlapCallback);

  glClear(GL_COLOR_BUFFER_BIT);
  DrawVoronoiOverlaps(VorOverlaps,NumOverlaps);

  // DRAW VORONOI SITES
  if (DrawSitesOn) { glColor3f(0.75f,0.75f,0.75f); vdDrawSites(vSites, -1,-1,1,1, ResX,ResY); }

  // DRAW BOUNDING BOXES
  if (DrawMinMaxBoxesOn) { glColor3f(0,0,1); DrawMinMaxBoxes(DBs,NumBodies); }

  // DRAW OVERLAPPING REGIONS
  if (DrawOverlappingRegionsOn) { glColor3f(1,0,0); DrawMinMaxOverlaps(DBs,NumBodies); }

  // DRAW FORCES
  if (DrawForcesOn) { glColor3f(1,1,0); for (i=0; i<NumBodies; i++) DBs[i]->DisplayForces(); }

  if (TimerOn) { glColor3f(1,1,1); Text(0,0,"%4.1f fps", (float)CLOCKS_PER_SEC/(clock()-StartTime)); }

  // SIMULATION
  for (i=0; i<NumBodies; i++) DBs[i]->ComputeForces();
  if (CollisionResponseOn) ApplyCollisionForces(DBs,NumBodies,VorOverlaps,NumOverlaps,10);
  for (i=0; i<NumBodies; i++) DBs[i]->TakeEulerStep(0.1f);

  DeleteVoronoiOverlaps(VorOverlaps,NumOverlaps);

  glutSwapBuffers();
}

void myDisplay(void)
{
  for (int i=0; i<NumBodies; i++)
    DBs[i]->Simulate(0.1f);

  clock_t StartTime;
  if (TimerOn) StartTime=clock();

  // COMPUTE VORONOI DIAGRAM
  if (ComputeVoronoiOn)
    vdCompute(vSites, -1,-1,1,1, MaxDist, FillGeomRatio, ResX,ResY, UseFastClear?2:1);
  else
    glClear(GL_COLOR_BUFFER_BIT);

  // COMPUTE CONTACT POINTS
  float *Pts;
  int NumPts;
  if (ComputeVoronoiOn && DrawContactPtsOn)
  {
    ComputeBoundaryContactPts(-1,-1,1,1,ResX,ResY,MaxDist,vdCalcDistError(-1,-1,1,1,ResX,ResY,FillGeomRatio),Pts,NumPts);
    glColor3f(1,0.5f,0.5f);
    glPointSize(3);
  }

  // DRAW DEPTH BUFFER
  if (ComputeVoronoiOn && ShowDepth)
  {
     GLuint TexID = vdCreateTextureObjFromDepthBuffer(ResX,ResY,1);
     vdDrawTextureObj(-1,-1,1,1,TexID,ResX,ResY);
     glDeleteTextures(1,&TexID);
  }

  // DRAW CONTACT POINTS
  if (ComputeVoronoiOn && DrawContactPtsOn)
  {
    glBegin(GL_POINTS);
      for (int i=0; i<NumPts*2; i+=2) glVertex2fv(&(Pts[i]));
    glEnd();
    delete[] Pts;
  }

  // DRAW VORONOI SITES
  if (DrawSitesOn) { glColor3f(0.75f,0.75f,0.75f); vdDrawSites(vSites, -1,-1,1,1, ResX,ResY); }

  // DRAW BOUNDING BOXES
  if (DrawMinMaxBoxesOn) { glColor3f(0,0,1); DrawMinMaxBoxes(DBs,NumBodies); }

  // DRAW OVERLAPPING REGIONS
  if (DrawOverlappingRegionsOn) { glColor3f(1,0,0); DrawMinMaxOverlaps(DBs,NumBodies); }

  if (TimerOn) { glColor3f(1,1,1); Text(0,0,"%4.1f fps", (float)CLOCKS_PER_SEC/(clock()-StartTime)); }

  glutSwapBuffers();
}

void myIdle()
{
  glutPostRedisplay();
  ErrorCheckGL();
}

void myReshape(int w, int h)
{
  glViewport(0, 0, w, h);
  ResX=w;
  ResY=h;

  // COMPUTE DistError BASED ON CURRENT RESOLUTION OF WINDOW SO FULL-SCREEN AND OVERLAP
  // VORONOI REGIONS ARE THE SAME RESOLUTION
  DistError = vdCalcDistError(-1,-1,1,1,ResX,ResY,FillGeomRatio);
//DistError*=2.0f;
}

void Pixel2Eye(float px, float py, float mx, float my, float Mx, float My, float *ex, float *ey)
{
  int VP[4];
  glGetIntegerv(GL_VIEWPORT,VP);
  int W=VP[2], H=VP[3];  
  *ex=mx+(px/W)*(Mx-mx);
  *ey=my+(1.0f-py/H)*(My-my);
}

int SelectSite(float x, float y, VoronoiSite* *vSites, int NumSites)
{
  if (NumSites<1) return(-1);

  int iSelected=0;
  float mx,my,Mx,My, cx,cy, dx,dy, Dist2, MinDist2;
  vSites[0]->CalcMinMax(&mx,&my,&Mx,&My);
  cx=(mx+Mx)*0.5f;  cy=(my+My)*0.5f;
  dx=cx-x;          dy=cy-y;
  MinDist2 = dx*dx+dy*dy;
  for (int i=1; i<NumSites; i++)
  {
    vSites[i]->CalcMinMax(&mx,&my,&Mx,&My);
    cx=(mx+Mx)*0.5f;  cy=(my+My)*0.5f;
    dx=cx-x;          dy=cy-y;
    Dist2 = dx*dx+dy*dy;
    if (Dist2<MinDist2) { MinDist2=Dist2; iSelected=i; }
  }
  return(iSelected);
}

int iClosestPt(float x, float y, float *Pts, int NumPts)  // RETURNS INDEX OF X-COORD OF CLOSEST PT
{
  if (NumPts<1) return(-1);
  float dx=x-Pts[0], dy=y-Pts[1], d2=dx*dx+dy*dy, iC=0, td2;
  for (int i=2; i<NumPts*2; i+=2)
  {
    dx = x-Pts[i];
    dy = y-Pts[i+1];
    td2 = dx*dx+dy*dy;
    if (td2<d2) { d2=td2; iC=i; }
  }
  return(iC);
}

void myMouseFunc(int button, int state, int x, int y)
{
  CtrlPressed = glutGetModifiers() & GLUT_ACTIVE_CTRL;

  if (button==GLUT_LEFT_BUTTON)
  {
    LeftButtonDown=!LeftButtonDown;
    Pixel2Eye(x,y,-1,-1,1,1,&NewX,&NewY);
    iSelectedSite = SelectSite(NewX,NewY,vSites->Sites,vSites->NumSites);
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
    Pixel2Eye(x,y,-1,-1,1,1,&NewX,&NewY);
    float RelX = NewX-OldX;
    float RelY = NewY-OldY;
    if (!CtrlPressed)
    {
      int iC = iClosestPt(NewX,NewY,DBs[iSelectedSite]->Pts,DBs[iSelectedSite]->NumPts);
      DBs[iSelectedSite]->Vels[iC]   = RelX;
      DBs[iSelectedSite]->Vels[iC+1] = RelY;
    }
    else
    {
    }
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
  int i;
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
    case 'C': UseFastClear=!UseFastClear; break;
    case 't': TimerOn=!TimerOn; break;
    case 'B': DrawMinMaxBoxesOn=!DrawMinMaxBoxesOn; break;
    case 'b': DrawBoxesOn=!DrawBoxesOn; break;
    case 'd': ShowDepth=!ShowDepth; break;
    case 'i': DrawContactPtsOn=!DrawContactPtsOn; break;
    case 'p': DrawPenetratingPtsOn=!DrawPenetratingPtsOn; break;
    case 'g': DrawGradientsOn=!DrawGradientsOn; break;
    case 'c': CollisionResponseOn=!CollisionResponseOn; break;
    case 'V': BoundaryPenetrationPtsOnly=!BoundaryPenetrationPtsOnly; break;
    case 'f': DrawForcesOn=!DrawForcesOn; break;
    case 'G': GravOn=!GravOn; 
              for (i=0; i<NumBodies; i++) DBs[i]->kGrav=GravOn?kGrav:0;
              break;
    case '1': WhichObject=(WhichObject+1)%3; break;
    case 27: exit(0);
  };

  if (Key=='+' || Key=='-' || Key=='.' || Key==',')
  {
    DeleteDeformableBodies(DBs,NumBodies);
    switch(Key)
    {
      case '+': NumBodies++; break;
      case '-': NumBodies--; if (NumBodies<=0) NumBodies=1; break;
      case '.': NumPts++; break;
      case ',': NumPts--; if (NumPts<=2) NumPts=2; break;
      case 27: exit(0);
    };
    DBs = CreateRandomDeformableBodies(NumBodies,NumPts);
    delete vSites;
    vSites = CreateVoronoiSites(DBs,NumBodies);
  }

  glutPostRedisplay();
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
  DBs = CreateRandomDeformableBodies(NumBodies,NumPts);
  vSites = CreateVoronoiSites(DBs,NumBodies);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL | GLUT_ACCUM);
  glutInitWindowSize(ResX,ResY);
  glutInitWindowPosition(180,100);
  glutCreateWindow("Kenny's Voronoi-based Collisions");

  glutKeyboardFunc(KeyInputHandler);
  glutReshapeFunc(myReshape);
  glutDisplayFunc(myDisplay_Overlaps);
  glutIdleFunc(myIdle);
  glutMouseFunc(myMouseFunc);
  glutMotionFunc(myMotionFunc);

  glDisable(GL_DEPTH_TEST);

  // DEFAULT STATE FOR VORONOI SYSTEM
  glShadeModel(GL_FLAT);
  glDisable(GL_CULL_FACE);
  glDisable(GL_DITHER);
  glPixelStorei(GL_PACK_ALIGNMENT,1); 
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  
PrintVisualInfo();

  glutMainLoop();

  DeleteDeformableBodies(DBs,NumBodies);
}
