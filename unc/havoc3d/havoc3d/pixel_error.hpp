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
// voronoi_pixel_error.hpp : routines for computing relationships between
//   pixel sampling error and distance error (unrelated to distance meshing error).
//   NOTE: both 2D and 3D routines are provided
//============================================================================

//******************************** 2D ROUTINES *******************************

float vdCalcPixelDistError2D(float MinX, float MinY, float MaxX, float MaxY,
                             int PixelDimX, int PixelDimY);

void vdCalcResolution2D(float MinX, float MinY, float MaxX, float MaxY,
                        float PixelDistError, int *Width, int *Height);

//******************************** 3D ROUTINES *******************************

float vdCalcSliceDistError(float VolumeDistError);

float vdCalcPixelDistError3D(float MinX, float MinY, float MinZ,
                             float MaxX, float MaxY, float MaxZ,
                             int PixelDimX, int PixelDimY, int PixelDimZ);

void vdCalcResolution3D(float MinX, float MinY, float MinZ,
                        float MaxX, float MaxY, float MaxZ,
                        float PixelDistError, 
                        int *Width, int *Height, int *NumSlices);
