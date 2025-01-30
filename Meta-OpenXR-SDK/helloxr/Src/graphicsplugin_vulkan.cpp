
// graphicsplugin_vulkan.cpp

#include "header.h"

namespace
{

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

VkResult VulkanTutorialCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
  auto func = (PFN_vkCreateDebugUtilsMessengerEXT)tableVk.GetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

  if(func)
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  else
    return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void VulkanTutorialDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
{
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)tableVk.GetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
  if(func)
    func(instance, debugMessenger, pAllocator);
}

struct VulkanTutorialQueueFamilyIndices
{
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;

  bool isComplete()
  {
    return graphicsFamily.has_value() && presentFamily.has_value();
  }
};

struct VulkanTutorialSwapChainSupportDetails
{
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

#if 0
struct VulkanTutorialVertex
{

glm::vec3 pos;
glm::vec3 color;
glm::vec2 texCoord;

static VkVertexInputBindingDescription getBindingDescription()
{
  VkVertexInputBindingDescription bindingDescription {};
  bindingDescription.binding = 0;
  bindingDescription.stride = sizeof(Vertex);
  bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

  return bindingDescription;
}

static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions()
{
  std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions {};

  attributeDescriptions[0].binding = 0;
  attributeDescriptions[0].location = 0;
  attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
  attributeDescriptions[0].offset = offsetof(Vertex, pos);

  attributeDescriptions[1].binding = 0;
  attributeDescriptions[1].location = 1;
  attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
  attributeDescriptions[1].offset = offsetof(Vertex, color);

  attributeDescriptions[2].binding = 0;
  attributeDescriptions[2].location = 2;
  attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
  attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

  return attributeDescriptions;
}

};

struct VulkanTutorialUniformBufferObject
{
  alignas(16) glm::mat4 model;
  alignas(16) glm::mat4 view;
  alignas(16) glm::mat4 proj;
};

const std::vector<Vertex> VulkanTutorialVertices =
{
  { {-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} },
  { {0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} },
  { {0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f} },
  { {-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} },

  { {-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} },
  { {0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} },
  { {0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f} },
  { {-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} }
};
#endif

const std::vector<uint16_t> VulkanTutorialIndices = {0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4};

uint32_t VulkanTutorialFindMemoryType(
  VkPhysicalDevice& physicalDevice,
  uint32_t typeFilter,
  VkMemoryPropertyFlags properties
)
{
  VkPhysicalDeviceMemoryProperties memProperties;
  tableVk.GetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

  for(uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
  {
    if( (typeFilter & (1 << i) ) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
      return i;
  }

  throw std::runtime_error("failed to find suitable memory type!");
}

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
)
{
  VkImageCreateInfo imageInfo {};

  imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  imageInfo.imageType = VK_IMAGE_TYPE_2D;
  imageInfo.extent.width = width;
  imageInfo.extent.height = height;
  imageInfo.extent.depth = 1;
  imageInfo.mipLevels = 1;
  imageInfo.arrayLayers = 1;
  imageInfo.format = format;
  imageInfo.tiling = tiling;
  imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  imageInfo.usage = usage;
  imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
  imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  if(tableVk.CreateImage(device, &imageInfo, nullptr, &image) != VK_SUCCESS)
    throw std::runtime_error("failed to create image!");

  VkMemoryRequirements memRequirements;
  tableVk.GetImageMemoryRequirements(device, image, &memRequirements);

  VkMemoryAllocateInfo allocInfo {};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = VulkanTutorialFindMemoryType(physicalDevice, memRequirements.memoryTypeBits, properties);

  if(tableVk.AllocateMemory(device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS)
    throw std::runtime_error("failed to allocate image memory!");

  tableVk.BindImageMemory(device, image, imageMemory, 0);
}

VkImageView VulkanTutorialCreateImageView(
  VkDevice& device,
  VkImage image,
  VkFormat format,
  VkImageAspectFlags aspectFlags
)
{
  VkImageViewCreateInfo viewInfo {};
  viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  viewInfo.image = image;
  viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
  viewInfo.format = format;
  viewInfo.subresourceRange.aspectMask = aspectFlags;
  viewInfo.subresourceRange.baseMipLevel = 0;
  viewInfo.subresourceRange.levelCount = 1;
  viewInfo.subresourceRange.baseArrayLayer = 0;
  viewInfo.subresourceRange.layerCount = 1;

  VkImageView imageView;
  if(tableVk.CreateImageView(device, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
    throw std::runtime_error("failed to create image view!");

  return imageView;
}

VkCommandBuffer VulkanTutorialsBeginSingleTimeCommands(VkDevice& device, VkCommandPool& commandPool)
{
  VkCommandBufferAllocateInfo allocInfo {};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandPool = commandPool;
  allocInfo.commandBufferCount = 1;

  VkCommandBuffer commandBuffer;
  tableVk.AllocateCommandBuffers(device, &allocInfo, &commandBuffer);

  VkCommandBufferBeginInfo beginInfo {};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

  tableVk.BeginCommandBuffer(commandBuffer, &beginInfo);

  return commandBuffer;
}

void VulkanTutorialEndSingleTimeCommands(
  VkDevice& device,
  VkQueue& graphicsQueue,
  VkCommandPool& commandPool,
  VkCommandBuffer commandBuffer
)
{
  tableVk.EndCommandBuffer(commandBuffer);

  VkSubmitInfo submitInfo {};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &commandBuffer;

  tableVk.QueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
  tableVk.QueueWaitIdle(graphicsQueue);

  tableVk.FreeCommandBuffers(device, commandPool, 1, &commandBuffer);
}

void VulkanTutorialTransitionImageLayout(
  VkDevice& device,
  VkQueue& graphicsQueue,
  VkCommandPool& commandPool,
  VkImage image,
  VkFormat format/*todo*/,
  VkImageLayout oldLayout,
  VkImageLayout newLayout
)
{
  VkCommandBuffer commandBuffer = VulkanTutorialsBeginSingleTimeCommands(device, commandPool);

  VkImageMemoryBarrier barrier {};
  barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  barrier.oldLayout = oldLayout;
  barrier.newLayout = newLayout;
  barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.image = image;
  barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  barrier.subresourceRange.baseMipLevel = 0;
  barrier.subresourceRange.levelCount = 1;
  barrier.subresourceRange.baseArrayLayer = 0;
  barrier.subresourceRange.layerCount = 1;

  VkPipelineStageFlags sourceStage;
  VkPipelineStageFlags destinationStage;

  if(oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
  {
    barrier.srcAccessMask = 0;
    barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

    sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
  }
  else if(oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
  {
    barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
  }
  else
  {
    throw std::invalid_argument("unsupported layout transition!");
  }

  tableVk.CmdPipelineBarrier(commandBuffer, sourceStage, destinationStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);

  VulkanTutorialEndSingleTimeCommands(device, graphicsQueue, commandPool, commandBuffer);
}

VkFormat VulkanTutorialFindSupportedFormat(
  VkPhysicalDevice& physicalDevice,
  const std::vector<VkFormat>& candidates,
  VkImageTiling tiling,
  VkFormatFeatureFlags features
)
{
  for(VkFormat format : candidates)
  {
    VkFormatProperties props;
    tableVk.GetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

    if(tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
      return format;
    else if(tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
      return format;
  }

  throw std::runtime_error("failed to find supported format!");
}

VkFormat VulkanTutorialFindDepthFormat(VkPhysicalDevice& physicalDevice)
{
  std::vector<VkFormat> candidates = {
    VK_FORMAT_D32_SFLOAT,
    VK_FORMAT_D32_SFLOAT_S8_UINT,
    VK_FORMAT_D24_UNORM_S8_UINT
  };

  return VulkanTutorialFindSupportedFormat(physicalDevice, candidates, VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
}

void VulkanTutorialCreateDepthResources(
  VkDevice& device,
  VkPhysicalDevice& physicalDevice,
  VkExtent2D& swapChainExtent,
  VkImage& depthImage,
  VkDeviceMemory& depthImageMemory,
  VkImageView& depthImageView
)
{
  VkFormat depthFormat = VulkanTutorialFindDepthFormat(physicalDevice);

  VulkanTutorialCreateImage(
    device,
    physicalDevice,
    swapChainExtent.width,
    swapChainExtent.height,
    depthFormat,
    VK_IMAGE_TILING_OPTIMAL,
    VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
    depthImage,
    depthImageMemory
  );

  depthImageView = VulkanTutorialCreateImageView(device, depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
}

void VulkanTutorialCreateRenderPass(
  VkDevice& device,
  VkPhysicalDevice& physicalDevice,
  VkFormat& swapChainImageFormat,
  VkRenderPass& renderPass
)
{
  VkAttachmentDescription colorAttachment {};
  colorAttachment.format = swapChainImageFormat;
  colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
  colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  VkAttachmentDescription depthAttachment {};
  depthAttachment.format = VulkanTutorialFindDepthFormat(physicalDevice);
  depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
  depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  VkAttachmentReference colorAttachmentRef {};
  colorAttachmentRef.attachment = 0;
  colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  VkAttachmentReference depthAttachmentRef {};
  depthAttachmentRef.attachment = 1;
  depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  VkSubpassDescription subpass {};
  subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass.colorAttachmentCount = 1;
  subpass.pColorAttachments = &colorAttachmentRef;
  subpass.pDepthStencilAttachment = &depthAttachmentRef;

  VkSubpassDependency dependency {};
  dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
  dependency.dstSubpass = 0;
  dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
  dependency.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
  dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
  dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

  std::array<VkAttachmentDescription, 2> attachments = {colorAttachment, depthAttachment};

  VkRenderPassCreateInfo renderPassInfo {};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size() );
  renderPassInfo.pAttachments = attachments.data();
  renderPassInfo.subpassCount = 1;
  renderPassInfo.pSubpasses = &subpass;
  renderPassInfo.dependencyCount = 1;
  renderPassInfo.pDependencies = &dependency;

  if(tableVk.CreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS)
    throw std::runtime_error("failed to create render pass!");
}

void VulkanTutorialCreateFramebuffers(
  VkDevice& device,
  VkExtent2D& swapChainExtent,
  std::vector<VkImageView>& swapChainImageViews,
  std::vector<VkFramebuffer>& swapChainFramebuffers,
  VkRenderPass& renderPass,
  VkImageView& depthImageView
)
{
  swapChainFramebuffers.resize(swapChainImageViews.size() );

  for(size_t i = 0; i < swapChainImageViews.size(); i++)
  {
    std::array<VkImageView, 2> attachments = {swapChainImageViews[i], depthImageView};

    VkFramebufferCreateInfo framebufferInfo {};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = renderPass;
    framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size() );
    framebufferInfo.pAttachments = attachments.data();
    framebufferInfo.width = swapChainExtent.width;
    framebufferInfo.height = swapChainExtent.height;
    framebufferInfo.layers = 1;

    if(tableVk.CreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i] ) != VK_SUCCESS)
      throw std::runtime_error("failed to create framebuffer!");
  }
}

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
)
{
  VkCommandBufferBeginInfo beginInfo {};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

  if(tableVk.BeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS)
    throw std::runtime_error("failed to begin recording command buffer!");

  VkRenderPassBeginInfo renderPassInfo {};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderPassInfo.renderPass = renderPass;
  renderPassInfo.framebuffer = swapChainFramebuffers[imageIndex];
  renderPassInfo.renderArea.offset = {0, 0};
  renderPassInfo.renderArea.extent = swapChainExtent;

  std::array<VkClearValue, 2> clearValues {};
  clearValues[0].color = { {0.0f, 0.0f, 0.0f, 1.0f} };
  clearValues[1].depthStencil = {1.0f, 0};

  renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size() );
  renderPassInfo.pClearValues = clearValues.data();

  tableVk.CmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

  tableVk.CmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

  VkViewport viewport {};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = (float)swapChainExtent.width;
  viewport.height = (float)swapChainExtent.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;
  tableVk.CmdSetViewport(commandBuffer, 0, 1, &viewport);

  VkRect2D scissor {};
  scissor.offset = {0, 0};
  scissor.extent = swapChainExtent;
  tableVk.CmdSetScissor(commandBuffer, 0, 1, &scissor);

  VkBuffer vertexBuffers[] = {vertexBuffer};
  VkDeviceSize offsets[] = {0};
  tableVk.CmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

  tableVk.CmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT16);

  tableVk.CmdBindDescriptorSets(
    commandBuffer,
    VK_PIPELINE_BIND_POINT_GRAPHICS,
    pipelineLayout,
    0,
    1,
    &descriptorSets[currentFrame],
    0,
    nullptr
  );

  tableVk.CmdDrawIndexed(commandBuffer, static_cast<uint32_t>(VulkanTutorialIndices.size() ), 1, 0, 0, 0);

  tableVk.CmdEndRenderPass(commandBuffer);

  if(tableVk.EndCommandBuffer(commandBuffer) != VK_SUCCESS)
    throw std::runtime_error("failed to record command buffer!");
}

void VulkanTutorialCleanupSwapChain(
  VkDevice& device,
  VkSwapchainKHR& swapChain,
  std::vector<VkImageView>& swapChainImageViews,
  std::vector<VkFramebuffer>& swapChainFramebuffers,
  VkImage& depthImage,
  VkDeviceMemory& depthImageMemory,
  VkImageView& depthImageView
)
{
  tableVk.DestroyImageView(device, depthImageView, nullptr);
  tableVk.DestroyImage(device, depthImage, nullptr);
  tableVk.FreeMemory(device, depthImageMemory, nullptr);

  for(auto framebuffer : swapChainFramebuffers)
    tableVk.DestroyFramebuffer(device, framebuffer, nullptr);

  for(auto imageView : swapChainImageViews)
    tableVk.DestroyImageView(device, imageView, nullptr);

  tableVk.DestroySwapchainKHR(device, swapChain, nullptr);
}

VulkanTutorialSwapChainSupportDetails VulkanTutorialQuerySwapChainSupport(VkPhysicalDevice physicalDevice, VkSurfaceKHR& surface)
{
  VulkanTutorialSwapChainSupportDetails details;

  tableVk.GetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &details.capabilities);

  uint32_t formatCount = 0;
  tableVk.GetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr);

  if(formatCount)
  {
    details.formats.resize(formatCount);
    tableVk.GetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, details.formats.data() );
  }

  uint32_t presentModeCount = 0;
  tableVk.GetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);

  if(presentModeCount)
  {
    details.presentModes.resize(presentModeCount);
    tableVk.GetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, details.presentModes.data() );
  }

  return details;
}

VkSurfaceFormatKHR VulkanTutorialChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
  for(const auto& availableFormat : availableFormats)
  {
    if(availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
      availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR
    )
      return availableFormat;
  }

  return availableFormats[0];
}

VkPresentModeKHR VulkanTutorialChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
  for(const auto& availablePresentMode : availablePresentModes)
  {
    if(availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
      return availablePresentMode;
  }

  return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanTutorialChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
{
  if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max() )
    return capabilities.currentExtent;

  int width = 0;
  int height = 0;

  // todo
  //glfwGetFramebufferSize(window, &width, &height);

  VkExtent2D actualExtent = {static_cast<uint32_t>(width), static_cast<uint32_t>(height) };

  actualExtent.width = std::clamp(
    actualExtent.width,
    capabilities.minImageExtent.width,
    capabilities.maxImageExtent.width
  );

  actualExtent.height = std::clamp(
    actualExtent.height,
    capabilities.minImageExtent.height,
    capabilities.maxImageExtent.height
  );

  return actualExtent;
}

VulkanTutorialQueueFamilyIndices VulkanTutorialFindQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR& surface)
{
  VulkanTutorialQueueFamilyIndices indices;

  uint32_t queueFamilyCount = 0;
  tableVk.GetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

  std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
  tableVk.GetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data() );

  int i = 0;
  for(const auto& queueFamily : queueFamilies)
  {
    if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
      indices.graphicsFamily = i;

    VkBool32 presentSupport = false;
    tableVk.GetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);

    if(presentSupport)
      indices.presentFamily = i;

    if(indices.isComplete() )
      break;

    i++;
  }

  return indices;
}

