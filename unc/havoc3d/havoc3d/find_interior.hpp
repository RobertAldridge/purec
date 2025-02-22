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
// find_interior.hpp : usage:
//   FindInterior *fi = new FindInterior(m,M,MinZ,ResX,ResY,
//                                       NumSlices,StencilMask);
//   fi->Begin(NumTris);
//     fi->AddTri(A,B,C);
//     ...
//   fi->End(&SliceZ);
//   do { 
//       // *** STENCIL BUFFER SET FOR SLICES z=SliceZ 
//   } while ( fi->NextSlice(&SliceZ) );
//   delete fi;
//============================================================================

#ifndef _FINDINTERIOR_
#define _FINDINTERIOR_

class FindInterior
{
  private:

    struct Triangle
    {
      float *A, *B, *C;  // PTR TO ARRAY OF 3 FLOATS EACH
      float mz, Mz;      // MIN/MAX Z VALUES OF THE TRIANGLE
    };

    struct TriNode
    {
      Triangle *Tri;
      TriNode *Link;
    };

    TriNode* *Buckets;
    int NumBuckets;

    float dz, StartZ, EndZ;  // VARIABLES USED FOR SWEEPING SLAB

    void SortByMinZ_Insertion();
    void UpdateActiveSites(float MinZ, float MaxZ);
    void OPENGL_STATE_BEGIN();
    void OPENGL_STATE_END();

  public:

    Triangle **Tris;
    int NumTris;
    int iStart,iEnd;         // INDICES INTO TRIS ARRAY TO DENOTE
                             // CULLED, ACTIVE, AND CANDIDATE
                             // TRIANGLES

    float m[3], M[3], MinZ;  // BOUNDING-BOX INTERSECTION

    int W, H, NumSlices;
    unsigned char StencilMask;

    FindInterior(const float min[3], const float max[3], float minz, int w,
                 int h, int numslices, unsigned char StencilMask);
    ~FindInterior();
    void Begin(int numtris);
    void AddTri(float *A, float *B, float *C);
    void End(float *FirstSliceZ);
    int NextSlice(float *SliceZ);
    float GetCurrentSliceZ() { return(StartZ); }
    float GetChangeInZ() { return(dz); }
};

#endif

