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



#ifndef POLY_TRI_H
#define POLY_TRI_H

#include "tri.H"

class poly_tri
{
public:
  
  eArray_tri tris;
  int num_tris;
  
  poly_tri(): num_tris(0) {}
 
  void
  add_tri(v3 p1, v3 p2, v3 p3, int i)
    {
      tris.reserve(num_tris+1);
      tris[num_tris].p1 = p1;
      tris[num_tris].p2 = p2;
      tris[num_tris].p3 = p3;
      tris[num_tris].id = i;
      num_tris++;
    }

  void
  add_tri(v3 p1, v3 p2, v3 p3)
    {
      tris.reserve(num_tris+1);
      tris[num_tris].p1 = p1;
      tris[num_tris].p2 = p2;
      tris[num_tris].p3 = p3;
      tris[num_tris].id = num_tris;
      num_tris++;
    }

  void
  add_tri(double *p1, double *p2, double *p3, int i)
    {
      tris.reserve(num_tris+1);
      tris[num_tris].p1.v[0] = p1[0];
      tris[num_tris].p1.v[1] = p1[1];
      tris[num_tris].p1.v[2] = p1[2];
      tris[num_tris].p2.v[0] = p2[0];
      tris[num_tris].p2.v[1] = p2[1];
      tris[num_tris].p2.v[2] = p2[2];
      tris[num_tris].p3.v[0] = p3[0];
      tris[num_tris].p3.v[1] = p3[1];
      tris[num_tris].p3.v[2] = p3[2];
      tris[num_tris].id = i;
      num_tris++;
    }

  void
  add_tri(tri t1)
    {
       tris.reserve(num_tris+1);
      tris[num_tris] = t1;
      num_tris++;
    }

  void clear()
    {
      num_tris = 0;
    }

  void clear_and_free()
    {
      num_tris = 0;
      tris.clear();
    }

  double min(double a, double b)
    {
      if (a < b) return a;
      else return b;
    }

  double min_size()
    {
      int i;
      double m = sqrt((tris[0].p1-tris[0].p2)*(tris[0].p1-tris[0].p2));;
      for(i=0; i<num_tris; i++)
	{
	  m = min(m, sqrt((tris[i].p1-tris[i].p2)*(tris[i].p1-tris[i].p2)));
	  m = min(m, sqrt((tris[i].p1-tris[i].p3)*(tris[i].p1-tris[i].p3)));
	  m = min(m, sqrt((tris[i].p2-tris[i].p3)*(tris[i].p2-tris[i].p3)));
	}
      return m;
    }  
};



#endif
