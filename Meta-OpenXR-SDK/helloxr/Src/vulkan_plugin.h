
// vulkan_plugin.h

#define THROW_VULKAN(res, cmd) ThrowVkResult(res, #cmd, FILE_AND_LINE_CHECK)

#define CHECK_VULKANCMD(cmd) CheckVkResult(cmd, #cmd, FILE_AND_LINE_CHECK)

#define CHECK_VULKANRESULT(res, cmdStr) CheckVkResult(res, cmdStr, FILE_AND_LINE_CHECK)

//#define CHECK_VULKANCMDBUFFERSTATE(s) \
//do \
//{ \
//  if(gCmdBufferState != (s) ) \
//  { \
//    Log::Write( \
//      Log::Level::Error, \
//      std::string("Expecting state " #s " from ") + \
//        __FUNCTION__ + \
//        ", in " + \
//        CmdBuffer_CmdBufferStateString(gCmdBufferState) \
//    ); \
// \
//    return false; \
//  } \
// \
//}while(0)

enum class CmdBufferStateEnum
{
  Undefined,
  Initialized,
  Recording,
  Executable,
  Executing
};

struct Cube
{
  XrPosef Pose;
  XrVector3f Scale;
};

struct VertexBufferBaseBlah
{
  uint32_t idx;
  uint32_t vtx;
};

constexpr VkFlags MemoryAllocator_m_memoryAllocatorDefaultFlags =
  VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

extern VkPipelineLayout gVkPipelineLayout;

extern VkPhysicalDeviceMemoryProperties gMemoryAllocatorMemoryProperties;

extern CmdBufferStateEnum gCmdBufferState;

extern VkCommandPool gCmdBufferPool;

extern VkCommandBuffer gCmdBufferBuffer;

extern VkFence gCmdBufferExecFence;

extern VkBuffer gVertexBufferBaseIdxBuf;

extern VkDeviceMemory gVertexBufferBaseIdxMem;

extern VkBuffer gVertexBufferBaseVtxBuf;

extern VkDeviceMemory gVertexBufferBaseVtxMem;

extern VkVertexInputBindingDescription gVertexBufferBaseBindDesc;

extern std::vector<VkVertexInputAttributeDescription> gVertexBufferBaseAttrDesc;

extern VertexBufferBaseBlah gVertexBufferBaseCount;

extern std::array<VkPipelineShaderStageCreateInfo, 2> gShaderProgramShaderInfo;

extern std::vector<std::vector<XrSwapchainImageVulkan2KHR> > m_swapchainImageContextSwapchainImages;

extern std::vector<std::vector<VkImage> > m_swapchainImageContextStdVector_renderTargetColorImage;
extern std::vector<std::vector<VkImage> > m_swapchainImageContextStdVector_renderTargetDepthImage;
extern std::vector<std::vector<VkImageView> > m_swapchainImageContextStdVector_renderTargetColorView;
extern std::vector<std::vector<VkImageView> > m_swapchainImageContextStdVector_renderTargetDepthView;
extern std::vector<std::vector<VkFramebuffer> > m_swapchainImageContextStdVector_renderTargetFrameBuffer;

extern std::vector<VkExtent2D> m_swapchainImageContextSize;

extern std::vector<VkDeviceMemory> m_swapchainImageContext_depthBufferDepthMemory;
extern std::vector<VkImage> m_swapchainImageContext_depthBufferDepthImage;
extern std::vector<VkImageLayout> m_swapchainImageContext_depthBufferVkImageLayout;

extern std::vector<VkFormat> m_swapchainImageContext_renderPassColorFmt;
extern std::vector<VkFormat> m_swapchainImageContext_renderPassDepthFmt;
extern std::vector<VkRenderPass> m_swapchainImageContext_renderPassPass;

