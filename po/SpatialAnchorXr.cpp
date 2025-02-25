
// SpatialAnchorXr.cpp

#define NUM_EYES 2

#include "SpatialAnchorExternalDataHandler.h"
#include "SpatialAnchorXr.h"
#include "OVR_Math.h"
#include "SpatialAnchorGl.h"
#include "SimpleXrInput.h"
#include "SpatialAnchorUtilities.h"
#include "SpatialAnchorFileHandler.h"

using namespace OVR;

#if !defined(EGL_OPENGL_ES3_BIT_KHR)
#define EGL_OPENGL_ES3_BIT_KHR 0x0040
#endif

#define DEBUG 1
#define OVR_LOG_TAG "SpatialAnchorXr"

#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, OVR_LOG_TAG, __VA_ARGS__)
#define ALOGW(...) __android_log_print(ANDROID_LOG_WARN, OVR_LOG_TAG, __VA_ARGS__)
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, OVR_LOG_TAG, __VA_ARGS__)

static const int CPU_LEVEL = 4;
static const int GPU_LEVEL = 4;
static const int NUM_MULTI_SAMPLES = 4;

static const uint32_t MAX_PERSISTENT_SPACES = 20;
static const uint32_t kMaxPersistenceSpacesPerApiCall = 32;

union ovrCompositorLayer_Union
{
  XrCompositionLayerProjection Projection;
  XrCompositionLayerQuad Quad;
  XrCompositionLayerCylinderKHR Cylinder;
  XrCompositionLayerCubeKHR Cube;
  XrCompositionLayerEquirectKHR Equirect;
  XrCompositionLayerPassthroughFB Passthrough;
};

enum { ovrMaxLayerCount = 16 };

// Forward declarations
XrInstance instance;

/*
================================================================================

OpenXR Utility Functions

================================================================================
*/

static void OXR_CheckErrors(XrResult result, const char* function, bool failOnError)
{
  if(XR_FAILED(result) )
  {
    char errorBuffer[XR_MAX_RESULT_STRING_SIZE] = {0};
    xrResultToString(instance, result, errorBuffer);

    if(failOnError)
      ALOGE("OpenXR error: %s: %s\n", function, errorBuffer);
    else
      ALOGV("OpenXR error: %s: %s\n", function, errorBuffer);
  }
}

#if defined(DEBUG)
#define OXR(func) OXR_CheckErrors(func, #func, true);
#else
#define OXR(func) OXR_CheckErrors(func, #func, false);
#endif

/*
================================================================================

OpenXR_Helpers.h Utility Functions

================================================================================
*/

static inline XrVector3f ToXrVector3f(const OVR::Vector3f& s)
{
  XrVector3f r;
  r.x = s.x;
  r.y = s.y;
  r.z = s.z;
  return r;
}

static inline OVR::Vector3f FromXrVector3f(const XrVector3f& s)
{
  OVR::Vector3f r;
  r.x = s.x;
  r.y = s.y;
  r.z = s.z;
  return r;
}

static inline XrQuaternionf ToXrQuaternionf(const OVR::Quatf& s)
{
  XrQuaternionf r;
  r.x = s.x;
  r.y = s.y;
  r.z = s.z;
  r.w = s.w;
  return r;
}

static inline OVR::Quatf FromXrQuaternionf(const XrQuaternionf& s)
{
  OVR::Quatf r;
  r.x = s.x;
  r.y = s.y;
  r.z = s.z;
  r.w = s.w;
  return r;
}

static inline XrPosef ToXrPosef(const OVR::Posef& s)
{
  XrPosef r;
  r.orientation = ToXrQuaternionf(s.Rotation);
  r.position = ToXrVector3f(s.Translation);
  return r;
}

static inline OVR::Posef FromXrPosef(const XrPosef& s)
{
  OVR::Posef r;
  r.Rotation = FromXrQuaternionf(s.orientation);
  r.Translation = FromXrVector3f(s.position);
  return r;
}

/*
================================================================================

Egl Utility Functions

================================================================================
*/

static const char* EglErrorString(const EGLint error)
{
  switch(error)
  {

  case EGL_SUCCESS:
  return "EGL_SUCCESS";

  case EGL_NOT_INITIALIZED:
  return "EGL_NOT_INITIALIZED";

  case EGL_BAD_ACCESS:
  return "EGL_BAD_ACCESS";

  case EGL_BAD_ALLOC:
  return "EGL_BAD_ALLOC";

  case EGL_BAD_ATTRIBUTE:
  return "EGL_BAD_ATTRIBUTE";

  case EGL_BAD_CONTEXT:
  return "EGL_BAD_CONTEXT";

  case EGL_BAD_CONFIG:
  return "EGL_BAD_CONFIG";

  case EGL_BAD_CURRENT_SURFACE:
  return "EGL_BAD_CURRENT_SURFACE";

  case EGL_BAD_DISPLAY:
  return "EGL_BAD_DISPLAY";

  case EGL_BAD_SURFACE:
  return "EGL_BAD_SURFACE";

  case EGL_BAD_MATCH:
  return "EGL_BAD_MATCH";

  case EGL_BAD_PARAMETER:
  return "EGL_BAD_PARAMETER";

  case EGL_BAD_NATIVE_PIXMAP:
  return "EGL_BAD_NATIVE_PIXMAP";

  case EGL_BAD_NATIVE_WINDOW:
  return "EGL_BAD_NATIVE_WINDOW";

  case EGL_CONTEXT_LOST:
  return "EGL_CONTEXT_LOST";

  default:
  return "unknown";

  }
}

/*
================================================================================

ovrEgl

================================================================================
*/

struct ovrEgl
{

void Clear();

void CreateContext(const ovrEgl* shareEgl);

void DestroyContext();

EGLint MajorVersion;
EGLint MinorVersion;
EGLDisplay Display;
EGLConfig Config;
EGLSurface TinySurface;
EGLSurface MainSurface;
EGLContext Context;

};

void ovrEgl::Clear()
{
  MajorVersion = 0;
  MinorVersion = 0;
  Display = 0;
  Config = 0;
  TinySurface = EGL_NO_SURFACE;
  MainSurface = EGL_NO_SURFACE;
  Context = EGL_NO_CONTEXT;
}

void ovrEgl::CreateContext(const ovrEgl* shareEgl)
{
  if(Display != 0)
    return;

  Display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  ALOGV("        eglInitialize( Display, &MajorVersion, &MinorVersion )");

  eglInitialize(Display, &MajorVersion, &MinorVersion);

  // Do NOT use eglChooseConfig, because the Android EGL code pushes in multisample
  // flags in eglChooseConfig if the user has selected the "force 4x MSAA" option in
  // settings, and that is completely wasted for our warp target.
  const int MAX_CONFIGS = 1024;
  EGLConfig configs[MAX_CONFIGS];
  EGLint numConfigs = 0;

  if(eglGetConfigs(Display, configs, MAX_CONFIGS, &numConfigs) == EGL_FALSE)
  {
    ALOGE("        eglGetConfigs() failed: %s", EglErrorString(eglGetError() ) );
    return;
  }

  const EGLint configAttribs[] =
  {
    EGL_RED_SIZE,
    8,
    EGL_GREEN_SIZE,
    8,
    EGL_BLUE_SIZE,
    8,
    EGL_ALPHA_SIZE,
    8, // need alpha for the multi-pass timewarp compositor
    EGL_DEPTH_SIZE,
    0,
    EGL_STENCIL_SIZE,
    0,
    EGL_SAMPLES,
    0,
    EGL_NONE
  };

  Config = 0;
  for(int i = 0; i < numConfigs; i++)
  {
    EGLint value = 0;

    eglGetConfigAttrib(Display, configs[i], EGL_RENDERABLE_TYPE, &value);
    if( (value & EGL_OPENGL_ES3_BIT_KHR) != EGL_OPENGL_ES3_BIT_KHR)
      continue;

    // The pbuffer config also needs to be compatible with normal window rendering
    // so it can share textures with the window context.
    eglGetConfigAttrib(Display, configs[i], EGL_SURFACE_TYPE, &value);
    if( (value & (EGL_WINDOW_BIT | EGL_PBUFFER_BIT) ) != (EGL_WINDOW_BIT | EGL_PBUFFER_BIT) )
      continue;

    int j = 0;
    for(; configAttribs[j] != EGL_NONE; j += 2)
    {
      eglGetConfigAttrib(Display, configs[i], configAttribs[j], &value);
      if(value != configAttribs[j + 1] )
        break;
    }

    if(configAttribs[j] == EGL_NONE)
    {
      Config = configs[i];
      break;
    }
  }

  if(Config == 0)
  {
    ALOGE("        eglChooseConfig() failed: %s", EglErrorString(eglGetError() ) );
    return;
  }

  EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
  ALOGV("        Context = eglCreateContext( Display, Config, EGL_NO_CONTEXT, contextAttribs )");

  Context = eglCreateContext(
    Display,
    Config,
    (shareEgl != nullptr) ? shareEgl->Context : EGL_NO_CONTEXT,
    contextAttribs
  );

  if(Context == EGL_NO_CONTEXT)
  {
    ALOGE("        eglCreateContext() failed: %s", EglErrorString(eglGetError() ) );
    return;
  }

  const EGLint surfaceAttribs[] = {EGL_WIDTH, 16, EGL_HEIGHT, 16, EGL_NONE};
  ALOGV("        TinySurface = eglCreatePbufferSurface( Display, Config, surfaceAttribs )");
  TinySurface = eglCreatePbufferSurface(Display, Config, surfaceAttribs);

  if(TinySurface == EGL_NO_SURFACE)
  {
    ALOGE("        eglCreatePbufferSurface() failed: %s", EglErrorString(eglGetError() ) );
    eglDestroyContext(Display, Context);
    Context = EGL_NO_CONTEXT;
    return;
  }

  ALOGV("        eglMakeCurrent( Display, TinySurface, TinySurface, Context )");

  if(eglMakeCurrent(Display, TinySurface, TinySurface, Context) == EGL_FALSE)
  {
    ALOGE("        eglMakeCurrent() failed: %s", EglErrorString(eglGetError() ) );
    eglDestroySurface(Display, TinySurface);
    eglDestroyContext(Display, Context);
    Context = EGL_NO_CONTEXT;
    return;
  }
}

void ovrEgl::DestroyContext()
{
  if(Display != 0)
  {
    ALOGE("        eglMakeCurrent( Display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT )");

    if(eglMakeCurrent(Display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT) == EGL_FALSE)
      ALOGE("        eglMakeCurrent() failed: %s", EglErrorString(eglGetError() ) );
  }

  if(Context != EGL_NO_CONTEXT)
  {
    ALOGE("        eglDestroyContext( Display, Context )");

    if(eglDestroyContext(Display, Context) == EGL_FALSE)
      ALOGE("        eglDestroyContext() failed: %s", EglErrorString(eglGetError() ) );

    Context = EGL_NO_CONTEXT;
  }

  if(TinySurface != EGL_NO_SURFACE)
  {
    ALOGE("        eglDestroySurface( Display, TinySurface )");

      if(eglDestroySurface(Display, TinySurface) == EGL_FALSE)
      ALOGE("        eglDestroySurface() failed: %s", EglErrorString(eglGetError() ) );

    TinySurface = EGL_NO_SURFACE;
  }

  if(Display != 0)
  {
    ALOGE("        eglTerminate( Display )");

    if(eglTerminate(Display) == EGL_FALSE)
      ALOGE("        eglTerminate() failed: %s", EglErrorString(eglGetError() ) );

    Display = 0;
  }
}

