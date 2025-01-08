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

#include <windows.h>
#include <gl/gl.h>

#include <math.h>
#include <stdio.h>
#include <assert.h>

#include "vec4d.h"
#include "model_shl.h"

#include "plyfile.h"
#pragma warning(disable: 4996)

#include <vector>

typedef struct PLYVertex{
	float coords[3];
	unsigned char color[3];
	void *other_props;		
} PLYVertex;

typedef struct PLYFace{
	unsigned char nverts;
	int *verts;		
	void *other_props;
} PLYFace;

#include "logger.h"
extern Logger *logger;

PlyProperty vert_props[] = { /* list of property information for a vertex */
	{"x", PLY_FLOAT, PLY_FLOAT, 0, 0, 0, 0, 0},
	{"y", PLY_FLOAT, PLY_FLOAT, 4, 0, 0, 0, 0},
	{"z", PLY_FLOAT, PLY_FLOAT, 8, 0, 0, 0, 0},
	{"red", PLY_UCHAR, PLY_UCHAR, (int)offsetof(PLYVertex,color[0]), 0, 0, 0, 0},
	{"green", PLY_UCHAR, PLY_UCHAR, (int)offsetof(PLYVertex,color[1]), 0, 0, 0, 0},
	{"blue", PLY_UCHAR, PLY_UCHAR, (int)offsetof(PLYVertex,color[2]), 0, 0, 0, 0},
};

PlyProperty face_props[] = { /* list of property information for a vertex */
	{"vertex_indices", PLY_INT, PLY_INT, offsetof(PLYFace,verts), 1, PLY_UCHAR, PLY_UCHAR, offsetof(PLYFace,nverts)},
};

class tri3f {
	unsigned int _ids[3];

public:
	tri3f() {
		_ids[0] = _ids[1] = _ids[2] = UINT_MAX;
	}

	void set(unsigned int id0, unsigned int id1, unsigned int id2) {
		_ids[0] = id0;
		_ids[1] = id1;
		_ids[2] = id2;
	}

	unsigned int id(int i) { return _ids[i]; }
	unsigned int id0() {return _ids[0];}
	unsigned int id1() {return _ids[1];}
	unsigned int id2() {return _ids[2];}
};

// only enable it for balls.
//#define OVER_VTX

#ifdef OVER_VTX
/*	[17400-17407]
	[17472-17479]
	[17544-17551]
	[17616-17623]
	[17688-17695]*/
static unsigned int get_id(unsigned int id)
{
	if (id > 17400 && id <= 17407)
		return 17400;
	if (id > 17472 && id <= 17479)
		return 17472;
	if (id > 17544 && id <= 17551)
		return 17544;
	if (id > 17616 && id <= 17623)
		return 17616;
	if (id > 17688 && id <= 17695)
		return 17688;

	return id;
}

#endif

