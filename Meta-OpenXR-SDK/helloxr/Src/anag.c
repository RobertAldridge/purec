
// anag.c

#include <jni.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

#include <poll.h>
#include <pthread.h>
#include <sched.h>

#include <android/configuration.h>
#include <android/looper.h>
#include <android/native_activity.h>

#include "anag.h"

#include <android/log.h>

#define LOGI(...) do{ __android_log_print(ANDROID_LOG_INFO, "threaded_app", __VA_ARGS__); } while(0)
#define LOGE(...) do{ __android_log_print(ANDROID_LOG_ERROR, "threaded_app", __VA_ARGS__); } while(0)

#ifndef NDEBUG

#define LOGV(...) do{ __android_log_print(ANDROID_LOG_VERBOSE, "threaded_app", __VA_ARGS__); } while(0)

#else

#define LOGV(...) do{ 0; } while(0)

#endif

static void free_saved_state(struct android_app* android_app)
{
  if( !android_app)
    return;

  pthread_mutex_lock( &android_app->mutex);

  if(android_app->savedState)
  {
    free(android_app->savedState);
    android_app->savedState = 0;
    android_app->savedStateSize = 0;
  }

  pthread_mutex_unlock( &android_app->mutex);
}

int8_t android_app_read_cmd(struct android_app* android_app)
{
  int8_t cmd = 0;

  if( !android_app)
    return -1;

  if(read(android_app->msgread, &cmd, sizeof(cmd) ) == sizeof(cmd) )
  {
    switch(cmd)
    {

    case APP_CMD_SAVE_STATE:
    {
      free_saved_state(android_app);
    }
    break;

    }

    return cmd;
  }
  else
  {
    LOGE("No data on command pipe!");
  }

  return -1;
}

static void print_cur_config(struct android_app* android_app)
{
  char lang[2] = {0};
  char country[2] = {0};

  if( !android_app)
    return;

  AConfiguration_getLanguage(android_app->config, lang);
  AConfiguration_getCountry(android_app->config, country);

  LOGV("Config: mcc=%d mnc=%d lang=%c%c cnt=%c%c orien=%d touch=%d dens=%d "
  "keys=%d nav=%d keysHid=%d navHid=%d sdk=%d size=%d long=%d "
  "modetype=%d modenight=%d",
  AConfiguration_getMcc(android_app->config),
  AConfiguration_getMnc(android_app->config),
  lang[0], lang[1], country[0], country[1],
  AConfiguration_getOrientation(android_app->config),
  AConfiguration_getTouchscreen(android_app->config),
  AConfiguration_getDensity(android_app->config),
  AConfiguration_getKeyboard(android_app->config),
  AConfiguration_getNavigation(android_app->config),
  AConfiguration_getKeysHidden(android_app->config),
  AConfiguration_getNavHidden(android_app->config),
  AConfiguration_getSdkVersion(android_app->config),
  AConfiguration_getScreenSize(android_app->config),
  AConfiguration_getScreenLong(android_app->config),
  AConfiguration_getUiModeType(android_app->config),
  AConfiguration_getUiModeNight(android_app->config) );
}

