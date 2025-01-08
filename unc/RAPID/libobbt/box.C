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

  EMail:              {gottscha}@cs.unc.edu


\**************************************************************************/


#include "box.H"
#include <stdio.h>
#include <stdlib.h>
#include "matvec.H"

// merlin's intersection test
#include "Intersect.H"

#ifdef gnu

#ifdef hppa
#define myfabs(x) \
 ({double __value, __arg = (x); \
   asm("fabs,dbl %1, %0": "=f" (__value): "f" (__arg)); \
   __value; \
});
#endif

#ifdef mips
#define myfabs(x) \
 ({double __value, __arg = (x); \
   asm("abs.d %0, %1": "=f" (__value): "f" (__arg)); \
   __value; \
});
#endif

#else  

#define myfabs(x) (fabs(x)) 

#endif



#define COLLIDE_FAST 1

#define NEW(b)  { if (!b) {fprintf(stderr, "Eek!  Failed new. File '%s', line %d.\n", __FILE__, __LINE__); fflush(stderr); exit(-1);} }


int OBBT_first_contact;

int OBBT_num_box_tests;
int OBBT_num_tri_tests;
int OBBT_num_contacts;

int OBBT_num_cols_alloced;
int OBBT_num_cols;
col_elt *OBBT_contact;

int OBBT_flag_reorient;
int OBBT_flag_subdivision_mode;



box::box() 
{
  U = P = N = 0;
  pR = Identity();
  pT.set(0.0, 0.0, 0.0);
  d[0] = d[1] = d[2] = 1.0;
  tri_list.clear();
  b_size = 1.0;
  rad = 1.732051;
}

box::~box()
{
  if (P) delete P;
  if (N) delete N;
}
 
static
double max(double a, double b, double c, double d)
{
  double t = a;
  if (b > t) t = b;
  if (c > t) t = c;
  if (d > t) t = d;
  return t;
}


static
double min(double a, double b, double c, double d)
{
  double t = a;
  if (b < t) t = b;
  if (c < t) t = c;
  if (d < t) t = d;
  return t;
}


static
double max(double a, double b, double c)
{
  double t = a;
  if (b > t) t = b;
  if (c > t) t = c;
  return t;
}


void
box::build_hierarchy()
{
  if (OBBT_flag_reorient) pR = best_orientation();
  refit();
  put_tris_in_self_cs();
  build_recurse();
} 

void
box::build_recurse()
{
  if (leaf()) split_once();

  if (leaf()) return;

  // and visit each child
  if (P) P->build_recurse();
  if (N) N->build_recurse();
}


void
box::split_once()
{
  int i;

  // determine optimal axis of split, and the coordinate for it.

  int axes[3];
  double coord[3];
  find_split_axes(axes, coord); // makes two passes through trilist

  // want largest dimension whose axis is good.
  double dim[3];
  dim[0] = axes[0] ? d[0] : 0.0;
  dim[1] = axes[1] ? d[1] : 0.0;
  dim[2] = axes[2] ? d[2] : 0.0;
  double md = max(dim[0], dim[1], dim[2]);
  if (md == 0.0)
    {
      // no split possible
      return;
    }
  int a;
  if (dim[0] == md) a = 0;
  else if (dim[1] == md) a = 1;
  else a = 2;
  
  // create subboxes
  P = new box(); 
  NEW(P);
  N = new box(); 
  NEW(N);
  P->U = N->U = this;
  
  // partition elements accordingly

  for(i=0; i<tri_list.num_tris; i++)
    {
      // tri_list is already in self cs
      double p = (tri_list.tris[i].p1.v[a] + 
		  tri_list.tris[i].p2.v[a] + 
		  tri_list.tris[i].p3.v[a]);
      p /= 3.0;

      if (p > coord[a])
	P->tri_list.add_tri(tri_list.tris[i]);
      else
 	N->tri_list.add_tri(tri_list.tris[i]);
    }

  // abort the split if either P or N got none
  if ((P->tri_list.num_tris == 0) || (N->tri_list.num_tris == 0))
    {
      delete P; P = 0; 
      delete N; N = 0; 
      fprintf(stderr, "Eek!  Shouldn't get here! '%s', line %d\n", __FILE__, __LINE__);
      fprintf(stderr, "a == %d\n", a);
      fprintf(stderr, "axes: %d %d %d\n", axes[0], axes[1], axes[2]);
      fprintf(stderr, "coords: %lf %lf %lf\n", coord[0], coord[1], coord[2]);
      
      return;
    }

  // assign positions and extents to each box
  if (P)
    {
      P->d[0] = d[0];
      P->d[1] = d[1];
      P->d[2] = d[2];
      if (OBBT_flag_reorient) P->pR = P->best_orientation();
      P->refit();
      P->put_tris_in_self_cs();
    }
  
  if (N)
    {
      N->d[0] = d[0];
      N->d[1] = d[1];
      N->d[2] = d[2];
      if (OBBT_flag_reorient) N->pR = N->best_orientation();
      N->refit();
      N->put_tris_in_self_cs();
    }
  
  // free the data in this box
  tri_list.clear_and_free();
}


/* 

   void box::put_tris_in_self_cs()

   Assume that the tris are in the parent cs, and that the
   box-from-parent transform (the elements pT and pR) has been set.

   Now go through and transform the tris from the parent to the box
   cs.  Note that this routine should only be called once on a box --
   if it is called multiple times, then the tris get shifted over too
   far.  

*/


void
box::put_tris_in_self_cs()
{
  int i;
  for(i=0; i<tri_list.num_tris; i++)
    {
      // tri list is in parent cs
      // xform from parent cs to self cs
      v3 p1 = pR.T()*(tri_list.tris[i].p1 - pT);
      v3 p2 = pR.T()*(tri_list.tris[i].p2 - pT);
      v3 p3 = pR.T()*(tri_list.tris[i].p3 - pT);

      tri_list.tris[i].p1 = p1;
      tri_list.tris[i].p2 = p2;
      tri_list.tris[i].p3 = p3;
    }
}

/*

   void box::find_split_coordinate(double c[3])

   This finds the arithmetic mean of the tris in the 
   box, and returns it.  For each coordinate axis.

*/


void
box::find_split_coordinate(double c[3])
{
  c[0] = c[1] = c[2] = 0.0;
  int i;
  for(i=0; i<tri_list.num_tris; i++)
    {
      // tri list is in self cs
      // xform from parent cs to self cs

      c[0] += tri_list.tris[i].p1.v[0];
      c[0] += tri_list.tris[i].p2.v[0];
      c[0] += tri_list.tris[i].p3.v[0];
      c[1] += tri_list.tris[i].p1.v[1];
      c[1] += tri_list.tris[i].p2.v[1];
      c[1] += tri_list.tris[i].p3.v[1];
      c[2] += tri_list.tris[i].p1.v[2];
      c[2] += tri_list.tris[i].p2.v[2];
      c[2] += tri_list.tris[i].p3.v[2];
    }

  c[0] /= tri_list.num_tris;
  c[0] /= 3.0;
  c[1] /= tri_list.num_tris;
  c[1] /= 3.0;
  c[2] /= tri_list.num_tris;
  c[2] /= 3.0;
}


