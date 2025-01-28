
// platformplugin_factory.cpp

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

#include <string>
#include <locale>
#include <algorithm>
#include <memory>
#include <stdarg.h>
#include <stddef.h>

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

#include "options.h"
#include "platformplugin.h"

#define UNUSED_PARM(x) \
  do{ (void)(x); } while(0)

std::shared_ptr<IPlatformPlugin> CreatePlatformPlugin_Android(const std::shared_ptr<Options>& /*unused*/, const std::shared_ptr<PlatformData>& /*unused*/);

std::shared_ptr<IPlatformPlugin> CreatePlatformPlugin(const std::shared_ptr<Options>& options, const std::shared_ptr<PlatformData>& data)
{
  return CreatePlatformPlugin_Android(options, data);
}
