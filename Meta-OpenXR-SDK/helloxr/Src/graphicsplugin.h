
// graphicsplugin.h

#define THROW_VULKAN(res, cmd) ThrowVkResult(res, #cmd, FILE_AND_LINE_CHECK)

#define CHECK_VULKANCMD(cmd) CheckVkResult(cmd, #cmd, FILE_AND_LINE_CHECK)

#define CHECK_VULKANRESULT(res, cmdStr) CheckVkResult(res, cmdStr, FILE_AND_LINE_CHECK)

#define CHECK_VULKANCMDBUFFERSTATE(s) \
do \
{ \
    if(gCmdBufferState != (s) ) \
    { \
        Log::Write(Log::Level::Error, std::string("Expecting state " #s " from ") + __FUNCTION__ + ", in " + CmdBuffer_CmdBufferStateString(gCmdBufferState) ); \
        return false; \
    } \
\
}while(0)

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

struct VulkanTutorialQueueFamilyIndices
{
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;
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

const std::vector<VkFormat> VulkanTutorialDepthFormatCandidates = {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT};

constexpr char VertexShaderGlsl[] =
R"_(

  #version 430
  #extension GL_ARB_separate_shader_objects : enable

  layout (std140, push_constant) uniform buf
  {
    mat4 mvp;

  }ubuf;

  layout (location = 0) in vec3 Position;
  layout (location = 1) in vec3 Color;

  layout (location = 0) out vec4 oColor;

  out gl_PerVertex
  {
    vec4 gl_Position;
  };

  void main()
  {
    oColor = vec4(Color, 1.0);

    gl_Position = ubuf.mvp * vec4(Position, 1.0);
  }

)_";

constexpr char FragmentShaderGlsl[] =
R"_(

  #version 430
  #extension GL_ARB_separate_shader_objects : enable

  layout (location = 0) in vec4 oColor;

  layout (location = 0) out vec4 FragColor;

  in vec4 gl_FragCoord;

  void main()
  {
    FragColor = oColor;
    //FragColor = vec4(min(abs(gl_FragCoord.w), 1.0), 0, 0, oColor.a);
  }

)_";

constexpr char SIX_DOF_VERTEX_SHADER[] =
R"_(

  #define NUM_VIEWS 2
  #define VIEW_ID gl_ViewID_OVR
  #extension GL_OVR_multiview2 : require

  layout (num_views = NUM_VIEWS) in;

  in vec3 vertexPosition;
  in vec4 vertexColor;

  uniform mat4 ModelMatrix;

  uniform SceneMatrices
  {
    uniform mat4 ViewMatrix[NUM_VIEWS];
    uniform mat4 ProjectionMatrix[NUM_VIEWS];

  }sm;

  out vec4 fragmentColor;
  out vec4 cubeWorldPosition;

  void main()
  {
    cubeWorldPosition = ModelMatrix * vec4(vertexPosition, 1.0f);

    gl_Position = sm.ProjectionMatrix[VIEW_ID] * sm.ViewMatrix[VIEW_ID] * cubeWorldPosition;

    fragmentColor = vertexColor;
  }

)_";

constexpr char SIX_DOF_FRAGMENT_SHADER[] =
R"_(

  #define NUM_VIEWS 2
  #define VIEW_ID gl_ViewID_OVR
  #extension GL_OVR_multiview2 : require
  #extension GL_ARB_shading_language_420pack : enable

  in lowp vec4 fragmentColor;
  in lowp vec4 cubeWorldPosition;

  uniform highp mat4 DepthViewMatrix[NUM_VIEWS];
  uniform highp mat4 DepthProjectionMatrix[NUM_VIEWS];

  layout(binding = 0) uniform highp sampler2DArray EnvironmentDepthTexture;

  out lowp vec4 outColor;

  void main()
  {
    // Transform from world space to depth camera space using 6-DOF matrix
    highp vec4 cubeDepthCameraPosition = DepthProjectionMatrix[VIEW_ID] * DepthViewMatrix[VIEW_ID] * cubeWorldPosition;

    // 3D point --> Homogeneous Coordinates --> Normalized Coordinates in [0,1]
    highp vec2 cubeDepthCameraPositionHC = cubeDepthCameraPosition.xy / cubeDepthCameraPosition.w;
    cubeDepthCameraPositionHC = cubeDepthCameraPositionHC * 0.5f + 0.5f;

    // Sample from Environment Depth API texture
    highp vec3 depthViewCoord = vec3(cubeDepthCameraPositionHC, VIEW_ID);
    highp float depthViewEyeZ = texture(EnvironmentDepthTexture, depthViewCoord).r;

    // Get virtual object depth
    highp float cubeDepth = cubeDepthCameraPosition.z / cubeDepthCameraPosition.w;
    cubeDepth = cubeDepth * 0.5f + 0.5f;

    // Test virtual object depth with environment depth.
    // If the virtual object is further away (occluded) output a transparent color so real scene content from PT layer is displayed.
    outColor = fragmentColor;

    if (cubeDepth < depthViewEyeZ)
    {
      outColor.a = 1.0f; // fully opaque
    }
    else
    {
      // invisible
      outColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    }

    gl_FragDepth = cubeDepth;
  }

)_";

