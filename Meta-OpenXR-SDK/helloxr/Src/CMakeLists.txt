
# CMakeLists.txt

set(
  LOCAL_HEADERS
  anag.h
  check.h
  common.h
  egl_egl.h
  egl_eglext.h
  egl_eglext_angle.h
  egl_eglplatform.h
  egl_platform.h
  extra_algorithms.h
  geometry.h
  gles3_gl3.h
  gles3_gl3ext.h
  gles3_gl3platform.h
  gles3_gl31.h
  gles3_gl32.h
  header.h
  hex_and_handles.h
  khr_khrplatform.h
  logger.h
  meta_openxr_preview_extx1_event_channel.h
  meta_openxr_preview_meta_body_tracking_calibration.h
  meta_openxr_preview_meta_body_tracking_fidelity.h
  meta_openxr_preview_meta_body_tracking_full_body.h
  meta_openxr_preview_meta_boundary_visibility.h
  meta_openxr_preview_meta_colocation_discovery.h
  meta_openxr_preview_meta_detached_controllers.h
  meta_openxr_preview_meta_dynamic_object_keyboard.h
  meta_openxr_preview_meta_dynamic_object_tracker.h
  meta_openxr_preview_meta_hand_tracking_wide_motion_mode.h
  meta_openxr_preview_meta_simultaneous_hands_and_controllers.h
  meta_openxr_preview_meta_spatial_entity_discovery.h
  meta_openxr_preview_meta_spatial_entity_group_sharing.h
  meta_openxr_preview_meta_spatial_entity_persistence.h
  meta_openxr_preview_meta_spatial_entity_sharing.h
  meta_openxr_preview_openxr_extension_helpers.h
  meta_openxr_preview_openxr_oculus_helpers.h
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
  shaderc.h
  shaderc_build_info.h
  shaderc_env.h
  shaderc_hpp.h
  shaderc_status.h
  shaderc_visibility.h
  stb_image.h
  stb_image_write.h
  stb_vorbis.h
  tiny_obj_loader.h
  tinyobjloader_earcut.h
  vk_icd.h
  vk_layer.h
  vk_platform.h
  vulkan_android.h
  vulkan_beta.h
  vulcan_core1.h
  vulcan_core2.h
  vulkan_debug_object_namer.h
  vulkan_plugin.h
  vulkan_tutorial.h
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
  stb_image.cpp
  stb_image_write.cpp
  stb_vorbis.cpp
  vulkan_plugin.cpp
  vulkan_tutorial.cpp
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

option(
  BUILD_FORCE_GENERATION
  "Force re-generation of files even in the presence of pre-generated copies, replacing those copies."
  OFF
)

add_library(
  helloxr
  MODULE
  ${LOCAL_SOURCE}
  ${LOCAL_HEADERS}
)

set_target_properties(
  helloxr
  PROPERTIES
  FOLDER ${SAMPLES_FOLDER}
  LINK_FLAGS "-u ANativeActivity_onCreate"
)

source_group(
  "Headers"
  FILES
  ${LOCAL_HEADERS}
)

set_target_properties(
  helloxr
  PROPERTIES
  FOLDER ${SAMPLES_FOLDER}
)

source_group(
  "Headers"
  FILES
  ${LOCAL_HEADERS}
)

target_include_directories(
  helloxr
  PRIVATE
  "${PROJECT_SOURCE_DIR}/src"
  "${CMAKE_CURRENT_BINARY_DIR}"
)

target_include_directories(
  helloxr
  PRIVATE
  ${Vulkan_INCLUDE_DIRS}
)