/*

   Determines what axis has most advantageous split.

*/


void
box::find_split_axes(int a[3], double c[3])
{
//  const double eps = 1e-6;
  double v[3];
  
  int p[3];
  p[0] = p[1] = p[2] = 0;
  
  int n[3];
  n[0] = n[1] = n[2] = 0;
  
  // partition elements accordingly
  int i;

  find_split_coordinate(c);

  for(i=0; i<tri_list.num_tris; i++)
    {
      // tri list is already in self cs
      v[0] = tri_list.tris[i].p1.v[0];
      v[0] += tri_list.tris[i].p2.v[0];
      v[0] += tri_list.tris[i].p3.v[0];
      v[1] = tri_list.tris[i].p1.v[1];
      v[1] += tri_list.tris[i].p2.v[1];
      v[1] += tri_list.tris[i].p3.v[1];
      v[2] = tri_list.tris[i].p1.v[2];
      v[2] += tri_list.tris[i].p2.v[2];
      v[2] += tri_list.tris[i].p3.v[2];

      v[0] /= 3.0;
      v[1] /= 3.0;
      v[2] /= 3.0;

      if (v[0] < c[0]) n[0]++; else p[0]++;
      if (v[1] < c[1]) n[1]++; else p[1]++;
      if (v[2] < c[2]) n[2]++; else p[2]++;
    }

  // abort the split if either P or N got none
  a[0] = ((p[0] != 0) && (n[0] != 0));
  a[1] = ((p[1] != 0) && (n[1] != 0));
  a[2] = ((p[2] != 0) && (n[2] != 0));
}


/*

   Keeps the orientation the same, but determines a new origin
   and dimensions to fit the enclosed tris exactly.

*/



void 
box::refit()
{
  // keep the frame the same;
  
  // find the max and min along each axis
  int i;
  v3 p1, p2, p3;
  double max_d0, min_d0;
  double max_d1, min_d1;
  double max_d2, min_d2;

  if (tri_list.num_tris <= 0) return;  // do nothing if no tris
  
  p1 = pR.T()*(tri_list.tris[0].p1);
  min_d0 = max_d0 = p1.v[0];
  min_d1 = max_d1 = p1.v[1];
  min_d2 = max_d2 = p1.v[2];
  for(i=0; i<tri_list.num_tris; i++)
    {
      p1 = pR.T()*(tri_list.tris[i].p1);
      p2 = pR.T()*(tri_list.tris[i].p2);
      p3 = pR.T()*(tri_list.tris[i].p3);
      max_d0 = max(max_d0, p1.v[0], p2.v[0], p3.v[0]);
      max_d1 = max(max_d1, p1.v[1], p2.v[1], p3.v[1]);
      max_d2 = max(max_d2, p1.v[2], p2.v[2], p3.v[2]);
      min_d0 = min(min_d0, p1.v[0], p2.v[0], p3.v[0]);
      min_d1 = min(min_d1, p1.v[1], p2.v[1], p3.v[1]);
      min_d2 = min(min_d2, p1.v[2], p2.v[2], p3.v[2]);
    }

  // now place the origin in the proper position.
  double ave_d0 = 0.5*(max_d0 + min_d0);
  double ave_d1 = 0.5*(max_d1 + min_d1);
  double ave_d2 = 0.5*(max_d2 + min_d2);
  v3 mid(ave_d0, ave_d1, ave_d2);
  pT = pR*mid;
  
  // correct the dimensions
  d[0] = 0.5*(max_d0 - min_d0);
  d[1] = 0.5*(max_d1 - min_d1);
  d[2] = 0.5*(max_d2 - min_d2);
  
  b_size = max(d[0], d[1], d[2]);
  rad = sqrt(d[0]*d[0] + d[1]*d[1] + d[2]*d[2]);
  
}






#if 1
m33
box::get_cov()
{
  // find the max and min along each axis
  int i;
  v3 p;
  m33 Cov;
  double S1[3];
  double S2[3][3];

  S1[0] = S1[1] = S1[2] = 0.0;
  S2[0][0] = S2[1][0] = S2[2][0] = 0.0;
  S2[0][1] = S2[1][1] = S2[2][1] = 0.0;
  S2[0][2] = S2[1][2] = S2[2][2] = 0.0;

  // get center of mass
  p.set(0.0, 0.0, 0.0);
  for(i=0; i<tri_list.num_tris; i++)
    {
      v3 *p1 = &tri_list.tris[i].p1;
      v3 *p2 = &tri_list.tris[i].p2;
      v3 *p3 = &tri_list.tris[i].p3;
      
      S1[0] += p1->v[0] + p2->v[0] + p3->v[0];
      S1[1] += p1->v[1] + p2->v[1] + p3->v[1];
      S1[2] += p1->v[2] + p2->v[2] + p3->v[2];
      
      S2[0][0] += (p1->v[0] * p1->v[0] +  
		   p2->v[0] * p2->v[0] +  
		   p3->v[0] * p3->v[0]);
      S2[1][1] += (p1->v[1] * p1->v[1] +  
		   p2->v[1] * p2->v[1] +  
		   p3->v[1] * p3->v[1]);
      S2[2][2] += (p1->v[2] * p1->v[2] +  
		   p2->v[2] * p2->v[2] +  
		   p3->v[2] * p3->v[2]);
      S2[0][1] += (p1->v[0] * p1->v[1] +  
		   p2->v[0] * p2->v[1] +  
		   p3->v[0] * p3->v[1]);
      S2[0][2] += (p1->v[0] * p1->v[2] +  
		   p2->v[0] * p2->v[2] +  
		   p3->v[0] * p3->v[2]);
      S2[1][2] += (p1->v[1] * p1->v[2] +  
		   p2->v[1] * p2->v[2] +  
		   p3->v[1] * p3->v[2]);
    }

  double n = 3 * tri_list.num_tris;

  // now get covariances

  Cov.m[0][0] = S2[0][0] - S1[0]*S1[0] / n;
  Cov.m[1][1] = S2[1][1] - S1[1]*S1[1] / n;
  Cov.m[2][2] = S2[2][2] - S1[2]*S1[2] / n;
  Cov.m[0][1] = S2[0][1] - S1[0]*S1[1] / n;
  Cov.m[1][2] = S2[1][2] - S1[1]*S1[2] / n;
  Cov.m[0][2] = S2[0][2] - S1[0]*S1[2] / n;
  Cov.m[1][0] = Cov.m[0][1];
  Cov.m[2][0] = Cov.m[0][2];
  Cov.m[2][1] = Cov.m[1][2];

  return Cov;
}
#endif



/* 

   Returns a new orientation matrix which better fits the data.

*/