bool VulkanTutorialCheckDeviceExtensionSupport(VkPhysicalDevice physicalDevice)
{
  uint32_t extensionCount = 0;
  tableVk.EnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

  std::vector<VkExtensionProperties> availableExtensions(extensionCount);
  tableVk.EnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data() );

  std::set<std::string> requiredExtensions(VulkanTutorialDeviceExtensions.begin(), VulkanTutorialDeviceExtensions.end() );

  for(const auto& extension : availableExtensions)
    requiredExtensions.erase(extension.extensionName);

  return requiredExtensions.empty();
}

bool VulkanTutorialIsDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR& surface)
{
  VulkanTutorialQueueFamilyIndices indices = VulkanTutorialFindQueueFamilies(physicalDevice, surface);

  bool extensionsSupported = VulkanTutorialCheckDeviceExtensionSupport(physicalDevice);

  bool swapChainAdequate = false;
  if(extensionsSupported)
  {
    VulkanTutorialSwapChainSupportDetails swapChainSupport = VulkanTutorialQuerySwapChainSupport(physicalDevice, surface);
    swapChainAdequate = ( !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty() );
  }

  VkPhysicalDeviceFeatures supportedFeatures;
  tableVk.GetPhysicalDeviceFeatures(physicalDevice, &supportedFeatures);

  return indices.isComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
}

void VulkanTutorialCreateSwapChain(
  VkDevice& device,
  VkPhysicalDevice& physicalDevice,
  VkSurfaceKHR& surface,
  VkSwapchainKHR& swapChain,
  std::vector<VkImage>& swapChainImages,
  VkFormat& swapChainImageFormat,
  VkExtent2D& swapChainExtent
)
{
  VulkanTutorialSwapChainSupportDetails swapChainSupport = VulkanTutorialQuerySwapChainSupport(physicalDevice, surface);

  VkSurfaceFormatKHR surfaceFormat = VulkanTutorialChooseSwapSurfaceFormat(swapChainSupport.formats);
  VkPresentModeKHR presentMode = VulkanTutorialChooseSwapPresentMode(swapChainSupport.presentModes);
  VkExtent2D extent = VulkanTutorialChooseSwapExtent(swapChainSupport.capabilities);

  uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

  if(swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
    imageCount = swapChainSupport.capabilities.maxImageCount;

  VkSwapchainCreateInfoKHR createInfo {};
  createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  createInfo.surface = surface;

  createInfo.minImageCount = imageCount;
  createInfo.imageFormat = surfaceFormat.format;
  createInfo.imageColorSpace = surfaceFormat.colorSpace;
  createInfo.imageExtent = extent;
  createInfo.imageArrayLayers = 1;
  createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

  VulkanTutorialQueueFamilyIndices indices = VulkanTutorialFindQueueFamilies(physicalDevice, surface);
  uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value() };

  if(indices.graphicsFamily != indices.presentFamily)
  {
    createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    createInfo.queueFamilyIndexCount = 2;
    createInfo.pQueueFamilyIndices = queueFamilyIndices;
  }
  else
  {
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
  }

  createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
  createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  createInfo.presentMode = presentMode;
  createInfo.clipped = VK_TRUE;

  if(tableVk.CreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS)
    throw std::runtime_error("failed to create swap chain!");

  tableVk.GetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
  swapChainImages.resize(imageCount);
  tableVk.GetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

  swapChainImageFormat = surfaceFormat.format;
  swapChainExtent = extent;
}

void VulkanTutorialCreateImageViews(VkDevice& device, std::vector<VkImage>& swapChainImages, VkFormat& swapChainImageFormat, std::vector<VkImageView>& swapChainImageViews)
{
  swapChainImageViews.resize(swapChainImages.size() );

  for(uint32_t i = 0; i < swapChainImages.size(); i++)
    swapChainImageViews[i] = VulkanTutorialCreateImageView(device, swapChainImages[i], swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT);
}

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
)
{
  int width = 0, height = 0;

  // todo
  //glfwGetFramebufferSize(window, &width, &height);

  while( !width || !height)
  {
    // todo
    //glfwGetFramebufferSize(window, &width, &height);
    //glfwWaitEvents();
  }

  tableVk.DeviceWaitIdle(device);

  VulkanTutorialCleanupSwapChain(device, swapChain, swapChainImageViews, swapChainFramebuffers, depthImage, depthImageMemory, depthImageView);

  VulkanTutorialCreateSwapChain(device, physicalDevice, surface, swapChain, swapChainImages, swapChainImageFormat, swapChainExtent);
  VulkanTutorialCreateImageViews(device, swapChainImages, swapChainImageFormat, swapChainImageViews);
  VulkanTutorialCreateDepthResources(device, physicalDevice, swapChainExtent, depthImage, depthImageMemory, depthImageView);
  VulkanTutorialCreateFramebuffers(device, swapChainExtent, swapChainImageViews, swapChainFramebuffers, renderPass, depthImageView);
}

#if 0
std::vector<const char*> VulkanTutorialGetRequiredExtensions()
{
  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions = 0;

  // todo
  //glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

  if(VulkanTutorialEnableValidationLayers)
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

  return extensions;
}

bool VulkanTutorialCheckValidationLayerSupport()
{
  uint32_t layerCount = 0;
  tableVk.EnumerateInstanceLayerProperties( &layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);
  tableVk.EnumerateInstanceLayerProperties( &layerCount, availableLayers.data() );

  for(const char* layerName : VulkanTutorialValidationLayers)
  {
    bool layerFound = false;

    for(const auto& layerProperties : availableLayers)
    {
      if( !strcmp(layerName, layerProperties.layerName) )
      {
        layerFound = true;
        break;
      }
    }

    if( !layerFound)
      return false;
  }

  return true;
}

std::vector<char> VulkanTutorialReadFile(const std::string& filename)
{
  std::ifstream file(filename, std::ios::ate | std::ios::binary);

  if( !file.is_open() )
    throw std::runtime_error("failed to open file!");

  size_t fileSize = (size_t)file.tellg();
  std::vector<char> buffer(fileSize);

  file.seekg(0);
  file.read(buffer.data(), fileSize);

  file.close();

  return buffer;
}

VkBool32 VulkanTutorialDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
  std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
  return VK_FALSE;
}

int VulkanTutorialMain()
{
  // todo
  //HelloTriangleApplication app;

  try
  {
    // todo
    //app.run();
  }
  catch(const std::exception& exception)
  {
    std::cerr << exception.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

VkShaderModule VulkanTutorialCreateShaderModule(const std::vector<char>& code)
{
  VkShaderModuleCreateInfo createInfo {};
  createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  createInfo.codeSize = code.size();
  createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

  VkShaderModule shaderModule;
  if(tableVk.CreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
    throw std::runtime_error("failed to create shader module!");

  return shaderModule;
}

void run()
{
  initWindow();
  initVulkan();
  mainLoop();
  cleanup();
}

void initWindow()
{
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
  glfwSetWindowUserPointer(window, this);
  glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
  auto app = reinterpret_cast<HelloTriangleApplication*>(glfwGetWindowUserPointer(window));
  app->framebufferResized = true;
}

void initVulkan()
{
  createInstance();
  setupDebugMessenger();
  createSurface();
  pickPhysicalDevice();
  createLogicalDevice();
  createSwapChain();
  createImageViews();
  createRenderPass();
  createDescriptorSetLayout();
  createGraphicsPipeline();
  createCommandPool();
  createDepthResources();
  createFramebuffers();
  createTextureImage();
  createTextureImageView();
  createTextureSampler();
  createVertexBuffer();
  createIndexBuffer();
  createUniformBuffers();
  createDescriptorPool();
  createDescriptorSets();
  createCommandBuffers();
  createSyncObjects();
}

void mainLoop()
{
  while( !glfwWindowShouldClose(window) )
  {
    glfwPollEvents();
    drawFrame();
  }

  vkDeviceWaitIdle(device);
}

void cleanup()
{
  cleanupSwapChain();

  vkDestroyPipeline(device, graphicsPipeline, nullptr);
  vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
  vkDestroyRenderPass(device, renderPass, nullptr);

  for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
  {
    vkDestroyBuffer(device, uniformBuffers[i], nullptr);
    vkFreeMemory(device, uniformBuffersMemory[i], nullptr);
  }

  vkDestroyDescriptorPool(device, descriptorPool, nullptr);

  vkDestroySampler(device, textureSampler, nullptr);
  vkDestroyImageView(device, textureImageView, nullptr);

  vkDestroyImage(device, textureImage, nullptr);
  vkFreeMemory(device, textureImageMemory, nullptr);

  vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);

  vkDestroyBuffer(device, indexBuffer, nullptr);
  vkFreeMemory(device, indexBufferMemory, nullptr);

  vkDestroyBuffer(device, vertexBuffer, nullptr);
  vkFreeMemory(device, vertexBufferMemory, nullptr);

  for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
  {
    vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
    vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
    vkDestroyFence(device, inFlightFences[i], nullptr);
  }

  vkDestroyCommandPool(device, commandPool, nullptr);

  vkDestroyDevice(device, nullptr);

  if(enableValidationLayers)
    DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);

  vkDestroySurfaceKHR(instance, surface, nullptr);
  vkDestroyInstance(instance, nullptr);

  glfwDestroyWindow(window);

  glfwTerminate();
}

void createInstance()
{
  if(enableValidationLayers && !checkValidationLayerSupport() )
    throw std::runtime_error("validation layers requested, but not available!");

  VkApplicationInfo appInfo {};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Hello Triangle";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "No Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo createInfo {};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;

  auto extensions = getRequiredExtensions();
  createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size() );
  createInfo.ppEnabledExtensionNames = extensions.data();

  VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo {};
  if(enableValidationLayers)
  {
    createInfo.enabledLayerCount = static_cast<uint32_t>(VulkanTutorialValidationLayers.size() );
    createInfo.ppEnabledLayerNames = VulkanTutorialValidationLayers.data();

    populateDebugMessengerCreateInfo(debugCreateInfo);
    createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
  }
  else
  {
    createInfo.enabledLayerCount = 0;
    createInfo.pNext = nullptr;
  }

  if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
    throw std::runtime_error("failed to create instance!");
}

void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
  createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  createInfo.pfnUserCallback = debugCallback;
}

void setupDebugMessenger()
{
  if( !enableValidationLayers)
    return;

  VkDebugUtilsMessengerCreateInfoEXT createInfo;
  populateDebugMessengerCreateInfo(createInfo);

  if(CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS)
    throw std::runtime_error("failed to set up debug messenger!");
}

void createSurface()
{
  if(glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS)
    throw std::runtime_error("failed to create window surface!");
}

void pickPhysicalDevice()
{
  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

  if( !deviceCount)
    throw std::runtime_error("failed to find GPUs with Vulkan support!");

  std::vector<VkPhysicalDevice> devices(deviceCount);
  vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

  for(const auto& device : devices)
  {
    if(isDeviceSuitable(device) )
    {
      physicalDevice = device;
      break;
    }
  }

  if(physicalDevice == VK_NULL_HANDLE)
    throw std::runtime_error("failed to find a suitable GPU!");
}

void createLogicalDevice()
{
  VulkanTutorialQueueFamilyIndices indices = VulkanTutorialFindQueueFamilies(physicalDevice);

  std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
  std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value() };

  float queuePriority = 1.0f;

  for(uint32_t queueFamily : uniqueQueueFamilies)
  {
    VkDeviceQueueCreateInfo queueCreateInfo {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queueFamily;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;
    queueCreateInfos.push_back(queueCreateInfo);
  }

  VkPhysicalDeviceFeatures deviceFeatures {};
  deviceFeatures.samplerAnisotropy = VK_TRUE;

  VkDeviceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

  createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size() );
  createInfo.pQueueCreateInfos = queueCreateInfos.data();

  createInfo.pEnabledFeatures = &deviceFeatures;

  createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size() );
  createInfo.ppEnabledExtensionNames = deviceExtensions.data();

  if(enableValidationLayers)
  {
    createInfo.enabledLayerCount = static_cast<uint32_t>(VulkanTutorialValidationLayers.size() );
    createInfo.ppEnabledLayerNames = VulkanTutorialValidationLayers.data();
  }
  else
  {
    createInfo.enabledLayerCount = 0;
  }

  if(vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
    throw std::runtime_error("failed to create logical device!");

  vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
  vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
}

