
// anag.c

#include "header.h"

#define LOGI(...) do{ __android_log_print(ANDROID_LOG_INFO, "threaded_app", __VA_ARGS__); } while(0)
#define LOGE(...) do{ __android_log_print(ANDROID_LOG_ERROR, "threaded_app", __VA_ARGS__); } while(0)

#ifndef NDEBUG
#define LOGV(...) do{ __android_log_print(ANDROID_LOG_VERBOSE, "threaded_app", __VA_ARGS__); } while(0)
#else
#define LOGV(...) do{ 0; } while(0)
#endif

static void free_saved_state(struct android_app* app)
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

int8_t android_app_read_cmd(struct android_app* app)
{
  int8_t cmd = 0;

  if( !app)
    return -1;

  if(read(app->msgread, &cmd, sizeof(cmd) ) != sizeof(cmd) )
  {
    LOGE("No data on command pipe!");
  return -1;
  }

  if(cmd == APP_CMD_SAVE_STATE)
    free_saved_state(app);

    return cmd;
}

static void print_cur_config(struct android_app* app)
{
  char lang[2] = {0};
  char country[2] = {0};

  if( !app)
    return;

  AConfiguration_getLanguage(app->config, lang);
  AConfiguration_getCountry(app->config, country);

  LOGV("Config: mcc=%d mnc=%d lang=%c%c cnt=%c%c orien=%d touch=%d dens=%d "
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

void android_app_pre_exec_cmd(struct android_app* app, int8_t cmd)
{
  switch(cmd)
  {

  case APP_CMD_INPUT_CHANGED:
  {
    LOGV("APP_CMD_INPUT_CHANGED");

    if( !app)
      break;

    pthread_mutex_lock( &app->mutex);

    if(app->inputQueue)
      AInputQueue_detachLooper(app->inputQueue);

    app->inputQueue = app->pendingInputQueue;

    if(app->inputQueue)
    {
      LOGV("Attaching input queue to looper");

      AInputQueue_attachLooper(app->inputQueue, app->looper, LOOPER_ID_INPUT, 0, &app->inputPollSource);
    }

    pthread_cond_broadcast( &app->cond);
    pthread_mutex_unlock( &app->mutex);
  }
  break;

  case APP_CMD_INIT_WINDOW:
  {
    LOGV("APP_CMD_INIT_WINDOW");

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
    LOGV("APP_CMD_TERM_WINDOW");

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
    LOGV("activityState %d", cmd);

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
    LOGV("APP_CMD_CONFIG_CHANGED");

    if( !app)
      break;

    if(app->activity)
      AConfiguration_fromAssetManager(app->config, app->activity->assetManager);

    print_cur_config(app);
  }
  break;

  case APP_CMD_DESTROY:
  {
    LOGV("APP_CMD_DESTROY");

    if( !app)
      break;

    app->destroyRequested = 1;
  }
  break;

  }
}

void android_app_post_exec_cmd(struct android_app* app, int8_t cmd)
{
  switch(cmd)
  {

  case APP_CMD_TERM_WINDOW:
  {
    LOGV("APP_CMD_TERM_WINDOW");

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
    LOGV("APP_CMD_SAVE_STATE");

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

    free_saved_state(app);
  }
  break;

  }
}

void app_dummy()
{
}

static void android_app_destroy(struct android_app* app)
{
  LOGV("android_app_destroy!");

  if( !app)
    return;

  free_saved_state(app);
  pthread_mutex_lock( &app->mutex);

  if(app->inputQueue)
    AInputQueue_detachLooper(app->inputQueue);

  AConfiguration_delete(app->config);
  app->destroyed = 1;
  pthread_cond_broadcast( &app->cond);
  pthread_mutex_unlock( &app->mutex);
}

static void process_input(struct android_app* app, struct android_poll_source* source)
{
  AInputEvent* event = 0;

  if( !app)
    return;

  while(AInputQueue_getEvent(app->inputQueue, &event) >= 0)
  {
    int32_t handled = 0;

    LOGV("New input event: type=%d", AInputEvent_getType(event) );

    if(AInputQueue_preDispatchEvent(app->inputQueue, event) )
      continue;

    if(app->onInputEvent)
      handled = app->onInputEvent(app, event);

    AInputQueue_finishEvent(app->inputQueue, event, handled);
  }
}

static void process_cmd(struct android_app* app, struct android_poll_source* source)
{
  int8_t cmd = 0;

  if( !app)
    return;

  cmd = android_app_read_cmd(app);
  android_app_pre_exec_cmd(app, cmd);

  if(app->onAppCmd)
    app->onAppCmd(app, cmd);

  android_app_post_exec_cmd(app, cmd);
}

static void* android_app_entry(void* param)
{
  struct android_app* app = 0;
  ALooper* looper = 0;

  app = (struct android_app*)param;

  if( !app)
    return 0;

  app->config = AConfiguration_new();
  AConfiguration_fromAssetManager(app->config, app->activity->assetManager);

  print_cur_config(app);

  app->cmdPollSource.id = LOOPER_ID_MAIN;
  app->cmdPollSource.app = app;
  app->cmdPollSource.process = process_cmd;
  app->inputPollSource.id = LOOPER_ID_INPUT;
  app->inputPollSource.app = app;
  app->inputPollSource.process = process_input;

  looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
  ALooper_addFd(looper, app->msgread, LOOPER_ID_MAIN, ALOOPER_EVENT_INPUT, 0, &app->cmdPollSource);

  app->looper = looper;

  pthread_mutex_lock( &app->mutex);
  app->running = 1;
  pthread_cond_broadcast( &app->cond);
  pthread_mutex_unlock( &app->mutex);

  android_main(app);

  android_app_destroy(app);

  return 0;
}

static struct android_app* android_app_create(ANativeActivity* activity, void* savedState, size_t savedStateSize)
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
    LOGE("could not create pipe: %s", strerror(errno) );
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
  pthread_create( &app->thread, &attr, android_app_entry, app);

  pthread_mutex_lock( &app->mutex);

  while( !app->running)
    pthread_cond_wait( &app->cond, &app->mutex);

  pthread_mutex_unlock( &app->mutex);

  return app;
}

static void android_app_write_cmd(struct android_app* app, int8_t cmd)
{
  if( !app)
    return;

  if(write(app->msgwrite, &cmd, sizeof(cmd) ) != sizeof(cmd) )
  {
    LOGE("Failure writing app cmd: %s", strerror(errno) );
  }
}

static void android_app_set_input(struct android_app* app, AInputQueue* inputQueue)
{
  if( !app)
    return;

  pthread_mutex_lock( &app->mutex);
  app->pendingInputQueue = inputQueue;
  android_app_write_cmd(app, APP_CMD_INPUT_CHANGED);

  while(app->inputQueue != app->pendingInputQueue)
    pthread_cond_wait( &app->cond, &app->mutex);

  pthread_mutex_unlock( &app->mutex);
}

static void android_app_set_window(struct android_app* app, ANativeWindow* window)
{
  if( !app)
    return;

  pthread_mutex_lock( &app->mutex);

  if(app->pendingWindow)
    android_app_write_cmd(app, APP_CMD_TERM_WINDOW);

  app->pendingWindow = window;

  if(window)
    android_app_write_cmd(app, APP_CMD_INIT_WINDOW);

  while(app->window != app->pendingWindow)
    pthread_cond_wait( &app->cond, &app->mutex);

  pthread_mutex_unlock( &app->mutex);
}

static void android_app_set_activity_state(struct android_app* app, int8_t cmd)
{
  if( !app)
    return;

  pthread_mutex_lock( &app->mutex);
  android_app_write_cmd(app, cmd);

  while(app->activityState != cmd)
    pthread_cond_wait( &app->cond, &app->mutex);

  pthread_mutex_unlock( &app->mutex);
}

static void android_app_free(struct android_app* app)
{
  if( !app)
    return;

  pthread_mutex_lock( &app->mutex);
  android_app_write_cmd(app, APP_CMD_DESTROY);

  while( !app->destroyed)
    pthread_cond_wait( &app->cond, &app->mutex);

  pthread_mutex_unlock( &app->mutex);

  close(app->msgread);
  close(app->msgwrite);
  pthread_cond_destroy( &app->cond);
  pthread_mutex_destroy( &app->mutex);
  free(app);
}

static struct android_app* ToApp(ANativeActivity* activity)
{
  struct android_app* app = 0;

  if( !activity)
    return 0;

  app = (struct android_app*)activity->instance;

  return app;
}

static void onDestroy(ANativeActivity* activity)
{
  struct android_app* app = 0;

  LOGV("Destroy: %p", activity);

  app = ToApp(activity);

  if( !app)
    return;

  android_app_free(app);
}

static void onStart(ANativeActivity* activity)
{
  struct android_app* app = 0;

  LOGV("Start: %p", activity);

  app = ToApp(activity);

  if( !app)
    return;

  android_app_set_activity_state(app, APP_CMD_START);
}

static void onResume(ANativeActivity* activity)
{
  struct android_app* app = 0;

  LOGV("Resume: %p", activity);

  app = ToApp(activity);

  if( !app)
    return;

  android_app_set_activity_state(app, APP_CMD_RESUME);
}

static void* onSaveInstanceState(ANativeActivity* activity, size_t* outLen)
{
  struct android_app* app = 0;
  void* savedState = 0;

  LOGV("SaveInstanceState: %p", activity);

  app = ToApp(activity);

  if( !app)
    return 0;

  pthread_mutex_lock( &app->mutex);
  app->stateSaved = 0;
  android_app_write_cmd(app, APP_CMD_SAVE_STATE);

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

static void onPause(ANativeActivity* activity)
{
  struct android_app* app = 0;

  LOGV("Pause: %p", activity);

  app = ToApp(activity);

  if( !app)
    return;

  android_app_set_activity_state(app, APP_CMD_PAUSE);
}

static void onStop(ANativeActivity* activity)
{
  struct android_app* app = 0;

  LOGV("Stop: %p", activity);

  app = ToApp(activity);

  if( !app)
    return;

  android_app_set_activity_state(app, APP_CMD_STOP);
}

static void onConfigurationChanged(ANativeActivity* activity)
{
  struct android_app* app = 0;

  LOGV("ConfigurationChanged: %p", activity);

  app = ToApp(activity);

  if( !app)
    return;

  android_app_write_cmd(app, APP_CMD_CONFIG_CHANGED);
}

static void onContentRectChanged(ANativeActivity* activity, const ARect* r)
{
  struct android_app* app = 0;

  if(r)
    LOGV("ContentRectChanged: l=%d,t=%d,r=%d,b=%d", r->left, r->top, r->right, r->bottom);

  app = ToApp(activity);

  if( !app)
    return;

  pthread_mutex_lock(&app->mutex);

  if(r)
    app->contentRect = *r;
  else
    memset( &app->contentRect, 0, sizeof(ARect) );

  pthread_mutex_unlock( &app->mutex);

  android_app_write_cmd(app, APP_CMD_CONTENT_RECT_CHANGED);
}

static void onLowMemory(ANativeActivity* activity)
{
  struct android_app* app = 0;

  LOGV("LowMemory: %p", activity);

  app = ToApp(activity);

  if( !app)
    return;

  android_app_write_cmd(app, APP_CMD_LOW_MEMORY);
}

static void onWindowFocusChanged(ANativeActivity* activity, int focused)
{
  struct android_app* app = 0;

  LOGV("WindowFocusChanged: %p -- %d", activity, focused);

  app = ToApp(activity);

  if( !app)
    return;

  android_app_write_cmd(app, focused ? APP_CMD_GAINED_FOCUS : APP_CMD_LOST_FOCUS);
}

static void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window)
{
  struct android_app* app = 0;

  LOGV("NativeWindowCreated: %p -- %p", activity, window);

  app = ToApp(activity);

  if( !app)
    return;

  android_app_set_window(app, window);
}

static void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window)
{
  struct android_app* app = 0;

  LOGV("NativeWindowDestroyed: %p -- %p", activity, window);

  app = ToApp(activity);

  if( !app)
    return;

  android_app_set_window(app, 0);
}

