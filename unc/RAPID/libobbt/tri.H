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



#ifndef TRI_H 
#define TRI_H

#include <stdio.h>
#include "SVM.H"

struct tri
{
  int id;
  v3 p1, p2, p3;

  void print()
    {
      printf("%d\n", id);
      p1.print();
      p2.print();
      p3.print();
    }
  
};


#define EARRAY_TRI_CHECK_BOUNDS

class eArray_tri
{
protected:
  
  int next; // number of elements valid in array
  int alloc; // number of elements allocated for in array
  tri *data; // the array itself

public:
  eArray_tri(const eArray_tri &ea);                      // copy constructor
  const eArray_tri & operator=(const eArray_tri &ea);	 // assignment
  
  eArray_tri() { next = 0; alloc = 0; data = 0; } 
  ~eArray_tri() { delete [] data; data = 0; next = -1; }
  void expand_to(int n);
  void reserve(int n);
  int num_alloced() const { return alloc; } 

  void add_next(tri e) { reserve(next+1);  data[next]=e; next++; }
  void set_next(int n) { next = n; } 
  int get_next() const { return next; } 

  void clear() { delete [] data;  data = 0;  alloc = 0; }
 
#ifndef EARRAY_TRI_CHECK_BOUNDS
  tri& operator[] (int i) const { return data[i]; }
#else
  tri& operator[] (int i) const;
#endif

  operator tri*() const { return data; }

  void
  replace(eArray_tri *a) 
    { 
      delete [] data; 
      data = a->data; alloc = a->alloc; next = a->next;
      a->data = 0; a->alloc = 0; a->next = 0;
    } 

};



#endif
// TRI_H
