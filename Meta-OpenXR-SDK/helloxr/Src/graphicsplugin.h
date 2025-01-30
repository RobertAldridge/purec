
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

  VkDevice m_memoryAllocatorVkDevice {VK_NULL_HANDLE};

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

  VkDevice m_cmdBufferVkDevice {VK_NULL_HANDLE};

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

  VkDevice m_shaderProgramVkDevice {VK_NULL_HANDLE};

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

  VkDevice m_vertexBufferBaseVkDevice {VK_NULL_HANDLE};

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

// RenderPass wrapper
struct RenderPass
{
  VkFormat m_renderPassColorFmt {};

  VkFormat m_renderPassDepthFmt {};

  VkRenderPass m_renderPassPass {VK_NULL_HANDLE};

  RenderPass() = default;

  bool RenderPassCreate(const VulkanDebugObjectNamer& namer, VkDevice device, VkFormat aColorFmt, VkFormat aDepthFmt);

  ~RenderPass();

  RenderPass(const RenderPass&) = delete;

  RenderPass& operator=(const RenderPass&) = delete;

  RenderPass(RenderPass&&) = delete;

  RenderPass& operator=(RenderPass&&) = delete;

private:

  VkDevice m_renderPassVkDevice {VK_NULL_HANDLE};
};

// VkImage + framebuffer wrapper
struct RenderTarget
{
  VkImage m_renderTargetColorImage {VK_NULL_HANDLE};

  VkImage m_renderTargetDepthImage {VK_NULL_HANDLE};

  VkImageView m_renderTargetColorView {VK_NULL_HANDLE};

  VkImageView m_renderTargetDepthView {VK_NULL_HANDLE};

  VkFramebuffer m_renderTargetFrameBuffer {VK_NULL_HANDLE};

  RenderTarget() = default;

  ~RenderTarget();

  RenderTarget(RenderTarget&& other);

  RenderTarget& operator=(RenderTarget&& other);

  void RenderTargetCreate(const VulkanDebugObjectNamer& namer, VkDevice device, VkImage aColorImage, VkImage aDepthImage, VkExtent2D size, RenderPass& renderPass);

  RenderTarget(const RenderTarget&) = delete;

  RenderTarget& operator=(const RenderTarget&) = delete;

private:

  VkDevice m_renderTargetVkDevice {VK_NULL_HANDLE};
};

// Simple vertex MVP xform & color fragment shader layout
struct PipelineLayout
{
  VkPipelineLayout m_pipelineLayoutLayout {VK_NULL_HANDLE};

  PipelineLayout() = default;

  ~PipelineLayout();

  void PipelineLayoutCreate(VkDevice device);

  PipelineLayout(const PipelineLayout& ) = delete;

  PipelineLayout& operator=(const PipelineLayout& ) = delete;

  PipelineLayout(PipelineLayout&& ) = delete;

  PipelineLayout& operator=(PipelineLayout&& ) = delete;

private:

  VkDevice m_pipelineLayoutVkDevice {VK_NULL_HANDLE};
};

// Pipeline wrapper for rendering pipeline state
struct Pipeline
{
  VkPipeline m_pipelinePipe {VK_NULL_HANDLE};

  VkPrimitiveTopology m_pipelineTopology {VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST};

  std::vector<VkDynamicState> m_pipelineDynamicStateEnables;

  Pipeline() = default;

  void PipelineDynamic(VkDynamicState state);

  void PipelineCreate(VkDevice device, VkExtent2D size, const PipelineLayout& layout, const RenderPass& rp, const ShaderProgram& sp, const VertexBufferBase& vb);

  void PipelineRelease();

private:

  VkDevice m_pipelineVkDevice {VK_NULL_HANDLE};
};

struct DepthBuffer
{
  VkDeviceMemory m_depthBufferDepthMemory {VK_NULL_HANDLE};

  VkImage m_depthBufferDepthImage {VK_NULL_HANDLE};

  DepthBuffer() = default;

  ~DepthBuffer();

  DepthBuffer(DepthBuffer&& other);

  DepthBuffer& operator=(DepthBuffer&& other);

  void DepthBufferCreate(const VulkanDebugObjectNamer& namer, VkDevice device, MemoryAllocator* memAllocator, VkFormat depthFormat, const XrSwapchainCreateInfo& swapchainCreateInfo);

  void DepthBufferTransitionImageLayout(CmdBuffer* cmdBuffer, VkImageLayout newLayout);

  DepthBuffer(const DepthBuffer&) = delete;

  DepthBuffer& operator=(const DepthBuffer&) = delete;

private:

  VkDevice m_depthBufferVkDevice {VK_NULL_HANDLE};

  VkImageLayout m_depthBufferVkImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
};

struct SwapchainImageContext
{
  SwapchainImageContext(XrStructureType _swapchainImageType);

  // A packed array of XrSwapchainImageVulkan2KHR's for tableXr.EnumerateSwapchainImages
  std::vector<XrSwapchainImageVulkan2KHR> m_swapchainImageContextSwapchainImages;

  std::vector<RenderTarget> m_swapchainImageContextRenderTarget;

  VkExtent2D m_swapchainImageContextSize {};

  DepthBuffer m_swapchainImageContextDepthBuffer {};

  RenderPass m_swapchainImageContextRenderPass {};

  Pipeline m_swapchainImageContextPipe {};

