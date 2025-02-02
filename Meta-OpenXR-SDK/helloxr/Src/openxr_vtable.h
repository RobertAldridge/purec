
// openxr_vtable.h

struct XrGeneratedDispatchTableCore
{
  // ---- Core 1.0 commands
  PFN_xrGetInstanceProcAddr GetInstanceProcAddr;

  PFN_xrAcquireSwapchainImage AcquireSwapchainImage;
  PFN_xrApplyHapticFeedback ApplyHapticFeedback;
  PFN_xrAttachSessionActionSets AttachSessionActionSets;
  PFN_xrBeginFrame BeginFrame;
  PFN_xrBeginSession BeginSession;
  PFN_xrCreateAction CreateAction;
  PFN_xrCreateActionSet CreateActionSet;
  PFN_xrCreateActionSpace CreateActionSpace;
  PFN_xrCreateInstance CreateInstance;
  PFN_xrCreateReferenceSpace CreateReferenceSpace;
  PFN_xrCreateSession CreateSession;
  PFN_xrCreateSwapchain CreateSwapchain;
  PFN_xrDestroyAction DestroyAction;
  PFN_xrDestroyActionSet DestroyActionSet;
  PFN_xrDestroyInstance DestroyInstance;
  PFN_xrDestroySession DestroySession;
  PFN_xrDestroySpace DestroySpace;
  PFN_xrDestroySwapchain DestroySwapchain;
  PFN_xrEndFrame EndFrame;
  PFN_xrEndSession EndSession;
  PFN_xrEnumerateApiLayerProperties EnumerateApiLayerProperties;
  PFN_xrEnumerateBoundSourcesForAction EnumerateBoundSourcesForAction;
  PFN_xrEnumerateEnvironmentBlendModes EnumerateEnvironmentBlendModes;
  PFN_xrEnumerateInstanceExtensionProperties EnumerateInstanceExtensionProperties;
  PFN_xrEnumerateReferenceSpaces EnumerateReferenceSpaces;
  PFN_xrEnumerateSwapchainFormats EnumerateSwapchainFormats;
  PFN_xrEnumerateSwapchainImages EnumerateSwapchainImages;
  PFN_xrEnumerateViewConfigurationViews EnumerateViewConfigurationViews;
  PFN_xrEnumerateViewConfigurations EnumerateViewConfigurations;
  PFN_xrGetActionStateBoolean GetActionStateBoolean;
  PFN_xrGetActionStateFloat GetActionStateFloat;
  PFN_xrGetActionStatePose GetActionStatePose;
  PFN_xrGetActionStateVector2f GetActionStateVector2f;
  PFN_xrGetCurrentInteractionProfile GetCurrentInteractionProfile;
  PFN_xrGetInputSourceLocalizedName GetInputSourceLocalizedName;

  PFN_xrGetInstanceProperties GetInstanceProperties;
  PFN_xrGetReferenceSpaceBoundsRect GetReferenceSpaceBoundsRect;
  PFN_xrGetSystem GetSystem;
  PFN_xrGetSystemProperties GetSystemProperties;
  PFN_xrGetViewConfigurationProperties GetViewConfigurationProperties;
  PFN_xrLocateSpace LocateSpace;
  PFN_xrLocateViews LocateViews;
  PFN_xrPathToString PathToString;
  PFN_xrPollEvent PollEvent;
  PFN_xrReleaseSwapchainImage ReleaseSwapchainImage;
  PFN_xrRequestExitSession RequestExitSession;
  PFN_xrResultToString ResultToString;
  PFN_xrStopHapticFeedback StopHapticFeedback;
  PFN_xrStringToPath StringToPath;
  PFN_xrStructureTypeToString StructureTypeToString;
  PFN_xrSuggestInteractionProfileBindings SuggestInteractionProfileBindings;
  PFN_xrSyncActions SyncActions;
  PFN_xrWaitFrame WaitFrame;
  PFN_xrWaitSwapchainImage WaitSwapchainImage;

  // ---- Core 1.1 commands
  PFN_xrLocateSpaces LocateSpaces;

