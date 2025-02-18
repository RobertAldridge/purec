
// header.h

// todo
#undef NDEBUG

#include <cassert>
//#include <ccomplex>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
//#include <cstdalign>
#include <cstdarg>
//#include <cstdatomic>
//#include <cstdbit>
//#include <cstdbool>
//#include <cstdckdint>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
//#include <cstdnoreturn>
#include <cstring>
//#include <ctgmath>
//#include <cthreads>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <cwctype>

#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <barrier>
#include <bit>
#include <bitset>
#include <charconv>
#include <chrono>
#include <codecvt>
#include <compare>
#include <complex>
#include <concepts>
#include <condition_variable>
#include <coroutine>
#include <deque>
#include <exception>
#include <execution>
#include <expected>
#include <filesystem>
//#include <flat_map>
//#include <flat_set>
#include <format>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
//#include <generator>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <latch>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <mdspan>
#include <memory>
#include <memory_resource>
#include <mutex>
#include <new>
#include <numbers>
#include <numeric>
#include <optional>
#include <ostream>
#include <print>
#include <queue>
#include <random>
#include <ranges>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <semaphore>
#include <set>
#include <shared_mutex>
#include <source_location>
#include <span>
//#include <spanstream>
#include <sstream>
#include <stack>
//#include <stacktrace>
#include <stdexcept>
//#include <stdfloat>
#include <stop_token>
#include <streambuf>
#include <string>
#include <string_view>
#include <strstream>
#include <syncstream>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <variant>
#include <vector>
#include <version>

//#define VULKAN_DEBUG_OBJECT_NAMER 1

#define USE_EXPERIMENTAL_FS 0
#define USE_FINAL_FS 1

#include <android/native_window.h>
#include <android/window.h>
#include <android/native_window_jni.h>

#include <android/asset_manager_jni.h>

#include <android/configuration.h>
#include <android/looper.h>
#include <android/native_activity.h>

#include <android/log.h>

#include <unistd.h>
#include <sys/resource.h>

#include <poll.h>
#include <pthread.h>
#include <sched.h>

class _jobject;
typedef _jobject* jobject;

#include "anag.h"

#include <jni.h>

#include <sys/stat.h>

#include <sys/system_properties.h>

#define XR_ARCH_ABI "arm64-v8a"

#include <dlfcn.h>

#include "vk_platform.h"

#include "vulkan_core1.h"

#define VK_KHR_video_decode_h264 1
#define VK_KHR_video_encode_h264 1

#define VK_KHR_video_decode_h265 1
#define VK_KHR_video_encode_h265 1

#define vulkan_video_codec_h264std 1
#define vulkan_video_codec_h265std 1
#include "vulkan_video_codecs_common.h"

#define vulkan_video_codec_h265std_decode 1
#define vulkan_video_codec_h265std_encode 1
#include "vulkan_video_codec_h265std.h"

#include "vulkan_video_codec_h265std_decode.h"
#include "vulkan_video_codec_h265std_encode.h"

#define vulkan_video_codec_h264std_decode 1
#define vulkan_video_codec_h264std_encode 1
#include "vulkan_video_codec_h264std.h"

#include "vulkan_video_codec_h264std_decode.h"
#include "vulkan_video_codec_h264std_encode.h"

#include "vulkan_core2.h"

#include "vulkan_android.h"
#include "vulkan_beta.h"

#include "vulkan_vtable.h"

#include "vk_layer.h"

#include "vk_icd.h"

extern struct VkGeneratedDispatchTableCore tableVk;

extern VkInstance gVkInstance;

extern VkDevice gVkDevice;

extern VkPhysicalDevice gVkPhysicalDevice;

#include "vulkan_debug_object_namer.h"

#include "openxr_platform_defines.h"

#include "openxr.h"
#include "openxr_platform.h"
#include "openxr_loader_negotiation.h"
#include "openxr_reflection.h"
#include "openxr_reflection_structs.h"
#include "openxr_reflection_parent_structs.h"

extern XrInstance gXrInstance;

extern XrSession gXrSession;

extern XrSystemId gXrSystemId;

#include "logger.h"
#include "common.h"
#include "options.h"

#include "geometry.h"

#include "shaderc_build_info.h"
#include "shaderc_env.h"
#include "shaderc_status.h"
#include "shaderc_visibility.h"
#include "shaderc.h"
#include "shaderc_hpp.h"

#include "check.h"

#include "vulkan_plugin.h"

#include "openxr_plugin.h"

inline std::string Fmt(const char* fmt, ...);

inline const char* to_string(XrReferenceSpaceType e);
inline const char* to_string(XrViewConfigurationType e);
inline const char* to_string(XrEnvironmentBlendMode e);
inline const char* to_string(XrSessionState e);
inline const char* to_string(XrResult e);
inline const char* to_string(XrFormFactor e);

#include "openxr_linear.h"

#include "vulkan_tutorial.h"

#include "hex_and_handles.h"

#include "object_info.h"

#include "extra_algorithms.h"

#include "meta_openxr_preview_extx1_event_channel.h"
#include "meta_openxr_preview_meta_body_tracking_calibration.h"
#include "meta_openxr_preview_meta_body_tracking_fidelity.h"
#include "meta_openxr_preview_meta_body_tracking_full_body.h"
#include "meta_openxr_preview_meta_boundary_visibility.h"
#include "meta_openxr_preview_meta_colocation_discovery.h"
#include "meta_openxr_preview_meta_detached_controllers.h"
#include "meta_openxr_preview_meta_dynamic_object_tracker.h"
#include "meta_openxr_preview_meta_dynamic_object_keyboard.h"
#include "meta_openxr_preview_meta_hand_tracking_wide_motion_mode.h"
#include "meta_openxr_preview_meta_simultaneous_hands_and_controllers.h"
#include "meta_openxr_preview_meta_spatial_entity_discovery.h"
#include "meta_openxr_preview_meta_spatial_entity_group_sharing.h"
#include "meta_openxr_preview_meta_spatial_entity_persistence.h"
#include "meta_openxr_preview_meta_spatial_entity_sharing.h"
#include "meta_openxr_preview_openxr_extension_helpers.h"
#include "meta_openxr_preview_openxr_oculus_helpers.h"

#include "openxr_vtable.h"

extern struct XrGeneratedDispatchTableCore tableXr;

// todo
#include "memory.h"

#include "pch.h"

//struct XrInstanceCreateInfoAndroidKHR
//{
//  XrStructureType type;
//  const void* next;
//  void* applicationVM;
//  void* applicationActivity;
//};

extern XrInstanceCreateInfoAndroidKHR instanceCreateInfoAndroid;

#define countof(blah) (sizeof(blah) / sizeof(blah[0] ) )

struct MatrixCmdPushConstants
{
  XrMatrix4x4f modelViewProjectionMatrix;

  XrMatrix4x4f transpose_inverse_modelViewMatrix;

  XrMatrix4x4f modelViewMatrix;

  XrVector3f modelColor;
};

#include "khr_khrplatform.h"

#include "gles3_gl3platform.h"

#include "egl_eglplatform.h"
#include "egl_egl.h"
#include "egl_eglext.h"
#include "egl_eglext_angle.h"

#include "egl_platform.h"

#include "gles3_gl3.h"
#include "gles3_gl3ext.h"

#include "gles3_gl31.h"
#include "gles3_gl32.h"

#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_vorbis.h"
