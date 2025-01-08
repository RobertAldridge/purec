/*************************************************************************\

  Copyright 2007 The University of North Carolina at Chapel Hill.
  All Rights Reserved.

  Permission to use, copy, modify and distribute this software and its
  documentation for educational, research and non-profit purposes, without
   fee, and without a written agreement is hereby granted, provided that the
  above copyright notice and the following three paragraphs appear in all
  copies.

  IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL BE
  LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR
  CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE
  USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY
  OF NORTH CAROLINA HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGES.

  THE UNIVERSITY OF NORTH CAROLINA SPECIFICALLY DISCLAIM ANY
  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE
  PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND THE UNIVERSITY OF
  NORTH CAROLINA HAS NO OBLIGATIONS TO PROVIDE MAINTENANCE, SUPPORT,
  UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

  The authors may be contacted via:

  US Mail:             GAMMA Research Group at UNC
                       Department of Computer Science
                       Sitterson Hall, CB #3175
                       University of N. Carolina
                       Chapel Hill, NC 27599-3175

  Phone:               (919)962-1749

  EMail:              {geom, tangm}@cs.unc.edu


\**************************************************************************/
#include <windows.h>
#include <gl/gl.h>


#include "model_shl.h"
#include <stdio.h>

#define CIRCLE 900

#include "timing.h"
extern ModelShl *LoadModel(char *fname, unsigned int num_frame, float ply_scale);

#define DATA_LINK "http://gamma.cs.unc.edu/SR/benchmarks/cloth_ball.plys.zip"
#define DATA_PATH "../data/cloth_ball.plys/cloth_ball"
#define NUM_FRAME 94

static ModelShl *s_mdl = NULL;


// for sprintf
#pragma warning(disable: 4996)

void
Collide(ModelShl *mdl)
{
	mdl->ResetColor(255, 255, 255);
	mdl->SelfCollide();
	mdl->ColorCollide();
}

void
printCollideInfo()
{
	int num_contacts = s_mdl->NumContact();

	unsigned int id1, id2;
	printf("Start list contact info (totally %d contacts):\n", num_contacts);
	for (int i=0; i<num_contacts; i++) {
		s_mdl->GetContact(i, id1, id2);
		printf("Tri %4d <-------> Tri %4d\n", id1, id2);
	}
	printf("End list contact info.\n");
}



void initModel()
{
	TIMING_BEGIN
	s_mdl = LoadModel(DATA_PATH, NUM_FRAME, 1.f);
	if (s_mdl == NULL) // files not found
	{
		printf("Data files cannot find!\n");
		printf("Please download it from this link:\n%s\n", DATA_LINK);
		printf("Then put the exacted ply files into %s\n", "../data/cloth_ball.plys/");
		printf("We are exiting ...\n");
		getchar();
		exit(1);
	}

	s_mdl->ResetColor(255, 255, 255);
	TIMING_END("Load models")

	TIMING_BEGIN
	s_mdl->BuildBVH();
	TIMING_END("Init BVH")
}

void quitModel()
{
	delete s_mdl;
}


void drawModel(int *boxes, int *pairs, int level)
{
	glEnable(GL_NORMALIZE);

	glPushMatrix();
	glTranslatef(0, -1.4, -2);
	glScalef(0.1f, 0.1f, 0.1f);
	s_mdl->DisplayBVH(level);

	*boxes = s_mdl->NumBoxTest();
	*pairs = s_mdl->NumContact();

	s_mdl->DisplayColor();
	glPopMatrix();
}

void dynamicModel(int t, bool refit)
{
	float circle = CIRCLE;
	s_mdl->Deform(float(t), circle);

	if (!refit) {
		s_mdl->DeleteBVH();
		s_mdl->BuildBVH();
	} else
		s_mdl->RefitBVH();

	Collide(s_mdl);
}