m33 
box::best_orientation()
{
  m33 Cov;

  if (tri_list.num_tris <= 0) return Identity();  // no tris?  exit!
  
  Cov = get_cov();

   // now get eigenvectors
  m33 Evecs;
  v3 Evals;
  eigen(&Evecs, &Evals, Cov);

#if 1
  // now do a little sorting:
  if (Evals.v[2] < Evals.v[1])
    {
      double u, t[3];
      u = Evals.v[2];
      t[0] = Evecs.m[0][2];
      t[1] = Evecs.m[1][2];
      t[2] = Evecs.m[2][2];
      Evals.v[2] = Evals.v[1];
      Evecs.m[0][2] = Evecs.m[0][1];
      Evecs.m[1][2] = Evecs.m[1][1];
      Evecs.m[2][2] = Evecs.m[2][1];
      Evals.v[1] = u;
      Evecs.m[0][1] = t[0];
      Evecs.m[1][1] = t[1];
      Evecs.m[2][1] = t[2];
    }

  if (Evals.v[1] < Evals.v[0])
    {
      double u, t[3];
      u = Evals.v[1];
      t[0] = Evecs.m[0][1];
      t[1] = Evecs.m[1][1];
      t[2] = Evecs.m[2][1];
      Evals.v[1] = Evals.v[0];
      Evecs.m[0][1] = Evecs.m[0][0];
      Evecs.m[1][1] = Evecs.m[1][0];
      Evecs.m[2][1] = Evecs.m[2][0];
      Evals.v[0] = u;
      Evecs.m[0][0] = t[0];
      Evecs.m[1][0] = t[1];
      Evecs.m[2][0] = t[2];
    }

  if (Evals.v[2] < Evals.v[1])
    {
      double u, t[3];
      u = Evals.v[2];
      t[0] = Evecs.m[0][2];
      t[1] = Evecs.m[1][2];
      t[2] = Evecs.m[2][2];
      Evals.v[2] = Evals.v[1];
      Evecs.m[0][2] = Evecs.m[0][1];
      Evecs.m[1][2] = Evecs.m[1][1];
      Evecs.m[2][2] = Evecs.m[2][1];
      Evals.v[1] = u;
      Evecs.m[0][1] = t[0];
      Evecs.m[1][1] = t[1];
      Evecs.m[2][1] = t[2];
    }
#endif  

  return Evecs;
}



int
edge_face(v3 l1, v3 l2, v3 p1, v3 p2, v3 p3)
{
  // line segment is formed by  x = l1 + t * (l2-l1)
  // plane face is x = p1 + u * (p2-p1) + v * (p3-p1)

  // find solution to
  //
  //         l1 + t * (l2-l1) = p1 + u * (p2-p1) + v * (p3-p1)
  //
  //         l1-p1 = t * (l1-l2) + u * (p2-p1) + v * (p3-p1)
  //         b = t * (x1)    + u * (x2)    + v * (x3)
  //                                                             

  v3 b = l1 - p1;
  v3 x1 = l1-l2;
  v3 x2 = p2-p1;
  v3 x3 = p3-p1;
  
  m33 M;
  M.m[0][0] = x1.v[0];
  M.m[1][0] = x1.v[1];
  M.m[2][0] = x1.v[2];
  M.m[0][1] = x2.v[0];
  M.m[1][1] = x2.v[1];
  M.m[2][1] = x2.v[2];
  M.m[0][2] = x3.v[0];
  M.m[1][2] = x3.v[1];
  M.m[2][2] = x3.v[2];
  
  v3 x = M.inverse()*b;
  
  if (x.v[0] < 0.0) return 0;
  if (x.v[0] > 1.0) return 0;
  if (x.v[1] < 0.0) return 0;
  if (x.v[2] < 0.0) return 0;
  if (x.v[1] + x.v[2] > 1.0) return 0;
  return 1;
}

int
tri_contact(box *b1, box *b2, 
	    double B[3][3], double T[3])
{
  // transform the coordinates from b2 into b1 and then perform a box test.
  m33 R(B[0][0], B[1][0], B[2][0],
	B[0][1], B[1][1], B[2][1],
	B[0][2], B[1][2], B[2][2]);
  v3 V(T[0], T[1], T[2]);

//  fprintf(stderr, "tri_contact: %d and %d tris\n", 
//	  b1->tri_list.num_tris, b2->tri_list.num_tris);
  
  int i,j;
  int f = 0;
  for(i=0; i<b1->tri_list.num_tris; i++)
    for(j=0; j<b2->tri_list.num_tris; j++)
      {

	v3 i1 = (b1->tri_list.tris[i].p1);
	v3 i2 = (b1->tri_list.tris[i].p2);
	v3 i3 = (b1->tri_list.tris[i].p3);
	v3 j1 = R * (b2->tri_list.tris[j].p1) + V;
	v3 j2 = R * (b2->tri_list.tris[j].p2) + V;
	v3 j3 = R * (b2->tri_list.tris[j].p3) + V;

	f |= intersect(i1.v, i2.v, i3.v, j1.v, j2.v, j3.v);
      }

  return f;
}


/*

   determines collision status between two box trees.

*/