void createDescriptorSetLayout()
{
  VkDescriptorSetLayoutBinding uboLayoutBinding{};
  uboLayoutBinding.binding = 0;
  uboLayoutBinding.descriptorCount = 1;
  uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  uboLayoutBinding.pImmutableSamplers = nullptr;
  uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

  VkDescriptorSetLayoutBinding samplerLayoutBinding{};
  samplerLayoutBinding.binding = 1;
  samplerLayoutBinding.descriptorCount = 1;
  samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  samplerLayoutBinding.pImmutableSamplers = nullptr;
  samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

  std::array<VkDescriptorSetLayoutBinding, 2> bindings = {uboLayoutBinding, samplerLayoutBinding};
  VkDescriptorSetLayoutCreateInfo layoutInfo{};
  layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
  layoutInfo.pBindings = bindings.data();

  if(vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
    throw std::runtime_error("failed to create descriptor set layout!");
}

void createGraphicsPipeline()
{
  auto vertShaderCode = readFile("shaders/vert.spv");
  auto fragShaderCode = readFile("shaders/frag.spv");

  VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
  VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

  VkPipelineShaderStageCreateInfo vertShaderStageInfo {};
  vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
  vertShaderStageInfo.module = vertShaderModule;
  vertShaderStageInfo.pName = "main";

  VkPipelineShaderStageCreateInfo fragShaderStageInfo {};
  fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  fragShaderStageInfo.module = fragShaderModule;
  fragShaderStageInfo.pName = "main";

  VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

  VkPipelineVertexInputStateCreateInfo vertexInputInfo {};
  vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

  auto bindingDescription = Vertex::getBindingDescription();
  auto attributeDescriptions = Vertex::getAttributeDescriptions();

  vertexInputInfo.vertexBindingDescriptionCount = 1;
  vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
  vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
  vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

  VkPipelineInputAssemblyStateCreateInfo inputAssembly {};
  inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  inputAssembly.primitiveRestartEnable = VK_FALSE;

  VkPipelineViewportStateCreateInfo viewportState {};
  viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewportState.viewportCount = 1;
  viewportState.scissorCount = 1;

  VkPipelineRasterizationStateCreateInfo rasterizer {};
  rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer.depthClampEnable = VK_FALSE;
  rasterizer.rasterizerDiscardEnable = VK_FALSE;
  rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
  rasterizer.lineWidth = 1.0f;
  rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
  rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
  rasterizer.depthBiasEnable = VK_FALSE;

  VkPipelineMultisampleStateCreateInfo multisampling {};
  multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling.sampleShadingEnable = VK_FALSE;
  multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

  VkPipelineDepthStencilStateCreateInfo depthStencil {};
  depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  depthStencil.depthTestEnable = VK_TRUE;
  depthStencil.depthWriteEnable = VK_TRUE;
  depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
  depthStencil.depthBoundsTestEnable = VK_FALSE;
  depthStencil.stencilTestEnable = VK_FALSE;

  VkPipelineColorBlendAttachmentState colorBlendAttachment {};
  colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  colorBlendAttachment.blendEnable = VK_FALSE;

  VkPipelineColorBlendStateCreateInfo colorBlending {};
  colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  colorBlending.logicOpEnable = VK_FALSE;
  colorBlending.logicOp = VK_LOGIC_OP_COPY;
  colorBlending.attachmentCount = 1;
  colorBlending.pAttachments = &colorBlendAttachment;
  colorBlending.blendConstants[0] = 0.0f;
  colorBlending.blendConstants[1] = 0.0f;
  colorBlending.blendConstants[2] = 0.0f;
  colorBlending.blendConstants[3] = 0.0f;

  std::vector<VkDynamicState> dynamicStates = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};

  VkPipelineDynamicStateCreateInfo dynamicState{};
  dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
  dynamicState.pDynamicStates = dynamicStates.data();

  VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
  pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipelineLayoutInfo.setLayoutCount = 1;
  pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;

  if(vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
    throw std::runtime_error("failed to create pipeline layout!");

  VkGraphicsPipelineCreateInfo pipelineInfo{};
  pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipelineInfo.stageCount = 2;
  pipelineInfo.pStages = shaderStages;
  pipelineInfo.pVertexInputState = &vertexInputInfo;
  pipelineInfo.pInputAssemblyState = &inputAssembly;
  pipelineInfo.pViewportState = &viewportState;
  pipelineInfo.pRasterizationState = &rasterizer;
  pipelineInfo.pMultisampleState = &multisampling;
  pipelineInfo.pDepthStencilState = &depthStencil;
  pipelineInfo.pColorBlendState = &colorBlending;
  pipelineInfo.pDynamicState = &dynamicState;
  pipelineInfo.layout = pipelineLayout;
  pipelineInfo.renderPass = renderPass;
  pipelineInfo.subpass = 0;
  pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

  if(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS)
    throw std::runtime_error("failed to create graphics pipeline!");

  vkDestroyShaderModule(device, fragShaderModule, nullptr);
  vkDestroyShaderModule(device, vertShaderModule, nullptr);
}

void createCommandPool()
{
  VulkanTutorialQueueFamilyIndices queueFamilyIndices = VulkanTutorialFindQueueFamilies(physicalDevice);

  VkCommandPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

  if(vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
    throw std::runtime_error("failed to create graphics command pool!");
}

bool hasStencilComponent(VkFormat format)
{
  return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
}

void createTextureImage()
{
  int texWidth = 0;
  int texHeight = 0;
  int texChannels = 0;
  stbi_uc* pixels = stbi_load("textures/texture.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
  VkDeviceSize imageSize = texWidth * texHeight * 4;

  if( !pixels)
    throw std::runtime_error("failed to load texture image!");

  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;
  createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

  void* data = 0;
  vkMapMemory(device, stagingBufferMemory, 0, imageSize, 0, &data);
  memcpy(data, pixels, static_cast<size_t>(imageSize) );
  vkUnmapMemory(device, stagingBufferMemory);

  stbi_image_free(pixels);

  createImage(texWidth, texHeight, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, textureImage, textureImageMemory);

  transitionImageLayout(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
  copyBufferToImage(stagingBuffer, textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight) );
  transitionImageLayout(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  vkDestroyBuffer(device, stagingBuffer, nullptr);
  vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void createTextureImageView()
{
  textureImageView = createImageView(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
}

void createTextureSampler()
{
  VkPhysicalDeviceProperties properties {};
  vkGetPhysicalDeviceProperties(physicalDevice, &properties);

  VkSamplerCreateInfo samplerInfo {};
  samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  samplerInfo.magFilter = VK_FILTER_LINEAR;
  samplerInfo.minFilter = VK_FILTER_LINEAR;
  samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  samplerInfo.anisotropyEnable = VK_TRUE;
  samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
  samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
  samplerInfo.unnormalizedCoordinates = VK_FALSE;
  samplerInfo.compareEnable = VK_FALSE;
  samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
  samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

  if(vkCreateSampler(device, &samplerInfo, nullptr, &textureSampler) != VK_SUCCESS)
    throw std::runtime_error("failed to create texture sampler!");
}

void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height)
{
  VkCommandBuffer commandBuffer = beginSingleTimeCommands();

  VkBufferImageCopy region {};
  region.bufferOffset = 0;
  region.bufferRowLength = 0;
  region.bufferImageHeight = 0;
  region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  region.imageSubresource.mipLevel = 0;
  region.imageSubresource.baseArrayLayer = 0;
  region.imageSubresource.layerCount = 1;
  region.imageOffset = {0, 0, 0};
  region.imageExtent = {width, height, 1};

  vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

  endSingleTimeCommands(commandBuffer);
}

void createVertexBuffer()
{
  VkDeviceSize bufferSize = sizeof(vertices[0] ) * vertices.size();

  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;
  createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

  void* data = 0;
  vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
  memcpy(data, vertices.data(), (size_t)bufferSize);
  vkUnmapMemory(device, stagingBufferMemory);

  createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

  copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

  vkDestroyBuffer(device, stagingBuffer, nullptr);
  vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void createIndexBuffer()
{
  VkDeviceSize bufferSize = sizeof(VulkanTutorialIndices[0] ) * VulkanTutorialIndices.size();

  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;
  createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

  void* data = 0;
  vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
  memcpy(data, VulkanTutorialIndices.data(), (size_t) bufferSize);
  vkUnmapMemory(device, stagingBufferMemory);

  createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

  copyBuffer(stagingBuffer, indexBuffer, bufferSize);

  vkDestroyBuffer(device, stagingBuffer, nullptr);
  vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void createUniformBuffers()
{
  VkDeviceSize bufferSize = sizeof(UniformBufferObject);

  uniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
  uniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
  uniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

  for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
  {
    createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i] );

    vkMapMemory(device, uniformBuffersMemory[i], 0, bufferSize, 0, &uniformBuffersMapped[i] );
  }
}

void createDescriptorPool()
{
  std::array<VkDescriptorPoolSize, 2> poolSizes {};
  poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  poolSizes[0].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
  poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  poolSizes[1].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

  VkDescriptorPoolCreateInfo poolInfo {};
  poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
  poolInfo.pPoolSizes = poolSizes.data();
  poolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

  if(vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS)
    throw std::runtime_error("failed to create descriptor pool!");
}

void createDescriptorSets()
{
  std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, descriptorSetLayout);
  VkDescriptorSetAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = descriptorPool;
  allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
  allocInfo.pSetLayouts = layouts.data();

  descriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
  if(vkAllocateDescriptorSets(device, &allocInfo, descriptorSets.data()) != VK_SUCCESS)
    throw std::runtime_error("failed to allocate descriptor sets!");

  for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
  {
    VkDescriptorBufferInfo bufferInfo {};
    bufferInfo.buffer = uniformBuffers[i];
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(UniformBufferObject);

    VkDescriptorImageInfo imageInfo {};
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfo.imageView = textureImageView;
    imageInfo.sampler = textureSampler;

    std::array<VkWriteDescriptorSet, 2> descriptorWrites {};

    descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrites[0].dstSet = descriptorSets[i];
    descriptorWrites[0].dstBinding = 0;
    descriptorWrites[0].dstArrayElement = 0;
    descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorWrites[0].descriptorCount = 1;
    descriptorWrites[0].pBufferInfo = &bufferInfo;

    descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrites[1].dstSet = descriptorSets[i];
    descriptorWrites[1].dstBinding = 1;
    descriptorWrites[1].dstArrayElement = 0;
    descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorWrites[1].descriptorCount = 1;
    descriptorWrites[1].pImageInfo = &imageInfo;

    vkUpdateDescriptorSets(device, static_cast<uint32_t>(descriptorWrites.size() ), descriptorWrites.data(), 0, nullptr);
  }
}

void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
{
  VkBufferCreateInfo bufferInfo {};
  bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  bufferInfo.size = size;
  bufferInfo.usage = usage;
  bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  if(vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
    throw std::runtime_error("failed to create buffer!");

  VkMemoryRequirements memRequirements;
  vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

  if(vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS)
    throw std::runtime_error("failed to allocate buffer memory!");

  vkBindBufferMemory(device, buffer, bufferMemory, 0);
}

void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
{
  VkCommandBuffer commandBuffer = beginSingleTimeCommands();

  VkBufferCopy copyRegion {};
  copyRegion.size = size;
  vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

  endSingleTimeCommands(commandBuffer);
}

void createCommandBuffers()
{
  commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.commandPool = commandPool;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

  if(vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data() ) != VK_SUCCESS)
    throw std::runtime_error("failed to allocate command buffers!");
}

void createSyncObjects()
{
  imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
  renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
  inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

  VkSemaphoreCreateInfo semaphoreInfo {};
  semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  VkFenceCreateInfo fenceInfo {};
  fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
  {
    if(vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i] ) != VK_SUCCESS ||
    vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i] ) != VK_SUCCESS ||
    vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i] ) != VK_SUCCESS
    )
      throw std::runtime_error("failed to create synchronization objects for a frame!");
  }
}

void updateUniformBuffer(uint32_t currentImage)
{
  static auto startTime = std::chrono::high_resolution_clock::now();

  auto currentTime = std::chrono::high_resolution_clock::now();
  float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

  UniformBufferObject ubo {};
  ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float) swapChainExtent.height, 0.1f, 10.0f);
  ubo.proj[1][1] *= -1;

  memcpy(uniformBuffersMapped[currentImage], &ubo, sizeof(ubo) );
}

void drawFrame()
{
  vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

  uint32_t imageIndex;
  VkResult result = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

  if(result == VK_ERROR_OUT_OF_DATE_KHR)
  {
    recreateSwapChain();
    return;
  }
  else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
  {
    throw std::runtime_error("failed to acquire swap chain image!");
  }

  updateUniformBuffer(currentFrame);

  vkResetFences(device, 1, &inFlightFences[currentFrame]);

  vkResetCommandBuffer(commandBuffers[currentFrame], /*VkCommandBufferResetFlagBits*/ 0);
  recordCommandBuffer(commandBuffers[currentFrame], imageIndex);

  VkSubmitInfo submitInfo {};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

  VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
  VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = waitSemaphores;
  submitInfo.pWaitDstStageMask = waitStages;

  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &commandBuffers[currentFrame];

  VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = signalSemaphores;

  if(vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS)
    throw std::runtime_error("failed to submit draw command buffer!");

  VkPresentInfoKHR presentInfo{};
  presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

  presentInfo.waitSemaphoreCount = 1;
  presentInfo.pWaitSemaphores = signalSemaphores;

  VkSwapchainKHR swapChains[] = {swapChain};
  presentInfo.swapchainCount = 1;
  presentInfo.pSwapchains = swapChains;

  presentInfo.pImageIndices = &imageIndex;

  result = vkQueuePresentKHR(presentQueue, &presentInfo);

  if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized)
  {
    framebufferResized = false;
    recreateSwapChain();
  }
  else if(result != VK_SUCCESS)
  {
    throw std::runtime_error("failed to present swap chain image!");
  }

  currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}
#endif

std::string BlahVkResultString(VkResult res)
{
  switch(res)
  {

  case VK_SUCCESS:
  return "SUCCESS";

  case VK_NOT_READY:
  return "NOT_READY";

  case VK_TIMEOUT:
  return "TIMEOUT";

  case VK_EVENT_SET:
  return "EVENT_SET";

  case VK_EVENT_RESET:
  return "EVENT_RESET";

  case VK_INCOMPLETE:
  return "INCOMPLETE";

  case VK_ERROR_OUT_OF_HOST_MEMORY:
  return "ERROR_OUT_OF_HOST_MEMORY";

  case VK_ERROR_OUT_OF_DEVICE_MEMORY:
  return "ERROR_OUT_OF_DEVICE_MEMORY";

  case VK_ERROR_INITIALIZATION_FAILED:
  return "ERROR_INITIALIZATION_FAILED";

  case VK_ERROR_DEVICE_LOST:
  return "ERROR_DEVICE_LOST";

  case VK_ERROR_MEMORY_MAP_FAILED:
  return "ERROR_MEMORY_MAP_FAILED";

  case VK_ERROR_LAYER_NOT_PRESENT:
  return "ERROR_LAYER_NOT_PRESENT";

  case VK_ERROR_EXTENSION_NOT_PRESENT:
  return "ERROR_EXTENSION_NOT_PRESENT";

  case VK_ERROR_FEATURE_NOT_PRESENT:
  return "ERROR_FEATURE_NOT_PRESENT";

  case VK_ERROR_INCOMPATIBLE_DRIVER:
  return "ERROR_INCOMPATIBLE_DRIVER";

  case VK_ERROR_TOO_MANY_OBJECTS:
  return "ERROR_TOO_MANY_OBJECTS";

  case VK_ERROR_FORMAT_NOT_SUPPORTED:
  return "ERROR_FORMAT_NOT_SUPPORTED";

  case VK_ERROR_SURFACE_LOST_KHR:
  return "ERROR_SURFACE_LOST_KHR";

  case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
  return "ERROR_NATIVE_WINDOW_IN_USE_KHR";

  case VK_SUBOPTIMAL_KHR:
  return "SUBOPTIMAL_KHR";

  case VK_ERROR_OUT_OF_DATE_KHR:
  return "ERROR_OUT_OF_DATE_KHR";

  case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
  return "ERROR_INCOMPATIBLE_DISPLAY_KHR";

  case VK_ERROR_VALIDATION_FAILED_EXT:
  return "ERROR_VALIDATION_FAILED_EXT";

  case VK_ERROR_INVALID_SHADER_NV:
  return "ERROR_INVALID_SHADER_NV";

  default:
  return std::to_string(res);

  }
}

[ [noreturn] ] inline void ThrowVkResult(VkResult res, const char* originator = nullptr, const char* sourceLocation = nullptr)
{
  Throw(Fmt("VkResult failure [%s]", BlahVkResultString(res).c_str() ), originator, sourceLocation);
}

inline VkResult CheckVkResult(VkResult res, const char* originator = nullptr, const char* sourceLocation = nullptr)
{
  if( (res) < VK_SUCCESS)
    ThrowVkResult(res, originator, sourceLocation);

  return res;
}

// XXX These really shouldn't have trailing ';'s
#define THROW_VK(res, cmd) ThrowVkResult(res, #cmd, FILE_AND_LINE)

#define CHECK_VKCMD(cmd) CheckVkResult(cmd, #cmd, FILE_AND_LINE)

#define CHECK_VKRESULT(res, cmdStr) CheckVkResult(res, cmdStr, FILE_AND_LINE)

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

}  // namespace

void MemoryAllocator::MemoryAllocatorInit(VkPhysicalDevice physicalDevice, VkDevice device)
{
  m_memoryAllocatorVkDevice = device;

  if(tableVk.GetPhysicalDeviceMemoryProperties)
    tableVk.GetPhysicalDeviceMemoryProperties(physicalDevice, &m_memoryAllocatorMemoryProperties);
}

void MemoryAllocator::MemoryAllocatorAllocate(VkMemoryRequirements const& memReqs, VkDeviceMemory* mem, VkFlags flags, const void* pNext) const
{
  // Search memtypes to find first index with those properties
  for(uint32_t i = 0; i < m_memoryAllocatorMemoryProperties.memoryTypeCount; ++i)
  {
    if( (memReqs.memoryTypeBits & (1 << i) ) != 0u)
    {
      // Type is available, does it match user properties?
      if( (m_memoryAllocatorMemoryProperties.memoryTypes[i].propertyFlags & flags) == flags)
      {
        VkMemoryAllocateInfo memAlloc {VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, pNext};

        memAlloc.allocationSize = memReqs.size;
        memAlloc.memoryTypeIndex = i;

        if(tableVk.AllocateMemory)
          CHECK_VKCMD(tableVk.AllocateMemory(m_memoryAllocatorVkDevice, &memAlloc, nullptr, mem) );

        return;
      }
    }
  }

  THROW("Memory format not supported");
}

//VkDevice MemoryAllocator::m_memoryAllocatorVkDevice {VK_NULL_HANDLE};

//VkPhysicalDeviceMemoryProperties MemoryAllocator::m_memoryAllocatorMemoryProperties {};

// CmdBuffer - manage VkCommandBuffer state

//CmdBufferStateEnum CmdBuffer::m_cmdBufferState {CmdBufferStateEnum::Undefined};

//VkCommandPool CmdBuffer::m_cmdBufferPool {VK_NULL_HANDLE};

//VkCommandBuffer CmdBuffer::m_cmdBufferBuffer {VK_NULL_HANDLE};

//VkFence CmdBuffer::m_cmdBufferExecFence {VK_NULL_HANDLE};

//CmdBuffer::CmdBuffer() = default;

//CmdBuffer::CmdBuffer(const CmdBuffer& ) = delete;

//CmdBuffer& CmdBuffer::operator=(const CmdBuffer& ) = delete;

