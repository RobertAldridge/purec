
// openxr_vtable.h

struct XrGraphicsRequirementsOpenGLKHR
{
  XrStructureType type;
  void* XR_MAY_ALIAS next;
  XrVersion minApiVersionSupported;
  XrVersion maxApiVersionSupported;
};

struct XrGraphicsRequirementsOpenGLESKHR
{
  XrStructureType type;
  void* XR_MAY_ALIAS next;
  XrVersion minApiVersionSupported;
  XrVersion maxApiVersionSupported;
};

typedef XrResult (XRAPI_PTR *PFN_xrGetOpenGLGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLKHR* graphicsRequirements);

typedef XrResult (XRAPI_PTR *PFN_xrGetOpenGLESGraphicsRequirementsKHR)(XrInstance instance, XrSystemId systemId, XrGraphicsRequirementsOpenGLESKHR* graphicsRequirements);

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

  PFN_xrInitializeLoaderKHR InitializeLoaderKHR;

  PFN_xrGetVulkanGraphicsRequirements2KHR GetVulkanGraphicsRequirements2KHR;
  PFN_xrCreateVulkanInstanceKHR CreateVulkanInstanceKHR;
  PFN_xrGetVulkanGraphicsDevice2KHR GetVulkanGraphicsDevice2KHR;
  PFN_xrCreateVulkanDeviceKHR CreateVulkanDeviceKHR;

  PFN_xrCreatePassthroughFB CreatePassthroughFB;
  PFN_xrCreatePassthroughLayerFB CreatePassthroughLayerFB;

  PFN_xrCreateEnvironmentDepthProviderMETA CreateEnvironmentDepthProviderMETA;
  PFN_xrDestroyEnvironmentDepthProviderMETA DestroyEnvironmentDepthProviderMETA;
  PFN_xrStartEnvironmentDepthProviderMETA StartEnvironmentDepthProviderMETA;
  PFN_xrStopEnvironmentDepthProviderMETA StopEnvironmentDepthProviderMETA;
  PFN_xrCreateEnvironmentDepthSwapchainMETA CreateEnvironmentDepthSwapchainMETA;
  PFN_xrDestroyEnvironmentDepthSwapchainMETA DestroyEnvironmentDepthSwapchainMETA;
  PFN_xrEnumerateEnvironmentDepthSwapchainImagesMETA EnumerateEnvironmentDepthSwapchainImagesMETA;
  PFN_xrGetEnvironmentDepthSwapchainStateMETA GetEnvironmentDepthSwapchainStateMETA;
  PFN_xrAcquireEnvironmentDepthImageMETA AcquireEnvironmentDepthImageMETA;
  PFN_xrSetEnvironmentDepthHandRemovalMETA SetEnvironmentDepthHandRemovalMETA;

  // openxr.h

  PFN_xrVoidFunction VoidFunction;

  PFN_xrDebugUtilsMessengerCallbackEXT DebugUtilsMessengerCallbackEXT;

  PFN_xrApplyForceFeedbackCurlMNDX ApplyForceFeedbackCurlMNDX;

  PFN_xrBeginPlaneDetectionEXT BeginPlaneDetectionEXT;

  PFN_xrCancelFutureEXT CancelFutureEXT;
  PFN_xrChangeVirtualKeyboardTextContextMETA ChangeVirtualKeyboardTextContextMETA;

  PFN_xrCreateBodyTrackerFB CreateBodyTrackerFB;

  PFN_xrCreateEyeTrackerFB CreateEyeTrackerFB;
  PFN_xrCreateFaceTracker2FB CreateFaceTracker2FB;
  PFN_xrCreateFaceTrackerFB CreateFaceTrackerFB;
  PFN_xrCreateFoveationProfileFB CreateFoveationProfileFB;
  PFN_xrCreateGeometryInstanceFB CreateGeometryInstanceFB;
  PFN_xrCreateHandTrackerEXT CreateHandTrackerEXT;

  PFN_xrCreateKeyboardSpaceFB CreateKeyboardSpaceFB;
  PFN_xrCreatePassthroughColorLutMETA CreatePassthroughColorLutMETA;

  PFN_xrCreatePlaneDetectorEXT CreatePlaneDetectorEXT;

  PFN_xrCreateSpaceUserFB CreateSpaceUserFB;
  PFN_xrCreateSpatialAnchorFB CreateSpatialAnchorFB;

  PFN_xrCreateTriangleMeshFB CreateTriangleMeshFB;
  PFN_xrCreateVirtualKeyboardMETA CreateVirtualKeyboardMETA;
  PFN_xrCreateVirtualKeyboardSpaceMETA CreateVirtualKeyboardSpaceMETA;

  PFN_xrDestroyBodyTrackerFB DestroyBodyTrackerFB;

  PFN_xrDestroyEyeTrackerFB DestroyEyeTrackerFB;
  PFN_xrDestroyFaceTracker2FB DestroyFaceTracker2FB;
  PFN_xrDestroyFaceTrackerFB DestroyFaceTrackerFB;
  PFN_xrDestroyFoveationProfileFB DestroyFoveationProfileFB;
  PFN_xrDestroyGeometryInstanceFB DestroyGeometryInstanceFB;
  PFN_xrDestroyHandTrackerEXT DestroyHandTrackerEXT;

  PFN_xrDestroyPassthroughColorLutMETA DestroyPassthroughColorLutMETA;
  PFN_xrDestroyPassthroughFB DestroyPassthroughFB;
  PFN_xrDestroyPassthroughLayerFB DestroyPassthroughLayerFB;
  PFN_xrDestroyPlaneDetectorEXT DestroyPlaneDetectorEXT;

  PFN_xrDestroySpaceUserFB DestroySpaceUserFB;

  PFN_xrDestroyTriangleMeshFB DestroyTriangleMeshFB;
  PFN_xrDestroyVirtualKeyboardMETA DestroyVirtualKeyboardMETA;

  PFN_xrEnumerateColorSpacesFB EnumerateColorSpacesFB;
  PFN_xrEnumerateDisplayRefreshRatesFB EnumerateDisplayRefreshRatesFB;

  PFN_xrEnumerateExternalCamerasOCULUS EnumerateExternalCamerasOCULUS;

  PFN_xrEnumeratePerformanceMetricsCounterPathsMETA EnumeratePerformanceMetricsCounterPathsMETA;

  PFN_xrEnumerateRenderModelPathsFB EnumerateRenderModelPathsFB;
  PFN_xrEnumerateSpaceSupportedComponentsFB EnumerateSpaceSupportedComponentsFB;

  PFN_xrEraseSpaceFB EraseSpaceFB;
  PFN_xrGeometryInstanceSetTransformFB GeometryInstanceSetTransformFB;

  PFN_xrGetBodySkeletonFB GetBodySkeletonFB;

  PFN_xrGetDeviceSampleRateFB GetDeviceSampleRateFB;
  PFN_xrGetDisplayRefreshRateFB GetDisplayRefreshRateFB;

  PFN_xrGetEyeGazesFB GetEyeGazesFB;
  PFN_xrGetFaceExpressionWeights2FB GetFaceExpressionWeights2FB;
  PFN_xrGetFaceExpressionWeightsFB GetFaceExpressionWeightsFB;
  PFN_xrGetFoveationEyeTrackedStateMETA GetFoveationEyeTrackedStateMETA;
  PFN_xrGetHandMeshFB GetHandMeshFB;

  PFN_xrGetPassthroughPreferencesMETA GetPassthroughPreferencesMETA;
  PFN_xrGetPerformanceMetricsStateMETA GetPerformanceMetricsStateMETA;
  PFN_xrGetPlaneDetectionStateEXT GetPlaneDetectionStateEXT;
  PFN_xrGetPlaneDetectionsEXT GetPlaneDetectionsEXT;
  PFN_xrGetPlanePolygonBufferEXT GetPlanePolygonBufferEXT;
  PFN_xrGetRecommendedLayerResolutionMETA GetRecommendedLayerResolutionMETA;

  PFN_xrGetRenderModelPropertiesFB GetRenderModelPropertiesFB;
  PFN_xrGetSpaceBoundary2DFB GetSpaceBoundary2DFB;
  PFN_xrGetSpaceBoundingBox2DFB GetSpaceBoundingBox2DFB;
  PFN_xrGetSpaceBoundingBox3DFB GetSpaceBoundingBox3DFB;
  PFN_xrGetSpaceComponentStatusFB GetSpaceComponentStatusFB;
  PFN_xrGetSpaceContainerFB GetSpaceContainerFB;
  PFN_xrGetSpaceRoomLayoutFB GetSpaceRoomLayoutFB;
  PFN_xrGetSpaceSemanticLabelsFB GetSpaceSemanticLabelsFB;
  PFN_xrGetSpaceTriangleMeshMETA GetSpaceTriangleMeshMETA;
  PFN_xrGetSpaceUserIdFB GetSpaceUserIdFB;
  PFN_xrGetSpaceUuidFB GetSpaceUuidFB;
  PFN_xrGetSwapchainStateFB GetSwapchainStateFB;

  PFN_xrGetVirtualKeyboardDirtyTexturesMETA GetVirtualKeyboardDirtyTexturesMETA;
  PFN_xrGetVirtualKeyboardModelAnimationStatesMETA GetVirtualKeyboardModelAnimationStatesMETA;
  PFN_xrGetVirtualKeyboardScaleMETA GetVirtualKeyboardScaleMETA;
  PFN_xrGetVirtualKeyboardTextureDataMETA GetVirtualKeyboardTextureDataMETA;
  PFN_xrGetVisibilityMaskKHR GetVisibilityMaskKHR;

  PFN_xrLoadRenderModelFB LoadRenderModelFB;
  PFN_xrLocateBodyJointsFB LocateBodyJointsFB;
  PFN_xrLocateHandJointsEXT LocateHandJointsEXT;

  PFN_xrLocateSpacesKHR LocateSpacesKHR;

  PFN_xrPassthroughLayerPauseFB PassthroughLayerPauseFB;
  PFN_xrPassthroughLayerResumeFB PassthroughLayerResumeFB;
  PFN_xrPassthroughLayerSetKeyboardHandsIntensityFB PassthroughLayerSetKeyboardHandsIntensityFB;
  PFN_xrPassthroughLayerSetStyleFB PassthroughLayerSetStyleFB;
  PFN_xrPassthroughPauseFB PassthroughPauseFB;
  PFN_xrPassthroughStartFB PassthroughStartFB;

  PFN_xrPerfSettingsSetPerformanceLevelEXT PerfSettingsSetPerformanceLevelEXT;

  PFN_xrPollFutureEXT PollFutureEXT;
  PFN_xrQueryPerformanceMetricsCounterMETA QueryPerformanceMetricsCounterMETA;
  PFN_xrQuerySpacesFB QuerySpacesFB;
  PFN_xrQuerySystemTrackedKeyboardFB QuerySystemTrackedKeyboardFB;

  PFN_xrRequestDisplayRefreshRateFB RequestDisplayRefreshRateFB;

  PFN_xrRequestSceneCaptureFB RequestSceneCaptureFB;

  PFN_xrRetrieveSpaceQueryResultsFB RetrieveSpaceQueryResultsFB;
  PFN_xrSaveSpaceFB SaveSpaceFB;
  PFN_xrSaveSpaceListFB SaveSpaceListFB;
  PFN_xrSendVirtualKeyboardInputMETA SendVirtualKeyboardInputMETA;

  PFN_xrSetColorSpaceFB SetColorSpaceFB;

  PFN_xrSetDigitalLensControlALMALENCE SetDigitalLensControlALMALENCE;

  PFN_xrSetInputDeviceActiveEXT SetInputDeviceActiveEXT;
  PFN_xrSetInputDeviceLocationEXT SetInputDeviceLocationEXT;
  PFN_xrSetInputDeviceStateBoolEXT SetInputDeviceStateBoolEXT;
  PFN_xrSetInputDeviceStateFloatEXT SetInputDeviceStateFloatEXT;
  PFN_xrSetInputDeviceStateVector2fEXT SetInputDeviceStateVector2fEXT;
  PFN_xrSetPerformanceMetricsStateMETA SetPerformanceMetricsStateMETA;
  PFN_xrSetSpaceComponentStatusFB SetSpaceComponentStatusFB;
  PFN_xrSetTrackingOptimizationSettingsHintQCOM SetTrackingOptimizationSettingsHintQCOM;
  PFN_xrSetVirtualKeyboardModelVisibilityMETA SetVirtualKeyboardModelVisibilityMETA;
  PFN_xrShareSpacesFB ShareSpacesFB;
  PFN_xrShareSpacesMETA ShareSpacesMETA;
  PFN_xrStartColocationAdvertisementMETA StartColocationAdvertisementMETA;
  PFN_xrStartColocationDiscoveryMETA StartColocationDiscoveryMETA;

  PFN_xrStopColocationAdvertisementMETA StopColocationAdvertisementMETA;
  PFN_xrStopColocationDiscoveryMETA StopColocationDiscoveryMETA;

  PFN_xrSuggestVirtualKeyboardLocationMETA SuggestVirtualKeyboardLocationMETA;

  PFN_xrThermalGetTemperatureTrendEXT ThermalGetTemperatureTrendEXT;
  PFN_xrTriangleMeshBeginUpdateFB TriangleMeshBeginUpdateFB;
  PFN_xrTriangleMeshBeginVertexBufferUpdateFB TriangleMeshBeginVertexBufferUpdateFB;
  PFN_xrTriangleMeshEndUpdateFB TriangleMeshEndUpdateFB;
  PFN_xrTriangleMeshEndVertexBufferUpdateFB TriangleMeshEndVertexBufferUpdateFB;
  PFN_xrTriangleMeshGetIndexBufferFB TriangleMeshGetIndexBufferFB;
  PFN_xrTriangleMeshGetVertexBufferFB TriangleMeshGetVertexBufferFB;
  PFN_xrUpdatePassthroughColorLutMETA UpdatePassthroughColorLutMETA;
  PFN_xrUpdateSwapchainFB UpdateSwapchainFB;

  // openxr_loader_negotiation

  PFN_xrCreateApiLayerInstance CreateApiLayerInstance;

  PFN_xrNegotiateLoaderApiLayerInterface NegotiateLoaderApiLayerInterface;
  PFN_xrNegotiateLoaderRuntimeInterface NegotiateLoaderRuntimeInterface;

  // openxr_platform

  PFN_xrConvertTimeToTimespecTimeKHR ConvertTimeToTimespecTimeKHR;
  PFN_xrConvertTimespecTimeToTimeKHR ConvertTimespecTimeToTimeKHR;
  PFN_xrCreateSwapchainAndroidSurfaceKHR CreateSwapchainAndroidSurfaceKHR;

  PFN_xrGetVulkanDeviceExtensionsKHR GetVulkanDeviceExtensionsKHR;

  PFN_xrGetVulkanGraphicsDeviceKHR GetVulkanGraphicsDeviceKHR;

  PFN_xrGetVulkanGraphicsRequirementsKHR GetVulkanGraphicsRequirementsKHR;
  PFN_xrGetVulkanInstanceExtensionsKHR GetVulkanInstanceExtensionsKHR;
  PFN_xrSetAndroidApplicationThreadKHR SetAndroidApplicationThreadKHR;

  PFN_xrCreateEventChannelEXTX1 CreateEventChannelEXTX1;
  PFN_xrDestroyEventChannelEXTX1 DestroyEventChannelEXTX1;
  PFN_xrPollEventChannelEXTX1 PollEventChannelEXTX1;
  PFN_xrSelectEventChannelEXTX1 SelectEventChannelEXTX1;
  PFN_xrSetDefaultEventChannelEXTX1 SetDefaultEventChannelEXTX1;

  PFN_xrSuggestBodyTrackingCalibrationOverrideMETA SuggestBodyTrackingCalibrationOverrideMETA;
  PFN_xrResetBodyTrackingCalibrationMETA ResetBodyTrackingCalibrationMETA;

  PFN_xrRequestBodyTrackingFidelityMETA RequestBodyTrackingFidelityMETA;

  PFN_xrRequestBoundaryVisibilityMETA RequestBoundaryVisibilityMETA;

  PFN_xrCreateDynamicObjectTrackerMETA CreateDynamicObjectTrackerMETA;
  PFN_xrDestroyDynamicObjectTrackerMETA DestroyDynamicObjectTrackerMETA;
  PFN_xrSetDynamicObjectTrackedClassesMETA SetDynamicObjectTrackedClassesMETA;
  PFN_xrGetSpaceDynamicObjectDataMETA GetSpaceDynamicObjectDataMETA;

  PFN_xrResumeSimultaneousHandsAndControllersTrackingMETA ResumeSimultaneousHandsAndControllersTrackingMETA;
  PFN_xrPauseSimultaneousHandsAndControllersTrackingMETA PauseSimultaneousHandsAndControllersTrackingMETA;

  PFN_xrDiscoverSpacesMETA DiscoverSpacesMETA;
  PFN_xrRetrieveSpaceDiscoveryResultsMETA RetrieveSpaceDiscoveryResultsMETA;

  PFN_xrSaveSpacesMETA SaveSpacesMETA;
  PFN_xrEraseSpacesMETA EraseSpacesMETA;

  PFN_xrGetOpenGLGraphicsRequirementsKHR GetOpenGLGraphicsRequirementsKHR;

  PFN_xrGetOpenGLESGraphicsRequirementsKHR GetOpenGLESGraphicsRequirementsKHR;
};

int InitOpenXr1();

int InitOpenXr2();
