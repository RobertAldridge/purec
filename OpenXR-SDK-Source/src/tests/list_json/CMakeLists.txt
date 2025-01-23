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

if(ANDROID)
    add_library(
        openxr_runtime_list_json MODULE
        list_json.cpp $<TARGET_OBJECTS:android_native_app_glue>
    )
    target_link_libraries(
        openxr_runtime_list_json PRIVATE ${ANDROID_LIBRARY}
                                         ${ANDROID_LOG_LIBRARY}
    )
    target_include_directories(
        openxr_runtime_list_json PRIVATE ${ANDROID_NATIVE_APP_GLUE}
    )
else()
    add_executable(openxr_runtime_list_json list_json.cpp)
endif()

set_target_properties(
    openxr_runtime_list_json PROPERTIES FOLDER ${TESTS_FOLDER}
)
target_link_libraries(openxr_runtime_list_json PRIVATE OpenXR::openxr_loader)
target_include_directories(
    openxr_runtime_list_json PRIVATE "${PROJECT_SOURCE_DIR}/src"
                                     "${PROJECT_SOURCE_DIR}/src/common"
)
target_link_libraries(openxr_runtime_list_json PRIVATE OpenXR::openxr_loader)

if(XR_USE_GRAPHICS_API_VULKAN)
    target_include_directories(
        openxr_runtime_list_json PRIVATE ${Vulkan_INCLUDE_DIRS}
    )
    target_link_libraries(openxr_runtime_list_json PRIVATE ${Vulkan_LIBRARY})
endif()

    install(
        FILES openxr_runtime_list_json.1
        DESTINATION ${CMAKE_INSTALL_MANDIR}/man1/
        COMPONENT ManPages
    )
