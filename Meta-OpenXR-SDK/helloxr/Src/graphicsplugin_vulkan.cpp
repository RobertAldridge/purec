
// graphicsplugin_vulkan.cpp

#include "header.h"

VkInstance gVkInstance = VK_NULL_HANDLE;

VkDevice gVkDevice = VK_NULL_HANDLE;

VkPhysicalDevice gVkPhysicalDevice = VK_NULL_HANDLE;

VkPipelineLayout gVkPipelineLayout = VK_NULL_HANDLE;

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

bool VulkanTutorialQueueFamilyIndices_isComplete(VulkanTutorialQueueFamilyIndices _this)
{
  return _this.graphicsFamily.has_value() && _this.presentFamily.has_value();
}

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

uint32_t VulkanTutorialFindMemoryType(
  VkPhysicalDevice& physicalDevice,
  uint32_t typeFilter,
  VkMemoryPropertyFlags properties
)
{
  VkPhysicalDeviceMemoryProperties memProperties;
  tableVk.GetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

  for(uint32_t offset = 0; offset < memProperties.memoryTypeCount; offset++)
  {
    if( (typeFilter & (1 << offset) ) && (memProperties.memoryTypes[offset].propertyFlags & properties) == properties)
      return offset;
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
  return VulkanTutorialFindSupportedFormat(physicalDevice, VulkanTutorialDepthFormatCandidates, VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
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

  int family = 0;
  for(const auto& queueFamily : queueFamilies)
  {
    if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
      indices.graphicsFamily = family;

    VkBool32 presentSupport = false;
    tableVk.GetPhysicalDeviceSurfaceSupportKHR(physicalDevice, family, surface, &presentSupport);

    if(presentSupport)
      indices.presentFamily = family;

    if(VulkanTutorialQueueFamilyIndices_isComplete(indices) )
      break;

    family++;
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

  return VulkanTutorialQueueFamilyIndices_isComplete(indices) && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
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
  colorBlending.blendConstants = 0.0f;

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
  ThrowCheck(Fmt("VkResult failure [%s]", BlahVkResultString(res).c_str() ), originator, sourceLocation);
}

inline VkResult CheckVkResult(VkResult res, const char* originator = nullptr, const char* sourceLocation = nullptr)
{
  if( (res) < VK_SUCCESS)
    ThrowVkResult(res, originator, sourceLocation);

  return res;
}

void PipelineLayout_PipelineLayoutCreate(VkDevice device)
{
  // MVP matrix is a push_constant
  VkPushConstantRange pcr = {};
  pcr.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  pcr.offset = 0;
  pcr.size = 4 * 4 * sizeof(float);

  VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo {VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO};

  pipelineLayoutCreateInfo.pushConstantRangeCount = 1;
  pipelineLayoutCreateInfo.pPushConstantRanges = &pcr;

  if(tableVk.CreatePipelineLayout)
    CHECK_VKCMD(tableVk.CreatePipelineLayout(gVkDevice, &pipelineLayoutCreateInfo, nullptr, &gVkPipelineLayout) );
}

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

VkPhysicalDeviceMemoryProperties gMemoryAllocatorMemoryProperties {};

void MemoryAllocator_MemoryAllocatorInit(VkPhysicalDevice physicalDevice)
{
  if(tableVk.GetPhysicalDeviceMemoryProperties)
    tableVk.GetPhysicalDeviceMemoryProperties(physicalDevice, &gMemoryAllocatorMemoryProperties);
}

void MemoryAllocator_MemoryAllocatorAllocate(VkMemoryRequirements const& memReqs, VkDeviceMemory* mem, VkFlags flags, void* pNext)
{
  // Search memtypes to find first offset with those properties
  for(uint32_t offset = 0; offset < gMemoryAllocatorMemoryProperties.memoryTypeCount; offset++)
  {
    if(memReqs.memoryTypeBits & (1 << offset) )
    {
      // Type is available, does it match user properties?
      if( (gMemoryAllocatorMemoryProperties.memoryTypes[offset].propertyFlags & flags) == flags)
      {
        VkMemoryAllocateInfo memAlloc {VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, pNext};

        memAlloc.allocationSize = memReqs.size;
        memAlloc.memoryTypeIndex = offset;

        if(tableVk.AllocateMemory)
          CHECK_VKCMD(tableVk.AllocateMemory(gVkDevice, &memAlloc, nullptr, mem) );

        return;
      }
    }
  }

  THROW_CHECK("Memory format not supported");
}

CmdBufferStateEnum gCmdBufferState {CmdBufferStateEnum::Undefined};

VkCommandPool gCmdBufferPool {VK_NULL_HANDLE};

VkCommandBuffer gCmdBufferBuffer {VK_NULL_HANDLE};

VkFence gCmdBufferExecFence {VK_NULL_HANDLE};

void CmdBuffer_CmdBufferSetState(CmdBufferStateEnum newState)
{
  gCmdBufferState = newState;
}

#if 0
void CmdBuffer_CmdBuffer_Destructor()
{
  CmdBuffer_CmdBufferSetState(CmdBufferStateEnum::Undefined);

  if(gVkDevice)
  {
    if(gCmdBufferBuffer != VK_NULL_HANDLE && tableVk.FreeCommandBuffers)
      tableVk.FreeCommandBuffers(gVkDevice, gCmdBufferPool, 1, &gCmdBufferBuffer);

    if(gCmdBufferPool != VK_NULL_HANDLE && tableVk.DestroyCommandPool)
      tableVk.DestroyCommandPool(gVkDevice, gCmdBufferPool, nullptr);

    if(gCmdBufferExecFence != VK_NULL_HANDLE && tableVk.DestroyFence)
      tableVk.DestroyFence(gVkDevice, gCmdBufferExecFence, nullptr);
  }

  gCmdBufferBuffer = VK_NULL_HANDLE;
  gCmdBufferPool = VK_NULL_HANDLE;
  gCmdBufferExecFence = VK_NULL_HANDLE;
}
#endif

std::string CmdBuffer_CmdBufferStateString(CmdBufferStateEnum s)
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

bool CmdBuffer_CmdBufferInit(const VulkanDebugObjectNamer& namer, VkDevice device, uint32_t queueFamilyIndex)
{
  CHECK_CBSTATE(CmdBufferStateEnum::Undefined);

  // Create a command pool to allocate our command buffer from
  VkCommandPoolCreateInfo cmdPoolInfo {VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO};
  cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  cmdPoolInfo.queueFamilyIndex = queueFamilyIndex;

  if(tableVk.CreateCommandPool)
    CHECK_VKCMD(tableVk.CreateCommandPool(gVkDevice, &cmdPoolInfo, nullptr, &gCmdBufferPool) );

  CHECK_VKCMD(namer.SetName(VK_OBJECT_TYPE_COMMAND_POOL, (uint64_t)gCmdBufferPool, "helloxr command pool") );

  // Create the command buffer from the command pool
  VkCommandBufferAllocateInfo cmd {VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO};
  cmd.commandPool = gCmdBufferPool;
  cmd.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  cmd.commandBufferCount = 1;

  if(tableVk.AllocateCommandBuffers)
    CHECK_VKCMD(tableVk.AllocateCommandBuffers(gVkDevice, &cmd, &gCmdBufferBuffer) );

  CHECK_VKCMD(namer.SetName(VK_OBJECT_TYPE_COMMAND_BUFFER, (uint64_t)gCmdBufferBuffer, "helloxr command buffer") );

  VkFenceCreateInfo fenceInfo {VK_STRUCTURE_TYPE_FENCE_CREATE_INFO};

  if(tableVk.CreateFence)
    CHECK_VKCMD(tableVk.CreateFence(gVkDevice, &fenceInfo, nullptr, &gCmdBufferExecFence) );

  CHECK_VKCMD(namer.SetName(VK_OBJECT_TYPE_FENCE, (uint64_t)gCmdBufferExecFence, "helloxr fence") );

  CmdBuffer_CmdBufferSetState(CmdBufferStateEnum::Initialized);

  return true;
}

bool CmdBuffer_CmdBufferBegin()
{
  CHECK_CBSTATE(CmdBufferStateEnum::Initialized);

  VkCommandBufferBeginInfo cmdBeginInfo {VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};

  if(tableVk.BeginCommandBuffer)
    CHECK_VKCMD(tableVk.BeginCommandBuffer(gCmdBufferBuffer, &cmdBeginInfo) );

  CmdBuffer_CmdBufferSetState(CmdBufferStateEnum::Recording);

  return true;
}

bool CmdBuffer_CmdBufferEnd()
{
  CHECK_CBSTATE(CmdBufferStateEnum::Recording);

  if(tableVk.EndCommandBuffer)
    CHECK_VKCMD(tableVk.EndCommandBuffer(gCmdBufferBuffer) );

  CmdBuffer_CmdBufferSetState(CmdBufferStateEnum::Executable);

  return true;
}

bool CmdBuffer_CmdBufferExec(VkQueue queue)
{
  CHECK_CBSTATE(CmdBufferStateEnum::Executable);

  VkSubmitInfo submitInfo {VK_STRUCTURE_TYPE_SUBMIT_INFO};

  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &gCmdBufferBuffer;

  if(tableVk.QueueSubmit)
    CHECK_VKCMD(tableVk.QueueSubmit(queue, 1, &submitInfo, gCmdBufferExecFence) );

  CmdBuffer_CmdBufferSetState(CmdBufferStateEnum::Executing);

  return true;
}

bool CmdBuffer_CmdBufferWait()
{
  // Waiting on a not-in-flight command buffer is a no-op
  if(gCmdBufferState == CmdBufferStateEnum::Initialized)
    return true;

  CHECK_CBSTATE(CmdBufferStateEnum::Executing);

  const uint32_t timeoutNs = 1 * 1000 * 1000 * 1000;

  for(int i = 0; i < 5; ++i)
  {
    VkResult res = VK_ERROR_OUT_OF_HOST_MEMORY;

    if(tableVk.WaitForFences)
      res = tableVk.WaitForFences(gVkDevice, 1, &gCmdBufferExecFence, VK_TRUE, timeoutNs);

    if(res == VK_SUCCESS)
    {
      // Buffer can be executed multiple times...
      CmdBuffer_CmdBufferSetState(CmdBufferStateEnum::Executable);
      return true;
    }

    Log::Write(Log::Level::Info, "Waiting for CmdBuffer fence timed out, retrying...");
  }

  return false;
}

bool CmdBuffer_CmdBufferReset()
{
  if(gCmdBufferState != CmdBufferStateEnum::Initialized)
  {
    CHECK_CBSTATE(CmdBufferStateEnum::Executable);

    if(tableVk.ResetFences)
      CHECK_VKCMD(tableVk.ResetFences(gVkDevice, 1, &gCmdBufferExecFence) );

    if(tableVk.ResetCommandBuffer)
      CHECK_VKCMD(tableVk.ResetCommandBuffer(gCmdBufferBuffer, 0) );

    CmdBuffer_CmdBufferSetState(CmdBufferStateEnum::Initialized);
  }

  return true;
}

VkBuffer gVertexBufferBaseIdxBuf {VK_NULL_HANDLE};

VkDeviceMemory gVertexBufferBaseIdxMem {VK_NULL_HANDLE};

VkBuffer gVertexBufferBaseVtxBuf {VK_NULL_HANDLE};

VkDeviceMemory gVertexBufferBaseVtxMem {VK_NULL_HANDLE};

VkVertexInputBindingDescription gVertexBufferBaseBindDesc {};

std::vector<VkVertexInputAttributeDescription> gVertexBufferBaseAttrDesc {};

VertexBufferBaseBlah gVertexBufferBaseCount = {0, 0};

#if 0
void VertexBufferBase_VertexBufferBase_Destructor()
{
  if(gVkDevice)
  {
    if(gVertexBufferBaseIdxBuf != VK_NULL_HANDLE && tableVk.DestroyBuffer)
      tableVk.DestroyBuffer(gVkDevice, gVertexBufferBaseIdxBuf, nullptr);

    if(gVertexBufferBaseIdxMem != VK_NULL_HANDLE && tableVk.FreeMemory)
      tableVk.FreeMemory(gVkDevice, gVertexBufferBaseIdxMem, nullptr);

    if(gVertexBufferBaseVtxBuf != VK_NULL_HANDLE && tableVk.DestroyBuffer)
      tableVk.DestroyBuffer(gVkDevice, gVertexBufferBaseVtxBuf, nullptr);

    if(gVertexBufferBaseVtxMem != VK_NULL_HANDLE && tableVk.FreeMemory)
      tableVk.FreeMemory(gVkDevice, gVertexBufferBaseVtxMem, nullptr);
  }

  gVertexBufferBaseIdxBuf = VK_NULL_HANDLE;
  gVertexBufferBaseIdxMem = VK_NULL_HANDLE;
  gVertexBufferBaseVtxBuf = VK_NULL_HANDLE;
  gVertexBufferBaseVtxMem = VK_NULL_HANDLE;

  gVertexBufferBaseBindDesc = {};
  gVertexBufferBaseAttrDesc.clear();
  gVertexBufferBaseCount = {0, 0};
}
#endif

void VertexBufferBase_VertexBufferBaseInit(const std::vector<VkVertexInputAttributeDescription>& attr)
{
  gVertexBufferBaseAttrDesc = attr;
}

void VertexBufferBase_VertexBufferBaseAllocateBufferMemory(VkBuffer buf, VkDeviceMemory* mem)
{
  VkMemoryRequirements memReq = {};

  if(tableVk.GetBufferMemoryRequirements)
    tableVk.GetBufferMemoryRequirements(gVkDevice, buf, &memReq);

  MemoryAllocator_MemoryAllocatorAllocate(memReq, mem);
}

bool VertexBuffer_VertexBufferCreate(uint32_t idxCount, uint32_t vtxCount)
{
  VkBufferCreateInfo bufInfo {VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO};

  bufInfo.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
  bufInfo.size = sizeof(uint16_t) * idxCount;

  if(tableVk.CreateBuffer)
    CHECK_VKCMD(tableVk.CreateBuffer(gVkDevice, &bufInfo, nullptr, &gVertexBufferBaseIdxBuf) );

  VertexBufferBase_VertexBufferBaseAllocateBufferMemory(gVertexBufferBaseIdxBuf, &gVertexBufferBaseIdxMem);

  if(tableVk.BindBufferMemory)
    CHECK_VKCMD(tableVk.BindBufferMemory(gVkDevice, gVertexBufferBaseIdxBuf, gVertexBufferBaseIdxMem, 0) );

  bufInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
  bufInfo.size = sizeof(Geometry::Vertex) * vtxCount;

  if(tableVk.CreateBuffer)
    CHECK_VKCMD(tableVk.CreateBuffer(gVkDevice, &bufInfo, nullptr, &gVertexBufferBaseVtxBuf) );

  VertexBufferBase_VertexBufferBaseAllocateBufferMemory(gVertexBufferBaseVtxBuf, &gVertexBufferBaseVtxMem);

  if(tableVk.BindBufferMemory)
    CHECK_VKCMD(tableVk.BindBufferMemory(gVkDevice, gVertexBufferBaseVtxBuf, gVertexBufferBaseVtxMem, 0) );

  gVertexBufferBaseBindDesc.binding = 0;
  gVertexBufferBaseBindDesc.stride = sizeof(Geometry::Vertex);
  gVertexBufferBaseBindDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

  gVertexBufferBaseCount = {idxCount, vtxCount};

  return true;
}

void VertexBuffer_VertexBufferUpdateIndices(const uint16_t* data, uint32_t elements, uint32_t offset)
{
  uint16_t* map = nullptr;

  if(tableVk.MapMemory)
    CHECK_VKCMD(tableVk.MapMemory(gVkDevice, gVertexBufferBaseIdxMem, sizeof(map[0] ) * offset, sizeof(map[0] ) * elements, 0, (void**)&map) );

  for(size_t i = 0; i < elements; ++i)
    map[i] = data[i];

  if(tableVk.UnmapMemory)
    tableVk.UnmapMemory(gVkDevice, gVertexBufferBaseIdxMem);
}

void VertexBuffer_VertexBufferUpdateVertices(const Geometry::Vertex* data, uint32_t elements, uint32_t offset)
{
  Geometry::Vertex* map = nullptr;

  if(tableVk.MapMemory)
    CHECK_VKCMD(tableVk.MapMemory(gVkDevice, gVertexBufferBaseVtxMem, sizeof(map[0] ) * offset, sizeof(map[0] ) * elements, 0, (void**) &map) );

  for(size_t i = 0; i < elements; ++i)
    map[i] = data[i];

  if(tableVk.UnmapMemory)
    tableVk.UnmapMemory(gVkDevice, gVertexBufferBaseVtxMem);
}

std::array<VkPipelineShaderStageCreateInfo, 2> gShaderProgramShaderInfo { { {VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO}, {VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO} } };

#if 0
void ShaderProgram_ShaderProgramDestructor()
{
  if(gVkDevice)
  {
    for(auto& si : gShaderProgramShaderInfo)
    {
      if(si.module != VK_NULL_HANDLE && tableVk.DestroyShaderModule)
        tableVk.DestroyShaderModule(gVkDevice, gShaderProgramShaderInfo[0].module, nullptr);

      si.module = VK_NULL_HANDLE;
    }
  }

  gShaderProgramShaderInfo = {};
}
#endif

void ShaderProgram_ShaderProgramLoad(uint32_t whichShaderInfo, const std::vector<uint32_t>& code)
{
  VkShaderModuleCreateInfo modInfo {VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO};

  auto& si = gShaderProgramShaderInfo[whichShaderInfo];
  si.pName = "main";
  std::string name;

  switch(whichShaderInfo)
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
      THROW_CHECK(Fmt("Unknown code whichShaderInfo %d", whichShaderInfo) );

  }

  modInfo.codeSize = code.size() * sizeof(code[0] );
  modInfo.pCode = &code[0];
  CHECK_MSG( (modInfo.codeSize > 0) && modInfo.pCode, Fmt("Invalid %s shader ", name.c_str() ) );

  if(tableVk.CreateShaderModule)
    CHECK_VKCMD(tableVk.CreateShaderModule(gVkDevice, &modInfo, nullptr, &si.module) );

  Log::Write(Log::Level::Info, Fmt("Loaded %s shader", name.c_str() ) );
}

void ShaderProgram_ShaderProgramLoadVertexShader(const std::vector<uint32_t>& code)
{
  ShaderProgram_ShaderProgramLoad(0, code);
}

void ShaderProgram_ShaderProgramLoadFragmentShader(const std::vector<uint32_t>& code)
{
  ShaderProgram_ShaderProgramLoad(1, code);
}

void ShaderProgram_ShaderProgramInit(VkDevice device)
{
}

std::vector<std::vector<XrSwapchainImageVulkan2KHR> > m_swapchainImageContextSwapchainImages;

std::vector<std::vector<VkImage> > m_swapchainImageContextStdVector_renderTargetColorImage;
std::vector<std::vector<VkImage> > m_swapchainImageContextStdVector_renderTargetDepthImage;
std::vector<std::vector<VkImageView> > m_swapchainImageContextStdVector_renderTargetColorView;
std::vector<std::vector<VkImageView> > m_swapchainImageContextStdVector_renderTargetDepthView;
std::vector<std::vector<VkFramebuffer> > m_swapchainImageContextStdVector_renderTargetFrameBuffer;

std::vector<VkExtent2D> m_swapchainImageContextSize;

std::vector<VkDeviceMemory> m_swapchainImageContext_depthBufferDepthMemory;
std::vector<VkImage> m_swapchainImageContext_depthBufferDepthImage;
std::vector<VkImageLayout> m_swapchainImageContext_depthBufferVkImageLayout;

std::vector<VkFormat> m_swapchainImageContext_renderPassColorFmt;
std::vector<VkFormat> m_swapchainImageContext_renderPassDepthFmt;
std::vector<VkRenderPass> m_swapchainImageContext_renderPassPass;

std::vector<VkPipeline> m_swapchainImageContextPipe_pipelinePipe;
std::vector<VkPrimitiveTopology> m_swapchainImageContextPipe_pipelineTopology;
std::vector<std::vector<VkDynamicState> > m_swapchainImageContextPipe_pipelineDynamicStateEnables;

std::vector<XrStructureType> m_swapchainImageContextSwapchainImageType;

std::vector<VulkanDebugObjectNamer> m_swapchainImageContextNamer;

void SwapchainImageContext_SwapchainImageContext_Constructor(int index, XrStructureType swapchainImageType, VulkanDebugObjectNamer& namer)
{
  m_swapchainImageContextSwapchainImages.resize(index + 1);
  m_swapchainImageContextStdVector_renderTargetColorImage.resize(index + 1);
  m_swapchainImageContextStdVector_renderTargetDepthImage.resize(index + 1);
  m_swapchainImageContextStdVector_renderTargetColorView.resize(index + 1);
  m_swapchainImageContextStdVector_renderTargetDepthView.resize(index + 1);
  m_swapchainImageContextStdVector_renderTargetFrameBuffer.resize(index + 1);
  m_swapchainImageContextSize.resize(index + 1);
  m_swapchainImageContext_depthBufferDepthMemory.resize(index + 1);
  m_swapchainImageContext_depthBufferDepthImage.resize(index + 1);
  m_swapchainImageContext_depthBufferVkImageLayout.resize(index + 1);
  m_swapchainImageContext_renderPassColorFmt.resize(index + 1);
  m_swapchainImageContext_renderPassDepthFmt.resize(index + 1);
  m_swapchainImageContext_renderPassPass.resize(index + 1);
  m_swapchainImageContextPipe_pipelinePipe.resize(index + 1);
  m_swapchainImageContextPipe_pipelineTopology.resize(index + 1);
  m_swapchainImageContextPipe_pipelineDynamicStateEnables.resize(index + 1);
  m_swapchainImageContextSwapchainImageType.resize(index + 1);
  m_swapchainImageContextNamer.resize(index + 1);

  //m_swapchainImageContextSwapchainImages[index].push_back( {swapchainImageType, 0, 0} );
  //m_swapchainImageContextStdVector_renderTargetColorImage[index].push_back(VK_NULL_HANDLE);
  //m_swapchainImageContextStdVector_renderTargetDepthImage[index].push_back(VK_NULL_HANDLE);
  //m_swapchainImageContextStdVector_renderTargetColorView[index].push_back(VK_NULL_HANDLE);
  //m_swapchainImageContextStdVector_renderTargetDepthView[index].push_back(VK_NULL_HANDLE);
  //m_swapchainImageContextStdVector_renderTargetFrameBuffer[index].push_back(VK_NULL_HANDLE);
  m_swapchainImageContextSize[index] = {640, 480};
  m_swapchainImageContext_depthBufferDepthMemory[index] = VK_NULL_HANDLE;
  m_swapchainImageContext_depthBufferDepthImage[index] = VK_NULL_HANDLE;
  m_swapchainImageContext_depthBufferVkImageLayout[index] = VK_IMAGE_LAYOUT_UNDEFINED;
  m_swapchainImageContext_renderPassColorFmt[index] = VK_FORMAT_B8G8R8A8_SRGB;
  m_swapchainImageContext_renderPassDepthFmt[index] = VK_FORMAT_D32_SFLOAT;
  m_swapchainImageContext_renderPassPass[index] = VK_NULL_HANDLE;
  m_swapchainImageContextPipe_pipelinePipe[index] = VK_NULL_HANDLE;
  m_swapchainImageContextPipe_pipelineTopology[index] = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  //m_swapchainImageContextPipe_pipelineDynamicStateEnables[index].push_back(VK_DYNAMIC_STATE_MAX_ENUM);
  m_swapchainImageContextSwapchainImageType[index] = swapchainImageType;
  m_swapchainImageContextNamer[index] = namer;
}

#if 0
void SwapchainImageContext_SwapchainImageContext_Destructor(int index)
{
  if(gVkDevice)
  {
    if(m_swapchainImageContext_depthBufferDepthImage[index] != VK_NULL_HANDLE && tableVk.DestroyImage)
      tableVk.DestroyImage(gVkDevice, m_swapchainImageContext_depthBufferDepthImage[index], nullptr);

    if(m_swapchainImageContext_depthBufferDepthMemory[index] != VK_NULL_HANDLE && tableVk.FreeMemory)
      tableVk.FreeMemory(gVkDevice, m_swapchainImageContext_depthBufferDepthMemory[index], nullptr);
  }

  m_swapchainImageContext_depthBufferDepthImage[index] = VK_NULL_HANDLE;
  m_swapchainImageContext_depthBufferDepthMemory[index] = VK_NULL_HANDLE;

  if(gVkDevice)
  {
    if(m_swapchainImageContext_renderPassPass[index] != VK_NULL_HANDLE && tableVk.DestroyRenderPass)
      tableVk.DestroyRenderPass(gVkDevice, m_swapchainImageContext_renderPassPass[index], nullptr);
  }

  m_swapchainImageContext_renderPassPass[index] = VK_NULL_HANDLE;

  for(int renderTarget = 0; renderTarget < m_swapchainImageContextStdVector_renderTargetFrameBuffer[index].size(); renderTarget++)
  {
    if(gVkDevice && m_swapchainImageContextStdVector_renderTargetFrameBuffer[index][renderTarget] != VK_NULL_HANDLE && tableVk.DestroyFramebuffer)
      tableVk.DestroyFramebuffer(gVkDevice, m_swapchainImageContextStdVector_renderTargetFrameBuffer[index][renderTarget], nullptr);

    if(gVkDevice && m_swapchainImageContextStdVector_renderTargetColorView[index][renderTarget] != VK_NULL_HANDLE && tableVk.DestroyImageView)
      tableVk.DestroyImageView(gVkDevice, m_swapchainImageContextStdVector_renderTargetColorView[index][renderTarget], nullptr);

    if(gVkDevice && m_swapchainImageContextStdVector_renderTargetDepthView[index][renderTarget] != VK_NULL_HANDLE && tableVk.DestroyImageView)
      tableVk.DestroyImageView(gVkDevice, m_swapchainImageContextStdVector_renderTargetDepthView[index][renderTarget], nullptr);
  }

  m_swapchainImageContextStdVector_renderTargetColorImage[index].empty();
  m_swapchainImageContextStdVector_renderTargetDepthImage[index].empty();
  m_swapchainImageContextStdVector_renderTargetColorView[index].empty();
  m_swapchainImageContextStdVector_renderTargetDepthView[index].empty();
  m_swapchainImageContextStdVector_renderTargetFrameBuffer[index].empty();
}
#endif

void SwapchainImageContext_SwapchainImageContext_RenderTargetCreate(int index, int renderTarget, const VulkanDebugObjectNamer& namer, VkDevice device, VkImage aColorImage, VkImage aDepthImage, VkExtent2D size)
{
  m_swapchainImageContextStdVector_renderTargetColorImage[index][renderTarget] = aColorImage;
  m_swapchainImageContextStdVector_renderTargetDepthImage[index][renderTarget] = aDepthImage;

  std::array<VkImageView, 2> attachments {};

  uint32_t attachmentCount = 0;

  // Create color image view
  if(m_swapchainImageContextStdVector_renderTargetColorImage[index][renderTarget] != VK_NULL_HANDLE)
  {
    VkImageViewCreateInfo colorViewInfo {VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};

    colorViewInfo.image = m_swapchainImageContextStdVector_renderTargetColorImage[index][renderTarget];
    colorViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    colorViewInfo.format = m_swapchainImageContext_renderPassColorFmt[index];
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
    {
      VkImageView renderTargetColorView {VK_NULL_HANDLE};
      CHECK_VKCMD(tableVk.CreateImageView(gVkDevice, &colorViewInfo, nullptr, &renderTargetColorView) );
      m_swapchainImageContextStdVector_renderTargetColorView[index][renderTarget] = renderTargetColorView;
    }

    CHECK_VKCMD(namer.SetName(VK_OBJECT_TYPE_IMAGE_VIEW, (uint64_t)m_swapchainImageContextStdVector_renderTargetColorView[index][renderTarget], "helloxr color image view") );
    attachments[attachmentCount++] = m_swapchainImageContextStdVector_renderTargetColorView[index][renderTarget];
  }

  // Create depth image view
  if(m_swapchainImageContextStdVector_renderTargetDepthImage[index][renderTarget] != VK_NULL_HANDLE)
  {
    VkImageViewCreateInfo depthViewInfo {VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};

    depthViewInfo.image = m_swapchainImageContextStdVector_renderTargetDepthImage[index][renderTarget];
    depthViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    depthViewInfo.format = m_swapchainImageContext_renderPassDepthFmt[index];
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
    {
      VkImageView renderTargetDepthView {VK_NULL_HANDLE};
      CHECK_VKCMD(tableVk.CreateImageView(gVkDevice, &depthViewInfo, nullptr, &renderTargetDepthView) );
      m_swapchainImageContextStdVector_renderTargetDepthView[index][renderTarget] = renderTargetDepthView;
    }

    CHECK_VKCMD(namer.SetName(VK_OBJECT_TYPE_IMAGE_VIEW, (uint64_t)m_swapchainImageContextStdVector_renderTargetDepthView[index][renderTarget], "helloxr depth image view") );
    attachments[attachmentCount++] = m_swapchainImageContextStdVector_renderTargetDepthView[index][renderTarget];
  }

  VkFramebufferCreateInfo fbInfo {VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO};

  fbInfo.renderPass = m_swapchainImageContext_renderPassPass[index];
  fbInfo.attachmentCount = attachmentCount;
  fbInfo.pAttachments = attachments.data();
  fbInfo.width = size.width;
  fbInfo.height = size.height;
  fbInfo.layers = 1;

  if(tableVk.CreateFramebuffer)
  {
    VkFramebuffer renderTargetFrameBuffer {VK_NULL_HANDLE};
    CHECK_VKCMD(tableVk.CreateFramebuffer(gVkDevice, &fbInfo, nullptr, &renderTargetFrameBuffer) );
    m_swapchainImageContextStdVector_renderTargetFrameBuffer[index][renderTarget] = renderTargetFrameBuffer;
  }

  CHECK_VKCMD(namer.SetName(VK_OBJECT_TYPE_FRAMEBUFFER, (uint64_t)m_swapchainImageContextStdVector_renderTargetFrameBuffer[index][renderTarget], "helloxr framebuffer") );
}

void SwapchainImageContext_SwapchainImageContext_DepthBufferCreate(int index, const VulkanDebugObjectNamer& namer, VkDevice device, VkFormat depthFormat, const XrSwapchainCreateInfo& swapchainCreateInfo)
{
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
    CHECK_VKCMD(tableVk.CreateImage(gVkDevice, &imageInfo, nullptr, &m_swapchainImageContext_depthBufferDepthImage[index]) );

  CHECK_VKCMD(namer.SetName(VK_OBJECT_TYPE_IMAGE, (uint64_t)m_swapchainImageContext_depthBufferDepthImage[index], "helloxr fallback depth image") );

  VkMemoryRequirements memRequirements {};

  if(tableVk.GetImageMemoryRequirements)
    tableVk.GetImageMemoryRequirements(gVkDevice, m_swapchainImageContext_depthBufferDepthImage[index], &memRequirements);

  MemoryAllocator_MemoryAllocatorAllocate(memRequirements, &m_swapchainImageContext_depthBufferDepthMemory[index], VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
  CHECK_VKCMD(namer.SetName(VK_OBJECT_TYPE_DEVICE_MEMORY, (uint64_t)m_swapchainImageContext_depthBufferDepthMemory[index], "helloxr fallback depth image memory") );

  if(tableVk.BindImageMemory)
    CHECK_VKCMD(tableVk.BindImageMemory(gVkDevice, m_swapchainImageContext_depthBufferDepthImage[index], m_swapchainImageContext_depthBufferDepthMemory[index], 0) );
}

void SwapchainImageContext_SwapchainImageContext_DepthBufferTransitionImageLayout(int index, VkImageLayout newLayout)
{
  if(newLayout == m_swapchainImageContext_depthBufferVkImageLayout[index] )
    return;

  VkImageMemoryBarrier depthBarrier {VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER};
  depthBarrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
  depthBarrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
  depthBarrier.oldLayout = m_swapchainImageContext_depthBufferVkImageLayout[index];
  depthBarrier.newLayout = newLayout;
  depthBarrier.image = m_swapchainImageContext_depthBufferDepthImage[index];

  depthBarrier.subresourceRange = {VK_IMAGE_ASPECT_DEPTH_BIT, 0, 1, 0, 1};

  if(tableVk.CmdPipelineBarrier)
    tableVk.CmdPipelineBarrier(gCmdBufferBuffer, VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, 0, 0, nullptr, 0, nullptr, 1, &depthBarrier);

  m_swapchainImageContext_depthBufferVkImageLayout[index] = newLayout;
}

bool SwapchainImageContext_SwapchainImageContext_RenderPassCreate(int index, const VulkanDebugObjectNamer& namer, VkDevice device, VkFormat aColorFmt, VkFormat aDepthFmt)
{
  m_swapchainImageContext_renderPassColorFmt[index] = aColorFmt;
  m_swapchainImageContext_renderPassDepthFmt[index] = aDepthFmt;

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

  if(m_swapchainImageContext_renderPassColorFmt[index] != VK_FORMAT_UNDEFINED)
  {
    colorRef.attachment = rpInfo.attachmentCount++;

    at[colorRef.attachment].format = m_swapchainImageContext_renderPassColorFmt[index];
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

  if(m_swapchainImageContext_renderPassDepthFmt[index] != VK_FORMAT_UNDEFINED)
  {
    depthRef.attachment = rpInfo.attachmentCount++;

    at[depthRef.attachment].format = m_swapchainImageContext_renderPassDepthFmt[index];
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
    CHECK_VKCMD(tableVk.CreateRenderPass(gVkDevice, &rpInfo, nullptr, &m_swapchainImageContext_renderPassPass[index] ) );

  CHECK_VKCMD(namer.SetName(VK_OBJECT_TYPE_RENDER_PASS, (uint64_t)m_swapchainImageContext_renderPassPass[index], "helloxr render pass") );

  return true;
}

void SwapchainImageContext_SwapchainImageContext_PipelineDynamic(int index, VkDynamicState state)
{
  //m_swapchainImageContextPipe_pipelineDynamicStateEnables[index].emplace_back(state);
  m_swapchainImageContextPipe_pipelineDynamicStateEnables[index].push_back(state);
}

void SwapchainImageContext_SwapchainImageContext_PipelineCreate(int index, VkDevice device, VkExtent2D size)
{
  VkPipelineDynamicStateCreateInfo dynamicState {VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO};
  dynamicState.dynamicStateCount = (uint32_t)m_swapchainImageContextPipe_pipelineDynamicStateEnables[index].size();
  dynamicState.pDynamicStates = m_swapchainImageContextPipe_pipelineDynamicStateEnables[index].data();

  VkPipelineVertexInputStateCreateInfo vi {VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO};
  vi.vertexBindingDescriptionCount = 1;
  vi.pVertexBindingDescriptions = &gVertexBufferBaseBindDesc;
  vi.vertexAttributeDescriptionCount = (uint32_t)gVertexBufferBaseAttrDesc.size();
  vi.pVertexAttributeDescriptions = gVertexBufferBaseAttrDesc.data();

  VkPipelineInputAssemblyStateCreateInfo ia {VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO};
  ia.primitiveRestartEnable = VK_FALSE;
  ia.topology = m_swapchainImageContextPipe_pipelineTopology[index];

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
  _operator_assign(cb.blendConstants, 1.0f);

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
  pipeInfo.stageCount = (uint32_t)gShaderProgramShaderInfo.size();
  pipeInfo.pStages = gShaderProgramShaderInfo.data();
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

  pipeInfo.layout = gVkPipelineLayout;
  pipeInfo.renderPass = m_swapchainImageContext_renderPassPass[index];
  pipeInfo.subpass = 0;

  if(tableVk.CreateGraphicsPipelines)
    CHECK_VKCMD(tableVk.CreateGraphicsPipelines(gVkDevice, VK_NULL_HANDLE, 1, &pipeInfo, nullptr, &m_swapchainImageContextPipe_pipelinePipe[index] ) );
}

void SwapchainImageContext_SwapchainImageContext_PipelineRelease(int index)
{
  if(gVkDevice)
  {
    if(m_swapchainImageContextPipe_pipelinePipe[index] != VK_NULL_HANDLE && tableVk.DestroyPipeline)
      tableVk.DestroyPipeline(gVkDevice, m_swapchainImageContextPipe_pipelinePipe[index], nullptr);
  }

  m_swapchainImageContextPipe_pipelinePipe[index] = VK_NULL_HANDLE;
}

std::vector<XrSwapchainImageBaseHeader*> SwapchainImageContext_SwapchainImageContextCreate(int index, const VulkanDebugObjectNamer& namer, VkDevice device, uint32_t capacity, const XrSwapchainCreateInfo& swapchainCreateInfo)
{
  m_swapchainImageContextNamer[index] = namer;

  m_swapchainImageContextSize[index] = {swapchainCreateInfo.width, swapchainCreateInfo.height};
  VkFormat colorFormat = (VkFormat)swapchainCreateInfo.format;
  VkFormat depthFormat = VK_FORMAT_D32_SFLOAT;

  SwapchainImageContext_SwapchainImageContext_DepthBufferCreate(index, m_swapchainImageContextNamer[index], gVkDevice, depthFormat, swapchainCreateInfo);
  SwapchainImageContext_SwapchainImageContext_RenderPassCreate(index, m_swapchainImageContextNamer[index], gVkDevice, colorFormat, depthFormat);

  SwapchainImageContext_SwapchainImageContext_PipelineCreate(index, gVkDevice, m_swapchainImageContextSize[index] );

  m_swapchainImageContextSwapchainImages[index].resize(capacity);

  m_swapchainImageContextStdVector_renderTargetColorImage[index].resize(capacity);
  m_swapchainImageContextStdVector_renderTargetDepthImage[index].resize(capacity);
  m_swapchainImageContextStdVector_renderTargetColorView[index].resize(capacity);
  m_swapchainImageContextStdVector_renderTargetDepthView[index].resize(capacity);
  m_swapchainImageContextStdVector_renderTargetFrameBuffer[index].resize(capacity);

  std::vector<XrSwapchainImageBaseHeader*> bases(capacity);

  for(uint32_t renderTarget = 0; renderTarget < capacity; renderTarget++)
  {
    m_swapchainImageContextSwapchainImages[index][renderTarget] = {m_swapchainImageContextSwapchainImageType[index] };
    bases[renderTarget] = reinterpret_cast<XrSwapchainImageBaseHeader*>( &m_swapchainImageContextSwapchainImages[index][renderTarget] );
  }

  return bases;
}

uint32_t SwapchainImageContext_SwapchainImageContextImageIndex(int index, const XrSwapchainImageBaseHeader* swapchainImageHeader)
{
  auto p = reinterpret_cast<const XrSwapchainImageVulkan2KHR*>(swapchainImageHeader);
  return (uint32_t)(p - &m_swapchainImageContextSwapchainImages[index][0] );
}

void SwapchainImageContext_SwapchainImageContextBindRenderTarget(int index, uint32_t renderTarget, VkRenderPassBeginInfo* renderPassBeginInfo)
{
  if(m_swapchainImageContextStdVector_renderTargetFrameBuffer[index][renderTarget] == VK_NULL_HANDLE)
    SwapchainImageContext_SwapchainImageContext_RenderTargetCreate(index, renderTarget, m_swapchainImageContextNamer[index], gVkDevice, m_swapchainImageContextSwapchainImages[index][renderTarget].image, m_swapchainImageContext_depthBufferDepthImage[index], m_swapchainImageContextSize[index] );

  renderPassBeginInfo->renderPass = m_swapchainImageContext_renderPassPass[index];
  renderPassBeginInfo->framebuffer = m_swapchainImageContextStdVector_renderTargetFrameBuffer[index][renderTarget];
  renderPassBeginInfo->renderArea.offset = {0, 0};
  renderPassBeginInfo->renderArea.extent = m_swapchainImageContextSize[index];
}

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

XrGraphicsBindingVulkan2KHR gVulkanGraphicsPluginXrGraphicsBindingVulkan2KHR {XR_TYPE_GRAPHICS_BINDING_VULKAN2_KHR};

//std::vector<SwapchainImageContext*> gVulkanGraphicsPluginStdList_SwapchainImageContext;
std::vector<int> gVulkanGraphicsPluginStdList_SwapchainImageContext;

std::map<const XrSwapchainImageBaseHeader*, int> gVulkanGraphicsPluginStdMap_XrSwapchainImageBaseHeader_SwapchainImageContext;

VulkanDebugObjectNamer gVulkanGraphicsPluginVulkanDebugObjectNamer {};

uint32_t gVulkanGraphicsPluginQueueFamilyIndex = 0;

VkQueue gVulkanGraphicsPluginVkQueue {VK_NULL_HANDLE};

VkSemaphore gVulkanGraphicsPluginVkSemaphoreDrawDone {VK_NULL_HANDLE};

std::array<float, 4> gVulkanGraphicsPluginStdArray_float_4_clearColor;

PFN_vkCreateDebugUtilsMessengerEXT gVulkanGraphicsPluginVkCreateDebugUtilsMessengerEXT {nullptr};

VkDebugUtilsMessengerEXT gVulkanGraphicsPluginVkDebugUtilsMessenger {VK_NULL_HANDLE};

void VulkanGraphicsPlugin_VulkanGraphicsPlugin()
{
  _operator_assign(gVulkanGraphicsPluginStdArray_float_4_clearColor, gOptions_BackgroundClearColor);

  gVulkanGraphicsPluginXrGraphicsBindingVulkan2KHR.type = VulkanGraphicsPlugin_VulkanGraphicsPluginGetGraphicsBindingType();
}

void VulkanGraphicsPlugin_VulkanGraphicsPlugin_Destructor()
{
  if(gVkDevice)
  {
    if(gVkPipelineLayout != VK_NULL_HANDLE && tableVk.DestroyPipelineLayout)
      tableVk.DestroyPipelineLayout(gVkDevice, gVkPipelineLayout, nullptr);

    gVkPipelineLayout = VK_NULL_HANDLE;
  }
}

std::vector<std::string> VulkanGraphicsPlugin_VulkanGraphicsPluginGetInstanceExtensions()
{
  return {XR_KHR_VULKAN_ENABLE2_EXTENSION_NAME};
}

// note: The output must not outlive the input - this modifies the input and returns a collection of views into that modified input!
std::vector<const char*> VulkanGraphicsPlugin_VulkanGraphicsPluginParseExtensionString(char* names)
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

const char* VulkanGraphicsPlugin_VulkanGraphicsPluginGetValidationLayerName()
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

void VulkanGraphicsPlugin_VulkanGraphicsPluginInitializeDevice(XrInstance instance, XrSystemId systemId)
{
  // Create the Vulkan device for the adapter associated with the system.
  // Extension function must be loaded by name
  XrGraphicsRequirementsVulkan2KHR graphicsRequirements {XR_TYPE_GRAPHICS_REQUIREMENTS_VULKAN2_KHR};

  CHECK_XRCMD_CHECK(VulkanGraphicsPlugin_VulkanGraphicsPluginGetVulkanGraphicsRequirements2KHR(instance, systemId, &graphicsRequirements) );

  VkResult err = VK_ERROR_OUT_OF_HOST_MEMORY;

  std::vector<const char*> layers;

#if !defined(NDEBUG)
  const char* const validationLayerName = VulkanGraphicsPlugin_VulkanGraphicsPluginGetValidationLayerName();

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
  debugInfo.pUserData = 0;

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

  CHECK_XRCMD_CHECK(VulkanGraphicsPlugin_VulkanGraphicsPluginCreateVulkanInstanceKHR(instance, &createInfo, &gVkInstance, &err) );
  CHECK_VKCMD(err);

  if(tableVk.GetInstanceProcAddr)
    gVulkanGraphicsPluginVkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)tableVk.GetInstanceProcAddr(gVkInstance, "vkCreateDebugUtilsMessengerEXT");

  if(gVulkanGraphicsPluginVkCreateDebugUtilsMessengerEXT != nullptr && tableVk.CreateDebugUtilsMessengerEXT)
    CHECK_VKCMD(tableVk.CreateDebugUtilsMessengerEXT(gVkInstance, &debugInfo, nullptr, &gVulkanGraphicsPluginVkDebugUtilsMessenger) );

  {
    XrVulkanGraphicsDeviceGetInfoKHR deviceGetInfo {XR_TYPE_VULKAN_GRAPHICS_DEVICE_GET_INFO_KHR};

    deviceGetInfo.systemId = systemId;
    deviceGetInfo.vulkanInstance = gVkInstance;

    CHECK_XRCMD_CHECK(VulkanGraphicsPlugin_VulkanGraphicsPluginGetVulkanGraphicsDevice2KHR(instance, &deviceGetInfo, &gVkPhysicalDevice) );
  }

  VkDeviceQueueCreateInfo queueInfo {VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO};

  float queuePriorities = 0;
  queueInfo.queueCount = 1;
  queueInfo.pQueuePriorities = &queuePriorities;

  uint32_t queueFamilyCount = 0;

  if(tableVk.GetPhysicalDeviceQueueFamilyProperties)
    tableVk.GetPhysicalDeviceQueueFamilyProperties(gVkPhysicalDevice, &queueFamilyCount, nullptr);

  std::vector<VkQueueFamilyProperties> queueFamilyProps(queueFamilyCount);

  if(tableVk.GetPhysicalDeviceQueueFamilyProperties)
    tableVk.GetPhysicalDeviceQueueFamilyProperties(gVkPhysicalDevice, &queueFamilyCount, &queueFamilyProps[0] );

  for(uint32_t i = 0; i < queueFamilyCount; ++i)
  {
    // Only need graphics (not presentation) for draw queue
    if(queueFamilyProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
    {
      gVulkanGraphicsPluginQueueFamilyIndex = queueInfo.queueFamilyIndex = i;
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
  deviceCreateInfo.vulkanPhysicalDevice = gVkPhysicalDevice;
  deviceCreateInfo.vulkanAllocator = nullptr;

  CHECK_XRCMD_CHECK(VulkanGraphicsPlugin_VulkanGraphicsPluginCreateVulkanDeviceKHR(instance, &deviceCreateInfo, &gVkDevice, &err) );
  CHECK_VKCMD(err);

  gVulkanGraphicsPluginVulkanDebugObjectNamer.Init(gVkInstance, gVkDevice);

  if(tableVk.GetDeviceQueue)
    tableVk.GetDeviceQueue(gVkDevice, queueInfo.queueFamilyIndex, 0, &gVulkanGraphicsPluginVkQueue);

  MemoryAllocator_MemoryAllocatorInit(gVkPhysicalDevice);

  VulkanGraphicsPlugin_VulkanGraphicsPluginInitializeResources();

  gVulkanGraphicsPluginXrGraphicsBindingVulkan2KHR.instance = gVkInstance;
  gVulkanGraphicsPluginXrGraphicsBindingVulkan2KHR.physicalDevice = gVkPhysicalDevice;
  gVulkanGraphicsPluginXrGraphicsBindingVulkan2KHR.device = gVkDevice;
  gVulkanGraphicsPluginXrGraphicsBindingVulkan2KHR.queueFamilyIndex = queueInfo.queueFamilyIndex;
  gVulkanGraphicsPluginXrGraphicsBindingVulkan2KHR.queueIndex = 0;
}

// compile a shader to a SPIR-V binary
std::vector<uint32_t> VulkanGraphicsPlugin_VulkanGraphicsPluginCompileGlslShader(const std::string& name, shaderc_shader_kind kind, const std::string& source)
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

void VulkanGraphicsPlugin_VulkanGraphicsPluginInitializeResources()
{
  auto vertexSPIRV = VulkanGraphicsPlugin_VulkanGraphicsPluginCompileGlslShader("vertex", shaderc_glsl_default_vertex_shader, VertexShaderGlsl);
  auto fragmentSPIRV = VulkanGraphicsPlugin_VulkanGraphicsPluginCompileGlslShader("fragment", shaderc_glsl_default_fragment_shader, FragmentShaderGlsl);

  if(vertexSPIRV.empty() ) THROW_CHECK("Failed to compile vertex shader");

  if(fragmentSPIRV.empty() ) THROW_CHECK("Failed to compile fragment shader");

  ShaderProgram_ShaderProgramInit(gVkDevice);
  ShaderProgram_ShaderProgramLoadVertexShader(vertexSPIRV);
  ShaderProgram_ShaderProgramLoadFragmentShader(fragmentSPIRV);

  // Semaphore to block on draw complete
  VkSemaphoreCreateInfo semInfo {VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};

  if(tableVk.CreateSemaphore)
    CHECK_VKCMD(tableVk.CreateSemaphore(gVkDevice, &semInfo, nullptr, &gVulkanGraphicsPluginVkSemaphoreDrawDone) );

  CHECK_VKCMD(gVulkanGraphicsPluginVulkanDebugObjectNamer.SetName(VK_OBJECT_TYPE_SEMAPHORE, (uint64_t)gVulkanGraphicsPluginVkSemaphoreDrawDone, "helloxr draw done semaphore") );

  if(!CmdBuffer_CmdBufferInit(gVulkanGraphicsPluginVulkanDebugObjectNamer, gVkDevice, gVulkanGraphicsPluginQueueFamilyIndex) ) THROW_CHECK("Failed to create command buffer");

  //gVkPipelineLayout.PipelineLayoutCreate(gVkDevice);
  PipelineLayout_PipelineLayoutCreate(gVkDevice);

  static_assert(sizeof(Geometry::Vertex) == 24, "Unexpected Vertex size");

  VertexBufferBase_VertexBufferBaseInit( { {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Geometry::Vertex, Position) }, {1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Geometry::Vertex, Color) } } );

  uint32_t numCubeIdicies = sizeof(Geometry::c_cubeIndices) / sizeof(Geometry::c_cubeIndices[0] );
  uint32_t numCubeVerticies = sizeof(Geometry::c_cubeVertices) / sizeof(Geometry::c_cubeVertices[0] );

  VertexBuffer_VertexBufferCreate(numCubeIdicies, numCubeVerticies);
  VertexBuffer_VertexBufferUpdateIndices(Geometry::c_cubeIndices, numCubeIdicies, 0);
  VertexBuffer_VertexBufferUpdateVertices(Geometry::c_cubeVertices, numCubeVerticies, 0);
}

int64_t VulkanGraphicsPlugin_VulkanGraphicsPluginSelectColorSwapchainFormat(const std::vector<int64_t>& runtimeFormats)
{
  // List of supported color swapchain formats.
  constexpr int64_t SupportedColorSwapchainFormats[] = {VK_FORMAT_B8G8R8A8_SRGB, VK_FORMAT_R8G8B8A8_SRGB, VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R8G8B8A8_UNORM};

  auto swapchainFormatIt = std::find_first_of(runtimeFormats.begin(), runtimeFormats.end(), std::begin(SupportedColorSwapchainFormats), std::end(SupportedColorSwapchainFormats) );

  if(swapchainFormatIt == runtimeFormats.end() )
    THROW_CHECK("No runtime swapchain format supported for color swapchain");

  return *swapchainFormatIt;
}

const XrBaseInStructure* VulkanGraphicsPlugin_VulkanGraphicsPluginGetGraphicsBinding()
{
  return reinterpret_cast<const XrBaseInStructure*>(&gVulkanGraphicsPluginXrGraphicsBindingVulkan2KHR);
}

std::vector<XrSwapchainImageBaseHeader*> VulkanGraphicsPlugin_VulkanGraphicsPluginAllocateSwapchainImageStructs(uint32_t capacity, const XrSwapchainCreateInfo& swapchainCreateInfo)
{
  int indice = gVulkanGraphicsPluginStdList_SwapchainImageContext.size();

  // Allocate and initialize the buffer of image structs (must be sequential in memory for xrEnumerateSwapchainImages).
  // Return back an array of pointers to each swapchain image struct so the consumer doesn't need to know the type/size.
  // Keep the buffer alive by adding it into the list of buffers.

  SwapchainImageContext_SwapchainImageContext_Constructor(indice, VulkanGraphicsPlugin_VulkanGraphicsPluginGetSwapchainImageType(), gVulkanGraphicsPluginVulkanDebugObjectNamer);

  //gVulkanGraphicsPluginStdList_SwapchainImageContext.push_back(new SwapchainImageContext(VulkanGraphicsPluginGetSwapchainImageType() ) );
  gVulkanGraphicsPluginStdList_SwapchainImageContext.push_back(indice);

  //SwapchainImageContext* swapchainImageContext = gVulkanGraphicsPluginStdList_SwapchainImageContext[indice];

  //std::vector<XrSwapchainImageBaseHeader*> bases = swapchainImageContext->SwapchainImageContextCreate(gVulkanGraphicsPluginVulkanDebugObjectNamer, gVkDevice, capacity, swapchainCreateInfo, m_vulkanGraphicsPluginShaderProgram, m_vulkanGraphicsPluginVertexBuffer_GeometryVertex_DrawBuffer);

  std::vector<XrSwapchainImageBaseHeader*> bases = SwapchainImageContext_SwapchainImageContextCreate(indice, gVulkanGraphicsPluginVulkanDebugObjectNamer, gVkDevice, capacity, swapchainCreateInfo);

  // Map every swapchainImage base pointer to this context
  for(auto& base : bases)
    gVulkanGraphicsPluginStdMap_XrSwapchainImageBaseHeader_SwapchainImageContext[base] = indice;

  return bases;
}

void VulkanGraphicsPlugin_VulkanGraphicsPluginRenderView(const XrCompositionLayerProjectionView& layerView, const XrSwapchainImageBaseHeader* swapchainImage, int64_t /*swapchainFormat*/, const std::vector<Cube>& cubes)
{
  CHECK_CHECK(layerView.subImage.imageArrayIndex == 0);  // Texture arrays not supported.

  int swapchainContextIndex = gVulkanGraphicsPluginStdMap_XrSwapchainImageBaseHeader_SwapchainImageContext[swapchainImage];
  uint32_t renderTarget = SwapchainImageContext_SwapchainImageContextImageIndex(swapchainContextIndex, swapchainImage);

  // XXX Should double-buffer the command buffers, for now just flush
  CmdBuffer_CmdBufferWait();
  CmdBuffer_CmdBufferReset();
  CmdBuffer_CmdBufferBegin();

  // Ensure depth is in the right layout
  SwapchainImageContext_SwapchainImageContext_DepthBufferTransitionImageLayout(swapchainContextIndex, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);

  // Bind and clear eye render target
  static std::array<VkClearValue, 2> clearValues;

  _operator_assign(clearValues[0].color.float32, gVulkanGraphicsPluginStdArray_float_4_clearColor);
  clearValues[1].depthStencil.depth = 1.0f;
  clearValues[1].depthStencil.stencil = 0;

  VkRenderPassBeginInfo renderPassBeginInfo {VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};

  renderPassBeginInfo.clearValueCount = (uint32_t)clearValues.size();
  renderPassBeginInfo.pClearValues = clearValues.data();

  SwapchainImageContext_SwapchainImageContextBindRenderTarget(swapchainContextIndex, renderTarget, &renderPassBeginInfo);

  if(tableVk.CmdBeginRenderPass)
    tableVk.CmdBeginRenderPass(gCmdBufferBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

  if(tableVk.CmdBindPipeline)
    tableVk.CmdBindPipeline(gCmdBufferBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_swapchainImageContextPipe_pipelinePipe[swapchainContextIndex] );

  // Bind indice and vertex buffers
  if(tableVk.CmdBindIndexBuffer)
    tableVk.CmdBindIndexBuffer(gCmdBufferBuffer, gVertexBufferBaseIdxBuf, 0, VK_INDEX_TYPE_UINT16);

  VkDeviceSize offset = 0;

  if(tableVk.CmdBindVertexBuffers)
    tableVk.CmdBindVertexBuffers(gCmdBufferBuffer, 0, 1, &gVertexBufferBaseVtxBuf, &offset);

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
      tableVk.CmdPushConstants(gCmdBufferBuffer, gVkPipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(mvp.m), &mvp.m[0] );

    // draw the cube
    if(tableVk.CmdDrawIndexed)
      tableVk.CmdDrawIndexed(gCmdBufferBuffer, gVertexBufferBaseCount.idx, 1, 0, 0, 0);
  }

  if(tableVk.CmdEndRenderPass)
    tableVk.CmdEndRenderPass(gCmdBufferBuffer);

  CmdBuffer_CmdBufferEnd();
  CmdBuffer_CmdBufferExec(gVulkanGraphicsPluginVkQueue);
}

uint32_t VulkanGraphicsPlugin_VulkanGraphicsPluginGetSupportedSwapchainSampleCount(const XrViewConfigurationView&)
{
  return VK_SAMPLE_COUNT_1_BIT;
}

void VulkanGraphicsPlugin_VulkanGraphicsPluginUpdateOptions()
{
  _operator_assign(gVulkanGraphicsPluginStdArray_float_4_clearColor, gOptions_BackgroundClearColor);
}

VkBool32 VulkanGraphicsPlugin_VulkanGraphicsPluginDebugMessage(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData)
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

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanGraphicsPlugin_debugMessageThunk(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* /*pUserData*/)
{
  return VulkanGraphicsPlugin_VulkanGraphicsPluginDebugMessage(messageSeverity, messageTypes, pCallbackData);
}

XrStructureType VulkanGraphicsPlugin_VulkanGraphicsPluginGetGraphicsBindingType()
{
  return XR_TYPE_GRAPHICS_BINDING_VULKAN2_KHR;
}

XrStructureType VulkanGraphicsPlugin_VulkanGraphicsPluginGetSwapchainImageType()
{
  return XR_TYPE_SWAPCHAIN_IMAGE_VULKAN2_KHR;
}

XrResult VulkanGraphicsPlugin_VulkanGraphicsPluginCreateVulkanInstanceKHR(XrInstance instance, const XrVulkanInstanceCreateInfoKHR* createInfo, VkInstance* vulkanInstance, VkResult* vulkanResult)
{
  PFN_xrCreateVulkanInstanceKHR pfnCreateVulkanInstanceKHR = nullptr;
  XrResult result = XR_ERROR_VALIDATION_FAILURE;

  InitOpenXr();

  if(tableXr.GetInstanceProcAddr)
  {
    result = tableXr.GetInstanceProcAddr(instance, "xrCreateVulkanInstanceKHR", reinterpret_cast<PFN_xrVoidFunction*>( &pfnCreateVulkanInstanceKHR) );
    CHECK_XRCMD_CHECK(result);
  }

  if(pfnCreateVulkanInstanceKHR)
    result = pfnCreateVulkanInstanceKHR(instance, createInfo, vulkanInstance, vulkanResult);

  return result;
}

XrResult VulkanGraphicsPlugin_VulkanGraphicsPluginCreateVulkanDeviceKHR(XrInstance instance, const XrVulkanDeviceCreateInfoKHR* createInfo, VkDevice* vulkanDevice, VkResult* vulkanResult)
{
  PFN_xrCreateVulkanDeviceKHR pfnCreateVulkanDeviceKHR = nullptr;
  XrResult result = XR_ERROR_VALIDATION_FAILURE;

  InitOpenXr();

  if(tableXr.GetInstanceProcAddr)
  {
    result = tableXr.GetInstanceProcAddr(instance, "xrCreateVulkanDeviceKHR", reinterpret_cast<PFN_xrVoidFunction*>( &pfnCreateVulkanDeviceKHR) );
    CHECK_XRCMD_CHECK(result);
  }

  if(pfnCreateVulkanDeviceKHR)
    result = pfnCreateVulkanDeviceKHR(instance, createInfo, vulkanDevice, vulkanResult);

  return result;
}

XrResult VulkanGraphicsPlugin_VulkanGraphicsPluginGetVulkanGraphicsDevice2KHR(XrInstance instance, const XrVulkanGraphicsDeviceGetInfoKHR* getInfo, VkPhysicalDevice* vulkanPhysicalDevice)
{
  PFN_xrGetVulkanGraphicsDevice2KHR pfnGetVulkanGraphicsDevice2KHR = nullptr;
  XrResult result = XR_ERROR_VALIDATION_FAILURE;

  InitOpenXr();

  if(tableXr.GetInstanceProcAddr)
  {
    result = tableXr.GetInstanceProcAddr(instance, "xrGetVulkanGraphicsDevice2KHR", reinterpret_cast<PFN_xrVoidFunction*>( &pfnGetVulkanGraphicsDevice2KHR) );
    CHECK_XRCMD_CHECK(result);
  }

  if(pfnGetVulkanGraphicsDevice2KHR)
    result = pfnGetVulkanGraphicsDevice2KHR(instance, getInfo, vulkanPhysicalDevice);

  return result;
}

XrResult VulkanGraphicsPlugin_VulkanGraphicsPluginGetVulkanGraphicsRequirements2KHR(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsVulkan2KHR* graphicsRequirements)
{
  PFN_xrGetVulkanGraphicsRequirements2KHR pfnGetVulkanGraphicsRequirements2KHR = nullptr;
  XrResult result = XR_ERROR_VALIDATION_FAILURE;

  InitOpenXr();

  if(tableXr.GetInstanceProcAddr)
  {
    result = tableXr.GetInstanceProcAddr(instance, "xrGetVulkanGraphicsRequirements2KHR", reinterpret_cast<PFN_xrVoidFunction*>( &pfnGetVulkanGraphicsRequirements2KHR) );
    CHECK_XRCMD_CHECK(result);
  }

  if(pfnGetVulkanGraphicsRequirements2KHR)
    result = pfnGetVulkanGraphicsRequirements2KHR(instance, systemId, graphicsRequirements);

  return result;
}

void VulkanGraphicsPlugin_CreateGraphicsPlugin_Vulkan()
{
  VulkanGraphicsPlugin_VulkanGraphicsPlugin();
}
