
// vulkan_tutorial.h

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

const uint32_t VULKAN_TUTORIAL_WIDTH = 800;
const uint32_t VULKAN_TUTORIAL_HEIGHT = 600;

const int VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT = 1/*2*/;

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

//struct VulkanTutorialUniformBufferObject
//{
//  alignas(16) glm::mat4 blahModel;
//  alignas(16) glm::mat4 view;
//  alignas(16) glm::mat4 proj;
//};
struct VulkanTutorialUniformBufferObject
{
  XrMatrix4x4f blahModel;
  XrMatrix4x4f view;
  XrMatrix4x4f proj;
};

#if 0
struct VulkanTutorialVertex
{
  XrVector3f pos;
  XrVector3f color;
  XrVector2f texCoord;

  static VkVertexInputBindingDescription getBindingDescription();

  static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
};

//struct VulkanTutorialVertex
//{
//  glm::vec3 pos;
//  glm::vec3 color;
//  glm::vec2 texCoord;
//};
#endif

#if 0
const std::vector<GeometryVertex> VulkanTutorialVertices =
{
  {
    {-0.5f, -0.5f, 0.0f},
    {1.0f, 0.0f, 0.0f},
    {1.0f, 0.0f}
  },

  {
    {0.5f, -0.5f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f}
  },

  {
    {0.5f, 0.5f, 0.0f},
    {0.0f, 0.0f, 1.0f},
    {0.0f, 1.0f}
  },

  {
    {-0.5f, 0.5f, 0.0f},
    {1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f}
  },

  {
    {-0.5f, -0.5f, -0.5f},
    {1.0f, 0.0f, 0.0f},
    {1.0f, 0.0f}
  },

  {
    {0.5f, -0.5f, -0.5f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f}
  },

  {
    {0.5f, 0.5f, -0.5f},
    {0.0f, 0.0f, 1.0f},
    {0.0f, 1.0f}
  },

  {
    {-0.5f, 0.5f, -0.5f},
    {1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f}
  }
};
#endif

const std::vector<uint32_t> VulkanTutorialIndices =
{
  0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4
};

const std::vector<VkFormat> VulkanTutorialDepthFormatCandidates =
{
  VK_FORMAT_D32_SFLOAT,
  VK_FORMAT_D32_SFLOAT_S8_UINT,
  VK_FORMAT_D24_UNORM_S8_UINT
};

uint32_t VulkanTutorialFindMemoryType(
  uint32_t typeFilter,
  VkMemoryPropertyFlags properties
);

void VulkanTutorialCreateImage(
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
  VkImage image,
  VkFormat format,
  VkImageAspectFlags aspectFlags
);

VkCommandBuffer VulkanTutorialsBeginSingleTimeCommands(
);

void VulkanTutorialEndSingleTimeCommands(
  VkQueue& graphicsQueue,
  VkCommandPool& commandPool,
  VkCommandBuffer commandBuffer
);

void VulkanTutorialTransitionImageLayout(
  VkQueue& graphicsQueue,
  VkCommandPool& commandPool,
  VkImage image,
  VkFormat format/*todo*/,
  VkImageLayout oldLayout,
  VkImageLayout newLayout
);

VkFormat VulkanTutorialFindSupportedFormat(
  const std::vector<VkFormat>& candidates,
  VkImageTiling tiling,
  VkFormatFeatureFlags features
);

void VulkanTutorialCreateDepthResources(
  VkExtent2D& swapChainExtent,
  VkImage& depthImage,
  VkDeviceMemory& depthImageMemory,
  VkImageView& depthImageView
);

void VulkanTutorialCreateRenderPass(
  VkFormat& swapChainImageFormat,
  VkRenderPass& renderPass
);

void VulkanTutorialCreateFramebuffers(
  VkExtent2D& swapChainExtent,
  std::vector<VkImageView>& swapChainImageViews,
  std::vector<VkFramebuffer>& swapChainFramebuffers,
  VkRenderPass& renderPass,
  VkImageView& depthImageView
);

void VulkanTutorialRecordCommandBuffer(
  VkCommandBuffer& commandBuffer,
  VkCommandPool& commandPool,
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
  VkSwapchainKHR& swapChain,
  std::vector<VkImageView>& swapChainImageViews,
  std::vector<VkFramebuffer>& swapChainFramebuffers,
  VkImage& depthImage,
  VkDeviceMemory& depthImageMemory,
  VkImageView& depthImageView
);