int
collide(box *b1, box *b2, double B[3][3], double T[3])
{
 
  if (OBBT_first_contact && (OBBT_num_contacts > 0)) return 0;
  
  // test top level

  OBBT_num_box_tests++;
  
  int f1;
  
  double a[3];
  double b[3];
  a[0] = b1->d[0];
  a[1] = b1->d[1];
  a[2] = b1->d[2];
  b[0] = b2->d[0];
  b[1] = b2->d[1];
  b[2] = b2->d[2];

  f1 = box_test4(B, T, a, b);
  
  if (!f1) 
    {
      // disjoint boxes
      return 0;
    }

  // contact between boxes
  if (b1->leaf() && b2->leaf()) 
    {
      // it is a leaf pair - compare the polygons therein
      OBBT_num_tri_tests++; 
      if (tri_contact(b1, b2, B, T))
	{
	  box::add_collision(b1->tri_list.tris[0].id, b2->tri_list.tris[0].id);
	  OBBT_num_contacts++;
	  int id1 = b1->tri_list.tris[0].id;
	  int id2 = b2->tri_list.tris[0].id;
	}

      return 0;
    }


  double Bp[3][3], Tp[3], U[3];
  
  if (!b1->leaf() && !b2->leaf()) 
    {
      // neither are leaves -- choose the larger one.

      if (b1->size() > b2->size())
	{
	  // child of 'A'

	  // Bp = b1->P->pR.T() * B
	  Bp[0][0] = (b1->P->pR.m[0][0] * B[0][0] +
		      b1->P->pR.m[1][0] * B[1][0] +
		      b1->P->pR.m[2][0] * B[2][0]);
	  Bp[1][0] = (b1->P->pR.m[0][1] * B[0][0] +
		      b1->P->pR.m[1][1] * B[1][0] +
		      b1->P->pR.m[2][1] * B[2][0]);
	  Bp[2][0] = (b1->P->pR.m[0][2] * B[0][0] +
		      b1->P->pR.m[1][2] * B[1][0] +
		      b1->P->pR.m[2][2] * B[2][0]);
	  Bp[0][1] = (b1->P->pR.m[0][0] * B[0][1] +
		      b1->P->pR.m[1][0] * B[1][1] +
		      b1->P->pR.m[2][0] * B[2][1]);
	  Bp[1][1] = (b1->P->pR.m[0][1] * B[0][1] +
		      b1->P->pR.m[1][1] * B[1][1] +
		      b1->P->pR.m[2][1] * B[2][1]);
	  Bp[2][1] = (b1->P->pR.m[0][2] * B[0][1] +
		      b1->P->pR.m[1][2] * B[1][1] +
		      b1->P->pR.m[2][2] * B[2][1]);
	  Bp[0][2] = (b1->P->pR.m[0][0] * B[0][2] +
		      b1->P->pR.m[1][0] * B[1][2] +
		      b1->P->pR.m[2][0] * B[2][2]);
	  Bp[1][2] = (b1->P->pR.m[0][1] * B[0][2] +
		      b1->P->pR.m[1][1] * B[1][2] +
		      b1->P->pR.m[2][1] * B[2][2]);
	  Bp[2][2] = (b1->P->pR.m[0][2] * B[0][2] +
		      b1->P->pR.m[1][2] * B[1][2] +
		      b1->P->pR.m[2][2] * B[2][2]);

	  // Tp = b1->P->pR.T() * (T - b1->P->pT)
	  U[0] = T[0] - b1->P->pT.v[0];
	  U[1] = T[1] - b1->P->pT.v[1];
	  U[2] = T[2] - b1->P->pT.v[2];

	  Tp[0] = (b1->P->pR.m[0][0] * U[0] + 
		   b1->P->pR.m[1][0] * U[1] + 
		   b1->P->pR.m[2][0] * U[2]);
	  Tp[1] = (b1->P->pR.m[0][1] * U[0] + 
		   b1->P->pR.m[1][1] * U[1] + 
		   b1->P->pR.m[2][1] * U[2]);
	  Tp[2] = (b1->P->pR.m[0][2] * U[0] + 
		   b1->P->pR.m[1][2] * U[1] + 
		   b1->P->pR.m[2][2] * U[2]);

	  if (b1->P) collide(b1->P, b2, Bp, Tp);

	  // Bp = b1->N->pR.T() * B
	  Bp[0][0] = (b1->N->pR.m[0][0] * B[0][0] +
		      b1->N->pR.m[1][0] * B[1][0] +
		      b1->N->pR.m[2][0] * B[2][0]);
	  Bp[1][0] = (b1->N->pR.m[0][1] * B[0][0] +
		      b1->N->pR.m[1][1] * B[1][0] +
		      b1->N->pR.m[2][1] * B[2][0]);
	  Bp[2][0] = (b1->N->pR.m[0][2] * B[0][0] +
		      b1->N->pR.m[1][2] * B[1][0] +
		      b1->N->pR.m[2][2] * B[2][0]);
	  Bp[0][1] = (b1->N->pR.m[0][0] * B[0][1] +
		      b1->N->pR.m[1][0] * B[1][1] +
		      b1->N->pR.m[2][0] * B[2][1]);
	  Bp[1][1] = (b1->N->pR.m[0][1] * B[0][1] +
		      b1->N->pR.m[1][1] * B[1][1] +
		      b1->N->pR.m[2][1] * B[2][1]);
	  Bp[2][1] = (b1->N->pR.m[0][2] * B[0][1] +
		      b1->N->pR.m[1][2] * B[1][1] +
		      b1->N->pR.m[2][2] * B[2][1]);
	  Bp[0][2] = (b1->N->pR.m[0][0] * B[0][2] +
		      b1->N->pR.m[1][0] * B[1][2] +
		      b1->N->pR.m[2][0] * B[2][2]);
	  Bp[1][2] = (b1->N->pR.m[0][1] * B[0][2] +
		      b1->N->pR.m[1][1] * B[1][2] +
		      b1->N->pR.m[2][1] * B[2][2]);
	  Bp[2][2] = (b1->N->pR.m[0][2] * B[0][2] +
		      b1->N->pR.m[1][2] * B[1][2] +
		      b1->N->pR.m[2][2] * B[2][2]);

	  // Tp = b1->N->pR.T() * (T - b1->N->pT)
	  U[0] = T[0] - b1->N->pT.v[0];
	  U[1] = T[1] - b1->N->pT.v[1];
	  U[2] = T[2] - b1->N->pT.v[2];

	  Tp[0] = (b1->N->pR.m[0][0] * U[0] + 
		   b1->N->pR.m[1][0] * U[1] + 
		   b1->N->pR.m[2][0] * U[2]);
	  Tp[1] = (b1->N->pR.m[0][1] * U[0] + 
		   b1->N->pR.m[1][1] * U[1] + 
		   b1->N->pR.m[2][1] * U[2]);
	  Tp[2] = (b1->N->pR.m[0][2] * U[0] + 
		   b1->N->pR.m[1][2] * U[1] + 
		   b1->N->pR.m[2][2] * U[2]);

	  if (b1->N) collide(b1->N, b2, Bp, Tp);
	}
      else
	{
	  // child of 'B'

	  // Bp = B * b2->P->pR
	  Bp[0][0] = (B[0][0] * b2->P->pR.m[0][0] +
		      B[0][1] * b2->P->pR.m[1][0] +
		      B[0][2] * b2->P->pR.m[2][0]);
	  Bp[1][0] = (B[1][0] * b2->P->pR.m[0][0] +
		      B[1][1] * b2->P->pR.m[1][0] +
		      B[1][2] * b2->P->pR.m[2][0]);
	  Bp[2][0] = (B[2][0] * b2->P->pR.m[0][0] +
		      B[2][1] * b2->P->pR.m[1][0] +
		      B[2][2] * b2->P->pR.m[2][0]);
	  Bp[0][1] = (B[0][0] * b2->P->pR.m[0][1] +
		      B[0][1] * b2->P->pR.m[1][1] +
		      B[0][2] * b2->P->pR.m[2][1]);
	  Bp[1][1] = (B[1][0] * b2->P->pR.m[0][1] +
		      B[1][1] * b2->P->pR.m[1][1] +
		      B[1][2] * b2->P->pR.m[2][1]);
	  Bp[2][1] = (B[2][0] * b2->P->pR.m[0][1] +
		      B[2][1] * b2->P->pR.m[1][1] +
		      B[2][2] * b2->P->pR.m[2][1]);
	  Bp[0][2] = (B[0][0] * b2->P->pR.m[0][2] +
		      B[0][1] * b2->P->pR.m[1][2] +
		      B[0][2] * b2->P->pR.m[2][2]);
	  Bp[1][2] = (B[1][0] * b2->P->pR.m[0][2] +
		      B[1][1] * b2->P->pR.m[1][2] +
		      B[1][2] * b2->P->pR.m[2][2]);
	  Bp[2][2] = (B[2][0] * b2->P->pR.m[0][2] +
		      B[2][1] * b2->P->pR.m[1][2] +
		      B[2][2] * b2->P->pR.m[2][2]);

	  // Tp = B * b2->P->pT + T
	  double a[3];
	  a[0] = b2->P->pT.v[0];
	  a[1] = b2->P->pT.v[1];
	  a[2] = b2->P->pT.v[2];
	  
	  Tp[0] = (B[0][0] * a[0] + 
		   B[0][1] * a[1] + 
		   B[0][2] * a[2] +
		   T[0]); 	  
	  Tp[1] = (B[1][0] * a[0] + 
		   B[1][1] * a[1] + 
		   B[1][2] * a[2] +
		   T[1]);           
	  Tp[2] = (B[2][0] * a[0] + 
		   B[2][1] * a[1] + 
		   B[2][2] * a[2] +
		   T[2]);
		  
	  if (b2->P) collide(b1, b2->P, Bp, Tp);

	  // Bp = B * b2->N->pR
	  Bp[0][0] = (B[0][0] * b2->N->pR.m[0][0] +
		      B[0][1] * b2->N->pR.m[1][0] +
		      B[0][2] * b2->N->pR.m[2][0]);
	  Bp[1][0] = (B[1][0] * b2->N->pR.m[0][0] +
		      B[1][1] * b2->N->pR.m[1][0] +
		      B[1][2] * b2->N->pR.m[2][0]);
	  Bp[2][0] = (B[2][0] * b2->N->pR.m[0][0] +
		      B[2][1] * b2->N->pR.m[1][0] +
		      B[2][2] * b2->N->pR.m[2][0]);
	  Bp[0][1] = (B[0][0] * b2->N->pR.m[0][1] +
		      B[0][1] * b2->N->pR.m[1][1] +
		      B[0][2] * b2->N->pR.m[2][1]);
	  Bp[1][1] = (B[1][0] * b2->N->pR.m[0][1] +
		      B[1][1] * b2->N->pR.m[1][1] +
		      B[1][2] * b2->N->pR.m[2][1]);
	  Bp[2][1] = (B[2][0] * b2->N->pR.m[0][1] +
		      B[2][1] * b2->N->pR.m[1][1] +
		      B[2][2] * b2->N->pR.m[2][1]);
	  Bp[0][2] = (B[0][0] * b2->N->pR.m[0][2] +
		      B[0][1] * b2->N->pR.m[1][2] +
		      B[0][2] * b2->N->pR.m[2][2]);
	  Bp[1][2] = (B[1][0] * b2->N->pR.m[0][2] +
		      B[1][1] * b2->N->pR.m[1][2] +
		      B[1][2] * b2->N->pR.m[2][2]);
	  Bp[2][2] = (B[2][0] * b2->N->pR.m[0][2] +
		      B[2][1] * b2->N->pR.m[1][2] +
		      B[2][2] * b2->N->pR.m[2][2]);

	  // Tp = B * b2->N->pT + T
	  a[0] = b2->N->pT.v[0];
	  a[1] = b2->N->pT.v[1];
	  a[2] = b2->N->pT.v[2];
	
	  Tp[0] = (B[0][0] * a[0] + 
		   B[0][1] * a[1] + 
		   B[0][2] * a[2] +
		   T[0]); 	  
	  Tp[1] = (B[1][0] * a[0] + 
		   B[1][1] * a[1] + 
		   B[1][2] * a[2] +
		   T[1]);           
	  Tp[2] = (B[2][0] * a[0] + 
		   B[2][1] * a[1] + 
		   B[2][2] * a[2] +
		   T[2]);

	  if (b2->N) collide(b1, b2->N, Bp, Tp);
	}
    }
  else if (b1->leaf() && !b2->leaf())
    {
      // child of 'B'

      // Bp = B * b2->P->pR
      Bp[0][0] = (B[0][0] * b2->P->pR.m[0][0] +
		  B[0][1] * b2->P->pR.m[1][0] +
		  B[0][2] * b2->P->pR.m[2][0]);
      Bp[1][0] = (B[1][0] * b2->P->pR.m[0][0] +
		  B[1][1] * b2->P->pR.m[1][0] +
		  B[1][2] * b2->P->pR.m[2][0]);
      Bp[2][0] = (B[2][0] * b2->P->pR.m[0][0] +
		  B[2][1] * b2->P->pR.m[1][0] +
		  B[2][2] * b2->P->pR.m[2][0]);
      Bp[0][1] = (B[0][0] * b2->P->pR.m[0][1] +
		  B[0][1] * b2->P->pR.m[1][1] +
		  B[0][2] * b2->P->pR.m[2][1]);
      Bp[1][1] = (B[1][0] * b2->P->pR.m[0][1] +
		  B[1][1] * b2->P->pR.m[1][1] +
		  B[1][2] * b2->P->pR.m[2][1]);
      Bp[2][1] = (B[2][0] * b2->P->pR.m[0][1] +
		  B[2][1] * b2->P->pR.m[1][1] +
		  B[2][2] * b2->P->pR.m[2][1]);
      Bp[0][2] = (B[0][0] * b2->P->pR.m[0][2] +
		  B[0][1] * b2->P->pR.m[1][2] +
		  B[0][2] * b2->P->pR.m[2][2]);
      Bp[1][2] = (B[1][0] * b2->P->pR.m[0][2] +
		  B[1][1] * b2->P->pR.m[1][2] +
		  B[1][2] * b2->P->pR.m[2][2]);
      Bp[2][2] = (B[2][0] * b2->P->pR.m[0][2] +
		  B[2][1] * b2->P->pR.m[1][2] +
		  B[2][2] * b2->P->pR.m[2][2]);

      // Tp = B * b2->P->pT + T
      double a[3];
      a[0] = b2->P->pT.v[0];
      a[1] = b2->P->pT.v[1];
      a[2] = b2->P->pT.v[2];
      
      Tp[0] = (B[0][0] * a[0] + 
	       B[0][1] * a[1] + 
	       B[0][2] * a[2] +
	       T[0]); 	  
      Tp[1] = (B[1][0] * a[0] + 
	       B[1][1] * a[1] + 
	       B[1][2] * a[2] +
	       T[1]);           
      Tp[2] = (B[2][0] * a[0] + 
	       B[2][1] * a[1] + 
	       B[2][2] * a[2] +
	       T[2]);
      
      if (b2->P) collide(b1, b2->P, Bp, Tp);

      // Bp = B * b2->N->pR
      Bp[0][0] = (B[0][0] * b2->N->pR.m[0][0] +
		  B[0][1] * b2->N->pR.m[1][0] +
		  B[0][2] * b2->N->pR.m[2][0]);
      Bp[1][0] = (B[1][0] * b2->N->pR.m[0][0] +
		  B[1][1] * b2->N->pR.m[1][0] +
		  B[1][2] * b2->N->pR.m[2][0]);
      Bp[2][0] = (B[2][0] * b2->N->pR.m[0][0] +
		  B[2][1] * b2->N->pR.m[1][0] +
		  B[2][2] * b2->N->pR.m[2][0]);
      Bp[0][1] = (B[0][0] * b2->N->pR.m[0][1] +
		  B[0][1] * b2->N->pR.m[1][1] +
		  B[0][2] * b2->N->pR.m[2][1]);
      Bp[1][1] = (B[1][0] * b2->N->pR.m[0][1] +
		  B[1][1] * b2->N->pR.m[1][1] +
		  B[1][2] * b2->N->pR.m[2][1]);
      Bp[2][1] = (B[2][0] * b2->N->pR.m[0][1] +
		  B[2][1] * b2->N->pR.m[1][1] +
		  B[2][2] * b2->N->pR.m[2][1]);
      Bp[0][2] = (B[0][0] * b2->N->pR.m[0][2] +
		  B[0][1] * b2->N->pR.m[1][2] +
		  B[0][2] * b2->N->pR.m[2][2]);
      Bp[1][2] = (B[1][0] * b2->N->pR.m[0][2] +
		  B[1][1] * b2->N->pR.m[1][2] +
		  B[1][2] * b2->N->pR.m[2][2]);
      Bp[2][2] = (B[2][0] * b2->N->pR.m[0][2] +
		  B[2][1] * b2->N->pR.m[1][2] +
		  B[2][2] * b2->N->pR.m[2][2]);

      // Tp = B * b2->N->pT + T
      a[0] = b2->N->pT.v[0];
      a[1] = b2->N->pT.v[1];
      a[2] = b2->N->pT.v[2];
      
      Tp[0] = (B[0][0] * a[0] + 
	       B[0][1] * a[1] + 
	       B[0][2] * a[2] +
	       T[0]); 	  
      Tp[1] = (B[1][0] * a[0] + 
	       B[1][1] * a[1] + 
	       B[1][2] * a[2] +
	       T[1]);           
      Tp[2] = (B[2][0] * a[0] + 
	       B[2][1] * a[1] + 
	       B[2][2] * a[2] +
	       T[2]);

      if (b2->N) collide(b1, b2->N, Bp, Tp);
    }
  else if (!b1->leaf() && b2->leaf())
    {
      // child of 'A'

      // Bp = b1->P->pR.T() * B
      Bp[0][0] = (b1->P->pR.m[0][0] * B[0][0] +
		  b1->P->pR.m[1][0] * B[1][0] +
		  b1->P->pR.m[2][0] * B[2][0]);
      Bp[1][0] = (b1->P->pR.m[0][1] * B[0][0] +
		  b1->P->pR.m[1][1] * B[1][0] +
		  b1->P->pR.m[2][1] * B[2][0]);
      Bp[2][0] = (b1->P->pR.m[0][2] * B[0][0] +
		  b1->P->pR.m[1][2] * B[1][0] +
		  b1->P->pR.m[2][2] * B[2][0]);
      Bp[0][1] = (b1->P->pR.m[0][0] * B[0][1] +
		  b1->P->pR.m[1][0] * B[1][1] +
		  b1->P->pR.m[2][0] * B[2][1]);
      Bp[1][1] = (b1->P->pR.m[0][1] * B[0][1] +
		  b1->P->pR.m[1][1] * B[1][1] +
		  b1->P->pR.m[2][1] * B[2][1]);
      Bp[2][1] = (b1->P->pR.m[0][2] * B[0][1] +
		  b1->P->pR.m[1][2] * B[1][1] +
		  b1->P->pR.m[2][2] * B[2][1]);
      Bp[0][2] = (b1->P->pR.m[0][0] * B[0][2] +
		  b1->P->pR.m[1][0] * B[1][2] +
		  b1->P->pR.m[2][0] * B[2][2]);
      Bp[1][2] = (b1->P->pR.m[0][1] * B[0][2] +
		  b1->P->pR.m[1][1] * B[1][2] +
		  b1->P->pR.m[2][1] * B[2][2]);
      Bp[2][2] = (b1->P->pR.m[0][2] * B[0][2] +
		  b1->P->pR.m[1][2] * B[1][2] +
		  b1->P->pR.m[2][2] * B[2][2]);

      // Tp = b1->P->pR.T() * (T - b1->P->pT)
      U[0] = T[0] - b1->P->pT.v[0];
      U[1] = T[1] - b1->P->pT.v[1];
      U[2] = T[2] - b1->P->pT.v[2];

      Tp[0] = (b1->P->pR.m[0][0] * U[0] + 
	       b1->P->pR.m[1][0] * U[1] + 
	       b1->P->pR.m[2][0] * U[2]);
      Tp[1] = (b1->P->pR.m[0][1] * U[0] + 
	       b1->P->pR.m[1][1] * U[1] + 
	       b1->P->pR.m[2][1] * U[2]);
      Tp[2] = (b1->P->pR.m[0][2] * U[0] + 
	       b1->P->pR.m[1][2] * U[1] + 
	       b1->P->pR.m[2][2] * U[2]);
      
      if (b1->P) collide(b1->P, b2, Bp, Tp);

      // Bp = b1->N->pR.T() * B
      Bp[0][0] = (b1->N->pR.m[0][0] * B[0][0] +
		  b1->N->pR.m[1][0] * B[1][0] +
		  b1->N->pR.m[2][0] * B[2][0]);
      Bp[1][0] = (b1->N->pR.m[0][1] * B[0][0] +
		  b1->N->pR.m[1][1] * B[1][0] +
		  b1->N->pR.m[2][1] * B[2][0]);
      Bp[2][0] = (b1->N->pR.m[0][2] * B[0][0] +
		  b1->N->pR.m[1][2] * B[1][0] +
		  b1->N->pR.m[2][2] * B[2][0]);
      Bp[0][1] = (b1->N->pR.m[0][0] * B[0][1] +
		  b1->N->pR.m[1][0] * B[1][1] +
		  b1->N->pR.m[2][0] * B[2][1]);
      Bp[1][1] = (b1->N->pR.m[0][1] * B[0][1] +
		  b1->N->pR.m[1][1] * B[1][1] +
		  b1->N->pR.m[2][1] * B[2][1]);
      Bp[2][1] = (b1->N->pR.m[0][2] * B[0][1] +
		  b1->N->pR.m[1][2] * B[1][1] +
		  b1->N->pR.m[2][2] * B[2][1]);
      Bp[0][2] = (b1->N->pR.m[0][0] * B[0][2] +
		  b1->N->pR.m[1][0] * B[1][2] +
		  b1->N->pR.m[2][0] * B[2][2]);
      Bp[1][2] = (b1->N->pR.m[0][1] * B[0][2] +
		  b1->N->pR.m[1][1] * B[1][2] +
		  b1->N->pR.m[2][1] * B[2][2]);
      Bp[2][2] = (b1->N->pR.m[0][2] * B[0][2] +
		  b1->N->pR.m[1][2] * B[1][2] +
		  b1->N->pR.m[2][2] * B[2][2]);

      // Tp = b1->N->pR.T() * (T - b1->N->pT)
      U[0] = T[0] - b1->N->pT.v[0];
      U[1] = T[1] - b1->N->pT.v[1];
      U[2] = T[2] - b1->N->pT.v[2];

      Tp[0] = (b1->N->pR.m[0][0] * U[0] + 
	       b1->N->pR.m[1][0] * U[1] + 
	       b1->N->pR.m[2][0] * U[2]);
      Tp[1] = (b1->N->pR.m[0][1] * U[0] + 
	       b1->N->pR.m[1][1] * U[1] + 
	       b1->N->pR.m[2][1] * U[2]);
      Tp[2] = (b1->N->pR.m[0][2] * U[0] + 
	       b1->N->pR.m[1][2] * U[1] + 
	       b1->N->pR.m[2][2] * U[2]);

      if (b1->N) collide(b1->N, b2, Bp, Tp);
    }

  return 0;
} 


