
// platformplugin.h

#pragma once

struct IPlatformPlugin
{
    virtual ~IPlatformPlugin() = default;

    virtual XrBaseInStructure* GetInstanceCreateExtension() const = 0;

    virtual std::vector<std::string> GetInstanceExtensions() const = 0;

    virtual void UpdateOptions(const std::shared_ptr<struct Options>& options) = 0;
};

std::shared_ptr<IPlatformPlugin> CreatePlatformPlugin(const std::shared_ptr<struct Options>& options, const std::shared_ptr<struct PlatformData>& data);
