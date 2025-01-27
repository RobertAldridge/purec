
// loader_init_data.h

#ifdef XR_KHR_LOADER_INIT_SUPPORT

/*!
 * Stores a copy of the data passed to the tableXr.InitializeLoaderKHR function in a singleton.
 */
class LoaderInitData
{
   public:
    /*!
     * Singleton accessor.
     */
    static LoaderInitData& instance()
    {
        static LoaderInitData obj;
        return obj;
    }

    /*!
     * Type alias for the platform-specific structure type.
     */
    using StructType = XrLoaderInitInfoAndroidKHR;
    /*!
     * Native library path.
     */
    std::string _native_library_path;
    /*!
     * Android asset manager.
     */
    AAssetManager* _android_asset_manager;

    /*!
     * Get our copy of the data, casted to pass to the runtime's matching method.
     */
    const XrLoaderInitInfoBaseHeaderKHR* getParam() const { return reinterpret_cast<const XrLoaderInitInfoBaseHeaderKHR*>(&_data); }

    /*!
     * Get the data via its real structure type.
     */
    const StructType& getData() const { return _data; }

    /*!
     * Has this been correctly initialized?
     */
    bool initialized() const noexcept { return _initialized; }

    /*!
     * Initialize loader data - called by InitializeLoaderInitData() and thus ultimately by the loader's tableXr.InitializeLoaderKHR
     * implementation. Each platform that needs this extension will provide an implementation of this.
     */
    XrResult initialize(const XrLoaderInitInfoBaseHeaderKHR* info);

   private:

    //! Private constructor, forces use of singleton accessor.
    LoaderInitData() = default;

    //! Platform-specific init data
    StructType _data = {};

    //! Flag for indicating whether _data is valid.
    bool _initialized = false;
};

//! Initialize loader init data, where required.
XrResult InitializeLoaderInitData(const XrLoaderInitInfoBaseHeaderKHR* loaderInitInfo);

XrResult GetPlatformRuntimeVirtualManifest(Json::Value& out_manifest);

std::string GetAndroidNativeLibraryDir();

void* Android_Get_Asset_Manager();

#endif  // XR_KHR_LOADER_INIT_SUPPORT
