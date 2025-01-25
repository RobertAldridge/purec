
cmake_minimum_required(VERSION 3.10.2)

project(helloxr)

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

#if(NOT TARGET OpenXR::openxr_loader)
#    find_package(OpenXR REQUIRED)
#endif()

    file(GLOB_RECURSE SRC_FILES *.c *.cpp)

    file(TO_CMAKE_PATH "$ENV{VULKAN_SDK}" VULKAN_SDK)

    add_library(${PROJECT_NAME} MODULE ${SRC_FILES})
#    target_link_libraries(${PROJECT_NAME} PRIVATE native_activity_framework)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-u ANativeActivity_onCreate")

    # Common across platforms
    target_include_directories(${PROJECT_NAME} PRIVATE Src)

    target_compile_definitions(
        helloxr
        PUBLIC
            VK_NO_PROTOTYPES=1
            XR_USE_PLATFORM_ANDROID=1
            XR_USE_GRAPHICS_API_VULKAN=1
            ANDROID_NDK
            $<IF:$<CONFIG:Debug>,OVR_BUILD_DEBUG=1,>
    )

#if(NOT TARGET OpenXR::openxr_loader)
#    find_package(OpenXR REQUIRED)
#endif()

set(LOCAL_HEADERS
    anag.h
    check.h
    common.h
    common_config.h
    extra_algorithms.h
    geometry.h
    graphicsapi.h
    graphicsplugin.h
    hex_and_handles.h
    jnipp.h
    logger.h
    object_info.h
    openxr.h
    openxr_loader_negotiation.h
    openxr_platform.h
    openxr_platform_defines.h
    openxr_program.h
    openxr_reflection.h
    options.h
    pch.h
    platformdata.h
    platformplugin.h
    stdfs_conditions.h
    unique_asset.h
    vk_platform.h
    vulkan.h
    vulcan_android.h
    vulcan_beta.h
    vulcan_core.h
    vulcan_wrapper.h
    xr_dependencies.h
    xr_generated_dispatch_table_core.h
    xr_linear.h
    exception_handling.hpp
    filesystem_utils.hpp
    loader_init_data.hpp
    loader_logger.hpp
    loader_platform.hpp
    platform_utils.hpp
    vulkan_debug_object_namer.hpp
    frag.spv
    vert.spv
)

set(LOCAL_SOURCE
    anag.c
    xr_generated_dispatch_table_core.cpp
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
)

include_directories("C:/Users/RobertLocalAldridge/AppData/Local/Android/Sdk/ndk/25.1.8937393/sources/third_party/vulkan/src/include/vulkan")

option(
    BUILD_FORCE_GENERATION
    "Force re-generation of files even in the presence of pre-generated copies, replacing those copies."
    OFF
)

set(VULKAN_SHADERS vulkan_shaders/frag.glsl vulkan_shaders/vert.glsl)

add_library(
  helloxr MODULE
  ${LOCAL_SOURCE}
  ${LOCAL_HEADERS}
  ${VULKAN_SHADERS}
)

target_link_libraries(
  helloxr PRIVATE ${ANDROID_LIBRARY} ${ANDROID_LOG_LIBRARY}
)

    # Only for Android because it lacks a command line
    set(HELLOXR_DEFAULT_GRAPHICS_PLUGIN
        "Vulkan"
        CACHE
            STRING
            "Which graphics plugin should be used by default for Hello XR artifacts?"
    )

    set_property(
        CACHE HELLOXR_DEFAULT_GRAPHICS_PLUGIN PROPERTY STRINGS "Vulkan"
                                                       "Vulkan"
    )

    # Now handle the value, normally provided by Gradle
#    if(HELLOXR_DEFAULT_GRAPHICS_PLUGIN STREQUAL "OpenGLES")
#        message(STATUS "helloxr will default to OpenGL ES graphics plugin")
#        target_compile_definitions(
#            helloxr PRIVATE DEFAULT_GRAPHICS_PLUGIN_OPENGLES
#        )
#    elseif(HELLOXR_DEFAULT_GRAPHICS_PLUGIN STREQUAL "Vulkan")
        message(STATUS "helloxr will default to Vulkan graphics plugin")
        target_compile_definitions(
            helloxr PRIVATE DEFAULT_GRAPHICS_PLUGIN_VULKAN
        )
#    endif()

set_target_properties(helloxr PROPERTIES FOLDER ${SAMPLES_FOLDER} LINK_FLAGS "-u ANativeActivity_onCreate")

source_group("Headers" FILES ${LOCAL_HEADERS})
source_group("Shaders" FILES ${VULKAN_SHADERS})

#target_link_libraries(helloxr PRIVATE OpenXR::openxr_loader)

compile_glsl(run_helloxr_glsl_compiles ${VULKAN_SHADERS})

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

set_target_properties(helloxr PROPERTIES FOLDER ${SAMPLES_FOLDER})
source_group("Headers" FILES ${LOCAL_HEADERS})
source_group("Shaders" FILES ${VULKAN_SHADERS})

target_link_libraries(helloxr PRIVATE libvulkan.so libopenxr_loader.so)

compile_glsl(run_helloxr_glsl_compiles ${VULKAN_SHADERS})

add_dependencies(helloxr run_helloxr_glsl_compiles)

target_include_directories(
    helloxr
    PRIVATE
        "${PROJECT_SOURCE_DIR}/vulkan_shaders"
        # For including compiled shaders
        "${CMAKE_CURRENT_BINARY_DIR}"
)

if(GLSLANG_VALIDATOR AND NOT GLSLC_COMMAND)
    target_compile_definitions(helloxr PRIVATE USE_GLSLANGVALIDATOR)
endif()

    target_include_directories(helloxr PRIVATE ${Vulkan_INCLUDE_DIRS})
    target_link_libraries(helloxr PRIVATE ${Vulkan_LIBRARY})

#if(TARGET openxr-gfxwrapper)
#    target_link_libraries(helloxr PRIVATE openxr-gfxwrapper)
#endif()
