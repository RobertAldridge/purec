
// main.cpp

#include "header.h"

namespace
{

void ShowHelp()
{
  Log::Write(Log::Level::Info, "adb shell setprop debug.xr.graphicsPlugin OpenGLES | Vulkan");
  Log::Write(Log::Level::Info, "adb shell setprop debug.xr.formFactor Hmd | Handheld");
  Log::Write(Log::Level::Info, "adb shell setprop debug.xr.viewConfiguration Stereo | Mono");
  Log::Write(Log::Level::Info, "adb shell setprop debug.xr.blendMode Opaque | Additive | AlphaBlend");
}

bool UpdateOptionsFromSystemProperties()
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

}  // namespace

struct AndroidAppState
{
  ANativeWindow* NativeWindow = nullptr;
  bool Resumed = false;
};

/**
 * Process the next main command.
 */
static void app_handle_cmd(struct android_app* app, int32_t cmd)
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
    Log::Write(Log::Level::Info, "onStart()");
    break;
  }

  case APP_CMD_RESUME:
  {
    Log::Write(Log::Level::Info, "onResume()");
    Log::Write(Log::Level::Info, "APP_CMD_RESUME");
    appState->Resumed = true;
    break;
  }

  case APP_CMD_PAUSE:
  {
    Log::Write(Log::Level::Info, "onPause()");
    Log::Write(Log::Level::Info, "APP_CMD_PAUSE");
    appState->Resumed = false;
    break;
  }

  case APP_CMD_STOP:
  {
    Log::Write(Log::Level::Info, "onStop()");
    Log::Write(Log::Level::Info, "APP_CMD_STOP");
    break;
  }

  case APP_CMD_DESTROY:
  {
    Log::Write(Log::Level::Info, "onDestroy()");
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

/**
 * This is the main entry point of a native application that is using
 * anag.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* app)
{
  try
  {
    JNIEnv* Env;
    app->activity->vm->AttachCurrentThread(&Env, nullptr);

    AndroidAppState appState = {};

    app->userData = &appState;
    app->onAppCmd = app_handle_cmd;

    if( !UpdateOptionsFromSystemProperties() )
      return;

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

    UpdateOptionsFromSystemProperties();

	AndroidPlatformPlugin_UpdateOptions();

    VulkanGraphicsPlugin_VulkanGraphicsPluginUpdateOptions();

    OpenXrProgram_OpenXrProgramInitializeDevice();
    OpenXrProgram_OpenXrProgramInitializeSession();
    OpenXrProgram_OpenXrProgramCreateSwapchains();

    while(app->destroyRequested == 0)
    {
      // Read all pending events.
      for(;;)
      {
        int events = 0;
        struct android_poll_source* source = 0;

        // If the timeout is zero, returns immediately without blocking.
        // If the timeout is negative, waits indefinitely until an event appears.
        const int timeoutMilliseconds = (!appState.Resumed && !OpenXrProgram_OpenXrProgramIsSessionRunning() && app->destroyRequested == 0) ? -1 : 0;

        if(ALooper_pollOnce(timeoutMilliseconds, nullptr, &events, (void**)&source) < 0)
          break;

        // Process this event.
        if(source != nullptr)
          source->process(app, source);
      }

      OpenXrProgram_OpenXrProgramPollEvents( &exitRenderLoop, &requestRestart);

      if(exitRenderLoop)
      {
        ANativeActivity_finish(app->activity);
        continue;
      }

      if( !OpenXrProgram_OpenXrProgramIsSessionRunning() )
      {
        // Throttle loop since xrWaitFrame won't be called.
        std::this_thread::sleep_for(std::chrono::milliseconds(250) );
        continue;
      }

      OpenXrProgram_OpenXrProgramPollActions();
      OpenXrProgram_OpenXrProgramRenderFrame();
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
}
