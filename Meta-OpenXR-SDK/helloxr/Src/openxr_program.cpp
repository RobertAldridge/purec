
// openxr_program.cpp

#include "header.h"

namespace
{

#define strcpy_s(dest, source) strncpy( (dest), (source), sizeof(dest) )

namespace Side
{
  const int LEFT = 0;
  const int RIGHT = 1;
  const int COUNT = 2;

} // namespace Side

inline std::string GetXrVersionString(XrVersion ver)
{
  return Fmt("%d.%d.%d", XR_VERSION_MAJOR(ver), XR_VERSION_MINOR(ver), XR_VERSION_PATCH(ver) );
}

namespace Math
{

namespace Pose
{

XrPosef Identity()
{
  XrPosef t {};
  t.orientation.w = 1;
  return t;
}

XrPosef Translation(const XrVector3f& translation)
{
  XrPosef t = Identity();
  t.position = translation;
  return t;
}

XrPosef RotateCCWAboutYAxis(float radians, XrVector3f translation)
{
  XrPosef t = Identity();
  t.orientation.x = 0.f;
  t.orientation.y = std::sin(radians * 0.5f);
  t.orientation.z = 0.f;
  t.orientation.w = std::cos(radians * 0.5f);
  t.position = translation;

  return t;
}

}  // namespace Pose

}  // namespace Math

inline XrReferenceSpaceCreateInfo GetXrReferenceSpaceCreateInfo(const std::string& referenceSpaceTypeStr)
{
  XrReferenceSpaceCreateInfo referenceSpaceCreateInfo {XR_TYPE_REFERENCE_SPACE_CREATE_INFO};
  referenceSpaceCreateInfo.poseInReferenceSpace = Math::Pose::Identity();

  if(EqualsIgnoreCase(referenceSpaceTypeStr, "View") )
  {
    referenceSpaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_VIEW;
  }
  else if(EqualsIgnoreCase(referenceSpaceTypeStr, "ViewFront") )
  {
    // Render head-locked 2m in front of device.
    referenceSpaceCreateInfo.poseInReferenceSpace = Math::Pose::Translation( {0.f, 0.f, -2.f} ),
    referenceSpaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_VIEW;
  }
  else if(EqualsIgnoreCase(referenceSpaceTypeStr, "Local") )
  {
    referenceSpaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_LOCAL;
  }
  else if(EqualsIgnoreCase(referenceSpaceTypeStr, "Stage") )
  {
    referenceSpaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_STAGE;
  }
  else if(EqualsIgnoreCase(referenceSpaceTypeStr, "StageLeft") )
  {
    referenceSpaceCreateInfo.poseInReferenceSpace = Math::Pose::RotateCCWAboutYAxis(0.f, {-2.f, 0.f, -2.f} );
    referenceSpaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_STAGE;
  }
  else if(EqualsIgnoreCase(referenceSpaceTypeStr, "StageRight") )
  {
    referenceSpaceCreateInfo.poseInReferenceSpace = Math::Pose::RotateCCWAboutYAxis(0.f, {2.f, 0.f, -2.f} );
    referenceSpaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_STAGE;
  }
  else if(EqualsIgnoreCase(referenceSpaceTypeStr, "StageLeftRotated") )
  {
    referenceSpaceCreateInfo.poseInReferenceSpace = Math::Pose::RotateCCWAboutYAxis(3.14f / 3.f, {-2.f, 0.5f, -2.f} );
    referenceSpaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_STAGE;
  }
  else if(EqualsIgnoreCase(referenceSpaceTypeStr, "StageRightRotated") )
  {
    referenceSpaceCreateInfo.poseInReferenceSpace = Math::Pose::RotateCCWAboutYAxis(-3.14f / 3.f, {2.f, 0.5f, -2.f} );
    referenceSpaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_STAGE;
  }
  else
  {
    throw std::invalid_argument(Fmt("Unknown reference space type '%s'", referenceSpaceTypeStr.c_str() ) );
  }

  return referenceSpaceCreateInfo;
}

struct OpenXrProgram : IOpenXrProgram
{
  OpenXrProgram(const std::shared_ptr<Options>& options, const std::shared_ptr<IPlatformPlugin>& platformPlugin, const std::shared_ptr<IGraphicsPlugin>& graphicsPlugin)
  : m_options(options),
    m_platformPlugin(platformPlugin),
    m_graphicsPlugin(graphicsPlugin),
    m_acceptableBlendModes {XR_ENVIRONMENT_BLEND_MODE_OPAQUE, XR_ENVIRONMENT_BLEND_MODE_ADDITIVE, XR_ENVIRONMENT_BLEND_MODE_ALPHA_BLEND}
  {
  }

  ~OpenXrProgram() override
  {
    if(m_input.actionSet != XR_NULL_HANDLE)
    {
      for(auto hand : {Side::LEFT, Side::RIGHT} )
      {
        if(tableXr.DestroySpace)
          tableXr.DestroySpace(m_input.handSpace[hand] );
      }

      if(tableXr.DestroyActionSet)
        tableXr.DestroyActionSet(m_input.actionSet);
    }

    for(Swapchain swapchain : m_swapchains)
    {
      if(tableXr.DestroySwapchain)
        tableXr.DestroySwapchain(swapchain.handle);
    }

    for(XrSpace visualizedSpace : m_visualizedSpaces)
    {
      if(tableXr.DestroySpace)
        tableXr.DestroySpace(visualizedSpace);
    }

    if(m_appSpace != XR_NULL_HANDLE && tableXr.DestroySpace)
      tableXr.DestroySpace(m_appSpace);

    if(m_session != XR_NULL_HANDLE && tableXr.DestroySession)
      tableXr.DestroySession(m_session);

    if(m_instance != XR_NULL_HANDLE && tableXr.DestroyInstance)
      tableXr.DestroyInstance(m_instance);
  }

  static void LogLayersAndExtensions()
  {
    // Write out extension properties for a given layer.
    const auto logExtensions = [](const char* layerName, int indent = 0 )
    {
      uint32_t instanceExtensionCount = 0;

      if(tableXr.EnumerateInstanceExtensionProperties)
        CHECK_XRCMD(tableXr.EnumerateInstanceExtensionProperties(layerName, 0, &instanceExtensionCount, nullptr) );

      std::vector<XrExtensionProperties> extensions(instanceExtensionCount, {XR_TYPE_EXTENSION_PROPERTIES} );

      if(tableXr.EnumerateInstanceExtensionProperties)
        CHECK_XRCMD(tableXr.EnumerateInstanceExtensionProperties(layerName, (uint32_t)extensions.size(), &instanceExtensionCount, extensions.data() ) );

      const std::string indentStr(indent, ' ');

      Log::Write(Log::Level::Verbose, Fmt("%sAvailable Extensions: (%d)", indentStr.c_str(), instanceExtensionCount) );

      for(const XrExtensionProperties& extension : extensions)
        Log::Write(Log::Level::Verbose, Fmt("%s  Name=%s SpecVersion=%d", indentStr.c_str(), extension.extensionName, extension.extensionVersion) );
    };

    // Log non-layer extensions (layerName==nullptr).
    logExtensions(nullptr);

    // Log layers and any of their extensions.
    {
      uint32_t layerCount = 0;

      if(tableXr.EnumerateApiLayerProperties)
        CHECK_XRCMD(tableXr.EnumerateApiLayerProperties(0, &layerCount, nullptr) );

      std::vector<XrApiLayerProperties> layers(layerCount, {XR_TYPE_API_LAYER_PROPERTIES} );

      if(tableXr.EnumerateApiLayerProperties)
        CHECK_XRCMD(tableXr.EnumerateApiLayerProperties( (uint32_t)layers.size(), &layerCount, layers.data() ) );

      Log::Write(Log::Level::Info, Fmt("Available Layers: (%d)", layerCount) );

      for(const XrApiLayerProperties& layer : layers)
      {
        Log::Write(Log::Level::Verbose, Fmt("  Name=%s SpecVersion=%s LayerVersion=%d Description=%s", layer.layerName, GetXrVersionString(layer.specVersion).c_str(), layer.layerVersion, layer.description) );

        logExtensions(layer.layerName, 4);
      }
    }
  }