extern std::vector<VkPipeline> m_swapchainImageContextPipe_pipelinePipe;
extern std::vector<VkPrimitiveTopology> m_swapchainImageContextPipe_pipelineTopology;
extern std::vector<std::vector<VkDynamicState> > m_swapchainImageContextPipe_pipelineDynamicStateEnables;

extern std::vector<XrStructureType> m_swapchainImageContextSwapchainImageType;

#if defined(VULKAN_DEBUG_OBJECT_NAMER)
extern std::vector<VulkanDebugObjectNamer> m_swapchainImageContextNamer;
#endif

extern XrGraphicsBindingVulkan2KHR gVulkanGraphicsPluginXrGraphicsBindingVulkan2KHR;

//std::vector<SwapchainImageContext*> gVulkanGraphicsPluginStdList_SwapchainImageContext;
extern std::vector<int> gVulkanGraphicsPluginStdList_SwapchainImageContext;

extern std::map<const XrSwapchainImageBaseHeader*, int>
  gVulkanGraphicsPluginStdMap_XrSwapchainImageBaseHeader_SwapchainImageContext;

#if defined(VULKAN_DEBUG_OBJECT_NAMER)
extern VulkanDebugObjectNamer gVulkanGraphicsPluginVulkanDebugObjectNamer;
#endif

extern uint32_t gVulkanGraphicsPluginQueueFamilyIndex;

extern VkQueue gVulkanGraphicsPluginVkQueue;

extern VkSemaphore gVulkanGraphicsPluginVkSemaphoreDrawDone;

extern std::array<float, 4> gVulkanGraphicsPluginStdArray_float_4_clearColor;

extern PFN_vkCreateDebugUtilsMessengerEXT gVulkanGraphicsPluginVkCreateDebugUtilsMessengerEXT;

extern VkDebugUtilsMessengerEXT gVulkanGraphicsPluginVkDebugUtilsMessenger;

constexpr char VertexShaderGlsl2[] =
R"_(

  #version 450

  layout(location = 0) out vec4 fragColor;

  vec2 positions[3] = vec2[](
      vec2(0.0, -0.5),
      vec2(0.5, 0.5),
      vec2(-0.5, 0.5)
  );

  vec4 colors[3] = vec4[](
      vec4(1.0, 0.0, 0.0, 1.0),
      vec4(0.0, 1.0, 0.0, 1.0),
      vec4(0.0, 0.0, 1.0, 1.0)
  );

  void main()
  {
      gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
      fragColor = colors[gl_VertexIndex % 3];
  }

)_";