int
box_test_good(double B[3][3], double T[3], double a[3], double b[3])
{
  register double t, s;
  register int r;
  double Bf[3][3];
  
  // Bf = fabs(B)
  Bf[0][0] = myfabs(B[0][0]);
  Bf[0][1] = myfabs(B[0][1]);
  Bf[0][2] = myfabs(B[0][2]);
  Bf[1][0] = myfabs(B[1][0]);
  Bf[1][1] = myfabs(B[1][1]);
  Bf[1][2] = myfabs(B[1][2]);
  Bf[2][0] = myfabs(B[2][0]);
  Bf[2][1] = myfabs(B[2][1]);
  Bf[2][2] = myfabs(B[2][2]);
  
  // if any of these tests are one-sided, then the polyhedra are disjoint

  r = 1;
  int f;
  

  // A1 x A2 = A0
  t = myfabs(T[0]);
  
  f = (t <= 
	  (a[0] + b[0] * Bf[0][0] + b[1] * Bf[0][1] + b[2] * Bf[0][2]));
  r &= f;
  
  // B1 x B2 = B0
  s = T[0]*B[0][0] + T[1]*B[1][0] + T[2]*B[2][0];
  t = myfabs(s);

  f = ( t <=
	  (b[0] + a[0] * Bf[0][0] + a[1] * Bf[1][0] + a[2] * Bf[2][0]));
  r &= f;
    
  // A2 x A0 = A1
  t = myfabs(T[1]);
  
  f = ( t <= 
	  (a[1] + b[0] * Bf[1][0] + b[1] * Bf[1][1] + b[2] * Bf[1][2]));
  r &= f;

  // A0 x A1 = A2
  t = myfabs(T[2]);

  f = ( t <= 
	  (a[2] + b[0] * Bf[2][0] + b[1] * Bf[2][1] + b[2] * Bf[2][2]));
  r &= f;

  // B2 x B0 = B1
  s = T[0]*B[0][1] + T[1]*B[1][1] + T[2]*B[2][1];
  t = myfabs(s);

  f = ( t <=
	  (b[1] + a[0] * Bf[0][1] + a[1] * Bf[1][1] + a[2] * Bf[2][1]));
  r &= f;

  // B0 x B1 = B2
  s = T[0]*B[0][2] + T[1]*B[1][2] + T[2]*B[2][2];
  t = myfabs(s);

  f = ( t <=
	  (b[2] + a[0] * Bf[0][2] + a[1] * Bf[1][2] + a[2] * Bf[2][2]));
  r &= f;

  // A0 x B0
  s = T[2] * B[1][0] - T[1] * B[2][0];
  t = myfabs(s);
  
  r &= ( t <= 
	(a[1] * Bf[2][0] + a[2] * Bf[1][0] +
	 b[1] * Bf[0][2] + b[2] * Bf[0][1]));
  
  // A0 x B1
  s = T[2] * B[1][1] - T[1] * B[2][1];
  t = myfabs(s);

  r &= ( t <=
	(a[1] * Bf[2][1] + a[2] * Bf[1][1] +
	 b[0] * Bf[0][2] + b[2] * Bf[0][0]));

  // A0 x B2
  s = T[2] * B[1][2] - T[1] * B[2][2];
  t = myfabs(s);

  r &= ( t <=
	  (a[1] * Bf[2][2] + a[2] * Bf[1][2] +
	   b[0] * Bf[0][1] + b[1] * Bf[0][0]));

  // A1 x B0
  s = T[0] * B[2][0] - T[2] * B[0][0];
  t = myfabs(s);

  r &= ( t <=
	  (a[0] * Bf[2][0] + a[2] * Bf[0][0] +
	   b[1] * Bf[1][2] + b[2] * Bf[1][1]));

  // A1 x B1
  s = T[0] * B[2][1] - T[2] * B[0][1];
  t = myfabs(s);

  r &= ( t <=
	  (a[0] * Bf[2][1] + a[2] * Bf[0][1] +
	   b[0] * Bf[1][2] + b[2] * Bf[1][0]));

  // A1 x B2
  s = T[0] * B[2][2] - T[2] * B[0][2];
  t = myfabs(s);

  r &= (t <=
	  (a[0] * Bf[2][2] + a[2] * Bf[0][2] +
	   b[0] * Bf[1][1] + b[1] * Bf[1][0]));

  // A2 x B0
  s = T[1] * B[0][0] - T[0] * B[1][0];
  t = myfabs(s);

  r &= (t <=
	  (a[0] * Bf[1][0] + a[1] * Bf[0][0] +
	   b[1] * Bf[2][2] + b[2] * Bf[2][1]));

  // A2 x B1
  s = T[1] * B[0][1] - T[0] * B[1][1];
  t = myfabs(s);

  r &= ( t <=
	  (a[0] * Bf[1][1] + a[1] * Bf[0][1] +
	   b[0] * Bf[2][2] + b[2] * Bf[2][0]));

  // A2 x B2
  s = T[1] * B[0][2] - T[0] * B[1][2];
  t = myfabs(s);

  r &= ( t <=
	  (a[0] * Bf[1][2] + a[1] * Bf[0][2] +
	   b[0] * Bf[2][1] + b[1] * Bf[2][0]));

  return r;
}
  

