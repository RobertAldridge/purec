
// openxr_vtable.cpp

#include "header.h"

struct XrGeneratedDispatchTableCore tableXr;

// dispatch tableXr blah function
int InitOpenXr1()
{
  void* libopenxr = 0;

  if(tableXr.CreateInstance)
    return 1;

  libopenxr = dlopen("libopenxr_loader.so", RTLD_NOW | RTLD_LOCAL);
  if( !libopenxr)
    return 0;

  // ---- Core 1.0 commands

  // tableXr.GetInstanceProcAddr
  tableXr.GetInstanceProcAddr = (PFN_xrGetInstanceProcAddr)dlsym(libopenxr, "xrGetInstanceProcAddr");

  // tableXr.InitializeLoaderKHR
  tableXr.GetInstanceProcAddr(XR_NULL_HANDLE, "xrInitializeLoaderKHR", (PFN_xrVoidFunction*)&tableXr.InitializeLoaderKHR);

  // tableXr.EnumerateInstanceExtensionProperties
  tableXr.GetInstanceProcAddr(XR_NULL_HANDLE, "xrEnumerateInstanceExtensionProperties", (PFN_xrVoidFunction*)&tableXr.EnumerateInstanceExtensionProperties);

  // tableXr.EnumerateApiLayerProperties
  tableXr.GetInstanceProcAddr(XR_NULL_HANDLE, "xrEnumerateApiLayerProperties", (PFN_xrVoidFunction*)&tableXr.EnumerateApiLayerProperties);

  // tableXr.CreateInstance
  tableXr.GetInstanceProcAddr(XR_NULL_HANDLE, "xrCreateInstance", (PFN_xrVoidFunction*)&tableXr.CreateInstance);

  return 1;
}

