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
#include <voronoi.hpp>
#include <voronoi_collide.hpp>
#include <voronoi_overlap.hpp>
#include <voronoi_sites.hpp>
#include <voronoi_site_polygon.hpp>
#include <voronoi_draw_gl.hpp>
#include <voronoi_pixel_error.hpp>
#include "waves1d.hpp"
#include "follow_object.hpp"
#include "snapshot.hpp"

int ResX=640, ResY=480;
float FillGeomRatio=0.5f;  // IN (0,1), HIGHER VALUES INCREASE FILL REQUIREMENTS AND REDUCE GEOMETRY
float DistError;
float MaxDist=2.83f; // sqrt(8.0f);

int AnimationOn=1;
int WhichObject=0; // 0=A, 1=B, 2=BOTH
int ComputeVoronoiOn=0;
int DrawContactPtsOn=0;
int DrawPenetratingPtsOn=0;
int DrawGradientsOn=0;
int DrawBoxesOn=0;
int BoundaryPenetrationPtsOnly=1;
int DrawMinMaxBoxesOn=0;
int DrawOverlappingRegionsOn=0;
int CollisionResponseOn=0;
int Show3D=1;
int DumpFramesOn=0;

int LeftButtonDown=0;        // MOUSE TRACKBALL STUFF
int RightButtonDown=0;
int OldX,OldY,NewX,NewY;
float Elevation=30;
float Azimuth=-25;

Waves1D *Awaves, *Bwaves;
float *Apts=NULL, *Bpts=NULL;
int Anumpts=0, Bnumpts=0;
float dt=0.05f;

FollowingObject *FollowA=NULL, *FollowB=NULL;

float Acx=-0.38f, Acy=-0.1f, Arad=0.6f, Bcx=0.38f, Bcy=0.1f, Brad=0.6f;

VoronoiOverlap *Overlap;

void DrawMinMaxBox(float mx, float my, float Mx, float My)
{
  glBegin(GL_LINE_LOOP);
    glVertex2f(mx,my); 
    glVertex2f(Mx,my); 
    glVertex2f(Mx,My); 
    glVertex2f(mx,My);
  glEnd();
}

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

void MakeCircles(Waves1D *Awaves, Waves1D *Bwaves, 
                 float Acx, float Acy, float Arad, float Bcx, float Bcy, float Brad, 
                 float* &Apts, int &Anumpts, float* &Bpts, int &Bnumpts)
{
  if (Apts==NULL) { Anumpts=Awaves->N; Apts = new float[Anumpts*2]; }
  if (Bpts==NULL) { Bnumpts=Bwaves->N; Bpts = new float[Bnumpts*2]; }

  float *H,Ang,AngIncr,R;
  int i,k,N;

  // LEFT
  H = Awaves->P;
  N = Awaves->N;
  Ang=0;
  AngIncr=6.2831853f/N;
  for (i=0,k=0; i<N; i++,k+=2, Ang+=AngIncr)
  {
    R = Arad+H[i];
    Apts[k]   = Acx + (float)cos(Ang)*R;
    Apts[k+1] = Acy + (float)sin(Ang)*R;
  }

  // RIGHT
  H = Bwaves->P;
  N = Bwaves->N;
  Ang=0;
  AngIncr=6.2831853f/N;
  for (i=0,k=0; i<N; i++,k+=2, Ang+=AngIncr)
  {
    R = Brad+H[i];
    Bpts[k]   = Bcx + (float)cos(Ang)*R;
    Bpts[k+1] = Bcy + (float)sin(Ang)*R;
  }
}

void DrawWavyObjs(float *Apts, int Anumpts, float *Bpts, int Bnumpts)
{
  int i;
  glBegin(GL_LINE_STRIP);
  for (i=0; i<Anumpts*2; i+=2)
    glVertex2fv(&(Apts[i]));
  glVertex2fv(Apts);
  glEnd();
  glBegin(GL_LINE_STRIP);
  for (i=0; i<Bnumpts*2; i+=2)
    glVertex2fv(&(Bpts[i]));
  glVertex2fv(Bpts);
  glEnd();
}

