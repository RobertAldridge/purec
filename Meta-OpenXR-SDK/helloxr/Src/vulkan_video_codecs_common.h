
// vulkan_video_codecs_common.h

// vulkan_video_codecs_common is a preprocessor guard. Do not pass it to API calls.
#define vulkan_video_codecs_common 1

#define VK_MAKE_VIDEO_STD_VERSION(major, minor, patch) \
  ( ( ( (uint32_t)(major) ) << 22) | ( ( (uint32_t)(minor) ) << 12) | ( (uint32_t)(patch) ) )
