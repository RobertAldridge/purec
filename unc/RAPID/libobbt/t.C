/*************************************************************************\

  Copyright 1995 The University of North Carolina at Chapel Hill.
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


  Permission to use, copy, modify and distribute this software and its
  documentation for educational, research and non-profit purposes, without
  fee, and without a written agreement is hereby granted, provided that the
  above copyright notice and the following three paragraphs appear in all
  copies.

  THE UNIVERSITY OF NORTH CAROLINA SPECIFICALLY DISCLAIM ANY
  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE
  PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND THE UNIVERSITY OF
  NORTH CAROLINA HAS NO OBLIGATIONS TO PROVIDE MAINTENANCE, SUPPORT,
  UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

  The authors may be contacted via:

  US Mail:             S. Gottschalk
                       Department of Computer Science
                       Sitterson Hall, CB #3175
                       University of N. Carolina
                       Chapel Hill, NC 27599-3175

  Phone:               (919)962-1749

\*************************************************************************/

#include "SVM.H"
#include "box.H"

#define LISTS 1


void
print_tree(void *b);


main()
{
  // first, initialize the library

  box::initialize();
  
  // next, get a couple of boxes in which to put our models

  box *b1 = new box;
  box *b2 = new box;
  
  // then, load the boxes with triangles.  The following loads each 
  // with a torus of 10000 triangles.

  fprintf(stderr, "loading tris into boxes...");  fflush(stderr);
  
  double a = 1.0;  // major radius of the tori
  double b = 0.2;  // minor radius of the tori

  int n1 = 5;     // tori will have n1*n2*2 triangles each
  int n2 = 5;

  int uc, vc;
  int count = 0;
  
  for(uc=0; uc<n1; uc++)
    for(vc=0; vc<n2; vc++)
      {
	double u1 = (2.0*M_PI*uc) / n1; 
	double u2 = (2.0*M_PI*(uc+1)) / n1; 
	double v1 = (2.0*M_PI*vc) / n2; 
	double v2 = (2.0*M_PI*(vc+1)) / n2; 

	double p1[3], p2[3], p3[3], p4[3];

	p1[0] = (a - b * cos(v1)) * cos(u1);
	p2[0] = (a - b * cos(v1)) * cos(u2);
	p3[0] = (a - b * cos(v2)) * cos(u1);
	p4[0] = (a - b * cos(v2)) * cos(u2);
	p1[1] = (a - b * cos(v1)) * sin(u1);
	p2[1] = (a - b * cos(v1)) * sin(u2);
	p3[1] = (a - b * cos(v2)) * sin(u1);
	p4[1] = (a - b * cos(v2)) * sin(u2);
	p1[2] = b * sin(v1);
	p2[2] = b * sin(v1);
	p3[2] = b * sin(v2);
	p4[2] = b * sin(v2);

	b1->add_tri(p1, p2, p3, count);
	b1->add_tri(p4, p2, p3, count+1);
	b2->add_tri(p1, p2, p3, count);
	b2->add_tri(p4, p2, p3, count+1);

	count += 2;
      }
  fprintf(stderr, "done\n");  fflush(stderr);
  fprintf(stderr, "Tori have %d triangles each.\n", count);
  
  // now build the hierarchies

  fprintf(stderr, "building hierarchies...");  fflush(stderr);
  b1->build_hierarchy();
  b2->build_hierarchy();
  fprintf(stderr, "done.\n"); fflush(stderr); 

  // now we are free to call the interference detect routine.
  // but first, construct the transformations which define the placement
  // of our two hierarchies in world space:

  // this placement causes them to overlap a large amount.

  double R1[3][3], R2[3][3], T1[3], T2[3];
  
  R1[0][0] = R1[1][1] = R1[2][2] = 1.0;
  R1[0][1] = R1[1][0] = R1[2][0] = 0.0;
  R1[0][2] = R1[1][2] = R1[2][1] = 0.0;

  R2[0][0] = R2[1][1] = R2[2][2] = 1.0;
  R2[0][1] = R2[1][0] = R2[2][0] = 0.0;
  R2[0][2] = R2[1][2] = R2[2][1] = 0.0;
  
  T1[0] = 1.0;  T1[1] = 0.0; T1[2] = 0.0;
  T2[0] = 0.0;  T2[1] = 0.0; T2[2] = 0.0;

  // now we can perform a collision query:

  collide(R1, T1, b1, R2, T2, b2, ALL_CONTACTS);

  // looking at the report, we can see where all the contacts were, and
  // also how many tests were necessary:

  printf("All contacts between overlapping tori:\n");
  
  printf("Num box tests: %d\n", OBBT_num_box_tests);
  printf("Num contact pairs: %d\n", OBBT_num_contacts);
#if LISTS
  int i;
  for(i=0; i<OBBT_num_contacts; i++)
    {
      printf("\t contact %4d: tri %4d and tri %4d\n", 
	     i, OBBT_contact[i].id1, OBBT_contact[i].id2);
    }
#endif

  // Notice the ALL_CONTACTS flag we used in the call to collide().
  // The alternative is to use the FIRST_CONTACT flag, instead.
  // the result is that the collide routine searches for any contact,
  // but not all of them.  It takes many many fewer tests to locate a single
  // contact.

  collide(R1, T1, b1, R2, T2, b2, FIRST_CONTACT);

  printf("First contact between overlapping tori:\n");
  
  printf("Num box tests: %d\n", OBBT_num_box_tests);
  printf("Num contact pairs: %d\n", OBBT_num_contacts);
#if LISTS
  for(i=0; i<OBBT_num_contacts; i++)
    {
      printf("\t contact %4d: tri %4d and tri %4d\n", 
	     i, OBBT_contact[i].id1, OBBT_contact[i].id2);
    }
#endif

  // by rotating one of them around the x-axis 90 degrees, they 
  // are now interlocked, but not quite touching.

  R1[0][0] = 1.0;  R1[0][1] = 0.0;  R1[0][2] = 0.0;
  R1[1][0] = 0.0;  R1[1][1] = 0.0;  R1[1][2] =-1.0;
  R1[2][0] = 0.0;  R1[2][1] = 1.0;  R1[2][2] = 0.0;
  
  collide(R1, T1, b1, R2, T2, b2, FIRST_CONTACT);

  printf("No contact between interlocked but nontouching tori:\n");
  
  printf("Num box tests: %d\n", OBBT_num_box_tests);
  printf("Num contact pairs: %d\n", OBBT_num_contacts);
#if LISTS
  for(i=0; i<OBBT_num_contacts; i++)
    {
      printf("\t contact %4d: tri %4d and tri %4d\n", 
	     i, OBBT_contact[i].id1, OBBT_contact[i].id2);
    }
#endif

  // by moving one of the tori closer to the other, they
  // almost touch.  This is the case that requires a lot
  // of work wiht methods which use bounding boxes of limited
  // aspect ratio.  Oriented bounding boxes are more efficient
  // at determining noncontact than spheres, octree, or axis-aligned
  // bounding boxes for scenarios like this.  In this case, the interlocked
  // tori are separated by 0.0001 at their closest point.


  T1[0] = 1.5999;
  
  collide(R1, T1, b1, R2, T2, b2, FIRST_CONTACT);

  printf("Many tests required for interlocked but almost touching tori:\n");
  
  printf("Num box tests: %d\n", OBBT_num_box_tests);
  printf("Num contact pairs: %d\n", OBBT_num_contacts);
#if LISTS
  for(i=0; i<OBBT_num_contacts; i++)
    {
      printf("\t contact %4d: tri %4d and tri %4d\n", 
	     i, OBBT_contact[i].id1, OBBT_contact[i].id2);
    }
#endif

  print_tree(b1);
  

  return 0;  
}



