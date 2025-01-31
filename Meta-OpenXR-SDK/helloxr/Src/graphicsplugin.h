
// graphicsplugin.h

struct Cube
{
  XrPosef Pose;
  XrVector3f Scale;
};

#ifdef __cplusplus

constexpr VkFlags MemoryAllocator_m_memoryAllocatorDefaultFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

struct MemoryAllocator
{
  void MemoryAllocatorInit(VkPhysicalDevice physicalDevice, VkDevice device);

  void MemoryAllocatorAllocate(VkMemoryRequirements const& memReqs, VkDeviceMemory* mem, VkFlags flags = MemoryAllocator_m_memoryAllocatorDefaultFlags, const void* pNext = nullptr) const;

private:

  VkPhysicalDeviceMemoryProperties m_memoryAllocatorMemoryProperties {};
};

// CmdBuffer - manage VkCommandBuffer state
struct CmdBuffer
{
  enum class CmdBufferStateEnum
  {
    Undefined,
    Initialized,
    Recording,
    Executable,
    Executing
  };

  CmdBufferStateEnum m_cmdBufferState {CmdBufferStateEnum::Undefined};

  VkCommandPool m_cmdBufferPool {VK_NULL_HANDLE};

  VkCommandBuffer m_cmdBufferBuffer {VK_NULL_HANDLE};

  VkFence m_cmdBufferExecFence {VK_NULL_HANDLE};

  CmdBuffer() = default;

  CmdBuffer(const CmdBuffer& ) = delete;

  CmdBuffer& operator=(const CmdBuffer& ) = delete;

  CmdBuffer(CmdBuffer&& ) = delete;

  CmdBuffer& operator=(CmdBuffer&& ) = delete;

  ~CmdBuffer();

  std::string CmdBufferStateString(CmdBufferStateEnum s);

  bool CmdBufferInit(const VulkanDebugObjectNamer& namer, VkDevice device, uint32_t queueFamilyIndex);

  bool CmdBufferBegin();

  bool CmdBufferEnd();

  bool CmdBufferExec(VkQueue queue);

  bool CmdBufferWait();

  bool CmdBufferReset();

private:

  void CmdBufferSetState(CmdBufferStateEnum newState);
};

// ShaderProgram to hold a pair of vertex & fragment shaders
struct ShaderProgram
{
  std::array<VkPipelineShaderStageCreateInfo, 2> m_shaderProgramShaderInfo { { {VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO}, {VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO} } };

  ShaderProgram() = default;

  ~ShaderProgram();

  ShaderProgram(const ShaderProgram& ) = delete;

  ShaderProgram& operator=(const ShaderProgram& ) = delete;

  ShaderProgram(ShaderProgram&& ) = delete;

  ShaderProgram& operator=(ShaderProgram&& ) = delete;

  void ShaderProgramLoadVertexShader(const std::vector<uint32_t>& code);

  void ShaderProgramLoadFragmentShader(const std::vector<uint32_t>& code);

  void ShaderProgramInit(VkDevice device);

private:

  void ShaderProgramLoad(uint32_t index, const std::vector<uint32_t>& code);
};

// VertexBuffer base class
struct VertexBufferBase
{
  VkBuffer m_vertexBufferBaseIdxBuf {VK_NULL_HANDLE};

  VkDeviceMemory m_vertexBufferBaseIdxMem {VK_NULL_HANDLE};

  VkBuffer m_vertexBufferBaseVtxBuf {VK_NULL_HANDLE};

  VkDeviceMemory m_vertexBufferBaseVtxMem {VK_NULL_HANDLE};

  VkVertexInputBindingDescription m_vertexBufferBaseBindDesc {};

  std::vector<VkVertexInputAttributeDescription> m_vertexBufferBaseAttrDesc {};

  struct
  {
    uint32_t idx;
    uint32_t vtx;

  }m_vertexBufferBaseCount = {0, 0};

  VertexBufferBase() = default;

  ~VertexBufferBase();

  VertexBufferBase(const VertexBufferBase& ) = delete;

  VertexBufferBase& operator=(const VertexBufferBase& ) = delete;

  VertexBufferBase(VertexBufferBase&& ) = delete;

  VertexBufferBase& operator=(VertexBufferBase&& ) = delete;

  void VertexBufferBaseInit(VkDevice device, const MemoryAllocator* memAllocator, const std::vector<VkVertexInputAttributeDescription>& attr);

protected:

  void VertexBufferBaseAllocateBufferMemory(VkBuffer buf, VkDeviceMemory* mem) const;

private:

  const MemoryAllocator* m_vertexBufferBaseMemoryAllocator {nullptr};
};

// VertexBuffer template to wrap the indices and vertices
template <typename T> struct VertexBuffer : public VertexBufferBase
{
  bool VertexBufferCreate(uint32_t idxCount, uint32_t vtxCount);

  void VertexBufferUpdateIndices(const uint16_t* data, uint32_t elements, uint32_t offset = 0);

  void VertexBufferUpdateVertices(const T* data, uint32_t elements, uint32_t offset = 0);
};

