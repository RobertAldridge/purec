
// openxr_program.cpp

#include "header.h"

#ifdef __cplusplus
extern "C" {
#endif

XrInstance gXrInstance = XR_NULL_HANDLE;

XrSession gXrSession = XR_NULL_HANDLE;

XrSystemId gXrSystemId = XR_NULL_SYSTEM_ID;

#ifdef __cplusplus
}
#endif

namespace
{

#define strcpy_s(dest, source) strncpy( (dest), (source), sizeof(dest) )

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

static XrPassthroughFB gPassthroughFeature = XR_NULL_HANDLE;
static XrPassthroughLayerFB gPassthroughLayer = XR_NULL_HANDLE;

static PFN_xrCreatePassthroughFB gCreatePassthroughFB = nullptr;
static PFN_xrCreatePassthroughLayerFB gCreatePassthroughLayerFB = nullptr;

static PFN_xrCreateEnvironmentDepthProviderMETA gCreateEnvironmentDepthProviderMETA = nullptr;
static PFN_xrDestroyEnvironmentDepthProviderMETA gDestroyEnvironmentDepthProviderMETA = nullptr;
static PFN_xrStartEnvironmentDepthProviderMETA gStartEnvironmentDepthProviderMETA = nullptr;
static PFN_xrStopEnvironmentDepthProviderMETA gStopEnvironmentDepthProviderMETA = nullptr;
static PFN_xrCreateEnvironmentDepthSwapchainMETA gCreateEnvironmentDepthSwapchainMETA = nullptr;
static PFN_xrDestroyEnvironmentDepthSwapchainMETA gDestroyEnvironmentDepthSwapchainMETA = nullptr;
static PFN_xrEnumerateEnvironmentDepthSwapchainImagesMETA gEnumerateEnvironmentDepthSwapchainImagesMETA = nullptr;
static PFN_xrGetEnvironmentDepthSwapchainStateMETA gGetEnvironmentDepthSwapchainStateMETA = nullptr;
static PFN_xrAcquireEnvironmentDepthImageMETA gAcquireEnvironmentDepthImageMETA = nullptr;
static PFN_xrSetEnvironmentDepthHandRemovalMETA gSetEnvironmentDepthHandRemovalMETA = nullptr;

static XrEnvironmentDepthProviderMETA gEnvironmentDepthProviderMETA = XR_NULL_HANDLE;

}

void OpenXrProgram_LogLayersAndExtensions()
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

OpenXrProgram::OpenXrProgram(const std::shared_ptr<Options>& options, const std::shared_ptr<AndroidPlatformPlugin>& platformPlugin)
: m_OpenXrProgramStdSharedPtr_Options(options),
  m_OpenXrProgramStdSharedPtr_AndroidPlatformPlugin(platformPlugin),
  m_OpenXrProgramStdSet_XrEnvironmentBlendMode {XR_ENVIRONMENT_BLEND_MODE_OPAQUE, XR_ENVIRONMENT_BLEND_MODE_ADDITIVE, XR_ENVIRONMENT_BLEND_MODE_ALPHA_BLEND}
{
}

OpenXrProgram::~OpenXrProgram()
{
  if(m_OpenXrProgramInputState.actionSet != XR_NULL_HANDLE)
  {
    for(auto hand : { (int)Side::LEFT, (int)Side::RIGHT} )
    {
      if(tableXr.DestroySpace)
        tableXr.DestroySpace(m_OpenXrProgramInputState.handSpace[hand] );
    }

    if(tableXr.DestroyActionSet)
      tableXr.DestroyActionSet(m_OpenXrProgramInputState.actionSet);
  }

  for(Swapchain swapchain : m_OpenXrProgramStdVector_Swapchain)
  {
    if(tableXr.DestroySwapchain)
      tableXr.DestroySwapchain(swapchain.handle);
  }

  for(XrSpace visualizedSpace : m_OpenXrProgramStdVector_XrSpace)
  {
    if(tableXr.DestroySpace)
      tableXr.DestroySpace(visualizedSpace);
  }

  if(m_OpenXrProgramXrSpace != XR_NULL_HANDLE && tableXr.DestroySpace)
    tableXr.DestroySpace(m_OpenXrProgramXrSpace);

  if(gXrSession != XR_NULL_HANDLE && tableXr.DestroySession)
  {
    tableXr.DestroySession(gXrSession);
    gXrSession = XR_NULL_HANDLE;
  }

  if(gXrInstance != XR_NULL_HANDLE && tableXr.DestroyInstance)
  {
    tableXr.DestroyInstance(gXrInstance);
    gXrInstance = XR_NULL_HANDLE;
  }
}

void OpenXrProgram::OpenXrProgramLogInstanceInfo()
{
  CHECK(gXrInstance != XR_NULL_HANDLE);

  XrInstanceProperties instanceProperties {XR_TYPE_INSTANCE_PROPERTIES};

  if(tableXr.GetInstanceProperties)
    CHECK_XRCMD(tableXr.GetInstanceProperties(gXrInstance, &instanceProperties) );

  Log::Write(Log::Level::Info, Fmt("Instance RuntimeName=%s RuntimeVersion=%s", instanceProperties.runtimeName, GetXrVersionString(instanceProperties.runtimeVersion).c_str() ) );
}

void OpenXrProgram::OpenXrProgramCreateInstanceInternal()
{
  CHECK(gXrInstance == XR_NULL_HANDLE);

  // Create union of extensions required by platform and graphics plugins.
  std::vector<const char*> extensions;

  // Transform platform and graphics extension std::strings to C strings.
  const std::vector<std::string> platformExtensions = m_OpenXrProgramStdSharedPtr_AndroidPlatformPlugin->GetInstanceExtensions();
  std::transform(platformExtensions.begin(), platformExtensions.end(), std::back_inserter(extensions), [] (const std::string& ext) { return ext.c_str(); } );

  const std::vector<std::string> graphicsExtensions = VulkanGraphicsPlugin_VulkanGraphicsPluginGetInstanceExtensions();
  std::transform(graphicsExtensions.begin(), graphicsExtensions.end(), std::back_inserter(extensions), [] (const std::string& ext) { return ext.c_str(); } );

  XrInstanceCreateInfo createInfo {XR_TYPE_INSTANCE_CREATE_INFO};
  createInfo.next = m_OpenXrProgramStdSharedPtr_AndroidPlatformPlugin->GetInstanceCreateExtension();

  // passthrough
  extensions.push_back(XR_FB_PASSTHROUGH_EXTENSION_NAME);
  extensions.push_back(XR_FB_TRIANGLE_MESH_EXTENSION_NAME);

  // depth
  extensions.push_back(XR_META_ENVIRONMENT_DEPTH_EXTENSION_NAME);

  createInfo.enabledExtensionCount = (uint32_t)extensions.size();
  createInfo.enabledExtensionNames = extensions.data();

  strcpy(createInfo.applicationInfo.applicationName, "HelloXR");

  // Current version is 1.1.x, but helloxr only requires 1.0.x
  createInfo.applicationInfo.apiVersion = XR_API_VERSION_1_0;

  for(int index = 0; index < extensions.size(); index++)
    Log::Write(Log::Level::Info, Fmt("blah %i %s", index, extensions[index] ) );

  // available Layers: (0)
  // blah 0 XR_KHR_android_create_instance
  // blah 1 XR_KHR_vulkan_enable
  // blah 2 XR_FB_passthrough
  // blah 3 XR_FB_triangle_mesh
  // blah 4 XR_META_environment_depth

  if(tableXr.CreateInstance)
    CHECK_XRCMD(tableXr.CreateInstance(&createInfo, &gXrInstance) );
}

void OpenXrProgram::OpenXrProgramCreateInstance()
{
  OpenXrProgram_LogLayersAndExtensions();

  OpenXrProgramCreateInstanceInternal();

  OpenXrProgramLogInstanceInfo();
}

