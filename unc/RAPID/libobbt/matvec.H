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



#ifndef MATVEC_H
#define MATVEC_H


inline
void
MxMpV(double Mr[3][3], double M1[3][3], double M2[3][3], double T[3])
{
  Mr[0][0] = (M1[0][0] * M2[0][0] +
	      M1[0][1] * M2[1][0] +
	      M1[0][2] * M2[2][0] +
	      T[0]);
  Mr[1][0] = (M1[1][0] * M2[0][0] +
	      M1[1][1] * M2[1][0] +
	      M1[1][2] * M2[2][0] +
	      T[1]);
  Mr[2][0] = (M1[2][0] * M2[0][0] +
	      M1[2][1] * M2[1][0] +
	      M1[2][2] * M2[2][0] +
	      T[2]);
  Mr[0][1] = (M1[0][0] * M2[0][1] +
	      M1[0][1] * M2[1][1] +
	      M1[0][2] * M2[2][1] +
	      T[0]);
  Mr[1][1] = (M1[1][0] * M2[0][1] +
	      M1[1][1] * M2[1][1] +
 	      M1[1][2] * M2[2][1] +
	      T[1]);
  Mr[2][1] = (M1[2][0] * M2[0][1] +
	      M1[2][1] * M2[1][1] +
	      M1[2][2] * M2[2][1] +
	      T[2]);
  Mr[0][2] = (M1[0][0] * M2[0][2] +
	      M1[0][1] * M2[1][2] +
	      M1[0][2] * M2[2][2] +
	      T[0]);
  Mr[1][2] = (M1[1][0] * M2[0][2] +
	      M1[1][1] * M2[1][2] +
	      M1[1][2] * M2[2][2] +
	      T[1]);
  Mr[2][2] = (M1[2][0] * M2[0][2] +
	      M1[2][1] * M2[1][2] +
	      M1[2][2] * M2[2][2] +
	      T[2]);
}

inline
void
MxM(double Mr[3][3], double M1[3][3], double M2[3][3])
{
  Mr[0][0] = (M1[0][0] * M2[0][0] +
	      M1[0][1] * M2[1][0] +
	      M1[0][2] * M2[2][0]);
  Mr[1][0] = (M1[1][0] * M2[0][0] +
	      M1[1][1] * M2[1][0] +
	      M1[1][2] * M2[2][0]);
  Mr[2][0] = (M1[2][0] * M2[0][0] +
	      M1[2][1] * M2[1][0] +
	      M1[2][2] * M2[2][0]);
  Mr[0][1] = (M1[0][0] * M2[0][1] +
	      M1[0][1] * M2[1][1] +
	      M1[0][2] * M2[2][1]);
  Mr[1][1] = (M1[1][0] * M2[0][1] +
	      M1[1][1] * M2[1][1] +
 	      M1[1][2] * M2[2][1]);
  Mr[2][1] = (M1[2][0] * M2[0][1] +
	      M1[2][1] * M2[1][1] +
	      M1[2][2] * M2[2][1]);
  Mr[0][2] = (M1[0][0] * M2[0][2] +
	      M1[0][1] * M2[1][2] +
	      M1[0][2] * M2[2][2]);
  Mr[1][2] = (M1[1][0] * M2[0][2] +
	      M1[1][1] * M2[1][2] +
	      M1[1][2] * M2[2][2]);
  Mr[2][2] = (M1[2][0] * M2[0][2] +
	      M1[2][1] * M2[1][2] +
	      M1[2][2] * M2[2][2]);
}


