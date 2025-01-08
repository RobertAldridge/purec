/******************************************************************************\

  Copyright 2004 The University of North Carolina at Chapel Hill.
  All Rights Reserved.

  Permission to use, copy, modify and distribute this software and its
  documentation for educational, research and non-profit purposes, without
  fee, and without a written agreement is hereby granted, provided that the
  above copyright notice and the following three paragraphs appear in all
  copies. Any use in a commercial organization requires a separate license.

  IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL BE LIABLE
  TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
  DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND
  ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF NORTH CAROLINA HAVE BEEN
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.


  Permission to use, copy, modify and distribute this software and its
  documentation for educational, research and non-profit purposes, without
  fee, and without a written agreement is hereby granted, provided that the
  above copyright notice and the following three paragraphs appear in all
  copies.

  THE UNIVERSITY OF NORTH CAROLINA SPECIFICALLY DISCLAIM ANY WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
  FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN
  "AS IS" BASIS, AND THE UNIVERSITY OF NORTH CAROLINA HAS NO OBLIGATION TO
  PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.


   ---------------------------------
  |Please send all BUG REPORTS to:  |
  |                                 |
  |   geom@cs.unc.edu               |
  |                                 |
   ---------------------------------


  The authors may be contacted via:

  US Mail:         K. Hoff, M. Foskey, A. Sud, M. Lin or D. Manocha
                       Department of Computer Science
                       Sitterson Hall, CB #3175
                       University of N. Carolina
                       Chapel Hill, NC 27599-3175

  Phone:               (919)962-1749


\*****************************************************************************/

//============================================================================
// voronoi_color_ids.cpp : color/id mapping routines
//   - maps between a 32-bit integer and a 32-bit RGBA triple
//   - only needed if nice looking colors are desired for visualization of the
//     Voronoi diagram. Otherwise, ints should be cast directly to unsigned chars
//     and vice versa.
//   - the ID (0,0,0,0) is automatically avoided
//   - user provides ordered indices
//   - not used internally by Voronoi system
//============================================================================

#define USE_PRETTY_COLORS  // COMMENT THIS OUT IF YOU WANT THE FAST MAPPING
#ifdef USE_PRETTY_COLORS

unsigned char* vdINT2RGBA(int i, unsigned char *C)
{
  i++; // BLACK IS RESERVED AND WILL NEVER BE CREATED IF WE ADD 1
  C[0] = (unsigned char)
         (     ((i&1)<<7) | ((i&(1<<3))<<3)   | ((i&(1<<6))>>1)   | ((i&(1<<9))>>5)  |
         ((i&(1<<12))>>9) | ((i&(1<<15))>>13) | ((i&(1<<18))>>17) | ((i&(1<<21))>>21) );
  C[1] = (unsigned char)
         ( ((i&(1<<1))<<6) | ((i&(1<<4))<<2)   | ((i&(1<<7))>>2)   | ((i&(1<<10))>>6) |
         ((i&(1<<13))>>10) | ((i&(1<<16))>>14) | ((i&(1<<19))>>18) | ((i&(1<<22))>>22) );
  C[2] = (unsigned char)
         ( ((i&(1<<2))<<5) | ((i&(1<<5))<<1)   | ((i&(1<<8))>>3)   | ((i&(1<<11))>>7) |
         ((i&(1<<14))>>11) | ((i&(1<<17))>>15) | ((i&(1<<20))>>19) | ((i&(1<<23))>>23) );
  C[3] = (unsigned char)(i>>24);
  return(C);
}

int vdRGBA2INT(const unsigned char *C)
{
  int R=C[0], G=C[1], B=C[2], A=C[3];
  int i = (A<<24) |
          ((R&(1<<7))>>7)  | ((G&(1<<7))>>6)  | ((B&(1<<7))>>5) |
          ((R&(1<<6))>>3)  | ((G&(1<<6))>>2)  | ((B&(1<<6))>>1) |
          ((R&(1<<5))<<1)  | ((G&(1<<5))<<2)  | ((B&(1<<5))<<3) |
          ((R&(1<<4))<<5)  | ((G&(1<<4))<<6)  | ((B&(1<<4))<<7) |
          ((R&(1<<3))<<9)  | ((G&(1<<3))<<10) | ((B&(1<<3))<<11) |
          ((R&(1<<2))<<13) | ((G&(1<<2))<<14) | ((B&(1<<2))<<15) |
          ((R&(1<<1))<<17) | ((G&(1<<1))<<18) | ((B&(1<<1))<<19) |
          ((R&(1<<0))<<21) | ((G&(1<<0))<<22) | ((B&(1<<0))<<23);
  i--;
  return(i);
}

#else

unsigned char* vdINT2RGBA(int i, unsigned char *C)
{
  i++; // BLACK IS RESERVED AND WILL NEVER BE CREATED IF WE ADD 1
  C[0] = (unsigned char)(i>>24);
  C[1] = (unsigned char)(i>>16);
  C[2] = (unsigned char)(i>>8);
  C[3] = (unsigned char)i;
  return(C);
}

int vdRGBA2INT(const unsigned char *C)
{
  int R=C[0], G=C[1], B=C[2], A=C[3];
  int i = (R<<24) | (G<<16) | (B<<8) | A;
  i--;
  return(i);
}

#endif
