
// filesystem_utils.cpp

#include "header.h"

#define OPENXR_RELATIVE_PATH "openxr/"
#define OPENXR_IMPLICIT_API_LAYER_RELATIVE_PATH "/api_layers/implicit.d"
#define OPENXR_EXPLICIT_API_LAYER_RELATIVE_PATH "/api_layers/explicit.d"

#define OPENXR_RUNTIME_JSON_ENV_VAR "XR_RUNTIME_JSON"
#define OPENXR_API_LAYER_PATH_ENV_VAR "XR_API_LAYER_PATH"

#define HAVE_SECURE_GETENV 1
#define HAVE___SECURE_GETENV 1

#define FS_PREFIX std::filesystem

#define PATH_SEPARATOR ':'
#define DIRECTORY_SYMBOL '/'

// We can use one of the C++ filesystem packages

bool FileSysUtilsIsRegularFile(const std::string& path)
{
  return FS_PREFIX::is_regular_file(path);
}

bool FileSysUtilsIsDirectory(const std::string& path)
{
  return FS_PREFIX::is_directory(path);
}

bool FileSysUtilsPathExists(const std::string& path)
{
  return FS_PREFIX::exists(path);
}

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