  void LogInstanceInfo()
  {
    CHECK(m_instance != XR_NULL_HANDLE);

    XrInstanceProperties instanceProperties {XR_TYPE_INSTANCE_PROPERTIES};

    if(tableXr.GetInstanceProperties)
      CHECK_XRCMD(tableXr.GetInstanceProperties(m_instance, &instanceProperties) );

    Log::Write(Log::Level::Info, Fmt("Instance RuntimeName=%s RuntimeVersion=%s", instanceProperties.runtimeName, GetXrVersionString(instanceProperties.runtimeVersion).c_str() ) );
  }

  void CreateInstanceInternal()
  {
    CHECK(m_instance == XR_NULL_HANDLE);

    // Create union of extensions required by platform and graphics plugins.
    std::vector<const char*> extensions;

    // Transform platform and graphics extension std::strings to C strings.
    const std::vector<std::string> platformExtensions = m_platformPlugin->GetInstanceExtensions();
    std::transform(platformExtensions.begin(), platformExtensions.end(), std::back_inserter(extensions), [] (const std::string& ext) { return ext.c_str(); } );

    const std::vector<std::string> graphicsExtensions = m_graphicsPlugin->GetInstanceExtensions();
    std::transform(graphicsExtensions.begin(), graphicsExtensions.end(), std::back_inserter(extensions), [] (const std::string& ext) { return ext.c_str(); } );

    XrInstanceCreateInfo createInfo {XR_TYPE_INSTANCE_CREATE_INFO};
    createInfo.next = m_platformPlugin->GetInstanceCreateExtension();

    createInfo.enabledExtensionCount = (uint32_t)extensions.size();
    createInfo.enabledExtensionNames = extensions.data();

    strcpy(createInfo.applicationInfo.applicationName, "HelloXR");

    // Current version is 1.1.x, but helloxr only requires 1.0.x
    createInfo.applicationInfo.apiVersion = XR_API_VERSION_1_0;

    if(tableXr.CreateInstance)
      CHECK_XRCMD(tableXr.CreateInstance(&createInfo, &m_instance) );
  }

  void CreateInstance() override
  {
    LogLayersAndExtensions();

    CreateInstanceInternal();

    LogInstanceInfo();
  }

  void LogViewConfigurations()
  {
    CHECK(m_instance != XR_NULL_HANDLE);
    CHECK(m_systemId != XR_NULL_SYSTEM_ID);

    uint32_t viewConfigTypeCount = 0;

    if(tableXr.EnumerateViewConfigurations)
      CHECK_XRCMD(tableXr.EnumerateViewConfigurations(m_instance, m_systemId, 0, &viewConfigTypeCount, nullptr) );

    std::vector<XrViewConfigurationType> viewConfigTypes(viewConfigTypeCount);

    if(tableXr.EnumerateViewConfigurations)
      CHECK_XRCMD(tableXr.EnumerateViewConfigurations(m_instance, m_systemId, viewConfigTypeCount, &viewConfigTypeCount, viewConfigTypes.data() ) );

    CHECK( (uint32_t)viewConfigTypes.size() == viewConfigTypeCount);

    Log::Write(Log::Level::Info, Fmt("Available View Configuration Types: (%d)", viewConfigTypeCount) );

    for(XrViewConfigurationType viewConfigType : viewConfigTypes)
    {
      Log::Write(Log::Level::Verbose, Fmt("View Configuration Type: %s %s", to_string(viewConfigType), viewConfigType == m_options->Parsed.ViewConfigType ? "(Selected)" : "") );

      XrViewConfigurationProperties viewConfigProperties {XR_TYPE_VIEW_CONFIGURATION_PROPERTIES};

      if(tableXr.GetViewConfigurationProperties)
        CHECK_XRCMD(tableXr.GetViewConfigurationProperties(m_instance, m_systemId, viewConfigType, &viewConfigProperties) );

      Log::Write(Log::Level::Verbose, Fmt("View configuration FovMutable=%s", viewConfigProperties.fovMutable == XR_TRUE ? "True" : "False") );

      uint32_t viewCount = 0;

      if(tableXr.EnumerateViewConfigurationViews)
        CHECK_XRCMD(tableXr.EnumerateViewConfigurationViews(m_instance, m_systemId, viewConfigType, 0, &viewCount, nullptr) );

      if(viewCount > 0)
      {
        std::vector<XrViewConfigurationView> views(viewCount, {XR_TYPE_VIEW_CONFIGURATION_VIEW} );

        if(tableXr.EnumerateViewConfigurationViews)
          CHECK_XRCMD(tableXr.EnumerateViewConfigurationViews(m_instance, m_systemId, viewConfigType, viewCount, &viewCount, views.data() ) );

        for(uint32_t i = 0; i < views.size(); i++)
        {
          const XrViewConfigurationView& view = views[i];

          Log::Write(Log::Level::Verbose, Fmt("View [%d]: Recommended Width=%d Height=%d SampleCount=%d", i, view.recommendedImageRectWidth, view.recommendedImageRectHeight, view.recommendedSwapchainSampleCount) );

          Log::Write(Log::Level::Verbose, Fmt("View [%d]: Maximum Width=%d Height=%d SampleCount=%d", i, view.maxImageRectWidth, view.maxImageRectHeight, view.maxSwapchainSampleCount) );
        }
      }
      else
      {
        Log::Write(Log::Level::Error, Fmt("Empty view configuration type") );
      }

      LogEnvironmentBlendMode(viewConfigType);
    }
  }

  void LogEnvironmentBlendMode(XrViewConfigurationType type)
  {
    CHECK(m_instance != XR_NULL_HANDLE);
    CHECK(m_systemId != 0);

    uint32_t count = 0;

    if(tableXr.EnumerateEnvironmentBlendModes)
      CHECK_XRCMD(tableXr.EnumerateEnvironmentBlendModes(m_instance, m_systemId, type, 0, &count, nullptr) );

    CHECK(count > 0);

    Log::Write(Log::Level::Info, Fmt("Available Environment Blend Mode count : (%d)", count) );

    std::vector<XrEnvironmentBlendMode> blendModes(count);

    if(tableXr.EnumerateEnvironmentBlendModes)
      CHECK_XRCMD(tableXr.EnumerateEnvironmentBlendModes(m_instance, m_systemId, type, count, &count, blendModes.data() ) );

    bool blendModeFound = false;

    for(XrEnvironmentBlendMode mode : blendModes)
    {
      const bool blendModeMatch = (mode == m_options->Parsed.EnvironmentBlendMode);

      Log::Write(Log::Level::Info, Fmt("Environment Blend Mode (%s) : %s", to_string(mode), blendModeMatch ? "(Selected)" : "") );

      blendModeFound |= blendModeMatch;
    }

    CHECK(blendModeFound);
  }

  XrEnvironmentBlendMode GetPreferredBlendMode() const override
  {
    uint32_t count = 0;

    if(tableXr.EnumerateEnvironmentBlendModes)
      CHECK_XRCMD(tableXr.EnumerateEnvironmentBlendModes(m_instance, m_systemId, m_options->Parsed.ViewConfigType, 0, &count, nullptr) );

    CHECK(count > 0);

    std::vector<XrEnvironmentBlendMode> blendModes(count);

    if(tableXr.EnumerateEnvironmentBlendModes)
      CHECK_XRCMD(tableXr.EnumerateEnvironmentBlendModes(m_instance, m_systemId, m_options->Parsed.ViewConfigType, count, &count, blendModes.data() ) );

    for(const auto& blendMode : blendModes)
    {
      if(m_acceptableBlendModes.count(blendMode) )
        return blendMode;
    }

    THROW("No acceptable blend mode returned from the tableXr.EnumerateEnvironmentBlendModes");
  }