ModelShl *
LoadModel(char *fname, unsigned int num_frame, float ply_scale)
{
	char ply_fname[256];
	
	unsigned int _num_frame = num_frame;
	unsigned int _num_vtx = 0;
	vec3d *_vtxs = NULL;

	unsigned int _num_tri = 0;
	unsigned int *_tris = NULL;

	for (unsigned int cur_f = 0; cur_f < _num_frame; cur_f++) {
		sprintf(ply_fname, "%s%d.ply", fname, cur_f);
		FILE *fp = fopen(ply_fname, "rb");
		if (fp == NULL)
			return NULL;

		// PLY object:
		PlyFile *ply;

		// PLY properties:
		char **elist;
		int nelems;

		// hand over the stream to the ply functions:
		ply = ply_read(fp, &nelems, &elist);
		assert(ply);

		int file_type;
		float version;		
		ply_get_info(ply, &version, &file_type);

		for (int i=0; i<nelems; i++) {
			char *elem_name = elist[i];

			int num_elems, nprops;
			PlyProperty **plist = ply_get_element_description(ply, elem_name, &num_elems, &nprops);

			bool has_vertex_x = false, has_vertex_y = false, has_vertex_z = false, has_colors = false;
			unsigned char color_components = 0;

			// this is a vertex:
			if (equal_strings ("vertex", elem_name)) {
				for (int j=0; j<nprops; j++)
				{
					if (equal_strings("x", plist[j]->name))
					{
						ply_get_property (ply, elem_name, &vert_props[0]);  /* x */
						has_vertex_x = TRUE;
					}
					else if (equal_strings("y", plist[j]->name))
					{
						ply_get_property (ply, elem_name, &vert_props[1]);  /* y */
						has_vertex_y = TRUE;
					}
					else if (equal_strings("z", plist[j]->name))
					{
						ply_get_property (ply, elem_name, &vert_props[2]);  /* z */
						has_vertex_z = TRUE;
					}
					else if (equal_strings("red", plist[j]->name))
					{
						ply_get_property (ply, elem_name, &vert_props[3]);  /* z */
						color_components++;
					}
					else if (equal_strings("green", plist[j]->name))
					{
						ply_get_property (ply, elem_name, &vert_props[4]);  /* z */
						color_components++;
					}
					else if (equal_strings("blue", plist[j]->name))
					{
						ply_get_property (ply, elem_name, &vert_props[5]);  /* z */
						color_components++;
					}
				}

				has_colors = color_components == 3;
				// test for necessary properties
				if ((!has_vertex_x) || (!has_vertex_y) || (!has_vertex_z))
				{
					logger->update("Warning: Vertex with less than 3 coordinated detected. Output will most likely be corrupt!");
					continue;
				}

				// must be first frame, initialize structures:
				if (_num_vtx == 0) {
					_num_vtx = num_elems;

					_vtxs = new vec3d[_num_vtx*_num_frame];
					cout << "Allocating " << _num_vtx*_num_frame*sizeof(vec3d) << " bytes for vertices." << endl;
				}

				// grab all the vertex elements
				PLYVertex plyNewVertex;		
				for (int j=0; j<num_elems; j++) {
					ply_get_element(ply, (void *)&plyNewVertex);								

					_vtxs[cur_f*_num_vtx+j] = (vec3d(plyNewVertex.coords) * ply_scale);
					if (j != 0 && j%1000000 == 0) {
						cout << " - " << j << " of " << num_elems << " loaded." << endl;					
					}				
				}
			}
			
			// this is a face (and, hopefully, a triangle):
			else if (equal_strings ("face", elem_name) && _tris == NULL) {
				// I need this for..., otherwise error ...
				for (int j=0; j<nprops; j++)
				{
					if (equal_strings("vertex_indices", plist[j]->name))
					{
						ply_get_property (ply, elem_name, &face_props[0]);  /* vertex_indices */
					}
				}

				/* grab all the face elements */
				PLYFace plyFace;	
				plyFace.other_props = NULL;			
								

				tri3f tri;
				std::vector<tri3f> trilist_temp;

				for (int j = 0; j < num_elems; j++) {				
					ply_get_element(ply, (void *)&plyFace);
					for (int fi = 0; fi < plyFace.nverts-2; fi++) {
						//
						// make a triangle in our format from PLY face + vertices
						//						

						// copy vertex indices
#ifdef OVER_VTX
						unsigned int id0 = get_id(plyFace.verts[0]);
						unsigned int id1 = get_id(plyFace.verts[fi+1]);
						unsigned int id2 = get_id(plyFace.verts[fi+2]);
						tri.set(id0, id1,id2);
#else

						tri.set(plyFace.verts[0], plyFace.verts[fi+1], plyFace.verts[fi+2]);
#endif
						// insert triangle into list							
						trilist_temp.push_back(tri);		
					}
					free(plyFace.verts);												

					if (j != 0 && j%500000 == 0) {
						cout << " - " << j << " of " << num_elems << " loaded." << endl;					
					}
				}

				// copy over temp list to static array
				_num_tri = (unsigned int)trilist_temp.size();
				cout << "Allocating " << _num_tri*sizeof(tri3f) << " bytes of storage for triangles." << endl;			
				_tris = new unsigned int[_num_tri*3];

				for (unsigned int t = 0; t < _num_tri; t++)
					for (int s=0; s<3; s++)
						_tris[t*3+s] = trilist_temp[t].id(s);
			}

			else // otherwise: skip all further
				NULL;
		}

		// PLY parsing ended, clean up vertex buffer and close the file		
		ply_close(ply);
		fclose(fp);
	}

/*	For the balls:
	[17400-17407]
	[17472-17479]
	[17544-17551]
	[17616-17623]
	[17688-17695]

	int *flags = new int[_num_vtx];
	for (int i=0; i<_num_vtx; i++) {
		flags[i] = 0;
		for (int j=0; j<_num_vtx; j++) {
			if (j == i) continue;
			if (s_covertex(_cur_vtxs[i], _cur_vtxs[j]))
				flags[i]++;
		}

		if (flags[i] == 8)
			flags[i] = 0;
	}*/

	ModelShl *mdl = new ModelShl(_num_frame, _num_vtx, _vtxs, _num_tri, _tris);

	delete [] _vtxs;
	delete [] _tris;
	return mdl;
}