  // ---- XR_EXT_debug_utils extension commands
  PFN_xrCreateDebugUtilsMessengerEXT CreateDebugUtilsMessengerEXT;
  PFN_xrDestroyDebugUtilsMessengerEXT DestroyDebugUtilsMessengerEXT;
  PFN_xrSessionBeginDebugUtilsLabelRegionEXT SessionBeginDebugUtilsLabelRegionEXT;
  PFN_xrSessionEndDebugUtilsLabelRegionEXT SessionEndDebugUtilsLabelRegionEXT;
  PFN_xrSessionInsertDebugUtilsLabelEXT SessionInsertDebugUtilsLabelEXT;
  PFN_xrSetDebugUtilsObjectNameEXT SetDebugUtilsObjectNameEXT;
  PFN_xrSubmitDebugUtilsMessageEXT SubmitDebugUtilsMessageEXT;

#if 0
  // openxr.h

  PFN_xrVoidFunction;

  PFN_xrDebugUtilsMessengerCallbackEXT;

  PFN_xrAcquireEnvironmentDepthImageMETA;
  PFN_xrAcquireSwapchainImage;
  PFN_xrApplyForceFeedbackCurlMNDX;
  PFN_xrApplyHapticFeedback;
  PFN_xrAttachSessionActionSets;
  PFN_xrBeginFrame;
  PFN_xrBeginPlaneDetectionEXT;
  PFN_xrBeginSession;
  PFN_xrCancelFutureEXT;
  PFN_xrChangeVirtualKeyboardTextContextMETA;
  PFN_xrCreateAction;
  PFN_xrCreateActionSet;
  PFN_xrCreateActionSpace;
  PFN_xrCreateBodyTrackerFB;
  PFN_xrCreateDebugUtilsMessengerEXT;
  PFN_xrCreateEnvironmentDepthProviderMETA;
  PFN_xrCreateEnvironmentDepthSwapchainMETA;
  PFN_xrCreateEyeTrackerFB
  PFN_xrCreateFaceTracker2FB
  PFN_xrCreateFaceTrackerFB
  PFN_xrCreateFoveationProfileFB
  PFN_xrCreateGeometryInstanceFB
  PFN_xrCreateHandTrackerEXT
  PFN_xrCreateInstance
  PFN_xrCreateKeyboardSpaceFB
  PFN_xrCreatePassthroughColorLutMETA
  PFN_xrCreatePassthroughFB
  PFN_xrCreatePassthroughLayerFB
  PFN_xrCreatePlaneDetectorEXT
  PFN_xrCreateReferenceSpace
  PFN_xrCreateSession
  PFN_xrCreateSpaceUserFB
  PFN_xrCreateSpatialAnchorFB
  PFN_xrCreateSwapchain
  PFN_xrCreateTriangleMeshFB
  PFN_xrCreateVirtualKeyboardMETA
  PFN_xrCreateVirtualKeyboardSpaceMETA
  PFN_xrDestroyAction
  PFN_xrDestroyActionSet
  PFN_xrDestroyBodyTrackerFB
  PFN_xrDestroyDebugUtilsMessengerEXT
  PFN_xrDestroyEnvironmentDepthProviderMETA
  PFN_xrDestroyEnvironmentDepthSwapchainMETA
  PFN_xrDestroyEyeTrackerFB
  PFN_xrDestroyFaceTracker2FB
  PFN_xrDestroyFaceTrackerFB
  PFN_xrDestroyFoveationProfileFB
  PFN_xrDestroyGeometryInstanceFB
  PFN_xrDestroyHandTrackerEXT
  PFN_xrDestroyInstance
  PFN_xrDestroyPassthroughColorLutMETA
  PFN_xrDestroyPassthroughFB
  PFN_xrDestroyPassthroughLayerFB
  PFN_xrDestroyPlaneDetectorEXT
  PFN_xrDestroySession
  PFN_xrDestroySpace
  PFN_xrDestroySpaceUserFB
  PFN_xrDestroySwapchain
  PFN_xrDestroyTriangleMeshFB
  PFN_xrDestroyVirtualKeyboardMETA
  PFN_xrEndFrame
  PFN_xrEndSession
  PFN_xrEnumerateApiLayerProperties
  PFN_xrEnumerateBoundSourcesForAction
  PFN_xrEnumerateColorSpacesFB
  PFN_xrEnumerateDisplayRefreshRatesFB
  PFN_xrEnumerateEnvironmentBlendModes
  PFN_xrEnumerateEnvironmentDepthSwapchainImagesMETA
  PFN_xrEnumerateExternalCamerasOCULUS
  PFN_xrEnumerateInstanceExtensionProperties
  PFN_xrEnumeratePerformanceMetricsCounterPathsMETA
  PFN_xrEnumerateReferenceSpaces
  PFN_xrEnumerateRenderModelPathsFB
  PFN_xrEnumerateSpaceSupportedComponentsFB
  PFN_xrEnumerateSwapchainFormats
  PFN_xrEnumerateSwapchainImages
  PFN_xrEnumerateViewConfigurationViews
  PFN_xrEnumerateViewConfigurations
  PFN_xrEraseSpaceFB
  PFN_xrGeometryInstanceSetTransformFB
  PFN_xrGetActionStateBoolean
  PFN_xrGetActionStateFloat
  PFN_xrGetActionStatePose
  PFN_xrGetActionStateVector2f
  PFN_xrGetBodySkeletonFB
  PFN_xrGetCurrentInteractionProfile
  PFN_xrGetDeviceSampleRateFB
  PFN_xrGetDisplayRefreshRateFB
  PFN_xrGetEnvironmentDepthSwapchainStateMETA
  PFN_xrGetEyeGazesFB
  PFN_xrGetFaceExpressionWeights2FB
  PFN_xrGetFaceExpressionWeightsFB
  PFN_xrGetFoveationEyeTrackedStateMETA
  PFN_xrGetHandMeshFB
  PFN_xrGetInputSourceLocalizedName
  PFN_xrGetInstanceProcAddr
  PFN_xrGetInstanceProperties
  PFN_xrGetPassthroughPreferencesMETA
  PFN_xrGetPerformanceMetricsStateMETA
  PFN_xrGetPlaneDetectionStateEXT
  PFN_xrGetPlaneDetectionsEXT
  PFN_xrGetPlanePolygonBufferEXT
  PFN_xrGetRecommendedLayerResolutionMETA
  PFN_xrGetReferenceSpaceBoundsRect
  PFN_xrGetRenderModelPropertiesFB
  PFN_xrGetSpaceBoundary2DFB
  PFN_xrGetSpaceBoundingBox2DFB
  PFN_xrGetSpaceBoundingBox3DFB
  PFN_xrGetSpaceComponentStatusFB
  PFN_xrGetSpaceContainerFB
  PFN_xrGetSpaceRoomLayoutFB
  PFN_xrGetSpaceSemanticLabelsFB
  PFN_xrGetSpaceTriangleMeshMETA
  PFN_xrGetSpaceUserIdFB
  PFN_xrGetSpaceUuidFB
  PFN_xrGetSwapchainStateFB
  PFN_xrGetSystem
  PFN_xrGetSystemProperties
  PFN_xrGetViewConfigurationProperties
  PFN_xrGetVirtualKeyboardDirtyTexturesMETA
  PFN_xrGetVirtualKeyboardModelAnimationStatesMETA
  PFN_xrGetVirtualKeyboardScaleMETA
  PFN_xrGetVirtualKeyboardTextureDataMETA
  PFN_xrGetVisibilityMaskKHR
  PFN_xrInitializeLoaderKHR
  PFN_xrLoadRenderModelFB
  PFN_xrLocateBodyJointsFB
  PFN_xrLocateHandJointsEXT
  PFN_xrLocateSpace
  PFN_xrLocateSpaces
  PFN_xrLocateSpacesKHR
  PFN_xrLocateViews
  PFN_xrPassthroughLayerPauseFB
  PFN_xrPassthroughLayerResumeFB
  PFN_xrPassthroughLayerSetKeyboardHandsIntensityFB
  PFN_xrPassthroughLayerSetStyleFB
  PFN_xrPassthroughPauseFB
  PFN_xrPassthroughStartFB
  PFN_xrPathToString
  PFN_xrPerfSettingsSetPerformanceLevelEXT
  PFN_xrPollEvent
  PFN_xrPollFutureEXT
  PFN_xrQueryPerformanceMetricsCounterMETA
  PFN_xrQuerySpacesFB
  PFN_xrQuerySystemTrackedKeyboardFB
  PFN_xrReleaseSwapchainImage
  PFN_xrRequestDisplayRefreshRateFB
  PFN_xrRequestExitSession
  PFN_xrRequestSceneCaptureFB
  PFN_xrResultToString
  PFN_xrRetrieveSpaceQueryResultsFB
  PFN_xrSaveSpaceFB
  PFN_xrSaveSpaceListFB
  PFN_xrSendVirtualKeyboardInputMETA
  PFN_xrSessionBeginDebugUtilsLabelRegionEXT
  PFN_xrSessionEndDebugUtilsLabelRegionEXT
  PFN_xrSessionInsertDebugUtilsLabelEXT
  PFN_xrSetColorSpaceFB
  PFN_xrSetDebugUtilsObjectNameEXT
  PFN_xrSetDigitalLensControlALMALENCE
  PFN_xrSetEnvironmentDepthHandRemovalMETA
  PFN_xrSetInputDeviceActiveEXT
  PFN_xrSetInputDeviceLocationEXT
  PFN_xrSetInputDeviceStateBoolEXT
  PFN_xrSetInputDeviceStateFloatEXT
  PFN_xrSetInputDeviceStateVector2fEXT
  PFN_xrSetPerformanceMetricsStateMETA
  PFN_xrSetSpaceComponentStatusFB
  PFN_xrSetTrackingOptimizationSettingsHintQCOM
  PFN_xrSetVirtualKeyboardModelVisibilityMETA
  PFN_xrShareSpacesFB
  PFN_xrShareSpacesMETA
  PFN_xrStartColocationAdvertisementMETA
  PFN_xrStartColocationDiscoveryMETA
  PFN_xrStartEnvironmentDepthProviderMETA
  PFN_xrStopColocationAdvertisementMETA
  PFN_xrStopColocationDiscoveryMETA
  PFN_xrStopEnvironmentDepthProviderMETA
  PFN_xrStopHapticFeedback
  PFN_xrStringToPath
  PFN_xrStructureTypeToString
  PFN_xrSubmitDebugUtilsMessageEXT
  PFN_xrSuggestInteractionProfileBindings
  PFN_xrSuggestVirtualKeyboardLocationMETA
  PFN_xrSyncActions
  PFN_xrThermalGetTemperatureTrendEXT
  PFN_xrTriangleMeshBeginUpdateFB
  PFN_xrTriangleMeshBeginVertexBufferUpdateFB
  PFN_xrTriangleMeshEndUpdateFB
  PFN_xrTriangleMeshEndVertexBufferUpdateFB
  PFN_xrTriangleMeshGetIndexBufferFB
  PFN_xrTriangleMeshGetVertexBufferFB
  PFN_xrUpdatePassthroughColorLutMETA
  PFN_xrUpdateSwapchainFB
  PFN_xrWaitFrame
  PFN_xrWaitSwapchainImage

  // openxr_loader_negotiation

  PFN_xrCreateApiLayerInstance
  PFN_xrCreateApiLayerInstance
  PFN_xrGetInstanceProcAddr
  PFN_xrNegotiateLoaderApiLayerInterface
  PFN_xrNegotiateLoaderRuntimeInterface

  // openxr_platform

  PFN_xrConvertTimeToTimespecTimeKHR
  PFN_xrConvertTimespecTimeToTimeKHR
  PFN_xrCreateSwapchainAndroidSurfaceKHR
  PFN_xrCreateVulkanDeviceKHR
  PFN_xrCreateVulkanInstanceKHR
  PFN_xrGetVulkanDeviceExtensionsKHR
  PFN_xrGetVulkanGraphicsDevice2KHR
  PFN_xrGetVulkanGraphicsDeviceKHR
  PFN_xrGetVulkanGraphicsRequirements2KHR
  PFN_xrGetVulkanGraphicsRequirementsKHR
  PFN_xrGetVulkanInstanceExtensionsKHR
  PFN_xrSetAndroidApplicationThreadKHR
#endif
};

int InitOpenXr();