//CmdBuffer::CmdBuffer(CmdBuffer&& ) = delete;

//CmdBuffer& CmdBuffer::operator=(CmdBuffer&& ) = delete;

CmdBuffer::~CmdBuffer()
{
  CmdBufferSetState(CmdBufferStateEnum::Undefined);

  if(m_cmdBufferVkDevice != nullptr)
  {
    if(m_cmdBufferBuffer != VK_NULL_HANDLE && tableVk.FreeCommandBuffers)
      tableVk.FreeCommandBuffers(m_cmdBufferVkDevice, m_cmdBufferPool, 1, &m_cmdBufferBuffer);

    if(m_cmdBufferPool != VK_NULL_HANDLE && tableVk.DestroyCommandPool)
      tableVk.DestroyCommandPool(m_cmdBufferVkDevice, m_cmdBufferPool, nullptr);

    if(m_cmdBufferExecFence != VK_NULL_HANDLE && tableVk.DestroyFence)
      tableVk.DestroyFence(m_cmdBufferVkDevice, m_cmdBufferExecFence, nullptr);
  }

  m_cmdBufferBuffer = VK_NULL_HANDLE;
  m_cmdBufferPool = VK_NULL_HANDLE;
  m_cmdBufferExecFence = VK_NULL_HANDLE;
  m_cmdBufferVkDevice = nullptr;
}

std::string CmdBuffer::CmdBufferStateString(CmdBufferStateEnum s)
{
  switch(s)
  {

  case CmdBufferStateEnum::Undefined:
  {
  }
  return "Undefined";

  case CmdBufferStateEnum::Initialized:
  {
  }
  return "Initialized";

  case CmdBufferStateEnum::Recording:
  {
  }
  return "Recording";

  case CmdBufferStateEnum::Executable:
  {
  }
  return "Executable";

  case CmdBufferStateEnum::Executing:
  {
  }
  return "Executing";

  }

  return "(Unknown)";
}

