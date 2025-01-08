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
// find_interior.cpp
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "find_interior.hpp"

// FINDS INTERIOR WITHIN SPECIFIED MIN/MAX BOX. USER ALSO MUST PROVIDE
// THE MIN Z-VALUE OF THE OBJECT AND THE "VOXEL" DIMENSIONS OF THE
// INTERSECTION REGION. INTERIOR FOR EACH SLICE IS DEFINED AS PIXELS
// WHOSE STENCIL BITS ARE SET (WHICH ONES ARE DETERMINED BY THE
// STENCIL MASK)
FindInterior::FindInterior(const float min[3], const float max[3],
                           float minz, int w, int h, int numslices,
                           unsigned char stencilmask)
{
  GLint NumStencilBits;
  glGetIntegerv(GL_STENCIL_BITS,&NumStencilBits);
  if (NumStencilBits<1)
      printf("No stencil buffer available! Add GLUT_STENCIL!\n");

  if (numslices==0)
      printf("ERROR: FindInterior::FindInterior: numslices==0!\n");
  if (w==0 || h==0)
      printf("ERROR: FindInterior::FindInterior: w or h == 0!\n");

  m[0]=min[0]; m[1]=min[1]; m[2]=min[2];
  M[0]=max[0]; M[1]=max[1]; M[2]=max[2];
  MinZ=minz;
  Tris=NULL;
  NumTris=0;
  W=w;
  H=h;
  NumSlices=numslices;
  StencilMask=stencilmask;

  // INITIALIZE THE SIZE OF EACH SWEEPING SLAB (dz) AND THE START/END
  // Z VALUES FOR FIRST SLAB
  dz=(M[2]-m[2])/(float)NumSlices;
  StartZ=m[2]+dz*0.5f;  // VOXEL CENTER!
  EndZ=StartZ+dz;
}

FindInterior::~FindInterior()
{
  if (Tris)
  {
    for (int i=0; i<NumTris; i++) if (Tris[i]) delete Tris[i];
    delete[] Tris;
  }
}

void FindInterior::Begin(int numtris)
{
  // CREATE BUCKETS FOR SORTING
  NumBuckets = (numtris/4) + 1;
  if (NumBuckets==0) printf("ERROR: FindInterior::Begin: NumBuckets==0!\n");
  Buckets = new TriNode*[NumBuckets];
  for (int i=0; i<NumBuckets; i++) Buckets[i]=NULL;

  // INITIALIZE VIEWING FRUSTUM (NEAR AND FAR SET TO AREA BEYOND FIRST
  // SLAB OUT TO MinZ)
  OPENGL_STATE_BEGIN();
  glStencilOp(GL_KEEP,GL_REPLACE,GL_REPLACE);  // CLEAR STENCIL BUFFER TO ZERO
  glRectf(-1,-1,1,1);
  glStencilOp(GL_KEEP,GL_INVERT,GL_INVERT);    // INVERT STENCIL FOR
                                               // ALL WRITTEN PIXELS

  glMatrixMode(GL_PROJECTION); 
  glOrtho(m[0],M[0],m[1],M[1],-StartZ,-MinZ);
  glBegin(GL_TRIANGLES);
}

