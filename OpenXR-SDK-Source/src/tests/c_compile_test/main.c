// Copyright (c) 2017-2024, The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <android/log.h>
#include "anag.h"
#include <android/native_window.h>
#include <jni.h>
#include <sys/system_properties.h>

#ifdef XR_USE_GRAPHICS_API_VULKAN

#define VK_USE_PLATFORM_ANDROID_KHR

#include <vulkan/vulkan.h>
#endif

#ifdef XR_USE_TIMESPEC
#include <time.h>
#endif

#include <openxr/openxr.h>
#include <openxr/openxr_platform.h>
#include <openxr/openxr_reflection.h>
#include <openxr/openxr_platform_defines.h>
#include <xr_linear.h>

#if !defined(ANDROID)
// this is just a test that our SDK headers compile with the C compiler
int main(int argc, const char** argv) {
    (void)argc;
    (void)argv;

    return 0;
}
#else   // defined(ANDROID)
static void app_handle_cmd(struct android_app* app, int32_t cmd) {
    (void)app;
    (void)cmd;
}

void android_main(struct android_app* app) {
    JNIEnv* Env;

    JavaVM* java_vm = app->activity->vm;

    (*java_vm)->AttachCurrentThread(java_vm, &Env, NULL);

    app->userData = NULL;
    app->onAppCmd = app_handle_cmd;

    // empty implementation

    ANativeActivity_finish(app->activity);
    (*java_vm)->DetachCurrentThread(java_vm);
}
#endif  // !defined(ANDROID)
