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

add_executable(openxr_runtime_list list.cpp)
target_include_directories(
    openxr_runtime_list
    PRIVATE "${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/src/common"
            "${PROJECT_SOURCE_DIR}/external/include"
)
if(XR_USE_GRAPHICS_API_VULKAN)
    target_include_directories(
        openxr_runtime_list PRIVATE ${Vulkan_INCLUDE_DIRS}
    )
endif()

target_link_libraries(openxr_runtime_list OpenXR::openxr_loader)

set_target_properties(openxr_runtime_list PROPERTIES FOLDER ${TESTS_FOLDER})

install(
    TARGETS openxr_runtime_list RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
                                        COMPONENT openxr_runtime_list
)

    install(
        FILES openxr_runtime_list.1
        DESTINATION ${CMAKE_INSTALL_MANDIR}/man1/
        COMPONENT ManPages
    )
