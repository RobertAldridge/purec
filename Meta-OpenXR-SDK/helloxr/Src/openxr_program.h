
// openxr_program.h

#pragma once

struct IOpenXrProgram
{
  virtual ~IOpenXrProgram() = default;

  virtual void CreateInstance() = 0;

  virtual void InitializeSystem() = 0;

  virtual void InitializeDevice() = 0;

  virtual void InitializeSession() = 0;

  virtual void CreateSwapchains() = 0;

  virtual void PollEvents(bool* exitRenderLoop, bool* requestRestart) = 0;

  virtual bool IsSessionRunning() const = 0;

  virtual bool IsSessionFocused() const = 0;

  virtual void PollActions() = 0;

  virtual void RenderFrame() = 0;

  virtual XrEnvironmentBlendMode GetPreferredBlendMode() const = 0;
};

struct Swapchain
{
  XrSwapchain handle;
  int32_t width;
  int32_t height;
};

std::shared_ptr<IOpenXrProgram> CreateOpenXrProgram(const std::shared_ptr<Options>& options, const std::shared_ptr<IPlatformPlugin>& platformPlugin, const std::shared_ptr<IGraphicsPlugin>& graphicsPlugin);