extern std::array<VkPipelineShaderStageCreateInfo, 2> gShaderProgramShaderInfo;

//////////

uint32_t VulkanTutorialFindMemoryType(
  VkPhysicalDevice& physicalDevice,
  uint32_t typeFilter,
  VkMemoryPropertyFlags properties
);

void VulkanTutorialCreateImage(
  VkDevice& device,
  VkPhysicalDevice& physicalDevice,
  uint32_t width,
  uint32_t height,
  VkFormat format,
  VkImageTiling tiling,
  VkImageUsageFlags usage,
  VkMemoryPropertyFlags properties,
  VkImage& image,
  VkDeviceMemory& imageMemory
);

VkImageView VulkanTutorialCreateImageView(
  VkDevice& device,
  VkImage image,
  VkFormat format,
  VkImageAspectFlags aspectFlags
);

VkCommandBuffer VulkanTutorialsBeginSingleTimeCommands(VkDevice& device, VkCommandPool& commandPool);

void VulkanTutorialEndSingleTimeCommands(
  VkDevice& device,
  VkQueue& graphicsQueue,
  VkCommandPool& commandPool,
  VkCommandBuffer commandBuffer
);

void VulkanTutorialTransitionImageLayout(
  VkDevice& device,
  VkQueue& graphicsQueue,
  VkCommandPool& commandPool,
  VkImage image,
  VkFormat format/*todo*/,
  VkImageLayout oldLayout,
  VkImageLayout newLayout
);

VkFormat VulkanTutorialFindSupportedFormat(
  VkPhysicalDevice& physicalDevice,
  const std::vector<VkFormat>& candidates,
  VkImageTiling tiling,
  VkFormatFeatureFlags features
);

void VulkanTutorialCreateDepthResources(
  VkDevice& device,
  VkPhysicalDevice& physicalDevice,
  VkExtent2D& swapChainExtent,
  VkImage& depthImage,
  VkDeviceMemory& depthImageMemory,
  VkImageView& depthImageView
);

void VulkanTutorialCreateRenderPass(
  VkDevice& device,
  VkPhysicalDevice& physicalDevice,
  VkFormat& swapChainImageFormat,
  VkRenderPass& renderPass
);

void VulkanTutorialCreateFramebuffers(
  VkDevice& device,
  VkExtent2D& swapChainExtent,
  std::vector<VkImageView>& swapChainImageViews,
  std::vector<VkFramebuffer>& swapChainFramebuffers,
  VkRenderPass& renderPass,
  VkImageView& depthImageView
);

void VulkanTutorialRecordCommandBuffer(
  VkCommandBuffer commandBuffer,
  uint32_t imageIndex,
  VkExtent2D& swapChainExtent,
  std::vector<VkFramebuffer>& swapChainFramebuffers,
  VkRenderPass& renderPass,
  VkPipelineLayout& pipelineLayout,
  VkPipeline& graphicsPipeline,
  VkBuffer& vertexBuffer,
  VkBuffer& indexBuffer,
  std::vector<VkDescriptorSet>& descriptorSets,
  uint32_t& currentFrame
);

void VulkanTutorialCleanupSwapChain(
  VkDevice& device,
  VkSwapchainKHR& swapChain,
  std::vector<VkImageView>& swapChainImageViews,
  std::vector<VkFramebuffer>& swapChainFramebuffers,
  VkImage& depthImage,
  VkDeviceMemory& depthImageMemory,
  VkImageView& depthImageView
);

VulkanTutorialSwapChainSupportDetails VulkanTutorialQuerySwapChainSupport(VkPhysicalDevice physicalDevice, VkSurfaceKHR& surface);

VkSurfaceFormatKHR VulkanTutorialChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

VkPresentModeKHR VulkanTutorialChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

VkExtent2D VulkanTutorialChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

VulkanTutorialQueueFamilyIndices VulkanTutorialFindQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR& surface);

