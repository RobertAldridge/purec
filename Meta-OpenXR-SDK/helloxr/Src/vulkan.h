
#ifndef VULKAN_H_
#define VULKAN_H_ 1

#include "vk_platform.h"
#include "vulkan_core.h"

#ifdef VK_USE_PLATFORM_ANDROID_KHR
#include "vulkan_android.h"
#endif

#ifdef VK_ENABLE_BETA_EXTENSIONS
#include "vulkan_beta.h"
#endif

#endif // VULKAN_H_
