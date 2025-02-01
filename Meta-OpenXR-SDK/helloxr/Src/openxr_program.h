
// openxr_program.h

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

extern XrAction gOpenXrProgramInputState_InputState_poseAction;

extern XrAction gOpenXrProgramInputState_InputState_vibrateAction;

extern XrAction gOpenXrProgramInputState_InputState_quitAction;

extern std::array<XrPath, Side_COUNT> gOpenXrProgramInputState_InputState_handSubactionPath;

extern std::array<XrSpace, Side_COUNT> gOpenXrProgramInputState_InputState_handSpace;

extern std::array<float, Side_COUNT> gOpenXrProgramInputState_InputState_handScale;

extern std::array<XrBool32, Side_COUNT> gOpenXrProgramInputState_InputState_handActive;

extern XrSpace gOpenXrProgramXrSpace;

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

extern "C" {
extern XrPassthroughFB gPassthroughFeature;
}

extern XrPassthroughLayerFB gPassthroughLayer;

extern PFN_xrCreatePassthroughFB gCreatePassthroughFB;
extern PFN_xrCreatePassthroughLayerFB gCreatePassthroughLayerFB;

extern PFN_xrCreateEnvironmentDepthProviderMETA gCreateEnvironmentDepthProviderMETA;
extern PFN_xrDestroyEnvironmentDepthProviderMETA gDestroyEnvironmentDepthProviderMETA;
extern PFN_xrStartEnvironmentDepthProviderMETA gStartEnvironmentDepthProviderMETA;
extern PFN_xrStopEnvironmentDepthProviderMETA gStopEnvironmentDepthProviderMETA;
extern PFN_xrCreateEnvironmentDepthSwapchainMETA gCreateEnvironmentDepthSwapchainMETA;
extern PFN_xrDestroyEnvironmentDepthSwapchainMETA gDestroyEnvironmentDepthSwapchainMETA;
extern PFN_xrEnumerateEnvironmentDepthSwapchainImagesMETA gEnumerateEnvironmentDepthSwapchainImagesMETA;
extern PFN_xrGetEnvironmentDepthSwapchainStateMETA gGetEnvironmentDepthSwapchainStateMETA;
extern PFN_xrAcquireEnvironmentDepthImageMETA gAcquireEnvironmentDepthImageMETA;
extern PFN_xrSetEnvironmentDepthHandRemovalMETA gSetEnvironmentDepthHandRemovalMETA;

extern XrEnvironmentDepthProviderMETA gEnvironmentDepthProviderMETA;

void OpenXrProgram_LogLayersAndExtensions();

void OpenXrProgram_OpenXrProgram();

void OpenXrProgram_OpenXrProgram_Destructor();

void OpenXrProgram_OpenXrProgramLogInstanceInfo();

void OpenXrProgram_OpenXrProgramCreateInstanceInternal();

void OpenXrProgram_OpenXrProgramCreateInstance();

void OpenXrProgram_OpenXrProgramLogViewConfigurations();

void OpenXrProgram_OpenXrProgramLogEnvironmentBlendMode(XrViewConfigurationType type);

XrEnvironmentBlendMode OpenXrProgram_OpenXrProgramGetPreferredBlendMode();

void OpenXrProgram_OpenXrProgramInitializeSystem();

void OpenXrProgram_OpenXrProgramInitializeDevice();

void OpenXrProgram_OpenXrProgramLogReferenceSpaces();

void OpenXrProgram_OpenXrProgramInitializeActions();

void OpenXrProgram_OpenXrProgramCreateVisualizedSpaces();

void OpenXrProgram_OpenXrProgramInitializeSession();

void OpenXrProgram_OpenXrProgramCreateSwapchains();

const XrEventDataBaseHeader* OpenXrProgram_OpenXrProgramTryReadNextEvent();

void OpenXrProgram_OpenXrProgramPollEvents(bool* exitRenderLoop, bool* requestRestart);

void OpenXrProgram_OpenXrProgramHandleSessionStateChangedEvent(const XrEventDataSessionStateChanged& stateChangedEvent, bool* exitRenderLoop, bool* requestRestart);

void OpenXrProgram_OpenXrProgramLogActionSourceName(XrAction action, const std::string& actionName);

bool OpenXrProgram_OpenXrProgramIsSessionRunning();

bool OpenXrProgram_OpenXrProgramIsSessionFocused();

void OpenXrProgram_OpenXrProgramPollActions();

// Unreal UOculusXRFunctionLibrary::SetSuggestedCpuAndGpuPerformanceLevels (exposed in Blueprint)
//
// Unity OVRPlugin::suggestedCpuPerfLevel, OVRPlugin::suggestedGpuPerfLevel
//
// Native ovrp_SetSuggestedCpuPerformanceLevel, ovrp_GetSuggestedGpuPerformanceLevel

void OpenXrProgram_OpenXrProgramRenderFrame();

bool OpenXrProgram_OpenXrProgramRenderLayer(XrTime predictedDisplayTime, std::vector<XrCompositionLayerProjectionView>& projectionLayerViews, XrCompositionLayerProjection& layer);

void OpenXrProgram_CreateOpenXrProgram();
