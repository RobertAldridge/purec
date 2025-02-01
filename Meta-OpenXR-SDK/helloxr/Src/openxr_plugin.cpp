
// openxr_plugin.cpp

#include "header.h"

XrInstance gXrInstance = XR_NULL_HANDLE;

XrSession gXrSession = XR_NULL_HANDLE;

XrSystemId gXrSystemId = XR_NULL_SYSTEM_ID;

XrActionSet gOpenXrProgramInputState_InputState_actionSet {XR_NULL_HANDLE};

XrAction gOpenXrProgramInputState_InputState_grabAction {XR_NULL_HANDLE};

XrAction gOpenXrProgramInputState_InputState_poseAction {XR_NULL_HANDLE};

XrAction gOpenXrProgramInputState_InputState_vibrateAction {XR_NULL_HANDLE};

XrAction gOpenXrProgramInputState_InputState_quitAction {XR_NULL_HANDLE};

std::array<XrPath, Side_COUNT> gOpenXrProgramInputState_InputState_handSubactionPath;

std::array<XrSpace, Side_COUNT> gOpenXrProgramInputState_InputState_handSpace;

std::array<float, Side_COUNT> gOpenXrProgramInputState_InputState_handScale = { {1.0f, 1.0f} };

std::array<XrBool32, Side_COUNT> gOpenXrProgramInputState_InputState_handActive;

XrSpace gOpenXrProgramXrSpace {XR_NULL_HANDLE};

std::vector<XrViewConfigurationView> gOpenXrProgramStdVector_XrViewConfigurationView;

std::vector<Swapchain> gOpenXrProgramStdVector_Swapchain;

std::map<XrSwapchain, std::vector<XrSwapchainImageBaseHeader*> > gOpenXrProgramStdMap_XrSwapchain_StdVectorXrSwapchainImageBaseHeader;

std::vector<XrView> gOpenXrProgramStdVector_XrView;

int64_t gOpenXrProgramColorSwapchainFormat {-1};

std::vector<XrSpace> gOpenXrProgramStdVector_XrSpace;

// Application's current lifecycle state according to the runtime
XrSessionState gOpenXrProgramXrSessionState {XR_SESSION_STATE_UNKNOWN};

bool gOpenXrProgramSessionRunning {false};

XrEventDataBuffer gOpenXrProgramXrEventDataBuffer;

extern "C" {
XrPassthroughFB gPassthroughFeature = XR_NULL_HANDLE;
}

XrPassthroughLayerFB gPassthroughLayer = XR_NULL_HANDLE;

PFN_xrCreatePassthroughFB gCreatePassthroughFB = nullptr;
PFN_xrCreatePassthroughLayerFB gCreatePassthroughLayerFB = nullptr;

PFN_xrCreateEnvironmentDepthProviderMETA gCreateEnvironmentDepthProviderMETA = nullptr;
PFN_xrDestroyEnvironmentDepthProviderMETA gDestroyEnvironmentDepthProviderMETA = nullptr;
PFN_xrStartEnvironmentDepthProviderMETA gStartEnvironmentDepthProviderMETA = nullptr;
PFN_xrStopEnvironmentDepthProviderMETA gStopEnvironmentDepthProviderMETA = nullptr;
PFN_xrCreateEnvironmentDepthSwapchainMETA gCreateEnvironmentDepthSwapchainMETA = nullptr;
PFN_xrDestroyEnvironmentDepthSwapchainMETA gDestroyEnvironmentDepthSwapchainMETA = nullptr;
PFN_xrEnumerateEnvironmentDepthSwapchainImagesMETA gEnumerateEnvironmentDepthSwapchainImagesMETA = nullptr;
PFN_xrGetEnvironmentDepthSwapchainStateMETA gGetEnvironmentDepthSwapchainStateMETA = nullptr;
PFN_xrAcquireEnvironmentDepthImageMETA gAcquireEnvironmentDepthImageMETA = nullptr;
PFN_xrSetEnvironmentDepthHandRemovalMETA gSetEnvironmentDepthHandRemovalMETA = nullptr;