  void InitializeSystem() override
  {
    CHECK(m_instance != XR_NULL_HANDLE);
    CHECK(m_systemId == XR_NULL_SYSTEM_ID);

    XrSystemGetInfo systemInfo {XR_TYPE_SYSTEM_GET_INFO};
    systemInfo.formFactor = m_options->Parsed.FormFactor;

    if(tableXr.GetSystem)
      CHECK_XRCMD(tableXr.GetSystem(m_instance, &systemInfo, &m_systemId) );

    Log::Write(Log::Level::Verbose, Fmt("Using system %d for form factor %s", m_systemId, to_string(m_options->Parsed.FormFactor) ) );
    CHECK(m_instance != XR_NULL_HANDLE);
    CHECK(m_systemId != XR_NULL_SYSTEM_ID);
  }

  void InitializeDevice() override
  {
    LogViewConfigurations();

    m_graphicsPlugin->InitializeDevice(m_instance, m_systemId);
  }

  void LogReferenceSpaces()
  {
    CHECK(m_session != XR_NULL_HANDLE);

    uint32_t spaceCount;

    if(tableXr.EnumerateReferenceSpaces)
      CHECK_XRCMD(tableXr.EnumerateReferenceSpaces(m_session, 0, &spaceCount, nullptr) );

    std::vector<XrReferenceSpaceType> spaces(spaceCount);

    if(tableXr.EnumerateReferenceSpaces)
      CHECK_XRCMD(tableXr.EnumerateReferenceSpaces(m_session, spaceCount, &spaceCount, spaces.data() ) );

    Log::Write(Log::Level::Info, Fmt("Available reference spaces: %d", spaceCount) );

    for(XrReferenceSpaceType space : spaces)
      Log::Write(Log::Level::Verbose, Fmt("  Name: %s", to_string(space) ) );
  }

  struct InputState
  {
    XrActionSet actionSet {XR_NULL_HANDLE};
    XrAction grabAction {XR_NULL_HANDLE};
    XrAction poseAction {XR_NULL_HANDLE};
    XrAction vibrateAction {XR_NULL_HANDLE};
    XrAction quitAction {XR_NULL_HANDLE};

    std::array<XrPath, Side::COUNT> handSubactionPath;
    std::array<XrSpace, Side::COUNT> handSpace;
    std::array<float, Side::COUNT> handScale = { {1.0f, 1.0f} };
    std::array<XrBool32, Side::COUNT> handActive;
  };

