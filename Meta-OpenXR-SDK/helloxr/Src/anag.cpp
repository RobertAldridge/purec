
// anag.cpp

#include "header.h"

void AnagShowHelpBlah()
{
  Log::Write(Log::Level::Info, "adb shell setprop debug.xr.graphicsPlugin OpenGLES | Vulkan");
  Log::Write(Log::Level::Info, "adb shell setprop debug.xr.formFactor Hmd | Handheld");
  Log::Write(Log::Level::Info, "adb shell setprop debug.xr.viewConfiguration Stereo | Mono");
  Log::Write(Log::Level::Info, "adb shell setprop debug.xr.blendMode Opaque | Additive | AlphaBlend");
}

bool AnagUpdateOptionsFromSystemProperties()
{
  // options.GraphicsPlugin
  // nop

  char value[PROP_VALUE_MAX] = {};

  if(__system_property_get("debug.xr.graphicsPlugin", value) != 0)
  {
    // options.GraphicsPlugin
    // nop
  }

  if(__system_property_get("debug.xr.formFactor", value) != 0)
  {
    // options.FormFactor
    // nop
  }

  if(__system_property_get("debug.xr.viewConfiguration", value) != 0)
  {
    // options.ViewConfiguration
    // nop
  }

  if(__system_property_get("debug.xr.blendMode", value) != 0)
  {
    // options.EnvironmentBlendMode
    // nop
  }

  // options
  // nop

  return true;
}

/**
 * Process the next main command.
 */
void anag_app_handle_cmd(struct android_app* app, int32_t cmd)
{
  AndroidAppState* appState = (AndroidAppState*)app->userData;

  switch(cmd)
  {

  // There is no APP_CMD_CREATE. The ANativeActivity creates the
  // application thread from onCreate(). The application thread
  // then calls android_main().
  case APP_CMD_START:
  {
    Log::Write(Log::Level::Info, "APP_CMD_START");
    Log::Write(Log::Level::Info, "anagOnStart()");
    break;
  }

  case APP_CMD_RESUME:
  {
    Log::Write(Log::Level::Info, "anagOnResume()");
    Log::Write(Log::Level::Info, "APP_CMD_RESUME");
    appState->Resumed = true;
    break;
  }

  case APP_CMD_PAUSE:
  {
    Log::Write(Log::Level::Info, "anagOnPause()");
    Log::Write(Log::Level::Info, "APP_CMD_PAUSE");
    appState->Resumed = false;
    break;
  }

  case APP_CMD_STOP:
  {
    Log::Write(Log::Level::Info, "anagOnStop()");
    Log::Write(Log::Level::Info, "APP_CMD_STOP");
    break;
  }

  case APP_CMD_DESTROY:
  {
    Log::Write(Log::Level::Info, "anagOnDestroy()");
    Log::Write(Log::Level::Info, "APP_CMD_DESTROY");
    appState->NativeWindow = NULL;
    break;
  }

  case APP_CMD_INIT_WINDOW:
  {
    Log::Write(Log::Level::Info, "surfaceCreated()");
    Log::Write(Log::Level::Info, "APP_CMD_INIT_WINDOW");
    appState->NativeWindow = app->window;
    break;
  }

  case APP_CMD_TERM_WINDOW:
  {
    Log::Write(Log::Level::Info, "surfaceDestroyed()");
    Log::Write(Log::Level::Info, "APP_CMD_TERM_WINDOW");
    appState->NativeWindow = NULL;
    break;
  }

  }
}

//struct XrInstanceCreateInfoAndroidKHR
//{
//  XrStructureType type;
//  const void* next;
//  void* applicationVM;
//  void* applicationActivity;
//};

XrInstanceCreateInfoAndroidKHR instanceCreateInfoAndroid {XR_TYPE_INSTANCE_CREATE_INFO_ANDROID_KHR, 0, 0, 0};

void anag_free_saved_state(struct android_app* app)
{
  if( !app)
    return;

  pthread_mutex_lock( &app->mutex);

  if(app->savedState)
  {
    free(app->savedState);
    app->savedState = 0;
    app->savedStateSize = 0;
  }

  pthread_mutex_unlock( &app->mutex);
}