XrEnvironmentDepthProviderMETA gEnvironmentDepthProviderMETA = XR_NULL_HANDLE;

std::string GetXrVersionString(XrVersion ver)
{
  return Fmt("%d.%d.%d", XR_VERSION_MAJOR(ver), XR_VERSION_MINOR(ver), XR_VERSION_PATCH(ver) );
}

XrPosef OpenXrProgram_Math::OpenXrProgram_Pose::Identity()
{
  XrPosef t {};
  t.orientation.w = 1;
  return t;
}

XrPosef OpenXrProgram_Math::OpenXrProgram_Pose::Translation(const XrVector3f& translation)
{
  XrPosef t = Identity();
  t.position = translation;
  return t;
}

XrPosef OpenXrProgram_Math::OpenXrProgram_Pose::RotateCCWAboutYAxis(float radians, XrVector3f translation)
{
  XrPosef t = Identity();
  t.orientation.x = 0.f;
  t.orientation.y = std::sin(radians * 0.5f);
  t.orientation.z = 0.f;
  t.orientation.w = std::cos(radians * 0.5f);
  t.position = translation;

  return t;
}

XrReferenceSpaceCreateInfo GetXrReferenceSpaceCreateInfo(const std::string& referenceSpaceTypeStr)
{
  XrReferenceSpaceCreateInfo referenceSpaceCreateInfo {XR_TYPE_REFERENCE_SPACE_CREATE_INFO};
  referenceSpaceCreateInfo.poseInReferenceSpace = OpenXrProgram_Math::OpenXrProgram_Pose::Identity();

  if(EqualsIgnoreCase(referenceSpaceTypeStr, "View") )
  {
    referenceSpaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_VIEW;
  }
  else if(EqualsIgnoreCase(referenceSpaceTypeStr, "ViewFront") )
  {
    // Render head-locked 2m in front of device.
    referenceSpaceCreateInfo.poseInReferenceSpace = OpenXrProgram_Math::OpenXrProgram_Pose::Translation( {0.f, 0.f, -2.f} ),
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
    referenceSpaceCreateInfo.poseInReferenceSpace = OpenXrProgram_Math::OpenXrProgram_Pose::RotateCCWAboutYAxis(0.f, {-2.f, 0.f, -2.f} );
    referenceSpaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_STAGE;
  }
  else if(EqualsIgnoreCase(referenceSpaceTypeStr, "StageRight") )
  {
    referenceSpaceCreateInfo.poseInReferenceSpace = OpenXrProgram_Math::OpenXrProgram_Pose::RotateCCWAboutYAxis(0.f, {2.f, 0.f, -2.f} );
    referenceSpaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_STAGE;
  }
  else if(EqualsIgnoreCase(referenceSpaceTypeStr, "StageLeftRotated") )
  {
    referenceSpaceCreateInfo.poseInReferenceSpace = OpenXrProgram_Math::OpenXrProgram_Pose::RotateCCWAboutYAxis(3.14f / 3.f, {-2.f, 0.5f, -2.f} );
    referenceSpaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_STAGE;
  }
  else if(EqualsIgnoreCase(referenceSpaceTypeStr, "StageRightRotated") )
  {
    referenceSpaceCreateInfo.poseInReferenceSpace = OpenXrProgram_Math::OpenXrProgram_Pose::RotateCCWAboutYAxis(-3.14f / 3.f, {2.f, 0.5f, -2.f} );
    referenceSpaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_STAGE;
  }
  else
  {
    throw std::invalid_argument(Fmt("Unknown reference space type '%s'", referenceSpaceTypeStr.c_str() ) );
  }

  return referenceSpaceCreateInfo;
}

