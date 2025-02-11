
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

const std::vector<uint32_t> VulkanTutorialIndices =
{
  0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4
};

const std::vector<VkFormat> VulkanTutorialDepthFormatCandidates =
{
  VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT
};

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

VulkanTutorialSwapChainSupportDetails VulkanTutorialQuerySwapChainSupport(
  VkPhysicalDevice physicalDevice,
  VkSurfaceKHR& surface
);

VkSurfaceFormatKHR VulkanTutorialChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

VkPresentModeKHR VulkanTutorialChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

VkExtent2D VulkanTutorialChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

VulkanTutorialQueueFamilyIndices VulkanTutorialFindQueueFamilies(
  VkPhysicalDevice physicalDevice,
  VkSurfaceKHR& surface
);

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

void VulkanTutorialCreateImageViews(
  VkDevice& device,
  std::vector<VkImage>& swapChainImages,
  VkFormat& swapChainImageFormat,
  std::vector<VkImageView>& swapChainImageViews
);

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

VkResult VulkanTutorialCreateDebugUtilsMessengerEXT(
  VkInstance instance,
  const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
  const VkAllocationCallbacks* pAllocator,
  VkDebugUtilsMessengerEXT* pDebugMessenger
);

void VulkanTutorialDestroyDebugUtilsMessengerEXT(
  VkInstance instance,
  VkDebugUtilsMessengerEXT debugMessenger,
  const VkAllocationCallbacks* pAllocator
);

bool VulkanTutorialQueueFamilyIndices_isComplete(VulkanTutorialQueueFamilyIndices _this);
