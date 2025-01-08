/*************************************************************************\
>
> Copyright 2001 The University of North Carolina at Chapel Hill.
> All Rights Reserved.
>
> Permission to use, copy, modify OR distribute this software and its
> documentation for educational, research and non-profit purposes, without
> fee, and without a written agreement is hereby granted, provided that the
> above copyright notice and the following three paragraphs appear in all
> copies.
>
> IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL BE
> LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR
> CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE
> USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY
> OF NORTH CAROLINA HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH
> DAMAGES.
>
> THE UNIVERSITY OF NORTH CAROLINA SPECIFICALLY DISCLAIM ANY
> WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
> MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE SOFTWARE
> PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND THE UNIVERSITY OF
> NORTH CAROLINA HAS NO OBLIGATIONS TO PROVIDE MAINTENANCE, SUPPORT,
> UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
>
> The authors may be contacted via:
>
> US Mail: K. Hoff, A. Zaferakis, M. Lin, D. Manocha
> Department of Computer Science
> Sitterson Hall, CB #3175
> University of N. Carolina
> Chapel Hill, NC 27599-3175
>
> Phone: (919) 962-1749
>
> EMail: 
> geom@cs.unc.edu 	<mailto:geom@cs.unc.edu>
> hoff@cs.unc.edu 	<mailto:hoff@cs.unc.edu>
> andrewz@cs.unc.edu 	<mailto:andrewz@cs.unc.edu>
> lin@cs.unc.edu 		<mailto:lin@cs.unc.edu>
> dm@cs.unc.edu 		<mailto:dm@cs.unc.edu>
>
\**************************************************************************/

//============================================================================
// hier_collide_poly.cpp : determines if two simple polygons intersect.
//============================================================================

#include "hier_collide_poly.hpp"

struct Line
{
  float *L;         // PTR TO ARRAY TO 1ST ELT OF ARRAY OF 4 FLOATS OF LINE SEGMENT
};

struct MinMaxBoxNode
{
  float m[2],M[2];
  Line* Lines;      // PTR TO FIRST MinMaxBox CONTAINED IN THIS NODE (PTR INTO ARRAY OF MinMaxBoxes)
  int NumLines;
};

//----------------------------------------------------------------------------
// OVERLAPPING MIN/MAX BOX WILL BE MIN = max of mins, MAX = min of maxs
// IF MIN/MAX DOES NOT FORM A VALID MIN/MAX BOX (MAX<MIN), THEN A AND B DO NOT OVERLAP
// IF 0 IS RETURNED, (mx,my,Mx,My) IS INVALID
//----------------------------------------------------------------------------
static inline int MinMaxBoxOverlap(const float Am[2], const float AM[2],
                                   const float Bm[2], const float BM[2],
                                          float m[2],       float M[2])
{
  m[0] = (Am[0]>Bm[0])?Am[0]:Bm[0];
  M[0] = (AM[0]<BM[0])?AM[0]:BM[0];
  if (M[0]<m[0]) return(0);
  m[1] = (Am[1]>Bm[1])?Am[1]:Bm[1];
  M[1] = (AM[1]<BM[1])?AM[1]:BM[1];
  if (M[1]<m[1]) return(0);
  return(1);
}

//----------------------------------------------------------------------------
// GIVEN AN ARRAY OF MIN/MAX BOXES, RETURNS THE MIN/MAX EXTENTS OF THE ENTIRE SET
//----------------------------------------------------------------------------
void ComputeMinMax(Line *Lines, int N, float *m, float *M)
{
  if (N<1) return;
  if (Lines[0].L[0]<Lines[0].L[2]) m[0]=Lines[0].L[0],M[0]=Lines[0].L[2]; else m[0]=Lines[0].L[2],M[0]=Lines[0].L[0];
  if (Lines[0].L[1]<Lines[0].L[3]) m[1]=Lines[0].L[1],M[1]=Lines[0].L[3]; else m[1]=Lines[0].L[3],M[1]=Lines[0].L[1];
  for (int i=1; i<N; i++)
  {
    if (Lines[i].L[0]<m[0]) m[0]=Lines[i].L[0]; else if (Lines[i].L[0]>M[0]) M[0]=Lines[i].L[0];
    if (Lines[i].L[2]<m[0]) m[0]=Lines[i].L[2]; else if (Lines[i].L[2]>M[0]) M[0]=Lines[i].L[2];
    if (Lines[i].L[1]<m[1]) m[1]=Lines[i].L[1]; else if (Lines[i].L[1]>M[1]) M[1]=Lines[i].L[1];
    if (Lines[i].L[3]<m[1]) m[1]=Lines[i].L[3]; else if (Lines[i].L[3]>M[1]) M[1]=Lines[i].L[3];
  }
}

