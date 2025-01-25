/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <jni.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

#include "anag.h"
#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "threaded_app", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "threaded_app", __VA_ARGS__))

/* For debug builds, always enable the debug traces in this library */
#ifndef NDEBUG
#  define LOGV(...)  ((void)__android_log_print(ANDROID_LOG_VERBOSE, "threaded_app", __VA_ARGS__))
#else
#  define LOGV(...)  ((void)0)
#endif

static void free_saved_state(struct android_app* android_app) {
    pthread_mutex_lock(&android_app->mutex);
    if (android_app->savedState != NULL) {
        free(android_app->savedState);
        android_app->savedState = NULL;
        android_app->savedStateSize = 0;
    }
    pthread_mutex_unlock(&android_app->mutex);
}

int8_t android_app_read_cmd(struct android_app* android_app) {
    int8_t cmd;
    if (read(android_app->msgread, &cmd, sizeof(cmd)) == sizeof(cmd)) {
        switch (cmd) {
            case APP_CMD_SAVE_STATE:
                free_saved_state(android_app);
                break;
        }
        return cmd;
    } else {
        LOGE("No data on command pipe!");
    }
    return -1;
}

static void print_cur_config(struct android_app* android_app) {
    char lang[2], country[2];
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
            AConfiguration_getUiModeNight(android_app->config));
}

void android_app_pre_exec_cmd(struct android_app* android_app, int8_t cmd) {
    switch (cmd) {
        case APP_CMD_INPUT_CHANGED:
            LOGV("APP_CMD_INPUT_CHANGED\n");
            pthread_mutex_lock(&android_app->mutex);
            if (android_app->inputQueue != NULL) {
                AInputQueue_detachLooper(android_app->inputQueue);
            }
            android_app->inputQueue = android_app->pendingInputQueue;
            if (android_app->inputQueue != NULL) {
                LOGV("Attaching input queue to looper");
                AInputQueue_attachLooper(android_app->inputQueue,
                        android_app->looper, LOOPER_ID_INPUT, NULL,
                        &android_app->inputPollSource);
            }
            pthread_cond_broadcast(&android_app->cond);
            pthread_mutex_unlock(&android_app->mutex);
            break;

        case APP_CMD_INIT_WINDOW:
            LOGV("APP_CMD_INIT_WINDOW\n");
            pthread_mutex_lock(&android_app->mutex);
            android_app->window = android_app->pendingWindow;
            pthread_cond_broadcast(&android_app->cond);
            pthread_mutex_unlock(&android_app->mutex);
            break;

        case APP_CMD_TERM_WINDOW:
            LOGV("APP_CMD_TERM_WINDOW\n");
            pthread_cond_broadcast(&android_app->cond);
            break;

        case APP_CMD_RESUME:
        case APP_CMD_START:
        case APP_CMD_PAUSE:
        case APP_CMD_STOP:
            LOGV("activityState=%d\n", cmd);
            pthread_mutex_lock(&android_app->mutex);
            android_app->activityState = cmd;
            pthread_cond_broadcast(&android_app->cond);
            pthread_mutex_unlock(&android_app->mutex);
            break;

        case APP_CMD_CONFIG_CHANGED:
            LOGV("APP_CMD_CONFIG_CHANGED\n");
            AConfiguration_fromAssetManager(android_app->config,
                    android_app->activity->assetManager);
            print_cur_config(android_app);
            break;

        case APP_CMD_DESTROY:
            LOGV("APP_CMD_DESTROY\n");
            android_app->destroyRequested = 1;
            break;
    }
}

void android_app_post_exec_cmd(struct android_app* android_app, int8_t cmd) {
    switch (cmd) {
        case APP_CMD_TERM_WINDOW:
            LOGV("APP_CMD_TERM_WINDOW\n");
            pthread_mutex_lock(&android_app->mutex);
            android_app->window = NULL;
            pthread_cond_broadcast(&android_app->cond);
            pthread_mutex_unlock(&android_app->mutex);
            break;

        case APP_CMD_SAVE_STATE:
            LOGV("APP_CMD_SAVE_STATE\n");
            pthread_mutex_lock(&android_app->mutex);
            android_app->stateSaved = 1;
            pthread_cond_broadcast(&android_app->cond);
            pthread_mutex_unlock(&android_app->mutex);
            break;

        case APP_CMD_RESUME:
            free_saved_state(android_app);
            break;
    }
}

void app_dummy() {

}