inline
void
MxMT(double Mr[3][3], double M1[3][3], double M2[3][3])
{
  Mr[0][0] = (M1[0][0] * M2[0][0] +
	      M1[0][1] * M2[0][1] +
	      M1[0][2] * M2[0][2]);
  Mr[1][0] = (M1[1][0] * M2[0][0] +
	      M1[1][1] * M2[0][1] +
	      M1[1][2] * M2[0][2]);
  Mr[2][0] = (M1[2][0] * M2[0][0] +
	      M1[2][1] * M2[0][1] +
	      M1[2][2] * M2[0][2]);
  Mr[0][1] = (M1[0][0] * M2[1][0] +
	      M1[0][1] * M2[1][1] +
	      M1[0][2] * M2[1][2]);
  Mr[1][1] = (M1[1][0] * M2[1][0] +
	      M1[1][1] * M2[1][1] +
 	      M1[1][2] * M2[1][2]);
  Mr[2][1] = (M1[2][0] * M2[1][0] +
	      M1[2][1] * M2[1][1] +
	      M1[2][2] * M2[1][2]);
  Mr[0][2] = (M1[0][0] * M2[2][0] +
	      M1[0][1] * M2[2][1] +
	      M1[0][2] * M2[2][2]);
  Mr[1][2] = (M1[1][0] * M2[2][0] +
	      M1[1][1] * M2[2][1] +
	      M1[1][2] * M2[2][2]);
  Mr[2][2] = (M1[2][0] * M2[2][0] +
	      M1[2][1] * M2[2][1] +
	      M1[2][2] * M2[2][2]);
}

inline
void
MTxM(double Mr[3][3], double M1[3][3], double M2[3][3])
{
  Mr[0][0] = (M1[0][0] * M2[0][0] +
	      M1[1][0] * M2[1][0] +
	      M1[2][0] * M2[2][0]);
  Mr[1][0] = (M1[0][1] * M2[0][0] +
	      M1[1][1] * M2[1][0] +
	      M1[2][1] * M2[2][0]);
  Mr[2][0] = (M1[0][2] * M2[0][0] +
	      M1[1][2] * M2[1][0] +
	      M1[2][2] * M2[2][0]);
  Mr[0][1] = (M1[0][0] * M2[0][1] +
	      M1[1][0] * M2[1][1] +
	      M1[2][0] * M2[2][1]);
  Mr[1][1] = (M1[0][1] * M2[0][1] +
	      M1[1][1] * M2[1][1] +
 	      M1[2][1] * M2[2][1]);
  Mr[2][1] = (M1[0][2] * M2[0][1] +
	      M1[1][2] * M2[1][1] +
	      M1[2][2] * M2[2][1]);
  Mr[0][2] = (M1[0][0] * M2[0][2] +
	      M1[1][0] * M2[1][2] +
	      M1[2][0] * M2[2][2]);
  Mr[1][2] = (M1[0][1] * M2[0][2] +
	      M1[1][1] * M2[1][2] +
	      M1[2][1] * M2[2][2]);
  Mr[2][2] = (M1[0][2] * M2[0][2] +
	      M1[1][2] * M2[1][2] +
	      M1[2][2] * M2[2][2]);
}

inline
void
MxVpV(double Vr[3], double M1[3][3], double V1[3], double V2[3])
{
  Vr[0] = (M1[0][0] * V1[0] +
	   M1[0][1] * V1[1] + 
	   M1[0][2] * V1[2] + 
	   V2[0]);
  Vr[1] = (M1[1][0] * V1[0] +
	   M1[1][1] * V1[1] + 
	   M1[1][2] * V1[2] + 
	   V2[1]);
  Vr[2] = (M1[2][0] * V1[0] +
	   M1[2][1] * V1[1] + 
	   M1[2][2] * V1[2] + 
	   V2[2]);
}

inline
void
MTxV(double Vr[3], double M1[3][3], double V1[3])
{
  Vr[0] = (M1[0][0] * V1[0] +
	   M1[1][0] * V1[1] + 
	   M1[2][0] * V1[2]); 
  Vr[1] = (M1[0][1] * V1[0] +
	   M1[1][1] * V1[1] + 
	   M1[2][1] * V1[2]);
  Vr[2] = (M1[0][2] * V1[0] +
	   M1[1][2] * V1[1] + 
	   M1[2][2] * V1[2]); 
}


inline
void
VmV(double Vr[3], double V1[3], double V2[3])
{
  Vr[0] = V1[0] - V2[0];
  Vr[1] = V1[1] - V2[1];
  Vr[2] = V1[2] - V2[2];
}


#endif
