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
project(helloxr)

#if(NOT TARGET OpenXR::openxr_loader)
#    find_package(OpenXR REQUIRED)
#endif()

file(GLOB_RECURSE SRC_FILES Src/*.c Src/*.cpp)

file(TO_CMAKE_PATH "$ENV{VULKAN_SDK}" VULKAN_SDK)

add_library(${PROJECT_NAME} MODULE ${SRC_FILES} )

#target_link_libraries(${PROJECT_NAME} PRIVATE native_activity_framework)

#classloader-namespace

#add_library(OpenXR::openxr_loader STATIC IMPORTED)

#set_target_properties(OpenXR::openxr_loader PROPERTIES IMPORTED_LOCATION C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libopenxr_loader.so)

#add_library(OpenXR::openxr_loader SHARED IMPORTED)

#set_target_properties(OpenXR::openxr_loader PROPERTIES INTERFACE_LINK_LIBRARIES "Threads::Threads;OpenXR::headers")

#add_library(OpenXR::headers INTERFACE IMPORTED)

#set_property(TARGET OpenXR::openxr_loader APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
#set_target_properties(OpenXR::openxr_loader PROPERTIES IMPORTED_LOCATION_RELEASE "C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libopenxr_loader.so" IMPORTED_SONAME_RELEASE "libopenxr_loader.so")
#list(APPEND _cmake_import_check_targets OpenXR::openxr_loader)
#list(APPEND _cmake_import_check_files_for_OpenXR::openxr_loader "C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libopenxr_loader.so")

add_library(OpenXR::headers INTERFACE IMPORTED)

set_target_properties(OpenXR::headers PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "C:/business/purec/Meta-OpenXR-SDK/helloxr/Src" INTERFACE_LINK_LIBRARIES "")

add_library(OpenXR::openxr_loader SHARED IMPORTED)

set_target_properties(OpenXR::openxr_loader PROPERTIES IMPORTED_LOCATION "C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libopenxr_loader.so" INTERFACE_LINK_LIBRARIES "OpenXR::headers")

#find_package(OpenXR REQUIRED)
#find_package(Vulkan)

target_include_directories(${PROJECT_NAME} PRIVATE C:/business/purec/Meta-OpenXR-SDK/helloxr/Src)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libandroid.so
  #EGL
  #GLESv3
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/liblog.so
  #minizip
  #stb
  #ktx
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
  #C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libopenxr_loader.so
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libvulkan.so )

target_include_directories(${PROJECT_NAME} PUBLIC C:/business/purec/Meta-OpenXR-SDK/helloxr/Src)

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libandroid.so
  #EGL
  #GLESv3
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/liblog.so
  #minizip
  #stb
  #ktx
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
  #C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libopenxr_loader.so
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libvulkan.so )

target_include_directories(${PROJECT_NAME} INTERFACE C:/business/purec/Meta-OpenXR-SDK/helloxr/Src)

target_link_libraries(
  ${PROJECT_NAME}
  INTERFACE
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libandroid.so
  #EGL
  #GLESv3
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/liblog.so
  #minizip
  #stb
  #ktx
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
  #C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libopenxr_loader.so
  C:/business/purec/Meta-OpenXR-SDK/helloxr/Src/libvulkan.so )

#C:\Users\RobertLocalAldridge\AppData\Local\Android\Sdk\ndk\25.1.8937393\sources\third_party\shaderc

#C:\Users\RobertLocalAldridge\AppData\Local\Android\Sdk\ndk\25.1.8937393\sources\third_party\vulkan\src\include\vulkan

#C:\Users\RobertLocalAldridge\AppData\Local\Android\Sdk\ndk\25.1.8937393\toolchains\llvm\prebuilt\windows-x86_64\sysroot\usr\include\vulkan

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-u ANativeActivity_onCreate")

# Common across platforms
target_include_directories(${PROJECT_NAME} PRIVATE Src)

target_compile_definitions(
  helloxr
  PUBLIC
  __ANDROID__=1
  ANDROID_NDK=1
  DEFAULT_GRAPHICS_PLUGIN_VULKAN=1
  USE_DEBUG_EXTENTIONS=1
  USE_GLSLANGVALIDATOR=1
  USE_ONLINE_VULKAN_SHADERC=1
  VK_ENABLE_BETA_EXTENSIONS=1
  VK_NO_PROTOTYPES=1
  VK_USE_PLATFORM_ANDROID=1
  VK_USE_PLATFORM_ANDROID_KHR=1
  XR_NO_PROTOTYPES=1
  XR_USE_GRAPHICS_API_VULKAN=1
  XR_USE_PLATFORM_ANDROID=1
  XR_USE_PLATFORM_ANDROID_KHR=1
  $<IF:$<CONFIG:Debug>,OVR_BUILD_DEBUG=1,> )