/*
================================================================================

ovrApp

================================================================================
*/

struct ovrExtensionFunctionPointers
{
  PFN_xrCreatePassthroughFB xrCreatePassthroughFB = nullptr;
  PFN_xrDestroyPassthroughFB xrDestroyPassthroughFB = nullptr;
  PFN_xrCreatePassthroughLayerFB xrCreatePassthroughLayerFB = nullptr;
  PFN_xrDestroyPassthroughLayerFB xrDestroyPassthroughLayerFB = nullptr;
  PFN_xrPassthroughLayerResumeFB xrPassthroughLayerResumeFB = nullptr;
  PFN_xrPassthroughLayerPauseFB xrPassthroughLayerPauseFB = nullptr;
  PFN_xrPassthroughLayerSetStyleFB xrPassthroughLayerSetStyleFB = nullptr;
  PFN_xrPassthroughStartFB xrPassthroughStartFB = nullptr;
  PFN_xrPassthroughPauseFB xrPassthroughPauseFB = nullptr;
  PFN_xrEnumerateSpaceSupportedComponentsFB xrEnumerateSpaceSupportedComponentsFB = nullptr;
  PFN_xrSetSpaceComponentStatusFB xrSetSpaceComponentStatusFB = nullptr;
  PFN_xrGetSpaceComponentStatusFB xrGetSpaceComponentStatusFB = nullptr;
  PFN_xrCreateSpatialAnchorFB xrCreateSpatialAnchorFB = nullptr;
  PFN_xrSaveSpacesMETA xrSaveSpacesMETA = nullptr;
  PFN_xrEraseSpacesMETA xrEraseSpacesMETA = nullptr;
  PFN_xrQuerySpacesFB xrQuerySpacesFB = nullptr;
  PFN_xrRetrieveSpaceQueryResultsFB xrRetrieveSpaceQueryResultsFB = nullptr;
  PFN_xrDiscoverSpacesMETA xrDiscoverSpacesMETA = nullptr;
  PFN_xrRetrieveSpaceDiscoveryResultsMETA xrRetrieveSpaceDiscoveryResultsMETA = nullptr;
  PFN_xrGetSpaceUuidFB xrGetSpaceUuidFB = nullptr;
  PFN_xrCreateSpaceUserFB xrCreateSpaceUserFB = nullptr;
  PFN_xrGetSpaceUserIdFB xrGetSpaceUserIdFB = nullptr;
  PFN_xrDestroySpaceUserFB xrDestroySpaceUserFB = nullptr;
  PFN_xrShareSpacesFB xrShareSpacesFB = nullptr;
};

struct ovrEnableComponentEvent
{
  XrSpaceComponentTypeFB componentType;
  XrSpace space;
};

struct ovrApp
{

void Clear();
void HandleSessionStateChanges(XrSessionState state);
void HandleXrEvents();
bool IsComponentSupported(XrSpace space, XrSpaceComponentTypeFB type);

ovrEgl Egl;

bool Resumed;

bool ShouldExit;
bool Focused;

XrSession Session;
XrViewConfigurationProperties ViewportConfig;
XrViewConfigurationView ViewConfigurationView[NUM_EYES];
XrSystemId SystemId;
XrSpace HeadSpace;
XrSpace LocalSpace;
XrSpace StageSpace;
bool SessionActive;

bool IsLocalMultiplayerSupported;

ovrExtensionFunctionPointers FunPtrs;
ovrScene Scene;

int SwapInterval;
int CpuLevel;
int GpuLevel;

// These threads will be marked as performance threads.
int MainThreadTid;
int RenderThreadTid;
ovrCompositorLayer_Union Layers[ovrMaxLayerCount];
int LayerCount;

bool TouchPadDownLastFrame;

bool ShouldDiscoverAnchors;
bool ShouldShareAnchors;

std::unique_ptr<SpatialAnchorExternalDataHandler> ExternalDataHandler =
  std::make_unique<SpatialAnchorFileHandler>();

// List of users to share Spatial Anchors with, if populated.
std::vector<XrSpaceUserIdFB> ShareUserList;

// List of inbound Shared Spatial Anchors, which could be empty.
std::vector<XrUuidEXT> InboundSpatialAnchorList;

std::unordered_map<XrAsyncRequestIdFB, std::vector<XrSpace>> SaveForSharingEventMap;

std::unordered_map<XrAsyncRequestIdFB, std::pair<std::vector<XrSpace>, std::vector<XrSpaceUserFB> > >
  ShareSpacesEventMap;

XrSwapchain ColorSwapChain;
uint32_t SwapChainLength;
Vector3f StageBounds;

// Provided by SpatialAnchorGl, which is not aware of VrApi or OpenXR
ovrAppRenderer AppRenderer;

std::unordered_map<XrAsyncRequestIdFB, std::pair<size_t, XrSpace*>> DestroySpaceEventMap;

};

void ovrApp::Clear()
{
  Resumed = false;

  ShouldExit = false;
  Focused = false;
  instance = XR_NULL_HANDLE;
  Session = XR_NULL_HANDLE;
  ViewportConfig = {};

  for(int i = 0; i < NUM_EYES; i++)
    ViewConfigurationView[i] = {};

  SystemId = XR_NULL_SYSTEM_ID;
  HeadSpace = XR_NULL_HANDLE;
  LocalSpace = XR_NULL_HANDLE;
  StageSpace = XR_NULL_HANDLE;
  SessionActive = false;
  SwapInterval = 1;

  for(int i = 0; i < ovrMaxLayerCount; i++)
    Layers[i] = {};

  LayerCount = 0;
  CpuLevel = 2;
  GpuLevel = 2;
  MainThreadTid = 0;
  RenderThreadTid = 0;
  TouchPadDownLastFrame = false;
  ShouldDiscoverAnchors = true;

  Egl.Clear();
  AppRenderer.Clear();
}

void ovrApp::HandleSessionStateChanges(XrSessionState state)
{
  if(state == XR_SESSION_STATE_READY)
  {
    assert(Resumed);

    assert(SessionActive == false);

    XrSessionBeginInfo sessionBeginInfo = {XR_TYPE_SESSION_BEGIN_INFO};
    sessionBeginInfo.primaryViewConfigurationType = ViewportConfig.viewConfigurationType;

    XrResult result;
    OXR(result = xrBeginSession(Session, &sessionBeginInfo) );

    SessionActive = (result == XR_SUCCESS);

    // Set session state once we have entered VR mode and have a valid session object.
    if(SessionActive)
    {
      XrPerfSettingsLevelEXT cpuPerfLevel = XR_PERF_SETTINGS_LEVEL_SUSTAINED_HIGH_EXT;
      switch(CpuLevel)
      {

      case 0:
        cpuPerfLevel = XR_PERF_SETTINGS_LEVEL_POWER_SAVINGS_EXT;
      break;

      case 1:
        cpuPerfLevel = XR_PERF_SETTINGS_LEVEL_SUSTAINED_LOW_EXT;
      break;

      case 2:
        cpuPerfLevel = XR_PERF_SETTINGS_LEVEL_SUSTAINED_HIGH_EXT;
      break;

      case 3:
        cpuPerfLevel = XR_PERF_SETTINGS_LEVEL_BOOST_EXT;
      break;

      default:
        ALOGE("Invalid CPU level %d", CpuLevel);
      break;

      }

      XrPerfSettingsLevelEXT gpuPerfLevel = XR_PERF_SETTINGS_LEVEL_SUSTAINED_HIGH_EXT;
      switch(GpuLevel)
      {

      case 0:
        gpuPerfLevel = XR_PERF_SETTINGS_LEVEL_POWER_SAVINGS_EXT;
      break;

      case 1:
        gpuPerfLevel = XR_PERF_SETTINGS_LEVEL_SUSTAINED_LOW_EXT;
      break;

      case 2:
        gpuPerfLevel = XR_PERF_SETTINGS_LEVEL_SUSTAINED_HIGH_EXT;
      break;

      case 3:
        gpuPerfLevel = XR_PERF_SETTINGS_LEVEL_BOOST_EXT;
      break;

      default:
        ALOGE("Invalid GPU level %d", GpuLevel);
      break;

      }

      PFN_xrPerfSettingsSetPerformanceLevelEXT pfnPerfSettingsSetPerformanceLevelEXT = NULL;

      OXR(xrGetInstanceProcAddr(
        instance,
        "xrPerfSettingsSetPerformanceLevelEXT",
        (PFN_xrVoidFunction*) &pfnPerfSettingsSetPerformanceLevelEXT
      ) );

      OXR(pfnPerfSettingsSetPerformanceLevelEXT(
      Session, XR_PERF_SETTINGS_DOMAIN_CPU_EXT, cpuPerfLevel) );

      OXR(pfnPerfSettingsSetPerformanceLevelEXT(
      Session, XR_PERF_SETTINGS_DOMAIN_GPU_EXT, gpuPerfLevel) );

      PFN_xrSetAndroidApplicationThreadKHR pfnSetAndroidApplicationThreadKHR = NULL;

      OXR(xrGetInstanceProcAddr(
        instance,
        "xrSetAndroidApplicationThreadKHR",
        (PFN_xrVoidFunction*) &pfnSetAndroidApplicationThreadKHR
      ) );

      OXR(pfnSetAndroidApplicationThreadKHR(
      Session, XR_ANDROID_THREAD_TYPE_APPLICATION_MAIN_KHR, MainThreadTid) );

      OXR(pfnSetAndroidApplicationThreadKHR(
      Session, XR_ANDROID_THREAD_TYPE_RENDERER_MAIN_KHR, RenderThreadTid) );
    }
  }
  else if(state == XR_SESSION_STATE_STOPPING)
  {
    assert(Resumed == false);

    assert(SessionActive);

    OXR(xrEndSession(Session) );
    SessionActive = false;
  }
}

bool ovrApp::IsComponentSupported(XrSpace space, XrSpaceComponentTypeFB type)
{
  uint32_t numComponents = 0;
  OXR(FunPtrs.xrEnumerateSpaceSupportedComponentsFB(space, 0, &numComponents, nullptr) );

  std::vector<XrSpaceComponentTypeFB> components(numComponents);

  OXR(FunPtrs.xrEnumerateSpaceSupportedComponentsFB(
    space,
    numComponents,
    &numComponents,
    components.data()
  ) );

  bool supported = false;
  for(uint32_t c = 0; c < numComponents; ++c)
  {
    if(components[c] == type)
    {
      supported = true;
      break;
    }
  }

  return supported;
}

