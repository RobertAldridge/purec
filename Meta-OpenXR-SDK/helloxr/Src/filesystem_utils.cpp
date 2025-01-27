
// filesystem_utils.cpp

#include <string>
#include <vector>

#include "filesystem_utils.h"

#include <android/native_window.h>
#include <android/window.h>
#include <android/native_window_jni.h>

#include <vulkan/vulkan.h>

#include <string>
#include <stdint.h>
#include <stdlib.h>

#define OPENXR_RELATIVE_PATH "openxr/"
#define OPENXR_IMPLICIT_API_LAYER_RELATIVE_PATH "/api_layers/implicit.d"
#define OPENXR_EXPLICIT_API_LAYER_RELATIVE_PATH "/api_layers/explicit.d"

#define OPENXR_RUNTIME_JSON_ENV_VAR "XR_RUNTIME_JSON"
#define OPENXR_API_LAYER_PATH_ENV_VAR "XR_API_LAYER_PATH"

#define HAVE_SECURE_GETENV 1
#define HAVE___SECURE_GETENV 1

#define XR_ARCH_ABI "arm64-v8a"

void LogPlatformUtilsError(const std::string& message);

#include <sys/stat.h>

#include <sys/system_properties.h>

#include "platform_utils.h"

#include <cstring>
#include <string>

#if defined DISABLE_STD_FILESYSTEM
#define USE_EXPERIMENTAL_FS 0
#define USE_FINAL_FS 0

#else
#include "stdfs_conditions.h"
#endif

#if USE_FINAL_FS == 1
#include <filesystem>
#define FS_PREFIX std::filesystem
#elif USE_EXPERIMENTAL_FS == 1
#include <experimental/filesystem>
#define FS_PREFIX std::experimental::filesystem
#else
// Linux/Apple fallback includes
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <dirent.h>
#endif

#define PATH_SEPARATOR ':'
#define DIRECTORY_SYMBOL '/'

#if(USE_FINAL_FS == 1) || (USE_EXPERIMENTAL_FS == 1)
// We can use one of the C++ filesystem packages

bool FileSysUtilsIsRegularFile(const std::string& path) { return FS_PREFIX::is_regular_file(path); }

bool FileSysUtilsIsDirectory(const std::string& path) { return FS_PREFIX::is_directory(path); }

bool FileSysUtilsPathExists(const std::string& path) { return FS_PREFIX::exists(path); }

bool FileSysUtilsIsAbsolutePath(const std::string& path)
{
  FS_PREFIX::path file_path(path);
  return file_path.is_absolute();
}

bool FileSysUtilsGetCurrentPath(std::string& path)
{
  FS_PREFIX::path cur_path = FS_PREFIX::current_path();
  path = cur_path.string();
  return true;
}

bool FileSysUtilsGetParentPath(const std::string& file_path, std::string& parent_path)
{
  FS_PREFIX::path path_var(file_path);
  parent_path = path_var.parent_path().string();
  return true;
}

bool FileSysUtilsGetAbsolutePath(const std::string& path, std::string& absolute)
{
  absolute = FS_PREFIX::absolute(path).string();
  return true;
}

bool FileSysUtilsGetCanonicalPath(const std::string& path, std::string& canonical)
{
  canonical = FS_PREFIX::canonical(path).string();
  return true;
}

bool FileSysUtilsCombinePaths(const std::string& parent, const std::string& child, std::string& combined)
{
  FS_PREFIX::path parent_path(parent);
  FS_PREFIX::path child_path(child);
  FS_PREFIX::path full_path = parent_path / child_path;
  combined = full_path.string();
  return true;
}

bool FileSysUtilsParsePathList(std::string& path_list, std::vector<std::string>& paths)
{
  std::string::size_type start = 0;
  std::string::size_type location = path_list.find(PATH_SEPARATOR);

  while(location != std::string::npos)
  {
    paths.push_back(path_list.substr(start, location) );
    start = location + 1;
    location = path_list.find(PATH_SEPARATOR, start);
  }

  paths.push_back(path_list.substr(start, location) );

  return true;
}

bool FileSysUtilsFindFilesInPath(const std::string& path, std::vector<std::string>& files)
{
  for(auto& dir_iter : FS_PREFIX::directory_iterator(path) )
    files.push_back(dir_iter.path().filename().string() );

  return true;
}

#else  // XR_OS_LINUX / XR_OS_APPLE fallback

// simple POSIX-compatible implementation of the <filesystem> pieces used by OpenXR

bool FileSysUtilsIsRegularFile(const std::string& path)
{
  struct stat path_stat;
  stat(path.c_str(), &path_stat);
  return S_ISREG(path_stat.st_mode);
}

bool FileSysUtilsIsDirectory(const std::string& path)
{
  struct stat path_stat;
  stat(path.c_str(), &path_stat);
  return S_ISDIR(path_stat.st_mode);
}

bool FileSysUtilsPathExists(const std::string& path) { return (access(path.c_str(), F_OK) != -1); }

bool FileSysUtilsIsAbsolutePath(const std::string& path) { return (path[0] == DIRECTORY_SYMBOL); }

bool FileSysUtilsGetCurrentPath(std::string& path)
{
  char tmp_path[PATH_MAX] = {0};

  if(nullptr != getcwd(tmp_path, PATH_MAX - 1) )
  {
    path = tmp_path;
    return true;
  }

  return false;
}

bool FileSysUtilsGetParentPath(const std::string& file_path, std::string& parent_path)
{
  std::string full_path;

  if(FileSysUtilsGetAbsolutePath(file_path, full_path) )
  {
    std::string::size_type lastSeparator = full_path.find_last_of(DIRECTORY_SYMBOL);
    parent_path = (lastSeparator == 0) ? full_path : full_path.substr(0, lastSeparator);
    return true;
  }

  return false;
}

bool FileSysUtilsGetAbsolutePath(const std::string& path, std::string& absolute)
{
  // canonical path is absolute
  return FileSysUtilsGetCanonicalPath(path, absolute);
}

bool FileSysUtilsGetCanonicalPath(const std::string& path, std::string& canonical)
{
  char buf[PATH_MAX] = {0};

  if(nullptr != realpath(path.c_str(), buf) )
  {
    canonical = buf;
    return true;
  }

  return false;
}

bool FileSysUtilsCombinePaths(const std::string& parent, const std::string& child, std::string& combined)
{
  std::string::size_type parent_len = parent.length();

  if(0 == parent_len || "." == parent || "./" == parent)
  {
    combined = child;
    return true;
  }

  char last_char = parent[parent_len - 1];

  if(last_char == DIRECTORY_SYMBOL)
    parent_len--;

  combined = parent.substr(0, parent_len) + DIRECTORY_SYMBOL + child;

  return true;
}

bool FileSysUtilsParsePathList(std::string& path_list, std::vector<std::string>& paths)
{
  std::string::size_type start = 0;
  std::string::size_type location = path_list.find(PATH_SEPARATOR);

  while(location != std::string::npos)
  {
    paths.push_back(path_list.substr(start, location) );
    start = location + 1;
    location = path_list.find(PATH_SEPARATOR, start);
  }

  paths.push_back(path_list.substr(start, location) );

  return true;
}

bool FileSysUtilsFindFilesInPath(const std::string& path, std::vector<std::string>& files)
{
  DIR* dir = opendir(path.c_str() );
  if(dir == nullptr)
    return false;

  struct dirent* entry = 0;
  while( (entry = readdir(dir) ) != nullptr)
    files.emplace_back(entry->d_name);

  closedir(dir);

  return true;
}

#endif
