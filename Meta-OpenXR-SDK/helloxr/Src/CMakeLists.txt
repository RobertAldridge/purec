
# CMakeLists.txt

set(
  LOCAL_HEADERS
  anag.h
  check.h
  common.h
  exception_handling.h
  extra_algorithms.h
  filesystem_utils.h
  geometry.h
  graphicsapi.h
  graphicsplugin.h
  header.h
  hex_and_handles.h
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
  shaderc_build_info.h
  shaderc_env.h
  shaderc_hpp.h
  shaderc_status.h
  shaderc_visibility.h
  stdfs_conditions.h
  unique_asset.h
  vk_icd.h
  vk_layer.h
  vk_platform.h
  vk_sdk_platform.h
  vulkan_android.h
  vulkan_beta.h
  vulcan_core1.h
  vulcan_core2.h
  vulkan_debug_object_namer.h
  vulcan_hpp.h
  vulkan_video_codec_h264std.h
  vulkan_video_codec_h264std_decode.h
  vulkan_video_codec_h264std_encode.h
  vulkan_video_codec_h265std.h
  vulkan_video_codec_h265std_decode.h
  vulkan_video_codec_h265std_encode.h
  vulkan_video_codecs_common.h
  vulcan_wrapper.h
  xr_generated_dispatch_table_core.h
  xr_linear.h
)

set(
  LOCAL_SOURCE
  anag.c
  filesystem_utils.cpp
  graphicsplugin_factory.cpp
  graphicsplugin_vulkan.cpp
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
