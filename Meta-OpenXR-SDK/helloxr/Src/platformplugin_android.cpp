
// platformplugin_android.cpp

#include "header.h"

AndroidPlatformPlugin::AndroidPlatformPlugin(const std::shared_ptr<Options>& /*unused*/, const std::shared_ptr<PlatformData>& data)
{
  instanceCreateInfoAndroid = {XR_TYPE_INSTANCE_CREATE_INFO_ANDROID_KHR};
  instanceCreateInfoAndroid.applicationVM = data->applicationVM;
  instanceCreateInfoAndroid.applicationActivity = data->applicationActivity;
}

std::vector<std::string> AndroidPlatformPlugin::GetInstanceExtensions() const
{
  return {XR_KHR_ANDROID_CREATE_INSTANCE_EXTENSION_NAME};
}

XrBaseInStructure* AndroidPlatformPlugin::GetInstanceCreateExtension() const
{
  return (XrBaseInStructure*) &instanceCreateInfoAndroid;
}

void AndroidPlatformPlugin::UpdateOptions(const std::shared_ptr<struct Options>& /*unused*/)
{
}

//XrInstanceCreateInfoAndroidKHR AndroidPlatformPlugin::instanceCreateInfoAndroid;

std::shared_ptr<AndroidPlatformPlugin> CreatePlatformPlugin_Android(const std::shared_ptr<Options>& options, const std::shared_ptr<PlatformData>& data)
{
  return std::make_shared<AndroidPlatformPlugin>(options, data);
}
