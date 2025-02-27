
// vulkan_android.h

extern "C" {

// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_android_surface 1
struct ANativeWindow;
#define VK_KHR_ANDROID_SURFACE_SPEC_VERSION 6
#define VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"
typedef VkFlags VkAndroidSurfaceCreateFlagsKHR;

struct VkAndroidSurfaceCreateInfoKHR
{
  VkStructureType sType;
  const void* pNext;
  VkAndroidSurfaceCreateFlagsKHR flags;
  struct ANativeWindow* window;
};

typedef VkResult (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, const VkAndroidSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateAndroidSurfaceKHR(
 VkInstance instance,
 const VkAndroidSurfaceCreateInfoKHR* pCreateInfo,
 const VkAllocationCallbacks* pAllocator,
 VkSurfaceKHR* pSurface);
#endif

// VK_ANDROID_external_memory_android_hardware_buffer is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_memory_android_hardware_buffer 1
struct AHardwareBuffer;
#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_SPEC_VERSION 5
#define VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"
struct VkAndroidHardwareBufferUsageANDROID
{
  VkStructureType sType;
  void* pNext;
  uint64_t androidHardwareBufferUsage;
};

struct VkAndroidHardwareBufferPropertiesANDROID
{
  VkStructureType sType;
  void* pNext;
  VkDeviceSize allocationSize;
  uint32_t memoryTypeBits;
};

struct VkAndroidHardwareBufferFormatPropertiesANDROID
{
  VkStructureType sType;
  void* pNext;
  VkFormat format;
  uint64_t externalFormat;
  VkFormatFeatureFlags formatFeatures;
  VkComponentMapping samplerYcbcrConversionComponents;
  VkSamplerYcbcrModelConversion suggestedYcbcrModel;
  VkSamplerYcbcrRange suggestedYcbcrRange;
  VkChromaLocation suggestedXChromaOffset;
  VkChromaLocation suggestedYChromaOffset;
};

struct VkImportAndroidHardwareBufferInfoANDROID
{
  VkStructureType sType;
  const void* pNext;
  struct AHardwareBuffer* buffer;
};

struct VkMemoryGetAndroidHardwareBufferInfoANDROID
{
  VkStructureType sType;
  const void* pNext;
  VkDeviceMemory memory;
};

struct VkExternalFormatANDROID
{
  VkStructureType sType;
  void* pNext;
  uint64_t externalFormat;
};

struct VkAndroidHardwareBufferFormatProperties2ANDROID
{
  VkStructureType sType;
  void* pNext;
  VkFormat format;
  uint64_t externalFormat;
  VkFormatFeatureFlags2 formatFeatures;
  VkComponentMapping samplerYcbcrConversionComponents;
  VkSamplerYcbcrModelConversion suggestedYcbcrModel;
  VkSamplerYcbcrRange suggestedYcbcrRange;
  VkChromaLocation suggestedXChromaOffset;
  VkChromaLocation suggestedYChromaOffset;
};

typedef VkResult (VKAPI_PTR *PFN_vkGetAndroidHardwareBufferPropertiesANDROID)(VkDevice device, const struct AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties);
typedef VkResult (VKAPI_PTR *PFN_vkGetMemoryAndroidHardwareBufferANDROID)(VkDevice device, const VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, struct AHardwareBuffer** pBuffer);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetAndroidHardwareBufferPropertiesANDROID(
 VkDevice device,
 const struct AHardwareBuffer* buffer,
 VkAndroidHardwareBufferPropertiesANDROID* pProperties);

VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryAndroidHardwareBufferANDROID(
 VkDevice device,
 const VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo,
 struct AHardwareBuffer** pBuffer);
#endif

// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#define VK_ANDROID_external_format_resolve 1
#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_VERSION 1
#define VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"
struct VkPhysicalDeviceExternalFormatResolveFeaturesANDROID
{
  VkStructureType sType;
  void* pNext;
  VkBool32 externalFormatResolve;
};

struct VkPhysicalDeviceExternalFormatResolvePropertiesANDROID
{
  VkStructureType sType;
  void* pNext;
  VkBool32 nullColorAttachmentWithExternalFormatResolve;
  VkChromaLocation externalFormatResolveChromaOffsetX;
  VkChromaLocation externalFormatResolveChromaOffsetY;
};

struct VkAndroidHardwareBufferFormatResolvePropertiesANDROID
{
  VkStructureType sType;
  void* pNext;
  VkFormat colorAttachmentFormat;
};

}
