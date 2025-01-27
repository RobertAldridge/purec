
// platform_utils.h

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

static inline bool PlatformUtilsGetEnvSet(const char* /* name */)
{
  // Stub func
  return false;
}

static inline std::string PlatformUtilsGetEnv(const char* /* name */)
{
  // Stub func
  return {};
}

static inline std::string PlatformUtilsGetSecureEnv(const char* /* name */)
{
  // Stub func
  return {};
}

// Intended to be only used as a fallback on Android, with a more open, "native" technique used in most cases
static inline bool PlatformGetGlobalRuntimeFileName(uint16_t major_version, std::string& file_name)
{
  // Prefix for the runtime JSON file name
  static const char* rt_dir_prefixes[] = {"/product", "/odm", "/oem", "/vendor", "/system"};

  static const std::string subdir = "/etc/openxr/";

  for(const auto prefix : rt_dir_prefixes)
  {
    const std::string rt_dir_prefix = prefix + subdir;

    if(detail::ImplTryRuntimeFilename(rt_dir_prefix.c_str(), major_version, file_name) )
      return true;
  }

  return false;
}

// Android system properties are sufficiently different from environment variables that we are not re-using
// PlatformUtilsGetEnv for this purpose
static inline std::string PlatformUtilsGetAndroidSystemProperty(const char* name)
{
  std::string result;
  const prop_info* pi = __system_property_find(name);

  if(pi == nullptr)
    return {};

  // use callback to retrieve > 92 character sys prop values, if available
  __system_property_read_callback(pi, [](void* cookie, const char*, const char* value, uint32_t)
  {
    auto property_value = reinterpret_cast<std::string*>(cookie);
    *property_value = value;
  },

  reinterpret_cast<void*>(&result) );

  // fallback to __system_property_get if no value retrieved via callback
  if(result.empty() )
  {
    char value[PROP_VALUE_MAX] = {};

    if(__system_property_get(name, value) != 0)
      result = value;
  }

  return result;
}
