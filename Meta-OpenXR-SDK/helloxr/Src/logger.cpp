
// logger.cpp

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

#include "openxr_platform_defines.h"
#include "openxr.h"
#include "openxr_platform.h"
#include "openxr_loader_negotiation.h"
#include "openxr_reflection.h"
#include "openxr_reflection_structs.h"
#include "openxr_reflection_parent_structs.h"

#include "logger.h"

#include <sstream>

#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, "helloxr", __VA_ARGS__)
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "helloxr", __VA_ARGS__)

namespace
{
  Log::Level g_minSeverity {Log::Level::Info};
  std::mutex g_logLock;

} // namespace

namespace Log
{

void SetLevel(Level minSeverity) { g_minSeverity = minSeverity; }

void Write(Level severity, const std::string& msg)
{
  if(severity < g_minSeverity)
    return;

  const auto now = std::chrono::system_clock::now();
  const time_t now_time = std::chrono::system_clock::to_time_t(now);
  tm now_tm;

  localtime_r( &now_time, &now_tm);

  // time_t only has second precision. Use the rounding error to get sub-second precision.
  const auto secondRemainder = now - std::chrono::system_clock::from_time_t(now_time);
  const int64_t milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(secondRemainder).count();

  static std::map<Level, const char*> severityName = { {Level::Verbose, "Verbose"}, {Level::Info, "Info   "}, {Level::Warning, "Warning"}, {Level::Error, "Error  "} };

  std::ostringstream out;

  out.fill('0');

  out << "[" << std::setw(2) << now_tm.tm_hour << ":" << std::setw(2) << now_tm.tm_min << ":" << std::setw(2) << now_tm.tm_sec
    << "." << std::setw(3) << milliseconds << "]"
    << "[" << severityName[severity] << "] " << msg << std::endl;

  std::lock_guard<std::mutex> lock(g_logLock); // Ensure output is serialized

  ( (severity == Level::Error) ? std::clog : std::cout) << out.str();

  if(severity == Level::Error)
    ALOGE("%s", out.str().c_str() );
  else
    ALOGV("%s", out.str().c_str() );
}

} // namespace Log
