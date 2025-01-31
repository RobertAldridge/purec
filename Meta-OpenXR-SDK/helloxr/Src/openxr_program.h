
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

struct OpenXrProgram
{
  OpenXrProgram(const std::shared_ptr<Options>& options, const std::shared_ptr<AndroidPlatformPlugin>& platformPlugin, const std::shared_ptr<VulkanGraphicsPlugin>& graphicsPlugin);

  ~OpenXrProgram();

  void OpenXrProgramLogInstanceInfo();

  void OpenXrProgramCreateInstanceInternal();

  void OpenXrProgramCreateInstance();

  void OpenXrProgramLogViewConfigurations();

  void OpenXrProgramLogEnvironmentBlendMode(XrViewConfigurationType type);

  XrEnvironmentBlendMode OpenXrProgramGetPreferredBlendMode() const;

  void OpenXrProgramInitializeSystem();

  void OpenXrProgramInitializeDevice();

  void OpenXrProgramLogReferenceSpaces();

  struct InputState
  {
    XrActionSet actionSet {XR_NULL_HANDLE};

    XrAction grabAction {XR_NULL_HANDLE};

    XrAction poseAction {XR_NULL_HANDLE};

    XrAction vibrateAction {XR_NULL_HANDLE};

    XrAction quitAction {XR_NULL_HANDLE};

    std::array<XrPath, (int)Side::COUNT> handSubactionPath;

    std::array<XrSpace, (int)Side::COUNT> handSpace;

    std::array<float, (int)Side::COUNT> handScale = { {1.0f, 1.0f} };

    std::array<XrBool32, (int)Side::COUNT> handActive;
  };

  void OpenXrProgramInitializeActions();

  void OpenXrProgramCreateVisualizedSpaces();

  void OpenXrProgramInitializeSession();

  void OpenXrProgramCreateSwapchains();

  const XrEventDataBaseHeader* OpenXrProgramTryReadNextEvent();

  void OpenXrProgramPollEvents(bool* exitRenderLoop, bool* requestRestart);

  void OpenXrProgramHandleSessionStateChangedEvent(const XrEventDataSessionStateChanged& stateChangedEvent, bool* exitRenderLoop, bool* requestRestart);

  void OpenXrProgramLogActionSourceName(XrAction action, const std::string& actionName) const;

  bool OpenXrProgramIsSessionRunning() const;

  bool OpenXrProgramIsSessionFocused() const;

  void OpenXrProgramPollActions();

  // Unreal UOculusXRFunctionLibrary::SetSuggestedCpuAndGpuPerformanceLevels (exposed in Blueprint)
  //
  // Unity OVRPlugin::suggestedCpuPerfLevel, OVRPlugin::suggestedGpuPerfLevel
  //
  // Native ovrp_SetSuggestedCpuPerformanceLevel, ovrp_GetSuggestedGpuPerformanceLevel

  void OpenXrProgramRenderFrame();

  bool OpenXrProgramRenderLayer(XrTime predictedDisplayTime, std::vector<XrCompositionLayerProjectionView>& projectionLayerViews, XrCompositionLayerProjection& layer);

private:

  const std::shared_ptr<const Options> m_OpenXrProgramStdSharedPtr_Options;

  std::shared_ptr<AndroidPlatformPlugin> m_OpenXrProgramStdSharedPtr_AndroidPlatformPlugin;

  std::shared_ptr<VulkanGraphicsPlugin> m_OpenXrProgramStdSharedPtr_VulkanGraphicsPlugin;

  XrInstance m_OpenXrProgramXrInstance {XR_NULL_HANDLE};

  XrSession m_OpenXrProgramXrSession {XR_NULL_HANDLE};

  XrSpace m_OpenXrProgramXrSpace {XR_NULL_HANDLE};

  XrSystemId m_OpenXrProgramXrSystemId {XR_NULL_SYSTEM_ID};

  std::vector<XrViewConfigurationView> m_OpenXrProgramStdVector_XrViewConfigurationView;

  std::vector<Swapchain> m_OpenXrProgramStdVector_Swapchain;

  std::map<XrSwapchain, std::vector<XrSwapchainImageBaseHeader*> > m_OpenXrProgramStdMap_XrSwapchain_StdVectorXrSwapchainImageBaseHeader;

  std::vector<XrView> m_OpenXrProgramStdVector_XrView;

  int64_t m_OpenXrProgramColorSwapchainFormat {-1};

  std::vector<XrSpace> m_OpenXrProgramStdVector_XrSpace;

  // Application's current lifecycle state according to the runtime
  XrSessionState m_OpenXrProgramXrSessionState {XR_SESSION_STATE_UNKNOWN};

  bool m_OpenXrProgramSessionRunning {false};

  XrEventDataBuffer m_OpenXrProgramXrEventDataBuffer;

  InputState m_OpenXrProgramInputState;

  const std::set<XrEnvironmentBlendMode> m_OpenXrProgramStdSet_XrEnvironmentBlendMode;

  friend void OpenXrProgram_LogLayersAndExtensions();
};

std::shared_ptr<OpenXrProgram> OpenXrProgram_CreateOpenXrProgram(const std::shared_ptr<Options>& options, const std::shared_ptr<AndroidPlatformPlugin>& platformPlugin, const std::shared_ptr<VulkanGraphicsPlugin>& graphicsPlugin);

#endif
