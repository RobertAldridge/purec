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
// voronoi_pixel_error.cpp : routines for computing relationships between
//   pixel sampling error and distance error (unrelated to distance meshing error).
//   NOTE: both 2D and 3D routines are provided
//============================================================================

#include <math.h>

//******************************** 2D ROUTINES *******************************

//----------------------------------------------------------------------------
// Calculates the pixel resolution error (farthest a point in the window on the 
// slice can be from a pixel sample for a given min/max window and pixel sampling 
// resolution). Allows for non-uniform sampling where the aspect ratio between 
// the window and the pixel dimensions are not the same (not necessarily).
//   WorlddimX / worldDimY  !=  PixelDimX / PixelDimY
//----------------------------------------------------------------------------
float vdCalcPixelDistError2D(float MinX, float MinY, float MaxX, float MaxY,
                             int PixelDimX, int PixelDimY)
{
  float PixelWidth = (MaxX-MinX) / PixelDimX;
  float PixelHeight = (MaxY-MinY) / PixelDimY;
  float DiagonalLength = (float)sqrt(PixelWidth*PixelWidth + PixelHeight*PixelHeight);
  return( DiagonalLength * 0.5f );
}

//----------------------------------------------------------------------------
// Calculate pixel dimensions of the Voronoi diagram for the specified
// min/max box and distance error. Pixel sampling density
// is chosen so that no point in the min/max box is farther than DistError
// away from a sample point (DistError becomes half diagonal length of a
// pixel "square").
//----------------------------------------------------------------------------
void vdCalcResolution2D(float MinX, float MinY, float MaxX, float MaxY,
                        float PixelDistError, int *Width, int *Height)
{
  float PixelWidth = 1.41421356f*PixelDistError; // 2*(DistError/sqrt(2))
  float vDX=MaxX-MinX, vDY=MaxY-MinY;       // VIEWPORT DIMENSIONS
  float NumPixelsW = vDX / PixelWidth;
  float NumPixelsH = vDY / PixelWidth;
  int iNumPixelsW = (int)NumPixelsW;
  int iNumPixelsH = (int)NumPixelsH;
  *Width  = iNumPixelsW + (NumPixelsW-iNumPixelsW > 0);
  *Height = iNumPixelsH + (NumPixelsH-iNumPixelsH > 0);
}

//******************************** 3D ROUTINES *******************************

//----------------------------------------------------------------------------
// Computes the 2D slice distance error treshold from a 3D distance error.
// Assumes uniform sampling (all pixels are "cubes"). Given the VolumeDistError
// as half the diagonal length of the cube, computes half the diagonal length
// of one of the sides.
//----------------------------------------------------------------------------
float vdCalcSliceDistError(float VolumeDistError)
{
  return( VolumeDistError * (float)sqrt(2.0/3.0) );
}

//----------------------------------------------------------------------------
// Calculates the pixel resolution error (farthest a point in the min/max box 
// can be from a pixel sample for a given min/max box and pixel sampling 
// resolution). Allows for non-uniform sampling where the aspect ratio between 
// the min/max box and the pixel dimensions are not the same (not necessarily).
//----------------------------------------------------------------------------
float vdCalcPixelDistError3D(float MinX, float MinY, float MinZ,
                             float MaxX, float MaxY, float MaxZ,
                             int PixelDimX, int PixelDimY, int PixelDimZ)
{
  float PixelW = (MaxX-MinX) / PixelDimX;
  float PixelH = (MaxY-MinY) / PixelDimY;
  float PixelD = (MaxZ-MinZ) / PixelDimZ;
  float DiagonalLength = (float)sqrt(PixelW*PixelW + PixelH*PixelH + PixelD*PixelD);
  return( DiagonalLength * 0.5f );
}

//----------------------------------------------------------------------------
// Calculate pixel dimensions of the Voronoi diagram for the specified
// min/max box and distance error. Pixel sampling density
// is chosen so that no point in the min/max box is farther than DistError
// away from a sample point (DistError becomes half diagonal length of a
// pixel "square"). This error is defined for points on the 2D slice.
//----------------------------------------------------------------------------
void vdCalcResolution3D(float MinX, float MinY, float MinZ,
                        float MaxX, float MaxY, float MaxZ,
                        float PixelDistError, 
                        int *Width, int *Height, int *NumSlices)
{
  float PixelWidth = (2.0f/(float)sqrt(3.0f))*PixelDistError;  // 2*(DistError/sqrt(3))
  float vDX=MaxX-MinX, vDY=MaxY-MinY, vDZ=MaxZ-MinZ;           // VIEWPORT DIMENSIONS
  float NumPixelsW = vDX / PixelWidth;
  float NumPixelsH = vDY / PixelWidth;
  float NumPixelsD = vDZ / PixelWidth;
  int iNumPixelsW = (int)NumPixelsW;
  int iNumPixelsH = (int)NumPixelsH;
  int iNumPixelsD = (int)NumPixelsD;
  *Width     = iNumPixelsW + (NumPixelsW-iNumPixelsW > 0);
  *Height    = iNumPixelsH + (NumPixelsH-iNumPixelsH > 0);
  *NumSlices = iNumPixelsD + (NumPixelsD-iNumPixelsD > 0);
}
