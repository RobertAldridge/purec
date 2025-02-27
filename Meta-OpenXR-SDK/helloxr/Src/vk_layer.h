
// vk_layer.h

#define MAX_NUM_UNKNOWN_EXTS 250

 // Loader-Layer version negotiation API. Versions add the following features:
 // Versions 0/1 - Initial. Doesn't support vk_layerGetPhysicalDeviceProcAddr
 // or vk_icdNegotiateLoaderLayerInterfaceVersion.
 // Version 2 - Add support for vk_layerGetPhysicalDeviceProcAddr and
 // vk_icdNegotiateLoaderLayerInterfaceVersion.
#define CURRENT_LOADER_LAYER_INTERFACE_VERSION 2
#define MIN_SUPPORTED_LOADER_LAYER_INTERFACE_VERSION 1

#define VK_CURRENT_CHAIN_VERSION 1

// Typedef for use in the interfaces below
typedef PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, const char* pName);

// Version negotiation values
enum VkNegotiateLayerStructType
{
  LAYER_NEGOTIATE_UNINTIALIZED = 0,
  LAYER_NEGOTIATE_INTERFACE_STRUCT = 1
};

// Version negotiation structures
struct VkNegotiateLayerInterface
{
  VkNegotiateLayerStructType sType;
  void* pNext;
  uint32_t loaderLayerInterfaceVersion;
  PFN_vkGetInstanceProcAddr pfnGetInstanceProcAddr;
  PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr;
  PFN_GetPhysicalDeviceProcAddr pfnGetPhysicalDeviceProcAddr;
};

// Version negotiation functions
typedef VkResult (VKAPI_PTR *PFN_vkNegotiateLoaderLayerInterfaceVersion)(VkNegotiateLayerInterface *pVersionStruct);

// Function prototype for unknown physical device extension command
typedef VkResult(VKAPI_PTR *PFN_PhysDevExt)(VkPhysicalDevice phys_device);

// ------------------------------------------------------------------------------------------------
// CreateInstance and CreateDevice support structures

/* Sub type of structure for instance and device loader ext of CreateInfo.
 * When sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
 * or sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
 * then VkLayerFunction indicates struct type pointed to by pNext
 */
enum VkLayerFunction_
{
  VK_LAYER_LINK_INFO = 0,
  VK_LOADER_DATA_CALLBACK = 1,
  VK_LOADER_LAYER_CREATE_DEVICE_CALLBACK = 2,
  VK_LOADER_FEATURES = 3
};

typedef enum VkLayerFunction_ VkLayerFunction;

struct VkLayerInstanceLink_
{
  struct VkLayerInstanceLink_* pNext;
  PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
  PFN_GetPhysicalDeviceProcAddr pfnNextGetPhysicalDeviceProcAddr;
};

typedef struct VkLayerInstanceLink_ VkLayerInstanceLink;

/*
 * When creating the device chain the loader needs to pass
 * down information about it's device structure needed at
 * the end of the chain. Passing the data via the
 * VkLayerDeviceInfo avoids issues with finding the
 * exact instance being used.
 */

struct VkLayerDeviceInfo_
{
  void* device_info;
  PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
};

typedef struct VkLayerDeviceInfo_ VkLayerDeviceInfo;

typedef VkResult (VKAPI_PTR *PFN_vkSetInstanceLoaderData)(VkInstance instance, void *object);

typedef VkResult (VKAPI_PTR *PFN_vkSetDeviceLoaderData)(VkDevice device, void *object);

typedef VkResult (VKAPI_PTR *PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDevice *pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr *nextGDPA);

typedef void (VKAPI_PTR *PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, const VkAllocationCallbacks *pAllocator, PFN_vkDestroyDevice destroyFunction);

enum VkLoaderFeastureFlagBits
{
  VK_LOADER_FEATURE_PHYSICAL_DEVICE_SORTING = 0x00000001
};

typedef enum VkLoaderFeastureFlagBits VkLoaderFlagBits;

typedef VkFlags VkLoaderFeatureFlags;

struct VkLayerInstanceCreateInfo
{
  // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
  VkStructureType sType;

  const void* pNext;
  VkLayerFunction function;

  union
  {
    VkLayerInstanceLink* pLayerInfo;
    PFN_vkSetInstanceLoaderData pfnSetInstanceLoaderData;

    struct
    {
      PFN_vkLayerCreateDevice pfnLayerCreateDevice;
      PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;

    }layerDevice;

    VkLoaderFeatureFlags loaderFeatures;

  }u;
};

struct VkLayerDeviceLink_
{
  struct VkLayerDeviceLink_* pNext;
  PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
  PFN_vkGetDeviceProcAddr pfnNextGetDeviceProcAddr;

};

typedef struct VkLayerDeviceLink_ VkLayerDeviceLink;

struct VkLayerDeviceCreateInfo
{
  // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
  VkStructureType sType;
  const void* pNext;
  VkLayerFunction function;

  union
  {
    VkLayerDeviceLink* pLayerInfo;
    PFN_vkSetDeviceLoaderData pfnSetDeviceLoaderData;

  }u;
};

VKAPI_ATTR VkResult VKAPI_CALL vkNegotiateLoaderLayerInterfaceVersion(VkNegotiateLayerInterface *pVersionStruct);

enum VkChainType
{
  VK_CHAIN_TYPE_UNKNOWN = 0,
  VK_CHAIN_TYPE_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES = 1,
  VK_CHAIN_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES = 2,
  VK_CHAIN_TYPE_ENUMERATE_INSTANCE_VERSION = 3
};

struct VkChainHeader
{
  VkChainType type;
  uint32_t version;
  uint32_t size;
};

struct VkEnumerateInstanceExtensionPropertiesChain
{
  VkChainHeader header;

  VkResult(VKAPI_PTR* pfnNextLayer)(const struct VkEnumerateInstanceExtensionPropertiesChain*, const char*, uint32_t*, VkExtensionProperties* );

  const struct VkEnumerateInstanceExtensionPropertiesChain* pNextLink;

  inline VkResult CallDown(const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties) const
  {
    return pfnNextLayer(pNextLink, pLayerName, pPropertyCount, pProperties);
  }
};

struct VkEnumerateInstanceLayerPropertiesChain
{
  VkChainHeader header;

  VkResult(VKAPI_PTR* pfnNextLayer)(const struct VkEnumerateInstanceLayerPropertiesChain*, uint32_t*, VkLayerProperties* );

  const struct VkEnumerateInstanceLayerPropertiesChain* pNextLink;

  inline VkResult CallDown(uint32_t* pPropertyCount, VkLayerProperties* pProperties) const
  {
    return pfnNextLayer(pNextLink, pPropertyCount, pProperties);
  }
};

struct VkEnumerateInstanceVersionChain
{
  VkChainHeader header;

  VkResult(VKAPI_PTR* pfnNextLayer)(const struct VkEnumerateInstanceVersionChain*, uint32_t* );

  const struct VkEnumerateInstanceVersionChain* pNextLink;

  inline VkResult CallDown(uint32_t* pApiVersion) const
  {
    return pfnNextLayer(pNextLink, pApiVersion);
  }
};