int
box_test4(double B[3][3], double T[3], double a[3], double b[3])
{
  register double t, s;
  register int r;
  double Bf[3][3];

  // Bf = fabs(B)
  Bf[0][0] = myfabs(B[0][0]);
  Bf[0][1] = myfabs(B[0][1]);
  Bf[0][2] = myfabs(B[0][2]);
  Bf[1][0] = myfabs(B[1][0]);
  Bf[1][1] = myfabs(B[1][1]);
  Bf[1][2] = myfabs(B[1][2]);
  Bf[2][0] = myfabs(B[2][0]);
  Bf[2][1] = myfabs(B[2][1]);
  Bf[2][2] = myfabs(B[2][2]);
  
  // if any of these tests are one-sided, then the polyhedra are disjoint

  r = 1;

  // A1 x A2 = A0
  t = myfabs(T[0]);
  
  r &= (t <= 
	  (a[0] + b[0] * Bf[0][0] + b[1] * Bf[0][1] + b[2] * Bf[0][2]));
  if (!r) return 0;
  
  // B1 x B2 = B0
  s = T[0]*B[0][0] + T[1]*B[1][0] + T[2]*B[2][0];
  t = myfabs(s);

  r &= ( t <=
	  (b[0] + a[0] * Bf[0][0] + a[1] * Bf[1][0] + a[2] * Bf[2][0]));
  if (!r) return 0;
    
  // A2 x A0 = A1
  t = myfabs(T[1]);
  
  r &= ( t <= 
	  (a[1] + b[0] * Bf[1][0] + b[1] * Bf[1][1] + b[2] * Bf[1][2]));
  if (!r) return 0;

  // A0 x A1 = A2
  t = myfabs(T[2]);

  r &= ( t <= 
	  (a[2] + b[0] * Bf[2][0] + b[1] * Bf[2][1] + b[2] * Bf[2][2]));
  if (!r) return 0;

  // B2 x B0 = B1
  s = T[0]*B[0][1] + T[1]*B[1][1] + T[2]*B[2][1];
  t = myfabs(s);

  r &= ( t <=
	  (b[1] + a[0] * Bf[0][1] + a[1] * Bf[1][1] + a[2] * Bf[2][1]));
  if (!r) return 0;

  // B0 x B1 = B2
  s = T[0]*B[0][2] + T[1]*B[1][2] + T[2]*B[2][2];
  t = myfabs(s);

  r &= ( t <=
	  (b[2] + a[0] * Bf[0][2] + a[1] * Bf[1][2] + a[2] * Bf[2][2]));
  if (!r) return 0;

  // A0 x B0
  s = T[2] * B[1][0] - T[1] * B[2][0];
  t = myfabs(s);
  
  r &= ( t <= 
	(a[1] * Bf[2][0] + a[2] * Bf[1][0] +
	 b[1] * Bf[0][2] + b[2] * Bf[0][1]));
  if (!r) return 0;
  
  // A0 x B1
  s = T[2] * B[1][1] - T[1] * B[2][1];
  t = myfabs(s);

  r &= ( t <=
	(a[1] * Bf[2][1] + a[2] * Bf[1][1] +
	 b[0] * Bf[0][2] + b[2] * Bf[0][0]));
  if (!r) return 0;

  // A0 x B2
  s = T[2] * B[1][2] - T[1] * B[2][2];
  t = myfabs(s);

  r &= ( t <=
	  (a[1] * Bf[2][2] + a[2] * Bf[1][2] +
	   b[0] * Bf[0][1] + b[1] * Bf[0][0]));
  if (!r) return 0;

  // A1 x B0
  s = T[0] * B[2][0] - T[2] * B[0][0];
  t = myfabs(s);

  r &= ( t <=
	  (a[0] * Bf[2][0] + a[2] * Bf[0][0] +
	   b[1] * Bf[1][2] + b[2] * Bf[1][1]));
  if (!r) return 0;

  // A1 x B1
  s = T[0] * B[2][1] - T[2] * B[0][1];
  t = myfabs(s);

  r &= ( t <=
	  (a[0] * Bf[2][1] + a[2] * Bf[0][1] +
	   b[0] * Bf[1][2] + b[2] * Bf[1][0]));
  if (!r) return 0;

  // A1 x B2
  s = T[0] * B[2][2] - T[2] * B[0][2];
  t = myfabs(s);

  r &= (t <=
	  (a[0] * Bf[2][2] + a[2] * Bf[0][2] +
	   b[0] * Bf[1][1] + b[1] * Bf[1][0]));
  if (!r) return 0;

  // A2 x B0
  s = T[1] * B[0][0] - T[0] * B[1][0];
  t = myfabs(s);

  r &= (t <=
	  (a[0] * Bf[1][0] + a[1] * Bf[0][0] +
	   b[1] * Bf[2][2] + b[2] * Bf[2][1]));
  if (!r) return 0;

  // A2 x B1
  s = T[1] * B[0][1] - T[0] * B[1][1];
  t = myfabs(s);

  r &= ( t <=
	  (a[0] * Bf[1][1] + a[1] * Bf[0][1] +
	   b[0] * Bf[2][2] + b[2] * Bf[2][0]));
  if (!r) return 0;

  // A2 x B2
  s = T[1] * B[0][2] - T[0] * B[1][2];
  t = myfabs(s);

  r &= ( t <=
	  (a[0] * Bf[1][2] + a[1] * Bf[0][2] +
	   b[0] * Bf[2][1] + b[1] * Bf[2][0]));

  return r;
}
  


