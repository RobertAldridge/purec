
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

std::array<float, Side_COUNT> gOpenXrProgramInputState_InputState_handScale =
{
  {1.0f, 1.0f}
};

std::array<XrBool32, Side_COUNT> gOpenXrProgramInputState_InputState_handActive;

// local space
XrSpace gOpenXrProgramXrSpace {XR_NULL_HANDLE};

//XrSpace gOpenXrHeadXrSpace {XR_NULL_HANDLE};

std::vector<XrViewConfigurationView> gOpenXrProgramStdVector_XrViewConfigurationView;

std::vector<Swapchain> gOpenXrProgramStdVector_Swapchain;

std::map<XrSwapchain, std::vector<XrSwapchainImageBaseHeader*> >
  gOpenXrProgramStdMap_XrSwapchain_StdVectorXrSwapchainImageBaseHeader;

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

XrEnvironmentDepthProviderMETA gEnvironmentDepthProviderMETA = XR_NULL_HANDLE;

XrEnvironmentDepthSwapchainMETA gEnvironmentDepthSwapchainMETA = XR_NULL_HANDLE;

XrEnvironmentDepthProviderCreateInfoMETA gEnvironmentDepthProviderCreateInfoMETA
{
  XR_TYPE_ENVIRONMENT_DEPTH_PROVIDER_CREATE_INFO_META
};

XrEnvironmentDepthHandRemovalSetInfoMETA gEnvironmentDepthHandRemovalSetInfoMETA
{
  XR_TYPE_ENVIRONMENT_DEPTH_HAND_REMOVAL_SET_INFO_META
};

XrEnvironmentDepthSwapchainCreateInfoMETA gEnvironmentDepthSwapchainCreateInfoMETA
{
  XR_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_CREATE_INFO_META
};

XrEnvironmentDepthSwapchainStateMETA gEnvironmentDepthSwapchainStateMETA
{
  XR_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_STATE_META
};

uint32_t gEnvironmentDepthSwapChainLength = 0;

std::vector<XrSwapchainImageVulkanKHR> gEnvironmentDepthImages;
std::vector<VkImage> gEnvironmentDepthTextures;

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
    referenceSpaceCreateInfo.poseInReferenceSpace =
      OpenXrProgram_Math::OpenXrProgram_Pose::Translation( {0.f, 0.f, -2.f} ),

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
    referenceSpaceCreateInfo.poseInReferenceSpace =
      OpenXrProgram_Math::OpenXrProgram_Pose::RotateCCWAboutYAxis(0.f, {-2.f, 0.f, -2.f} );

    referenceSpaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_STAGE;
  }
  else if(EqualsIgnoreCase(referenceSpaceTypeStr, "StageRight") )
  {
    referenceSpaceCreateInfo.poseInReferenceSpace =
      OpenXrProgram_Math::OpenXrProgram_Pose::RotateCCWAboutYAxis(0.f, {2.f, 0.f, -2.f} );

    referenceSpaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_STAGE;
  }
  else if(EqualsIgnoreCase(referenceSpaceTypeStr, "StageLeftRotated") )
  {
    referenceSpaceCreateInfo.poseInReferenceSpace =
      OpenXrProgram_Math::OpenXrProgram_Pose::RotateCCWAboutYAxis(3.14f / 3.f, {-2.f, 0.5f, -2.f} );

    referenceSpaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_STAGE;
  }
  else if(EqualsIgnoreCase(referenceSpaceTypeStr, "StageRightRotated") )
  {
    referenceSpaceCreateInfo.poseInReferenceSpace =
      OpenXrProgram_Math::OpenXrProgram_Pose::RotateCCWAboutYAxis(-3.14f / 3.f, {2.f, 0.5f, -2.f} );

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
//  std::array<float, Side_COUNT> handScale =
//  {
//    {1.0f, 1.0f}
//  };
//
//  std::array<XrBool32, Side_COUNT> handActive;
//};

#if 0
bool OpenXrProgram_OpenXrProgramIsSessionFocused()
{
  return gOpenXrProgramXrSessionState == XR_SESSION_STATE_FOCUSED;
}
#endif

// Unreal UOculusXRFunctionLibrary::SetSuggestedCpuAndGpuPerformanceLevels (exposed in Blueprint)
//
// Unity OVRPlugin::suggestedCpuPerfLevel, OVRPlugin::suggestedGpuPerfLevel
//
// Native ovrp_SetSuggestedCpuPerformanceLevel, ovrp_GetSuggestedGpuPerformanceLevel