constexpr char FragmentShaderGlsl2[] =
R"_(

  #version 450

  layout(location = 0) in vec3 fragColor;

  layout(location = 0) out vec4 outColor;

  void main()
  {
      outColor = vec4(fragColor, 1.0);
  }

)_";

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

  layout (location = 0) out vec4 fragColor;

  out gl_PerVertex
  {
    vec4 gl_Position;
  };

  vec4 colors[36] = vec4[](
      vec4(0.0, 0.0, 0.0, 1.0),
      vec4(0.0, 0.0, 0.0, 1.0),
      vec4(1.0, 1.0, 1.0, 1.0),
      vec4(0.0, 0.0, 0.0, 1.0),
      vec4(1.0, 1.0, 1.0, 1.0),
      vec4(0.0, 0.0, 0.0, 1.0),

      vec4(0.79, 0.79, 0.79, 1.0),
      vec4(0.25, 0.25, 0.25, 1.0),
      vec4(0.25, 0.25, 0.25, 1.0),
      vec4(0.79, 0.79, 0.79, 1.0),
      vec4(0.25, 0.25, 0.25, 1.0),
      vec4(0.25, 0.25, 0.25, 1.0),

      vec4(0.0, 1.0, 0.0, 1.0),
      vec4(1.0, 0.0, 0.0, 1.0),
      vec4(0.0, 1.0, 0.0, 1.0),
      vec4(0.0, 1.0, 0.0, 1.0),
      vec4(0.0, 1.0, 0.0, 1.0),
      vec4(0.0, 0.0, 1.0, 1.0),

      vec4(1.0, 0.0, 0.0, 1.0),
      vec4(0.0, 1.0, 0.0, 1.0),
      vec4(0.0, 0.0, 1.0, 1.0),
      vec4(1.0, 0.0, 0.0, 1.0),
      vec4(0.0, 0.0, 1.0, 1.0),
      vec4(0.0, 1.0, 0.0, 1.0),

      vec4(0.0, 0.54, 0.54, 1.0),
      vec4(0.0, 0.54, 0.54, 1.0),
      vec4(0.54, 0.54, 0.54, 1.0),
      vec4(0.0, 0.54, 0.54, 1.0),
      vec4(0.54, 0.54, 0.54, 1.0),
      vec4(0.0, 0.54, 0.54, 1.0),

      vec4(0.54, 0.54, 0.0, 1.0),
      vec4(0.54, 0.54, 0.0, 1.0),
      vec4(0.54, 0.54, 0.54, 1.0),
      vec4(0.54, 0.54, 0.0, 1.0),
      vec4(0.54, 0.54, 0.54, 1.0),
      vec4(0.54, 0.54, 0.0, 1.0)
  );

  void main()
  {
    //fragColor = vec4(Color, 1.0);
    fragColor = colors[gl_VertexIndex];

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

    // 3D point --> Homogeneous Coordinates --> Normalized Coordinates in [0, 1]
    highp vec2 cubeDepthCameraPositionHC = cubeDepthCameraPosition.xy / cubeDepthCameraPosition.w;
    cubeDepthCameraPositionHC = cubeDepthCameraPositionHC * 0.5f + 0.5f;

    // Sample from Environment Depth API texture
    highp vec3 depthViewCoord = vec3(cubeDepthCameraPositionHC, VIEW_ID);
    highp float depthViewEyeZ = texture(EnvironmentDepthTexture, depthViewCoord).r;

    // Get virtual object depth
    highp float cubeDepth = cubeDepthCameraPosition.z / cubeDepthCameraPosition.w;
    cubeDepth = cubeDepth * 0.5f + 0.5f;

    // Test virtual object depth with environment depth.
    //
    // If the virtual object is further away (occluded) output a transparent color so real scene content from PT layer
    // is displayed.
    outColor = fragmentColor;

    if(cubeDepth < depthViewEyeZ)
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

//////////

std::string BlahVkResultString(VkResult res);

[ [noreturn] ] inline void ThrowVkResult(
  VkResult res,
  const char* originator = nullptr,
  const char* sourceLocation = nullptr
)
{
  ThrowCheck(Fmt("VkResult failure [%s]", BlahVkResultString(res).c_str() ), originator, sourceLocation);
}

inline VkResult CheckVkResult(VkResult res, const char* originator = nullptr, const char* sourceLocation = nullptr)
{
  if( (res) < VK_SUCCESS)
    ThrowVkResult(res, originator, sourceLocation);

  return res;
}

std::string CmdBuffer_CmdBufferStateString(CmdBufferStateEnum s);

#if 0
void SwapchainImageContext_SwapchainImageContext_PipelineDynamic(int index, VkDynamicState state);
#endif

#if 0
void SwapchainImageContext_SwapchainImageContext_PipelineRelease(int index);
#endif

void VulkanGraphicsPlugin_VulkanGraphicsPlugin_Destructor();

#if 0
// note: The output must not outlive the input - this modifies the input and returns a collection of views into that
// modified input!
std::vector<const char*> VulkanGraphicsPlugin_VulkanGraphicsPluginParseExtensionString(char* names);
#endif

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanGraphicsPlugin_debugMessageThunk(
  VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
  VkDebugUtilsMessageTypeFlagsEXT messageTypes,
  const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
  void* /*pUserData*/
);

std::string VulkanGraphicsPlugin_BlahVkObjectTypeToString(VkObjectType objectType);