static void android_app_destroy(struct android_app* android_app) {
    LOGV("android_app_destroy!");
    free_saved_state(android_app);
    pthread_mutex_lock(&android_app->mutex);
    if (android_app->inputQueue != NULL) {
        AInputQueue_detachLooper(android_app->inputQueue);
    }
    AConfiguration_delete(android_app->config);
    android_app->destroyed = 1;
    pthread_cond_broadcast(&android_app->cond);
    pthread_mutex_unlock(&android_app->mutex);
    // Can't touch android_app object after this.
}

static void process_input(struct android_app* app, struct android_poll_source* source) {
    AInputEvent* event = NULL;
    while (AInputQueue_getEvent(app->inputQueue, &event) >= 0) {
        LOGV("New input event: type=%d\n", AInputEvent_getType(event));
        if (AInputQueue_preDispatchEvent(app->inputQueue, event)) {
            continue;
        }
        int32_t handled = 0;
        if (app->onInputEvent != NULL) handled = app->onInputEvent(app, event);
        AInputQueue_finishEvent(app->inputQueue, event, handled);
    }
}

static void process_cmd(struct android_app* app, struct android_poll_source* source) {
    int8_t cmd = android_app_read_cmd(app);
    android_app_pre_exec_cmd(app, cmd);
    if (app->onAppCmd != NULL) app->onAppCmd(app, cmd);
    android_app_post_exec_cmd(app, cmd);
}

static void* android_app_entry(void* param) {
    struct android_app* android_app = (struct android_app*)param;

    android_app->config = AConfiguration_new();
    AConfiguration_fromAssetManager(android_app->config, android_app->activity->assetManager);

    print_cur_config(android_app);

    android_app->cmdPollSource.id = LOOPER_ID_MAIN;
    android_app->cmdPollSource.app = android_app;
    android_app->cmdPollSource.process = process_cmd;
    android_app->inputPollSource.id = LOOPER_ID_INPUT;
    android_app->inputPollSource.app = android_app;
    android_app->inputPollSource.process = process_input;

    ALooper* looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
    ALooper_addFd(looper, android_app->msgread, LOOPER_ID_MAIN, ALOOPER_EVENT_INPUT, NULL,
            &android_app->cmdPollSource);
    android_app->looper = looper;

    pthread_mutex_lock(&android_app->mutex);
    android_app->running = 1;
    pthread_cond_broadcast(&android_app->cond);
    pthread_mutex_unlock(&android_app->mutex);

    android_main(android_app);

    android_app_destroy(android_app);
    return NULL;
}

// --------------------------------------------------------------------
// Native activity interaction (called from main thread)
// --------------------------------------------------------------------

static struct android_app* android_app_create(ANativeActivity* activity,
        void* savedState, size_t savedStateSize) {
    struct android_app* android_app = (struct android_app*)malloc(sizeof(struct android_app));
    memset(android_app, 0, sizeof(struct android_app));
    android_app->activity = activity;

    pthread_mutex_init(&android_app->mutex, NULL);
    pthread_cond_init(&android_app->cond, NULL);

    if (savedState != NULL) {
        android_app->savedState = malloc(savedStateSize);
        android_app->savedStateSize = savedStateSize;
        memcpy(android_app->savedState, savedState, savedStateSize);
    }

    int msgpipe[2];
    if (pipe(msgpipe)) {
        LOGE("could not create pipe: %s", strerror(errno));
        return NULL;
    }
    android_app->msgread = msgpipe[0];
    android_app->msgwrite = msgpipe[1];

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&android_app->thread, &attr, android_app_entry, android_app);

    // Wait for thread to start.
    pthread_mutex_lock(&android_app->mutex);
    while (!android_app->running) {
        pthread_cond_wait(&android_app->cond, &android_app->mutex);
    }
    pthread_mutex_unlock(&android_app->mutex);

    return android_app;
}

static void android_app_write_cmd(struct android_app* android_app, int8_t cmd) {
    if (write(android_app->msgwrite, &cmd, sizeof(cmd)) != sizeof(cmd)) {
        LOGE("Failure writing android_app cmd: %s\n", strerror(errno));
    }
}

static void android_app_set_input(struct android_app* android_app, AInputQueue* inputQueue) {
    pthread_mutex_lock(&android_app->mutex);
    android_app->pendingInputQueue = inputQueue;
    android_app_write_cmd(android_app, APP_CMD_INPUT_CHANGED);
    while (android_app->inputQueue != android_app->pendingInputQueue) {
        pthread_cond_wait(&android_app->cond, &android_app->mutex);
    }
    pthread_mutex_unlock(&android_app->mutex);
}

