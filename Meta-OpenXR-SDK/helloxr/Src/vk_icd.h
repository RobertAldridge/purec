
// vk_icd.h

// Loader-ICD version negotiation API. Versions add the following features:
// Version 0 - Initial. Doesn't support vk_icdGetInstanceProcAddr
// or vk_icdNegotiateLoaderICDInterfaceVersion.
// Version 1 - Add support for vk_icdGetInstanceProcAddr.
// Version 2 - Add Loader/ICD Interface version negotiation
// via vk_icdNegotiateLoaderICDInterfaceVersion.
// Version 3 - Add ICD creation/destruction of KHR_surface objects.
// Version 4 - Add unknown physical device extension querying via
// vk_icdGetPhysicalDeviceProcAddr.
// Version 5 - Tells ICDs that the loader is now paying attention to the
// application version of Vulkan passed into the ApplicationInfo
// structure during vkCreateInstance. This will tell the ICD
// that if the loader is older, it should automatically fail a
// call for any API version > 1.0. Otherwise, the loader will
// manually determine if it can support the expected version.
// Version 6 - Add support for vk_icdEnumerateAdapterPhysicalDevices.
// Version 7 - If an ICD supports any of the following functions, they must be
// queryable with vk_icdGetInstanceProcAddr:
// vk_icdNegotiateLoaderICDInterfaceVersion
// vk_icdGetPhysicalDeviceProcAddr
// vk_icdEnumerateAdapterPhysicalDevices (Windows only)
// In addition, these functions no longer need to be exported directly.
// This version allows drivers provided through the extension
// VK_LUNARG_direct_driver_loading be able to support the entire
// Driver-Loader interface.

#define CURRENT_LOADER_ICD_INTERFACE_VERSION 7
#define MIN_SUPPORTED_LOADER_ICD_INTERFACE_VERSION 0
#define MIN_PHYS_DEV_EXTENSION_ICD_INTERFACE_VERSION 4

// Old typedefs that don't follow a proper naming convention but are preserved for compatibility
typedef VkResult(VKAPI_PTR *PFN_vkNegotiateLoaderICDInterfaceVersion)(uint32_t *pVersion);
// This is defined in vk_layer.h which will be found by the loader, but if an ICD is building against this
// file directly, it won't be found.
#ifndef PFN_GetPhysicalDeviceProcAddr
typedef PFN_vkVoidFunction(VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, const char *pName);
#endif

// Typedefs for loader/ICD interface
typedef VkResult (VKAPI_PTR *PFN_vk_icdNegotiateLoaderICDInterfaceVersion)(uint32_t* pVersion);
typedef PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetInstanceProcAddr)(VkInstance instance, const char* pName);
typedef PFN_vkVoidFunction (VKAPI_PTR *PFN_vk_icdGetPhysicalDeviceProcAddr)(VkInstance instance, const char* pName);

// Prototypes for loader/ICD interface
#if !defined(VK_NO_PROTOTYPES)
VKAPI_ATTR VkResult VKAPI_CALL vk_icdNegotiateLoaderICDInterfaceVersion(uint32_t* pVersion);
VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetInstanceProcAddr(VkInstance instance, const char* pName);
VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetPhysicalDeviceProcAddr(VkInstance instance, const char* pName);
#endif

/*
 * The ICD must reserve space for a pointer for the loader's dispatch
 * table, at the start of <each object>.
 * The ICD must initialize this variable using the SET_LOADER_MAGIC_VALUE macro.
 */

#define ICD_LOADER_MAGIC 0x01CDC0DE

union VK_LOADER_DATA
{
  uintptr_t loaderMagic;
  void *loaderData;
};

static inline void set_loader_magic_value(void *pNewObject)
{
 VK_LOADER_DATA *loader_info = (VK_LOADER_DATA *)pNewObject;
 loader_info->loaderMagic = ICD_LOADER_MAGIC;
}

static inline bool valid_loader_magic_value(void *pNewObject)
{
 const VK_LOADER_DATA *loader_info = (VK_LOADER_DATA *)pNewObject;
 return (loader_info->loaderMagic & 0xffffffff) == ICD_LOADER_MAGIC;
}

/*
 * Windows and Linux ICDs will treat VkSurfaceKHR as a pointer to a struct that
 * contains the platform-specific connection and surface information.
 */
enum VkIcdWsiPlatform
{
 VK_ICD_WSI_PLATFORM_MIR,
 VK_ICD_WSI_PLATFORM_WAYLAND,
 VK_ICD_WSI_PLATFORM_WIN32,
 VK_ICD_WSI_PLATFORM_XCB,
 VK_ICD_WSI_PLATFORM_XLIB,
 VK_ICD_WSI_PLATFORM_ANDROID,
 VK_ICD_WSI_PLATFORM_DISPLAY,
 VK_ICD_WSI_PLATFORM_HEADLESS,
 VK_ICD_WSI_PLATFORM_DIRECTFB,
 VK_ICD_WSI_PLATFORM_VI,
 VK_ICD_WSI_PLATFORM_GGP,
 VK_ICD_WSI_PLATFORM_SCREEN,
 VK_ICD_WSI_PLATFORM_FUCHSIA,
};

struct VkIcdSurfaceBase
{
  VkIcdWsiPlatform platform;
};

struct VkIcdSurfaceAndroid
{
  VkIcdSurfaceBase base;
  struct ANativeWindow* window;
};

struct VkIcdSurfaceDisplay
{
  VkIcdSurfaceBase base;
  VkDisplayModeKHR displayMode;
  uint32_t planeIndex;
  uint32_t planeStackIndex;
  VkSurfaceTransformFlagBitsKHR transform;
  float globalAlpha;
  VkDisplayPlaneAlphaFlagBitsKHR alphaMode;
  VkExtent2D imageExtent;
};

struct VkIcdSurfaceHeadless
{
  VkIcdSurfaceBase base;
};
