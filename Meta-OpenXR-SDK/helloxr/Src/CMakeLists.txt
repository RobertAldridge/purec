# Copyright (c) 2017-2024, The Khronos Group Inc.
#
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

#if(NOT TARGET OpenXR::openxr_loader)
#    find_package(OpenXR REQUIRED)
#endif()

set(LOCAL_HEADERS
    anag.h
    check.h
    common.h
    exception_handling.h
    extra_algorithms.h
    filesystem_utils.h
    geometry.h
    graphicsapi.h
    graphicsplugin.h
    hex_and_handles.h
    jnipp.h
    loader_init_data.h
    loader_logger.h
    logger.h
    object_info.h
    openxr.h
    openxr_loader_negotiation.h
    openxr_platform.h
    openxr_platform_defines.h
    openxr_program.h
    openxr_reflection.h
    openxr_reflection_parent_structs.h
    openxr_reflection_structs.h
    options.h
    pch.h
    platform_utils.h
    platformdata.h
    platformplugin.h
    shaderc.h
    shaderc_env.h
    shaderc_hpp.h
    shaderc_status.h
    shaderc_visibility.h
    stdfs_conditions.h
    unique_asset.h
    vulkan_debug_object_namer.h
    vulcan_wrapper.h
    xr_generated_dispatch_table_core.h
    xr_linear.h
    frag.spv
    vert.spv
)

set(LOCAL_SOURCE
    anag.c
    filesystem_utils.cpp
    graphicsplugin_factory.cpp
    graphicsplugin_vulkan.cpp
    loader_init_data.cpp
    loader_logger.cpp
    logger.cpp
    main.cpp
    object_info.cpp
    openxr_program.cpp
    pch.cpp
    platformplugin_android.cpp
    platformplugin_factory.cpp
    vulcan_wrapper.cpp
    xr_generated_dispatch_table_core.cpp
    C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libglslang.a
    C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libOGLCompiler.a
    C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libOSDependent.a
    C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libshaderc.a
    C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libshaderc_util.a
    C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libSPIRV.a
    C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libHLSL.a
    C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libSPIRV-Tools.a
    C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libSPIRV-Tools-opt.a
)

option(
    BUILD_FORCE_GENERATION
    "Force re-generation of files even in the presence of pre-generated copies, replacing those copies."
    OFF
)

set(VULKAN_SHADERS frag.glsl vert.glsl)

add_library(
  helloxr MODULE
  ${LOCAL_SOURCE}
  ${LOCAL_HEADERS}
  ${VULKAN_SHADERS}
)

#target_link_libraries(helloxr PRIVATE ${ANDROID_LIBRARY} ${ANDROID_LOG_LIBRARY} )

set_target_properties(helloxr PROPERTIES FOLDER ${SAMPLES_FOLDER} LINK_FLAGS "-u ANativeActivity_onCreate")

source_group("Headers" FILES ${LOCAL_HEADERS} )
source_group("Shaders" FILES ${VULKAN_SHADERS} )

#target_link_libraries(helloxr PRIVATE OpenXR::openxr_loader)

compile_glsl(run_helloxr_glsl_compiles ${VULKAN_SHADERS} )

add_dependencies(helloxr run_helloxr_glsl_compiles)

#target_include_directories(
#    helloxr
#    PRIVATE
#        "${PROJECT_SOURCE_DIR}/src"
#        "${PROJECT_SOURCE_DIR}/src/common"
#        "${PROJECT_SOURCE_DIR}/src/external/metal-cpp"
#        "${PROJECT_SOURCE_DIR}/src/tests/helloxr/vulkan_shaders"
#
#        "${PROJECT_SOURCE_DIR}/external/include"
        # For including compiled shaders
#        "${CMAKE_CURRENT_BINARY_DIR}"
#)

set_target_properties(helloxr PROPERTIES FOLDER ${SAMPLES_FOLDER} )
source_group("Headers" FILES ${LOCAL_HEADERS} )
source_group("Shaders" FILES ${VULKAN_SHADERS} )

#target_link_libraries(helloxr PRIVATE libvulkan.so libopenxr_loader.so)

compile_glsl(run_helloxr_glsl_compiles ${VULKAN_SHADERS} )

add_dependencies(helloxr run_helloxr_glsl_compiles)

target_include_directories(
    helloxr
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src"
        # For including compiled shaders
        "${CMAKE_CURRENT_BINARY_DIR}"
)

if(GLSLANG_VALIDATOR AND NOT GLSLC_COMMAND)
    target_compile_definitions(helloxr PRIVATE USE_GLSLANGVALIDATOR)
endif()

    target_include_directories(helloxr PRIVATE ${Vulkan_INCLUDE_DIRS} )
#target_link_libraries(helloxr PRIVATE ${Vulkan_LIBRARY} )

#if(TARGET openxr-gfxwrapper)
#    target_link_libraries(helloxr PRIVATE openxr-gfxwrapper)
#endif()
