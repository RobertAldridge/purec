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
// deformable_body.hpp
//============================================================================

#ifndef DEFORMABLE_BODY
#define DEFORMABLE_BODY

class DeformableBody
{
  private:

    void ComputeRestingLengths();
    float PtLineSegDist2(float Px, float Py, float Ax, float Ay, float Bx, float By, float *t);
    int FindNearestLineSegment(float Px, float Py, float *t);

  public:

    float kGrav, kDrag, kCollide, kFriction, kSpring, kSpringDamp;

    float *Pts;
    float *Vels;
    float *Forces;
    float *RestingLengths;
    int NumPts, NumPtsAlloced;

    DeformableBody(int numpts, float kgrav=0.005f, float kdrag=0.05f, float kcollide=0.8f,
                   float kfriction=0.8f, float kspring=0.9f, float kspringdamp=0.8f);
    ~DeformableBody();
    void AddPt(float x, float y);
    void ComputeForces();
    void TakeEulerStep(float dt);
    void Simulate(float dt);
    void ApplyForceAtPt(float Px, float Py, float Fx, float Fy);
    void ComputeMinMaxBox(float *mx, float *my, float *Mx, float *My);
    void Display();
    void DisplayForces();
};

#endif