  void InitializeActions()
  {
    // Create an action set.
    {
      XrActionSetCreateInfo actionSetInfo {XR_TYPE_ACTION_SET_CREATE_INFO};
      strcpy_s(actionSetInfo.actionSetName, "gameplay");
      strcpy_s(actionSetInfo.localizedActionSetName, "Gameplay");
      actionSetInfo.priority = 0;

      if(tableXr.CreateActionSet)
        CHECK_XRCMD(tableXr.CreateActionSet(m_instance, &actionSetInfo, &m_input.actionSet) );
    }

    // Get the XrPath for the left and right hands - we will use them as subaction paths.

    if(tableXr.StringToPath)
      CHECK_XRCMD(tableXr.StringToPath(m_instance, "/user/hand/left", &m_input.handSubactionPath[Side::LEFT] ) );

    if(tableXr.StringToPath)
      CHECK_XRCMD(tableXr.StringToPath(m_instance, "/user/hand/right", &m_input.handSubactionPath[Side::RIGHT] ) );

    // Create actions.
    {
      // Create an input action for grabbing objects with the left and right hands.
      XrActionCreateInfo actionInfo {XR_TYPE_ACTION_CREATE_INFO};
      actionInfo.actionType = XR_ACTION_TYPE_FLOAT_INPUT;
      strcpy_s(actionInfo.actionName, "grab_object");
      strcpy_s(actionInfo.localizedActionName, "Grab Object");
      actionInfo.countSubactionPaths = uint32_t(m_input.handSubactionPath.size() );
      actionInfo.subactionPaths = m_input.handSubactionPath.data();

      if(tableXr.CreateAction)
        CHECK_XRCMD(tableXr.CreateAction(m_input.actionSet, &actionInfo, &m_input.grabAction) );

      // Create an input action getting the left and right hand poses.
      actionInfo.actionType = XR_ACTION_TYPE_POSE_INPUT;
      strcpy_s(actionInfo.actionName, "hand_pose");
      strcpy_s(actionInfo.localizedActionName, "Hand Pose");
      actionInfo.countSubactionPaths = uint32_t(m_input.handSubactionPath.size() );
      actionInfo.subactionPaths = m_input.handSubactionPath.data();

      if(tableXr.CreateAction)
        CHECK_XRCMD(tableXr.CreateAction(m_input.actionSet, &actionInfo, &m_input.poseAction) );

      // Create output actions for vibrating the left and right controller.
      actionInfo.actionType = XR_ACTION_TYPE_VIBRATION_OUTPUT;
      strcpy_s(actionInfo.actionName, "vibrate_hand");
      strcpy_s(actionInfo.localizedActionName, "Vibrate Hand");
      actionInfo.countSubactionPaths = uint32_t(m_input.handSubactionPath.size() );
      actionInfo.subactionPaths = m_input.handSubactionPath.data();

      if(tableXr.CreateAction)
        CHECK_XRCMD(tableXr.CreateAction(m_input.actionSet, &actionInfo, &m_input.vibrateAction) );

      // Create input actions for quitting the session using the left and right controller.
      // Since it doesn't matter which hand did this, we do not specify subaction paths for it.
      // We will just suggest bindings for both hands, where possible.
      actionInfo.actionType = XR_ACTION_TYPE_BOOLEAN_INPUT;
      strcpy_s(actionInfo.actionName, "quit_session");
      strcpy_s(actionInfo.localizedActionName, "Quit Session");
      actionInfo.countSubactionPaths = 0;
      actionInfo.subactionPaths = nullptr;

      if(tableXr.CreateAction)
        CHECK_XRCMD(tableXr.CreateAction(m_input.actionSet, &actionInfo, &m_input.quitAction) );
    }

    std::array<XrPath, Side::COUNT> selectPath;
    std::array<XrPath, Side::COUNT> squeezeValuePath;
    std::array<XrPath, Side::COUNT> squeezeForcePath;
    std::array<XrPath, Side::COUNT> squeezeClickPath;
    std::array<XrPath, Side::COUNT> posePath;
    std::array<XrPath, Side::COUNT> hapticPath;
    std::array<XrPath, Side::COUNT> menuClickPath;
    std::array<XrPath, Side::COUNT> bClickPath;
    std::array<XrPath, Side::COUNT> triggerValuePath;

    if(tableXr.StringToPath)
    {
      CHECK_XRCMD(tableXr.StringToPath(m_instance, "/user/hand/left/input/select/click", &selectPath[Side::LEFT] ) );
      CHECK_XRCMD(tableXr.StringToPath(m_instance, "/user/hand/right/input/select/click", &selectPath[Side::RIGHT] ) );
      CHECK_XRCMD(tableXr.StringToPath(m_instance, "/user/hand/left/input/squeeze/value", &squeezeValuePath[Side::LEFT] ) );
      CHECK_XRCMD(tableXr.StringToPath(m_instance, "/user/hand/right/input/squeeze/value", &squeezeValuePath[Side::RIGHT] ) );
      CHECK_XRCMD(tableXr.StringToPath(m_instance, "/user/hand/left/input/squeeze/force", &squeezeForcePath[Side::LEFT] ) );
      CHECK_XRCMD(tableXr.StringToPath(m_instance, "/user/hand/right/input/squeeze/force", &squeezeForcePath[Side::RIGHT] ) );
      CHECK_XRCMD(tableXr.StringToPath(m_instance, "/user/hand/left/input/squeeze/click", &squeezeClickPath[Side::LEFT] ) );
      CHECK_XRCMD(tableXr.StringToPath(m_instance, "/user/hand/right/input/squeeze/click", &squeezeClickPath[Side::RIGHT] ) );
      CHECK_XRCMD(tableXr.StringToPath(m_instance, "/user/hand/left/input/grip/pose", &posePath[Side::LEFT] ) );
      CHECK_XRCMD(tableXr.StringToPath(m_instance, "/user/hand/right/input/grip/pose", &posePath[Side::RIGHT] ) );
      CHECK_XRCMD(tableXr.StringToPath(m_instance, "/user/hand/left/output/haptic", &hapticPath[Side::LEFT] ) );
      CHECK_XRCMD(tableXr.StringToPath(m_instance, "/user/hand/right/output/haptic", &hapticPath[Side::RIGHT] ) );
      CHECK_XRCMD(tableXr.StringToPath(m_instance, "/user/hand/left/input/menu/click", &menuClickPath[Side::LEFT] ) );
      CHECK_XRCMD(tableXr.StringToPath(m_instance, "/user/hand/right/input/menu/click", &menuClickPath[Side::RIGHT] ) );
      CHECK_XRCMD(tableXr.StringToPath(m_instance, "/user/hand/left/input/b/click", &bClickPath[Side::LEFT] ) );
      CHECK_XRCMD(tableXr.StringToPath(m_instance, "/user/hand/right/input/b/click", &bClickPath[Side::RIGHT] ) );
      CHECK_XRCMD(tableXr.StringToPath(m_instance, "/user/hand/left/input/trigger/value", &triggerValuePath[Side::LEFT] ) );
      CHECK_XRCMD(tableXr.StringToPath(m_instance, "/user/hand/right/input/trigger/value", &triggerValuePath[Side::RIGHT] ) );
    }

    // Suggest bindings for KHR Simple.
    {
      XrPath khrSimpleInteractionProfilePath;

      if(tableXr.StringToPath)
        CHECK_XRCMD(tableXr.StringToPath(m_instance, "/interaction_profiles/khr/simple_controller", &khrSimpleInteractionProfilePath) );

      std::vector<XrActionSuggestedBinding> bindings { {// Fall back to a click input for the grab action.
                                                      {m_input.grabAction, selectPath[Side::LEFT]},
                                                      {m_input.grabAction, selectPath[Side::RIGHT]},
                                                      {m_input.poseAction, posePath[Side::LEFT]},
                                                      {m_input.poseAction, posePath[Side::RIGHT]},
                                                      {m_input.quitAction, menuClickPath[Side::LEFT]},
                                                      {m_input.quitAction, menuClickPath[Side::RIGHT]},
                                                      {m_input.vibrateAction, hapticPath[Side::LEFT]},
                                                      {m_input.vibrateAction, hapticPath[Side::RIGHT]} } };

      XrInteractionProfileSuggestedBinding suggestedBindings {XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING};

      suggestedBindings.interactionProfile = khrSimpleInteractionProfilePath;
      suggestedBindings.suggestedBindings = bindings.data();
      suggestedBindings.countSuggestedBindings = (uint32_t)bindings.size();

      if(tableXr.SuggestInteractionProfileBindings)
        CHECK_XRCMD(tableXr.SuggestInteractionProfileBindings(m_instance, &suggestedBindings) );
    }

    // Suggest bindings for the Oculus Touch.
    {
      XrPath oculusTouchInteractionProfilePath;

      if(tableXr.StringToPath)
        CHECK_XRCMD(tableXr.StringToPath(m_instance, "/interaction_profiles/oculus/touch_controller", &oculusTouchInteractionProfilePath) );

      std::vector<XrActionSuggestedBinding> bindings { { {m_input.grabAction, squeezeValuePath[Side::LEFT]},
                                                      {m_input.grabAction, squeezeValuePath[Side::RIGHT]},
                                                      {m_input.poseAction, posePath[Side::LEFT]},
                                                      {m_input.poseAction, posePath[Side::RIGHT]},
                                                      {m_input.quitAction, menuClickPath[Side::LEFT]},
                                                      {m_input.vibrateAction, hapticPath[Side::LEFT]},
                                                      {m_input.vibrateAction, hapticPath[Side::RIGHT]} } };

      XrInteractionProfileSuggestedBinding suggestedBindings {XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING};

      suggestedBindings.interactionProfile = oculusTouchInteractionProfilePath;
      suggestedBindings.suggestedBindings = bindings.data();
      suggestedBindings.countSuggestedBindings = (uint32_t)bindings.size();

      if(tableXr.SuggestInteractionProfileBindings)
        CHECK_XRCMD(tableXr.SuggestInteractionProfileBindings(m_instance, &suggestedBindings) );
    }

    // Suggest bindings for the Vive Controller.
    {
      XrPath viveControllerInteractionProfilePath;

      if(tableXr.StringToPath)
        CHECK_XRCMD(tableXr.StringToPath(m_instance, "/interaction_profiles/htc/vive_controller", &viveControllerInteractionProfilePath) );

      std::vector<XrActionSuggestedBinding> bindings { { {m_input.grabAction, triggerValuePath[Side::LEFT]},
                                                      {m_input.grabAction, triggerValuePath[Side::RIGHT]},
                                                      {m_input.poseAction, posePath[Side::LEFT]},
                                                      {m_input.poseAction, posePath[Side::RIGHT]},
                                                      {m_input.quitAction, menuClickPath[Side::LEFT]},
                                                      {m_input.quitAction, menuClickPath[Side::RIGHT]},
                                                      {m_input.vibrateAction, hapticPath[Side::LEFT]},
                                                      {m_input.vibrateAction, hapticPath[Side::RIGHT]} } };

      XrInteractionProfileSuggestedBinding suggestedBindings {XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING};

      suggestedBindings.interactionProfile = viveControllerInteractionProfilePath;
      suggestedBindings.suggestedBindings = bindings.data();
      suggestedBindings.countSuggestedBindings = (uint32_t)bindings.size();

      if(tableXr.SuggestInteractionProfileBindings)
        CHECK_XRCMD(tableXr.SuggestInteractionProfileBindings(m_instance, &suggestedBindings) );
    }

    // Suggest bindings for the Valve Index Controller.
    {
      XrPath indexControllerInteractionProfilePath;

      if(tableXr.StringToPath)
        CHECK_XRCMD(tableXr.StringToPath(m_instance, "/interaction_profiles/valve/index_controller", &indexControllerInteractionProfilePath) );

      std::vector<XrActionSuggestedBinding> bindings { { {m_input.grabAction, squeezeForcePath[Side::LEFT]},
                                                      {m_input.grabAction, squeezeForcePath[Side::RIGHT]},
                                                      {m_input.poseAction, posePath[Side::LEFT]},
                                                      {m_input.poseAction, posePath[Side::RIGHT]},
                                                      {m_input.quitAction, bClickPath[Side::LEFT]},
                                                      {m_input.quitAction, bClickPath[Side::RIGHT]},
                                                      {m_input.vibrateAction, hapticPath[Side::LEFT]},
                                                      {m_input.vibrateAction, hapticPath[Side::RIGHT]} } };

      XrInteractionProfileSuggestedBinding suggestedBindings {XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING};

      suggestedBindings.interactionProfile = indexControllerInteractionProfilePath;
      suggestedBindings.suggestedBindings = bindings.data();
      suggestedBindings.countSuggestedBindings = (uint32_t)bindings.size();

      if(tableXr.SuggestInteractionProfileBindings)
        CHECK_XRCMD(tableXr.SuggestInteractionProfileBindings(m_instance, &suggestedBindings) );
    }

    // Suggest bindings for the Microsoft Mixed Reality Motion Controller.
    {
      XrPath microsoftMixedRealityInteractionProfilePath;

      if(tableXr.StringToPath)
        CHECK_XRCMD(tableXr.StringToPath(m_instance, "/interaction_profiles/microsoft/motion_controller", &microsoftMixedRealityInteractionProfilePath) );

      std::vector<XrActionSuggestedBinding> bindings { { {m_input.grabAction, squeezeClickPath[Side::LEFT]},
                                                      {m_input.grabAction, squeezeClickPath[Side::RIGHT]},
                                                      {m_input.poseAction, posePath[Side::LEFT]},
                                                      {m_input.poseAction, posePath[Side::RIGHT]},
                                                      {m_input.quitAction, menuClickPath[Side::LEFT]},
                                                      {m_input.quitAction, menuClickPath[Side::RIGHT]},
                                                      {m_input.vibrateAction, hapticPath[Side::LEFT]},
                                                      {m_input.vibrateAction, hapticPath[Side::RIGHT]} } };

      XrInteractionProfileSuggestedBinding suggestedBindings {XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING};

      suggestedBindings.interactionProfile = microsoftMixedRealityInteractionProfilePath;
      suggestedBindings.suggestedBindings = bindings.data();
      suggestedBindings.countSuggestedBindings = (uint32_t)bindings.size();

      if(tableXr.SuggestInteractionProfileBindings)
        CHECK_XRCMD(tableXr.SuggestInteractionProfileBindings(m_instance, &suggestedBindings) );
    }

    XrActionSpaceCreateInfo actionSpaceInfo {XR_TYPE_ACTION_SPACE_CREATE_INFO};

    actionSpaceInfo.action = m_input.poseAction;
    actionSpaceInfo.poseInActionSpace.orientation.w = 1.f;
    actionSpaceInfo.subactionPath = m_input.handSubactionPath[Side::LEFT];

    if(tableXr.CreateActionSpace)
      CHECK_XRCMD(tableXr.CreateActionSpace(m_session, &actionSpaceInfo, &m_input.handSpace[Side::LEFT] ) );

    actionSpaceInfo.subactionPath = m_input.handSubactionPath[Side::RIGHT];

    if(tableXr.CreateActionSpace)
      CHECK_XRCMD(tableXr.CreateActionSpace(m_session, &actionSpaceInfo, &m_input.handSpace[Side::RIGHT] ) );

    XrSessionActionSetsAttachInfo attachInfo {XR_TYPE_SESSION_ACTION_SETS_ATTACH_INFO};
    attachInfo.countActionSets = 1;
    attachInfo.actionSets = &m_input.actionSet;

    if(tableXr.AttachSessionActionSets)
      CHECK_XRCMD(tableXr.AttachSessionActionSets(m_session, &attachInfo) );
  }

