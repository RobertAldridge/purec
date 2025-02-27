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


#include <stdlib.h>
#include <assert.h>

#include "bvh.h"
#include "vec4d.h"
#include "Model.h"
#include "aap.h"

extern float middle_xyz(char xyz, const vec3d &p1, const vec3d &p2, const vec3d &p3);

#define IsLeaf(node) (node->_left == NULL)


bvh_tree::bvh_tree(Model *mdl)
{
	aabb total;
	for (unsigned int i=0; i<mdl->_num_vtx; i++)
		total += mdl->_vtxs[i];

	assert(mdl->_tri_boxes == NULL);
	assert(mdl->_tri_centers == NULL);

	mdl->_tri_boxes = new aabb[mdl->_num_tri];
	mdl->_tri_centers = new vec3f[mdl->_num_tri];

	aap  pln(total);
	unsigned int *idx_buffer = new unsigned int[mdl->_num_tri];
	unsigned int left_idx = 0, right_idx = mdl->_num_tri;

	for (unsigned int i=0; i<mdl->_num_tri; i++) {
		vec3d &p1 = mdl->_vtxs[mdl->_tris[i*3]];
		vec3d &p2 = mdl->_vtxs[mdl->_tris[i*3+1]];
		vec3d &p3 = mdl->_vtxs[mdl->_tris[i*3+2]];

		mdl->_tri_centers[i][0] = middle_xyz(0, p1, p2, p3);
		mdl->_tri_centers[i][1] = middle_xyz(1, p1, p2, p3);
		mdl->_tri_centers[i][2] = middle_xyz(2, p1, p2, p3);

		if (pln.inside(mdl->_tri_centers[i]))
			idx_buffer[left_idx++] = i;
		else
			idx_buffer[--right_idx] = i;

		mdl->_tri_boxes[i] += p1;
		mdl->_tri_boxes[i] += p2;
		mdl->_tri_boxes[i] += p3;
	}

	_root = new bvh_node();
	_root->_box = total;
	_root->_left = new bvh_node(idx_buffer, left_idx, mdl);
	_root->_right = new bvh_node(idx_buffer+left_idx, mdl->_num_tri-left_idx, mdl);
	_mdl = mdl;

	delete [] mdl->_tri_boxes;
	delete [] mdl->_tri_centers;
	mdl->_tri_boxes = NULL;
	mdl->_tri_centers = NULL;

	delete [] idx_buffer;
}

bvh_tree::~bvh_tree()
{
	delete _root;
}

void
bvh_tree::visulization(int level)
{
	_root->visulization(level);
}

static int s_num_leaf;
static Model *s_mdl;

int
bvh_tree::refit()
{
	s_num_leaf = 0;
	s_mdl = _mdl;

	_root->refit();

	return s_num_leaf;
}

//#################################################################

bvh_node::bvh_node()
{
	_id = UINT_MAX;
	_left = _right = NULL;
}

bvh_node::~bvh_node()
{
	if (_left) delete _left;
	if (_right) delete _right;
}

bvh_node::bvh_node(unsigned int id)
{
	_left = _right = NULL;
	_id = id;
}

bvh_node::bvh_node(unsigned int *lst, unsigned int lst_num, Model *mdl)
{
	assert(lst_num > 0);
	_left = _right = NULL;
	_id = UINT_MAX;
	
	if (lst_num == 1) {
		_id = lst[0];
		_box = mdl->_tri_boxes[_id];
	}
	else { // try to split them
		for (unsigned int t=0; t<lst_num; t++) {
			int i=lst[t];
			_box += mdl->_tri_boxes[i];
		}

		if (lst_num == 2) { // must split it!
			_left = new bvh_node(lst[0]);
			_right = new bvh_node(lst[1]);
		} else {
			aap pln(_box);
			unsigned int left_idx = 0, right_idx = lst_num-1;

			for (unsigned int t=0; t<lst_num; t++) {
				int i=lst[left_idx];
				if (pln.inside(mdl->_tri_centers[i]))
					left_idx++;
				else {// swap it
					unsigned int tmp = i;
					lst[left_idx] = lst[right_idx];
					lst[right_idx--] = tmp;
				}
			}

			int hal = lst_num/2;
			if (left_idx == 0 || left_idx == lst_num)
			{
				_left = new bvh_node(lst, hal, mdl);
				_right = new bvh_node(lst+hal, lst_num-hal, mdl);
			}
			else {
				_left = new bvh_node(lst, left_idx, mdl);
				_right = new bvh_node(lst+left_idx, lst_num-left_idx, mdl);
			}

		}
	}
}

void
bvh_node::visulization(int level)
{
	if (IsLeaf(this))
		_box.visulization();
	else
		if ((level > 0)) {
			if (level == 1)
				_box.visulization();
			else
			if (_left)
				_left->visulization(level-1);
			if (_right)
				_right->visulization(level-1);
		}
}

aabb &
bvh_node::refit()
{
	if (IsLeaf(this)) {
		s_num_leaf++;

		int i = _id;
		vec3d &p1 = s_mdl->_vtxs[s_mdl->_tris[i*3]];
		vec3d &p2 = s_mdl->_vtxs[s_mdl->_tris[i*3+1]];
		vec3d &p3 = s_mdl->_vtxs[s_mdl->_tris[i*3+2]];

		_box.empty();
		_box += p1;
		_box += p2;
		_box += p3;
	} else {
		_box = _left->refit();
		_box += _right->refit();
	}

	return _box;
}