static void onNativeWindowRedrawNeeded(ANativeActivity* activity, ANativeWindow* window)
{
  struct android_app* app = 0;

  LOGV("NativeWindowRedrawNeeded: %p -- %p", activity, window);

  app = ToApp(activity);

  if( !app)
    return;

  android_app_write_cmd(ToApp(activity), APP_CMD_WINDOW_REDRAW_NEEDED);
}

static void onNativeWindowResized(ANativeActivity* activity, ANativeWindow* window)
{
  struct android_app* app = 0;

  LOGV("NativeWindowResized: %p -- %p", activity, window);

  app = ToApp(activity);

  if( !app)
    return;

  android_app_write_cmd(app, APP_CMD_WINDOW_RESIZED);
}

static void onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue)
{
  struct android_app* app = 0;

  LOGV("InputQueueCreated: %p -- %p", activity, queue);

  app = ToApp(activity);

  if( !app)
    return;

  android_app_set_input(app, queue);
}

static void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue)
{
  struct android_app* app = 0;

  LOGV("InputQueueDestroyed: %p -- %p", activity, queue);

  app = ToApp(activity);

  if( !app)
    return;

  android_app_set_input(app, 0);
}

JNIEXPORT void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize)
{
  LOGV("Creating: %p", activity);

  if( !activity)
    return;

  if(activity->callbacks)
  {
    activity->callbacks->onConfigurationChanged = onConfigurationChanged;
    activity->callbacks->onContentRectChanged = onContentRectChanged;
    activity->callbacks->onDestroy = onDestroy;
    activity->callbacks->onInputQueueCreated = onInputQueueCreated;
    activity->callbacks->onInputQueueDestroyed = onInputQueueDestroyed;
    activity->callbacks->onLowMemory = onLowMemory;
    activity->callbacks->onNativeWindowCreated = onNativeWindowCreated;
    activity->callbacks->onNativeWindowDestroyed = onNativeWindowDestroyed;
    activity->callbacks->onNativeWindowRedrawNeeded = onNativeWindowRedrawNeeded;
    activity->callbacks->onNativeWindowResized = onNativeWindowResized;
    activity->callbacks->onPause = onPause;
    activity->callbacks->onResume = onResume;
    activity->callbacks->onSaveInstanceState = onSaveInstanceState;
    activity->callbacks->onStart = onStart;
    activity->callbacks->onStop = onStop;
    activity->callbacks->onWindowFocusChanged = onWindowFocusChanged;
  }

  activity->instance = android_app_create(activity, savedState, savedStateSize);
}