void ovrApp::HandleXrEvents()
{
  XrEventDataBuffer eventDataBuffer = {};

  // Poll for events
  for(/*nop*/; /*nop*/; /*nop*/)
  {
    XrEventDataBaseHeader* baseEventHeader = (XrEventDataBaseHeader*)(&eventDataBuffer);
    baseEventHeader->type = XR_TYPE_EVENT_DATA_BUFFER;
    baseEventHeader->next = NULL;
    XrResult r;
    OXR(r = xrPollEvent(instance, &eventDataBuffer) );
    if(r != XR_SUCCESS)
      break;

    switch(baseEventHeader->type)
    {

    case XR_TYPE_EVENT_DATA_EVENTS_LOST:
      ALOGV("xrPollEvent: received XR_TYPE_EVENT_DATA_EVENTS_LOST event");
    break;

    case XR_TYPE_EVENT_DATA_INSTANCE_LOSS_PENDING:
      ALOGV("xrPollEvent: received XR_TYPE_EVENT_DATA_INSTANCE_LOSS_PENDING event");
    break;

    case XR_TYPE_EVENT_DATA_INTERACTION_PROFILE_CHANGED:
      ALOGV("xrPollEvent: received XR_TYPE_EVENT_DATA_INTERACTION_PROFILE_CHANGED event");
    break;

    case XR_TYPE_EVENT_DATA_PERF_SETTINGS_EXT:
    {
      const XrEventDataPerfSettingsEXT* perf_settings_event = (XrEventDataPerfSettingsEXT*)baseEventHeader;

      ALOGV(
        "xrPollEvent: received XR_TYPE_EVENT_DATA_PERF_SETTINGS_EXT event: type %d subdomain %d : level %d -> level %d",
        perf_settings_event->type,
        perf_settings_event->subDomain,
        perf_settings_event->fromLevel,
        perf_settings_event->toLevel
      );
    }
    break;

    case XR_TYPE_EVENT_DATA_REFERENCE_SPACE_CHANGE_PENDING:
      ALOGV("xrPollEvent: received XR_TYPE_EVENT_DATA_REFERENCE_SPACE_CHANGE_PENDING event");
    break;

    case XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED:
    {
      const XrEventDataSessionStateChanged* session_state_changed_event =
        (XrEventDataSessionStateChanged*)baseEventHeader;

      ALOGV(
        "xrPollEvent: received XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED: %d for session %p at time %f",
        session_state_changed_event->state,
        (void*)session_state_changed_event->session,
        FromXrTime(session_state_changed_event->time)
      );

      switch(session_state_changed_event->state)
      {

      case XR_SESSION_STATE_FOCUSED:
        Focused = true;
      break;

      case XR_SESSION_STATE_VISIBLE:
        Focused = false;
      break;

      case XR_SESSION_STATE_READY:
      case XR_SESSION_STATE_STOPPING:
        HandleSessionStateChanges(session_state_changed_event->state);
      break;

      case XR_SESSION_STATE_EXITING:
        ShouldExit = true;
      break;

      default:
      break;

      }
    }
    break;

    case XR_TYPE_EVENT_DATA_SPACE_SET_STATUS_COMPLETE_FB:
    {
      ALOGV("xrPollEvent: received XR_TYPE_EVENT_DATA_SPACE_SET_STATUS_COMPLETE_FB");

      const XrEventDataSpaceSetStatusCompleteFB* enableResult = (XrEventDataSpaceSetStatusCompleteFB*)(baseEventHeader);

      if(enableResult->result == XR_SUCCESS && enableResult->componentType == XR_SPACE_COMPONENT_TYPE_LOCATABLE_FB)
      {
        if(AppRenderer.Scene.SpaceList.size() < MAX_PERSISTENT_SPACES)
          AppRenderer.Scene.SpaceList.push_back(enableResult->space);
      }
    }
    break;

    case XR_TYPE_EVENT_DATA_SPATIAL_ANCHOR_CREATE_COMPLETE_FB:
    {
      ALOGV("xrPollEvent: received XR_TYPE_EVENT_DATA_SPATIAL_ANCHOR_CREATE_COMPLETE_FB");

      const XrEventDataSpatialAnchorCreateCompleteFB* createAnchorResult =
        (XrEventDataSpatialAnchorCreateCompleteFB*)baseEventHeader;

      XrSpace space = createAnchorResult->space;
      AppRenderer.Scene.SpaceList.push_back(space);

      if(IsComponentSupported(space, XR_SPACE_COMPONENT_TYPE_STORABLE_FB) )
      {
        XrSpaceComponentStatusSetInfoFB request = {XR_TYPE_SPACE_COMPONENT_STATUS_SET_INFO_FB};
        request.componentType = XR_SPACE_COMPONENT_TYPE_STORABLE_FB;
        request.enabled = XR_TRUE;
        request.timeout = 0;

        XrAsyncRequestIdFB requestId;
        FunPtrs.xrSetSpaceComponentStatusFB(space, &request, &requestId);
      }

      if(IsComponentSupported(space, XR_SPACE_COMPONENT_TYPE_SHARABLE_FB) )
      {
        XrSpaceComponentStatusSetInfoFB request = {XR_TYPE_SPACE_COMPONENT_STATUS_SET_INFO_FB};
        request.componentType = XR_SPACE_COMPONENT_TYPE_SHARABLE_FB;
        request.enabled = XR_TRUE;
        request.timeout = 0;

        XrAsyncRequestIdFB requestId;
        FunPtrs.xrSetSpaceComponentStatusFB(space, &request, &requestId);
      }

      ALOGV(
        "Number of anchors after calling PlaceAnchor: %zu",
        AppRenderer.Scene.SpaceList.size()
      );
    }
    break;

    case XR_TYPE_EVENT_DATA_SPACE_QUERY_RESULTS_AVAILABLE_FB:
    {
      ALOGV("xrPollEvent: received XR_TYPE_EVENT_DATA_SPACE_QUERY_RESULTS_AVAILABLE_FB");

      const auto resultsAvailable =
        (XrEventDataSpaceQueryResultsAvailableFB*)baseEventHeader;

      XrResult res = XR_SUCCESS;

      XrSpaceQueryResultsFB queryResults{XR_TYPE_SPACE_QUERY_RESULTS_FB};
      queryResults.resultCapacityInput = 0;
      queryResults.resultCountOutput = 0;
      queryResults.results = nullptr;

      res = FunPtrs.xrRetrieveSpaceQueryResultsFB(
        Session, resultsAvailable->requestId, &queryResults);

      if(res != XR_SUCCESS)
      {
        ALOGV("xrRetrieveSpaceQueryResultsFB: error %u", res);
        break;
      }

      std::vector<XrSpaceQueryResultFB> results(queryResults.resultCountOutput);
      queryResults.resultCapacityInput = results.size();
      queryResults.results = results.data();

      res = FunPtrs.xrRetrieveSpaceQueryResultsFB(
        Session,
        resultsAvailable->requestId,
        &queryResults
      );

      if(res != XR_SUCCESS)
      {
        ALOGV("xrRetrieveSpaceQueryResultsFB: error %u", res);
        break;
      }

      for(uint32_t i = 0; i < queryResults.resultCountOutput; ++i)
      {
        auto& result = results[i];

        if(IsComponentSupported(result.space, XR_SPACE_COMPONENT_TYPE_LOCATABLE_FB) )
        {
          XrSpaceComponentStatusSetInfoFB request = {XR_TYPE_SPACE_COMPONENT_STATUS_SET_INFO_FB};
          request.componentType = XR_SPACE_COMPONENT_TYPE_LOCATABLE_FB;
          request.enabled = XR_TRUE;
          request.timeout = 0;
          XrAsyncRequestIdFB requestId;
          res = FunPtrs.xrSetSpaceComponentStatusFB(result.space, &request, &requestId);
          if(res == XR_ERROR_SPACE_COMPONENT_STATUS_ALREADY_SET_FB)
          {
            if(AppRenderer.Scene.SpaceList.size() < MAX_PERSISTENT_SPACES)
              AppRenderer.Scene.SpaceList.push_back(result.space);
          }
        }

        if(IsComponentSupported(result.space, XR_SPACE_COMPONENT_TYPE_STORABLE_FB) )
        {
          XrSpaceComponentStatusSetInfoFB request = {XR_TYPE_SPACE_COMPONENT_STATUS_SET_INFO_FB};
          request.componentType = XR_SPACE_COMPONENT_TYPE_STORABLE_FB;
          request.enabled = XR_TRUE;
          request.timeout = 0;
          XrAsyncRequestIdFB requestId;
          res = FunPtrs.xrSetSpaceComponentStatusFB(result.space, &request, &requestId);
          if(res == XR_ERROR_SPACE_COMPONENT_STATUS_ALREADY_SET_FB)
          {
            ALOGV(
              "xrPollEvent: Storable component was already enabled for Space uuid: %s",
              uuidToHexString(result.uuid).c_str()
            );
          }
        }

        if(IsComponentSupported(result.space, XR_SPACE_COMPONENT_TYPE_SHARABLE_FB) )
        {
          XrSpaceComponentStatusSetInfoFB request = {XR_TYPE_SPACE_COMPONENT_STATUS_SET_INFO_FB};
          request.componentType = XR_SPACE_COMPONENT_TYPE_SHARABLE_FB;
          request.enabled = XR_TRUE;
          request.timeout = 0;
          XrAsyncRequestIdFB requestId;
          res = FunPtrs.xrSetSpaceComponentStatusFB(result.space, &request, &requestId);
          if(res == XR_ERROR_SPACE_COMPONENT_STATUS_ALREADY_SET_FB)
          {
            ALOGV(
              "xrPollEvent: Sharable component was already enabled for Space uuid: %s",
              uuidToHexString(result.uuid).c_str()
            );
          }
        }
      }

      ALOGV(
        "Number of anchors after receiving XR_TYPE_EVENT_DATA_SPACE_QUERY_RESULTS_AVAILABLE_FB: %zu",
        AppRenderer.Scene.SpaceList.size()
      );
    }
    break;

    case XR_TYPE_EVENT_DATA_SPACE_QUERY_COMPLETE_FB:
    {
      ALOGV("xrPollEvent: received XR_TYPE_EVENT_DATA_SPACE_QUERY_COMPLETE_FB");
    }
    break;

    case XR_TYPE_EVENT_DATA_SPACE_DISCOVERY_RESULTS_AVAILABLE_META:
    {
      ALOGV(
        "xrPollEvent: received XR_TYPE_EVENT_DATA_SPACE_DISCOVERY_RESULTS_AVAILABLE_META"
      );

      const auto resultsAvailable =
        (XrEventDataSpaceDiscoveryResultsAvailableMETA*)baseEventHeader;

      XrResult res = XR_SUCCESS;
      XrSpaceDiscoveryResultsMETA discoveryResults{XR_TYPE_SPACE_DISCOVERY_RESULTS_META};
      discoveryResults.resultCapacityInput = 0;
      discoveryResults.resultCountOutput = 0;
      discoveryResults.results = nullptr;

      res = FunPtrs.xrRetrieveSpaceDiscoveryResultsMETA(
        Session, resultsAvailable->requestId, &discoveryResults);

      if(res != XR_SUCCESS)
      {
        ALOGV("xrRetrieveSpaceDiscoveryResultsMETA: error %u", res);
        break;
      }

      std::vector<XrSpaceDiscoveryResultMETA> results(discoveryResults.resultCountOutput);
      discoveryResults.resultCapacityInput = results.size();
      discoveryResults.results = results.data();

      res = FunPtrs.xrRetrieveSpaceDiscoveryResultsMETA(
        Session,
        resultsAvailable->requestId,
        &discoveryResults
      );

      if(res != XR_SUCCESS)
      {
        ALOGV("xrRetrieveSpaceDiscoveryResultsMETA: error %u", res);
        break;
      }

      for(uint32_t i = 0; i < discoveryResults.resultCountOutput; ++i)
      {
        auto& result = results[i];

        if(IsComponentSupported(result.space, XR_SPACE_COMPONENT_TYPE_LOCATABLE_FB) )
        {
          XrSpaceComponentStatusSetInfoFB request = {XR_TYPE_SPACE_COMPONENT_STATUS_SET_INFO_FB};
          request.componentType = XR_SPACE_COMPONENT_TYPE_LOCATABLE_FB;
          request.enabled = XR_TRUE;
          request.timeout = 0;
          XrAsyncRequestIdFB requestId;
          res = FunPtrs.xrSetSpaceComponentStatusFB(result.space, &request, &requestId);
          if(res == XR_ERROR_SPACE_COMPONENT_STATUS_ALREADY_SET_FB)
          {
            if(AppRenderer.Scene.SpaceList.size() < MAX_PERSISTENT_SPACES)
              AppRenderer.Scene.SpaceList.push_back(result.space);
          }
        }

        if(IsComponentSupported(result.space, XR_SPACE_COMPONENT_TYPE_STORABLE_FB) )
        {
          XrSpaceComponentStatusSetInfoFB request = {XR_TYPE_SPACE_COMPONENT_STATUS_SET_INFO_FB};
          request.componentType = XR_SPACE_COMPONENT_TYPE_STORABLE_FB;
          request.enabled = XR_TRUE;
          request.timeout = 0;
          XrAsyncRequestIdFB requestId;
          res = FunPtrs.xrSetSpaceComponentStatusFB(result.space, &request, &requestId);
          if(res == XR_ERROR_SPACE_COMPONENT_STATUS_ALREADY_SET_FB)
          {
            ALOGV(
              "xrPollEvent: Storable component was already enabled for Space uuid: %s",
              uuidToHexString(result.uuid).c_str()
            );
          }
        }

        if(IsComponentSupported(result.space, XR_SPACE_COMPONENT_TYPE_SHARABLE_FB) )
        {
          XrSpaceComponentStatusSetInfoFB request = {XR_TYPE_SPACE_COMPONENT_STATUS_SET_INFO_FB};
          request.componentType = XR_SPACE_COMPONENT_TYPE_SHARABLE_FB;
          request.enabled = XR_TRUE;
          request.timeout = 0;
          XrAsyncRequestIdFB requestId;
          res = FunPtrs.xrSetSpaceComponentStatusFB(result.space, &request, &requestId);
          if(res == XR_ERROR_SPACE_COMPONENT_STATUS_ALREADY_SET_FB)
          {
            ALOGV(
              "xrPollEvent: Sharable component was already enabled for Space uuid: %s",
              uuidToHexString(result.uuid).c_str()
            );
          }
        }
      }

      ALOGV(
        "Number of anchors after receiving XR_TYPE_EVENT_DATA_SPACE_DISCOVERY_RESULTS_AVAILABLE_META: %zu",
        AppRenderer.Scene.SpaceList.size()
      );
    }
    break;

    case XR_TYPE_EVENT_DATA_SPACE_DISCOVERY_COMPLETE_META:
    {
      ALOGV("xrPollEvent: received XR_TYPE_EVENT_DATA_SPACE_DISCOVERY_COMPLETE_META");

      const XrEventDataSpaceDiscoveryCompleteMETA* discoveryCompleteResult =
        (XrEventDataSpaceDiscoveryCompleteMETA*)(baseEventHeader);

      ALOGV(
        "XR_TYPE_EVENT_DATA_SPACE_DISCOVERY_COMPLETE_META result: %d",
        discoveryCompleteResult->result
      );
    }
    break;

    case XR_TYPE_EVENT_DATA_SPACES_SAVE_RESULT_META:
    {
      ALOGV("xrPollEvent: received XR_TYPE_EVENT_DATA_SPACES_SAVE_RESULT_META");

      const XrEventDataSpacesSaveResultMETA* saveResult =
        (XrEventDataSpacesSaveResultMETA*)(baseEventHeader);

      auto requestId = saveResult->requestId;

      if(saveResult->result < XR_SUCCESS)
      {
        ALOGE(
          "xrPollEvent: XR_TYPE_EVENT_DATA_SPACES_SAVE_RESULT_META came with error result: %" PRIu64,
          requestId
        );
      }

      auto itr = SaveForSharingEventMap.find(requestId);
      if(itr == SaveForSharingEventMap.end() )
      {
        ALOGE("xrPollEvent: no requestId found in map for XR_TYPE_EVENT_DATA_SPACES_SAVE_RESULT_META");
        break;
      }

      if(saveResult->result < XR_SUCCESS)
      {
        SaveForSharingEventMap.erase(itr);
        break;
      }

      if(IsLocalMultiplayerSupported && ShouldShareAnchors)
      {
        auto spaceList = std::move(itr->second);
        SaveForSharingEventMap.erase(itr);

        // Skip the share step if there are no users to share with.
        if(ShareUserList.empty() )
        {
          ALOGW("xrPollEvent: no users specified for share operation. Skipping share.");
        }
        else
        {
          // Set up the share audience
          std::vector<XrSpaceUserFB> users;
          for(std::size_t k = 0; k < ShareUserList.size(); k++)
          {
            XrSpaceUserFB user;
            XrSpaceUserCreateInfoFB createInfo = {XR_TYPE_SPACE_USER_CREATE_INFO_FB};
            createInfo.userId = ShareUserList[k];
            OXR(FunPtrs.xrCreateSpaceUserFB(Session, &createInfo, &user) );
            users.push_back(user);
          }

          XrSpaceShareInfoFB shareInfo = {XR_TYPE_SPACE_SHARE_INFO_FB};
          shareInfo.spaceCount = static_cast<uint32_t>(spaceList.size() );
          shareInfo.spaces = spaceList.data();
          shareInfo.userCount = static_cast<uint32_t>(users.size() );
          shareInfo.users = users.data();
          XrAsyncRequestIdFB shareRequestId;
          OXR(FunPtrs.xrShareSpacesFB(Session, &shareInfo, &shareRequestId) );
          ShareSpacesEventMap[shareRequestId] = std::make_pair(spaceList, users);
        }
      }
      else
      {
        ALOGW(
          "xrPollEvent: Didn't share anchors. Local multiplayer supported: %s. Should Share Anchors: %s",
          IsLocalMultiplayerSupported ? "true" : "false",
          ShouldShareAnchors ? "true" : "false"
        );
      }

      ShouldShareAnchors = false;
    }
    break;

    case XR_TYPE_EVENT_DATA_SPACES_ERASE_RESULT_META:
    {
      ALOGV("xrPollEvent: received XR_TYPE_EVENT_DATA_SPACES_ERASE_RESULT_META");

      const XrEventDataSpacesEraseResultMETA* eraseResult =
        (XrEventDataSpacesEraseResultMETA*)(baseEventHeader);

      if(eraseResult->result == XR_SUCCESS)
      {
        ALOGV(
          "xrPollEvent: Erase Space successful! Async request: %" PRIu64,
          eraseResult->requestId
        );

        auto iter = DestroySpaceEventMap.find(eraseResult->requestId);
        if(iter != DestroySpaceEventMap.end() )
        {
          XrSpace* spaceList = iter->second.second;
          for(size_t i = 0; i < iter->second.first; i++)
            xrDestroySpace(spaceList[i] );

          AppRenderer.Scene.SpaceList.clear();
          DestroySpaceEventMap.erase(iter);
        }
      }
      else
      {
        ALOGV(
          "xrPollEvent: Erase Space failed! Async request: %" PRIu64,
          eraseResult->requestId
        );
      }
    }
    break;

    case XR_TYPE_EVENT_DATA_SPACE_SHARE_COMPLETE_FB:
    {
      ALOGV("xrPollEvent: received XR_TYPE_EVENT_DATA_SPACE_SHARE_COMPLETE_FB");

      const XrEventDataSpaceShareCompleteFB* shareResult =
        (XrEventDataSpaceShareCompleteFB*)(baseEventHeader);

      ALOGV(
        "xrPollEvent: xrShareSpacesFB request %" PRIu64 " completed with result (%d)",
        shareResult->requestId,
        shareResult->result
      );

      auto itr = ShareSpacesEventMap.find(shareResult->requestId);
      if(itr != ShareSpacesEventMap.end() )
      {
        auto spaces = std::move(itr->second.first);
        auto users = std::move(itr->second.second);
        ShareSpacesEventMap.erase(itr);
        if(shareResult->result == XR_SUCCESS)
        {
          std::vector<XrUuidEXT> sharedSpatialAnchors;
          for(std::size_t k = 0; k < spaces.size(); k++)
          {
            XrUuidEXT uuid;
            OXR(FunPtrs.xrGetSpaceUuidFB(spaces[k], &uuid) );
            ALOGV("xrPollEvent: Shared space %s", uuidToHexString(uuid).c_str() );
            sharedSpatialAnchors.emplace_back(uuid);
          }

          std::vector<XrSpaceUserIdFB> sharedUserIds;
          for(std::size_t k = 0; k < users.size(); k++)
          {
            XrSpaceUserIdFB userId;
            OXR(FunPtrs.xrGetSpaceUserIdFB(users[k], &userId) );
            ALOGV("xrPollEvent: Shared spaces with user %" PRIu64, userId);
            sharedUserIds.emplace_back(userId);
          }

          ExternalDataHandler->WriteSharedSpatialAnchorList(sharedSpatialAnchors, sharedUserIds);
        }

        // We're done with the user handles at this point, so destroy them.
        for(std::size_t k = 0; k < users.size(); k++)
        {
          OXR(FunPtrs.xrDestroySpaceUserFB(users[k] ) );
          ALOGV("xrPollEvent: Destroyed user handle %" PRIu64, (uint64_t)users[k] );
        }
      }
      else
      {
        ALOGE(
          "Failed to match xrShareSpacesFB request data to requestId %" PRIu64,
          shareResult->requestId
        );
      }
    }
    break;

    default:
      ALOGV("xrPollEvent: Unknown event");
    break;

    }
  }
}

