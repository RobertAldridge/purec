
// vulkan_beta.h

extern "C" {

// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_portability_subset 1
#define VK_KHR_PORTABILITY_SUBSET_SPEC_VERSION 1
#define VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

struct VkPhysicalDevicePortabilitySubsetFeaturesKHR
{
  VkStructureType sType;
  void* pNext;
  VkBool32 constantAlphaColorBlendFactors;
  VkBool32 events;
  VkBool32 imageViewFormatReinterpretation;
  VkBool32 imageViewFormatSwizzle;
  VkBool32 imageView2DOn3DImage;
  VkBool32 multisampleArrayImage;
  VkBool32 mutableComparisonSamplers;
  VkBool32 pointPolygons;
  VkBool32 samplerMipLodBias;
  VkBool32 separateStencilMaskRef;
  VkBool32 shaderSampleRateInterpolationFunctions;
  VkBool32 tessellationIsolines;
  VkBool32 tessellationPointMode;
  VkBool32 triangleFans;
  VkBool32 vertexAttributeAccessBeyondStride;
};

struct VkPhysicalDevicePortabilitySubsetPropertiesKHR
{
  VkStructureType sType;
  void* pNext;
  uint32_t minVertexInputBindingStrideAlignment;
};

// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_displacement_micromap 1
#define VK_NV_DISPLACEMENT_MICROMAP_SPEC_VERSION 2
#define VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

enum VkDisplacementMicromapFormatNV
{
  VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV = 1,
  VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV = 2,
  VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV = 3,
  VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
};

struct VkPhysicalDeviceDisplacementMicromapFeaturesNV
{
  VkStructureType sType;
  void* pNext;
  VkBool32 displacementMicromap;
};

struct VkPhysicalDeviceDisplacementMicromapPropertiesNV
{
  VkStructureType sType;
  void* pNext;
  uint32_t maxDisplacementMicromapSubdivisionLevel;
};

struct VkAccelerationStructureTrianglesDisplacementMicromapNV
{
  VkStructureType sType;
  void* pNext;
  VkFormat displacementBiasAndScaleFormat;
  VkFormat displacementVectorFormat;
  VkDeviceOrHostAddressConstKHR displacementBiasAndScaleBuffer;
  VkDeviceSize displacementBiasAndScaleStride;
  VkDeviceOrHostAddressConstKHR displacementVectorBuffer;
  VkDeviceSize displacementVectorStride;
  VkDeviceOrHostAddressConstKHR displacedMicromapPrimitiveFlags;
  VkDeviceSize displacedMicromapPrimitiveFlagsStride;
  VkIndexType indexType;
  VkDeviceOrHostAddressConstKHR indexBuffer;
  VkDeviceSize indexStride;
  uint32_t baseTriangle;
  uint32_t usageCountsCount;
  const VkMicromapUsageEXT* pUsageCounts;
  const VkMicromapUsageEXT* const* ppUsageCounts;
  VkMicromapEXT micromap;
};

}
