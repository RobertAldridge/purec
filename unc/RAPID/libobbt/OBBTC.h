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

#ifndef OBBTC_H
#define OBBTC_H

#ifdef __cplusplus
extern "C" {
  
#endif
  
  void OBBTC_initialize();
  void OBBTC_add_tri(void *b, double *p, double *q, double *r, int id);
  void OBBTC_build_hierarchy(void *b);
  void *OBBTC_new_box();
  void OBBTC_delete_box(void *b);
  void OBBTC_collide(double R1[3][3], double T1[3], void *b1,
		double R2[3][3], double T2[3], void *b2,
		int flag);

#ifdef __cplusplus
};
#endif

#define ALL_CONTACTS 1
#define FIRST_CONTACT 2


struct col_elt
{
  int id1;
  int id2;
};


extern int OBBT_first_contact;

extern  int OBBT_num_box_tests;
extern  int OBBT_num_tri_tests;
extern  int OBBT_num_contacts;

extern  int OBBT_num_cols_alloced;
extern  int OBBT_num_cols;
extern int OBBT_first_contact;

extern  int OBBT_num_box_tests;
extern  int OBBT_num_tri_tests;
extern  int OBBT_num_contacts;

extern  int OBBT_num_cols_alloced;
extern  int OBBT_num_cols;

extern  int OBBT_flag_reorient;
extern  int OBBT_flag_subdivision_mode;

extern  struct col_elt *OBBT_contact;

#endif