void android_app_pre_exec_cmd(struct android_app* android_app, int8_t cmd)
{
  switch(cmd)
  {

  case APP_CMD_INPUT_CHANGED:
  {
    LOGV("APP_CMD_INPUT_CHANGED\n");

    if( !android_app)
      break;

    pthread_mutex_lock( &android_app->mutex);

    if(android_app->inputQueue)
      AInputQueue_detachLooper(android_app->inputQueue);

    android_app->inputQueue = android_app->pendingInputQueue;

    if(android_app->inputQueue && android_app->looper)
    {
      LOGV("Attaching input queue to looper");

      AInputQueue_attachLooper(android_app->inputQueue, android_app->looper, LOOPER_ID_INPUT, 0, &android_app->inputPollSource);
    }

    pthread_cond_broadcast( &android_app->cond);
    pthread_mutex_unlock( &android_app->mutex);
  }
  break;

  case APP_CMD_INIT_WINDOW:
  {
    LOGV("APP_CMD_INIT_WINDOW\n");

    if( !android_app)
      break;

    pthread_mutex_lock( &android_app->mutex);

    android_app->window = android_app->pendingWindow;

    pthread_cond_broadcast( &android_app->cond);
    pthread_mutex_unlock( &android_app->mutex);
  }
  break;

  case APP_CMD_TERM_WINDOW:
  {
    LOGV("APP_CMD_TERM_WINDOW\n");

    if( !android_app)
      break;

    pthread_cond_broadcast( &android_app->cond);
  }
  break;

  case APP_CMD_RESUME:
  case APP_CMD_START:
  case APP_CMD_PAUSE:
  case APP_CMD_STOP:
  {
    LOGV("activityState %d\n", cmd);

    if( !android_app)
      break;

    pthread_mutex_lock( &android_app->mutex);

    android_app->activityState = cmd;

    pthread_cond_broadcast( &android_app->cond);
    pthread_mutex_unlock( &android_app->mutex);
  }
  break;

  case APP_CMD_CONFIG_CHANGED:
  {
    LOGV("APP_CMD_CONFIG_CHANGED\n");

    if( !android_app)
      break;

    if(android_app->config && android_app->activity)
      AConfiguration_fromAssetManager(android_app->config, android_app->activity->assetManager);

    print_cur_config(android_app);
  }
  break;

  case APP_CMD_DESTROY:
  {
    LOGV("APP_CMD_DESTROY\n");

    if( !android_app)
      break;

    android_app->destroyRequested = 1;
  }
  break;

  }
}

void android_app_post_exec_cmd(struct android_app* android_app, int8_t cmd)
{
  switch(cmd)
  {

  case APP_CMD_TERM_WINDOW:
  {
    LOGV("APP_CMD_TERM_WINDOW\n");

    if( !android_app)
      return;

    pthread_mutex_lock( &android_app->mutex);
    android_app->window = 0;
    pthread_cond_broadcast( &android_app->cond);
    pthread_mutex_unlock( &android_app->mutex);
  }
  break;

  case APP_CMD_SAVE_STATE:
  {
    LOGV("APP_CMD_SAVE_STATE\n");

    if( !android_app)
      return;

    pthread_mutex_lock( &android_app->mutex);
    android_app->stateSaved = 1;
    pthread_cond_broadcast( &android_app->cond);
    pthread_mutex_unlock( &android_app->mutex);
  }
  break;

  case APP_CMD_RESUME:
  {
    if( !android_app)
      return;

    free_saved_state(android_app);
  }
  break;

  }
}

void app_dummy()
{
}

static void android_app_destroy(struct android_app* android_app)
{
  LOGV("android_app_destroy!");

  if( !android_app)
    return;

  free_saved_state(android_app);
  pthread_mutex_lock( &android_app->mutex);

  if(android_app->inputQueue)
    AInputQueue_detachLooper(android_app->inputQueue);

  AConfiguration_delete(android_app->config);
  android_app->destroyed = 1;
  pthread_cond_broadcast( &android_app->cond);
  pthread_mutex_unlock( &android_app->mutex);
}

static void process_input(struct android_app* app, struct android_poll_source* source)
{
  AInputEvent* event = 0;

  if( !app)
    return;

  while(AInputQueue_getEvent(app->inputQueue, &event) >= 0)
  {
    int32_t handled = 0;

    LOGV("New input event: type=%d\n", AInputEvent_getType(event) );

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
  struct android_app* android_app = 0;
  ALooper* looper = 0;

  if( !param)
    return 0;

  android_app = (struct android_app*)param;

  android_app->config = AConfiguration_new();
  AConfiguration_fromAssetManager(android_app->config, android_app->activity->assetManager);

  print_cur_config(android_app);

  android_app->cmdPollSource.id = LOOPER_ID_MAIN;
  android_app->cmdPollSource.app = android_app;
  android_app->cmdPollSource.process = process_cmd;
  android_app->inputPollSource.id = LOOPER_ID_INPUT;
  android_app->inputPollSource.app = android_app;
  android_app->inputPollSource.process = process_input;

  looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
  ALooper_addFd(looper, android_app->msgread, LOOPER_ID_MAIN, ALOOPER_EVENT_INPUT, 0, &android_app->cmdPollSource);
  android_app->looper = looper;

  pthread_mutex_lock( &android_app->mutex);
  android_app->running = 1;
  pthread_cond_broadcast( &android_app->cond);
  pthread_mutex_unlock( &android_app->mutex);

  android_main(android_app);

  android_app_destroy(android_app);

  return 0;
}

static struct android_app* android_app_create(ANativeActivity* activity, void* savedState, size_t savedStateSize)
{
  struct android_app* android_app = 0;
  int msgpipe[2] = {0};

  android_app = (struct android_app*)malloc(sizeof(struct android_app) );
  if( !android_app)
    return 0;

  memset(android_app, 0, sizeof(struct android_app) );

  android_app->activity = activity;

  pthread_mutex_init( &android_app->mutex, 0);
  pthread_cond_init( &android_app->cond, 0);

  if(savedState)
  {
    android_app->savedState = malloc(savedStateSize);

    android_app->savedStateSize = savedStateSize;

    if(android_app->savedState)
      memcpy(android_app->savedState, savedState, savedStateSize);
  }

  if(pipe(msgpipe) )
  {
    LOGE("could not create pipe: %s", strerror(errno) );

    return 0;
  }

  android_app->msgread = msgpipe[0];
  android_app->msgwrite = msgpipe[1];

  pthread_attr_t attr;
  memset( &attr, 0, sizeof(pthread_attr_t) );

  pthread_attr_init( &attr);
  pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED);
  pthread_create( &android_app->thread, &attr, android_app_entry, android_app);

  pthread_mutex_lock( &android_app->mutex);

  while( !android_app->running)
    pthread_cond_wait( &android_app->cond, &android_app->mutex);

  pthread_mutex_unlock( &android_app->mutex);

  return android_app;
}

