
// anag.h

#define ANAG_LOGI(...) do{ __android_log_print(ANDROID_LOG_INFO, "threaded_app", __VA_ARGS__); }while(0)
#define ANAG_LOGE(...) do{ __android_log_print(ANDROID_LOG_ERROR, "threaded_app", __VA_ARGS__); }while(0)

#ifndef NDEBUG
#define ANAG_LOGV(...) do{ __android_log_print(ANDROID_LOG_VERBOSE, "threaded_app", __VA_ARGS__); }while(0)
#else
#define ANAG_LOGV(...) do{ /*nop*/; }while(0)
#endif

//struct XrInstanceCreateInfoAndroidKHR
//{
//  XrStructureType type;
//  const void* next;
//  void* applicationVM;
//  void* applicationActivity;
//};

struct AndroidAppState
{
  ANativeWindow* NativeWindow = nullptr;
  bool Resumed = false;
};

struct android_app;

struct android_poll_source
{
  int32_t id;

  struct android_app* app;

  void (*process)(struct android_app* app, struct android_poll_source* source);
};

struct android_app
{
  void* userData;

  void (*onAppCmd)(struct android_app* app, int32_t cmd);

  int32_t (*onInputEvent)(struct android_app* app, AInputEvent* event);

  ANativeActivity* activity;

  AConfiguration* config;

  void* savedState;
  size_t savedStateSize;

  ALooper* looper;

  AInputQueue* inputQueue;

  ANativeWindow* window;

  ARect contentRect;

  int activityState;

  int destroyRequested;

  pthread_mutex_t mutex;
  pthread_cond_t cond;

  int msgread;
  int msgwrite;

  pthread_t thread;

  struct android_poll_source cmdPollSource;
  struct android_poll_source inputPollSource;

  int running;
  int stateSaved;
  int destroyed;
  int redrawNeeded;

  AInputQueue* pendingInputQueue;
  ANativeWindow* pendingWindow;
  ARect pendingContentRect;
};

enum
{
  LOOPER_ID_MAIN = 1,
  LOOPER_ID_INPUT = 2,
  LOOPER_ID_USER = 3
};

enum
{
  APP_CMD_INPUT_CHANGED,
  APP_CMD_INIT_WINDOW,
  APP_CMD_TERM_WINDOW,
  APP_CMD_WINDOW_RESIZED,
  APP_CMD_WINDOW_REDRAW_NEEDED,
  APP_CMD_CONTENT_RECT_CHANGED,
  APP_CMD_GAINED_FOCUS,
  APP_CMD_LOST_FOCUS,
  APP_CMD_CONFIG_CHANGED,
  APP_CMD_LOW_MEMORY,
  APP_CMD_START,
  APP_CMD_RESUME,
  APP_CMD_SAVE_STATE,
  APP_CMD_PAUSE,
  APP_CMD_STOP,
  APP_CMD_DESTROY
};

extern JNIEnv* gEnvironment;

extern struct android_app* gApplication;

void AnagShowHelpBlah();

bool AnagUpdateOptionsFromSystemProperties();

unsigned char* AnagLoadFileBlah(const char* fileName, int* fileSize);

/**
 * Process the next main command.
 */
void anag_app_handle_cmd(struct android_app* app, int32_t cmd);

void anag_free_saved_state(struct android_app* app);

int8_t anag_android_app_read_cmd(struct android_app* app);

void anag_print_cur_config(struct android_app* app);

void anag_android_app_pre_exec_cmd(struct android_app* app, int8_t cmd);

void anag_android_app_post_exec_cmd(struct android_app* app, int8_t cmd);

//void anag_app_dummy();

void anag_android_app_destroy(struct android_app* app);

void anag_process_input(struct android_app* app, struct android_poll_source* source);

void anag_process_cmd(struct android_app* app, struct android_poll_source* source);

void* anag_android_app_entry(void* param);

struct android_app* anag_android_app_create(ANativeActivity* activity, void* savedState, size_t savedStateSize);

void anag_android_app_write_cmd(struct android_app* app, int8_t cmd);

void anag_android_app_set_input(struct android_app* app, AInputQueue* inputQueue);

void anag_android_app_set_window(struct android_app* app, ANativeWindow* window);

void anag_android_app_set_activity_state(struct android_app* app, int8_t cmd);

void anag_android_app_free(struct android_app* app);

struct android_app* AnagToApp(ANativeActivity* activity);

void anagOnDestroy(ANativeActivity* activity);

void anagOnStart(ANativeActivity* activity);

void anagOnResume(ANativeActivity* activity);

void* anagOnSaveInstanceState(ANativeActivity* activity, size_t* outLen);

void anagOnPause(ANativeActivity* activity);

void anagOnStop(ANativeActivity* activity);

void anagOnConfigurationChanged(ANativeActivity* activity);

void anagOnContentRectChanged(ANativeActivity* activity, const ARect* r);

void anagOnLowMemory(ANativeActivity* activity);

void anagOnWindowFocusChanged(ANativeActivity* activity, int focused);

void anagOnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window);

void anagOnNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window);

void anagOnNativeWindowRedrawNeeded(ANativeActivity* activity, ANativeWindow* window);

void anagOnNativeWindowResized(ANativeActivity* activity, ANativeWindow* window);

void anagOnInputQueueCreated(ANativeActivity* activity, AInputQueue* queue);

void anagOnInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue);

extern "C" __attribute__ ( (visibility ("default") ) ) void ANativeActivity_onCreate(
  ANativeActivity* activity,
  void* savedState,
  size_t savedStateSize
);