static void android_app_set_window(struct android_app* android_app, ANativeWindow* window) {
    pthread_mutex_lock(&android_app->mutex);
    if (android_app->pendingWindow != NULL) {
        android_app_write_cmd(android_app, APP_CMD_TERM_WINDOW);
    }
    android_app->pendingWindow = window;
    if (window != NULL) {
        android_app_write_cmd(android_app, APP_CMD_INIT_WINDOW);
    }
    while (android_app->window != android_app->pendingWindow) {
        pthread_cond_wait(&android_app->cond, &android_app->mutex);
    }
    pthread_mutex_unlock(&android_app->mutex);
}

static void android_app_set_activity_state(struct android_app* android_app, int8_t cmd) {
    pthread_mutex_lock(&android_app->mutex);
    android_app_write_cmd(android_app, cmd);
    while (android_app->activityState != cmd) {
        pthread_cond_wait(&android_app->cond, &android_app->mutex);
    }
    pthread_mutex_unlock(&android_app->mutex);
}

static void android_app_free(struct android_app* android_app) {
    pthread_mutex_lock(&android_app->mutex);
    android_app_write_cmd(android_app, APP_CMD_DESTROY);
    while (!android_app->destroyed) {
        pthread_cond_wait(&android_app->cond, &android_app->mutex);
    }
    pthread_mutex_unlock(&android_app->mutex);

    close(android_app->msgread);
    close(android_app->msgwrite);
    pthread_cond_destroy(&android_app->cond);
    pthread_mutex_destroy(&android_app->mutex);
    free(android_app);
}

static void onDestroy(ANativeActivity* activity) {
    LOGV("Destroy: %p\n", activity);
    android_app_free((struct android_app*)activity->instance);
}

static void onStart(ANativeActivity* activity) {
    LOGV("Start: %p\n", activity);
    android_app_set_activity_state((struct android_app*)activity->instance, APP_CMD_START);
}

static void onResume(ANativeActivity* activity) {
    LOGV("Resume: %p\n", activity);
    android_app_set_activity_state((struct android_app*)activity->instance, APP_CMD_RESUME);
}

static void* onSaveInstanceState(ANativeActivity* activity, size_t* outLen) {
    struct android_app* android_app = (struct android_app*)activity->instance;
    void* savedState = NULL;

    LOGV("SaveInstanceState: %p\n", activity);
    pthread_mutex_lock(&android_app->mutex);
    android_app->stateSaved = 0;
    android_app_write_cmd(android_app, APP_CMD_SAVE_STATE);
    while (!android_app->stateSaved) {
        pthread_cond_wait(&android_app->cond, &android_app->mutex);
    }

    if (android_app->savedState != NULL) {
        savedState = android_app->savedState;
        *outLen = android_app->savedStateSize;
        android_app->savedState = NULL;
        android_app->savedStateSize = 0;
    }

    pthread_mutex_unlock(&android_app->mutex);

    return savedState;
}

static void onPause(ANativeActivity* activity) {
    LOGV("Pause: %p\n", activity);
    android_app_set_activity_state((struct android_app*)activity->instance, APP_CMD_PAUSE);
}

static void onStop(ANativeActivity* activity) {
    LOGV("Stop: %p\n", activity);
    android_app_set_activity_state((struct android_app*)activity->instance, APP_CMD_STOP);
}

static void onConfigurationChanged(ANativeActivity* activity) {
    struct android_app* android_app = (struct android_app*)activity->instance;
    LOGV("ConfigurationChanged: %p\n", activity);
    android_app_write_cmd(android_app, APP_CMD_CONFIG_CHANGED);
}

static void onLowMemory(ANativeActivity* activity) {
    struct android_app* android_app = (struct android_app*)activity->instance;
    LOGV("LowMemory: %p\n", activity);
    android_app_write_cmd(android_app, APP_CMD_LOW_MEMORY);
}

static void onWindowFocusChanged(ANativeActivity* activity, int focused) {
    LOGV("WindowFocusChanged: %p -- %d\n", activity, focused);
    android_app_write_cmd((struct android_app*)activity->instance,
            focused ? APP_CMD_GAINED_FOCUS : APP_CMD_LOST_FOCUS);
}

