
# Copyright (c) Meta Platforms, Inc. and affiliates.
# All rights reserved.
#
# Licensed under the Oculus SDK License Agreement (the "License");
# you may not use the Oculus SDK except in compliance with the License,
# which is provided at the time of installation or download, or which
# otherwise accompanies this software in either electronic or hard copy form.
#
# You may obtain a copy of the License at
# https://developer.oculus.com/licenses/oculussdk/
#
# Unless required by applicable law or agreed to in writing, the Oculus SDK
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.10.2)

project(MetaOpenXRSDK C CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#include(StdFilesystemFlags)

#set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)

set(XR_USE_GRAPHICS_API_OPENGL FALSE)
set(XR_USE_GRAPHICS_API_OPENGL_ES FALSE)
set(XR_USE_GRAPHICS_API_VULKAN TRUE)
set(XR_USE_GRAPHICS_API_D3D11 FALSE)
set(XR_USE_GRAPHICS_API_D3D12 FALSE)
set(XR_USE_GRAPHICS_API_METAL FALSE)

set(OPENGLES_INCOMPATIBLE TRUE)
set(OPENGL_INCOMPATIBLE TRUE)
set(VULKAN_INCOMPATIBLE FALSE)
set(METAL_INCOMPATIBLE TRUE)

find_package(Vulkan)

if(Vulkan_FOUND)
    set(XR_USE_GRAPHICS_API_VULKAN TRUE)
    add_definitions(-DXR_USE_GRAPHICS_API_VULKAN)
    message(STATUS "Enabling Vulkan support")
elseif(BUILD_ALL_EXTENSIONS)
    message(FATAL_ERROR "Vulkan headers not found")
endif()

#cmake_dependent_option(
#    BUILD_WITH_STD_FILESYSTEM
#    "Use std::[experimental::]filesystem."
#    ON
#    "HAVE_FILESYSTEM_WITHOUT_LIB OR HAVE_FILESYSTEM_NEEDING_LIBSTDCXXFS OR HAVE_FILESYSTEM_NEEDING_LIBCXXFS"
#    OFF
#)

add_definitions(-DXR_OS_ANDROID)

add_definitions(-DXR_USE_PLATFORM_ANDROID)

set(OPENXR_ANDROID_VERSION_SUFFIX
    ""
    CACHE STRING "Suffix for generated Android artifacts."
)

set(BUILD_CONFORMANCE_CLI OFF)

file(
    GLOB
    glslc_folders
    CONFIGURE_DEPENDS
    ${ANDROID_NDK}/shader-tools/*
)

find_program(
    GLSL_COMPILER glslc
    PATHS ${glslc_folders}
    NO_DEFAULT_PATH
)

find_program(
    GLSLANG_VALIDATOR glslangValidator
    HINTS "${Vulkan_GLSLANG_VALIDATOR_EXECUTABLE}"
)

if(GLSL_COMPILER)
    message(STATUS "Found glslc: ${GLSL_COMPILER}")
elseif(GLSLANG_VALIDATOR)
    message(STATUS "Found glslangValidator: ${GLSLANG_VALIDATOR}")
else()
    message(STATUS "Could NOT find glslc, using precompiled .spv files")
endif()

function(compile_glsl run_target_name)
    set(glsl_output_files "")
    foreach(in_file IN LISTS ARGN)
        get_filename_component(glsl_stage "${in_file}" NAME_WE)
        set(out_file "${CMAKE_CURRENT_BINARY_DIR}/${glsl_stage}.spv")
        if(GLSL_COMPILER)
            # Run glslc if we can find it
            add_custom_command(
                OUTPUT "${out_file}"
                COMMAND
                    "${GLSL_COMPILER}" -mfmt=c -fshader-stage=${glsl_stage}
                    "${in_file}" -o "${out_file}"
                DEPENDS "${in_file}"
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                VERBATIM
            )
        elseif(GLSLANG_VALIDATOR)
            # Run glslangValidator if we can find it
            add_custom_command(
                OUTPUT "${out_file}"
                COMMAND
                    "${GLSLANG_VALIDATOR}" -V -S ${glsl_stage} "${in_file}" -x
                    -o "${out_file}"
                DEPENDS "${in_file}"
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                VERBATIM
            )
        else()
            # Use the precompiled .spv files
            get_filename_component(glsl_src_dir "${in_file}" DIRECTORY)
            set(precompiled_file "${glsl_src_dir}/${glsl_stage}.spv")
            configure_file("${precompiled_file}" "${out_file}" COPYONLY)
        endif()
        list(APPEND glsl_output_files "${out_file}")
    endforeach()
    add_custom_target(${run_target_name} ALL DEPENDS ${glsl_output_files})
    set_target_properties(${run_target_name} PROPERTIES FOLDER ${HELPER_FOLDER})

endfunction()

find_library(ANDROID_LIBRARY NAMES android)
find_library(ANDROID_LOG_LIBRARY NAMES log)

add_subdirectory(3rdParty)
add_subdirectory(SampleXrFramework)
add_subdirectory(helloxr)
