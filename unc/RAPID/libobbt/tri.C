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

#include "tri.H"

eArray_tri::eArray_tri(const eArray_tri &ea) :
     alloc(0), data(0), next(0)
{
  int i;
  
  expand_to(ea.alloc);
  for(i=0; i<ea.alloc; i++)
      data[i] = ea.data[i];
}


#ifdef EARRAY_TRI_CHECK_BOUNDS
tri &
eArray_tri::operator[](int i) const
{

  if (!data || (i >= alloc) || (i<0)) 
    {
      ::fprintf(stderr, "eArray_tri: array bounds exceeded! (alloc = %d, index = %d)\n", alloc, i);
      ::fflush(stderr);
      // seg fault here so we can see stack trace within debugger
      {
	char *s = (char *) 0;
	*s = 'x';
      }
    }

  return data[i];
}
#endif

const eArray_tri &
eArray_tri::operator=(const eArray_tri &ea)
{
  int i;

  if (this == &ea) return *this;
  
  if (data) delete [] data;
  data = 0;
  alloc = 0;
  next = 0;
  
  expand_to(ea.alloc);
  for(i=0; i<ea.alloc; i++)
      data[i] = ea.data[i];

  return *this;
}


/*
   expand_to(n) will set ensure that at least n+1 elements are allocated.
   The 'n+1' rather than 'n' may seem strange, but this is conservative
   'over allocation' so that fragments such as 

       ar.expand_to[i];
       ar[i] = elt;

   are guaranteed to work.

*/


void
eArray_tri::expand_to(int n)
{
  tri *t_data;
  int i;

  if (n >= alloc)
    {
      t_data = new tri[n+1];
      for(i=0; i<alloc; i++) t_data[i] = data[i];
      if (data) delete [] data;
      data = t_data;
      alloc = n+1;
    }

  return;
}


/*
   
   reserve(n) is like expand_to(n) in that it sets aside n+1 elements.
   However, if it needs to allocate more memory, it does so by allocating 
   twice the requested store, instead of just meeting the request.  

   This is to avoid successive reallocations within loops such as 

   for(i=0; i<n; i++)
   {
     ar.reserve(i);
     ar[i] = tri;
   }

   If reserve() acted like expand_to(), then this would have complexity 
   quadratic in n.  The doubing which reserve() does makes this loop linear
   in n.

*/

void
eArray_tri::reserve(int n)
{
  tri *t_data;
  int i;

  
  if (n >= alloc)
    {
      t_data = new tri[2*(n+1)];
      for(i=0; i<alloc; i++) t_data[i] = data[i];
      if (data) delete [] data;
      data = t_data;
      alloc = 2*(n+1);
    }

  return;
}