/*
================================================================================

Native Activity

================================================================================
*/

/**
 * Process the next main command.
 */
static void app_handle_cmd(struct android_app* androidApp, int32_t cmd)
{
  ovrApp& app = *(ovrApp*)androidApp->userData;

  switch(cmd)
  {

  // There is no APP_CMD_CREATE. The ANativeActivity creates the
  // application thread from onCreate(). The application thread
  // then calls android_main().
  case APP_CMD_START:
  {
    ALOGV("onStart()");
    ALOGV("    APP_CMD_START");
  }
  break;

  case APP_CMD_RESUME:
  {
    ALOGV("onResume()");
    ALOGV("    APP_CMD_RESUME");
    app.Resumed = true;
  }
  break;

  case APP_CMD_PAUSE:
  {
    ALOGV("onPause()");
    ALOGV("    APP_CMD_PAUSE");
    app.Resumed = false;
  }
  break;

  case APP_CMD_STOP:
  {
    ALOGV("onStop()");
    ALOGV("    APP_CMD_STOP");
  }
  break;

  case APP_CMD_DESTROY:
  {
    ALOGV("onDestroy()");
    ALOGV("    APP_CMD_DESTROY");
    app.Clear();
  }
  break;

  case APP_CMD_INIT_WINDOW:
  {
    ALOGV("surfaceCreated()");
    ALOGV("    APP_CMD_INIT_WINDOW");
  }
  break;

  case APP_CMD_TERM_WINDOW:
  {
    ALOGV("surfaceDestroyed()");
    ALOGV("    APP_CMD_TERM_WINDOW");
  }
  break;

  }
}