int8_t anag_android_app_read_cmd(struct android_app* app)
{
  int8_t cmd = 0;

  if( !app)
    return -1;

  if(read(app->msgread, &cmd, sizeof(cmd) ) != sizeof(cmd) )
  {
    ANAG_LOGE("No data on command pipe!");
  return -1;
  }

  if(cmd == APP_CMD_SAVE_STATE)
    anag_free_saved_state(app);

    return cmd;
}

void anag_print_cur_config(struct android_app* app)
{
  char lang[2] = {0};
  char country[2] = {0};

  if( !app)
    return;

  AConfiguration_getLanguage(app->config, lang);
  AConfiguration_getCountry(app->config, country);

  ANAG_LOGV("Config: mcc=%d mnc=%d lang=%c%c cnt=%c%c orien=%d touch=%d dens=%d "
    "keys=%d nav=%d keysHid=%d navHid=%d sdk=%d size=%d long=%d "
    "modetype=%d modenight=%d",
    AConfiguration_getMcc(app->config),
    AConfiguration_getMnc(app->config),
    lang[0], lang[1], country[0], country[1],
    AConfiguration_getOrientation(app->config),
    AConfiguration_getTouchscreen(app->config),
    AConfiguration_getDensity(app->config),
    AConfiguration_getKeyboard(app->config),
    AConfiguration_getNavigation(app->config),
    AConfiguration_getKeysHidden(app->config),
    AConfiguration_getNavHidden(app->config),
    AConfiguration_getSdkVersion(app->config),
    AConfiguration_getScreenSize(app->config),
    AConfiguration_getScreenLong(app->config),
    AConfiguration_getUiModeType(app->config),
    AConfiguration_getUiModeNight(app->config) );
}

void anag_android_app_pre_exec_cmd(struct android_app* app, int8_t cmd)
{
  switch(cmd)
  {

  case APP_CMD_INPUT_CHANGED:
  {
    ANAG_LOGV("APP_CMD_INPUT_CHANGED");

    if( !app)
      break;

    pthread_mutex_lock( &app->mutex);

    if(app->inputQueue)
      AInputQueue_detachLooper(app->inputQueue);

    app->inputQueue = app->pendingInputQueue;

    if(app->inputQueue)
    {
      ANAG_LOGV("Attaching input queue to looper");

      AInputQueue_attachLooper(app->inputQueue, app->looper, LOOPER_ID_INPUT, 0, &app->inputPollSource);
    }

    pthread_cond_broadcast( &app->cond);
    pthread_mutex_unlock( &app->mutex);
  }
  break;

  case APP_CMD_INIT_WINDOW:
  {
    ANAG_LOGV("APP_CMD_INIT_WINDOW");

    if( !app)
      break;

    pthread_mutex_lock( &app->mutex);

    app->window = app->pendingWindow;

    pthread_cond_broadcast( &app->cond);
    pthread_mutex_unlock( &app->mutex);
  }
  break;

  case APP_CMD_TERM_WINDOW:
  {
    ANAG_LOGV("APP_CMD_TERM_WINDOW");

    if( !app)
      break;

    pthread_cond_broadcast( &app->cond);
  }
  break;

  case APP_CMD_RESUME:
  case APP_CMD_START:
  case APP_CMD_PAUSE:
  case APP_CMD_STOP:
  {
    ANAG_LOGV("activityState %d", cmd);

    if( !app)
      break;

    pthread_mutex_lock( &app->mutex);

    app->activityState = cmd;

    pthread_cond_broadcast( &app->cond);
    pthread_mutex_unlock( &app->mutex);
  }
  break;

  case APP_CMD_CONFIG_CHANGED:
  {
    ANAG_LOGV("APP_CMD_CONFIG_CHANGED");

    if( !app)
      break;

    if(app->activity)
      AConfiguration_fromAssetManager(app->config, app->activity->assetManager);

    anag_print_cur_config(app);
  }
  break;

  case APP_CMD_DESTROY:
  {
    ANAG_LOGV("APP_CMD_DESTROY");

    if( !app)
      break;

    app->destroyRequested = 1;
  }
  break;

  }
}

