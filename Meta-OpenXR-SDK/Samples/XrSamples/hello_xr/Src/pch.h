// Copyright (c) 2017-2024, The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <exception>
#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <numeric>
#include <set>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>

#include <time.h>
#include <string.h>

#include <android/log.h>
#include <anag.h>
#include <android/native_window.h>
#include <jni.h>
#include <sys/system_properties.h>


#define XR_USE_GRAPHICS_API_VULKAN 1

#define XR_USE_PLATFORM_ANDROID 1

#define VK_USE_PLATFORM_ANDROID_KHR 1

#include <vulkan/vulkan.h>

//
// OpenXR Headers
//
#include "openxr.h"
#include "openxr_platform.h"
#include "openxr_reflection.h"
