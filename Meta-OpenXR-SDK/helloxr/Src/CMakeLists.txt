
# CMakeLists.txt

set(
  LOCAL_HEADERS
  anag.h
  check.h
  common.h
  extra_algorithms.h
  geometry.h
  header.h
  hex_and_handles.h
  logger.h
  object_info.h
  openxr.h
  openxr_linear.h
  openxr_loader_negotiation.h
  openxr_platform.h
  openxr_platform_defines.h
  openxr_plugin.h
  openxr_reflection.h
  openxr_reflection_parent_structs.h
  openxr_reflection_structs.h
  openxr_vtable.h
  options.h
  pch.h
  platformplugin.h
  shaderc.h
  shaderc_build_info.h
  shaderc_env.h
  shaderc_hpp.h
  shaderc_status.h
  shaderc_visibility.h
  unique_asset.h
  vk_icd.h
  vk_layer.h
  vk_platform.h
  vulkan_android.h
  vulkan_beta.h
  vulcan_core1.h
  vulcan_core2.h
  vulkan_debug_object_namer.h
  vulkan_plugin.h
  vulkan_video_codec_h264std.h
  vulkan_video_codec_h264std_decode.h
  vulkan_video_codec_h264std_encode.h
  vulkan_video_codec_h265std.h
  vulkan_video_codec_h265std_decode.h
  vulkan_video_codec_h265std_encode.h
  vulkan_video_codecs_common.h
  vulkan_vtable.h
)

set(
  LOCAL_SOURCE
  anag.cpp
  logger.cpp
  object_info.cpp
  openxr_plugin.cpp
  openxr_vtable.cpp
  pch.cpp
  vulkan_plugin.cpp
  vulkan_vtable.cpp
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libHLSL.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libOGLCompiler.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libOSDependent.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libSPIRV-Tools-opt.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libSPIRV-Tools.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libSPIRV.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libglslang.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libshaderc.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libshaderc_util.a
)

option(BUILD_FORCE_GENERATION "Force re-generation of files even in the presence of pre-generated copies, replacing those copies." OFF)

add_library(helloxr MODULE ${LOCAL_SOURCE} ${LOCAL_HEADERS} )

set_target_properties(helloxr PROPERTIES FOLDER ${SAMPLES_FOLDER} LINK_FLAGS "-u ANativeActivity_onCreate")

source_group("Headers" FILES ${LOCAL_HEADERS} )

set_target_properties(helloxr PROPERTIES FOLDER ${SAMPLES_FOLDER} )
source_group("Headers" FILES ${LOCAL_HEADERS} )

target_include_directories(helloxr PRIVATE "${PROJECT_SOURCE_DIR}/src" "${CMAKE_CURRENT_BINARY_DIR}")

target_include_directories(helloxr PRIVATE ${Vulkan_INCLUDE_DIRS} )
