
# CMakeLists.txt

project(helloxr)

file(GLOB_RECURSE SRC_FILES Src/*.c Src/*.cpp)

file(TO_CMAKE_PATH "$ENV{VULKAN_SDK}" VULKAN_SDK)

add_library( ${PROJECT_NAME} MODULE ${SRC_FILES} )

add_library(OpenXR::headers INTERFACE IMPORTED)

set_target_properties(OpenXR::headers PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "C:/business/purec/Meta-OpenXR-SDK/helloxr/Src" INTERFACE_LINK_LIBRARIES "")

add_library(OpenXR::openxr_loader SHARED IMPORTED)

set_target_properties(OpenXR::openxr_loader PROPERTIES IMPORTED_LOCATION "C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libopenxr_loader.so" INTERFACE_LINK_LIBRARIES "OpenXR::headers")

target_include_directories( ${PROJECT_NAME} PRIVATE C:/business/purec/Meta-OpenXR-SDK/helloxr/Src)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libandroid.so
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/liblog.so
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libglslang.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libOGLCompiler.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libOSDependent.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libshaderc.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libshaderc_util.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libSPIRV.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libHLSL.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libSPIRV-Tools.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libSPIRV-Tools-opt.a
  OpenXR::openxr_loader
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libvulkan.so
)

target_include_directories( ${PROJECT_NAME} PUBLIC C:/business/purec/Meta-OpenXR-SDK/helloxr/Src)

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libandroid.so
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/liblog.so
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libglslang.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libOGLCompiler.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libOSDependent.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libshaderc.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libshaderc_util.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libSPIRV.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libHLSL.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libSPIRV-Tools.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libSPIRV-Tools-opt.a
  OpenXR::openxr_loader
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libvulkan.so
)

target_include_directories( ${PROJECT_NAME} INTERFACE C:/business/purec/Meta-OpenXR-SDK/helloxr/Src)

target_link_libraries(
  ${PROJECT_NAME}
  INTERFACE
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libandroid.so
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/liblog.so
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libglslang.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libOGLCompiler.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libOSDependent.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libshaderc.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libshaderc_util.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libSPIRV.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libHLSL.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libSPIRV-Tools.a
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libSPIRV-Tools-opt.a
  OpenXR::openxr_loader
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libvulkan.so
)

set_target_properties( ${PROJECT_NAME} PROPERTIES LINK_FLAGS "-u ANativeActivity_onCreate")

target_include_directories(${PROJECT_NAME} PRIVATE Src)

target_compile_definitions(
  helloxr
  PUBLIC
  __ANDROID__=1
  ANDROID_NDK=1
  DEFAULT_GRAPHICS_PLUGIN_VULKAN=1
  USE_DEBUG_EXTENTIONS=1
  USE_ONLINE_VULKAN_SHADERC=1
  VK_ENABLE_BETA_EXTENSIONS=1
  VK_NO_PROTOTYPES=1
  VK_USE_PLATFORM_ANDROID=1
  VK_USE_PLATFORM_ANDROID_KHR=1
  VULKAN_HPP_ENABLE_DYNAMIC_LOADER_TOOL=1
  XR_EXTENSION_PROTOTYPES=1
  #XR_KHR_LOADER_INIT_SUPPORT=1
  XR_NO_PROTOTYPES=1
  XR_USE_GRAPHICS_API_VULKAN=1
  XR_USE_PLATFORM_ANDROID=1
  XR_USE_PLATFORM_ANDROID_KHR=1
  XR_USE_TIMESPEC=1
  $<IF:$<CONFIG:Debug>,OVR_BUILD_DEBUG=1,>
)