  void CreateVisualizedSpaces()
  {
    CHECK(m_session != XR_NULL_HANDLE);

    std::string visualizedSpaces[] = {"ViewFront", "Local", "Stage", "StageLeft", "StageRight", "StageLeftRotated", "StageRightRotated"};

    for(const auto& visualizedSpace : visualizedSpaces)
    {
      XrReferenceSpaceCreateInfo referenceSpaceCreateInfo = GetXrReferenceSpaceCreateInfo(visualizedSpace);

      XrSpace space;

      XrResult res = XR_ERROR_VALIDATION_FAILURE;

      if(tableXr.CreateReferenceSpace)
        res = tableXr.CreateReferenceSpace(m_session, &referenceSpaceCreateInfo, &space);

      if(XR_SUCCEEDED(res) )
        m_visualizedSpaces.push_back(space);
      else
        Log::Write(Log::Level::Warning, Fmt("Failed to create reference space %s with error %d", visualizedSpace.c_str(), res) );
    }
  }

  void InitializeSession() override
  {
    CHECK(m_instance != XR_NULL_HANDLE);
    CHECK(m_session == XR_NULL_HANDLE);

    {
      Log::Write(Log::Level::Verbose, Fmt("Creating session...") );

      XrSessionCreateInfo createInfo {XR_TYPE_SESSION_CREATE_INFO};

      createInfo.next = m_graphicsPlugin->GetGraphicsBinding();
      createInfo.systemId = m_systemId;

      if(tableXr.CreateSession)
        CHECK_XRCMD(tableXr.CreateSession(m_instance, &createInfo, &m_session) );
    }

    LogReferenceSpaces();
    InitializeActions();
    CreateVisualizedSpaces();

    {
      XrReferenceSpaceCreateInfo referenceSpaceCreateInfo = GetXrReferenceSpaceCreateInfo(m_options->AppSpace);

      if(tableXr.CreateReferenceSpace)
        CHECK_XRCMD(tableXr.CreateReferenceSpace(m_session, &referenceSpaceCreateInfo, &m_appSpace) );
    }
  }