void anag_android_app_post_exec_cmd(struct android_app* app, int8_t cmd)
{
  switch(cmd)
  {

  case APP_CMD_TERM_WINDOW:
  {
    ANAG_LOGV("APP_CMD_TERM_WINDOW");

    if( !app)
      return;

    pthread_mutex_lock( &app->mutex);
    app->window = 0;
    pthread_cond_broadcast( &app->cond);
    pthread_mutex_unlock( &app->mutex);
  }
  break;

  case APP_CMD_SAVE_STATE:
  {
    ANAG_LOGV("APP_CMD_SAVE_STATE");

    if( !app)
      return;

    pthread_mutex_lock( &app->mutex);
    app->stateSaved = 1;
    pthread_cond_broadcast( &app->cond);
    pthread_mutex_unlock( &app->mutex);
  }
  break;

  case APP_CMD_RESUME:
  {
    if( !app)
      return;

    anag_free_saved_state(app);
  }
  break;

  }
}

//void anag_app_dummy()
//{
//}

void anag_android_app_destroy(struct android_app* app)
{
  ANAG_LOGV("anag_android_app_destroy!");

  if( !app)
    return;

  anag_free_saved_state(app);
  pthread_mutex_lock( &app->mutex);

  if(app->inputQueue)
    AInputQueue_detachLooper(app->inputQueue);

  AConfiguration_delete(app->config);
  app->destroyed = 1;
  pthread_cond_broadcast( &app->cond);
  pthread_mutex_unlock( &app->mutex);
}

void anag_process_input(struct android_app* app, struct android_poll_source* source)
{
  AInputEvent* event = 0;

  if( !app)
    return;

  while(AInputQueue_getEvent(app->inputQueue, &event) >= 0)
  {
    int32_t handled = 0;

    ANAG_LOGV("New input event: type=%d", AInputEvent_getType(event) );

    if(AInputQueue_preDispatchEvent(app->inputQueue, event) )
      continue;

    if(app->onInputEvent)
      handled = app->onInputEvent(app, event);

    AInputQueue_finishEvent(app->inputQueue, event, handled);
  }
}

void anag_process_cmd(struct android_app* app, struct android_poll_source* source)
{
  int8_t cmd = 0;

  if( !app)
    return;

  cmd = anag_android_app_read_cmd(app);
  anag_android_app_pre_exec_cmd(app, cmd);

  if(app->onAppCmd)
    app->onAppCmd(app, cmd);

  anag_android_app_post_exec_cmd(app, cmd);
}