bool VulkanTutorialCheckDeviceExtensionSupport(VkPhysicalDevice physicalDevice);

bool VulkanTutorialIsDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR& surface);

void VulkanTutorialCreateSwapChain(
  VkDevice& device,
  VkPhysicalDevice& physicalDevice,
  VkSurfaceKHR& surface,
  VkSwapchainKHR& swapChain,
  std::vector<VkImage>& swapChainImages,
  VkFormat& swapChainImageFormat,
  VkExtent2D& swapChainExtent
);

void VulkanTutorialCreateImageViews(VkDevice& device, std::vector<VkImage>& swapChainImages, VkFormat& swapChainImageFormat, std::vector<VkImageView>& swapChainImageViews);

void VulkanTutorialRecreateSwapChain(
  VkDevice& device,
  VkPhysicalDevice& physicalDevice,
  VkSurfaceKHR& surface,
  VkSwapchainKHR& swapChain,
  std::vector<VkImage>& swapChainImages,
  VkFormat& swapChainImageFormat,
  VkExtent2D& swapChainExtent,
  std::vector<VkImageView>& swapChainImageViews,
  std::vector<VkFramebuffer>& swapChainFramebuffers,
  VkRenderPass& renderPass,
  VkImage& depthImage,
  VkDeviceMemory& depthImageMemory,
  VkImageView& depthImageView
);

std::string BlahVkResultString(VkResult res);

[ [noreturn] ] inline void ThrowVkResult(VkResult res, const char* originator = nullptr, const char* sourceLocation = nullptr)
{
  ThrowCheck(Fmt("VkResult failure [%s]", BlahVkResultString(res).c_str() ), originator, sourceLocation);
}

inline VkResult CheckVkResult(VkResult res, const char* originator = nullptr, const char* sourceLocation = nullptr)
{
  if( (res) < VK_SUCCESS)
    ThrowVkResult(res, originator, sourceLocation);

  return res;
}

void PipelineLayout_PipelineLayoutCreate(VkDevice device);

void MemoryAllocator_MemoryAllocatorInit(VkPhysicalDevice physicalDevice);

void MemoryAllocator_MemoryAllocatorAllocate(VkMemoryRequirements const& memReqs, VkDeviceMemory* mem, VkFlags flags = MemoryAllocator_m_memoryAllocatorDefaultFlags, void* pNext = nullptr);

void CmdBuffer_CmdBufferSetState(CmdBufferStateEnum newState);

std::string CmdBuffer_CmdBufferStateString(CmdBufferStateEnum s);

bool CmdBuffer_CmdBufferInit(const VulkanDebugObjectNamer& namer, VkDevice device, uint32_t queueFamilyIndex);

bool CmdBuffer_CmdBufferBegin();

bool CmdBuffer_CmdBufferEnd();

bool CmdBuffer_CmdBufferExec(VkQueue queue);

bool CmdBuffer_CmdBufferWait();

bool CmdBuffer_CmdBufferReset();

void VertexBufferBase_VertexBufferBaseInit(const std::vector<VkVertexInputAttributeDescription>& attr);

void VertexBufferBase_VertexBufferBaseAllocateBufferMemory(VkBuffer buf, VkDeviceMemory* mem);

bool VertexBuffer_VertexBufferCreate(uint32_t idxCount, uint32_t vtxCount);

void VertexBuffer_VertexBufferUpdateIndices(const uint16_t* data, uint32_t elements, uint32_t offset);

void VertexBuffer_VertexBufferUpdateVertices(const Geometry::Vertex* data, uint32_t elements, uint32_t offset);

void ShaderProgram_ShaderProgramLoad(uint32_t whichShaderInfo, const std::vector<uint32_t>& code);

void ShaderProgram_ShaderProgramLoadVertexShader(const std::vector<uint32_t>& code);

void ShaderProgram_ShaderProgramLoadFragmentShader(const std::vector<uint32_t>& code);

void ShaderProgram_ShaderProgramInit(VkDevice device);

void SwapchainImageContext_SwapchainImageContext_Constructor(int index, XrStructureType swapchainImageType, VulkanDebugObjectNamer& namer);

void SwapchainImageContext_SwapchainImageContext_RenderTargetCreate(int index, int renderTarget, const VulkanDebugObjectNamer& namer, VkDevice device, VkImage aColorImage, VkImage aDepthImage, VkExtent2D size);

void SwapchainImageContext_SwapchainImageContext_DepthBufferCreate(int index, const VulkanDebugObjectNamer& namer, VkDevice device, VkFormat depthFormat, const XrSwapchainCreateInfo& swapchainCreateInfo);

