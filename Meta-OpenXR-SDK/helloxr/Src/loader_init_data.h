
// loader_init_data.h

#ifdef XR_KHR_LOADER_INIT_SUPPORT

class LoaderInitData
{
public:

  static LoaderInitData& instance()
  {
    static LoaderInitData obj;
    return obj;
  }

  using StructType = XrLoaderInitInfoAndroidKHR;

  std::string _native_library_path;

  AAssetManager* _android_asset_manager;

  const XrLoaderInitInfoBaseHeaderKHR* getParam() const { return reinterpret_cast<const XrLoaderInitInfoBaseHeaderKHR*>( &_data); }

  const StructType& getData() const { return _data; }

  bool initialized() const noexcept { return _initialized; }

  XrResult initialize(const XrLoaderInitInfoBaseHeaderKHR* info);

private:

  LoaderInitData() = default;

  StructType _data = {};

  bool _initialized = false;
};

XrResult InitializeLoaderInitData(const XrLoaderInitInfoBaseHeaderKHR* loaderInitInfo);

XrResult GetPlatformRuntimeVirtualManifest(Json::Value& out_manifest);

std::string GetAndroidNativeLibraryDir();

void* Android_Get_Asset_Manager();

#endif  // XR_KHR_LOADER_INIT_SUPPORT
