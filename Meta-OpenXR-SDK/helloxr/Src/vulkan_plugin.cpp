
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

std::array<VkPipelineShaderStageCreateInfo, 2> gShaderProgramShaderInfo { { {VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO}, {VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO} } };

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
    CHECK_VULKANCMD(tableVk.CreatePipelineLayout(gVkDevice, &pipelineLayoutCreateInfo, nullptr, &gVkPipelineLayout) );
}

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
          CHECK_VULKANCMD(tableVk.AllocateMemory(gVkDevice, &memAlloc, nullptr, mem) );

        return;
      }
    }
  }

  THROW_CHECK("Memory format not supported");
}

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
  CHECK_VULKANCMDBUFFERSTATE(CmdBufferStateEnum::Undefined);

  // Create a command pool to allocate our command buffer from
  VkCommandPoolCreateInfo cmdPoolInfo {VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO};
  cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  cmdPoolInfo.queueFamilyIndex = queueFamilyIndex;

  if(tableVk.CreateCommandPool)
    CHECK_VULKANCMD(tableVk.CreateCommandPool(gVkDevice, &cmdPoolInfo, nullptr, &gCmdBufferPool) );

  CHECK_VULKANCMD(namer.SetName(VK_OBJECT_TYPE_COMMAND_POOL, (uint64_t)gCmdBufferPool, "helloxr command pool") );

  // Create the command buffer from the command pool
  VkCommandBufferAllocateInfo cmd {VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO};
  cmd.commandPool = gCmdBufferPool;
  cmd.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  cmd.commandBufferCount = 1;

  if(tableVk.AllocateCommandBuffers)
    CHECK_VULKANCMD(tableVk.AllocateCommandBuffers(gVkDevice, &cmd, &gCmdBufferBuffer) );

  CHECK_VULKANCMD(namer.SetName(VK_OBJECT_TYPE_COMMAND_BUFFER, (uint64_t)gCmdBufferBuffer, "helloxr command buffer") );

  VkFenceCreateInfo fenceInfo {VK_STRUCTURE_TYPE_FENCE_CREATE_INFO};

  if(tableVk.CreateFence)
    CHECK_VULKANCMD(tableVk.CreateFence(gVkDevice, &fenceInfo, nullptr, &gCmdBufferExecFence) );

  CHECK_VULKANCMD(namer.SetName(VK_OBJECT_TYPE_FENCE, (uint64_t)gCmdBufferExecFence, "helloxr fence") );

  CmdBuffer_CmdBufferSetState(CmdBufferStateEnum::Initialized);

  return true;
}

bool CmdBuffer_CmdBufferBegin()
{
  CHECK_VULKANCMDBUFFERSTATE(CmdBufferStateEnum::Initialized);

  VkCommandBufferBeginInfo cmdBeginInfo {VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};

  if(tableVk.BeginCommandBuffer)
    CHECK_VULKANCMD(tableVk.BeginCommandBuffer(gCmdBufferBuffer, &cmdBeginInfo) );

  CmdBuffer_CmdBufferSetState(CmdBufferStateEnum::Recording);

  return true;
}

bool CmdBuffer_CmdBufferEnd()
{
  CHECK_VULKANCMDBUFFERSTATE(CmdBufferStateEnum::Recording);

  if(tableVk.EndCommandBuffer)
    CHECK_VULKANCMD(tableVk.EndCommandBuffer(gCmdBufferBuffer) );

  CmdBuffer_CmdBufferSetState(CmdBufferStateEnum::Executable);

  return true;
}

bool CmdBuffer_CmdBufferExec(VkQueue queue)
{
  CHECK_VULKANCMDBUFFERSTATE(CmdBufferStateEnum::Executable);

  VkSubmitInfo submitInfo {VK_STRUCTURE_TYPE_SUBMIT_INFO};

  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &gCmdBufferBuffer;

  if(tableVk.QueueSubmit)
    CHECK_VULKANCMD(tableVk.QueueSubmit(queue, 1, &submitInfo, gCmdBufferExecFence) );

  CmdBuffer_CmdBufferSetState(CmdBufferStateEnum::Executing);

  return true;
}

