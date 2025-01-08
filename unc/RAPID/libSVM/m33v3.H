#ifndef M33V3_H
#define M33V3_H

#include "m33.H"
#include "v3.H"
#include <string.h>
#include <strings.h>

v3 
solve_system(const m33 &A, const v3 &b);

v3
operator*(const m33 &ma, const v3 &va);

void
ptx(m33 *M, v3 *V, double t);

void
pty(m33 *M, v3 *V, double t);

void
ptz(m33 *M, v3 *V, double t);

void
ltx(m33 *M, v3 *V, double t);

void
lty(m33 *M, v3 *V, double t);

void
ltz(m33 *M, v3 *V, double t);


void
prx(m33 *M, v3 *V, double t);

void
pry(m33 *M, v3 *V, double t);

void
prz(m33 *M, v3 *V, double t);

void
lrx(m33 *M, v3 *V, double t);

void
lry(m33 *M, v3 *V, double t);

void
lrz(m33 *M, v3 *V, double t);

void
eigen(m33 *evec, v3 *eval, m33 M);

m33
skew(v3 s);

m33 
orthonormalize(m33 m);

/*

   make_xform

   make_xform interprets a string as a sequence of
   translations and rotations, and creates a rotation matrix / translation 
   vector pair which accomplishes that aggregate transformation.

   The string specifies a sequence of transforms which move the 
   parent CS axes to where the object's CS axes are.  The matrix R and
   vector T which are returned will, with multiplication and addition,
   transform a point from the local object's CS to the parent CS like so:

       x_p = R * x_l + T

   To perform the inverse tranformation, from parent CS to local CS,
   do the following:

       x_l = R.T() * (x_p - T)

   where R.T() is the transpose of R.

   The string is a space-delimited sequence of tokens and values.
   There are twelve allowable tokens:

       prx pry prz       ptx pty ptz
       lrx lry lrz       ltx lty ltz

    Each token is of the form 'abc', where 'a' may be 'p' (parent) or 
    'l' (local), 'b' may be 'r' (rotation) or 't' (translation) , 
    and 'c' may be 'x', 'y', or 'z' (which axis).

    Each token is followed by a value, which has units of degrees
    for rotations and meters (conventionally) for translations.

    So the token / value pair 'prx 45.0' means "rotation about the 
    parent's x-axis by 45 degrees", and 'tlz 0.10' means "translation
    along local z-axis by 10 centimeters".  Remember, 0.10 meters
    is 10 cm.  

    The sequence "prx 63.4 prx 72.0 lrz 45.0 ltz 0.017" means
    "rotation around parent's x-axis by 6

    AN EXAMPLE:

    There is a stop sign on the corner of North St. and West St. 

    The stop sign has a local coordinate
    system: origin is in the middle of the octagonal sign, x-axis points 
    toward the 'P' (to the right as you face the sign), y-axis points upward
    (to the top of the sign), and the z-axis points out of the red octagonal 
    face (toward you as you face the sign).

    The stop sign "lives" in its parent coordinate system.  The origin
    of the parent CS is in the middle of the intersection of 
    North Street and West Street.  The parent x-axis points north, 
    the y-axis points west, and the z-axis points skyward.

                                                                 
                                 North                                      
                                  Street                                    

                                  |   |                                     
                                  |   |                                     
                                  |   |                                     
                                  |   |                                     
                                  |   |                                     
                            ------+   +------                                
                     West Street                                           
                            ------+   +------                                
                                  |   |S                                    
                                  |   |                                     
                                  |   |                                     

    The stop sign is planted 4 meters south and 3 meters east of the 
    center of the intersection, and the center is 2 meters above the
    ground.  

    OK.  What string of tokens/values describes the stop sign's
    placement in the intersection?  There is no single right answer.

    First, imagine placing the stop sign so that its origin was at the 
    parent's origin and so that the stop sign's local coordinate axes 
    line up with the parent's axes (x along x, y along y, and z 
    along z).  This would put the sign lying down in the middle of the
    intersection, face up, so that the letters run south to north as you
    read.  The base of the sign shaft points eastward.

    Now, the sequence of transforms.  First translate the sign to the
    corner: "ptx -4.0 pty -3.0".  Here, "ptx" means "move north".  Moving
    north by -3 meters is really moving south 3 meters.  

    Now, raise the center of the sign with "ptz 2.0".  The sign is now
    levitating 2 m above ground, red side facing skyward, with the foot
    of the sign's pole still pointing eastward.  To get the sign upright, 
    we can rotate around the *sign's* x-axis by 90 degrees, "lrx 90".
    We also had the option of using "prx 90", since the x-axes of the
    world and the sign were still aligned.

    Now the sign is in the right place, planted in the ground, but it
    is facing eastward, and we want it to face southward.  Do this
    with "prz -90".

    So the string to pass to make_xform is

        "ptx -4 pty -3 ptz 2 lrx 90 prz -90"

    This yields

    R =  0  0 -1    V = -3
        -1  0  0         4
	 0  1  0         4

    The matrix R and vector T have been set to affect that transformation.
    With p = R * l + T the point l is transformed from the local CS (the
    stop sign) into the parent's CS (the street).  For example, suppose 
    the location of the bottom of the 'P' in 'STOP' is at 
    l=(0.3,-0.1,0.0) in the stop sign's CS.  Then p = R * l + T gets us:

    l =  0.3   p =  -3.0
        -0.1         3.7
	 0.0         3.9

    p is the location for the bottom of the 'P' in the world (street) CS.

    ANOTHER EXAMPLE:

 
    Now suppose a road runs                   /                           
    north-north-east.  The road has          /         NORTH = x          
    a coordinate system: origin             /                             
    is at a marker in middle of the        /                 ^             
    road, x-axis points north, y-axis     /                  |             
    points west, and z-axis              /                   |             
    points skyward.                     + MARKER        <----+             
                                       /                      
    About 100m from the marker        /               WEST = y            
    there is a line in the           /
    road.  Beside the road          /
    where the line is, there       /       
    is a stop sign.  It is 2m     /                                       
    from the center of the       /                                        
    road.                       /   + SIGN                                
                               /                                          
    The sign used to stand
    2m tall, facing the 
    NNE-bound traffic, but somebody bumped into it, causing it to tilt 
    back by 10 degrees.  There is still 2m of shaft from ground to the 
    center of the sign, but the center of the sign is no longer quite
    2m above the ground (it is now 2*cos(10 deg) meters high).
    The sign has the same local coordinate system as in the previous
    example.

    How do we find the matrix R and vector T which transforms a point 
    from the sign's CS to the road's CS with p = R * l + T ?
                                   
    First imagine the sign at the "home" position as before: lying face
    up on top of the marker with foot of shaft pointing eastward.

    Now, swing the shaft so that it points along the road toward the 
    line:  "prz -112.5".

    Now, move the sign along its LOCAL y axis until it is at the line
    in the road: "lty -100".  

    Now, slide the sign off to side to where it should be planted: "ltx 2".

    Now the sign's origin is where it should be planted; that is, where
    the shaft should enter the ground.  We would ordinarily rotate the sign
    so that it would be vertical, but since it got knocked back by 10 
    degrees, we will rotate that much less: "lrx 80".

    Now the sign has the correct orientation, and its origin is where the
    shaft should enter the ground.  Since there should be two meters of
    shaft between the center of the sign and the plant point, we move
    the sign two meters along the shaft (local y axis): "lty 2".

    Were done.  The string is "prz 112.5 lty -100 ltx 2 lrx 80 lty 2".

    Passed to make_xform, this yields 

    R = -0.382683 -0.160430 0.909844     T = 91.301726
         0.923880 -0.066452 0.376870         39.983198
         0.000000  0.984808 0.173648          1.969616

    T is the origin of the sign as expressed in the parent (street)
    coordination.  Notice that the z-component, which in this case
    is the height of the sign's center above ground, is 2*cos(10 deg).

    The columns of R are the sign x, y, and z, axis directions as expressed
    in the world CS.  Notice the 0.00000 term in R.  It occurs in the 
    x-column, indicating that the SIGN's x-axis parallels the world's
    x-y planes (the world z-coordinate doesn't change as we move along
    the sign's x-axis).

*/

void
make_xform(m33 *R, v3 *T, const char *str);

#endif
/* M33V3_H */