void FindInterior::AddTri(float *A, float *B, float *C)
{
  // CULL TRIANGLE AGAINST INTERSECTION BOX (mx,my,-INFINITY),(Mx,My,Mz)
  if (A[0]>M[0] && B[0]>M[0] && C[0]>M[0]) return;
  if (A[1]>M[1] && B[1]>M[1] && C[1]>M[1]) return;
  if (A[2]>M[2] && B[2]>M[2] && C[2]>M[2]) return;
  if (A[0]<m[0] && B[0]<m[0] && C[0]<m[0]) return;
  if (A[1]<m[1] && B[1]<m[1] && C[1]<m[1]) return;

  // TRIANGLES WITH ALL MIN Z-VALUE < MIN/MAX BOX MIN Z-VAL AND
  // TRIANGLES IN FIRST SLAB (z in [MinZ,StartZ]) ARE RENDERED
  // DIRECTLY (MAX Z-VALUE < FIRST SLAB START Z-VAL DO NOT NEED TO BE
  // SORTED).  OTHERWISE, TRIANGLE MUST BE ADDED TO BUCKETS FOR
  // SORTING (BASED ON MIN Z-VALUE).
  if (A[2]<=StartZ || B[2]<=StartZ || C[2]<=StartZ)
  {
    glVertex3fv(A);
    glVertex3fv(B);
    glVertex3fv(C);
  }

  // STORE AND BUCKET-SORT ALL TRIANGLES THAT ARE INSIDE MIN/MAX BOX
  // (z in (StartZ,M[2])).  DO NOT NEED TO INCLUDE TRIANGLES WHOSE MAX
  // VALUE TOUCHES MIN Z OF MIN/MAX BOX (ALREADY RENDERED, AVOID
  // OVERWRITE)
  if (A[2]>StartZ || B[2]>StartZ || C[2]>StartZ)
  {
    // CREATE NEW TRIANGLE
    Triangle* Tri = new Triangle;
    Tri->A = A;
    Tri->B = B;
    Tri->C = C;

    Tri->mz = (A[2]<B[2]) ?
              ( (A[2]<C[2])?A[2]:C[2] ) :
              ( (B[2]<C[2])?B[2]:C[2] );

    Tri->Mz = (A[2]>B[2]) ?
              ( (A[2]>C[2])?A[2]:C[2] ) :
              ( (B[2]>C[2])?B[2]:C[2] );

    // BUCKET BASE ON TRIANGLE'S MIN Z-VALUE
    float mz = Tri->mz;
    int iBucket;
    if (mz<=m[2]) iBucket=0;
    else if (mz>=M[2]) iBucket=NumBuckets-1;
    else iBucket=(int)( (mz-m[2])/(M[2]-m[2])*NumBuckets ); 

    // ADD NEW NODE TO HEAD OF BUCKET
    TriNode *NewNode = new TriNode;
    NewNode->Tri=Tri;
    NewNode->Link=Buckets[iBucket];
    Buckets[iBucket]=NewNode;

    NumTris++;
  }
}

// STENCIL INITIALIZED TO PARITY OF TRIANGLES BEYOND Min/Max BOX MIN Z-VALUE
void FindInterior::End(float *FirstSliceZ)
{
  // RESET GL STATE
  glEnd();  // GL_TRIANGLES
  OPENGL_STATE_END();

  // SET RETURN SLICE Z PLANE Z-VALUE
  *FirstSliceZ = StartZ;

  // ALLOCATE TRIS ARRAY. INITIALIZE VORONOI ACTIVE AND CANDIDATE
  // TRIANGLE LISTS.  INITIALLY NO SITES ARE ACTIVE, ALL ARE
  // CANDIDATES
  iStart=0;
  iEnd=-1;
  if (NumTris==0) { Tris=NULL; delete[] Buckets; return; }
  Tris = new Triangle*[NumTris];

  // BUCKET SORT, MERGE BUCKET LISTS INTO Tris ARRAY, DELETE BUCKETS
  // TRAVERSE BUCKETS AND INSERT INTO TRIS ARRAY IN ORDER (CANDIDATE
  // SECTION), DELETE DURING TRAVERSAL
  int j=0;
  for (int i=0; i<NumBuckets; i++)
  {
    TriNode *n=Buckets[i], *p;
    while(n!=NULL)
    { 
      Tris[j]=n->Tri; j++;
      p=n; n=n->Link; delete p; 
    }
  }
  delete[] Buckets;

  // SORT PARTIALLY SORTED CANDIDATE TRIANGLES (DO NOT SORT THOSE
  // ALREADY IN ACTIVE LIST [iStart,iEnd])
  SortByMinZ_Insertion();
}

// SORT SITES BY MIN Z (INSERTION SORT - FAST WHEN ALMOST SORTED)
void FindInterior::SortByMinZ_Insertion()
{
  Triangle* t;
  int j,j_1;
  for (int i=1; i<NumTris; i++)
    for (j=i; (j>0) && (Tris[j]->mz < Tris[j-1]->mz); j--)
    {
      j_1=j-1;
      t=Tris[j]; Tris[j]=Tris[j_1]; Tris[j_1]=t;  // SWAP TRIANGLES j AND j-1
    }
}