void VoronoiOverlapCallback(float mx, float my, float Mx, float My, VoronoiSite *A, VoronoiSite *B)
{
  if (ComputeVoronoiOn || DrawBoxesOn || DrawGradientsOn || CollisionResponseOn)
  {
    if ((WhichObject==0 || WhichObject==2) || CollisionResponseOn)
    {
      ComputePenetratingPtsWithGradients(A,B,MaxDist,DistError,FillGeomRatio,Overlap->APts,
                                         Overlap->ADists,Overlap->AGrads,
                                         Overlap->ANumPts,1,1,
                                         Overlap->A.mx,Overlap->A.my,
                                         Overlap->A.Mx,Overlap->A.My,
                                         Overlap->A.W,Overlap->A.H);
      if (ComputeVoronoiOn && Overlap->ANumPts>0)
        Overlap->A.TexID = vdCreateTextureObjFromDepthBuffer(Overlap->A.W,Overlap->A.H,1);
    }
    if ((WhichObject==1 || (WhichObject==2 && Overlap->ANumPts>0)) || CollisionResponseOn)
    {
      ComputePenetratingPtsWithGradients(B,A,MaxDist,DistError,FillGeomRatio,Overlap->BPts,
                                         Overlap->BDists,Overlap->BGrads,
                                         Overlap->BNumPts,1,1,
                                         Overlap->B.mx,Overlap->B.my,
                                         Overlap->B.Mx,Overlap->B.My,
                                         Overlap->B.W,Overlap->B.H);
      if (ComputeVoronoiOn && Overlap->BNumPts>0)
        Overlap->B.TexID = vdCreateTextureObjFromDepthBuffer(Overlap->B.W,Overlap->B.H,1);
    }
  }

  else if (DrawPenetratingPtsOn && !DrawGradientsOn)
  {
    if (BoundaryPenetrationPtsOnly)
    {
      if (WhichObject==0 || WhichObject==2)
        ComputePenetratingPts(A,B,MaxDist,DistError,FillGeomRatio,Overlap->APts,
                              Overlap->ANumPts,1,1);
      if (WhichObject==1 || (WhichObject==2 && Overlap->ANumPts>0))
        ComputePenetratingPts(B,A,MaxDist,DistError,FillGeomRatio,Overlap->BPts,
                              Overlap->BNumPts,1,1);
    }
    else // COMPUTE ENTIRE VOLUME OF PENETRATION (SYMMETRIC!)
    {
      ComputePenetratingPts(A,B,MaxDist,DistError,FillGeomRatio,Overlap->APts,
                            Overlap->ANumPts,0,1);
    }
  }

  Overlap->SiteA=A;
  Overlap->SiteB=B;
}

void ApplyCollisionForces(Waves1D *Awaves, Waves1D *Bwaves,
                          float Acx, float Acy, float Arad, float Bcx, float Bcy, float Brad, 
                          VoronoiOverlap* Overlap, float dt)
{
  int j;
  float Px,Py,Fx,Fy,Cx,Cy,D,S;
  for (j=0; j<Overlap->ANumPts*2; j+=2) // APPLY FORCES TO A
  {
    D  = Overlap->ADists[j/2];
    Px = Overlap->APts[j];
    Py = Overlap->APts[j+1];
    Fx = -Overlap->AGrads[j];
    Fy = -Overlap->AGrads[j+1];
    S = D/(float)sqrt(Fx*Fx+Fy*Fy);
    Fx*=S;
    Fy*=S;
    Cx = Acx-Px;
    Cy = Acy-Py;
    S = 1.0f/(float)sqrt(Cx*Cx+Cy*Cy);
    Cx*=S;
    Cy*=S;
    S = (Fx*Cx+Fy*Cy)*dt;
    if (S<0) S=0;
    float Ang = (float)atan2(Py-Acy,Px-Acx);
    if (Ang<0) Ang+=6.2831853f;
    float t = Ang/6.2831853f;
    int k=(int)(t*Awaves->N);
    int km1 = (k-1<0) ? k-1+Awaves->N : k-1;
    int kp1 = (k+1)%Awaves->N;
    Awaves->P[k]-=S;
    Awaves->P[km1]-=(S*0.5f);
    Awaves->P[kp1]-=(S*0.5f);
  }
  for (j=0; j<Overlap->BNumPts*2; j+=2) // APPLY FORCES TO A
  {
    D  = Overlap->BDists[j/2];
    Px = Overlap->BPts[j];
    Py = Overlap->BPts[j+1];
    Fx = -Overlap->BGrads[j];
    Fy = -Overlap->BGrads[j+1];
    S = D/(float)sqrt(Fx*Fx+Fy*Fy);
    Fx*=S;
    Fy*=S;
    Cx = Bcx-Px;
    Cy = Bcy-Py;
    S = 1.0f/(float)sqrt(Cx*Cx+Cy*Cy);
    Cx*=S;
    Cy*=S;
    S = (Fx*Cx+Fy*Cy)*dt;
    if (S<0) S=0;
    float Ang = (float)atan2(Py-Bcy,Px-Bcx);
    if (Ang<0) Ang+=6.2831853f;
    float t = Ang/6.2831853f;
    int k=(int)(t*Bwaves->N);
    int km1 = (k-1<0) ? k-1+Bwaves->N : k-1;
    int kp1 = (k+1)%Bwaves->N;
    Bwaves->P[k]-=S;
    Bwaves->P[km1]-=(S*0.5f);
    Bwaves->P[kp1]-=(S*0.5f);
  }
}