int 
collide(double R1[3][3], double T1[3], box *b1,
	double R2[3][3], double T2[3], box *b2,
	int flag)
{
  if ((flag & ALL_CONTACTS) && (flag & FIRST_CONTACT))
    {
      fprintf(stderr, "Contradictory flag setting: cannot have\n");
      fprintf(stderr, "ALL_CONTACTS and FIRST_CONTACT both set.\n");
      return 0;
    }
  
  OBBT_first_contact = 0; 
  if (flag & FIRST_CONTACT) OBBT_first_contact = 1;
  
  double tR1[3][3], tR2[3][3], R[3][3];
  double tT1[3], tT2[3], T[3], U[3];
  
  if (!b1 || !b2) return 0;

  // (R1,T1) and (R2,T2) are how the two triangle sets are positioned
  // in world space.  (tR1,tT1) and (tR2,tT2) are how the top level
  // boxes are positioned in world space
  
  MxM(tR1, R1, b1->pR.m);                  // tR1 = R1 * b1->pR;
  MxVpV(tT1, R1, b1->pT.v, T1);            // tT1 = R1 * b1->pT + T1;
  MxM(tR2, R2, b2->pR.m);                  // tR2 = R2 * b2->pR;
  MxVpV(tT2, R2, b2->pT.v, T2);            // tT2 = R2 * b2->pT + T2;
  
  // (R,T) is the placement of b2's top level box within
  // the coordinate system of b1's top level box.

  MTxM(R, tR1, tR2);                     // R = tR1.T()*tR2;
  VmV(U, tT2, tT1);  MTxV(T, tR1, U);    // T = tR1.T()*(tT2-tT1);

  // reset the report fields
  OBBT_num_box_tests = 0;
  OBBT_num_tri_tests = 0;
  OBBT_num_contacts = 0;
  OBBT_num_cols = 0;
  
  // make the call

  collide(b1, b2, R, T);
  OBBT_num_contacts = OBBT_num_cols;
 
  return OBBT_num_contacts;
}