//----------------------------------------------------------------------------
// Given two lines segments (as an array of four floats), determine if they
// intersect.
//----------------------------------------------------------------------------
inline int LinesIntersect(float *a, float *b)
{
  float am,aM,bm,bM;
  if (a[0]<a[2]) am=a[0],aM=a[2]; else am=a[2],aM=a[0];
  if (b[0]<b[2]) bm=b[0],bM=b[2]; else bm=b[2],bM=b[0];
  if (bm>aM || bM<am) return(0);
  if (a[1]<a[3]) am=a[1],aM=a[3]; else am=a[3],aM=a[1];
  if (b[1]<b[3]) bm=b[1],bM=b[3]; else bm=b[3],bM=b[1];
  if (bm>aM || bM<am) return(0);

  float px,py,abx0=b[0]-a[0],aby0=b[1]-a[1];
  px=a[1]-a[3], py=a[2]-a[0];
  if ( (abx0*px + aby0*py) * ((b[2]-a[0])*px + (b[3]-a[1])*py) >= 0) return(0);
  px=b[1]-b[3], py=b[2]-b[0];
  if ( (abx0*px + aby0*py) * ((a[2]-b[0])*px + (a[3]-b[1])*py) <= 0) return(0);
  return(1);
}

//----------------------------------------------------------------------------
// Given two MinMaxBoxNodes containing 1 or more MinMaxBoxes, perform
// pairwise intersection tests and calls callback on intersecting ones.
// Callback gets passed the MinMaxBoxes and the intersecting region
//----------------------------------------------------------------------------
void Collide_Pairwise(Line *Alines, int NumInA, Line *Blines, int NumInB,
                      void (*IntersectCallback)(float *a, float *b))
{
  for (int i=0; i<NumInA; i++)
    for (int j=0; j<NumInB; j++)
      if (LinesIntersect(Alines[i].L,Blines[j].L))
        (*IntersectCallback)(Alines[i].L,Blines[j].L);
}

//----------------------------------------------------------------------------
// GIVEN A MinMaxBoxNode CONTAINING AT LEAST 2 MinMaxBoxes, PARTITIONS THE BOXES INTO TWO
// SETS SPLIT ALONG THE LONGEST BOX DIMENSION ABOUT THE BOX CENTER, TWO NEW CHILD MinMaxBoxNodes
// ARE CREATED CONTAINING THERE SET OF BOXES. IF LESS THAN 2 BOXES ARE IN THE GIVEN NODE, OR
// SET CREATED DURING PARTITIONING IS EMPTY, THE ROUTINE RETURNS 0. IF PARTITION IS SUCCESSFUL
// 1 IS RETURNED.
//----------------------------------------------------------------------------
int PartitionMinMaxBoxes(MinMaxBoxNode *Parent, MinMaxBoxNode* &Child1, MinMaxBoxNode* &Child2)
{
  if (Parent->NumLines<2) return(0);
  
  // CREATE PTR TO ARRAY OF BOXES TO BE PARTITIONED
  Line *Lines = Parent->Lines;

  // FIND SPLITTING AXIS
  int iAxis = (Parent->M[0]-Parent->m[0] > Parent->M[1]-Parent->m[1]) ? 0 : 1;

  // FIND SPLIT VALUE
  float SplitVal = (Parent->m[iAxis] + Parent->M[iAxis]);

  // PARTITION ALL BOXES BASED ON CENTER VALUE
  int i=0, j=Parent->NumLines-1;
  Line tmp;
  float CntrVal;
  while (i<j)
  {
    CntrVal = (Lines[i].L[iAxis] + Lines[i].L[iAxis+2]);  // COMPUTE CENTER VALUE FOR CURRENT BOX
    if (CntrVal < SplitVal)  // IF ALREADY IN PROPER PLACE, ADVANCE i
    {
      i++;
    }
    else  // BELONGS ON OTHER SIDE, SWAP i AND j, DECREMENT j, i MUST STILL BE TESTED
    {
      tmp=Lines[i];
      Lines[i]=Lines[j];
      Lines[j]=tmp;
      j--;
    }
  }

  // i==j WHEN WHILE TERMINATES, TEST LAST BOX TO DETERMINE PARTITION BOUNDARIES
  CntrVal = (Lines[i].L[iAxis] + Lines[i].L[iAxis]);
  int iChild2Lines = (CntrVal < SplitVal) ? i+1 : i;
  if (iChild2Lines<=0 || iChild2Lines>=Parent->NumLines) return(0);
  Child1 = new MinMaxBoxNode;
  Child1->Lines = Parent->Lines;
  Child1->NumLines = iChild2Lines;
  Child2 = new MinMaxBoxNode;
  Child2->Lines = &(Parent->Lines[iChild2Lines]);
  Child2->NumLines = Parent->NumLines - Child1->NumLines;

  // COMPUTE MIN/MAX Lines OF CHILD NODES
  ComputeMinMax(Child1->Lines,Child1->NumLines,Child1->m,Child1->M);
  ComputeMinMax(Child2->Lines,Child2->NumLines,Child2->m,Child2->M);

  return(1);
}