void DrawNonconvexPoly(float *Pts, int NumPts, float Z) 
{ 
  int i,j,k;
  GLUtesselator *tobj = gluNewTess();
  double *pts = new double[NumPts*3];
  for (j=0,k=0; j<NumPts*2; j+=2,k+=3)
    { pts[k]=Pts[j]; pts[k+1]=Pts[j+1]; pts[k+2]=Z; }
  gluTessNormal(tobj,0,0,1);
  gluTessCallback(tobj,GLU_TESS_VERTEX,(GLvoid (CALLBACK *)(void))glVertex3dv);
  gluTessCallback(tobj,GLU_TESS_BEGIN,(GLvoid (CALLBACK *)(void))glBegin);
  gluTessCallback(tobj,GLU_TESS_END,glEnd);

  gluTessBeginPolygon(tobj,0);
    gluTessBeginContour(tobj);
      for (i=0; i<NumPts*3; i+=3)
        gluTessVertex(tobj,&pts[i],&pts[i]);
    gluTessEndContour(tobj);
  gluTessEndPolygon(tobj);

  gluDeleteTess(tobj);
  delete[] pts;
}

void DrawExtrudedObj(float *A, float *B, int N, float MinZ, float MaxZ)
{
  float Height = MaxZ-MinZ;
  int ip,i_,in,N2=N*2;
  float u[2],v[2],n[3];
  glBegin(GL_QUAD_STRIP);
    for (int i=0; i<=N2; i+=2) 
    { 
      i_=i%N2;
      ip=i-2; if (ip<0) ip+=N2;
      in=(i+2)%N2;
      v[0]=A[i_]-B[i_];
      v[1]=A[i_+1]-B[i_+1];
      u[0]=B[in]-B[ip];
      u[1]=B[in+1]-B[ip+1];
      n[0]=Height*u[1];
      n[1]=-Height*u[0];
      n[2]=v[1]*u[0]-v[0]*u[1];
      glNormal3fv(n);
      glVertex3f(B[i_],B[i_+1],MaxZ); 
      u[0]=A[in]-A[ip];
      u[1]=A[in+1]-A[ip+1];
      n[0]=Height*u[1];
      n[1]=-Height*u[0];
      n[2]=v[1]*u[0]-v[0]*u[1];
      glNormal3fv(n);
      glVertex3f(A[i_],A[i_+1],MinZ); 
    }
  glEnd();

  glFrontFace(GL_CW);
  glNormal3f(0,0,-1);
  DrawNonconvexPoly(A,N,MinZ);

  glFrontFace(GL_CCW);
  glNormal3f(0,0,1);
  DrawNonconvexPoly(B,N,MaxZ);
}

void ErrorCheckGL()
{
  GLenum errCode;
  if ((errCode=glGetError()) != GL_NO_ERROR)
    fprintf(stderr,"OpenGL error: %s\n",gluErrorString(errCode));
}

