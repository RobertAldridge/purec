
// Copyright (c) 2017-2024, The Khronos Group Inc.
// Copyright (c) 2017-2019, Valve Corporation
// Copyright (c) 2017-2019, LunarG, Inc.

// SPDX-License-Identifier: Apache-2.0 OR MIT

// *********** THIS FILE IS GENERATED - DO NOT EDIT ***********
//     See utility_source_generator.py for modifications
// ************************************************************

// Copyright (c) 2017-2024, The Khronos Group Inc.
// Copyright (c) 2017-2019 Valve Corporation
// Copyright (c) 2017-2019 LunarG, Inc.
//
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Author: Mark Young <marky@lunarg.com>

#pragma once

#include "openxr.h"

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
};

int InitOpenXr();