//----------------------------------------------------------------------------
// The main recursive collision detection routine. ALL THE WAY TO LEAVES.
//----------------------------------------------------------------------------
void RecursiveCollide(MinMaxBoxNode *Anode, MinMaxBoxNode *Bnode,
                      void (*IntersectCallback)(float *a, float *b))
{
  // CHECK IF NODES INTERSECT, IF THEY DO NOT JUST RETURN
  float m[2],M[2];  // STORAGE FOR OVERLAPPING REGION
  if (!MinMaxBoxOverlap(Anode->m,Anode->M,Bnode->m,Bnode->M,m,M)) return;

  // IF NODES INTERSECT, SPLIT LARGEST (BY VOLUME) AND RECURSIVE CHECK COLLISION AGAINST CHILDREN.
  MinMaxBoxNode *SplitNode;
  SplitNode = ((Anode->M[0]-Anode->m[0])*(Anode->M[1]-Anode->m[1]) > (Bnode->M[0]-Bnode->m[0])*(Bnode->M[1]-Bnode->m[1])) ? Anode : Bnode;

  // CHECK IF LARGEST CANNOT BE SPLIT, TRY TO SPLIT OTHER NODE, IF ALSO FAILS, REPORT INTERSECTION OF LEAVES!
  MinMaxBoxNode *Child1, *Child2;
  if (!PartitionMinMaxBoxes(SplitNode,Child1,Child2))
  {
    SplitNode = (SplitNode==Anode) ? Bnode : Anode;
    if (!PartitionMinMaxBoxes(SplitNode,Child1,Child2))
    {
//      if (Anode->NumLines==1 && Bnode->NumLines==1) (*IntersectCallback)(Anode->Lines[0].L,Bnode->Lines[0].L);
      Collide_Pairwise(Anode->Lines,Anode->NumLines,Bnode->Lines,Bnode->NumLines,IntersectCallback);
      return; 
    }
  }

  // AT THIS POINT TWO VALID CHILDREN HAVE BEEN CREATED, RECURSIVELY COLLIDE CHILDREN WITH NODE NOT SPLIT
  MinMaxBoxNode *NotSplitNode = (SplitNode==Anode) ? Bnode : Anode;
  RecursiveCollide(NotSplitNode,Child1,IntersectCallback);
  RecursiveCollide(NotSplitNode,Child2,IntersectCallback);
  delete Child1;
  delete Child2;
}

//----------------------------------------------------------------------------
// Given two objects composed of an array of MinMaxBoxes over their primitives,
// finds all boxes that intersect hierarchically and calls the intersection
// callback with each intersecting pair of lines.
//----------------------------------------------------------------------------
void Collide_Hierarchical(float *A, int NumPtsA, float *B, int NumPtsB, 
                          void (*IntersectCallback)(float *a, float *b))
{
  // CREATE BOXES FOR LINES OF POLYLINE
  Line *Alines = new Line[NumPtsA];
  Line *Blines = new Line[NumPtsB];
  int i,k;
  for (i=0, k=0; i<NumPtsA-1; i++, k+=2) Alines[i].L=&(A[k]);
  for (i=0, k=0; i<NumPtsB-1; i++, k+=2) Blines[i].L=&(B[k]);
  float LastLineA[] = {A[(NumPtsA*2)-2],A[(NumPtsA*2)-1],A[0],A[1]};
  float LastLineB[] = {B[(NumPtsB*2)-2],B[(NumPtsB*2)-1],B[0],B[1]};
  Alines[NumPtsA-1].L=LastLineA;
  Blines[NumPtsB-1].L=LastLineB;

  // CREATE ROOT NODES FOR EACH OBJECT
  MinMaxBoxNode RootA, RootB;
  RootA.Lines=Alines;
  RootA.NumLines=NumPtsA;
  RootB.Lines=Blines;
  RootB.NumLines=NumPtsB;
  ComputeMinMax(Alines,NumPtsA,RootA.m,RootA.M);
  ComputeMinMax(Blines,NumPtsB,RootB.m,RootB.M);

  // CALL RECURSIVE COLLISION DETECTION ROUTINE
  RecursiveCollide(&RootA,&RootB,IntersectCallback);

  delete[] Alines;
  delete[] Blines;
}