#define CHECK_CBSTATE(s) \
do \
{ \
    if(m_cmdBufferState != (s) ) \
    { \
        Log::Write(Log::Level::Error, std::string("Expecting state " #s " from ") + __FUNCTION__ + ", in " + CmdBufferStateString(m_cmdBufferState) ); \
        return false; \
    } \
\
}while(0)

bool CmdBuffer::CmdBufferInit(const VulkanDebugObjectNamer& namer, VkDevice device, uint32_t queueFamilyIndex)
{
  CHECK_CBSTATE(CmdBufferStateEnum::Undefined);

  m_cmdBufferVkDevice = device;

  // Create a command pool to allocate our command buffer from
  VkCommandPoolCreateInfo cmdPoolInfo {VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO};
  cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  cmdPoolInfo.queueFamilyIndex = queueFamilyIndex;

  if(tableVk.CreateCommandPool)
    CHECK_VKCMD(tableVk.CreateCommandPool(m_cmdBufferVkDevice, &cmdPoolInfo, nullptr, &m_cmdBufferPool) );

  CHECK_VKCMD(namer.SetName(VK_OBJECT_TYPE_COMMAND_POOL, (uint64_t)m_cmdBufferPool, "helloxr command pool") );

  // Create the command buffer from the command pool
  VkCommandBufferAllocateInfo cmd {VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO};
  cmd.commandPool = m_cmdBufferPool;
  cmd.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  cmd.commandBufferCount = 1;

  if(tableVk.AllocateCommandBuffers)
    CHECK_VKCMD(tableVk.AllocateCommandBuffers(m_cmdBufferVkDevice, &cmd, &m_cmdBufferBuffer) );

  CHECK_VKCMD(namer.SetName(VK_OBJECT_TYPE_COMMAND_BUFFER, (uint64_t)m_cmdBufferBuffer, "helloxr command buffer") );

  VkFenceCreateInfo fenceInfo {VK_STRUCTURE_TYPE_FENCE_CREATE_INFO};

  if(tableVk.CreateFence)
    CHECK_VKCMD(tableVk.CreateFence(m_cmdBufferVkDevice, &fenceInfo, nullptr, &m_cmdBufferExecFence) );

  CHECK_VKCMD(namer.SetName(VK_OBJECT_TYPE_FENCE, (uint64_t)m_cmdBufferExecFence, "helloxr fence") );

  CmdBufferSetState(CmdBufferStateEnum::Initialized);

  return true;
}

bool CmdBuffer::CmdBufferBegin()
{
  CHECK_CBSTATE(CmdBufferStateEnum::Initialized);

  VkCommandBufferBeginInfo cmdBeginInfo {VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};

  if(tableVk.BeginCommandBuffer)
    CHECK_VKCMD(tableVk.BeginCommandBuffer(m_cmdBufferBuffer, &cmdBeginInfo) );

  CmdBufferSetState(CmdBufferStateEnum::Recording);

  return true;
}

bool CmdBuffer::CmdBufferEnd()
{
  CHECK_CBSTATE(CmdBufferStateEnum::Recording);

  if(tableVk.EndCommandBuffer)
    CHECK_VKCMD(tableVk.EndCommandBuffer(m_cmdBufferBuffer) );

  CmdBufferSetState(CmdBufferStateEnum::Executable);

  return true;
}

bool CmdBuffer::CmdBufferExec(VkQueue queue)
{
  CHECK_CBSTATE(CmdBufferStateEnum::Executable);

  VkSubmitInfo submitInfo {VK_STRUCTURE_TYPE_SUBMIT_INFO};

  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &m_cmdBufferBuffer;

  if(tableVk.QueueSubmit)
    CHECK_VKCMD(tableVk.QueueSubmit(queue, 1, &submitInfo, m_cmdBufferExecFence) );

  CmdBufferSetState(CmdBufferStateEnum::Executing);

  return true;
}

bool CmdBuffer::CmdBufferWait()
{
  // Waiting on a not-in-flight command buffer is a no-op
  if(m_cmdBufferState == CmdBufferStateEnum::Initialized)
    return true;

  CHECK_CBSTATE(CmdBufferStateEnum::Executing);

  const uint32_t timeoutNs = 1 * 1000 * 1000 * 1000;

  for(int i = 0; i < 5; ++i)
  {
    VkResult res = VK_ERROR_OUT_OF_HOST_MEMORY;

    if(tableVk.WaitForFences)
      res = tableVk.WaitForFences(m_cmdBufferVkDevice, 1, &m_cmdBufferExecFence, VK_TRUE, timeoutNs);

    if(res == VK_SUCCESS)
    {
      // Buffer can be executed multiple times...
      CmdBufferSetState(CmdBufferStateEnum::Executable);
      return true;
    }

    Log::Write(Log::Level::Info, "Waiting for CmdBuffer fence timed out, retrying...");
  }

  return false;
}

bool CmdBuffer::CmdBufferReset()
{
  if(m_cmdBufferState != CmdBufferStateEnum::Initialized)
  {
    CHECK_CBSTATE(CmdBufferStateEnum::Executable);

    if(tableVk.ResetFences)
      CHECK_VKCMD(tableVk.ResetFences(m_cmdBufferVkDevice, 1, &m_cmdBufferExecFence) );

    if(tableVk.ResetCommandBuffer)
      CHECK_VKCMD(tableVk.ResetCommandBuffer(m_cmdBufferBuffer, 0) );

    CmdBufferSetState(CmdBufferStateEnum::Initialized);
  }

  return true;
}

//VkDevice CmdBuffer::m_cmdBufferVkDevice {VK_NULL_HANDLE};

void CmdBuffer::CmdBufferSetState(CmdBufferStateEnum newState)
{
  m_cmdBufferState = newState;
}

#undef CHECK_CBSTATE

// ShaderProgram to hold a pair of vertex & fragment shaders

//std::array<VkPipelineShaderStageCreateInfo, 2> ShaderProgram::m_shaderProgramShaderInfo { { {VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO}, {VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO} } };

//ShaderProgram::ShaderProgram() = default;

ShaderProgram::~ShaderProgram()
{
  if(m_shaderProgramVkDevice != nullptr)
  {
    for(auto& si : m_shaderProgramShaderInfo)
    {
      if(si.module != VK_NULL_HANDLE && tableVk.DestroyShaderModule)
        tableVk.DestroyShaderModule(m_shaderProgramVkDevice, m_shaderProgramShaderInfo[0].module, nullptr);

      si.module = VK_NULL_HANDLE;
    }
  }

  m_shaderProgramShaderInfo = {};

  m_shaderProgramVkDevice = nullptr;
}

//ShaderProgram::ShaderProgram(const ShaderProgram& ) = delete;

//ShaderProgram& ShaderProgram::operator=(const ShaderProgram& ) = delete;

//ShaderProgram::ShaderProgram(ShaderProgram&& ) = delete;

//ShaderProgram& ShaderProgram::operator=(ShaderProgram&& ) = delete;

void ShaderProgram::ShaderProgramLoadVertexShader(const std::vector<uint32_t>& code)
{
  ShaderProgramLoad(0, code);
}

void ShaderProgram::ShaderProgramLoadFragmentShader(const std::vector<uint32_t>& code)
{
  ShaderProgramLoad(1, code);
}

void ShaderProgram::ShaderProgramInit(VkDevice device)
{
  m_shaderProgramVkDevice = device;
}

//VkDevice ShaderProgram::m_shaderProgramVkDevice {VK_NULL_HANDLE};

void ShaderProgram::ShaderProgramLoad(uint32_t index, const std::vector<uint32_t>& code)
{
  VkShaderModuleCreateInfo modInfo {VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO};

  auto& si = m_shaderProgramShaderInfo[index];
  si.pName = "main";
  std::string name;

  switch(index)
  {

  case 0:
      si.stage = VK_SHADER_STAGE_VERTEX_BIT;
      name = "vertex";
      break;

  case 1:
      si.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
      name = "fragment";
      break;

  default:
      THROW(Fmt("Unknown code index %d", index) );

  }

  modInfo.codeSize = code.size() * sizeof(code[0] );
  modInfo.pCode = &code[0];
  CHECK_MSG( (modInfo.codeSize > 0) && modInfo.pCode, Fmt("Invalid %s shader ", name.c_str() ) );

  if(tableVk.CreateShaderModule)
    CHECK_VKCMD(tableVk.CreateShaderModule(m_shaderProgramVkDevice, &modInfo, nullptr, &si.module) );

  Log::Write(Log::Level::Info, Fmt("Loaded %s shader", name.c_str() ) );
}

// VertexBuffer base class

//VkBuffer VertexBufferBase::m_vertexBufferBaseIdxBuf {VK_NULL_HANDLE};

//VkDeviceMemory VertexBufferBase::m_vertexBufferBaseIdxMem {VK_NULL_HANDLE};

//VkBuffer VertexBufferBase::m_vertexBufferBaseVtxBuf {VK_NULL_HANDLE};

//VkDeviceMemory VertexBufferBase::m_vertexBufferBaseVtxMem {VK_NULL_HANDLE};

//VkVertexInputBindingDescription VertexBufferBase::m_vertexBufferBaseBindDesc {};

//std::vector<VkVertexInputAttributeDescription> VertexBufferBase::m_vertexBufferBaseAttrDesc {};

//struct
//{
//  uint32_t idx;
//  uint32_t vtx;
//
//}VertexBufferBase::m_vertexBufferBaseCount = {0, 0};

//VertexBufferBase::VertexBufferBase() = default;

VertexBufferBase::~VertexBufferBase()
{
  if(m_vertexBufferBaseVkDevice)
  {
    if(m_vertexBufferBaseIdxBuf != VK_NULL_HANDLE && tableVk.DestroyBuffer)
      tableVk.DestroyBuffer(m_vertexBufferBaseVkDevice, m_vertexBufferBaseIdxBuf, nullptr);

    if(m_vertexBufferBaseIdxMem != VK_NULL_HANDLE && tableVk.FreeMemory)
      tableVk.FreeMemory(m_vertexBufferBaseVkDevice, m_vertexBufferBaseIdxMem, nullptr);

    if(m_vertexBufferBaseVtxBuf != VK_NULL_HANDLE && tableVk.DestroyBuffer)
      tableVk.DestroyBuffer(m_vertexBufferBaseVkDevice, m_vertexBufferBaseVtxBuf, nullptr);

    if(m_vertexBufferBaseVtxMem != VK_NULL_HANDLE && tableVk.FreeMemory)
      tableVk.FreeMemory(m_vertexBufferBaseVkDevice, m_vertexBufferBaseVtxMem, nullptr);
  }

  m_vertexBufferBaseIdxBuf = VK_NULL_HANDLE;
  m_vertexBufferBaseIdxMem = VK_NULL_HANDLE;
  m_vertexBufferBaseVtxBuf = VK_NULL_HANDLE;
  m_vertexBufferBaseVtxMem = VK_NULL_HANDLE;
  m_vertexBufferBaseBindDesc = {};
  m_vertexBufferBaseAttrDesc.clear();
  m_vertexBufferBaseCount = {0, 0};
  m_vertexBufferBaseVkDevice = nullptr;
}

//VertexBufferBase::VertexBufferBase(const VertexBufferBase& ) = delete;

//VertexBufferBase& VertexBufferBase::operator=(const VertexBufferBase& ) = delete;

//VertexBufferBase::VertexBufferBase(VertexBufferBase&& ) = delete;

//VertexBufferBase& VertexBufferBase::operator=(VertexBufferBase&& ) = delete;

void VertexBufferBase::VertexBufferBaseInit(VkDevice device, const MemoryAllocator* memAllocator, const std::vector<VkVertexInputAttributeDescription>& attr)
{
  m_vertexBufferBaseVkDevice = device;
  m_vertexBufferBaseMemoryAllocator = memAllocator;
  m_vertexBufferBaseAttrDesc = attr;
}

//VkDevice VertexBufferBase::m_vertexBufferBaseVkDevice {VK_NULL_HANDLE};

void VertexBufferBase::VertexBufferBaseAllocateBufferMemory(VkBuffer buf, VkDeviceMemory* mem) const
{
  VkMemoryRequirements memReq = {};

  if(tableVk.GetBufferMemoryRequirements)
    tableVk.GetBufferMemoryRequirements(m_vertexBufferBaseVkDevice, buf, &memReq);

  m_vertexBufferBaseMemoryAllocator->MemoryAllocatorAllocate(memReq, mem);
}

//const MemoryAllocator* VertexBufferBase::m_vertexBufferBaseMemoryAllocator {nullptr};

// VertexBuffer template to wrap the indices and vertices

template <typename T> bool VertexBuffer<T>::VertexBufferCreate(uint32_t idxCount, uint32_t vtxCount)
{
  VkBufferCreateInfo bufInfo {VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO};

  bufInfo.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
  bufInfo.size = sizeof(uint16_t) * idxCount;

  if(tableVk.CreateBuffer)
    CHECK_VKCMD(tableVk.CreateBuffer(m_vertexBufferBaseVkDevice, &bufInfo, nullptr, &m_vertexBufferBaseIdxBuf) );

  VertexBufferBaseAllocateBufferMemory(m_vertexBufferBaseIdxBuf, &m_vertexBufferBaseIdxMem);

  if(tableVk.BindBufferMemory)
    CHECK_VKCMD(tableVk.BindBufferMemory(m_vertexBufferBaseVkDevice, m_vertexBufferBaseIdxBuf, m_vertexBufferBaseIdxMem, 0) );

  bufInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
  bufInfo.size = sizeof(T) * vtxCount;

  if(tableVk.CreateBuffer)
    CHECK_VKCMD(tableVk.CreateBuffer(m_vertexBufferBaseVkDevice, &bufInfo, nullptr, &m_vertexBufferBaseVtxBuf) );

  VertexBufferBaseAllocateBufferMemory(m_vertexBufferBaseVtxBuf, &m_vertexBufferBaseVtxMem);

  if(tableVk.BindBufferMemory)
    CHECK_VKCMD(tableVk.BindBufferMemory(m_vertexBufferBaseVkDevice, m_vertexBufferBaseVtxBuf, m_vertexBufferBaseVtxMem, 0) );

  m_vertexBufferBaseBindDesc.binding = 0;
  m_vertexBufferBaseBindDesc.stride = sizeof(T);
  m_vertexBufferBaseBindDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

  m_vertexBufferBaseCount = {idxCount, vtxCount};

  return true;
}

template <typename T> void VertexBuffer<T>::VertexBufferUpdateIndices(const uint16_t* data, uint32_t elements, uint32_t offset)
{
  uint16_t* map = nullptr;

  if(tableVk.MapMemory)
    CHECK_VKCMD(tableVk.MapMemory(m_vertexBufferBaseVkDevice, m_vertexBufferBaseIdxMem, sizeof(map[0] ) * offset, sizeof(map[0] ) * elements, 0, (void**)&map) );

  for(size_t i = 0; i < elements; ++i)
    map[i] = data[i];

  if(tableVk.UnmapMemory)
    tableVk.UnmapMemory(m_vertexBufferBaseVkDevice, m_vertexBufferBaseIdxMem);
}

template <typename T> void VertexBuffer<T>::VertexBufferUpdateVertices(const T* data, uint32_t elements, uint32_t offset)
{
  T* map = nullptr;

  if(tableVk.MapMemory)
    CHECK_VKCMD(tableVk.MapMemory(m_vertexBufferBaseVkDevice, m_vertexBufferBaseVtxMem, sizeof(map[0] ) * offset, sizeof(map[0] ) * elements, 0, (void**)&map) );

  for(size_t i = 0; i < elements; ++i)
    map[i] = data[i];

  if(tableVk.UnmapMemory)
    tableVk.UnmapMemory(m_vertexBufferBaseVkDevice, m_vertexBufferBaseVtxMem);
}

// RenderPass wrapper

//VkFormat RenderPass::m_renderPassColorFmt {};

//VkFormat RenderPass::m_renderPassDepthFmt {};

//VkRenderPass RenderPass::m_renderPassPass {VK_NULL_HANDLE};

//RenderPass::RenderPass() = default;

bool RenderPass::RenderPassCreate(const VulkanDebugObjectNamer& namer, VkDevice device, VkFormat aColorFmt, VkFormat aDepthFmt)
{
  m_renderPassVkDevice = device;
  m_renderPassColorFmt = aColorFmt;
  m_renderPassDepthFmt = aDepthFmt;

  VkSubpassDescription subpass = {};
  subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

  VkAttachmentReference colorRef = {0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
  VkAttachmentReference depthRef = {1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};

  std::array<VkAttachmentDescription, 2> at = {};

  VkRenderPassCreateInfo rpInfo {VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO};
  rpInfo.attachmentCount = 0;
  rpInfo.pAttachments = at.data();
  rpInfo.subpassCount = 1;
  rpInfo.pSubpasses = &subpass;

  if(m_renderPassColorFmt != VK_FORMAT_UNDEFINED)
  {
    colorRef.attachment = rpInfo.attachmentCount++;

    at[colorRef.attachment].format = m_renderPassColorFmt;
    at[colorRef.attachment].samples = VK_SAMPLE_COUNT_1_BIT;
    at[colorRef.attachment].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    at[colorRef.attachment].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    at[colorRef.attachment].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    at[colorRef.attachment].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    at[colorRef.attachment].initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    at[colorRef.attachment].finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorRef;
  }

  if(m_renderPassDepthFmt != VK_FORMAT_UNDEFINED)
  {
    depthRef.attachment = rpInfo.attachmentCount++;

    at[depthRef.attachment].format = m_renderPassDepthFmt;
    at[depthRef.attachment].samples = VK_SAMPLE_COUNT_1_BIT;
    at[depthRef.attachment].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    at[depthRef.attachment].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    at[depthRef.attachment].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    at[depthRef.attachment].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    at[depthRef.attachment].initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    at[depthRef.attachment].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    subpass.pDepthStencilAttachment = &depthRef;
  }

  if(tableVk.CreateRenderPass)
    CHECK_VKCMD(tableVk.CreateRenderPass(m_renderPassVkDevice, &rpInfo, nullptr, &m_renderPassPass) );

  CHECK_VKCMD(namer.SetName(VK_OBJECT_TYPE_RENDER_PASS, (uint64_t)m_renderPassPass, "helloxr render pass") );

  return true;
}

RenderPass::~RenderPass()
{
    if(m_renderPassVkDevice)
    {
      if(m_renderPassPass != VK_NULL_HANDLE && tableVk.DestroyRenderPass)
        tableVk.DestroyRenderPass(m_renderPassVkDevice, m_renderPassPass, nullptr);
    }

    m_renderPassPass = VK_NULL_HANDLE;
    m_renderPassVkDevice = nullptr;
}

//RenderPass::RenderPass(const RenderPass&) = delete;

//RenderPass& RenderPass::operator=(const RenderPass&) = delete;

//RenderPass::RenderPass(RenderPass&&) = delete;

//RenderPass& RenderPass::operator=(RenderPass&&) = delete;

//VkDevice RenderPass::m_renderPassVkDevice {VK_NULL_HANDLE};

// VkImage + framebuffer wrapper

//VkImage RenderTarget::m_renderTargetColorImage {VK_NULL_HANDLE};

//VkImage RenderTarget::m_renderTargetDepthImage {VK_NULL_HANDLE};

//VkImageView RenderTarget::m_renderTargetColorView {VK_NULL_HANDLE};

//VkImageView RenderTarget::m_renderTargetDepthView {VK_NULL_HANDLE};

//VkFramebuffer RenderTarget::m_renderTargetFrameBuffer {VK_NULL_HANDLE};

//RenderTarget::RenderTarget() = default;

RenderTarget::~RenderTarget()
{
  if(m_renderTargetVkDevice != nullptr)
  {
    if(m_renderTargetFrameBuffer != VK_NULL_HANDLE && tableVk.DestroyFramebuffer)
      tableVk.DestroyFramebuffer(m_renderTargetVkDevice, m_renderTargetFrameBuffer, nullptr);

    if(m_renderTargetColorView != VK_NULL_HANDLE && tableVk.DestroyImageView)
      tableVk.DestroyImageView(m_renderTargetVkDevice, m_renderTargetColorView, nullptr);

    if(m_renderTargetDepthView != VK_NULL_HANDLE && tableVk.DestroyImageView)
      tableVk.DestroyImageView(m_renderTargetVkDevice, m_renderTargetDepthView, nullptr);
  }

  // Note we don't own color, it will get destroyed when xrDestroySwapchain is called
  m_renderTargetColorImage = VK_NULL_HANDLE;

  // Note we don't own depthImage, it will get destroyed when xrDestroySwapchain is called
  m_renderTargetDepthImage = VK_NULL_HANDLE;
  m_renderTargetColorView = VK_NULL_HANDLE;
  m_renderTargetDepthView = VK_NULL_HANDLE;
  m_renderTargetFrameBuffer = VK_NULL_HANDLE;
  m_renderTargetVkDevice = nullptr;
}

RenderTarget::RenderTarget(RenderTarget&& other) : RenderTarget()
{
  using std::swap;
  swap(m_renderTargetColorImage, other.m_renderTargetColorImage);
  swap(m_renderTargetDepthImage, other.m_renderTargetDepthImage);
  swap(m_renderTargetColorView, other.m_renderTargetColorView);
  swap(m_renderTargetDepthView, other.m_renderTargetDepthView);
  swap(m_renderTargetFrameBuffer, other.m_renderTargetFrameBuffer);
  swap(m_renderTargetVkDevice, other.m_renderTargetVkDevice);
}

RenderTarget& RenderTarget::operator=(RenderTarget&& other)
{
  if( &other == this)
    return *this;

  // Clean up ourselves.
  this->~RenderTarget();
  using std::swap;
  swap(m_renderTargetColorImage, other.m_renderTargetColorImage);
  swap(m_renderTargetDepthImage, other.m_renderTargetDepthImage);
  swap(m_renderTargetColorView, other.m_renderTargetColorView);
  swap(m_renderTargetDepthView, other.m_renderTargetDepthView);
  swap(m_renderTargetFrameBuffer, other.m_renderTargetFrameBuffer);
  swap(m_renderTargetVkDevice, other.m_renderTargetVkDevice);
  return *this;
}

void RenderTarget::RenderTargetCreate(const VulkanDebugObjectNamer& namer, VkDevice device, VkImage aColorImage, VkImage aDepthImage, VkExtent2D size, RenderPass& renderPass)
{
  m_renderTargetVkDevice = device;

  m_renderTargetColorImage = aColorImage;
  m_renderTargetDepthImage = aDepthImage;

  std::array<VkImageView, 2> attachments {};

  uint32_t attachmentCount = 0;

  // Create color image view
  if(m_renderTargetColorImage != VK_NULL_HANDLE)
  {
    VkImageViewCreateInfo colorViewInfo {VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};

    colorViewInfo.image = m_renderTargetColorImage;
    colorViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    colorViewInfo.format = renderPass.m_renderPassColorFmt;
    colorViewInfo.components.r = VK_COMPONENT_SWIZZLE_R;
    colorViewInfo.components.g = VK_COMPONENT_SWIZZLE_G;
    colorViewInfo.components.b = VK_COMPONENT_SWIZZLE_B;
    colorViewInfo.components.a = VK_COMPONENT_SWIZZLE_A;
    colorViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    colorViewInfo.subresourceRange.baseMipLevel = 0;
    colorViewInfo.subresourceRange.levelCount = 1;
    colorViewInfo.subresourceRange.baseArrayLayer = 0;
    colorViewInfo.subresourceRange.layerCount = 1;

    if(tableVk.CreateImageView)
      CHECK_VKCMD(tableVk.CreateImageView(m_renderTargetVkDevice, &colorViewInfo, nullptr, &m_renderTargetColorView) );

    CHECK_VKCMD(namer.SetName(VK_OBJECT_TYPE_IMAGE_VIEW, (uint64_t)m_renderTargetColorView, "helloxr color image view") );

    attachments[attachmentCount++] = m_renderTargetColorView;
  }

  // Create depth image view
  if(m_renderTargetDepthImage != VK_NULL_HANDLE)
  {
    VkImageViewCreateInfo depthViewInfo {VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};

    depthViewInfo.image = m_renderTargetDepthImage;
    depthViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    depthViewInfo.format = renderPass.m_renderPassDepthFmt;
    depthViewInfo.components.r = VK_COMPONENT_SWIZZLE_R;
    depthViewInfo.components.g = VK_COMPONENT_SWIZZLE_G;
    depthViewInfo.components.b = VK_COMPONENT_SWIZZLE_B;
    depthViewInfo.components.a = VK_COMPONENT_SWIZZLE_A;
    depthViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    depthViewInfo.subresourceRange.baseMipLevel = 0;
    depthViewInfo.subresourceRange.levelCount = 1;
    depthViewInfo.subresourceRange.baseArrayLayer = 0;
    depthViewInfo.subresourceRange.layerCount = 1;

    if(tableVk.CreateImageView)
      CHECK_VKCMD(tableVk.CreateImageView(m_renderTargetVkDevice, &depthViewInfo, nullptr, &m_renderTargetDepthView) );

    CHECK_VKCMD(namer.SetName(VK_OBJECT_TYPE_IMAGE_VIEW, (uint64_t)m_renderTargetDepthView, "helloxr depth image view") );
    attachments[attachmentCount++] = m_renderTargetDepthView;
  }

  VkFramebufferCreateInfo fbInfo {VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO};

  fbInfo.renderPass = renderPass.m_renderPassPass;
  fbInfo.attachmentCount = attachmentCount;
  fbInfo.pAttachments = attachments.data();
  fbInfo.width = size.width;
  fbInfo.height = size.height;
  fbInfo.layers = 1;

  if(tableVk.CreateFramebuffer)
    CHECK_VKCMD(tableVk.CreateFramebuffer(m_renderTargetVkDevice, &fbInfo, nullptr, &m_renderTargetFrameBuffer) );

  CHECK_VKCMD(namer.SetName(VK_OBJECT_TYPE_FRAMEBUFFER, (uint64_t)m_renderTargetFrameBuffer, "helloxr framebuffer") );
}

//RenderTarget::RenderTarget(const RenderTarget&) = delete;

//RenderTarget& RenderTarget::operator=(const RenderTarget&) = delete;

//VkDevice RenderTarget::m_renderTargetVkDevice {VK_NULL_HANDLE};

// Simple vertex MVP xform & color fragment shader layout

//VkPipelineLayout PipelineLayout::m_pipelineLayoutLayout {VK_NULL_HANDLE};

//PipelineLayout::PipelineLayout() = default;

PipelineLayout::~PipelineLayout()
{
  if(m_pipelineLayoutVkDevice)
  {
    if(m_pipelineLayoutLayout != VK_NULL_HANDLE && tableVk.DestroyPipelineLayout)
      tableVk.DestroyPipelineLayout(m_pipelineLayoutVkDevice, m_pipelineLayoutLayout, nullptr);

    m_pipelineLayoutLayout = VK_NULL_HANDLE;
    m_pipelineLayoutVkDevice = nullptr;
  }
}

void PipelineLayout::PipelineLayoutCreate(VkDevice device)
{
  m_pipelineLayoutVkDevice = device;

  // MVP matrix is a push_constant
  VkPushConstantRange pcr = {};
  pcr.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  pcr.offset = 0;
  pcr.size = 4 * 4 * sizeof(float);

  VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo {VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO};

  pipelineLayoutCreateInfo.pushConstantRangeCount = 1;
  pipelineLayoutCreateInfo.pPushConstantRanges = &pcr;

  if(tableVk.CreatePipelineLayout)
    CHECK_VKCMD(tableVk.CreatePipelineLayout(m_pipelineLayoutVkDevice, &pipelineLayoutCreateInfo, nullptr, &m_pipelineLayoutLayout) );
}

//PipelineLayout::PipelineLayout(const PipelineLayout& ) = delete;

//PipelineLayout& PipelineLayout::operator=(const PipelineLayout& ) = delete;

//PipelineLayout::PipelineLayout(PipelineLayout&& ) = delete;

//PipelineLayout& PipelineLayout::operator=(PipelineLayout&& ) = delete;

//VkDevice PipelineLayout::m_pipelineLayoutVkDevice {VK_NULL_HANDLE};

// Pipeline wrapper for rendering pipeline state

//VkPipeline Pipeline::m_pipelinePipe {VK_NULL_HANDLE};

//VkPrimitiveTopology Pipeline::m_pipelineTopology {VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST};

//std::vector<VkDynamicState> Pipeline::m_pipelineDynamicStateEnables;

//Pipeline::Pipeline() = default;

void Pipeline::PipelineDynamic(VkDynamicState state)
{
  m_pipelineDynamicStateEnables.emplace_back(state);
}

void Pipeline::PipelineCreate(VkDevice device, VkExtent2D size, const PipelineLayout& layout, const RenderPass& rp, const ShaderProgram& sp, const VertexBufferBase& vb)
{
  m_pipelineVkDevice = device;

  VkPipelineDynamicStateCreateInfo dynamicState {VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO};
  dynamicState.dynamicStateCount = (uint32_t)m_pipelineDynamicStateEnables.size();
  dynamicState.pDynamicStates = m_pipelineDynamicStateEnables.data();

  VkPipelineVertexInputStateCreateInfo vi {VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO};
  vi.vertexBindingDescriptionCount = 1;
  vi.pVertexBindingDescriptions = &vb.m_vertexBufferBaseBindDesc;
  vi.vertexAttributeDescriptionCount = (uint32_t)vb.m_vertexBufferBaseAttrDesc.size();
  vi.pVertexAttributeDescriptions = vb.m_vertexBufferBaseAttrDesc.data();

  VkPipelineInputAssemblyStateCreateInfo ia {VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO};
  ia.primitiveRestartEnable = VK_FALSE;
  ia.topology = m_pipelineTopology;

  VkPipelineRasterizationStateCreateInfo rs {VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO};
  rs.polygonMode = VK_POLYGON_MODE_FILL;
  rs.cullMode = VK_CULL_MODE_BACK_BIT;
  rs.frontFace = VK_FRONT_FACE_CLOCKWISE;
  rs.depthClampEnable = VK_FALSE;
  rs.rasterizerDiscardEnable = VK_FALSE;
  rs.depthBiasEnable = VK_FALSE;
  rs.depthBiasConstantFactor = 0;
  rs.depthBiasClamp = 0;
  rs.depthBiasSlopeFactor = 0;
  rs.lineWidth = 1.0f;

  VkPipelineColorBlendAttachmentState attachState {};
  attachState.blendEnable = 0;
  attachState.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
  attachState.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
  attachState.colorBlendOp = VK_BLEND_OP_ADD;
  attachState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
  attachState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  attachState.alphaBlendOp = VK_BLEND_OP_ADD;
  attachState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

  VkPipelineColorBlendStateCreateInfo cb {VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO};
  cb.attachmentCount = 1;
  cb.pAttachments = &attachState;
  cb.logicOpEnable = VK_FALSE;
  cb.logicOp = VK_LOGIC_OP_NO_OP;
  cb.blendConstants[0] = 1.0f;
  cb.blendConstants[1] = 1.0f;
  cb.blendConstants[2] = 1.0f;
  cb.blendConstants[3] = 1.0f;

  VkRect2D scissor = { {0, 0}, size};

#if defined(ORIGIN_BOTTOM_LEFT)
  // Flipped view so origin is bottom-left like GL (requires VK_KHR_maintenance1)
  VkViewport viewport = {0.0f, (float)size.height, (float)size.width, -(float)size.height, 0.0f, 1.0f};
#else
  // Will invert y after projection
  VkViewport viewport = {0.0f, 0.0f, (float)size.width, (float)size.height, 0.0f, 1.0f};
#endif

  VkPipelineViewportStateCreateInfo vp {VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO};
  vp.viewportCount = 1;
  vp.pViewports = &viewport;
  vp.scissorCount = 1;
  vp.pScissors = &scissor;

  VkPipelineDepthStencilStateCreateInfo ds {VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO};
  ds.depthTestEnable = VK_TRUE;
  ds.depthWriteEnable = VK_TRUE;
  ds.depthCompareOp = VK_COMPARE_OP_LESS;
  ds.depthBoundsTestEnable = VK_FALSE;
  ds.stencilTestEnable = VK_FALSE;
  ds.front.failOp = VK_STENCIL_OP_KEEP;
  ds.front.passOp = VK_STENCIL_OP_KEEP;
  ds.front.depthFailOp = VK_STENCIL_OP_KEEP;
  ds.front.compareOp = VK_COMPARE_OP_ALWAYS;
  ds.back = ds.front;
  ds.minDepthBounds = 0.0f;
  ds.maxDepthBounds = 1.0f;

  VkPipelineMultisampleStateCreateInfo ms {VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO};
  ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

  VkGraphicsPipelineCreateInfo pipeInfo {VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO};
  pipeInfo.stageCount = (uint32_t)sp.m_shaderProgramShaderInfo.size();
  pipeInfo.pStages = sp.m_shaderProgramShaderInfo.data();
  pipeInfo.pVertexInputState = &vi;
  pipeInfo.pInputAssemblyState = &ia;
  pipeInfo.pTessellationState = nullptr;
  pipeInfo.pViewportState = &vp;
  pipeInfo.pRasterizationState = &rs;
  pipeInfo.pMultisampleState = &ms;
  pipeInfo.pDepthStencilState = &ds;
  pipeInfo.pColorBlendState = &cb;

  if(dynamicState.dynamicStateCount > 0)
    pipeInfo.pDynamicState = &dynamicState;

  pipeInfo.layout = layout.m_pipelineLayoutLayout;
  pipeInfo.renderPass = rp.m_renderPassPass;
  pipeInfo.subpass = 0;

  if(tableVk.CreateGraphicsPipelines)
    CHECK_VKCMD(tableVk.CreateGraphicsPipelines(m_pipelineVkDevice, VK_NULL_HANDLE, 1, &pipeInfo, nullptr, &m_pipelinePipe) );
}

void Pipeline::PipelineRelease()
{
  if(m_pipelineVkDevice)
  {
    if(m_pipelinePipe != VK_NULL_HANDLE && tableVk.DestroyPipeline)
      tableVk.DestroyPipeline(m_pipelineVkDevice, m_pipelinePipe, nullptr);
  }

  m_pipelinePipe = VK_NULL_HANDLE;
  m_pipelineVkDevice = nullptr;
}

//VkDevice Pipeline::m_pipelineVkDevice {VK_NULL_HANDLE};

//VkDeviceMemory DepthBuffer::m_depthBufferDepthMemory {VK_NULL_HANDLE};

//VkImage DepthBuffer::m_depthBufferDepthImage {VK_NULL_HANDLE};

//DepthBuffer::DepthBuffer() = default;

DepthBuffer::~DepthBuffer()
{
  if(m_depthBufferVkDevice != nullptr)
  {
    if(m_depthBufferDepthImage != VK_NULL_HANDLE && tableVk.DestroyImage)
      tableVk.DestroyImage(m_depthBufferVkDevice, m_depthBufferDepthImage, nullptr);

    if(m_depthBufferDepthMemory != VK_NULL_HANDLE && tableVk.FreeMemory)
      tableVk.FreeMemory(m_depthBufferVkDevice, m_depthBufferDepthMemory, nullptr);
  }

  m_depthBufferDepthImage = VK_NULL_HANDLE;
  m_depthBufferDepthMemory = VK_NULL_HANDLE;
  m_depthBufferVkDevice = nullptr;
}

DepthBuffer::DepthBuffer(DepthBuffer&& other) : DepthBuffer()
{
  using std::swap;

  swap(m_depthBufferDepthImage, other.m_depthBufferDepthImage);
  swap(m_depthBufferDepthMemory, other.m_depthBufferDepthMemory);
  swap(m_depthBufferVkDevice, other.m_depthBufferVkDevice);
}

DepthBuffer& DepthBuffer::operator=(DepthBuffer&& other)
{
  if( &other == this)
    return *this;

  // clean up self
  this->~DepthBuffer();
  using std::swap;

  swap(m_depthBufferDepthImage, other.m_depthBufferDepthImage);
  swap(m_depthBufferDepthMemory, other.m_depthBufferDepthMemory);
  swap(m_depthBufferVkDevice, other.m_depthBufferVkDevice);
  return *this;
}

void DepthBuffer::DepthBufferCreate(const VulkanDebugObjectNamer& namer, VkDevice device, MemoryAllocator* memAllocator, VkFormat depthFormat, const XrSwapchainCreateInfo& swapchainCreateInfo)
{
  m_depthBufferVkDevice = device;

  VkExtent2D size = {swapchainCreateInfo.width, swapchainCreateInfo.height};

  // Create a D32 depthbuffer
  VkImageCreateInfo imageInfo {VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO};
  imageInfo.imageType = VK_IMAGE_TYPE_2D;
  imageInfo.extent.width = size.width;
  imageInfo.extent.height = size.height;
  imageInfo.extent.depth = 1;
  imageInfo.mipLevels = 1;
  imageInfo.arrayLayers = 1;
  imageInfo.format = depthFormat;
  imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
  imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
  imageInfo.samples = (VkSampleCountFlagBits)swapchainCreateInfo.sampleCount;
  imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  if(tableVk.CreateImage)
    CHECK_VKCMD(tableVk.CreateImage(m_depthBufferVkDevice, &imageInfo, nullptr, &m_depthBufferDepthImage) );

  CHECK_VKCMD(namer.SetName(VK_OBJECT_TYPE_IMAGE, (uint64_t)m_depthBufferDepthImage, "helloxr fallback depth image") );

  VkMemoryRequirements memRequirements {};

  if(tableVk.GetImageMemoryRequirements)
    tableVk.GetImageMemoryRequirements(m_depthBufferVkDevice, m_depthBufferDepthImage, &memRequirements);

  memAllocator->MemoryAllocatorAllocate(memRequirements, &m_depthBufferDepthMemory, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
  CHECK_VKCMD(namer.SetName(VK_OBJECT_TYPE_DEVICE_MEMORY, (uint64_t)m_depthBufferDepthMemory, "helloxr fallback depth image memory") );

  if(tableVk.BindImageMemory)
    CHECK_VKCMD(tableVk.BindImageMemory(m_depthBufferVkDevice, m_depthBufferDepthImage, m_depthBufferDepthMemory, 0) );
}

void DepthBuffer::DepthBufferTransitionImageLayout(CmdBuffer* cmdBuffer, VkImageLayout newLayout)
{
  if(newLayout == m_depthBufferVkImageLayout)
    return;

  VkImageMemoryBarrier depthBarrier {VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER};
  depthBarrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
  depthBarrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
  depthBarrier.oldLayout = m_depthBufferVkImageLayout;
  depthBarrier.newLayout = newLayout;
  depthBarrier.image = m_depthBufferDepthImage;

  depthBarrier.subresourceRange = {VK_IMAGE_ASPECT_DEPTH_BIT, 0, 1, 0, 1};

  if(tableVk.CmdPipelineBarrier)
    tableVk.CmdPipelineBarrier(cmdBuffer->m_cmdBufferBuffer, VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, 0, 0, nullptr, 0, nullptr, 1, &depthBarrier);

  m_depthBufferVkImageLayout = newLayout;
}

//DepthBuffer::DepthBuffer(const DepthBuffer&) = delete;

//DepthBuffer& DepthBuffer::operator=(const DepthBuffer&) = delete;

//VkDevice DepthBuffer::m_depthBufferVkDevice {VK_NULL_HANDLE};

//VkImageLayout DepthBuffer::m_depthBufferVkImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;

SwapchainImageContext::SwapchainImageContext(XrStructureType _swapchainImageType) : m_swapchainImageContextSwapchainImageType(_swapchainImageType)
{
}

// A packed array of XrSwapchainImageVulkan2KHR's for tableXr.EnumerateSwapchainImages
//std::vector<XrSwapchainImageVulkan2KHR> SwapchainImageContext::m_swapchainImageContextSwapchainImages;

//std::vector<RenderTarget> SwapchainImageContext::m_swapchainImageContextRenderTarget;

//VkExtent2D SwapchainImageContext::m_swapchainImageContextSize {};

//DepthBuffer SwapchainImageContext::m_swapchainImageContextDepthBuffer {};

//RenderPass SwapchainImageContext::m_swapchainImageContextRenderPass {};

//Pipeline SwapchainImageContext::m_swapchainImageContextPipe {};

//XrStructureType SwapchainImageContext::m_swapchainImageContextSwapchainImageType;

//SwapchainImageContext::SwapchainImageContext() = default;

std::vector<XrSwapchainImageBaseHeader*> SwapchainImageContext::SwapchainImageContextCreate(const VulkanDebugObjectNamer& namer, VkDevice device, MemoryAllocator* memAllocator, uint32_t capacity, const XrSwapchainCreateInfo& swapchainCreateInfo, const PipelineLayout& layout, const ShaderProgram& sp, const VertexBuffer<Geometry::Vertex>& vb)
{
  m_swapchainImageContextVkDevice = device;
  m_swapchainImageContextNamer = namer;

  m_swapchainImageContextSize = {swapchainCreateInfo.width, swapchainCreateInfo.height};
  VkFormat colorFormat = (VkFormat)swapchainCreateInfo.format;
  VkFormat depthFormat = VK_FORMAT_D32_SFLOAT;
  // XXX handle swapchainCreateInfo.sampleCount

  m_swapchainImageContextDepthBuffer.DepthBufferCreate(m_swapchainImageContextNamer, m_swapchainImageContextVkDevice, memAllocator, depthFormat, swapchainCreateInfo);
  m_swapchainImageContextRenderPass.RenderPassCreate(m_swapchainImageContextNamer, m_swapchainImageContextVkDevice, colorFormat, depthFormat);
  m_swapchainImageContextPipe.PipelineCreate(m_swapchainImageContextVkDevice, m_swapchainImageContextSize, layout, m_swapchainImageContextRenderPass, sp, vb);

  m_swapchainImageContextSwapchainImages.resize(capacity);
  m_swapchainImageContextRenderTarget.resize(capacity);

  std::vector<XrSwapchainImageBaseHeader*> bases(capacity);

  for(uint32_t i = 0; i < capacity; ++i)
  {
    m_swapchainImageContextSwapchainImages[i] = {m_swapchainImageContextSwapchainImageType};
    bases[i] = reinterpret_cast<XrSwapchainImageBaseHeader*>(&m_swapchainImageContextSwapchainImages[i] );
  }

  return bases;
}

uint32_t SwapchainImageContext::SwapchainImageContextImageIndex(const XrSwapchainImageBaseHeader* swapchainImageHeader)
{
  auto p = reinterpret_cast<const XrSwapchainImageVulkan2KHR*>(swapchainImageHeader);
  return (uint32_t)(p - &m_swapchainImageContextSwapchainImages[0] );
}

void SwapchainImageContext::SwapchainImageContextBindRenderTarget(uint32_t index, VkRenderPassBeginInfo* renderPassBeginInfo)
{
  if(m_swapchainImageContextRenderTarget[index].m_renderTargetFrameBuffer == VK_NULL_HANDLE)
    m_swapchainImageContextRenderTarget[index].RenderTargetCreate(m_swapchainImageContextNamer, m_swapchainImageContextVkDevice, m_swapchainImageContextSwapchainImages[index].image, m_swapchainImageContextDepthBuffer.m_depthBufferDepthImage, m_swapchainImageContextSize, m_swapchainImageContextRenderPass);

  renderPassBeginInfo->renderPass = m_swapchainImageContextRenderPass.m_renderPassPass;
  renderPassBeginInfo->framebuffer = m_swapchainImageContextRenderTarget[index].m_renderTargetFrameBuffer;
  renderPassBeginInfo->renderArea.offset = {0, 0};
  renderPassBeginInfo->renderArea.extent = m_swapchainImageContextSize;
}

//VkDevice SwapchainImageContext::m_swapchainImageContextVkDevice {VK_NULL_HANDLE};

//VulkanDebugObjectNamer SwapchainImageContext::m_swapchainImageContextNamer;

std::string VulkanGraphicsPlugin_BlahVkObjectTypeToString(VkObjectType objectType)
{
  std::string objName;

#define LIST_OBJECT_TYPES(_) \
_(UNKNOWN) \
_(INSTANCE) \
_(PHYSICAL_DEVICE) \
_(DEVICE) \
_(QUEUE) \
_(SEMAPHORE) \
_(COMMAND_BUFFER) \
_(FENCE) \
_(DEVICE_MEMORY) \
_(BUFFER) \
_(IMAGE) \
_(EVENT) \
_(QUERY_POOL) \
_(BUFFER_VIEW) \
_(IMAGE_VIEW) \
_(SHADER_MODULE) \
_(PIPELINE_CACHE) \
_(PIPELINE_LAYOUT) \
_(RENDER_PASS) \
_(PIPELINE) \
_(DESCRIPTOR_SET_LAYOUT) \
_(SAMPLER) \
_(DESCRIPTOR_POOL) \
_(DESCRIPTOR_SET) \
_(FRAMEBUFFER) \
_(COMMAND_POOL) \
_(SURFACE_KHR) \
_(SWAPCHAIN_KHR) \
_(DISPLAY_KHR) \
_(DISPLAY_MODE_KHR) \
_(DESCRIPTOR_UPDATE_TEMPLATE_KHR) \
_(DEBUG_UTILS_MESSENGER_EXT)

  switch(objectType)
  {

  default:
#define MK_OBJECT_TYPE_CASE(name) \
  case VK_OBJECT_TYPE_##name: \
    objName = #name; \
  break;

  LIST_OBJECT_TYPES(MK_OBJECT_TYPE_CASE)

  }

  return objName;
}

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanGraphicsPlugin_debugMessageThunk(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
  return static_cast<VulkanGraphicsPlugin*>(pUserData)->VulkanGraphicsPluginDebugMessage(messageSeverity, messageTypes, pCallbackData);
}

VulkanGraphicsPlugin::VulkanGraphicsPlugin(
  const std::shared_ptr<Options>& options,
  std::shared_ptr<AndroidPlatformPlugin> /*unused*/
) :
m_vulkanGraphicsPluginStdArray_float_4_clearColor(options->GetBackgroundClearColor() )
{
  m_vulkanGraphicsPluginXrGraphicsBindingVulkan2KHR.type = VulkanGraphicsPluginGetGraphicsBindingType();
}

std::vector<std::string> VulkanGraphicsPlugin::VulkanGraphicsPluginGetInstanceExtensions() const
{
  return {XR_KHR_VULKAN_ENABLE2_EXTENSION_NAME};
}

// note: The output must not outlive the input - this modifies the input and returns a collection of views into that modified input!
std::vector<const char*> VulkanGraphicsPlugin::VulkanGraphicsPluginParseExtensionString(char* names)
{
  std::vector<const char*> list;

  while(*names != 0)
  {
    list.push_back(names);

    while(*(++names) != 0)
    {
      if(*names == ' ')
      {
        *names++ = '\0';
        break;
      }
    }
  }

  return list;
}

const char* VulkanGraphicsPlugin::VulkanGraphicsPluginGetValidationLayerName()
{
  uint32_t layerCount;

  if(tableVk.EnumerateInstanceLayerProperties)
    tableVk.EnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);

  if(tableVk.EnumerateInstanceLayerProperties)
    tableVk.EnumerateInstanceLayerProperties(&layerCount, availableLayers.data() );

  std::vector<const char*> validationLayerNames;
  validationLayerNames.push_back("VK_LAYER_KHRONOS_validation");
  validationLayerNames.push_back("VK_LAYER_LUNARG_standard_validation");

  // Enable only one validation layer from the list above. Prefer KHRONOS.
  for(auto& validationLayerName : validationLayerNames)
  {
    for(const auto& layerProperties : availableLayers)
    {
      if(0 == strcmp(validationLayerName, layerProperties.layerName) )
        return validationLayerName;
    }
  }

  return nullptr;
}

void VulkanGraphicsPlugin::VulkanGraphicsPluginInitializeDevice(XrInstance instance, XrSystemId systemId)
{
  // Create the Vulkan device for the adapter associated with the system.
  // Extension function must be loaded by name
  XrGraphicsRequirementsVulkan2KHR graphicsRequirements {XR_TYPE_GRAPHICS_REQUIREMENTS_VULKAN2_KHR};

  CHECK_XRCMD(VulkanGraphicsPluginGetVulkanGraphicsRequirements2KHR(instance, systemId, &graphicsRequirements) );

  VkResult err = VK_ERROR_OUT_OF_HOST_MEMORY;

  std::vector<const char*> layers;

#if !defined(NDEBUG)
  const char* const validationLayerName = VulkanGraphicsPluginGetValidationLayerName();

  if(validationLayerName)
    layers.push_back(validationLayerName);
  else
    Log::Write(Log::Level::Warning, "No validation layers found in the system, skipping");
#endif

  std::vector<const char*> extensions;
  {
    uint32_t extensionCount = 0;

    if(tableVk.EnumerateInstanceExtensionProperties)
      CHECK_VKCMD(tableVk.EnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr) );

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);

    if(tableVk.EnumerateInstanceExtensionProperties)
      CHECK_VKCMD(tableVk.EnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data() ) );

    const auto b = availableExtensions.begin();
    const auto e = availableExtensions.end();

    auto isExtSupported = [&](const char* extName) -> bool
    {
      auto it = std::find_if(b, e, [&](const VkExtensionProperties& properties)
      {
        return (0 == strcmp(extName, properties.extensionName) );
      } );

      return (it != e);
    };

    // Debug utils is optional and not always available
    if(isExtSupported(VK_EXT_DEBUG_UTILS_EXTENSION_NAME) )
      extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    // TODO add back VK_EXT_debug_report code for compatibility with older systems? (Android)
  }

  VkDebugUtilsMessengerCreateInfoEXT debugInfo {VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT};

  debugInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;

#if !defined(NDEBUG)
  debugInfo.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;
#endif

  debugInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

  debugInfo.pfnUserCallback = VulkanGraphicsPlugin_debugMessageThunk;
  debugInfo.pUserData = this;

  VkApplicationInfo appInfo {VK_STRUCTURE_TYPE_APPLICATION_INFO};

  appInfo.pApplicationName = "helloxr";
  appInfo.applicationVersion = 1;
  appInfo.pEngineName = "helloxr";
  appInfo.engineVersion = 1;
  appInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo instInfo {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};

  instInfo.pNext = &debugInfo;
  instInfo.pApplicationInfo = &appInfo;
  instInfo.enabledLayerCount = (uint32_t)layers.size();
  instInfo.ppEnabledLayerNames = layers.empty() ? nullptr : layers.data();
  instInfo.enabledExtensionCount = (uint32_t)extensions.size();
  instInfo.ppEnabledExtensionNames = extensions.empty() ? nullptr : extensions.data();

  XrVulkanInstanceCreateInfoKHR createInfo {XR_TYPE_VULKAN_INSTANCE_CREATE_INFO_KHR};

  createInfo.systemId = systemId;

  createInfo.pfnGetInstanceProcAddr = tableVk.GetInstanceProcAddr;

  createInfo.vulkanCreateInfo = &instInfo;
  createInfo.vulkanAllocator = nullptr;

  CHECK_XRCMD(VulkanGraphicsPluginCreateVulkanInstanceKHR(instance, &createInfo, &m_vulkanGraphicsPluginVkInstance, &err) );
  CHECK_VKCMD(err);

  if(tableVk.GetInstanceProcAddr)
    m_vulkanGraphicsPluginVkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)tableVk.GetInstanceProcAddr(m_vulkanGraphicsPluginVkInstance, "vkCreateDebugUtilsMessengerEXT");

  if(m_vulkanGraphicsPluginVkCreateDebugUtilsMessengerEXT != nullptr && tableVk.CreateDebugUtilsMessengerEXT)
    CHECK_VKCMD(tableVk.CreateDebugUtilsMessengerEXT(m_vulkanGraphicsPluginVkInstance, &debugInfo, nullptr, &m_vulkanGraphicsPluginVkDebugUtilsMessenger) );

  XrVulkanGraphicsDeviceGetInfoKHR deviceGetInfo {XR_TYPE_VULKAN_GRAPHICS_DEVICE_GET_INFO_KHR};

  deviceGetInfo.systemId = systemId;
  deviceGetInfo.vulkanInstance = m_vulkanGraphicsPluginVkInstance;

  CHECK_XRCMD(VulkanGraphicsPluginGetVulkanGraphicsDevice2KHR(instance, &deviceGetInfo, &m_vulkanGraphicsPluginVkPhysicalDevice) );

  VkDeviceQueueCreateInfo queueInfo {VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO};

  float queuePriorities = 0;
  queueInfo.queueCount = 1;
  queueInfo.pQueuePriorities = &queuePriorities;

  uint32_t queueFamilyCount = 0;

  if(tableVk.GetPhysicalDeviceQueueFamilyProperties)
    tableVk.GetPhysicalDeviceQueueFamilyProperties(m_vulkanGraphicsPluginVkPhysicalDevice, &queueFamilyCount, nullptr);

  std::vector<VkQueueFamilyProperties> queueFamilyProps(queueFamilyCount);

  if(tableVk.GetPhysicalDeviceQueueFamilyProperties)
    tableVk.GetPhysicalDeviceQueueFamilyProperties(m_vulkanGraphicsPluginVkPhysicalDevice, &queueFamilyCount, &queueFamilyProps[0] );

  for(uint32_t i = 0; i < queueFamilyCount; ++i)
  {
    // Only need graphics (not presentation) for draw queue
    if(queueFamilyProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
    {
      m_vulkanGraphicsPluginQueueFamilyIndex = queueInfo.queueFamilyIndex = i;
      break;
    }
  }

  std::vector<const char*> deviceExtensions;

  VkPhysicalDeviceFeatures features {};
  // features.samplerAnisotropy = VK_TRUE;

  VkDeviceCreateInfo deviceInfo {VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO};
  deviceInfo.queueCreateInfoCount = 1;
  deviceInfo.pQueueCreateInfos = &queueInfo;
  deviceInfo.enabledLayerCount = 0;
  deviceInfo.ppEnabledLayerNames = nullptr;
  deviceInfo.enabledExtensionCount = (uint32_t)deviceExtensions.size();
  deviceInfo.ppEnabledExtensionNames = deviceExtensions.empty() ? nullptr : deviceExtensions.data();
  deviceInfo.pEnabledFeatures = &features;

  XrVulkanDeviceCreateInfoKHR deviceCreateInfo {XR_TYPE_VULKAN_DEVICE_CREATE_INFO_KHR};

  deviceCreateInfo.systemId = systemId;

  deviceCreateInfo.pfnGetInstanceProcAddr = tableVk.GetInstanceProcAddr;

  deviceCreateInfo.vulkanCreateInfo = &deviceInfo;
  deviceCreateInfo.vulkanPhysicalDevice = m_vulkanGraphicsPluginVkPhysicalDevice;
  deviceCreateInfo.vulkanAllocator = nullptr;

  CHECK_XRCMD(VulkanGraphicsPluginCreateVulkanDeviceKHR(instance, &deviceCreateInfo, &m_vulkanGraphicsPluginVkDevice, &err) );
  CHECK_VKCMD(err);

  m_vulkanGraphicsPluginVulkanDebugObjectNamer.Init(m_vulkanGraphicsPluginVkInstance, m_vulkanGraphicsPluginVkDevice);

  if(tableVk.GetDeviceQueue)
    tableVk.GetDeviceQueue(m_vulkanGraphicsPluginVkDevice, queueInfo.queueFamilyIndex, 0, &m_vulkanGraphicsPluginVkQueue);

  m_vulkanGraphicsPluginMemoryAllocator.MemoryAllocatorInit(m_vulkanGraphicsPluginVkPhysicalDevice, m_vulkanGraphicsPluginVkDevice);

  VulkanGraphicsPluginInitializeResources();

  m_vulkanGraphicsPluginXrGraphicsBindingVulkan2KHR.instance = m_vulkanGraphicsPluginVkInstance;
  m_vulkanGraphicsPluginXrGraphicsBindingVulkan2KHR.physicalDevice = m_vulkanGraphicsPluginVkPhysicalDevice;
  m_vulkanGraphicsPluginXrGraphicsBindingVulkan2KHR.device = m_vulkanGraphicsPluginVkDevice;
  m_vulkanGraphicsPluginXrGraphicsBindingVulkan2KHR.queueFamilyIndex = queueInfo.queueFamilyIndex;
  m_vulkanGraphicsPluginXrGraphicsBindingVulkan2KHR.queueIndex = 0;
}

