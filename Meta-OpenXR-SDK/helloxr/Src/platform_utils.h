
// platform_utils.h

#pragma once

#include "xr_dependencies.h"
#include <string>
#include <stdint.h>
#include <stdlib.h>

// OpenXR paths and registry key locations
#define OPENXR_RELATIVE_PATH "openxr/"
#define OPENXR_IMPLICIT_API_LAYER_RELATIVE_PATH "/api_layers/implicit.d"
#define OPENXR_EXPLICIT_API_LAYER_RELATIVE_PATH "/api_layers/explicit.d"

// OpenXR Loader environment variables of interest
#define OPENXR_RUNTIME_JSON_ENV_VAR "XR_RUNTIME_JSON"
#define OPENXR_API_LAYER_PATH_ENV_VAR "XR_API_LAYER_PATH"

#define HAVE_SECURE_GETENV 1
#define HAVE___SECURE_GETENV 1

#define XR_ARCH_ABI "arm64-v8a"

// Consumers of this file must ensure this function is implemented. For example, the loader will implement this function so that it
// can route messages through the loader's logging system.
void LogPlatformUtilsError(const std::string& message);

#include <sys/stat.h>

#include <sys/system_properties.h>

namespace detail
{

static inline bool ImplTryRuntimeFilename(const char* rt_dir_prefix, uint16_t major_version, std::string& file_name)
{
    auto decorated_path = rt_dir_prefix + std::to_string(major_version) + "/active_runtime." XR_ARCH_ABI ".json";
    auto undecorated_path = rt_dir_prefix + std::to_string(major_version) + "/active_runtime.json";

    struct stat buf {};

    if(0 == stat(decorated_path.c_str(), &buf) )
    {
        file_name = decorated_path;
        return true;
    }

    if(0 == stat(undecorated_path.c_str(), &buf) )
    {
        file_name = undecorated_path;
        return true;
    }

    return false;
}

} // namespace detail

static inline bool PlatformUtilsGetEnvSet(const char* /* name */) {
    // Stub func
    return false;
}

static inline std::string PlatformUtilsGetEnv(const char* /* name */) {
    // Stub func
    return {};
}

static inline std::string PlatformUtilsGetSecureEnv(const char* /* name */) {
    // Stub func
    return {};
}

// Intended to be only used as a fallback on Android, with a more open, "native" technique used in most cases
static inline bool PlatformGetGlobalRuntimeFileName(uint16_t major_version, std::string& file_name) {
    // Prefix for the runtime JSON file name
    static const char* rt_dir_prefixes[] = {"/product", "/odm", "/oem", "/vendor", "/system"};

    static const std::string subdir = "/etc/openxr/";
    for(const auto prefix : rt_dir_prefixes) {
        const std::string rt_dir_prefix = prefix + subdir;
        if(detail::ImplTryRuntimeFilename(rt_dir_prefix.c_str(), major_version, file_name) ) {
            return true;
        }
    }

    return false;
}

// Android system properties are sufficiently different from environment variables that we are not re-using
// PlatformUtilsGetEnv for this purpose
static inline std::string PlatformUtilsGetAndroidSystemProperty(const char* name) {
    std::string result;
    const prop_info* pi = __system_property_find(name);
    if(pi == nullptr) {
        return {};
    }


    // use callback to retrieve > 92 character sys prop values, if available
    __system_property_read_callback(
        pi,
        [](void* cookie, const char*, const char* value, uint32_t) {
            auto property_value = reinterpret_cast<std::string*>(cookie);
            *property_value = value;
        },
        reinterpret_cast<void*>(&result) );

    // fallback to __system_property_get if no value retrieved via callback
    if(result.empty() ) {
        char value[PROP_VALUE_MAX] = {};
        if(__system_property_get(name, value) != 0) {
            result = value;
        }
    }

    return result;
}
