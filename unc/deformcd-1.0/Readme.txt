/*************************************************************************\

  Copyright 2007 The University of North Carolina at Chapel Hill.
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

  THE UNIVERSITY OF NORTH CAROLINA SPECIFICALLY DISCLAIM ANY
  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE
  PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND THE UNIVERSITY OF
  NORTH CAROLINA HAS NO OBLIGATIONS TO PROVIDE MAINTENANCE, SUPPORT,
  UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

  The authors may be contacted via:

  US Mail:             GAMMA Research Group at UNC
                       Department of Computer Science
                       Sitterson Hall, CB #3175
                       University of N. Carolina
                       Chapel Hill, NC 27599-3175

  Phone:               (919)962-1749

  EMail:              {geom, tangm}@cs.unc.edu


\**************************************************************************/

This is the deformCD collision detection package.

------------------------------------------------------------------------------
1. Installation Instructions:
------------------------------------------------------------------------------

Version 1.0 of deformCD is developed by Visual Studio 2005, so currently it
 can only be used on Windows platform.
 
For external calling, the following directories will be used:
	inc\				#head files
	lib\release\			#release version of rapid_fit.lib
	lib\debug\			##debug version of rapid_fit.lib

For rebuilding or runing the demos:

Open deformCD.sln, then build and run it.
To compile and build deformCD, OpenGL will be used.
To compile and build demos, NVIDIA SDK 9.5 will be used for visulization.

To run the demos, please download data files from fellowing links:
a. download http://gamma.cs.unc.edu/SR/benchmarks/dragbun.plys.zip (76.1 MB, 79,877,730 bytes)
   and put the extracted ply files into data\dragbun.plys\
b. download http://gamma.cs.unc.edu/SR/benchmarks/cloth_ball.plys.zip (100 MB, 104,915,287 bytes)
   and put the extracted ply files into data\cloth_ball.plys\
c. download http://gamma.cs.unc.edu/SR/benchmarks/balls16_.plys.zip (47.2 MB, 49,512,531 bytes)
   and put the extracted ply files into ../data/balls16_.plys/

After get the data files, just click the bat files in bin directory:
    run-demo-balls.bat
    run-demo-cloth.bat
    run-demo-dragon.bat
for runing demos.

------------------------------------------------------------------------------
2. Directory Contents:
------------------------------------------------------------------------------

rapid_fit\
	rapid_fit.sln			#Visual Studio 2005 project file		
	bin\				#executable
		release\	
		debug\	
	data\		
		balls16_.plys\       #data files for Demo-balls, please download from
		                     #http://gamma.cs.unc.edu/SR/benchmarks/balls16_.plys.zip
		                     #76.1 MB (79,877,730 bytes)
		                     
		cloth_ball.plys\     #data files for Demo-cloth, please download from
		                     #http://gamma.cs.unc.edu/SR/benchmarks/cloth_ball.plys.zip
		                     #100 MB (104,915,287 bytes)
		                     
		dragbun.plys\        #data files for Demo-cloth, please download from
		                     #http://gamma.cs.unc.edu/SR/benchmarks/dragbun.plys.zip
		                     #47.2 MB (49,512,531 bytes)
		                     

		  
	demo-balls\         #project & source files for move balls
	    balls.cpp
	    Demo-balls.vcproj
	    
	demo-cloth\         #project & source files for dropping cloth collison with a sphere
	    cloth.cpp
	    Demo-cloth.vcproj
	    
	demo-dragon\        #project & source files for a falling bunny collision with a dragon
	    dragon.cpp
	    Demo-dragon.vcproj
	     
	inc\				#header files for external calling
		model_shl.h
		model.h
		vec4d.h
	lib\				#library files
		release\	
		debug\	
	rapid_fit\			# source files for building rapid_fit
		aabb.[cpp, h]
		app.[cpp, h]
		bvh.[cpp, h]
		collide.[cpp, h]
		model.[cpp, h]
		model_shl.[cpp, h]
		rapid_fit.vcproj
		ReadMe.txt
		tri_contact.cpp
		vec4d.h
	shared\				# files used for Demo1 & Demo2
		glut_client_shl.cpp
		logger.h
		timing.h

------------------------------------------------------------------------------
3. Who will need it?
------------------------------------------------------------------------------
I assume the reader is familiar with collision detection, and RAPID.
In fact, deformCD is just designed for the situations where the model for 
collision detection is undergoes minor deformations.RAPID is mainly 
designed for rigid models, and builds an OBBTree. On the other hand,
deformCD uses a combination of AABB hierarchies and recomputes them every
frame using rebuilding or refitting algorithms.


------------------------------------------------------------------------------
4. How to use it?
------------------------------------------------------------------------------

a, defining the deformable model:

ModelShl *mdl = new ModelShl(num_frame, num_vtx, vtxs_frames, num_tri, tris);
// num_frame:   totally frame number
// num_vtx:     how many vertices of the model
// vtxs_frames: all the vertices 
//               sizeof(vtxs_frames)  = num_frame*num_vtx*3*sizeof(double)
// num_tri:     how many triangles of the model
// tris:         sizeof(tris) = num_tri*3*sizeof(unsigned int)
// 

// if you don't want use the vec3f class, you can directly use an array of doubles:
// the memories can be destorired just after the ModelShl construction, it makes a copy 
ModelShl::ModelShl(int num_frame, int num_vtx, double *vtxs_frames, int num_tri, unsigned int *tris);

b, initialize the BVH

s_mdl1->BuildBVH();
s_mdl2->BuildBVH();

c, update it with interpolation:

s_mdl1->Deform(float(t), circle);
s_mdl2->Deform(float(t), circle);
	
//[0-num_frame] is mapped to [0-1], so float(t)/circle is used to decide the deformation.

d, refit the BVH	

s_mdl1->RefitBVH();
s_mdl2->RefitBVH();

e, collision detection:

Collide(s_mdl1, s_mdl2);

f, get collision results:

void printCollideInfo()
{
	int num_contacts = s_mdl1->NumContact();

	unsigned int id1, id2;
	printf("Start list contact info (totally %d contacts):\n", num_contacts);
	for (int i=0; i<num_contacts; i++) {
		s_mdl1->GetContact(i, id1, id2);
		printf("Tri %4d <-------> Tri %4d\n", id1, id2);
	}
	printf("End list contact info.\n");
}

e, some visualization functions

// reset and mark collision related vertices
mdl1->ResetColor(255, 0, 0);
mdl2->ResetColor(255, 0, 255);
mdl1->Collide(mdl2);
mdl1->ColorCollide();

// display BVH to specified level
s_mdl1->DisplayBVH(level);

// display the collision related vertices in green
s_mdl1->DisplayColor();

------------------------------------------------------------------------------
5. bug report
------------------------------------------------------------------------------

We would be interested in knowing more about your application as well as any
bugs you may encounter in the collision detection library. You can
report them by sending e-mail to geom@cs.unc.edu.

------------------------------------------------------------------------------
6. release notes
------------------------------------------------------------------------------

Release 1.0: 2007/7/10