bool CmdBuffer_CmdBufferWait()
{
  // Waiting on a not-in-flight command buffer is a no-op
  if(gCmdBufferState == CmdBufferStateEnum::Initialized)
    return true;

  CHECK_VULKANCMDBUFFERSTATE(CmdBufferStateEnum::Executing);

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
    CHECK_VULKANCMDBUFFERSTATE(CmdBufferStateEnum::Executable);

    if(tableVk.ResetFences)
      CHECK_VULKANCMD(tableVk.ResetFences(gVkDevice, 1, &gCmdBufferExecFence) );

    if(tableVk.ResetCommandBuffer)
      CHECK_VULKANCMD(tableVk.ResetCommandBuffer(gCmdBufferBuffer, 0) );

    CmdBuffer_CmdBufferSetState(CmdBufferStateEnum::Initialized);
  }

  return true;
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
    CHECK_VULKANCMD(tableVk.CreateBuffer(gVkDevice, &bufInfo, nullptr, &gVertexBufferBaseIdxBuf) );

  VertexBufferBase_VertexBufferBaseAllocateBufferMemory(gVertexBufferBaseIdxBuf, &gVertexBufferBaseIdxMem);

  if(tableVk.BindBufferMemory)
    CHECK_VULKANCMD(tableVk.BindBufferMemory(gVkDevice, gVertexBufferBaseIdxBuf, gVertexBufferBaseIdxMem, 0) );

  bufInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
  bufInfo.size = sizeof(Geometry::Vertex) * vtxCount;

  if(tableVk.CreateBuffer)
    CHECK_VULKANCMD(tableVk.CreateBuffer(gVkDevice, &bufInfo, nullptr, &gVertexBufferBaseVtxBuf) );

  VertexBufferBase_VertexBufferBaseAllocateBufferMemory(gVertexBufferBaseVtxBuf, &gVertexBufferBaseVtxMem);

  if(tableVk.BindBufferMemory)
    CHECK_VULKANCMD(tableVk.BindBufferMemory(gVkDevice, gVertexBufferBaseVtxBuf, gVertexBufferBaseVtxMem, 0) );

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
    CHECK_VULKANCMD(tableVk.MapMemory(gVkDevice, gVertexBufferBaseIdxMem, sizeof(map[0] ) * offset, sizeof(map[0] ) * elements, 0, (void**)&map) );

  for(size_t i = 0; i < elements; ++i)
    map[i] = data[i];

  if(tableVk.UnmapMemory)
    tableVk.UnmapMemory(gVkDevice, gVertexBufferBaseIdxMem);
}

