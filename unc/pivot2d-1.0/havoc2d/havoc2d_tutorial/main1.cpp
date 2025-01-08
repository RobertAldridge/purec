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
#include <GL/glut.h>
#include "voronoi.hpp"
#include "voronoi_sites.hpp"
#include "voronoi_site_pt.hpp"
#include "voronoi_site_line.hpp"
#include "voronoi_site_bezier.hpp"

int Res=512;
float FillGeomRatio=0.5f;  // IN (0,1), HIGHER VALUES INCREASE FILL REQUIREMENTS AND REDUCE GEOMETRY
VoronoiSites *vSites=NULL;

void myDisplay(void)
{
  // COMPUTE VORONOI DIAGRAM
  vdCompute(vSites, 0,0,1,1, 1.415f, FillGeomRatio, Res,Res);

  // DRAW VORONOI SITES
  glColor3f(1,1,1);
  glPointSize(3);
  vdDrawSites(vSites, 0,0,1,1, Res,Res);

  glutSwapBuffers();
}

void myReshape(int w, int h)
{
  glViewport(0, 0, w, h);
}

void main(void)
{
  // CREATE LIST OF VORONOI SITES (LINK SITES TO ANIMATED POINTS)
  vSites = new VoronoiSites();

  float Px=0.1f, Py=0.1f;
  VoronoiPointSite *PtSite = new VoronoiPointSite(&Px,&Py);
  vSites->Add(PtSite);

  float Lax=0.8f, Lay=0.1f, Lbx=0.6f, Lby=0.9f;
  VoronoiLineSite *LineSite = new VoronoiLineSite(&Lax,&Lay,&Lbx,&Lby);
  vSites->Add(LineSite);

  float Ax=0,Ay=0,Bx=0,By=1,Cx=1,Cy=1.5f,Dx=1,Dy=0;
  VoronoiBezierSite *BezSite = new VoronoiBezierSite(&Ax,&Ay,&Bx,&By,&Cx,&Cy,&Dx,&Dy,32);
  vSites->Add(BezSite);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(Res,Res);
  glutInitWindowPosition(180,100);
  glutCreateWindow("Kenny's New and Improved 2D Voronoi Diagrams");

  glutReshapeFunc(myReshape);
  glutDisplayFunc(myDisplay);

  glDisable(GL_DEPTH_TEST);

  // DEFAULT STATE FOR VORONOI SYSTEM
  glShadeModel(GL_FLAT);
  glDisable(GL_CULL_FACE);
  glDisable(GL_DITHER);
  glPixelStorei(GL_PACK_ALIGNMENT,1); 
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);

  glutMainLoop();
}
