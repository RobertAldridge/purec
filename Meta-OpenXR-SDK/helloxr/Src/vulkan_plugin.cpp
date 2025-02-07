
// vulkan_plugin.cpp

#include "header.h"

VkInstance gVkInstance = VK_NULL_HANDLE;

VkDevice gVkDevice = VK_NULL_HANDLE;

VkPhysicalDevice gVkPhysicalDevice = VK_NULL_HANDLE;

VkPipelineLayout gVkPipelineLayout = VK_NULL_HANDLE;

VkPhysicalDeviceMemoryProperties gMemoryAllocatorMemoryProperties {};

CmdBufferStateEnum gCmdBufferState {CmdBufferStateEnum::Undefined};

VkCommandPool gCmdBufferPool {VK_NULL_HANDLE};

VkCommandBuffer gCmdBufferBuffer {VK_NULL_HANDLE};

VkFence gCmdBufferExecFence {VK_NULL_HANDLE};

VkBuffer gVertexBufferBaseIdxBuf {VK_NULL_HANDLE};

VkDeviceMemory gVertexBufferBaseIdxMem {VK_NULL_HANDLE};

VkBuffer gVertexBufferBaseVtxBuf {VK_NULL_HANDLE};

VkDeviceMemory gVertexBufferBaseVtxMem {VK_NULL_HANDLE};

VkVertexInputBindingDescription gVertexBufferBaseBindDesc {};

std::vector<VkVertexInputAttributeDescription> gVertexBufferBaseAttrDesc {};

VertexBufferBaseBlah gVertexBufferBaseCount = {0, 0};

std::array<VkPipelineShaderStageCreateInfo, 2> gShaderProgramShaderInfo
{
  {
    {VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO},
    {VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO}
  }
};

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
          CHECK_VULKANCMD(tableVk.AllocateMemory(gVkDevice, &memAlloc, nullptr, mem) );

        return;
      }
    }
  }

  THROW_CHECK("Memory format not supported");
}

#if 0
void CmdBuffer_CmdBuffer_Destructor()
{
  gCmdBufferState = CmdBufferStateEnum::Undefined;

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

#if 0
void SwapchainImageContext_SwapchainImageContext_PipelineDynamic(int index, VkDynamicState state)
{
  //m_swapchainImageContextPipe_pipelineDynamicStateEnables[index].emplace_back(state);
  m_swapchainImageContextPipe_pipelineDynamicStateEnables[index].push_back(state);
}
#endif

#if 0
void SwapchainImageContext_SwapchainImageContext_PipelineRelease(int index)
{
  if(gVkDevice)
  {
    if(m_swapchainImageContextPipe_pipelinePipe[index] != VK_NULL_HANDLE && tableVk.DestroyPipeline)
      tableVk.DestroyPipeline(gVkDevice, m_swapchainImageContextPipe_pipelinePipe[index], nullptr);
  }

  m_swapchainImageContextPipe_pipelinePipe[index] = VK_NULL_HANDLE;
}
#endif

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

#if 0
void VulkanGraphicsPlugin_VulkanGraphicsPlugin_Destructor()
{
  if(gVkDevice)
  {
    if(gVkPipelineLayout != VK_NULL_HANDLE && tableVk.DestroyPipelineLayout)
      tableVk.DestroyPipelineLayout(gVkDevice, gVkPipelineLayout, nullptr);

    gVkPipelineLayout = VK_NULL_HANDLE;
  }
}
#endif

#if 0
// note: The output must not outlive the input - this modifies the input and returns a collection of views into that modified input!
std::vector<const char*> VulkanGraphicsPlugin_VulkanGraphicsPluginParseExtensionString(char* names)
{
  std::vector<const char*> list;

  while(*names != 0)
  {
    list.push_back(names);

    while( *(++names) != 0)
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
#endif

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanGraphicsPlugin_debugMessageThunk(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* /*pUserData*/)
{
  VkBool32 result = VK_FALSE;

  //return VulkanGraphicsPlugin_VulkanGraphicsPluginDebugMessage(messageSeverity, messageTypes, pCallbackData);
  //VkBool32 VulkanGraphicsPlugin_VulkanGraphicsPluginDebugMessage(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData)
  do
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
        break;

      objName = VulkanGraphicsPlugin_BlahVkObjectTypeToString(objectType);
      object = pCallbackData->pObjects[0].objectHandle;

      if(pCallbackData->pObjects[0].pObjectName != nullptr)
        objName += " " + std::string(pCallbackData->pObjects[0].pObjectName);
    }

    Log::Write(level, Fmt("%s (%s 0x%llx) %s", flagNames.c_str(), objName.c_str(), object, pCallbackData->pMessage) );

  }while(0);

  return result;
}