void myDisplay2D()
{
  float Aspect=(float)ResY/ResX;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1,1,-Aspect,Aspect);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  MakeCircles(Awaves,Bwaves,Acx,Acy,Arad,Bcx,Bcy,Brad,Apts,Anumpts,Bpts,Bnumpts);

  VoronoiSites *vSites = new VoronoiSites();
  vSites->Add(new VoronoiPolygonSite(Apts,Anumpts));
  vSites->Add(new VoronoiPolygonSite(Bpts,Bnumpts));

  Overlap = new VoronoiOverlap;
  ComputeVoronoiOverlaps(vSites->Sites,vSites->NumSites,MaxDist,DistError,FillGeomRatio,1,VoronoiOverlapCallback);

  if (CollisionResponseOn)
    ApplyCollisionForces(Awaves, Bwaves, Acx,Acy,Arad,Bcx,Bcy,Brad, Overlap,dt);

  glClear(GL_COLOR_BUFFER_BIT);

  float Amx,Amy,AMx,AMy,Bmx,Bmy,BMx,BMy;
  if (DrawMinMaxBoxesOn || DrawOverlappingRegionsOn)
  {
    vSites->Sites[0]->CalcMinMax(&Amx,&Amy,&AMx,&AMy);
    vSites->Sites[1]->CalcMinMax(&Bmx,&Bmy,&BMx,&BMy);
    if (DrawMinMaxBoxesOn)
    {
      glColor3f(0.5f,0.5f,0.5f);
      DrawMinMaxBox(Amx,Amy,AMx,AMy);
      DrawMinMaxBox(Bmx,Bmy,BMx,BMy);
    }
    if (DrawOverlappingRegionsOn)
    {
      float mx,my,Mx,My;
      if (MinMaxBoxOverlap(Amx,Amy,AMx,AMy,Bmx,Bmy,BMx,BMy,&mx,&my,&Mx,&My))
      {
        glColor3f(1,0,0);
        DrawMinMaxBox(mx,my,Mx,My);
      }
    }
  }

  Overlap->Draw(WhichObject,ComputeVoronoiOn,DrawPenetratingPtsOn,DrawGradientsOn,DrawBoxesOn);

  delete Overlap;
  delete vSites;

  glColor3f(1,1,1);
  DrawWavyObjs(Apts,Anumpts,Bpts,Bnumpts);

  glutSwapBuffers();
ErrorCheckGL();
}

void myDisplay3D()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45,(float)ResX/(float)ResY,0.01,10);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0,-2,0, 0,0,0, 0,0,1);  

  MakeCircles(Awaves,Bwaves,Acx,Acy,Arad,Bcx,Bcy,Brad,Apts,Anumpts,Bpts,Bnumpts);
  if (FollowA==NULL && FollowB==NULL)
  { 
    FollowA = new FollowingObject(Apts,Anumpts);
    FollowB = new FollowingObject(Bpts,Bnumpts);
  }

  VoronoiSites *vSites = new VoronoiSites();
  vSites->Add(new VoronoiPolygonSite(Apts,Anumpts));
  vSites->Add(new VoronoiPolygonSite(Bpts,Bnumpts));

  Overlap = new VoronoiOverlap;
  ComputeVoronoiOverlaps(vSites->Sites,vSites->NumSites,MaxDist,DistError,FillGeomRatio,1,VoronoiOverlapCallback);

  if (CollisionResponseOn)
    ApplyCollisionForces(Awaves, Bwaves, Acx,Acy,Arad,Bcx,Bcy,Brad, Overlap,dt);

  delete Overlap;
  delete vSites;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glRotatef(Elevation,1,0,0);
  glRotatef(Azimuth,0,0,1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

      glCullFace(GL_FRONT);
      glColor4f(0.8f,0.5f,0.3f,0.5f);
      DrawExtrudedObj(Apts,FollowA->FollowPts,Anumpts,0,0.35f);
      glColor4f(0.5f,0.8f,0.3f,0.5f);
      DrawExtrudedObj(Bpts,FollowB->FollowPts,Bnumpts,-0.1f,0.3f);

      glCullFace(GL_BACK);
      glColor4f(0.8f,0.5f,0.3f,0.75f);
      DrawExtrudedObj(Apts,FollowA->FollowPts,Anumpts,0,0.35f);
      glColor4f(0.5f,0.8f,0.3f,0.75f);
      DrawExtrudedObj(Bpts,FollowB->FollowPts,Bnumpts,-0.1f,0.3f);

    glDisable(GL_BLEND);

    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_NORMALIZE);
    glShadeModel(GL_FLAT);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  glutSwapBuffers();
ErrorCheckGL();
}

void myReshape(int w, int h)
{
  glViewport(0, 0, w, h);
  ResX=w;
  ResY=h;

  // COMPUTE DistError BASED ON CURRENT RESOLUTION OF WINDOW SO FULL-SCREEN AND OVERLAP
  // VORONOI REGIONS ARE THE SAME RESOLUTION
  float Aspect=(float)ResY/ResX;
  DistError = vdCalcDistError(-1,-Aspect,1,Aspect,ResX,ResY,FillGeomRatio);
DistError*=2.0f;
}

void myIdle()
{
  Awaves->Simulate(dt);
  Bwaves->Simulate(dt);
  if (Show3D && FollowA && FollowB) { FollowA->TakeStep(0.1f,dt); FollowB->TakeStep(0.1f,dt); }
  glutPostRedisplay();
  if (DumpFramesOn) SnapShot();
}

