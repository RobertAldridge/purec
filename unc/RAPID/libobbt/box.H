
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

#ifndef BOX_H
#define BOX_H

#include "SVM.H"
#include "poly_tri.H"
#include "OBBTC.h"


class box
{
public:

  // placement in parent's space
  m33 pR;
  v3 pT;
  
  // dimensions
  double d[3];        // this is "radius", that is, 
                      // half the measure of a side length

  box();
  ~box();
  
  double rad;
  
  box *P;
  box *N;
  box *U;

  double b_size;

  // box to model space: x_m = R*x_b + T
  // model to box space: x_b = R.T()*(x_m - T)

  poly_tri tri_list;
  void add_tri(double *p, double *q, double *r, int id)
    {
      tri_list.add_tri(p, q, r, id);
    }

  int leaf() { return (!P && !N); } 
  double size() 
    { 
      double t = d[0]; 
      if (d[1] > t) t = d[1];
      if (d[2] > t) t = d[2];
      return t;
    } 

  void build_hierarchy();
  void build_recurse();
  
  void find_split_axes(int a[3], double c[3]);
  void split_once();
  void refit();
  void refit_to_new_tris();
  void find_split_coordinate(double c[3]);
  void put_tris_in_self_cs();

  m33 get_cov();
  m33 best_orientation();

  void write(FILE *fp);
  void read(FILE *fp);

  static void add_collision(int id1, int id2);
  static void initialize();
};


int 
collide(double R1[3][3], double T1[3], box *b1,
	double R2[3][3], double T2[3], box *b2,
	int flag);

int 
collide(box *b1, box *b2, double R[3][3], double T[3]);

int
box_test4(double B[3][3], double T[3], double a[3], double b[3]);

int
box_test_good(double B[3][3], double T[3], double a[3], double b[3]);

int
tri_contact(double *p1, double *p2, double *p3, 
	    double *q1, double *q2, double *q3);





#endif