  void CreateSwapchains() override
  {
    CHECK(m_session != XR_NULL_HANDLE);
    CHECK(m_swapchains.empty() );
    CHECK(m_configViews.empty() );

    // Read graphics properties for preferred swapchain length and logging.
    XrSystemProperties systemProperties {XR_TYPE_SYSTEM_PROPERTIES};

    if(tableXr.GetSystemProperties)
      CHECK_XRCMD(tableXr.GetSystemProperties(m_instance, m_systemId, &systemProperties) );

    // Log system properties.
    Log::Write(Log::Level::Info, Fmt("System Properties: Name=%s VendorId=%d", systemProperties.systemName, systemProperties.vendorId) );

    Log::Write(Log::Level::Info, Fmt("System Graphics Properties: MaxWidth=%d MaxHeight=%d MaxLayers=%d", systemProperties.graphicsProperties.maxSwapchainImageWidth, systemProperties.graphicsProperties.maxSwapchainImageHeight, systemProperties.graphicsProperties.maxLayerCount) );

    Log::Write(Log::Level::Info, Fmt("System Tracking Properties: OrientationTracking=%s PositionTracking=%s", systemProperties.trackingProperties.orientationTracking == XR_TRUE ? "True" : "False", systemProperties.trackingProperties.positionTracking == XR_TRUE ? "True" : "False") );

    // Note: No other view configurations exist at the time this code was written. If this
    // condition is not met, the project will need to be audited to see how support should be
    // added.
    CHECK_MSG(m_options->Parsed.ViewConfigType == XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, "Unsupported view configuration type");

    // Query and cache view configuration views.
    uint32_t viewCount;

    if(tableXr.EnumerateViewConfigurationViews)
      CHECK_XRCMD(tableXr.EnumerateViewConfigurationViews(m_instance, m_systemId, m_options->Parsed.ViewConfigType, 0, &viewCount, nullptr) );

    m_configViews.resize(viewCount, {XR_TYPE_VIEW_CONFIGURATION_VIEW} );

    if(tableXr.EnumerateViewConfigurationViews)
      CHECK_XRCMD(tableXr.EnumerateViewConfigurationViews(m_instance, m_systemId, m_options->Parsed.ViewConfigType, viewCount, &viewCount, m_configViews.data() ) );

    // Create and cache view buffer for xrLocateViews later
    m_views.resize(viewCount, {XR_TYPE_VIEW} );

    // Create the swapchain and get the images.
    if(viewCount > 0)
    {
      // Select a swapchain format.
      uint32_t swapchainFormatCount = 0;

      if(tableXr.EnumerateSwapchainFormats)
        CHECK_XRCMD(tableXr.EnumerateSwapchainFormats(m_session, 0, &swapchainFormatCount, nullptr) );

      std::vector<int64_t> swapchainFormats(swapchainFormatCount);

      if(tableXr.EnumerateSwapchainFormats)
        CHECK_XRCMD(tableXr.EnumerateSwapchainFormats(m_session, (uint32_t)swapchainFormats.size(), &swapchainFormatCount, swapchainFormats.data() ) );

      CHECK(swapchainFormatCount == swapchainFormats.size() );
      m_colorSwapchainFormat = m_graphicsPlugin->SelectColorSwapchainFormat(swapchainFormats);

      // Print swapchain formats and the selected one
      {
        std::string swapchainFormatsString;

        for(int64_t format : swapchainFormats)
        {
          const bool selected = format == m_colorSwapchainFormat;

          swapchainFormatsString += " ";

          if(selected)
            swapchainFormatsString += "[";

          swapchainFormatsString += std::to_string(format);

          if(selected)
            swapchainFormatsString += "]";
        }

        Log::Write(Log::Level::Verbose, Fmt("Swapchain Formats: %s", swapchainFormatsString.c_str() ) );
      }

      // Create a swapchain for each view
      for(uint32_t i = 0; i < viewCount; i++)
      {
        const XrViewConfigurationView& vp = m_configViews[i];

        Log::Write(Log::Level::Info, Fmt("Creating swapchain for view %d with dimensions Width=%d Height=%d SampleCount=%d", i, vp.recommendedImageRectWidth, vp.recommendedImageRectHeight, vp.recommendedSwapchainSampleCount) );

        // Create the swapchain.
        XrSwapchainCreateInfo swapchainCreateInfo {XR_TYPE_SWAPCHAIN_CREATE_INFO};
        swapchainCreateInfo.arraySize = 1;
        swapchainCreateInfo.format = m_colorSwapchainFormat;
        swapchainCreateInfo.width = vp.recommendedImageRectWidth;
        swapchainCreateInfo.height = vp.recommendedImageRectHeight;
        swapchainCreateInfo.mipCount = 1;
        swapchainCreateInfo.faceCount = 1;
        swapchainCreateInfo.sampleCount = m_graphicsPlugin->GetSupportedSwapchainSampleCount(vp);
        swapchainCreateInfo.usageFlags = XR_SWAPCHAIN_USAGE_SAMPLED_BIT | XR_SWAPCHAIN_USAGE_COLOR_ATTACHMENT_BIT;
        Swapchain swapchain;
        swapchain.width = swapchainCreateInfo.width;
        swapchain.height = swapchainCreateInfo.height;

        if(tableXr.CreateSwapchain)
          CHECK_XRCMD(tableXr.CreateSwapchain(m_session, &swapchainCreateInfo, &swapchain.handle) );

        m_swapchains.push_back(swapchain);

        uint32_t imageCount = 0;

        if(tableXr.EnumerateSwapchainImages)
          CHECK_XRCMD(tableXr.EnumerateSwapchainImages(swapchain.handle, 0, &imageCount, nullptr) );

        // XXX This should really just return XrSwapchainImageBaseHeader*
        std::vector<XrSwapchainImageBaseHeader*> swapchainImages = m_graphicsPlugin->AllocateSwapchainImageStructs(imageCount, swapchainCreateInfo);

        if(tableXr.EnumerateSwapchainImages)
          CHECK_XRCMD(tableXr.EnumerateSwapchainImages(swapchain.handle, imageCount, &imageCount, swapchainImages[0] ) );

        m_swapchainImages.insert(std::make_pair(swapchain.handle, std::move(swapchainImages) ) );
      }
    }
  }

  const XrEventDataBaseHeader* TryReadNextEvent()
  {
    XrEventDataBaseHeader* baseHeader = reinterpret_cast<XrEventDataBaseHeader*>(&m_eventDataBuffer);
    *baseHeader = {XR_TYPE_EVENT_DATA_BUFFER};

    XrResult xr = XR_ERROR_VALIDATION_FAILURE;

    if(tableXr.PollEvent)
      xr = tableXr.PollEvent(m_instance, &m_eventDataBuffer);

    if(xr == XR_SUCCESS)
    {
      if(baseHeader->type == XR_TYPE_EVENT_DATA_EVENTS_LOST)
      {
        const XrEventDataEventsLost* const eventsLost = reinterpret_cast<const XrEventDataEventsLost*>(baseHeader);
        Log::Write(Log::Level::Warning, Fmt("%d events lost", eventsLost->lostEventCount) );
      }

      return baseHeader;
    }

    if(xr == XR_EVENT_UNAVAILABLE)
    {
      return nullptr;
    }

    THROW_XR(xr, "xrPollEvent");
  }

  void PollEvents(bool* exitRenderLoop, bool* requestRestart) override
  {
    *exitRenderLoop = *requestRestart = false;

    while(const XrEventDataBaseHeader* event = TryReadNextEvent() )
    {
      switch(event->type)
      {

      case XR_TYPE_EVENT_DATA_INSTANCE_LOSS_PENDING:
      {
        const auto& instanceLossPending = *reinterpret_cast<const XrEventDataInstanceLossPending*>(event);
        Log::Write(Log::Level::Warning, Fmt("XrEventDataInstanceLossPending by %lld", instanceLossPending.lossTime) );
        *exitRenderLoop = true;
        *requestRestart = true;
        return;
      }

      case XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED:
      {
        auto sessionStateChangedEvent = *reinterpret_cast<const XrEventDataSessionStateChanged*>(event);
        HandleSessionStateChangedEvent(sessionStateChangedEvent, exitRenderLoop, requestRestart);
        break;
      }

      case XR_TYPE_EVENT_DATA_INTERACTION_PROFILE_CHANGED:
      {
        LogActionSourceName(m_input.grabAction, "Grab");
        LogActionSourceName(m_input.quitAction, "Quit");
        LogActionSourceName(m_input.poseAction, "Pose");
        LogActionSourceName(m_input.vibrateAction, "Vibrate");
      }
      break;

      case XR_TYPE_EVENT_DATA_REFERENCE_SPACE_CHANGE_PENDING:
      default:
      {
        Log::Write(Log::Level::Verbose, Fmt("Ignoring event type %d", event->type) );
        break;
      }

      }
    }
  }

  void HandleSessionStateChangedEvent(const XrEventDataSessionStateChanged& stateChangedEvent, bool* exitRenderLoop, bool* requestRestart)
  {
    const XrSessionState oldState = m_sessionState;
    m_sessionState = stateChangedEvent.state;

    Log::Write(Log::Level::Info, Fmt("XrEventDataSessionStateChanged: state %s->%s session=%lld time=%lld", to_string(oldState), to_string(m_sessionState), stateChangedEvent.session, stateChangedEvent.time) );

    if(stateChangedEvent.session != XR_NULL_HANDLE && stateChangedEvent.session != m_session)
    {
      Log::Write(Log::Level::Error, "XrEventDataSessionStateChanged for unknown session");
      return;
    }

    switch(m_sessionState)
    {

    case XR_SESSION_STATE_READY:
    {
      CHECK(m_session != XR_NULL_HANDLE);

      XrSessionBeginInfo sessionBeginInfo {XR_TYPE_SESSION_BEGIN_INFO};

      sessionBeginInfo.primaryViewConfigurationType = m_options->Parsed.ViewConfigType;

      if(tableXr.BeginSession)
        CHECK_XRCMD(tableXr.BeginSession(m_session, &sessionBeginInfo) );

      m_sessionRunning = true;
      break;
    }

    case XR_SESSION_STATE_STOPPING:
    {
      CHECK(m_session != XR_NULL_HANDLE);
      m_sessionRunning = false;

      if(tableXr.EndSession)
        CHECK_XRCMD(tableXr.EndSession(m_session) );

      break;
    }

    case XR_SESSION_STATE_EXITING:
    {
      *exitRenderLoop = true;
      *requestRestart = false;
      break;
    }

    case XR_SESSION_STATE_LOSS_PENDING:
    {
      *exitRenderLoop = true;
      *requestRestart = true;
      break;
    }

    default:
    {
    }
    break;

    }
  }

