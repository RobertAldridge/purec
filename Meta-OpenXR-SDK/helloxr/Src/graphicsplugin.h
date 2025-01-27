
// graphicsplugin.h

struct Cube
{
  XrPosef Pose;
  XrVector3f Scale;
};

struct IGraphicsPlugin
{
  virtual ~IGraphicsPlugin() = default;

  virtual std::vector<std::string> GetInstanceExtensions() const = 0;

  virtual void InitializeDevice(XrInstance instance, XrSystemId systemId) = 0;

  virtual int64_t SelectColorSwapchainFormat(const std::vector<int64_t>& runtimeFormats) const = 0;

  virtual const XrBaseInStructure* GetGraphicsBinding() const = 0;

  virtual std::vector<XrSwapchainImageBaseHeader*> AllocateSwapchainImageStructs(uint32_t capacity, const XrSwapchainCreateInfo& swapchainCreateInfo) = 0;

  virtual void RenderView(const XrCompositionLayerProjectionView& layerView, const XrSwapchainImageBaseHeader* swapchainImage, int64_t swapchainFormat, const std::vector<Cube>& cubes) = 0;

  virtual uint32_t GetSupportedSwapchainSampleCount(const XrViewConfigurationView& view)
  {
    return view.recommendedSwapchainSampleCount;
  }

  virtual void UpdateOptions(const std::shared_ptr<struct Options>& options) = 0;
};

std::shared_ptr<IGraphicsPlugin> CreateGraphicsPlugin(const std::shared_ptr<struct Options>& options, std::shared_ptr<struct IPlatformPlugin> platformPlugin);