void* anag_android_app_entry(void* param)
{
  struct android_app* app = 0;
  ALooper* looper = 0;

  app = (struct android_app*)param;

  if( !app)
    return 0;

  app->config = AConfiguration_new();
  AConfiguration_fromAssetManager(app->config, app->activity->assetManager);

  anag_print_cur_config(app);

  app->cmdPollSource.id = LOOPER_ID_MAIN;
  app->cmdPollSource.app = app;
  app->cmdPollSource.process = anag_process_cmd;
  app->inputPollSource.id = LOOPER_ID_INPUT;
  app->inputPollSource.app = app;
  app->inputPollSource.process = anag_process_input;

  looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
  ALooper_addFd(looper, app->msgread, LOOPER_ID_MAIN, ALOOPER_EVENT_INPUT, 0, &app->cmdPollSource);

  app->looper = looper;

  pthread_mutex_lock( &app->mutex);
  app->running = 1;
  pthread_cond_broadcast( &app->cond);
  pthread_mutex_unlock( &app->mutex);

try
{
  JNIEnv* Env = 0;

  app->activity->vm->AttachCurrentThread(&Env, nullptr);

  AndroidAppState appState = {};

  app->userData = &appState;
  app->onAppCmd = anag_app_handle_cmd;

  if( !AnagUpdateOptionsFromSystemProperties() )
    return 0;

  instanceCreateInfoAndroid.applicationVM = app->activity->vm;
  instanceCreateInfoAndroid.applicationActivity = app->activity->clazz;

  bool requestRestart = false;
  bool exitRenderLoop = false;

  if(InitOpenXr() )
    Log::Write(Log::Level::Verbose, "xr 1");

  if(InitVulkan() )
    Log::Write(Log::Level::Verbose, "vk 1");

  CreatePlatformPlugin_Android();

  // Create graphics API implementation.
  VulkanGraphicsPlugin_CreateGraphicsPlugin_Vulkan();

  // Initialize the OpenXR program.
  OpenXrProgram_CreateOpenXrProgram();

  // Initialize the loader for this platform
  PFN_xrInitializeLoaderKHR initializeLoader = nullptr;

  XrResult result = XR_ERROR_VALIDATION_FAILURE;

  if(tableXr.GetInstanceProcAddr)
    result = tableXr.GetInstanceProcAddr(XR_NULL_HANDLE, "xrInitializeLoaderKHR", (PFN_xrVoidFunction*) &initializeLoader);

  if(XR_SUCCEEDED(result) && initializeLoader)
  {
    XrLoaderInitInfoAndroidKHR loaderInitInfoAndroid = {XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR};

    loaderInitInfoAndroid.applicationVM = app->activity->vm;
    loaderInitInfoAndroid.applicationContext = app->activity->clazz;

    initializeLoader( (const XrLoaderInitInfoBaseHeaderKHR*) &loaderInitInfoAndroid);
  }

  OpenXrProgram_OpenXrProgramCreateInstance();
  OpenXrProgram_OpenXrProgramInitializeSystem();

  Options_SetEnvironmentBlendMode(OpenXrProgram_OpenXrProgramGetPreferredBlendMode() );

  AnagUpdateOptionsFromSystemProperties();

  AndroidPlatformPlugin_UpdateOptions();

  VulkanGraphicsPlugin_VulkanGraphicsPluginUpdateOptions();

  OpenXrProgram_OpenXrProgramInitializeDevice();
  OpenXrProgram_OpenXrProgramInitializeSession();
  OpenXrProgram_OpenXrProgramCreateSwapchains();

  while(app->destroyRequested == 0)
  {
    bool result = false;

    // Read all pending events.
    for(;;)
    {
      int events = 0;
      struct android_poll_source* source = 0;

      // If the timeout is zero, returns immediately without blocking.
      // If the timeout is negative, waits indefinitely until an event appears.
      const int timeoutMilliseconds = (!appState.Resumed && !gOpenXrProgramSessionRunning && app->destroyRequested == 0) ? -1 : 0;

      if(ALooper_pollOnce(timeoutMilliseconds, nullptr, &events, (void**)&source) < 0)
        break;

      // Process this event.
      if(source != nullptr)
        source->process(app, source);
    }

    //OpenXrProgram_OpenXrProgramPollEvents( &exitRenderLoop, &requestRestart);

    // void OpenXrProgram_OpenXrProgramPollEvents(bool* exitRenderLoop, bool* requestRestart)

    exitRenderLoop = false;
    requestRestart = false;

    for(XrEventDataBaseHeader* event = (XrEventDataBaseHeader*)OpenXrProgram_OpenXrProgramTryReadNextEvent(); !exitRenderLoop && event; event = (XrEventDataBaseHeader*)OpenXrProgram_OpenXrProgramTryReadNextEvent() )
    {
      switch(event->type)
      {

      case XR_TYPE_EVENT_DATA_INSTANCE_LOSS_PENDING:
      {
        const auto& instanceLossPending = *reinterpret_cast<const XrEventDataInstanceLossPending*>(event);
        Log::Write(Log::Level::Warning, Fmt("XrEventDataInstanceLossPending by %lld", instanceLossPending.lossTime) );
        exitRenderLoop = true;
        requestRestart = true;
        break;
      }

      case XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED:
      {
        auto sessionStateChangedEvent = *reinterpret_cast<const XrEventDataSessionStateChanged*>(event);
        OpenXrProgram_OpenXrProgramHandleSessionStateChangedEvent(sessionStateChangedEvent, &exitRenderLoop, &requestRestart);
        break;
      }

      case XR_TYPE_EVENT_DATA_INTERACTION_PROFILE_CHANGED:
      {
        OpenXrProgram_OpenXrProgramLogActionSourceName(gOpenXrProgramInputState_InputState_grabAction, "Grab");
        OpenXrProgram_OpenXrProgramLogActionSourceName(gOpenXrProgramInputState_InputState_quitAction, "Quit");
        OpenXrProgram_OpenXrProgramLogActionSourceName(gOpenXrProgramInputState_InputState_poseAction, "Pose");
        OpenXrProgram_OpenXrProgramLogActionSourceName(gOpenXrProgramInputState_InputState_vibrateAction, "Vibrate");
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

    if(exitRenderLoop)
    {
      ANativeActivity_finish(app->activity);
      continue;
    }

    if( !gOpenXrProgramSessionRunning)
    {
      // Throttle loop since xrWaitFrame won't be called.
      std::this_thread::sleep_for(std::chrono::milliseconds(250) );
      continue;
    }

    //OpenXrProgram_OpenXrProgramPollActions();

    // void OpenXrProgram_OpenXrProgramPollActions()

    gOpenXrProgramInputState_InputState_handActive = {XR_FALSE, XR_FALSE};

    // Sync actions
    const XrActiveActionSet activeActionSet {gOpenXrProgramInputState_InputState_actionSet, XR_NULL_PATH};

    XrActionsSyncInfo syncInfo {XR_TYPE_ACTIONS_SYNC_INFO};
    syncInfo.countActiveActionSets = 1;
    syncInfo.activeActionSets = &activeActionSet;

    if(tableXr.SyncActions)
      CHECK_XRCMD(tableXr.SyncActions(gXrSession, &syncInfo) );

    // Get pose and grab action state and start haptic vibrate when hand is 90% squeezed.
    for(auto hand : {Side_LEFT, Side_RIGHT} )
    {
      XrActionStateGetInfo getInfo {XR_TYPE_ACTION_STATE_GET_INFO};

      getInfo.action = gOpenXrProgramInputState_InputState_grabAction;
      getInfo.subactionPath = gOpenXrProgramInputState_InputState_handSubactionPath[hand];

      XrActionStateFloat grabValue {XR_TYPE_ACTION_STATE_FLOAT};

      if(tableXr.GetActionStateFloat)
        CHECK_XRCMD(tableXr.GetActionStateFloat(gXrSession, &getInfo, &grabValue) );

      if(grabValue.isActive == XR_TRUE)
      {
        // Scale the rendered hand by 1.0f (open) to 0.5f (fully squeezed).
        gOpenXrProgramInputState_InputState_handScale[hand] = 1.0f - 0.5f * grabValue.currentState;

        if(grabValue.currentState > 0.9f)
        {
          XrHapticVibration vibration {XR_TYPE_HAPTIC_VIBRATION};
          vibration.amplitude = 0.5;
          vibration.duration = XR_MIN_HAPTIC_DURATION;
          vibration.frequency = XR_FREQUENCY_UNSPECIFIED;

          XrHapticActionInfo hapticActionInfo {XR_TYPE_HAPTIC_ACTION_INFO};
          hapticActionInfo.action = gOpenXrProgramInputState_InputState_vibrateAction;
          hapticActionInfo.subactionPath = gOpenXrProgramInputState_InputState_handSubactionPath[hand];

          if(tableXr.ApplyHapticFeedback)
            CHECK_XRCMD(tableXr.ApplyHapticFeedback(gXrSession, &hapticActionInfo, (XrHapticBaseHeader*) &vibration) );
        }
      }

      getInfo.action = gOpenXrProgramInputState_InputState_poseAction;

      XrActionStatePose poseState {XR_TYPE_ACTION_STATE_POSE};

      if(tableXr.GetActionStatePose)
        CHECK_XRCMD(tableXr.GetActionStatePose(gXrSession, &getInfo, &poseState) );

      gOpenXrProgramInputState_InputState_handActive[hand] = poseState.isActive;
    }

    // There were no subaction paths specified for the quit action, because we don't care which hand did it.
    XrActionStateGetInfo getInfo {XR_TYPE_ACTION_STATE_GET_INFO, nullptr, gOpenXrProgramInputState_InputState_quitAction, XR_NULL_PATH};
    XrActionStateBoolean quitValue {XR_TYPE_ACTION_STATE_BOOLEAN};

    if(tableXr.GetActionStateBoolean)
      CHECK_XRCMD(tableXr.GetActionStateBoolean(gXrSession, &getInfo, &quitValue) );

    if(quitValue.isActive == XR_TRUE && quitValue.changedSinceLastSync == XR_TRUE && quitValue.currentState == XR_TRUE && tableXr.RequestExitSession)
      CHECK_XRCMD(tableXr.RequestExitSession(gXrSession) );

    //OpenXrProgram_OpenXrProgramRenderFrame();

    // void OpenXrProgram_OpenXrProgramRenderFrame()

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
        if(OpenXrProgram_OpenXrProgramRenderLayer(frameState.predictedDisplayTime, projectionLayerViews, layer) )
          layers.push_back(reinterpret_cast<XrCompositionLayerBaseHeader*>(&layer) );
      }

      XrFrameEndInfo frameEndInfo {XR_TYPE_FRAME_END_INFO};
      frameEndInfo.displayTime = frameState.predictedDisplayTime;
      frameEndInfo.environmentBlendMode = gOptions_XrEnvironmentBlendMode;
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
        OpenXrProgram_OpenXrProgramRenderLayer(frameState.predictedDisplayTime, projectionLayerViews, layer);

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

  app->activity->vm->DetachCurrentThread();
}
catch(const std::exception& ex)
{
  Log::Write(Log::Level::Error, ex.what() );
}
catch(...)
{
  Log::Write(Log::Level::Error, "Unknown Error");
}

  anag_android_app_destroy(app);

  return 0;
}

struct android_app* anag_android_app_create(ANativeActivity* activity, void* savedState, size_t savedStateSize)
{
  struct android_app* app = 0;
  int msgpipe[2] = {0};

  app = (struct android_app*)calloc(1, sizeof(struct android_app) );
  if( !app)
    return 0;

  app->activity = activity;

  pthread_mutex_init( &app->mutex, 0);
  pthread_cond_init( &app->cond, 0);

  if(savedState)
  {
    app->savedState = malloc(savedStateSize);
    if( !app->savedState)
    {
      free(app);
      return 0;
    }

    app->savedStateSize = savedStateSize;

    if(app->savedState)
      memcpy(app->savedState, savedState, savedStateSize);
  }

  if(pipe(msgpipe) )
  {
    ANAG_LOGE("could not create pipe: %s", strerror(errno) );
    free(app->savedState);
    free(app);
    return 0;
  }

  app->msgread = msgpipe[0];
  app->msgwrite = msgpipe[1];

  pthread_attr_t attr;
  memset( &attr, 0, sizeof(pthread_attr_t) );

  pthread_attr_init( &attr);
  pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED);
  pthread_create( &app->thread, &attr, anag_android_app_entry, app);

  pthread_mutex_lock( &app->mutex);

  while( !app->running)
    pthread_cond_wait( &app->cond, &app->mutex);

  pthread_mutex_unlock( &app->mutex);

  return app;
}

void anag_android_app_write_cmd(struct android_app* app, int8_t cmd)
{
  if( !app)
    return;

  if(write(app->msgwrite, &cmd, sizeof(cmd) ) != sizeof(cmd) )
  {
    ANAG_LOGE("Failure writing app cmd: %s", strerror(errno) );
  }
}

void anag_android_app_set_input(struct android_app* app, AInputQueue* inputQueue)
{
  if( !app)
    return;

  pthread_mutex_lock( &app->mutex);
  app->pendingInputQueue = inputQueue;
  anag_android_app_write_cmd(app, APP_CMD_INPUT_CHANGED);

  while(app->inputQueue != app->pendingInputQueue)
    pthread_cond_wait( &app->cond, &app->mutex);

  pthread_mutex_unlock( &app->mutex);
}

void anag_android_app_set_window(struct android_app* app, ANativeWindow* window)
{
  if( !app)
    return;

  pthread_mutex_lock( &app->mutex);

  if(app->pendingWindow)
    anag_android_app_write_cmd(app, APP_CMD_TERM_WINDOW);

  app->pendingWindow = window;

  if(window)
    anag_android_app_write_cmd(app, APP_CMD_INIT_WINDOW);

  while(app->window != app->pendingWindow)
    pthread_cond_wait( &app->cond, &app->mutex);

  pthread_mutex_unlock( &app->mutex);
}

void anag_android_app_set_activity_state(struct android_app* app, int8_t cmd)
{
  if( !app)
    return;

  pthread_mutex_lock( &app->mutex);
  anag_android_app_write_cmd(app, cmd);

  while(app->activityState != cmd)
    pthread_cond_wait( &app->cond, &app->mutex);

  pthread_mutex_unlock( &app->mutex);
}

void anag_android_app_free(struct android_app* app)
{
  if( !app)
    return;

  pthread_mutex_lock( &app->mutex);
  anag_android_app_write_cmd(app, APP_CMD_DESTROY);

  while( !app->destroyed)
    pthread_cond_wait( &app->cond, &app->mutex);

  pthread_mutex_unlock( &app->mutex);

  close(app->msgread);
  close(app->msgwrite);
  pthread_cond_destroy( &app->cond);
  pthread_mutex_destroy( &app->mutex);
  free(app);
}

struct android_app* AnagToApp(ANativeActivity* activity)
{
  struct android_app* app = 0;

  if( !activity)
    return 0;

  app = (struct android_app*)activity->instance;

  return app;
}

void anagOnDestroy(ANativeActivity* activity)
{
  struct android_app* app = 0;

  ANAG_LOGV("Destroy: %p", activity);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_free(app);
}

void anagOnStart(ANativeActivity* activity)
{
  struct android_app* app = 0;

  ANAG_LOGV("Start: %p", activity);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_set_activity_state(app, APP_CMD_START);
}

void anagOnResume(ANativeActivity* activity)
{
  struct android_app* app = 0;

  ANAG_LOGV("Resume: %p", activity);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_set_activity_state(app, APP_CMD_RESUME);
}

void* anagOnSaveInstanceState(ANativeActivity* activity, size_t* outLen)
{
  struct android_app* app = 0;
  void* savedState = 0;

  ANAG_LOGV("SaveInstanceState: %p", activity);

  app = AnagToApp(activity);

  if( !app)
    return 0;

  pthread_mutex_lock( &app->mutex);
  app->stateSaved = 0;
  anag_android_app_write_cmd(app, APP_CMD_SAVE_STATE);

  while( !app->stateSaved)
    pthread_cond_wait( &app->cond, &app->mutex);

  if(app->savedState)
  {
    savedState = app->savedState;
    *outLen = app->savedStateSize;
    app->savedState = 0;
    app->savedStateSize = 0;
  }

  pthread_mutex_unlock( &app->mutex);

  return savedState;
}

void anagOnPause(ANativeActivity* activity)
{
  struct android_app* app = 0;

  ANAG_LOGV("Pause: %p", activity);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_set_activity_state(app, APP_CMD_PAUSE);
}

void anagOnStop(ANativeActivity* activity)
{
  struct android_app* app = 0;

  ANAG_LOGV("Stop: %p", activity);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_set_activity_state(app, APP_CMD_STOP);
}

void anagOnConfigurationChanged(ANativeActivity* activity)
{
  struct android_app* app = 0;

  ANAG_LOGV("ConfigurationChanged: %p", activity);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_write_cmd(app, APP_CMD_CONFIG_CHANGED);
}

void anagOnContentRectChanged(ANativeActivity* activity, const ARect* r)
{
  struct android_app* app = 0;

  if(r)
    ANAG_LOGV("ContentRectChanged: l=%d,t=%d,r=%d,b=%d", r->left, r->top, r->right, r->bottom);

  app = AnagToApp(activity);

  if( !app)
    return;

  pthread_mutex_lock(&app->mutex);

  if(r)
    app->contentRect = *r;
  else
    memset( &app->contentRect, 0, sizeof(ARect) );

  pthread_mutex_unlock( &app->mutex);

  anag_android_app_write_cmd(app, APP_CMD_CONTENT_RECT_CHANGED);
}

void anagOnLowMemory(ANativeActivity* activity)
{
  struct android_app* app = 0;

  ANAG_LOGV("LowMemory: %p", activity);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_write_cmd(app, APP_CMD_LOW_MEMORY);
}

void anagOnWindowFocusChanged(ANativeActivity* activity, int focused)
{
  struct android_app* app = 0;

  ANAG_LOGV("WindowFocusChanged: %p -- %d", activity, focused);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_write_cmd(app, focused ? APP_CMD_GAINED_FOCUS : APP_CMD_LOST_FOCUS);
}

void anagOnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window)
{
  struct android_app* app = 0;

  ANAG_LOGV("NativeWindowCreated: %p -- %p", activity, window);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_set_window(app, window);
}

void anagOnNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window)
{
  struct android_app* app = 0;

  ANAG_LOGV("NativeWindowDestroyed: %p -- %p", activity, window);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_set_window(app, 0);
}