static Matrix4f OvrFromXr(const XrMatrix4x4f& x)
{
  return Matrix4f(
    x.m[0x0],
    x.m[0x1],
    x.m[0x2],
    x.m[0x3],
    x.m[0x4],
    x.m[0x5],
    x.m[0x6],
    x.m[0x7],
    x.m[0x8],
    x.m[0x9],
    x.m[0xa],
    x.m[0xb],
    x.m[0xc],
    x.m[0xd],
    x.m[0xe],
    x.m[0xf]
  );
}

static Quatf OvrFromXr(const XrQuaternionf& q)
{
  return Quatf(q.x, q.y, q.z, q.w);
}

static Vector3f OvrFromXr(const XrVector3f& v)
{
  return Vector3f(v.x, v.y, v.z);
}

static Posef OvrFromXr(const XrPosef& p)
{
  return Posef(OvrFromXr(p.orientation), OvrFromXr(p.position) );
}

static void DiscoverAnchors(ovrApp& app)
{
  ALOGV("DiscoverAnchors");
  XrSpaceDiscoveryInfoMETA info = {XR_TYPE_SPACE_DISCOVERY_INFO_META};
  info.filters = nullptr;
  info.filters = 0;
  XrAsyncRequestIdFB requestId;
  OXR(app.FunPtrs.xrDiscoverSpacesMETA(app.Session, &info, &requestId) );
}

static void DownloadAnchors(ovrApp& app)
{
  ALOGV("DownloadAnchors");

  if(!app.IsLocalMultiplayerSupported)
  {
    ALOGW("Local multiplayer is not supported. Skipping download.");
    return;
  }

  if(app.InboundSpatialAnchorList.empty() )
  {
    ALOGW("DownloadAnchors: No Spatial Anchors to download");
    return;
  }

  XrSpaceStorageLocationFilterInfoFB locationFilterInfo = {XR_TYPE_SPACE_STORAGE_LOCATION_FILTER_INFO_FB};
  locationFilterInfo.location = XR_SPACE_STORAGE_LOCATION_CLOUD_FB;

  XrSpaceUuidFilterInfoFB uuidFilterInfo = {XR_TYPE_SPACE_UUID_FILTER_INFO_FB};
  uuidFilterInfo.next = &locationFilterInfo;
  uuidFilterInfo.uuidCount = (uint32_t)app.InboundSpatialAnchorList.size();
  uuidFilterInfo.uuids = app.InboundSpatialAnchorList.data();

  XrSpaceQueryInfoFB queryInfo = {XR_TYPE_SPACE_QUERY_INFO_FB};
  queryInfo.queryAction = XR_SPACE_QUERY_ACTION_LOAD_FB;
  queryInfo.maxResultCount = MAX_PERSISTENT_SPACES;
  queryInfo.timeout = 0;
  queryInfo.filter = (XrSpaceFilterInfoBaseHeaderFB*)&uuidFilterInfo;

  XrAsyncRequestIdFB requestId;
  OXR(app.FunPtrs.xrQuerySpacesFB(
    app.Session,
    (XrSpaceQueryInfoBaseHeaderFB*) &queryInfo,
    &requestId
  ) );
}

static void SaveAnchorsAndTrySharing(ovrApp& app)
{
  ALOGV("SaveAnchorsAndTrySharing");

  if(!app.IsLocalMultiplayerSupported)
    ALOGW("SaveAnchorsAndTrySharing: Local multiplayer is not supported, will only save not share.");
  else
    app.ShouldShareAnchors = true;

  std::vector<XrSpace> saveList;
  for(XrSpace space : app.AppRenderer.Scene.SpaceList)
  {
    // We will only upload Anchors that are Storable and Sharable.

    XrSpaceComponentStatusFB storableStatus;
    XrSpaceComponentStatusFB sharableStatus;

    OXR(app.FunPtrs.xrGetSpaceComponentStatusFB(
      space,
      XR_SPACE_COMPONENT_TYPE_STORABLE_FB,
      &storableStatus
    ) );

    OXR(app.FunPtrs.xrGetSpaceComponentStatusFB(
      space,
      XR_SPACE_COMPONENT_TYPE_SHARABLE_FB,
      &sharableStatus
    ) );

    if(storableStatus.enabled && sharableStatus.enabled)
      saveList.push_back(space);
  }

  XrSpacesSaveInfoMETA saveInfo = {XR_TYPE_SPACES_SAVE_INFO_META};
  saveInfo.spaceCount = static_cast<uint32_t>(saveList.size() );
  saveInfo.spaces = saveList.data();
  XrAsyncRequestIdFB requestId;
  XrResult res = XR_SUCCESS;
  OXR(res = app.FunPtrs.xrSaveSpacesMETA(app.Session, &saveInfo, &requestId) );

  if(res == XR_SUCCESS)
    ALOGV("SaveAnchors call successfully kicked off!");
  else
    ALOGV("SaveAnchors call failed to kick off!");

  // The share operation will continue on the completion event of xrSaveSpacesMETA.
  // Add the current spaces to the map. This step needs to be a copy here because we're taking a
  // snapshot of the Spatial Anchors in the app state.
  app.SaveForSharingEventMap[requestId] = saveList;
}

void UpdateStageBounds(ovrApp& app)
{
  XrExtent2Df stageBounds = {};

  XrResult result;
  OXR(result = xrGetReferenceSpaceBoundsRect(
    app.Session,
    XR_REFERENCE_SPACE_TYPE_STAGE,
    &stageBounds
  ) );

  if(result != XR_SUCCESS)
  {
    ALOGV("Stage bounds query failed: using small defaults");
    stageBounds.width = 1.0f;
    stageBounds.height = 1.0f;
  }

  app.StageBounds = Vector3f(stageBounds.width * 0.5f, 1.0f, stageBounds.height * 0.5f);
}

void EraseAndDestroyAnchors(ovrApp& app)
{
  if(app.AppRenderer.Scene.SpaceList.empty() )
    return;

  if(app.Session == XR_NULL_HANDLE)
    return;

  size_t numSpacesToEraseAndDestroy =
    std::min( (size_t)kMaxPersistenceSpacesPerApiCall, app.AppRenderer.Scene.SpaceList.size() );

  ALOGV("About to call erase with %d handles", (int)numSpacesToEraseAndDestroy);
  std::vector<XrSpace> spacesToErase(numSpacesToEraseAndDestroy);

  std::copy(
    app.AppRenderer.Scene.SpaceList.begin(),
    app.AppRenderer.Scene.SpaceList.begin() + numSpacesToEraseAndDestroy,
    spacesToErase.begin()
  );

  XrSpacesEraseInfoMETA eraseInfo = {XR_TYPE_SPACES_ERASE_INFO_META};
  eraseInfo.spaceCount = static_cast<uint32_t>(spacesToErase.size() );
  eraseInfo.spaces = spacesToErase.data();
  eraseInfo.uuidCount = 0;

  XrAsyncRequestIdFB requestId;
  XrResult res = XR_SUCCESS;
  OXR(res = app.FunPtrs.xrEraseSpacesMETA(app.Session, &eraseInfo, &requestId) );

  if(res == XR_SUCCESS)
  {
    ALOGV("EraseAndDestroyAnchors erase call successfully kicked off!");

    app.DestroySpaceEventMap[requestId] =
    std::pair<size_t, XrSpace*>(spacesToErase.size(), spacesToErase.data() );
  }
  else
  {
    ALOGE("EraseAndDestroyAnchors erase call failed to kick off!");
  }

  // Call destroy in the event handling of erase API
}

void PlaceAnchor(ovrApp& app, SimpleXrInput* input, const XrFrameState& frameState)
{
  // Handle Right Controller Events
  if(input == nullptr)
    return;

  if(app.Session == XR_NULL_HANDLE)
    return;

  if(app.AppRenderer.Scene.SpaceList.size() >= MAX_PERSISTENT_SPACES)
    return;

  OVR::Posef localFromRightAim = input->FromControllerSpace(
    SimpleXrInput::Side_Right,
    SimpleXrInput::Controller_Aim,
    app.LocalSpace,
    frameState.predictedDisplayTime
  );

  XrSpatialAnchorCreateInfoFB anchorCreateInfo = {XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_FB};
  anchorCreateInfo.space = app.LocalSpace;
  anchorCreateInfo.poseInSpace = ToXrPosef(localFromRightAim);
  anchorCreateInfo.time = frameState.predictedDisplayTime;
  XrAsyncRequestIdFB createRequest;
  OXR(app.FunPtrs.xrCreateSpatialAnchorFB(app.Session, &anchorCreateInfo, &createRequest) );
  ALOGV("Place Spatial Anchor initiated.");
}

