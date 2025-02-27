
// vulkan_tutorial.cpp

#include "header.h"

//std::vector<VkBuffer> gVulkanTutorialUniformBuffers;
//std::vector<VkDescriptorSet> gVulkanTutorialDescriptorSets;

#if 0
VkVertexInputBindingDescription GeometryVertex::getBindingDescription()
{
  VkVertexInputBindingDescription bindingDescription {};
  bindingDescription.binding = 0;
  bindingDescription.stride = sizeof(GeometryVertex);
  bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

  return bindingDescription;
}

std::array<VkVertexInputAttributeDescription, 3> GeometryVertex::getAttributeDescriptions()
{
  std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions {};

  attributeDescriptions[0].binding = 0;
  attributeDescriptions[0].location = 0;
  attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
  attributeDescriptions[0].offset = offsetof(GeometryVertex, pos);

  attributeDescriptions[1].binding = 0;
  attributeDescriptions[1].location = 1;
  attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
  attributeDescriptions[1].offset = offsetof(GeometryVertex, color);

  attributeDescriptions[2].binding = 0;
  attributeDescriptions[2].location = 2;
  attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
  attributeDescriptions[2].offset = offsetof(GeometryVertex, texCoord);

  return attributeDescriptions;
}
#endif

VkResult VulkanTutorialCreateDebugUtilsMessengerEXT(
  const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
  const VkAllocationCallbacks* pAllocator,
  VkDebugUtilsMessengerEXT* pDebugMessenger
)
{
  PFN_vkCreateDebugUtilsMessengerEXT createDebugUtilsMessengerEXT = nullptr;

  if(tableVk.GetInstanceProcAddr)
  {
    createDebugUtilsMessengerEXT =
      (PFN_vkCreateDebugUtilsMessengerEXT)tableVk.GetInstanceProcAddr(gVkInstance, "vkCreateDebugUtilsMessengerEXT");
  }

  VkResult result = VK_ERROR_EXTENSION_NOT_PRESENT;

  if(createDebugUtilsMessengerEXT)
    result = createDebugUtilsMessengerEXT(gVkInstance, pCreateInfo, pAllocator, pDebugMessenger);

  return result;
}

void VulkanTutorialDestroyDebugUtilsMessengerEXT(
  VkDebugUtilsMessengerEXT debugMessenger,
  const VkAllocationCallbacks* pAllocator
)
{
  PFN_vkDestroyDebugUtilsMessengerEXT destroyDebugUtilsMessengerEXT = nullptr;

  if(tableVk.GetInstanceProcAddr)
  {
    destroyDebugUtilsMessengerEXT =
      (PFN_vkDestroyDebugUtilsMessengerEXT)tableVk.GetInstanceProcAddr(gVkInstance, "vkDestroyDebugUtilsMessengerEXT");
  }

  if(destroyDebugUtilsMessengerEXT)
    destroyDebugUtilsMessengerEXT(gVkInstance, debugMessenger, pAllocator);
}

bool VulkanTutorialQueueFamilyIndices_isComplete(
  VulkanTutorialQueueFamilyIndices _this
)
{
  return _this.graphicsFamily.has_value() && _this.presentFamily.has_value();
}

uint32_t VulkanTutorialFindMemoryType(
  uint32_t typeFilter,
  VkMemoryPropertyFlags properties
)
{
  VkPhysicalDeviceMemoryProperties memProperties;

  if(tableVk.GetPhysicalDeviceMemoryProperties)
    tableVk.GetPhysicalDeviceMemoryProperties(gVkPhysicalDevice, &memProperties);

  for(uint32_t offset = 0; offset < memProperties.memoryTypeCount; offset++)
  {
    if( (typeFilter & (1 << offset) ) && (memProperties.memoryTypes[offset].propertyFlags & properties) == properties)
      return offset;
  }

  throw std::runtime_error("failed to find suitable memory type!");
}