void
print_tree(void *v)
{
  box *b = (box *)v;
  
  // print the transform
  printf("%12.8lf %12.8lf %12.8lf\n%12.8lf %12.8lf %12.8lf\n%12.8lf %12.8lf %12.8lf\n", 
	 b->pR.m[0][0], b->pR.m[0][1], b->pR.m[0][2],
	 b->pR.m[1][0], b->pR.m[1][1], b->pR.m[1][2],
	 b->pR.m[2][0], b->pR.m[2][1], b->pR.m[2][2]);
  printf("%12.8lf %12.8lf %12.8lf\n", 
	 b->pT.v[0], b->pT.v[1], b->pT.v[2]);

  // print num polygons and polygon list
  printf("%d\n", b->tri_list.num_tris);
  int i;
  for(i=0; i<b->tri_list.num_tris; i++)
    {
      printf("%12.8lf %12.8lf %12.8lf\n",
	     b->tri_list.tris[i].p1.v[0], 
	     b->tri_list.tris[i].p1.v[1], 
	     b->tri_list.tris[i].p1.v[2]); 
      printf("%12.8lf %12.8lf %12.8lf\n",
	     b->tri_list.tris[i].p2.v[0], 
	     b->tri_list.tris[i].p2.v[1], 
	     b->tri_list.tris[i].p2.v[2]); 
      printf("%12.8lf %12.8lf %12.8lf\n",
	     b->tri_list.tris[i].p3.v[0], 
	     b->tri_list.tris[i].p3.v[1], 
	     b->tri_list.tris[i].p3.v[2]); 
      printf("%d\n",
	     b->tri_list.tris[i].id); 
    }

  // print children
  if (b->N && b->P)
    {
      print_tree(b->N);
      print_tree(b->P);
    }
  
}
