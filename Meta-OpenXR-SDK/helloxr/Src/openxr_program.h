
// openxr_program.h

struct Swapchain
{
  XrSwapchain handle;
  int32_t width;
  int32_t height;
};

void OpenXrProgram_LogLayersAndExtensions();

#ifdef __cplusplus

enum class Side
{
  LEFT = 0,
  RIGHT = 1,
  COUNT = 2
};

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

#endif