void SwapchainImageContext_SwapchainImageContext_DepthBufferTransitionImageLayout(int index, VkImageLayout newLayout);

bool SwapchainImageContext_SwapchainImageContext_RenderPassCreate(int index, const VulkanDebugObjectNamer& namer, VkDevice device, VkFormat aColorFmt, VkFormat aDepthFmt);

void SwapchainImageContext_SwapchainImageContext_PipelineDynamic(int index, VkDynamicState state);

void SwapchainImageContext_SwapchainImageContext_PipelineCreate(int index, VkDevice device, VkExtent2D size);

void SwapchainImageContext_SwapchainImageContext_PipelineRelease(int index);

std::vector<XrSwapchainImageBaseHeader*> SwapchainImageContext_SwapchainImageContextCreate(int index, const VulkanDebugObjectNamer& namer, VkDevice device, uint32_t capacity, const XrSwapchainCreateInfo& swapchainCreateInfo);

uint32_t SwapchainImageContext_SwapchainImageContextImageIndex(int index, const XrSwapchainImageBaseHeader* swapchainImageHeader);

void SwapchainImageContext_SwapchainImageContextBindRenderTarget(int index, uint32_t renderTarget, VkRenderPassBeginInfo* renderPassBeginInfo);

void VulkanGraphicsPlugin_VulkanGraphicsPlugin_Destructor();

std::vector<std::string> VulkanGraphicsPlugin_VulkanGraphicsPluginGetInstanceExtensions();

// note: The output must not outlive the input - this modifies the input and returns a collection of views into that modified input!
std::vector<const char*> VulkanGraphicsPlugin_VulkanGraphicsPluginParseExtensionString(char* names);

const char* VulkanGraphicsPlugin_VulkanGraphicsPluginGetValidationLayerName();

// compile a shader to a SPIR-V binary
std::vector<uint32_t> VulkanGraphicsPlugin_VulkanGraphicsPluginCompileGlslShader(const std::string& name, shaderc_shader_kind kind, const std::string& source);

int64_t VulkanGraphicsPlugin_VulkanGraphicsPluginSelectColorSwapchainFormat(const std::vector<int64_t>& runtimeFormats);

const XrBaseInStructure* VulkanGraphicsPlugin_VulkanGraphicsPluginGetGraphicsBinding();

std::vector<XrSwapchainImageBaseHeader*> VulkanGraphicsPlugin_VulkanGraphicsPluginAllocateSwapchainImageStructs(uint32_t capacity, const XrSwapchainCreateInfo& swapchainCreateInfo);

void VulkanGraphicsPlugin_VulkanGraphicsPluginRenderView(const XrCompositionLayerProjectionView& layerView, const XrSwapchainImageBaseHeader* swapchainImage, int64_t /*swapchainFormat*/, const std::vector<Cube>& cubes);

uint32_t VulkanGraphicsPlugin_VulkanGraphicsPluginGetSupportedSwapchainSampleCount(const XrViewConfigurationView&);

VkBool32 VulkanGraphicsPlugin_VulkanGraphicsPluginDebugMessage(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData);

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanGraphicsPlugin_debugMessageThunk(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* /*pUserData*/);

XrStructureType VulkanGraphicsPlugin_VulkanGraphicsPluginGetSwapchainImageType();

XrResult VulkanGraphicsPlugin_VulkanGraphicsPluginCreateVulkanInstanceKHR(XrInstance instance, const XrVulkanInstanceCreateInfoKHR* createInfo, VkInstance* vulkanInstance, VkResult* vulkanResult);

XrResult VulkanGraphicsPlugin_VulkanGraphicsPluginCreateVulkanDeviceKHR(XrInstance instance, const XrVulkanDeviceCreateInfoKHR* createInfo, VkDevice* vulkanDevice, VkResult* vulkanResult);

XrResult VulkanGraphicsPlugin_VulkanGraphicsPluginGetVulkanGraphicsDevice2KHR(XrInstance instance, const XrVulkanGraphicsDeviceGetInfoKHR* getInfo, VkPhysicalDevice* vulkanPhysicalDevice);

XrResult VulkanGraphicsPlugin_VulkanGraphicsPluginGetVulkanGraphicsRequirements2KHR(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkan2KHR* graphicsRequirements);

//////////

VkResult VulkanTutorialCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

void VulkanTutorialDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

bool VulkanTutorialQueueFamilyIndices_isComplete(VulkanTutorialQueueFamilyIndices _this);

std::string VulkanGraphicsPlugin_BlahVkObjectTypeToString(VkObjectType objectType);