// Compile a shader to a SPIR-V binary.
std::vector<uint32_t> VulkanGraphicsPlugin::VulkanGraphicsPluginCompileGlslShader(const std::string& name, shaderc_shader_kind kind, const std::string& source)
{
  shaderc::Compiler compiler;
  shaderc::CompileOptions options;

  options.SetOptimizationLevel(shaderc_optimization_level_size);

  shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, kind, name.c_str(), options);

  if(module.GetCompilationStatus() != shaderc_compilation_status_success)
  {
    Log::Write(Log::Level::Error, Fmt("Shader %s compilation failed: %s", name.c_str(), module.GetErrorMessage().c_str() ) );

    return std::vector<uint32_t>();
  }

  return {module.cbegin(), module.cend() };
}

void VulkanGraphicsPlugin::VulkanGraphicsPluginInitializeResources()
{
  auto vertexSPIRV = VulkanGraphicsPluginCompileGlslShader("vertex", shaderc_glsl_default_vertex_shader, VertexShaderGlsl);
  auto fragmentSPIRV = VulkanGraphicsPluginCompileGlslShader("fragment", shaderc_glsl_default_fragment_shader, FragmentShaderGlsl);

  if(vertexSPIRV.empty() ) THROW("Failed to compile vertex shader");

  if(fragmentSPIRV.empty() ) THROW("Failed to compile fragment shader");

  m_vulkanGraphicsPluginShaderProgram.ShaderProgramInit(m_vulkanGraphicsPluginVkDevice);
  m_vulkanGraphicsPluginShaderProgram.ShaderProgramLoadVertexShader(vertexSPIRV);
  m_vulkanGraphicsPluginShaderProgram.ShaderProgramLoadFragmentShader(fragmentSPIRV);

  // Semaphore to block on draw complete
  VkSemaphoreCreateInfo semInfo {VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};

  if(tableVk.CreateSemaphore)
    CHECK_VKCMD(tableVk.CreateSemaphore(m_vulkanGraphicsPluginVkDevice, &semInfo, nullptr, &m_vulkanGraphicsPluginVkSemaphoreDrawDone) );

  CHECK_VKCMD(m_vulkanGraphicsPluginVulkanDebugObjectNamer.SetName(VK_OBJECT_TYPE_SEMAPHORE, (uint64_t)m_vulkanGraphicsPluginVkSemaphoreDrawDone, "helloxr draw done semaphore") );

  if(!m_vulkanGraphicsPluginCmdBuffer.CmdBufferInit(m_vulkanGraphicsPluginVulkanDebugObjectNamer, m_vulkanGraphicsPluginVkDevice, m_vulkanGraphicsPluginQueueFamilyIndex) ) THROW("Failed to create command buffer");

  m_vulkanGraphicsPluginPipelineLayout.PipelineLayoutCreate(m_vulkanGraphicsPluginVkDevice);

  static_assert(sizeof(Geometry::Vertex) == 24, "Unexpected Vertex size");

  m_vulkanGraphicsPluginVertexBuffer_GeometryVertex_DrawBuffer.VertexBufferBaseInit(m_vulkanGraphicsPluginVkDevice, &m_vulkanGraphicsPluginMemoryAllocator, { {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Geometry::Vertex, Position) }, {1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Geometry::Vertex, Color) } } );

  uint32_t numCubeIdicies = sizeof(Geometry::c_cubeIndices) / sizeof(Geometry::c_cubeIndices[0] );
  uint32_t numCubeVerticies = sizeof(Geometry::c_cubeVertices) / sizeof(Geometry::c_cubeVertices[0] );

  m_vulkanGraphicsPluginVertexBuffer_GeometryVertex_DrawBuffer.VertexBufferCreate(numCubeIdicies, numCubeVerticies);
  m_vulkanGraphicsPluginVertexBuffer_GeometryVertex_DrawBuffer.VertexBufferUpdateIndices(Geometry::c_cubeIndices, numCubeIdicies, 0);
  m_vulkanGraphicsPluginVertexBuffer_GeometryVertex_DrawBuffer.VertexBufferUpdateVertices(Geometry::c_cubeVertices, numCubeVerticies, 0);
}

