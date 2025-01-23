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

set(LOCAL_HEADERS
    anag.h
    check.h
    common.h
        geometry.h
    graphicsapi.h
    graphicsplugin.h
    logger.h
    openxr_program.h
    options.h
    pch.h
    platformdata.h
    platformplugin.h
)
set(LOCAL_SOURCE
        anag.c
        graphicsplugin_factory.cpp
        graphicsplugin_vulkan.cpp
        logger.cpp
    main.cpp
    openxr_program.cpp
    pch.cpp
    platformplugin_android.cpp
    platformplugin_factory.cpp
        )
set(VULKAN_SHADERS vulkan_shaders/frag.glsl vulkan_shaders/vert.glsl)

    add_library(
        hello_xr MODULE
        ${LOCAL_SOURCE}
        ${LOCAL_HEADERS}
        ${VULKAN_SHADERS}
#        $<TARGET_OBJECTS:android_native_app_glue>
    )
    target_link_libraries(
        hello_xr PRIVATE ${ANDROID_LIBRARY} ${ANDROID_LOG_LIBRARY}
    )

    # Only for Android because it lacks a command line
    set(HELLOXR_DEFAULT_GRAPHICS_PLUGIN
        "Vulkan"
#        "OpenGLES"
        CACHE
            STRING
            "Which graphics plugin should be used by default for Hello XR artifacts?"
    )
    # These are the recognized options: provide them as a helper in the CMake GUI
    set_property(
        CACHE HELLOXR_DEFAULT_GRAPHICS_PLUGIN PROPERTY STRINGS "OpenGLES"
                                                       "Vulkan"
    )

    # Now handle the value, normally provided by Gradle
#    if(HELLOXR_DEFAULT_GRAPHICS_PLUGIN STREQUAL "OpenGLES")
#        message(STATUS "hello_xr will default to OpenGL ES graphics plugin")
#        target_compile_definitions(
#            hello_xr PRIVATE DEFAULT_GRAPHICS_PLUGIN_OPENGLES
#        )
#    elseif(HELLOXR_DEFAULT_GRAPHICS_PLUGIN STREQUAL "Vulkan")
        message(STATUS "hello_xr will default to Vulkan graphics plugin")
        target_compile_definitions(
            hello_xr PRIVATE DEFAULT_GRAPHICS_PLUGIN_VULKAN
        )
#    endif()

set_target_properties(hello_xr PROPERTIES FOLDER ${SAMPLES_FOLDER} LINK_FLAGS "-u ANativeActivity_onCreate")
source_group("Headers" FILES ${LOCAL_HEADERS})
source_group("Shaders" FILES ${VULKAN_SHADERS})

target_link_libraries(hello_xr PRIVATE OpenXR::openxr_loader)

compile_glsl(run_hello_xr_glsl_compiles ${VULKAN_SHADERS})

add_dependencies(hello_xr run_hello_xr_glsl_compiles)

target_include_directories(
    hello_xr
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src"
        "${PROJECT_SOURCE_DIR}/src/common"
        "${PROJECT_SOURCE_DIR}/src/external/metal-cpp"
        "${PROJECT_SOURCE_DIR}/src/tests/hello_xr/vulkan_shaders"
        # for helper headers
        "${PROJECT_SOURCE_DIR}/external/include"
        # For including compiled shaders
        "${CMAKE_CURRENT_BINARY_DIR}"
)

target_link_libraries(hello_xr PRIVATE OpenXR::openxr_loader)

if(GLSLANG_VALIDATOR AND NOT GLSLC_COMMAND)
    target_compile_definitions(hello_xr PRIVATE USE_GLSLANGVALIDATOR)
endif()

if(XR_USE_GRAPHICS_API_VULKAN)
    target_include_directories(hello_xr PRIVATE ${Vulkan_INCLUDE_DIRS})
    target_link_libraries(hello_xr PRIVATE ${Vulkan_LIBRARY})
endif()

if(TARGET openxr-gfxwrapper)
    target_link_libraries(hello_xr PRIVATE openxr-gfxwrapper)
endif()
