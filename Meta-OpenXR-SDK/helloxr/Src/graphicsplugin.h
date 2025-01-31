
// graphicsplugin.h

struct Cube
{
  XrPosef Pose;
  XrVector3f Scale;
};

#ifdef __cplusplus

constexpr VkFlags MemoryAllocator_m_memoryAllocatorDefaultFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

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

  //std::vector<SwapchainImageContext*> m_vulkanGraphicsPluginStdList_SwapchainImageContext;
  std::vector<int> m_vulkanGraphicsPluginStdList_SwapchainImageContext;

  std::map<const XrSwapchainImageBaseHeader*, int> m_vulkanGraphicsPluginStdMap_XrSwapchainImageBaseHeader_SwapchainImageContext;

  VulkanDebugObjectNamer m_vulkanGraphicsPluginVulkanDebugObjectNamer {};

  uint32_t m_vulkanGraphicsPluginQueueFamilyIndex = 0;

  VkQueue m_vulkanGraphicsPluginVkQueue {VK_NULL_HANDLE};

  VkSemaphore m_vulkanGraphicsPluginVkSemaphoreDrawDone {VK_NULL_HANDLE};

  ShaderProgram m_vulkanGraphicsPluginShaderProgram {};

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