  void LogActionSourceName(XrAction action, const std::string& actionName) const
  {
    XrBoundSourcesForActionEnumerateInfo getInfo = {XR_TYPE_BOUND_SOURCES_FOR_ACTION_ENUMERATE_INFO};

    getInfo.action = action;

    uint32_t pathCount = 0;

    if(tableXr.EnumerateBoundSourcesForAction)
      CHECK_XRCMD(tableXr.EnumerateBoundSourcesForAction(m_session, &getInfo, 0, &pathCount, nullptr) );

    std::vector<XrPath> paths(pathCount);

    if(tableXr.EnumerateBoundSourcesForAction)
      CHECK_XRCMD(tableXr.EnumerateBoundSourcesForAction(m_session, &getInfo, uint32_t(paths.size() ), &pathCount, paths.data() ) );

    std::string sourceName;

    for(uint32_t i = 0; i < pathCount; ++i)
    {
      constexpr XrInputSourceLocalizedNameFlags all = XR_INPUT_SOURCE_LOCALIZED_NAME_USER_PATH_BIT | XR_INPUT_SOURCE_LOCALIZED_NAME_INTERACTION_PROFILE_BIT | XR_INPUT_SOURCE_LOCALIZED_NAME_COMPONENT_BIT;

      XrInputSourceLocalizedNameGetInfo nameInfo = {XR_TYPE_INPUT_SOURCE_LOCALIZED_NAME_GET_INFO};

      nameInfo.sourcePath = paths[i];
      nameInfo.whichComponents = all;

      uint32_t size = 0;

      if(tableXr.GetInputSourceLocalizedName)
        CHECK_XRCMD(tableXr.GetInputSourceLocalizedName(m_session, &nameInfo, 0, &size, nullptr) );

      if(size < 1)
        continue;

      std::vector<char> grabSource(size);

      if(tableXr.GetInputSourceLocalizedName)
        CHECK_XRCMD(tableXr.GetInputSourceLocalizedName(m_session, &nameInfo, uint32_t(grabSource.size() ), &size, grabSource.data() ) );

      if(!sourceName.empty() )
        sourceName += " and ";

      sourceName += "'";
      sourceName += std::string(grabSource.data(), size - 1);

      sourceName += "'";
    }

    Log::Write(Log::Level::Info, Fmt("%s action is bound to %s", actionName.c_str(), ( (!sourceName.empty() ) ? sourceName.c_str() : "nothing") ) );
  }

  bool IsSessionRunning() const override { return m_sessionRunning; }

  bool IsSessionFocused() const override { return m_sessionState == XR_SESSION_STATE_FOCUSED; }

  void PollActions() override
  {
    m_input.handActive = {XR_FALSE, XR_FALSE};

    // Sync actions
    const XrActiveActionSet activeActionSet {m_input.actionSet, XR_NULL_PATH};

    XrActionsSyncInfo syncInfo {XR_TYPE_ACTIONS_SYNC_INFO};
    syncInfo.countActiveActionSets = 1;
    syncInfo.activeActionSets = &activeActionSet;

    if(tableXr.SyncActions)
      CHECK_XRCMD(tableXr.SyncActions(m_session, &syncInfo) );

    // Get pose and grab action state and start haptic vibrate when hand is 90% squeezed.
    for(auto hand : {Side::LEFT, Side::RIGHT} )
    {
      XrActionStateGetInfo getInfo {XR_TYPE_ACTION_STATE_GET_INFO};

      getInfo.action = m_input.grabAction;
      getInfo.subactionPath = m_input.handSubactionPath[hand];

      XrActionStateFloat grabValue {XR_TYPE_ACTION_STATE_FLOAT};

      if(tableXr.GetActionStateFloat)
        CHECK_XRCMD(tableXr.GetActionStateFloat(m_session, &getInfo, &grabValue) );

      if(grabValue.isActive == XR_TRUE)
      {
        // Scale the rendered hand by 1.0f (open) to 0.5f (fully squeezed).
        m_input.handScale[hand] = 1.0f - 0.5f * grabValue.currentState;

        if(grabValue.currentState > 0.9f)
        {
          XrHapticVibration vibration {XR_TYPE_HAPTIC_VIBRATION};
          vibration.amplitude = 0.5;
          vibration.duration = XR_MIN_HAPTIC_DURATION;
          vibration.frequency = XR_FREQUENCY_UNSPECIFIED;

          XrHapticActionInfo hapticActionInfo {XR_TYPE_HAPTIC_ACTION_INFO};
          hapticActionInfo.action = m_input.vibrateAction;
          hapticActionInfo.subactionPath = m_input.handSubactionPath[hand];

          if(tableXr.ApplyHapticFeedback)
            CHECK_XRCMD(tableXr.ApplyHapticFeedback(m_session, &hapticActionInfo, (XrHapticBaseHeader*) &vibration) );
        }
      }

      getInfo.action = m_input.poseAction;

      XrActionStatePose poseState {XR_TYPE_ACTION_STATE_POSE};

      if(tableXr.GetActionStatePose)
        CHECK_XRCMD(tableXr.GetActionStatePose(m_session, &getInfo, &poseState) );

      m_input.handActive[hand] = poseState.isActive;
    }

    // There were no subaction paths specified for the quit action, because we don't care which hand did it.
    XrActionStateGetInfo getInfo {XR_TYPE_ACTION_STATE_GET_INFO, nullptr, m_input.quitAction, XR_NULL_PATH};
    XrActionStateBoolean quitValue {XR_TYPE_ACTION_STATE_BOOLEAN};

    if(tableXr.GetActionStateBoolean)
      CHECK_XRCMD(tableXr.GetActionStateBoolean(m_session, &getInfo, &quitValue) );

    if(quitValue.isActive == XR_TRUE && quitValue.changedSinceLastSync == XR_TRUE && quitValue.currentState == XR_TRUE && tableXr.RequestExitSession)
      CHECK_XRCMD(tableXr.RequestExitSession(m_session) );
  }

  void RenderFrame() override
  {
    CHECK(m_session != XR_NULL_HANDLE);

    XrFrameWaitInfo frameWaitInfo {XR_TYPE_FRAME_WAIT_INFO};
    XrFrameState frameState {XR_TYPE_FRAME_STATE};

    if(tableXr.WaitFrame)
      CHECK_XRCMD(tableXr.WaitFrame(m_session, &frameWaitInfo, &frameState) );

    XrFrameBeginInfo frameBeginInfo {XR_TYPE_FRAME_BEGIN_INFO};

    if(tableXr.BeginFrame)
      CHECK_XRCMD(tableXr.BeginFrame(m_session, &frameBeginInfo) );

    std::vector<XrCompositionLayerBaseHeader*> layers;
    XrCompositionLayerProjection layer {XR_TYPE_COMPOSITION_LAYER_PROJECTION};
    std::vector<XrCompositionLayerProjectionView> projectionLayerViews;

    if(frameState.shouldRender == XR_TRUE)
    {
      if(RenderLayer(frameState.predictedDisplayTime, projectionLayerViews, layer) )
        layers.push_back(reinterpret_cast<XrCompositionLayerBaseHeader*>(&layer) );
    }

    XrFrameEndInfo frameEndInfo {XR_TYPE_FRAME_END_INFO};
    frameEndInfo.displayTime = frameState.predictedDisplayTime;
    frameEndInfo.environmentBlendMode = m_options->Parsed.EnvironmentBlendMode;
    frameEndInfo.layerCount = (uint32_t)layers.size();
    frameEndInfo.layers = layers.data();

    if(tableXr.EndFrame)
      CHECK_XRCMD(tableXr.EndFrame(m_session, &frameEndInfo) );
  }