static void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window) {
    LOGV("NativeWindowCreated: %p -- %p\n", activity, window);
    android_app_set_window((struct android_app*)activity->instance, window);
}

static void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) {
    LOGV("NativeWindowDestroyed: %p -- %p\n", activity, window);
    android_app_set_window((struct android_app*)activity->instance, NULL);
}

static void onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue) {
    LOGV("InputQueueCreated: %p -- %p\n", activity, queue);
    android_app_set_input((struct android_app*)activity->instance, queue);
}

static void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue) {
    LOGV("InputQueueDestroyed: %p -- %p\n", activity, queue);
    android_app_set_input((struct android_app*)activity->instance, NULL);
}

int __android_log_print(int prio, const char* tag, const char* fmt, ... )//__attribute__ ( (__format__ (printf, 3, 4) ) )
{
  return 0;
}

AConfiguration* AConfiguration_new() { return 0; }
void AConfiguration_delete(AConfiguration* config) { }
void AConfiguration_fromAssetManager(AConfiguration* out, AAssetManager* am) { }
//void AConfiguration_copy(AConfiguration* dest, AConfiguration* src);
int32_t AConfiguration_getMcc(AConfiguration* config) { return 0; }
//void AConfiguration_setMcc(AConfiguration* config, int32_t mcc);
int32_t AConfiguration_getMnc(AConfiguration* config) { return 0; }
//void AConfiguration_setMnc(AConfiguration* config, int32_t mnc);
void AConfiguration_getLanguage(AConfiguration* config, char* outLanguage) { }
//void AConfiguration_setLanguage(AConfiguration* config, const char* language);
void AConfiguration_getCountry(AConfiguration* config, char* outCountry) { }
//void AConfiguration_setCountry(AConfiguration* config, const char* country);
int32_t AConfiguration_getOrientation(AConfiguration* config) { return 0; }
//void AConfiguration_setOrientation(AConfiguration* config, int32_t orientation);
int32_t AConfiguration_getTouchscreen(AConfiguration* config) { return 0; }
//void AConfiguration_setTouchscreen(AConfiguration* config, int32_t touchscreen);
int32_t AConfiguration_getDensity(AConfiguration* config) { return 0; }
//void AConfiguration_setDensity(AConfiguration* config, int32_t density);
int32_t AConfiguration_getKeyboard(AConfiguration* config) { return 0; }
//void AConfiguration_setKeyboard(AConfiguration* config, int32_t keyboard);
int32_t AConfiguration_getNavigation(AConfiguration* config) { return 0; }
//void AConfiguration_setNavigation(AConfiguration* config, int32_t navigation);
int32_t AConfiguration_getKeysHidden(AConfiguration* config) { return 0; }
//void AConfiguration_setKeysHidden(AConfiguration* config, int32_t keysHidden);
int32_t AConfiguration_getNavHidden(AConfiguration* config) { return 0; }
//void AConfiguration_setNavHidden(AConfiguration* config, int32_t navHidden);
int32_t AConfiguration_getSdkVersion(AConfiguration* config) { return 0; }
//void AConfiguration_setSdkVersion(AConfiguration* config, int32_t sdkVersion);
int32_t AConfiguration_getScreenSize(AConfiguration* config) { return 0; }
//void AConfiguration_setScreenSize(AConfiguration* config, int32_t screenSize);
int32_t AConfiguration_getScreenLong(AConfiguration* config) { return 0; }
//void AConfiguration_setScreenLong(AConfiguration* config, int32_t screenLong);
//int32_t AConfiguration_getScreenRound(AConfiguration* config) __INTRODUCED_IN(30);
//void AConfiguration_setScreenRound(AConfiguration* config, int32_t screenRound);
int32_t AConfiguration_getUiModeType(AConfiguration* config) { return 0; }
//void AConfiguration_setUiModeType(AConfiguration* config, int32_t uiModeType);
int32_t AConfiguration_getUiModeNight(AConfiguration* config) { return 0; }
//void AConfiguration_setUiModeNight(AConfiguration* config, int32_t uiModeNight);
//int32_t AConfiguration_getScreenWidthDp(AConfiguration* config);
//void AConfiguration_setScreenWidthDp(AConfiguration* config, int32_t value);
//int32_t AConfiguration_getScreenHeightDp(AConfiguration* config);
//void AConfiguration_setScreenHeightDp(AConfiguration* config, int32_t value);
//int32_t AConfiguration_getSmallestScreenWidthDp(AConfiguration* config);
//void AConfiguration_setSmallestScreenWidthDp(AConfiguration* config, int32_t value);
//int32_t AConfiguration_getLayoutDirection(AConfiguration* config) __INTRODUCED_IN(17);
//void AConfiguration_setLayoutDirection(AConfiguration* config, int32_t value) __INTRODUCED_IN(17);
//int32_t AConfiguration_diff(AConfiguration* config1, AConfiguration* config2);
//int32_t AConfiguration_match(AConfiguration* base, AConfiguration* requested);
//int32_t AConfiguration_isBetterThan(AConfiguration* base, AConfiguration* test, AConfiguration* requested);

