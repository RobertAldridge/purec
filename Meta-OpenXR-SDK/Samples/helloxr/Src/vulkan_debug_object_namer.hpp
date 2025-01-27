// Copyright (c) 2017-2024, The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <vulkan/vulkan_core.h>
#include <stdexcept>

#include "vulkan_wrapper.h"

extern struct VkGeneratedDispatchTableCore tableVk;

/// Utility class for assigning debug names to Vulkan objects we create.
class VulkanDebugObjectNamer
{
   public:

    /// Construct without initializing
    VulkanDebugObjectNamer() = default;

    /// Construct and initialize
    VulkanDebugObjectNamer(VkInstance instance, VkDevice device) : m_vkDevice {device}
    {
        if(tableVk.GetInstanceProcAddr)
          BlahVkSetDebugUtilsObjectNameEXT = (PFN_vkSetDebugUtilsObjectNameEXT)tableVk.GetInstanceProcAddr(instance, "vkSetDebugUtilsObjectNameEXT");
    }

    /// Copy constructor
    VulkanDebugObjectNamer(const VulkanDebugObjectNamer&) = default;

    /// Copy assignment operator
    VulkanDebugObjectNamer& operator=(const VulkanDebugObjectNamer&) = default;

    /// Destructor
    ~VulkanDebugObjectNamer() { Reset(); }

    /// (Re-) Initialize the namer: takes a valid `VkInstance` and `VkDevice`
    void Init(VkInstance instance, VkDevice device)
    {
        Reset();
        *this = VulkanDebugObjectNamer(instance, device);
    }

    /// The main operation of the namer: actually set an object name.
    ///
    /// If the namer is not initialized, this exits silently.
    VkResult SetName(VkObjectType objectType, uint64_t objectHandle, const char* pObjectName) const
    {
        if(m_vkDevice == nullptr)
        {
            return VK_SUCCESS;
        }

        if(BlahVkSetDebugUtilsObjectNameEXT != nullptr)
        {
            VkDebugUtilsObjectNameInfoEXT nameInfo {VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT, nullptr, objectType, objectHandle, pObjectName};

            return BlahVkSetDebugUtilsObjectNameEXT(m_vkDevice, &nameInfo);
        }

        return VK_SUCCESS;
    }

    /// De-initialize the namer, forgetting the device and the function pointer loaded from the instance.
    void Reset()
    {
        BlahVkSetDebugUtilsObjectNameEXT = nullptr;

        m_vkDevice = VK_NULL_HANDLE;
    }

   private:

    VkDevice m_vkDevice {VK_NULL_HANDLE};
    PFN_vkSetDebugUtilsObjectNameEXT BlahVkSetDebugUtilsObjectNameEXT {nullptr};
};