void
box::add_collision(int id1, int id2)
{
  if (!OBBT_contact)
    {
      OBBT_contact = new col_elt[10];
      OBBT_num_cols_alloced = 10;
      OBBT_num_cols = 0;
    }

  if (OBBT_num_cols == OBBT_num_cols_alloced)
    {
      col_elt *t = new col_elt[OBBT_num_cols_alloced*2];
      OBBT_num_cols_alloced *= 2;
      
      for(int i=0; i<OBBT_num_cols; i++) t[i] = OBBT_contact[i];
      delete [] OBBT_contact;
      OBBT_contact = t;
    }
  
  OBBT_contact[OBBT_num_cols].id1 = id1;
  OBBT_contact[OBBT_num_cols].id2 = id2;
  OBBT_num_cols++;
}

void
box::initialize()
{
  OBBT_num_box_tests = 0;
  OBBT_num_contacts = 0;
  OBBT_num_cols_alloced = 0;
  OBBT_num_cols = 0;
  OBBT_contact = 0;

  OBBT_flag_reorient = 1;
  OBBT_flag_subdivision_mode = 0;
}             

#if 1

void
OBBTC_initialize()
{
  box::initialize();
}

void
OBBTC_build_hierarchy(void *b)
{
  ((box *) b)->build_hierarchy();
}

void *
OBBTC_new_box()
{
  return new box;
}

void
OBBTC_delete_box(void *b)
{
  delete ((box *)b);
}

void
OBBTC_collide(double R1[3][3], double T1[3], void *b1,
	      double R2[3][3], double T2[3], void *b2,
	      int flag)
{
  collide(R1, T1, (box *)b1, R2, T2, (box *)b2, flag);
}

void
OBBTC_add_tri(void *b, double *p1, double *p2, double *p3, int id)
{
  ((box *)b)->add_tri(p1, p2, p3, id);
}

#endif