//struct AInputEvent;
int32_t AInputEvent_getType(const AInputEvent* event) { return 0; }
//int32_t AInputEvent_getDeviceId(const AInputEvent* event);
//int32_t AInputEvent_getSource(const AInputEvent* event);
//void AInputEvent_release(const AInputEvent* event) __INTRODUCED_IN(31);

//struct AInputQueue;
//typedef struct AInputQueue AInputQueue;
void AInputQueue_attachLooper(AInputQueue* queue, ALooper* looper, int ident, ALooper_callbackFunc callback, void* data) { }
void AInputQueue_detachLooper(AInputQueue* queue) { }
//int32_t AInputQueue_hasEvents(AInputQueue* queue);
int32_t AInputQueue_getEvent(AInputQueue* queue, AInputEvent** outEvent) { return 0; }
int32_t AInputQueue_preDispatchEvent(AInputQueue* queue, AInputEvent* event) { return 0; }
void AInputQueue_finishEvent(AInputQueue* queue, AInputEvent* event, int handled) { }
//AInputQueue* AInputQueue_fromJava(JNIEnv* env, jobject inputQueue) __INTRODUCED_IN(33);

//int32_t AKeyEvent_getAction(const AInputEvent* key_event);
//int32_t AKeyEvent_getFlags(const AInputEvent* key_event);
//int32_t AKeyEvent_getKeyCode(const AInputEvent* key_event);
//int32_t AKeyEvent_getScanCode(const AInputEvent* key_event);
//int32_t AKeyEvent_getMetaState(const AInputEvent* key_event);
//int32_t AKeyEvent_getRepeatCount(const AInputEvent* key_event);
//int64_t AKeyEvent_getDownTime(const AInputEvent* key_event);
//int64_t AKeyEvent_getEventTime(const AInputEvent* key_event);
//const AInputEvent* AKeyEvent_fromJava(JNIEnv* env, jobject keyEvent) __INTRODUCED_IN(31);

//ALooper* ALooper_forThread();
ALooper* ALooper_prepare(int opts) { return 0; }
//void ALooper_acquire(ALooper* looper);
//void ALooper_release(ALooper* looper);
//typedef int (*ALooper_callbackFunc)(int fd, int events, void* data);
//int ALooper_pollOnce(int timeoutMillis, int* outFd, int* outEvents, void** outData);
int ALooper_pollAll(int timeoutMillis, int* outFd, int* outEvents, void** outData) { return 0; }
//void ALooper_wake(ALooper* looper);
int ALooper_addFd(ALooper* looper, int fd, int ident, int events, ALooper_callbackFunc callback, void* data) { return 0; }
//int ALooper_removeFd(ALooper* looper, int fd);

