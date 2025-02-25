
// openxr_plugin.h

struct Swapchain
{
  XrSwapchain handle;
  int32_t width;
  int32_t height;
};

constexpr int Side_LEFT {0};
constexpr int Side_RIGHT {1};
constexpr int Side_COUNT {2};

extern XrActionSet gOpenXrProgramInputState_InputState_actionSet;

extern XrAction gOpenXrProgramInputState_InputState_grabAction;

extern XrAction gOpenXrProgramInputState_InputState_triggerAction;

extern XrAction gOpenXrProgramInputState_InputState_poseAction;

extern XrAction gOpenXrProgramInputState_InputState_vibrateAction;

extern XrAction gOpenXrProgramInputState_InputState_quitAction;

extern std::array<XrPath, Side_COUNT> gOpenXrProgramInputState_InputState_handSubactionPath;

extern std::array<XrSpace, Side_COUNT> gOpenXrProgramInputState_InputState_handSpace;

extern std::array<float, Side_COUNT> gOpenXrProgramInputState_InputState_handScale;

extern std::array<XrBool32, Side_COUNT> gOpenXrProgramInputState_InputState_handActive;

// local space
extern XrSpace gOpenXrProgramXrSpace;

//extern XrSpace gOpenXrHeadXrSpace;

extern std::vector<XrViewConfigurationView> gOpenXrProgramStdVector_XrViewConfigurationView;

extern std::vector<Swapchain> gOpenXrProgramStdVector_Swapchain;

extern std::map<XrSwapchain, std::vector<XrSwapchainImageBaseHeader*> > gOpenXrProgramStdMap_XrSwapchain_StdVectorXrSwapchainImageBaseHeader;

extern std::vector<XrView> gOpenXrProgramStdVector_XrView;

extern int64_t gOpenXrProgramColorSwapchainFormat;

extern std::vector<XrSpace> gOpenXrProgramStdVector_XrSpace;

// Application's current lifecycle state according to the runtime
extern XrSessionState gOpenXrProgramXrSessionState;

extern bool gOpenXrProgramSessionRunning;

extern XrEventDataBuffer gOpenXrProgramXrEventDataBuffer;

const std::set<XrEnvironmentBlendMode> gOpenXrProgramStdSet_XrEnvironmentBlendMode {XR_ENVIRONMENT_BLEND_MODE_OPAQUE, XR_ENVIRONMENT_BLEND_MODE_ADDITIVE, XR_ENVIRONMENT_BLEND_MODE_ALPHA_BLEND};

extern "C" {
extern XrPassthroughFB gPassthroughFeature;
}

extern XrPassthroughLayerFB gPassthroughLayer;

extern XrEnvironmentDepthProviderMETA gEnvironmentDepthProviderMETA;
extern XrEnvironmentDepthSwapchainMETA gEnvironmentDepthSwapchainMETA;

extern XrEnvironmentDepthProviderCreateInfoMETA gEnvironmentDepthProviderCreateInfoMETA;
extern XrEnvironmentDepthHandRemovalSetInfoMETA gEnvironmentDepthHandRemovalSetInfoMETA;
extern XrEnvironmentDepthSwapchainCreateInfoMETA gEnvironmentDepthSwapchainCreateInfoMETA;
extern XrEnvironmentDepthSwapchainStateMETA gEnvironmentDepthSwapchainStateMETA;

extern uint32_t gEnvironmentDepthSwapChainLength;

extern std::vector<XrSwapchainImageVulkanKHR> gEnvironmentDepthImages;
extern std::vector<VkImage> gEnvironmentDepthTextures;

namespace OpenXrProgram_Math
{

namespace OpenXrProgram_Pose
{

XrPosef Identity();

XrPosef Translation(const XrVector3f& translation);

XrPosef RotateCCWAboutYAxis(float radians, XrVector3f translation);

} // namespace OpenXrProgram_Pose

} // namespace OpenXrProgram_Math

std::string GetXrVersionString(XrVersion ver);

XrReferenceSpaceCreateInfo GetXrReferenceSpaceCreateInfo(const std::string& referenceSpaceTypeStr);

void OpenXrProgram_OpenXrProgram_Destructor();

// Instance RuntimeName = Oculus RuntimeVersion = 71.601.0
// Available View Configuration Types: (1)
// Available Environment Blend Mode count : (1)
// Environment Blend Mode (XR_ENVIRONMENT_BLEND_MODE_OPAQUE) : (Selected)
// No validation layers found in the system, skipping
//
// System Properties: Name = Oculus Quest VendorId = 10291
// System Graphics Properties: MaxWidth = 8192 MaxHeight = 8192 MaxLayers = 32
// System Tracking Properties: OrientationTracking = True PositionTracking = True
// Creating swapchain for view 0 with dimensions Width = 1680 Height = 1760 SampleCount = 1

//struct OpenXrProgram_InputState
//{
//  XrActionSet actionSet {XR_NULL_HANDLE};
//
//  XrAction grabAction {XR_NULL_HANDLE};
//
//  XrAction poseAction {XR_NULL_HANDLE};
//
//  XrAction vibrateAction {XR_NULL_HANDLE};
//
//  XrAction quitAction {XR_NULL_HANDLE};
//
//  std::array<XrPath, Side_COUNT> handSubactionPath;
//
//  std::array<XrSpace, Side_COUNT> handSpace;
//
//  std::array<float, Side_COUNT> handScale =
//  {
//    {1.0f, 1.0f}
//  };
//
//  std::array<XrBool32, Side_COUNT> handActive;
//};

#if 0
bool OpenXrProgram_OpenXrProgramIsSessionFocused();
#endif

// Unreal UOculusXRFunctionLibrary::SetSuggestedCpuAndGpuPerformanceLevels (exposed in Blueprint)
//
// Unity OVRPlugin::suggestedCpuPerfLevel, OVRPlugin::suggestedGpuPerfLevel
//
// Native ovrp_SetSuggestedCpuPerformanceLevel, ovrp_GetSuggestedGpuPerformanceLevel