void OpenXrProgram::OpenXrProgramLogViewConfigurations()
{
  CHECK(gXrInstance != XR_NULL_HANDLE);
  CHECK(gXrSystemId != XR_NULL_SYSTEM_ID);

  uint32_t viewConfigTypeCount = 0;

  if(tableXr.EnumerateViewConfigurations)
    CHECK_XRCMD(tableXr.EnumerateViewConfigurations(gXrInstance, gXrSystemId, 0, &viewConfigTypeCount, nullptr) );

  std::vector<XrViewConfigurationType> viewConfigTypes(viewConfigTypeCount);

  if(tableXr.EnumerateViewConfigurations)
    CHECK_XRCMD(tableXr.EnumerateViewConfigurations(gXrInstance, gXrSystemId, viewConfigTypeCount, &viewConfigTypeCount, viewConfigTypes.data() ) );

  CHECK( (uint32_t)viewConfigTypes.size() == viewConfigTypeCount);

  Log::Write(Log::Level::Info, Fmt("Available View Configuration Types: (%d)", viewConfigTypeCount) );

  for(XrViewConfigurationType viewConfigType : viewConfigTypes)
  {
    Log::Write(Log::Level::Verbose, Fmt("View Configuration Type: %s %s", to_string(viewConfigType), viewConfigType == m_OpenXrProgramStdSharedPtr_Options->Parsed.ViewConfigType ? "(Selected)" : "") );

    XrViewConfigurationProperties viewConfigProperties {XR_TYPE_VIEW_CONFIGURATION_PROPERTIES};

    if(tableXr.GetViewConfigurationProperties)
      CHECK_XRCMD(tableXr.GetViewConfigurationProperties(gXrInstance, gXrSystemId, viewConfigType, &viewConfigProperties) );

    Log::Write(Log::Level::Verbose, Fmt("View configuration FovMutable=%s", viewConfigProperties.fovMutable == XR_TRUE ? "True" : "False") );

    uint32_t viewCount = 0;

    if(tableXr.EnumerateViewConfigurationViews)
      CHECK_XRCMD(tableXr.EnumerateViewConfigurationViews(gXrInstance, gXrSystemId, viewConfigType, 0, &viewCount, nullptr) );

    if(viewCount > 0)
    {
      std::vector<XrViewConfigurationView> views(viewCount, {XR_TYPE_VIEW_CONFIGURATION_VIEW} );

      if(tableXr.EnumerateViewConfigurationViews)
        CHECK_XRCMD(tableXr.EnumerateViewConfigurationViews(gXrInstance, gXrSystemId, viewConfigType, viewCount, &viewCount, views.data() ) );

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

    OpenXrProgramLogEnvironmentBlendMode(viewConfigType);
  }
}

void OpenXrProgram::OpenXrProgramLogEnvironmentBlendMode(XrViewConfigurationType type)
{
  CHECK(gXrInstance != XR_NULL_HANDLE);
  CHECK(gXrSystemId != 0);

  uint32_t count = 0;

  if(tableXr.EnumerateEnvironmentBlendModes)
    CHECK_XRCMD(tableXr.EnumerateEnvironmentBlendModes(gXrInstance, gXrSystemId, type, 0, &count, nullptr) );

  CHECK(count > 0);

  Log::Write(Log::Level::Info, Fmt("Available Environment Blend Mode count : (%d)", count) );

  std::vector<XrEnvironmentBlendMode> blendModes(count);

  if(tableXr.EnumerateEnvironmentBlendModes)
    CHECK_XRCMD(tableXr.EnumerateEnvironmentBlendModes(gXrInstance, gXrSystemId, type, count, &count, blendModes.data() ) );

  bool blendModeFound = false;

  for(XrEnvironmentBlendMode mode : blendModes)
  {
    const bool blendModeMatch = (mode == m_OpenXrProgramStdSharedPtr_Options->Parsed.EnvironmentBlendMode);

    Log::Write(Log::Level::Info, Fmt("Environment Blend Mode (%s) : %s", to_string(mode), blendModeMatch ? "(Selected)" : "") );

    blendModeFound |= blendModeMatch;
  }

  CHECK(blendModeFound);
}

XrEnvironmentBlendMode OpenXrProgram::OpenXrProgramGetPreferredBlendMode() const
{
  uint32_t count = 0;

  if(tableXr.EnumerateEnvironmentBlendModes)
    CHECK_XRCMD(tableXr.EnumerateEnvironmentBlendModes(gXrInstance, gXrSystemId, m_OpenXrProgramStdSharedPtr_Options->Parsed.ViewConfigType, 0, &count, nullptr) );

  CHECK(count > 0);

  std::vector<XrEnvironmentBlendMode> blendModes(count);

  if(tableXr.EnumerateEnvironmentBlendModes)
    CHECK_XRCMD(tableXr.EnumerateEnvironmentBlendModes(gXrInstance, gXrSystemId, m_OpenXrProgramStdSharedPtr_Options->Parsed.ViewConfigType, count, &count, blendModes.data() ) );

  for(const auto& blendMode : blendModes)
  {
    if(m_OpenXrProgramStdSet_XrEnvironmentBlendMode.count(blendMode) )
      return blendMode;
  }

  THROW("No acceptable blend mode returned from the tableXr.EnumerateEnvironmentBlendModes");
}

void OpenXrProgram::OpenXrProgramInitializeSystem()
{
  CHECK(gXrInstance != XR_NULL_HANDLE);
  CHECK(gXrSystemId == XR_NULL_SYSTEM_ID);

  XrSystemGetInfo systemInfo {XR_TYPE_SYSTEM_GET_INFO};
  systemInfo.formFactor = m_OpenXrProgramStdSharedPtr_Options->Parsed.FormFactor;

  if(tableXr.GetSystem)
    CHECK_XRCMD(tableXr.GetSystem(gXrInstance, &systemInfo, &gXrSystemId) );

  Log::Write(Log::Level::Verbose, Fmt("Using system %d for form factor %s", gXrSystemId, to_string(m_OpenXrProgramStdSharedPtr_Options->Parsed.FormFactor) ) );
  CHECK(gXrInstance != XR_NULL_HANDLE);
  CHECK(gXrSystemId != XR_NULL_SYSTEM_ID);
}

void OpenXrProgram::OpenXrProgramInitializeDevice()
{
  OpenXrProgramLogViewConfigurations();

  VulkanGraphicsPlugin_VulkanGraphicsPluginInitializeDevice(gXrInstance, gXrSystemId);
}

void OpenXrProgram::OpenXrProgramLogReferenceSpaces()
{
  CHECK(gXrSession != XR_NULL_HANDLE);

  uint32_t spaceCount;

  if(tableXr.EnumerateReferenceSpaces)
    CHECK_XRCMD(tableXr.EnumerateReferenceSpaces(gXrSession, 0, &spaceCount, nullptr) );

  std::vector<XrReferenceSpaceType> spaces(spaceCount);

  if(tableXr.EnumerateReferenceSpaces)
    CHECK_XRCMD(tableXr.EnumerateReferenceSpaces(gXrSession, spaceCount, &spaceCount, spaces.data() ) );

  Log::Write(Log::Level::Info, Fmt("Available reference spaces: %d", spaceCount) );

  for(XrReferenceSpaceType space : spaces)
    Log::Write(Log::Level::Verbose, Fmt("  Name: %s", to_string(space) ) );
}

//struct OpenXrProgram::InputState
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
//  std::array<XrPath, (int)Side::COUNT> handSubactionPath;
//
//  std::array<XrSpace, (int)Side::COUNT> handSpace;
//
//  std::array<float, (int)Side::COUNT> handScale = { {1.0f, 1.0f} };
//
//  std::array<XrBool32, (int)Side::COUNT> handActive;
//};

void OpenXrProgram::OpenXrProgramInitializeActions()
{
  // Create an action set.
  {
    XrActionSetCreateInfo actionSetInfo {XR_TYPE_ACTION_SET_CREATE_INFO};
    strcpy_s(actionSetInfo.actionSetName, "gameplay");
    strcpy_s(actionSetInfo.localizedActionSetName, "Gameplay");
    actionSetInfo.priority = 0;

    if(tableXr.CreateActionSet)
      CHECK_XRCMD(tableXr.CreateActionSet(gXrInstance, &actionSetInfo, &m_OpenXrProgramInputState.actionSet) );
  }

  // Get the XrPath for the left and right hands - we will use them as subaction paths.

  if(tableXr.StringToPath)
    CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/user/hand/left", &m_OpenXrProgramInputState.handSubactionPath[ (int)Side::LEFT] ) );

  if(tableXr.StringToPath)
    CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/user/hand/right", &m_OpenXrProgramInputState.handSubactionPath[ (int)Side::RIGHT] ) );

  // Create actions.
  {
    // Create an input action for grabbing objects with the left and right hands.
    XrActionCreateInfo actionInfo {XR_TYPE_ACTION_CREATE_INFO};
    actionInfo.actionType = XR_ACTION_TYPE_FLOAT_INPUT;
    strcpy_s(actionInfo.actionName, "grab_object");
    strcpy_s(actionInfo.localizedActionName, "Grab Object");
    actionInfo.countSubactionPaths = uint32_t(m_OpenXrProgramInputState.handSubactionPath.size() );
    actionInfo.subactionPaths = m_OpenXrProgramInputState.handSubactionPath.data();

    if(tableXr.CreateAction)
      CHECK_XRCMD(tableXr.CreateAction(m_OpenXrProgramInputState.actionSet, &actionInfo, &m_OpenXrProgramInputState.grabAction) );

    // Create an input action getting the left and right hand poses.
    actionInfo.actionType = XR_ACTION_TYPE_POSE_INPUT;
    strcpy_s(actionInfo.actionName, "hand_pose");
    strcpy_s(actionInfo.localizedActionName, "Hand Pose");
    actionInfo.countSubactionPaths = uint32_t(m_OpenXrProgramInputState.handSubactionPath.size() );
    actionInfo.subactionPaths = m_OpenXrProgramInputState.handSubactionPath.data();

    if(tableXr.CreateAction)
      CHECK_XRCMD(tableXr.CreateAction(m_OpenXrProgramInputState.actionSet, &actionInfo, &m_OpenXrProgramInputState.poseAction) );

    // Create output actions for vibrating the left and right controller.
    actionInfo.actionType = XR_ACTION_TYPE_VIBRATION_OUTPUT;
    strcpy_s(actionInfo.actionName, "vibrate_hand");
    strcpy_s(actionInfo.localizedActionName, "Vibrate Hand");
    actionInfo.countSubactionPaths = uint32_t(m_OpenXrProgramInputState.handSubactionPath.size() );
    actionInfo.subactionPaths = m_OpenXrProgramInputState.handSubactionPath.data();

    if(tableXr.CreateAction)
      CHECK_XRCMD(tableXr.CreateAction(m_OpenXrProgramInputState.actionSet, &actionInfo, &m_OpenXrProgramInputState.vibrateAction) );

    // Create input actions for quitting the session using the left and right controller.
    // Since it doesn't matter which hand did this, we do not specify subaction paths for it.
    // We will just suggest bindings for both hands, where possible.
    actionInfo.actionType = XR_ACTION_TYPE_BOOLEAN_INPUT;
    strcpy_s(actionInfo.actionName, "quit_session");
    strcpy_s(actionInfo.localizedActionName, "Quit Session");
    actionInfo.countSubactionPaths = 0;
    actionInfo.subactionPaths = nullptr;

    if(tableXr.CreateAction)
      CHECK_XRCMD(tableXr.CreateAction(m_OpenXrProgramInputState.actionSet, &actionInfo, &m_OpenXrProgramInputState.quitAction) );
  }

  std::array<XrPath, (int)Side::COUNT> selectPath;
  std::array<XrPath, (int)Side::COUNT> squeezeValuePath;
  std::array<XrPath, (int)Side::COUNT> squeezeForcePath;
  std::array<XrPath, (int)Side::COUNT> squeezeClickPath;
  std::array<XrPath, (int)Side::COUNT> posePath;
  std::array<XrPath, (int)Side::COUNT> hapticPath;
  std::array<XrPath, (int)Side::COUNT> menuClickPath;
  std::array<XrPath, (int)Side::COUNT> bClickPath;
  std::array<XrPath, (int)Side::COUNT> triggerValuePath;

  if(tableXr.StringToPath)
  {
    CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/user/hand/left/input/select/click", &selectPath[ (int)Side::LEFT] ) );
    CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/user/hand/right/input/select/click", &selectPath[ (int)Side::RIGHT] ) );
    CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/user/hand/left/input/squeeze/value", &squeezeValuePath[ (int)Side::LEFT] ) );
    CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/user/hand/right/input/squeeze/value", &squeezeValuePath[ (int)Side::RIGHT] ) );
    CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/user/hand/left/input/squeeze/force", &squeezeForcePath[ (int)Side::LEFT] ) );
    CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/user/hand/right/input/squeeze/force", &squeezeForcePath[ (int)Side::RIGHT] ) );
    CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/user/hand/left/input/squeeze/click", &squeezeClickPath[ (int)Side::LEFT] ) );
    CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/user/hand/right/input/squeeze/click", &squeezeClickPath[ (int)Side::RIGHT] ) );
    CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/user/hand/left/input/grip/pose", &posePath[ (int)Side::LEFT] ) );
    CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/user/hand/right/input/grip/pose", &posePath[ (int)Side::RIGHT] ) );
    CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/user/hand/left/output/haptic", &hapticPath[ (int)Side::LEFT] ) );
    CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/user/hand/right/output/haptic", &hapticPath[ (int)Side::RIGHT] ) );
    CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/user/hand/left/input/menu/click", &menuClickPath[ (int)Side::LEFT] ) );
    CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/user/hand/right/input/menu/click", &menuClickPath[ (int)Side::RIGHT] ) );
    CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/user/hand/left/input/b/click", &bClickPath[ (int)Side::LEFT] ) );
    CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/user/hand/right/input/b/click", &bClickPath[ (int)Side::RIGHT] ) );
    CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/user/hand/left/input/trigger/value", &triggerValuePath[ (int)Side::LEFT] ) );
    CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/user/hand/right/input/trigger/value", &triggerValuePath[ (int)Side::RIGHT] ) );
  }

  // Suggest bindings for KHR Simple.
  {
    XrPath khrSimpleInteractionProfilePath;

    if(tableXr.StringToPath)
      CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/interaction_profiles/khr/simple_controller", &khrSimpleInteractionProfilePath) );

    std::vector<XrActionSuggestedBinding> bindings { {// Fall back to a click input for the grab action.
                                                    {m_OpenXrProgramInputState.grabAction, selectPath[ (int)Side::LEFT]},
                                                    {m_OpenXrProgramInputState.grabAction, selectPath[ (int)Side::RIGHT]},
                                                    {m_OpenXrProgramInputState.poseAction, posePath[ (int)Side::LEFT]},
                                                    {m_OpenXrProgramInputState.poseAction, posePath[ (int)Side::RIGHT]},
                                                    {m_OpenXrProgramInputState.quitAction, menuClickPath[ (int)Side::LEFT]},
                                                    {m_OpenXrProgramInputState.quitAction, menuClickPath[ (int)Side::RIGHT]},
                                                    {m_OpenXrProgramInputState.vibrateAction, hapticPath[ (int)Side::LEFT]},
                                                    {m_OpenXrProgramInputState.vibrateAction, hapticPath[ (int)Side::RIGHT]} } };

    XrInteractionProfileSuggestedBinding suggestedBindings {XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING};

    suggestedBindings.interactionProfile = khrSimpleInteractionProfilePath;
    suggestedBindings.suggestedBindings = bindings.data();
    suggestedBindings.countSuggestedBindings = (uint32_t)bindings.size();

    if(tableXr.SuggestInteractionProfileBindings)
      CHECK_XRCMD(tableXr.SuggestInteractionProfileBindings(gXrInstance, &suggestedBindings) );
  }

  // Suggest bindings for the Oculus Touch.
  {
    XrPath oculusTouchInteractionProfilePath;

    if(tableXr.StringToPath)
      CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/interaction_profiles/oculus/touch_controller", &oculusTouchInteractionProfilePath) );

    std::vector<XrActionSuggestedBinding> bindings { { {m_OpenXrProgramInputState.grabAction, squeezeValuePath[ (int)Side::LEFT]},
                                                    {m_OpenXrProgramInputState.grabAction, squeezeValuePath[ (int)Side::RIGHT]},
                                                    {m_OpenXrProgramInputState.poseAction, posePath[ (int)Side::LEFT]},
                                                    {m_OpenXrProgramInputState.poseAction, posePath[ (int)Side::RIGHT]},
                                                    {m_OpenXrProgramInputState.quitAction, menuClickPath[ (int)Side::LEFT]},
                                                    {m_OpenXrProgramInputState.vibrateAction, hapticPath[ (int)Side::LEFT]},
                                                    {m_OpenXrProgramInputState.vibrateAction, hapticPath[ (int)Side::RIGHT]} } };

    XrInteractionProfileSuggestedBinding suggestedBindings {XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING};

    suggestedBindings.interactionProfile = oculusTouchInteractionProfilePath;
    suggestedBindings.suggestedBindings = bindings.data();
    suggestedBindings.countSuggestedBindings = (uint32_t)bindings.size();

    if(tableXr.SuggestInteractionProfileBindings)
      CHECK_XRCMD(tableXr.SuggestInteractionProfileBindings(gXrInstance, &suggestedBindings) );
  }

  // Suggest bindings for the Vive Controller.
  {
    XrPath viveControllerInteractionProfilePath;

    if(tableXr.StringToPath)
      CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/interaction_profiles/htc/vive_controller", &viveControllerInteractionProfilePath) );

    std::vector<XrActionSuggestedBinding> bindings { { {m_OpenXrProgramInputState.grabAction, triggerValuePath[ (int)Side::LEFT]},
                                                    {m_OpenXrProgramInputState.grabAction, triggerValuePath[ (int)Side::RIGHT]},
                                                    {m_OpenXrProgramInputState.poseAction, posePath[ (int)Side::LEFT]},
                                                    {m_OpenXrProgramInputState.poseAction, posePath[ (int)Side::RIGHT]},
                                                    {m_OpenXrProgramInputState.quitAction, menuClickPath[ (int)Side::LEFT]},
                                                    {m_OpenXrProgramInputState.quitAction, menuClickPath[ (int)Side::RIGHT]},
                                                    {m_OpenXrProgramInputState.vibrateAction, hapticPath[ (int)Side::LEFT]},
                                                    {m_OpenXrProgramInputState.vibrateAction, hapticPath[ (int)Side::RIGHT]} } };

    XrInteractionProfileSuggestedBinding suggestedBindings {XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING};

    suggestedBindings.interactionProfile = viveControllerInteractionProfilePath;
    suggestedBindings.suggestedBindings = bindings.data();
    suggestedBindings.countSuggestedBindings = (uint32_t)bindings.size();

    if(tableXr.SuggestInteractionProfileBindings)
      CHECK_XRCMD(tableXr.SuggestInteractionProfileBindings(gXrInstance, &suggestedBindings) );
  }

  // Suggest bindings for the Valve Index Controller.
  {
    XrPath indexControllerInteractionProfilePath;

    if(tableXr.StringToPath)
      CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/interaction_profiles/valve/index_controller", &indexControllerInteractionProfilePath) );

    std::vector<XrActionSuggestedBinding> bindings { { {m_OpenXrProgramInputState.grabAction, squeezeForcePath[ (int)Side::LEFT]},
                                                    {m_OpenXrProgramInputState.grabAction, squeezeForcePath[ (int)Side::RIGHT]},
                                                    {m_OpenXrProgramInputState.poseAction, posePath[ (int)Side::LEFT]},
                                                    {m_OpenXrProgramInputState.poseAction, posePath[ (int)Side::RIGHT]},
                                                    {m_OpenXrProgramInputState.quitAction, bClickPath[ (int)Side::LEFT]},
                                                    {m_OpenXrProgramInputState.quitAction, bClickPath[ (int)Side::RIGHT]},
                                                    {m_OpenXrProgramInputState.vibrateAction, hapticPath[ (int)Side::LEFT]},
                                                    {m_OpenXrProgramInputState.vibrateAction, hapticPath[ (int)Side::RIGHT]} } };

    XrInteractionProfileSuggestedBinding suggestedBindings {XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING};

    suggestedBindings.interactionProfile = indexControllerInteractionProfilePath;
    suggestedBindings.suggestedBindings = bindings.data();
    suggestedBindings.countSuggestedBindings = (uint32_t)bindings.size();

    if(tableXr.SuggestInteractionProfileBindings)
      CHECK_XRCMD(tableXr.SuggestInteractionProfileBindings(gXrInstance, &suggestedBindings) );
  }

  // Suggest bindings for the Microsoft Mixed Reality Motion Controller.
  {
    XrPath microsoftMixedRealityInteractionProfilePath;

    if(tableXr.StringToPath)
      CHECK_XRCMD(tableXr.StringToPath(gXrInstance, "/interaction_profiles/microsoft/motion_controller", &microsoftMixedRealityInteractionProfilePath) );

    std::vector<XrActionSuggestedBinding> bindings { { {m_OpenXrProgramInputState.grabAction, squeezeClickPath[ (int)Side::LEFT]},
                                                    {m_OpenXrProgramInputState.grabAction, squeezeClickPath[ (int)Side::RIGHT]},
                                                    {m_OpenXrProgramInputState.poseAction, posePath[ (int)Side::LEFT]},
                                                    {m_OpenXrProgramInputState.poseAction, posePath[ (int)Side::RIGHT]},
                                                    {m_OpenXrProgramInputState.quitAction, menuClickPath[ (int)Side::LEFT]},
                                                    {m_OpenXrProgramInputState.quitAction, menuClickPath[ (int)Side::RIGHT]},
                                                    {m_OpenXrProgramInputState.vibrateAction, hapticPath[ (int)Side::LEFT]},
                                                    {m_OpenXrProgramInputState.vibrateAction, hapticPath[ (int)Side::RIGHT]} } };

    XrInteractionProfileSuggestedBinding suggestedBindings {XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING};

    suggestedBindings.interactionProfile = microsoftMixedRealityInteractionProfilePath;
    suggestedBindings.suggestedBindings = bindings.data();
    suggestedBindings.countSuggestedBindings = (uint32_t)bindings.size();

    if(tableXr.SuggestInteractionProfileBindings)
      CHECK_XRCMD(tableXr.SuggestInteractionProfileBindings(gXrInstance, &suggestedBindings) );
  }

  XrActionSpaceCreateInfo actionSpaceInfo {XR_TYPE_ACTION_SPACE_CREATE_INFO};

  actionSpaceInfo.action = m_OpenXrProgramInputState.poseAction;
  actionSpaceInfo.poseInActionSpace.orientation.w = 1.f;
  actionSpaceInfo.subactionPath = m_OpenXrProgramInputState.handSubactionPath[ (int)Side::LEFT];

  if(tableXr.CreateActionSpace)
    CHECK_XRCMD(tableXr.CreateActionSpace(gXrSession, &actionSpaceInfo, &m_OpenXrProgramInputState.handSpace[ (int)Side::LEFT] ) );

  actionSpaceInfo.subactionPath = m_OpenXrProgramInputState.handSubactionPath[ (int)Side::RIGHT];

  if(tableXr.CreateActionSpace)
    CHECK_XRCMD(tableXr.CreateActionSpace(gXrSession, &actionSpaceInfo, &m_OpenXrProgramInputState.handSpace[ (int)Side::RIGHT] ) );

  XrSessionActionSetsAttachInfo attachInfo {XR_TYPE_SESSION_ACTION_SETS_ATTACH_INFO};
  attachInfo.countActionSets = 1;
  attachInfo.actionSets = &m_OpenXrProgramInputState.actionSet;

  if(tableXr.AttachSessionActionSets)
    CHECK_XRCMD(tableXr.AttachSessionActionSets(gXrSession, &attachInfo) );
}

void OpenXrProgram::OpenXrProgramCreateVisualizedSpaces()
{
  CHECK(gXrSession != XR_NULL_HANDLE);

  std::string visualizedSpaces[] = {"ViewFront", "Local", "Stage", "StageLeft", "StageRight", "StageLeftRotated", "StageRightRotated"};

  for(const auto& visualizedSpace : visualizedSpaces)
  {
    XrReferenceSpaceCreateInfo referenceSpaceCreateInfo = GetXrReferenceSpaceCreateInfo(visualizedSpace);

    XrSpace space;

    XrResult res = XR_ERROR_VALIDATION_FAILURE;

    if(tableXr.CreateReferenceSpace)
      res = tableXr.CreateReferenceSpace(gXrSession, &referenceSpaceCreateInfo, &space);

    if(XR_SUCCEEDED(res) )
      m_OpenXrProgramStdVector_XrSpace.push_back(space);
    else
      Log::Write(Log::Level::Warning, Fmt("Failed to create reference space %s with error %d", visualizedSpace.c_str(), res) );
  }
}

void OpenXrProgram::OpenXrProgramInitializeSession()
{
  CHECK(gXrInstance != XR_NULL_HANDLE);
  CHECK(gXrSession == XR_NULL_HANDLE);

  {
    Log::Write(Log::Level::Verbose, Fmt("Creating session...") );

    XrSessionCreateInfo createInfo {XR_TYPE_SESSION_CREATE_INFO};

    createInfo.next = VulkanGraphicsPlugin_VulkanGraphicsPluginGetGraphicsBinding();
    createInfo.systemId = gXrSystemId;

    if(tableXr.CreateSession)
      CHECK_XRCMD(tableXr.CreateSession(gXrInstance, &createInfo, &gXrSession) );
  }

  OpenXrProgramLogReferenceSpaces();
  OpenXrProgramInitializeActions();
  OpenXrProgramCreateVisualizedSpaces();

  {
    XrReferenceSpaceCreateInfo referenceSpaceCreateInfo = GetXrReferenceSpaceCreateInfo(m_OpenXrProgramStdSharedPtr_Options->AppSpace);

    if(tableXr.CreateReferenceSpace)
      CHECK_XRCMD(tableXr.CreateReferenceSpace(gXrSession, &referenceSpaceCreateInfo, &m_OpenXrProgramXrSpace) );
  }
}

void OpenXrProgram::OpenXrProgramCreateSwapchains()
{
  CHECK(gXrSession != XR_NULL_HANDLE);
  CHECK(m_OpenXrProgramStdVector_Swapchain.empty() );
  CHECK(m_OpenXrProgramStdVector_XrViewConfigurationView.empty() );

  // Read graphics properties for preferred swapchain length and logging.
  XrSystemProperties systemProperties {XR_TYPE_SYSTEM_PROPERTIES};

  if(tableXr.GetSystemProperties)
    CHECK_XRCMD(tableXr.GetSystemProperties(gXrInstance, gXrSystemId, &systemProperties) );

  // Log system properties.
  Log::Write(Log::Level::Info, Fmt("System Properties: Name=%s VendorId=%d", systemProperties.systemName, systemProperties.vendorId) );

  Log::Write(Log::Level::Info, Fmt("System Graphics Properties: MaxWidth=%d MaxHeight=%d MaxLayers=%d", systemProperties.graphicsProperties.maxSwapchainImageWidth, systemProperties.graphicsProperties.maxSwapchainImageHeight, systemProperties.graphicsProperties.maxLayerCount) );

  Log::Write(Log::Level::Info, Fmt("System Tracking Properties: OrientationTracking=%s PositionTracking=%s", systemProperties.trackingProperties.orientationTracking == XR_TRUE ? "True" : "False", systemProperties.trackingProperties.positionTracking == XR_TRUE ? "True" : "False") );

  // Note: No other view configurations exist at the time this code was written. If this
  // condition is not met, the project will need to be audited to see how support should be
  // added.
  CHECK_MSG(m_OpenXrProgramStdSharedPtr_Options->Parsed.ViewConfigType == XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, "Unsupported view configuration type");

  // Query and cache view configuration views.
  uint32_t viewCount;

  if(tableXr.EnumerateViewConfigurationViews)
    CHECK_XRCMD(tableXr.EnumerateViewConfigurationViews(gXrInstance, gXrSystemId, m_OpenXrProgramStdSharedPtr_Options->Parsed.ViewConfigType, 0, &viewCount, nullptr) );

  m_OpenXrProgramStdVector_XrViewConfigurationView.resize(viewCount, {XR_TYPE_VIEW_CONFIGURATION_VIEW} );

  if(tableXr.EnumerateViewConfigurationViews)
    CHECK_XRCMD(tableXr.EnumerateViewConfigurationViews(gXrInstance, gXrSystemId, m_OpenXrProgramStdSharedPtr_Options->Parsed.ViewConfigType, viewCount, &viewCount, m_OpenXrProgramStdVector_XrViewConfigurationView.data() ) );

  // Create and cache view buffer for xrLocateViews later
  m_OpenXrProgramStdVector_XrView.resize(viewCount, {XR_TYPE_VIEW} );

  // Create the swapchain and get the images.
  if(viewCount > 0)
  {
    // Select a swapchain format.
    uint32_t swapchainFormatCount = 0;

    if(tableXr.EnumerateSwapchainFormats)
      CHECK_XRCMD(tableXr.EnumerateSwapchainFormats(gXrSession, 0, &swapchainFormatCount, nullptr) );

    std::vector<int64_t> swapchainFormats(swapchainFormatCount);

    if(tableXr.EnumerateSwapchainFormats)
      CHECK_XRCMD(tableXr.EnumerateSwapchainFormats(gXrSession, (uint32_t)swapchainFormats.size(), &swapchainFormatCount, swapchainFormats.data() ) );

    CHECK(swapchainFormatCount == swapchainFormats.size() );
    m_OpenXrProgramColorSwapchainFormat = VulkanGraphicsPlugin_VulkanGraphicsPluginSelectColorSwapchainFormat(swapchainFormats);

    // Print swapchain formats and the selected one
    {
      std::string swapchainFormatsString;

      for(int64_t format : swapchainFormats)
      {
        const bool selected = format == m_OpenXrProgramColorSwapchainFormat;

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
      const XrViewConfigurationView& vp = m_OpenXrProgramStdVector_XrViewConfigurationView[i];

      Log::Write(Log::Level::Info, Fmt("Creating swapchain for view %d with dimensions Width=%d Height=%d SampleCount=%d", i, vp.recommendedImageRectWidth, vp.recommendedImageRectHeight, vp.recommendedSwapchainSampleCount) );

      // Create the swapchain.
      XrSwapchainCreateInfo swapchainCreateInfo {XR_TYPE_SWAPCHAIN_CREATE_INFO};
      swapchainCreateInfo.arraySize = 1;
      swapchainCreateInfo.format = m_OpenXrProgramColorSwapchainFormat;
      swapchainCreateInfo.width = vp.recommendedImageRectWidth;
      swapchainCreateInfo.height = vp.recommendedImageRectHeight;
      swapchainCreateInfo.mipCount = 1;
      swapchainCreateInfo.faceCount = 1;
      swapchainCreateInfo.sampleCount = VulkanGraphicsPlugin_VulkanGraphicsPluginGetSupportedSwapchainSampleCount(vp);
      swapchainCreateInfo.usageFlags = XR_SWAPCHAIN_USAGE_SAMPLED_BIT | XR_SWAPCHAIN_USAGE_COLOR_ATTACHMENT_BIT;
      Swapchain swapchain;
      swapchain.width = swapchainCreateInfo.width;
      swapchain.height = swapchainCreateInfo.height;

      if(tableXr.CreateSwapchain)
        CHECK_XRCMD(tableXr.CreateSwapchain(gXrSession, &swapchainCreateInfo, &swapchain.handle) );

      m_OpenXrProgramStdVector_Swapchain.push_back(swapchain);

      uint32_t imageCount = 0;

      if(tableXr.EnumerateSwapchainImages)
        CHECK_XRCMD(tableXr.EnumerateSwapchainImages(swapchain.handle, 0, &imageCount, nullptr) );

      // XXX This should really just return XrSwapchainImageBaseHeader*
      std::vector<XrSwapchainImageBaseHeader*> swapchainImages = VulkanGraphicsPlugin_VulkanGraphicsPluginAllocateSwapchainImageStructs(imageCount, swapchainCreateInfo);

      if(tableXr.EnumerateSwapchainImages)
        CHECK_XRCMD(tableXr.EnumerateSwapchainImages(swapchain.handle, imageCount, &imageCount, swapchainImages[0] ) );

      m_OpenXrProgramStdMap_XrSwapchain_StdVectorXrSwapchainImageBaseHeader.insert(std::make_pair(swapchain.handle, std::move(swapchainImages) ) );
    }
  }
}

const XrEventDataBaseHeader* OpenXrProgram::OpenXrProgramTryReadNextEvent()
{
  XrEventDataBaseHeader* baseHeader = reinterpret_cast<XrEventDataBaseHeader*>(&m_OpenXrProgramXrEventDataBuffer);
  *baseHeader = {XR_TYPE_EVENT_DATA_BUFFER};

  XrResult xr = XR_ERROR_VALIDATION_FAILURE;

  if(tableXr.PollEvent)
    xr = tableXr.PollEvent(gXrInstance, &m_OpenXrProgramXrEventDataBuffer);

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

void OpenXrProgram::OpenXrProgramPollEvents(bool* exitRenderLoop, bool* requestRestart)
{
  *exitRenderLoop = *requestRestart = false;

  while(const XrEventDataBaseHeader* event = OpenXrProgramTryReadNextEvent() )
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
      OpenXrProgramHandleSessionStateChangedEvent(sessionStateChangedEvent, exitRenderLoop, requestRestart);
      break;
    }

    case XR_TYPE_EVENT_DATA_INTERACTION_PROFILE_CHANGED:
    {
      OpenXrProgramLogActionSourceName(m_OpenXrProgramInputState.grabAction, "Grab");
      OpenXrProgramLogActionSourceName(m_OpenXrProgramInputState.quitAction, "Quit");
      OpenXrProgramLogActionSourceName(m_OpenXrProgramInputState.poseAction, "Pose");
      OpenXrProgramLogActionSourceName(m_OpenXrProgramInputState.vibrateAction, "Vibrate");
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

void OpenXrProgram::OpenXrProgramHandleSessionStateChangedEvent(const XrEventDataSessionStateChanged& stateChangedEvent, bool* exitRenderLoop, bool* requestRestart)
{
  const XrSessionState oldState = m_OpenXrProgramXrSessionState;
  m_OpenXrProgramXrSessionState = stateChangedEvent.state;

  Log::Write(Log::Level::Info, Fmt("XrEventDataSessionStateChanged: state %s->%s session=%lld time=%lld", to_string(oldState), to_string(m_OpenXrProgramXrSessionState), stateChangedEvent.session, stateChangedEvent.time) );

  if(stateChangedEvent.session != XR_NULL_HANDLE && stateChangedEvent.session != gXrSession)
  {
    Log::Write(Log::Level::Error, "XrEventDataSessionStateChanged for unknown session");
    return;
  }

  switch(m_OpenXrProgramXrSessionState)
  {

  case XR_SESSION_STATE_READY:
  {
    CHECK(gXrSession != XR_NULL_HANDLE);

    XrSessionBeginInfo sessionBeginInfo {XR_TYPE_SESSION_BEGIN_INFO};

    sessionBeginInfo.primaryViewConfigurationType = m_OpenXrProgramStdSharedPtr_Options->Parsed.ViewConfigType;

    if(tableXr.BeginSession)
      CHECK_XRCMD(tableXr.BeginSession(gXrSession, &sessionBeginInfo) );

    m_OpenXrProgramSessionRunning = true;
    break;
  }

  case XR_SESSION_STATE_STOPPING:
  {
    CHECK(gXrSession != XR_NULL_HANDLE);
    m_OpenXrProgramSessionRunning = false;

    if(tableXr.EndSession)
      CHECK_XRCMD(tableXr.EndSession(gXrSession) );

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

void OpenXrProgram::OpenXrProgramLogActionSourceName(XrAction action, const std::string& actionName) const
{
  XrBoundSourcesForActionEnumerateInfo getInfo = {XR_TYPE_BOUND_SOURCES_FOR_ACTION_ENUMERATE_INFO};

  getInfo.action = action;

  uint32_t pathCount = 0;

  if(tableXr.EnumerateBoundSourcesForAction)
    CHECK_XRCMD(tableXr.EnumerateBoundSourcesForAction(gXrSession, &getInfo, 0, &pathCount, nullptr) );

  std::vector<XrPath> paths(pathCount);

  if(tableXr.EnumerateBoundSourcesForAction)
    CHECK_XRCMD(tableXr.EnumerateBoundSourcesForAction(gXrSession, &getInfo, uint32_t(paths.size() ), &pathCount, paths.data() ) );

  std::string sourceName;

  for(uint32_t i = 0; i < pathCount; ++i)
  {
    constexpr XrInputSourceLocalizedNameFlags all = XR_INPUT_SOURCE_LOCALIZED_NAME_USER_PATH_BIT | XR_INPUT_SOURCE_LOCALIZED_NAME_INTERACTION_PROFILE_BIT | XR_INPUT_SOURCE_LOCALIZED_NAME_COMPONENT_BIT;

    XrInputSourceLocalizedNameGetInfo nameInfo = {XR_TYPE_INPUT_SOURCE_LOCALIZED_NAME_GET_INFO};

    nameInfo.sourcePath = paths[i];
    nameInfo.whichComponents = all;

    uint32_t size = 0;

    if(tableXr.GetInputSourceLocalizedName)
      CHECK_XRCMD(tableXr.GetInputSourceLocalizedName(gXrSession, &nameInfo, 0, &size, nullptr) );

    if(size < 1)
      continue;

    std::vector<char> grabSource(size);

    if(tableXr.GetInputSourceLocalizedName)
      CHECK_XRCMD(tableXr.GetInputSourceLocalizedName(gXrSession, &nameInfo, uint32_t(grabSource.size() ), &size, grabSource.data() ) );

    if(!sourceName.empty() )
      sourceName += " and ";

    sourceName += "'";
    sourceName += std::string(grabSource.data(), size - 1);

    sourceName += "'";
  }

  Log::Write(Log::Level::Info, Fmt("%s action is bound to %s", actionName.c_str(), ( (!sourceName.empty() ) ? sourceName.c_str() : "nothing") ) );
}

bool OpenXrProgram::OpenXrProgramIsSessionRunning() const
{
  return m_OpenXrProgramSessionRunning;
}

bool OpenXrProgram::OpenXrProgramIsSessionFocused() const
{
  return m_OpenXrProgramXrSessionState == XR_SESSION_STATE_FOCUSED;
}

void OpenXrProgram::OpenXrProgramPollActions()
{
  m_OpenXrProgramInputState.handActive = {XR_FALSE, XR_FALSE};

  // Sync actions
  const XrActiveActionSet activeActionSet {m_OpenXrProgramInputState.actionSet, XR_NULL_PATH};

  XrActionsSyncInfo syncInfo {XR_TYPE_ACTIONS_SYNC_INFO};
  syncInfo.countActiveActionSets = 1;
  syncInfo.activeActionSets = &activeActionSet;

  if(tableXr.SyncActions)
    CHECK_XRCMD(tableXr.SyncActions(gXrSession, &syncInfo) );

  // Get pose and grab action state and start haptic vibrate when hand is 90% squeezed.
  for(auto hand : {(int)Side::LEFT, (int)Side::RIGHT} )
  {
    XrActionStateGetInfo getInfo {XR_TYPE_ACTION_STATE_GET_INFO};

    getInfo.action = m_OpenXrProgramInputState.grabAction;
    getInfo.subactionPath = m_OpenXrProgramInputState.handSubactionPath[hand];

    XrActionStateFloat grabValue {XR_TYPE_ACTION_STATE_FLOAT};

    if(tableXr.GetActionStateFloat)
      CHECK_XRCMD(tableXr.GetActionStateFloat(gXrSession, &getInfo, &grabValue) );

    if(grabValue.isActive == XR_TRUE)
    {
      // Scale the rendered hand by 1.0f (open) to 0.5f (fully squeezed).
      m_OpenXrProgramInputState.handScale[hand] = 1.0f - 0.5f * grabValue.currentState;

      if(grabValue.currentState > 0.9f)
      {
        XrHapticVibration vibration {XR_TYPE_HAPTIC_VIBRATION};
        vibration.amplitude = 0.5;
        vibration.duration = XR_MIN_HAPTIC_DURATION;
        vibration.frequency = XR_FREQUENCY_UNSPECIFIED;

        XrHapticActionInfo hapticActionInfo {XR_TYPE_HAPTIC_ACTION_INFO};
        hapticActionInfo.action = m_OpenXrProgramInputState.vibrateAction;
        hapticActionInfo.subactionPath = m_OpenXrProgramInputState.handSubactionPath[hand];

        if(tableXr.ApplyHapticFeedback)
          CHECK_XRCMD(tableXr.ApplyHapticFeedback(gXrSession, &hapticActionInfo, (XrHapticBaseHeader*) &vibration) );
      }
    }

    getInfo.action = m_OpenXrProgramInputState.poseAction;

    XrActionStatePose poseState {XR_TYPE_ACTION_STATE_POSE};

    if(tableXr.GetActionStatePose)
      CHECK_XRCMD(tableXr.GetActionStatePose(gXrSession, &getInfo, &poseState) );

    m_OpenXrProgramInputState.handActive[hand] = poseState.isActive;
  }

  // There were no subaction paths specified for the quit action, because we don't care which hand did it.
  XrActionStateGetInfo getInfo {XR_TYPE_ACTION_STATE_GET_INFO, nullptr, m_OpenXrProgramInputState.quitAction, XR_NULL_PATH};
  XrActionStateBoolean quitValue {XR_TYPE_ACTION_STATE_BOOLEAN};

  if(tableXr.GetActionStateBoolean)
    CHECK_XRCMD(tableXr.GetActionStateBoolean(gXrSession, &getInfo, &quitValue) );

  if(quitValue.isActive == XR_TRUE && quitValue.changedSinceLastSync == XR_TRUE && quitValue.currentState == XR_TRUE && tableXr.RequestExitSession)
    CHECK_XRCMD(tableXr.RequestExitSession(gXrSession) );
}

// Unreal UOculusXRFunctionLibrary::SetSuggestedCpuAndGpuPerformanceLevels (exposed in Blueprint)
//
// Unity OVRPlugin::suggestedCpuPerfLevel, OVRPlugin::suggestedGpuPerfLevel
//
// Native ovrp_SetSuggestedCpuPerformanceLevel, ovrp_GetSuggestedGpuPerformanceLevel

void OpenXrProgram::OpenXrProgramRenderFrame()
{
  CHECK(gXrSession != XR_NULL_HANDLE);

  XrFrameWaitInfo frameWaitInfo {XR_TYPE_FRAME_WAIT_INFO};
  XrFrameState frameState {XR_TYPE_FRAME_STATE};

  if(tableXr.WaitFrame)
    CHECK_XRCMD(tableXr.WaitFrame(gXrSession, &frameWaitInfo, &frameState) );

  XrFrameBeginInfo frameBeginInfo {XR_TYPE_FRAME_BEGIN_INFO};

  if(tableXr.BeginFrame)
    CHECK_XRCMD(tableXr.BeginFrame(gXrSession, &frameBeginInfo) );

  if(gPassthroughFeature == XR_NULL_HANDLE)
  {
    std::vector<XrCompositionLayerBaseHeader*> layers;
    XrCompositionLayerProjection layer {XR_TYPE_COMPOSITION_LAYER_PROJECTION};
    std::vector<XrCompositionLayerProjectionView> projectionLayerViews;

    if(frameState.shouldRender == XR_TRUE)
    {
      if(OpenXrProgramRenderLayer(frameState.predictedDisplayTime, projectionLayerViews, layer) )
        layers.push_back(reinterpret_cast<XrCompositionLayerBaseHeader*>(&layer) );
    }

    XrFrameEndInfo frameEndInfo {XR_TYPE_FRAME_END_INFO};
    frameEndInfo.displayTime = frameState.predictedDisplayTime;
    frameEndInfo.environmentBlendMode = m_OpenXrProgramStdSharedPtr_Options->Parsed.EnvironmentBlendMode;
    frameEndInfo.layerCount = (uint32_t)layers.size();
    frameEndInfo.layers = layers.data();

    if(tableXr.EndFrame)
      CHECK_XRCMD(tableXr.EndFrame(gXrSession, &frameEndInfo) );
  }
  else
  {
    XrCompositionLayerProjection layer {XR_TYPE_COMPOSITION_LAYER_PROJECTION};
    std::vector<XrCompositionLayerProjectionView> projectionLayerViews;

    if(frameState.shouldRender == XR_TRUE)
      OpenXrProgramRenderLayer(frameState.predictedDisplayTime, projectionLayerViews, layer);

    XrCompositionLayerPassthroughFB passthroughCompLayer = {XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_FB};
    passthroughCompLayer.layerHandle = gPassthroughLayer;
    passthroughCompLayer.flags = XR_COMPOSITION_LAYER_BLEND_TEXTURE_SOURCE_ALPHA_BIT;
    passthroughCompLayer.space = XR_NULL_HANDLE;

    layer.layerFlags = XR_COMPOSITION_LAYER_BLEND_TEXTURE_SOURCE_ALPHA_BIT;

    const int kLayerCount = 2;
    const XrCompositionLayerBaseHeader* layers[kLayerCount] = {
      (const XrCompositionLayerBaseHeader*)&passthroughCompLayer,
      (const XrCompositionLayerBaseHeader*)&layer/*applicationCompLayer*/
    };

    XrFrameEndInfo frameEndInfo = {XR_TYPE_FRAME_END_INFO};
    frameEndInfo.displayTime = frameState.predictedDisplayTime;
    frameEndInfo.environmentBlendMode = XR_ENVIRONMENT_BLEND_MODE_OPAQUE;
    frameEndInfo.layerCount = kLayerCount;
    frameEndInfo.layers = layers;

    if(tableXr.EndFrame)
      CHECK_XRCMD(tableXr.EndFrame(gXrSession, &frameEndInfo) );
  }

  //XR_COMPOSITION_LAYER_BLEND_TEXTURE_SOURCE_ALPHA_BIT | XR_COMPOSITION_LAYER_UNPREMULTIPLIED_ALPHA_BIT

  if( !gCreatePassthroughFB)
  {
    XrResult result = tableXr.GetInstanceProcAddr(gXrInstance, "xrCreatePassthroughFB", (PFN_xrVoidFunction*) &gCreatePassthroughFB);

    if(XR_FAILED(result) )
      Log::Write(Log::Level::Info, Fmt("failed to obtain the function pointer for xrCreatePassthroughFB") );
    else
      Log::Write(Log::Level::Info, Fmt("obtained the function pointer for xrCreatePassthroughFB") );

    XrPassthroughCreateInfoFB passthroughCreateInfo = {XR_TYPE_PASSTHROUGH_CREATE_INFO_FB};
    passthroughCreateInfo.flags = XR_PASSTHROUGH_IS_RUNNING_AT_CREATION_BIT_FB;

    result = gCreatePassthroughFB(gXrSession, &passthroughCreateInfo, &gPassthroughFeature);
    if(XR_FAILED(result) )
      Log::Write(Log::Level::Info, Fmt("failed to create the passthrough feature") );
    else
      Log::Write(Log::Level::Info, Fmt("created the passthrough feature") );

    // Create and run passthrough layer

    result = tableXr.GetInstanceProcAddr(gXrInstance, "xrCreatePassthroughLayerFB", (PFN_xrVoidFunction*) &gCreatePassthroughLayerFB);

    XrPassthroughLayerCreateInfoFB layerCreateInfo = {XR_TYPE_PASSTHROUGH_LAYER_CREATE_INFO_FB};
    layerCreateInfo.passthrough = gPassthroughFeature;
    layerCreateInfo.purpose = XR_PASSTHROUGH_LAYER_PURPOSE_RECONSTRUCTION_FB;
    layerCreateInfo.flags = XR_PASSTHROUGH_IS_RUNNING_AT_CREATION_BIT_FB;

    result = gCreatePassthroughLayerFB(gXrSession, &layerCreateInfo, &gPassthroughLayer);
    if(XR_FAILED(result) )
      Log::Write(Log::Level::Info, Fmt("failed to create and start a passthrough layer") );
    else
      Log::Write(Log::Level::Info, Fmt("created and started a passthrough layer") );
  }

  if( !gCreateEnvironmentDepthProviderMETA)
  {
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // OpenXR Depth API Overview

    // Health and Safety Recommendation: While building mixed reality experiences, we highly recommend that you
    // evaluate your content to offer your users a comfortable and safe experience. Please refer to the Health and
    // Safety and Design guidelines before designing and developing your app using Depth.

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Overview

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // What is Depth API?

    // The Depth API provides real-time depth maps that apps can use to sense the environment. Primarily, it enhances
    // mixed reality (MR) by allowing virtual objects to be occluded by real-world objects and surfaces, which makes
    // them appear integrated into the actual environment. Occlusion is crucial because it prevents virtual content
    // from appearing as a layer over the real world, which can disrupt immersion.

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Why use Depth API?

    // The Scene Model enables the creation of room-scale, mixed reality experiences featuring realistic occlusion.
    // However, it cannot handle occlusion for objects that are dynamically moving within the user’s view, such as
    // hands, limbs, other people, and pets. To achieve realistic occlusion with these dynamic elements, you must also
    // use the Depth API.

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Requesting user permission

    // An app that wants to use Depth API needs to request and be granted spatial data permission
    // (com.oculus.permission.USE_SCENE) before accessing any of the functions in the XR_META_environment_depth
    // extension. See the Spatial Data Permission guide for how to set up the app and how to request this permission.

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Enabling the extension

    // The Depth API is defined in the XR_META_environment_depth OpenXR extension. All extensions should be explicitly
    // listed when creating an XrInstance. Include XR_META_ENVIRONMENT_DEPTH_EXTENSION_NAME in this list to enable the
    // Depth API extension:

    // std::vector<const char*> extensions = {XR_META_ENVIRONMENT_DEPTH_EXTENSION_NAME};
    //
    // XrInstanceCreateInfo instanceCreateInfo = {XR_TYPE_INSTANCE_CREATE_INFO};
    // instanceCreateInfo.enabledExtensionCount = extensions.size();
    // instanceCreateInfo.enabledExtensionNames = extensions.data();
    //
    // XrInstance instance = XR_NULL_HANDLE;
    // xrCreateInstance(&instanceCreateInfo, &instance);

    // For more details, see SampleXrFramework/Src/XrApp.cpp.

    // Note that this feature is not supported by all runtimes and devices so the app must first call
    // xrGetSystemProperties to query for a XrSystemEnvironmentDepthPropertiesMETA struct and check that
    // supportsEnvironmentDepth is true.

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Getting the extension function pointers

    // You must retrieve pointers to all the functions in the extension before calling them. For more details, see
    // xrGetInstanceProcAddr in the OpenXR spec.

    // The following snippet initializes all the available functions:

    tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateEnvironmentDepthProviderMETA", (PFN_xrVoidFunction*) &gCreateEnvironmentDepthProviderMETA);
    tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyEnvironmentDepthProviderMETA", (PFN_xrVoidFunction*) &gDestroyEnvironmentDepthProviderMETA);
    tableXr.GetInstanceProcAddr(gXrInstance, "xrStartEnvironmentDepthProviderMETA", (PFN_xrVoidFunction*) &gStartEnvironmentDepthProviderMETA);
    tableXr.GetInstanceProcAddr(gXrInstance, "xrStopEnvironmentDepthProviderMETA", (PFN_xrVoidFunction*) &gStopEnvironmentDepthProviderMETA);
    tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateEnvironmentDepthSwapchainMETA", (PFN_xrVoidFunction*) &gCreateEnvironmentDepthSwapchainMETA);
    tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyEnvironmentDepthSwapchainMETA", (PFN_xrVoidFunction*) &gDestroyEnvironmentDepthSwapchainMETA);
    tableXr.GetInstanceProcAddr(gXrInstance, "xrEnumerateEnvironmentDepthSwapchainImagesMETA", (PFN_xrVoidFunction*) &gEnumerateEnvironmentDepthSwapchainImagesMETA);
    tableXr.GetInstanceProcAddr(gXrInstance, "xrGetEnvironmentDepthSwapchainStateMETA", (PFN_xrVoidFunction*) &gGetEnvironmentDepthSwapchainStateMETA);
    tableXr.GetInstanceProcAddr(gXrInstance, "xrAcquireEnvironmentDepthImageMETA", (PFN_xrVoidFunction*) &gAcquireEnvironmentDepthImageMETA);
    tableXr.GetInstanceProcAddr(gXrInstance, "xrSetEnvironmentDepthHandRemovalMETA", (PFN_xrVoidFunction*) &gSetEnvironmentDepthHandRemovalMETA);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Creating a depth provider

    // You can create a depth provider by using the xrCreateEnvironmentDepthProviderMETA function.
    // This function creates and returns a XrEnvironmentDepthProvider handle to a depth provider instance.
    // Maximum one depth provider is allowed to exist per app at any given time.
    // The handle is unique per process and cannot be shared across processes.

    // XrResult xrCreateEnvironmentDepthProviderMETA(
    //   XrSession session,
    //   const XrEnvironmentDepthProviderCreateInfoMETA* createInfo,
    //   XrEnvironmentDepthProviderMETA* environmentDepthProvider
    // );

    // To call this function, you must pass a XrEnvironmentDepthProviderCreateInfoMETA struct containing creation
    // flags. Currently createFlags must be zero, but it might be extended in the future.

    // struct XrEnvironmentDepthProviderCreateInfoMETA
    // {
    //   XrStructureType type;
    //   const void* XR_MAY_ALIAS next;
    //   XrEnvironmentDepthProviderCreateFlagsMETA createFlags;
    // };

    XrEnvironmentDepthProviderCreateInfoMETA environmentDepthProviderCreateInfoMETA {XR_TYPE_ENVIRONMENT_DEPTH_PROVIDER_CREATE_INFO_META};
    environmentDepthProviderCreateInfoMETA.next = nullptr;
    environmentDepthProviderCreateInfoMETA.createFlags = 0;

    XrResult result = gCreateEnvironmentDepthProviderMETA(gXrSession, &environmentDepthProviderCreateInfoMETA, &gEnvironmentDepthProviderMETA);
    if(XR_FAILED(result) )
      Log::Write(Log::Level::Info, Fmt("failed CreateEnvironmentDepthProviderMETA") );
    else
      Log::Write(Log::Level::Info, Fmt("succeeded CreateEnvironmentDepthProviderMETA") );

    // To free up all the resources used by the depth provider, you can destroy it by calling
    // xrDestroyEnvironmentDepthProviderMETA

    // XrResult xrDestroyEnvironmentDepthProviderMETA(XrEnvironmentDepthProviderMETA environmentDepthProvider);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Toggling hand removal

    // The Depth API supports removing hands from depth maps and replacing them with estimated background depth.
    // Removing hands can be useful for example if the app prefers to use Tracked Hands for hand occlusions instead of
    // the depth maps.

    // Note that this feature is not supported by all runtimes and devices so the app must first call
    // xrGetSystemProperties to query for a XrSystemEnvironmentDepthPropertiesMETA struct and check that
    // supportsHandRemoval is true.

    // Hand removal can be enabled or disabled at any time by calling the xrSetEnvironmentDepthHandRemovalMETA
    // function:

    // XrResult xrSetEnvironmentDepthHandRemovalMETA(
    //   XrEnvironmentDepthProviderMETA environmentDepthProvider,
    //   const XrEnvironmentDepthHandRemovalSetInfoMETA* setInfo
    // );

    // The function takes a XrEnvironmentDepthHandRemovalSetInfoMETA argument which is defined as:

    // struct XrEnvironmentDepthHandRemovalSetInfoMETA
    // {
    //   XrStructureType type;
    //   const void* XR_MAY_ALIAS next;
    //   XrBool32 enabled;
    // };

    XrEnvironmentDepthHandRemovalSetInfoMETA environmentDepthHandRemovalSetInfoMETA {XR_TYPE_ENVIRONMENT_DEPTH_HAND_REMOVAL_SET_INFO_META};
    environmentDepthHandRemovalSetInfoMETA.next = nullptr;
    environmentDepthHandRemovalSetInfoMETA.enabled = true;

    result = gSetEnvironmentDepthHandRemovalMETA(gEnvironmentDepthProviderMETA, &environmentDepthHandRemovalSetInfoMETA);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Creating and enumerating a depth swapchain

    // Depth maps are provided to the app through a special “readable swapchain” type XrEnvironmentDepthSwapchainMETA.
    // This type is similar to XrSwapchain but supports a different set of operations and is intended to be read
    // instead of written to by the app.

    // Create the swapchain by calling xrCreateEnvironmentDepthSwapchainMETA:

    // XrResult xrCreateEnvironmentDepthSwapchainMETA(
    //   XrEnvironmentDepthProviderMETA environmentDepthProvider,
    //   const XrEnvironmentDepthSwapchainCreateInfoMETA* createInfo,
    //   XrEnvironmentDepthSwapchainMETA* swapchain
    // );

    // This function takes a XrEnvironmentDepthSwapchainCreateInfoMETA struct specifying options for creating the
    // swapchain:

    // struct XrEnvironmentDepthSwapchainCreateInfoMETA
    // {
    //   XrStructureType type;
    //   const void* XR_MAY_ALIAS next;
    //   XrEnvironmentDepthSwapchainCreateFlagsMETA createFlags;
    // };

    // Currently createFlags must be zero, but it might be extended in the future.

    // Once the swapchain is created the resolution can be queried by calling xrGetEnvironmentDepthSwapchainStateMETA:

    // XrResult xrGetEnvironmentDepthSwapchainStateMETA(
    //   XrEnvironmentDepthSwapchainMETA swapchain,
    //   XrEnvironmentDepthSwapchainStateMETA* state
    // );

    // The returned XrEnvironmentDepthSwapchainStateMETA is defined as:

    // struct XrEnvironmentDepthSwapchainStateMETA
    // {
    //   XrStructureType type;
    //   void* XR_MAY_ALIAS next;
    //   uint32_t width;
    //   uint32_t height;
    // };

    // In the same way as for a regular XrSwapchain, the XrEnvironmentDepthSwapchainMETA needs to be “enumerated” into
    // a graphics API specific array of texture handles. This is done by calling
    // xrEnumerateEnvironmentDepthSwapchainImagesMETA that has the same semantics as xrEnumerateSwapchainImages:

    // XrResult xrEnumerateEnvironmentDepthSwapchainImagesMETA(
    //   XrEnvironmentDepthSwapchainMETA swapchain,
    //   uint32_t imageCapacityInput,
    //   uint32_t* imageCountOutput,
    //   XrSwapchainImageBaseHeader* images
    // );

    // To free up all the resources used by the swapchain, you can destroy it by calling
    // xrDestroyEnvironmentDepthSwapchainMETA:

    // XrResult xrDestroyEnvironmentDepthSwapchainMETA(XrEnvironmentDepthSwapchainMETA swapchain);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Starting and stopping the depth provider

    // The depth provider is created in a stopped state by default.
    // To start the asynchronous generation of depth maps, you need to call xrStartEnvironmentDepthProviderMETA:

    // XrResult xrStartEnvironmentDepthProviderMETA(XrEnvironmentDepthProviderMETA environmentDepthProvider);

    // To stop the asynchronous generation of depth maps, call xrStopEnvironmentDepthProviderMETA:

    // XrResult xrStopEnvironmentDepthProviderMETA(XrEnvironmentDepthProviderMETA environmentDepthProvider);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Acquiring depth maps

    // Depth maps should only be accessed between the xrBeginFrame and xrEndFrame calls.  To acquire a lock on the
    // latest available depth map in the swapchain, as well as retrieve metadata needed to parse the depth, apps need
    // to call xrAcquireEnvironmentDepthImageMETA. Once a depth swapchain has been acquired it is locked for the
    // entire duration of the frame. You shouldn’t call xrAcquireEnvironmentDepthImageMETA more than once per frame.

    // XrResult xrAcquireEnvironmentDepthImageMETA(
    //   XrEnvironmentDepthProviderMETA environmentDepthProvider,
    //   const XrEnvironmentDepthImageAcquireInfoMETA* acquireInfo,
    //   XrEnvironmentDepthImageMETA* environmentDepthImage
    // );

    // This function takes an XrEnvironmentDepthImageAcquireInfoMETA struct that needs to be populated with some
    // required parameters:

    // struct XrEnvironmentDepthImageAcquireInfoMETA
    // {
    //   XrStructureType type;
    //   const void* XR_MAY_ALIAS next;
    //   XrSpace space;
    //   XrTime displayTime;
    // };

    // The space field should be set to the XrSpace you want the space to be of the returned pose which the depth map
    // was rendered from. The displayTime field should be set to the displayTime of the current rendered frame as it’s
    // used to compute the pose in case it is time dependent.

    // The information about the now locked swapchain image is returned the XrEnvironmentDepthImageMETA struct defined
    // as:

    // struct XrEnvironmentDepthImageMETA
    // {
    //   XrStructureType type;
    //   const void* XR_MAY_ALIAS next;
    //   uint32_t swapchainIndex;
    //   float nearZ;
    //   float farZ;
    //   XrEnvironmentDepthImageViewMETA views[2];
    // };

    // struct XrEnvironmentDepthImageViewMETA
    // {
    //   XrStructureType type;
    //   const void* XR_MAY_ALIAS next;
    //   XrFovf fov;
    //   XrPosef pose;
    // };

    // The nearZ and farZ are the near and far planes defined in an OpenGL projection matrix, and are needed to
    // convert the depth map’s pixel values into metric distances. The format and convention is the same as for
    // regular OpenGL depth textures.

    // There is a special case you should be aware of: when farZ = inf, you can use an infinite projection matrix as
    // described in Tightening the Precision of Perspective Rendering (see section 3.2: Infinite projection).

    // When farZ == inf, the bottom-right 2x2 quadrant of the 4x4 projection matrix is defined as:

    // [ -1   -2 * nearZ ]
    // [ -1    0         ]

    // zNear zFar infinity

    // Building a projection matrix using common OpenGL helpers and ignoring this special case will introduce NaN
    // values on its coefficients.

    // Note that the display time and pose of the acquired depth map is likely not the same as the estimated display
    // time and pose for the your app’s frame. To compute the depth of your rendered fragments, you must therefore
    // project the fragments 3D coordinates into the depth map using the provided pose and field-of-view (fov). For an
    // example, see the XrSamples / XrPassthroughOcclusion sample where this method is used to render a scene with
    // Depth API based occlusions.
  }

  //Log::Write(Log::Level::Info, Fmt("number of render layers %i", layers.size() ) );
}

bool OpenXrProgram::OpenXrProgramRenderLayer(XrTime predictedDisplayTime, std::vector<XrCompositionLayerProjectionView>& projectionLayerViews, XrCompositionLayerProjection& layer)
{
  XrResult res = XR_ERROR_VALIDATION_FAILURE;

  XrViewState viewState {XR_TYPE_VIEW_STATE};
  uint32_t viewCapacityInput = (uint32_t)m_OpenXrProgramStdVector_XrView.size();
  uint32_t viewCountOutput;

  XrViewLocateInfo viewLocateInfo {XR_TYPE_VIEW_LOCATE_INFO};
  viewLocateInfo.viewConfigurationType = m_OpenXrProgramStdSharedPtr_Options->Parsed.ViewConfigType;
  viewLocateInfo.displayTime = predictedDisplayTime;
  viewLocateInfo.space = m_OpenXrProgramXrSpace;

  if(tableXr.LocateViews)
  {
    res = tableXr.LocateViews(gXrSession, &viewLocateInfo, &viewState, viewCapacityInput, &viewCountOutput, m_OpenXrProgramStdVector_XrView.data() );
    CHECK_XRRESULT(res, "xrLocateViews");
  }

  if( (viewState.viewStateFlags & XR_VIEW_STATE_POSITION_VALID_BIT) == 0 || (viewState.viewStateFlags & XR_VIEW_STATE_ORIENTATION_VALID_BIT) == 0)
    return false;  // There is no valid tracking poses for the views.

  CHECK(viewCountOutput == viewCapacityInput);
  CHECK(viewCountOutput == m_OpenXrProgramStdVector_XrViewConfigurationView.size() );
  CHECK(viewCountOutput == m_OpenXrProgramStdVector_Swapchain.size() );

  projectionLayerViews.resize(viewCountOutput);

  // For each locatable space that we want to visualize, render a 25cm cube.
  std::vector<Cube> cubes;

  for(XrSpace visualizedSpace : m_OpenXrProgramStdVector_XrSpace)
  {
    XrSpaceLocation spaceLocation {XR_TYPE_SPACE_LOCATION};

    if(tableXr.LocateSpace)
    {
      res = tableXr.LocateSpace(visualizedSpace, m_OpenXrProgramXrSpace, predictedDisplayTime, &spaceLocation);
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
  for(auto hand : {(int)Side::LEFT, (int)Side::RIGHT} )
  {
    XrSpaceLocation spaceLocation {XR_TYPE_SPACE_LOCATION};

    if(tableXr.LocateSpace)
    {
      res = tableXr.LocateSpace(m_OpenXrProgramInputState.handSpace[hand], m_OpenXrProgramXrSpace, predictedDisplayTime, &spaceLocation);
      CHECK_XRRESULT(res, "xrLocateSpace");
    }

    if(XR_UNQUALIFIED_SUCCESS(res) )
    {
      if( (spaceLocation.locationFlags & XR_SPACE_LOCATION_POSITION_VALID_BIT) != 0 && (spaceLocation.locationFlags & XR_SPACE_LOCATION_ORIENTATION_VALID_BIT) != 0)
      {
        float scale = 0.1f * m_OpenXrProgramInputState.handScale[hand];
        cubes.push_back(Cube {spaceLocation.pose, {scale, scale, scale} } );
      }
    }
    else
    {
      // Tracking loss is expected when the hand is not active so only log a message
      // if the hand is active.
      if(m_OpenXrProgramInputState.handActive[hand] == XR_TRUE)
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
    const Swapchain viewSwapchain = m_OpenXrProgramStdVector_Swapchain[i];

    XrSwapchainImageAcquireInfo acquireInfo {XR_TYPE_SWAPCHAIN_IMAGE_ACQUIRE_INFO};

    uint32_t swapchainImageIndex;

    if(tableXr.AcquireSwapchainImage)
      CHECK_XRCMD(tableXr.AcquireSwapchainImage(viewSwapchain.handle, &acquireInfo, &swapchainImageIndex) );

    XrSwapchainImageWaitInfo waitInfo {XR_TYPE_SWAPCHAIN_IMAGE_WAIT_INFO};
    waitInfo.timeout = XR_INFINITE_DURATION;

    if(tableXr.WaitSwapchainImage)
      CHECK_XRCMD(tableXr.WaitSwapchainImage(viewSwapchain.handle, &waitInfo) );

    projectionLayerViews[i] = {XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW};
    projectionLayerViews[i].pose = m_OpenXrProgramStdVector_XrView[i].pose;
    projectionLayerViews[i].fov = m_OpenXrProgramStdVector_XrView[i].fov;
    projectionLayerViews[i].subImage.swapchain = viewSwapchain.handle;
    projectionLayerViews[i].subImage.imageRect.offset = {0, 0};
    projectionLayerViews[i].subImage.imageRect.extent = {viewSwapchain.width, viewSwapchain.height};

    const XrSwapchainImageBaseHeader* const swapchainImage = m_OpenXrProgramStdMap_XrSwapchain_StdVectorXrSwapchainImageBaseHeader[viewSwapchain.handle][swapchainImageIndex];
    VulkanGraphicsPlugin_VulkanGraphicsPluginRenderView(projectionLayerViews[i], swapchainImage, m_OpenXrProgramColorSwapchainFormat, cubes);

    XrSwapchainImageReleaseInfo releaseInfo {XR_TYPE_SWAPCHAIN_IMAGE_RELEASE_INFO};

    if(tableXr.ReleaseSwapchainImage)
      CHECK_XRCMD(tableXr.ReleaseSwapchainImage(viewSwapchain.handle, &releaseInfo) );
  }

  layer.space = m_OpenXrProgramXrSpace;
  layer.layerFlags = m_OpenXrProgramStdSharedPtr_Options->Parsed.EnvironmentBlendMode == XR_ENVIRONMENT_BLEND_MODE_ALPHA_BLEND ? XR_COMPOSITION_LAYER_BLEND_TEXTURE_SOURCE_ALPHA_BIT | XR_COMPOSITION_LAYER_UNPREMULTIPLIED_ALPHA_BIT : 0;
  layer.viewCount = (uint32_t)projectionLayerViews.size();
  layer.views = projectionLayerViews.data();
  return true;
}

//const std::shared_ptr<const Options> OpenXrProgram::m_OpenXrProgramStdSharedPtr_Options;

//std::shared_ptr<AndroidPlatformPlugin> OpenXrProgram::m_OpenXrProgramStdSharedPtr_AndroidPlatformPlugin;

//std::shared_ptr<VulkanGraphicsPlugin> OpenXrProgram::m_OpenXrProgramStdSharedPtr_VulkanGraphicsPlugin;

//XrSpace OpenXrProgram::m_OpenXrProgramXrSpace {XR_NULL_HANDLE};

//std::vector<XrViewConfigurationView> OpenXrProgram::m_OpenXrProgramStdVector_XrView;

//std::vector<Swapchain> OpenXrProgram::m_OpenXrProgramStdVector_Swapchain;

//std::map<XrSwapchain, std::vector<XrSwapchainImageBaseHeader*> > OpenXrProgram::m_OpenXrProgramStdMap_XrSwapchain_StdVectorXrSwapchainImageBaseHeader;

//std::vector<XrView> OpenXrProgram::m_OpenXrProgramStdVector_XrView;

//int64_t OpenXrProgram::m_OpenXrProgramColorSwapchainFormat {-1};

//std::vector<XrSpace> OpenXrProgram::m_OpenXrProgramStdVector_XrSpace;

// Application's current lifecycle state according to the runtime
//XrSessionState OpenXrProgram::m_OpenXrProgramXrSessionState {XR_SESSION_STATE_UNKNOWN};

//bool OpenXrProgram::m_OpenXrProgramSessionRunning {false};

//XrEventDataBuffer OpenXrProgram::m_OpenXrProgramXrEventDataBuffer;

//InputState OpenXrProgram::m_OpenXrProgramInputState;

//const std::set<XrEnvironmentBlendMode> OpenXrProgram::m_OpenXrProgramStdSet_XrEnvironmentBlendMode;

std::shared_ptr<OpenXrProgram> OpenXrProgram_CreateOpenXrProgram(const std::shared_ptr<Options>& options, const std::shared_ptr<AndroidPlatformPlugin>& platformPlugin)
{
  return std::make_shared<OpenXrProgram>(options, platformPlugin);
}