//int32_t AMotionEvent_getAction(const AInputEvent* motion_event);
//int32_t AMotionEvent_getFlags(const AInputEvent* motion_event);
//int32_t AMotionEvent_getMetaState(const AInputEvent* motion_event);
//int32_t AMotionEvent_getButtonState(const AInputEvent* motion_event);
//int32_t AMotionEvent_getEdgeFlags(const AInputEvent* motion_event);
//int64_t AMotionEvent_getDownTime(const AInputEvent* motion_event);
//int64_t AMotionEvent_getEventTime(const AInputEvent* motion_event);
//float AMotionEvent_getXOffset(const AInputEvent* motion_event);
//float AMotionEvent_getYOffset(const AInputEvent* motion_event);
//float AMotionEvent_getXPrecision(const AInputEvent* motion_event);
//float AMotionEvent_getYPrecision(const AInputEvent* motion_event);
//size_t AMotionEvent_getPointerCount(const AInputEvent* motion_event);
//int32_t AMotionEvent_getPointerId(const AInputEvent* motion_event, size_t pointer_index);
//int32_t AMotionEvent_getToolType(const AInputEvent* motion_event, size_t pointer_index);
//float AMotionEvent_getRawX(const AInputEvent* motion_event, size_t pointer_index);
//float AMotionEvent_getRawY(const AInputEvent* motion_event, size_t pointer_index);
//float AMotionEvent_getX(const AInputEvent* motion_event, size_t pointer_index);
//float AMotionEvent_getY(const AInputEvent* motion_event, size_t pointer_index);
//float AMotionEvent_getPressure(const AInputEvent* motion_event, size_t pointer_index);
//float AMotionEvent_getSize(const AInputEvent* motion_event, size_t pointer_index);
//float AMotionEvent_getTouchMajor(const AInputEvent* motion_event, size_t pointer_index);
//float AMotionEvent_getTouchMinor(const AInputEvent* motion_event, size_t pointer_index);
//float AMotionEvent_getToolMajor(const AInputEvent* motion_event, size_t pointer_index);
//float AMotionEvent_getToolMinor(const AInputEvent* motion_event, size_t pointer_index);
//float AMotionEvent_getOrientation(const AInputEvent* motion_event, size_t pointer_index);
//float AMotionEvent_getAxisValue(const AInputEvent* motion_event, int32_t axis, size_t pointer_index);
//size_t AMotionEvent_getHistorySize(const AInputEvent* motion_event);
//int64_t AMotionEvent_getHistoricalEventTime(const AInputEvent* motion_event, size_t history_index);
//float AMotionEvent_getHistoricalRawX(const AInputEvent* motion_event, size_t pointer_index, size_t history_index);
//float AMotionEvent_getHistoricalRawY(const AInputEvent* motion_event, size_t pointer_index, size_t history_index);
//float AMotionEvent_getHistoricalX(const AInputEvent* motion_event, size_t pointer_index, size_t history_index);
//float AMotionEvent_getHistoricalY(const AInputEvent* motion_event, size_t pointer_index, size_t history_index);
//float AMotionEvent_getHistoricalPressure(const AInputEvent* motion_event, size_t pointer_index, size_t history_index);
//float AMotionEvent_getHistoricalSize(const AInputEvent* motion_event, size_t pointer_index, size_t history_index);
//float AMotionEvent_getHistoricalTouchMajor(const AInputEvent* motion_event, size_t pointer_index, size_t history_index);
//float AMotionEvent_getHistoricalTouchMinor(const AInputEvent* motion_event, size_t pointer_index, size_t history_index);
//float AMotionEvent_getHistoricalToolMajor(const AInputEvent* motion_event, size_t pointer_index, size_t history_index);
//float AMotionEvent_getHistoricalToolMinor(const AInputEvent* motion_event, size_t pointer_index, size_t history_index);
//float AMotionEvent_getHistoricalOrientation(const AInputEvent* motion_event, size_t pointer_index, size_t history_index);
//float AMotionEvent_getHistoricalAxisValue(const AInputEvent* motion_event, int32_t axis, size_t pointer_index, size_t history_index);
//int32_t AMotionEvent_getActionButton(const AInputEvent* motion_event) __INTRODUCED_IN(__ANDROID_API_T__);
//int32_t AMotionEvent_getClassification(const AInputEvent* motion_event) __INTRODUCED_IN(__ANDROID_API_T__);
//const AInputEvent* AMotionEvent_fromJava(JNIEnv* env, jobject motionEvent) __INTRODUCED_IN(31);

//struct ANativeActivityCallbacks;
//typedef void ANativeActivity_createFunc(ANativeActivity* activity, void* savedState, size_t savedStateSize);
//extern ANativeActivity_createFunc ANativeActivity_onCreate;
void ANativeActivity_finish(ANativeActivity* activity) { }
//void ANativeActivity_setWindowFormat(ANativeActivity* activity, int32_t format);
//void ANativeActivity_setWindowFlags(ANativeActivity* activity, uint32_t addFlags, uint32_t removeFlags);
//void ANativeActivity_showSoftInput(ANativeActivity* activity, uint32_t flags);
//void ANativeActivity_hideSoftInput(ANativeActivity* activity, uint32_t flags);

JNIEXPORT
void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize)
{
  LOGV("Creating: %p\n", activity);

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

  activity->instance = android_app_create(activity, savedState, savedStateSize);
}