  XrStructureType m_swapchainImageContextSwapchainImageType;

  SwapchainImageContext() = default;

  std::vector<XrSwapchainImageBaseHeader*> SwapchainImageContextCreate(const VulkanDebugObjectNamer& namer, VkDevice device, MemoryAllocator* memAllocator, uint32_t capacity, const XrSwapchainCreateInfo& swapchainCreateInfo, const PipelineLayout& layout, const ShaderProgram& sp, const VertexBuffer<Geometry::Vertex>& vb);

  uint32_t SwapchainImageContextImageIndex(const XrSwapchainImageBaseHeader* swapchainImageHeader);

  void SwapchainImageContextBindRenderTarget(uint32_t index, VkRenderPassBeginInfo* renderPassBeginInfo);

private:

  VkDevice m_swapchainImageContextVkDevice {VK_NULL_HANDLE};

  VulkanDebugObjectNamer m_swapchainImageContextNamer;
};

std::string VulkanGraphicsPlugin_BlahVkObjectTypeToString(VkObjectType objectType);

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanGraphicsPlugin_debugMessageThunk(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

struct VulkanGraphicsPlugin
{
  VulkanGraphicsPlugin(const std::shared_ptr<Options>& options, std::shared_ptr<AndroidPlatformPlugin> /*unused*/);

  std::vector<std::string> GetInstanceExtensions() const;

  // note: The output must not outlive the input - this modifies the input and returns a collection of views into that modified input!
  std::vector<const char*> ParseExtensionString(char* names);

  const char* GetValidationLayerName();

  void InitializeDevice(XrInstance instance, XrSystemId systemId);

  // Compile a shader to a SPIR-V binary.
  std::vector<uint32_t> CompileGlslShader(const std::string& name, shaderc_shader_kind kind, const std::string& source);

  void InitializeResources();

  int64_t SelectColorSwapchainFormat(const std::vector<int64_t>& runtimeFormats) const;

  const XrBaseInStructure* GetGraphicsBinding() const;

  std::vector<XrSwapchainImageBaseHeader*> AllocateSwapchainImageStructs(uint32_t capacity, const XrSwapchainCreateInfo& swapchainCreateInfo);

  void RenderView(const XrCompositionLayerProjectionView& layerView, const XrSwapchainImageBaseHeader* swapchainImage, int64_t /*swapchainFormat*/, const std::vector<Cube>& cubes);

  uint32_t GetSupportedSwapchainSampleCount(const XrViewConfigurationView& );

  void UpdateOptions(const std::shared_ptr<Options>& options);

protected:

  XrGraphicsBindingVulkan2KHR m_graphicsBinding {XR_TYPE_GRAPHICS_BINDING_VULKAN2_KHR};

  std::list<SwapchainImageContext> m_swapchainImageContexts;

  std::map<const XrSwapchainImageBaseHeader*, SwapchainImageContext*> m_swapchainImageContextMap;

  VkInstance m_vkInstance {VK_NULL_HANDLE};

  VkPhysicalDevice m_vkPhysicalDevice {VK_NULL_HANDLE};

  VkDevice m_vkDevice {VK_NULL_HANDLE};

  VulkanDebugObjectNamer m_namer {};

  uint32_t m_queueFamilyIndex = 0;

  VkQueue m_vkQueue {VK_NULL_HANDLE};

  VkSemaphore m_vkDrawDone {VK_NULL_HANDLE};

  MemoryAllocator m_memAllocator {};

  ShaderProgram m_shaderProgram {};

  CmdBuffer m_cmdBuffer {};

  PipelineLayout m_pipelineLayout {};

  VertexBuffer<Geometry::Vertex> m_drawBuffer {};

  std::array<float, 4> m_clearColor;

  PFN_vkCreateDebugUtilsMessengerEXT BlahVkCreateDebugUtilsMessengerEXT {nullptr};

  VkDebugUtilsMessengerEXT m_vkDebugUtilsMessenger {VK_NULL_HANDLE};

  friend std::string VulkanGraphicsPlugin_BlahVkObjectTypeToString(VkObjectType objectType);

  VkBool32 debugMessage(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData);

  friend VKAPI_ATTR VkBool32 VKAPI_CALL VulkanGraphicsPlugin_debugMessageThunk(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

  XrStructureType GetGraphicsBindingType() const;

  XrStructureType GetSwapchainImageType() const;

  XrResult CreateVulkanInstanceKHR(XrInstance instance, const XrVulkanInstanceCreateInfoKHR* createInfo, VkInstance* vulkanInstance, VkResult* vulkanResult);

  XrResult CreateVulkanDeviceKHR(XrInstance instance, const XrVulkanDeviceCreateInfoKHR* createInfo, VkDevice* vulkanDevice, VkResult* vulkanResult);

  XrResult GetVulkanGraphicsDevice2KHR(XrInstance instance, const XrVulkanGraphicsDeviceGetInfoKHR* getInfo, VkPhysicalDevice* vulkanPhysicalDevice);

  XrResult GetVulkanGraphicsRequirements2KHR(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkan2KHR* graphicsRequirements);
};

std::shared_ptr<VulkanGraphicsPlugin> CreateGraphicsPlugin_Vulkan(const std::shared_ptr<Options>& options, std::shared_ptr<AndroidPlatformPlugin> platformPlugin);

#endif
