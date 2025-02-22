
// vulkan_video_codec_h264std_decode.h

// vulkan_video_codec_h264std_decode is a preprocessor guard. Do not pass it to API calls.
#define vulkan_video_codec_h264std_decode 1

#define VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_VERSION_1_0_0 VK_MAKE_VIDEO_STD_VERSION(1, 0, 0)

#define VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_SPEC_VERSION VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_VERSION_1_0_0
#define VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h264_decode"
#define STD_VIDEO_DECODE_H264_FIELD_ORDER_COUNT_LIST_SIZE 2

enum StdVideoDecodeH264FieldOrderCount
{
  STD_VIDEO_DECODE_H264_FIELD_ORDER_COUNT_TOP = 0,
  STD_VIDEO_DECODE_H264_FIELD_ORDER_COUNT_BOTTOM = 1,
  STD_VIDEO_DECODE_H264_FIELD_ORDER_COUNT_INVALID = 0x7FFFFFFF,
  STD_VIDEO_DECODE_H264_FIELD_ORDER_COUNT_MAX_ENUM = 0x7FFFFFFF
};

struct StdVideoDecodeH264PictureInfoFlags
{
  uint32_t field_pic_flag : 1;
  uint32_t is_intra : 1;
  uint32_t IdrPicFlag : 1;
  uint32_t bottom_field_flag : 1;
  uint32_t is_reference : 1;
  uint32_t complementary_field_pair : 1;
};

struct StdVideoDecodeH264PictureInfo
{
  StdVideoDecodeH264PictureInfoFlags flags;
  uint8_t seq_parameter_set_id;
  uint8_t pic_parameter_set_id;
  uint8_t reserved1;
  uint8_t reserved2;
  uint16_t frame_num;
  uint16_t idr_pic_id;
  int32_t PicOrderCnt[STD_VIDEO_DECODE_H264_FIELD_ORDER_COUNT_LIST_SIZE];
};

struct StdVideoDecodeH264ReferenceInfoFlags
{
  uint32_t top_field_flag : 1;
  uint32_t bottom_field_flag : 1;
  uint32_t used_for_long_term_reference : 1;
  uint32_t is_non_existing : 1;
};

struct StdVideoDecodeH264ReferenceInfo
{
  StdVideoDecodeH264ReferenceInfoFlags flags;
  uint16_t FrameNum;
  uint16_t reserved;
  int32_t PicOrderCnt[STD_VIDEO_DECODE_H264_FIELD_ORDER_COUNT_LIST_SIZE];
};