/**
 * This is the main entry point of a native application that is using
 * anag.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* androidApp)
{
  ALOGV("----------------------------------------------------------------");
  ALOGV("android_app_entry()");
  ALOGV("    android_main()");

  JNIEnv* Env = 0;
  (*androidApp->activity->vm).AttachCurrentThread(&Env, nullptr);

  // Note that AttachCurrentThread will reset the thread name.
  prctl(PR_SET_NAME, (long)"OVR::Main", 0, 0, 0);

  ovrApp app;
  app.Clear();

  PFN_xrInitializeLoaderKHR xrInitializeLoaderKHR;

  xrGetInstanceProcAddr(
    XR_NULL_HANDLE,
    "xrInitializeLoaderKHR",
    (PFN_xrVoidFunction*) &xrInitializeLoaderKHR
  );

  if(xrInitializeLoaderKHR != NULL)
  {
    XrLoaderInitInfoAndroidKHR loaderInitializeInfoAndroid = {XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR};

    loaderInitializeInfoAndroid.applicationVM = androidApp->activity->vm;
    loaderInitializeInfoAndroid.applicationContext = androidApp->activity->clazz;
    xrInitializeLoaderKHR( (XrLoaderInitInfoBaseHeaderKHR*)&loaderInitializeInfoAndroid);
  }

  // Log available layers.
  {
    XrResult result;

    PFN_xrEnumerateApiLayerProperties xrEnumerateApiLayerProperties;

    OXR(result = xrGetInstanceProcAddr(
      XR_NULL_HANDLE,
      "xrEnumerateApiLayerProperties",
      (PFN_xrVoidFunction*)&xrEnumerateApiLayerProperties
    ) );

    if(result != XR_SUCCESS)
    {
      ALOGE("Failed to get xrEnumerateApiLayerProperties function pointer.");
      exit(1);
    }

    uint32_t layerCount = 0;
    OXR(xrEnumerateApiLayerProperties(0, &layerCount, NULL) );

    std::vector<XrApiLayerProperties> layerProperties(
    layerCount, {XR_TYPE_API_LAYER_PROPERTIES} );

    OXR(xrEnumerateApiLayerProperties(layerCount, &layerCount, layerProperties.data() ) );

    for(const auto& layer : layerProperties)
      ALOGV("Found layer %s", layer.layerName);
  }

  // Check that the extensions required are present.
  std::vector<const char*> requiredExtensionNames
  {
    XR_KHR_OPENGL_ES_ENABLE_EXTENSION_NAME,

    XR_EXT_PERFORMANCE_SETTINGS_EXTENSION_NAME,
    XR_KHR_ANDROID_THREAD_SETTINGS_EXTENSION_NAME,

    XR_FB_PASSTHROUGH_EXTENSION_NAME,
    XR_FB_SPATIAL_ENTITY_EXTENSION_NAME,
    XR_FB_SPATIAL_ENTITY_QUERY_EXTENSION_NAME,
    XR_META_SPATIAL_ENTITY_DISCOVERY_EXTENSION_NAME,
    XR_META_SPATIAL_ENTITY_PERSISTENCE_EXTENSION_NAME
  };

  const uint32_t numRequiredExtensions = requiredExtensionNames.size();

  std::vector<const char*> localMultiplayerExtensionNames
  {
    XR_FB_SPATIAL_ENTITY_SHARING_EXTENSION_NAME, XR_FB_SPATIAL_ENTITY_USER_EXTENSION_NAME
  };

  const uint32_t numLocalMultiplayerExtensions = localMultiplayerExtensionNames.size();

  std::vector<const char*> requestedExtensionNames(
  requiredExtensionNames.begin(), requiredExtensionNames.end() );

  // Check the list of required extensions against what is supported by the runtime.
  {
    uint32_t numOutputExtensions = 0;
    OXR(xrEnumerateInstanceExtensionProperties(nullptr, 0, &numOutputExtensions, nullptr) );
    ALOGV("xrEnumerateInstanceExtensionProperties found %u extension(s).", numOutputExtensions);

    auto extensionProperties =
    std::vector<XrExtensionProperties>(numOutputExtensions, {XR_TYPE_EXTENSION_PROPERTIES});

    OXR(xrEnumerateInstanceExtensionProperties(
    nullptr, numOutputExtensions, &numOutputExtensions, extensionProperties.data() ) );

    for(uint32_t i = 0; i < numOutputExtensions; i++)
      ALOGV("Extension #%d = '%s'.", i, extensionProperties[i].extensionName);

    for(uint32_t i = 0; i < numRequiredExtensions; i++)
    {
      if(!isExtensionEnumerated(requiredExtensionNames[i], extensionProperties.data(), numOutputExtensions) )
      {
        ALOGE("Failed to find required extension %s", requiredExtensionNames[i] );
        exit(1);
      }
      else
      {
        ALOGV("Found required extension %s", requiredExtensionNames[i] );
      }
    }

    app.IsLocalMultiplayerSupported = true;
    for(uint32_t i = 0; i < numLocalMultiplayerExtensions; i++)
    {
      if( !isExtensionEnumerated(
        localMultiplayerExtensionNames[i],
        extensionProperties.data(),
        numOutputExtensions
      ) )
      {
        ALOGW(
          "Failed to find local multiplayer extension %s - feature is not supported on this device",
          localMultiplayerExtensionNames[i]
        );

        app.IsLocalMultiplayerSupported = false;
      }
      else
      {
        ALOGV("Found local multiplayer extension %s", localMultiplayerExtensionNames[i] );

        requestedExtensionNames.push_back(localMultiplayerExtensionNames[i] );
      }
    }
  }

  // Create the OpenXR instance.
  XrApplicationInfo appInfo = {};
  strcpy(appInfo.applicationName, "SpatialAnchorXr");

  appInfo.applicationVersion = 0;
  strcpy(appInfo.engineName, "Oculus Mobile Sample");

  appInfo.engineVersion = 0;
  appInfo.apiVersion = XR_API_VERSION_1_0;

  XrInstanceCreateInfo instanceCreateInfo = {XR_TYPE_INSTANCE_CREATE_INFO};
  instanceCreateInfo.createFlags = 0;
  instanceCreateInfo.applicationInfo = appInfo;
  instanceCreateInfo.enabledApiLayerCount = 0;
  instanceCreateInfo.enabledApiLayerNames = NULL;
  instanceCreateInfo.enabledExtensionCount = requestedExtensionNames.size();
  instanceCreateInfo.enabledExtensionNames = requestedExtensionNames.data();

  XrResult initResult;
  OXR(initResult = xrCreateInstance(&instanceCreateInfo, &instance) );

  if(initResult != XR_SUCCESS)
  {
    ALOGE("Failed to create XR instance: %d.", initResult);
    exit(1);
  }

  XrInstanceProperties instanceInfo = {XR_TYPE_INSTANCE_PROPERTIES};
  OXR(xrGetInstanceProperties(instance, &instanceInfo) );

  ALOGV(
    "Runtime %s: Version : %u.%u.%u",
    instanceInfo.runtimeName,
    XR_VERSION_MAJOR(instanceInfo.runtimeVersion),
    XR_VERSION_MINOR(instanceInfo.runtimeVersion),
    XR_VERSION_PATCH(instanceInfo.runtimeVersion)
  );

  XrSystemGetInfo systemGetInfo = {XR_TYPE_SYSTEM_GET_INFO};
  systemGetInfo.formFactor = XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY;

  XrSystemId systemId;
  OXR(initResult = xrGetSystem(instance, &systemGetInfo, &systemId) );
  if(initResult != XR_SUCCESS)
  {
    if(initResult == XR_ERROR_FORM_FACTOR_UNAVAILABLE)
      ALOGE("Failed to get system; the specified form factor is not available. Is your headset connected?");
    else
      ALOGE("xrGetSystem failed, error %d", initResult);

    exit(1);
  }

  XrSystemProperties systemProperties = {XR_TYPE_SYSTEM_PROPERTIES};
  OXR(xrGetSystemProperties(instance, systemId, &systemProperties) );

  ALOGV(
    "System Properties: Name=%s VendorId=%x",
    systemProperties.systemName,
    systemProperties.vendorId
  );

  ALOGV(
    "System Graphics Properties: MaxWidth=%d MaxHeight=%d MaxLayers=%d",
    systemProperties.graphicsProperties.maxSwapchainImageWidth,
    systemProperties.graphicsProperties.maxSwapchainImageHeight,
    systemProperties.graphicsProperties.maxLayerCount
  );

  ALOGV(
    "System Tracking Properties: OrientationTracking=%s PositionTracking=%s",
    systemProperties.trackingProperties.orientationTracking ? "True" : "False",
    systemProperties.trackingProperties.positionTracking ? "True" : "False"
  );

  assert(ovrMaxLayerCount <= systemProperties.graphicsProperties.maxLayerCount);

  // Get the graphics requirements.
  PFN_xrGetOpenGLESGraphicsRequirementsKHR pfnGetOpenGLESGraphicsRequirementsKHR = NULL;

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrGetOpenGLESGraphicsRequirementsKHR",
    (PFN_xrVoidFunction*) &pfnGetOpenGLESGraphicsRequirementsKHR
  ) );

  XrGraphicsRequirementsOpenGLESKHR graphicsRequirements = {XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_ES_KHR};

  OXR(pfnGetOpenGLESGraphicsRequirementsKHR(instance, systemId, &graphicsRequirements) );

  // Create the EGL Context
  app.Egl.CreateContext(nullptr);

  // Check the graphics requirements.
  int eglMajor = 0;
  int eglMinor = 0;
  glGetIntegerv(GL_MAJOR_VERSION, &eglMajor);
  glGetIntegerv(GL_MINOR_VERSION, &eglMinor);
  const XrVersion eglVersion = XR_MAKE_VERSION(eglMajor, eglMinor, 0);

  if(eglVersion < graphicsRequirements.minApiVersionSupported ||
    eglVersion > graphicsRequirements.maxApiVersionSupported
  )
  {
    ALOGE("GLES version %d.%d not supported", eglMajor, eglMinor);
    exit(0);
  }

  app.CpuLevel = CPU_LEVEL;
  app.GpuLevel = GPU_LEVEL;

  app.MainThreadTid = gettid();

  app.SystemId = systemId;

  // Create the OpenXR Session.

  XrGraphicsBindingOpenGLESAndroidKHR graphicsBinding = {XR_TYPE_GRAPHICS_BINDING_OPENGL_ES_ANDROID_KHR};
  graphicsBinding.display = app.Egl.Display;
  graphicsBinding.config = app.Egl.Config;
  graphicsBinding.context = app.Egl.Context;

  XrSessionCreateInfo sessionCreateInfo = {XR_TYPE_SESSION_CREATE_INFO};
  sessionCreateInfo.next = &graphicsBinding;
  sessionCreateInfo.createFlags = 0;
  sessionCreateInfo.systemId = app.SystemId;

  OXR(initResult = xrCreateSession(instance, &sessionCreateInfo, &app.Session) );

  if(initResult != XR_SUCCESS)
  {
    ALOGE("Failed to create XR session: %d.", initResult);
    exit(1);
  }

  // App only supports the primary stereo view config.
  const XrViewConfigurationType supportedViewConfigType = XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO;

  // Enumerate the viewport configurations.
  uint32_t viewportConfigTypeCount = 0;
  OXR(xrEnumerateViewConfigurations(instance, app.SystemId, 0, &viewportConfigTypeCount, NULL) );

  auto viewportConfigurationTypes = new XrViewConfigurationType[viewportConfigTypeCount];

  OXR(xrEnumerateViewConfigurations(
    instance,
    app.SystemId,
    viewportConfigTypeCount,
    &viewportConfigTypeCount,
    viewportConfigurationTypes
  ) );

  ALOGV("Available Viewport Configuration Types: %d", viewportConfigTypeCount);

  for(uint32_t i = 0; i < viewportConfigTypeCount; i++)
  {
    const XrViewConfigurationType viewportConfigType = viewportConfigurationTypes[i];

    ALOGV(
      "Viewport configuration type %d : %s",
      viewportConfigType,
      viewportConfigType == supportedViewConfigType ? "Selected" : ""
    );

    XrViewConfigurationProperties viewportConfig = {XR_TYPE_VIEW_CONFIGURATION_PROPERTIES};

    OXR(xrGetViewConfigurationProperties(
      instance, app.SystemId, viewportConfigType, &viewportConfig
    ) );

    ALOGV(
      "FovMutable=%s ConfigurationType %d",
      viewportConfig.fovMutable ? "true" : "false",
      viewportConfig.viewConfigurationType
    );

    uint32_t viewCount;
    OXR(xrEnumerateViewConfigurationViews(
      instance,
      app.SystemId,
      viewportConfigType,
      0,
      &viewCount,
      NULL
    ) );

    if(viewCount > 0)
    {
      auto elements = new XrViewConfigurationView[viewCount];

      for(uint32_t e = 0; e < viewCount; e++)
      {
        elements[e].type = XR_TYPE_VIEW_CONFIGURATION_VIEW;
        elements[e].next = NULL;
      }

      OXR(xrEnumerateViewConfigurationViews(
        instance,
        app.SystemId,
        viewportConfigType,
        viewCount,
        &viewCount,
        elements
      ) );

      // Log the view config info for each view type for debugging purposes.
      for(uint32_t e = 0; e < viewCount; e++)
      {
        const XrViewConfigurationView* element = &elements[e];

        ALOGV(
          "Viewport [%d]: Recommended Width=%d Height=%d SampleCount=%d",
          e,
          element->recommendedImageRectWidth,
          element->recommendedImageRectHeight,
          element->recommendedSwapchainSampleCount
        );

        ALOGV(
          "Viewport [%d]: Max Width=%d Height=%d SampleCount=%d",
          e,
          element->maxImageRectWidth,
          element->maxImageRectHeight,
          element->maxSwapchainSampleCount
        );
      }

      // Cache the view config properties for the selected config type.
      if(viewportConfigType == supportedViewConfigType)
      {
        assert(viewCount == NUM_EYES);

        for(uint32_t e = 0; e < viewCount; e++)
          app.ViewConfigurationView[e] = elements[e];
      }

      delete[] elements;
    }
    else
    {
      ALOGE("Empty viewport configuration type: %d", viewCount);
    }
  }

  delete[] viewportConfigurationTypes;

  // Get the viewport configuration info for the chosen viewport configuration type.
  app.ViewportConfig.type = XR_TYPE_VIEW_CONFIGURATION_PROPERTIES;

  OXR(xrGetViewConfigurationProperties(
    instance,
    app.SystemId,
    supportedViewConfigType,
    &app.ViewportConfig
  ) );

  bool stageSupported = false;

  uint32_t numOutputSpaces = 0;
  OXR(xrEnumerateReferenceSpaces(app.Session, 0, &numOutputSpaces, NULL) );

  auto referenceSpaces = new XrReferenceSpaceType[numOutputSpaces];

  OXR(xrEnumerateReferenceSpaces(
    app.Session,
    numOutputSpaces,
    &numOutputSpaces,
    referenceSpaces
  ) );

  for(uint32_t i = 0; i < numOutputSpaces; i++)
  {
    if(referenceSpaces[i] == XR_REFERENCE_SPACE_TYPE_STAGE)
    {
      stageSupported = true;
      break;
    }
  }

  delete[] referenceSpaces;

  // Create a space to the first path
  XrReferenceSpaceCreateInfo spaceCreateInfo = {XR_TYPE_REFERENCE_SPACE_CREATE_INFO};
  spaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_VIEW;
  spaceCreateInfo.poseInReferenceSpace.orientation.w = 1.0f;
  OXR(xrCreateReferenceSpace(app.Session, &spaceCreateInfo, &app.HeadSpace) );

  spaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_LOCAL;
  OXR(xrCreateReferenceSpace(app.Session, &spaceCreateInfo, &app.LocalSpace) );

  if(stageSupported)
  {
    spaceCreateInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_STAGE;
    spaceCreateInfo.poseInReferenceSpace.position.y = 0.0f;
    OXR(xrCreateReferenceSpace(app.Session, &spaceCreateInfo, &app.StageSpace) );
    ALOGV("Created stage space");
  }

  XrView projections[NUM_EYES];
  for(int eye = 0; eye < NUM_EYES; eye++)
  projections[eye] = XrView{XR_TYPE_VIEW};

  GLenum format = GL_SRGB8_ALPHA8;
  int width = app.ViewConfigurationView[0].recommendedImageRectWidth;
  int height = app.ViewConfigurationView[0].recommendedImageRectHeight;

  XrSwapchainCreateInfo swapChainCreateInfo = {XR_TYPE_SWAPCHAIN_CREATE_INFO};

  swapChainCreateInfo.usageFlags =
  XR_SWAPCHAIN_USAGE_SAMPLED_BIT | XR_SWAPCHAIN_USAGE_COLOR_ATTACHMENT_BIT;

  swapChainCreateInfo.format = format;
  swapChainCreateInfo.sampleCount = 1;
  swapChainCreateInfo.width = width;
  swapChainCreateInfo.height = height;
  swapChainCreateInfo.faceCount = 1;
  swapChainCreateInfo.arraySize = 2;
  swapChainCreateInfo.mipCount = 1;

  // Create the swapchain.
  OXR(xrCreateSwapchain(app.Session, &swapChainCreateInfo, &app.ColorSwapChain) );
  OXR(xrEnumerateSwapchainImages(app.ColorSwapChain, 0, &app.SwapChainLength, nullptr) );

  auto images = new XrSwapchainImageOpenGLESKHR[app.SwapChainLength];

  // Populate the swapchain image array.
  for(uint32_t i = 0; i < app.SwapChainLength; i++)
  images[i] = {XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR};

  OXR(xrEnumerateSwapchainImages(
    app.ColorSwapChain,
    app.SwapChainLength,
    &app.SwapChainLength,
    (XrSwapchainImageBaseHeader*)images
  ) );

  auto colorTextures = new GLuint[app.SwapChainLength];
  for(uint32_t i = 0; i < app.SwapChainLength; i++)
  colorTextures[i] = GLuint(images[i].image);

  app.AppRenderer.Create(
    format,
    width,
    height,
    NUM_MULTI_SAMPLES,
    app.SwapChainLength,
    colorTextures
  );

  delete[] images;
  delete[] colorTextures;

  androidApp->userData = &app;
  androidApp->onAppCmd = app_handle_cmd;

  bool stageBoundsDirty = true;

  SimpleXrInput* input = CreateSimpleXrInput(instance);
  input->BeginSession(app.Session);

  // Hook up extensions for passthrough

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrCreatePassthroughFB",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrCreatePassthroughFB
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrDestroyPassthroughFB",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrDestroyPassthroughFB
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrCreatePassthroughLayerFB",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrCreatePassthroughLayerFB
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrDestroyPassthroughLayerFB",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrDestroyPassthroughLayerFB
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrPassthroughLayerResumeFB",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrPassthroughLayerResumeFB
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrPassthroughLayerPauseFB",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrPassthroughLayerPauseFB
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrPassthroughLayerSetStyleFB",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrPassthroughLayerSetStyleFB
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrPassthroughStartFB",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrPassthroughStartFB
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrPassthroughPauseFB",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrPassthroughPauseFB
  ) );

  // Hook up extensions for spatial entity

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrCreateSpatialAnchorFB",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrCreateSpatialAnchorFB
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrGetSpaceUuidFB",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrGetSpaceUuidFB
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrEnumerateSpaceSupportedComponentsFB",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrEnumerateSpaceSupportedComponentsFB
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrGetSpaceComponentStatusFB",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrGetSpaceComponentStatusFB
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrSetSpaceComponentStatusFB",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrSetSpaceComponentStatusFB
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrSaveSpacesMETA",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrSaveSpacesMETA
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrEraseSpacesMETA",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrEraseSpacesMETA
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrQuerySpacesFB",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrQuerySpacesFB
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrRetrieveSpaceQueryResultsFB",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrRetrieveSpaceQueryResultsFB
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrDiscoverSpacesMETA",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrDiscoverSpacesMETA
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrRetrieveSpaceDiscoveryResultsMETA",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrRetrieveSpaceDiscoveryResultsMETA
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrCreateSpaceUserFB",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrCreateSpaceUserFB
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrGetSpaceUserIdFB",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrGetSpaceUserIdFB
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrDestroySpaceUserFB",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrDestroySpaceUserFB
  ) );

  OXR(xrGetInstanceProcAddr(
    instance,
    "xrShareSpacesFB",
    (PFN_xrVoidFunction*) &app.FunPtrs.xrShareSpacesFB
  ) );

  // Create and start passthrough

  XrPassthroughFB passthrough = XR_NULL_HANDLE;

  XrPassthroughLayerFB reconPassthroughLayer = XR_NULL_HANDLE;

  {
    XrPassthroughCreateInfoFB ptci = {XR_TYPE_PASSTHROUGH_CREATE_INFO_FB};
    XrResult result;
    OXR(result = app.FunPtrs.xrCreatePassthroughFB(app.Session, &ptci, &passthrough) );

    if(XR_SUCCEEDED(result) )
    {
      ALOGV("Creating passthrough layer");
      XrPassthroughLayerCreateInfoFB plci = {XR_TYPE_PASSTHROUGH_LAYER_CREATE_INFO_FB};
      plci.passthrough = passthrough;
      plci.purpose = XR_PASSTHROUGH_LAYER_PURPOSE_RECONSTRUCTION_FB;
      OXR(app.FunPtrs.xrCreatePassthroughLayerFB(app.Session, &plci, &reconPassthroughLayer) );
    }

    if(XR_SUCCEEDED(result) )
    {
      ALOGV("Setting passthrough style");
      XrPassthroughStyleFB style{XR_TYPE_PASSTHROUGH_STYLE_FB};
      OXR(app.FunPtrs.xrPassthroughLayerResumeFB(reconPassthroughLayer) );
      style.textureOpacityFactor = 0.5f;
      style.edgeColor = {0.0f, 0.0f, 0.0f, 0.0f};
      OXR(app.FunPtrs.xrPassthroughLayerSetStyleFB(reconPassthroughLayer, &style) );
    }

    if(result != XR_ERROR_FEATURE_UNSUPPORTED)
      OXR(result = app.FunPtrs.xrPassthroughStartFB(passthrough) );
  }

  // Initialize lists for Shared Spatial Anchors
  if( !app.ExternalDataHandler->LoadShareUserList(app.ShareUserList) )
  {
    ALOGW("Failed to load list of users to share Spatial Anchors with");
    app.ShareUserList.clear();
  }

  if( !app.ExternalDataHandler->LoadInboundSpatialAnchorList(app.InboundSpatialAnchorList) )
  {
    ALOGW("Failed to load list of Spatial Anchors shared with current user");
    app.InboundSpatialAnchorList.clear();
  }

  // Controller button states
  bool aButtonVal = false;
  bool aPrevButtonVal = false;
  bool bButtonVal = false;
  bool bPrevButtonVal = false;
  bool xButtonVal = false;
  bool xPrevButtonVal = false;
  bool yButtonVal = false;
  bool yPrevButtonVal = false;

  while(androidApp->destroyRequested == 0)
  {
    // Read all pending events.
    for(/*nop*/; /*nop*/; /*nop*/)
    {
      int events = 0;

      struct android_poll_source* source = nullptr;

      // If the timeout is zero, returns immediately without blocking.
      // If the timeout is negative, waits indefinitely until an event appears.
      const int timeoutMilliseconds =
        (app.Resumed == false && app.SessionActive == false && androidApp->destroyRequested == 0) ? -1 : 0;

      if(ALooper_pollAll(timeoutMilliseconds, NULL, &events, (void**)&source) < 0)
        break;

      // Process this event.
      if(source != NULL)
        source->process(androidApp, source);
    }

    app.HandleXrEvents();

    if(app.ShouldExit)
      break;

    if(app.SessionActive == false)
      continue;

    input->SyncActions();

    // Create the scene if not yet created.
    // The scene is created here to be able to show a loading icon.
    if(!app.AppRenderer.Scene.IsCreated() )
    {
      // Create the scene.
      app.AppRenderer.Scene.Create();
    }

    if(stageBoundsDirty)
    {
      UpdateStageBounds(app);
      stageBoundsDirty = false;
    }

    if(app.ShouldDiscoverAnchors)
    {
      // This is called after the app starts, or after Button X is pressed.
      app.AppRenderer.Scene.SpaceList.clear();
      DiscoverAnchors(app);
      DownloadAnchors(app);
      app.ShouldDiscoverAnchors = false;
    }

    // NOTE: OpenXR does not use the concept of frame indices. Instead,
    // XrWaitFrame returns the predicted display time.
    XrFrameWaitInfo waitFrameInfo = {XR_TYPE_FRAME_WAIT_INFO};

    XrFrameState frameState = {XR_TYPE_FRAME_STATE};

    OXR(xrWaitFrame(app.Session, &waitFrameInfo, &frameState) );

    // Get the HMD pose, predicted for the middle of the time period during which
    // the new eye images will be displayed. The number of frames predicted ahead
    // depends on the pipeline depth of the engine and the synthesis rate.
    // The better the prediction, the less black will be pulled in at the edges.
    XrFrameBeginInfo beginFrameDesc = {XR_TYPE_FRAME_BEGIN_INFO};
    OXR(xrBeginFrame(app.Session, &beginFrameDesc) );

    XrSpaceLocation loc = {XR_TYPE_SPACE_LOCATION};
    OXR(xrLocateSpace(app.HeadSpace, app.LocalSpace, frameState.predictedDisplayTime, &loc) );
    XrPosef xfLocalFromHead = loc.pose;

    XrViewState viewState = {XR_TYPE_VIEW_STATE, NULL};

    XrViewLocateInfo projectionInfo = {XR_TYPE_VIEW_LOCATE_INFO};
    projectionInfo.viewConfigurationType = app.ViewportConfig.viewConfigurationType;
    projectionInfo.displayTime = frameState.predictedDisplayTime;
    projectionInfo.space = app.HeadSpace;

    uint32_t projectionCapacityInput = NUM_EYES;
    uint32_t projectionCountOutput = projectionCapacityInput;

    OXR(xrLocateViews(
      app.Session,
      &projectionInfo,
      &viewState,
      projectionCapacityInput,
      &projectionCountOutput,
      projections
    ) );

    auto& scene = app.AppRenderer.Scene;
    scene.CubeData.clear();
    {
      ovrCubeData persistedCube;
      persistedCube.ColorScale *= 0.0f;
      persistedCube.ColorBias = OVR::Vector4f(1, 0.5, 0, 1); // Orange

      for(XrSpace space : scene.SpaceList)
      {
        // If anchor was placed, just update the anchor location
        // Updating it regularly will prevent drift
        XrSpaceLocation persistedAnchorLoc = {XR_TYPE_SPACE_LOCATION};
        XrResult res = XR_SUCCESS;

        OXR(res = xrLocateSpace(
          space,
          app.LocalSpace,
          frameState.predictedDisplayTime,
          &persistedAnchorLoc
        ) );

        if(res == XR_SUCCESS)
        {
          OVR::Posef localFromPersistedAnchor = FromXrPosef(persistedAnchorLoc.pose);
          persistedCube.Model = OVR::Matrix4f(localFromPersistedAnchor);
          persistedCube.Model *= OVR::Matrix4f::Scaling(0.01f, 0.01f, 0.05f);
          scene.CubeData.push_back(persistedCube);
        }
        else
        {
          ALOGE("Failed getting anchor pose");
        }
      }
    }

    // A Button: Place a world locked anchor.
    // B Button: Erase and Destroy all anchors in the scene.
    // X Button: Refresh anchors by querying them.
    // Y Button: Share all loaded anchors.
    if(input != nullptr)
    {
      aPrevButtonVal = aButtonVal;
      aButtonVal = input->A();
      if(aPrevButtonVal != aButtonVal && aPrevButtonVal)
        PlaceAnchor(app, input, frameState);

      bPrevButtonVal = bButtonVal;
      bButtonVal = input->B();
      if(bPrevButtonVal != bButtonVal && bPrevButtonVal)
        EraseAndDestroyAnchors(app);

      xPrevButtonVal = xButtonVal;
      xButtonVal = input->X();
      if(xPrevButtonVal != xButtonVal && xPrevButtonVal)
        app.ShouldDiscoverAnchors = true;

      yPrevButtonVal = yButtonVal;
      yButtonVal = input->Y();
      if(yPrevButtonVal != yButtonVal && yPrevButtonVal)
        SaveAnchorsAndTrySharing(app);
    }

    ovrAppRenderer::FrameIn frameIn;
    uint32_t chainIndex = 0;
    XrSwapchainImageAcquireInfo acquireInfo = {XR_TYPE_SWAPCHAIN_IMAGE_ACQUIRE_INFO, NULL};
    OXR(xrAcquireSwapchainImage(app.ColorSwapChain, &acquireInfo, &chainIndex) );
    frameIn.SwapChainIndex = int(chainIndex);

    XrPosef xfLocalFromEye[NUM_EYES];

    for(int eye = 0; eye < NUM_EYES; eye++)
    {
      // LOG_POSE( "viewTransform", &projectionInfo.projections[eye].viewTransform );
      XrPosef xfHeadFromEye = projections[eye].pose;
      XrPosef_Multiply(&xfLocalFromEye[eye], &xfLocalFromHead, &xfHeadFromEye);

      XrPosef xfEyeFromLocal;
      XrPosef_Invert(&xfEyeFromLocal, &xfLocalFromEye[eye] );

      XrMatrix4x4f viewMat{};
      XrMatrix4x4f_CreateFromRigidTransform(&viewMat, &xfEyeFromLocal);

      const XrFovf fov = projections[eye].fov;
      XrMatrix4x4f projMat;
      XrMatrix4x4f_CreateProjectionFov(&projMat, GRAPHICS_OPENGL_ES, fov, 0.1f, 0.0f);

      frameIn.View[eye] = OvrFromXr(viewMat);
      frameIn.Proj[eye] = OvrFromXr(projMat);
    }

    if(app.StageSpace != XR_NULL_HANDLE)
    {
      loc = {XR_TYPE_SPACE_LOCATION};

      OXR(xrLocateSpace(
      app.StageSpace, app.LocalSpace, frameState.predictedDisplayTime, &loc) );

      XrPosef xfLocalFromStage = loc.pose;

      frameIn.HasStage = true;
      frameIn.StagePose = OvrFromXr(xfLocalFromStage);
      frameIn.StageScale = app.StageBounds;
    }
    else
    {
      frameIn.HasStage = false;
    }

    XrSwapchainImageWaitInfo waitInfo = {XR_TYPE_SWAPCHAIN_IMAGE_WAIT_INFO};
    waitInfo.timeout = 1000000000; /* timeout in nanoseconds */
    XrResult res = xrWaitSwapchainImage(app.ColorSwapChain, &waitInfo);

    int retry = 0;
    while(res == XR_TIMEOUT_EXPIRED)
    {
      res = xrWaitSwapchainImage(app.ColorSwapChain, &waitInfo);
      retry++;

      ALOGV(
        " Retry xrWaitSwapchainImage %d times due to XR_TIMEOUT_EXPIRED (duration %f seconds)",
        retry,
        waitInfo.timeout * (1E-9)
      );
    }

    app.AppRenderer.RenderFrame(frameIn);

    XrSwapchainImageReleaseInfo releaseInfo = {XR_TYPE_SWAPCHAIN_IMAGE_RELEASE_INFO, NULL};
    OXR(xrReleaseSwapchainImage(app.ColorSwapChain, &releaseInfo) );

    // Set-up the compositor layers for this frame.
    // NOTE: Multiple independent layers are allowed, but they need to be added
    // in a depth consistent order.

    XrCompositionLayerProjectionView proj_views[2] = {};

    app.LayerCount = 0;
    memset(app.Layers, 0, sizeof(ovrCompositorLayer_Union) * ovrMaxLayerCount);

    // passthrough layer is backmost layer (if available)
    if(reconPassthroughLayer != XR_NULL_HANDLE)
    {
      XrCompositionLayerPassthroughFB passthrough_layer = {XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_FB};

      passthrough_layer.layerHandle = reconPassthroughLayer;
      passthrough_layer.flags = XR_COMPOSITION_LAYER_BLEND_TEXTURE_SOURCE_ALPHA_BIT;
      passthrough_layer.space = XR_NULL_HANDLE;
      app.Layers[app.LayerCount++].Passthrough = passthrough_layer;
    }

    XrCompositionLayerProjection proj_layer = {XR_TYPE_COMPOSITION_LAYER_PROJECTION};
    proj_layer.layerFlags = XR_COMPOSITION_LAYER_BLEND_TEXTURE_SOURCE_ALPHA_BIT;
    proj_layer.layerFlags |= XR_COMPOSITION_LAYER_CORRECT_CHROMATIC_ABERRATION_BIT;
    proj_layer.space = app.LocalSpace;
    proj_layer.viewCount = NUM_EYES;
    proj_layer.views = proj_views;

    for(int eye = 0; eye < NUM_EYES; eye++)
    {
      XrCompositionLayerProjectionView& proj_view = proj_views[eye];
      proj_view = {XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW};
      proj_view.pose = xfLocalFromEye[eye];
      proj_view.fov = projections[eye].fov;

      proj_view.subImage.swapchain = app.ColorSwapChain;
      proj_view.subImage.imageRect.offset.x = 0;
      proj_view.subImage.imageRect.offset.y = 0;
      proj_view.subImage.imageRect.extent.width = width;
      proj_view.subImage.imageRect.extent.height = height;
      proj_view.subImage.imageArrayIndex = eye;
    }

    app.Layers[app.LayerCount++].Projection = proj_layer;

    // Compose the layers for this frame.
    const XrCompositionLayerBaseHeader* layers[ovrMaxLayerCount] = {};

    for(int i = 0; i < app.LayerCount; i++)
      layers[i] = (const XrCompositionLayerBaseHeader*)&app.Layers[i];

    XrFrameEndInfo endFrameInfo = {XR_TYPE_FRAME_END_INFO};
    endFrameInfo.displayTime = frameState.predictedDisplayTime;
    endFrameInfo.environmentBlendMode = XR_ENVIRONMENT_BLEND_MODE_OPAQUE;
    endFrameInfo.layerCount = app.LayerCount;
    endFrameInfo.layers = layers;

    OXR(xrEndFrame(app.Session, &endFrameInfo) );
  }

  input->EndSession();

  delete input;

  app.AppRenderer.Destroy();

  OXR(xrDestroySwapchain(app.ColorSwapChain) );
  OXR(xrDestroySpace(app.HeadSpace) );
  OXR(xrDestroySpace(app.LocalSpace) );

  // StageSpace is optional.
  if(app.StageSpace != XR_NULL_HANDLE)
    OXR(xrDestroySpace(app.StageSpace) );

  OXR(xrDestroySession(app.Session) );

  app.Egl.DestroyContext();

  OXR(xrDestroyInstance(instance) );

  (*androidApp->activity->vm).DetachCurrentThread();
}