void myMouseFunc(int button, int state, int x, int y)
{
  if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
  {
    float X = ((float)x / glutGet((GLenum)GLUT_WINDOW_WIDTH))*2.0f - 1.0f;
    float Y = (1.0f - ((float)y / glutGet((GLenum)GLUT_WINDOW_HEIGHT)))*2.0f - 1.0f;
    if (X<0)
    {
      X+=0.5f;
      float Ang = (float)atan2(Y,X);
      if (Ang<0) Ang+=6.2831853f;
      float t = Ang/6.2831853f;
      Awaves->MakeBump((int)(t*Awaves->N),10,0.3f);
    }
    else
    {
      X-=0.5f;
      float Ang = (float)atan2(Y,X);
      if (Ang<0) Ang+=6.2831853f;
      float t = Ang/6.2831853f;
      Bwaves->MakeBump((int)(t*Bwaves->N),10,0.3f);
    }
  }
}

void myMouseFunc3d(int button, int state, int x, int y)
{
  NewX=x; NewY=y;
  if (button==GLUT_LEFT_BUTTON)
    LeftButtonDown=!LeftButtonDown;
  else if (button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    myMouseFunc(GLUT_LEFT_BUTTON,GLUT_DOWN,x,y);
}

void myMotionFunc3d(int x, int y)
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

void KeyInputHandler(unsigned char Key, int x, int y)
{
  switch(Key)
  {
    case '\\': AnimationOn=!AnimationOn;
      if (AnimationOn) glutIdleFunc(myIdle); else glutIdleFunc(0); break;
    case 'v': ComputeVoronoiOn=!ComputeVoronoiOn; break;
    case 'b': DrawBoxesOn=!DrawBoxesOn; break;
    case 'i': DrawContactPtsOn=!DrawContactPtsOn; break;
    case 'p': DrawPenetratingPtsOn=!DrawPenetratingPtsOn; break;
    case 'g': DrawGradientsOn=!DrawGradientsOn; break;
    case 'V': BoundaryPenetrationPtsOnly=!BoundaryPenetrationPtsOnly; break;
    case '1': WhichObject=(WhichObject+1)%3; break;
    case 'B': DrawMinMaxBoxesOn=!DrawMinMaxBoxesOn; break;
    case 'r': DrawOverlappingRegionsOn=!DrawOverlappingRegionsOn; break;
    case 'c': CollisionResponseOn=!CollisionResponseOn; break;
    case '-': Arad-=0.01f; Brad-=0.01f; break;
    case '+': Arad+=0.01f; Brad+=0.01f; break;
    case 'R': delete Awaves; delete Bwaves;
      Awaves = new Waves1D(100,0.01f,1);
      Bwaves = new Waves1D(100,0.01f,1);
      break;
    case '3': Show3D=!Show3D;
      if (Show3D) { glutDisplayFunc(myDisplay3D); glutMouseFunc(myMouseFunc3d); glutMotionFunc(myMotionFunc3d); }
      else        { glutDisplayFunc(myDisplay2D); glutMouseFunc(myMouseFunc);   glutMotionFunc(0); }
      break;
    case '`': SnapShot(); break;
    case '~': DumpFramesOn=!DumpFramesOn; break;
    case '/': WhichObject=0;                 // RESET TO DEFAULT STATE
              ComputeVoronoiOn=0;
              DrawContactPtsOn=0;
              DrawPenetratingPtsOn=0;
              DrawGradientsOn=0;
              DrawBoxesOn=0;
              BoundaryPenetrationPtsOnly=1;
              DrawMinMaxBoxesOn=0;
              DrawOverlappingRegionsOn=0;
              CollisionResponseOn=0;
              break;
    case 27: exit(0);
  };
  glutPostRedisplay();
}

void main(void)
{
  Awaves = new Waves1D(100,0.01f,1);
  Bwaves = new Waves1D(100,0.01f,1);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
  glutInitWindowSize(ResX,ResY);
  glutInitWindowPosition(180,100);
  glutCreateWindow("Kenny's Wavy Circles");

  glutReshapeFunc(myReshape);
  glutIdleFunc(myIdle);
  glutKeyboardFunc(KeyInputHandler);
  if (Show3D) { glutDisplayFunc(myDisplay3D); glutMouseFunc(myMouseFunc3d); glutMotionFunc(myMotionFunc3d); }
  else        { glutDisplayFunc(myDisplay2D); glutMouseFunc(myMouseFunc);   glutMotionFunc(0); }

  // DEFAULT STATE FOR VORONOI SYSTEM
  glShadeModel(GL_FLAT);
  glDisable(GL_CULL_FACE);
  glDisable(GL_DITHER);
  glPixelStorei(GL_PACK_ALIGNMENT,1); 
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);

  glutMainLoop();
}
