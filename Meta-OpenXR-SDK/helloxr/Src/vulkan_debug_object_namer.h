
// vulkan_debug_object_namer.h

#ifdef __cplusplus

class VulkanDebugObjectNamer
{
public:

  VulkanDebugObjectNamer() = default;

  VulkanDebugObjectNamer(VkInstance instance, VkDevice device)
  {
    if(instance && tableVk.GetInstanceProcAddr)
      BlahVkSetDebugUtilsObjectNameEXT = (PFN_vkSetDebugUtilsObjectNameEXT)tableVk.GetInstanceProcAddr(instance, "vkSetDebugUtilsObjectNameEXT");
  }

  VulkanDebugObjectNamer(const VulkanDebugObjectNamer&) = default;

  VulkanDebugObjectNamer& operator=(const VulkanDebugObjectNamer&) = default;

  ~VulkanDebugObjectNamer() { Reset(); }

  void Init(VkInstance instance, VkDevice device)
  {
    Reset();

    *this = VulkanDebugObjectNamer(instance, device);
  }

  VkResult SetName(VkObjectType objectType, uint64_t objectHandle, const char* pObjectName) const
  {
    if(gVkDevice && BlahVkSetDebugUtilsObjectNameEXT)
    {
      VkDebugUtilsObjectNameInfoEXT nameInfo {VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT, nullptr, objectType, objectHandle, pObjectName};

      return BlahVkSetDebugUtilsObjectNameEXT(gVkDevice, &nameInfo);
    }

    return VK_SUCCESS;
  }

  void Reset()
  {
    BlahVkSetDebugUtilsObjectNameEXT = nullptr;
  }

private:

  PFN_vkSetDebugUtilsObjectNameEXT BlahVkSetDebugUtilsObjectNameEXT {nullptr};
};

#endif