int InitOpenXr2()
{
  if(tableXr.BeginFrame)
    return 1;

  // ---- Core 1.0 commands

  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetInstanceProcAddr", (PFN_xrVoidFunction*)&tableXr.GetInstanceProcAddr);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrInitializeLoaderKHR", (PFN_xrVoidFunction*)&tableXr.InitializeLoaderKHR);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrEnumerateInstanceExtensionProperties", (PFN_xrVoidFunction*)&tableXr.EnumerateInstanceExtensionProperties);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrEnumerateApiLayerProperties", (PFN_xrVoidFunction*)&tableXr.EnumerateApiLayerProperties);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateInstance", (PFN_xrVoidFunction*)&tableXr.CreateInstance);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrAcquireSwapchainImage", (PFN_xrVoidFunction*)&tableXr.AcquireSwapchainImage);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrApplyHapticFeedback", (PFN_xrVoidFunction*)&tableXr.ApplyHapticFeedback);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrAttachSessionActionSets", (PFN_xrVoidFunction*)&tableXr.AttachSessionActionSets);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrBeginFrame", (PFN_xrVoidFunction*)&tableXr.BeginFrame);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrBeginSession", (PFN_xrVoidFunction*)&tableXr.BeginSession);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateAction", (PFN_xrVoidFunction*)&tableXr.CreateAction);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateActionSet", (PFN_xrVoidFunction*)&tableXr.CreateActionSet);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateActionSpace", (PFN_xrVoidFunction*)&tableXr.CreateActionSpace);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateReferenceSpace", (PFN_xrVoidFunction*)&tableXr.CreateReferenceSpace);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateSession", (PFN_xrVoidFunction*)&tableXr.CreateSession);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateSwapchain", (PFN_xrVoidFunction*)&tableXr.CreateSwapchain);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyAction", (PFN_xrVoidFunction*)&tableXr.DestroyAction);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyActionSet", (PFN_xrVoidFunction*)&tableXr.DestroyActionSet);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyInstance", (PFN_xrVoidFunction*)&tableXr.DestroyInstance);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroySession", (PFN_xrVoidFunction*)&tableXr.DestroySession);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroySpace", (PFN_xrVoidFunction*)&tableXr.DestroySpace);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroySwapchain", (PFN_xrVoidFunction*)&tableXr.DestroySwapchain);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrEndFrame", (PFN_xrVoidFunction*)&tableXr.EndFrame);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrEndSession", (PFN_xrVoidFunction*)&tableXr.EndSession);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrEnumerateBoundSourcesForAction", (PFN_xrVoidFunction*)&tableXr.EnumerateBoundSourcesForAction);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrEnumerateEnvironmentBlendModes", (PFN_xrVoidFunction*)&tableXr.EnumerateEnvironmentBlendModes);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrEnumerateReferenceSpaces", (PFN_xrVoidFunction*)&tableXr.EnumerateReferenceSpaces);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrEnumerateSwapchainFormats", (PFN_xrVoidFunction*)&tableXr.EnumerateSwapchainFormats);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrEnumerateSwapchainImages", (PFN_xrVoidFunction*)&tableXr.EnumerateSwapchainImages);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrEnumerateViewConfigurationViews", (PFN_xrVoidFunction*)&tableXr.EnumerateViewConfigurationViews);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrEnumerateViewConfigurations", (PFN_xrVoidFunction*)&tableXr.EnumerateViewConfigurations);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetActionStateBoolean", (PFN_xrVoidFunction*)&tableXr.GetActionStateBoolean);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetActionStateFloat", (PFN_xrVoidFunction*)&tableXr.GetActionStateFloat);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetActionStatePose", (PFN_xrVoidFunction*)&tableXr.GetActionStatePose);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetActionStateVector2f", (PFN_xrVoidFunction*)&tableXr.GetActionStateVector2f);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetCurrentInteractionProfile", (PFN_xrVoidFunction*)&tableXr.GetCurrentInteractionProfile);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetInputSourceLocalizedName", (PFN_xrVoidFunction*)&tableXr.GetInputSourceLocalizedName);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetInstanceProperties", (PFN_xrVoidFunction*)&tableXr.GetInstanceProperties);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetReferenceSpaceBoundsRect", (PFN_xrVoidFunction*)&tableXr.GetReferenceSpaceBoundsRect);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetSystem", (PFN_xrVoidFunction*)&tableXr.GetSystem);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetSystemProperties", (PFN_xrVoidFunction*)&tableXr.GetSystemProperties);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetViewConfigurationProperties", (PFN_xrVoidFunction*)&tableXr.GetViewConfigurationProperties);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrLocateSpace", (PFN_xrVoidFunction*)&tableXr.LocateSpace);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrLocateViews", (PFN_xrVoidFunction*)&tableXr.LocateViews);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrPathToString", (PFN_xrVoidFunction*)&tableXr.PathToString);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrPollEvent", (PFN_xrVoidFunction*)&tableXr.PollEvent);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrReleaseSwapchainImage", (PFN_xrVoidFunction*)&tableXr.ReleaseSwapchainImage);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrRequestExitSession", (PFN_xrVoidFunction*)&tableXr.RequestExitSession);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrResultToString", (PFN_xrVoidFunction*)&tableXr.ResultToString);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrStopHapticFeedback", (PFN_xrVoidFunction*)&tableXr.StopHapticFeedback);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrStringToPath", (PFN_xrVoidFunction*)&tableXr.StringToPath);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrStructureTypeToString", (PFN_xrVoidFunction*)&tableXr.StructureTypeToString);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSuggestInteractionProfileBindings", (PFN_xrVoidFunction*)&tableXr.SuggestInteractionProfileBindings);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSyncActions", (PFN_xrVoidFunction*)&tableXr.SyncActions);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrWaitFrame", (PFN_xrVoidFunction*)&tableXr.WaitFrame);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrWaitSwapchainImage", (PFN_xrVoidFunction*)&tableXr.WaitSwapchainImage);

  // ---- Core 1.1 commands

  tableXr.GetInstanceProcAddr(gXrInstance, "xrLocateSpaces", (PFN_xrVoidFunction*)&tableXr.LocateSpaces);

  // ---- XR_EXT_debug_utils extension commands

  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateDebugUtilsMessengerEXT", (PFN_xrVoidFunction*)&tableXr.CreateDebugUtilsMessengerEXT);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyDebugUtilsMessengerEXT", (PFN_xrVoidFunction*)&tableXr.DestroyDebugUtilsMessengerEXT);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSessionBeginDebugUtilsLabelRegionEXT", (PFN_xrVoidFunction*)&tableXr.SessionBeginDebugUtilsLabelRegionEXT);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSessionEndDebugUtilsLabelRegionEXT", (PFN_xrVoidFunction*)&tableXr.SessionEndDebugUtilsLabelRegionEXT);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSessionInsertDebugUtilsLabelEXT", (PFN_xrVoidFunction*)&tableXr.SessionInsertDebugUtilsLabelEXT);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSetDebugUtilsObjectNameEXT", (PFN_xrVoidFunction*)&tableXr.SetDebugUtilsObjectNameEXT);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSubmitDebugUtilsMessageEXT", (PFN_xrVoidFunction*)&tableXr.SubmitDebugUtilsMessageEXT);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetVulkanGraphicsRequirements2KHR", (PFN_xrVoidFunction*)&tableXr.GetVulkanGraphicsRequirements2KHR);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateVulkanInstanceKHR", (PFN_xrVoidFunction*)&tableXr.CreateVulkanInstanceKHR);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetVulkanGraphicsDevice2KHR", (PFN_xrVoidFunction*)&tableXr.GetVulkanGraphicsDevice2KHR);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateVulkanDeviceKHR", (PFN_xrVoidFunction*)&tableXr.CreateVulkanDeviceKHR);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreatePassthroughFB", (PFN_xrVoidFunction*)&tableXr.CreatePassthroughFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreatePassthroughLayerFB", (PFN_xrVoidFunction*)&tableXr.CreatePassthroughLayerFB);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateEnvironmentDepthProviderMETA", (PFN_xrVoidFunction*)&tableXr.CreateEnvironmentDepthProviderMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyEnvironmentDepthProviderMETA", (PFN_xrVoidFunction*)&tableXr.DestroyEnvironmentDepthProviderMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrStartEnvironmentDepthProviderMETA", (PFN_xrVoidFunction*)&tableXr.StartEnvironmentDepthProviderMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrStopEnvironmentDepthProviderMETA", (PFN_xrVoidFunction*)&tableXr.StopEnvironmentDepthProviderMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateEnvironmentDepthSwapchainMETA", (PFN_xrVoidFunction*)&tableXr.CreateEnvironmentDepthSwapchainMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyEnvironmentDepthSwapchainMETA", (PFN_xrVoidFunction*)&tableXr.DestroyEnvironmentDepthSwapchainMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrEnumerateEnvironmentDepthSwapchainImagesMETA", (PFN_xrVoidFunction*)&tableXr.EnumerateEnvironmentDepthSwapchainImagesMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetEnvironmentDepthSwapchainStateMETA", (PFN_xrVoidFunction*)&tableXr.GetEnvironmentDepthSwapchainStateMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrAcquireEnvironmentDepthImageMETA", (PFN_xrVoidFunction*)&tableXr.AcquireEnvironmentDepthImageMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSetEnvironmentDepthHandRemovalMETA", (PFN_xrVoidFunction*)&tableXr.SetEnvironmentDepthHandRemovalMETA);

  // openxr.h

  tableXr.GetInstanceProcAddr(gXrInstance, "xrVoidFunction", (PFN_xrVoidFunction*)&tableXr.VoidFunction);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrDebugUtilsMessengerCallbackEXT", (PFN_xrVoidFunction*)&tableXr.DebugUtilsMessengerCallbackEXT);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrApplyForceFeedbackCurlMNDX", (PFN_xrVoidFunction*)&tableXr.ApplyForceFeedbackCurlMNDX);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrBeginPlaneDetectionEXT", (PFN_xrVoidFunction*)&tableXr.BeginPlaneDetectionEXT);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrCancelFutureEXT", (PFN_xrVoidFunction*)&tableXr.CancelFutureEXT);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrChangeVirtualKeyboardTextContextMETA", (PFN_xrVoidFunction*)&tableXr.ChangeVirtualKeyboardTextContextMETA);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateBodyTrackerFB", (PFN_xrVoidFunction*)&tableXr.CreateBodyTrackerFB);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateEyeTrackerFB", (PFN_xrVoidFunction*)&tableXr.CreateEyeTrackerFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateFaceTracker2FB", (PFN_xrVoidFunction*)&tableXr.CreateFaceTracker2FB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateFaceTrackerFB", (PFN_xrVoidFunction*)&tableXr.CreateFaceTrackerFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateFoveationProfileFB", (PFN_xrVoidFunction*)&tableXr.CreateFoveationProfileFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateGeometryInstanceFB", (PFN_xrVoidFunction*)&tableXr.CreateGeometryInstanceFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateHandTrackerEXT", (PFN_xrVoidFunction*)&tableXr.CreateHandTrackerEXT);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateKeyboardSpaceFB", (PFN_xrVoidFunction*)&tableXr.CreateKeyboardSpaceFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreatePassthroughColorLutMETA", (PFN_xrVoidFunction*)&tableXr.CreatePassthroughColorLutMETA);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreatePlaneDetectorEXT", (PFN_xrVoidFunction*)&tableXr.CreatePlaneDetectorEXT);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateSpaceUserFB", (PFN_xrVoidFunction*)&tableXr.CreateSpaceUserFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateSpatialAnchorFB", (PFN_xrVoidFunction*)&tableXr.CreateSpatialAnchorFB);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateTriangleMeshFB", (PFN_xrVoidFunction*)&tableXr.CreateTriangleMeshFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateVirtualKeyboardMETA", (PFN_xrVoidFunction*)&tableXr.CreateVirtualKeyboardMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateVirtualKeyboardSpaceMETA", (PFN_xrVoidFunction*)&tableXr.CreateVirtualKeyboardSpaceMETA);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyBodyTrackerFB", (PFN_xrVoidFunction*)&tableXr.DestroyBodyTrackerFB);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyEyeTrackerFB", (PFN_xrVoidFunction*)&tableXr.DestroyEyeTrackerFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyFaceTracker2FB", (PFN_xrVoidFunction*)&tableXr.DestroyFaceTracker2FB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyFaceTrackerFB", (PFN_xrVoidFunction*)&tableXr.DestroyFaceTrackerFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyFoveationProfileFB", (PFN_xrVoidFunction*)&tableXr.DestroyFoveationProfileFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyGeometryInstanceFB", (PFN_xrVoidFunction*)&tableXr.DestroyGeometryInstanceFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyHandTrackerEXT", (PFN_xrVoidFunction*)&tableXr.DestroyHandTrackerEXT);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyPassthroughColorLutMETA", (PFN_xrVoidFunction*)&tableXr.DestroyPassthroughColorLutMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyPassthroughFB", (PFN_xrVoidFunction*)&tableXr.DestroyPassthroughFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyPassthroughLayerFB", (PFN_xrVoidFunction*)&tableXr.DestroyPassthroughLayerFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyPlaneDetectorEXT", (PFN_xrVoidFunction*)&tableXr.DestroyPlaneDetectorEXT);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroySpaceUserFB", (PFN_xrVoidFunction*)&tableXr.DestroySpaceUserFB);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyTriangleMeshFB", (PFN_xrVoidFunction*)&tableXr.DestroyTriangleMeshFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyVirtualKeyboardMETA", (PFN_xrVoidFunction*)&tableXr.DestroyVirtualKeyboardMETA);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrEnumerateApiLayerProperties", (PFN_xrVoidFunction*)&tableXr.EnumerateApiLayerProperties);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrEnumerateColorSpacesFB", (PFN_xrVoidFunction*)&tableXr.EnumerateColorSpacesFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrEnumerateDisplayRefreshRatesFB", (PFN_xrVoidFunction*)&tableXr.EnumerateDisplayRefreshRatesFB);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrEnumerateExternalCamerasOCULUS", (PFN_xrVoidFunction*)&tableXr.EnumerateExternalCamerasOCULUS);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrEnumerateInstanceExtensionProperties", (PFN_xrVoidFunction*)&tableXr.EnumerateInstanceExtensionProperties);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrEnumeratePerformanceMetricsCounterPathsMETA", (PFN_xrVoidFunction*)&tableXr.EnumeratePerformanceMetricsCounterPathsMETA);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrEnumerateRenderModelPathsFB", (PFN_xrVoidFunction*)&tableXr.EnumerateRenderModelPathsFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrEnumerateSpaceSupportedComponentsFB", (PFN_xrVoidFunction*)&tableXr.EnumerateSpaceSupportedComponentsFB);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrEraseSpaceFB", (PFN_xrVoidFunction*)&tableXr.EraseSpaceFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGeometryInstanceSetTransformFB", (PFN_xrVoidFunction*)&tableXr.GeometryInstanceSetTransformFB);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetBodySkeletonFB", (PFN_xrVoidFunction*)&tableXr.GetBodySkeletonFB);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetDeviceSampleRateFB", (PFN_xrVoidFunction*)&tableXr.GetDeviceSampleRateFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetDisplayRefreshRateFB", (PFN_xrVoidFunction*)&tableXr.GetDisplayRefreshRateFB);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetEyeGazesFB", (PFN_xrVoidFunction*)&tableXr.GetEyeGazesFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetFaceExpressionWeights2FB", (PFN_xrVoidFunction*)&tableXr.GetFaceExpressionWeights2FB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetFaceExpressionWeightsFB", (PFN_xrVoidFunction*)&tableXr.GetFaceExpressionWeightsFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetFoveationEyeTrackedStateMETA", (PFN_xrVoidFunction*)&tableXr.GetFoveationEyeTrackedStateMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetHandMeshFB", (PFN_xrVoidFunction*)&tableXr.GetHandMeshFB);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetInstanceProcAddr", (PFN_xrVoidFunction*)&tableXr.GetInstanceProcAddr);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetPassthroughPreferencesMETA", (PFN_xrVoidFunction*)&tableXr.GetPassthroughPreferencesMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetPerformanceMetricsStateMETA", (PFN_xrVoidFunction*)&tableXr.GetPerformanceMetricsStateMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetPlaneDetectionStateEXT", (PFN_xrVoidFunction*)&tableXr.GetPlaneDetectionStateEXT);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetPlaneDetectionsEXT", (PFN_xrVoidFunction*)&tableXr.GetPlaneDetectionsEXT);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetPlanePolygonBufferEXT", (PFN_xrVoidFunction*)&tableXr.GetPlanePolygonBufferEXT);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetRecommendedLayerResolutionMETA", (PFN_xrVoidFunction*)&tableXr.GetRecommendedLayerResolutionMETA);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetRenderModelPropertiesFB", (PFN_xrVoidFunction*)&tableXr.GetRenderModelPropertiesFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetSpaceBoundary2DFB", (PFN_xrVoidFunction*)&tableXr.GetSpaceBoundary2DFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetSpaceBoundingBox2DFB", (PFN_xrVoidFunction*)&tableXr.GetSpaceBoundingBox2DFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetSpaceBoundingBox3DFB", (PFN_xrVoidFunction*)&tableXr.GetSpaceBoundingBox3DFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetSpaceComponentStatusFB", (PFN_xrVoidFunction*)&tableXr.GetSpaceComponentStatusFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetSpaceContainerFB", (PFN_xrVoidFunction*)&tableXr.GetSpaceContainerFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetSpaceRoomLayoutFB", (PFN_xrVoidFunction*)&tableXr.GetSpaceRoomLayoutFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetSpaceSemanticLabelsFB", (PFN_xrVoidFunction*)&tableXr.GetSpaceSemanticLabelsFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetSpaceTriangleMeshMETA", (PFN_xrVoidFunction*)&tableXr.GetSpaceTriangleMeshMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetSpaceUserIdFB", (PFN_xrVoidFunction*)&tableXr.GetSpaceUserIdFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetSpaceUuidFB", (PFN_xrVoidFunction*)&tableXr.GetSpaceUuidFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetSwapchainStateFB", (PFN_xrVoidFunction*)&tableXr.GetSwapchainStateFB);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetVirtualKeyboardDirtyTexturesMETA", (PFN_xrVoidFunction*)&tableXr.GetVirtualKeyboardDirtyTexturesMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetVirtualKeyboardModelAnimationStatesMETA", (PFN_xrVoidFunction*)&tableXr.GetVirtualKeyboardModelAnimationStatesMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetVirtualKeyboardScaleMETA", (PFN_xrVoidFunction*)&tableXr.GetVirtualKeyboardScaleMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetVirtualKeyboardTextureDataMETA", (PFN_xrVoidFunction*)&tableXr.GetVirtualKeyboardTextureDataMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetVisibilityMaskKHR", (PFN_xrVoidFunction*)&tableXr.GetVisibilityMaskKHR);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrLoadRenderModelFB", (PFN_xrVoidFunction*)&tableXr.LoadRenderModelFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrLocateBodyJointsFB", (PFN_xrVoidFunction*)&tableXr.LocateBodyJointsFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrLocateHandJointsEXT", (PFN_xrVoidFunction*)&tableXr.LocateHandJointsEXT);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrLocateSpacesKHR", (PFN_xrVoidFunction*)&tableXr.LocateSpacesKHR);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrPassthroughLayerPauseFB", (PFN_xrVoidFunction*)&tableXr.PassthroughLayerPauseFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrPassthroughLayerResumeFB", (PFN_xrVoidFunction*)&tableXr.PassthroughLayerResumeFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrPassthroughLayerSetKeyboardHandsIntensityFB", (PFN_xrVoidFunction*)&tableXr.PassthroughLayerSetKeyboardHandsIntensityFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrPassthroughLayerSetStyleFB", (PFN_xrVoidFunction*)&tableXr.PassthroughLayerSetStyleFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrPassthroughPauseFB", (PFN_xrVoidFunction*)&tableXr.PassthroughPauseFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrPassthroughStartFB", (PFN_xrVoidFunction*)&tableXr.PassthroughStartFB);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrPerfSettingsSetPerformanceLevelEXT", (PFN_xrVoidFunction*)&tableXr.PerfSettingsSetPerformanceLevelEXT);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrPollFutureEXT", (PFN_xrVoidFunction*)&tableXr.PollFutureEXT);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrQueryPerformanceMetricsCounterMETA", (PFN_xrVoidFunction*)&tableXr.QueryPerformanceMetricsCounterMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrQuerySpacesFB", (PFN_xrVoidFunction*)&tableXr.QuerySpacesFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrQuerySystemTrackedKeyboardFB", (PFN_xrVoidFunction*)&tableXr.QuerySystemTrackedKeyboardFB);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrRequestDisplayRefreshRateFB", (PFN_xrVoidFunction*)&tableXr.RequestDisplayRefreshRateFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrRequestExitSession", (PFN_xrVoidFunction*)&tableXr.RequestExitSession);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrRequestSceneCaptureFB", (PFN_xrVoidFunction*)&tableXr.RequestSceneCaptureFB);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrRetrieveSpaceQueryResultsFB", (PFN_xrVoidFunction*)&tableXr.RetrieveSpaceQueryResultsFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSaveSpaceFB", (PFN_xrVoidFunction*)&tableXr.SaveSpaceFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSaveSpaceListFB", (PFN_xrVoidFunction*)&tableXr.SaveSpaceListFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSendVirtualKeyboardInputMETA", (PFN_xrVoidFunction*)&tableXr.SendVirtualKeyboardInputMETA);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrSetColorSpaceFB", (PFN_xrVoidFunction*)&tableXr.SetColorSpaceFB);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrSetDigitalLensControlALMALENCE", (PFN_xrVoidFunction*)&tableXr.SetDigitalLensControlALMALENCE);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrSetInputDeviceActiveEXT", (PFN_xrVoidFunction*)&tableXr.SetInputDeviceActiveEXT);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSetInputDeviceLocationEXT", (PFN_xrVoidFunction*)&tableXr.SetInputDeviceLocationEXT);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSetInputDeviceStateBoolEXT", (PFN_xrVoidFunction*)&tableXr.SetInputDeviceStateBoolEXT);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSetInputDeviceStateFloatEXT", (PFN_xrVoidFunction*)&tableXr.SetInputDeviceStateFloatEXT);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSetInputDeviceStateVector2fEXT", (PFN_xrVoidFunction*)&tableXr.SetInputDeviceStateVector2fEXT);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSetPerformanceMetricsStateMETA", (PFN_xrVoidFunction*)&tableXr.SetPerformanceMetricsStateMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSetSpaceComponentStatusFB", (PFN_xrVoidFunction*)&tableXr.SetSpaceComponentStatusFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSetTrackingOptimizationSettingsHintQCOM", (PFN_xrVoidFunction*)&tableXr.SetTrackingOptimizationSettingsHintQCOM);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSetVirtualKeyboardModelVisibilityMETA", (PFN_xrVoidFunction*)&tableXr.SetVirtualKeyboardModelVisibilityMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrShareSpacesFB", (PFN_xrVoidFunction*)&tableXr.ShareSpacesFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrShareSpacesMETA", (PFN_xrVoidFunction*)&tableXr.ShareSpacesMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrStartColocationAdvertisementMETA", (PFN_xrVoidFunction*)&tableXr.StartColocationAdvertisementMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrStartColocationDiscoveryMETA", (PFN_xrVoidFunction*)&tableXr.StartColocationDiscoveryMETA);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrStopColocationAdvertisementMETA", (PFN_xrVoidFunction*)&tableXr.StopColocationAdvertisementMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrStopColocationDiscoveryMETA", (PFN_xrVoidFunction*)&tableXr.StopColocationDiscoveryMETA);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrSuggestVirtualKeyboardLocationMETA", (PFN_xrVoidFunction*)&tableXr.SuggestVirtualKeyboardLocationMETA);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrThermalGetTemperatureTrendEXT", (PFN_xrVoidFunction*)&tableXr.ThermalGetTemperatureTrendEXT);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrTriangleMeshBeginUpdateFB", (PFN_xrVoidFunction*)&tableXr.TriangleMeshBeginUpdateFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrTriangleMeshBeginVertexBufferUpdateFB", (PFN_xrVoidFunction*)&tableXr.TriangleMeshBeginVertexBufferUpdateFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrTriangleMeshEndUpdateFB", (PFN_xrVoidFunction*)&tableXr.TriangleMeshEndUpdateFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrTriangleMeshEndVertexBufferUpdateFB", (PFN_xrVoidFunction*)&tableXr.TriangleMeshEndVertexBufferUpdateFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrTriangleMeshGetIndexBufferFB", (PFN_xrVoidFunction*)&tableXr.TriangleMeshGetIndexBufferFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrTriangleMeshGetVertexBufferFB", (PFN_xrVoidFunction*)&tableXr.TriangleMeshGetVertexBufferFB);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrUpdatePassthroughColorLutMETA", (PFN_xrVoidFunction*)&tableXr.UpdatePassthroughColorLutMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrUpdateSwapchainFB", (PFN_xrVoidFunction*)&tableXr.UpdateSwapchainFB);

  // openxr_loader_negotiation

  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateApiLayerInstance", (PFN_xrVoidFunction*)&tableXr.CreateApiLayerInstance);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrNegotiateLoaderApiLayerInterface", (PFN_xrVoidFunction*)&tableXr.NegotiateLoaderApiLayerInterface);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrNegotiateLoaderRuntimeInterface", (PFN_xrVoidFunction*)&tableXr.NegotiateLoaderRuntimeInterface);

  // openxr_platform

  tableXr.GetInstanceProcAddr(gXrInstance, "xrConvertTimeToTimespecTimeKHR", (PFN_xrVoidFunction*)&tableXr.ConvertTimeToTimespecTimeKHR);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrConvertTimespecTimeToTimeKHR", (PFN_xrVoidFunction*)&tableXr.ConvertTimespecTimeToTimeKHR);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateSwapchainAndroidSurfaceKHR", (PFN_xrVoidFunction*)&tableXr.CreateSwapchainAndroidSurfaceKHR);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetVulkanDeviceExtensionsKHR", (PFN_xrVoidFunction*)&tableXr.GetVulkanDeviceExtensionsKHR);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetVulkanGraphicsDeviceKHR", (PFN_xrVoidFunction*)&tableXr.GetVulkanGraphicsDeviceKHR);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetVulkanGraphicsRequirementsKHR", (PFN_xrVoidFunction*)&tableXr.GetVulkanGraphicsRequirementsKHR);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetVulkanInstanceExtensionsKHR", (PFN_xrVoidFunction*)&tableXr.GetVulkanInstanceExtensionsKHR);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSetAndroidApplicationThreadKHR", (PFN_xrVoidFunction*)&tableXr.SetAndroidApplicationThreadKHR);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateEventChannelEXTX1", (PFN_xrVoidFunction*)&tableXr.CreateEventChannelEXTX1);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyEventChannelEXTX1", (PFN_xrVoidFunction*)&tableXr.DestroyEventChannelEXTX1);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrPollEventChannelEXTX1", (PFN_xrVoidFunction*)&tableXr.PollEventChannelEXTX1);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSelectEventChannelEXTX1", (PFN_xrVoidFunction*)&tableXr.SelectEventChannelEXTX1);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSetDefaultEventChannelEXTX1", (PFN_xrVoidFunction*)&tableXr.SetDefaultEventChannelEXTX1);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrSuggestBodyTrackingCalibrationOverrideMETA", (PFN_xrVoidFunction*)&tableXr.SuggestBodyTrackingCalibrationOverrideMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrResetBodyTrackingCalibrationMETA", (PFN_xrVoidFunction*)&tableXr.ResetBodyTrackingCalibrationMETA);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrRequestBodyTrackingFidelityMETA", (PFN_xrVoidFunction*)&tableXr.RequestBodyTrackingFidelityMETA);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrRequestBoundaryVisibilityMETA", (PFN_xrVoidFunction*)&tableXr.RequestBoundaryVisibilityMETA);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrCreateDynamicObjectTrackerMETA", (PFN_xrVoidFunction*)&tableXr.CreateDynamicObjectTrackerMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrDestroyDynamicObjectTrackerMETA", (PFN_xrVoidFunction*)&tableXr.DestroyDynamicObjectTrackerMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrSetDynamicObjectTrackedClassesMETA", (PFN_xrVoidFunction*)&tableXr.SetDynamicObjectTrackedClassesMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetSpaceDynamicObjectDataMETA", (PFN_xrVoidFunction*)&tableXr.GetSpaceDynamicObjectDataMETA);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrResumeSimultaneousHandsAndControllersTrackingMETA", (PFN_xrVoidFunction*)&tableXr.ResumeSimultaneousHandsAndControllersTrackingMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrPauseSimultaneousHandsAndControllersTrackingMETA", (PFN_xrVoidFunction*)&tableXr.PauseSimultaneousHandsAndControllersTrackingMETA);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrDiscoverSpacesMETA", (PFN_xrVoidFunction*)&tableXr.DiscoverSpacesMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrRetrieveSpaceDiscoveryResultsMETA", (PFN_xrVoidFunction*)&tableXr.RetrieveSpaceDiscoveryResultsMETA);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrSaveSpacesMETA", (PFN_xrVoidFunction*)&tableXr.SaveSpacesMETA);
  tableXr.GetInstanceProcAddr(gXrInstance, "xrEraseSpacesMETA", (PFN_xrVoidFunction*)&tableXr.EraseSpacesMETA);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetOpenGLGraphicsRequirementsKHR", (PFN_xrVoidFunction*)&tableXr.GetOpenGLGraphicsRequirementsKHR);

  tableXr.GetInstanceProcAddr(gXrInstance, "xrGetOpenGLESGraphicsRequirementsKHR", (PFN_xrVoidFunction*)&tableXr.GetOpenGLESGraphicsRequirementsKHR);

  return 1;
}