int64_t VulkanGraphicsPlugin::VulkanGraphicsPluginSelectColorSwapchainFormat(const std::vector<int64_t>& runtimeFormats) const
{
  // List of supported color swapchain formats.
  constexpr int64_t SupportedColorSwapchainFormats[] = {VK_FORMAT_B8G8R8A8_SRGB, VK_FORMAT_R8G8B8A8_SRGB, VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R8G8B8A8_UNORM};

  auto swapchainFormatIt = std::find_first_of(runtimeFormats.begin(), runtimeFormats.end(), std::begin(SupportedColorSwapchainFormats), std::end(SupportedColorSwapchainFormats) );

  if(swapchainFormatIt == runtimeFormats.end() )
    THROW("No runtime swapchain format supported for color swapchain");

  return *swapchainFormatIt;
}

const XrBaseInStructure* VulkanGraphicsPlugin::VulkanGraphicsPluginGetGraphicsBinding() const
{
  return reinterpret_cast<const XrBaseInStructure*>(&m_vulkanGraphicsPluginXrGraphicsBindingVulkan2KHR);
}

std::vector<XrSwapchainImageBaseHeader*> VulkanGraphicsPlugin::VulkanGraphicsPluginAllocateSwapchainImageStructs(uint32_t capacity, const XrSwapchainCreateInfo& swapchainCreateInfo)
{
  // Allocate and initialize the buffer of image structs (must be sequential in memory for xrEnumerateSwapchainImages).
  // Return back an array of pointers to each swapchain image struct so the consumer doesn't need to know the type/size.
  // Keep the buffer alive by adding it into the list of buffers.
  m_vulkanGraphicsPluginStdList_SwapchainImageContext.emplace_back(VulkanGraphicsPluginGetSwapchainImageType() );
  SwapchainImageContext& swapchainImageContext = m_vulkanGraphicsPluginStdList_SwapchainImageContext.back();

  std::vector<XrSwapchainImageBaseHeader*> bases = swapchainImageContext.SwapchainImageContextCreate(m_vulkanGraphicsPluginVulkanDebugObjectNamer, m_vulkanGraphicsPluginVkDevice, &m_vulkanGraphicsPluginMemoryAllocator, capacity, swapchainCreateInfo, m_vulkanGraphicsPluginPipelineLayout, m_vulkanGraphicsPluginShaderProgram, m_vulkanGraphicsPluginVertexBuffer_GeometryVertex_DrawBuffer);

  // Map every swapchainImage base pointer to this context
  for(auto& base : bases)
    m_vulkanGraphicsPluginStdMap_XrSwapchainImageBaseHeader_SwapchainImageContext[base] = &swapchainImageContext;

  return bases;
}

