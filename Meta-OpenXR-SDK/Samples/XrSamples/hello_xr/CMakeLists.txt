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

    add_library(${PROJECT_NAME} MODULE ${SRC_FILES})
    target_link_libraries(${PROJECT_NAME} PRIVATE native_activity_framework)
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