struct SwapchainImageContext
{
  SwapchainImageContext(XrStructureType _swapchainImageType);

  // A packed array of XrSwapchainImageVulkan2KHR's for tableXr.EnumerateSwapchainImages
  std::vector<XrSwapchainImageVulkan2KHR> m_swapchainImageContextSwapchainImages;

  //std::vector<RenderTarget> m_swapchainImageContextRenderTarget;
  std::vector<VkImage> m_swapchainImageContextStdVector_renderTargetColorImage;
  std::vector<VkImage> m_swapchainImageContextStdVector_renderTargetDepthImage;
  std::vector<VkImageView> m_swapchainImageContextStdVector_renderTargetColorView;
  std::vector<VkImageView> m_swapchainImageContextStdVector_renderTargetDepthView;
  std::vector<VkFramebuffer> m_swapchainImageContextStdVector_renderTargetFrameBuffer;

  VkExtent2D m_swapchainImageContextSize {};

  VkDeviceMemory m_swapchainImageContext_depthBufferDepthMemory {VK_NULL_HANDLE};
  VkImage m_swapchainImageContext_depthBufferDepthImage {VK_NULL_HANDLE};
  VkImageLayout m_swapchainImageContext_depthBufferVkImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;

  VkFormat m_swapchainImageContext_renderPassColorFmt {};
  VkFormat m_swapchainImageContext_renderPassDepthFmt {};
  VkRenderPass m_swapchainImageContext_renderPassPass {VK_NULL_HANDLE};

  VkPipeline m_swapchainImageContextPipe_pipelinePipe {VK_NULL_HANDLE};
  VkPrimitiveTopology m_swapchainImageContextPipe_pipelineTopology {VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST};
  std::vector<VkDynamicState> m_swapchainImageContextPipe_pipelineDynamicStateEnables;

  XrStructureType m_swapchainImageContextSwapchainImageType;

  SwapchainImageContext() = default;

  SwapchainImageContext(SwapchainImageContext&& other) = delete;

  SwapchainImageContext& operator=(SwapchainImageContext&& other) = delete;

  ~SwapchainImageContext();

  void SwapchainImageContext_RenderTargetCreate(int index, const VulkanDebugObjectNamer& namer, VkDevice device, VkImage aColorImage, VkImage aDepthImage, VkExtent2D size, VkFormat& m_swapchainImageContext_renderPassColorFmt, VkFormat& m_swapchainImageContext_renderPassDepthFmt, VkRenderPass& m_swapchainImageContext_renderPassPass);

  void SwapchainImageContext_DepthBufferCreate(const VulkanDebugObjectNamer& namer, VkDevice device, MemoryAllocator* memAllocator, VkFormat depthFormat, const XrSwapchainCreateInfo& swapchainCreateInfo);
  void SwapchainImageContext_DepthBufferTransitionImageLayout(CmdBuffer* cmdBuffer, VkImageLayout newLayout);

  bool SwapchainImageContext_RenderPassCreate(const VulkanDebugObjectNamer& namer, VkDevice device, VkFormat aColorFmt, VkFormat aDepthFmt);

  void SwapchainImageContext_PipelineDynamic(VkDynamicState state);
  void SwapchainImageContext_PipelineCreate(VkDevice device, VkExtent2D size, VkRenderPass& m_swapchainImageContext_renderPassPass, const ShaderProgram& sp, const VertexBufferBase& vb);
  void SwapchainImageContext_PipelineRelease();

  std::vector<XrSwapchainImageBaseHeader*> SwapchainImageContextCreate(const VulkanDebugObjectNamer& namer, VkDevice device, MemoryAllocator* memAllocator, uint32_t capacity, const XrSwapchainCreateInfo& swapchainCreateInfo, const ShaderProgram& sp, const VertexBuffer<Geometry::Vertex>& vb);

  uint32_t SwapchainImageContextImageIndex(const XrSwapchainImageBaseHeader* swapchainImageHeader);

  void SwapchainImageContextBindRenderTarget(uint32_t index, VkRenderPassBeginInfo* renderPassBeginInfo);

private:

  VulkanDebugObjectNamer m_swapchainImageContextNamer;
};