void VertexBuffer_VertexBufferUpdateVertices(const Geometry::Vertex* data, uint32_t elements, uint32_t offset)
{
  Geometry::Vertex* map = nullptr;

  if(tableVk.MapMemory)
    CHECK_VULKANCMD(tableVk.MapMemory(gVkDevice, gVertexBufferBaseVtxMem, sizeof(map[0] ) * offset, sizeof(map[0] ) * elements, 0, (void**) &map) );

  for(size_t i = 0; i < elements; ++i)
    map[i] = data[i];

  if(tableVk.UnmapMemory)
    tableVk.UnmapMemory(gVkDevice, gVertexBufferBaseVtxMem);
}

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
    CHECK_VULKANCMD(tableVk.CreateShaderModule(gVkDevice, &modInfo, nullptr, &si.module) );

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
      CHECK_VULKANCMD(tableVk.CreateImageView(gVkDevice, &colorViewInfo, nullptr, &renderTargetColorView) );
      m_swapchainImageContextStdVector_renderTargetColorView[index][renderTarget] = renderTargetColorView;
    }

    CHECK_VULKANCMD(namer.SetName(VK_OBJECT_TYPE_IMAGE_VIEW, (uint64_t)m_swapchainImageContextStdVector_renderTargetColorView[index][renderTarget], "helloxr color image view") );
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
      CHECK_VULKANCMD(tableVk.CreateImageView(gVkDevice, &depthViewInfo, nullptr, &renderTargetDepthView) );
      m_swapchainImageContextStdVector_renderTargetDepthView[index][renderTarget] = renderTargetDepthView;
    }

    CHECK_VULKANCMD(namer.SetName(VK_OBJECT_TYPE_IMAGE_VIEW, (uint64_t)m_swapchainImageContextStdVector_renderTargetDepthView[index][renderTarget], "helloxr depth image view") );
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
    CHECK_VULKANCMD(tableVk.CreateFramebuffer(gVkDevice, &fbInfo, nullptr, &renderTargetFrameBuffer) );
    m_swapchainImageContextStdVector_renderTargetFrameBuffer[index][renderTarget] = renderTargetFrameBuffer;
  }

  CHECK_VULKANCMD(namer.SetName(VK_OBJECT_TYPE_FRAMEBUFFER, (uint64_t)m_swapchainImageContextStdVector_renderTargetFrameBuffer[index][renderTarget], "helloxr framebuffer") );
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
    CHECK_VULKANCMD(tableVk.CreateImage(gVkDevice, &imageInfo, nullptr, &m_swapchainImageContext_depthBufferDepthImage[index]) );

  CHECK_VULKANCMD(namer.SetName(VK_OBJECT_TYPE_IMAGE, (uint64_t)m_swapchainImageContext_depthBufferDepthImage[index], "helloxr fallback depth image") );

  VkMemoryRequirements memRequirements {};

  if(tableVk.GetImageMemoryRequirements)
    tableVk.GetImageMemoryRequirements(gVkDevice, m_swapchainImageContext_depthBufferDepthImage[index], &memRequirements);

  MemoryAllocator_MemoryAllocatorAllocate(memRequirements, &m_swapchainImageContext_depthBufferDepthMemory[index], VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
  CHECK_VULKANCMD(namer.SetName(VK_OBJECT_TYPE_DEVICE_MEMORY, (uint64_t)m_swapchainImageContext_depthBufferDepthMemory[index], "helloxr fallback depth image memory") );

  if(tableVk.BindImageMemory)
    CHECK_VULKANCMD(tableVk.BindImageMemory(gVkDevice, m_swapchainImageContext_depthBufferDepthImage[index], m_swapchainImageContext_depthBufferDepthMemory[index], 0) );
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
    CHECK_VULKANCMD(tableVk.CreateRenderPass(gVkDevice, &rpInfo, nullptr, &m_swapchainImageContext_renderPassPass[index] ) );

  CHECK_VULKANCMD(namer.SetName(VK_OBJECT_TYPE_RENDER_PASS, (uint64_t)m_swapchainImageContext_renderPassPass[index], "helloxr render pass") );

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
    CHECK_VULKANCMD(tableVk.CreateGraphicsPipelines(gVkDevice, VK_NULL_HANDLE, 1, &pipeInfo, nullptr, &m_swapchainImageContextPipe_pipelinePipe[index] ) );
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

void VulkanGraphicsPlugin_VulkanGraphicsPlugin_Destructor()
{
  if(gVkDevice)
  {
    if(gVkPipelineLayout != VK_NULL_HANDLE && tableVk.DestroyPipelineLayout)
      tableVk.DestroyPipelineLayout(gVkDevice, gVkPipelineLayout, nullptr);

    gVkPipelineLayout = VK_NULL_HANDLE;
  }
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

uint32_t VulkanGraphicsPlugin_VulkanGraphicsPluginGetSupportedSwapchainSampleCount(const XrViewConfigurationView&)
{
  return VK_SAMPLE_COUNT_1_BIT;
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