void VulkanGraphicsPlugin::VulkanGraphicsPluginRenderView(const XrCompositionLayerProjectionView& layerView, const XrSwapchainImageBaseHeader* swapchainImage, int64_t /*swapchainFormat*/, const std::vector<Cube>& cubes)
{
  CHECK(layerView.subImage.imageArrayIndex == 0);  // Texture arrays not supported.

  auto swapchainContext = m_vulkanGraphicsPluginStdMap_XrSwapchainImageBaseHeader_SwapchainImageContext[swapchainImage];
  uint32_t imageIndex = swapchainContext->SwapchainImageContextImageIndex(swapchainImage);

  // XXX Should double-buffer the command buffers, for now just flush
  m_vulkanGraphicsPluginCmdBuffer.CmdBufferWait();
  m_vulkanGraphicsPluginCmdBuffer.CmdBufferReset();
  m_vulkanGraphicsPluginCmdBuffer.CmdBufferBegin();

  // Ensure depth is in the right layout
  swapchainContext->m_swapchainImageContextDepthBuffer.DepthBufferTransitionImageLayout(&m_vulkanGraphicsPluginCmdBuffer, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);

  // Bind and clear eye render target
  static std::array<VkClearValue, 2> clearValues;

  clearValues[0].color.float32[0] = m_vulkanGraphicsPluginStdArray_float_4_clearColor[0];
  clearValues[0].color.float32[1] = m_vulkanGraphicsPluginStdArray_float_4_clearColor[1];
  clearValues[0].color.float32[2] = m_vulkanGraphicsPluginStdArray_float_4_clearColor[2];
  clearValues[0].color.float32[3] = m_vulkanGraphicsPluginStdArray_float_4_clearColor[3];
  clearValues[1].depthStencil.depth = 1.0f;
  clearValues[1].depthStencil.stencil = 0;

  VkRenderPassBeginInfo renderPassBeginInfo {VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};

  renderPassBeginInfo.clearValueCount = (uint32_t)clearValues.size();
  renderPassBeginInfo.pClearValues = clearValues.data();

  swapchainContext->SwapchainImageContextBindRenderTarget(imageIndex, &renderPassBeginInfo);

  if(tableVk.CmdBeginRenderPass)
    tableVk.CmdBeginRenderPass(m_vulkanGraphicsPluginCmdBuffer.m_cmdBufferBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

  if(tableVk.CmdBindPipeline)
    tableVk.CmdBindPipeline(m_vulkanGraphicsPluginCmdBuffer.m_cmdBufferBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, swapchainContext->m_swapchainImageContextPipe.m_pipelinePipe);

  // Bind index and vertex buffers
  if(tableVk.CmdBindIndexBuffer)
    tableVk.CmdBindIndexBuffer(m_vulkanGraphicsPluginCmdBuffer.m_cmdBufferBuffer, m_vulkanGraphicsPluginVertexBuffer_GeometryVertex_DrawBuffer.m_vertexBufferBaseIdxBuf, 0, VK_INDEX_TYPE_UINT16);

  VkDeviceSize offset = 0;

  if(tableVk.CmdBindVertexBuffers)
    tableVk.CmdBindVertexBuffers(m_vulkanGraphicsPluginCmdBuffer.m_cmdBufferBuffer, 0, 1, &m_vulkanGraphicsPluginVertexBuffer_GeometryVertex_DrawBuffer.m_vertexBufferBaseVtxBuf, &offset);

  // Compute the view-projection transform.
  // Note all matrixes (including OpenXR's) are column-major, right-handed.
  const auto& pose = layerView.pose;

  XrMatrix4x4f proj;
  XrMatrix4x4f_CreateProjectionFov(&proj, GRAPHICS_VULKAN, layerView.fov, 0.05f, 100.0f);

  XrMatrix4x4f toView;
  XrMatrix4x4f_CreateFromRigidTransform(&toView, &pose);

  XrMatrix4x4f view;
  XrMatrix4x4f_InvertRigidBody(&view, &toView);

  XrMatrix4x4f vp;
  XrMatrix4x4f_Multiply(&vp, &proj, &view);

  // Render each cube
  for(const Cube& cube : cubes)
  {
    // Compute the model-view-projection transform and push it.
    XrMatrix4x4f model;
    XrMatrix4x4f_CreateTranslationRotationScale(&model, &cube.Pose.position, &cube.Pose.orientation, &cube.Scale);

    XrMatrix4x4f mvp;
    XrMatrix4x4f_Multiply(&mvp, &vp, &model);

    if(tableVk.CmdPushConstants)
      tableVk.CmdPushConstants(m_vulkanGraphicsPluginCmdBuffer.m_cmdBufferBuffer, m_vulkanGraphicsPluginPipelineLayout.m_pipelineLayoutLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(mvp.m), &mvp.m[0] );

    // draw the cube
    if(tableVk.CmdDrawIndexed)
      tableVk.CmdDrawIndexed(m_vulkanGraphicsPluginCmdBuffer.m_cmdBufferBuffer, m_vulkanGraphicsPluginVertexBuffer_GeometryVertex_DrawBuffer.m_vertexBufferBaseCount.idx, 1, 0, 0, 0);
  }

  if(tableVk.CmdEndRenderPass)
    tableVk.CmdEndRenderPass(m_vulkanGraphicsPluginCmdBuffer.m_cmdBufferBuffer);

  m_vulkanGraphicsPluginCmdBuffer.CmdBufferEnd();
  m_vulkanGraphicsPluginCmdBuffer.CmdBufferExec(m_vulkanGraphicsPluginVkQueue);
}

uint32_t VulkanGraphicsPlugin::VulkanGraphicsPluginGetSupportedSwapchainSampleCount(const XrViewConfigurationView&)
{
  return VK_SAMPLE_COUNT_1_BIT;
}

void VulkanGraphicsPlugin::VulkanGraphicsPluginUpdateOptions(const std::shared_ptr<Options>& options)
{
  m_vulkanGraphicsPluginStdArray_float_4_clearColor = options->GetBackgroundClearColor();
}

//XrGraphicsBindingVulkan2KHR VulkanGraphicsPlugin::m_vulkanGraphicsPluginXrGraphicsBindingVulkan2KHR {XR_TYPE_GRAPHICS_BINDING_VULKAN2_KHR};

//std::list<SwapchainImageContext> VulkanGraphicsPlugin::m_vulkanGraphicsPluginStdList_SwapchainImageContext;

//std::map<const XrSwapchainImageBaseHeader*, SwapchainImageContext*> VulkanGraphicsPlugin::m_vulkanGraphicsPluginStdMap_XrSwapchainImageBaseHeader_SwapchainImageContext;

//VkInstance VulkanGraphicsPlugin::m_vulkanGraphicsPluginVkInstance {VK_NULL_HANDLE};

//VkPhysicalDevice VulkanGraphicsPlugin::m_vulkanGraphicsPluginVkPhysicalDevice {VK_NULL_HANDLE};

//VkDevice VulkanGraphicsPlugin::m_vulkanGraphicsPluginVkDevice {VK_NULL_HANDLE};

//VulkanDebugObjectNamer VulkanGraphicsPlugin::m_vulkanGraphicsPluginVulkanDebugObjectNamer {};

//uint32_t VulkanGraphicsPlugin::m_vulkanGraphicsPluginQueueFamilyIndex = 0;

//VkQueue VulkanGraphicsPlugin::m_vulkanGraphicsPluginVkQueue {VK_NULL_HANDLE};

//VkSemaphore VulkanGraphicsPlugin::m_vulkanGraphicsPluginVkSemaphoreDrawDone {VK_NULL_HANDLE};

//MemoryAllocator VulkanGraphicsPlugin::m_vulkanGraphicsPluginMemoryAllocator {};

//ShaderProgram VulkanGraphicsPlugin::m_vulkanGraphicsPluginShaderProgram {};

//CmdBuffer VulkanGraphicsPlugin::m_vulkanGraphicsPluginCmdBuffer {};

//PipelineLayout VulkanGraphicsPlugin::m_vulkanGraphicsPluginPipelineLayout {};

//VertexBuffer<Geometry::Vertex> VulkanGraphicsPlugin::m_vulkanGraphicsPluginVertexBuffer_GeometryVertex_DrawBuffer {};

//std::array<float, 4> VulkanGraphicsPlugin::m_vulkanGraphicsPluginStdArray_float_4_clearColor;

//PFN_vkCreateDebugUtilsMessengerEXT VulkanGraphicsPlugin::m_vulkanGraphicsPluginVkCreateDebugUtilsMessengerEXT {nullptr};

//VkDebugUtilsMessengerEXT VulkanGraphicsPlugin::m_vulkanGraphicsPluginVkDebugUtilsMessenger {VK_NULL_HANDLE};

VkBool32 VulkanGraphicsPlugin::VulkanGraphicsPluginDebugMessage(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData)
{
  std::string flagNames;
  std::string objName;
  Log::Level level = Log::Level::Error;

  if( (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) != 0u)
  {
    flagNames += "DEBUG:";
    level = Log::Level::Verbose;
  }

  if( (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) != 0u)
  {
    flagNames += "INFO:";
    level = Log::Level::Info;
  }

  if( (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) != 0u)
  {
    flagNames += "WARN:";
    level = Log::Level::Warning;
  }

  if( (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) != 0u)
  {
    flagNames += "ERROR:";
    level = Log::Level::Error;
  }

  if( (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) != 0u)
  {
    flagNames += "PERF:";
    level = Log::Level::Warning;
  }

  uint64_t object = 0;

  // skip loader messages about device extensions
  if(pCallbackData->objectCount > 0)
  {
    auto objectType = pCallbackData->pObjects[0].objectType;

    if( (objectType == VK_OBJECT_TYPE_INSTANCE) && (strncmp(pCallbackData->pMessage, "Device Extension:", 17) == 0) )
      return VK_FALSE;

    objName = VulkanGraphicsPlugin_BlahVkObjectTypeToString(objectType);
    object = pCallbackData->pObjects[0].objectHandle;

    if(pCallbackData->pObjects[0].pObjectName != nullptr)
      objName += " " + std::string(pCallbackData->pObjects[0].pObjectName);
  }

  Log::Write(level, Fmt("%s (%s 0x%llx) %s", flagNames.c_str(), objName.c_str(), object, pCallbackData->pMessage) );

  return VK_FALSE;
}

XrStructureType VulkanGraphicsPlugin::VulkanGraphicsPluginGetGraphicsBindingType() const
{
  return XR_TYPE_GRAPHICS_BINDING_VULKAN2_KHR;
}

XrStructureType VulkanGraphicsPlugin::VulkanGraphicsPluginGetSwapchainImageType() const
{
  return XR_TYPE_SWAPCHAIN_IMAGE_VULKAN2_KHR;
}

XrResult VulkanGraphicsPlugin::VulkanGraphicsPluginCreateVulkanInstanceKHR(XrInstance instance, const XrVulkanInstanceCreateInfoKHR* createInfo, VkInstance* vulkanInstance, VkResult* vulkanResult)
{
  PFN_xrCreateVulkanInstanceKHR pfnCreateVulkanInstanceKHR = nullptr;
  XrResult result = XR_ERROR_VALIDATION_FAILURE;

  InitOpenXr();

  if(tableXr.GetInstanceProcAddr)
  {
    result = tableXr.GetInstanceProcAddr(instance, "xrCreateVulkanInstanceKHR", reinterpret_cast<PFN_xrVoidFunction*>( &pfnCreateVulkanInstanceKHR) );
    CHECK_XRCMD(result);
  }

  if(pfnCreateVulkanInstanceKHR)
    result = pfnCreateVulkanInstanceKHR(instance, createInfo, vulkanInstance, vulkanResult);

  return result;
}

XrResult VulkanGraphicsPlugin::VulkanGraphicsPluginCreateVulkanDeviceKHR(XrInstance instance, const XrVulkanDeviceCreateInfoKHR* createInfo, VkDevice* vulkanDevice, VkResult* vulkanResult)
{
  PFN_xrCreateVulkanDeviceKHR pfnCreateVulkanDeviceKHR = nullptr;
  XrResult result = XR_ERROR_VALIDATION_FAILURE;

  InitOpenXr();

  if(tableXr.GetInstanceProcAddr)
  {
    result = tableXr.GetInstanceProcAddr(instance, "xrCreateVulkanDeviceKHR", reinterpret_cast<PFN_xrVoidFunction*>( &pfnCreateVulkanDeviceKHR) );
    CHECK_XRCMD(result);
  }

  if(pfnCreateVulkanDeviceKHR)
    result = pfnCreateVulkanDeviceKHR(instance, createInfo, vulkanDevice, vulkanResult);

  return result;
}

XrResult VulkanGraphicsPlugin::VulkanGraphicsPluginGetVulkanGraphicsDevice2KHR(XrInstance instance, const XrVulkanGraphicsDeviceGetInfoKHR* getInfo, VkPhysicalDevice* vulkanPhysicalDevice)
{
  PFN_xrGetVulkanGraphicsDevice2KHR pfnGetVulkanGraphicsDevice2KHR = nullptr;
  XrResult result = XR_ERROR_VALIDATION_FAILURE;

  InitOpenXr();

  if(tableXr.GetInstanceProcAddr)
  {
    result = tableXr.GetInstanceProcAddr(instance, "xrGetVulkanGraphicsDevice2KHR", reinterpret_cast<PFN_xrVoidFunction*>( &pfnGetVulkanGraphicsDevice2KHR) );
    CHECK_XRCMD(result);
  }

  if(pfnGetVulkanGraphicsDevice2KHR)
    result = pfnGetVulkanGraphicsDevice2KHR(instance, getInfo, vulkanPhysicalDevice);

  return result;
}

XrResult VulkanGraphicsPlugin::VulkanGraphicsPluginGetVulkanGraphicsRequirements2KHR(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkan2KHR* graphicsRequirements)
{
  PFN_xrGetVulkanGraphicsRequirements2KHR pfnGetVulkanGraphicsRequirements2KHR = nullptr;
  XrResult result = XR_ERROR_VALIDATION_FAILURE;

  InitOpenXr();

  if(tableXr.GetInstanceProcAddr)
  {
    result = tableXr.GetInstanceProcAddr(instance, "xrGetVulkanGraphicsRequirements2KHR", reinterpret_cast<PFN_xrVoidFunction*>( &pfnGetVulkanGraphicsRequirements2KHR) );
    CHECK_XRCMD(result);
  }

  if(pfnGetVulkanGraphicsRequirements2KHR)
    result = pfnGetVulkanGraphicsRequirements2KHR(instance, systemId, graphicsRequirements);

  return result;
}

std::shared_ptr<VulkanGraphicsPlugin> VulkanGraphicsPlugin_CreateGraphicsPlugin_Vulkan(const std::shared_ptr<Options>& options, std::shared_ptr<AndroidPlatformPlugin> platformPlugin)
{
  return std::make_shared<VulkanGraphicsPlugin>(options, std::move(platformPlugin) );
}
