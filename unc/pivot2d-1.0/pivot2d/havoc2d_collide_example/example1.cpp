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

// SIMPLE EXAMPLE USING HAVOC2D_COLLIDE (PIVOT2D) SYSTEM
// Kenneth E. Hoff III
// 5/2/2001

#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <voronoi_collide.hpp>

// TWO 2D POLYGON OBJECTS AS A PACKED ARRAY OF FLOATS
float Pts0[]={ -0.7f,-0.8f, 0.5f,-0.8f, -0.1f,0 };
int NumPts0=3;
float Pts1[]={ -0.5f,-0.3f, 0.5f,-0.3f, 0.5f,0.7f, -0.5f,0.7f };
int NumPts1=4;

void DrawPolygon(float *Pts, int NumPts)
{
  glBegin(GL_LINE_LOOP);
  for (int i=0; i<NumPts*2; i+=2)
    glVertex2fv(&(Pts[i]));
  glEnd();
}

void myDisplay(void)
{
  float *Pts=NULL, *Dists=NULL, *Grads=NULL, MinX, MinY, MaxX, MaxY;
  int NumPts, PixelWidth, PixelHeight;

  ComputePenetratingPtsWithGradients(Pts0,NumPts0,Pts1,NumPts1,  // TWO POLYGON OBJECTS
                                     1.0f,0.01f,0.5f,             // MAXDIST, DISTERROR, FILLGEOMRATIO
                                     Pts,Dists,Grads,NumPts,     // COMPUTED PENETRATING PTS, DISTS, GRADIENTS
                                     1,1,                        // ONLY BOUNDARY INTERSECTIONS, USE FAST CLEAR
                                     MinX,MinY,MaxX,MaxY,        // OBJECT-SPACE WINDOW CONTAINING INTERSECTION
                                     PixelWidth,PixelHeight);    // RESOLUTION OF BUFFER USED TO PERFORM QUERY


  glClear(GL_COLOR_BUFFER_BIT);

  int j;

  // DRAW THE WINDOW CONTAINING THE INTERSECTION POINTS
  glColor3f(0.2f,0.2f,0.2f);
  glRectf(MinX,MinY,MaxX,MaxY);

  // DRAW THE OBJECTS
  glColor3f(1,1,1);
  DrawPolygon(Pts0,NumPts0);
  DrawPolygon(Pts1,NumPts1);

  // GRADIENTS DRAWN WITH THE LENGTH EQUAL TO THE PENETRATION DISTANCE
  glColor3f(0.5f,0.3f,0.7f);
  glBegin(GL_LINES);
  for (j=0; j<NumPts*2; j+=6)
  {
    glVertex2fv(&(Pts[j]));
    float D[]={Grads[j],Grads[j+1]};
    float S = Dists[j/2] / (float)sqrt(D[0]*D[0] + D[1]*D[1]);
    D[0]*=S;
    D[1]*=S;
    glVertex2f(Pts[j]-D[0],Pts[j+1]-D[1]);
  }
  glEnd();

  // DRAW PENETRATING POINTS
  glPointSize(3);
  glColor3f(1,0,0.7f);
  glBegin(GL_POINTS);
    for (j=0; j<NumPts*2; j+=2) glVertex2fv(&(Pts[j]));
  glEnd();

  glutSwapBuffers();

  if (Pts) delete[] Pts;
  if (Dists) delete[] Dists;
  if (Grads) delete[] Grads;
}

void myReshape(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1,1,-1,1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void main(void)
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
  glutInitWindowSize(512,512);
  glutInitWindowPosition(180,100);
  glutCreateWindow("HAVOC2D_COLLIDE Example Program 1");

  glutReshapeFunc(myReshape);
  glutDisplayFunc(myDisplay);

  // DEFAULT STATE FOR VORONOI SYSTEM
  glShadeModel(GL_FLAT);
  glDisable(GL_CULL_FACE);
  glDisable(GL_DITHER);
  glPixelStorei(GL_PACK_ALIGNMENT,1); 
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);

  glutMainLoop();
}