void VulkanTutorialCreateImage(
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

  if(tableVk.CreateImage)
  {
    if(tableVk.CreateImage(gVkDevice, &imageInfo, nullptr, &image) != VK_SUCCESS)
      throw std::runtime_error("failed to create image!");
  }

  VkMemoryRequirements memRequirements;

  if(tableVk.GetImageMemoryRequirements)
    tableVk.GetImageMemoryRequirements(gVkDevice, image, &memRequirements);

  VkMemoryAllocateInfo allocInfo {};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = VulkanTutorialFindMemoryType(memRequirements.memoryTypeBits, properties);

  if(tableVk.AllocateMemory)
  {
    if(tableVk.AllocateMemory(gVkDevice, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS)
      throw std::runtime_error("failed to allocate image memory!");
  }

  if(tableVk.BindImageMemory)
  {
    if(tableVk.BindImageMemory(gVkDevice, image, imageMemory, 0) != VK_SUCCESS)
      throw std::runtime_error("BindImageMemory failure");
  }
}

VkImageView VulkanTutorialCreateImageView(
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

  if(tableVk.CreateImageView)
  {
    if(tableVk.CreateImageView(gVkDevice, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
      throw std::runtime_error("failed to create image view!");
  }

  return imageView;
}

VkCommandBuffer VulkanTutorialsBeginSingleTimeCommands(
  VkCommandPool& commandPool
)
{
  VkCommandBufferAllocateInfo allocInfo {};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandPool = commandPool;
  allocInfo.commandBufferCount = 1;

  VkCommandBuffer commandBuffer;

  if(tableVk.AllocateCommandBuffers)
    tableVk.AllocateCommandBuffers(gVkDevice, &allocInfo, &commandBuffer);

  VkCommandBufferBeginInfo beginInfo {};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

  if(tableVk.BeginCommandBuffer)
    tableVk.BeginCommandBuffer(commandBuffer, &beginInfo);

  return commandBuffer;
}

void VulkanTutorialEndSingleTimeCommands(
  VkQueue& graphicsQueue,
  VkCommandPool& commandPool,
  VkCommandBuffer commandBuffer
)
{
  if(tableVk.EndCommandBuffer)
    tableVk.EndCommandBuffer(commandBuffer);

  VkSubmitInfo submitInfo {};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &commandBuffer;

  if(tableVk.QueueSubmit)
    tableVk.QueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);

  if(tableVk.QueueWaitIdle)
    tableVk.QueueWaitIdle(graphicsQueue);

  if(tableVk.FreeCommandBuffers)
    tableVk.FreeCommandBuffers(gVkDevice, commandPool, 1, &commandBuffer);
}

void VulkanTutorialTransitionImageLayout(
  VkQueue& graphicsQueue,
  VkCommandPool& commandPool,
  VkImage image,
  VkFormat format/*todo*/,
  VkImageLayout oldLayout,
  VkImageLayout newLayout
)
{
  VkCommandBuffer commandBuffer = VulkanTutorialsBeginSingleTimeCommands(commandPool);

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

  if(tableVk.CmdPipelineBarrier)
    tableVk.CmdPipelineBarrier(commandBuffer, sourceStage, destinationStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);

  VulkanTutorialEndSingleTimeCommands(graphicsQueue, commandPool, commandBuffer);
}

VkFormat VulkanTutorialFindSupportedFormat(
  const std::vector<VkFormat>& candidates,
  VkImageTiling tiling,
  VkFormatFeatureFlags features
)
{
  for(VkFormat format : candidates)
  {
    VkFormatProperties props;

    if(tableVk.GetPhysicalDeviceFormatProperties)
      tableVk.GetPhysicalDeviceFormatProperties(gVkPhysicalDevice, format, &props);

    if(tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
      return format;
    else if(tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
      return format;
  }

  throw std::runtime_error("failed to find supported format!");
}

VkFormat VulkanTutorialFindDepthFormat(
)
{
  VkFormat result = VulkanTutorialFindSupportedFormat(
    VulkanTutorialDepthFormatCandidates,
    VK_IMAGE_TILING_OPTIMAL,
    VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
  );

  return result;
}

void VulkanTutorialCreateDepthResources(
  VkExtent2D& swapChainExtent,
  VkImage& depthImage,
  VkDeviceMemory& depthImageMemory,
  VkImageView& depthImageView
)
{
  VkFormat depthFormat = VulkanTutorialFindDepthFormat();

  VulkanTutorialCreateImage(
    swapChainExtent.width,
    swapChainExtent.height,
    depthFormat,
    VK_IMAGE_TILING_OPTIMAL,
    VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
    depthImage,
    depthImageMemory
  );

  depthImageView = VulkanTutorialCreateImageView(depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
}

void VulkanTutorialCreateRenderPass(
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
  depthAttachment.format = VulkanTutorialFindDepthFormat();
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

  if(tableVk.CreateRenderPass)
  {
    if(tableVk.CreateRenderPass(gVkDevice, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS)
      throw std::runtime_error("failed to create render pass!");
  }
}

void VulkanTutorialCreateFramebuffers(
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

    if(tableVk.CreateFramebuffer)
    {
      if(tableVk.CreateFramebuffer(gVkDevice, &framebufferInfo, nullptr, &swapChainFramebuffers[i] ) != VK_SUCCESS)
        throw std::runtime_error("failed to create framebuffer!");
    }
  }
}

void VulkanTutorialRecordCommandBuffer(
  VkCommandBuffer& commandBuffer,
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

  if(tableVk.BeginCommandBuffer)
  {
    if(tableVk.BeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS)
      throw std::runtime_error("failed to begin recording command buffer!");
  }

  VkRenderPassBeginInfo renderPassInfo {};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderPassInfo.renderPass = renderPass;
  renderPassInfo.framebuffer = swapChainFramebuffers[imageIndex];
  renderPassInfo.renderArea.offset = {0, 0};
  renderPassInfo.renderArea.extent = swapChainExtent;

  std::array<VkClearValue, 2> clearValues {};

  clearValues[0].color =
  {
    {0.0f, 0.0f, 0.0f, 1.0f}
  };

  clearValues[1].depthStencil =
  {
    1.0f,
    0
  };

  renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size() );
  renderPassInfo.pClearValues = clearValues.data();

  if(tableVk.CmdBeginRenderPass)
    tableVk.CmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

  if(tableVk.CmdBindPipeline)
    tableVk.CmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

  VkViewport viewport {};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = (float)swapChainExtent.width;
  viewport.height = (float)swapChainExtent.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  if(tableVk.CmdSetViewport)
    tableVk.CmdSetViewport(commandBuffer, 0, 1, &viewport);

  VkRect2D scissor {};
  scissor.offset = {0, 0};
  scissor.extent = swapChainExtent;

  if(tableVk.CmdSetScissor)
    tableVk.CmdSetScissor(commandBuffer, 0, 1, &scissor);

  VkBuffer vertexBuffers[] = {vertexBuffer};
  VkDeviceSize offsets[] = {0};

  if(tableVk.CmdBindVertexBuffers)
    tableVk.CmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

  if(tableVk.CmdBindIndexBuffer)
    tableVk.CmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT32);

  if(tableVk.CmdBindDescriptorSets)
  {
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
  }

  if(tableVk.CmdDrawIndexed)
    tableVk.CmdDrawIndexed(commandBuffer, static_cast<uint32_t>(VulkanTutorialIndices.size() ), 1, 0, 0, 0);

  if(tableVk.CmdEndRenderPass)
    tableVk.CmdEndRenderPass(commandBuffer);

  if(tableVk.EndCommandBuffer)
  {
    if(tableVk.EndCommandBuffer(commandBuffer) != VK_SUCCESS)
      throw std::runtime_error("failed to record command buffer!");
  }
}

void VulkanTutorialCleanupSwapChain(
  VkSwapchainKHR& swapChain,
  std::vector<VkImageView>& swapChainImageViews,
  std::vector<VkFramebuffer>& swapChainFramebuffers,
  VkImage& depthImage,
  VkDeviceMemory& depthImageMemory,
  VkImageView& depthImageView
)
{
  if(tableVk.DestroyImageView)
    tableVk.DestroyImageView(gVkDevice, depthImageView, nullptr);

  if(tableVk.DestroyImage)
    tableVk.DestroyImage(gVkDevice, depthImage, nullptr);

  if(tableVk.FreeMemory)
    tableVk.FreeMemory(gVkDevice, depthImageMemory, nullptr);

  for(const VkFramebuffer& framebuffer : swapChainFramebuffers)
  {
    if(tableVk.DestroyFramebuffer)
      tableVk.DestroyFramebuffer(gVkDevice, framebuffer, nullptr);
  }

  for(const VkImageView& imageView : swapChainImageViews)
  {
    if(tableVk.DestroyImageView)
      tableVk.DestroyImageView(gVkDevice, imageView, nullptr);
  }

  if(tableVk.DestroySwapchainKHR)
    tableVk.DestroySwapchainKHR(gVkDevice, swapChain, nullptr);
}

VulkanTutorialSwapChainSupportDetails VulkanTutorialQuerySwapChainSupport(
  VkSurfaceKHR& surface
)
{
  VulkanTutorialSwapChainSupportDetails details;

  if(tableVk.GetPhysicalDeviceSurfaceCapabilitiesKHR)
    tableVk.GetPhysicalDeviceSurfaceCapabilitiesKHR(gVkPhysicalDevice, surface, &details.capabilities);

  uint32_t formatCount = 0;

  if(tableVk.GetPhysicalDeviceSurfaceFormatsKHR)
    tableVk.GetPhysicalDeviceSurfaceFormatsKHR(gVkPhysicalDevice, surface, &formatCount, nullptr);

  if(formatCount)
  {
    details.formats.resize(formatCount);

    if(tableVk.GetPhysicalDeviceSurfaceFormatsKHR)
      tableVk.GetPhysicalDeviceSurfaceFormatsKHR(gVkPhysicalDevice, surface, &formatCount, details.formats.data() );
  }

  uint32_t presentModeCount = 0;

  if(tableVk.GetPhysicalDeviceSurfacePresentModesKHR)
    tableVk.GetPhysicalDeviceSurfacePresentModesKHR(gVkPhysicalDevice, surface, &presentModeCount, nullptr);

  if(presentModeCount)
  {
    details.presentModes.resize(presentModeCount);

    if(tableVk.GetPhysicalDeviceSurfacePresentModesKHR)
    {
      tableVk.GetPhysicalDeviceSurfacePresentModesKHR(
        gVkPhysicalDevice,
        surface,
        &presentModeCount,
        details.presentModes.data()
      );
    }
  }

  return details;
}

VkSurfaceFormatKHR VulkanTutorialChooseSwapSurfaceFormat(
  const std::vector<VkSurfaceFormatKHR>& availableFormats
)
{
  for(const auto& availableFormat : availableFormats)
  {
    if(availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
      availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR
    )
    {
      return availableFormat;
    }
  }

  return availableFormats[0];
}

VkPresentModeKHR VulkanTutorialChooseSwapPresentMode(
  const std::vector<VkPresentModeKHR>& availablePresentModes
)
{
  for(const auto& availablePresentMode : availablePresentModes)
  {
    if(availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
      return availablePresentMode;
  }

  return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanTutorialChooseSwapExtent(
  const VkSurfaceCapabilitiesKHR& capabilities
)
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

VulkanTutorialQueueFamilyIndices VulkanTutorialFindQueueFamilies(
  VkSurfaceKHR& surface
)
{
  VulkanTutorialQueueFamilyIndices indices;

  uint32_t queueFamilyCount = 0;

  if(tableVk.GetPhysicalDeviceQueueFamilyProperties)
    tableVk.GetPhysicalDeviceQueueFamilyProperties(gVkPhysicalDevice, &queueFamilyCount, nullptr);

  std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);

  if(tableVk.GetPhysicalDeviceQueueFamilyProperties)
    tableVk.GetPhysicalDeviceQueueFamilyProperties(gVkPhysicalDevice, &queueFamilyCount, queueFamilies.data() );

  int family = 0;
  for(const auto& queueFamily : queueFamilies)
  {
    if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
      indices.graphicsFamily = family;

    VkBool32 presentSupport = false;

    if(tableVk.GetPhysicalDeviceSurfaceSupportKHR)
      tableVk.GetPhysicalDeviceSurfaceSupportKHR(gVkPhysicalDevice, family, surface, &presentSupport);

    if(presentSupport)
      indices.presentFamily = family;

    if(VulkanTutorialQueueFamilyIndices_isComplete(indices) )
      break;

    family++;
  }

  return indices;
}

bool VulkanTutorialCheckDeviceExtensionSupport(
)
{
  uint32_t extensionCount = 0;

  if(tableVk.EnumerateDeviceExtensionProperties)
    tableVk.EnumerateDeviceExtensionProperties(gVkPhysicalDevice, nullptr, &extensionCount, nullptr);

  std::vector<VkExtensionProperties> availableExtensions(extensionCount);

  if(tableVk.EnumerateDeviceExtensionProperties)
    tableVk.EnumerateDeviceExtensionProperties(gVkPhysicalDevice, nullptr, &extensionCount, availableExtensions.data() );

  std::set<std::string> requiredExtensions(
    VulkanTutorialDeviceExtensions.begin(),
    VulkanTutorialDeviceExtensions.end()
  );

  for(const auto& extension : availableExtensions)
    requiredExtensions.erase(extension.extensionName);

  return requiredExtensions.empty();
}

bool VulkanTutorialIsDeviceSuitable(
  VkSurfaceKHR& surface
)
{
  VulkanTutorialQueueFamilyIndices indices = VulkanTutorialFindQueueFamilies(surface);

  bool extensionsSupported = VulkanTutorialCheckDeviceExtensionSupport();

  bool swapChainAdequate = false;

  if(extensionsSupported)
  {
    VulkanTutorialSwapChainSupportDetails swapChainSupport =
      VulkanTutorialQuerySwapChainSupport(surface);

    swapChainAdequate = ( !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty() );
  }

  VkPhysicalDeviceFeatures supportedFeatures;

  if(tableVk.GetPhysicalDeviceFeatures)
    tableVk.GetPhysicalDeviceFeatures(gVkPhysicalDevice, &supportedFeatures);

  bool result =
    VulkanTutorialQueueFamilyIndices_isComplete(indices) &&
    extensionsSupported &&
    swapChainAdequate &&
    supportedFeatures.samplerAnisotropy;

  return result;
}

void VulkanTutorialCreateSwapChain(
  VkSurfaceKHR& surface,
  VkSwapchainKHR& swapChain,
  std::vector<VkImage>& swapChainImages,
  VkFormat& swapChainImageFormat,
  VkExtent2D& swapChainExtent
)
{
  VulkanTutorialSwapChainSupportDetails swapChainSupport = VulkanTutorialQuerySwapChainSupport(surface);

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

  VulkanTutorialQueueFamilyIndices indices = VulkanTutorialFindQueueFamilies(surface);

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

  if(tableVk.CreateSwapchainKHR)
  {
    if(tableVk.CreateSwapchainKHR(gVkDevice, &createInfo, nullptr, &swapChain) != VK_SUCCESS)
      throw std::runtime_error("failed to create swap chain!");
  }

  if(tableVk.GetSwapchainImagesKHR)
    tableVk.GetSwapchainImagesKHR(gVkDevice, swapChain, &imageCount, nullptr);

  swapChainImages.resize(imageCount);

  if(tableVk.GetSwapchainImagesKHR)
    tableVk.GetSwapchainImagesKHR(gVkDevice, swapChain, &imageCount, swapChainImages.data() );

  swapChainImageFormat = surfaceFormat.format;
  swapChainExtent = extent;
}

void VulkanTutorialCreateImageViews(
  std::vector<VkImage>& swapChainImages,
  VkFormat& swapChainImageFormat,
  std::vector<VkImageView>& swapChainImageViews
)
{
  swapChainImageViews.resize(swapChainImages.size() );

  for(uint32_t i = 0; i < swapChainImages.size(); i++)
  {
    swapChainImageViews[i] = VulkanTutorialCreateImageView(
      swapChainImages[i],
      swapChainImageFormat,
      VK_IMAGE_ASPECT_COLOR_BIT
    );
  }
}

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
)
{
  int width = 0, height = 0;

  // todo
  //glfwGetFramebufferSize(window, &width, &height);

  while( !width || !height)
  {
    // todo
    //glfwGetFramebufferSize(window, &width, &height);

    // todo
    //glfwWaitEvents();
  }

  if(tableVk.DeviceWaitIdle)
    tableVk.DeviceWaitIdle(gVkDevice);

  VulkanTutorialCleanupSwapChain(
    swapChain,
    swapChainImageViews,
    swapChainFramebuffers,
    depthImage,
    depthImageMemory,
    depthImageView
  );

  VulkanTutorialCreateSwapChain(
    surface,
    swapChain,
    swapChainImages,
    swapChainImageFormat,
    swapChainExtent
  );

  VulkanTutorialCreateImageViews(swapChainImages, swapChainImageFormat, swapChainImageViews);

  VulkanTutorialCreateDepthResources(
    swapChainExtent,
    depthImage,
    depthImageMemory,
    depthImageView
  );

  VulkanTutorialCreateFramebuffers(
    swapChainExtent,
    swapChainImageViews,
    swapChainFramebuffers,
    renderPass,
    depthImageView
  );
}

#if 0
std::vector<const char*> VulkanTutorialGetRequiredExtensions()
{
  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions = 0;

  // todo
  //glfwExtensions = glfwGetRequiredInstanceExtensions( &glfwExtensionCount);

  std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

  if(VulkanTutorialEnableValidationLayers)
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

  return extensions;
}
#endif

#if 0
bool VulkanTutorialCheckValidationLayerSupport()
{
  uint32_t layerCount = 0;

  if(tableVk.EnumerateInstanceLayerProperties)
    tableVk.EnumerateInstanceLayerProperties( &layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);

  if(tableVk.EnumerateInstanceLayerProperties)
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
#endif

#if 0
std::vector<char> VulkanTutorialReadFile(
  const std::string& filename
)
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
#endif

#if 0
VkBool32 VulkanTutorialDebugCallback(
  VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
  VkDebugUtilsMessageTypeFlagsEXT messageType,
  const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
  void* pUserData
)
{
  std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
  return VK_FALSE;
}
#endif

#if 0
int VulkanTutorialMain(
)
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
#endif

VkShaderModule VulkanTutorialCreateShaderModule(
  const std::vector<char>& code
)
{
  VkShaderModuleCreateInfo createInfo {};
  createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  createInfo.codeSize = code.size();

  createInfo.pCode = (const uint32_t*)code.data();

  VkShaderModule shaderModule;

  if(tableVk.CreateShaderModule)
  {
    if(tableVk.CreateShaderModule(gVkDevice, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
      throw std::runtime_error("failed to create shader module!");
  }

  return shaderModule;
}

#if 0
void run(
)
{
  initWindow();
  initVulkan();
  mainLoop();
  cleanup();
}
#endif

#if 0
void initWindow(
)
{
  // todo
  glfwInit();

  // todo
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  // todo
  window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);

  // todo
  glfwSetWindowUserPointer(window, this);

  // todo
  glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}
#endif

#if 0
// todo
void framebufferResizeCallback(
  GLFWwindow* window,
  int width,
  int height
)
{
  // todo
  HelloTriangleApplication* app = (HelloTriangleApplication*)glfwGetWindowUserPointer(window);

  // todo
  app->framebufferResized = true;
}
#endif

#if 0
void initVulkan(
  VkImage& textureImage,
  VkImageView& textureImageView
)
{
  VulkanTutorialCreateInstance();
  VulkanTutorialSetupDebugMessenger();
  VulkanTutorialCreateSurface();
  VulkanTutorialPickPhysicalDevice();
  VulkanTutorialCreateLogicalDevice();
  VulkanTutorialCreateSwapChain();
  VulkanTutorialCreateImageViews();
  VulkanTutorialCreateRenderPass();
  VulkanTutorialCreateDescriptorSetLayout();
  VulkanTutorialCreateGraphicsPipeline();
  VulkanTutorialCreateCommandPool();
  VulkanTutorialCreateDepthResources();
  VulkanTutorialCreateFramebuffers();

  VulkanTutorialCreateTextureImage();

  textureImageView = VulkanTutorialCreateImageView(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);

  VulkanTutorialCreateTextureSampler();
  VulkanTutorialCreateVertexBuffer();
  VulkanTutorialCreateIndexBuffer();

  VulkanTutorialCreateUniformBuffers();
  VulkanTutorialCreateDescriptorPool();
  VulkanTutorialUpdateDescriptorSets();
  VulkanTutorialCreateCommandBuffers();
  VulkanTutorialCreateSyncObjects();
}
#endif

#if 0
void mainLoop(
)
{
  // todo
  while( !glfwWindowShouldClose(window) )
  {
    // todo
    glfwPollEvents();

    drawFrame();
  }

  if(tableVk.DeviceWaitIdle)
    tableVk.DeviceWaitIdle(gVkDevice);
}
#endif

#if 0
void VulkanTutorialCleanup(
  VkCommandPool& commandPool
)
{
  cleanupSwapChain();

  if(tableVk.DestroyPipeline)
    tableVk.DestroyPipeline(gVkDevice, graphicsPipeline, nullptr);

  if(tableVk.DestroyPipelineLayout)
    tableVk.DestroyPipelineLayout(gVkDevice, pipelineLayout, nullptr);

  if(tableVk.DestroyRenderPass)
    tableVk.DestroyRenderPass(gVkDevice, renderPass, nullptr);

  for(size_t i = 0; i < VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT; i++)
  {
    if(tableVk.DestroyBuffer)
      tableVk.DestroyBuffer(gVkDevice, uniformBuffers[i], nullptr);

    if(tableVk.FreeMemory)
      tableVk.FreeMemory(gVkDevice, uniformBuffersMemory[i], nullptr);
  }

  if(tableVk.DestroyDescriptorPool)
    tableVk.DestroyDescriptorPool(gVkDevice, descriptorPool, nullptr);

  if(tableVk.DestroySampler)
    tableVk.DestroySampler(gVkDevice, textureSampler, nullptr);

  if(tableVk.DestroyImageView)
    tableVk.DestroyImageView(gVkDevice, textureImageView, nullptr);

  if(tableVk.DestroyImage)
    tableVk.DestroyImage(gVkDevice, textureImage, nullptr);

  if(tableVk.FreeMemory)
    tableVk.FreeMemory(gVkDevice, textureImageMemory, nullptr);

  if(tableVk.DestroyDescriptorSetLayout)
    tableVk.DestroyDescriptorSetLayout(gVkDevice, descriptorSetLayout, nullptr);

  if(tableVk.DestroyBuffer)
    tableVk.DestroyBuffer(gVkDevice, indexBuffer, nullptr);

  if(tableVk.FreeMemory)
    tableVk.FreeMemory(gVkDevice, indexBufferMemory, nullptr);

  if(tableVk.DestroyBuffer)
    tableVk.DestroyBuffer(gVkDevice, vertexBuffer, nullptr);

  if(tableVk.FreeMemory)
    tableVk.FreeMemory(gVkDevice, vertexBufferMemory, nullptr);

  for(size_t i = 0; i < VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT; i++)
  {
    if(tableVk.DestroySemaphore)
    {
      tableVk.DestroySemaphore(gVkDevice, renderFinishedSemaphores[i], nullptr);
      tableVk.DestroySemaphore(gVkDevice, imageAvailableSemaphores[i], nullptr);
    }

    if(tableVk.DestroyFence)
      tableVk.DestroyFence(gVkDevice, inFlightFences[i], nullptr);
  }

  if(tableVk.DestroyCommandPool)
    tableVk.DestroyCommandPool(gVkDevice, commandPool, nullptr);

  if(tableVk.DestroyDevice)
    tableVk.DestroyDevice(gVkDevice, nullptr);

  if(enableValidationLayers)
    DestroyDebugUtilsMessengerEXT(gVkInstance, debugMessenger, nullptr);

  if(tableVk.DestroySurfaceKHR)
    tableVk.DestroySurfaceKHR(gVkInstance, surface, nullptr);

  if(tableVk.DestroyInstance)
    tableVk.DestroyInstance(gVkInstance, nullptr);

  // todo
  glfwDestroyWindow(window);

  // todo
  glfwTerminate();
}
#endif

#if 0
void createInstance(
)
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

  if(tableVk.CreateInstance)
  {
    if(tableVk.CreateInstance( &createInfo, nullptr, &gVkInstance) != VK_SUCCESS)
      throw std::runtime_error("failed to create instance!");
  }
}
#endif

#if 0
void populateDebugMessengerCreateInfo(
  VkDebugUtilsMessengerCreateInfoEXT& createInfo
)
{
  createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

  createInfo.messageSeverity =
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

  createInfo.messageType =
    VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

  createInfo.pfnUserCallback = debugCallback;
}
#endif

#if 0
void setupDebugMessenger(
)
{
  if( !enableValidationLayers)
    return;

  VkDebugUtilsMessengerCreateInfoEXT createInfo;
  populateDebugMessengerCreateInfo(createInfo);

  if(CreateDebugUtilsMessengerEXT(gVkInstance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS)
    throw std::runtime_error("failed to set up debug messenger!");
}
#endif

#if 0
void createSurface(
)
{
  // todo
  if(glfwCreateWindowSurface(gVkInstance, window, nullptr, &surface) != VK_SUCCESS)
    throw std::runtime_error("failed to create window surface!");
}
#endif

#if 0
void pickPhysicalDevice(
)
{
  uint32_t deviceCount = 0;

  if(tableVk.EnumeratePhysicalDevices)
    tableVk.EnumeratePhysicalDevices(gVkInstance, &deviceCount, nullptr);

  if( !deviceCount)
    throw std::runtime_error("failed to find GPUs with Vulkan support!");

  std::vector<VkPhysicalDevice> physicalDevices(deviceCount);

  if(tableVk.EnumeratePhysicalDevices)
    tableVk.EnumeratePhysicalDevices(gVkInstance, &deviceCount, physicalDevices.data() );

  gVkPhysicalDevice = VK_NULL_HANDLE;

  for(const auto& physicalDevice : physicalDevices)
  {
    if(isDeviceSuitable(physicalDevice) )
    {
      gVkPhysicalDevice = physicalDevice;
      break;
    }
  }

  if(gVkPhysicalDevice == VK_NULL_HANDLE)
    throw std::runtime_error("failed to find a suitable GPU!");
}
#endif

#if 0
void createLogicalDevice(
  VkSurfaceKHR& surface
)
{
  VulkanTutorialQueueFamilyIndices indices = VulkanTutorialFindQueueFamilies(surface);

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
  // todo
  deviceFeatures.samplerAnisotropy = VK_TRUE;

  VkDeviceCreateInfo createInfo {};
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

  if(tableVk.CreateDevice)
  {
    if(tableVk.CreateDevice(gVkPhysicalDevice, &createInfo, nullptr, &gVkDevice) != VK_SUCCESS)
      throw std::runtime_error("failed to create logical device!");
  }

  if(tableVk.GetDeviceQueue)
  {
    tableVk.GetDeviceQueue(gVkDevice, indices.graphicsFamily.value(), 0, &graphicsQueue);
    tableVk.GetDeviceQueue(gVkDevice, indices.presentFamily.value(), 0, &presentQueue);
  }
}
#endif

void VulkanTutorialCreateDescriptorSetLayout(
  VkDescriptorSetLayout& descriptorSetLayout
)
{
  VkDescriptorSetLayoutBinding uboLayoutBinding {};
  uboLayoutBinding.binding = 0;
  uboLayoutBinding.descriptorCount = 1;
  uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  uboLayoutBinding.pImmutableSamplers = nullptr;
  uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

  VkDescriptorSetLayoutBinding samplerLayoutBinding {};
  samplerLayoutBinding.binding = 1;
  samplerLayoutBinding.descriptorCount = 1;
  samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  samplerLayoutBinding.pImmutableSamplers = nullptr;
  samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

  std::array<VkDescriptorSetLayoutBinding, 2> bindings = {uboLayoutBinding, samplerLayoutBinding};
  VkDescriptorSetLayoutCreateInfo layoutInfo {};
  layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size() );
  layoutInfo.pBindings = bindings.data();

  if(tableVk.CreateDescriptorSetLayout)
  {
    if(tableVk.CreateDescriptorSetLayout(gVkDevice, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
      throw std::runtime_error("failed to create descriptor set layout!");
  }
}

#if 0
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

  auto bindingDescription = GeometryVertex::getBindingDescription();
  auto attributeDescriptions = GeometryVertex::getAttributeDescriptions();

  vertexInputInfo.vertexBindingDescriptionCount = 1;
  vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size() );
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

  colorBlendAttachment.colorWriteMask =
    VK_COLOR_COMPONENT_R_BIT |
    VK_COLOR_COMPONENT_G_BIT |
    VK_COLOR_COMPONENT_B_BIT |
    VK_COLOR_COMPONENT_A_BIT;

  colorBlendAttachment.blendEnable = VK_TRUE; // todo

  VkPipelineColorBlendStateCreateInfo colorBlending {};
  colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  colorBlending.logicOpEnable = VK_FALSE;
  colorBlending.logicOp = VK_LOGIC_OP_COPY;
  colorBlending.attachmentCount = 1;
  colorBlending.pAttachments = &colorBlendAttachment;
  colorBlending.blendConstants = 0.0f;

  std::vector<VkDynamicState> dynamicStates = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};

  VkPipelineDynamicStateCreateInfo dynamicState {};
  dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size() );
  dynamicState.pDynamicStates = dynamicStates.data();

  VkPipelineLayoutCreateInfo pipelineLayoutInfo {};
  pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipelineLayoutInfo.setLayoutCount = 1;
  pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;

  if(tableVk.CreatePipelineLayout)
  {
    if(tableVk.CreatePipelineLayout(gVkDevice, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
      throw std::runtime_error("failed to create pipeline layout!");
  }

  VkGraphicsPipelineCreateInfo pipelineInfo {};
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

  if(tableVk.CreateGraphicsPipelines)
  {
    if(tableVk.CreateGraphicsPipelines(gVkDevice, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS)
      throw std::runtime_error("failed to create graphics pipeline!");
  }

  if(tableVk.DestroyShaderModule)
  {
    tableVk.DestroyShaderModule(gVkDevice, fragShaderModule, nullptr);
    tableVk.DestroyShaderModule(gVkDevice, vertShaderModule, nullptr);
  }
}
#endif

void VulkanTutorialCreateCommandPool(
  VkSurfaceKHR& surface,
  VkCommandPool& commandPool
)
{
  VulkanTutorialQueueFamilyIndices queueFamilyIndices = VulkanTutorialFindQueueFamilies(surface);

  VkCommandPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

  if(tableVk.CreateCommandPool)
  {
    if(tableVk.CreateCommandPool(gVkDevice, &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
      throw std::runtime_error("failed to create graphics command pool!");
  }
}

#if 0
bool hasStencilComponent(VkFormat format)
{
  return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
}
#endif

void VulkanTutorialCreateTextureImage(
  VkQueue& graphicsQueue,
  VkCommandPool& commandPool,
  TextureBlah& textureBlah
)
{
  int fileSize = 0;

  unsigned char* buffer = AnagLoadFileBlah(textureBlah.fileName, &fileSize);

  int texWidth = 0;
  int texHeight = 0;

  stbi_uc* pixels = 0;

  if(buffer)
  {
    int texChannels = 0;

    pixels = stbi_load_from_memory(buffer, fileSize, &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

    textureBlah.width = texWidth;
    textureBlah.height = texHeight;

    if(pixels)
      Log::Write(Log::Level::Info, Fmt("stbi_load_from_memory pixels valid pointer\n") );
    else
      Log::Write(Log::Level::Info, Fmt("stbi_load_from_memory null pointer %s\n", stbi_failure_reason() ) );

    // todo
    free(buffer);
    buffer = 0;
  }

  VkDeviceSize imageSize = texWidth * texHeight * 4;

  if( !pixels)
    throw std::runtime_error("failed to load texture image!");

  VkBuffer stagingBuffer = VK_NULL_HANDLE;
  VkDeviceMemory stagingBufferMemory = VK_NULL_HANDLE;

  VulkanTutorialCreateBuffer(
    imageSize,
    VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
    stagingBuffer,
    stagingBufferMemory
  );

  void* data = 0;

  if(tableVk.MapMemory)
  {
    tableVk.MapMemory(gVkDevice, stagingBufferMemory, 0, imageSize, 0, &data);
  }

  if(data)
    memcpy(data, pixels, static_cast<size_t>(imageSize) );

  if(tableVk.UnmapMemory)
    tableVk.UnmapMemory(gVkDevice, stagingBufferMemory);

  // todo
  stbi_image_free(pixels);

  VulkanTutorialCreateImage(
    texWidth,
    texHeight,
    VK_FORMAT_R8G8B8A8_SRGB,
    VK_IMAGE_TILING_OPTIMAL,
    VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
    textureBlah.image,
    textureBlah.deviceMemory
  );

  VulkanTutorialTransitionImageLayout(
    graphicsQueue,
    commandPool,
    textureBlah.image,
    VK_FORMAT_R8G8B8A8_SRGB,
    VK_IMAGE_LAYOUT_UNDEFINED,
    VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
  );

  VulkanTutorialCopyBufferToImage(
    graphicsQueue,
    commandPool,
    stagingBuffer,
    textureBlah.image,
    static_cast<uint32_t>(texWidth),
    static_cast<uint32_t>(texHeight)
  );

  VulkanTutorialTransitionImageLayout(
    graphicsQueue,
    commandPool,
    textureBlah.image,
    VK_FORMAT_R8G8B8A8_SRGB,
    VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
    VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
  );

  if(tableVk.DestroyBuffer)
    tableVk.DestroyBuffer(gVkDevice, stagingBuffer, nullptr);

  if(tableVk.FreeMemory)
    tableVk.FreeMemory(gVkDevice, stagingBufferMemory, nullptr);
}

void VulkanTutorialCreateTextureSampler(
  VkSampler& textureSampler
)
{
  VkPhysicalDeviceProperties properties {};

  if(tableVk.GetPhysicalDeviceProperties)
    tableVk.GetPhysicalDeviceProperties(gVkPhysicalDevice, &properties);

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

  if(tableVk.CreateSampler)
  {
    if(tableVk.CreateSampler(gVkDevice, &samplerInfo, nullptr, &textureSampler) != VK_SUCCESS)
      throw std::runtime_error("failed to create texture sampler!");
  }
}

void VulkanTutorialCopyBufferToImage(
  VkQueue& graphicsQueue,
  VkCommandPool& commandPool,
  VkBuffer& buffer,
  VkImage& image,
  uint32_t width,
  uint32_t height
)
{
  VkCommandBuffer commandBuffer = VulkanTutorialsBeginSingleTimeCommands(commandPool);

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

  if(tableVk.CmdCopyBufferToImage)
    tableVk.CmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

  VulkanTutorialEndSingleTimeCommands(graphicsQueue, commandPool, commandBuffer);
}

#if 0
void createVertexBuffer()
{
  VkDeviceSize bufferSize = sizeof(VulkanTutorialVertices[0] ) * VulkanTutorialVertices.size();

  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;

  createBuffer(
    bufferSize,
    VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
    stagingBuffer,
    stagingBufferMemory
  );

  void* data = 0;

  if(tableVk.MapMemory)
    tableVk.MapMemory(gVkDevice, stagingBufferMemory, 0, bufferSize, 0, &data);

  if(data)
    memcpy(data, VulkanTutorialVertices.data(), (size_t)bufferSize);

  if(tableVk.UnmapMemory)
    tableVk.UnmapMemory(gVkDevice, stagingBufferMemory);

  createBuffer(
    bufferSize,
    VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
    vertexBuffer,
    vertexBufferMemory
  );

  copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

  if(tableVk.DestroyBuffer)
    tableVk.DestroyBuffer(gVkDevice, stagingBuffer, nullptr);

  if(tableVk.FreeMemory)
    tableVk.FreeMemory(gVkDevice, stagingBufferMemory, nullptr);
}
#endif

#if 0
void createIndexBuffer()
{
  VkDeviceSize bufferSize = sizeof(VulkanTutorialIndices[0] ) * VulkanTutorialIndices.size();

  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;
  createBuffer(
    bufferSize,
    VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
    stagingBuffer,
    stagingBufferMemory
  );

  void* data = 0;

  if(tableVk.MapMemory)
    tableVk.MapMemory(gVkDevice, stagingBufferMemory, 0, bufferSize, 0, &data);

  if(data)
    memcpy(data, VulkanTutorialIndices.data(), (size_t) bufferSize);

  if(tableVk.UnmapMemory)
    tableVk.UnmapMemory(gVkDevice, stagingBufferMemory);

  createBuffer(
    bufferSize,
    VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
    indexBuffer,
    indexBufferMemory
  );

  copyBuffer(stagingBuffer, indexBuffer, bufferSize);

  if(tableVk.DestroyBuffer)
    tableVk.DestroyBuffer(gVkDevice, stagingBuffer, nullptr);

  if(tableVk.FreeMemory)
    tableVk.FreeMemory(gVkDevice, stagingBufferMemory, nullptr);
}
#endif

void VulkanTutorialCreateUniformBuffers(
  std::vector<VkBuffer>& uniformBuffers,
  std::vector<VkDeviceMemory>& uniformBuffersMemory,
  std::vector<void*>& uniformBuffersMapped
)
{
  VkDeviceSize bufferSize = sizeof(VulkanTutorialUniformBufferObject);

  uniformBuffers.resize(VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT);
  uniformBuffersMemory.resize(VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT);
  uniformBuffersMapped.resize(VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT);

  for(size_t i = 0; i < VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT; i++)
  {
    VulkanTutorialCreateBuffer(
      bufferSize,
      VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
      VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
      uniformBuffers[i],
      uniformBuffersMemory[i]
    );

    if(tableVk.MapMemory)
      tableVk.MapMemory(gVkDevice, uniformBuffersMemory[i], 0, bufferSize, 0, &uniformBuffersMapped[i] );
  }
}

void VulkanTutorialCreateDescriptorPool(
  VkDescriptorPool& descriptorPool
)
{
  std::array<VkDescriptorPoolSize, 2> poolSizes {};

  poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  poolSizes[0].descriptorCount = static_cast<uint32_t>(VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT);

  poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  poolSizes[1].descriptorCount = static_cast<uint32_t>(VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT);

  VkDescriptorPoolCreateInfo poolInfo {};
  poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size() );
  poolInfo.pPoolSizes = poolSizes.data();
  poolInfo.maxSets = static_cast<uint32_t>(VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT);

  if(tableVk.CreateDescriptorPool)
  {
    if(tableVk.CreateDescriptorPool(gVkDevice, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS)
      throw std::runtime_error("failed to create descriptor pool!");
  }
}

void VulkanTutorialUpdateDescriptorSets(
  VkImageView& textureImageView,
  VkSampler& textureSampler,
  std::vector<VkBuffer>& uniformBuffers,
  VkDescriptorSetLayout descriptorSetLayout,
  VkDescriptorPool descriptorPool,
  std::vector<VkDescriptorSet>& descriptorSets
)
{
  std::vector<VkDescriptorSetLayout> layouts(VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT, descriptorSetLayout);

  VkDescriptorSetAllocateInfo allocInfo {};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = descriptorPool;
  allocInfo.descriptorSetCount = static_cast<uint32_t>(VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT);
  allocInfo.pSetLayouts = layouts.data();

  descriptorSets.resize(VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT);

  if(tableVk.AllocateDescriptorSets)
  {
    if(tableVk.AllocateDescriptorSets(gVkDevice, &allocInfo, descriptorSets.data() ) != VK_SUCCESS)
      throw std::runtime_error("failed to allocate descriptor sets!");
  }

  for(size_t i = 0; i < VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT; i++)
  {
    VkDescriptorBufferInfo bufferInfo {};
    bufferInfo.buffer = uniformBuffers[i];
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(VulkanTutorialUniformBufferObject);

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

    if(tableVk.UpdateDescriptorSets)
    {
      tableVk.UpdateDescriptorSets(
        gVkDevice,
        static_cast<uint32_t>(descriptorWrites.size() ),
        descriptorWrites.data(),
        0,
        nullptr
      );
    }
  }
}

void VulkanTutorialCreateBuffer(
  VkDeviceSize size,
  VkBufferUsageFlags usage,
  VkMemoryPropertyFlags properties,
  VkBuffer& buffer,
  VkDeviceMemory& bufferMemory
)
{
  VkBufferCreateInfo bufferInfo {};
  bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  bufferInfo.size = size;
  bufferInfo.usage = usage;
  bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  if(tableVk.CreateBuffer)
  {
    if(tableVk.CreateBuffer(gVkDevice, &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
      throw std::runtime_error("failed to create buffer!");
  }

  VkMemoryRequirements memRequirements;

  if(tableVk.GetBufferMemoryRequirements)
    tableVk.GetBufferMemoryRequirements(gVkDevice, buffer, &memRequirements);

  VkMemoryAllocateInfo allocInfo {};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = VulkanTutorialFindMemoryType(memRequirements.memoryTypeBits, properties);

  if(tableVk.AllocateMemory)
  {
    if(tableVk.AllocateMemory(gVkDevice, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS)
      throw std::runtime_error("failed to allocate buffer memory!");
  }

  if(tableVk.BindBufferMemory)
    tableVk.BindBufferMemory(gVkDevice, buffer, bufferMemory, 0);
}

#if 0
void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
{
  VkCommandBuffer commandBuffer = beginSingleTimeCommands();

  VkBufferCopy copyRegion {};
  copyRegion.size = size;

  if(tableVk.CmdCopyBuffer)
    tableVk.CmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

  endSingleTimeCommands(commandBuffer);
}
#endif

void VulkanTutorialCreateCommandBuffers(
  VkCommandPool& commandPool,
  std::vector<VkCommandBuffer>& commandBuffers
)
{
  commandBuffers.resize(VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT);

  VkCommandBufferAllocateInfo allocInfo {};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.commandPool = commandPool;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

  if(tableVk.AllocateCommandBuffers)
  {
    if(tableVk.AllocateCommandBuffers(gVkDevice, &allocInfo, commandBuffers.data() ) != VK_SUCCESS)
      throw std::runtime_error("failed to allocate command buffers!");
  }
}

void VulkanTutorialCreateSyncObjects(
  std::vector<VkSemaphore> imageAvailableSemaphores,
  std::vector<VkSemaphore> renderFinishedSemaphores,
  std::vector<VkFence> inFlightFences
)
{
  imageAvailableSemaphores.resize(VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT);
  renderFinishedSemaphores.resize(VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT);
  inFlightFences.resize(VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT);

  VkSemaphoreCreateInfo semaphoreInfo {};
  semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  VkFenceCreateInfo fenceInfo {};
  fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  for(size_t i = 0; i < VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT; i++)
  {
    if(tableVk.CreateSemaphore)
    {
      if(tableVk.CreateSemaphore(gVkDevice, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i] ) != VK_SUCCESS)
        throw std::runtime_error("failed to create synchronization objects for a frame!");

      if(tableVk.CreateSemaphore(gVkDevice, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i] ) != VK_SUCCESS)
        throw std::runtime_error("failed to create synchronization objects for a frame!");
    }

    if(tableVk.CreateFence)
    {
      if(tableVk.CreateFence(gVkDevice, &fenceInfo, nullptr, &inFlightFences[i] ) != VK_SUCCESS)
        throw std::runtime_error("failed to create synchronization objects for a frame!");
    }
  }
}

#if 0
void updateUniformBuffer(uint32_t currentImage)
{
  static auto startTime = std::chrono::high_resolution_clock::now();

  auto currentTime = std::chrono::high_resolution_clock::now();
  float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

  VulkanTutorialUniformBufferObject ubo {};

  ubo.blahModel = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f) );
  ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) );
  ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float) swapChainExtent.height, 0.1f, 10.0f);
  ubo.proj[1][1] *= -1;

  memcpy(uniformBuffersMapped[currentImage], &ubo, sizeof(ubo) );
}
#endif

#if 0
void drawFrame()
{
  do
  {
    if(tableVk.WaitForFences)
      tableVk.WaitForFences(gVkDevice, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex = 0;

    VkResult result = XR_ERROR_VALIDATION_FAILURE;

    if(tableVk.AcquireNextImageKHR)
    {
      result = tableVk.AcquireNextImageKHR(
        gVkDevice,
        swapChain,
        UINT64_MAX,
        imageAvailableSemaphores[currentFrame],
        VK_NULL_HANDLE,
        &imageIndex
      );
    }

    if(result == VK_ERROR_OUT_OF_DATE_KHR)
    {
      recreateSwapChain();
      break;
    }
    else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
    {
      throw std::runtime_error("failed to acquire swap chain image!");
    }

    updateUniformBuffer(currentFrame);

    if(tableVk.ResetFences)
      tableVk.ResetFences(gVkDevice, 1, &inFlightFences[currentFrame] );

    if(tableVk.ResetCommandBuffer)
      tableVk.ResetCommandBuffer(commandBuffers[currentFrame], /*VkCommandBufferResetFlagBits*/0);

    recordCommandBuffer(commandBuffers[currentFrame], imageIndex);

    VkSubmitInfo submitInfo {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame] };
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffers[currentFrame];

    VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame] };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if(tableVk.QueueSubmit)
    {
      if(tableVk.QueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame] ) != VK_SUCCESS)
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {swapChain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    result = XR_ERROR_VALIDATION_FAILURE;

    if(tableVk.QueuePresentKHR)
      result = tableVk.QueuePresentKHR(presentQueue, &presentInfo);

    if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized)
    {
      framebufferResized = false;
      recreateSwapChain();
    }
    else if(result != VK_SUCCESS)
    {
      throw std::runtime_error("failed to present swap chain image!");
    }

    currentFrame = (currentFrame + 1) % VULKAN_TUTORIAL_MAX_FRAMES_IN_FLIGHT;

  }while(0);
}
#endif