// SWEEPING PLANE IS ALWAYS ASSUMED TO BE MOVING IN A POSITIVE Z
// DIRECTION.  SUBSEQUENT [MinZ,MaxZ] INTERVALS LEAVE NO "GAPS". NEXT
// SLICE'S MinZ SHOULD BE LAST SLICE'S MaxZ
// SITES ARE ASSUMED TO ALREADY BE SORTED BY MIN Z.
// SITES IN [0,iStart-1] HAVE BEEN CULLED PERMANENTLY
// SITES IN [iStart,iEnd] ARE THE CURRENTLY ACTIVE SITES
// SITES IN [iEnd+1,NumSites-1] ARE CANDIDATE FUTURE SITES TO BE ADDED TO ACTIVE LIST
// Initially, all sites are candidates (iStart=0,iEnd=-1)
void FindInterior::UpdateActiveSites(float MinZ, float MaxZ)
{
  int i;
  Triangle* t;

  // CHECK IF ACTIVE SITES IN [iStart,iEnd] ARE STILL ACTIVE. IF
  // SliceZ HAS PROGRESSED BEYOND MAX Z MOVE CULLED SITES TO FRONT OF
  // LIST AND UPDATE iStart
  for (i=iStart; i<=iEnd; i++)
    if (MinZ>=Tris[i]->Mz) // SWAP i WITH iStart, INCR iStart. ">=" TO
                           // CULL TRIS TOUCHING MinZ BOUNDARY
    {
      t=Tris[i]; Tris[i]=Tris[iStart]; Tris[iStart]=t;
      iStart++;
    }
  
  // SEE IF ANY NEW SITES IN [iEnd+1,NumSites-1] ARE ACTIVE. IF MaxZ
  // HAS PROGRESSED BEYOND TRI MIN Z THIS MAY BE CONSERVATIVE, SINCE
  // IT IS POSSIBLE FOR MinZ TO PROGRESS BEYOND TRI MAX Z.
  iEnd++;
  while(iEnd<NumTris && MaxZ>=Tris[iEnd]->mz) iEnd++;
  iEnd--;
}

int FindInterior::NextSlice(float *SliceZ)
{
  // SET RETURN SLICE Z PLANE Z-VALUE
  *SliceZ = EndZ;

  // RETURN ZERO IF NO MORE SLICES
  if (EndZ>M[2]) return(0);

  // UPDATE ACTIVE LIST OF TRIANGLES FOR NEXT SLICE
  UpdateActiveSites(StartZ,EndZ);

  // SETUP VIEWING MATRICES AND DRAW ACTIVE TRIS
  OPENGL_STATE_BEGIN();
  glMatrixMode(GL_PROJECTION); 
  glOrtho(m[0],M[0],m[1],M[1],-EndZ,-StartZ);
  glBegin(GL_TRIANGLES);
  for (int j=iStart; j<=iEnd; j++)
  {
    glVertex3fv(Tris[j]->A);
    glVertex3fv(Tris[j]->B);
    glVertex3fv(Tris[j]->C);
  }
  glEnd();
  OPENGL_STATE_END();

  // GO TO NEXT SLICE
  StartZ=EndZ;
  EndZ=StartZ+dz;

  return(1);
}

void FindInterior::OPENGL_STATE_BEGIN()
{
  glPushAttrib(GL_POLYGON_BIT);
    glDisable(GL_CULL_FACE);
  glPushAttrib(GL_VIEWPORT_BIT);
    glViewport(0,0,W,H);
  glPushAttrib(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(0);
  glPushAttrib(GL_COLOR_BUFFER_BIT);
    glColorMask(0,0,0,0);
  glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
  glMatrixMode(GL_PROJECTION); 
    glPushMatrix();
    glLoadIdentity();
  glPushAttrib(GL_STENCIL_BUFFER_BIT);
    glEnable(GL_STENCIL_TEST);
    glStencilMask(StencilMask);
    glStencilFunc(GL_ALWAYS,0,0);
    glStencilOp(GL_KEEP,GL_INVERT,GL_INVERT);
}

void FindInterior::OPENGL_STATE_END()
{
  glPopAttrib();   // GL_STENCIL_BUFFER_BIT
  glMatrixMode(GL_PROJECTION); 
    glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
  glPopAttrib();   // GL_COLOR_BUFFER_BIT
  glPopAttrib();   // GL_DEPTH_BUFFER_BIT
  glPopAttrib();   // GL_VIEWPORT_BIT
  glPopAttrib();   // GL_POLYGON_BIT
}
