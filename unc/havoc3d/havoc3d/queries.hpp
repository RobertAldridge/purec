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
// voronoi_queries.hpp
//============================================================================

void vdReadbackIDs(unsigned char* &IDs, int W, int H);

void vdReadbackDists(float* &Dists, int W, int H, float MaxDist);

void vdReadbackID(unsigned char *ID, int Px, int Py);

void vdReadbackDist(float *Dist, int Px, int Py, float MaxDist);

void vdNearestPixel(float wx, float wy,                              // WORLD POSITION IN MIN/MAX BOX
                    float MinX, float MinY, float MaxX, float MaxY,  // MIN/MAX BOX
                    int W, int H,                                    // PIXEL DIMENSION OF VOR DIAG
                    int &px, int &py);                               // RETURNED NEAREST PIXEL LOCATION

void vdReadbackID(unsigned char *ID, 
                  float wx, float wy,
                  float MinX, float MinY, float MaxX, float MaxY,
                  int W, int H);

void vdReadbackDist(float *Dist, float MaxDist,
                    float wx, float wy,
                    float MinX, float MinY, float MaxX, float MaxY,
                    int W, int H);
