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
//

#include "xr_generated_dispatch_table_core.h"
#include <dlfcn.h>

struct XrGeneratedDispatchTableCore table;

// Helper function to populate an instance dispatch table
int InitOpenXr()
{
  void* libopenxr = 0;

  if(table.GetInstanceProcAddr)
    return 1;

  libopenxr = dlopen("libopenxr_loader.so", RTLD_NOW | RTLD_LOCAL);
  if( !libopenxr)
    return 0;

  // ---- Core 1.0 commands
  table.GetInstanceProcAddr = reinterpret_cast<PFN_xrGetInstanceProcAddr>(dlsym(libopenxr, "xrGetInstanceProcAddr") );

  table.AcquireSwapchainImage = reinterpret_cast<PFN_xrAcquireSwapchainImage>(dlsym(libopenxr, "xrAcquireSwapchainImage") );
  table.ApplyHapticFeedback = reinterpret_cast<PFN_xrApplyHapticFeedback>(dlsym(libopenxr, "xrApplyHapticFeedback") );
  table.AttachSessionActionSets = reinterpret_cast<PFN_xrAttachSessionActionSets>(dlsym(libopenxr, "xrAttachSessionActionSets") );
  table.BeginFrame = reinterpret_cast<PFN_xrBeginFrame>(dlsym(libopenxr, "xrBeginFrame") );
  table.BeginSession = reinterpret_cast<PFN_xrBeginSession>(dlsym(libopenxr, "xrBeginSession") );
  table.CreateAction = reinterpret_cast<PFN_xrCreateAction>(dlsym(libopenxr, "xrCreateAction") );
  table.CreateActionSet = reinterpret_cast<PFN_xrCreateActionSet>(dlsym(libopenxr, "xrCreateActionSet") );
  table.CreateActionSpace = reinterpret_cast<PFN_xrCreateActionSpace>(dlsym(libopenxr, "xrCreateActionSpace") );
  table.CreateInstance = reinterpret_cast<PFN_xrCreateInstance>(dlsym(libopenxr, "xrCreateInstance") );
  table.CreateReferenceSpace = reinterpret_cast<PFN_xrCreateReferenceSpace>(dlsym(libopenxr, "xrCreateReferenceSpace") );
  table.CreateSession = reinterpret_cast<PFN_xrCreateSession>(dlsym(libopenxr, "xrCreateSession") );
  table.CreateSwapchain = reinterpret_cast<PFN_xrCreateSwapchain>(dlsym(libopenxr, "xrCreateSwapchain") );
  table.DestroyAction = reinterpret_cast<PFN_xrDestroyAction>(dlsym(libopenxr, "xrDestroyAction") );
  table.DestroyActionSet = reinterpret_cast<PFN_xrDestroyActionSet>(dlsym(libopenxr, "xrDestroyActionSet") );
  table.DestroyInstance = reinterpret_cast<PFN_xrDestroyInstance>(dlsym(libopenxr, "xrDestroyInstance") );
  table.DestroySession = reinterpret_cast<PFN_xrDestroySession>(dlsym(libopenxr, "xrDestroySession") );
  table.DestroySpace = reinterpret_cast<PFN_xrDestroySpace>(dlsym(libopenxr, "xrDestroySpace") );
  table.DestroySwapchain = reinterpret_cast<PFN_xrDestroySwapchain>(dlsym(libopenxr, "xrDestroySwapchain") );
  table.EndFrame = reinterpret_cast<PFN_xrEndFrame>(dlsym(libopenxr, "xrEndFrame") );
  table.EndSession = reinterpret_cast<PFN_xrEndSession>(dlsym(libopenxr, "xrEndSession") );
  table.EnumerateApiLayerProperties = reinterpret_cast<PFN_xrEnumerateApiLayerProperties>(dlsym(libopenxr, "xrEnumerateApiLayerProperties") );
  table.EnumerateBoundSourcesForAction = reinterpret_cast<PFN_xrEnumerateBoundSourcesForAction>(dlsym(libopenxr, "xrEnumerateBoundSourcesForAction") );
  table.EnumerateEnvironmentBlendModes = reinterpret_cast<PFN_xrEnumerateEnvironmentBlendModes>(dlsym(libopenxr, "xrEnumerateEnvironmentBlendModes") );
  table.EnumerateInstanceExtensionProperties = reinterpret_cast<PFN_xrEnumerateInstanceExtensionProperties>(dlsym(libopenxr, "xrEnumerateInstanceExtensionProperties") );
  table.EnumerateReferenceSpaces = reinterpret_cast<PFN_xrEnumerateReferenceSpaces>(dlsym(libopenxr, "xrEnumerateReferenceSpaces") );
  table.EnumerateSwapchainFormats = reinterpret_cast<PFN_xrEnumerateSwapchainFormats>(dlsym(libopenxr, "xrEnumerateSwapchainFormats") );
  table.EnumerateSwapchainImages = reinterpret_cast<PFN_xrEnumerateSwapchainImages>(dlsym(libopenxr, "xrEnumerateSwapchainImages") );
  table.EnumerateViewConfigurationViews = reinterpret_cast<PFN_xrEnumerateViewConfigurationViews>(dlsym(libopenxr, "xrEnumerateViewConfigurationViews") );
  table.EnumerateViewConfigurations = reinterpret_cast<PFN_xrEnumerateViewConfigurations>(dlsym(libopenxr, "xrEnumerateViewConfigurations") );
  table.GetActionStateBoolean = reinterpret_cast<PFN_xrGetActionStateBoolean>(dlsym(libopenxr, "xrGetActionStateBoolean") );
  table.GetActionStateFloat = reinterpret_cast<PFN_xrGetActionStateFloat>(dlsym(libopenxr, "xrGetActionStateFloat") );
  table.GetActionStatePose = reinterpret_cast<PFN_xrGetActionStatePose>(dlsym(libopenxr, "xrGetActionStatePose") );
  table.GetActionStateVector2f = reinterpret_cast<PFN_xrGetActionStateVector2f>(dlsym(libopenxr, "xrGetActionStateVector2f") );
  table.GetCurrentInteractionProfile = reinterpret_cast<PFN_xrGetCurrentInteractionProfile>(dlsym(libopenxr, "xrGetCurrentInteractionProfile") );
  table.GetInputSourceLocalizedName = reinterpret_cast<PFN_xrGetInputSourceLocalizedName>(dlsym(libopenxr, "xrGetInputSourceLocalizedName") );
  table.GetInstanceProperties = reinterpret_cast<PFN_xrGetInstanceProperties>(dlsym(libopenxr, "xrGetInstanceProperties") );
  table.GetReferenceSpaceBoundsRect = reinterpret_cast<PFN_xrGetReferenceSpaceBoundsRect>(dlsym(libopenxr, "xrGetReferenceSpaceBoundsRect") );
  table.GetSystem = reinterpret_cast<PFN_xrGetSystem>(dlsym(libopenxr, "xrGetSystem") );
  table.GetSystemProperties = reinterpret_cast<PFN_xrGetSystemProperties>(dlsym(libopenxr, "xrGetSystemProperties") );
  table.GetViewConfigurationProperties = reinterpret_cast<PFN_xrGetViewConfigurationProperties>(dlsym(libopenxr, "xrGetViewConfigurationProperties") );
  table.LocateSpace = reinterpret_cast<PFN_xrLocateSpace>(dlsym(libopenxr, "xrLocateSpace") );
  table.LocateViews = reinterpret_cast<PFN_xrLocateViews>(dlsym(libopenxr, "xrLocateViews") );
  table.PathToString = reinterpret_cast<PFN_xrPathToString>(dlsym(libopenxr, "xrPathToString") );
  table.PollEvent = reinterpret_cast<PFN_xrPollEvent>(dlsym(libopenxr, "xrPollEvent") );
  table.ReleaseSwapchainImage = reinterpret_cast<PFN_xrReleaseSwapchainImage>(dlsym(libopenxr, "xrReleaseSwapchainImage") );
  table.RequestExitSession = reinterpret_cast<PFN_xrRequestExitSession>(dlsym(libopenxr, "xrRequestExitSession") );
  table.ResultToString = reinterpret_cast<PFN_xrResultToString>(dlsym(libopenxr, "xrResultToString") );
  table.StopHapticFeedback = reinterpret_cast<PFN_xrStopHapticFeedback>(dlsym(libopenxr, "xrStopHapticFeedback") );
  table.StringToPath = reinterpret_cast<PFN_xrStringToPath>(dlsym(libopenxr, "xrStringToPath") );
  table.StructureTypeToString = reinterpret_cast<PFN_xrStructureTypeToString>(dlsym(libopenxr, "xrStructureTypeToString") );
  table.SuggestInteractionProfileBindings = reinterpret_cast<PFN_xrSuggestInteractionProfileBindings>(dlsym(libopenxr, "xrSuggestInteractionProfileBindings") );
  table.SyncActions = reinterpret_cast<PFN_xrSyncActions>(dlsym(libopenxr, "xrSyncActions") );
  table.WaitFrame = reinterpret_cast<PFN_xrWaitFrame>(dlsym(libopenxr, "xrWaitFrame") );
  table.WaitSwapchainImage = reinterpret_cast<PFN_xrWaitSwapchainImage>(dlsym(libopenxr, "xrWaitSwapchainImage") );

  // ---- Core 1.1 commands
  table.LocateSpaces = reinterpret_cast<PFN_xrLocateSpaces>(dlsym(libopenxr, "xrLocateSpaces") );

  return 1;
}
