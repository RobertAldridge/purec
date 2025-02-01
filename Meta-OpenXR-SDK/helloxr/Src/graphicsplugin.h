
// graphicsplugin.h

#define THROW_VK(res, cmd) ThrowVkResult(res, #cmd, FILE_AND_LINE)

#define CHECK_VKCMD(cmd) CheckVkResult(cmd, #cmd, FILE_AND_LINE)

#define CHECK_VKRESULT(res, cmdStr) CheckVkResult(res, cmdStr, FILE_AND_LINE)

enum class CmdBufferStateEnum
{
  Undefined,
  Initialized,
  Recording,
  Executable,
  Executing
};

struct Cube
{
  XrPosef Pose;
  XrVector3f Scale;
};

struct VulkanTutorialSwapChainSupportDetails
{
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

struct VertexBufferBaseBlah
{
  uint32_t idx;
  uint32_t vtx;

};

constexpr VkFlags MemoryAllocator_m_memoryAllocatorDefaultFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

const uint32_t VULKAN_TUTORIAL_WIDTH = 800;
const uint32_t VULKAN_TUTORIAL_HEIGHT = 600;

const int VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> VulkanTutorialValidationLayers =
{
  "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> VulkanTutorialDeviceExtensions =
{
  VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
const bool VulkanTutorialEnableValidationLayers = false;
#else
const bool VulkanTutorialEnableValidationLayers = true;
#endif

const std::vector<uint16_t> VulkanTutorialIndices = {0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4};

extern VkPhysicalDeviceMemoryProperties gMemoryAllocatorMemoryProperties;

extern CmdBufferStateEnum gCmdBufferState;

extern VkCommandPool gCmdBufferPool;

extern VkCommandBuffer gCmdBufferBuffer;

extern VkFence gCmdBufferExecFence;

extern VkBuffer gVertexBufferBaseIdxBuf;

extern VkDeviceMemory gVertexBufferBaseIdxMem;

extern VkBuffer gVertexBufferBaseVtxBuf;

extern VkDeviceMemory gVertexBufferBaseVtxMem;

extern VkVertexInputBindingDescription gVertexBufferBaseBindDesc;

extern std::vector<VkVertexInputAttributeDescription> gVertexBufferBaseAttrDesc;

extern VertexBufferBaseBlah gVertexBufferBaseCount;

extern std::vector<std::vector<XrSwapchainImageVulkan2KHR> > m_swapchainImageContextSwapchainImages;

extern std::vector<std::vector<VkImage> > m_swapchainImageContextStdVector_renderTargetColorImage;
extern std::vector<std::vector<VkImage> > m_swapchainImageContextStdVector_renderTargetDepthImage;
extern std::vector<std::vector<VkImageView> > m_swapchainImageContextStdVector_renderTargetColorView;
extern std::vector<std::vector<VkImageView> > m_swapchainImageContextStdVector_renderTargetDepthView;
extern std::vector<std::vector<VkFramebuffer> > m_swapchainImageContextStdVector_renderTargetFrameBuffer;

extern std::vector<VkExtent2D> m_swapchainImageContextSize;

extern std::vector<VkDeviceMemory> m_swapchainImageContext_depthBufferDepthMemory;
extern std::vector<VkImage> m_swapchainImageContext_depthBufferDepthImage;
extern std::vector<VkImageLayout> m_swapchainImageContext_depthBufferVkImageLayout;

extern std::vector<VkFormat> m_swapchainImageContext_renderPassColorFmt;
extern std::vector<VkFormat> m_swapchainImageContext_renderPassDepthFmt;
extern std::vector<VkRenderPass> m_swapchainImageContext_renderPassPass;

extern std::vector<VkPipeline> m_swapchainImageContextPipe_pipelinePipe;
extern std::vector<VkPrimitiveTopology> m_swapchainImageContextPipe_pipelineTopology;
extern std::vector<std::vector<VkDynamicState> > m_swapchainImageContextPipe_pipelineDynamicStateEnables;

extern std::vector<XrStructureType> m_swapchainImageContextSwapchainImageType;

extern std::vector<VulkanDebugObjectNamer> m_swapchainImageContextNamer;

extern XrGraphicsBindingVulkan2KHR gVulkanGraphicsPluginXrGraphicsBindingVulkan2KHR;

//std::vector<SwapchainImageContext*> gVulkanGraphicsPluginStdList_SwapchainImageContext;
extern std::vector<int> gVulkanGraphicsPluginStdList_SwapchainImageContext;

extern std::map<const XrSwapchainImageBaseHeader*, int> gVulkanGraphicsPluginStdMap_XrSwapchainImageBaseHeader_SwapchainImageContext;

extern VulkanDebugObjectNamer gVulkanGraphicsPluginVulkanDebugObjectNamer;

extern uint32_t gVulkanGraphicsPluginQueueFamilyIndex;

extern VkQueue gVulkanGraphicsPluginVkQueue;

extern VkSemaphore gVulkanGraphicsPluginVkSemaphoreDrawDone;

extern std::array<float, 4> gVulkanGraphicsPluginStdArray_float_4_clearColor;

extern PFN_vkCreateDebugUtilsMessengerEXT gVulkanGraphicsPluginVkCreateDebugUtilsMessengerEXT;

extern VkDebugUtilsMessengerEXT gVulkanGraphicsPluginVkDebugUtilsMessenger;

std::string VulkanGraphicsPlugin_BlahVkObjectTypeToString(VkObjectType objectType);

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanGraphicsPlugin_debugMessageThunk(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

void VulkanGraphicsPlugin_VulkanGraphicsPlugin();

void VulkanGraphicsPlugin_VulkanGraphicsPlugin_Destructor();

std::vector<std::string> VulkanGraphicsPlugin_VulkanGraphicsPluginGetInstanceExtensions();

// note: The output must not outlive the input - this modifies the input and returns a collection of views into that modified input!
std::vector<const char*> VulkanGraphicsPlugin_VulkanGraphicsPluginParseExtensionString(char* names);

const char* VulkanGraphicsPlugin_VulkanGraphicsPluginGetValidationLayerName();

void VulkanGraphicsPlugin_VulkanGraphicsPluginInitializeDevice(XrInstance instance, XrSystemId systemId);

// Compile a shader to a SPIR-V binary.
std::vector<uint32_t> VulkanGraphicsPlugin_VulkanGraphicsPluginCompileGlslShader(const std::string& name, shaderc_shader_kind kind, const std::string& source);

void VulkanGraphicsPlugin_VulkanGraphicsPluginInitializeResources();

int64_t VulkanGraphicsPlugin_VulkanGraphicsPluginSelectColorSwapchainFormat(const std::vector<int64_t>& runtimeFormats);

const XrBaseInStructure* VulkanGraphicsPlugin_VulkanGraphicsPluginGetGraphicsBinding();

std::vector<XrSwapchainImageBaseHeader*> VulkanGraphicsPlugin_VulkanGraphicsPluginAllocateSwapchainImageStructs(uint32_t capacity, const XrSwapchainCreateInfo& swapchainCreateInfo);

void VulkanGraphicsPlugin_VulkanGraphicsPluginRenderView(const XrCompositionLayerProjectionView& layerView, const XrSwapchainImageBaseHeader* swapchainImage, int64_t /*swapchainFormat*/, const std::vector<Cube>& cubes);

uint32_t VulkanGraphicsPlugin_VulkanGraphicsPluginGetSupportedSwapchainSampleCount(const XrViewConfigurationView& );

void VulkanGraphicsPlugin_VulkanGraphicsPluginUpdateOptions();

VkBool32 VulkanGraphicsPlugin_VulkanGraphicsPluginDebugMessage(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData);

XrStructureType VulkanGraphicsPlugin_VulkanGraphicsPluginGetGraphicsBindingType();

XrStructureType VulkanGraphicsPlugin_VulkanGraphicsPluginGetSwapchainImageType();

XrResult VulkanGraphicsPlugin_VulkanGraphicsPluginCreateVulkanInstanceKHR(XrInstance instance, const XrVulkanInstanceCreateInfoKHR* createInfo, VkInstance* vulkanInstance, VkResult* vulkanResult);

XrResult VulkanGraphicsPlugin_VulkanGraphicsPluginCreateVulkanDeviceKHR(XrInstance instance, const XrVulkanDeviceCreateInfoKHR* createInfo, VkDevice* vulkanDevice, VkResult* vulkanResult);

XrResult VulkanGraphicsPlugin_VulkanGraphicsPluginGetVulkanGraphicsDevice2KHR(XrInstance instance, const XrVulkanGraphicsDeviceGetInfoKHR* getInfo, VkPhysicalDevice* vulkanPhysicalDevice);

XrResult VulkanGraphicsPlugin_VulkanGraphicsPluginGetVulkanGraphicsRequirements2KHR(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkan2KHR* graphicsRequirements);

void VulkanGraphicsPlugin_CreateGraphicsPlugin_Vulkan();
