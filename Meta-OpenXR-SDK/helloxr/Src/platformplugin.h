
// platformplugin.h

struct PlatformData
{
  void* applicationVM;
  void* applicationActivity;
};

#ifdef __cplusplus

struct AndroidPlatformPlugin
{
  AndroidPlatformPlugin(const std::shared_ptr<Options>& /*unused*/, const std::shared_ptr<PlatformData>& data);

  std::vector<std::string> GetInstanceExtensions() const;

  XrBaseInStructure* GetInstanceCreateExtension() const;

  void UpdateOptions(const std::shared_ptr<struct Options>& /*unused*/);

  XrInstanceCreateInfoAndroidKHR instanceCreateInfoAndroid;
};

std::shared_ptr<AndroidPlatformPlugin> CreatePlatformPlugin_Android(const std::shared_ptr<Options>& options, const std::shared_ptr<struct PlatformData>& data);

#endif
