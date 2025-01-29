
// xr_generated_dispatch_table_core.cpp

#include "header.h"

#ifdef __cplusplus
extern "C" {
#endif

struct XrGeneratedDispatchTableCore tableXr;

#ifdef __cplusplus
}
#endif

// dispatch tableXr blah function
int InitOpenXr()
{
  void* libopenxr = 0;

  if(tableXr.GetInstanceProcAddr)
    return 1;

  libopenxr = dlopen("libopenxr_loader.so", RTLD_NOW | RTLD_LOCAL);
  if( !libopenxr)
    return 0;

  // ---- Core 1.0 commands
  tableXr.GetInstanceProcAddr = reinterpret_cast<PFN_xrGetInstanceProcAddr>(dlsym(libopenxr, "xrGetInstanceProcAddr") );

  tableXr.AcquireSwapchainImage = reinterpret_cast<PFN_xrAcquireSwapchainImage>(dlsym(libopenxr, "xrAcquireSwapchainImage") );
  tableXr.ApplyHapticFeedback = reinterpret_cast<PFN_xrApplyHapticFeedback>(dlsym(libopenxr, "xrApplyHapticFeedback") );
  tableXr.AttachSessionActionSets = reinterpret_cast<PFN_xrAttachSessionActionSets>(dlsym(libopenxr, "xrAttachSessionActionSets") );
  tableXr.BeginFrame = reinterpret_cast<PFN_xrBeginFrame>(dlsym(libopenxr, "xrBeginFrame") );
  tableXr.BeginSession = reinterpret_cast<PFN_xrBeginSession>(dlsym(libopenxr, "xrBeginSession") );
  tableXr.CreateAction = reinterpret_cast<PFN_xrCreateAction>(dlsym(libopenxr, "xrCreateAction") );
  tableXr.CreateActionSet = reinterpret_cast<PFN_xrCreateActionSet>(dlsym(libopenxr, "xrCreateActionSet") );
  tableXr.CreateActionSpace = reinterpret_cast<PFN_xrCreateActionSpace>(dlsym(libopenxr, "xrCreateActionSpace") );
  tableXr.CreateInstance = reinterpret_cast<PFN_xrCreateInstance>(dlsym(libopenxr, "xrCreateInstance") );
  tableXr.CreateReferenceSpace = reinterpret_cast<PFN_xrCreateReferenceSpace>(dlsym(libopenxr, "xrCreateReferenceSpace") );
  tableXr.CreateSession = reinterpret_cast<PFN_xrCreateSession>(dlsym(libopenxr, "xrCreateSession") );
  tableXr.CreateSwapchain = reinterpret_cast<PFN_xrCreateSwapchain>(dlsym(libopenxr, "xrCreateSwapchain") );
  tableXr.DestroyAction = reinterpret_cast<PFN_xrDestroyAction>(dlsym(libopenxr, "xrDestroyAction") );
  tableXr.DestroyActionSet = reinterpret_cast<PFN_xrDestroyActionSet>(dlsym(libopenxr, "xrDestroyActionSet") );
  tableXr.DestroyInstance = reinterpret_cast<PFN_xrDestroyInstance>(dlsym(libopenxr, "xrDestroyInstance") );
  tableXr.DestroySession = reinterpret_cast<PFN_xrDestroySession>(dlsym(libopenxr, "xrDestroySession") );
  tableXr.DestroySpace = reinterpret_cast<PFN_xrDestroySpace>(dlsym(libopenxr, "xrDestroySpace") );
  tableXr.DestroySwapchain = reinterpret_cast<PFN_xrDestroySwapchain>(dlsym(libopenxr, "xrDestroySwapchain") );
  tableXr.EndFrame = reinterpret_cast<PFN_xrEndFrame>(dlsym(libopenxr, "xrEndFrame") );
  tableXr.EndSession = reinterpret_cast<PFN_xrEndSession>(dlsym(libopenxr, "xrEndSession") );
  tableXr.EnumerateApiLayerProperties = reinterpret_cast<PFN_xrEnumerateApiLayerProperties>(dlsym(libopenxr, "xrEnumerateApiLayerProperties") );
  tableXr.EnumerateBoundSourcesForAction = reinterpret_cast<PFN_xrEnumerateBoundSourcesForAction>(dlsym(libopenxr, "xrEnumerateBoundSourcesForAction") );
  tableXr.EnumerateEnvironmentBlendModes = reinterpret_cast<PFN_xrEnumerateEnvironmentBlendModes>(dlsym(libopenxr, "xrEnumerateEnvironmentBlendModes") );
  tableXr.EnumerateInstanceExtensionProperties = reinterpret_cast<PFN_xrEnumerateInstanceExtensionProperties>(dlsym(libopenxr, "xrEnumerateInstanceExtensionProperties") );
  tableXr.EnumerateReferenceSpaces = reinterpret_cast<PFN_xrEnumerateReferenceSpaces>(dlsym(libopenxr, "xrEnumerateReferenceSpaces") );
  tableXr.EnumerateSwapchainFormats = reinterpret_cast<PFN_xrEnumerateSwapchainFormats>(dlsym(libopenxr, "xrEnumerateSwapchainFormats") );
  tableXr.EnumerateSwapchainImages = reinterpret_cast<PFN_xrEnumerateSwapchainImages>(dlsym(libopenxr, "xrEnumerateSwapchainImages") );
  tableXr.EnumerateViewConfigurationViews = reinterpret_cast<PFN_xrEnumerateViewConfigurationViews>(dlsym(libopenxr, "xrEnumerateViewConfigurationViews") );
  tableXr.EnumerateViewConfigurations = reinterpret_cast<PFN_xrEnumerateViewConfigurations>(dlsym(libopenxr, "xrEnumerateViewConfigurations") );
  tableXr.GetActionStateBoolean = reinterpret_cast<PFN_xrGetActionStateBoolean>(dlsym(libopenxr, "xrGetActionStateBoolean") );
  tableXr.GetActionStateFloat = reinterpret_cast<PFN_xrGetActionStateFloat>(dlsym(libopenxr, "xrGetActionStateFloat") );
  tableXr.GetActionStatePose = reinterpret_cast<PFN_xrGetActionStatePose>(dlsym(libopenxr, "xrGetActionStatePose") );
  tableXr.GetActionStateVector2f = reinterpret_cast<PFN_xrGetActionStateVector2f>(dlsym(libopenxr, "xrGetActionStateVector2f") );
  tableXr.GetCurrentInteractionProfile = reinterpret_cast<PFN_xrGetCurrentInteractionProfile>(dlsym(libopenxr, "xrGetCurrentInteractionProfile") );
  tableXr.GetInputSourceLocalizedName = reinterpret_cast<PFN_xrGetInputSourceLocalizedName>(dlsym(libopenxr, "xrGetInputSourceLocalizedName") );

  tableXr.GetInstanceProperties = reinterpret_cast<PFN_xrGetInstanceProperties>(dlsym(libopenxr, "xrGetInstanceProperties") );
  tableXr.GetReferenceSpaceBoundsRect = reinterpret_cast<PFN_xrGetReferenceSpaceBoundsRect>(dlsym(libopenxr, "xrGetReferenceSpaceBoundsRect") );
  tableXr.GetSystem = reinterpret_cast<PFN_xrGetSystem>(dlsym(libopenxr, "xrGetSystem") );
  tableXr.GetSystemProperties = reinterpret_cast<PFN_xrGetSystemProperties>(dlsym(libopenxr, "xrGetSystemProperties") );
  tableXr.GetViewConfigurationProperties = reinterpret_cast<PFN_xrGetViewConfigurationProperties>(dlsym(libopenxr, "xrGetViewConfigurationProperties") );
  tableXr.LocateSpace = reinterpret_cast<PFN_xrLocateSpace>(dlsym(libopenxr, "xrLocateSpace") );
  tableXr.LocateViews = reinterpret_cast<PFN_xrLocateViews>(dlsym(libopenxr, "xrLocateViews") );
  tableXr.PathToString = reinterpret_cast<PFN_xrPathToString>(dlsym(libopenxr, "xrPathToString") );
  tableXr.PollEvent = reinterpret_cast<PFN_xrPollEvent>(dlsym(libopenxr, "xrPollEvent") );
  tableXr.ReleaseSwapchainImage = reinterpret_cast<PFN_xrReleaseSwapchainImage>(dlsym(libopenxr, "xrReleaseSwapchainImage") );
  tableXr.RequestExitSession = reinterpret_cast<PFN_xrRequestExitSession>(dlsym(libopenxr, "xrRequestExitSession") );
  tableXr.ResultToString = reinterpret_cast<PFN_xrResultToString>(dlsym(libopenxr, "xrResultToString") );
  tableXr.StopHapticFeedback = reinterpret_cast<PFN_xrStopHapticFeedback>(dlsym(libopenxr, "xrStopHapticFeedback") );
  tableXr.StringToPath = reinterpret_cast<PFN_xrStringToPath>(dlsym(libopenxr, "xrStringToPath") );
  tableXr.StructureTypeToString = reinterpret_cast<PFN_xrStructureTypeToString>(dlsym(libopenxr, "xrStructureTypeToString") );
  tableXr.SuggestInteractionProfileBindings = reinterpret_cast<PFN_xrSuggestInteractionProfileBindings>(dlsym(libopenxr, "xrSuggestInteractionProfileBindings") );
  tableXr.SyncActions = reinterpret_cast<PFN_xrSyncActions>(dlsym(libopenxr, "xrSyncActions") );
  tableXr.WaitFrame = reinterpret_cast<PFN_xrWaitFrame>(dlsym(libopenxr, "xrWaitFrame") );
  tableXr.WaitSwapchainImage = reinterpret_cast<PFN_xrWaitSwapchainImage>(dlsym(libopenxr, "xrWaitSwapchainImage") );

  // ---- Core 1.1 commands
  tableXr.LocateSpaces = reinterpret_cast<PFN_xrLocateSpaces>(dlsym(libopenxr, "xrLocateSpaces") );

  // ---- XR_EXT_debug_utils extension commands
  tableXr.CreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_xrCreateDebugUtilsMessengerEXT>(dlsym(libopenxr, "xrCreateDebugUtilsMessengerEXT") );
  tableXr.DestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_xrDestroyDebugUtilsMessengerEXT>(dlsym(libopenxr, "xrDestroyDebugUtilsMessengerEXT") );
  tableXr.SessionBeginDebugUtilsLabelRegionEXT = reinterpret_cast<PFN_xrSessionBeginDebugUtilsLabelRegionEXT>(dlsym(libopenxr, "xrSessionBeginDebugUtilsLabelRegionEXT") );
  tableXr.SessionEndDebugUtilsLabelRegionEXT = reinterpret_cast<PFN_xrSessionEndDebugUtilsLabelRegionEXT>(dlsym(libopenxr, "xrSessionEndDebugUtilsLabelRegionEXT") );
  tableXr.SessionInsertDebugUtilsLabelEXT = reinterpret_cast<PFN_xrSessionInsertDebugUtilsLabelEXT>(dlsym(libopenxr, "xrSessionInsertDebugUtilsLabelEXT") );
  tableXr.SetDebugUtilsObjectNameEXT = reinterpret_cast<PFN_xrSetDebugUtilsObjectNameEXT>(dlsym(libopenxr, "xrSetDebugUtilsObjectNameEXT") );
  tableXr.SubmitDebugUtilsMessageEXT = reinterpret_cast<PFN_xrSubmitDebugUtilsMessageEXT>(dlsym(libopenxr, "xrSubmitDebugUtilsMessageEXT") );

  return 1;
}