static void android_app_write_cmd(struct android_app* android_app, int8_t cmd)
{
  if( !android_app)
    return;

  if(write(android_app->msgwrite, &cmd, sizeof(cmd) ) != sizeof(cmd) )
  {
    LOGE("Failure writing android_app cmd: %s\n", strerror(errno) );
  }
}

static void android_app_set_input(struct android_app* android_app, AInputQueue* inputQueue)
{
  if( !android_app)
    return;

  pthread_mutex_lock( &android_app->mutex);
  android_app->pendingInputQueue = inputQueue;
  android_app_write_cmd(android_app, APP_CMD_INPUT_CHANGED);

  while(android_app->inputQueue != android_app->pendingInputQueue)
    pthread_cond_wait( &android_app->cond, &android_app->mutex);

  pthread_mutex_unlock( &android_app->mutex);
}

static void android_app_set_window(struct android_app* android_app, ANativeWindow* window)
{
  if( !android_app)
    return;

  pthread_mutex_lock( &android_app->mutex);

  if(android_app->pendingWindow)
    android_app_write_cmd(android_app, APP_CMD_TERM_WINDOW);

  android_app->pendingWindow = window;

  if(window)
    android_app_write_cmd(android_app, APP_CMD_INIT_WINDOW);

  while(android_app->window != android_app->pendingWindow)
    pthread_cond_wait( &android_app->cond, &android_app->mutex);

  pthread_mutex_unlock( &android_app->mutex);
}

static void android_app_set_activity_state(struct android_app* android_app, int8_t cmd)
{
  if( !android_app)
    return;

  pthread_mutex_lock( &android_app->mutex);
  android_app_write_cmd(android_app, cmd);

  while(android_app->activityState != cmd)
    pthread_cond_wait( &android_app->cond, &android_app->mutex);

  pthread_mutex_unlock( &android_app->mutex);
}

static void android_app_free(struct android_app* android_app)
{
  if( !android_app)
    return;

  pthread_mutex_lock( &android_app->mutex);
  android_app_write_cmd(android_app, APP_CMD_DESTROY);

  while( !android_app->destroyed)
    pthread_cond_wait( &android_app->cond, &android_app->mutex);

  pthread_mutex_unlock( &android_app->mutex);

  close(android_app->msgread);
  close(android_app->msgwrite);
  pthread_cond_destroy( &android_app->cond);
  pthread_mutex_destroy( &android_app->mutex);
  free(android_app);
}

static void onDestroy(ANativeActivity* activity)
{
  LOGV("Destroy: %p\n", activity);

  if( !activity)
    return;

  android_app_free( (struct android_app*)activity->instance);
}

static void onStart(ANativeActivity* activity)
{
  LOGV("Start: %p\n", activity);

  if( !activity)
    return;

  android_app_set_activity_state( (struct android_app*)activity->instance, APP_CMD_START);
}

static void onResume(ANativeActivity* activity)
{
  LOGV("Resume: %p\n", activity);

  if( !activity)
    return;

  android_app_set_activity_state( (struct android_app*)activity->instance, APP_CMD_RESUME);
}

