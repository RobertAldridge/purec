
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

  friend void OpenXrProgram_LogLayersAndExtensions();

  void LogInstanceInfo();

  void CreateInstanceInternal();

  void CreateInstance();

  void LogViewConfigurations();

  void LogEnvironmentBlendMode(XrViewConfigurationType type);

  XrEnvironmentBlendMode GetPreferredBlendMode() const;

  void InitializeSystem();

  void InitializeDevice();

  void LogReferenceSpaces();

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

  void InitializeActions();

  void CreateVisualizedSpaces();

  void InitializeSession();

  void CreateSwapchains();

  const XrEventDataBaseHeader* TryReadNextEvent();

  void PollEvents(bool* exitRenderLoop, bool* requestRestart);

  void HandleSessionStateChangedEvent(const XrEventDataSessionStateChanged& stateChangedEvent, bool* exitRenderLoop, bool* requestRestart);

  void LogActionSourceName(XrAction action, const std::string& actionName) const;

  bool IsSessionRunning() const;

  bool IsSessionFocused() const;

  void PollActions();

  // Unreal UOculusXRFunctionLibrary::SetSuggestedCpuAndGpuPerformanceLevels (exposed in Blueprint)
  //
  // Unity OVRPlugin::suggestedCpuPerfLevel, OVRPlugin::suggestedGpuPerfLevel
  //
  // Native ovrp_SetSuggestedCpuPerformanceLevel, ovrp_GetSuggestedGpuPerformanceLevel

  void RenderFrame();

  bool RenderLayer(XrTime predictedDisplayTime, std::vector<XrCompositionLayerProjectionView>& projectionLayerViews, XrCompositionLayerProjection& layer);

private:

  const std::shared_ptr<const Options> m_options;

  std::shared_ptr<AndroidPlatformPlugin> m_platformPlugin;

  std::shared_ptr<VulkanGraphicsPlugin> m_graphicsPlugin;

  XrInstance m_instance {XR_NULL_HANDLE};

  XrSession m_session {XR_NULL_HANDLE};

  XrSpace m_appSpace {XR_NULL_HANDLE};

  XrSystemId m_systemId {XR_NULL_SYSTEM_ID};

  std::vector<XrViewConfigurationView> m_configViews;

  std::vector<Swapchain> m_swapchains;

  std::map<XrSwapchain, std::vector<XrSwapchainImageBaseHeader*> > m_swapchainImages;

  std::vector<XrView> m_views;

  int64_t m_colorSwapchainFormat {-1};

  std::vector<XrSpace> m_visualizedSpaces;

  // Application's current lifecycle state according to the runtime
  XrSessionState m_sessionState {XR_SESSION_STATE_UNKNOWN};

  bool m_sessionRunning {false};

  XrEventDataBuffer m_eventDataBuffer;

  InputState m_input;

  const std::set<XrEnvironmentBlendMode> m_acceptableBlendModes;
};

std::shared_ptr<OpenXrProgram> CreateOpenXrProgram(const std::shared_ptr<Options>& options, const std::shared_ptr<AndroidPlatformPlugin>& platformPlugin, const std::shared_ptr<VulkanGraphicsPlugin>& graphicsPlugin);

#endif