VulkanTutorialSwapChainSupportDetails VulkanTutorialQuerySwapChainSupport(
  VkSurfaceKHR& surface
);

VkSurfaceFormatKHR VulkanTutorialChooseSwapSurfaceFormat(
  const std::vector<VkSurfaceFormatKHR>& availableFormats
);

VkPresentModeKHR VulkanTutorialChooseSwapPresentMode(
  const std::vector<VkPresentModeKHR>& availablePresentModes
);

VkExtent2D VulkanTutorialChooseSwapExtent(
  const VkSurfaceCapabilitiesKHR& capabilities
);

VulkanTutorialQueueFamilyIndices VulkanTutorialFindQueueFamilies(
  VkSurfaceKHR& surface
);

bool VulkanTutorialCheckDeviceExtensionSupport(
);

bool VulkanTutorialIsDeviceSuitable(
  VkSurfaceKHR& surface
);

void VulkanTutorialCreateSwapChain(
  VkSurfaceKHR& surface,
  VkSwapchainKHR& swapChain,
  std::vector<VkImage>& swapChainImages,
  VkFormat& swapChainImageFormat,
  VkExtent2D& swapChainExtent
);

void VulkanTutorialCreateImageViews(
  std::vector<VkImage>& swapChainImages,
  VkFormat& swapChainImageFormat,
  std::vector<VkImageView>& swapChainImageViews
);

void VulkanTutorialRecreateSwapChain(
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

VkResult VulkanTutorialCreateDebugUtilsMessengerEXT(
  const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
  const VkAllocationCallbacks* pAllocator,
  VkDebugUtilsMessengerEXT* pDebugMessenger
);

void VulkanTutorialDestroyDebugUtilsMessengerEXT(
  VkDebugUtilsMessengerEXT debugMessenger,
  const VkAllocationCallbacks* pAllocator
);

bool VulkanTutorialQueueFamilyIndices_isComplete(
  VulkanTutorialQueueFamilyIndices _this
);

void VulkanTutorialCreateCommandBuffers(
  std::vector<VkCommandBuffer>& commandBuffers
);

void VulkanTutorialCreateSyncObjects(
  std::vector<VkSemaphore> imageAvailableSemaphores,
  std::vector<VkSemaphore> renderFinishedSemaphores,
  std::vector<VkFence> inFlightFences
);

void VulkanTutorialCreateUniformBuffers(
  std::vector<VkBuffer>& uniformBuffers,
  std::vector<VkDeviceMemory>& uniformBuffersMemory,
  std::vector<void*>& uniformBuffersMapped
);

void VulkanTutorialCreateDescriptorSets(
  VkImageView& textureImageView,
  VkSampler& textureSampler,
  std::vector<VkBuffer>& uniformBuffers,
  VkDescriptorSetLayout descriptorSetLayout,
  VkDescriptorPool descriptorPool,
  std::vector<VkDescriptorSet>& descriptorSets
);

void VulkanTutorialCreateDescriptorPool(
  VkDescriptorPool& descriptorPool
);

void VulkanTutorialCreateDescriptorSetLayout(
  VkDescriptorSetLayout& descriptorSetLayout
);

void VulkanTutorialCreateTextureSampler(
  VkSampler& textureSampler
);

void VulkanTutorialCreateTextureImageView(
  VkImage& textureImage,
  VkImageView& textureImageView
);

void VulkanTutorialCreateBuffer(
  VkDeviceSize size,
  VkBufferUsageFlags usage,
  VkMemoryPropertyFlags properties,
  VkBuffer& buffer,
  VkDeviceMemory& bufferMemory
);

void VulkanTutorialCopyBufferToImage(
  VkQueue& graphicsQueue,
  VkCommandPool& commandPool,
  VkBuffer& buffer,
  VkImage& image,
  uint32_t width,
  uint32_t height
);

void VulkanTutorialCreateTextureImage(
  const char* fileName,
  VkQueue& graphicsQueue,
  VkCommandPool& commandPool,
  VkImage& textureImage,
  VkDeviceMemory& textureImageMemory
);
