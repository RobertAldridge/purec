
// openxr_loader_negotiation.h

#define XR_LOADER_VERSION_1_0 1

#define XR_CURRENT_LOADER_API_LAYER_VERSION 1

#define XR_CURRENT_LOADER_RUNTIME_VERSION 1

#define XR_LOADER_INFO_STRUCT_VERSION 1

#define XR_API_LAYER_INFO_STRUCT_VERSION 1

#define XR_RUNTIME_INFO_STRUCT_VERSION 1

#define XR_API_LAYER_NEXT_INFO_STRUCT_VERSION 1

#define XR_API_LAYER_CREATE_INFO_STRUCT_VERSION 1

#define XR_API_LAYER_MAX_SETTINGS_PATH_SIZE 512

enum XrLoaderInterfaceStructs
{
  XR_LOADER_INTERFACE_STRUCT_UNINTIALIZED = 0,
  XR_LOADER_INTERFACE_STRUCT_LOADER_INFO = 1,
  XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST = 2,
  XR_LOADER_INTERFACE_STRUCT_RUNTIME_REQUEST = 3,
  XR_LOADER_INTERFACE_STRUCT_API_LAYER_CREATE_INFO = 4,
  XR_LOADER_INTERFACE_STRUCT_API_LAYER_NEXT_INFO = 5,
  XR_LOADER_INTERFACE_STRUCTS_MAX_ENUM = 0x7FFFFFFF
};

typedef XrResult (XRAPI_PTR *PFN_xrGetInstanceProcAddr)(XrInstance instance, const char* name, PFN_xrVoidFunction* function);

typedef struct XrApiLayerCreateInfo XrApiLayerCreateInfo;

typedef XrResult (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(const XrInstanceCreateInfo* info, const XrApiLayerCreateInfo* apiLayerInfo, XrInstance* instance);

struct XrApiLayerNextInfo
{
  XrLoaderInterfaceStructs structType;
  uint32_t structVersion;
  size_t structSize;
  char layerName[XR_MAX_API_LAYER_NAME_SIZE];
  PFN_xrGetInstanceProcAddr nextGetInstanceProcAddr;
  PFN_xrCreateApiLayerInstance nextCreateApiLayerInstance;
  struct XrApiLayerNextInfo* next;
};

struct XrApiLayerCreateInfo
{
  XrLoaderInterfaceStructs structType;
  uint32_t structVersion;
  size_t structSize;
  void* XR_MAY_ALIAS loaderInstance;
  char settings_file_location[XR_API_LAYER_MAX_SETTINGS_PATH_SIZE];
  XrApiLayerNextInfo* nextInfo;
};

struct XrNegotiateLoaderInfo
{
  XrLoaderInterfaceStructs structType;
  uint32_t structVersion;
  size_t structSize;
  uint32_t minInterfaceVersion;
  uint32_t maxInterfaceVersion;
  XrVersion minApiVersion;
  XrVersion maxApiVersion;
};

struct XrNegotiateRuntimeRequest
{
  XrLoaderInterfaceStructs structType;
  uint32_t structVersion;
  size_t structSize;
  uint32_t runtimeInterfaceVersion;
  XrVersion runtimeApiVersion;
  PFN_xrGetInstanceProcAddr getInstanceProcAddr;
};

struct XrNegotiateApiLayerRequest
{
  XrLoaderInterfaceStructs structType;
  uint32_t structVersion;
  size_t structSize;
  uint32_t layerInterfaceVersion;
  XrVersion layerApiVersion;
  PFN_xrGetInstanceProcAddr getInstanceProcAddr;
  PFN_xrCreateApiLayerInstance createApiLayerInstance;
};

typedef XrResult (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(const XrInstanceCreateInfo* info, const XrApiLayerCreateInfo* layerInfo, XrInstance* instance);

typedef XrResult (XRAPI_PTR *PFN_xrNegotiateLoaderRuntimeInterface)(const XrNegotiateLoaderInfo* loaderInfo, XrNegotiateRuntimeRequest* runtimeRequest);

typedef XrResult (XRAPI_PTR *PFN_xrNegotiateLoaderApiLayerInterface)(const XrNegotiateLoaderInfo* loaderInfo, const char* layerName, XrNegotiateApiLayerRequest* apiLayerRequest);

#ifndef XR_NO_PROTOTYPES

#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrCreateApiLayerInstance(const XrInstanceCreateInfo* info, const XrApiLayerCreateInfo* layerInfo, XrInstance* instance);

XRAPI_ATTR XrResult XRAPI_CALL xrNegotiateLoaderRuntimeInterface(const XrNegotiateLoaderInfo* loaderInfo, XrNegotiateRuntimeRequest* runtimeRequest);

XRAPI_ATTR XrResult XRAPI_CALL xrNegotiateLoaderApiLayerInterface(const XrNegotiateLoaderInfo* loaderInfo, const char* layerName, XrNegotiateApiLayerRequest* apiLayerRequest);
#endif /* XR_EXTENSION_PROTOTYPES */

#endif /* !XR_NO_PROTOTYPES */