std::string VulkanGraphicsPlugin_BlahVkObjectTypeToString(VkObjectType objectType);

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanGraphicsPlugin_debugMessageThunk(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

struct VulkanGraphicsPlugin
{
  VulkanGraphicsPlugin(const std::shared_ptr<Options>& options, std::shared_ptr<AndroidPlatformPlugin> /*unused*/);

  ~VulkanGraphicsPlugin();

  std::vector<std::string> VulkanGraphicsPluginGetInstanceExtensions() const;

  // note: The output must not outlive the input - this modifies the input and returns a collection of views into that modified input!
  std::vector<const char*> VulkanGraphicsPluginParseExtensionString(char* names);

  const char* VulkanGraphicsPluginGetValidationLayerName();

  void VulkanGraphicsPluginInitializeDevice(XrInstance instance, XrSystemId systemId);

  // Compile a shader to a SPIR-V binary.
  std::vector<uint32_t> VulkanGraphicsPluginCompileGlslShader(const std::string& name, shaderc_shader_kind kind, const std::string& source);

  void VulkanGraphicsPluginInitializeResources();

  int64_t VulkanGraphicsPluginSelectColorSwapchainFormat(const std::vector<int64_t>& runtimeFormats) const;

  const XrBaseInStructure* VulkanGraphicsPluginGetGraphicsBinding() const;

  std::vector<XrSwapchainImageBaseHeader*> VulkanGraphicsPluginAllocateSwapchainImageStructs(uint32_t capacity, const XrSwapchainCreateInfo& swapchainCreateInfo);

  void VulkanGraphicsPluginRenderView(const XrCompositionLayerProjectionView& layerView, const XrSwapchainImageBaseHeader* swapchainImage, int64_t /*swapchainFormat*/, const std::vector<Cube>& cubes);

  uint32_t VulkanGraphicsPluginGetSupportedSwapchainSampleCount(const XrViewConfigurationView& );

  void VulkanGraphicsPluginUpdateOptions(const std::shared_ptr<Options>& options);

protected:

  XrGraphicsBindingVulkan2KHR m_vulkanGraphicsPluginXrGraphicsBindingVulkan2KHR {XR_TYPE_GRAPHICS_BINDING_VULKAN2_KHR};

  std::vector<SwapchainImageContext*> m_vulkanGraphicsPluginStdList_SwapchainImageContext;

  std::map<const XrSwapchainImageBaseHeader*, int> m_vulkanGraphicsPluginStdMap_XrSwapchainImageBaseHeader_SwapchainImageContext;

  VulkanDebugObjectNamer m_vulkanGraphicsPluginVulkanDebugObjectNamer {};

  uint32_t m_vulkanGraphicsPluginQueueFamilyIndex = 0;

  VkQueue m_vulkanGraphicsPluginVkQueue {VK_NULL_HANDLE};

  VkSemaphore m_vulkanGraphicsPluginVkSemaphoreDrawDone {VK_NULL_HANDLE};

  MemoryAllocator m_vulkanGraphicsPluginMemoryAllocator {};

  ShaderProgram m_vulkanGraphicsPluginShaderProgram {};

  CmdBuffer m_vulkanGraphicsPluginCmdBuffer {};

  VertexBuffer<Geometry::Vertex> m_vulkanGraphicsPluginVertexBuffer_GeometryVertex_DrawBuffer {};

  std::array<float, 4> m_vulkanGraphicsPluginStdArray_float_4_clearColor;

  PFN_vkCreateDebugUtilsMessengerEXT m_vulkanGraphicsPluginVkCreateDebugUtilsMessengerEXT {nullptr};

  VkDebugUtilsMessengerEXT m_vulkanGraphicsPluginVkDebugUtilsMessenger {VK_NULL_HANDLE};

  VkBool32 VulkanGraphicsPluginDebugMessage(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData);

  XrStructureType VulkanGraphicsPluginGetGraphicsBindingType() const;

  XrStructureType VulkanGraphicsPluginGetSwapchainImageType() const;

  XrResult VulkanGraphicsPluginCreateVulkanInstanceKHR(XrInstance instance, const XrVulkanInstanceCreateInfoKHR* createInfo, VkInstance* vulkanInstance, VkResult* vulkanResult);

  XrResult VulkanGraphicsPluginCreateVulkanDeviceKHR(XrInstance instance, const XrVulkanDeviceCreateInfoKHR* createInfo, VkDevice* vulkanDevice, VkResult* vulkanResult);

  XrResult VulkanGraphicsPluginGetVulkanGraphicsDevice2KHR(XrInstance instance, const XrVulkanGraphicsDeviceGetInfoKHR* getInfo, VkPhysicalDevice* vulkanPhysicalDevice);

  XrResult VulkanGraphicsPluginGetVulkanGraphicsRequirements2KHR(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkan2KHR* graphicsRequirements);

  friend std::string VulkanGraphicsPlugin_BlahVkObjectTypeToString(VkObjectType objectType);

  friend VKAPI_ATTR VkBool32 VKAPI_CALL VulkanGraphicsPlugin_debugMessageThunk(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
};

std::shared_ptr<VulkanGraphicsPlugin> VulkanGraphicsPlugin_CreateGraphicsPlugin_Vulkan(const std::shared_ptr<Options>& options, std::shared_ptr<AndroidPlatformPlugin> platformPlugin);

#endif