  bool RenderLayer(XrTime predictedDisplayTime, std::vector<XrCompositionLayerProjectionView>& projectionLayerViews, XrCompositionLayerProjection& layer)
  {
    XrResult res = XR_ERROR_VALIDATION_FAILURE;

    XrViewState viewState {XR_TYPE_VIEW_STATE};
    uint32_t viewCapacityInput = (uint32_t)m_views.size();
    uint32_t viewCountOutput;

    XrViewLocateInfo viewLocateInfo {XR_TYPE_VIEW_LOCATE_INFO};
    viewLocateInfo.viewConfigurationType = m_options->Parsed.ViewConfigType;
    viewLocateInfo.displayTime = predictedDisplayTime;
    viewLocateInfo.space = m_appSpace;

    if(tableXr.LocateViews)
    {
      res = tableXr.LocateViews(m_session, &viewLocateInfo, &viewState, viewCapacityInput, &viewCountOutput, m_views.data() );
      CHECK_XRRESULT(res, "xrLocateViews");
    }

    if( (viewState.viewStateFlags & XR_VIEW_STATE_POSITION_VALID_BIT) == 0 || (viewState.viewStateFlags & XR_VIEW_STATE_ORIENTATION_VALID_BIT) == 0)
      return false;  // There is no valid tracking poses for the views.

    CHECK(viewCountOutput == viewCapacityInput);
    CHECK(viewCountOutput == m_configViews.size() );
    CHECK(viewCountOutput == m_swapchains.size() );

    projectionLayerViews.resize(viewCountOutput);

    // For each locatable space that we want to visualize, render a 25cm cube.
    std::vector<Cube> cubes;

    for(XrSpace visualizedSpace : m_visualizedSpaces)
    {
      XrSpaceLocation spaceLocation {XR_TYPE_SPACE_LOCATION};

      if(tableXr.LocateSpace)
      {
        res = tableXr.LocateSpace(visualizedSpace, m_appSpace, predictedDisplayTime, &spaceLocation);
        CHECK_XRRESULT(res, "xrLocateSpace");
      }

      if(XR_UNQUALIFIED_SUCCESS(res) )
      {
        if( (spaceLocation.locationFlags & XR_SPACE_LOCATION_POSITION_VALID_BIT) != 0 && (spaceLocation.locationFlags & XR_SPACE_LOCATION_ORIENTATION_VALID_BIT) != 0)
          cubes.push_back(Cube {spaceLocation.pose, {0.25f, 0.25f, 0.25f} } );
      }
      else
      {
        Log::Write(Log::Level::Verbose, Fmt("Unable to locate a visualized reference space in app space: %d", res) );
      }
    }

    // Render a 10cm cube scaled by grabAction for each hand. Note renderHand will only be
    // true when the application has focus.
    for(auto hand : {Side::LEFT, Side::RIGHT} )
    {
      XrSpaceLocation spaceLocation {XR_TYPE_SPACE_LOCATION};

      if(tableXr.LocateSpace)
      {
        res = tableXr.LocateSpace(m_input.handSpace[hand], m_appSpace, predictedDisplayTime, &spaceLocation);
        CHECK_XRRESULT(res, "xrLocateSpace");
      }

      if(XR_UNQUALIFIED_SUCCESS(res) )
      {
        if( (spaceLocation.locationFlags & XR_SPACE_LOCATION_POSITION_VALID_BIT) != 0 && (spaceLocation.locationFlags & XR_SPACE_LOCATION_ORIENTATION_VALID_BIT) != 0)
        {
          float scale = 0.1f * m_input.handScale[hand];
          cubes.push_back(Cube {spaceLocation.pose, {scale, scale, scale} } );
        }
      }
      else
      {
        // Tracking loss is expected when the hand is not active so only log a message
        // if the hand is active.
        if(m_input.handActive[hand] == XR_TRUE)
        {
          const char* handName[] = {"left", "right"};
          Log::Write(Log::Level::Verbose, Fmt("Unable to locate %s hand action space in app space: %d", handName[hand], res) );
        }
      }
    }

    // Render view to the appropriate part of the swapchain image.
    for(uint32_t i = 0; i < viewCountOutput; i++)
    {
      // Each view has a separate swapchain which is acquired, rendered to, and released.
      const Swapchain viewSwapchain = m_swapchains[i];

      XrSwapchainImageAcquireInfo acquireInfo {XR_TYPE_SWAPCHAIN_IMAGE_ACQUIRE_INFO};

      uint32_t swapchainImageIndex;

      if(tableXr.AcquireSwapchainImage)
        CHECK_XRCMD(tableXr.AcquireSwapchainImage(viewSwapchain.handle, &acquireInfo, &swapchainImageIndex) );

      XrSwapchainImageWaitInfo waitInfo {XR_TYPE_SWAPCHAIN_IMAGE_WAIT_INFO};
      waitInfo.timeout = XR_INFINITE_DURATION;

      if(tableXr.WaitSwapchainImage)
        CHECK_XRCMD(tableXr.WaitSwapchainImage(viewSwapchain.handle, &waitInfo) );

      projectionLayerViews[i] = {XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW};
      projectionLayerViews[i].pose = m_views[i].pose;
      projectionLayerViews[i].fov = m_views[i].fov;
      projectionLayerViews[i].subImage.swapchain = viewSwapchain.handle;
      projectionLayerViews[i].subImage.imageRect.offset = {0, 0};
      projectionLayerViews[i].subImage.imageRect.extent = {viewSwapchain.width, viewSwapchain.height};

      const XrSwapchainImageBaseHeader* const swapchainImage = m_swapchainImages[viewSwapchain.handle][swapchainImageIndex];
      m_graphicsPlugin->RenderView(projectionLayerViews[i], swapchainImage, m_colorSwapchainFormat, cubes);

      XrSwapchainImageReleaseInfo releaseInfo {XR_TYPE_SWAPCHAIN_IMAGE_RELEASE_INFO};

      if(tableXr.ReleaseSwapchainImage)
        CHECK_XRCMD(tableXr.ReleaseSwapchainImage(viewSwapchain.handle, &releaseInfo) );
    }

    layer.space = m_appSpace;
    layer.layerFlags = m_options->Parsed.EnvironmentBlendMode == XR_ENVIRONMENT_BLEND_MODE_ALPHA_BLEND ? XR_COMPOSITION_LAYER_BLEND_TEXTURE_SOURCE_ALPHA_BIT | XR_COMPOSITION_LAYER_UNPREMULTIPLIED_ALPHA_BIT : 0;
    layer.viewCount = (uint32_t)projectionLayerViews.size();
    layer.views = projectionLayerViews.data();
    return true;
  }

private:

  const std::shared_ptr<const Options> m_options;
  std::shared_ptr<IPlatformPlugin> m_platformPlugin;
  std::shared_ptr<IGraphicsPlugin> m_graphicsPlugin;
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

} // namespace

std::shared_ptr<IOpenXrProgram> CreateOpenXrProgram(const std::shared_ptr<Options>& options, const std::shared_ptr<IPlatformPlugin>& platformPlugin, const std::shared_ptr<IGraphicsPlugin>& graphicsPlugin)
{
  return std::make_shared<OpenXrProgram>(options, platformPlugin, graphicsPlugin);
}