void anagOnNativeWindowRedrawNeeded(ANativeActivity* activity, ANativeWindow* window)
{
  struct android_app* app = 0;

  ANAG_LOGV("NativeWindowRedrawNeeded: %p -- %p", activity, window);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_write_cmd(AnagToApp(activity), APP_CMD_WINDOW_REDRAW_NEEDED);
}

void anagOnNativeWindowResized(ANativeActivity* activity, ANativeWindow* window)
{
  struct android_app* app = 0;

  ANAG_LOGV("NativeWindowResized: %p -- %p", activity, window);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_write_cmd(app, APP_CMD_WINDOW_RESIZED);
}

void anagOnInputQueueCreated(ANativeActivity* activity, AInputQueue* queue)
{
  struct android_app* app = 0;

  ANAG_LOGV("InputQueueCreated: %p -- %p", activity, queue);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_set_input(app, queue);
}

void anagOnInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue)
{
  struct android_app* app = 0;

  ANAG_LOGV("InputQueueDestroyed: %p -- %p", activity, queue);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_set_input(app, 0);
}

extern "C" __attribute__ ( (visibility ("default") ) ) void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize)
{
  ANAG_LOGV("Creating: %p", activity);

  if( !activity)
    return;

  if(activity->callbacks)
  {
    activity->callbacks->onConfigurationChanged = anagOnConfigurationChanged;
    activity->callbacks->onContentRectChanged = anagOnContentRectChanged;
    activity->callbacks->onDestroy = anagOnDestroy;
    activity->callbacks->onInputQueueCreated = anagOnInputQueueCreated;
    activity->callbacks->onInputQueueDestroyed = anagOnInputQueueDestroyed;
    activity->callbacks->onLowMemory = anagOnLowMemory;
    activity->callbacks->onNativeWindowCreated = anagOnNativeWindowCreated;
    activity->callbacks->onNativeWindowDestroyed = anagOnNativeWindowDestroyed;
    activity->callbacks->onNativeWindowRedrawNeeded = anagOnNativeWindowRedrawNeeded;
    activity->callbacks->onNativeWindowResized = anagOnNativeWindowResized;
    activity->callbacks->onPause = anagOnPause;
    activity->callbacks->onResume = anagOnResume;
    activity->callbacks->onSaveInstanceState = anagOnSaveInstanceState;
    activity->callbacks->onStart = anagOnStart;
    activity->callbacks->onStop = anagOnStop;
    activity->callbacks->onWindowFocusChanged = anagOnWindowFocusChanged;
  }

  activity->instance = anag_android_app_create(activity, savedState, savedStateSize);
}
