
// main.cpp

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <exception>
#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <numeric>
#include <set>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>

#include <time.h>
#include <string.h>

#include <android/log.h>

#include <poll.h>
#include <pthread.h>
#include <sched.h>

#include <android/configuration.h>
#include <android/looper.h>
#include <android/native_activity.h>

#include "anag.h"

#include <android/native_window.h>
#include <jni.h>
#include <sys/system_properties.h>

#define XR_USE_GRAPHICS_API_VULKAN 1

#define XR_USE_PLATFORM_ANDROID 1

#define VK_USE_PLATFORM_ANDROID_KHR 1

class _jobject;
typedef _jobject* jobject;

#include "vulkan.h"
#include "vk_sdk_platform.h"

#include "openxr_platform_defines.h"
#include "openxr.h"
#include "openxr_platform.h"
#include "openxr_loader_negotiation.h"
#include "openxr_reflection.h"
#include "openxr_reflection_structs.h"
#include "openxr_reflection_parent_structs.h"

#include <string>
#include <locale>
#include <algorithm>
#include <memory>
#include <stdarg.h>
#include <stddef.h>

class _jobject;
typedef _jobject* jobject;

#include "vulkan.h"
#include "vk_sdk_platform.h"

#include "openxr_platform_defines.h"
#include "openxr.h"
#include "openxr_platform.h"
#include "openxr_loader_negotiation.h"
#include "openxr_reflection.h"
#include "openxr_reflection_structs.h"
#include "openxr_reflection_parent_structs.h"

inline std::string Fmt(const char* fmt, ...);

inline const char* to_string(XrReferenceSpaceType e);
inline const char* to_string(XrViewConfigurationType e);
inline const char* to_string(XrEnvironmentBlendMode e);
inline const char* to_string(XrSessionState e);
inline const char* to_string(XrResult e);
inline const char* to_string(XrFormFactor e);

#include "logger.h"
#include "common.h"
#include "check.h"

#include "platformdata.h"
#include "options.h"
#include "platformplugin.h"
#include "graphicsplugin.h"
#include "openxr_program.h"

#include "vulkan_wrapper.h"

#include "xr_generated_dispatch_table_core.h"

extern struct XrGeneratedDispatchTableCore tableXr;

namespace
{

void ShowHelp()
{
  Log::Write(Log::Level::Info, "adb shell setprop debug.xr.graphicsPlugin OpenGLES | Vulkan");
  Log::Write(Log::Level::Info, "adb shell setprop debug.xr.formFactor Hmd | Handheld");
  Log::Write(Log::Level::Info, "adb shell setprop debug.xr.viewConfiguration Stereo | Mono");
  Log::Write(Log::Level::Info, "adb shell setprop debug.xr.blendMode Opaque | Additive | AlphaBlend");
}

bool UpdateOptionsFromSystemProperties(Options& options)
{
  options.GraphicsPlugin = "Vulkan";

  char value[PROP_VALUE_MAX] = {};

  if(__system_property_get("debug.xr.graphicsPlugin", value) != 0)
  {
    options.GraphicsPlugin = value;
  }

  if(__system_property_get("debug.xr.formFactor", value) != 0)
  {
    options.FormFactor = value;
  }

  if(__system_property_get("debug.xr.viewConfiguration", value) != 0)
  {
    options.ViewConfiguration = value;
  }

  if(__system_property_get("debug.xr.blendMode", value) != 0)
  {
    options.EnvironmentBlendMode = value;
  }

  try
  {
    options.ParseStrings();
  }
  catch(std::invalid_argument& ia)
  {
    Log::Write(Log::Level::Error, ia.what() );
    ShowHelp();
    return false;
  }

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

    std::shared_ptr<Options> options = std::make_shared<Options>();

    if(!UpdateOptionsFromSystemProperties(*options) )
      return;

    std::shared_ptr<PlatformData> data = std::make_shared<PlatformData>();
    data->applicationVM = app->activity->vm;
    data->applicationActivity = app->activity->clazz;

    bool requestRestart = false;
    bool exitRenderLoop = false;

    if(InitOpenXr() )
      Log::Write(Log::Level::Verbose, "xr 1");

    if(InitVulkan() )
      Log::Write(Log::Level::Verbose, "vk 1");

    // Create platform-specific implementation.
    std::shared_ptr<IPlatformPlugin> platformPlugin = CreatePlatformPlugin(options, data);

    // Create graphics API implementation.
    std::shared_ptr<IGraphicsPlugin> graphicsPlugin = CreateGraphicsPlugin(options, platformPlugin);

    // Initialize the OpenXR program.
    std::shared_ptr<IOpenXrProgram> program = CreateOpenXrProgram(options, platformPlugin, graphicsPlugin);

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

    program->CreateInstance();
    program->InitializeSystem();

    options->SetEnvironmentBlendMode(program->GetPreferredBlendMode() );
    UpdateOptionsFromSystemProperties(*options);
    platformPlugin->UpdateOptions(options);
    graphicsPlugin->UpdateOptions(options);

    program->InitializeDevice();
    program->InitializeSession();
    program->CreateSwapchains();

    while(app->destroyRequested == 0)
    {
      // Read all pending events.
      for(;;)
      {
        int events = 0;
        struct android_poll_source* source = 0;

        // If the timeout is zero, returns immediately without blocking.
        // If the timeout is negative, waits indefinitely until an event appears.
        const int timeoutMilliseconds = (!appState.Resumed && !program->IsSessionRunning() && app->destroyRequested == 0) ? -1 : 0;

        if(ALooper_pollOnce(timeoutMilliseconds, nullptr, &events, (void**)&source) < 0)
          break;

        // Process this event.
        if(source != nullptr)
          source->process(app, source);
      }

      program->PollEvents(&exitRenderLoop, &requestRestart);

      if(exitRenderLoop)
      {
        ANativeActivity_finish(app->activity);
        continue;
      }

      if(!program->IsSessionRunning() )
      {
        // Throttle loop since xrWaitFrame won't be called.
        std::this_thread::sleep_for(std::chrono::milliseconds(250) );
        continue;
      }

      program->PollActions();
      program->RenderFrame();
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