void OpenXrProgram_OpenXrProgram_Destructor()
{
  if(gOpenXrProgramInputState_InputState_actionSet != XR_NULL_HANDLE)
  {
    for(auto hand : { Side_LEFT, Side_RIGHT} )
    {
      if(tableXr.DestroySpace)
        tableXr.DestroySpace(gOpenXrProgramInputState_InputState_handSpace[hand] );
    }

    if(tableXr.DestroyActionSet)
      tableXr.DestroyActionSet(gOpenXrProgramInputState_InputState_actionSet);
  }

  for(Swapchain swapchain : gOpenXrProgramStdVector_Swapchain)
  {
    if(tableXr.DestroySwapchain)
      tableXr.DestroySwapchain(swapchain.handle);
  }

  for(XrSpace visualizedSpace : gOpenXrProgramStdVector_XrSpace)
  {
    if(tableXr.DestroySpace)
      tableXr.DestroySpace(visualizedSpace);
  }

  if(gOpenXrProgramXrSpace != XR_NULL_HANDLE && tableXr.DestroySpace)
    tableXr.DestroySpace(gOpenXrProgramXrSpace);

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
//  std::array<float, Side_COUNT> handScale = { {1.0f, 1.0f} };
//
//  std::array<XrBool32, Side_COUNT> handActive;
//};

bool OpenXrProgram_OpenXrProgramIsSessionRunning()
{
  return gOpenXrProgramSessionRunning;
}

bool OpenXrProgram_OpenXrProgramIsSessionFocused()
{
  return gOpenXrProgramXrSessionState == XR_SESSION_STATE_FOCUSED;
}

// Unreal UOculusXRFunctionLibrary::SetSuggestedCpuAndGpuPerformanceLevels (exposed in Blueprint)
//
// Unity OVRPlugin::suggestedCpuPerfLevel, OVRPlugin::suggestedGpuPerfLevel
//
// Native ovrp_SetSuggestedCpuPerformanceLevel, ovrp_GetSuggestedGpuPerformanceLevel

bool OpenXrProgram_OpenXrProgramRenderLayer(XrTime predictedDisplayTime, std::vector<XrCompositionLayerProjectionView>& projectionLayerViews, XrCompositionLayerProjection& layer)
{
  XrResult res = XR_ERROR_VALIDATION_FAILURE;

  XrViewState viewState {XR_TYPE_VIEW_STATE};
  uint32_t viewCapacityInput = (uint32_t)gOpenXrProgramStdVector_XrView.size();
  uint32_t viewCountOutput;

  XrViewLocateInfo viewLocateInfo {XR_TYPE_VIEW_LOCATE_INFO};
  viewLocateInfo.viewConfigurationType = gOptions_XrViewConfigurationType;
  viewLocateInfo.displayTime = predictedDisplayTime;
  viewLocateInfo.space = gOpenXrProgramXrSpace;

  if(tableXr.LocateViews)
  {
    res = tableXr.LocateViews(gXrSession, &viewLocateInfo, &viewState, viewCapacityInput, &viewCountOutput, gOpenXrProgramStdVector_XrView.data() );
    CHECK_XRRESULT(res, "xrLocateViews");
  }

  if( (viewState.viewStateFlags & XR_VIEW_STATE_POSITION_VALID_BIT) == 0 || (viewState.viewStateFlags & XR_VIEW_STATE_ORIENTATION_VALID_BIT) == 0)
    return false;  // There is no valid tracking poses for the views.

  CHECK_CHECK(viewCountOutput == viewCapacityInput);
  CHECK_CHECK(viewCountOutput == gOpenXrProgramStdVector_XrViewConfigurationView.size() );
  CHECK_CHECK(viewCountOutput == gOpenXrProgramStdVector_Swapchain.size() );

  projectionLayerViews.resize(viewCountOutput);

  // For each locatable space that we want to visualize, render a 25cm cube.
  std::vector<Cube> cubes;

  for(XrSpace visualizedSpace : gOpenXrProgramStdVector_XrSpace)
  {
    XrSpaceLocation spaceLocation {XR_TYPE_SPACE_LOCATION};

    if(tableXr.LocateSpace)
    {
      res = tableXr.LocateSpace(visualizedSpace, gOpenXrProgramXrSpace, predictedDisplayTime, &spaceLocation);
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
  for(auto hand : {Side_LEFT, Side_RIGHT} )
  {
    XrSpaceLocation spaceLocation {XR_TYPE_SPACE_LOCATION};

    if(tableXr.LocateSpace)
    {
      res = tableXr.LocateSpace(gOpenXrProgramInputState_InputState_handSpace[hand], gOpenXrProgramXrSpace, predictedDisplayTime, &spaceLocation);
      CHECK_XRRESULT(res, "xrLocateSpace");
    }

    if(XR_UNQUALIFIED_SUCCESS(res) )
    {
      if( (spaceLocation.locationFlags & XR_SPACE_LOCATION_POSITION_VALID_BIT) != 0 && (spaceLocation.locationFlags & XR_SPACE_LOCATION_ORIENTATION_VALID_BIT) != 0)
      {
        float scale = 0.1f * gOpenXrProgramInputState_InputState_handScale[hand];
        cubes.push_back(Cube {spaceLocation.pose, {scale, scale, scale} } );
      }
    }
    else
    {
      // Tracking loss is expected when the hand is not active so only log a message
      // if the hand is active.
      if(gOpenXrProgramInputState_InputState_handActive[hand] == XR_TRUE)
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
    const Swapchain viewSwapchain = gOpenXrProgramStdVector_Swapchain[i];

    XrSwapchainImageAcquireInfo acquireInfo {XR_TYPE_SWAPCHAIN_IMAGE_ACQUIRE_INFO};

    uint32_t swapchainImageIndex;

    if(tableXr.AcquireSwapchainImage)
      CHECK_XRCMD_CHECK(tableXr.AcquireSwapchainImage(viewSwapchain.handle, &acquireInfo, &swapchainImageIndex) );

    XrSwapchainImageWaitInfo waitInfo {XR_TYPE_SWAPCHAIN_IMAGE_WAIT_INFO};
    waitInfo.timeout = XR_INFINITE_DURATION;

    if(tableXr.WaitSwapchainImage)
      CHECK_XRCMD_CHECK(tableXr.WaitSwapchainImage(viewSwapchain.handle, &waitInfo) );

    projectionLayerViews[i] = {XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW};
    projectionLayerViews[i].pose = gOpenXrProgramStdVector_XrView[i].pose;
    projectionLayerViews[i].fov = gOpenXrProgramStdVector_XrView[i].fov;
    projectionLayerViews[i].subImage.swapchain = viewSwapchain.handle;
    projectionLayerViews[i].subImage.imageRect.offset = {0, 0};
    projectionLayerViews[i].subImage.imageRect.extent = {viewSwapchain.width, viewSwapchain.height};

    const XrSwapchainImageBaseHeader* const swapchainImage = gOpenXrProgramStdMap_XrSwapchain_StdVectorXrSwapchainImageBaseHeader[viewSwapchain.handle][swapchainImageIndex];
    VulkanGraphicsPlugin_VulkanGraphicsPluginRenderView(projectionLayerViews[i], swapchainImage, gOpenXrProgramColorSwapchainFormat, cubes);

    XrSwapchainImageReleaseInfo releaseInfo {XR_TYPE_SWAPCHAIN_IMAGE_RELEASE_INFO};

    if(tableXr.ReleaseSwapchainImage)
      CHECK_XRCMD_CHECK(tableXr.ReleaseSwapchainImage(viewSwapchain.handle, &releaseInfo) );
  }

  layer.space = gOpenXrProgramXrSpace;
  layer.layerFlags = gOptions_XrEnvironmentBlendMode == XR_ENVIRONMENT_BLEND_MODE_ALPHA_BLEND ? XR_COMPOSITION_LAYER_BLEND_TEXTURE_SOURCE_ALPHA_BIT | XR_COMPOSITION_LAYER_UNPREMULTIPLIED_ALPHA_BIT : 0;
  layer.viewCount = (uint32_t)projectionLayerViews.size();
  layer.views = projectionLayerViews.data();
  return true;
}
