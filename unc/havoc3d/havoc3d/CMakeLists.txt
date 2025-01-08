
PROJECT( havoc3d )

INCLUDE(${CMAKE_ROOT}/Modules/FindOpenGL.cmake)

INCLUDE_DIRECTORIES(
  ${OPENGL_INCLUDE_PATH}
)

SET( havoc3d_SRCS 
  check_if_closed.cpp
  color_ids.cpp
  drawslice_gl.cpp
  find_interior.cpp
  find_interior_slice.cpp
  line_distmesh.cpp
  line_distmesh_grad.cpp
  pixel_error.cpp
  pt_distmesh.cpp
  pt_distmesh_grad.cpp
  queries.cpp
  sitecull.cpp
  tri_distmesh.cpp
  tri_distmesh_grad.cpp
  voronoi_slice.cpp
)

SET( havoc3d_HDRS
  check_if_closed.hpp
  color_ids.hpp
  drawslice_gl.hpp
  find_interior.hpp
  find_interior_slice.hpp
  grad_utilities.hpp
  line_distmesh.hpp
  line_distmesh_grad.hpp
  pixel_error.hpp
  pt_distmesh.hpp
  pt_distmesh_grad.hpp
  queries.hpp
  sitecull.hpp
  tri_distmesh.hpp
  tri_distmesh_grad.hpp
  voronoi_slice.hpp
)

#specify executables
ADD_LIBRARY( havoc3d havoc3d_SRCS )

