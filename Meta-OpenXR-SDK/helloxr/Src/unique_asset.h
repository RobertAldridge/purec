
// unique_asset.h

namespace deleters
{

struct AAssetDeleter
{
  void operator()(AAsset* asset) const
  {
    if(asset != nullptr)
    {
      AAsset_close(asset);
    }
  }
};

struct AAssetDirDeleter
{
  void operator()(AAssetDir* dir) const
  {
    if(dir != nullptr)
    {
      AAssetDir_close(dir);
    }
  }
};

} // namespace deleters

using UniqueAsset = std::unique_ptr<AAsset, deleters::AAssetDeleter>;

using UniqueAssetDir = std::unique_ptr<AAssetDir, deleters::AAssetDirDeleter>;