static void* onSaveInstanceState(ANativeActivity* activity, size_t* outLen)
{
  struct android_app* android_app = 0;
  void* savedState = 0;

  LOGV("SaveInstanceState: %p\n", activity);

  if( !activity)
    return 0;

  android_app = (struct android_app*)activity->instance;

  pthread_mutex_lock( &android_app->mutex);
  android_app->stateSaved = 0;
  android_app_write_cmd(android_app, APP_CMD_SAVE_STATE);

  while( !android_app->stateSaved)
    pthread_cond_wait( &android_app->cond, &android_app->mutex);

  if(android_app->savedState)
  {
    savedState = android_app->savedState;
    *outLen = android_app->savedStateSize;
    android_app->savedState = 0;
    android_app->savedStateSize = 0;
  }

  pthread_mutex_unlock( &android_app->mutex);

  return savedState;
}

static void onPause(ANativeActivity* activity)
{
  LOGV("Pause: %p\n", activity);

  if( !activity)
    return;

  android_app_set_activity_state( (struct android_app*)activity->instance, APP_CMD_PAUSE);
}

static void onStop(ANativeActivity* activity)
{
  LOGV("Stop: %p\n", activity);

  if( !activity)
    return;

  android_app_set_activity_state( (struct android_app*)activity->instance, APP_CMD_STOP);
}

static void onConfigurationChanged(ANativeActivity* activity)
{
  struct android_app* android_app = 0;

  LOGV("ConfigurationChanged: %p\n", activity);

  if( !activity)
    return;

  android_app = (struct android_app*)activity->instance;

  android_app_write_cmd(android_app, APP_CMD_CONFIG_CHANGED);
}

static void onLowMemory(ANativeActivity* activity)
{
  struct android_app* android_app = 0;

  LOGV("LowMemory: %p\n", activity);

  if( !activity)
    return;

  android_app = (struct android_app*)activity->instance;

  android_app_write_cmd(android_app, APP_CMD_LOW_MEMORY);
}

static void onWindowFocusChanged(ANativeActivity* activity, int focused)
{
  LOGV("WindowFocusChanged: %p -- %d\n", activity, focused);

  if( !activity)
    return;

  android_app_write_cmd( (struct android_app*)activity->instance, focused ? APP_CMD_GAINED_FOCUS : APP_CMD_LOST_FOCUS);
}

static void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window)
{
  LOGV("NativeWindowCreated: %p -- %p\n", activity, window);

  if( !activity)
    return;

  android_app_set_window( (struct android_app*)activity->instance, window);
}

static void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window)
{
  LOGV("NativeWindowDestroyed: %p -- %p\n", activity, window);

  if( !activity)
    return;

  android_app_set_window( (struct android_app*)activity->instance, 0);
}

static void onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue)
{
  LOGV("InputQueueCreated: %p -- %p\n", activity, queue);

  if( !activity)
    return;

  android_app_set_input( (struct android_app*)activity->instance, queue);
}

static void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue)
{
  LOGV("InputQueueDestroyed: %p -- %p\n", activity, queue);

  if( !activity)
    return;

  android_app_set_input( (struct android_app*)activity->instance, 0);
}

JNIEXPORT void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize)
{
  LOGV("Creating: %p\n", activity);

  if( !activity)
    return;

  if(activity->callbacks)
  {
    activity->callbacks->onDestroy = onDestroy;
    activity->callbacks->onStart = onStart;
    activity->callbacks->onResume = onResume;
    activity->callbacks->onSaveInstanceState = onSaveInstanceState;
    activity->callbacks->onPause = onPause;
    activity->callbacks->onStop = onStop;
    activity->callbacks->onConfigurationChanged = onConfigurationChanged;
    activity->callbacks->onLowMemory = onLowMemory;
    activity->callbacks->onWindowFocusChanged = onWindowFocusChanged;
    activity->callbacks->onNativeWindowCreated = onNativeWindowCreated;
    activity->callbacks->onNativeWindowDestroyed = onNativeWindowDestroyed;
    activity->callbacks->onInputQueueCreated = onInputQueueCreated;
    activity->callbacks->onInputQueueDestroyed = onInputQueueDestroyed;
  }

  activity->instance = android_app_create(activity, savedState, savedStateSize);
}
