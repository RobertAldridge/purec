
// vulkan_core2.h

extern "C" {

// VK_KHR_video_encode_h264 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_video_encode_h264 1

#define VK_KHR_VIDEO_ENCODE_H264_SPEC_VERSION 14
#define VK_KHR_VIDEO_ENCODE_H264_EXTENSION_NAME "VK_KHR_video_encode_h264"

typedef enum VkVideoEncodeH264CapabilityFlagBitsKHR {
 VK_VIDEO_ENCODE_H264_CAPABILITY_HRD_COMPLIANCE_BIT_KHR = 0x00000001,
 VK_VIDEO_ENCODE_H264_CAPABILITY_PREDICTION_WEIGHT_TABLE_GENERATED_BIT_KHR = 0x00000002,
 VK_VIDEO_ENCODE_H264_CAPABILITY_ROW_UNALIGNED_SLICE_BIT_KHR = 0x00000004,
 VK_VIDEO_ENCODE_H264_CAPABILITY_DIFFERENT_SLICE_TYPE_BIT_KHR = 0x00000008,
 VK_VIDEO_ENCODE_H264_CAPABILITY_B_FRAME_IN_L0_LIST_BIT_KHR = 0x00000010,
 VK_VIDEO_ENCODE_H264_CAPABILITY_B_FRAME_IN_L1_LIST_BIT_KHR = 0x00000020,
 VK_VIDEO_ENCODE_H264_CAPABILITY_PER_PICTURE_TYPE_MIN_MAX_QP_BIT_KHR = 0x00000040,
 VK_VIDEO_ENCODE_H264_CAPABILITY_PER_SLICE_CONSTANT_QP_BIT_KHR = 0x00000080,
 VK_VIDEO_ENCODE_H264_CAPABILITY_GENERATE_PREFIX_NALU_BIT_KHR = 0x00000100,
 VK_VIDEO_ENCODE_H264_CAPABILITY_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkVideoEncodeH264CapabilityFlagBitsKHR;
typedef VkFlags VkVideoEncodeH264CapabilityFlagsKHR;

typedef enum VkVideoEncodeH264StdFlagBitsKHR {
 VK_VIDEO_ENCODE_H264_STD_SEPARATE_COLOR_PLANE_FLAG_SET_BIT_KHR = 0x00000001,
 VK_VIDEO_ENCODE_H264_STD_QPPRIME_Y_ZERO_TRANSFORM_BYPASS_FLAG_SET_BIT_KHR = 0x00000002,
 VK_VIDEO_ENCODE_H264_STD_SCALING_MATRIX_PRESENT_FLAG_SET_BIT_KHR = 0x00000004,
 VK_VIDEO_ENCODE_H264_STD_CHROMA_QP_INDEX_OFFSET_BIT_KHR = 0x00000008,
 VK_VIDEO_ENCODE_H264_STD_SECOND_CHROMA_QP_INDEX_OFFSET_BIT_KHR = 0x00000010,
 VK_VIDEO_ENCODE_H264_STD_PIC_INIT_QP_MINUS26_BIT_KHR = 0x00000020,
 VK_VIDEO_ENCODE_H264_STD_WEIGHTED_PRED_FLAG_SET_BIT_KHR = 0x00000040,
 VK_VIDEO_ENCODE_H264_STD_WEIGHTED_BIPRED_IDC_EXPLICIT_BIT_KHR = 0x00000080,
 VK_VIDEO_ENCODE_H264_STD_WEIGHTED_BIPRED_IDC_IMPLICIT_BIT_KHR = 0x00000100,
 VK_VIDEO_ENCODE_H264_STD_TRANSFORM_8X8_MODE_FLAG_SET_BIT_KHR = 0x00000200,
 VK_VIDEO_ENCODE_H264_STD_DIRECT_SPATIAL_MV_PRED_FLAG_UNSET_BIT_KHR = 0x00000400,
 VK_VIDEO_ENCODE_H264_STD_ENTROPY_CODING_MODE_FLAG_UNSET_BIT_KHR = 0x00000800,
 VK_VIDEO_ENCODE_H264_STD_ENTROPY_CODING_MODE_FLAG_SET_BIT_KHR = 0x00001000,
 VK_VIDEO_ENCODE_H264_STD_DIRECT_8X8_INFERENCE_FLAG_UNSET_BIT_KHR = 0x00002000,
 VK_VIDEO_ENCODE_H264_STD_CONSTRAINED_INTRA_PRED_FLAG_SET_BIT_KHR = 0x00004000,
 VK_VIDEO_ENCODE_H264_STD_DEBLOCKING_FILTER_DISABLED_BIT_KHR = 0x00008000,
 VK_VIDEO_ENCODE_H264_STD_DEBLOCKING_FILTER_ENABLED_BIT_KHR = 0x00010000,
 VK_VIDEO_ENCODE_H264_STD_DEBLOCKING_FILTER_PARTIAL_BIT_KHR = 0x00020000,
 VK_VIDEO_ENCODE_H264_STD_SLICE_QP_DELTA_BIT_KHR = 0x00080000,
 VK_VIDEO_ENCODE_H264_STD_DIFFERENT_SLICE_QP_DELTA_BIT_KHR = 0x00100000,
 VK_VIDEO_ENCODE_H264_STD_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkVideoEncodeH264StdFlagBitsKHR;
typedef VkFlags VkVideoEncodeH264StdFlagsKHR;

typedef enum VkVideoEncodeH264RateControlFlagBitsKHR {
 VK_VIDEO_ENCODE_H264_RATE_CONTROL_ATTEMPT_HRD_COMPLIANCE_BIT_KHR = 0x00000001,
 VK_VIDEO_ENCODE_H264_RATE_CONTROL_REGULAR_GOP_BIT_KHR = 0x00000002,
 VK_VIDEO_ENCODE_H264_RATE_CONTROL_REFERENCE_PATTERN_FLAT_BIT_KHR = 0x00000004,
 VK_VIDEO_ENCODE_H264_RATE_CONTROL_REFERENCE_PATTERN_DYADIC_BIT_KHR = 0x00000008,
 VK_VIDEO_ENCODE_H264_RATE_CONTROL_TEMPORAL_LAYER_PATTERN_DYADIC_BIT_KHR = 0x00000010,
 VK_VIDEO_ENCODE_H264_RATE_CONTROL_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkVideoEncodeH264RateControlFlagBitsKHR;
typedef VkFlags VkVideoEncodeH264RateControlFlagsKHR;
typedef struct VkVideoEncodeH264CapabilitiesKHR {
 VkStructureType sType;
 void* pNext;
 VkVideoEncodeH264CapabilityFlagsKHR flags;
 StdVideoH264LevelIdc maxLevelIdc;
 uint32_t maxSliceCount;
 uint32_t maxPPictureL0ReferenceCount;
 uint32_t maxBPictureL0ReferenceCount;
 uint32_t maxL1ReferenceCount;
 uint32_t maxTemporalLayerCount;
 VkBool32 expectDyadicTemporalLayerPattern;
 int32_t minQp;
 int32_t maxQp;
 VkBool32 prefersGopRemainingFrames;
 VkBool32 requiresGopRemainingFrames;
 VkVideoEncodeH264StdFlagsKHR stdSyntaxFlags;
} VkVideoEncodeH264CapabilitiesKHR;

typedef struct VkVideoEncodeH264QpKHR {
 int32_t qpI;
 int32_t qpP;
 int32_t qpB;
} VkVideoEncodeH264QpKHR;

typedef struct VkVideoEncodeH264QualityLevelPropertiesKHR {
 VkStructureType sType;
 void* pNext;
 VkVideoEncodeH264RateControlFlagsKHR preferredRateControlFlags;
 uint32_t preferredGopFrameCount;
 uint32_t preferredIdrPeriod;
 uint32_t preferredConsecutiveBFrameCount;
 uint32_t preferredTemporalLayerCount;
 VkVideoEncodeH264QpKHR preferredConstantQp;
 uint32_t preferredMaxL0ReferenceCount;
 uint32_t preferredMaxL1ReferenceCount;
 VkBool32 preferredStdEntropyCodingModeFlag;
} VkVideoEncodeH264QualityLevelPropertiesKHR;

typedef struct VkVideoEncodeH264SessionCreateInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkBool32 useMaxLevelIdc;
 StdVideoH264LevelIdc maxLevelIdc;
} VkVideoEncodeH264SessionCreateInfoKHR;

typedef struct VkVideoEncodeH264SessionParametersAddInfoKHR {
 VkStructureType sType;
 const void* pNext;
 uint32_t stdSPSCount;
 const StdVideoH264SequenceParameterSet* pStdSPSs;
 uint32_t stdPPSCount;
 const StdVideoH264PictureParameterSet* pStdPPSs;
} VkVideoEncodeH264SessionParametersAddInfoKHR;

typedef struct VkVideoEncodeH264SessionParametersCreateInfoKHR {
 VkStructureType sType;
 const void* pNext;
 uint32_t maxStdSPSCount;
 uint32_t maxStdPPSCount;
 const VkVideoEncodeH264SessionParametersAddInfoKHR* pParametersAddInfo;
} VkVideoEncodeH264SessionParametersCreateInfoKHR;

typedef struct VkVideoEncodeH264SessionParametersGetInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkBool32 writeStdSPS;
 VkBool32 writeStdPPS;
 uint32_t stdSPSId;
 uint32_t stdPPSId;
} VkVideoEncodeH264SessionParametersGetInfoKHR;

typedef struct VkVideoEncodeH264SessionParametersFeedbackInfoKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 hasStdSPSOverrides;
 VkBool32 hasStdPPSOverrides;
} VkVideoEncodeH264SessionParametersFeedbackInfoKHR;

typedef struct VkVideoEncodeH264NaluSliceInfoKHR {
 VkStructureType sType;
 const void* pNext;
 int32_t constantQp;
 const StdVideoEncodeH264SliceHeader* pStdSliceHeader;
} VkVideoEncodeH264NaluSliceInfoKHR;

typedef struct VkVideoEncodeH264PictureInfoKHR {
 VkStructureType sType;
 const void* pNext;
 uint32_t naluSliceEntryCount;
 const VkVideoEncodeH264NaluSliceInfoKHR* pNaluSliceEntries;
 const StdVideoEncodeH264PictureInfo* pStdPictureInfo;
 VkBool32 generatePrefixNalu;
} VkVideoEncodeH264PictureInfoKHR;

typedef struct VkVideoEncodeH264DpbSlotInfoKHR {
 VkStructureType sType;
 const void* pNext;
 const StdVideoEncodeH264ReferenceInfo* pStdReferenceInfo;
} VkVideoEncodeH264DpbSlotInfoKHR;

typedef struct VkVideoEncodeH264ProfileInfoKHR {
 VkStructureType sType;
 const void* pNext;
 StdVideoH264ProfileIdc stdProfileIdc;
} VkVideoEncodeH264ProfileInfoKHR;

typedef struct VkVideoEncodeH264RateControlInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkVideoEncodeH264RateControlFlagsKHR flags;
 uint32_t gopFrameCount;
 uint32_t idrPeriod;
 uint32_t consecutiveBFrameCount;
 uint32_t temporalLayerCount;
} VkVideoEncodeH264RateControlInfoKHR;

typedef struct VkVideoEncodeH264FrameSizeKHR {
 uint32_t frameISize;
 uint32_t framePSize;
 uint32_t frameBSize;
} VkVideoEncodeH264FrameSizeKHR;

typedef struct VkVideoEncodeH264RateControlLayerInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkBool32 useMinQp;
 VkVideoEncodeH264QpKHR minQp;
 VkBool32 useMaxQp;
 VkVideoEncodeH264QpKHR maxQp;
 VkBool32 useMaxFrameSize;
 VkVideoEncodeH264FrameSizeKHR maxFrameSize;
} VkVideoEncodeH264RateControlLayerInfoKHR;

typedef struct VkVideoEncodeH264GopRemainingFrameInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkBool32 useGopRemainingFrames;
 uint32_t gopRemainingI;
 uint32_t gopRemainingP;
 uint32_t gopRemainingB;
} VkVideoEncodeH264GopRemainingFrameInfoKHR;

// VK_KHR_video_encode_h265 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_video_encode_h265 1

#define VK_KHR_VIDEO_ENCODE_H265_SPEC_VERSION 14
#define VK_KHR_VIDEO_ENCODE_H265_EXTENSION_NAME "VK_KHR_video_encode_h265"

typedef enum VkVideoEncodeH265CapabilityFlagBitsKHR {
 VK_VIDEO_ENCODE_H265_CAPABILITY_HRD_COMPLIANCE_BIT_KHR = 0x00000001,
 VK_VIDEO_ENCODE_H265_CAPABILITY_PREDICTION_WEIGHT_TABLE_GENERATED_BIT_KHR = 0x00000002,
 VK_VIDEO_ENCODE_H265_CAPABILITY_ROW_UNALIGNED_SLICE_SEGMENT_BIT_KHR = 0x00000004,
 VK_VIDEO_ENCODE_H265_CAPABILITY_DIFFERENT_SLICE_SEGMENT_TYPE_BIT_KHR = 0x00000008,
 VK_VIDEO_ENCODE_H265_CAPABILITY_B_FRAME_IN_L0_LIST_BIT_KHR = 0x00000010,
 VK_VIDEO_ENCODE_H265_CAPABILITY_B_FRAME_IN_L1_LIST_BIT_KHR = 0x00000020,
 VK_VIDEO_ENCODE_H265_CAPABILITY_PER_PICTURE_TYPE_MIN_MAX_QP_BIT_KHR = 0x00000040,
 VK_VIDEO_ENCODE_H265_CAPABILITY_PER_SLICE_SEGMENT_CONSTANT_QP_BIT_KHR = 0x00000080,
 VK_VIDEO_ENCODE_H265_CAPABILITY_MULTIPLE_TILES_PER_SLICE_SEGMENT_BIT_KHR = 0x00000100,
 VK_VIDEO_ENCODE_H265_CAPABILITY_MULTIPLE_SLICE_SEGMENTS_PER_TILE_BIT_KHR = 0x00000200,
 VK_VIDEO_ENCODE_H265_CAPABILITY_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkVideoEncodeH265CapabilityFlagBitsKHR;
typedef VkFlags VkVideoEncodeH265CapabilityFlagsKHR;

typedef enum VkVideoEncodeH265StdFlagBitsKHR {
 VK_VIDEO_ENCODE_H265_STD_SEPARATE_COLOR_PLANE_FLAG_SET_BIT_KHR = 0x00000001,
 VK_VIDEO_ENCODE_H265_STD_SAMPLE_ADAPTIVE_OFFSET_ENABLED_FLAG_SET_BIT_KHR = 0x00000002,
 VK_VIDEO_ENCODE_H265_STD_SCALING_LIST_DATA_PRESENT_FLAG_SET_BIT_KHR = 0x00000004,
 VK_VIDEO_ENCODE_H265_STD_PCM_ENABLED_FLAG_SET_BIT_KHR = 0x00000008,
 VK_VIDEO_ENCODE_H265_STD_SPS_TEMPORAL_MVP_ENABLED_FLAG_SET_BIT_KHR = 0x00000010,
 VK_VIDEO_ENCODE_H265_STD_INIT_QP_MINUS26_BIT_KHR = 0x00000020,
 VK_VIDEO_ENCODE_H265_STD_WEIGHTED_PRED_FLAG_SET_BIT_KHR = 0x00000040,
 VK_VIDEO_ENCODE_H265_STD_WEIGHTED_BIPRED_FLAG_SET_BIT_KHR = 0x00000080,
 VK_VIDEO_ENCODE_H265_STD_LOG2_PARALLEL_MERGE_LEVEL_MINUS2_BIT_KHR = 0x00000100,
 VK_VIDEO_ENCODE_H265_STD_SIGN_DATA_HIDING_ENABLED_FLAG_SET_BIT_KHR = 0x00000200,
 VK_VIDEO_ENCODE_H265_STD_TRANSFORM_SKIP_ENABLED_FLAG_SET_BIT_KHR = 0x00000400,
 VK_VIDEO_ENCODE_H265_STD_TRANSFORM_SKIP_ENABLED_FLAG_UNSET_BIT_KHR = 0x00000800,
 VK_VIDEO_ENCODE_H265_STD_PPS_SLICE_CHROMA_QP_OFFSETS_PRESENT_FLAG_SET_BIT_KHR = 0x00001000,
 VK_VIDEO_ENCODE_H265_STD_TRANSQUANT_BYPASS_ENABLED_FLAG_SET_BIT_KHR = 0x00002000,
 VK_VIDEO_ENCODE_H265_STD_CONSTRAINED_INTRA_PRED_FLAG_SET_BIT_KHR = 0x00004000,
 VK_VIDEO_ENCODE_H265_STD_ENTROPY_CODING_SYNC_ENABLED_FLAG_SET_BIT_KHR = 0x00008000,
 VK_VIDEO_ENCODE_H265_STD_DEBLOCKING_FILTER_OVERRIDE_ENABLED_FLAG_SET_BIT_KHR = 0x00010000,
 VK_VIDEO_ENCODE_H265_STD_DEPENDENT_SLICE_SEGMENTS_ENABLED_FLAG_SET_BIT_KHR = 0x00020000,
 VK_VIDEO_ENCODE_H265_STD_DEPENDENT_SLICE_SEGMENT_FLAG_SET_BIT_KHR = 0x00040000,
 VK_VIDEO_ENCODE_H265_STD_SLICE_QP_DELTA_BIT_KHR = 0x00080000,
 VK_VIDEO_ENCODE_H265_STD_DIFFERENT_SLICE_QP_DELTA_BIT_KHR = 0x00100000,
 VK_VIDEO_ENCODE_H265_STD_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkVideoEncodeH265StdFlagBitsKHR;
typedef VkFlags VkVideoEncodeH265StdFlagsKHR;

typedef enum VkVideoEncodeH265CtbSizeFlagBitsKHR {
 VK_VIDEO_ENCODE_H265_CTB_SIZE_16_BIT_KHR = 0x00000001,
 VK_VIDEO_ENCODE_H265_CTB_SIZE_32_BIT_KHR = 0x00000002,
 VK_VIDEO_ENCODE_H265_CTB_SIZE_64_BIT_KHR = 0x00000004,
 VK_VIDEO_ENCODE_H265_CTB_SIZE_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkVideoEncodeH265CtbSizeFlagBitsKHR;
typedef VkFlags VkVideoEncodeH265CtbSizeFlagsKHR;

typedef enum VkVideoEncodeH265TransformBlockSizeFlagBitsKHR {
 VK_VIDEO_ENCODE_H265_TRANSFORM_BLOCK_SIZE_4_BIT_KHR = 0x00000001,
 VK_VIDEO_ENCODE_H265_TRANSFORM_BLOCK_SIZE_8_BIT_KHR = 0x00000002,
 VK_VIDEO_ENCODE_H265_TRANSFORM_BLOCK_SIZE_16_BIT_KHR = 0x00000004,
 VK_VIDEO_ENCODE_H265_TRANSFORM_BLOCK_SIZE_32_BIT_KHR = 0x00000008,
 VK_VIDEO_ENCODE_H265_TRANSFORM_BLOCK_SIZE_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkVideoEncodeH265TransformBlockSizeFlagBitsKHR;
typedef VkFlags VkVideoEncodeH265TransformBlockSizeFlagsKHR;

typedef enum VkVideoEncodeH265RateControlFlagBitsKHR {
 VK_VIDEO_ENCODE_H265_RATE_CONTROL_ATTEMPT_HRD_COMPLIANCE_BIT_KHR = 0x00000001,
 VK_VIDEO_ENCODE_H265_RATE_CONTROL_REGULAR_GOP_BIT_KHR = 0x00000002,
 VK_VIDEO_ENCODE_H265_RATE_CONTROL_REFERENCE_PATTERN_FLAT_BIT_KHR = 0x00000004,
 VK_VIDEO_ENCODE_H265_RATE_CONTROL_REFERENCE_PATTERN_DYADIC_BIT_KHR = 0x00000008,
 VK_VIDEO_ENCODE_H265_RATE_CONTROL_TEMPORAL_SUB_LAYER_PATTERN_DYADIC_BIT_KHR = 0x00000010,
 VK_VIDEO_ENCODE_H265_RATE_CONTROL_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkVideoEncodeH265RateControlFlagBitsKHR;
typedef VkFlags VkVideoEncodeH265RateControlFlagsKHR;
typedef struct VkVideoEncodeH265CapabilitiesKHR {
 VkStructureType sType;
 void* pNext;
 VkVideoEncodeH265CapabilityFlagsKHR flags;
 StdVideoH265LevelIdc maxLevelIdc;
 uint32_t maxSliceSegmentCount;
 VkExtent2D maxTiles;
 VkVideoEncodeH265CtbSizeFlagsKHR ctbSizes;
 VkVideoEncodeH265TransformBlockSizeFlagsKHR transformBlockSizes;
 uint32_t maxPPictureL0ReferenceCount;
 uint32_t maxBPictureL0ReferenceCount;
 uint32_t maxL1ReferenceCount;
 uint32_t maxSubLayerCount;
 VkBool32 expectDyadicTemporalSubLayerPattern;
 int32_t minQp;
 int32_t maxQp;
 VkBool32 prefersGopRemainingFrames;
 VkBool32 requiresGopRemainingFrames;
 VkVideoEncodeH265StdFlagsKHR stdSyntaxFlags;
} VkVideoEncodeH265CapabilitiesKHR;

typedef struct VkVideoEncodeH265SessionCreateInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkBool32 useMaxLevelIdc;
 StdVideoH265LevelIdc maxLevelIdc;
} VkVideoEncodeH265SessionCreateInfoKHR;

typedef struct VkVideoEncodeH265QpKHR {
 int32_t qpI;
 int32_t qpP;
 int32_t qpB;
} VkVideoEncodeH265QpKHR;

typedef struct VkVideoEncodeH265QualityLevelPropertiesKHR {
 VkStructureType sType;
 void* pNext;
 VkVideoEncodeH265RateControlFlagsKHR preferredRateControlFlags;
 uint32_t preferredGopFrameCount;
 uint32_t preferredIdrPeriod;
 uint32_t preferredConsecutiveBFrameCount;
 uint32_t preferredSubLayerCount;
 VkVideoEncodeH265QpKHR preferredConstantQp;
 uint32_t preferredMaxL0ReferenceCount;
 uint32_t preferredMaxL1ReferenceCount;
} VkVideoEncodeH265QualityLevelPropertiesKHR;

typedef struct VkVideoEncodeH265SessionParametersAddInfoKHR {
 VkStructureType sType;
 const void* pNext;
 uint32_t stdVPSCount;
 const StdVideoH265VideoParameterSet* pStdVPSs;
 uint32_t stdSPSCount;
 const StdVideoH265SequenceParameterSet* pStdSPSs;
 uint32_t stdPPSCount;
 const StdVideoH265PictureParameterSet* pStdPPSs;
} VkVideoEncodeH265SessionParametersAddInfoKHR;

typedef struct VkVideoEncodeH265SessionParametersCreateInfoKHR {
 VkStructureType sType;
 const void* pNext;
 uint32_t maxStdVPSCount;
 uint32_t maxStdSPSCount;
 uint32_t maxStdPPSCount;
 const VkVideoEncodeH265SessionParametersAddInfoKHR* pParametersAddInfo;
} VkVideoEncodeH265SessionParametersCreateInfoKHR;

typedef struct VkVideoEncodeH265SessionParametersGetInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkBool32 writeStdVPS;
 VkBool32 writeStdSPS;
 VkBool32 writeStdPPS;
 uint32_t stdVPSId;
 uint32_t stdSPSId;
 uint32_t stdPPSId;
} VkVideoEncodeH265SessionParametersGetInfoKHR;

typedef struct VkVideoEncodeH265SessionParametersFeedbackInfoKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 hasStdVPSOverrides;
 VkBool32 hasStdSPSOverrides;
 VkBool32 hasStdPPSOverrides;
} VkVideoEncodeH265SessionParametersFeedbackInfoKHR;

typedef struct VkVideoEncodeH265NaluSliceSegmentInfoKHR {
 VkStructureType sType;
 const void* pNext;
 int32_t constantQp;
 const StdVideoEncodeH265SliceSegmentHeader* pStdSliceSegmentHeader;
} VkVideoEncodeH265NaluSliceSegmentInfoKHR;

typedef struct VkVideoEncodeH265PictureInfoKHR {
 VkStructureType sType;
 const void* pNext;
 uint32_t naluSliceSegmentEntryCount;
 const VkVideoEncodeH265NaluSliceSegmentInfoKHR* pNaluSliceSegmentEntries;
 const StdVideoEncodeH265PictureInfo* pStdPictureInfo;
} VkVideoEncodeH265PictureInfoKHR;

typedef struct VkVideoEncodeH265DpbSlotInfoKHR {
 VkStructureType sType;
 const void* pNext;
 const StdVideoEncodeH265ReferenceInfo* pStdReferenceInfo;
} VkVideoEncodeH265DpbSlotInfoKHR;

typedef struct VkVideoEncodeH265ProfileInfoKHR {
 VkStructureType sType;
 const void* pNext;
 StdVideoH265ProfileIdc stdProfileIdc;
} VkVideoEncodeH265ProfileInfoKHR;

typedef struct VkVideoEncodeH265RateControlInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkVideoEncodeH265RateControlFlagsKHR flags;
 uint32_t gopFrameCount;
 uint32_t idrPeriod;
 uint32_t consecutiveBFrameCount;
 uint32_t subLayerCount;
} VkVideoEncodeH265RateControlInfoKHR;

typedef struct VkVideoEncodeH265FrameSizeKHR {
 uint32_t frameISize;
 uint32_t framePSize;
 uint32_t frameBSize;
} VkVideoEncodeH265FrameSizeKHR;

typedef struct VkVideoEncodeH265RateControlLayerInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkBool32 useMinQp;
 VkVideoEncodeH265QpKHR minQp;
 VkBool32 useMaxQp;
 VkVideoEncodeH265QpKHR maxQp;
 VkBool32 useMaxFrameSize;
 VkVideoEncodeH265FrameSizeKHR maxFrameSize;
} VkVideoEncodeH265RateControlLayerInfoKHR;

typedef struct VkVideoEncodeH265GopRemainingFrameInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkBool32 useGopRemainingFrames;
 uint32_t gopRemainingI;
 uint32_t gopRemainingP;
 uint32_t gopRemainingB;
} VkVideoEncodeH265GopRemainingFrameInfoKHR;

// VK_KHR_video_decode_h264 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_video_decode_h264 1

#define VK_KHR_VIDEO_DECODE_H264_SPEC_VERSION 9
#define VK_KHR_VIDEO_DECODE_H264_EXTENSION_NAME "VK_KHR_video_decode_h264"

typedef enum VkVideoDecodeH264PictureLayoutFlagBitsKHR {
 VK_VIDEO_DECODE_H264_PICTURE_LAYOUT_PROGRESSIVE_KHR = 0,
 VK_VIDEO_DECODE_H264_PICTURE_LAYOUT_INTERLACED_INTERLEAVED_LINES_BIT_KHR = 0x00000001,
 VK_VIDEO_DECODE_H264_PICTURE_LAYOUT_INTERLACED_SEPARATE_PLANES_BIT_KHR = 0x00000002,
 VK_VIDEO_DECODE_H264_PICTURE_LAYOUT_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkVideoDecodeH264PictureLayoutFlagBitsKHR;
typedef VkFlags VkVideoDecodeH264PictureLayoutFlagsKHR;
typedef struct VkVideoDecodeH264ProfileInfoKHR {
 VkStructureType sType;
 const void* pNext;
 StdVideoH264ProfileIdc stdProfileIdc;
 VkVideoDecodeH264PictureLayoutFlagBitsKHR pictureLayout;
} VkVideoDecodeH264ProfileInfoKHR;

typedef struct VkVideoDecodeH264CapabilitiesKHR {
 VkStructureType sType;
 void* pNext;
 StdVideoH264LevelIdc maxLevelIdc;
 VkOffset2D fieldOffsetGranularity;
} VkVideoDecodeH264CapabilitiesKHR;

typedef struct VkVideoDecodeH264SessionParametersAddInfoKHR {
 VkStructureType sType;
 const void* pNext;
 uint32_t stdSPSCount;
 const StdVideoH264SequenceParameterSet* pStdSPSs;
 uint32_t stdPPSCount;
 const StdVideoH264PictureParameterSet* pStdPPSs;
} VkVideoDecodeH264SessionParametersAddInfoKHR;

typedef struct VkVideoDecodeH264SessionParametersCreateInfoKHR {
 VkStructureType sType;
 const void* pNext;
 uint32_t maxStdSPSCount;
 uint32_t maxStdPPSCount;
 const VkVideoDecodeH264SessionParametersAddInfoKHR* pParametersAddInfo;
} VkVideoDecodeH264SessionParametersCreateInfoKHR;

typedef struct VkVideoDecodeH264PictureInfoKHR {
 VkStructureType sType;
 const void* pNext;
 const StdVideoDecodeH264PictureInfo* pStdPictureInfo;
 uint32_t sliceCount;
 const uint32_t* pSliceOffsets;
} VkVideoDecodeH264PictureInfoKHR;

typedef struct VkVideoDecodeH264DpbSlotInfoKHR {
 VkStructureType sType;
 const void* pNext;
 const StdVideoDecodeH264ReferenceInfo* pStdReferenceInfo;
} VkVideoDecodeH264DpbSlotInfoKHR;

// VK_KHR_dynamic_rendering is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_dynamic_rendering 1
#define VK_KHR_DYNAMIC_RENDERING_SPEC_VERSION 1
#define VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME "VK_KHR_dynamic_rendering"
typedef VkRenderingFlags VkRenderingFlagsKHR;

typedef VkRenderingFlagBits VkRenderingFlagBitsKHR;

typedef VkRenderingInfo VkRenderingInfoKHR;

typedef VkRenderingAttachmentInfo VkRenderingAttachmentInfoKHR;

typedef VkPipelineRenderingCreateInfo VkPipelineRenderingCreateInfoKHR;

typedef VkPhysicalDeviceDynamicRenderingFeatures VkPhysicalDeviceDynamicRenderingFeaturesKHR;

typedef VkCommandBufferInheritanceRenderingInfo VkCommandBufferInheritanceRenderingInfoKHR;

typedef struct VkRenderingFragmentShadingRateAttachmentInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkImageView imageView;
 VkImageLayout imageLayout;
 VkExtent2D shadingRateAttachmentTexelSize;
} VkRenderingFragmentShadingRateAttachmentInfoKHR;

typedef struct VkRenderingFragmentDensityMapAttachmentInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkImageView imageView;
 VkImageLayout imageLayout;
} VkRenderingFragmentDensityMapAttachmentInfoEXT;

typedef struct VkAttachmentSampleCountInfoAMD {
 VkStructureType sType;
 const void* pNext;
 uint32_t colorAttachmentCount;
 const VkSampleCountFlagBits* pColorAttachmentSamples;
 VkSampleCountFlagBits depthStencilAttachmentSamples;
} VkAttachmentSampleCountInfoAMD;

typedef VkAttachmentSampleCountInfoAMD VkAttachmentSampleCountInfoNV;

typedef struct VkMultiviewPerViewAttributesInfoNVX {
 VkStructureType sType;
 const void* pNext;
 VkBool32 perViewAttributes;
 VkBool32 perViewAttributesPositionXOnly;
} VkMultiviewPerViewAttributesInfoNVX;

typedef void (VKAPI_PTR *PFN_vkCmdBeginRenderingKHR)(VkCommandBuffer commandBuffer, const VkRenderingInfo* pRenderingInfo);
typedef void (VKAPI_PTR *PFN_vkCmdEndRenderingKHR)(VkCommandBuffer commandBuffer);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdBeginRenderingKHR(
 VkCommandBuffer commandBuffer,
 const VkRenderingInfo* pRenderingInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdEndRenderingKHR(
 VkCommandBuffer commandBuffer);
#endif

// VK_KHR_multiview is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_multiview 1
#define VK_KHR_MULTIVIEW_SPEC_VERSION 1
#define VK_KHR_MULTIVIEW_EXTENSION_NAME "VK_KHR_multiview"
typedef VkRenderPassMultiviewCreateInfo VkRenderPassMultiviewCreateInfoKHR;

typedef VkPhysicalDeviceMultiviewFeatures VkPhysicalDeviceMultiviewFeaturesKHR;

typedef VkPhysicalDeviceMultiviewProperties VkPhysicalDeviceMultiviewPropertiesKHR;

// VK_KHR_get_physical_device_properties2 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_get_physical_device_properties2 1
#define VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_SPEC_VERSION 2
#define VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME "VK_KHR_get_physical_device_properties2"
typedef VkPhysicalDeviceFeatures2 VkPhysicalDeviceFeatures2KHR;

typedef VkPhysicalDeviceProperties2 VkPhysicalDeviceProperties2KHR;

typedef VkFormatProperties2 VkFormatProperties2KHR;

typedef VkImageFormatProperties2 VkImageFormatProperties2KHR;

typedef VkPhysicalDeviceImageFormatInfo2 VkPhysicalDeviceImageFormatInfo2KHR;

typedef VkQueueFamilyProperties2 VkQueueFamilyProperties2KHR;

typedef VkPhysicalDeviceMemoryProperties2 VkPhysicalDeviceMemoryProperties2KHR;

typedef VkSparseImageFormatProperties2 VkSparseImageFormatProperties2KHR;

typedef VkPhysicalDeviceSparseImageFormatInfo2 VkPhysicalDeviceSparseImageFormatInfo2KHR;

typedef void (VKAPI_PTR *PFN_vkGetPhysicalDeviceFeatures2KHR)(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2* pFeatures);
typedef void (VKAPI_PTR *PFN_vkGetPhysicalDeviceProperties2KHR)(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2* pProperties);
typedef void (VKAPI_PTR *PFN_vkGetPhysicalDeviceFormatProperties2KHR)(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2* pFormatProperties);
typedef VkResult (VKAPI_PTR *PFN_vkGetPhysicalDeviceImageFormatProperties2KHR)(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo, VkImageFormatProperties2* pImageFormatProperties);
typedef void (VKAPI_PTR *PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR)(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2* pQueueFamilyProperties);
typedef void (VKAPI_PTR *PFN_vkGetPhysicalDeviceMemoryProperties2KHR)(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2* pMemoryProperties);
typedef void (VKAPI_PTR *PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR)(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo, uint32_t* pPropertyCount, VkSparseImageFormatProperties2* pProperties);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceFeatures2KHR(
 VkPhysicalDevice physicalDevice,
 VkPhysicalDeviceFeatures2* pFeatures);

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceProperties2KHR(
 VkPhysicalDevice physicalDevice,
 VkPhysicalDeviceProperties2* pProperties);

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceFormatProperties2KHR(
 VkPhysicalDevice physicalDevice,
 VkFormat format,
 VkFormatProperties2* pFormatProperties);

VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceImageFormatProperties2KHR(
 VkPhysicalDevice physicalDevice,
 const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo,
 VkImageFormatProperties2* pImageFormatProperties);

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceQueueFamilyProperties2KHR(
 VkPhysicalDevice physicalDevice,
 uint32_t* pQueueFamilyPropertyCount,
 VkQueueFamilyProperties2* pQueueFamilyProperties);

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceMemoryProperties2KHR(
 VkPhysicalDevice physicalDevice,
 VkPhysicalDeviceMemoryProperties2* pMemoryProperties);

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceSparseImageFormatProperties2KHR(
 VkPhysicalDevice physicalDevice,
 const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo,
 uint32_t* pPropertyCount,
 VkSparseImageFormatProperties2* pProperties);
#endif

// VK_KHR_device_group is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_device_group 1
#define VK_KHR_DEVICE_GROUP_SPEC_VERSION 4
#define VK_KHR_DEVICE_GROUP_EXTENSION_NAME "VK_KHR_device_group"
typedef VkPeerMemoryFeatureFlags VkPeerMemoryFeatureFlagsKHR;

typedef VkPeerMemoryFeatureFlagBits VkPeerMemoryFeatureFlagBitsKHR;

typedef VkMemoryAllocateFlags VkMemoryAllocateFlagsKHR;

typedef VkMemoryAllocateFlagBits VkMemoryAllocateFlagBitsKHR;

typedef VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfoKHR;

typedef VkDeviceGroupRenderPassBeginInfo VkDeviceGroupRenderPassBeginInfoKHR;

typedef VkDeviceGroupCommandBufferBeginInfo VkDeviceGroupCommandBufferBeginInfoKHR;

typedef VkDeviceGroupSubmitInfo VkDeviceGroupSubmitInfoKHR;

typedef VkDeviceGroupBindSparseInfo VkDeviceGroupBindSparseInfoKHR;

typedef VkBindBufferMemoryDeviceGroupInfo VkBindBufferMemoryDeviceGroupInfoKHR;

typedef VkBindImageMemoryDeviceGroupInfo VkBindImageMemoryDeviceGroupInfoKHR;

typedef void (VKAPI_PTR *PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR)(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures);
typedef void (VKAPI_PTR *PFN_vkCmdSetDeviceMaskKHR)(VkCommandBuffer commandBuffer, uint32_t deviceMask);
typedef void (VKAPI_PTR *PFN_vkCmdDispatchBaseKHR)(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkGetDeviceGroupPeerMemoryFeaturesKHR(
 VkDevice device,
 uint32_t heapIndex,
 uint32_t localDeviceIndex,
 uint32_t remoteDeviceIndex,
 VkPeerMemoryFeatureFlags* pPeerMemoryFeatures);

VKAPI_ATTR void VKAPI_CALL vkCmdSetDeviceMaskKHR(
 VkCommandBuffer commandBuffer,
 uint32_t deviceMask);

VKAPI_ATTR void VKAPI_CALL vkCmdDispatchBaseKHR(
 VkCommandBuffer commandBuffer,
 uint32_t baseGroupX,
 uint32_t baseGroupY,
 uint32_t baseGroupZ,
 uint32_t groupCountX,
 uint32_t groupCountY,
 uint32_t groupCountZ);
#endif

// VK_KHR_shader_draw_parameters is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_shader_draw_parameters 1
#define VK_KHR_SHADER_DRAW_PARAMETERS_SPEC_VERSION 1
#define VK_KHR_SHADER_DRAW_PARAMETERS_EXTENSION_NAME "VK_KHR_shader_draw_parameters"

// VK_KHR_maintenance1 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_maintenance1 1
#define VK_KHR_MAINTENANCE_1_SPEC_VERSION 2
#define VK_KHR_MAINTENANCE_1_EXTENSION_NAME "VK_KHR_maintenance1"
#define VK_KHR_MAINTENANCE1_SPEC_VERSION VK_KHR_MAINTENANCE_1_SPEC_VERSION
#define VK_KHR_MAINTENANCE1_EXTENSION_NAME VK_KHR_MAINTENANCE_1_EXTENSION_NAME
typedef VkCommandPoolTrimFlags VkCommandPoolTrimFlagsKHR;

typedef void (VKAPI_PTR *PFN_vkTrimCommandPoolKHR)(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkTrimCommandPoolKHR(
 VkDevice device,
 VkCommandPool commandPool,
 VkCommandPoolTrimFlags flags);
#endif

// VK_KHR_device_group_creation is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_device_group_creation 1
#define VK_KHR_DEVICE_GROUP_CREATION_SPEC_VERSION 1
#define VK_KHR_DEVICE_GROUP_CREATION_EXTENSION_NAME "VK_KHR_device_group_creation"
#define VK_MAX_DEVICE_GROUP_SIZE_KHR VK_MAX_DEVICE_GROUP_SIZE
typedef VkPhysicalDeviceGroupProperties VkPhysicalDeviceGroupPropertiesKHR;

typedef VkDeviceGroupDeviceCreateInfo VkDeviceGroupDeviceCreateInfoKHR;

typedef VkResult (VKAPI_PTR *PFN_vkEnumeratePhysicalDeviceGroupsKHR)(VkInstance instance, uint32_t* pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkEnumeratePhysicalDeviceGroupsKHR(
 VkInstance instance,
 uint32_t* pPhysicalDeviceGroupCount,
 VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties);
#endif

// VK_KHR_external_memory_capabilities is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_external_memory_capabilities 1
#define VK_KHR_EXTERNAL_MEMORY_CAPABILITIES_SPEC_VERSION 1
#define VK_KHR_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME "VK_KHR_external_memory_capabilities"
#define VK_LUID_SIZE_KHR VK_LUID_SIZE
typedef VkExternalMemoryHandleTypeFlags VkExternalMemoryHandleTypeFlagsKHR;

typedef VkExternalMemoryHandleTypeFlagBits VkExternalMemoryHandleTypeFlagBitsKHR;

typedef VkExternalMemoryFeatureFlags VkExternalMemoryFeatureFlagsKHR;

typedef VkExternalMemoryFeatureFlagBits VkExternalMemoryFeatureFlagBitsKHR;

typedef VkExternalMemoryProperties VkExternalMemoryPropertiesKHR;

typedef VkPhysicalDeviceExternalImageFormatInfo VkPhysicalDeviceExternalImageFormatInfoKHR;

typedef VkExternalImageFormatProperties VkExternalImageFormatPropertiesKHR;

typedef VkPhysicalDeviceExternalBufferInfo VkPhysicalDeviceExternalBufferInfoKHR;

typedef VkExternalBufferProperties VkExternalBufferPropertiesKHR;

typedef VkPhysicalDeviceIDProperties VkPhysicalDeviceIDPropertiesKHR;

typedef void (VKAPI_PTR *PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR)(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo, VkExternalBufferProperties* pExternalBufferProperties);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalBufferPropertiesKHR(
 VkPhysicalDevice physicalDevice,
 const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo,
 VkExternalBufferProperties* pExternalBufferProperties);
#endif

// VK_KHR_external_memory is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_external_memory 1
#define VK_KHR_EXTERNAL_MEMORY_SPEC_VERSION 1
#define VK_KHR_EXTERNAL_MEMORY_EXTENSION_NAME "VK_KHR_external_memory"
#define VK_QUEUE_FAMILY_EXTERNAL_KHR VK_QUEUE_FAMILY_EXTERNAL
typedef VkExternalMemoryImageCreateInfo VkExternalMemoryImageCreateInfoKHR;

typedef VkExternalMemoryBufferCreateInfo VkExternalMemoryBufferCreateInfoKHR;

typedef VkExportMemoryAllocateInfo VkExportMemoryAllocateInfoKHR;

// VK_KHR_external_memory_fd is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_external_memory_fd 1
#define VK_KHR_EXTERNAL_MEMORY_FD_SPEC_VERSION 1
#define VK_KHR_EXTERNAL_MEMORY_FD_EXTENSION_NAME "VK_KHR_external_memory_fd"
typedef struct VkImportMemoryFdInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkExternalMemoryHandleTypeFlagBits handleType;
 int fd;
} VkImportMemoryFdInfoKHR;

typedef struct VkMemoryFdPropertiesKHR {
 VkStructureType sType;
 void* pNext;
 uint32_t memoryTypeBits;
} VkMemoryFdPropertiesKHR;

typedef struct VkMemoryGetFdInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkDeviceMemory memory;
 VkExternalMemoryHandleTypeFlagBits handleType;
} VkMemoryGetFdInfoKHR;

typedef VkResult (VKAPI_PTR *PFN_vkGetMemoryFdKHR)(VkDevice device, const VkMemoryGetFdInfoKHR* pGetFdInfo, int* pFd);
typedef VkResult (VKAPI_PTR *PFN_vkGetMemoryFdPropertiesKHR)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, int fd, VkMemoryFdPropertiesKHR* pMemoryFdProperties);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryFdKHR(
 VkDevice device,
 const VkMemoryGetFdInfoKHR* pGetFdInfo,
 int* pFd);

VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryFdPropertiesKHR(
 VkDevice device,
 VkExternalMemoryHandleTypeFlagBits handleType,
 int fd,
 VkMemoryFdPropertiesKHR* pMemoryFdProperties);
#endif

// VK_KHR_external_semaphore_capabilities is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_external_semaphore_capabilities 1
#define VK_KHR_EXTERNAL_SEMAPHORE_CAPABILITIES_SPEC_VERSION 1
#define VK_KHR_EXTERNAL_SEMAPHORE_CAPABILITIES_EXTENSION_NAME "VK_KHR_external_semaphore_capabilities"
typedef VkExternalSemaphoreHandleTypeFlags VkExternalSemaphoreHandleTypeFlagsKHR;

typedef VkExternalSemaphoreHandleTypeFlagBits VkExternalSemaphoreHandleTypeFlagBitsKHR;

typedef VkExternalSemaphoreFeatureFlags VkExternalSemaphoreFeatureFlagsKHR;

typedef VkExternalSemaphoreFeatureFlagBits VkExternalSemaphoreFeatureFlagBitsKHR;

typedef VkPhysicalDeviceExternalSemaphoreInfo VkPhysicalDeviceExternalSemaphoreInfoKHR;

typedef VkExternalSemaphoreProperties VkExternalSemaphorePropertiesKHR;

typedef void (VKAPI_PTR *PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR)(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo, VkExternalSemaphoreProperties* pExternalSemaphoreProperties);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(
 VkPhysicalDevice physicalDevice,
 const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo,
 VkExternalSemaphoreProperties* pExternalSemaphoreProperties);
#endif

// VK_KHR_external_semaphore is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_external_semaphore 1
#define VK_KHR_EXTERNAL_SEMAPHORE_SPEC_VERSION 1
#define VK_KHR_EXTERNAL_SEMAPHORE_EXTENSION_NAME "VK_KHR_external_semaphore"
typedef VkSemaphoreImportFlags VkSemaphoreImportFlagsKHR;

typedef VkSemaphoreImportFlagBits VkSemaphoreImportFlagBitsKHR;

typedef VkExportSemaphoreCreateInfo VkExportSemaphoreCreateInfoKHR;

// VK_KHR_external_semaphore_fd is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_external_semaphore_fd 1
#define VK_KHR_EXTERNAL_SEMAPHORE_FD_SPEC_VERSION 1
#define VK_KHR_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME "VK_KHR_external_semaphore_fd"
typedef struct VkImportSemaphoreFdInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkSemaphore semaphore;
 VkSemaphoreImportFlags flags;
 VkExternalSemaphoreHandleTypeFlagBits handleType;
 int fd;
} VkImportSemaphoreFdInfoKHR;

typedef struct VkSemaphoreGetFdInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkSemaphore semaphore;
 VkExternalSemaphoreHandleTypeFlagBits handleType;
} VkSemaphoreGetFdInfoKHR;

typedef VkResult (VKAPI_PTR *PFN_vkImportSemaphoreFdKHR)(VkDevice device, const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo);
typedef VkResult (VKAPI_PTR *PFN_vkGetSemaphoreFdKHR)(VkDevice device, const VkSemaphoreGetFdInfoKHR* pGetFdInfo, int* pFd);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkImportSemaphoreFdKHR(
 VkDevice device,
 const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreFdKHR(
 VkDevice device,
 const VkSemaphoreGetFdInfoKHR* pGetFdInfo,
 int* pFd);
#endif

// VK_KHR_push_descriptor is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_push_descriptor 1
#define VK_KHR_PUSH_DESCRIPTOR_SPEC_VERSION 2
#define VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME "VK_KHR_push_descriptor"
typedef struct VkPhysicalDevicePushDescriptorPropertiesKHR {
 VkStructureType sType;
 void* pNext;
 uint32_t maxPushDescriptors;
} VkPhysicalDevicePushDescriptorPropertiesKHR;

typedef void (VKAPI_PTR *PFN_vkCmdPushDescriptorSetKHR)(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites);
typedef void (VKAPI_PTR *PFN_vkCmdPushDescriptorSetWithTemplateKHR)(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdPushDescriptorSetKHR(
 VkCommandBuffer commandBuffer,
 VkPipelineBindPoint pipelineBindPoint,
 VkPipelineLayout layout,
 uint32_t set,
 uint32_t descriptorWriteCount,
 const VkWriteDescriptorSet* pDescriptorWrites);

VKAPI_ATTR void VKAPI_CALL vkCmdPushDescriptorSetWithTemplateKHR(
 VkCommandBuffer commandBuffer,
 VkDescriptorUpdateTemplate descriptorUpdateTemplate,
 VkPipelineLayout layout,
 uint32_t set,
 const void* pData);
#endif

// VK_KHR_shader_float16_int8 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_shader_float16_int8 1
#define VK_KHR_SHADER_FLOAT16_INT8_SPEC_VERSION 1
#define VK_KHR_SHADER_FLOAT16_INT8_EXTENSION_NAME "VK_KHR_shader_float16_int8"
typedef VkPhysicalDeviceShaderFloat16Int8Features VkPhysicalDeviceShaderFloat16Int8FeaturesKHR;

typedef VkPhysicalDeviceShaderFloat16Int8Features VkPhysicalDeviceFloat16Int8FeaturesKHR;

// VK_KHR_16bit_storage is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_16bit_storage 1
#define VK_KHR_16BIT_STORAGE_SPEC_VERSION 1
#define VK_KHR_16BIT_STORAGE_EXTENSION_NAME "VK_KHR_16bit_storage"
typedef VkPhysicalDevice16BitStorageFeatures VkPhysicalDevice16BitStorageFeaturesKHR;

// VK_KHR_incremental_present is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_incremental_present 1
#define VK_KHR_INCREMENTAL_PRESENT_SPEC_VERSION 2
#define VK_KHR_INCREMENTAL_PRESENT_EXTENSION_NAME "VK_KHR_incremental_present"
typedef struct VkRectLayerKHR {
 VkOffset2D offset;
 VkExtent2D extent;
 uint32_t layer;
} VkRectLayerKHR;

typedef struct VkPresentRegionKHR {
 uint32_t rectangleCount;
 const VkRectLayerKHR* pRectangles;
} VkPresentRegionKHR;

typedef struct VkPresentRegionsKHR {
 VkStructureType sType;
 const void* pNext;
 uint32_t swapchainCount;
 const VkPresentRegionKHR* pRegions;
} VkPresentRegionsKHR;

// VK_KHR_descriptor_update_template is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_descriptor_update_template 1
typedef VkDescriptorUpdateTemplate VkDescriptorUpdateTemplateKHR;

#define VK_KHR_DESCRIPTOR_UPDATE_TEMPLATE_SPEC_VERSION 1
#define VK_KHR_DESCRIPTOR_UPDATE_TEMPLATE_EXTENSION_NAME "VK_KHR_descriptor_update_template"
typedef VkDescriptorUpdateTemplateType VkDescriptorUpdateTemplateTypeKHR;

typedef VkDescriptorUpdateTemplateCreateFlags VkDescriptorUpdateTemplateCreateFlagsKHR;

typedef VkDescriptorUpdateTemplateEntry VkDescriptorUpdateTemplateEntryKHR;

typedef VkDescriptorUpdateTemplateCreateInfo VkDescriptorUpdateTemplateCreateInfoKHR;

typedef VkResult (VKAPI_PTR *PFN_vkCreateDescriptorUpdateTemplateKHR)(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate);
typedef void (VKAPI_PTR *PFN_vkDestroyDescriptorUpdateTemplateKHR)(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator);
typedef void (VKAPI_PTR *PFN_vkUpdateDescriptorSetWithTemplateKHR)(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDescriptorUpdateTemplateKHR(
 VkDevice device,
 const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo,
 const VkAllocationCallbacks* pAllocator,
 VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate);

VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorUpdateTemplateKHR(
 VkDevice device,
 VkDescriptorUpdateTemplate descriptorUpdateTemplate,
 const VkAllocationCallbacks* pAllocator);

VKAPI_ATTR void VKAPI_CALL vkUpdateDescriptorSetWithTemplateKHR(
 VkDevice device,
 VkDescriptorSet descriptorSet,
 VkDescriptorUpdateTemplate descriptorUpdateTemplate,
 const void* pData);
#endif

// VK_KHR_imageless_framebuffer is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_imageless_framebuffer 1
#define VK_KHR_IMAGELESS_FRAMEBUFFER_SPEC_VERSION 1
#define VK_KHR_IMAGELESS_FRAMEBUFFER_EXTENSION_NAME "VK_KHR_imageless_framebuffer"
typedef VkPhysicalDeviceImagelessFramebufferFeatures VkPhysicalDeviceImagelessFramebufferFeaturesKHR;

typedef VkFramebufferAttachmentsCreateInfo VkFramebufferAttachmentsCreateInfoKHR;

typedef VkFramebufferAttachmentImageInfo VkFramebufferAttachmentImageInfoKHR;

typedef VkRenderPassAttachmentBeginInfo VkRenderPassAttachmentBeginInfoKHR;

// VK_KHR_create_renderpass2 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_create_renderpass2 1
#define VK_KHR_CREATE_RENDERPASS_2_SPEC_VERSION 1
#define VK_KHR_CREATE_RENDERPASS_2_EXTENSION_NAME "VK_KHR_create_renderpass2"
typedef VkRenderPassCreateInfo2 VkRenderPassCreateInfo2KHR;

typedef VkAttachmentDescription2 VkAttachmentDescription2KHR;

typedef VkAttachmentReference2 VkAttachmentReference2KHR;

typedef VkSubpassDescription2 VkSubpassDescription2KHR;

typedef VkSubpassDependency2 VkSubpassDependency2KHR;

typedef VkSubpassBeginInfo VkSubpassBeginInfoKHR;

typedef VkSubpassEndInfo VkSubpassEndInfoKHR;

typedef VkResult (VKAPI_PTR *PFN_vkCreateRenderPass2KHR)(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass);
typedef void (VKAPI_PTR *PFN_vkCmdBeginRenderPass2KHR)(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, const VkSubpassBeginInfo* pSubpassBeginInfo);
typedef void (VKAPI_PTR *PFN_vkCmdNextSubpass2KHR)(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo* pSubpassBeginInfo, const VkSubpassEndInfo* pSubpassEndInfo);
typedef void (VKAPI_PTR *PFN_vkCmdEndRenderPass2KHR)(VkCommandBuffer commandBuffer, const VkSubpassEndInfo* pSubpassEndInfo);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateRenderPass2KHR(
 VkDevice device,
 const VkRenderPassCreateInfo2* pCreateInfo,
 const VkAllocationCallbacks* pAllocator,
 VkRenderPass* pRenderPass);

VKAPI_ATTR void VKAPI_CALL vkCmdBeginRenderPass2KHR(
 VkCommandBuffer commandBuffer,
 const VkRenderPassBeginInfo* pRenderPassBegin,
 const VkSubpassBeginInfo* pSubpassBeginInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdNextSubpass2KHR(
 VkCommandBuffer commandBuffer,
 const VkSubpassBeginInfo* pSubpassBeginInfo,
 const VkSubpassEndInfo* pSubpassEndInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdEndRenderPass2KHR(
 VkCommandBuffer commandBuffer,
 const VkSubpassEndInfo* pSubpassEndInfo);
#endif

// VK_KHR_shared_presentable_image is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_shared_presentable_image 1
#define VK_KHR_SHARED_PRESENTABLE_IMAGE_SPEC_VERSION 1
#define VK_KHR_SHARED_PRESENTABLE_IMAGE_EXTENSION_NAME "VK_KHR_shared_presentable_image"
typedef struct VkSharedPresentSurfaceCapabilitiesKHR {
 VkStructureType sType;
 void* pNext;
 VkImageUsageFlags sharedPresentSupportedUsageFlags;
} VkSharedPresentSurfaceCapabilitiesKHR;

typedef VkResult (VKAPI_PTR *PFN_vkGetSwapchainStatusKHR)(VkDevice device, VkSwapchainKHR swapchain);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetSwapchainStatusKHR(
 VkDevice device,
 VkSwapchainKHR swapchain);
#endif

// VK_KHR_external_fence_capabilities is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_external_fence_capabilities 1
#define VK_KHR_EXTERNAL_FENCE_CAPABILITIES_SPEC_VERSION 1
#define VK_KHR_EXTERNAL_FENCE_CAPABILITIES_EXTENSION_NAME "VK_KHR_external_fence_capabilities"
typedef VkExternalFenceHandleTypeFlags VkExternalFenceHandleTypeFlagsKHR;

typedef VkExternalFenceHandleTypeFlagBits VkExternalFenceHandleTypeFlagBitsKHR;

typedef VkExternalFenceFeatureFlags VkExternalFenceFeatureFlagsKHR;

typedef VkExternalFenceFeatureFlagBits VkExternalFenceFeatureFlagBitsKHR;

typedef VkPhysicalDeviceExternalFenceInfo VkPhysicalDeviceExternalFenceInfoKHR;

typedef VkExternalFenceProperties VkExternalFencePropertiesKHR;

typedef void (VKAPI_PTR *PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR)(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo, VkExternalFenceProperties* pExternalFenceProperties);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalFencePropertiesKHR(
 VkPhysicalDevice physicalDevice,
 const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo,
 VkExternalFenceProperties* pExternalFenceProperties);
#endif

// VK_KHR_external_fence is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_external_fence 1
#define VK_KHR_EXTERNAL_FENCE_SPEC_VERSION 1
#define VK_KHR_EXTERNAL_FENCE_EXTENSION_NAME "VK_KHR_external_fence"
typedef VkFenceImportFlags VkFenceImportFlagsKHR;

typedef VkFenceImportFlagBits VkFenceImportFlagBitsKHR;

typedef VkExportFenceCreateInfo VkExportFenceCreateInfoKHR;

// VK_KHR_external_fence_fd is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_external_fence_fd 1
#define VK_KHR_EXTERNAL_FENCE_FD_SPEC_VERSION 1
#define VK_KHR_EXTERNAL_FENCE_FD_EXTENSION_NAME "VK_KHR_external_fence_fd"
typedef struct VkImportFenceFdInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkFence fence;
 VkFenceImportFlags flags;
 VkExternalFenceHandleTypeFlagBits handleType;
 int fd;
} VkImportFenceFdInfoKHR;

typedef struct VkFenceGetFdInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkFence fence;
 VkExternalFenceHandleTypeFlagBits handleType;
} VkFenceGetFdInfoKHR;

typedef VkResult (VKAPI_PTR *PFN_vkImportFenceFdKHR)(VkDevice device, const VkImportFenceFdInfoKHR* pImportFenceFdInfo);
typedef VkResult (VKAPI_PTR *PFN_vkGetFenceFdKHR)(VkDevice device, const VkFenceGetFdInfoKHR* pGetFdInfo, int* pFd);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkImportFenceFdKHR(
 VkDevice device,
 const VkImportFenceFdInfoKHR* pImportFenceFdInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkGetFenceFdKHR(
 VkDevice device,
 const VkFenceGetFdInfoKHR* pGetFdInfo,
 int* pFd);
#endif

// VK_KHR_performance_query is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_performance_query 1
#define VK_KHR_PERFORMANCE_QUERY_SPEC_VERSION 1
#define VK_KHR_PERFORMANCE_QUERY_EXTENSION_NAME "VK_KHR_performance_query"

typedef enum VkPerformanceCounterUnitKHR {
 VK_PERFORMANCE_COUNTER_UNIT_GENERIC_KHR = 0,
 VK_PERFORMANCE_COUNTER_UNIT_PERCENTAGE_KHR = 1,
 VK_PERFORMANCE_COUNTER_UNIT_NANOSECONDS_KHR = 2,
 VK_PERFORMANCE_COUNTER_UNIT_BYTES_KHR = 3,
 VK_PERFORMANCE_COUNTER_UNIT_BYTES_PER_SECOND_KHR = 4,
 VK_PERFORMANCE_COUNTER_UNIT_KELVIN_KHR = 5,
 VK_PERFORMANCE_COUNTER_UNIT_WATTS_KHR = 6,
 VK_PERFORMANCE_COUNTER_UNIT_VOLTS_KHR = 7,
 VK_PERFORMANCE_COUNTER_UNIT_AMPS_KHR = 8,
 VK_PERFORMANCE_COUNTER_UNIT_HERTZ_KHR = 9,
 VK_PERFORMANCE_COUNTER_UNIT_CYCLES_KHR = 10,
 VK_PERFORMANCE_COUNTER_UNIT_MAX_ENUM_KHR = 0x7FFFFFFF
} VkPerformanceCounterUnitKHR;

typedef enum VkPerformanceCounterScopeKHR {
 VK_PERFORMANCE_COUNTER_SCOPE_COMMAND_BUFFER_KHR = 0,
 VK_PERFORMANCE_COUNTER_SCOPE_RENDER_PASS_KHR = 1,
 VK_PERFORMANCE_COUNTER_SCOPE_COMMAND_KHR = 2,
 VK_QUERY_SCOPE_COMMAND_BUFFER_KHR = VK_PERFORMANCE_COUNTER_SCOPE_COMMAND_BUFFER_KHR,
 VK_QUERY_SCOPE_RENDER_PASS_KHR = VK_PERFORMANCE_COUNTER_SCOPE_RENDER_PASS_KHR,
 VK_QUERY_SCOPE_COMMAND_KHR = VK_PERFORMANCE_COUNTER_SCOPE_COMMAND_KHR,
 VK_PERFORMANCE_COUNTER_SCOPE_MAX_ENUM_KHR = 0x7FFFFFFF
} VkPerformanceCounterScopeKHR;

typedef enum VkPerformanceCounterStorageKHR {
 VK_PERFORMANCE_COUNTER_STORAGE_INT32_KHR = 0,
 VK_PERFORMANCE_COUNTER_STORAGE_INT64_KHR = 1,
 VK_PERFORMANCE_COUNTER_STORAGE_UINT32_KHR = 2,
 VK_PERFORMANCE_COUNTER_STORAGE_UINT64_KHR = 3,
 VK_PERFORMANCE_COUNTER_STORAGE_FLOAT32_KHR = 4,
 VK_PERFORMANCE_COUNTER_STORAGE_FLOAT64_KHR = 5,
 VK_PERFORMANCE_COUNTER_STORAGE_MAX_ENUM_KHR = 0x7FFFFFFF
} VkPerformanceCounterStorageKHR;

typedef enum VkPerformanceCounterDescriptionFlagBitsKHR {
 VK_PERFORMANCE_COUNTER_DESCRIPTION_PERFORMANCE_IMPACTING_BIT_KHR = 0x00000001,
 VK_PERFORMANCE_COUNTER_DESCRIPTION_CONCURRENTLY_IMPACTED_BIT_KHR = 0x00000002,
 VK_PERFORMANCE_COUNTER_DESCRIPTION_PERFORMANCE_IMPACTING_KHR = VK_PERFORMANCE_COUNTER_DESCRIPTION_PERFORMANCE_IMPACTING_BIT_KHR,
 VK_PERFORMANCE_COUNTER_DESCRIPTION_CONCURRENTLY_IMPACTED_KHR = VK_PERFORMANCE_COUNTER_DESCRIPTION_CONCURRENTLY_IMPACTED_BIT_KHR,
 VK_PERFORMANCE_COUNTER_DESCRIPTION_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkPerformanceCounterDescriptionFlagBitsKHR;
typedef VkFlags VkPerformanceCounterDescriptionFlagsKHR;

typedef enum VkAcquireProfilingLockFlagBitsKHR {
 VK_ACQUIRE_PROFILING_LOCK_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkAcquireProfilingLockFlagBitsKHR;
typedef VkFlags VkAcquireProfilingLockFlagsKHR;
typedef struct VkPhysicalDevicePerformanceQueryFeaturesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 performanceCounterQueryPools;
 VkBool32 performanceCounterMultipleQueryPools;
} VkPhysicalDevicePerformanceQueryFeaturesKHR;

typedef struct VkPhysicalDevicePerformanceQueryPropertiesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 allowCommandBufferQueryCopies;
} VkPhysicalDevicePerformanceQueryPropertiesKHR;

typedef struct VkPerformanceCounterKHR {
 VkStructureType sType;
 void* pNext;
 VkPerformanceCounterUnitKHR unit;
 VkPerformanceCounterScopeKHR scope;
 VkPerformanceCounterStorageKHR storage;
 uint8_t uuid[VK_UUID_SIZE];
} VkPerformanceCounterKHR;

typedef struct VkPerformanceCounterDescriptionKHR {
 VkStructureType sType;
 void* pNext;
 VkPerformanceCounterDescriptionFlagsKHR flags;
 char name[VK_MAX_DESCRIPTION_SIZE];
 char category[VK_MAX_DESCRIPTION_SIZE];
 char description[VK_MAX_DESCRIPTION_SIZE];
} VkPerformanceCounterDescriptionKHR;

typedef struct VkQueryPoolPerformanceCreateInfoKHR {
 VkStructureType sType;
 const void* pNext;
 uint32_t queueFamilyIndex;
 uint32_t counterIndexCount;
 const uint32_t* pCounterIndices;
} VkQueryPoolPerformanceCreateInfoKHR;

typedef union VkPerformanceCounterResultKHR {
 int32_t int32;
 int64_t int64;
 uint32_t uint32;
 uint64_t uint64;
 float float32;
 double float64;
} VkPerformanceCounterResultKHR;

typedef struct VkAcquireProfilingLockInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkAcquireProfilingLockFlagsKHR flags;
 uint64_t timeout;
} VkAcquireProfilingLockInfoKHR;

typedef struct VkPerformanceQuerySubmitInfoKHR {
 VkStructureType sType;
 const void* pNext;
 uint32_t counterPassIndex;
} VkPerformanceQuerySubmitInfoKHR;

typedef VkResult (VKAPI_PTR *PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, uint32_t* pCounterCount, VkPerformanceCounterKHR* pCounters, VkPerformanceCounterDescriptionKHR* pCounterDescriptions);
typedef void (VKAPI_PTR *PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR)(VkPhysicalDevice physicalDevice, const VkQueryPoolPerformanceCreateInfoKHR* pPerformanceQueryCreateInfo, uint32_t* pNumPasses);
typedef VkResult (VKAPI_PTR *PFN_vkAcquireProfilingLockKHR)(VkDevice device, const VkAcquireProfilingLockInfoKHR* pInfo);
typedef void (VKAPI_PTR *PFN_vkReleaseProfilingLockKHR)(VkDevice device);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(
 VkPhysicalDevice physicalDevice,
 uint32_t queueFamilyIndex,
 uint32_t* pCounterCount,
 VkPerformanceCounterKHR* pCounters,
 VkPerformanceCounterDescriptionKHR* pCounterDescriptions);

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(
 VkPhysicalDevice physicalDevice,
 const VkQueryPoolPerformanceCreateInfoKHR* pPerformanceQueryCreateInfo,
 uint32_t* pNumPasses);

VKAPI_ATTR VkResult VKAPI_CALL vkAcquireProfilingLockKHR(
 VkDevice device,
 const VkAcquireProfilingLockInfoKHR* pInfo);

VKAPI_ATTR void VKAPI_CALL vkReleaseProfilingLockKHR(
 VkDevice device);
#endif

// VK_KHR_maintenance2 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_maintenance2 1
#define VK_KHR_MAINTENANCE_2_SPEC_VERSION 1
#define VK_KHR_MAINTENANCE_2_EXTENSION_NAME "VK_KHR_maintenance2"
#define VK_KHR_MAINTENANCE2_SPEC_VERSION VK_KHR_MAINTENANCE_2_SPEC_VERSION
#define VK_KHR_MAINTENANCE2_EXTENSION_NAME VK_KHR_MAINTENANCE_2_EXTENSION_NAME
typedef VkPointClippingBehavior VkPointClippingBehaviorKHR;

typedef VkTessellationDomainOrigin VkTessellationDomainOriginKHR;

typedef VkPhysicalDevicePointClippingProperties VkPhysicalDevicePointClippingPropertiesKHR;

typedef VkRenderPassInputAttachmentAspectCreateInfo VkRenderPassInputAttachmentAspectCreateInfoKHR;

typedef VkInputAttachmentAspectReference VkInputAttachmentAspectReferenceKHR;

typedef VkImageViewUsageCreateInfo VkImageViewUsageCreateInfoKHR;

typedef VkPipelineTessellationDomainOriginStateCreateInfo VkPipelineTessellationDomainOriginStateCreateInfoKHR;

// VK_KHR_get_surface_capabilities2 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_get_surface_capabilities2 1
#define VK_KHR_GET_SURFACE_CAPABILITIES_2_SPEC_VERSION 1
#define VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME "VK_KHR_get_surface_capabilities2"
typedef struct VkPhysicalDeviceSurfaceInfo2KHR {
 VkStructureType sType;
 const void* pNext;
 VkSurfaceKHR surface;
} VkPhysicalDeviceSurfaceInfo2KHR;

typedef struct VkSurfaceCapabilities2KHR {
 VkStructureType sType;
 void* pNext;
 VkSurfaceCapabilitiesKHR surfaceCapabilities;
} VkSurfaceCapabilities2KHR;

typedef struct VkSurfaceFormat2KHR {
 VkStructureType sType;
 void* pNext;
 VkSurfaceFormatKHR surfaceFormat;
} VkSurfaceFormat2KHR;

typedef VkResult (VKAPI_PTR *PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR)(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkSurfaceCapabilities2KHR* pSurfaceCapabilities);
typedef VkResult (VKAPI_PTR *PFN_vkGetPhysicalDeviceSurfaceFormats2KHR)(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* pSurfaceFormatCount, VkSurfaceFormat2KHR* pSurfaceFormats);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceCapabilities2KHR(
 VkPhysicalDevice physicalDevice,
 const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo,
 VkSurfaceCapabilities2KHR* pSurfaceCapabilities);

VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceFormats2KHR(
 VkPhysicalDevice physicalDevice,
 const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo,
 uint32_t* pSurfaceFormatCount,
 VkSurfaceFormat2KHR* pSurfaceFormats);
#endif

// VK_KHR_variable_pointers is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_variable_pointers 1
#define VK_KHR_VARIABLE_POINTERS_SPEC_VERSION 1
#define VK_KHR_VARIABLE_POINTERS_EXTENSION_NAME "VK_KHR_variable_pointers"
typedef VkPhysicalDeviceVariablePointersFeatures VkPhysicalDeviceVariablePointerFeaturesKHR;

typedef VkPhysicalDeviceVariablePointersFeatures VkPhysicalDeviceVariablePointersFeaturesKHR;

// VK_KHR_get_display_properties2 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_get_display_properties2 1
#define VK_KHR_GET_DISPLAY_PROPERTIES_2_SPEC_VERSION 1
#define VK_KHR_GET_DISPLAY_PROPERTIES_2_EXTENSION_NAME "VK_KHR_get_display_properties2"
typedef struct VkDisplayProperties2KHR {
 VkStructureType sType;
 void* pNext;
 VkDisplayPropertiesKHR displayProperties;
} VkDisplayProperties2KHR;

typedef struct VkDisplayPlaneProperties2KHR {
 VkStructureType sType;
 void* pNext;
 VkDisplayPlanePropertiesKHR displayPlaneProperties;
} VkDisplayPlaneProperties2KHR;

typedef struct VkDisplayModeProperties2KHR {
 VkStructureType sType;
 void* pNext;
 VkDisplayModePropertiesKHR displayModeProperties;
} VkDisplayModeProperties2KHR;

typedef struct VkDisplayPlaneInfo2KHR {
 VkStructureType sType;
 const void* pNext;
 VkDisplayModeKHR mode;
 uint32_t planeIndex;
} VkDisplayPlaneInfo2KHR;

typedef struct VkDisplayPlaneCapabilities2KHR {
 VkStructureType sType;
 void* pNext;
 VkDisplayPlaneCapabilitiesKHR capabilities;
} VkDisplayPlaneCapabilities2KHR;

typedef VkResult (VKAPI_PTR *PFN_vkGetPhysicalDeviceDisplayProperties2KHR)(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayProperties2KHR* pProperties);
typedef VkResult (VKAPI_PTR *PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR)(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPlaneProperties2KHR* pProperties);
typedef VkResult (VKAPI_PTR *PFN_vkGetDisplayModeProperties2KHR)(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t* pPropertyCount, VkDisplayModeProperties2KHR* pProperties);
typedef VkResult (VKAPI_PTR *PFN_vkGetDisplayPlaneCapabilities2KHR)(VkPhysicalDevice physicalDevice, const VkDisplayPlaneInfo2KHR* pDisplayPlaneInfo, VkDisplayPlaneCapabilities2KHR* pCapabilities);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceDisplayProperties2KHR(
 VkPhysicalDevice physicalDevice,
 uint32_t* pPropertyCount,
 VkDisplayProperties2KHR* pProperties);

VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceDisplayPlaneProperties2KHR(
 VkPhysicalDevice physicalDevice,
 uint32_t* pPropertyCount,
 VkDisplayPlaneProperties2KHR* pProperties);

VKAPI_ATTR VkResult VKAPI_CALL vkGetDisplayModeProperties2KHR(
 VkPhysicalDevice physicalDevice,
 VkDisplayKHR display,
 uint32_t* pPropertyCount,
 VkDisplayModeProperties2KHR* pProperties);

VKAPI_ATTR VkResult VKAPI_CALL vkGetDisplayPlaneCapabilities2KHR(
 VkPhysicalDevice physicalDevice,
 const VkDisplayPlaneInfo2KHR* pDisplayPlaneInfo,
 VkDisplayPlaneCapabilities2KHR* pCapabilities);
#endif

// VK_KHR_dedicated_allocation is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_dedicated_allocation 1
#define VK_KHR_DEDICATED_ALLOCATION_SPEC_VERSION 3
#define VK_KHR_DEDICATED_ALLOCATION_EXTENSION_NAME "VK_KHR_dedicated_allocation"
typedef VkMemoryDedicatedRequirements VkMemoryDedicatedRequirementsKHR;

typedef VkMemoryDedicatedAllocateInfo VkMemoryDedicatedAllocateInfoKHR;

// VK_KHR_storage_buffer_storage_class is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_storage_buffer_storage_class 1
#define VK_KHR_STORAGE_BUFFER_STORAGE_CLASS_SPEC_VERSION 1
#define VK_KHR_STORAGE_BUFFER_STORAGE_CLASS_EXTENSION_NAME "VK_KHR_storage_buffer_storage_class"

// VK_KHR_relaxed_block_layout is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_relaxed_block_layout 1
#define VK_KHR_RELAXED_BLOCK_LAYOUT_SPEC_VERSION 1
#define VK_KHR_RELAXED_BLOCK_LAYOUT_EXTENSION_NAME "VK_KHR_relaxed_block_layout"

// VK_KHR_get_memory_requirements2 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_get_memory_requirements2 1
#define VK_KHR_GET_MEMORY_REQUIREMENTS_2_SPEC_VERSION 1
#define VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME "VK_KHR_get_memory_requirements2"
typedef VkBufferMemoryRequirementsInfo2 VkBufferMemoryRequirementsInfo2KHR;

typedef VkImageMemoryRequirementsInfo2 VkImageMemoryRequirementsInfo2KHR;

typedef VkImageSparseMemoryRequirementsInfo2 VkImageSparseMemoryRequirementsInfo2KHR;

typedef VkMemoryRequirements2 VkMemoryRequirements2KHR;

typedef VkSparseImageMemoryRequirements2 VkSparseImageMemoryRequirements2KHR;

typedef void (VKAPI_PTR *PFN_vkGetImageMemoryRequirements2KHR)(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements);
typedef void (VKAPI_PTR *PFN_vkGetBufferMemoryRequirements2KHR)(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements);
typedef void (VKAPI_PTR *PFN_vkGetImageSparseMemoryRequirements2KHR)(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkGetImageMemoryRequirements2KHR(
 VkDevice device,
 const VkImageMemoryRequirementsInfo2* pInfo,
 VkMemoryRequirements2* pMemoryRequirements);

VKAPI_ATTR void VKAPI_CALL vkGetBufferMemoryRequirements2KHR(
 VkDevice device,
 const VkBufferMemoryRequirementsInfo2* pInfo,
 VkMemoryRequirements2* pMemoryRequirements);

VKAPI_ATTR void VKAPI_CALL vkGetImageSparseMemoryRequirements2KHR(
 VkDevice device,
 const VkImageSparseMemoryRequirementsInfo2* pInfo,
 uint32_t* pSparseMemoryRequirementCount,
 VkSparseImageMemoryRequirements2* pSparseMemoryRequirements);
#endif

// VK_KHR_image_format_list is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_image_format_list 1
#define VK_KHR_IMAGE_FORMAT_LIST_SPEC_VERSION 1
#define VK_KHR_IMAGE_FORMAT_LIST_EXTENSION_NAME "VK_KHR_image_format_list"
typedef VkImageFormatListCreateInfo VkImageFormatListCreateInfoKHR;

// VK_KHR_sampler_ycbcr_conversion is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_sampler_ycbcr_conversion 1
typedef VkSamplerYcbcrConversion VkSamplerYcbcrConversionKHR;

#define VK_KHR_SAMPLER_YCBCR_CONVERSION_SPEC_VERSION 14
#define VK_KHR_SAMPLER_YCBCR_CONVERSION_EXTENSION_NAME "VK_KHR_sampler_ycbcr_conversion"
typedef VkSamplerYcbcrModelConversion VkSamplerYcbcrModelConversionKHR;

typedef VkSamplerYcbcrRange VkSamplerYcbcrRangeKHR;

typedef VkChromaLocation VkChromaLocationKHR;

typedef VkSamplerYcbcrConversionCreateInfo VkSamplerYcbcrConversionCreateInfoKHR;

typedef VkSamplerYcbcrConversionInfo VkSamplerYcbcrConversionInfoKHR;

typedef VkBindImagePlaneMemoryInfo VkBindImagePlaneMemoryInfoKHR;

typedef VkImagePlaneMemoryRequirementsInfo VkImagePlaneMemoryRequirementsInfoKHR;

typedef VkPhysicalDeviceSamplerYcbcrConversionFeatures VkPhysicalDeviceSamplerYcbcrConversionFeaturesKHR;

typedef VkSamplerYcbcrConversionImageFormatProperties VkSamplerYcbcrConversionImageFormatPropertiesKHR;

typedef VkResult (VKAPI_PTR *PFN_vkCreateSamplerYcbcrConversionKHR)(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion);
typedef void (VKAPI_PTR *PFN_vkDestroySamplerYcbcrConversionKHR)(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateSamplerYcbcrConversionKHR(
 VkDevice device,
 const VkSamplerYcbcrConversionCreateInfo* pCreateInfo,
 const VkAllocationCallbacks* pAllocator,
 VkSamplerYcbcrConversion* pYcbcrConversion);

VKAPI_ATTR void VKAPI_CALL vkDestroySamplerYcbcrConversionKHR(
 VkDevice device,
 VkSamplerYcbcrConversion ycbcrConversion,
 const VkAllocationCallbacks* pAllocator);
#endif

// VK_KHR_bind_memory2 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_bind_memory2 1
#define VK_KHR_BIND_MEMORY_2_SPEC_VERSION 1
#define VK_KHR_BIND_MEMORY_2_EXTENSION_NAME "VK_KHR_bind_memory2"
typedef VkBindBufferMemoryInfo VkBindBufferMemoryInfoKHR;

typedef VkBindImageMemoryInfo VkBindImageMemoryInfoKHR;

typedef VkResult (VKAPI_PTR *PFN_vkBindBufferMemory2KHR)(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos);
typedef VkResult (VKAPI_PTR *PFN_vkBindImageMemory2KHR)(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkBindBufferMemory2KHR(
 VkDevice device,
 uint32_t bindInfoCount,
 const VkBindBufferMemoryInfo* pBindInfos);

VKAPI_ATTR VkResult VKAPI_CALL vkBindImageMemory2KHR(
 VkDevice device,
 uint32_t bindInfoCount,
 const VkBindImageMemoryInfo* pBindInfos);
#endif

// VK_KHR_maintenance3 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_maintenance3 1
#define VK_KHR_MAINTENANCE_3_SPEC_VERSION 1
#define VK_KHR_MAINTENANCE_3_EXTENSION_NAME "VK_KHR_maintenance3"
#define VK_KHR_MAINTENANCE3_SPEC_VERSION VK_KHR_MAINTENANCE_3_SPEC_VERSION
#define VK_KHR_MAINTENANCE3_EXTENSION_NAME VK_KHR_MAINTENANCE_3_EXTENSION_NAME
typedef VkPhysicalDeviceMaintenance3Properties VkPhysicalDeviceMaintenance3PropertiesKHR;

typedef VkDescriptorSetLayoutSupport VkDescriptorSetLayoutSupportKHR;

typedef void (VKAPI_PTR *PFN_vkGetDescriptorSetLayoutSupportKHR)(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkGetDescriptorSetLayoutSupportKHR(
 VkDevice device,
 const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
 VkDescriptorSetLayoutSupport* pSupport);
#endif

// VK_KHR_draw_indirect_count is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_draw_indirect_count 1
#define VK_KHR_DRAW_INDIRECT_COUNT_SPEC_VERSION 1
#define VK_KHR_DRAW_INDIRECT_COUNT_EXTENSION_NAME "VK_KHR_draw_indirect_count"
typedef void (VKAPI_PTR *PFN_vkCmdDrawIndirectCountKHR)(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride);
typedef void (VKAPI_PTR *PFN_vkCmdDrawIndexedIndirectCountKHR)(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndirectCountKHR(
 VkCommandBuffer commandBuffer,
 VkBuffer buffer,
 VkDeviceSize offset,
 VkBuffer countBuffer,
 VkDeviceSize countBufferOffset,
 uint32_t maxDrawCount,
 uint32_t stride);

VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndexedIndirectCountKHR(
 VkCommandBuffer commandBuffer,
 VkBuffer buffer,
 VkDeviceSize offset,
 VkBuffer countBuffer,
 VkDeviceSize countBufferOffset,
 uint32_t maxDrawCount,
 uint32_t stride);
#endif

// VK_KHR_shader_subgroup_extended_types is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_shader_subgroup_extended_types 1
#define VK_KHR_SHADER_SUBGROUP_EXTENDED_TYPES_SPEC_VERSION 1
#define VK_KHR_SHADER_SUBGROUP_EXTENDED_TYPES_EXTENSION_NAME "VK_KHR_shader_subgroup_extended_types"
typedef VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures VkPhysicalDeviceShaderSubgroupExtendedTypesFeaturesKHR;

// VK_KHR_8bit_storage is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_8bit_storage 1
#define VK_KHR_8BIT_STORAGE_SPEC_VERSION 1
#define VK_KHR_8BIT_STORAGE_EXTENSION_NAME "VK_KHR_8bit_storage"
typedef VkPhysicalDevice8BitStorageFeatures VkPhysicalDevice8BitStorageFeaturesKHR;

// VK_KHR_shader_atomic_int64 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_shader_atomic_int64 1
#define VK_KHR_SHADER_ATOMIC_INT64_SPEC_VERSION 1
#define VK_KHR_SHADER_ATOMIC_INT64_EXTENSION_NAME "VK_KHR_shader_atomic_int64"
typedef VkPhysicalDeviceShaderAtomicInt64Features VkPhysicalDeviceShaderAtomicInt64FeaturesKHR;

// VK_KHR_shader_clock is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_shader_clock 1
#define VK_KHR_SHADER_CLOCK_SPEC_VERSION 1
#define VK_KHR_SHADER_CLOCK_EXTENSION_NAME "VK_KHR_shader_clock"
typedef struct VkPhysicalDeviceShaderClockFeaturesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 shaderSubgroupClock;
 VkBool32 shaderDeviceClock;
} VkPhysicalDeviceShaderClockFeaturesKHR;

// VK_KHR_video_decode_h265 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_video_decode_h265 1

#define VK_KHR_VIDEO_DECODE_H265_SPEC_VERSION 8
#define VK_KHR_VIDEO_DECODE_H265_EXTENSION_NAME "VK_KHR_video_decode_h265"
typedef struct VkVideoDecodeH265ProfileInfoKHR {
 VkStructureType sType;
 const void* pNext;
 StdVideoH265ProfileIdc stdProfileIdc;
} VkVideoDecodeH265ProfileInfoKHR;

typedef struct VkVideoDecodeH265CapabilitiesKHR {
 VkStructureType sType;
 void* pNext;
 StdVideoH265LevelIdc maxLevelIdc;
} VkVideoDecodeH265CapabilitiesKHR;

typedef struct VkVideoDecodeH265SessionParametersAddInfoKHR {
 VkStructureType sType;
 const void* pNext;
 uint32_t stdVPSCount;
 const StdVideoH265VideoParameterSet* pStdVPSs;
 uint32_t stdSPSCount;
 const StdVideoH265SequenceParameterSet* pStdSPSs;
 uint32_t stdPPSCount;
 const StdVideoH265PictureParameterSet* pStdPPSs;
} VkVideoDecodeH265SessionParametersAddInfoKHR;

typedef struct VkVideoDecodeH265SessionParametersCreateInfoKHR {
 VkStructureType sType;
 const void* pNext;
 uint32_t maxStdVPSCount;
 uint32_t maxStdSPSCount;
 uint32_t maxStdPPSCount;
 const VkVideoDecodeH265SessionParametersAddInfoKHR* pParametersAddInfo;
} VkVideoDecodeH265SessionParametersCreateInfoKHR;

typedef struct VkVideoDecodeH265PictureInfoKHR {
 VkStructureType sType;
 const void* pNext;
 const StdVideoDecodeH265PictureInfo* pStdPictureInfo;
 uint32_t sliceSegmentCount;
 const uint32_t* pSliceSegmentOffsets;
} VkVideoDecodeH265PictureInfoKHR;

typedef struct VkVideoDecodeH265DpbSlotInfoKHR {
 VkStructureType sType;
 const void* pNext;
 const StdVideoDecodeH265ReferenceInfo* pStdReferenceInfo;
} VkVideoDecodeH265DpbSlotInfoKHR;

// VK_KHR_global_priority is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_global_priority 1
#define VK_MAX_GLOBAL_PRIORITY_SIZE_KHR 16U
#define VK_KHR_GLOBAL_PRIORITY_SPEC_VERSION 1
#define VK_KHR_GLOBAL_PRIORITY_EXTENSION_NAME "VK_KHR_global_priority"

typedef enum VkQueueGlobalPriorityKHR {
 VK_QUEUE_GLOBAL_PRIORITY_LOW_KHR = 128,
 VK_QUEUE_GLOBAL_PRIORITY_MEDIUM_KHR = 256,
 VK_QUEUE_GLOBAL_PRIORITY_HIGH_KHR = 512,
 VK_QUEUE_GLOBAL_PRIORITY_REALTIME_KHR = 1024,
 VK_QUEUE_GLOBAL_PRIORITY_LOW_EXT = VK_QUEUE_GLOBAL_PRIORITY_LOW_KHR,
 VK_QUEUE_GLOBAL_PRIORITY_MEDIUM_EXT = VK_QUEUE_GLOBAL_PRIORITY_MEDIUM_KHR,
 VK_QUEUE_GLOBAL_PRIORITY_HIGH_EXT = VK_QUEUE_GLOBAL_PRIORITY_HIGH_KHR,
 VK_QUEUE_GLOBAL_PRIORITY_REALTIME_EXT = VK_QUEUE_GLOBAL_PRIORITY_REALTIME_KHR,
 VK_QUEUE_GLOBAL_PRIORITY_MAX_ENUM_KHR = 0x7FFFFFFF
} VkQueueGlobalPriorityKHR;
typedef struct VkDeviceQueueGlobalPriorityCreateInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkQueueGlobalPriorityKHR globalPriority;
} VkDeviceQueueGlobalPriorityCreateInfoKHR;

typedef struct VkPhysicalDeviceGlobalPriorityQueryFeaturesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 globalPriorityQuery;
} VkPhysicalDeviceGlobalPriorityQueryFeaturesKHR;

typedef struct VkQueueFamilyGlobalPriorityPropertiesKHR {
 VkStructureType sType;
 void* pNext;
 uint32_t priorityCount;
 VkQueueGlobalPriorityKHR priorities[VK_MAX_GLOBAL_PRIORITY_SIZE_KHR];
} VkQueueFamilyGlobalPriorityPropertiesKHR;

// VK_KHR_driver_properties is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_driver_properties 1
#define VK_KHR_DRIVER_PROPERTIES_SPEC_VERSION 1
#define VK_KHR_DRIVER_PROPERTIES_EXTENSION_NAME "VK_KHR_driver_properties"
#define VK_MAX_DRIVER_NAME_SIZE_KHR VK_MAX_DRIVER_NAME_SIZE
#define VK_MAX_DRIVER_INFO_SIZE_KHR VK_MAX_DRIVER_INFO_SIZE
typedef VkDriverId VkDriverIdKHR;

typedef VkConformanceVersion VkConformanceVersionKHR;

typedef VkPhysicalDeviceDriverProperties VkPhysicalDeviceDriverPropertiesKHR;

// VK_KHR_shader_float_controls is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_shader_float_controls 1
#define VK_KHR_SHADER_FLOAT_CONTROLS_SPEC_VERSION 4
#define VK_KHR_SHADER_FLOAT_CONTROLS_EXTENSION_NAME "VK_KHR_shader_float_controls"
typedef VkShaderFloatControlsIndependence VkShaderFloatControlsIndependenceKHR;

typedef VkPhysicalDeviceFloatControlsProperties VkPhysicalDeviceFloatControlsPropertiesKHR;

// VK_KHR_depth_stencil_resolve is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_depth_stencil_resolve 1
#define VK_KHR_DEPTH_STENCIL_RESOLVE_SPEC_VERSION 1
#define VK_KHR_DEPTH_STENCIL_RESOLVE_EXTENSION_NAME "VK_KHR_depth_stencil_resolve"
typedef VkResolveModeFlagBits VkResolveModeFlagBitsKHR;

typedef VkResolveModeFlags VkResolveModeFlagsKHR;

typedef VkSubpassDescriptionDepthStencilResolve VkSubpassDescriptionDepthStencilResolveKHR;

typedef VkPhysicalDeviceDepthStencilResolveProperties VkPhysicalDeviceDepthStencilResolvePropertiesKHR;

// VK_KHR_swapchain_mutable_format is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_swapchain_mutable_format 1
#define VK_KHR_SWAPCHAIN_MUTABLE_FORMAT_SPEC_VERSION 1
#define VK_KHR_SWAPCHAIN_MUTABLE_FORMAT_EXTENSION_NAME "VK_KHR_swapchain_mutable_format"

// VK_KHR_timeline_semaphore is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_timeline_semaphore 1
#define VK_KHR_TIMELINE_SEMAPHORE_SPEC_VERSION 2
#define VK_KHR_TIMELINE_SEMAPHORE_EXTENSION_NAME "VK_KHR_timeline_semaphore"
typedef VkSemaphoreType VkSemaphoreTypeKHR;

typedef VkSemaphoreWaitFlagBits VkSemaphoreWaitFlagBitsKHR;

typedef VkSemaphoreWaitFlags VkSemaphoreWaitFlagsKHR;

typedef VkPhysicalDeviceTimelineSemaphoreFeatures VkPhysicalDeviceTimelineSemaphoreFeaturesKHR;

typedef VkPhysicalDeviceTimelineSemaphoreProperties VkPhysicalDeviceTimelineSemaphorePropertiesKHR;

typedef VkSemaphoreTypeCreateInfo VkSemaphoreTypeCreateInfoKHR;

typedef VkTimelineSemaphoreSubmitInfo VkTimelineSemaphoreSubmitInfoKHR;

typedef VkSemaphoreWaitInfo VkSemaphoreWaitInfoKHR;

typedef VkSemaphoreSignalInfo VkSemaphoreSignalInfoKHR;

typedef VkResult (VKAPI_PTR *PFN_vkGetSemaphoreCounterValueKHR)(VkDevice device, VkSemaphore semaphore, uint64_t* pValue);
typedef VkResult (VKAPI_PTR *PFN_vkWaitSemaphoresKHR)(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout);
typedef VkResult (VKAPI_PTR *PFN_vkSignalSemaphoreKHR)(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreCounterValueKHR(
 VkDevice device,
 VkSemaphore semaphore,
 uint64_t* pValue);

VKAPI_ATTR VkResult VKAPI_CALL vkWaitSemaphoresKHR(
 VkDevice device,
 const VkSemaphoreWaitInfo* pWaitInfo,
 uint64_t timeout);

VKAPI_ATTR VkResult VKAPI_CALL vkSignalSemaphoreKHR(
 VkDevice device,
 const VkSemaphoreSignalInfo* pSignalInfo);
#endif

// VK_KHR_vulkan_memory_model is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_vulkan_memory_model 1
#define VK_KHR_VULKAN_MEMORY_MODEL_SPEC_VERSION 3
#define VK_KHR_VULKAN_MEMORY_MODEL_EXTENSION_NAME "VK_KHR_vulkan_memory_model"
typedef VkPhysicalDeviceVulkanMemoryModelFeatures VkPhysicalDeviceVulkanMemoryModelFeaturesKHR;

// VK_KHR_shader_terminate_invocation is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_shader_terminate_invocation 1
#define VK_KHR_SHADER_TERMINATE_INVOCATION_SPEC_VERSION 1
#define VK_KHR_SHADER_TERMINATE_INVOCATION_EXTENSION_NAME "VK_KHR_shader_terminate_invocation"
typedef VkPhysicalDeviceShaderTerminateInvocationFeatures VkPhysicalDeviceShaderTerminateInvocationFeaturesKHR;

// VK_KHR_fragment_shading_rate is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_fragment_shading_rate 1
#define VK_KHR_FRAGMENT_SHADING_RATE_SPEC_VERSION 2
#define VK_KHR_FRAGMENT_SHADING_RATE_EXTENSION_NAME "VK_KHR_fragment_shading_rate"

typedef enum VkFragmentShadingRateCombinerOpKHR {
 VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR = 0,
 VK_FRAGMENT_SHADING_RATE_COMBINER_OP_REPLACE_KHR = 1,
 VK_FRAGMENT_SHADING_RATE_COMBINER_OP_MIN_KHR = 2,
 VK_FRAGMENT_SHADING_RATE_COMBINER_OP_MAX_KHR = 3,
 VK_FRAGMENT_SHADING_RATE_COMBINER_OP_MUL_KHR = 4,
 VK_FRAGMENT_SHADING_RATE_COMBINER_OP_MAX_ENUM_KHR = 0x7FFFFFFF
} VkFragmentShadingRateCombinerOpKHR;
typedef struct VkFragmentShadingRateAttachmentInfoKHR {
 VkStructureType sType;
 const void* pNext;
 const VkAttachmentReference2* pFragmentShadingRateAttachment;
 VkExtent2D shadingRateAttachmentTexelSize;
} VkFragmentShadingRateAttachmentInfoKHR;

typedef struct VkPipelineFragmentShadingRateStateCreateInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkExtent2D fragmentSize;
 VkFragmentShadingRateCombinerOpKHR combinerOps[2];
} VkPipelineFragmentShadingRateStateCreateInfoKHR;

typedef struct VkPhysicalDeviceFragmentShadingRateFeaturesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 pipelineFragmentShadingRate;
 VkBool32 primitiveFragmentShadingRate;
 VkBool32 attachmentFragmentShadingRate;
} VkPhysicalDeviceFragmentShadingRateFeaturesKHR;

typedef struct VkPhysicalDeviceFragmentShadingRatePropertiesKHR {
 VkStructureType sType;
 void* pNext;
 VkExtent2D minFragmentShadingRateAttachmentTexelSize;
 VkExtent2D maxFragmentShadingRateAttachmentTexelSize;
 uint32_t maxFragmentShadingRateAttachmentTexelSizeAspectRatio;
 VkBool32 primitiveFragmentShadingRateWithMultipleViewports;
 VkBool32 layeredShadingRateAttachments;
 VkBool32 fragmentShadingRateNonTrivialCombinerOps;
 VkExtent2D maxFragmentSize;
 uint32_t maxFragmentSizeAspectRatio;
 uint32_t maxFragmentShadingRateCoverageSamples;
 VkSampleCountFlagBits maxFragmentShadingRateRasterizationSamples;
 VkBool32 fragmentShadingRateWithShaderDepthStencilWrites;
 VkBool32 fragmentShadingRateWithSampleMask;
 VkBool32 fragmentShadingRateWithShaderSampleMask;
 VkBool32 fragmentShadingRateWithConservativeRasterization;
 VkBool32 fragmentShadingRateWithFragmentShaderInterlock;
 VkBool32 fragmentShadingRateWithCustomSampleLocations;
 VkBool32 fragmentShadingRateStrictMultiplyCombiner;
} VkPhysicalDeviceFragmentShadingRatePropertiesKHR;

typedef struct VkPhysicalDeviceFragmentShadingRateKHR {
 VkStructureType sType;
 void* pNext;
 VkSampleCountFlags sampleCounts;
 VkExtent2D fragmentSize;
} VkPhysicalDeviceFragmentShadingRateKHR;

typedef VkResult (VKAPI_PTR *PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR)(VkPhysicalDevice physicalDevice, uint32_t* pFragmentShadingRateCount, VkPhysicalDeviceFragmentShadingRateKHR* pFragmentShadingRates);
typedef void (VKAPI_PTR *PFN_vkCmdSetFragmentShadingRateKHR)(VkCommandBuffer commandBuffer, const VkExtent2D* pFragmentSize, const VkFragmentShadingRateCombinerOpKHR combinerOps[2]);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceFragmentShadingRatesKHR(
 VkPhysicalDevice physicalDevice,
 uint32_t* pFragmentShadingRateCount,
 VkPhysicalDeviceFragmentShadingRateKHR* pFragmentShadingRates);

VKAPI_ATTR void VKAPI_CALL vkCmdSetFragmentShadingRateKHR(
 VkCommandBuffer commandBuffer,
 const VkExtent2D* pFragmentSize,
 const VkFragmentShadingRateCombinerOpKHR combinerOps[2]);
#endif

// VK_KHR_spirv_1_4 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_spirv_1_4 1
#define VK_KHR_SPIRV_1_4_SPEC_VERSION 1
#define VK_KHR_SPIRV_1_4_EXTENSION_NAME "VK_KHR_spirv_1_4"

// VK_KHR_surface_protected_capabilities is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_surface_protected_capabilities 1
#define VK_KHR_SURFACE_PROTECTED_CAPABILITIES_SPEC_VERSION 1
#define VK_KHR_SURFACE_PROTECTED_CAPABILITIES_EXTENSION_NAME "VK_KHR_surface_protected_capabilities"
typedef struct VkSurfaceProtectedCapabilitiesKHR {
 VkStructureType sType;
 const void* pNext;
 VkBool32 supportsProtected;
} VkSurfaceProtectedCapabilitiesKHR;

// VK_KHR_separate_depth_stencil_layouts is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_separate_depth_stencil_layouts 1
#define VK_KHR_SEPARATE_DEPTH_STENCIL_LAYOUTS_SPEC_VERSION 1
#define VK_KHR_SEPARATE_DEPTH_STENCIL_LAYOUTS_EXTENSION_NAME "VK_KHR_separate_depth_stencil_layouts"
typedef VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures VkPhysicalDeviceSeparateDepthStencilLayoutsFeaturesKHR;

typedef VkAttachmentReferenceStencilLayout VkAttachmentReferenceStencilLayoutKHR;

typedef VkAttachmentDescriptionStencilLayout VkAttachmentDescriptionStencilLayoutKHR;

// VK_KHR_present_wait is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_present_wait 1
#define VK_KHR_PRESENT_WAIT_SPEC_VERSION 1
#define VK_KHR_PRESENT_WAIT_EXTENSION_NAME "VK_KHR_present_wait"
typedef struct VkPhysicalDevicePresentWaitFeaturesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 presentWait;
} VkPhysicalDevicePresentWaitFeaturesKHR;

typedef VkResult (VKAPI_PTR *PFN_vkWaitForPresentKHR)(VkDevice device, VkSwapchainKHR swapchain, uint64_t presentId, uint64_t timeout);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkWaitForPresentKHR(
 VkDevice device,
 VkSwapchainKHR swapchain,
 uint64_t presentId,
 uint64_t timeout);
#endif

// VK_KHR_uniform_buffer_standard_layout is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_uniform_buffer_standard_layout 1
#define VK_KHR_UNIFORM_BUFFER_STANDARD_LAYOUT_SPEC_VERSION 1
#define VK_KHR_UNIFORM_BUFFER_STANDARD_LAYOUT_EXTENSION_NAME "VK_KHR_uniform_buffer_standard_layout"
typedef VkPhysicalDeviceUniformBufferStandardLayoutFeatures VkPhysicalDeviceUniformBufferStandardLayoutFeaturesKHR;

// VK_KHR_buffer_device_address is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_buffer_device_address 1
#define VK_KHR_BUFFER_DEVICE_ADDRESS_SPEC_VERSION 1
#define VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME "VK_KHR_buffer_device_address"
typedef VkPhysicalDeviceBufferDeviceAddressFeatures VkPhysicalDeviceBufferDeviceAddressFeaturesKHR;

typedef VkBufferDeviceAddressInfo VkBufferDeviceAddressInfoKHR;

typedef VkBufferOpaqueCaptureAddressCreateInfo VkBufferOpaqueCaptureAddressCreateInfoKHR;

typedef VkMemoryOpaqueCaptureAddressAllocateInfo VkMemoryOpaqueCaptureAddressAllocateInfoKHR;

typedef VkDeviceMemoryOpaqueCaptureAddressInfo VkDeviceMemoryOpaqueCaptureAddressInfoKHR;

typedef VkDeviceAddress (VKAPI_PTR *PFN_vkGetBufferDeviceAddressKHR)(VkDevice device, const VkBufferDeviceAddressInfo* pInfo);
typedef uint64_t (VKAPI_PTR *PFN_vkGetBufferOpaqueCaptureAddressKHR)(VkDevice device, const VkBufferDeviceAddressInfo* pInfo);
typedef uint64_t (VKAPI_PTR *PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR)(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkDeviceAddress VKAPI_CALL vkGetBufferDeviceAddressKHR(
 VkDevice device,
 const VkBufferDeviceAddressInfo* pInfo);

VKAPI_ATTR uint64_t VKAPI_CALL vkGetBufferOpaqueCaptureAddressKHR(
 VkDevice device,
 const VkBufferDeviceAddressInfo* pInfo);

VKAPI_ATTR uint64_t VKAPI_CALL vkGetDeviceMemoryOpaqueCaptureAddressKHR(
 VkDevice device,
 const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo);
#endif

// VK_KHR_deferred_host_operations is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_deferred_host_operations 1
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDeferredOperationKHR)
#define VK_KHR_DEFERRED_HOST_OPERATIONS_SPEC_VERSION 4
#define VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME "VK_KHR_deferred_host_operations"
typedef VkResult (VKAPI_PTR *PFN_vkCreateDeferredOperationKHR)(VkDevice device, const VkAllocationCallbacks* pAllocator, VkDeferredOperationKHR* pDeferredOperation);
typedef void (VKAPI_PTR *PFN_vkDestroyDeferredOperationKHR)(VkDevice device, VkDeferredOperationKHR operation, const VkAllocationCallbacks* pAllocator);
typedef uint32_t (VKAPI_PTR *PFN_vkGetDeferredOperationMaxConcurrencyKHR)(VkDevice device, VkDeferredOperationKHR operation);
typedef VkResult (VKAPI_PTR *PFN_vkGetDeferredOperationResultKHR)(VkDevice device, VkDeferredOperationKHR operation);
typedef VkResult (VKAPI_PTR *PFN_vkDeferredOperationJoinKHR)(VkDevice device, VkDeferredOperationKHR operation);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDeferredOperationKHR(
 VkDevice device,
 const VkAllocationCallbacks* pAllocator,
 VkDeferredOperationKHR* pDeferredOperation);

VKAPI_ATTR void VKAPI_CALL vkDestroyDeferredOperationKHR(
 VkDevice device,
 VkDeferredOperationKHR operation,
 const VkAllocationCallbacks* pAllocator);

VKAPI_ATTR uint32_t VKAPI_CALL vkGetDeferredOperationMaxConcurrencyKHR(
 VkDevice device,
 VkDeferredOperationKHR operation);

VKAPI_ATTR VkResult VKAPI_CALL vkGetDeferredOperationResultKHR(
 VkDevice device,
 VkDeferredOperationKHR operation);

VKAPI_ATTR VkResult VKAPI_CALL vkDeferredOperationJoinKHR(
 VkDevice device,
 VkDeferredOperationKHR operation);
#endif

// VK_KHR_pipeline_executable_properties is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_pipeline_executable_properties 1
#define VK_KHR_PIPELINE_EXECUTABLE_PROPERTIES_SPEC_VERSION 1
#define VK_KHR_PIPELINE_EXECUTABLE_PROPERTIES_EXTENSION_NAME "VK_KHR_pipeline_executable_properties"

typedef enum VkPipelineExecutableStatisticFormatKHR {
 VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_BOOL32_KHR = 0,
 VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_INT64_KHR = 1,
 VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_UINT64_KHR = 2,
 VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_FLOAT64_KHR = 3,
 VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_MAX_ENUM_KHR = 0x7FFFFFFF
} VkPipelineExecutableStatisticFormatKHR;
typedef struct VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 pipelineExecutableInfo;
} VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR;

typedef struct VkPipelineInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkPipeline pipeline;
} VkPipelineInfoKHR;

typedef struct VkPipelineExecutablePropertiesKHR {
 VkStructureType sType;
 void* pNext;
 VkShaderStageFlags stages;
 char name[VK_MAX_DESCRIPTION_SIZE];
 char description[VK_MAX_DESCRIPTION_SIZE];
 uint32_t subgroupSize;
} VkPipelineExecutablePropertiesKHR;

typedef struct VkPipelineExecutableInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkPipeline pipeline;
 uint32_t executableIndex;
} VkPipelineExecutableInfoKHR;

typedef union VkPipelineExecutableStatisticValueKHR {
 VkBool32 b32;
 int64_t i64;
 uint64_t u64;
 double f64;
} VkPipelineExecutableStatisticValueKHR;

typedef struct VkPipelineExecutableStatisticKHR {
 VkStructureType sType;
 void* pNext;
 char name[VK_MAX_DESCRIPTION_SIZE];
 char description[VK_MAX_DESCRIPTION_SIZE];
 VkPipelineExecutableStatisticFormatKHR format;
 VkPipelineExecutableStatisticValueKHR value;
} VkPipelineExecutableStatisticKHR;

typedef struct VkPipelineExecutableInternalRepresentationKHR {
 VkStructureType sType;
 void* pNext;
 char name[VK_MAX_DESCRIPTION_SIZE];
 char description[VK_MAX_DESCRIPTION_SIZE];
 VkBool32 isText;
 size_t dataSize;
 void* pData;
} VkPipelineExecutableInternalRepresentationKHR;

typedef VkResult (VKAPI_PTR *PFN_vkGetPipelineExecutablePropertiesKHR)(VkDevice device, const VkPipelineInfoKHR* pPipelineInfo, uint32_t* pExecutableCount, VkPipelineExecutablePropertiesKHR* pProperties);
typedef VkResult (VKAPI_PTR *PFN_vkGetPipelineExecutableStatisticsKHR)(VkDevice device, const VkPipelineExecutableInfoKHR* pExecutableInfo, uint32_t* pStatisticCount, VkPipelineExecutableStatisticKHR* pStatistics);
typedef VkResult (VKAPI_PTR *PFN_vkGetPipelineExecutableInternalRepresentationsKHR)(VkDevice device, const VkPipelineExecutableInfoKHR* pExecutableInfo, uint32_t* pInternalRepresentationCount, VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetPipelineExecutablePropertiesKHR(
 VkDevice device,
 const VkPipelineInfoKHR* pPipelineInfo,
 uint32_t* pExecutableCount,
 VkPipelineExecutablePropertiesKHR* pProperties);

VKAPI_ATTR VkResult VKAPI_CALL vkGetPipelineExecutableStatisticsKHR(
 VkDevice device,
 const VkPipelineExecutableInfoKHR* pExecutableInfo,
 uint32_t* pStatisticCount,
 VkPipelineExecutableStatisticKHR* pStatistics);

VKAPI_ATTR VkResult VKAPI_CALL vkGetPipelineExecutableInternalRepresentationsKHR(
 VkDevice device,
 const VkPipelineExecutableInfoKHR* pExecutableInfo,
 uint32_t* pInternalRepresentationCount,
 VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations);
#endif

// VK_KHR_map_memory2 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_map_memory2 1
#define VK_KHR_MAP_MEMORY_2_SPEC_VERSION 1
#define VK_KHR_MAP_MEMORY_2_EXTENSION_NAME "VK_KHR_map_memory2"
typedef VkFlags VkMemoryUnmapFlagsKHR;
typedef struct VkMemoryMapInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkMemoryMapFlags flags;
 VkDeviceMemory memory;
 VkDeviceSize offset;
 VkDeviceSize size;
} VkMemoryMapInfoKHR;

typedef struct VkMemoryUnmapInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkMemoryUnmapFlagsKHR flags;
 VkDeviceMemory memory;
} VkMemoryUnmapInfoKHR;

typedef VkResult (VKAPI_PTR *PFN_vkMapMemory2KHR)(VkDevice device, const VkMemoryMapInfoKHR* pMemoryMapInfo, void** ppData);
typedef VkResult (VKAPI_PTR *PFN_vkUnmapMemory2KHR)(VkDevice device, const VkMemoryUnmapInfoKHR* pMemoryUnmapInfo);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkMapMemory2KHR(
 VkDevice device,
 const VkMemoryMapInfoKHR* pMemoryMapInfo,
 void** ppData);

VKAPI_ATTR VkResult VKAPI_CALL vkUnmapMemory2KHR(
 VkDevice device,
 const VkMemoryUnmapInfoKHR* pMemoryUnmapInfo);
#endif

// VK_KHR_shader_integer_dot_product is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_shader_integer_dot_product 1
#define VK_KHR_SHADER_INTEGER_DOT_PRODUCT_SPEC_VERSION 1
#define VK_KHR_SHADER_INTEGER_DOT_PRODUCT_EXTENSION_NAME "VK_KHR_shader_integer_dot_product"
typedef VkPhysicalDeviceShaderIntegerDotProductFeatures VkPhysicalDeviceShaderIntegerDotProductFeaturesKHR;

typedef VkPhysicalDeviceShaderIntegerDotProductProperties VkPhysicalDeviceShaderIntegerDotProductPropertiesKHR;

// VK_KHR_pipeline_library is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_pipeline_library 1
#define VK_KHR_PIPELINE_LIBRARY_SPEC_VERSION 1
#define VK_KHR_PIPELINE_LIBRARY_EXTENSION_NAME "VK_KHR_pipeline_library"
typedef struct VkPipelineLibraryCreateInfoKHR {
 VkStructureType sType;
 const void* pNext;
 uint32_t libraryCount;
 const VkPipeline* pLibraries;
} VkPipelineLibraryCreateInfoKHR;

// VK_KHR_shader_non_semantic_info is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_shader_non_semantic_info 1
#define VK_KHR_SHADER_NON_SEMANTIC_INFO_SPEC_VERSION 1
#define VK_KHR_SHADER_NON_SEMANTIC_INFO_EXTENSION_NAME "VK_KHR_shader_non_semantic_info"

// VK_KHR_present_id is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_present_id 1
#define VK_KHR_PRESENT_ID_SPEC_VERSION 1
#define VK_KHR_PRESENT_ID_EXTENSION_NAME "VK_KHR_present_id"
typedef struct VkPresentIdKHR {
 VkStructureType sType;
 const void* pNext;
 uint32_t swapchainCount;
 const uint64_t* pPresentIds;
} VkPresentIdKHR;

typedef struct VkPhysicalDevicePresentIdFeaturesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 presentId;
} VkPhysicalDevicePresentIdFeaturesKHR;

// VK_KHR_video_encode_queue is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_video_encode_queue 1
#define VK_KHR_VIDEO_ENCODE_QUEUE_SPEC_VERSION 12
#define VK_KHR_VIDEO_ENCODE_QUEUE_EXTENSION_NAME "VK_KHR_video_encode_queue"

typedef enum VkVideoEncodeTuningModeKHR {
 VK_VIDEO_ENCODE_TUNING_MODE_DEFAULT_KHR = 0,
 VK_VIDEO_ENCODE_TUNING_MODE_HIGH_QUALITY_KHR = 1,
 VK_VIDEO_ENCODE_TUNING_MODE_LOW_LATENCY_KHR = 2,
 VK_VIDEO_ENCODE_TUNING_MODE_ULTRA_LOW_LATENCY_KHR = 3,
 VK_VIDEO_ENCODE_TUNING_MODE_LOSSLESS_KHR = 4,
 VK_VIDEO_ENCODE_TUNING_MODE_MAX_ENUM_KHR = 0x7FFFFFFF
} VkVideoEncodeTuningModeKHR;
typedef VkFlags VkVideoEncodeFlagsKHR;

typedef enum VkVideoEncodeCapabilityFlagBitsKHR {
 VK_VIDEO_ENCODE_CAPABILITY_PRECEDING_EXTERNALLY_ENCODED_BYTES_BIT_KHR = 0x00000001,
 VK_VIDEO_ENCODE_CAPABILITY_INSUFFICIENT_BITSTREAM_BUFFER_RANGE_DETECTION_BIT_KHR = 0x00000002,
 VK_VIDEO_ENCODE_CAPABILITY_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkVideoEncodeCapabilityFlagBitsKHR;
typedef VkFlags VkVideoEncodeCapabilityFlagsKHR;

typedef enum VkVideoEncodeRateControlModeFlagBitsKHR {
 VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DEFAULT_KHR = 0,
 VK_VIDEO_ENCODE_RATE_CONTROL_MODE_DISABLED_BIT_KHR = 0x00000001,
 VK_VIDEO_ENCODE_RATE_CONTROL_MODE_CBR_BIT_KHR = 0x00000002,
 VK_VIDEO_ENCODE_RATE_CONTROL_MODE_VBR_BIT_KHR = 0x00000004,
 VK_VIDEO_ENCODE_RATE_CONTROL_MODE_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkVideoEncodeRateControlModeFlagBitsKHR;
typedef VkFlags VkVideoEncodeRateControlModeFlagsKHR;

typedef enum VkVideoEncodeFeedbackFlagBitsKHR {
 VK_VIDEO_ENCODE_FEEDBACK_BITSTREAM_BUFFER_OFFSET_BIT_KHR = 0x00000001,
 VK_VIDEO_ENCODE_FEEDBACK_BITSTREAM_BYTES_WRITTEN_BIT_KHR = 0x00000002,
 VK_VIDEO_ENCODE_FEEDBACK_BITSTREAM_HAS_OVERRIDES_BIT_KHR = 0x00000004,
 VK_VIDEO_ENCODE_FEEDBACK_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkVideoEncodeFeedbackFlagBitsKHR;
typedef VkFlags VkVideoEncodeFeedbackFlagsKHR;

typedef enum VkVideoEncodeUsageFlagBitsKHR {
 VK_VIDEO_ENCODE_USAGE_DEFAULT_KHR = 0,
 VK_VIDEO_ENCODE_USAGE_TRANSCODING_BIT_KHR = 0x00000001,
 VK_VIDEO_ENCODE_USAGE_STREAMING_BIT_KHR = 0x00000002,
 VK_VIDEO_ENCODE_USAGE_RECORDING_BIT_KHR = 0x00000004,
 VK_VIDEO_ENCODE_USAGE_CONFERENCING_BIT_KHR = 0x00000008,
 VK_VIDEO_ENCODE_USAGE_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkVideoEncodeUsageFlagBitsKHR;
typedef VkFlags VkVideoEncodeUsageFlagsKHR;

typedef enum VkVideoEncodeContentFlagBitsKHR {
 VK_VIDEO_ENCODE_CONTENT_DEFAULT_KHR = 0,
 VK_VIDEO_ENCODE_CONTENT_CAMERA_BIT_KHR = 0x00000001,
 VK_VIDEO_ENCODE_CONTENT_DESKTOP_BIT_KHR = 0x00000002,
 VK_VIDEO_ENCODE_CONTENT_RENDERED_BIT_KHR = 0x00000004,
 VK_VIDEO_ENCODE_CONTENT_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkVideoEncodeContentFlagBitsKHR;
typedef VkFlags VkVideoEncodeContentFlagsKHR;
typedef VkFlags VkVideoEncodeRateControlFlagsKHR;
typedef struct VkVideoEncodeInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkVideoEncodeFlagsKHR flags;
 VkBuffer dstBuffer;
 VkDeviceSize dstBufferOffset;
 VkDeviceSize dstBufferRange;
 VkVideoPictureResourceInfoKHR srcPictureResource;
 const VkVideoReferenceSlotInfoKHR* pSetupReferenceSlot;
 uint32_t referenceSlotCount;
 const VkVideoReferenceSlotInfoKHR* pReferenceSlots;
 uint32_t precedingExternallyEncodedBytes;
} VkVideoEncodeInfoKHR;

typedef struct VkVideoEncodeCapabilitiesKHR {
 VkStructureType sType;
 void* pNext;
 VkVideoEncodeCapabilityFlagsKHR flags;
 VkVideoEncodeRateControlModeFlagsKHR rateControlModes;
 uint32_t maxRateControlLayers;
 uint64_t maxBitrate;
 uint32_t maxQualityLevels;
 VkExtent2D encodeInputPictureGranularity;
 VkVideoEncodeFeedbackFlagsKHR supportedEncodeFeedbackFlags;
} VkVideoEncodeCapabilitiesKHR;

typedef struct VkQueryPoolVideoEncodeFeedbackCreateInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkVideoEncodeFeedbackFlagsKHR encodeFeedbackFlags;
} VkQueryPoolVideoEncodeFeedbackCreateInfoKHR;

typedef struct VkVideoEncodeUsageInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkVideoEncodeUsageFlagsKHR videoUsageHints;
 VkVideoEncodeContentFlagsKHR videoContentHints;
 VkVideoEncodeTuningModeKHR tuningMode;
} VkVideoEncodeUsageInfoKHR;

typedef struct VkVideoEncodeRateControlLayerInfoKHR {
 VkStructureType sType;
 const void* pNext;
 uint64_t averageBitrate;
 uint64_t maxBitrate;
 uint32_t frameRateNumerator;
 uint32_t frameRateDenominator;
} VkVideoEncodeRateControlLayerInfoKHR;

typedef struct VkVideoEncodeRateControlInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkVideoEncodeRateControlFlagsKHR flags;
 VkVideoEncodeRateControlModeFlagBitsKHR rateControlMode;
 uint32_t layerCount;
 const VkVideoEncodeRateControlLayerInfoKHR* pLayers;
 uint32_t virtualBufferSizeInMs;
 uint32_t initialVirtualBufferSizeInMs;
} VkVideoEncodeRateControlInfoKHR;

typedef struct VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR {
 VkStructureType sType;
 const void* pNext;
 const VkVideoProfileInfoKHR* pVideoProfile;
 uint32_t qualityLevel;
} VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR;

typedef struct VkVideoEncodeQualityLevelPropertiesKHR {
 VkStructureType sType;
 void* pNext;
 VkVideoEncodeRateControlModeFlagBitsKHR preferredRateControlMode;
 uint32_t preferredRateControlLayerCount;
} VkVideoEncodeQualityLevelPropertiesKHR;

typedef struct VkVideoEncodeQualityLevelInfoKHR {
 VkStructureType sType;
 const void* pNext;
 uint32_t qualityLevel;
} VkVideoEncodeQualityLevelInfoKHR;

typedef struct VkVideoEncodeSessionParametersGetInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkVideoSessionParametersKHR videoSessionParameters;
} VkVideoEncodeSessionParametersGetInfoKHR;

typedef struct VkVideoEncodeSessionParametersFeedbackInfoKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 hasOverrides;
} VkVideoEncodeSessionParametersFeedbackInfoKHR;

typedef VkResult (VKAPI_PTR *PFN_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR)(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR* pQualityLevelInfo, VkVideoEncodeQualityLevelPropertiesKHR* pQualityLevelProperties);
typedef VkResult (VKAPI_PTR *PFN_vkGetEncodedVideoSessionParametersKHR)(VkDevice device, const VkVideoEncodeSessionParametersGetInfoKHR* pVideoSessionParametersInfo, VkVideoEncodeSessionParametersFeedbackInfoKHR* pFeedbackInfo, size_t* pDataSize, void* pData);
typedef void (VKAPI_PTR *PFN_vkCmdEncodeVideoKHR)(VkCommandBuffer commandBuffer, const VkVideoEncodeInfoKHR* pEncodeInfo);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR(
 VkPhysicalDevice physicalDevice,
 const VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR* pQualityLevelInfo,
 VkVideoEncodeQualityLevelPropertiesKHR* pQualityLevelProperties);

VKAPI_ATTR VkResult VKAPI_CALL vkGetEncodedVideoSessionParametersKHR(
 VkDevice device,
 const VkVideoEncodeSessionParametersGetInfoKHR* pVideoSessionParametersInfo,
 VkVideoEncodeSessionParametersFeedbackInfoKHR* pFeedbackInfo,
 size_t* pDataSize,
 void* pData);

VKAPI_ATTR void VKAPI_CALL vkCmdEncodeVideoKHR(
 VkCommandBuffer commandBuffer,
 const VkVideoEncodeInfoKHR* pEncodeInfo);
#endif

// VK_KHR_synchronization2 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_synchronization2 1
#define VK_KHR_SYNCHRONIZATION_2_SPEC_VERSION 1
#define VK_KHR_SYNCHRONIZATION_2_EXTENSION_NAME "VK_KHR_synchronization2"
typedef VkPipelineStageFlags2 VkPipelineStageFlags2KHR;

typedef VkPipelineStageFlagBits2 VkPipelineStageFlagBits2KHR;

typedef VkAccessFlags2 VkAccessFlags2KHR;

typedef VkAccessFlagBits2 VkAccessFlagBits2KHR;

typedef VkSubmitFlagBits VkSubmitFlagBitsKHR;

typedef VkSubmitFlags VkSubmitFlagsKHR;

typedef VkMemoryBarrier2 VkMemoryBarrier2KHR;

typedef VkBufferMemoryBarrier2 VkBufferMemoryBarrier2KHR;

typedef VkImageMemoryBarrier2 VkImageMemoryBarrier2KHR;

typedef VkDependencyInfo VkDependencyInfoKHR;

typedef VkSubmitInfo2 VkSubmitInfo2KHR;

typedef VkSemaphoreSubmitInfo VkSemaphoreSubmitInfoKHR;

typedef VkCommandBufferSubmitInfo VkCommandBufferSubmitInfoKHR;

typedef VkPhysicalDeviceSynchronization2Features VkPhysicalDeviceSynchronization2FeaturesKHR;

typedef struct VkQueueFamilyCheckpointProperties2NV {
 VkStructureType sType;
 void* pNext;
 VkPipelineStageFlags2 checkpointExecutionStageMask;
} VkQueueFamilyCheckpointProperties2NV;

typedef struct VkCheckpointData2NV {
 VkStructureType sType;
 void* pNext;
 VkPipelineStageFlags2 stage;
 void* pCheckpointMarker;
} VkCheckpointData2NV;

typedef void (VKAPI_PTR *PFN_vkCmdSetEvent2KHR)(VkCommandBuffer commandBuffer, VkEvent event, const VkDependencyInfo* pDependencyInfo);
typedef void (VKAPI_PTR *PFN_vkCmdResetEvent2KHR)(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags2 stageMask);
typedef void (VKAPI_PTR *PFN_vkCmdWaitEvents2KHR)(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, const VkDependencyInfo* pDependencyInfos);
typedef void (VKAPI_PTR *PFN_vkCmdPipelineBarrier2KHR)(VkCommandBuffer commandBuffer, const VkDependencyInfo* pDependencyInfo);
typedef void (VKAPI_PTR *PFN_vkCmdWriteTimestamp2KHR)(VkCommandBuffer commandBuffer, VkPipelineStageFlags2 stage, VkQueryPool queryPool, uint32_t query);
typedef VkResult (VKAPI_PTR *PFN_vkQueueSubmit2KHR)(VkQueue queue, uint32_t submitCount, const VkSubmitInfo2* pSubmits, VkFence fence);
typedef void (VKAPI_PTR *PFN_vkCmdWriteBufferMarker2AMD)(VkCommandBuffer commandBuffer, VkPipelineStageFlags2 stage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker);
typedef void (VKAPI_PTR *PFN_vkGetQueueCheckpointData2NV)(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointData2NV* pCheckpointData);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdSetEvent2KHR(
 VkCommandBuffer commandBuffer,
 VkEvent event,
 const VkDependencyInfo* pDependencyInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdResetEvent2KHR(
 VkCommandBuffer commandBuffer,
 VkEvent event,
 VkPipelineStageFlags2 stageMask);

VKAPI_ATTR void VKAPI_CALL vkCmdWaitEvents2KHR(
 VkCommandBuffer commandBuffer,
 uint32_t eventCount,
 const VkEvent* pEvents,
 const VkDependencyInfo* pDependencyInfos);

VKAPI_ATTR void VKAPI_CALL vkCmdPipelineBarrier2KHR(
 VkCommandBuffer commandBuffer,
 const VkDependencyInfo* pDependencyInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdWriteTimestamp2KHR(
 VkCommandBuffer commandBuffer,
 VkPipelineStageFlags2 stage,
 VkQueryPool queryPool,
 uint32_t query);

VKAPI_ATTR VkResult VKAPI_CALL vkQueueSubmit2KHR(
 VkQueue queue,
 uint32_t submitCount,
 const VkSubmitInfo2* pSubmits,
 VkFence fence);

VKAPI_ATTR void VKAPI_CALL vkCmdWriteBufferMarker2AMD(
 VkCommandBuffer commandBuffer,
 VkPipelineStageFlags2 stage,
 VkBuffer dstBuffer,
 VkDeviceSize dstOffset,
 uint32_t marker);

VKAPI_ATTR void VKAPI_CALL vkGetQueueCheckpointData2NV(
 VkQueue queue,
 uint32_t* pCheckpointDataCount,
 VkCheckpointData2NV* pCheckpointData);
#endif

// VK_KHR_fragment_shader_barycentric is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_fragment_shader_barycentric 1
#define VK_KHR_FRAGMENT_SHADER_BARYCENTRIC_SPEC_VERSION 1
#define VK_KHR_FRAGMENT_SHADER_BARYCENTRIC_EXTENSION_NAME "VK_KHR_fragment_shader_barycentric"
typedef struct VkPhysicalDeviceFragmentShaderBarycentricFeaturesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 fragmentShaderBarycentric;
} VkPhysicalDeviceFragmentShaderBarycentricFeaturesKHR;

typedef struct VkPhysicalDeviceFragmentShaderBarycentricPropertiesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 triStripVertexOrderIndependentOfProvokingVertex;
} VkPhysicalDeviceFragmentShaderBarycentricPropertiesKHR;

// VK_KHR_shader_subgroup_uniform_control_flow is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_shader_subgroup_uniform_control_flow 1
#define VK_KHR_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_SPEC_VERSION 1
#define VK_KHR_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_EXTENSION_NAME "VK_KHR_shader_subgroup_uniform_control_flow"
typedef struct VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 shaderSubgroupUniformControlFlow;
} VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR;

// VK_KHR_zero_initialize_workgroup_memory is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_zero_initialize_workgroup_memory 1
#define VK_KHR_ZERO_INITIALIZE_WORKGROUP_MEMORY_SPEC_VERSION 1
#define VK_KHR_ZERO_INITIALIZE_WORKGROUP_MEMORY_EXTENSION_NAME "VK_KHR_zero_initialize_workgroup_memory"
typedef VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeaturesKHR;

// VK_KHR_workgroup_memory_explicit_layout is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_workgroup_memory_explicit_layout 1
#define VK_KHR_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_SPEC_VERSION 1
#define VK_KHR_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_EXTENSION_NAME "VK_KHR_workgroup_memory_explicit_layout"
typedef struct VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 workgroupMemoryExplicitLayout;
 VkBool32 workgroupMemoryExplicitLayoutScalarBlockLayout;
 VkBool32 workgroupMemoryExplicitLayout8BitAccess;
 VkBool32 workgroupMemoryExplicitLayout16BitAccess;
} VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR;

// VK_KHR_copy_commands2 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_copy_commands2 1
#define VK_KHR_COPY_COMMANDS_2_SPEC_VERSION 1
#define VK_KHR_COPY_COMMANDS_2_EXTENSION_NAME "VK_KHR_copy_commands2"
typedef VkCopyBufferInfo2 VkCopyBufferInfo2KHR;

typedef VkCopyImageInfo2 VkCopyImageInfo2KHR;

typedef VkCopyBufferToImageInfo2 VkCopyBufferToImageInfo2KHR;

typedef VkCopyImageToBufferInfo2 VkCopyImageToBufferInfo2KHR;

typedef VkBlitImageInfo2 VkBlitImageInfo2KHR;

typedef VkResolveImageInfo2 VkResolveImageInfo2KHR;

typedef VkBufferCopy2 VkBufferCopy2KHR;

typedef VkImageCopy2 VkImageCopy2KHR;

typedef VkImageBlit2 VkImageBlit2KHR;

typedef VkBufferImageCopy2 VkBufferImageCopy2KHR;

typedef VkImageResolve2 VkImageResolve2KHR;

typedef void (VKAPI_PTR *PFN_vkCmdCopyBuffer2KHR)(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo);
typedef void (VKAPI_PTR *PFN_vkCmdCopyImage2KHR)(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo);
typedef void (VKAPI_PTR *PFN_vkCmdCopyBufferToImage2KHR)(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo);
typedef void (VKAPI_PTR *PFN_vkCmdCopyImageToBuffer2KHR)(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo);
typedef void (VKAPI_PTR *PFN_vkCmdBlitImage2KHR)(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo);
typedef void (VKAPI_PTR *PFN_vkCmdResolveImage2KHR)(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdCopyBuffer2KHR(
 VkCommandBuffer commandBuffer,
 const VkCopyBufferInfo2* pCopyBufferInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdCopyImage2KHR(
 VkCommandBuffer commandBuffer,
 const VkCopyImageInfo2* pCopyImageInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdCopyBufferToImage2KHR(
 VkCommandBuffer commandBuffer,
 const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdCopyImageToBuffer2KHR(
 VkCommandBuffer commandBuffer,
 const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdBlitImage2KHR(
 VkCommandBuffer commandBuffer,
 const VkBlitImageInfo2* pBlitImageInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdResolveImage2KHR(
 VkCommandBuffer commandBuffer,
 const VkResolveImageInfo2* pResolveImageInfo);
#endif

// VK_KHR_format_feature_flags2 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_format_feature_flags2 1
#define VK_KHR_FORMAT_FEATURE_FLAGS_2_SPEC_VERSION 2
#define VK_KHR_FORMAT_FEATURE_FLAGS_2_EXTENSION_NAME "VK_KHR_format_feature_flags2"
typedef VkFormatFeatureFlags2 VkFormatFeatureFlags2KHR;

typedef VkFormatFeatureFlagBits2 VkFormatFeatureFlagBits2KHR;

typedef VkFormatProperties3 VkFormatProperties3KHR;

// VK_KHR_ray_tracing_maintenance1 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_ray_tracing_maintenance1 1
#define VK_KHR_RAY_TRACING_MAINTENANCE_1_SPEC_VERSION 1
#define VK_KHR_RAY_TRACING_MAINTENANCE_1_EXTENSION_NAME "VK_KHR_ray_tracing_maintenance1"
typedef struct VkPhysicalDeviceRayTracingMaintenance1FeaturesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 rayTracingMaintenance1;
 VkBool32 rayTracingPipelineTraceRaysIndirect2;
} VkPhysicalDeviceRayTracingMaintenance1FeaturesKHR;

typedef struct VkTraceRaysIndirectCommand2KHR {
 VkDeviceAddress raygenShaderRecordAddress;
 VkDeviceSize raygenShaderRecordSize;
 VkDeviceAddress missShaderBindingTableAddress;
 VkDeviceSize missShaderBindingTableSize;
 VkDeviceSize missShaderBindingTableStride;
 VkDeviceAddress hitShaderBindingTableAddress;
 VkDeviceSize hitShaderBindingTableSize;
 VkDeviceSize hitShaderBindingTableStride;
 VkDeviceAddress callableShaderBindingTableAddress;
 VkDeviceSize callableShaderBindingTableSize;
 VkDeviceSize callableShaderBindingTableStride;
 uint32_t width;
 uint32_t height;
 uint32_t depth;
} VkTraceRaysIndirectCommand2KHR;

typedef void (VKAPI_PTR *PFN_vkCmdTraceRaysIndirect2KHR)(VkCommandBuffer commandBuffer, VkDeviceAddress indirectDeviceAddress);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdTraceRaysIndirect2KHR(
 VkCommandBuffer commandBuffer,
 VkDeviceAddress indirectDeviceAddress);
#endif

// VK_KHR_portability_enumeration is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_portability_enumeration 1
#define VK_KHR_PORTABILITY_ENUMERATION_SPEC_VERSION 1
#define VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME "VK_KHR_portability_enumeration"

// VK_KHR_maintenance4 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_maintenance4 1
#define VK_KHR_MAINTENANCE_4_SPEC_VERSION 2
#define VK_KHR_MAINTENANCE_4_EXTENSION_NAME "VK_KHR_maintenance4"
typedef VkPhysicalDeviceMaintenance4Features VkPhysicalDeviceMaintenance4FeaturesKHR;

typedef VkPhysicalDeviceMaintenance4Properties VkPhysicalDeviceMaintenance4PropertiesKHR;

typedef VkDeviceBufferMemoryRequirements VkDeviceBufferMemoryRequirementsKHR;

typedef VkDeviceImageMemoryRequirements VkDeviceImageMemoryRequirementsKHR;

typedef void (VKAPI_PTR *PFN_vkGetDeviceBufferMemoryRequirementsKHR)(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements);
typedef void (VKAPI_PTR *PFN_vkGetDeviceImageMemoryRequirementsKHR)(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements);
typedef void (VKAPI_PTR *PFN_vkGetDeviceImageSparseMemoryRequirementsKHR)(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkGetDeviceBufferMemoryRequirementsKHR(
 VkDevice device,
 const VkDeviceBufferMemoryRequirements* pInfo,
 VkMemoryRequirements2* pMemoryRequirements);

VKAPI_ATTR void VKAPI_CALL vkGetDeviceImageMemoryRequirementsKHR(
 VkDevice device,
 const VkDeviceImageMemoryRequirements* pInfo,
 VkMemoryRequirements2* pMemoryRequirements);

VKAPI_ATTR void VKAPI_CALL vkGetDeviceImageSparseMemoryRequirementsKHR(
 VkDevice device,
 const VkDeviceImageMemoryRequirements* pInfo,
 uint32_t* pSparseMemoryRequirementCount,
 VkSparseImageMemoryRequirements2* pSparseMemoryRequirements);
#endif

// VK_KHR_maintenance5 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_maintenance5 1
#define VK_KHR_MAINTENANCE_5_SPEC_VERSION 1
#define VK_KHR_MAINTENANCE_5_EXTENSION_NAME "VK_KHR_maintenance5"
typedef VkFlags64 VkPipelineCreateFlags2KHR;

// Flag bits for VkPipelineCreateFlagBits2KHR
typedef VkFlags64 VkPipelineCreateFlagBits2KHR;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_DISABLE_OPTIMIZATION_BIT_KHR = 0x00000001ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_ALLOW_DERIVATIVES_BIT_KHR = 0x00000002ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_DERIVATIVE_BIT_KHR = 0x00000004ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_VIEW_INDEX_FROM_DEVICE_INDEX_BIT_KHR = 0x00000008ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_DISPATCH_BASE_BIT_KHR = 0x00000010ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_DEFER_COMPILE_BIT_NV = 0x00000020ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_CAPTURE_STATISTICS_BIT_KHR = 0x00000040ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_CAPTURE_INTERNAL_REPRESENTATIONS_BIT_KHR = 0x00000080ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT_KHR = 0x00000100ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_EARLY_RETURN_ON_FAILURE_BIT_KHR = 0x00000200ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_LINK_TIME_OPTIMIZATION_BIT_EXT = 0x00000400ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_RETAIN_LINK_TIME_OPTIMIZATION_INFO_BIT_EXT = 0x00800000ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_LIBRARY_BIT_KHR = 0x00000800ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_RAY_TRACING_SKIP_TRIANGLES_BIT_KHR = 0x00001000ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_RAY_TRACING_SKIP_AABBS_BIT_KHR = 0x00002000ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_RAY_TRACING_NO_NULL_ANY_HIT_SHADERS_BIT_KHR = 0x00004000ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR = 0x00008000ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_RAY_TRACING_NO_NULL_MISS_SHADERS_BIT_KHR = 0x00010000ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR = 0x00020000ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_RAY_TRACING_SHADER_GROUP_HANDLE_CAPTURE_REPLAY_BIT_KHR = 0x00080000ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_INDIRECT_BINDABLE_BIT_NV = 0x00040000ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_RAY_TRACING_ALLOW_MOTION_BIT_NV = 0x00100000ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_RENDERING_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR = 0x00200000ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_RENDERING_FRAGMENT_DENSITY_MAP_ATTACHMENT_BIT_EXT = 0x00400000ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_RAY_TRACING_OPACITY_MICROMAP_BIT_EXT = 0x01000000ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_COLOR_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT = 0x02000000ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_DEPTH_STENCIL_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT = 0x04000000ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_NO_PROTECTED_ACCESS_BIT_EXT = 0x08000000ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_PROTECTED_ACCESS_ONLY_BIT_EXT = 0x40000000ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_RAY_TRACING_DISPLACEMENT_MICROMAP_BIT_NV = 0x10000000ULL;
static const VkPipelineCreateFlagBits2KHR VK_PIPELINE_CREATE_2_DESCRIPTOR_BUFFER_BIT_EXT = 0x20000000ULL;

typedef VkFlags64 VkBufferUsageFlags2KHR;

// Flag bits for VkBufferUsageFlagBits2KHR
typedef VkFlags64 VkBufferUsageFlagBits2KHR;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_TRANSFER_SRC_BIT_KHR = 0x00000001ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_TRANSFER_DST_BIT_KHR = 0x00000002ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_UNIFORM_TEXEL_BUFFER_BIT_KHR = 0x00000004ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_STORAGE_TEXEL_BUFFER_BIT_KHR = 0x00000008ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_UNIFORM_BUFFER_BIT_KHR = 0x00000010ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_STORAGE_BUFFER_BIT_KHR = 0x00000020ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_INDEX_BUFFER_BIT_KHR = 0x00000040ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_VERTEX_BUFFER_BIT_KHR = 0x00000080ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_INDIRECT_BUFFER_BIT_KHR = 0x00000100ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_CONDITIONAL_RENDERING_BIT_EXT = 0x00000200ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_SHADER_BINDING_TABLE_BIT_KHR = 0x00000400ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_RAY_TRACING_BIT_NV = 0x00000400ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT = 0x00000800ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT = 0x00001000ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_VIDEO_DECODE_SRC_BIT_KHR = 0x00002000ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_VIDEO_DECODE_DST_BIT_KHR = 0x00004000ULL;

static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_VIDEO_ENCODE_DST_BIT_KHR = 0x00008000ULL;

static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_VIDEO_ENCODE_SRC_BIT_KHR = 0x00010000ULL;

static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_SHADER_DEVICE_ADDRESS_BIT_KHR = 0x00020000ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR = 0x00080000ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR = 0x00100000ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_SAMPLER_DESCRIPTOR_BUFFER_BIT_EXT = 0x00200000ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_RESOURCE_DESCRIPTOR_BUFFER_BIT_EXT = 0x00400000ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_PUSH_DESCRIPTORS_DESCRIPTOR_BUFFER_BIT_EXT = 0x04000000ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_MICROMAP_BUILD_INPUT_READ_ONLY_BIT_EXT = 0x00800000ULL;
static const VkBufferUsageFlagBits2KHR VK_BUFFER_USAGE_2_MICROMAP_STORAGE_BIT_EXT = 0x01000000ULL;

typedef struct VkPhysicalDeviceMaintenance5FeaturesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 maintenance5;
} VkPhysicalDeviceMaintenance5FeaturesKHR;

typedef struct VkPhysicalDeviceMaintenance5PropertiesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 earlyFragmentMultisampleCoverageAfterSampleCounting;
 VkBool32 earlyFragmentSampleMaskTestBeforeSampleCounting;
 VkBool32 depthStencilSwizzleOneSupport;
 VkBool32 polygonModePointSize;
 VkBool32 nonStrictSinglePixelWideLinesUseParallelogram;
 VkBool32 nonStrictWideLinesUseParallelogram;
} VkPhysicalDeviceMaintenance5PropertiesKHR;

typedef struct VkRenderingAreaInfoKHR {
 VkStructureType sType;
 const void* pNext;
 uint32_t viewMask;
 uint32_t colorAttachmentCount;
 const VkFormat* pColorAttachmentFormats;
 VkFormat depthAttachmentFormat;
 VkFormat stencilAttachmentFormat;
} VkRenderingAreaInfoKHR;

typedef struct VkImageSubresource2KHR {
 VkStructureType sType;
 void* pNext;
 VkImageSubresource imageSubresource;
} VkImageSubresource2KHR;

typedef struct VkDeviceImageSubresourceInfoKHR {
 VkStructureType sType;
 const void* pNext;
 const VkImageCreateInfo* pCreateInfo;
 const VkImageSubresource2KHR* pSubresource;
} VkDeviceImageSubresourceInfoKHR;

typedef struct VkSubresourceLayout2KHR {
 VkStructureType sType;
 void* pNext;
 VkSubresourceLayout subresourceLayout;
} VkSubresourceLayout2KHR;

typedef struct VkPipelineCreateFlags2CreateInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkPipelineCreateFlags2KHR flags;
} VkPipelineCreateFlags2CreateInfoKHR;

typedef struct VkBufferUsageFlags2CreateInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkBufferUsageFlags2KHR usage;
} VkBufferUsageFlags2CreateInfoKHR;

typedef void (VKAPI_PTR *PFN_vkCmdBindIndexBuffer2KHR)(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, VkIndexType indexType);
typedef void (VKAPI_PTR *PFN_vkGetRenderingAreaGranularityKHR)(VkDevice device, const VkRenderingAreaInfoKHR* pRenderingAreaInfo, VkExtent2D* pGranularity);
typedef void (VKAPI_PTR *PFN_vkGetDeviceImageSubresourceLayoutKHR)(VkDevice device, const VkDeviceImageSubresourceInfoKHR* pInfo, VkSubresourceLayout2KHR* pLayout);
typedef void (VKAPI_PTR *PFN_vkGetImageSubresourceLayout2KHR)(VkDevice device, VkImage image, const VkImageSubresource2KHR* pSubresource, VkSubresourceLayout2KHR* pLayout);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdBindIndexBuffer2KHR(
 VkCommandBuffer commandBuffer,
 VkBuffer buffer,
 VkDeviceSize offset,
 VkDeviceSize size,
 VkIndexType indexType);

VKAPI_ATTR void VKAPI_CALL vkGetRenderingAreaGranularityKHR(
 VkDevice device,
 const VkRenderingAreaInfoKHR* pRenderingAreaInfo,
 VkExtent2D* pGranularity);

VKAPI_ATTR void VKAPI_CALL vkGetDeviceImageSubresourceLayoutKHR(
 VkDevice device,
 const VkDeviceImageSubresourceInfoKHR* pInfo,
 VkSubresourceLayout2KHR* pLayout);

VKAPI_ATTR void VKAPI_CALL vkGetImageSubresourceLayout2KHR(
 VkDevice device,
 VkImage image,
 const VkImageSubresource2KHR* pSubresource,
 VkSubresourceLayout2KHR* pLayout);
#endif

// VK_KHR_ray_tracing_position_fetch is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_ray_tracing_position_fetch 1
#define VK_KHR_RAY_TRACING_POSITION_FETCH_SPEC_VERSION 1
#define VK_KHR_RAY_TRACING_POSITION_FETCH_EXTENSION_NAME "VK_KHR_ray_tracing_position_fetch"
typedef struct VkPhysicalDeviceRayTracingPositionFetchFeaturesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 rayTracingPositionFetch;
} VkPhysicalDeviceRayTracingPositionFetchFeaturesKHR;

// VK_KHR_cooperative_matrix is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_cooperative_matrix 1
#define VK_KHR_COOPERATIVE_MATRIX_SPEC_VERSION 2
#define VK_KHR_COOPERATIVE_MATRIX_EXTENSION_NAME "VK_KHR_cooperative_matrix"

typedef enum VkComponentTypeKHR {
 VK_COMPONENT_TYPE_FLOAT16_KHR = 0,
 VK_COMPONENT_TYPE_FLOAT32_KHR = 1,
 VK_COMPONENT_TYPE_FLOAT64_KHR = 2,
 VK_COMPONENT_TYPE_SINT8_KHR = 3,
 VK_COMPONENT_TYPE_SINT16_KHR = 4,
 VK_COMPONENT_TYPE_SINT32_KHR = 5,
 VK_COMPONENT_TYPE_SINT64_KHR = 6,
 VK_COMPONENT_TYPE_UINT8_KHR = 7,
 VK_COMPONENT_TYPE_UINT16_KHR = 8,
 VK_COMPONENT_TYPE_UINT32_KHR = 9,
 VK_COMPONENT_TYPE_UINT64_KHR = 10,
 VK_COMPONENT_TYPE_FLOAT16_NV = VK_COMPONENT_TYPE_FLOAT16_KHR,
 VK_COMPONENT_TYPE_FLOAT32_NV = VK_COMPONENT_TYPE_FLOAT32_KHR,
 VK_COMPONENT_TYPE_FLOAT64_NV = VK_COMPONENT_TYPE_FLOAT64_KHR,
 VK_COMPONENT_TYPE_SINT8_NV = VK_COMPONENT_TYPE_SINT8_KHR,
 VK_COMPONENT_TYPE_SINT16_NV = VK_COMPONENT_TYPE_SINT16_KHR,
 VK_COMPONENT_TYPE_SINT32_NV = VK_COMPONENT_TYPE_SINT32_KHR,
 VK_COMPONENT_TYPE_SINT64_NV = VK_COMPONENT_TYPE_SINT64_KHR,
 VK_COMPONENT_TYPE_UINT8_NV = VK_COMPONENT_TYPE_UINT8_KHR,
 VK_COMPONENT_TYPE_UINT16_NV = VK_COMPONENT_TYPE_UINT16_KHR,
 VK_COMPONENT_TYPE_UINT32_NV = VK_COMPONENT_TYPE_UINT32_KHR,
 VK_COMPONENT_TYPE_UINT64_NV = VK_COMPONENT_TYPE_UINT64_KHR,
 VK_COMPONENT_TYPE_MAX_ENUM_KHR = 0x7FFFFFFF
} VkComponentTypeKHR;

typedef enum VkScopeKHR {
 VK_SCOPE_DEVICE_KHR = 1,
 VK_SCOPE_WORKGROUP_KHR = 2,
 VK_SCOPE_SUBGROUP_KHR = 3,
 VK_SCOPE_QUEUE_FAMILY_KHR = 5,
 VK_SCOPE_DEVICE_NV = VK_SCOPE_DEVICE_KHR,
 VK_SCOPE_WORKGROUP_NV = VK_SCOPE_WORKGROUP_KHR,
 VK_SCOPE_SUBGROUP_NV = VK_SCOPE_SUBGROUP_KHR,
 VK_SCOPE_QUEUE_FAMILY_NV = VK_SCOPE_QUEUE_FAMILY_KHR,
 VK_SCOPE_MAX_ENUM_KHR = 0x7FFFFFFF
} VkScopeKHR;
typedef struct VkCooperativeMatrixPropertiesKHR {
 VkStructureType sType;
 void* pNext;
 uint32_t MSize;
 uint32_t NSize;
 uint32_t KSize;
 VkComponentTypeKHR AType;
 VkComponentTypeKHR BType;
 VkComponentTypeKHR CType;
 VkComponentTypeKHR ResultType;
 VkBool32 saturatingAccumulation;
 VkScopeKHR scope;
} VkCooperativeMatrixPropertiesKHR;

typedef struct VkPhysicalDeviceCooperativeMatrixFeaturesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 cooperativeMatrix;
 VkBool32 cooperativeMatrixRobustBufferAccess;
} VkPhysicalDeviceCooperativeMatrixFeaturesKHR;

typedef struct VkPhysicalDeviceCooperativeMatrixPropertiesKHR {
 VkStructureType sType;
 void* pNext;
 VkShaderStageFlags cooperativeMatrixSupportedStages;
} VkPhysicalDeviceCooperativeMatrixPropertiesKHR;

typedef VkResult (VKAPI_PTR *PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR)(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkCooperativeMatrixPropertiesKHR* pProperties);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR(
 VkPhysicalDevice physicalDevice,
 uint32_t* pPropertyCount,
 VkCooperativeMatrixPropertiesKHR* pProperties);
#endif

// VK_KHR_video_maintenance1 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_video_maintenance1 1
#define VK_KHR_VIDEO_MAINTENANCE_1_SPEC_VERSION 1
#define VK_KHR_VIDEO_MAINTENANCE_1_EXTENSION_NAME "VK_KHR_video_maintenance1"
typedef struct VkPhysicalDeviceVideoMaintenance1FeaturesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 videoMaintenance1;
} VkPhysicalDeviceVideoMaintenance1FeaturesKHR;

typedef struct VkVideoInlineQueryInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkQueryPool queryPool;
 uint32_t firstQuery;
 uint32_t queryCount;
} VkVideoInlineQueryInfoKHR;

// VK_KHR_vertex_attribute_divisor is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_vertex_attribute_divisor 1
#define VK_KHR_VERTEX_ATTRIBUTE_DIVISOR_SPEC_VERSION 1
#define VK_KHR_VERTEX_ATTRIBUTE_DIVISOR_EXTENSION_NAME "VK_KHR_vertex_attribute_divisor"
typedef struct VkPhysicalDeviceVertexAttributeDivisorPropertiesKHR {
 VkStructureType sType;
 void* pNext;
 uint32_t maxVertexAttribDivisor;
 VkBool32 supportsNonZeroFirstInstance;
} VkPhysicalDeviceVertexAttributeDivisorPropertiesKHR;

typedef struct VkVertexInputBindingDivisorDescriptionKHR {
 uint32_t binding;
 uint32_t divisor;
} VkVertexInputBindingDivisorDescriptionKHR;

typedef struct VkPipelineVertexInputDivisorStateCreateInfoKHR {
 VkStructureType sType;
 const void* pNext;
 uint32_t vertexBindingDivisorCount;
 const VkVertexInputBindingDivisorDescriptionKHR* pVertexBindingDivisors;
} VkPipelineVertexInputDivisorStateCreateInfoKHR;

typedef struct VkPhysicalDeviceVertexAttributeDivisorFeaturesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 vertexAttributeInstanceRateDivisor;
 VkBool32 vertexAttributeInstanceRateZeroDivisor;
} VkPhysicalDeviceVertexAttributeDivisorFeaturesKHR;

// VK_KHR_calibrated_timestamps is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_calibrated_timestamps 1
#define VK_KHR_CALIBRATED_TIMESTAMPS_SPEC_VERSION 1
#define VK_KHR_CALIBRATED_TIMESTAMPS_EXTENSION_NAME "VK_KHR_calibrated_timestamps"

typedef enum VkTimeDomainKHR {
 VK_TIME_DOMAIN_DEVICE_KHR = 0,
 VK_TIME_DOMAIN_CLOCK_MONOTONIC_KHR = 1,
 VK_TIME_DOMAIN_CLOCK_MONOTONIC_RAW_KHR = 2,
 VK_TIME_DOMAIN_QUERY_PERFORMANCE_COUNTER_KHR = 3,
 VK_TIME_DOMAIN_DEVICE_EXT = VK_TIME_DOMAIN_DEVICE_KHR,
 VK_TIME_DOMAIN_CLOCK_MONOTONIC_EXT = VK_TIME_DOMAIN_CLOCK_MONOTONIC_KHR,
 VK_TIME_DOMAIN_CLOCK_MONOTONIC_RAW_EXT = VK_TIME_DOMAIN_CLOCK_MONOTONIC_RAW_KHR,
 VK_TIME_DOMAIN_QUERY_PERFORMANCE_COUNTER_EXT = VK_TIME_DOMAIN_QUERY_PERFORMANCE_COUNTER_KHR,
 VK_TIME_DOMAIN_MAX_ENUM_KHR = 0x7FFFFFFF
} VkTimeDomainKHR;
typedef struct VkCalibratedTimestampInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkTimeDomainKHR timeDomain;
} VkCalibratedTimestampInfoKHR;

typedef VkResult (VKAPI_PTR *PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR)(VkPhysicalDevice physicalDevice, uint32_t* pTimeDomainCount, VkTimeDomainKHR* pTimeDomains);
typedef VkResult (VKAPI_PTR *PFN_vkGetCalibratedTimestampsKHR)(VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoKHR* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceCalibrateableTimeDomainsKHR(
 VkPhysicalDevice physicalDevice,
 uint32_t* pTimeDomainCount,
 VkTimeDomainKHR* pTimeDomains);

VKAPI_ATTR VkResult VKAPI_CALL vkGetCalibratedTimestampsKHR(
 VkDevice device,
 uint32_t timestampCount,
 const VkCalibratedTimestampInfoKHR* pTimestampInfos,
 uint64_t* pTimestamps,
 uint64_t* pMaxDeviation);
#endif

// VK_KHR_maintenance6 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_maintenance6 1
#define VK_KHR_MAINTENANCE_6_SPEC_VERSION 1
#define VK_KHR_MAINTENANCE_6_EXTENSION_NAME "VK_KHR_maintenance6"
typedef struct VkPhysicalDeviceMaintenance6FeaturesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 maintenance6;
} VkPhysicalDeviceMaintenance6FeaturesKHR;

typedef struct VkPhysicalDeviceMaintenance6PropertiesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 blockTexelViewCompatibleMultipleLayers;
 uint32_t maxCombinedImageSamplerDescriptorCount;
 VkBool32 fragmentShadingRateClampCombinerInputs;
} VkPhysicalDeviceMaintenance6PropertiesKHR;

typedef struct VkBindMemoryStatusKHR {
 VkStructureType sType;
 const void* pNext;
 VkResult* pResult;
} VkBindMemoryStatusKHR;

typedef struct VkBindDescriptorSetsInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkShaderStageFlags stageFlags;
 VkPipelineLayout layout;
 uint32_t firstSet;
 uint32_t descriptorSetCount;
 const VkDescriptorSet* pDescriptorSets;
 uint32_t dynamicOffsetCount;
 const uint32_t* pDynamicOffsets;
} VkBindDescriptorSetsInfoKHR;

typedef struct VkPushConstantsInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkPipelineLayout layout;
 VkShaderStageFlags stageFlags;
 uint32_t offset;
 uint32_t size;
 const void* pValues;
} VkPushConstantsInfoKHR;

typedef struct VkPushDescriptorSetInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkShaderStageFlags stageFlags;
 VkPipelineLayout layout;
 uint32_t set;
 uint32_t descriptorWriteCount;
 const VkWriteDescriptorSet* pDescriptorWrites;
} VkPushDescriptorSetInfoKHR;

typedef struct VkPushDescriptorSetWithTemplateInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkDescriptorUpdateTemplate descriptorUpdateTemplate;
 VkPipelineLayout layout;
 uint32_t set;
 const void* pData;
} VkPushDescriptorSetWithTemplateInfoKHR;

typedef struct VkSetDescriptorBufferOffsetsInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkShaderStageFlags stageFlags;
 VkPipelineLayout layout;
 uint32_t firstSet;
 uint32_t setCount;
 const uint32_t* pBufferIndices;
 const VkDeviceSize* pOffsets;
} VkSetDescriptorBufferOffsetsInfoEXT;

typedef struct VkBindDescriptorBufferEmbeddedSamplersInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkShaderStageFlags stageFlags;
 VkPipelineLayout layout;
 uint32_t set;
} VkBindDescriptorBufferEmbeddedSamplersInfoEXT;

typedef void (VKAPI_PTR *PFN_vkCmdBindDescriptorSets2KHR)(VkCommandBuffer commandBuffer, const VkBindDescriptorSetsInfoKHR* pBindDescriptorSetsInfo);
typedef void (VKAPI_PTR *PFN_vkCmdPushConstants2KHR)(VkCommandBuffer commandBuffer, const VkPushConstantsInfoKHR* pPushConstantsInfo);
typedef void (VKAPI_PTR *PFN_vkCmdPushDescriptorSet2KHR)(VkCommandBuffer commandBuffer, const VkPushDescriptorSetInfoKHR* pPushDescriptorSetInfo);
typedef void (VKAPI_PTR *PFN_vkCmdPushDescriptorSetWithTemplate2KHR)(VkCommandBuffer commandBuffer, const VkPushDescriptorSetWithTemplateInfoKHR* pPushDescriptorSetWithTemplateInfo);
typedef void (VKAPI_PTR *PFN_vkCmdSetDescriptorBufferOffsets2EXT)(VkCommandBuffer commandBuffer, const VkSetDescriptorBufferOffsetsInfoEXT* pSetDescriptorBufferOffsetsInfo);
typedef void (VKAPI_PTR *PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT)(VkCommandBuffer commandBuffer, const VkBindDescriptorBufferEmbeddedSamplersInfoEXT* pBindDescriptorBufferEmbeddedSamplersInfo);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdBindDescriptorSets2KHR(
 VkCommandBuffer commandBuffer,
 const VkBindDescriptorSetsInfoKHR* pBindDescriptorSetsInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdPushConstants2KHR(
 VkCommandBuffer commandBuffer,
 const VkPushConstantsInfoKHR* pPushConstantsInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdPushDescriptorSet2KHR(
 VkCommandBuffer commandBuffer,
 const VkPushDescriptorSetInfoKHR* pPushDescriptorSetInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdPushDescriptorSetWithTemplate2KHR(
 VkCommandBuffer commandBuffer,
 const VkPushDescriptorSetWithTemplateInfoKHR* pPushDescriptorSetWithTemplateInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdSetDescriptorBufferOffsets2EXT(
 VkCommandBuffer commandBuffer,
 const VkSetDescriptorBufferOffsetsInfoEXT* pSetDescriptorBufferOffsetsInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdBindDescriptorBufferEmbeddedSamplers2EXT(
 VkCommandBuffer commandBuffer,
 const VkBindDescriptorBufferEmbeddedSamplersInfoEXT* pBindDescriptorBufferEmbeddedSamplersInfo);
#endif

// VK_EXT_debug_report is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_debug_report 1
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDebugReportCallbackEXT)
#define VK_EXT_DEBUG_REPORT_SPEC_VERSION 10
#define VK_EXT_DEBUG_REPORT_EXTENSION_NAME "VK_EXT_debug_report"

typedef enum VkDebugReportObjectTypeEXT {
 VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT = 0,
 VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT = 1,
 VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT = 2,
 VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT = 3,
 VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT = 4,
 VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT = 5,
 VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT = 6,
 VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT = 7,
 VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT = 8,
 VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT = 9,
 VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT = 10,
 VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT = 11,
 VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT = 12,
 VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_VIEW_EXT = 13,
 VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT = 14,
 VK_DEBUG_REPORT_OBJECT_TYPE_SHADER_MODULE_EXT = 15,
 VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT = 16,
 VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT = 17,
 VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT = 18,
 VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT = 19,
 VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT_EXT = 20,
 VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_EXT = 21,
 VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT = 22,
 VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT = 23,
 VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT = 24,
 VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT = 25,
 VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT = 26,
 VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT = 27,
 VK_DEBUG_REPORT_OBJECT_TYPE_DEBUG_REPORT_CALLBACK_EXT_EXT = 28,
 VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_KHR_EXT = 29,
 VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_MODE_KHR_EXT = 30,
 VK_DEBUG_REPORT_OBJECT_TYPE_VALIDATION_CACHE_EXT_EXT = 33,
 VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION_EXT = 1000156000,
 VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_EXT = 1000085000,
 VK_DEBUG_REPORT_OBJECT_TYPE_CU_MODULE_NVX_EXT = 1000029000,
 VK_DEBUG_REPORT_OBJECT_TYPE_CU_FUNCTION_NVX_EXT = 1000029001,
 VK_DEBUG_REPORT_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR_EXT = 1000150000,
 VK_DEBUG_REPORT_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV_EXT = 1000165000,
 VK_DEBUG_REPORT_OBJECT_TYPE_CUDA_MODULE_NV_EXT = 1000307000,
 VK_DEBUG_REPORT_OBJECT_TYPE_CUDA_FUNCTION_NV_EXT = 1000307001,
 VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_COLLECTION_FUCHSIA_EXT = 1000366000,
 VK_DEBUG_REPORT_OBJECT_TYPE_DEBUG_REPORT_EXT = VK_DEBUG_REPORT_OBJECT_TYPE_DEBUG_REPORT_CALLBACK_EXT_EXT,
 VK_DEBUG_REPORT_OBJECT_TYPE_VALIDATION_CACHE_EXT = VK_DEBUG_REPORT_OBJECT_TYPE_VALIDATION_CACHE_EXT_EXT,
 VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_KHR_EXT = VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_EXT,
 VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION_KHR_EXT = VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION_EXT,
 VK_DEBUG_REPORT_OBJECT_TYPE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkDebugReportObjectTypeEXT;

typedef enum VkDebugReportFlagBitsEXT {
 VK_DEBUG_REPORT_INFORMATION_BIT_EXT = 0x00000001,
 VK_DEBUG_REPORT_WARNING_BIT_EXT = 0x00000002,
 VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT = 0x00000004,
 VK_DEBUG_REPORT_ERROR_BIT_EXT = 0x00000008,
 VK_DEBUG_REPORT_DEBUG_BIT_EXT = 0x00000010,
 VK_DEBUG_REPORT_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkDebugReportFlagBitsEXT;
typedef VkFlags VkDebugReportFlagsEXT;
typedef VkBool32 (VKAPI_PTR *PFN_vkDebugReportCallbackEXT)(
 VkDebugReportFlagsEXT flags,
 VkDebugReportObjectTypeEXT objectType,
 uint64_t object,
 size_t location,
 int32_t messageCode,
 const char* pLayerPrefix,
 const char* pMessage,
 void* pUserData);

typedef struct VkDebugReportCallbackCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkDebugReportFlagsEXT flags;
 PFN_vkDebugReportCallbackEXT pfnCallback;
 void* pUserData;
} VkDebugReportCallbackCreateInfoEXT;

typedef VkResult (VKAPI_PTR *PFN_vkCreateDebugReportCallbackEXT)(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);
typedef void (VKAPI_PTR *PFN_vkDestroyDebugReportCallbackEXT)(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);
typedef void (VKAPI_PTR *PFN_vkDebugReportMessageEXT)(VkInstance instance, VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugReportCallbackEXT(
 VkInstance instance,
 const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
 const VkAllocationCallbacks* pAllocator,
 VkDebugReportCallbackEXT* pCallback);

VKAPI_ATTR void VKAPI_CALL vkDestroyDebugReportCallbackEXT(
 VkInstance instance,
 VkDebugReportCallbackEXT callback,
 const VkAllocationCallbacks* pAllocator);

VKAPI_ATTR void VKAPI_CALL vkDebugReportMessageEXT(
 VkInstance instance,
 VkDebugReportFlagsEXT flags,
 VkDebugReportObjectTypeEXT objectType,
 uint64_t object,
 size_t location,
 int32_t messageCode,
 const char* pLayerPrefix,
 const char* pMessage);
#endif

// VK_NV_glsl_shader is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_glsl_shader 1
#define VK_NV_GLSL_SHADER_SPEC_VERSION 1
#define VK_NV_GLSL_SHADER_EXTENSION_NAME "VK_NV_glsl_shader"

// VK_EXT_depth_range_unrestricted is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_depth_range_unrestricted 1
#define VK_EXT_DEPTH_RANGE_UNRESTRICTED_SPEC_VERSION 1
#define VK_EXT_DEPTH_RANGE_UNRESTRICTED_EXTENSION_NAME "VK_EXT_depth_range_unrestricted"

// VK_IMG_filter_cubic is a preprocessor guard. Do not pass it to API calls.
#define VK_IMG_filter_cubic 1
#define VK_IMG_FILTER_CUBIC_SPEC_VERSION 1
#define VK_IMG_FILTER_CUBIC_EXTENSION_NAME "VK_IMG_filter_cubic"

// VK_AMD_rasterization_order is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_rasterization_order 1
#define VK_AMD_RASTERIZATION_ORDER_SPEC_VERSION 1
#define VK_AMD_RASTERIZATION_ORDER_EXTENSION_NAME "VK_AMD_rasterization_order"

typedef enum VkRasterizationOrderAMD {
 VK_RASTERIZATION_ORDER_STRICT_AMD = 0,
 VK_RASTERIZATION_ORDER_RELAXED_AMD = 1,
 VK_RASTERIZATION_ORDER_MAX_ENUM_AMD = 0x7FFFFFFF
} VkRasterizationOrderAMD;
typedef struct VkPipelineRasterizationStateRasterizationOrderAMD {
 VkStructureType sType;
 const void* pNext;
 VkRasterizationOrderAMD rasterizationOrder;
} VkPipelineRasterizationStateRasterizationOrderAMD;

// VK_AMD_shader_trinary_minmax is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_shader_trinary_minmax 1
#define VK_AMD_SHADER_TRINARY_MINMAX_SPEC_VERSION 1
#define VK_AMD_SHADER_TRINARY_MINMAX_EXTENSION_NAME "VK_AMD_shader_trinary_minmax"

// VK_AMD_shader_explicit_vertex_parameter is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_shader_explicit_vertex_parameter 1
#define VK_AMD_SHADER_EXPLICIT_VERTEX_PARAMETER_SPEC_VERSION 1
#define VK_AMD_SHADER_EXPLICIT_VERTEX_PARAMETER_EXTENSION_NAME "VK_AMD_shader_explicit_vertex_parameter"

// VK_EXT_debug_marker is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_debug_marker 1
#define VK_EXT_DEBUG_MARKER_SPEC_VERSION 4
#define VK_EXT_DEBUG_MARKER_EXTENSION_NAME "VK_EXT_debug_marker"
typedef struct VkDebugMarkerObjectNameInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkDebugReportObjectTypeEXT objectType;
 uint64_t object;
 const char* pObjectName;
} VkDebugMarkerObjectNameInfoEXT;

typedef struct VkDebugMarkerObjectTagInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkDebugReportObjectTypeEXT objectType;
 uint64_t object;
 uint64_t tagName;
 size_t tagSize;
 const void* pTag;
} VkDebugMarkerObjectTagInfoEXT;

typedef struct VkDebugMarkerMarkerInfoEXT {
 VkStructureType sType;
 const void* pNext;
 const char* pMarkerName;
 float color[4];
} VkDebugMarkerMarkerInfoEXT;

typedef VkResult (VKAPI_PTR *PFN_vkDebugMarkerSetObjectTagEXT)(VkDevice device, const VkDebugMarkerObjectTagInfoEXT* pTagInfo);
typedef VkResult (VKAPI_PTR *PFN_vkDebugMarkerSetObjectNameEXT)(VkDevice device, const VkDebugMarkerObjectNameInfoEXT* pNameInfo);
typedef void (VKAPI_PTR *PFN_vkCmdDebugMarkerBeginEXT)(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo);
typedef void (VKAPI_PTR *PFN_vkCmdDebugMarkerEndEXT)(VkCommandBuffer commandBuffer);
typedef void (VKAPI_PTR *PFN_vkCmdDebugMarkerInsertEXT)(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkDebugMarkerSetObjectTagEXT(
 VkDevice device,
 const VkDebugMarkerObjectTagInfoEXT* pTagInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkDebugMarkerSetObjectNameEXT(
 VkDevice device,
 const VkDebugMarkerObjectNameInfoEXT* pNameInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdDebugMarkerBeginEXT(
 VkCommandBuffer commandBuffer,
 const VkDebugMarkerMarkerInfoEXT* pMarkerInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdDebugMarkerEndEXT(
 VkCommandBuffer commandBuffer);

VKAPI_ATTR void VKAPI_CALL vkCmdDebugMarkerInsertEXT(
 VkCommandBuffer commandBuffer,
 const VkDebugMarkerMarkerInfoEXT* pMarkerInfo);
#endif

// VK_AMD_gcn_shader is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_gcn_shader 1
#define VK_AMD_GCN_SHADER_SPEC_VERSION 1
#define VK_AMD_GCN_SHADER_EXTENSION_NAME "VK_AMD_gcn_shader"

// VK_NV_dedicated_allocation is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_dedicated_allocation 1
#define VK_NV_DEDICATED_ALLOCATION_SPEC_VERSION 1
#define VK_NV_DEDICATED_ALLOCATION_EXTENSION_NAME "VK_NV_dedicated_allocation"
typedef struct VkDedicatedAllocationImageCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkBool32 dedicatedAllocation;
} VkDedicatedAllocationImageCreateInfoNV;

typedef struct VkDedicatedAllocationBufferCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkBool32 dedicatedAllocation;
} VkDedicatedAllocationBufferCreateInfoNV;

typedef struct VkDedicatedAllocationMemoryAllocateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkImage image;
 VkBuffer buffer;
} VkDedicatedAllocationMemoryAllocateInfoNV;

// VK_EXT_transform_feedback is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_transform_feedback 1
#define VK_EXT_TRANSFORM_FEEDBACK_SPEC_VERSION 1
#define VK_EXT_TRANSFORM_FEEDBACK_EXTENSION_NAME "VK_EXT_transform_feedback"
typedef VkFlags VkPipelineRasterizationStateStreamCreateFlagsEXT;
typedef struct VkPhysicalDeviceTransformFeedbackFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 transformFeedback;
 VkBool32 geometryStreams;
} VkPhysicalDeviceTransformFeedbackFeaturesEXT;

typedef struct VkPhysicalDeviceTransformFeedbackPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 uint32_t maxTransformFeedbackStreams;
 uint32_t maxTransformFeedbackBuffers;
 VkDeviceSize maxTransformFeedbackBufferSize;
 uint32_t maxTransformFeedbackStreamDataSize;
 uint32_t maxTransformFeedbackBufferDataSize;
 uint32_t maxTransformFeedbackBufferDataStride;
 VkBool32 transformFeedbackQueries;
 VkBool32 transformFeedbackStreamsLinesTriangles;
 VkBool32 transformFeedbackRasterizationStreamSelect;
 VkBool32 transformFeedbackDraw;
} VkPhysicalDeviceTransformFeedbackPropertiesEXT;

typedef struct VkPipelineRasterizationStateStreamCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkPipelineRasterizationStateStreamCreateFlagsEXT flags;
 uint32_t rasterizationStream;
} VkPipelineRasterizationStateStreamCreateInfoEXT;

typedef void (VKAPI_PTR *PFN_vkCmdBindTransformFeedbackBuffersEXT)(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes);
typedef void (VKAPI_PTR *PFN_vkCmdBeginTransformFeedbackEXT)(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets);
typedef void (VKAPI_PTR *PFN_vkCmdEndTransformFeedbackEXT)(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets);
typedef void (VKAPI_PTR *PFN_vkCmdBeginQueryIndexedEXT)(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags, uint32_t index);
typedef void (VKAPI_PTR *PFN_vkCmdEndQueryIndexedEXT)(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, uint32_t index);
typedef void (VKAPI_PTR *PFN_vkCmdDrawIndirectByteCountEXT)(VkCommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdBindTransformFeedbackBuffersEXT(
 VkCommandBuffer commandBuffer,
 uint32_t firstBinding,
 uint32_t bindingCount,
 const VkBuffer* pBuffers,
 const VkDeviceSize* pOffsets,
 const VkDeviceSize* pSizes);

VKAPI_ATTR void VKAPI_CALL vkCmdBeginTransformFeedbackEXT(
 VkCommandBuffer commandBuffer,
 uint32_t firstCounterBuffer,
 uint32_t counterBufferCount,
 const VkBuffer* pCounterBuffers,
 const VkDeviceSize* pCounterBufferOffsets);

VKAPI_ATTR void VKAPI_CALL vkCmdEndTransformFeedbackEXT(
 VkCommandBuffer commandBuffer,
 uint32_t firstCounterBuffer,
 uint32_t counterBufferCount,
 const VkBuffer* pCounterBuffers,
 const VkDeviceSize* pCounterBufferOffsets);

VKAPI_ATTR void VKAPI_CALL vkCmdBeginQueryIndexedEXT(
 VkCommandBuffer commandBuffer,
 VkQueryPool queryPool,
 uint32_t query,
 VkQueryControlFlags flags,
 uint32_t index);

VKAPI_ATTR void VKAPI_CALL vkCmdEndQueryIndexedEXT(
 VkCommandBuffer commandBuffer,
 VkQueryPool queryPool,
 uint32_t query,
 uint32_t index);

VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndirectByteCountEXT(
 VkCommandBuffer commandBuffer,
 uint32_t instanceCount,
 uint32_t firstInstance,
 VkBuffer counterBuffer,
 VkDeviceSize counterBufferOffset,
 uint32_t counterOffset,
 uint32_t vertexStride);
#endif

// VK_NVX_binary_import is a preprocessor guard. Do not pass it to API calls.
#define VK_NVX_binary_import 1
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCuModuleNVX)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCuFunctionNVX)
#define VK_NVX_BINARY_IMPORT_SPEC_VERSION 1
#define VK_NVX_BINARY_IMPORT_EXTENSION_NAME "VK_NVX_binary_import"
typedef struct VkCuModuleCreateInfoNVX {
 VkStructureType sType;
 const void* pNext;
 size_t dataSize;
 const void* pData;
} VkCuModuleCreateInfoNVX;

typedef struct VkCuFunctionCreateInfoNVX {
 VkStructureType sType;
 const void* pNext;
 VkCuModuleNVX module;
 const char* pName;
} VkCuFunctionCreateInfoNVX;

typedef struct VkCuLaunchInfoNVX {
 VkStructureType sType;
 const void* pNext;
 VkCuFunctionNVX function;
 uint32_t gridDimX;
 uint32_t gridDimY;
 uint32_t gridDimZ;
 uint32_t blockDimX;
 uint32_t blockDimY;
 uint32_t blockDimZ;
 uint32_t sharedMemBytes;
 size_t paramCount;
 const void* const * pParams;
 size_t extraCount;
 const void* const * pExtras;
} VkCuLaunchInfoNVX;

typedef VkResult (VKAPI_PTR *PFN_vkCreateCuModuleNVX)(VkDevice device, const VkCuModuleCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuModuleNVX* pModule);
typedef VkResult (VKAPI_PTR *PFN_vkCreateCuFunctionNVX)(VkDevice device, const VkCuFunctionCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuFunctionNVX* pFunction);
typedef void (VKAPI_PTR *PFN_vkDestroyCuModuleNVX)(VkDevice device, VkCuModuleNVX module, const VkAllocationCallbacks* pAllocator);
typedef void (VKAPI_PTR *PFN_vkDestroyCuFunctionNVX)(VkDevice device, VkCuFunctionNVX function, const VkAllocationCallbacks* pAllocator);
typedef void (VKAPI_PTR *PFN_vkCmdCuLaunchKernelNVX)(VkCommandBuffer commandBuffer, const VkCuLaunchInfoNVX* pLaunchInfo);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCuModuleNVX(
 VkDevice device,
 const VkCuModuleCreateInfoNVX* pCreateInfo,
 const VkAllocationCallbacks* pAllocator,
 VkCuModuleNVX* pModule);

VKAPI_ATTR VkResult VKAPI_CALL vkCreateCuFunctionNVX(
 VkDevice device,
 const VkCuFunctionCreateInfoNVX* pCreateInfo,
 const VkAllocationCallbacks* pAllocator,
 VkCuFunctionNVX* pFunction);

VKAPI_ATTR void VKAPI_CALL vkDestroyCuModuleNVX(
 VkDevice device,
 VkCuModuleNVX module,
 const VkAllocationCallbacks* pAllocator);

VKAPI_ATTR void VKAPI_CALL vkDestroyCuFunctionNVX(
 VkDevice device,
 VkCuFunctionNVX function,
 const VkAllocationCallbacks* pAllocator);

VKAPI_ATTR void VKAPI_CALL vkCmdCuLaunchKernelNVX(
 VkCommandBuffer commandBuffer,
 const VkCuLaunchInfoNVX* pLaunchInfo);
#endif

// VK_NVX_image_view_handle is a preprocessor guard. Do not pass it to API calls.
#define VK_NVX_image_view_handle 1
#define VK_NVX_IMAGE_VIEW_HANDLE_SPEC_VERSION 2
#define VK_NVX_IMAGE_VIEW_HANDLE_EXTENSION_NAME "VK_NVX_image_view_handle"
typedef struct VkImageViewHandleInfoNVX {
 VkStructureType sType;
 const void* pNext;
 VkImageView imageView;
 VkDescriptorType descriptorType;
 VkSampler sampler;
} VkImageViewHandleInfoNVX;

typedef struct VkImageViewAddressPropertiesNVX {
 VkStructureType sType;
 void* pNext;
 VkDeviceAddress deviceAddress;
 VkDeviceSize size;
} VkImageViewAddressPropertiesNVX;

typedef uint32_t (VKAPI_PTR *PFN_vkGetImageViewHandleNVX)(VkDevice device, const VkImageViewHandleInfoNVX* pInfo);
typedef VkResult (VKAPI_PTR *PFN_vkGetImageViewAddressNVX)(VkDevice device, VkImageView imageView, VkImageViewAddressPropertiesNVX* pProperties);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR uint32_t VKAPI_CALL vkGetImageViewHandleNVX(
 VkDevice device,
 const VkImageViewHandleInfoNVX* pInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkGetImageViewAddressNVX(
 VkDevice device,
 VkImageView imageView,
 VkImageViewAddressPropertiesNVX* pProperties);
#endif

// VK_AMD_draw_indirect_count is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_draw_indirect_count 1
#define VK_AMD_DRAW_INDIRECT_COUNT_SPEC_VERSION 2
#define VK_AMD_DRAW_INDIRECT_COUNT_EXTENSION_NAME "VK_AMD_draw_indirect_count"
typedef void (VKAPI_PTR *PFN_vkCmdDrawIndirectCountAMD)(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride);
typedef void (VKAPI_PTR *PFN_vkCmdDrawIndexedIndirectCountAMD)(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndirectCountAMD(
 VkCommandBuffer commandBuffer,
 VkBuffer buffer,
 VkDeviceSize offset,
 VkBuffer countBuffer,
 VkDeviceSize countBufferOffset,
 uint32_t maxDrawCount,
 uint32_t stride);

VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndexedIndirectCountAMD(
 VkCommandBuffer commandBuffer,
 VkBuffer buffer,
 VkDeviceSize offset,
 VkBuffer countBuffer,
 VkDeviceSize countBufferOffset,
 uint32_t maxDrawCount,
 uint32_t stride);
#endif

// VK_AMD_negative_viewport_height is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_negative_viewport_height 1
#define VK_AMD_NEGATIVE_VIEWPORT_HEIGHT_SPEC_VERSION 1
#define VK_AMD_NEGATIVE_VIEWPORT_HEIGHT_EXTENSION_NAME "VK_AMD_negative_viewport_height"

// VK_AMD_gpu_shader_half_float is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_gpu_shader_half_float 1
#define VK_AMD_GPU_SHADER_HALF_FLOAT_SPEC_VERSION 2
#define VK_AMD_GPU_SHADER_HALF_FLOAT_EXTENSION_NAME "VK_AMD_gpu_shader_half_float"

// VK_AMD_shader_ballot is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_shader_ballot 1
#define VK_AMD_SHADER_BALLOT_SPEC_VERSION 1
#define VK_AMD_SHADER_BALLOT_EXTENSION_NAME "VK_AMD_shader_ballot"

// VK_AMD_texture_gather_bias_lod is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_texture_gather_bias_lod 1
#define VK_AMD_TEXTURE_GATHER_BIAS_LOD_SPEC_VERSION 1
#define VK_AMD_TEXTURE_GATHER_BIAS_LOD_EXTENSION_NAME "VK_AMD_texture_gather_bias_lod"
typedef struct VkTextureLODGatherFormatPropertiesAMD {
 VkStructureType sType;
 void* pNext;
 VkBool32 supportsTextureGatherLODBiasAMD;
} VkTextureLODGatherFormatPropertiesAMD;

// VK_AMD_shader_info is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_shader_info 1
#define VK_AMD_SHADER_INFO_SPEC_VERSION 1
#define VK_AMD_SHADER_INFO_EXTENSION_NAME "VK_AMD_shader_info"

typedef enum VkShaderInfoTypeAMD {
 VK_SHADER_INFO_TYPE_STATISTICS_AMD = 0,
 VK_SHADER_INFO_TYPE_BINARY_AMD = 1,
 VK_SHADER_INFO_TYPE_DISASSEMBLY_AMD = 2,
 VK_SHADER_INFO_TYPE_MAX_ENUM_AMD = 0x7FFFFFFF
} VkShaderInfoTypeAMD;
typedef struct VkShaderResourceUsageAMD {
 uint32_t numUsedVgprs;
 uint32_t numUsedSgprs;
 uint32_t ldsSizePerLocalWorkGroup;
 size_t ldsUsageSizeInBytes;
 size_t scratchMemUsageInBytes;
} VkShaderResourceUsageAMD;

typedef struct VkShaderStatisticsInfoAMD {
 VkShaderStageFlags shaderStageMask;
 VkShaderResourceUsageAMD resourceUsage;
 uint32_t numPhysicalVgprs;
 uint32_t numPhysicalSgprs;
 uint32_t numAvailableVgprs;
 uint32_t numAvailableSgprs;
 uint32_t computeWorkGroupSize[3];
} VkShaderStatisticsInfoAMD;

typedef VkResult (VKAPI_PTR *PFN_vkGetShaderInfoAMD)(VkDevice device, VkPipeline pipeline, VkShaderStageFlagBits shaderStage, VkShaderInfoTypeAMD infoType, size_t* pInfoSize, void* pInfo);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetShaderInfoAMD(
 VkDevice device,
 VkPipeline pipeline,
 VkShaderStageFlagBits shaderStage,
 VkShaderInfoTypeAMD infoType,
 size_t* pInfoSize,
 void* pInfo);
#endif

// VK_AMD_shader_image_load_store_lod is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_shader_image_load_store_lod 1
#define VK_AMD_SHADER_IMAGE_LOAD_STORE_LOD_SPEC_VERSION 1
#define VK_AMD_SHADER_IMAGE_LOAD_STORE_LOD_EXTENSION_NAME "VK_AMD_shader_image_load_store_lod"

// VK_NV_corner_sampled_image is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_corner_sampled_image 1
#define VK_NV_CORNER_SAMPLED_IMAGE_SPEC_VERSION 2
#define VK_NV_CORNER_SAMPLED_IMAGE_EXTENSION_NAME "VK_NV_corner_sampled_image"
typedef struct VkPhysicalDeviceCornerSampledImageFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 cornerSampledImage;
} VkPhysicalDeviceCornerSampledImageFeaturesNV;

// VK_IMG_format_pvrtc is a preprocessor guard. Do not pass it to API calls.
#define VK_IMG_format_pvrtc 1
#define VK_IMG_FORMAT_PVRTC_SPEC_VERSION 1
#define VK_IMG_FORMAT_PVRTC_EXTENSION_NAME "VK_IMG_format_pvrtc"

// VK_NV_external_memory_capabilities is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_external_memory_capabilities 1
#define VK_NV_EXTERNAL_MEMORY_CAPABILITIES_SPEC_VERSION 1
#define VK_NV_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME "VK_NV_external_memory_capabilities"

typedef enum VkExternalMemoryHandleTypeFlagBitsNV {
 VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT_NV = 0x00000001,
 VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT_NV = 0x00000002,
 VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_IMAGE_BIT_NV = 0x00000004,
 VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_IMAGE_KMT_BIT_NV = 0x00000008,
 VK_EXTERNAL_MEMORY_HANDLE_TYPE_FLAG_BITS_MAX_ENUM_NV = 0x7FFFFFFF
} VkExternalMemoryHandleTypeFlagBitsNV;
typedef VkFlags VkExternalMemoryHandleTypeFlagsNV;

typedef enum VkExternalMemoryFeatureFlagBitsNV {
 VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT_NV = 0x00000001,
 VK_EXTERNAL_MEMORY_FEATURE_EXPORTABLE_BIT_NV = 0x00000002,
 VK_EXTERNAL_MEMORY_FEATURE_IMPORTABLE_BIT_NV = 0x00000004,
 VK_EXTERNAL_MEMORY_FEATURE_FLAG_BITS_MAX_ENUM_NV = 0x7FFFFFFF
} VkExternalMemoryFeatureFlagBitsNV;
typedef VkFlags VkExternalMemoryFeatureFlagsNV;
typedef struct VkExternalImageFormatPropertiesNV {
 VkImageFormatProperties imageFormatProperties;
 VkExternalMemoryFeatureFlagsNV externalMemoryFeatures;
 VkExternalMemoryHandleTypeFlagsNV exportFromImportedHandleTypes;
 VkExternalMemoryHandleTypeFlagsNV compatibleHandleTypes;
} VkExternalImageFormatPropertiesNV;

typedef VkResult (VKAPI_PTR *PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV)(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkExternalMemoryHandleTypeFlagsNV externalHandleType, VkExternalImageFormatPropertiesNV* pExternalImageFormatProperties);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceExternalImageFormatPropertiesNV(
 VkPhysicalDevice physicalDevice,
 VkFormat format,
 VkImageType type,
 VkImageTiling tiling,
 VkImageUsageFlags usage,
 VkImageCreateFlags flags,
 VkExternalMemoryHandleTypeFlagsNV externalHandleType,
 VkExternalImageFormatPropertiesNV* pExternalImageFormatProperties);
#endif

// VK_NV_external_memory is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_external_memory 1
#define VK_NV_EXTERNAL_MEMORY_SPEC_VERSION 1
#define VK_NV_EXTERNAL_MEMORY_EXTENSION_NAME "VK_NV_external_memory"
typedef struct VkExternalMemoryImageCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkExternalMemoryHandleTypeFlagsNV handleTypes;
} VkExternalMemoryImageCreateInfoNV;

typedef struct VkExportMemoryAllocateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkExternalMemoryHandleTypeFlagsNV handleTypes;
} VkExportMemoryAllocateInfoNV;

// VK_EXT_validation_flags is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_validation_flags 1
#define VK_EXT_VALIDATION_FLAGS_SPEC_VERSION 3
#define VK_EXT_VALIDATION_FLAGS_EXTENSION_NAME "VK_EXT_validation_flags"

typedef enum VkValidationCheckEXT {
 VK_VALIDATION_CHECK_ALL_EXT = 0,
 VK_VALIDATION_CHECK_SHADERS_EXT = 1,
 VK_VALIDATION_CHECK_MAX_ENUM_EXT = 0x7FFFFFFF
} VkValidationCheckEXT;
typedef struct VkValidationFlagsEXT {
 VkStructureType sType;
 const void* pNext;
 uint32_t disabledValidationCheckCount;
 const VkValidationCheckEXT* pDisabledValidationChecks;
} VkValidationFlagsEXT;

// VK_EXT_shader_subgroup_ballot is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_shader_subgroup_ballot 1
#define VK_EXT_SHADER_SUBGROUP_BALLOT_SPEC_VERSION 1
#define VK_EXT_SHADER_SUBGROUP_BALLOT_EXTENSION_NAME "VK_EXT_shader_subgroup_ballot"

// VK_EXT_shader_subgroup_vote is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_shader_subgroup_vote 1
#define VK_EXT_SHADER_SUBGROUP_VOTE_SPEC_VERSION 1
#define VK_EXT_SHADER_SUBGROUP_VOTE_EXTENSION_NAME "VK_EXT_shader_subgroup_vote"

// VK_EXT_texture_compression_astc_hdr is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_texture_compression_astc_hdr 1
#define VK_EXT_TEXTURE_COMPRESSION_ASTC_HDR_SPEC_VERSION 1
#define VK_EXT_TEXTURE_COMPRESSION_ASTC_HDR_EXTENSION_NAME "VK_EXT_texture_compression_astc_hdr"
typedef VkPhysicalDeviceTextureCompressionASTCHDRFeatures VkPhysicalDeviceTextureCompressionASTCHDRFeaturesEXT;

// VK_EXT_astc_decode_mode is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_astc_decode_mode 1
#define VK_EXT_ASTC_DECODE_MODE_SPEC_VERSION 1
#define VK_EXT_ASTC_DECODE_MODE_EXTENSION_NAME "VK_EXT_astc_decode_mode"
typedef struct VkImageViewASTCDecodeModeEXT {
 VkStructureType sType;
 const void* pNext;
 VkFormat decodeMode;
} VkImageViewASTCDecodeModeEXT;

typedef struct VkPhysicalDeviceASTCDecodeFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 decodeModeSharedExponent;
} VkPhysicalDeviceASTCDecodeFeaturesEXT;

// VK_EXT_pipeline_robustness is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_pipeline_robustness 1
#define VK_EXT_PIPELINE_ROBUSTNESS_SPEC_VERSION 1
#define VK_EXT_PIPELINE_ROBUSTNESS_EXTENSION_NAME "VK_EXT_pipeline_robustness"

typedef enum VkPipelineRobustnessBufferBehaviorEXT {
 VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_DEVICE_DEFAULT_EXT = 0,
 VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_DISABLED_EXT = 1,
 VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_EXT = 2,
 VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_ROBUST_BUFFER_ACCESS_2_EXT = 3,
 VK_PIPELINE_ROBUSTNESS_BUFFER_BEHAVIOR_MAX_ENUM_EXT = 0x7FFFFFFF
} VkPipelineRobustnessBufferBehaviorEXT;

typedef enum VkPipelineRobustnessImageBehaviorEXT {
 VK_PIPELINE_ROBUSTNESS_IMAGE_BEHAVIOR_DEVICE_DEFAULT_EXT = 0,
 VK_PIPELINE_ROBUSTNESS_IMAGE_BEHAVIOR_DISABLED_EXT = 1,
 VK_PIPELINE_ROBUSTNESS_IMAGE_BEHAVIOR_ROBUST_IMAGE_ACCESS_EXT = 2,
 VK_PIPELINE_ROBUSTNESS_IMAGE_BEHAVIOR_ROBUST_IMAGE_ACCESS_2_EXT = 3,
 VK_PIPELINE_ROBUSTNESS_IMAGE_BEHAVIOR_MAX_ENUM_EXT = 0x7FFFFFFF
} VkPipelineRobustnessImageBehaviorEXT;
typedef struct VkPhysicalDevicePipelineRobustnessFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 pipelineRobustness;
} VkPhysicalDevicePipelineRobustnessFeaturesEXT;

typedef struct VkPhysicalDevicePipelineRobustnessPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 VkPipelineRobustnessBufferBehaviorEXT defaultRobustnessStorageBuffers;
 VkPipelineRobustnessBufferBehaviorEXT defaultRobustnessUniformBuffers;
 VkPipelineRobustnessBufferBehaviorEXT defaultRobustnessVertexInputs;
 VkPipelineRobustnessImageBehaviorEXT defaultRobustnessImages;
} VkPhysicalDevicePipelineRobustnessPropertiesEXT;

typedef struct VkPipelineRobustnessCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkPipelineRobustnessBufferBehaviorEXT storageBuffers;
 VkPipelineRobustnessBufferBehaviorEXT uniformBuffers;
 VkPipelineRobustnessBufferBehaviorEXT vertexInputs;
 VkPipelineRobustnessImageBehaviorEXT images;
} VkPipelineRobustnessCreateInfoEXT;

// VK_EXT_conditional_rendering is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_conditional_rendering 1
#define VK_EXT_CONDITIONAL_RENDERING_SPEC_VERSION 2
#define VK_EXT_CONDITIONAL_RENDERING_EXTENSION_NAME "VK_EXT_conditional_rendering"

typedef enum VkConditionalRenderingFlagBitsEXT {
 VK_CONDITIONAL_RENDERING_INVERTED_BIT_EXT = 0x00000001,
 VK_CONDITIONAL_RENDERING_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkConditionalRenderingFlagBitsEXT;
typedef VkFlags VkConditionalRenderingFlagsEXT;
typedef struct VkConditionalRenderingBeginInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkBuffer buffer;
 VkDeviceSize offset;
 VkConditionalRenderingFlagsEXT flags;
} VkConditionalRenderingBeginInfoEXT;

typedef struct VkPhysicalDeviceConditionalRenderingFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 conditionalRendering;
 VkBool32 inheritedConditionalRendering;
} VkPhysicalDeviceConditionalRenderingFeaturesEXT;

typedef struct VkCommandBufferInheritanceConditionalRenderingInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkBool32 conditionalRenderingEnable;
} VkCommandBufferInheritanceConditionalRenderingInfoEXT;

typedef void (VKAPI_PTR *PFN_vkCmdBeginConditionalRenderingEXT)(VkCommandBuffer commandBuffer, const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin);
typedef void (VKAPI_PTR *PFN_vkCmdEndConditionalRenderingEXT)(VkCommandBuffer commandBuffer);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdBeginConditionalRenderingEXT(
 VkCommandBuffer commandBuffer,
 const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin);

VKAPI_ATTR void VKAPI_CALL vkCmdEndConditionalRenderingEXT(
 VkCommandBuffer commandBuffer);
#endif

// VK_NV_clip_space_w_scaling is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_clip_space_w_scaling 1
#define VK_NV_CLIP_SPACE_W_SCALING_SPEC_VERSION 1
#define VK_NV_CLIP_SPACE_W_SCALING_EXTENSION_NAME "VK_NV_clip_space_w_scaling"
typedef struct VkViewportWScalingNV {
 float xcoeff;
 float ycoeff;
} VkViewportWScalingNV;

typedef struct VkPipelineViewportWScalingStateCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkBool32 viewportWScalingEnable;
 uint32_t viewportCount;
 const VkViewportWScalingNV* pViewportWScalings;
} VkPipelineViewportWScalingStateCreateInfoNV;

typedef void (VKAPI_PTR *PFN_vkCmdSetViewportWScalingNV)(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportWScalingNV* pViewportWScalings);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdSetViewportWScalingNV(
 VkCommandBuffer commandBuffer,
 uint32_t firstViewport,
 uint32_t viewportCount,
 const VkViewportWScalingNV* pViewportWScalings);
#endif

// VK_EXT_direct_mode_display is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_direct_mode_display 1
#define VK_EXT_DIRECT_MODE_DISPLAY_SPEC_VERSION 1
#define VK_EXT_DIRECT_MODE_DISPLAY_EXTENSION_NAME "VK_EXT_direct_mode_display"
typedef VkResult (VKAPI_PTR *PFN_vkReleaseDisplayEXT)(VkPhysicalDevice physicalDevice, VkDisplayKHR display);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkReleaseDisplayEXT(
 VkPhysicalDevice physicalDevice,
 VkDisplayKHR display);
#endif

// VK_EXT_display_surface_counter is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_display_surface_counter 1
#define VK_EXT_DISPLAY_SURFACE_COUNTER_SPEC_VERSION 1
#define VK_EXT_DISPLAY_SURFACE_COUNTER_EXTENSION_NAME "VK_EXT_display_surface_counter"

typedef enum VkSurfaceCounterFlagBitsEXT {
 VK_SURFACE_COUNTER_VBLANK_BIT_EXT = 0x00000001,
 VK_SURFACE_COUNTER_VBLANK_EXT = VK_SURFACE_COUNTER_VBLANK_BIT_EXT,
 VK_SURFACE_COUNTER_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkSurfaceCounterFlagBitsEXT;
typedef VkFlags VkSurfaceCounterFlagsEXT;
typedef struct VkSurfaceCapabilities2EXT {
 VkStructureType sType;
 void* pNext;
 uint32_t minImageCount;
 uint32_t maxImageCount;
 VkExtent2D currentExtent;
 VkExtent2D minImageExtent;
 VkExtent2D maxImageExtent;
 uint32_t maxImageArrayLayers;
 VkSurfaceTransformFlagsKHR supportedTransforms;
 VkSurfaceTransformFlagBitsKHR currentTransform;
 VkCompositeAlphaFlagsKHR supportedCompositeAlpha;
 VkImageUsageFlags supportedUsageFlags;
 VkSurfaceCounterFlagsEXT supportedSurfaceCounters;
} VkSurfaceCapabilities2EXT;

typedef VkResult (VKAPI_PTR *PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT)(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilities2EXT* pSurfaceCapabilities);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceCapabilities2EXT(
 VkPhysicalDevice physicalDevice,
 VkSurfaceKHR surface,
 VkSurfaceCapabilities2EXT* pSurfaceCapabilities);
#endif

// VK_EXT_display_control is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_display_control 1
#define VK_EXT_DISPLAY_CONTROL_SPEC_VERSION 1
#define VK_EXT_DISPLAY_CONTROL_EXTENSION_NAME "VK_EXT_display_control"

typedef enum VkDisplayPowerStateEXT {
 VK_DISPLAY_POWER_STATE_OFF_EXT = 0,
 VK_DISPLAY_POWER_STATE_SUSPEND_EXT = 1,
 VK_DISPLAY_POWER_STATE_ON_EXT = 2,
 VK_DISPLAY_POWER_STATE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkDisplayPowerStateEXT;

typedef enum VkDeviceEventTypeEXT {
 VK_DEVICE_EVENT_TYPE_DISPLAY_HOTPLUG_EXT = 0,
 VK_DEVICE_EVENT_TYPE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkDeviceEventTypeEXT;

typedef enum VkDisplayEventTypeEXT {
 VK_DISPLAY_EVENT_TYPE_FIRST_PIXEL_OUT_EXT = 0,
 VK_DISPLAY_EVENT_TYPE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkDisplayEventTypeEXT;
typedef struct VkDisplayPowerInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkDisplayPowerStateEXT powerState;
} VkDisplayPowerInfoEXT;

typedef struct VkDeviceEventInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkDeviceEventTypeEXT deviceEvent;
} VkDeviceEventInfoEXT;

typedef struct VkDisplayEventInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkDisplayEventTypeEXT displayEvent;
} VkDisplayEventInfoEXT;

typedef struct VkSwapchainCounterCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkSurfaceCounterFlagsEXT surfaceCounters;
} VkSwapchainCounterCreateInfoEXT;

typedef VkResult (VKAPI_PTR *PFN_vkDisplayPowerControlEXT)(VkDevice device, VkDisplayKHR display, const VkDisplayPowerInfoEXT* pDisplayPowerInfo);
typedef VkResult (VKAPI_PTR *PFN_vkRegisterDeviceEventEXT)(VkDevice device, const VkDeviceEventInfoEXT* pDeviceEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence);
typedef VkResult (VKAPI_PTR *PFN_vkRegisterDisplayEventEXT)(VkDevice device, VkDisplayKHR display, const VkDisplayEventInfoEXT* pDisplayEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence);
typedef VkResult (VKAPI_PTR *PFN_vkGetSwapchainCounterEXT)(VkDevice device, VkSwapchainKHR swapchain, VkSurfaceCounterFlagBitsEXT counter, uint64_t* pCounterValue);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkDisplayPowerControlEXT(
 VkDevice device,
 VkDisplayKHR display,
 const VkDisplayPowerInfoEXT* pDisplayPowerInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkRegisterDeviceEventEXT(
 VkDevice device,
 const VkDeviceEventInfoEXT* pDeviceEventInfo,
 const VkAllocationCallbacks* pAllocator,
 VkFence* pFence);

VKAPI_ATTR VkResult VKAPI_CALL vkRegisterDisplayEventEXT(
 VkDevice device,
 VkDisplayKHR display,
 const VkDisplayEventInfoEXT* pDisplayEventInfo,
 const VkAllocationCallbacks* pAllocator,
 VkFence* pFence);

VKAPI_ATTR VkResult VKAPI_CALL vkGetSwapchainCounterEXT(
 VkDevice device,
 VkSwapchainKHR swapchain,
 VkSurfaceCounterFlagBitsEXT counter,
 uint64_t* pCounterValue);
#endif

// VK_GOOGLE_display_timing is a preprocessor guard. Do not pass it to API calls.
#define VK_GOOGLE_display_timing 1
#define VK_GOOGLE_DISPLAY_TIMING_SPEC_VERSION 1
#define VK_GOOGLE_DISPLAY_TIMING_EXTENSION_NAME "VK_GOOGLE_display_timing"
typedef struct VkRefreshCycleDurationGOOGLE {
 uint64_t refreshDuration;
} VkRefreshCycleDurationGOOGLE;

typedef struct VkPastPresentationTimingGOOGLE {
 uint32_t presentID;
 uint64_t desiredPresentTime;
 uint64_t actualPresentTime;
 uint64_t earliestPresentTime;
 uint64_t presentMargin;
} VkPastPresentationTimingGOOGLE;

typedef struct VkPresentTimeGOOGLE {
 uint32_t presentID;
 uint64_t desiredPresentTime;
} VkPresentTimeGOOGLE;

typedef struct VkPresentTimesInfoGOOGLE {
 VkStructureType sType;
 const void* pNext;
 uint32_t swapchainCount;
 const VkPresentTimeGOOGLE* pTimes;
} VkPresentTimesInfoGOOGLE;

typedef VkResult (VKAPI_PTR *PFN_vkGetRefreshCycleDurationGOOGLE)(VkDevice device, VkSwapchainKHR swapchain, VkRefreshCycleDurationGOOGLE* pDisplayTimingProperties);
typedef VkResult (VKAPI_PTR *PFN_vkGetPastPresentationTimingGOOGLE)(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pPresentationTimingCount, VkPastPresentationTimingGOOGLE* pPresentationTimings);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetRefreshCycleDurationGOOGLE(
 VkDevice device,
 VkSwapchainKHR swapchain,
 VkRefreshCycleDurationGOOGLE* pDisplayTimingProperties);

VKAPI_ATTR VkResult VKAPI_CALL vkGetPastPresentationTimingGOOGLE(
 VkDevice device,
 VkSwapchainKHR swapchain,
 uint32_t* pPresentationTimingCount,
 VkPastPresentationTimingGOOGLE* pPresentationTimings);
#endif

// VK_NV_sample_mask_override_coverage is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_sample_mask_override_coverage 1
#define VK_NV_SAMPLE_MASK_OVERRIDE_COVERAGE_SPEC_VERSION 1
#define VK_NV_SAMPLE_MASK_OVERRIDE_COVERAGE_EXTENSION_NAME "VK_NV_sample_mask_override_coverage"

// VK_NV_geometry_shader_passthrough is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_geometry_shader_passthrough 1
#define VK_NV_GEOMETRY_SHADER_PASSTHROUGH_SPEC_VERSION 1
#define VK_NV_GEOMETRY_SHADER_PASSTHROUGH_EXTENSION_NAME "VK_NV_geometry_shader_passthrough"

// VK_NV_viewport_array2 is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_viewport_array2 1
#define VK_NV_VIEWPORT_ARRAY_2_SPEC_VERSION 1
#define VK_NV_VIEWPORT_ARRAY_2_EXTENSION_NAME "VK_NV_viewport_array2"
#define VK_NV_VIEWPORT_ARRAY2_SPEC_VERSION VK_NV_VIEWPORT_ARRAY_2_SPEC_VERSION
#define VK_NV_VIEWPORT_ARRAY2_EXTENSION_NAME VK_NV_VIEWPORT_ARRAY_2_EXTENSION_NAME

// VK_NVX_multiview_per_view_attributes is a preprocessor guard. Do not pass it to API calls.
#define VK_NVX_multiview_per_view_attributes 1
#define VK_NVX_MULTIVIEW_PER_VIEW_ATTRIBUTES_SPEC_VERSION 1
#define VK_NVX_MULTIVIEW_PER_VIEW_ATTRIBUTES_EXTENSION_NAME "VK_NVX_multiview_per_view_attributes"
typedef struct VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX {
 VkStructureType sType;
 void* pNext;
 VkBool32 perViewPositionAllComponents;
} VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX;

// VK_NV_viewport_swizzle is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_viewport_swizzle 1
#define VK_NV_VIEWPORT_SWIZZLE_SPEC_VERSION 1
#define VK_NV_VIEWPORT_SWIZZLE_EXTENSION_NAME "VK_NV_viewport_swizzle"

typedef enum VkViewportCoordinateSwizzleNV {
 VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_X_NV = 0,
 VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_X_NV = 1,
 VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_Y_NV = 2,
 VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_Y_NV = 3,
 VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_Z_NV = 4,
 VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_Z_NV = 5,
 VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_W_NV = 6,
 VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_W_NV = 7,
 VK_VIEWPORT_COORDINATE_SWIZZLE_MAX_ENUM_NV = 0x7FFFFFFF
} VkViewportCoordinateSwizzleNV;
typedef VkFlags VkPipelineViewportSwizzleStateCreateFlagsNV;
typedef struct VkViewportSwizzleNV {
 VkViewportCoordinateSwizzleNV x;
 VkViewportCoordinateSwizzleNV y;
 VkViewportCoordinateSwizzleNV z;
 VkViewportCoordinateSwizzleNV w;
} VkViewportSwizzleNV;

typedef struct VkPipelineViewportSwizzleStateCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkPipelineViewportSwizzleStateCreateFlagsNV flags;
 uint32_t viewportCount;
 const VkViewportSwizzleNV* pViewportSwizzles;
} VkPipelineViewportSwizzleStateCreateInfoNV;

// VK_EXT_discard_rectangles is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_discard_rectangles 1
#define VK_EXT_DISCARD_RECTANGLES_SPEC_VERSION 2
#define VK_EXT_DISCARD_RECTANGLES_EXTENSION_NAME "VK_EXT_discard_rectangles"

typedef enum VkDiscardRectangleModeEXT {
 VK_DISCARD_RECTANGLE_MODE_INCLUSIVE_EXT = 0,
 VK_DISCARD_RECTANGLE_MODE_EXCLUSIVE_EXT = 1,
 VK_DISCARD_RECTANGLE_MODE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkDiscardRectangleModeEXT;
typedef VkFlags VkPipelineDiscardRectangleStateCreateFlagsEXT;
typedef struct VkPhysicalDeviceDiscardRectanglePropertiesEXT {
 VkStructureType sType;
 void* pNext;
 uint32_t maxDiscardRectangles;
} VkPhysicalDeviceDiscardRectanglePropertiesEXT;

typedef struct VkPipelineDiscardRectangleStateCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkPipelineDiscardRectangleStateCreateFlagsEXT flags;
 VkDiscardRectangleModeEXT discardRectangleMode;
 uint32_t discardRectangleCount;
 const VkRect2D* pDiscardRectangles;
} VkPipelineDiscardRectangleStateCreateInfoEXT;

typedef void (VKAPI_PTR *PFN_vkCmdSetDiscardRectangleEXT)(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VkRect2D* pDiscardRectangles);
typedef void (VKAPI_PTR *PFN_vkCmdSetDiscardRectangleEnableEXT)(VkCommandBuffer commandBuffer, VkBool32 discardRectangleEnable);
typedef void (VKAPI_PTR *PFN_vkCmdSetDiscardRectangleModeEXT)(VkCommandBuffer commandBuffer, VkDiscardRectangleModeEXT discardRectangleMode);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdSetDiscardRectangleEXT(
 VkCommandBuffer commandBuffer,
 uint32_t firstDiscardRectangle,
 uint32_t discardRectangleCount,
 const VkRect2D* pDiscardRectangles);

VKAPI_ATTR void VKAPI_CALL vkCmdSetDiscardRectangleEnableEXT(
 VkCommandBuffer commandBuffer,
 VkBool32 discardRectangleEnable);

VKAPI_ATTR void VKAPI_CALL vkCmdSetDiscardRectangleModeEXT(
 VkCommandBuffer commandBuffer,
 VkDiscardRectangleModeEXT discardRectangleMode);
#endif

// VK_EXT_conservative_rasterization is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_conservative_rasterization 1
#define VK_EXT_CONSERVATIVE_RASTERIZATION_SPEC_VERSION 1
#define VK_EXT_CONSERVATIVE_RASTERIZATION_EXTENSION_NAME "VK_EXT_conservative_rasterization"

typedef enum VkConservativeRasterizationModeEXT {
 VK_CONSERVATIVE_RASTERIZATION_MODE_DISABLED_EXT = 0,
 VK_CONSERVATIVE_RASTERIZATION_MODE_OVERESTIMATE_EXT = 1,
 VK_CONSERVATIVE_RASTERIZATION_MODE_UNDERESTIMATE_EXT = 2,
 VK_CONSERVATIVE_RASTERIZATION_MODE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkConservativeRasterizationModeEXT;
typedef VkFlags VkPipelineRasterizationConservativeStateCreateFlagsEXT;
typedef struct VkPhysicalDeviceConservativeRasterizationPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 float primitiveOverestimationSize;
 float maxExtraPrimitiveOverestimationSize;
 float extraPrimitiveOverestimationSizeGranularity;
 VkBool32 primitiveUnderestimation;
 VkBool32 conservativePointAndLineRasterization;
 VkBool32 degenerateTrianglesRasterized;
 VkBool32 degenerateLinesRasterized;
 VkBool32 fullyCoveredFragmentShaderInputVariable;
 VkBool32 conservativeRasterizationPostDepthCoverage;
} VkPhysicalDeviceConservativeRasterizationPropertiesEXT;

typedef struct VkPipelineRasterizationConservativeStateCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkPipelineRasterizationConservativeStateCreateFlagsEXT flags;
 VkConservativeRasterizationModeEXT conservativeRasterizationMode;
 float extraPrimitiveOverestimationSize;
} VkPipelineRasterizationConservativeStateCreateInfoEXT;

// VK_EXT_depth_clip_enable is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_depth_clip_enable 1
#define VK_EXT_DEPTH_CLIP_ENABLE_SPEC_VERSION 1
#define VK_EXT_DEPTH_CLIP_ENABLE_EXTENSION_NAME "VK_EXT_depth_clip_enable"
typedef VkFlags VkPipelineRasterizationDepthClipStateCreateFlagsEXT;
typedef struct VkPhysicalDeviceDepthClipEnableFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 depthClipEnable;
} VkPhysicalDeviceDepthClipEnableFeaturesEXT;

typedef struct VkPipelineRasterizationDepthClipStateCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkPipelineRasterizationDepthClipStateCreateFlagsEXT flags;
 VkBool32 depthClipEnable;
} VkPipelineRasterizationDepthClipStateCreateInfoEXT;

// VK_EXT_swapchain_colorspace is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_swapchain_colorspace 1
#define VK_EXT_SWAPCHAIN_COLOR_SPACE_SPEC_VERSION 4
#define VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME "VK_EXT_swapchain_colorspace"

// VK_EXT_hdr_metadata is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_hdr_metadata 1
#define VK_EXT_HDR_METADATA_SPEC_VERSION 2
#define VK_EXT_HDR_METADATA_EXTENSION_NAME "VK_EXT_hdr_metadata"
typedef struct VkXYColorEXT {
 float x;
 float y;
} VkXYColorEXT;

typedef struct VkHdrMetadataEXT {
 VkStructureType sType;
 const void* pNext;
 VkXYColorEXT displayPrimaryRed;
 VkXYColorEXT displayPrimaryGreen;
 VkXYColorEXT displayPrimaryBlue;
 VkXYColorEXT whitePoint;
 float maxLuminance;
 float minLuminance;
 float maxContentLightLevel;
 float maxFrameAverageLightLevel;
} VkHdrMetadataEXT;

typedef void (VKAPI_PTR *PFN_vkSetHdrMetadataEXT)(VkDevice device, uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, const VkHdrMetadataEXT* pMetadata);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkSetHdrMetadataEXT(
 VkDevice device,
 uint32_t swapchainCount,
 const VkSwapchainKHR* pSwapchains,
 const VkHdrMetadataEXT* pMetadata);
#endif

// VK_IMG_relaxed_line_rasterization is a preprocessor guard. Do not pass it to API calls.
#define VK_IMG_relaxed_line_rasterization 1
#define VK_IMG_RELAXED_LINE_RASTERIZATION_SPEC_VERSION 1
#define VK_IMG_RELAXED_LINE_RASTERIZATION_EXTENSION_NAME "VK_IMG_relaxed_line_rasterization"
typedef struct VkPhysicalDeviceRelaxedLineRasterizationFeaturesIMG {
 VkStructureType sType;
 void* pNext;
 VkBool32 relaxedLineRasterization;
} VkPhysicalDeviceRelaxedLineRasterizationFeaturesIMG;

// VK_EXT_external_memory_dma_buf is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_external_memory_dma_buf 1
#define VK_EXT_EXTERNAL_MEMORY_DMA_BUF_SPEC_VERSION 1
#define VK_EXT_EXTERNAL_MEMORY_DMA_BUF_EXTENSION_NAME "VK_EXT_external_memory_dma_buf"

// VK_EXT_queue_family_foreign is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_queue_family_foreign 1
#define VK_EXT_QUEUE_FAMILY_FOREIGN_SPEC_VERSION 1
#define VK_EXT_QUEUE_FAMILY_FOREIGN_EXTENSION_NAME "VK_EXT_queue_family_foreign"
#define VK_QUEUE_FAMILY_FOREIGN_EXT (~2U)

// VK_EXT_debug_utils is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_debug_utils 1
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDebugUtilsMessengerEXT)
#define VK_EXT_DEBUG_UTILS_SPEC_VERSION 2
#define VK_EXT_DEBUG_UTILS_EXTENSION_NAME "VK_EXT_debug_utils"
typedef VkFlags VkDebugUtilsMessengerCallbackDataFlagsEXT;

typedef enum VkDebugUtilsMessageSeverityFlagBitsEXT {
 VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT = 0x00000001,
 VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT = 0x00000010,
 VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT = 0x00000100,
 VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT = 0x00001000,
 VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkDebugUtilsMessageSeverityFlagBitsEXT;

typedef enum VkDebugUtilsMessageTypeFlagBitsEXT {
 VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT = 0x00000001,
 VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT = 0x00000002,
 VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT = 0x00000004,
 VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT = 0x00000008,
 VK_DEBUG_UTILS_MESSAGE_TYPE_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkDebugUtilsMessageTypeFlagBitsEXT;
typedef VkFlags VkDebugUtilsMessageTypeFlagsEXT;
typedef VkFlags VkDebugUtilsMessageSeverityFlagsEXT;
typedef VkFlags VkDebugUtilsMessengerCreateFlagsEXT;
typedef struct VkDebugUtilsLabelEXT {
 VkStructureType sType;
 const void* pNext;
 const char* pLabelName;
 float color[4];
} VkDebugUtilsLabelEXT;

typedef struct VkDebugUtilsObjectNameInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkObjectType objectType;
 uint64_t objectHandle;
 const char* pObjectName;
} VkDebugUtilsObjectNameInfoEXT;

typedef struct VkDebugUtilsMessengerCallbackDataEXT {
 VkStructureType sType;
 const void* pNext;
 VkDebugUtilsMessengerCallbackDataFlagsEXT flags;
 const char* pMessageIdName;
 int32_t messageIdNumber;
 const char* pMessage;
 uint32_t queueLabelCount;
 const VkDebugUtilsLabelEXT* pQueueLabels;
 uint32_t cmdBufLabelCount;
 const VkDebugUtilsLabelEXT* pCmdBufLabels;
 uint32_t objectCount;
 const VkDebugUtilsObjectNameInfoEXT* pObjects;
} VkDebugUtilsMessengerCallbackDataEXT;

typedef VkBool32 (VKAPI_PTR *PFN_vkDebugUtilsMessengerCallbackEXT)(
 VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
 VkDebugUtilsMessageTypeFlagsEXT messageTypes,
 const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
 void* pUserData);

typedef struct VkDebugUtilsMessengerCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkDebugUtilsMessengerCreateFlagsEXT flags;
 VkDebugUtilsMessageSeverityFlagsEXT messageSeverity;
 VkDebugUtilsMessageTypeFlagsEXT messageType;
 PFN_vkDebugUtilsMessengerCallbackEXT pfnUserCallback;
 void* pUserData;
} VkDebugUtilsMessengerCreateInfoEXT;

typedef struct VkDebugUtilsObjectTagInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkObjectType objectType;
 uint64_t objectHandle;
 uint64_t tagName;
 size_t tagSize;
 const void* pTag;
} VkDebugUtilsObjectTagInfoEXT;

typedef VkResult (VKAPI_PTR *PFN_vkSetDebugUtilsObjectNameEXT)(VkDevice device, const VkDebugUtilsObjectNameInfoEXT* pNameInfo);
typedef VkResult (VKAPI_PTR *PFN_vkSetDebugUtilsObjectTagEXT)(VkDevice device, const VkDebugUtilsObjectTagInfoEXT* pTagInfo);
typedef void (VKAPI_PTR *PFN_vkQueueBeginDebugUtilsLabelEXT)(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo);
typedef void (VKAPI_PTR *PFN_vkQueueEndDebugUtilsLabelEXT)(VkQueue queue);
typedef void (VKAPI_PTR *PFN_vkQueueInsertDebugUtilsLabelEXT)(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo);
typedef void (VKAPI_PTR *PFN_vkCmdBeginDebugUtilsLabelEXT)(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo);
typedef void (VKAPI_PTR *PFN_vkCmdEndDebugUtilsLabelEXT)(VkCommandBuffer commandBuffer);
typedef void (VKAPI_PTR *PFN_vkCmdInsertDebugUtilsLabelEXT)(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo);
typedef VkResult (VKAPI_PTR *PFN_vkCreateDebugUtilsMessengerEXT)(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pMessenger);
typedef void (VKAPI_PTR *PFN_vkDestroyDebugUtilsMessengerEXT)(VkInstance instance, VkDebugUtilsMessengerEXT messenger, const VkAllocationCallbacks* pAllocator);
typedef void (VKAPI_PTR *PFN_vkSubmitDebugUtilsMessageEXT)(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkSetDebugUtilsObjectNameEXT(
 VkDevice device,
 const VkDebugUtilsObjectNameInfoEXT* pNameInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkSetDebugUtilsObjectTagEXT(
 VkDevice device,
 const VkDebugUtilsObjectTagInfoEXT* pTagInfo);

VKAPI_ATTR void VKAPI_CALL vkQueueBeginDebugUtilsLabelEXT(
 VkQueue queue,
 const VkDebugUtilsLabelEXT* pLabelInfo);

VKAPI_ATTR void VKAPI_CALL vkQueueEndDebugUtilsLabelEXT(
 VkQueue queue);

VKAPI_ATTR void VKAPI_CALL vkQueueInsertDebugUtilsLabelEXT(
 VkQueue queue,
 const VkDebugUtilsLabelEXT* pLabelInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdBeginDebugUtilsLabelEXT(
 VkCommandBuffer commandBuffer,
 const VkDebugUtilsLabelEXT* pLabelInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdEndDebugUtilsLabelEXT(
 VkCommandBuffer commandBuffer);

VKAPI_ATTR void VKAPI_CALL vkCmdInsertDebugUtilsLabelEXT(
 VkCommandBuffer commandBuffer,
 const VkDebugUtilsLabelEXT* pLabelInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugUtilsMessengerEXT(
 VkInstance instance,
 const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
 const VkAllocationCallbacks* pAllocator,
 VkDebugUtilsMessengerEXT* pMessenger);

VKAPI_ATTR void VKAPI_CALL vkDestroyDebugUtilsMessengerEXT(
 VkInstance instance,
 VkDebugUtilsMessengerEXT messenger,
 const VkAllocationCallbacks* pAllocator);

VKAPI_ATTR void VKAPI_CALL vkSubmitDebugUtilsMessageEXT(
 VkInstance instance,
 VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
 VkDebugUtilsMessageTypeFlagsEXT messageTypes,
 const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData);
#endif

// VK_EXT_sampler_filter_minmax is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_sampler_filter_minmax 1
#define VK_EXT_SAMPLER_FILTER_MINMAX_SPEC_VERSION 2
#define VK_EXT_SAMPLER_FILTER_MINMAX_EXTENSION_NAME "VK_EXT_sampler_filter_minmax"
typedef VkSamplerReductionMode VkSamplerReductionModeEXT;

typedef VkSamplerReductionModeCreateInfo VkSamplerReductionModeCreateInfoEXT;

typedef VkPhysicalDeviceSamplerFilterMinmaxProperties VkPhysicalDeviceSamplerFilterMinmaxPropertiesEXT;

// VK_AMD_gpu_shader_int16 is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_gpu_shader_int16 1
#define VK_AMD_GPU_SHADER_INT16_SPEC_VERSION 2
#define VK_AMD_GPU_SHADER_INT16_EXTENSION_NAME "VK_AMD_gpu_shader_int16"

// VK_AMD_mixed_attachment_samples is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_mixed_attachment_samples 1
#define VK_AMD_MIXED_ATTACHMENT_SAMPLES_SPEC_VERSION 1
#define VK_AMD_MIXED_ATTACHMENT_SAMPLES_EXTENSION_NAME "VK_AMD_mixed_attachment_samples"

// VK_AMD_shader_fragment_mask is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_shader_fragment_mask 1
#define VK_AMD_SHADER_FRAGMENT_MASK_SPEC_VERSION 1
#define VK_AMD_SHADER_FRAGMENT_MASK_EXTENSION_NAME "VK_AMD_shader_fragment_mask"

// VK_EXT_inline_uniform_block is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_inline_uniform_block 1
#define VK_EXT_INLINE_UNIFORM_BLOCK_SPEC_VERSION 1
#define VK_EXT_INLINE_UNIFORM_BLOCK_EXTENSION_NAME "VK_EXT_inline_uniform_block"
typedef VkPhysicalDeviceInlineUniformBlockFeatures VkPhysicalDeviceInlineUniformBlockFeaturesEXT;

typedef VkPhysicalDeviceInlineUniformBlockProperties VkPhysicalDeviceInlineUniformBlockPropertiesEXT;

typedef VkWriteDescriptorSetInlineUniformBlock VkWriteDescriptorSetInlineUniformBlockEXT;

typedef VkDescriptorPoolInlineUniformBlockCreateInfo VkDescriptorPoolInlineUniformBlockCreateInfoEXT;

// VK_EXT_shader_stencil_export is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_shader_stencil_export 1
#define VK_EXT_SHADER_STENCIL_EXPORT_SPEC_VERSION 1
#define VK_EXT_SHADER_STENCIL_EXPORT_EXTENSION_NAME "VK_EXT_shader_stencil_export"

// VK_EXT_sample_locations is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_sample_locations 1
#define VK_EXT_SAMPLE_LOCATIONS_SPEC_VERSION 1
#define VK_EXT_SAMPLE_LOCATIONS_EXTENSION_NAME "VK_EXT_sample_locations"
typedef struct VkSampleLocationEXT {
 float x;
 float y;
} VkSampleLocationEXT;

typedef struct VkSampleLocationsInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkSampleCountFlagBits sampleLocationsPerPixel;
 VkExtent2D sampleLocationGridSize;
 uint32_t sampleLocationsCount;
 const VkSampleLocationEXT* pSampleLocations;
} VkSampleLocationsInfoEXT;

typedef struct VkAttachmentSampleLocationsEXT {
 uint32_t attachmentIndex;
 VkSampleLocationsInfoEXT sampleLocationsInfo;
} VkAttachmentSampleLocationsEXT;

typedef struct VkSubpassSampleLocationsEXT {
 uint32_t subpassIndex;
 VkSampleLocationsInfoEXT sampleLocationsInfo;
} VkSubpassSampleLocationsEXT;

typedef struct VkRenderPassSampleLocationsBeginInfoEXT {
 VkStructureType sType;
 const void* pNext;
 uint32_t attachmentInitialSampleLocationsCount;
 const VkAttachmentSampleLocationsEXT* pAttachmentInitialSampleLocations;
 uint32_t postSubpassSampleLocationsCount;
 const VkSubpassSampleLocationsEXT* pPostSubpassSampleLocations;
} VkRenderPassSampleLocationsBeginInfoEXT;

typedef struct VkPipelineSampleLocationsStateCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkBool32 sampleLocationsEnable;
 VkSampleLocationsInfoEXT sampleLocationsInfo;
} VkPipelineSampleLocationsStateCreateInfoEXT;

typedef struct VkPhysicalDeviceSampleLocationsPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 VkSampleCountFlags sampleLocationSampleCounts;
 VkExtent2D maxSampleLocationGridSize;
 float sampleLocationCoordinateRange[2];
 uint32_t sampleLocationSubPixelBits;
 VkBool32 variableSampleLocations;
} VkPhysicalDeviceSampleLocationsPropertiesEXT;

typedef struct VkMultisamplePropertiesEXT {
 VkStructureType sType;
 void* pNext;
 VkExtent2D maxSampleLocationGridSize;
} VkMultisamplePropertiesEXT;

typedef void (VKAPI_PTR *PFN_vkCmdSetSampleLocationsEXT)(VkCommandBuffer commandBuffer, const VkSampleLocationsInfoEXT* pSampleLocationsInfo);
typedef void (VKAPI_PTR *PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT)(VkPhysicalDevice physicalDevice, VkSampleCountFlagBits samples, VkMultisamplePropertiesEXT* pMultisampleProperties);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdSetSampleLocationsEXT(
 VkCommandBuffer commandBuffer,
 const VkSampleLocationsInfoEXT* pSampleLocationsInfo);

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceMultisamplePropertiesEXT(
 VkPhysicalDevice physicalDevice,
 VkSampleCountFlagBits samples,
 VkMultisamplePropertiesEXT* pMultisampleProperties);
#endif

// VK_EXT_blend_operation_advanced is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_blend_operation_advanced 1
#define VK_EXT_BLEND_OPERATION_ADVANCED_SPEC_VERSION 2
#define VK_EXT_BLEND_OPERATION_ADVANCED_EXTENSION_NAME "VK_EXT_blend_operation_advanced"

typedef enum VkBlendOverlapEXT {
 VK_BLEND_OVERLAP_UNCORRELATED_EXT = 0,
 VK_BLEND_OVERLAP_DISJOINT_EXT = 1,
 VK_BLEND_OVERLAP_CONJOINT_EXT = 2,
 VK_BLEND_OVERLAP_MAX_ENUM_EXT = 0x7FFFFFFF
} VkBlendOverlapEXT;
typedef struct VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 advancedBlendCoherentOperations;
} VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT;

typedef struct VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 uint32_t advancedBlendMaxColorAttachments;
 VkBool32 advancedBlendIndependentBlend;
 VkBool32 advancedBlendNonPremultipliedSrcColor;
 VkBool32 advancedBlendNonPremultipliedDstColor;
 VkBool32 advancedBlendCorrelatedOverlap;
 VkBool32 advancedBlendAllOperations;
} VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT;

typedef struct VkPipelineColorBlendAdvancedStateCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkBool32 srcPremultiplied;
 VkBool32 dstPremultiplied;
 VkBlendOverlapEXT blendOverlap;
} VkPipelineColorBlendAdvancedStateCreateInfoEXT;

// VK_NV_fragment_coverage_to_color is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_fragment_coverage_to_color 1
#define VK_NV_FRAGMENT_COVERAGE_TO_COLOR_SPEC_VERSION 1
#define VK_NV_FRAGMENT_COVERAGE_TO_COLOR_EXTENSION_NAME "VK_NV_fragment_coverage_to_color"
typedef VkFlags VkPipelineCoverageToColorStateCreateFlagsNV;
typedef struct VkPipelineCoverageToColorStateCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkPipelineCoverageToColorStateCreateFlagsNV flags;
 VkBool32 coverageToColorEnable;
 uint32_t coverageToColorLocation;
} VkPipelineCoverageToColorStateCreateInfoNV;

// VK_NV_framebuffer_mixed_samples is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_framebuffer_mixed_samples 1
#define VK_NV_FRAMEBUFFER_MIXED_SAMPLES_SPEC_VERSION 1
#define VK_NV_FRAMEBUFFER_MIXED_SAMPLES_EXTENSION_NAME "VK_NV_framebuffer_mixed_samples"

typedef enum VkCoverageModulationModeNV {
 VK_COVERAGE_MODULATION_MODE_NONE_NV = 0,
 VK_COVERAGE_MODULATION_MODE_RGB_NV = 1,
 VK_COVERAGE_MODULATION_MODE_ALPHA_NV = 2,
 VK_COVERAGE_MODULATION_MODE_RGBA_NV = 3,
 VK_COVERAGE_MODULATION_MODE_MAX_ENUM_NV = 0x7FFFFFFF
} VkCoverageModulationModeNV;
typedef VkFlags VkPipelineCoverageModulationStateCreateFlagsNV;
typedef struct VkPipelineCoverageModulationStateCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkPipelineCoverageModulationStateCreateFlagsNV flags;
 VkCoverageModulationModeNV coverageModulationMode;
 VkBool32 coverageModulationTableEnable;
 uint32_t coverageModulationTableCount;
 const float* pCoverageModulationTable;
} VkPipelineCoverageModulationStateCreateInfoNV;

// VK_NV_fill_rectangle is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_fill_rectangle 1
#define VK_NV_FILL_RECTANGLE_SPEC_VERSION 1
#define VK_NV_FILL_RECTANGLE_EXTENSION_NAME "VK_NV_fill_rectangle"

// VK_NV_shader_sm_builtins is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_shader_sm_builtins 1
#define VK_NV_SHADER_SM_BUILTINS_SPEC_VERSION 1
#define VK_NV_SHADER_SM_BUILTINS_EXTENSION_NAME "VK_NV_shader_sm_builtins"
typedef struct VkPhysicalDeviceShaderSMBuiltinsPropertiesNV {
 VkStructureType sType;
 void* pNext;
 uint32_t shaderSMCount;
 uint32_t shaderWarpsPerSM;
} VkPhysicalDeviceShaderSMBuiltinsPropertiesNV;

typedef struct VkPhysicalDeviceShaderSMBuiltinsFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 shaderSMBuiltins;
} VkPhysicalDeviceShaderSMBuiltinsFeaturesNV;

// VK_EXT_post_depth_coverage is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_post_depth_coverage 1
#define VK_EXT_POST_DEPTH_COVERAGE_SPEC_VERSION 1
#define VK_EXT_POST_DEPTH_COVERAGE_EXTENSION_NAME "VK_EXT_post_depth_coverage"

// VK_EXT_image_drm_format_modifier is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_image_drm_format_modifier 1
#define VK_EXT_IMAGE_DRM_FORMAT_MODIFIER_SPEC_VERSION 2
#define VK_EXT_IMAGE_DRM_FORMAT_MODIFIER_EXTENSION_NAME "VK_EXT_image_drm_format_modifier"
typedef struct VkDrmFormatModifierPropertiesEXT {
 uint64_t drmFormatModifier;
 uint32_t drmFormatModifierPlaneCount;
 VkFormatFeatureFlags drmFormatModifierTilingFeatures;
} VkDrmFormatModifierPropertiesEXT;

typedef struct VkDrmFormatModifierPropertiesListEXT {
 VkStructureType sType;
 void* pNext;
 uint32_t drmFormatModifierCount;
 VkDrmFormatModifierPropertiesEXT* pDrmFormatModifierProperties;
} VkDrmFormatModifierPropertiesListEXT;

typedef struct VkPhysicalDeviceImageDrmFormatModifierInfoEXT {
 VkStructureType sType;
 const void* pNext;
 uint64_t drmFormatModifier;
 VkSharingMode sharingMode;
 uint32_t queueFamilyIndexCount;
 const uint32_t* pQueueFamilyIndices;
} VkPhysicalDeviceImageDrmFormatModifierInfoEXT;

typedef struct VkImageDrmFormatModifierListCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 uint32_t drmFormatModifierCount;
 const uint64_t* pDrmFormatModifiers;
} VkImageDrmFormatModifierListCreateInfoEXT;

typedef struct VkImageDrmFormatModifierExplicitCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 uint64_t drmFormatModifier;
 uint32_t drmFormatModifierPlaneCount;
 const VkSubresourceLayout* pPlaneLayouts;
} VkImageDrmFormatModifierExplicitCreateInfoEXT;

typedef struct VkImageDrmFormatModifierPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 uint64_t drmFormatModifier;
} VkImageDrmFormatModifierPropertiesEXT;

typedef struct VkDrmFormatModifierProperties2EXT {
 uint64_t drmFormatModifier;
 uint32_t drmFormatModifierPlaneCount;
 VkFormatFeatureFlags2 drmFormatModifierTilingFeatures;
} VkDrmFormatModifierProperties2EXT;

typedef struct VkDrmFormatModifierPropertiesList2EXT {
 VkStructureType sType;
 void* pNext;
 uint32_t drmFormatModifierCount;
 VkDrmFormatModifierProperties2EXT* pDrmFormatModifierProperties;
} VkDrmFormatModifierPropertiesList2EXT;

typedef VkResult (VKAPI_PTR *PFN_vkGetImageDrmFormatModifierPropertiesEXT)(VkDevice device, VkImage image, VkImageDrmFormatModifierPropertiesEXT* pProperties);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetImageDrmFormatModifierPropertiesEXT(
 VkDevice device,
 VkImage image,
 VkImageDrmFormatModifierPropertiesEXT* pProperties);
#endif

// VK_EXT_validation_cache is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_validation_cache 1
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkValidationCacheEXT)
#define VK_EXT_VALIDATION_CACHE_SPEC_VERSION 1
#define VK_EXT_VALIDATION_CACHE_EXTENSION_NAME "VK_EXT_validation_cache"

typedef enum VkValidationCacheHeaderVersionEXT {
 VK_VALIDATION_CACHE_HEADER_VERSION_ONE_EXT = 1,
 VK_VALIDATION_CACHE_HEADER_VERSION_MAX_ENUM_EXT = 0x7FFFFFFF
} VkValidationCacheHeaderVersionEXT;
typedef VkFlags VkValidationCacheCreateFlagsEXT;
typedef struct VkValidationCacheCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkValidationCacheCreateFlagsEXT flags;
 size_t initialDataSize;
 const void* pInitialData;
} VkValidationCacheCreateInfoEXT;

typedef struct VkShaderModuleValidationCacheCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkValidationCacheEXT validationCache;
} VkShaderModuleValidationCacheCreateInfoEXT;

typedef VkResult (VKAPI_PTR *PFN_vkCreateValidationCacheEXT)(VkDevice device, const VkValidationCacheCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkValidationCacheEXT* pValidationCache);
typedef void (VKAPI_PTR *PFN_vkDestroyValidationCacheEXT)(VkDevice device, VkValidationCacheEXT validationCache, const VkAllocationCallbacks* pAllocator);
typedef VkResult (VKAPI_PTR *PFN_vkMergeValidationCachesEXT)(VkDevice device, VkValidationCacheEXT dstCache, uint32_t srcCacheCount, const VkValidationCacheEXT* pSrcCaches);
typedef VkResult (VKAPI_PTR *PFN_vkGetValidationCacheDataEXT)(VkDevice device, VkValidationCacheEXT validationCache, size_t* pDataSize, void* pData);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateValidationCacheEXT(
 VkDevice device,
 const VkValidationCacheCreateInfoEXT* pCreateInfo,
 const VkAllocationCallbacks* pAllocator,
 VkValidationCacheEXT* pValidationCache);

VKAPI_ATTR void VKAPI_CALL vkDestroyValidationCacheEXT(
 VkDevice device,
 VkValidationCacheEXT validationCache,
 const VkAllocationCallbacks* pAllocator);

VKAPI_ATTR VkResult VKAPI_CALL vkMergeValidationCachesEXT(
 VkDevice device,
 VkValidationCacheEXT dstCache,
 uint32_t srcCacheCount,
 const VkValidationCacheEXT* pSrcCaches);

VKAPI_ATTR VkResult VKAPI_CALL vkGetValidationCacheDataEXT(
 VkDevice device,
 VkValidationCacheEXT validationCache,
 size_t* pDataSize,
 void* pData);
#endif

// VK_EXT_descriptor_indexing is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_descriptor_indexing 1
#define VK_EXT_DESCRIPTOR_INDEXING_SPEC_VERSION 2
#define VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME "VK_EXT_descriptor_indexing"
typedef VkDescriptorBindingFlagBits VkDescriptorBindingFlagBitsEXT;

typedef VkDescriptorBindingFlags VkDescriptorBindingFlagsEXT;

typedef VkDescriptorSetLayoutBindingFlagsCreateInfo VkDescriptorSetLayoutBindingFlagsCreateInfoEXT;

typedef VkPhysicalDeviceDescriptorIndexingFeatures VkPhysicalDeviceDescriptorIndexingFeaturesEXT;

typedef VkPhysicalDeviceDescriptorIndexingProperties VkPhysicalDeviceDescriptorIndexingPropertiesEXT;

typedef VkDescriptorSetVariableDescriptorCountAllocateInfo VkDescriptorSetVariableDescriptorCountAllocateInfoEXT;

typedef VkDescriptorSetVariableDescriptorCountLayoutSupport VkDescriptorSetVariableDescriptorCountLayoutSupportEXT;

// VK_EXT_shader_viewport_index_layer is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_shader_viewport_index_layer 1
#define VK_EXT_SHADER_VIEWPORT_INDEX_LAYER_SPEC_VERSION 1
#define VK_EXT_SHADER_VIEWPORT_INDEX_LAYER_EXTENSION_NAME "VK_EXT_shader_viewport_index_layer"

// VK_NV_shading_rate_image is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_shading_rate_image 1
#define VK_NV_SHADING_RATE_IMAGE_SPEC_VERSION 3
#define VK_NV_SHADING_RATE_IMAGE_EXTENSION_NAME "VK_NV_shading_rate_image"

typedef enum VkShadingRatePaletteEntryNV {
 VK_SHADING_RATE_PALETTE_ENTRY_NO_INVOCATIONS_NV = 0,
 VK_SHADING_RATE_PALETTE_ENTRY_16_INVOCATIONS_PER_PIXEL_NV = 1,
 VK_SHADING_RATE_PALETTE_ENTRY_8_INVOCATIONS_PER_PIXEL_NV = 2,
 VK_SHADING_RATE_PALETTE_ENTRY_4_INVOCATIONS_PER_PIXEL_NV = 3,
 VK_SHADING_RATE_PALETTE_ENTRY_2_INVOCATIONS_PER_PIXEL_NV = 4,
 VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_PIXEL_NV = 5,
 VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_2X1_PIXELS_NV = 6,
 VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_1X2_PIXELS_NV = 7,
 VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_2X2_PIXELS_NV = 8,
 VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_4X2_PIXELS_NV = 9,
 VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_2X4_PIXELS_NV = 10,
 VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_4X4_PIXELS_NV = 11,
 VK_SHADING_RATE_PALETTE_ENTRY_MAX_ENUM_NV = 0x7FFFFFFF
} VkShadingRatePaletteEntryNV;

typedef enum VkCoarseSampleOrderTypeNV {
 VK_COARSE_SAMPLE_ORDER_TYPE_DEFAULT_NV = 0,
 VK_COARSE_SAMPLE_ORDER_TYPE_CUSTOM_NV = 1,
 VK_COARSE_SAMPLE_ORDER_TYPE_PIXEL_MAJOR_NV = 2,
 VK_COARSE_SAMPLE_ORDER_TYPE_SAMPLE_MAJOR_NV = 3,
 VK_COARSE_SAMPLE_ORDER_TYPE_MAX_ENUM_NV = 0x7FFFFFFF
} VkCoarseSampleOrderTypeNV;
typedef struct VkShadingRatePaletteNV {
 uint32_t shadingRatePaletteEntryCount;
 const VkShadingRatePaletteEntryNV* pShadingRatePaletteEntries;
} VkShadingRatePaletteNV;

typedef struct VkPipelineViewportShadingRateImageStateCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkBool32 shadingRateImageEnable;
 uint32_t viewportCount;
 const VkShadingRatePaletteNV* pShadingRatePalettes;
} VkPipelineViewportShadingRateImageStateCreateInfoNV;

typedef struct VkPhysicalDeviceShadingRateImageFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 shadingRateImage;
 VkBool32 shadingRateCoarseSampleOrder;
} VkPhysicalDeviceShadingRateImageFeaturesNV;

typedef struct VkPhysicalDeviceShadingRateImagePropertiesNV {
 VkStructureType sType;
 void* pNext;
 VkExtent2D shadingRateTexelSize;
 uint32_t shadingRatePaletteSize;
 uint32_t shadingRateMaxCoarseSamples;
} VkPhysicalDeviceShadingRateImagePropertiesNV;

typedef struct VkCoarseSampleLocationNV {
 uint32_t pixelX;
 uint32_t pixelY;
 uint32_t sample;
} VkCoarseSampleLocationNV;

typedef struct VkCoarseSampleOrderCustomNV {
 VkShadingRatePaletteEntryNV shadingRate;
 uint32_t sampleCount;
 uint32_t sampleLocationCount;
 const VkCoarseSampleLocationNV* pSampleLocations;
} VkCoarseSampleOrderCustomNV;

typedef struct VkPipelineViewportCoarseSampleOrderStateCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkCoarseSampleOrderTypeNV sampleOrderType;
 uint32_t customSampleOrderCount;
 const VkCoarseSampleOrderCustomNV* pCustomSampleOrders;
} VkPipelineViewportCoarseSampleOrderStateCreateInfoNV;

typedef void (VKAPI_PTR *PFN_vkCmdBindShadingRateImageNV)(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout);
typedef void (VKAPI_PTR *PFN_vkCmdSetViewportShadingRatePaletteNV)(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkShadingRatePaletteNV* pShadingRatePalettes);
typedef void (VKAPI_PTR *PFN_vkCmdSetCoarseSampleOrderNV)(VkCommandBuffer commandBuffer, VkCoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const VkCoarseSampleOrderCustomNV* pCustomSampleOrders);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdBindShadingRateImageNV(
 VkCommandBuffer commandBuffer,
 VkImageView imageView,
 VkImageLayout imageLayout);

VKAPI_ATTR void VKAPI_CALL vkCmdSetViewportShadingRatePaletteNV(
 VkCommandBuffer commandBuffer,
 uint32_t firstViewport,
 uint32_t viewportCount,
 const VkShadingRatePaletteNV* pShadingRatePalettes);

VKAPI_ATTR void VKAPI_CALL vkCmdSetCoarseSampleOrderNV(
 VkCommandBuffer commandBuffer,
 VkCoarseSampleOrderTypeNV sampleOrderType,
 uint32_t customSampleOrderCount,
 const VkCoarseSampleOrderCustomNV* pCustomSampleOrders);
#endif

// VK_NV_ray_tracing is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_ray_tracing 1
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkAccelerationStructureNV)
#define VK_NV_RAY_TRACING_SPEC_VERSION 3
#define VK_NV_RAY_TRACING_EXTENSION_NAME "VK_NV_ray_tracing"
#define VK_SHADER_UNUSED_KHR (~0U)
#define VK_SHADER_UNUSED_NV VK_SHADER_UNUSED_KHR

typedef enum VkRayTracingShaderGroupTypeKHR {
 VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_KHR = 0,
 VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_KHR = 1,
 VK_RAY_TRACING_SHADER_GROUP_TYPE_PROCEDURAL_HIT_GROUP_KHR = 2,
 VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_NV = VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_KHR,
 VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_NV = VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_KHR,
 VK_RAY_TRACING_SHADER_GROUP_TYPE_PROCEDURAL_HIT_GROUP_NV = VK_RAY_TRACING_SHADER_GROUP_TYPE_PROCEDURAL_HIT_GROUP_KHR,
 VK_RAY_TRACING_SHADER_GROUP_TYPE_MAX_ENUM_KHR = 0x7FFFFFFF
} VkRayTracingShaderGroupTypeKHR;
typedef VkRayTracingShaderGroupTypeKHR VkRayTracingShaderGroupTypeNV;

typedef enum VkGeometryTypeKHR {
 VK_GEOMETRY_TYPE_TRIANGLES_KHR = 0,
 VK_GEOMETRY_TYPE_AABBS_KHR = 1,
 VK_GEOMETRY_TYPE_INSTANCES_KHR = 2,
 VK_GEOMETRY_TYPE_TRIANGLES_NV = VK_GEOMETRY_TYPE_TRIANGLES_KHR,
 VK_GEOMETRY_TYPE_AABBS_NV = VK_GEOMETRY_TYPE_AABBS_KHR,
 VK_GEOMETRY_TYPE_MAX_ENUM_KHR = 0x7FFFFFFF
} VkGeometryTypeKHR;
typedef VkGeometryTypeKHR VkGeometryTypeNV;

typedef enum VkAccelerationStructureTypeKHR {
 VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR = 0,
 VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR = 1,
 VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR = 2,
 VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_NV = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR,
 VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_NV = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
 VK_ACCELERATION_STRUCTURE_TYPE_MAX_ENUM_KHR = 0x7FFFFFFF
} VkAccelerationStructureTypeKHR;
typedef VkAccelerationStructureTypeKHR VkAccelerationStructureTypeNV;

typedef enum VkCopyAccelerationStructureModeKHR {
 VK_COPY_ACCELERATION_STRUCTURE_MODE_CLONE_KHR = 0,
 VK_COPY_ACCELERATION_STRUCTURE_MODE_COMPACT_KHR = 1,
 VK_COPY_ACCELERATION_STRUCTURE_MODE_SERIALIZE_KHR = 2,
 VK_COPY_ACCELERATION_STRUCTURE_MODE_DESERIALIZE_KHR = 3,
 VK_COPY_ACCELERATION_STRUCTURE_MODE_CLONE_NV = VK_COPY_ACCELERATION_STRUCTURE_MODE_CLONE_KHR,
 VK_COPY_ACCELERATION_STRUCTURE_MODE_COMPACT_NV = VK_COPY_ACCELERATION_STRUCTURE_MODE_COMPACT_KHR,
 VK_COPY_ACCELERATION_STRUCTURE_MODE_MAX_ENUM_KHR = 0x7FFFFFFF
} VkCopyAccelerationStructureModeKHR;
typedef VkCopyAccelerationStructureModeKHR VkCopyAccelerationStructureModeNV;

typedef enum VkAccelerationStructureMemoryRequirementsTypeNV {
 VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_OBJECT_NV = 0,
 VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_BUILD_SCRATCH_NV = 1,
 VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_UPDATE_SCRATCH_NV = 2,
 VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_MAX_ENUM_NV = 0x7FFFFFFF
} VkAccelerationStructureMemoryRequirementsTypeNV;

typedef enum VkGeometryFlagBitsKHR {
 VK_GEOMETRY_OPAQUE_BIT_KHR = 0x00000001,
 VK_GEOMETRY_NO_DUPLICATE_ANY_HIT_INVOCATION_BIT_KHR = 0x00000002,
 VK_GEOMETRY_OPAQUE_BIT_NV = VK_GEOMETRY_OPAQUE_BIT_KHR,
 VK_GEOMETRY_NO_DUPLICATE_ANY_HIT_INVOCATION_BIT_NV = VK_GEOMETRY_NO_DUPLICATE_ANY_HIT_INVOCATION_BIT_KHR,
 VK_GEOMETRY_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkGeometryFlagBitsKHR;
typedef VkFlags VkGeometryFlagsKHR;
typedef VkGeometryFlagsKHR VkGeometryFlagsNV;

typedef VkGeometryFlagBitsKHR VkGeometryFlagBitsNV;

typedef enum VkGeometryInstanceFlagBitsKHR {
 VK_GEOMETRY_INSTANCE_TRIANGLE_FACING_CULL_DISABLE_BIT_KHR = 0x00000001,
 VK_GEOMETRY_INSTANCE_TRIANGLE_FLIP_FACING_BIT_KHR = 0x00000002,
 VK_GEOMETRY_INSTANCE_FORCE_OPAQUE_BIT_KHR = 0x00000004,
 VK_GEOMETRY_INSTANCE_FORCE_NO_OPAQUE_BIT_KHR = 0x00000008,
 VK_GEOMETRY_INSTANCE_FORCE_OPACITY_MICROMAP_2_STATE_EXT = 0x00000010,
 VK_GEOMETRY_INSTANCE_DISABLE_OPACITY_MICROMAPS_EXT = 0x00000020,
 VK_GEOMETRY_INSTANCE_TRIANGLE_FRONT_COUNTERCLOCKWISE_BIT_KHR = VK_GEOMETRY_INSTANCE_TRIANGLE_FLIP_FACING_BIT_KHR,
 VK_GEOMETRY_INSTANCE_TRIANGLE_CULL_DISABLE_BIT_NV = VK_GEOMETRY_INSTANCE_TRIANGLE_FACING_CULL_DISABLE_BIT_KHR,
 VK_GEOMETRY_INSTANCE_TRIANGLE_FRONT_COUNTERCLOCKWISE_BIT_NV = VK_GEOMETRY_INSTANCE_TRIANGLE_FRONT_COUNTERCLOCKWISE_BIT_KHR,
 VK_GEOMETRY_INSTANCE_FORCE_OPAQUE_BIT_NV = VK_GEOMETRY_INSTANCE_FORCE_OPAQUE_BIT_KHR,
 VK_GEOMETRY_INSTANCE_FORCE_NO_OPAQUE_BIT_NV = VK_GEOMETRY_INSTANCE_FORCE_NO_OPAQUE_BIT_KHR,
 VK_GEOMETRY_INSTANCE_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkGeometryInstanceFlagBitsKHR;
typedef VkFlags VkGeometryInstanceFlagsKHR;
typedef VkGeometryInstanceFlagsKHR VkGeometryInstanceFlagsNV;

typedef VkGeometryInstanceFlagBitsKHR VkGeometryInstanceFlagBitsNV;

typedef enum VkBuildAccelerationStructureFlagBitsKHR {
 VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR = 0x00000001,
 VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR = 0x00000002,
 VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR = 0x00000004,
 VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_KHR = 0x00000008,
 VK_BUILD_ACCELERATION_STRUCTURE_LOW_MEMORY_BIT_KHR = 0x00000010,
 VK_BUILD_ACCELERATION_STRUCTURE_MOTION_BIT_NV = 0x00000020,
 VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_OPACITY_MICROMAP_UPDATE_EXT = 0x00000040,
 VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_DISABLE_OPACITY_MICROMAPS_EXT = 0x00000080,
 VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_OPACITY_MICROMAP_DATA_UPDATE_EXT = 0x00000100,

 VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_DISPLACEMENT_MICROMAP_UPDATE_NV = 0x00000200,

 VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_DATA_ACCESS_KHR = 0x00000800,
 VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_NV = VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR,
 VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_NV = VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR,
 VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_NV = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR,
 VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_NV = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_KHR,
 VK_BUILD_ACCELERATION_STRUCTURE_LOW_MEMORY_BIT_NV = VK_BUILD_ACCELERATION_STRUCTURE_LOW_MEMORY_BIT_KHR,
 VK_BUILD_ACCELERATION_STRUCTURE_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkBuildAccelerationStructureFlagBitsKHR;
typedef VkFlags VkBuildAccelerationStructureFlagsKHR;
typedef VkBuildAccelerationStructureFlagsKHR VkBuildAccelerationStructureFlagsNV;

typedef VkBuildAccelerationStructureFlagBitsKHR VkBuildAccelerationStructureFlagBitsNV;

typedef struct VkRayTracingShaderGroupCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkRayTracingShaderGroupTypeKHR type;
 uint32_t generalShader;
 uint32_t closestHitShader;
 uint32_t anyHitShader;
 uint32_t intersectionShader;
} VkRayTracingShaderGroupCreateInfoNV;

typedef struct VkRayTracingPipelineCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkPipelineCreateFlags flags;
 uint32_t stageCount;
 const VkPipelineShaderStageCreateInfo* pStages;
 uint32_t groupCount;
 const VkRayTracingShaderGroupCreateInfoNV* pGroups;
 uint32_t maxRecursionDepth;
 VkPipelineLayout layout;
 VkPipeline basePipelineHandle;
 int32_t basePipelineIndex;
} VkRayTracingPipelineCreateInfoNV;

typedef struct VkGeometryTrianglesNV {
 VkStructureType sType;
 const void* pNext;
 VkBuffer vertexData;
 VkDeviceSize vertexOffset;
 uint32_t vertexCount;
 VkDeviceSize vertexStride;
 VkFormat vertexFormat;
 VkBuffer indexData;
 VkDeviceSize indexOffset;
 uint32_t indexCount;
 VkIndexType indexType;
 VkBuffer transformData;
 VkDeviceSize transformOffset;
} VkGeometryTrianglesNV;

typedef VkGeometryTrianglesNV VkGeometryTrianglesKHR;

typedef struct VkGeometryAABBNV {
 VkStructureType sType;
 const void* pNext;
 VkBuffer aabbData;
 uint32_t numAABBs;
 uint32_t stride;
 VkDeviceSize offset;
} VkGeometryAABBNV;

typedef VkGeometryAABBNV VkGeometryAABBKHR;

typedef struct VkGeometryDataNV {
 VkGeometryTrianglesNV triangles;
 VkGeometryAABBNV aabbs;
} VkGeometryDataNV;

typedef VkGeometryDataNV VkGeometryDataKHR;

typedef struct VkGeometryNV {
 VkStructureType sType;
 const void* pNext;
 VkGeometryTypeKHR geometryType;
 VkGeometryDataNV geometry;
 VkGeometryFlagsKHR flags;
} VkGeometryNV;

typedef VkGeometryNV VkGeometryKHR;

typedef struct VkAccelerationStructureInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkAccelerationStructureTypeNV type;
 VkBuildAccelerationStructureFlagsNV flags;
 uint32_t instanceCount;
 uint32_t geometryCount;
 const VkGeometryNV* pGeometries;
} VkAccelerationStructureInfoNV;

typedef VkAccelerationStructureInfoNV VkAccelerationStructureInfoKHR;

typedef struct VkAccelerationStructureCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkDeviceSize compactedSize;
 VkAccelerationStructureInfoNV info;
} VkAccelerationStructureCreateInfoNV;

typedef struct VkBindAccelerationStructureMemoryInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkAccelerationStructureNV accelerationStructure;
 VkDeviceMemory memory;
 VkDeviceSize memoryOffset;
 uint32_t deviceIndexCount;
 const uint32_t* pDeviceIndices;
} VkBindAccelerationStructureMemoryInfoNV;

typedef VkBindAccelerationStructureMemoryInfoNV VkBindAccelerationStructureMemoryInfoKHR;

typedef struct VkWriteDescriptorSetAccelerationStructureNV {
 VkStructureType sType;
 const void* pNext;
 uint32_t accelerationStructureCount;
 const VkAccelerationStructureNV* pAccelerationStructures;
} VkWriteDescriptorSetAccelerationStructureNV;

typedef struct VkAccelerationStructureMemoryRequirementsInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkAccelerationStructureMemoryRequirementsTypeNV type;
 VkAccelerationStructureNV accelerationStructure;
} VkAccelerationStructureMemoryRequirementsInfoNV;

typedef VkAccelerationStructureMemoryRequirementsInfoNV VkAccelerationStructureMemoryRequirementsInfoKHR;

typedef struct VkPhysicalDeviceRayTracingPropertiesNV {
 VkStructureType sType;
 void* pNext;
 uint32_t shaderGroupHandleSize;
 uint32_t maxRecursionDepth;
 uint32_t maxShaderGroupStride;
 uint32_t shaderGroupBaseAlignment;
 uint64_t maxGeometryCount;
 uint64_t maxInstanceCount;
 uint64_t maxTriangleCount;
 uint32_t maxDescriptorSetAccelerationStructures;
} VkPhysicalDeviceRayTracingPropertiesNV;

typedef VkPhysicalDeviceRayTracingPropertiesNV VkPhysicalDeviceRayTracingPropertiesKHR;

typedef struct VkTransformMatrixKHR {
 float matrix[3][4];
} VkTransformMatrixKHR;

typedef VkTransformMatrixKHR VkTransformMatrixNV;

typedef struct VkAabbPositionsKHR {
 float minX;
 float minY;
 float minZ;
 float maxX;
 float maxY;
 float maxZ;
} VkAabbPositionsKHR;

typedef VkAabbPositionsKHR VkAabbPositionsNV;

typedef struct VkAccelerationStructureInstanceKHR {
 VkTransformMatrixKHR transform;
 uint32_t instanceCustomIndex:24;
 uint32_t mask:8;
 uint32_t instanceShaderBindingTableRecordOffset:24;
 VkGeometryInstanceFlagsKHR flags:8;
 uint64_t accelerationStructureReference;
} VkAccelerationStructureInstanceKHR;

typedef VkAccelerationStructureInstanceKHR VkAccelerationStructureInstanceNV;

typedef VkResult (VKAPI_PTR *PFN_vkCreateAccelerationStructureNV)(VkDevice device, const VkAccelerationStructureCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureNV* pAccelerationStructure);
typedef void (VKAPI_PTR *PFN_vkDestroyAccelerationStructureNV)(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkAllocationCallbacks* pAllocator);
typedef void (VKAPI_PTR *PFN_vkGetAccelerationStructureMemoryRequirementsNV)(VkDevice device, const VkAccelerationStructureMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements);
typedef VkResult (VKAPI_PTR *PFN_vkBindAccelerationStructureMemoryNV)(VkDevice device, uint32_t bindInfoCount, const VkBindAccelerationStructureMemoryInfoNV* pBindInfos);
typedef void (VKAPI_PTR *PFN_vkCmdBuildAccelerationStructureNV)(VkCommandBuffer commandBuffer, const VkAccelerationStructureInfoNV* pInfo, VkBuffer instanceData, VkDeviceSize instanceOffset, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBuffer scratch, VkDeviceSize scratchOffset);
typedef void (VKAPI_PTR *PFN_vkCmdCopyAccelerationStructureNV)(VkCommandBuffer commandBuffer, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkCopyAccelerationStructureModeKHR mode);
typedef void (VKAPI_PTR *PFN_vkCmdTraceRaysNV)(VkCommandBuffer commandBuffer, VkBuffer raygenShaderBindingTableBuffer, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth);
typedef VkResult (VKAPI_PTR *PFN_vkCreateRayTracingPipelinesNV)(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoNV* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines);
typedef VkResult (VKAPI_PTR *PFN_vkGetRayTracingShaderGroupHandlesKHR)(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData);
typedef VkResult (VKAPI_PTR *PFN_vkGetRayTracingShaderGroupHandlesNV)(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData);
typedef VkResult (VKAPI_PTR *PFN_vkGetAccelerationStructureHandleNV)(VkDevice device, VkAccelerationStructureNV accelerationStructure, size_t dataSize, void* pData);
typedef void (VKAPI_PTR *PFN_vkCmdWriteAccelerationStructuresPropertiesNV)(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureNV* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery);
typedef VkResult (VKAPI_PTR *PFN_vkCompileDeferredNV)(VkDevice device, VkPipeline pipeline, uint32_t shader);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateAccelerationStructureNV(
 VkDevice device,
 const VkAccelerationStructureCreateInfoNV* pCreateInfo,
 const VkAllocationCallbacks* pAllocator,
 VkAccelerationStructureNV* pAccelerationStructure);

VKAPI_ATTR void VKAPI_CALL vkDestroyAccelerationStructureNV(
 VkDevice device,
 VkAccelerationStructureNV accelerationStructure,
 const VkAllocationCallbacks* pAllocator);

VKAPI_ATTR void VKAPI_CALL vkGetAccelerationStructureMemoryRequirementsNV(
 VkDevice device,
 const VkAccelerationStructureMemoryRequirementsInfoNV* pInfo,
 VkMemoryRequirements2KHR* pMemoryRequirements);

VKAPI_ATTR VkResult VKAPI_CALL vkBindAccelerationStructureMemoryNV(
 VkDevice device,
 uint32_t bindInfoCount,
 const VkBindAccelerationStructureMemoryInfoNV* pBindInfos);

VKAPI_ATTR void VKAPI_CALL vkCmdBuildAccelerationStructureNV(
 VkCommandBuffer commandBuffer,
 const VkAccelerationStructureInfoNV* pInfo,
 VkBuffer instanceData,
 VkDeviceSize instanceOffset,
 VkBool32 update,
 VkAccelerationStructureNV dst,
 VkAccelerationStructureNV src,
 VkBuffer scratch,
 VkDeviceSize scratchOffset);

VKAPI_ATTR void VKAPI_CALL vkCmdCopyAccelerationStructureNV(
 VkCommandBuffer commandBuffer,
 VkAccelerationStructureNV dst,
 VkAccelerationStructureNV src,
 VkCopyAccelerationStructureModeKHR mode);

VKAPI_ATTR void VKAPI_CALL vkCmdTraceRaysNV(
 VkCommandBuffer commandBuffer,
 VkBuffer raygenShaderBindingTableBuffer,
 VkDeviceSize raygenShaderBindingOffset,
 VkBuffer missShaderBindingTableBuffer,
 VkDeviceSize missShaderBindingOffset,
 VkDeviceSize missShaderBindingStride,
 VkBuffer hitShaderBindingTableBuffer,
 VkDeviceSize hitShaderBindingOffset,
 VkDeviceSize hitShaderBindingStride,
 VkBuffer callableShaderBindingTableBuffer,
 VkDeviceSize callableShaderBindingOffset,
 VkDeviceSize callableShaderBindingStride,
 uint32_t width,
 uint32_t height,
 uint32_t depth);

VKAPI_ATTR VkResult VKAPI_CALL vkCreateRayTracingPipelinesNV(
 VkDevice device,
 VkPipelineCache pipelineCache,
 uint32_t createInfoCount,
 const VkRayTracingPipelineCreateInfoNV* pCreateInfos,
 const VkAllocationCallbacks* pAllocator,
 VkPipeline* pPipelines);

VKAPI_ATTR VkResult VKAPI_CALL vkGetRayTracingShaderGroupHandlesKHR(
 VkDevice device,
 VkPipeline pipeline,
 uint32_t firstGroup,
 uint32_t groupCount,
 size_t dataSize,
 void* pData);

VKAPI_ATTR VkResult VKAPI_CALL vkGetRayTracingShaderGroupHandlesNV(
 VkDevice device,
 VkPipeline pipeline,
 uint32_t firstGroup,
 uint32_t groupCount,
 size_t dataSize,
 void* pData);

VKAPI_ATTR VkResult VKAPI_CALL vkGetAccelerationStructureHandleNV(
 VkDevice device,
 VkAccelerationStructureNV accelerationStructure,
 size_t dataSize,
 void* pData);

VKAPI_ATTR void VKAPI_CALL vkCmdWriteAccelerationStructuresPropertiesNV(
 VkCommandBuffer commandBuffer,
 uint32_t accelerationStructureCount,
 const VkAccelerationStructureNV* pAccelerationStructures,
 VkQueryType queryType,
 VkQueryPool queryPool,
 uint32_t firstQuery);

VKAPI_ATTR VkResult VKAPI_CALL vkCompileDeferredNV(
 VkDevice device,
 VkPipeline pipeline,
 uint32_t shader);
#endif

// VK_NV_representative_fragment_test is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_representative_fragment_test 1
#define VK_NV_REPRESENTATIVE_FRAGMENT_TEST_SPEC_VERSION 2
#define VK_NV_REPRESENTATIVE_FRAGMENT_TEST_EXTENSION_NAME "VK_NV_representative_fragment_test"
typedef struct VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 representativeFragmentTest;
} VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV;

typedef struct VkPipelineRepresentativeFragmentTestStateCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkBool32 representativeFragmentTestEnable;
} VkPipelineRepresentativeFragmentTestStateCreateInfoNV;

// VK_EXT_filter_cubic is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_filter_cubic 1
#define VK_EXT_FILTER_CUBIC_SPEC_VERSION 3
#define VK_EXT_FILTER_CUBIC_EXTENSION_NAME "VK_EXT_filter_cubic"
typedef struct VkPhysicalDeviceImageViewImageFormatInfoEXT {
 VkStructureType sType;
 void* pNext;
 VkImageViewType imageViewType;
} VkPhysicalDeviceImageViewImageFormatInfoEXT;

typedef struct VkFilterCubicImageViewImageFormatPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 filterCubic;
 VkBool32 filterCubicMinmax;
} VkFilterCubicImageViewImageFormatPropertiesEXT;

// VK_QCOM_render_pass_shader_resolve is a preprocessor guard. Do not pass it to API calls.
#define VK_QCOM_render_pass_shader_resolve 1
#define VK_QCOM_RENDER_PASS_SHADER_RESOLVE_SPEC_VERSION 4
#define VK_QCOM_RENDER_PASS_SHADER_RESOLVE_EXTENSION_NAME "VK_QCOM_render_pass_shader_resolve"

// VK_EXT_global_priority is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_global_priority 1
#define VK_EXT_GLOBAL_PRIORITY_SPEC_VERSION 2
#define VK_EXT_GLOBAL_PRIORITY_EXTENSION_NAME "VK_EXT_global_priority"
typedef VkQueueGlobalPriorityKHR VkQueueGlobalPriorityEXT;

typedef VkDeviceQueueGlobalPriorityCreateInfoKHR VkDeviceQueueGlobalPriorityCreateInfoEXT;

// VK_EXT_external_memory_host is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_external_memory_host 1
#define VK_EXT_EXTERNAL_MEMORY_HOST_SPEC_VERSION 1
#define VK_EXT_EXTERNAL_MEMORY_HOST_EXTENSION_NAME "VK_EXT_external_memory_host"
typedef struct VkImportMemoryHostPointerInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkExternalMemoryHandleTypeFlagBits handleType;
 void* pHostPointer;
} VkImportMemoryHostPointerInfoEXT;

typedef struct VkMemoryHostPointerPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 uint32_t memoryTypeBits;
} VkMemoryHostPointerPropertiesEXT;

typedef struct VkPhysicalDeviceExternalMemoryHostPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 VkDeviceSize minImportedHostPointerAlignment;
} VkPhysicalDeviceExternalMemoryHostPropertiesEXT;

typedef VkResult (VKAPI_PTR *PFN_vkGetMemoryHostPointerPropertiesEXT)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, const void* pHostPointer, VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryHostPointerPropertiesEXT(
 VkDevice device,
 VkExternalMemoryHandleTypeFlagBits handleType,
 const void* pHostPointer,
 VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties);
#endif

// VK_AMD_buffer_marker is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_buffer_marker 1
#define VK_AMD_BUFFER_MARKER_SPEC_VERSION 1
#define VK_AMD_BUFFER_MARKER_EXTENSION_NAME "VK_AMD_buffer_marker"
typedef void (VKAPI_PTR *PFN_vkCmdWriteBufferMarkerAMD)(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdWriteBufferMarkerAMD(
 VkCommandBuffer commandBuffer,
 VkPipelineStageFlagBits pipelineStage,
 VkBuffer dstBuffer,
 VkDeviceSize dstOffset,
 uint32_t marker);
#endif

// VK_AMD_pipeline_compiler_control is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_pipeline_compiler_control 1
#define VK_AMD_PIPELINE_COMPILER_CONTROL_SPEC_VERSION 1
#define VK_AMD_PIPELINE_COMPILER_CONTROL_EXTENSION_NAME "VK_AMD_pipeline_compiler_control"

typedef enum VkPipelineCompilerControlFlagBitsAMD {
 VK_PIPELINE_COMPILER_CONTROL_FLAG_BITS_MAX_ENUM_AMD = 0x7FFFFFFF
} VkPipelineCompilerControlFlagBitsAMD;
typedef VkFlags VkPipelineCompilerControlFlagsAMD;
typedef struct VkPipelineCompilerControlCreateInfoAMD {
 VkStructureType sType;
 const void* pNext;
 VkPipelineCompilerControlFlagsAMD compilerControlFlags;
} VkPipelineCompilerControlCreateInfoAMD;

// VK_EXT_calibrated_timestamps is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_calibrated_timestamps 1
#define VK_EXT_CALIBRATED_TIMESTAMPS_SPEC_VERSION 2
#define VK_EXT_CALIBRATED_TIMESTAMPS_EXTENSION_NAME "VK_EXT_calibrated_timestamps"
typedef VkTimeDomainKHR VkTimeDomainEXT;

typedef VkCalibratedTimestampInfoKHR VkCalibratedTimestampInfoEXT;

typedef VkResult (VKAPI_PTR *PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT)(VkPhysicalDevice physicalDevice, uint32_t* pTimeDomainCount, VkTimeDomainKHR* pTimeDomains);
typedef VkResult (VKAPI_PTR *PFN_vkGetCalibratedTimestampsEXT)(VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoKHR* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceCalibrateableTimeDomainsEXT(
 VkPhysicalDevice physicalDevice,
 uint32_t* pTimeDomainCount,
 VkTimeDomainKHR* pTimeDomains);

VKAPI_ATTR VkResult VKAPI_CALL vkGetCalibratedTimestampsEXT(
 VkDevice device,
 uint32_t timestampCount,
 const VkCalibratedTimestampInfoKHR* pTimestampInfos,
 uint64_t* pTimestamps,
 uint64_t* pMaxDeviation);
#endif

// VK_AMD_shader_core_properties is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_shader_core_properties 1
#define VK_AMD_SHADER_CORE_PROPERTIES_SPEC_VERSION 2
#define VK_AMD_SHADER_CORE_PROPERTIES_EXTENSION_NAME "VK_AMD_shader_core_properties"
typedef struct VkPhysicalDeviceShaderCorePropertiesAMD {
 VkStructureType sType;
 void* pNext;
 uint32_t shaderEngineCount;
 uint32_t shaderArraysPerEngineCount;
 uint32_t computeUnitsPerShaderArray;
 uint32_t simdPerComputeUnit;
 uint32_t wavefrontsPerSimd;
 uint32_t wavefrontSize;
 uint32_t sgprsPerSimd;
 uint32_t minSgprAllocation;
 uint32_t maxSgprAllocation;
 uint32_t sgprAllocationGranularity;
 uint32_t vgprsPerSimd;
 uint32_t minVgprAllocation;
 uint32_t maxVgprAllocation;
 uint32_t vgprAllocationGranularity;
} VkPhysicalDeviceShaderCorePropertiesAMD;

// VK_AMD_memory_overallocation_behavior is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_memory_overallocation_behavior 1
#define VK_AMD_MEMORY_OVERALLOCATION_BEHAVIOR_SPEC_VERSION 1
#define VK_AMD_MEMORY_OVERALLOCATION_BEHAVIOR_EXTENSION_NAME "VK_AMD_memory_overallocation_behavior"

typedef enum VkMemoryOverallocationBehaviorAMD {
 VK_MEMORY_OVERALLOCATION_BEHAVIOR_DEFAULT_AMD = 0,
 VK_MEMORY_OVERALLOCATION_BEHAVIOR_ALLOWED_AMD = 1,
 VK_MEMORY_OVERALLOCATION_BEHAVIOR_DISALLOWED_AMD = 2,
 VK_MEMORY_OVERALLOCATION_BEHAVIOR_MAX_ENUM_AMD = 0x7FFFFFFF
} VkMemoryOverallocationBehaviorAMD;
typedef struct VkDeviceMemoryOverallocationCreateInfoAMD {
 VkStructureType sType;
 const void* pNext;
 VkMemoryOverallocationBehaviorAMD overallocationBehavior;
} VkDeviceMemoryOverallocationCreateInfoAMD;

// VK_EXT_vertex_attribute_divisor is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_vertex_attribute_divisor 1
#define VK_EXT_VERTEX_ATTRIBUTE_DIVISOR_SPEC_VERSION 3
#define VK_EXT_VERTEX_ATTRIBUTE_DIVISOR_EXTENSION_NAME "VK_EXT_vertex_attribute_divisor"
typedef struct VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 uint32_t maxVertexAttribDivisor;
} VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT;

typedef VkVertexInputBindingDivisorDescriptionKHR VkVertexInputBindingDivisorDescriptionEXT;

typedef VkPipelineVertexInputDivisorStateCreateInfoKHR VkPipelineVertexInputDivisorStateCreateInfoEXT;

typedef VkPhysicalDeviceVertexAttributeDivisorFeaturesKHR VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT;

// VK_EXT_pipeline_creation_feedback is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_pipeline_creation_feedback 1
#define VK_EXT_PIPELINE_CREATION_FEEDBACK_SPEC_VERSION 1
#define VK_EXT_PIPELINE_CREATION_FEEDBACK_EXTENSION_NAME "VK_EXT_pipeline_creation_feedback"
typedef VkPipelineCreationFeedbackFlagBits VkPipelineCreationFeedbackFlagBitsEXT;

typedef VkPipelineCreationFeedbackFlags VkPipelineCreationFeedbackFlagsEXT;

typedef VkPipelineCreationFeedbackCreateInfo VkPipelineCreationFeedbackCreateInfoEXT;

typedef VkPipelineCreationFeedback VkPipelineCreationFeedbackEXT;

// VK_NV_shader_subgroup_partitioned is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_shader_subgroup_partitioned 1
#define VK_NV_SHADER_SUBGROUP_PARTITIONED_SPEC_VERSION 1
#define VK_NV_SHADER_SUBGROUP_PARTITIONED_EXTENSION_NAME "VK_NV_shader_subgroup_partitioned"

// VK_NV_compute_shader_derivatives is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_compute_shader_derivatives 1
#define VK_NV_COMPUTE_SHADER_DERIVATIVES_SPEC_VERSION 1
#define VK_NV_COMPUTE_SHADER_DERIVATIVES_EXTENSION_NAME "VK_NV_compute_shader_derivatives"
typedef struct VkPhysicalDeviceComputeShaderDerivativesFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 computeDerivativeGroupQuads;
 VkBool32 computeDerivativeGroupLinear;
} VkPhysicalDeviceComputeShaderDerivativesFeaturesNV;

// VK_NV_mesh_shader is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_mesh_shader 1
#define VK_NV_MESH_SHADER_SPEC_VERSION 1
#define VK_NV_MESH_SHADER_EXTENSION_NAME "VK_NV_mesh_shader"
typedef struct VkPhysicalDeviceMeshShaderFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 taskShader;
 VkBool32 meshShader;
} VkPhysicalDeviceMeshShaderFeaturesNV;

typedef struct VkPhysicalDeviceMeshShaderPropertiesNV {
 VkStructureType sType;
 void* pNext;
 uint32_t maxDrawMeshTasksCount;
 uint32_t maxTaskWorkGroupInvocations;
 uint32_t maxTaskWorkGroupSize[3];
 uint32_t maxTaskTotalMemorySize;
 uint32_t maxTaskOutputCount;
 uint32_t maxMeshWorkGroupInvocations;
 uint32_t maxMeshWorkGroupSize[3];
 uint32_t maxMeshTotalMemorySize;
 uint32_t maxMeshOutputVertices;
 uint32_t maxMeshOutputPrimitives;
 uint32_t maxMeshMultiviewViewCount;
 uint32_t meshOutputPerVertexGranularity;
 uint32_t meshOutputPerPrimitiveGranularity;
} VkPhysicalDeviceMeshShaderPropertiesNV;

typedef struct VkDrawMeshTasksIndirectCommandNV {
 uint32_t taskCount;
 uint32_t firstTask;
} VkDrawMeshTasksIndirectCommandNV;

typedef void (VKAPI_PTR *PFN_vkCmdDrawMeshTasksNV)(VkCommandBuffer commandBuffer, uint32_t taskCount, uint32_t firstTask);
typedef void (VKAPI_PTR *PFN_vkCmdDrawMeshTasksIndirectNV)(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride);
typedef void (VKAPI_PTR *PFN_vkCmdDrawMeshTasksIndirectCountNV)(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdDrawMeshTasksNV(
 VkCommandBuffer commandBuffer,
 uint32_t taskCount,
 uint32_t firstTask);

VKAPI_ATTR void VKAPI_CALL vkCmdDrawMeshTasksIndirectNV(
 VkCommandBuffer commandBuffer,
 VkBuffer buffer,
 VkDeviceSize offset,
 uint32_t drawCount,
 uint32_t stride);

VKAPI_ATTR void VKAPI_CALL vkCmdDrawMeshTasksIndirectCountNV(
 VkCommandBuffer commandBuffer,
 VkBuffer buffer,
 VkDeviceSize offset,
 VkBuffer countBuffer,
 VkDeviceSize countBufferOffset,
 uint32_t maxDrawCount,
 uint32_t stride);
#endif

// VK_NV_fragment_shader_barycentric is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_fragment_shader_barycentric 1
#define VK_NV_FRAGMENT_SHADER_BARYCENTRIC_SPEC_VERSION 1
#define VK_NV_FRAGMENT_SHADER_BARYCENTRIC_EXTENSION_NAME "VK_NV_fragment_shader_barycentric"
typedef VkPhysicalDeviceFragmentShaderBarycentricFeaturesKHR VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV;

// VK_NV_shader_image_footprint is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_shader_image_footprint 1
#define VK_NV_SHADER_IMAGE_FOOTPRINT_SPEC_VERSION 2
#define VK_NV_SHADER_IMAGE_FOOTPRINT_EXTENSION_NAME "VK_NV_shader_image_footprint"
typedef struct VkPhysicalDeviceShaderImageFootprintFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 imageFootprint;
} VkPhysicalDeviceShaderImageFootprintFeaturesNV;

// VK_NV_scissor_exclusive is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_scissor_exclusive 1
#define VK_NV_SCISSOR_EXCLUSIVE_SPEC_VERSION 2
#define VK_NV_SCISSOR_EXCLUSIVE_EXTENSION_NAME "VK_NV_scissor_exclusive"
typedef struct VkPipelineViewportExclusiveScissorStateCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 uint32_t exclusiveScissorCount;
 const VkRect2D* pExclusiveScissors;
} VkPipelineViewportExclusiveScissorStateCreateInfoNV;

typedef struct VkPhysicalDeviceExclusiveScissorFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 exclusiveScissor;
} VkPhysicalDeviceExclusiveScissorFeaturesNV;

typedef void (VKAPI_PTR *PFN_vkCmdSetExclusiveScissorEnableNV)(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkBool32* pExclusiveScissorEnables);
typedef void (VKAPI_PTR *PFN_vkCmdSetExclusiveScissorNV)(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkRect2D* pExclusiveScissors);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdSetExclusiveScissorEnableNV(
 VkCommandBuffer commandBuffer,
 uint32_t firstExclusiveScissor,
 uint32_t exclusiveScissorCount,
 const VkBool32* pExclusiveScissorEnables);

VKAPI_ATTR void VKAPI_CALL vkCmdSetExclusiveScissorNV(
 VkCommandBuffer commandBuffer,
 uint32_t firstExclusiveScissor,
 uint32_t exclusiveScissorCount,
 const VkRect2D* pExclusiveScissors);
#endif

// VK_NV_device_diagnostic_checkpoints is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_device_diagnostic_checkpoints 1
#define VK_NV_DEVICE_DIAGNOSTIC_CHECKPOINTS_SPEC_VERSION 2
#define VK_NV_DEVICE_DIAGNOSTIC_CHECKPOINTS_EXTENSION_NAME "VK_NV_device_diagnostic_checkpoints"
typedef struct VkQueueFamilyCheckpointPropertiesNV {
 VkStructureType sType;
 void* pNext;
 VkPipelineStageFlags checkpointExecutionStageMask;
} VkQueueFamilyCheckpointPropertiesNV;

typedef struct VkCheckpointDataNV {
 VkStructureType sType;
 void* pNext;
 VkPipelineStageFlagBits stage;
 void* pCheckpointMarker;
} VkCheckpointDataNV;

typedef void (VKAPI_PTR *PFN_vkCmdSetCheckpointNV)(VkCommandBuffer commandBuffer, const void* pCheckpointMarker);
typedef void (VKAPI_PTR *PFN_vkGetQueueCheckpointDataNV)(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointDataNV* pCheckpointData);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdSetCheckpointNV(
 VkCommandBuffer commandBuffer,
 const void* pCheckpointMarker);

VKAPI_ATTR void VKAPI_CALL vkGetQueueCheckpointDataNV(
 VkQueue queue,
 uint32_t* pCheckpointDataCount,
 VkCheckpointDataNV* pCheckpointData);
#endif

// VK_EXT_pci_bus_info is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_pci_bus_info 1
#define VK_EXT_PCI_BUS_INFO_SPEC_VERSION 2
#define VK_EXT_PCI_BUS_INFO_EXTENSION_NAME "VK_EXT_pci_bus_info"
typedef struct VkPhysicalDevicePCIBusInfoPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 uint32_t pciDomain;
 uint32_t pciBus;
 uint32_t pciDevice;
 uint32_t pciFunction;
} VkPhysicalDevicePCIBusInfoPropertiesEXT;

// VK_AMD_display_native_hdr is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_display_native_hdr 1
#define VK_AMD_DISPLAY_NATIVE_HDR_SPEC_VERSION 1
#define VK_AMD_DISPLAY_NATIVE_HDR_EXTENSION_NAME "VK_AMD_display_native_hdr"
typedef struct VkDisplayNativeHdrSurfaceCapabilitiesAMD {
 VkStructureType sType;
 void* pNext;
 VkBool32 localDimmingSupport;
} VkDisplayNativeHdrSurfaceCapabilitiesAMD;

typedef struct VkSwapchainDisplayNativeHdrCreateInfoAMD {
 VkStructureType sType;
 const void* pNext;
 VkBool32 localDimmingEnable;
} VkSwapchainDisplayNativeHdrCreateInfoAMD;

typedef void (VKAPI_PTR *PFN_vkSetLocalDimmingAMD)(VkDevice device, VkSwapchainKHR swapChain, VkBool32 localDimmingEnable);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkSetLocalDimmingAMD(
 VkDevice device,
 VkSwapchainKHR swapChain,
 VkBool32 localDimmingEnable);
#endif

// VK_EXT_fragment_density_map is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_fragment_density_map 1
#define VK_EXT_FRAGMENT_DENSITY_MAP_SPEC_VERSION 2
#define VK_EXT_FRAGMENT_DENSITY_MAP_EXTENSION_NAME "VK_EXT_fragment_density_map"
typedef struct VkPhysicalDeviceFragmentDensityMapFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 fragmentDensityMap;
 VkBool32 fragmentDensityMapDynamic;
 VkBool32 fragmentDensityMapNonSubsampledImages;
} VkPhysicalDeviceFragmentDensityMapFeaturesEXT;

typedef struct VkPhysicalDeviceFragmentDensityMapPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 VkExtent2D minFragmentDensityTexelSize;
 VkExtent2D maxFragmentDensityTexelSize;
 VkBool32 fragmentDensityInvocations;
} VkPhysicalDeviceFragmentDensityMapPropertiesEXT;

typedef struct VkRenderPassFragmentDensityMapCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkAttachmentReference fragmentDensityMapAttachment;
} VkRenderPassFragmentDensityMapCreateInfoEXT;

// VK_EXT_scalar_block_layout is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_scalar_block_layout 1
#define VK_EXT_SCALAR_BLOCK_LAYOUT_SPEC_VERSION 1
#define VK_EXT_SCALAR_BLOCK_LAYOUT_EXTENSION_NAME "VK_EXT_scalar_block_layout"
typedef VkPhysicalDeviceScalarBlockLayoutFeatures VkPhysicalDeviceScalarBlockLayoutFeaturesEXT;

// VK_GOOGLE_hlsl_functionality1 is a preprocessor guard. Do not pass it to API calls.
#define VK_GOOGLE_hlsl_functionality1 1
#define VK_GOOGLE_HLSL_FUNCTIONALITY_1_SPEC_VERSION 1
#define VK_GOOGLE_HLSL_FUNCTIONALITY_1_EXTENSION_NAME "VK_GOOGLE_hlsl_functionality1"
#define VK_GOOGLE_HLSL_FUNCTIONALITY1_SPEC_VERSION VK_GOOGLE_HLSL_FUNCTIONALITY_1_SPEC_VERSION
#define VK_GOOGLE_HLSL_FUNCTIONALITY1_EXTENSION_NAME VK_GOOGLE_HLSL_FUNCTIONALITY_1_EXTENSION_NAME

// VK_GOOGLE_decorate_string is a preprocessor guard. Do not pass it to API calls.
#define VK_GOOGLE_decorate_string 1
#define VK_GOOGLE_DECORATE_STRING_SPEC_VERSION 1
#define VK_GOOGLE_DECORATE_STRING_EXTENSION_NAME "VK_GOOGLE_decorate_string"

// VK_EXT_subgroup_size_control is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_subgroup_size_control 1
#define VK_EXT_SUBGROUP_SIZE_CONTROL_SPEC_VERSION 2
#define VK_EXT_SUBGROUP_SIZE_CONTROL_EXTENSION_NAME "VK_EXT_subgroup_size_control"
typedef VkPhysicalDeviceSubgroupSizeControlFeatures VkPhysicalDeviceSubgroupSizeControlFeaturesEXT;

typedef VkPhysicalDeviceSubgroupSizeControlProperties VkPhysicalDeviceSubgroupSizeControlPropertiesEXT;

typedef VkPipelineShaderStageRequiredSubgroupSizeCreateInfo VkPipelineShaderStageRequiredSubgroupSizeCreateInfoEXT;

// VK_AMD_shader_core_properties2 is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_shader_core_properties2 1
#define VK_AMD_SHADER_CORE_PROPERTIES_2_SPEC_VERSION 1
#define VK_AMD_SHADER_CORE_PROPERTIES_2_EXTENSION_NAME "VK_AMD_shader_core_properties2"

typedef enum VkShaderCorePropertiesFlagBitsAMD {
 VK_SHADER_CORE_PROPERTIES_FLAG_BITS_MAX_ENUM_AMD = 0x7FFFFFFF
} VkShaderCorePropertiesFlagBitsAMD;
typedef VkFlags VkShaderCorePropertiesFlagsAMD;
typedef struct VkPhysicalDeviceShaderCoreProperties2AMD {
 VkStructureType sType;
 void* pNext;
 VkShaderCorePropertiesFlagsAMD shaderCoreFeatures;
 uint32_t activeComputeUnitCount;
} VkPhysicalDeviceShaderCoreProperties2AMD;

// VK_AMD_device_coherent_memory is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_device_coherent_memory 1
#define VK_AMD_DEVICE_COHERENT_MEMORY_SPEC_VERSION 1
#define VK_AMD_DEVICE_COHERENT_MEMORY_EXTENSION_NAME "VK_AMD_device_coherent_memory"
typedef struct VkPhysicalDeviceCoherentMemoryFeaturesAMD {
 VkStructureType sType;
 void* pNext;
 VkBool32 deviceCoherentMemory;
} VkPhysicalDeviceCoherentMemoryFeaturesAMD;

// VK_EXT_shader_image_atomic_int64 is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_shader_image_atomic_int64 1
#define VK_EXT_SHADER_IMAGE_ATOMIC_INT64_SPEC_VERSION 1
#define VK_EXT_SHADER_IMAGE_ATOMIC_INT64_EXTENSION_NAME "VK_EXT_shader_image_atomic_int64"
typedef struct VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 shaderImageInt64Atomics;
 VkBool32 sparseImageInt64Atomics;
} VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT;

// VK_EXT_memory_budget is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_memory_budget 1
#define VK_EXT_MEMORY_BUDGET_SPEC_VERSION 1
#define VK_EXT_MEMORY_BUDGET_EXTENSION_NAME "VK_EXT_memory_budget"
typedef struct VkPhysicalDeviceMemoryBudgetPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 VkDeviceSize heapBudget[VK_MAX_MEMORY_HEAPS];
 VkDeviceSize heapUsage[VK_MAX_MEMORY_HEAPS];
} VkPhysicalDeviceMemoryBudgetPropertiesEXT;

// VK_EXT_memory_priority is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_memory_priority 1
#define VK_EXT_MEMORY_PRIORITY_SPEC_VERSION 1
#define VK_EXT_MEMORY_PRIORITY_EXTENSION_NAME "VK_EXT_memory_priority"
typedef struct VkPhysicalDeviceMemoryPriorityFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 memoryPriority;
} VkPhysicalDeviceMemoryPriorityFeaturesEXT;

typedef struct VkMemoryPriorityAllocateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 float priority;
} VkMemoryPriorityAllocateInfoEXT;

// VK_NV_dedicated_allocation_image_aliasing is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_dedicated_allocation_image_aliasing 1
#define VK_NV_DEDICATED_ALLOCATION_IMAGE_ALIASING_SPEC_VERSION 1
#define VK_NV_DEDICATED_ALLOCATION_IMAGE_ALIASING_EXTENSION_NAME "VK_NV_dedicated_allocation_image_aliasing"
typedef struct VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 dedicatedAllocationImageAliasing;
} VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV;

// VK_EXT_buffer_device_address is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_buffer_device_address 1
#define VK_EXT_BUFFER_DEVICE_ADDRESS_SPEC_VERSION 2
#define VK_EXT_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME "VK_EXT_buffer_device_address"
typedef struct VkPhysicalDeviceBufferDeviceAddressFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 bufferDeviceAddress;
 VkBool32 bufferDeviceAddressCaptureReplay;
 VkBool32 bufferDeviceAddressMultiDevice;
} VkPhysicalDeviceBufferDeviceAddressFeaturesEXT;

typedef VkPhysicalDeviceBufferDeviceAddressFeaturesEXT VkPhysicalDeviceBufferAddressFeaturesEXT;

typedef VkBufferDeviceAddressInfo VkBufferDeviceAddressInfoEXT;

typedef struct VkBufferDeviceAddressCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkDeviceAddress deviceAddress;
} VkBufferDeviceAddressCreateInfoEXT;

typedef VkDeviceAddress (VKAPI_PTR *PFN_vkGetBufferDeviceAddressEXT)(VkDevice device, const VkBufferDeviceAddressInfo* pInfo);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkDeviceAddress VKAPI_CALL vkGetBufferDeviceAddressEXT(
 VkDevice device,
 const VkBufferDeviceAddressInfo* pInfo);
#endif

// VK_EXT_tooling_info is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_tooling_info 1
#define VK_EXT_TOOLING_INFO_SPEC_VERSION 1
#define VK_EXT_TOOLING_INFO_EXTENSION_NAME "VK_EXT_tooling_info"
typedef VkToolPurposeFlagBits VkToolPurposeFlagBitsEXT;

typedef VkToolPurposeFlags VkToolPurposeFlagsEXT;

typedef VkPhysicalDeviceToolProperties VkPhysicalDeviceToolPropertiesEXT;

typedef VkResult (VKAPI_PTR *PFN_vkGetPhysicalDeviceToolPropertiesEXT)(VkPhysicalDevice physicalDevice, uint32_t* pToolCount, VkPhysicalDeviceToolProperties* pToolProperties);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceToolPropertiesEXT(
 VkPhysicalDevice physicalDevice,
 uint32_t* pToolCount,
 VkPhysicalDeviceToolProperties* pToolProperties);
#endif

// VK_EXT_separate_stencil_usage is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_separate_stencil_usage 1
#define VK_EXT_SEPARATE_STENCIL_USAGE_SPEC_VERSION 1
#define VK_EXT_SEPARATE_STENCIL_USAGE_EXTENSION_NAME "VK_EXT_separate_stencil_usage"
typedef VkImageStencilUsageCreateInfo VkImageStencilUsageCreateInfoEXT;

// VK_EXT_validation_features is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_validation_features 1
#define VK_EXT_VALIDATION_FEATURES_SPEC_VERSION 6
#define VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME "VK_EXT_validation_features"

typedef enum VkValidationFeatureEnableEXT {
 VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT = 0,
 VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT = 1,
 VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT = 2,
 VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT = 3,
 VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT = 4,
 VK_VALIDATION_FEATURE_ENABLE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkValidationFeatureEnableEXT;

typedef enum VkValidationFeatureDisableEXT {
 VK_VALIDATION_FEATURE_DISABLE_ALL_EXT = 0,
 VK_VALIDATION_FEATURE_DISABLE_SHADERS_EXT = 1,
 VK_VALIDATION_FEATURE_DISABLE_THREAD_SAFETY_EXT = 2,
 VK_VALIDATION_FEATURE_DISABLE_API_PARAMETERS_EXT = 3,
 VK_VALIDATION_FEATURE_DISABLE_OBJECT_LIFETIMES_EXT = 4,
 VK_VALIDATION_FEATURE_DISABLE_CORE_CHECKS_EXT = 5,
 VK_VALIDATION_FEATURE_DISABLE_UNIQUE_HANDLES_EXT = 6,
 VK_VALIDATION_FEATURE_DISABLE_SHADER_VALIDATION_CACHE_EXT = 7,
 VK_VALIDATION_FEATURE_DISABLE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkValidationFeatureDisableEXT;
typedef struct VkValidationFeaturesEXT {
 VkStructureType sType;
 const void* pNext;
 uint32_t enabledValidationFeatureCount;
 const VkValidationFeatureEnableEXT* pEnabledValidationFeatures;
 uint32_t disabledValidationFeatureCount;
 const VkValidationFeatureDisableEXT* pDisabledValidationFeatures;
} VkValidationFeaturesEXT;

// VK_NV_cooperative_matrix is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_cooperative_matrix 1
#define VK_NV_COOPERATIVE_MATRIX_SPEC_VERSION 1
#define VK_NV_COOPERATIVE_MATRIX_EXTENSION_NAME "VK_NV_cooperative_matrix"
typedef VkComponentTypeKHR VkComponentTypeNV;

typedef VkScopeKHR VkScopeNV;

typedef struct VkCooperativeMatrixPropertiesNV {
 VkStructureType sType;
 void* pNext;
 uint32_t MSize;
 uint32_t NSize;
 uint32_t KSize;
 VkComponentTypeNV AType;
 VkComponentTypeNV BType;
 VkComponentTypeNV CType;
 VkComponentTypeNV DType;
 VkScopeNV scope;
} VkCooperativeMatrixPropertiesNV;

typedef struct VkPhysicalDeviceCooperativeMatrixFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 cooperativeMatrix;
 VkBool32 cooperativeMatrixRobustBufferAccess;
} VkPhysicalDeviceCooperativeMatrixFeaturesNV;

typedef struct VkPhysicalDeviceCooperativeMatrixPropertiesNV {
 VkStructureType sType;
 void* pNext;
 VkShaderStageFlags cooperativeMatrixSupportedStages;
} VkPhysicalDeviceCooperativeMatrixPropertiesNV;

typedef VkResult (VKAPI_PTR *PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV)(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkCooperativeMatrixPropertiesNV* pProperties);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceCooperativeMatrixPropertiesNV(
 VkPhysicalDevice physicalDevice,
 uint32_t* pPropertyCount,
 VkCooperativeMatrixPropertiesNV* pProperties);
#endif

// VK_NV_coverage_reduction_mode is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_coverage_reduction_mode 1
#define VK_NV_COVERAGE_REDUCTION_MODE_SPEC_VERSION 1
#define VK_NV_COVERAGE_REDUCTION_MODE_EXTENSION_NAME "VK_NV_coverage_reduction_mode"

typedef enum VkCoverageReductionModeNV {
 VK_COVERAGE_REDUCTION_MODE_MERGE_NV = 0,
 VK_COVERAGE_REDUCTION_MODE_TRUNCATE_NV = 1,
 VK_COVERAGE_REDUCTION_MODE_MAX_ENUM_NV = 0x7FFFFFFF
} VkCoverageReductionModeNV;
typedef VkFlags VkPipelineCoverageReductionStateCreateFlagsNV;
typedef struct VkPhysicalDeviceCoverageReductionModeFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 coverageReductionMode;
} VkPhysicalDeviceCoverageReductionModeFeaturesNV;

typedef struct VkPipelineCoverageReductionStateCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkPipelineCoverageReductionStateCreateFlagsNV flags;
 VkCoverageReductionModeNV coverageReductionMode;
} VkPipelineCoverageReductionStateCreateInfoNV;

typedef struct VkFramebufferMixedSamplesCombinationNV {
 VkStructureType sType;
 void* pNext;
 VkCoverageReductionModeNV coverageReductionMode;
 VkSampleCountFlagBits rasterizationSamples;
 VkSampleCountFlags depthStencilSamples;
 VkSampleCountFlags colorSamples;
} VkFramebufferMixedSamplesCombinationNV;

typedef VkResult (VKAPI_PTR *PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV)(VkPhysicalDevice physicalDevice, uint32_t* pCombinationCount, VkFramebufferMixedSamplesCombinationNV* pCombinations);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(
 VkPhysicalDevice physicalDevice,
 uint32_t* pCombinationCount,
 VkFramebufferMixedSamplesCombinationNV* pCombinations);
#endif

// VK_EXT_fragment_shader_interlock is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_fragment_shader_interlock 1
#define VK_EXT_FRAGMENT_SHADER_INTERLOCK_SPEC_VERSION 1
#define VK_EXT_FRAGMENT_SHADER_INTERLOCK_EXTENSION_NAME "VK_EXT_fragment_shader_interlock"
typedef struct VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 fragmentShaderSampleInterlock;
 VkBool32 fragmentShaderPixelInterlock;
 VkBool32 fragmentShaderShadingRateInterlock;
} VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT;

// VK_EXT_ycbcr_image_arrays is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_ycbcr_image_arrays 1
#define VK_EXT_YCBCR_IMAGE_ARRAYS_SPEC_VERSION 1
#define VK_EXT_YCBCR_IMAGE_ARRAYS_EXTENSION_NAME "VK_EXT_ycbcr_image_arrays"
typedef struct VkPhysicalDeviceYcbcrImageArraysFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 ycbcrImageArrays;
} VkPhysicalDeviceYcbcrImageArraysFeaturesEXT;

// VK_EXT_provoking_vertex is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_provoking_vertex 1
#define VK_EXT_PROVOKING_VERTEX_SPEC_VERSION 1
#define VK_EXT_PROVOKING_VERTEX_EXTENSION_NAME "VK_EXT_provoking_vertex"

typedef enum VkProvokingVertexModeEXT {
 VK_PROVOKING_VERTEX_MODE_FIRST_VERTEX_EXT = 0,
 VK_PROVOKING_VERTEX_MODE_LAST_VERTEX_EXT = 1,
 VK_PROVOKING_VERTEX_MODE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkProvokingVertexModeEXT;
typedef struct VkPhysicalDeviceProvokingVertexFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 provokingVertexLast;
 VkBool32 transformFeedbackPreservesProvokingVertex;
} VkPhysicalDeviceProvokingVertexFeaturesEXT;

typedef struct VkPhysicalDeviceProvokingVertexPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 provokingVertexModePerPipeline;
 VkBool32 transformFeedbackPreservesTriangleFanProvokingVertex;
} VkPhysicalDeviceProvokingVertexPropertiesEXT;

typedef struct VkPipelineRasterizationProvokingVertexStateCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkProvokingVertexModeEXT provokingVertexMode;
} VkPipelineRasterizationProvokingVertexStateCreateInfoEXT;

// VK_EXT_headless_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_headless_surface 1
#define VK_EXT_HEADLESS_SURFACE_SPEC_VERSION 1
#define VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME "VK_EXT_headless_surface"
typedef VkFlags VkHeadlessSurfaceCreateFlagsEXT;
typedef struct VkHeadlessSurfaceCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkHeadlessSurfaceCreateFlagsEXT flags;
} VkHeadlessSurfaceCreateInfoEXT;

typedef VkResult (VKAPI_PTR *PFN_vkCreateHeadlessSurfaceEXT)(VkInstance instance, const VkHeadlessSurfaceCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateHeadlessSurfaceEXT(
 VkInstance instance,
 const VkHeadlessSurfaceCreateInfoEXT* pCreateInfo,
 const VkAllocationCallbacks* pAllocator,
 VkSurfaceKHR* pSurface);
#endif

// VK_EXT_line_rasterization is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_line_rasterization 1
#define VK_EXT_LINE_RASTERIZATION_SPEC_VERSION 1
#define VK_EXT_LINE_RASTERIZATION_EXTENSION_NAME "VK_EXT_line_rasterization"

typedef enum VkLineRasterizationModeEXT {
 VK_LINE_RASTERIZATION_MODE_DEFAULT_EXT = 0,
 VK_LINE_RASTERIZATION_MODE_RECTANGULAR_EXT = 1,
 VK_LINE_RASTERIZATION_MODE_BRESENHAM_EXT = 2,
 VK_LINE_RASTERIZATION_MODE_RECTANGULAR_SMOOTH_EXT = 3,
 VK_LINE_RASTERIZATION_MODE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkLineRasterizationModeEXT;
typedef struct VkPhysicalDeviceLineRasterizationFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 rectangularLines;
 VkBool32 bresenhamLines;
 VkBool32 smoothLines;
 VkBool32 stippledRectangularLines;
 VkBool32 stippledBresenhamLines;
 VkBool32 stippledSmoothLines;
} VkPhysicalDeviceLineRasterizationFeaturesEXT;

typedef struct VkPhysicalDeviceLineRasterizationPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 uint32_t lineSubPixelPrecisionBits;
} VkPhysicalDeviceLineRasterizationPropertiesEXT;

typedef struct VkPipelineRasterizationLineStateCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkLineRasterizationModeEXT lineRasterizationMode;
 VkBool32 stippledLineEnable;
 uint32_t lineStippleFactor;
 uint16_t lineStipplePattern;
} VkPipelineRasterizationLineStateCreateInfoEXT;

typedef void (VKAPI_PTR *PFN_vkCmdSetLineStippleEXT)(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdSetLineStippleEXT(
 VkCommandBuffer commandBuffer,
 uint32_t lineStippleFactor,
 uint16_t lineStipplePattern);
#endif

// VK_EXT_shader_atomic_float is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_shader_atomic_float 1
#define VK_EXT_SHADER_ATOMIC_FLOAT_SPEC_VERSION 1
#define VK_EXT_SHADER_ATOMIC_FLOAT_EXTENSION_NAME "VK_EXT_shader_atomic_float"
typedef struct VkPhysicalDeviceShaderAtomicFloatFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 shaderBufferFloat32Atomics;
 VkBool32 shaderBufferFloat32AtomicAdd;
 VkBool32 shaderBufferFloat64Atomics;
 VkBool32 shaderBufferFloat64AtomicAdd;
 VkBool32 shaderSharedFloat32Atomics;
 VkBool32 shaderSharedFloat32AtomicAdd;
 VkBool32 shaderSharedFloat64Atomics;
 VkBool32 shaderSharedFloat64AtomicAdd;
 VkBool32 shaderImageFloat32Atomics;
 VkBool32 shaderImageFloat32AtomicAdd;
 VkBool32 sparseImageFloat32Atomics;
 VkBool32 sparseImageFloat32AtomicAdd;
} VkPhysicalDeviceShaderAtomicFloatFeaturesEXT;

// VK_EXT_host_query_reset is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_host_query_reset 1
#define VK_EXT_HOST_QUERY_RESET_SPEC_VERSION 1
#define VK_EXT_HOST_QUERY_RESET_EXTENSION_NAME "VK_EXT_host_query_reset"
typedef VkPhysicalDeviceHostQueryResetFeatures VkPhysicalDeviceHostQueryResetFeaturesEXT;

typedef void (VKAPI_PTR *PFN_vkResetQueryPoolEXT)(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkResetQueryPoolEXT(
 VkDevice device,
 VkQueryPool queryPool,
 uint32_t firstQuery,
 uint32_t queryCount);
#endif

// VK_EXT_index_type_uint8 is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_index_type_uint8 1
#define VK_EXT_INDEX_TYPE_UINT8_SPEC_VERSION 1
#define VK_EXT_INDEX_TYPE_UINT8_EXTENSION_NAME "VK_EXT_index_type_uint8"
typedef struct VkPhysicalDeviceIndexTypeUint8FeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 indexTypeUint8;
} VkPhysicalDeviceIndexTypeUint8FeaturesEXT;

// VK_EXT_extended_dynamic_state is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_extended_dynamic_state 1
#define VK_EXT_EXTENDED_DYNAMIC_STATE_SPEC_VERSION 1
#define VK_EXT_EXTENDED_DYNAMIC_STATE_EXTENSION_NAME "VK_EXT_extended_dynamic_state"
typedef struct VkPhysicalDeviceExtendedDynamicStateFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 extendedDynamicState;
} VkPhysicalDeviceExtendedDynamicStateFeaturesEXT;

typedef void (VKAPI_PTR *PFN_vkCmdSetCullModeEXT)(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode);
typedef void (VKAPI_PTR *PFN_vkCmdSetFrontFaceEXT)(VkCommandBuffer commandBuffer, VkFrontFace frontFace);
typedef void (VKAPI_PTR *PFN_vkCmdSetPrimitiveTopologyEXT)(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology);
typedef void (VKAPI_PTR *PFN_vkCmdSetViewportWithCountEXT)(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports);
typedef void (VKAPI_PTR *PFN_vkCmdSetScissorWithCountEXT)(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors);
typedef void (VKAPI_PTR *PFN_vkCmdBindVertexBuffers2EXT)(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides);
typedef void (VKAPI_PTR *PFN_vkCmdSetDepthTestEnableEXT)(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable);
typedef void (VKAPI_PTR *PFN_vkCmdSetDepthWriteEnableEXT)(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable);
typedef void (VKAPI_PTR *PFN_vkCmdSetDepthCompareOpEXT)(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp);
typedef void (VKAPI_PTR *PFN_vkCmdSetDepthBoundsTestEnableEXT)(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable);
typedef void (VKAPI_PTR *PFN_vkCmdSetStencilTestEnableEXT)(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable);
typedef void (VKAPI_PTR *PFN_vkCmdSetStencilOpEXT)(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdSetCullModeEXT(
 VkCommandBuffer commandBuffer,
 VkCullModeFlags cullMode);

VKAPI_ATTR void VKAPI_CALL vkCmdSetFrontFaceEXT(
 VkCommandBuffer commandBuffer,
 VkFrontFace frontFace);

VKAPI_ATTR void VKAPI_CALL vkCmdSetPrimitiveTopologyEXT(
 VkCommandBuffer commandBuffer,
 VkPrimitiveTopology primitiveTopology);

VKAPI_ATTR void VKAPI_CALL vkCmdSetViewportWithCountEXT(
 VkCommandBuffer commandBuffer,
 uint32_t viewportCount,
 const VkViewport* pViewports);

VKAPI_ATTR void VKAPI_CALL vkCmdSetScissorWithCountEXT(
 VkCommandBuffer commandBuffer,
 uint32_t scissorCount,
 const VkRect2D* pScissors);

VKAPI_ATTR void VKAPI_CALL vkCmdBindVertexBuffers2EXT(
 VkCommandBuffer commandBuffer,
 uint32_t firstBinding,
 uint32_t bindingCount,
 const VkBuffer* pBuffers,
 const VkDeviceSize* pOffsets,
 const VkDeviceSize* pSizes,
 const VkDeviceSize* pStrides);

VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthTestEnableEXT(
 VkCommandBuffer commandBuffer,
 VkBool32 depthTestEnable);

VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthWriteEnableEXT(
 VkCommandBuffer commandBuffer,
 VkBool32 depthWriteEnable);

VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthCompareOpEXT(
 VkCommandBuffer commandBuffer,
 VkCompareOp depthCompareOp);

VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthBoundsTestEnableEXT(
 VkCommandBuffer commandBuffer,
 VkBool32 depthBoundsTestEnable);

VKAPI_ATTR void VKAPI_CALL vkCmdSetStencilTestEnableEXT(
 VkCommandBuffer commandBuffer,
 VkBool32 stencilTestEnable);

VKAPI_ATTR void VKAPI_CALL vkCmdSetStencilOpEXT(
 VkCommandBuffer commandBuffer,
 VkStencilFaceFlags faceMask,
 VkStencilOp failOp,
 VkStencilOp passOp,
 VkStencilOp depthFailOp,
 VkCompareOp compareOp);
#endif

// VK_EXT_host_image_copy is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_host_image_copy 1
#define VK_EXT_HOST_IMAGE_COPY_SPEC_VERSION 1
#define VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME "VK_EXT_host_image_copy"

typedef enum VkHostImageCopyFlagBitsEXT {
 VK_HOST_IMAGE_COPY_MEMCPY_EXT = 0x00000001,
 VK_HOST_IMAGE_COPY_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkHostImageCopyFlagBitsEXT;
typedef VkFlags VkHostImageCopyFlagsEXT;
typedef struct VkPhysicalDeviceHostImageCopyFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 hostImageCopy;
} VkPhysicalDeviceHostImageCopyFeaturesEXT;

typedef struct VkPhysicalDeviceHostImageCopyPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 uint32_t copySrcLayoutCount;
 VkImageLayout* pCopySrcLayouts;
 uint32_t copyDstLayoutCount;
 VkImageLayout* pCopyDstLayouts;
 uint8_t optimalTilingLayoutUUID[VK_UUID_SIZE];
 VkBool32 identicalMemoryTypeRequirements;
} VkPhysicalDeviceHostImageCopyPropertiesEXT;

typedef struct VkMemoryToImageCopyEXT {
 VkStructureType sType;
 const void* pNext;
 const void* pHostPointer;
 uint32_t memoryRowLength;
 uint32_t memoryImageHeight;
 VkImageSubresourceLayers imageSubresource;
 VkOffset3D imageOffset;
 VkExtent3D imageExtent;
} VkMemoryToImageCopyEXT;

typedef struct VkImageToMemoryCopyEXT {
 VkStructureType sType;
 const void* pNext;
 void* pHostPointer;
 uint32_t memoryRowLength;
 uint32_t memoryImageHeight;
 VkImageSubresourceLayers imageSubresource;
 VkOffset3D imageOffset;
 VkExtent3D imageExtent;
} VkImageToMemoryCopyEXT;

typedef struct VkCopyMemoryToImageInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkHostImageCopyFlagsEXT flags;
 VkImage dstImage;
 VkImageLayout dstImageLayout;
 uint32_t regionCount;
 const VkMemoryToImageCopyEXT* pRegions;
} VkCopyMemoryToImageInfoEXT;

typedef struct VkCopyImageToMemoryInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkHostImageCopyFlagsEXT flags;
 VkImage srcImage;
 VkImageLayout srcImageLayout;
 uint32_t regionCount;
 const VkImageToMemoryCopyEXT* pRegions;
} VkCopyImageToMemoryInfoEXT;

typedef struct VkCopyImageToImageInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkHostImageCopyFlagsEXT flags;
 VkImage srcImage;
 VkImageLayout srcImageLayout;
 VkImage dstImage;
 VkImageLayout dstImageLayout;
 uint32_t regionCount;
 const VkImageCopy2* pRegions;
} VkCopyImageToImageInfoEXT;

typedef struct VkHostImageLayoutTransitionInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkImage image;
 VkImageLayout oldLayout;
 VkImageLayout newLayout;
 VkImageSubresourceRange subresourceRange;
} VkHostImageLayoutTransitionInfoEXT;

typedef struct VkSubresourceHostMemcpySizeEXT {
 VkStructureType sType;
 void* pNext;
 VkDeviceSize size;
} VkSubresourceHostMemcpySizeEXT;

typedef struct VkHostImageCopyDevicePerformanceQueryEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 optimalDeviceAccess;
 VkBool32 identicalMemoryLayout;
} VkHostImageCopyDevicePerformanceQueryEXT;

typedef VkSubresourceLayout2KHR VkSubresourceLayout2EXT;

typedef VkImageSubresource2KHR VkImageSubresource2EXT;

typedef VkResult (VKAPI_PTR *PFN_vkCopyMemoryToImageEXT)(VkDevice device, const VkCopyMemoryToImageInfoEXT* pCopyMemoryToImageInfo);
typedef VkResult (VKAPI_PTR *PFN_vkCopyImageToMemoryEXT)(VkDevice device, const VkCopyImageToMemoryInfoEXT* pCopyImageToMemoryInfo);
typedef VkResult (VKAPI_PTR *PFN_vkCopyImageToImageEXT)(VkDevice device, const VkCopyImageToImageInfoEXT* pCopyImageToImageInfo);
typedef VkResult (VKAPI_PTR *PFN_vkTransitionImageLayoutEXT)(VkDevice device, uint32_t transitionCount, const VkHostImageLayoutTransitionInfoEXT* pTransitions);
typedef void (VKAPI_PTR *PFN_vkGetImageSubresourceLayout2EXT)(VkDevice device, VkImage image, const VkImageSubresource2KHR* pSubresource, VkSubresourceLayout2KHR* pLayout);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCopyMemoryToImageEXT(
 VkDevice device,
 const VkCopyMemoryToImageInfoEXT* pCopyMemoryToImageInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkCopyImageToMemoryEXT(
 VkDevice device,
 const VkCopyImageToMemoryInfoEXT* pCopyImageToMemoryInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkCopyImageToImageEXT(
 VkDevice device,
 const VkCopyImageToImageInfoEXT* pCopyImageToImageInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkTransitionImageLayoutEXT(
 VkDevice device,
 uint32_t transitionCount,
 const VkHostImageLayoutTransitionInfoEXT* pTransitions);

VKAPI_ATTR void VKAPI_CALL vkGetImageSubresourceLayout2EXT(
 VkDevice device,
 VkImage image,
 const VkImageSubresource2KHR* pSubresource,
 VkSubresourceLayout2KHR* pLayout);
#endif

// VK_EXT_shader_atomic_float2 is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_shader_atomic_float2 1
#define VK_EXT_SHADER_ATOMIC_FLOAT_2_SPEC_VERSION 1
#define VK_EXT_SHADER_ATOMIC_FLOAT_2_EXTENSION_NAME "VK_EXT_shader_atomic_float2"
typedef struct VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 shaderBufferFloat16Atomics;
 VkBool32 shaderBufferFloat16AtomicAdd;
 VkBool32 shaderBufferFloat16AtomicMinMax;
 VkBool32 shaderBufferFloat32AtomicMinMax;
 VkBool32 shaderBufferFloat64AtomicMinMax;
 VkBool32 shaderSharedFloat16Atomics;
 VkBool32 shaderSharedFloat16AtomicAdd;
 VkBool32 shaderSharedFloat16AtomicMinMax;
 VkBool32 shaderSharedFloat32AtomicMinMax;
 VkBool32 shaderSharedFloat64AtomicMinMax;
 VkBool32 shaderImageFloat32AtomicMinMax;
 VkBool32 sparseImageFloat32AtomicMinMax;
} VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT;

// VK_EXT_surface_maintenance1 is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_surface_maintenance1 1
#define VK_EXT_SURFACE_MAINTENANCE_1_SPEC_VERSION 1
#define VK_EXT_SURFACE_MAINTENANCE_1_EXTENSION_NAME "VK_EXT_surface_maintenance1"

typedef enum VkPresentScalingFlagBitsEXT {
 VK_PRESENT_SCALING_ONE_TO_ONE_BIT_EXT = 0x00000001,
 VK_PRESENT_SCALING_ASPECT_RATIO_STRETCH_BIT_EXT = 0x00000002,
 VK_PRESENT_SCALING_STRETCH_BIT_EXT = 0x00000004,
 VK_PRESENT_SCALING_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkPresentScalingFlagBitsEXT;
typedef VkFlags VkPresentScalingFlagsEXT;

typedef enum VkPresentGravityFlagBitsEXT {
 VK_PRESENT_GRAVITY_MIN_BIT_EXT = 0x00000001,
 VK_PRESENT_GRAVITY_MAX_BIT_EXT = 0x00000002,
 VK_PRESENT_GRAVITY_CENTERED_BIT_EXT = 0x00000004,
 VK_PRESENT_GRAVITY_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkPresentGravityFlagBitsEXT;
typedef VkFlags VkPresentGravityFlagsEXT;
typedef struct VkSurfacePresentModeEXT {
 VkStructureType sType;
 void* pNext;
 VkPresentModeKHR presentMode;
} VkSurfacePresentModeEXT;

typedef struct VkSurfacePresentScalingCapabilitiesEXT {
 VkStructureType sType;
 void* pNext;
 VkPresentScalingFlagsEXT supportedPresentScaling;
 VkPresentGravityFlagsEXT supportedPresentGravityX;
 VkPresentGravityFlagsEXT supportedPresentGravityY;
 VkExtent2D minScaledImageExtent;
 VkExtent2D maxScaledImageExtent;
} VkSurfacePresentScalingCapabilitiesEXT;

typedef struct VkSurfacePresentModeCompatibilityEXT {
 VkStructureType sType;
 void* pNext;
 uint32_t presentModeCount;
 VkPresentModeKHR* pPresentModes;
} VkSurfacePresentModeCompatibilityEXT;

// VK_EXT_swapchain_maintenance1 is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_swapchain_maintenance1 1
#define VK_EXT_SWAPCHAIN_MAINTENANCE_1_SPEC_VERSION 1
#define VK_EXT_SWAPCHAIN_MAINTENANCE_1_EXTENSION_NAME "VK_EXT_swapchain_maintenance1"
typedef struct VkPhysicalDeviceSwapchainMaintenance1FeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 swapchainMaintenance1;
} VkPhysicalDeviceSwapchainMaintenance1FeaturesEXT;

typedef struct VkSwapchainPresentFenceInfoEXT {
 VkStructureType sType;
 const void* pNext;
 uint32_t swapchainCount;
 const VkFence* pFences;
} VkSwapchainPresentFenceInfoEXT;

typedef struct VkSwapchainPresentModesCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 uint32_t presentModeCount;
 const VkPresentModeKHR* pPresentModes;
} VkSwapchainPresentModesCreateInfoEXT;

typedef struct VkSwapchainPresentModeInfoEXT {
 VkStructureType sType;
 const void* pNext;
 uint32_t swapchainCount;
 const VkPresentModeKHR* pPresentModes;
} VkSwapchainPresentModeInfoEXT;

typedef struct VkSwapchainPresentScalingCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkPresentScalingFlagsEXT scalingBehavior;
 VkPresentGravityFlagsEXT presentGravityX;
 VkPresentGravityFlagsEXT presentGravityY;
} VkSwapchainPresentScalingCreateInfoEXT;

typedef struct VkReleaseSwapchainImagesInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkSwapchainKHR swapchain;
 uint32_t imageIndexCount;
 const uint32_t* pImageIndices;
} VkReleaseSwapchainImagesInfoEXT;

typedef VkResult (VKAPI_PTR *PFN_vkReleaseSwapchainImagesEXT)(VkDevice device, const VkReleaseSwapchainImagesInfoEXT* pReleaseInfo);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkReleaseSwapchainImagesEXT(
 VkDevice device,
 const VkReleaseSwapchainImagesInfoEXT* pReleaseInfo);
#endif

// VK_EXT_shader_demote_to_helper_invocation is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_shader_demote_to_helper_invocation 1
#define VK_EXT_SHADER_DEMOTE_TO_HELPER_INVOCATION_SPEC_VERSION 1
#define VK_EXT_SHADER_DEMOTE_TO_HELPER_INVOCATION_EXTENSION_NAME "VK_EXT_shader_demote_to_helper_invocation"
typedef VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures VkPhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT;

// VK_NV_device_generated_commands is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_device_generated_commands 1
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkIndirectCommandsLayoutNV)
#define VK_NV_DEVICE_GENERATED_COMMANDS_SPEC_VERSION 3
#define VK_NV_DEVICE_GENERATED_COMMANDS_EXTENSION_NAME "VK_NV_device_generated_commands"

typedef enum VkIndirectCommandsTokenTypeNV {
 VK_INDIRECT_COMMANDS_TOKEN_TYPE_SHADER_GROUP_NV = 0,
 VK_INDIRECT_COMMANDS_TOKEN_TYPE_STATE_FLAGS_NV = 1,
 VK_INDIRECT_COMMANDS_TOKEN_TYPE_INDEX_BUFFER_NV = 2,
 VK_INDIRECT_COMMANDS_TOKEN_TYPE_VERTEX_BUFFER_NV = 3,
 VK_INDIRECT_COMMANDS_TOKEN_TYPE_PUSH_CONSTANT_NV = 4,
 VK_INDIRECT_COMMANDS_TOKEN_TYPE_DRAW_INDEXED_NV = 5,
 VK_INDIRECT_COMMANDS_TOKEN_TYPE_DRAW_NV = 6,
 VK_INDIRECT_COMMANDS_TOKEN_TYPE_DRAW_TASKS_NV = 7,
 VK_INDIRECT_COMMANDS_TOKEN_TYPE_DRAW_MESH_TASKS_NV = 1000328000,
 VK_INDIRECT_COMMANDS_TOKEN_TYPE_PIPELINE_NV = 1000428003,
 VK_INDIRECT_COMMANDS_TOKEN_TYPE_DISPATCH_NV = 1000428004,
 VK_INDIRECT_COMMANDS_TOKEN_TYPE_MAX_ENUM_NV = 0x7FFFFFFF
} VkIndirectCommandsTokenTypeNV;

typedef enum VkIndirectStateFlagBitsNV {
 VK_INDIRECT_STATE_FLAG_FRONTFACE_BIT_NV = 0x00000001,
 VK_INDIRECT_STATE_FLAG_BITS_MAX_ENUM_NV = 0x7FFFFFFF
} VkIndirectStateFlagBitsNV;
typedef VkFlags VkIndirectStateFlagsNV;

typedef enum VkIndirectCommandsLayoutUsageFlagBitsNV {
 VK_INDIRECT_COMMANDS_LAYOUT_USAGE_EXPLICIT_PREPROCESS_BIT_NV = 0x00000001,
 VK_INDIRECT_COMMANDS_LAYOUT_USAGE_INDEXED_SEQUENCES_BIT_NV = 0x00000002,
 VK_INDIRECT_COMMANDS_LAYOUT_USAGE_UNORDERED_SEQUENCES_BIT_NV = 0x00000004,
 VK_INDIRECT_COMMANDS_LAYOUT_USAGE_FLAG_BITS_MAX_ENUM_NV = 0x7FFFFFFF
} VkIndirectCommandsLayoutUsageFlagBitsNV;
typedef VkFlags VkIndirectCommandsLayoutUsageFlagsNV;
typedef struct VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV {
 VkStructureType sType;
 void* pNext;
 uint32_t maxGraphicsShaderGroupCount;
 uint32_t maxIndirectSequenceCount;
 uint32_t maxIndirectCommandsTokenCount;
 uint32_t maxIndirectCommandsStreamCount;
 uint32_t maxIndirectCommandsTokenOffset;
 uint32_t maxIndirectCommandsStreamStride;
 uint32_t minSequencesCountBufferOffsetAlignment;
 uint32_t minSequencesIndexBufferOffsetAlignment;
 uint32_t minIndirectCommandsBufferOffsetAlignment;
} VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV;

typedef struct VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 deviceGeneratedCommands;
} VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV;

typedef struct VkGraphicsShaderGroupCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 uint32_t stageCount;
 const VkPipelineShaderStageCreateInfo* pStages;
 const VkPipelineVertexInputStateCreateInfo* pVertexInputState;
 const VkPipelineTessellationStateCreateInfo* pTessellationState;
} VkGraphicsShaderGroupCreateInfoNV;

typedef struct VkGraphicsPipelineShaderGroupsCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 uint32_t groupCount;
 const VkGraphicsShaderGroupCreateInfoNV* pGroups;
 uint32_t pipelineCount;
 const VkPipeline* pPipelines;
} VkGraphicsPipelineShaderGroupsCreateInfoNV;

typedef struct VkBindShaderGroupIndirectCommandNV {
 uint32_t groupIndex;
} VkBindShaderGroupIndirectCommandNV;

typedef struct VkBindIndexBufferIndirectCommandNV {
 VkDeviceAddress bufferAddress;
 uint32_t size;
 VkIndexType indexType;
} VkBindIndexBufferIndirectCommandNV;

typedef struct VkBindVertexBufferIndirectCommandNV {
 VkDeviceAddress bufferAddress;
 uint32_t size;
 uint32_t stride;
} VkBindVertexBufferIndirectCommandNV;

typedef struct VkSetStateFlagsIndirectCommandNV {
 uint32_t data;
} VkSetStateFlagsIndirectCommandNV;

typedef struct VkIndirectCommandsStreamNV {
 VkBuffer buffer;
 VkDeviceSize offset;
} VkIndirectCommandsStreamNV;

typedef struct VkIndirectCommandsLayoutTokenNV {
 VkStructureType sType;
 const void* pNext;
 VkIndirectCommandsTokenTypeNV tokenType;
 uint32_t stream;
 uint32_t offset;
 uint32_t vertexBindingUnit;
 VkBool32 vertexDynamicStride;
 VkPipelineLayout pushconstantPipelineLayout;
 VkShaderStageFlags pushconstantShaderStageFlags;
 uint32_t pushconstantOffset;
 uint32_t pushconstantSize;
 VkIndirectStateFlagsNV indirectStateFlags;
 uint32_t indexTypeCount;
 const VkIndexType* pIndexTypes;
 const uint32_t* pIndexTypeValues;
} VkIndirectCommandsLayoutTokenNV;

typedef struct VkIndirectCommandsLayoutCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkIndirectCommandsLayoutUsageFlagsNV flags;
 VkPipelineBindPoint pipelineBindPoint;
 uint32_t tokenCount;
 const VkIndirectCommandsLayoutTokenNV* pTokens;
 uint32_t streamCount;
 const uint32_t* pStreamStrides;
} VkIndirectCommandsLayoutCreateInfoNV;

typedef struct VkGeneratedCommandsInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkPipelineBindPoint pipelineBindPoint;
 VkPipeline pipeline;
 VkIndirectCommandsLayoutNV indirectCommandsLayout;
 uint32_t streamCount;
 const VkIndirectCommandsStreamNV* pStreams;
 uint32_t sequencesCount;
 VkBuffer preprocessBuffer;
 VkDeviceSize preprocessOffset;
 VkDeviceSize preprocessSize;
 VkBuffer sequencesCountBuffer;
 VkDeviceSize sequencesCountOffset;
 VkBuffer sequencesIndexBuffer;
 VkDeviceSize sequencesIndexOffset;
} VkGeneratedCommandsInfoNV;

typedef struct VkGeneratedCommandsMemoryRequirementsInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkPipelineBindPoint pipelineBindPoint;
 VkPipeline pipeline;
 VkIndirectCommandsLayoutNV indirectCommandsLayout;
 uint32_t maxSequencesCount;
} VkGeneratedCommandsMemoryRequirementsInfoNV;

typedef void (VKAPI_PTR *PFN_vkGetGeneratedCommandsMemoryRequirementsNV)(VkDevice device, const VkGeneratedCommandsMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2* pMemoryRequirements);
typedef void (VKAPI_PTR *PFN_vkCmdPreprocessGeneratedCommandsNV)(VkCommandBuffer commandBuffer, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo);
typedef void (VKAPI_PTR *PFN_vkCmdExecuteGeneratedCommandsNV)(VkCommandBuffer commandBuffer, VkBool32 isPreprocessed, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo);
typedef void (VKAPI_PTR *PFN_vkCmdBindPipelineShaderGroupNV)(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline, uint32_t groupIndex);
typedef VkResult (VKAPI_PTR *PFN_vkCreateIndirectCommandsLayoutNV)(VkDevice device, const VkIndirectCommandsLayoutCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectCommandsLayoutNV* pIndirectCommandsLayout);
typedef void (VKAPI_PTR *PFN_vkDestroyIndirectCommandsLayoutNV)(VkDevice device, VkIndirectCommandsLayoutNV indirectCommandsLayout, const VkAllocationCallbacks* pAllocator);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkGetGeneratedCommandsMemoryRequirementsNV(
 VkDevice device,
 const VkGeneratedCommandsMemoryRequirementsInfoNV* pInfo,
 VkMemoryRequirements2* pMemoryRequirements);

VKAPI_ATTR void VKAPI_CALL vkCmdPreprocessGeneratedCommandsNV(
 VkCommandBuffer commandBuffer,
 const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdExecuteGeneratedCommandsNV(
 VkCommandBuffer commandBuffer,
 VkBool32 isPreprocessed,
 const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdBindPipelineShaderGroupNV(
 VkCommandBuffer commandBuffer,
 VkPipelineBindPoint pipelineBindPoint,
 VkPipeline pipeline,
 uint32_t groupIndex);

VKAPI_ATTR VkResult VKAPI_CALL vkCreateIndirectCommandsLayoutNV(
 VkDevice device,
 const VkIndirectCommandsLayoutCreateInfoNV* pCreateInfo,
 const VkAllocationCallbacks* pAllocator,
 VkIndirectCommandsLayoutNV* pIndirectCommandsLayout);

VKAPI_ATTR void VKAPI_CALL vkDestroyIndirectCommandsLayoutNV(
 VkDevice device,
 VkIndirectCommandsLayoutNV indirectCommandsLayout,
 const VkAllocationCallbacks* pAllocator);
#endif

// VK_NV_inherited_viewport_scissor is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_inherited_viewport_scissor 1
#define VK_NV_INHERITED_VIEWPORT_SCISSOR_SPEC_VERSION 1
#define VK_NV_INHERITED_VIEWPORT_SCISSOR_EXTENSION_NAME "VK_NV_inherited_viewport_scissor"
typedef struct VkPhysicalDeviceInheritedViewportScissorFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 inheritedViewportScissor2D;
} VkPhysicalDeviceInheritedViewportScissorFeaturesNV;

typedef struct VkCommandBufferInheritanceViewportScissorInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkBool32 viewportScissor2D;
 uint32_t viewportDepthCount;
 const VkViewport* pViewportDepths;
} VkCommandBufferInheritanceViewportScissorInfoNV;

// VK_EXT_texel_buffer_alignment is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_texel_buffer_alignment 1
#define VK_EXT_TEXEL_BUFFER_ALIGNMENT_SPEC_VERSION 1
#define VK_EXT_TEXEL_BUFFER_ALIGNMENT_EXTENSION_NAME "VK_EXT_texel_buffer_alignment"
typedef struct VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 texelBufferAlignment;
} VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT;

typedef VkPhysicalDeviceTexelBufferAlignmentProperties VkPhysicalDeviceTexelBufferAlignmentPropertiesEXT;

// VK_QCOM_render_pass_transform is a preprocessor guard. Do not pass it to API calls.
#define VK_QCOM_render_pass_transform 1
#define VK_QCOM_RENDER_PASS_TRANSFORM_SPEC_VERSION 4
#define VK_QCOM_RENDER_PASS_TRANSFORM_EXTENSION_NAME "VK_QCOM_render_pass_transform"
typedef struct VkRenderPassTransformBeginInfoQCOM {
 VkStructureType sType;
 void* pNext;
 VkSurfaceTransformFlagBitsKHR transform;
} VkRenderPassTransformBeginInfoQCOM;

typedef struct VkCommandBufferInheritanceRenderPassTransformInfoQCOM {
 VkStructureType sType;
 void* pNext;
 VkSurfaceTransformFlagBitsKHR transform;
 VkRect2D renderArea;
} VkCommandBufferInheritanceRenderPassTransformInfoQCOM;

// VK_EXT_depth_bias_control is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_depth_bias_control 1
#define VK_EXT_DEPTH_BIAS_CONTROL_SPEC_VERSION 1
#define VK_EXT_DEPTH_BIAS_CONTROL_EXTENSION_NAME "VK_EXT_depth_bias_control"

typedef enum VkDepthBiasRepresentationEXT {
 VK_DEPTH_BIAS_REPRESENTATION_LEAST_REPRESENTABLE_VALUE_FORMAT_EXT = 0,
 VK_DEPTH_BIAS_REPRESENTATION_LEAST_REPRESENTABLE_VALUE_FORCE_UNORM_EXT = 1,
 VK_DEPTH_BIAS_REPRESENTATION_FLOAT_EXT = 2,
 VK_DEPTH_BIAS_REPRESENTATION_MAX_ENUM_EXT = 0x7FFFFFFF
} VkDepthBiasRepresentationEXT;
typedef struct VkPhysicalDeviceDepthBiasControlFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 depthBiasControl;
 VkBool32 leastRepresentableValueForceUnormRepresentation;
 VkBool32 floatRepresentation;
 VkBool32 depthBiasExact;
} VkPhysicalDeviceDepthBiasControlFeaturesEXT;

typedef struct VkDepthBiasInfoEXT {
 VkStructureType sType;
 const void* pNext;
 float depthBiasConstantFactor;
 float depthBiasClamp;
 float depthBiasSlopeFactor;
} VkDepthBiasInfoEXT;

typedef struct VkDepthBiasRepresentationInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkDepthBiasRepresentationEXT depthBiasRepresentation;
 VkBool32 depthBiasExact;
} VkDepthBiasRepresentationInfoEXT;

typedef void (VKAPI_PTR *PFN_vkCmdSetDepthBias2EXT)(VkCommandBuffer commandBuffer, const VkDepthBiasInfoEXT* pDepthBiasInfo);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthBias2EXT(
 VkCommandBuffer commandBuffer,
 const VkDepthBiasInfoEXT* pDepthBiasInfo);
#endif

// VK_EXT_device_memory_report is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_device_memory_report 1
#define VK_EXT_DEVICE_MEMORY_REPORT_SPEC_VERSION 2
#define VK_EXT_DEVICE_MEMORY_REPORT_EXTENSION_NAME "VK_EXT_device_memory_report"

typedef enum VkDeviceMemoryReportEventTypeEXT {
 VK_DEVICE_MEMORY_REPORT_EVENT_TYPE_ALLOCATE_EXT = 0,
 VK_DEVICE_MEMORY_REPORT_EVENT_TYPE_FREE_EXT = 1,
 VK_DEVICE_MEMORY_REPORT_EVENT_TYPE_IMPORT_EXT = 2,
 VK_DEVICE_MEMORY_REPORT_EVENT_TYPE_UNIMPORT_EXT = 3,
 VK_DEVICE_MEMORY_REPORT_EVENT_TYPE_ALLOCATION_FAILED_EXT = 4,
 VK_DEVICE_MEMORY_REPORT_EVENT_TYPE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkDeviceMemoryReportEventTypeEXT;
typedef VkFlags VkDeviceMemoryReportFlagsEXT;
typedef struct VkPhysicalDeviceDeviceMemoryReportFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 deviceMemoryReport;
} VkPhysicalDeviceDeviceMemoryReportFeaturesEXT;

typedef struct VkDeviceMemoryReportCallbackDataEXT {
 VkStructureType sType;
 void* pNext;
 VkDeviceMemoryReportFlagsEXT flags;
 VkDeviceMemoryReportEventTypeEXT type;
 uint64_t memoryObjectId;
 VkDeviceSize size;
 VkObjectType objectType;
 uint64_t objectHandle;
 uint32_t heapIndex;
} VkDeviceMemoryReportCallbackDataEXT;

typedef void (VKAPI_PTR *PFN_vkDeviceMemoryReportCallbackEXT)(
 const VkDeviceMemoryReportCallbackDataEXT* pCallbackData,
 void* pUserData);

typedef struct VkDeviceDeviceMemoryReportCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkDeviceMemoryReportFlagsEXT flags;
 PFN_vkDeviceMemoryReportCallbackEXT pfnUserCallback;
 void* pUserData;
} VkDeviceDeviceMemoryReportCreateInfoEXT;

// VK_EXT_acquire_drm_display is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_acquire_drm_display 1
#define VK_EXT_ACQUIRE_DRM_DISPLAY_SPEC_VERSION 1
#define VK_EXT_ACQUIRE_DRM_DISPLAY_EXTENSION_NAME "VK_EXT_acquire_drm_display"
typedef VkResult (VKAPI_PTR *PFN_vkAcquireDrmDisplayEXT)(VkPhysicalDevice physicalDevice, int32_t drmFd, VkDisplayKHR display);
typedef VkResult (VKAPI_PTR *PFN_vkGetDrmDisplayEXT)(VkPhysicalDevice physicalDevice, int32_t drmFd, uint32_t connectorId, VkDisplayKHR* display);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkAcquireDrmDisplayEXT(
 VkPhysicalDevice physicalDevice,
 int32_t drmFd,
 VkDisplayKHR display);

VKAPI_ATTR VkResult VKAPI_CALL vkGetDrmDisplayEXT(
 VkPhysicalDevice physicalDevice,
 int32_t drmFd,
 uint32_t connectorId,
 VkDisplayKHR* display);
#endif

// VK_EXT_robustness2 is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_robustness2 1
#define VK_EXT_ROBUSTNESS_2_SPEC_VERSION 1
#define VK_EXT_ROBUSTNESS_2_EXTENSION_NAME "VK_EXT_robustness2"
typedef struct VkPhysicalDeviceRobustness2FeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 robustBufferAccess2;
 VkBool32 robustImageAccess2;
 VkBool32 nullDescriptor;
} VkPhysicalDeviceRobustness2FeaturesEXT;

typedef struct VkPhysicalDeviceRobustness2PropertiesEXT {
 VkStructureType sType;
 void* pNext;
 VkDeviceSize robustStorageBufferAccessSizeAlignment;
 VkDeviceSize robustUniformBufferAccessSizeAlignment;
} VkPhysicalDeviceRobustness2PropertiesEXT;

// VK_EXT_custom_border_color is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_custom_border_color 1
#define VK_EXT_CUSTOM_BORDER_COLOR_SPEC_VERSION 12
#define VK_EXT_CUSTOM_BORDER_COLOR_EXTENSION_NAME "VK_EXT_custom_border_color"
typedef struct VkSamplerCustomBorderColorCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkClearColorValue customBorderColor;
 VkFormat format;
} VkSamplerCustomBorderColorCreateInfoEXT;

typedef struct VkPhysicalDeviceCustomBorderColorPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 uint32_t maxCustomBorderColorSamplers;
} VkPhysicalDeviceCustomBorderColorPropertiesEXT;

typedef struct VkPhysicalDeviceCustomBorderColorFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 customBorderColors;
 VkBool32 customBorderColorWithoutFormat;
} VkPhysicalDeviceCustomBorderColorFeaturesEXT;

// VK_GOOGLE_user_type is a preprocessor guard. Do not pass it to API calls.
#define VK_GOOGLE_user_type 1
#define VK_GOOGLE_USER_TYPE_SPEC_VERSION 1
#define VK_GOOGLE_USER_TYPE_EXTENSION_NAME "VK_GOOGLE_user_type"

// VK_NV_present_barrier is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_present_barrier 1
#define VK_NV_PRESENT_BARRIER_SPEC_VERSION 1
#define VK_NV_PRESENT_BARRIER_EXTENSION_NAME "VK_NV_present_barrier"
typedef struct VkPhysicalDevicePresentBarrierFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 presentBarrier;
} VkPhysicalDevicePresentBarrierFeaturesNV;

typedef struct VkSurfaceCapabilitiesPresentBarrierNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 presentBarrierSupported;
} VkSurfaceCapabilitiesPresentBarrierNV;

typedef struct VkSwapchainPresentBarrierCreateInfoNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 presentBarrierEnable;
} VkSwapchainPresentBarrierCreateInfoNV;

// VK_EXT_private_data is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_private_data 1
typedef VkPrivateDataSlot VkPrivateDataSlotEXT;

#define VK_EXT_PRIVATE_DATA_SPEC_VERSION 1
#define VK_EXT_PRIVATE_DATA_EXTENSION_NAME "VK_EXT_private_data"
typedef VkPrivateDataSlotCreateFlags VkPrivateDataSlotCreateFlagsEXT;

typedef VkPhysicalDevicePrivateDataFeatures VkPhysicalDevicePrivateDataFeaturesEXT;

typedef VkDevicePrivateDataCreateInfo VkDevicePrivateDataCreateInfoEXT;

typedef VkPrivateDataSlotCreateInfo VkPrivateDataSlotCreateInfoEXT;

typedef VkResult (VKAPI_PTR *PFN_vkCreatePrivateDataSlotEXT)(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot);
typedef void (VKAPI_PTR *PFN_vkDestroyPrivateDataSlotEXT)(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator);
typedef VkResult (VKAPI_PTR *PFN_vkSetPrivateDataEXT)(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data);
typedef void (VKAPI_PTR *PFN_vkGetPrivateDataEXT)(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreatePrivateDataSlotEXT(
 VkDevice device,
 const VkPrivateDataSlotCreateInfo* pCreateInfo,
 const VkAllocationCallbacks* pAllocator,
 VkPrivateDataSlot* pPrivateDataSlot);

VKAPI_ATTR void VKAPI_CALL vkDestroyPrivateDataSlotEXT(
 VkDevice device,
 VkPrivateDataSlot privateDataSlot,
 const VkAllocationCallbacks* pAllocator);

VKAPI_ATTR VkResult VKAPI_CALL vkSetPrivateDataEXT(
 VkDevice device,
 VkObjectType objectType,
 uint64_t objectHandle,
 VkPrivateDataSlot privateDataSlot,
 uint64_t data);

VKAPI_ATTR void VKAPI_CALL vkGetPrivateDataEXT(
 VkDevice device,
 VkObjectType objectType,
 uint64_t objectHandle,
 VkPrivateDataSlot privateDataSlot,
 uint64_t* pData);
#endif

// VK_EXT_pipeline_creation_cache_control is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_pipeline_creation_cache_control 1
#define VK_EXT_PIPELINE_CREATION_CACHE_CONTROL_SPEC_VERSION 3
#define VK_EXT_PIPELINE_CREATION_CACHE_CONTROL_EXTENSION_NAME "VK_EXT_pipeline_creation_cache_control"
typedef VkPhysicalDevicePipelineCreationCacheControlFeatures VkPhysicalDevicePipelineCreationCacheControlFeaturesEXT;

// VK_NV_device_diagnostics_config is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_device_diagnostics_config 1
#define VK_NV_DEVICE_DIAGNOSTICS_CONFIG_SPEC_VERSION 2
#define VK_NV_DEVICE_DIAGNOSTICS_CONFIG_EXTENSION_NAME "VK_NV_device_diagnostics_config"

typedef enum VkDeviceDiagnosticsConfigFlagBitsNV {
 VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_SHADER_DEBUG_INFO_BIT_NV = 0x00000001,
 VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_RESOURCE_TRACKING_BIT_NV = 0x00000002,
 VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_AUTOMATIC_CHECKPOINTS_BIT_NV = 0x00000004,
 VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_SHADER_ERROR_REPORTING_BIT_NV = 0x00000008,
 VK_DEVICE_DIAGNOSTICS_CONFIG_FLAG_BITS_MAX_ENUM_NV = 0x7FFFFFFF
} VkDeviceDiagnosticsConfigFlagBitsNV;
typedef VkFlags VkDeviceDiagnosticsConfigFlagsNV;
typedef struct VkPhysicalDeviceDiagnosticsConfigFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 diagnosticsConfig;
} VkPhysicalDeviceDiagnosticsConfigFeaturesNV;

typedef struct VkDeviceDiagnosticsConfigCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkDeviceDiagnosticsConfigFlagsNV flags;
} VkDeviceDiagnosticsConfigCreateInfoNV;

// VK_QCOM_render_pass_store_ops is a preprocessor guard. Do not pass it to API calls.
#define VK_QCOM_render_pass_store_ops 1
#define VK_QCOM_RENDER_PASS_STORE_OPS_SPEC_VERSION 2
#define VK_QCOM_RENDER_PASS_STORE_OPS_EXTENSION_NAME "VK_QCOM_render_pass_store_ops"

// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_cuda_kernel_launch 1
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)
#define VK_NV_CUDA_KERNEL_LAUNCH_SPEC_VERSION 2
#define VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"
typedef struct VkCudaModuleCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 size_t dataSize;
 const void* pData;
} VkCudaModuleCreateInfoNV;

typedef struct VkCudaFunctionCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkCudaModuleNV module;
 const char* pName;
} VkCudaFunctionCreateInfoNV;

typedef struct VkCudaLaunchInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkCudaFunctionNV function;
 uint32_t gridDimX;
 uint32_t gridDimY;
 uint32_t gridDimZ;
 uint32_t blockDimX;
 uint32_t blockDimY;
 uint32_t blockDimZ;
 uint32_t sharedMemBytes;
 size_t paramCount;
 const void* const * pParams;
 size_t extraCount;
 const void* const * pExtras;
} VkCudaLaunchInfoNV;

typedef struct VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

typedef struct VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
 VkStructureType sType;
 void* pNext;
 uint32_t computeCapabilityMinor;
 uint32_t computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;

typedef VkResult (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, const VkCudaModuleCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCudaModuleNV* pModule);
typedef VkResult (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, size_t* pCacheSize, void* pCacheData);
typedef VkResult (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, const VkCudaFunctionCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCudaFunctionNV* pFunction);
typedef void (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, const VkAllocationCallbacks* pAllocator);
typedef void (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, const VkAllocationCallbacks* pAllocator);
typedef void (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(VkCommandBuffer commandBuffer, const VkCudaLaunchInfoNV* pLaunchInfo);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaModuleNV(
 VkDevice device,
 const VkCudaModuleCreateInfoNV* pCreateInfo,
 const VkAllocationCallbacks* pAllocator,
 VkCudaModuleNV* pModule);

VKAPI_ATTR VkResult VKAPI_CALL vkGetCudaModuleCacheNV(
 VkDevice device,
 VkCudaModuleNV module,
 size_t* pCacheSize,
 void* pCacheData);

VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaFunctionNV(
 VkDevice device,
 const VkCudaFunctionCreateInfoNV* pCreateInfo,
 const VkAllocationCallbacks* pAllocator,
 VkCudaFunctionNV* pFunction);

VKAPI_ATTR void VKAPI_CALL vkDestroyCudaModuleNV(
 VkDevice device,
 VkCudaModuleNV module,
 const VkAllocationCallbacks* pAllocator);

VKAPI_ATTR void VKAPI_CALL vkDestroyCudaFunctionNV(
 VkDevice device,
 VkCudaFunctionNV function,
 const VkAllocationCallbacks* pAllocator);

VKAPI_ATTR void VKAPI_CALL vkCmdCudaLaunchKernelNV(
 VkCommandBuffer commandBuffer,
 const VkCudaLaunchInfoNV* pLaunchInfo);
#endif

// VK_NV_low_latency is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_low_latency 1
#define VK_NV_LOW_LATENCY_SPEC_VERSION 1
#define VK_NV_LOW_LATENCY_EXTENSION_NAME "VK_NV_low_latency"
typedef struct VkQueryLowLatencySupportNV {
 VkStructureType sType;
 const void* pNext;
 void* pQueriedLowLatencyData;
} VkQueryLowLatencySupportNV;

// VK_EXT_descriptor_buffer is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_descriptor_buffer 1
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkAccelerationStructureKHR)
#define VK_EXT_DESCRIPTOR_BUFFER_SPEC_VERSION 1
#define VK_EXT_DESCRIPTOR_BUFFER_EXTENSION_NAME "VK_EXT_descriptor_buffer"
typedef struct VkPhysicalDeviceDescriptorBufferPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 combinedImageSamplerDescriptorSingleArray;
 VkBool32 bufferlessPushDescriptors;
 VkBool32 allowSamplerImageViewPostSubmitCreation;
 VkDeviceSize descriptorBufferOffsetAlignment;
 uint32_t maxDescriptorBufferBindings;
 uint32_t maxResourceDescriptorBufferBindings;
 uint32_t maxSamplerDescriptorBufferBindings;
 uint32_t maxEmbeddedImmutableSamplerBindings;
 uint32_t maxEmbeddedImmutableSamplers;
 size_t bufferCaptureReplayDescriptorDataSize;
 size_t imageCaptureReplayDescriptorDataSize;
 size_t imageViewCaptureReplayDescriptorDataSize;
 size_t samplerCaptureReplayDescriptorDataSize;
 size_t accelerationStructureCaptureReplayDescriptorDataSize;
 size_t samplerDescriptorSize;
 size_t combinedImageSamplerDescriptorSize;
 size_t sampledImageDescriptorSize;
 size_t storageImageDescriptorSize;
 size_t uniformTexelBufferDescriptorSize;
 size_t robustUniformTexelBufferDescriptorSize;
 size_t storageTexelBufferDescriptorSize;
 size_t robustStorageTexelBufferDescriptorSize;
 size_t uniformBufferDescriptorSize;
 size_t robustUniformBufferDescriptorSize;
 size_t storageBufferDescriptorSize;
 size_t robustStorageBufferDescriptorSize;
 size_t inputAttachmentDescriptorSize;
 size_t accelerationStructureDescriptorSize;
 VkDeviceSize maxSamplerDescriptorBufferRange;
 VkDeviceSize maxResourceDescriptorBufferRange;
 VkDeviceSize samplerDescriptorBufferAddressSpaceSize;
 VkDeviceSize resourceDescriptorBufferAddressSpaceSize;
 VkDeviceSize descriptorBufferAddressSpaceSize;
} VkPhysicalDeviceDescriptorBufferPropertiesEXT;

typedef struct VkPhysicalDeviceDescriptorBufferDensityMapPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 size_t combinedImageSamplerDensityMapDescriptorSize;
} VkPhysicalDeviceDescriptorBufferDensityMapPropertiesEXT;

typedef struct VkPhysicalDeviceDescriptorBufferFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 descriptorBuffer;
 VkBool32 descriptorBufferCaptureReplay;
 VkBool32 descriptorBufferImageLayoutIgnored;
 VkBool32 descriptorBufferPushDescriptors;
} VkPhysicalDeviceDescriptorBufferFeaturesEXT;

typedef struct VkDescriptorAddressInfoEXT {
 VkStructureType sType;
 void* pNext;
 VkDeviceAddress address;
 VkDeviceSize range;
 VkFormat format;
} VkDescriptorAddressInfoEXT;

typedef struct VkDescriptorBufferBindingInfoEXT {
 VkStructureType sType;
 void* pNext;
 VkDeviceAddress address;
 VkBufferUsageFlags usage;
} VkDescriptorBufferBindingInfoEXT;

typedef struct VkDescriptorBufferBindingPushDescriptorBufferHandleEXT {
 VkStructureType sType;
 void* pNext;
 VkBuffer buffer;
} VkDescriptorBufferBindingPushDescriptorBufferHandleEXT;

typedef union VkDescriptorDataEXT {
 const VkSampler* pSampler;
 const VkDescriptorImageInfo* pCombinedImageSampler;
 const VkDescriptorImageInfo* pInputAttachmentImage;
 const VkDescriptorImageInfo* pSampledImage;
 const VkDescriptorImageInfo* pStorageImage;
 const VkDescriptorAddressInfoEXT* pUniformTexelBuffer;
 const VkDescriptorAddressInfoEXT* pStorageTexelBuffer;
 const VkDescriptorAddressInfoEXT* pUniformBuffer;
 const VkDescriptorAddressInfoEXT* pStorageBuffer;
 VkDeviceAddress accelerationStructure;
} VkDescriptorDataEXT;

typedef struct VkDescriptorGetInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkDescriptorType type;
 VkDescriptorDataEXT data;
} VkDescriptorGetInfoEXT;

typedef struct VkBufferCaptureDescriptorDataInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkBuffer buffer;
} VkBufferCaptureDescriptorDataInfoEXT;

typedef struct VkImageCaptureDescriptorDataInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkImage image;
} VkImageCaptureDescriptorDataInfoEXT;

typedef struct VkImageViewCaptureDescriptorDataInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkImageView imageView;
} VkImageViewCaptureDescriptorDataInfoEXT;

typedef struct VkSamplerCaptureDescriptorDataInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkSampler sampler;
} VkSamplerCaptureDescriptorDataInfoEXT;

typedef struct VkOpaqueCaptureDescriptorDataCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 const void* opaqueCaptureDescriptorData;
} VkOpaqueCaptureDescriptorDataCreateInfoEXT;

typedef struct VkAccelerationStructureCaptureDescriptorDataInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkAccelerationStructureKHR accelerationStructure;
 VkAccelerationStructureNV accelerationStructureNV;
} VkAccelerationStructureCaptureDescriptorDataInfoEXT;

typedef void (VKAPI_PTR *PFN_vkGetDescriptorSetLayoutSizeEXT)(VkDevice device, VkDescriptorSetLayout layout, VkDeviceSize* pLayoutSizeInBytes);
typedef void (VKAPI_PTR *PFN_vkGetDescriptorSetLayoutBindingOffsetEXT)(VkDevice device, VkDescriptorSetLayout layout, uint32_t binding, VkDeviceSize* pOffset);
typedef void (VKAPI_PTR *PFN_vkGetDescriptorEXT)(VkDevice device, const VkDescriptorGetInfoEXT* pDescriptorInfo, size_t dataSize, void* pDescriptor);
typedef void (VKAPI_PTR *PFN_vkCmdBindDescriptorBuffersEXT)(VkCommandBuffer commandBuffer, uint32_t bufferCount, const VkDescriptorBufferBindingInfoEXT* pBindingInfos);
typedef void (VKAPI_PTR *PFN_vkCmdSetDescriptorBufferOffsetsEXT)(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t setCount, const uint32_t* pBufferIndices, const VkDeviceSize* pOffsets);
typedef void (VKAPI_PTR *PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT)(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set);
typedef VkResult (VKAPI_PTR *PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT)(VkDevice device, const VkBufferCaptureDescriptorDataInfoEXT* pInfo, void* pData);
typedef VkResult (VKAPI_PTR *PFN_vkGetImageOpaqueCaptureDescriptorDataEXT)(VkDevice device, const VkImageCaptureDescriptorDataInfoEXT* pInfo, void* pData);
typedef VkResult (VKAPI_PTR *PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT)(VkDevice device, const VkImageViewCaptureDescriptorDataInfoEXT* pInfo, void* pData);
typedef VkResult (VKAPI_PTR *PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT)(VkDevice device, const VkSamplerCaptureDescriptorDataInfoEXT* pInfo, void* pData);
typedef VkResult (VKAPI_PTR *PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT)(VkDevice device, const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo, void* pData);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkGetDescriptorSetLayoutSizeEXT(
 VkDevice device,
 VkDescriptorSetLayout layout,
 VkDeviceSize* pLayoutSizeInBytes);

VKAPI_ATTR void VKAPI_CALL vkGetDescriptorSetLayoutBindingOffsetEXT(
 VkDevice device,
 VkDescriptorSetLayout layout,
 uint32_t binding,
 VkDeviceSize* pOffset);

VKAPI_ATTR void VKAPI_CALL vkGetDescriptorEXT(
 VkDevice device,
 const VkDescriptorGetInfoEXT* pDescriptorInfo,
 size_t dataSize,
 void* pDescriptor);

VKAPI_ATTR void VKAPI_CALL vkCmdBindDescriptorBuffersEXT(
 VkCommandBuffer commandBuffer,
 uint32_t bufferCount,
 const VkDescriptorBufferBindingInfoEXT* pBindingInfos);

VKAPI_ATTR void VKAPI_CALL vkCmdSetDescriptorBufferOffsetsEXT(
 VkCommandBuffer commandBuffer,
 VkPipelineBindPoint pipelineBindPoint,
 VkPipelineLayout layout,
 uint32_t firstSet,
 uint32_t setCount,
 const uint32_t* pBufferIndices,
 const VkDeviceSize* pOffsets);

VKAPI_ATTR void VKAPI_CALL vkCmdBindDescriptorBufferEmbeddedSamplersEXT(
 VkCommandBuffer commandBuffer,
 VkPipelineBindPoint pipelineBindPoint,
 VkPipelineLayout layout,
 uint32_t set);

VKAPI_ATTR VkResult VKAPI_CALL vkGetBufferOpaqueCaptureDescriptorDataEXT(
 VkDevice device,
 const VkBufferCaptureDescriptorDataInfoEXT* pInfo,
 void* pData);

VKAPI_ATTR VkResult VKAPI_CALL vkGetImageOpaqueCaptureDescriptorDataEXT(
 VkDevice device,
 const VkImageCaptureDescriptorDataInfoEXT* pInfo,
 void* pData);

VKAPI_ATTR VkResult VKAPI_CALL vkGetImageViewOpaqueCaptureDescriptorDataEXT(
 VkDevice device,
 const VkImageViewCaptureDescriptorDataInfoEXT* pInfo,
 void* pData);

VKAPI_ATTR VkResult VKAPI_CALL vkGetSamplerOpaqueCaptureDescriptorDataEXT(
 VkDevice device,
 const VkSamplerCaptureDescriptorDataInfoEXT* pInfo,
 void* pData);

VKAPI_ATTR VkResult VKAPI_CALL vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT(
 VkDevice device,
 const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo,
 void* pData);
#endif

// VK_EXT_graphics_pipeline_library is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_graphics_pipeline_library 1
#define VK_EXT_GRAPHICS_PIPELINE_LIBRARY_SPEC_VERSION 1
#define VK_EXT_GRAPHICS_PIPELINE_LIBRARY_EXTENSION_NAME "VK_EXT_graphics_pipeline_library"

typedef enum VkGraphicsPipelineLibraryFlagBitsEXT {
 VK_GRAPHICS_PIPELINE_LIBRARY_VERTEX_INPUT_INTERFACE_BIT_EXT = 0x00000001,
 VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT = 0x00000002,
 VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT = 0x00000004,
 VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_OUTPUT_INTERFACE_BIT_EXT = 0x00000008,
 VK_GRAPHICS_PIPELINE_LIBRARY_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkGraphicsPipelineLibraryFlagBitsEXT;
typedef VkFlags VkGraphicsPipelineLibraryFlagsEXT;
typedef struct VkPhysicalDeviceGraphicsPipelineLibraryFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 graphicsPipelineLibrary;
} VkPhysicalDeviceGraphicsPipelineLibraryFeaturesEXT;

typedef struct VkPhysicalDeviceGraphicsPipelineLibraryPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 graphicsPipelineLibraryFastLinking;
 VkBool32 graphicsPipelineLibraryIndependentInterpolationDecoration;
} VkPhysicalDeviceGraphicsPipelineLibraryPropertiesEXT;

typedef struct VkGraphicsPipelineLibraryCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkGraphicsPipelineLibraryFlagsEXT flags;
} VkGraphicsPipelineLibraryCreateInfoEXT;

// VK_AMD_shader_early_and_late_fragment_tests is a preprocessor guard. Do not pass it to API calls.
#define VK_AMD_shader_early_and_late_fragment_tests 1
#define VK_AMD_SHADER_EARLY_AND_LATE_FRAGMENT_TESTS_SPEC_VERSION 1
#define VK_AMD_SHADER_EARLY_AND_LATE_FRAGMENT_TESTS_EXTENSION_NAME "VK_AMD_shader_early_and_late_fragment_tests"
typedef struct VkPhysicalDeviceShaderEarlyAndLateFragmentTestsFeaturesAMD {
 VkStructureType sType;
 void* pNext;
 VkBool32 shaderEarlyAndLateFragmentTests;
} VkPhysicalDeviceShaderEarlyAndLateFragmentTestsFeaturesAMD;

// VK_NV_fragment_shading_rate_enums is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_fragment_shading_rate_enums 1
#define VK_NV_FRAGMENT_SHADING_RATE_ENUMS_SPEC_VERSION 1
#define VK_NV_FRAGMENT_SHADING_RATE_ENUMS_EXTENSION_NAME "VK_NV_fragment_shading_rate_enums"

typedef enum VkFragmentShadingRateTypeNV {
 VK_FRAGMENT_SHADING_RATE_TYPE_FRAGMENT_SIZE_NV = 0,
 VK_FRAGMENT_SHADING_RATE_TYPE_ENUMS_NV = 1,
 VK_FRAGMENT_SHADING_RATE_TYPE_MAX_ENUM_NV = 0x7FFFFFFF
} VkFragmentShadingRateTypeNV;

typedef enum VkFragmentShadingRateNV {
 VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_PIXEL_NV = 0,
 VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_1X2_PIXELS_NV = 1,
 VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_2X1_PIXELS_NV = 4,
 VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_2X2_PIXELS_NV = 5,
 VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_2X4_PIXELS_NV = 6,
 VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_4X2_PIXELS_NV = 9,
 VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_4X4_PIXELS_NV = 10,
 VK_FRAGMENT_SHADING_RATE_2_INVOCATIONS_PER_PIXEL_NV = 11,
 VK_FRAGMENT_SHADING_RATE_4_INVOCATIONS_PER_PIXEL_NV = 12,
 VK_FRAGMENT_SHADING_RATE_8_INVOCATIONS_PER_PIXEL_NV = 13,
 VK_FRAGMENT_SHADING_RATE_16_INVOCATIONS_PER_PIXEL_NV = 14,
 VK_FRAGMENT_SHADING_RATE_NO_INVOCATIONS_NV = 15,
 VK_FRAGMENT_SHADING_RATE_MAX_ENUM_NV = 0x7FFFFFFF
} VkFragmentShadingRateNV;
typedef struct VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 fragmentShadingRateEnums;
 VkBool32 supersampleFragmentShadingRates;
 VkBool32 noInvocationFragmentShadingRates;
} VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV;

typedef struct VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV {
 VkStructureType sType;
 void* pNext;
 VkSampleCountFlagBits maxFragmentShadingRateInvocationCount;
} VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV;

typedef struct VkPipelineFragmentShadingRateEnumStateCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkFragmentShadingRateTypeNV shadingRateType;
 VkFragmentShadingRateNV shadingRate;
 VkFragmentShadingRateCombinerOpKHR combinerOps[2];
} VkPipelineFragmentShadingRateEnumStateCreateInfoNV;

typedef void (VKAPI_PTR *PFN_vkCmdSetFragmentShadingRateEnumNV)(VkCommandBuffer commandBuffer, VkFragmentShadingRateNV shadingRate, const VkFragmentShadingRateCombinerOpKHR combinerOps[2]);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdSetFragmentShadingRateEnumNV(
 VkCommandBuffer commandBuffer,
 VkFragmentShadingRateNV shadingRate,
 const VkFragmentShadingRateCombinerOpKHR combinerOps[2]);
#endif

// VK_NV_ray_tracing_motion_blur is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_ray_tracing_motion_blur 1
#define VK_NV_RAY_TRACING_MOTION_BLUR_SPEC_VERSION 1
#define VK_NV_RAY_TRACING_MOTION_BLUR_EXTENSION_NAME "VK_NV_ray_tracing_motion_blur"

typedef enum VkAccelerationStructureMotionInstanceTypeNV {
 VK_ACCELERATION_STRUCTURE_MOTION_INSTANCE_TYPE_STATIC_NV = 0,
 VK_ACCELERATION_STRUCTURE_MOTION_INSTANCE_TYPE_MATRIX_MOTION_NV = 1,
 VK_ACCELERATION_STRUCTURE_MOTION_INSTANCE_TYPE_SRT_MOTION_NV = 2,
 VK_ACCELERATION_STRUCTURE_MOTION_INSTANCE_TYPE_MAX_ENUM_NV = 0x7FFFFFFF
} VkAccelerationStructureMotionInstanceTypeNV;
typedef VkFlags VkAccelerationStructureMotionInfoFlagsNV;
typedef VkFlags VkAccelerationStructureMotionInstanceFlagsNV;
typedef union VkDeviceOrHostAddressConstKHR {
 VkDeviceAddress deviceAddress;
 const void* hostAddress;
} VkDeviceOrHostAddressConstKHR;

typedef struct VkAccelerationStructureGeometryMotionTrianglesDataNV {
 VkStructureType sType;
 const void* pNext;
 VkDeviceOrHostAddressConstKHR vertexData;
} VkAccelerationStructureGeometryMotionTrianglesDataNV;

typedef struct VkAccelerationStructureMotionInfoNV {
 VkStructureType sType;
 const void* pNext;
 uint32_t maxInstances;
 VkAccelerationStructureMotionInfoFlagsNV flags;
} VkAccelerationStructureMotionInfoNV;

typedef struct VkAccelerationStructureMatrixMotionInstanceNV {
 VkTransformMatrixKHR transformT0;
 VkTransformMatrixKHR transformT1;
 uint32_t instanceCustomIndex:24;
 uint32_t mask:8;
 uint32_t instanceShaderBindingTableRecordOffset:24;
 VkGeometryInstanceFlagsKHR flags:8;
 uint64_t accelerationStructureReference;
} VkAccelerationStructureMatrixMotionInstanceNV;

typedef struct VkSRTDataNV {
 float sx;
 float a;
 float b;
 float pvx;
 float sy;
 float c;
 float pvy;
 float sz;
 float pvz;
 float qx;
 float qy;
 float qz;
 float qw;
 float tx;
 float ty;
 float tz;
} VkSRTDataNV;

typedef struct VkAccelerationStructureSRTMotionInstanceNV {
 VkSRTDataNV transformT0;
 VkSRTDataNV transformT1;
 uint32_t instanceCustomIndex:24;
 uint32_t mask:8;
 uint32_t instanceShaderBindingTableRecordOffset:24;
 VkGeometryInstanceFlagsKHR flags:8;
 uint64_t accelerationStructureReference;
} VkAccelerationStructureSRTMotionInstanceNV;

typedef union VkAccelerationStructureMotionInstanceDataNV {
 VkAccelerationStructureInstanceKHR staticInstance;
 VkAccelerationStructureMatrixMotionInstanceNV matrixMotionInstance;
 VkAccelerationStructureSRTMotionInstanceNV srtMotionInstance;
} VkAccelerationStructureMotionInstanceDataNV;

typedef struct VkAccelerationStructureMotionInstanceNV {
 VkAccelerationStructureMotionInstanceTypeNV type;
 VkAccelerationStructureMotionInstanceFlagsNV flags;
 VkAccelerationStructureMotionInstanceDataNV data;
} VkAccelerationStructureMotionInstanceNV;

typedef struct VkPhysicalDeviceRayTracingMotionBlurFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 rayTracingMotionBlur;
 VkBool32 rayTracingMotionBlurPipelineTraceRaysIndirect;
} VkPhysicalDeviceRayTracingMotionBlurFeaturesNV;

// VK_EXT_ycbcr_2plane_444_formats is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_ycbcr_2plane_444_formats 1
#define VK_EXT_YCBCR_2PLANE_444_FORMATS_SPEC_VERSION 1
#define VK_EXT_YCBCR_2PLANE_444_FORMATS_EXTENSION_NAME "VK_EXT_ycbcr_2plane_444_formats"
typedef struct VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 ycbcr2plane444Formats;
} VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT;

// VK_EXT_fragment_density_map2 is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_fragment_density_map2 1
#define VK_EXT_FRAGMENT_DENSITY_MAP_2_SPEC_VERSION 1
#define VK_EXT_FRAGMENT_DENSITY_MAP_2_EXTENSION_NAME "VK_EXT_fragment_density_map2"
typedef struct VkPhysicalDeviceFragmentDensityMap2FeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 fragmentDensityMapDeferred;
} VkPhysicalDeviceFragmentDensityMap2FeaturesEXT;

typedef struct VkPhysicalDeviceFragmentDensityMap2PropertiesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 subsampledLoads;
 VkBool32 subsampledCoarseReconstructionEarlyAccess;
 uint32_t maxSubsampledArrayLayers;
 uint32_t maxDescriptorSetSubsampledSamplers;
} VkPhysicalDeviceFragmentDensityMap2PropertiesEXT;

// VK_QCOM_rotated_copy_commands is a preprocessor guard. Do not pass it to API calls.
#define VK_QCOM_rotated_copy_commands 1
#define VK_QCOM_ROTATED_COPY_COMMANDS_SPEC_VERSION 2
#define VK_QCOM_ROTATED_COPY_COMMANDS_EXTENSION_NAME "VK_QCOM_rotated_copy_commands"
typedef struct VkCopyCommandTransformInfoQCOM {
 VkStructureType sType;
 const void* pNext;
 VkSurfaceTransformFlagBitsKHR transform;
} VkCopyCommandTransformInfoQCOM;

// VK_EXT_image_robustness is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_image_robustness 1
#define VK_EXT_IMAGE_ROBUSTNESS_SPEC_VERSION 1
#define VK_EXT_IMAGE_ROBUSTNESS_EXTENSION_NAME "VK_EXT_image_robustness"
typedef VkPhysicalDeviceImageRobustnessFeatures VkPhysicalDeviceImageRobustnessFeaturesEXT;

// VK_EXT_image_compression_control is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_image_compression_control 1
#define VK_EXT_IMAGE_COMPRESSION_CONTROL_SPEC_VERSION 1
#define VK_EXT_IMAGE_COMPRESSION_CONTROL_EXTENSION_NAME "VK_EXT_image_compression_control"

typedef enum VkImageCompressionFlagBitsEXT {
 VK_IMAGE_COMPRESSION_DEFAULT_EXT = 0,
 VK_IMAGE_COMPRESSION_FIXED_RATE_DEFAULT_EXT = 0x00000001,
 VK_IMAGE_COMPRESSION_FIXED_RATE_EXPLICIT_EXT = 0x00000002,
 VK_IMAGE_COMPRESSION_DISABLED_EXT = 0x00000004,
 VK_IMAGE_COMPRESSION_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkImageCompressionFlagBitsEXT;
typedef VkFlags VkImageCompressionFlagsEXT;

typedef enum VkImageCompressionFixedRateFlagBitsEXT {
 VK_IMAGE_COMPRESSION_FIXED_RATE_NONE_EXT = 0,
 VK_IMAGE_COMPRESSION_FIXED_RATE_1BPC_BIT_EXT = 0x00000001,
 VK_IMAGE_COMPRESSION_FIXED_RATE_2BPC_BIT_EXT = 0x00000002,
 VK_IMAGE_COMPRESSION_FIXED_RATE_3BPC_BIT_EXT = 0x00000004,
 VK_IMAGE_COMPRESSION_FIXED_RATE_4BPC_BIT_EXT = 0x00000008,
 VK_IMAGE_COMPRESSION_FIXED_RATE_5BPC_BIT_EXT = 0x00000010,
 VK_IMAGE_COMPRESSION_FIXED_RATE_6BPC_BIT_EXT = 0x00000020,
 VK_IMAGE_COMPRESSION_FIXED_RATE_7BPC_BIT_EXT = 0x00000040,
 VK_IMAGE_COMPRESSION_FIXED_RATE_8BPC_BIT_EXT = 0x00000080,
 VK_IMAGE_COMPRESSION_FIXED_RATE_9BPC_BIT_EXT = 0x00000100,
 VK_IMAGE_COMPRESSION_FIXED_RATE_10BPC_BIT_EXT = 0x00000200,
 VK_IMAGE_COMPRESSION_FIXED_RATE_11BPC_BIT_EXT = 0x00000400,
 VK_IMAGE_COMPRESSION_FIXED_RATE_12BPC_BIT_EXT = 0x00000800,
 VK_IMAGE_COMPRESSION_FIXED_RATE_13BPC_BIT_EXT = 0x00001000,
 VK_IMAGE_COMPRESSION_FIXED_RATE_14BPC_BIT_EXT = 0x00002000,
 VK_IMAGE_COMPRESSION_FIXED_RATE_15BPC_BIT_EXT = 0x00004000,
 VK_IMAGE_COMPRESSION_FIXED_RATE_16BPC_BIT_EXT = 0x00008000,
 VK_IMAGE_COMPRESSION_FIXED_RATE_17BPC_BIT_EXT = 0x00010000,
 VK_IMAGE_COMPRESSION_FIXED_RATE_18BPC_BIT_EXT = 0x00020000,
 VK_IMAGE_COMPRESSION_FIXED_RATE_19BPC_BIT_EXT = 0x00040000,
 VK_IMAGE_COMPRESSION_FIXED_RATE_20BPC_BIT_EXT = 0x00080000,
 VK_IMAGE_COMPRESSION_FIXED_RATE_21BPC_BIT_EXT = 0x00100000,
 VK_IMAGE_COMPRESSION_FIXED_RATE_22BPC_BIT_EXT = 0x00200000,
 VK_IMAGE_COMPRESSION_FIXED_RATE_23BPC_BIT_EXT = 0x00400000,
 VK_IMAGE_COMPRESSION_FIXED_RATE_24BPC_BIT_EXT = 0x00800000,
 VK_IMAGE_COMPRESSION_FIXED_RATE_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkImageCompressionFixedRateFlagBitsEXT;
typedef VkFlags VkImageCompressionFixedRateFlagsEXT;
typedef struct VkPhysicalDeviceImageCompressionControlFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 imageCompressionControl;
} VkPhysicalDeviceImageCompressionControlFeaturesEXT;

typedef struct VkImageCompressionControlEXT {
 VkStructureType sType;
 const void* pNext;
 VkImageCompressionFlagsEXT flags;
 uint32_t compressionControlPlaneCount;
 VkImageCompressionFixedRateFlagsEXT* pFixedRateFlags;
} VkImageCompressionControlEXT;

typedef struct VkImageCompressionPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 VkImageCompressionFlagsEXT imageCompressionFlags;
 VkImageCompressionFixedRateFlagsEXT imageCompressionFixedRateFlags;
} VkImageCompressionPropertiesEXT;

// VK_EXT_attachment_feedback_loop_layout is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_attachment_feedback_loop_layout 1
#define VK_EXT_ATTACHMENT_FEEDBACK_LOOP_LAYOUT_SPEC_VERSION 2
#define VK_EXT_ATTACHMENT_FEEDBACK_LOOP_LAYOUT_EXTENSION_NAME "VK_EXT_attachment_feedback_loop_layout"
typedef struct VkPhysicalDeviceAttachmentFeedbackLoopLayoutFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 attachmentFeedbackLoopLayout;
} VkPhysicalDeviceAttachmentFeedbackLoopLayoutFeaturesEXT;

// VK_EXT_4444_formats is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_4444_formats 1
#define VK_EXT_4444_FORMATS_SPEC_VERSION 1
#define VK_EXT_4444_FORMATS_EXTENSION_NAME "VK_EXT_4444_formats"
typedef struct VkPhysicalDevice4444FormatsFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 formatA4R4G4B4;
 VkBool32 formatA4B4G4R4;
} VkPhysicalDevice4444FormatsFeaturesEXT;

// VK_EXT_device_fault is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_device_fault 1
#define VK_EXT_DEVICE_FAULT_SPEC_VERSION 2
#define VK_EXT_DEVICE_FAULT_EXTENSION_NAME "VK_EXT_device_fault"

typedef enum VkDeviceFaultAddressTypeEXT {
 VK_DEVICE_FAULT_ADDRESS_TYPE_NONE_EXT = 0,
 VK_DEVICE_FAULT_ADDRESS_TYPE_READ_INVALID_EXT = 1,
 VK_DEVICE_FAULT_ADDRESS_TYPE_WRITE_INVALID_EXT = 2,
 VK_DEVICE_FAULT_ADDRESS_TYPE_EXECUTE_INVALID_EXT = 3,
 VK_DEVICE_FAULT_ADDRESS_TYPE_INSTRUCTION_POINTER_UNKNOWN_EXT = 4,
 VK_DEVICE_FAULT_ADDRESS_TYPE_INSTRUCTION_POINTER_INVALID_EXT = 5,
 VK_DEVICE_FAULT_ADDRESS_TYPE_INSTRUCTION_POINTER_FAULT_EXT = 6,
 VK_DEVICE_FAULT_ADDRESS_TYPE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkDeviceFaultAddressTypeEXT;

typedef enum VkDeviceFaultVendorBinaryHeaderVersionEXT {
 VK_DEVICE_FAULT_VENDOR_BINARY_HEADER_VERSION_ONE_EXT = 1,
 VK_DEVICE_FAULT_VENDOR_BINARY_HEADER_VERSION_MAX_ENUM_EXT = 0x7FFFFFFF
} VkDeviceFaultVendorBinaryHeaderVersionEXT;
typedef struct VkPhysicalDeviceFaultFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 deviceFault;
 VkBool32 deviceFaultVendorBinary;
} VkPhysicalDeviceFaultFeaturesEXT;

typedef struct VkDeviceFaultCountsEXT {
 VkStructureType sType;
 void* pNext;
 uint32_t addressInfoCount;
 uint32_t vendorInfoCount;
 VkDeviceSize vendorBinarySize;
} VkDeviceFaultCountsEXT;

typedef struct VkDeviceFaultAddressInfoEXT {
 VkDeviceFaultAddressTypeEXT addressType;
 VkDeviceAddress reportedAddress;
 VkDeviceSize addressPrecision;
} VkDeviceFaultAddressInfoEXT;

typedef struct VkDeviceFaultVendorInfoEXT {
 char description[VK_MAX_DESCRIPTION_SIZE];
 uint64_t vendorFaultCode;
 uint64_t vendorFaultData;
} VkDeviceFaultVendorInfoEXT;

typedef struct VkDeviceFaultInfoEXT {
 VkStructureType sType;
 void* pNext;
 char description[VK_MAX_DESCRIPTION_SIZE];
 VkDeviceFaultAddressInfoEXT* pAddressInfos;
 VkDeviceFaultVendorInfoEXT* pVendorInfos;
 void* pVendorBinaryData;
} VkDeviceFaultInfoEXT;

typedef struct VkDeviceFaultVendorBinaryHeaderVersionOneEXT {
 uint32_t headerSize;
 VkDeviceFaultVendorBinaryHeaderVersionEXT headerVersion;
 uint32_t vendorID;
 uint32_t deviceID;
 uint32_t driverVersion;
 uint8_t pipelineCacheUUID[VK_UUID_SIZE];
 uint32_t applicationNameOffset;
 uint32_t applicationVersion;
 uint32_t engineNameOffset;
 uint32_t engineVersion;
 uint32_t apiVersion;
} VkDeviceFaultVendorBinaryHeaderVersionOneEXT;

typedef VkResult (VKAPI_PTR *PFN_vkGetDeviceFaultInfoEXT)(VkDevice device, VkDeviceFaultCountsEXT* pFaultCounts, VkDeviceFaultInfoEXT* pFaultInfo);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetDeviceFaultInfoEXT(
 VkDevice device,
 VkDeviceFaultCountsEXT* pFaultCounts,
 VkDeviceFaultInfoEXT* pFaultInfo);
#endif

// VK_ARM_rasterization_order_attachment_access is a preprocessor guard. Do not pass it to API calls.
#define VK_ARM_rasterization_order_attachment_access 1
#define VK_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_SPEC_VERSION 1
#define VK_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_EXTENSION_NAME "VK_ARM_rasterization_order_attachment_access"
typedef struct VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 rasterizationOrderColorAttachmentAccess;
 VkBool32 rasterizationOrderDepthAttachmentAccess;
 VkBool32 rasterizationOrderStencilAttachmentAccess;
} VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT;

typedef VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesARM;

// VK_EXT_rgba10x6_formats is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_rgba10x6_formats 1
#define VK_EXT_RGBA10X6_FORMATS_SPEC_VERSION 1
#define VK_EXT_RGBA10X6_FORMATS_EXTENSION_NAME "VK_EXT_rgba10x6_formats"
typedef struct VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 formatRgba10x6WithoutYCbCrSampler;
} VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT;

// VK_VALVE_mutable_descriptor_type is a preprocessor guard. Do not pass it to API calls.
#define VK_VALVE_mutable_descriptor_type 1
#define VK_VALVE_MUTABLE_DESCRIPTOR_TYPE_SPEC_VERSION 1
#define VK_VALVE_MUTABLE_DESCRIPTOR_TYPE_EXTENSION_NAME "VK_VALVE_mutable_descriptor_type"
typedef struct VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 mutableDescriptorType;
} VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT;

typedef VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT VkPhysicalDeviceMutableDescriptorTypeFeaturesVALVE;

typedef struct VkMutableDescriptorTypeListEXT {
 uint32_t descriptorTypeCount;
 const VkDescriptorType* pDescriptorTypes;
} VkMutableDescriptorTypeListEXT;

typedef VkMutableDescriptorTypeListEXT VkMutableDescriptorTypeListVALVE;

typedef struct VkMutableDescriptorTypeCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 uint32_t mutableDescriptorTypeListCount;
 const VkMutableDescriptorTypeListEXT* pMutableDescriptorTypeLists;
} VkMutableDescriptorTypeCreateInfoEXT;

typedef VkMutableDescriptorTypeCreateInfoEXT VkMutableDescriptorTypeCreateInfoVALVE;

// VK_EXT_vertex_input_dynamic_state is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_vertex_input_dynamic_state 1
#define VK_EXT_VERTEX_INPUT_DYNAMIC_STATE_SPEC_VERSION 2
#define VK_EXT_VERTEX_INPUT_DYNAMIC_STATE_EXTENSION_NAME "VK_EXT_vertex_input_dynamic_state"
typedef struct VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 vertexInputDynamicState;
} VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT;

typedef struct VkVertexInputBindingDescription2EXT {
 VkStructureType sType;
 void* pNext;
 uint32_t binding;
 uint32_t stride;
 VkVertexInputRate inputRate;
 uint32_t divisor;
} VkVertexInputBindingDescription2EXT;

typedef struct VkVertexInputAttributeDescription2EXT {
 VkStructureType sType;
 void* pNext;
 uint32_t location;
 uint32_t binding;
 VkFormat format;
 uint32_t offset;
} VkVertexInputAttributeDescription2EXT;

typedef void (VKAPI_PTR *PFN_vkCmdSetVertexInputEXT)(VkCommandBuffer commandBuffer, uint32_t vertexBindingDescriptionCount, const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions, uint32_t vertexAttributeDescriptionCount, const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdSetVertexInputEXT(
 VkCommandBuffer commandBuffer,
 uint32_t vertexBindingDescriptionCount,
 const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions,
 uint32_t vertexAttributeDescriptionCount,
 const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions);
#endif

// VK_EXT_physical_device_drm is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_physical_device_drm 1
#define VK_EXT_PHYSICAL_DEVICE_DRM_SPEC_VERSION 1
#define VK_EXT_PHYSICAL_DEVICE_DRM_EXTENSION_NAME "VK_EXT_physical_device_drm"
typedef struct VkPhysicalDeviceDrmPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 hasPrimary;
 VkBool32 hasRender;
 int64_t primaryMajor;
 int64_t primaryMinor;
 int64_t renderMajor;
 int64_t renderMinor;
} VkPhysicalDeviceDrmPropertiesEXT;

// VK_EXT_device_address_binding_report is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_device_address_binding_report 1
#define VK_EXT_DEVICE_ADDRESS_BINDING_REPORT_SPEC_VERSION 1
#define VK_EXT_DEVICE_ADDRESS_BINDING_REPORT_EXTENSION_NAME "VK_EXT_device_address_binding_report"

typedef enum VkDeviceAddressBindingTypeEXT {
 VK_DEVICE_ADDRESS_BINDING_TYPE_BIND_EXT = 0,
 VK_DEVICE_ADDRESS_BINDING_TYPE_UNBIND_EXT = 1,
 VK_DEVICE_ADDRESS_BINDING_TYPE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkDeviceAddressBindingTypeEXT;

typedef enum VkDeviceAddressBindingFlagBitsEXT {
 VK_DEVICE_ADDRESS_BINDING_INTERNAL_OBJECT_BIT_EXT = 0x00000001,
 VK_DEVICE_ADDRESS_BINDING_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkDeviceAddressBindingFlagBitsEXT;
typedef VkFlags VkDeviceAddressBindingFlagsEXT;
typedef struct VkPhysicalDeviceAddressBindingReportFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 reportAddressBinding;
} VkPhysicalDeviceAddressBindingReportFeaturesEXT;

typedef struct VkDeviceAddressBindingCallbackDataEXT {
 VkStructureType sType;
 void* pNext;
 VkDeviceAddressBindingFlagsEXT flags;
 VkDeviceAddress baseAddress;
 VkDeviceSize size;
 VkDeviceAddressBindingTypeEXT bindingType;
} VkDeviceAddressBindingCallbackDataEXT;

// VK_EXT_depth_clip_control is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_depth_clip_control 1
#define VK_EXT_DEPTH_CLIP_CONTROL_SPEC_VERSION 1
#define VK_EXT_DEPTH_CLIP_CONTROL_EXTENSION_NAME "VK_EXT_depth_clip_control"
typedef struct VkPhysicalDeviceDepthClipControlFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 depthClipControl;
} VkPhysicalDeviceDepthClipControlFeaturesEXT;

typedef struct VkPipelineViewportDepthClipControlCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkBool32 negativeOneToOne;
} VkPipelineViewportDepthClipControlCreateInfoEXT;

// VK_EXT_primitive_topology_list_restart is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_primitive_topology_list_restart 1
#define VK_EXT_PRIMITIVE_TOPOLOGY_LIST_RESTART_SPEC_VERSION 1
#define VK_EXT_PRIMITIVE_TOPOLOGY_LIST_RESTART_EXTENSION_NAME "VK_EXT_primitive_topology_list_restart"
typedef struct VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 primitiveTopologyListRestart;
 VkBool32 primitiveTopologyPatchListRestart;
} VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT;

// VK_HUAWEI_subpass_shading is a preprocessor guard. Do not pass it to API calls.
#define VK_HUAWEI_subpass_shading 1
#define VK_HUAWEI_SUBPASS_SHADING_SPEC_VERSION 3
#define VK_HUAWEI_SUBPASS_SHADING_EXTENSION_NAME "VK_HUAWEI_subpass_shading"
typedef struct VkSubpassShadingPipelineCreateInfoHUAWEI {
 VkStructureType sType;
 void* pNext;
 VkRenderPass renderPass;
 uint32_t subpass;
} VkSubpassShadingPipelineCreateInfoHUAWEI;

typedef struct VkPhysicalDeviceSubpassShadingFeaturesHUAWEI {
 VkStructureType sType;
 void* pNext;
 VkBool32 subpassShading;
} VkPhysicalDeviceSubpassShadingFeaturesHUAWEI;

typedef struct VkPhysicalDeviceSubpassShadingPropertiesHUAWEI {
 VkStructureType sType;
 void* pNext;
 uint32_t maxSubpassShadingWorkgroupSizeAspectRatio;
} VkPhysicalDeviceSubpassShadingPropertiesHUAWEI;

typedef VkResult (VKAPI_PTR *PFN_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI)(VkDevice device, VkRenderPass renderpass, VkExtent2D* pMaxWorkgroupSize);
typedef void (VKAPI_PTR *PFN_vkCmdSubpassShadingHUAWEI)(VkCommandBuffer commandBuffer);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI(
 VkDevice device,
 VkRenderPass renderpass,
 VkExtent2D* pMaxWorkgroupSize);

VKAPI_ATTR void VKAPI_CALL vkCmdSubpassShadingHUAWEI(
 VkCommandBuffer commandBuffer);
#endif

// VK_HUAWEI_invocation_mask is a preprocessor guard. Do not pass it to API calls.
#define VK_HUAWEI_invocation_mask 1
#define VK_HUAWEI_INVOCATION_MASK_SPEC_VERSION 1
#define VK_HUAWEI_INVOCATION_MASK_EXTENSION_NAME "VK_HUAWEI_invocation_mask"
typedef struct VkPhysicalDeviceInvocationMaskFeaturesHUAWEI {
 VkStructureType sType;
 void* pNext;
 VkBool32 invocationMask;
} VkPhysicalDeviceInvocationMaskFeaturesHUAWEI;

typedef void (VKAPI_PTR *PFN_vkCmdBindInvocationMaskHUAWEI)(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdBindInvocationMaskHUAWEI(
 VkCommandBuffer commandBuffer,
 VkImageView imageView,
 VkImageLayout imageLayout);
#endif

// VK_NV_external_memory_rdma is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_external_memory_rdma 1
typedef void* VkRemoteAddressNV;
#define VK_NV_EXTERNAL_MEMORY_RDMA_SPEC_VERSION 1
#define VK_NV_EXTERNAL_MEMORY_RDMA_EXTENSION_NAME "VK_NV_external_memory_rdma"
typedef struct VkMemoryGetRemoteAddressInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkDeviceMemory memory;
 VkExternalMemoryHandleTypeFlagBits handleType;
} VkMemoryGetRemoteAddressInfoNV;

typedef struct VkPhysicalDeviceExternalMemoryRDMAFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 externalMemoryRDMA;
} VkPhysicalDeviceExternalMemoryRDMAFeaturesNV;

typedef VkResult (VKAPI_PTR *PFN_vkGetMemoryRemoteAddressNV)(VkDevice device, const VkMemoryGetRemoteAddressInfoNV* pMemoryGetRemoteAddressInfo, VkRemoteAddressNV* pAddress);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryRemoteAddressNV(
 VkDevice device,
 const VkMemoryGetRemoteAddressInfoNV* pMemoryGetRemoteAddressInfo,
 VkRemoteAddressNV* pAddress);
#endif

// VK_EXT_pipeline_properties is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_pipeline_properties 1
#define VK_EXT_PIPELINE_PROPERTIES_SPEC_VERSION 1
#define VK_EXT_PIPELINE_PROPERTIES_EXTENSION_NAME "VK_EXT_pipeline_properties"
typedef VkPipelineInfoKHR VkPipelineInfoEXT;

typedef struct VkPipelinePropertiesIdentifierEXT {
 VkStructureType sType;
 void* pNext;
 uint8_t pipelineIdentifier[VK_UUID_SIZE];
} VkPipelinePropertiesIdentifierEXT;

typedef struct VkPhysicalDevicePipelinePropertiesFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 pipelinePropertiesIdentifier;
} VkPhysicalDevicePipelinePropertiesFeaturesEXT;

typedef VkResult (VKAPI_PTR *PFN_vkGetPipelinePropertiesEXT)(VkDevice device, const VkPipelineInfoEXT* pPipelineInfo, VkBaseOutStructure* pPipelineProperties);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetPipelinePropertiesEXT(
 VkDevice device,
 const VkPipelineInfoEXT* pPipelineInfo,
 VkBaseOutStructure* pPipelineProperties);
#endif

// VK_EXT_frame_boundary is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_frame_boundary 1
#define VK_EXT_FRAME_BOUNDARY_SPEC_VERSION 1
#define VK_EXT_FRAME_BOUNDARY_EXTENSION_NAME "VK_EXT_frame_boundary"

typedef enum VkFrameBoundaryFlagBitsEXT {
 VK_FRAME_BOUNDARY_FRAME_END_BIT_EXT = 0x00000001,
 VK_FRAME_BOUNDARY_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkFrameBoundaryFlagBitsEXT;
typedef VkFlags VkFrameBoundaryFlagsEXT;
typedef struct VkPhysicalDeviceFrameBoundaryFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 frameBoundary;
} VkPhysicalDeviceFrameBoundaryFeaturesEXT;

typedef struct VkFrameBoundaryEXT {
 VkStructureType sType;
 const void* pNext;
 VkFrameBoundaryFlagsEXT flags;
 uint64_t frameID;
 uint32_t imageCount;
 const VkImage* pImages;
 uint32_t bufferCount;
 const VkBuffer* pBuffers;
 uint64_t tagName;
 size_t tagSize;
 const void* pTag;
} VkFrameBoundaryEXT;

// VK_EXT_multisampled_render_to_single_sampled is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_multisampled_render_to_single_sampled 1
#define VK_EXT_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_SPEC_VERSION 1
#define VK_EXT_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_EXTENSION_NAME "VK_EXT_multisampled_render_to_single_sampled"
typedef struct VkPhysicalDeviceMultisampledRenderToSingleSampledFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 multisampledRenderToSingleSampled;
} VkPhysicalDeviceMultisampledRenderToSingleSampledFeaturesEXT;

typedef struct VkSubpassResolvePerformanceQueryEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 optimal;
} VkSubpassResolvePerformanceQueryEXT;

typedef struct VkMultisampledRenderToSingleSampledInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkBool32 multisampledRenderToSingleSampledEnable;
 VkSampleCountFlagBits rasterizationSamples;
} VkMultisampledRenderToSingleSampledInfoEXT;

// VK_EXT_extended_dynamic_state2 is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_extended_dynamic_state2 1
#define VK_EXT_EXTENDED_DYNAMIC_STATE_2_SPEC_VERSION 1
#define VK_EXT_EXTENDED_DYNAMIC_STATE_2_EXTENSION_NAME "VK_EXT_extended_dynamic_state2"
typedef struct VkPhysicalDeviceExtendedDynamicState2FeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 extendedDynamicState2;
 VkBool32 extendedDynamicState2LogicOp;
 VkBool32 extendedDynamicState2PatchControlPoints;
} VkPhysicalDeviceExtendedDynamicState2FeaturesEXT;

typedef void (VKAPI_PTR *PFN_vkCmdSetPatchControlPointsEXT)(VkCommandBuffer commandBuffer, uint32_t patchControlPoints);
typedef void (VKAPI_PTR *PFN_vkCmdSetRasterizerDiscardEnableEXT)(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable);
typedef void (VKAPI_PTR *PFN_vkCmdSetDepthBiasEnableEXT)(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable);
typedef void (VKAPI_PTR *PFN_vkCmdSetLogicOpEXT)(VkCommandBuffer commandBuffer, VkLogicOp logicOp);
typedef void (VKAPI_PTR *PFN_vkCmdSetPrimitiveRestartEnableEXT)(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdSetPatchControlPointsEXT(
 VkCommandBuffer commandBuffer,
 uint32_t patchControlPoints);

VKAPI_ATTR void VKAPI_CALL vkCmdSetRasterizerDiscardEnableEXT(
 VkCommandBuffer commandBuffer,
 VkBool32 rasterizerDiscardEnable);

VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthBiasEnableEXT(
 VkCommandBuffer commandBuffer,
 VkBool32 depthBiasEnable);

VKAPI_ATTR void VKAPI_CALL vkCmdSetLogicOpEXT(
 VkCommandBuffer commandBuffer,
 VkLogicOp logicOp);

VKAPI_ATTR void VKAPI_CALL vkCmdSetPrimitiveRestartEnableEXT(
 VkCommandBuffer commandBuffer,
 VkBool32 primitiveRestartEnable);
#endif

// VK_EXT_color_write_enable is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_color_write_enable 1
#define VK_EXT_COLOR_WRITE_ENABLE_SPEC_VERSION 1
#define VK_EXT_COLOR_WRITE_ENABLE_EXTENSION_NAME "VK_EXT_color_write_enable"
typedef struct VkPhysicalDeviceColorWriteEnableFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 colorWriteEnable;
} VkPhysicalDeviceColorWriteEnableFeaturesEXT;

typedef struct VkPipelineColorWriteCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 uint32_t attachmentCount;
 const VkBool32* pColorWriteEnables;
} VkPipelineColorWriteCreateInfoEXT;

typedef void (VKAPI_PTR *PFN_vkCmdSetColorWriteEnableEXT)(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkBool32* pColorWriteEnables);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdSetColorWriteEnableEXT(
 VkCommandBuffer commandBuffer,
 uint32_t attachmentCount,
 const VkBool32* pColorWriteEnables);
#endif

// VK_EXT_primitives_generated_query is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_primitives_generated_query 1
#define VK_EXT_PRIMITIVES_GENERATED_QUERY_SPEC_VERSION 1
#define VK_EXT_PRIMITIVES_GENERATED_QUERY_EXTENSION_NAME "VK_EXT_primitives_generated_query"
typedef struct VkPhysicalDevicePrimitivesGeneratedQueryFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 primitivesGeneratedQuery;
 VkBool32 primitivesGeneratedQueryWithRasterizerDiscard;
 VkBool32 primitivesGeneratedQueryWithNonZeroStreams;
} VkPhysicalDevicePrimitivesGeneratedQueryFeaturesEXT;

// VK_EXT_global_priority_query is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_global_priority_query 1
#define VK_EXT_GLOBAL_PRIORITY_QUERY_SPEC_VERSION 1
#define VK_EXT_GLOBAL_PRIORITY_QUERY_EXTENSION_NAME "VK_EXT_global_priority_query"
#define VK_MAX_GLOBAL_PRIORITY_SIZE_EXT VK_MAX_GLOBAL_PRIORITY_SIZE_KHR
typedef VkPhysicalDeviceGlobalPriorityQueryFeaturesKHR VkPhysicalDeviceGlobalPriorityQueryFeaturesEXT;

typedef VkQueueFamilyGlobalPriorityPropertiesKHR VkQueueFamilyGlobalPriorityPropertiesEXT;

// VK_EXT_image_view_min_lod is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_image_view_min_lod 1
#define VK_EXT_IMAGE_VIEW_MIN_LOD_SPEC_VERSION 1
#define VK_EXT_IMAGE_VIEW_MIN_LOD_EXTENSION_NAME "VK_EXT_image_view_min_lod"
typedef struct VkPhysicalDeviceImageViewMinLodFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 minLod;
} VkPhysicalDeviceImageViewMinLodFeaturesEXT;

typedef struct VkImageViewMinLodCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 float minLod;
} VkImageViewMinLodCreateInfoEXT;

// VK_EXT_multi_draw is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_multi_draw 1
#define VK_EXT_MULTI_DRAW_SPEC_VERSION 1
#define VK_EXT_MULTI_DRAW_EXTENSION_NAME "VK_EXT_multi_draw"
typedef struct VkPhysicalDeviceMultiDrawFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 multiDraw;
} VkPhysicalDeviceMultiDrawFeaturesEXT;

typedef struct VkPhysicalDeviceMultiDrawPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 uint32_t maxMultiDrawCount;
} VkPhysicalDeviceMultiDrawPropertiesEXT;

typedef struct VkMultiDrawInfoEXT {
 uint32_t firstVertex;
 uint32_t vertexCount;
} VkMultiDrawInfoEXT;

typedef struct VkMultiDrawIndexedInfoEXT {
 uint32_t firstIndex;
 uint32_t indexCount;
 int32_t vertexOffset;
} VkMultiDrawIndexedInfoEXT;

typedef void (VKAPI_PTR *PFN_vkCmdDrawMultiEXT)(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawInfoEXT* pVertexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride);
typedef void (VKAPI_PTR *PFN_vkCmdDrawMultiIndexedEXT)(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawIndexedInfoEXT* pIndexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, const int32_t* pVertexOffset);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdDrawMultiEXT(
 VkCommandBuffer commandBuffer,
 uint32_t drawCount,
 const VkMultiDrawInfoEXT* pVertexInfo,
 uint32_t instanceCount,
 uint32_t firstInstance,
 uint32_t stride);

VKAPI_ATTR void VKAPI_CALL vkCmdDrawMultiIndexedEXT(
 VkCommandBuffer commandBuffer,
 uint32_t drawCount,
 const VkMultiDrawIndexedInfoEXT* pIndexInfo,
 uint32_t instanceCount,
 uint32_t firstInstance,
 uint32_t stride,
 const int32_t* pVertexOffset);
#endif

// VK_EXT_image_2d_view_of_3d is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_image_2d_view_of_3d 1
#define VK_EXT_IMAGE_2D_VIEW_OF_3D_SPEC_VERSION 1
#define VK_EXT_IMAGE_2D_VIEW_OF_3D_EXTENSION_NAME "VK_EXT_image_2d_view_of_3d"
typedef struct VkPhysicalDeviceImage2DViewOf3DFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 image2DViewOf3D;
 VkBool32 sampler2DViewOf3D;
} VkPhysicalDeviceImage2DViewOf3DFeaturesEXT;

// VK_EXT_shader_tile_image is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_shader_tile_image 1
#define VK_EXT_SHADER_TILE_IMAGE_SPEC_VERSION 1
#define VK_EXT_SHADER_TILE_IMAGE_EXTENSION_NAME "VK_EXT_shader_tile_image"
typedef struct VkPhysicalDeviceShaderTileImageFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 shaderTileImageColorReadAccess;
 VkBool32 shaderTileImageDepthReadAccess;
 VkBool32 shaderTileImageStencilReadAccess;
} VkPhysicalDeviceShaderTileImageFeaturesEXT;

typedef struct VkPhysicalDeviceShaderTileImagePropertiesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 shaderTileImageCoherentReadAccelerated;
 VkBool32 shaderTileImageReadSampleFromPixelRateInvocation;
 VkBool32 shaderTileImageReadFromHelperInvocation;
} VkPhysicalDeviceShaderTileImagePropertiesEXT;

// VK_EXT_opacity_micromap is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_opacity_micromap 1
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkMicromapEXT)
#define VK_EXT_OPACITY_MICROMAP_SPEC_VERSION 2
#define VK_EXT_OPACITY_MICROMAP_EXTENSION_NAME "VK_EXT_opacity_micromap"

typedef enum VkMicromapTypeEXT {
 VK_MICROMAP_TYPE_OPACITY_MICROMAP_EXT = 0,

 VK_MICROMAP_TYPE_DISPLACEMENT_MICROMAP_NV = 1000397000,

 VK_MICROMAP_TYPE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkMicromapTypeEXT;

typedef enum VkBuildMicromapModeEXT {
 VK_BUILD_MICROMAP_MODE_BUILD_EXT = 0,
 VK_BUILD_MICROMAP_MODE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkBuildMicromapModeEXT;

typedef enum VkCopyMicromapModeEXT {
 VK_COPY_MICROMAP_MODE_CLONE_EXT = 0,
 VK_COPY_MICROMAP_MODE_SERIALIZE_EXT = 1,
 VK_COPY_MICROMAP_MODE_DESERIALIZE_EXT = 2,
 VK_COPY_MICROMAP_MODE_COMPACT_EXT = 3,
 VK_COPY_MICROMAP_MODE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkCopyMicromapModeEXT;

typedef enum VkOpacityMicromapFormatEXT {
 VK_OPACITY_MICROMAP_FORMAT_2_STATE_EXT = 1,
 VK_OPACITY_MICROMAP_FORMAT_4_STATE_EXT = 2,
 VK_OPACITY_MICROMAP_FORMAT_MAX_ENUM_EXT = 0x7FFFFFFF
} VkOpacityMicromapFormatEXT;

typedef enum VkOpacityMicromapSpecialIndexEXT {
 VK_OPACITY_MICROMAP_SPECIAL_INDEX_FULLY_TRANSPARENT_EXT = -1,
 VK_OPACITY_MICROMAP_SPECIAL_INDEX_FULLY_OPAQUE_EXT = -2,
 VK_OPACITY_MICROMAP_SPECIAL_INDEX_FULLY_UNKNOWN_TRANSPARENT_EXT = -3,
 VK_OPACITY_MICROMAP_SPECIAL_INDEX_FULLY_UNKNOWN_OPAQUE_EXT = -4,
 VK_OPACITY_MICROMAP_SPECIAL_INDEX_MAX_ENUM_EXT = 0x7FFFFFFF
} VkOpacityMicromapSpecialIndexEXT;

typedef enum VkAccelerationStructureCompatibilityKHR {
 VK_ACCELERATION_STRUCTURE_COMPATIBILITY_COMPATIBLE_KHR = 0,
 VK_ACCELERATION_STRUCTURE_COMPATIBILITY_INCOMPATIBLE_KHR = 1,
 VK_ACCELERATION_STRUCTURE_COMPATIBILITY_MAX_ENUM_KHR = 0x7FFFFFFF
} VkAccelerationStructureCompatibilityKHR;

typedef enum VkAccelerationStructureBuildTypeKHR {
 VK_ACCELERATION_STRUCTURE_BUILD_TYPE_HOST_KHR = 0,
 VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR = 1,
 VK_ACCELERATION_STRUCTURE_BUILD_TYPE_HOST_OR_DEVICE_KHR = 2,
 VK_ACCELERATION_STRUCTURE_BUILD_TYPE_MAX_ENUM_KHR = 0x7FFFFFFF
} VkAccelerationStructureBuildTypeKHR;

typedef enum VkBuildMicromapFlagBitsEXT {
 VK_BUILD_MICROMAP_PREFER_FAST_TRACE_BIT_EXT = 0x00000001,
 VK_BUILD_MICROMAP_PREFER_FAST_BUILD_BIT_EXT = 0x00000002,
 VK_BUILD_MICROMAP_ALLOW_COMPACTION_BIT_EXT = 0x00000004,
 VK_BUILD_MICROMAP_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkBuildMicromapFlagBitsEXT;
typedef VkFlags VkBuildMicromapFlagsEXT;

typedef enum VkMicromapCreateFlagBitsEXT {
 VK_MICROMAP_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT_EXT = 0x00000001,
 VK_MICROMAP_CREATE_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkMicromapCreateFlagBitsEXT;
typedef VkFlags VkMicromapCreateFlagsEXT;
typedef struct VkMicromapUsageEXT {
 uint32_t count;
 uint32_t subdivisionLevel;
 uint32_t format;
} VkMicromapUsageEXT;

typedef union VkDeviceOrHostAddressKHR {
 VkDeviceAddress deviceAddress;
 void* hostAddress;
} VkDeviceOrHostAddressKHR;

typedef struct VkMicromapBuildInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkMicromapTypeEXT type;
 VkBuildMicromapFlagsEXT flags;
 VkBuildMicromapModeEXT mode;
 VkMicromapEXT dstMicromap;
 uint32_t usageCountsCount;
 const VkMicromapUsageEXT* pUsageCounts;
 const VkMicromapUsageEXT* const* ppUsageCounts;
 VkDeviceOrHostAddressConstKHR data;
 VkDeviceOrHostAddressKHR scratchData;
 VkDeviceOrHostAddressConstKHR triangleArray;
 VkDeviceSize triangleArrayStride;
} VkMicromapBuildInfoEXT;

typedef struct VkMicromapCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkMicromapCreateFlagsEXT createFlags;
 VkBuffer buffer;
 VkDeviceSize offset;
 VkDeviceSize size;
 VkMicromapTypeEXT type;
 VkDeviceAddress deviceAddress;
} VkMicromapCreateInfoEXT;

typedef struct VkPhysicalDeviceOpacityMicromapFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 micromap;
 VkBool32 micromapCaptureReplay;
 VkBool32 micromapHostCommands;
} VkPhysicalDeviceOpacityMicromapFeaturesEXT;

typedef struct VkPhysicalDeviceOpacityMicromapPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 uint32_t maxOpacity2StateSubdivisionLevel;
 uint32_t maxOpacity4StateSubdivisionLevel;
} VkPhysicalDeviceOpacityMicromapPropertiesEXT;

typedef struct VkMicromapVersionInfoEXT {
 VkStructureType sType;
 const void* pNext;
 const uint8_t* pVersionData;
} VkMicromapVersionInfoEXT;

typedef struct VkCopyMicromapToMemoryInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkMicromapEXT src;
 VkDeviceOrHostAddressKHR dst;
 VkCopyMicromapModeEXT mode;
} VkCopyMicromapToMemoryInfoEXT;

typedef struct VkCopyMemoryToMicromapInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkDeviceOrHostAddressConstKHR src;
 VkMicromapEXT dst;
 VkCopyMicromapModeEXT mode;
} VkCopyMemoryToMicromapInfoEXT;

typedef struct VkCopyMicromapInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkMicromapEXT src;
 VkMicromapEXT dst;
 VkCopyMicromapModeEXT mode;
} VkCopyMicromapInfoEXT;

typedef struct VkMicromapBuildSizesInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkDeviceSize micromapSize;
 VkDeviceSize buildScratchSize;
 VkBool32 discardable;
} VkMicromapBuildSizesInfoEXT;

typedef struct VkAccelerationStructureTrianglesOpacityMicromapEXT {
 VkStructureType sType;
 void* pNext;
 VkIndexType indexType;
 VkDeviceOrHostAddressConstKHR indexBuffer;
 VkDeviceSize indexStride;
 uint32_t baseTriangle;
 uint32_t usageCountsCount;
 const VkMicromapUsageEXT* pUsageCounts;
 const VkMicromapUsageEXT* const* ppUsageCounts;
 VkMicromapEXT micromap;
} VkAccelerationStructureTrianglesOpacityMicromapEXT;

typedef struct VkMicromapTriangleEXT {
 uint32_t dataOffset;
 uint16_t subdivisionLevel;
 uint16_t format;
} VkMicromapTriangleEXT;

typedef VkResult (VKAPI_PTR *PFN_vkCreateMicromapEXT)(VkDevice device, const VkMicromapCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkMicromapEXT* pMicromap);
typedef void (VKAPI_PTR *PFN_vkDestroyMicromapEXT)(VkDevice device, VkMicromapEXT micromap, const VkAllocationCallbacks* pAllocator);
typedef void (VKAPI_PTR *PFN_vkCmdBuildMicromapsEXT)(VkCommandBuffer commandBuffer, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos);
typedef VkResult (VKAPI_PTR *PFN_vkBuildMicromapsEXT)(VkDevice device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos);
typedef VkResult (VKAPI_PTR *PFN_vkCopyMicromapEXT)(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapInfoEXT* pInfo);
typedef VkResult (VKAPI_PTR *PFN_vkCopyMicromapToMemoryEXT)(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapToMemoryInfoEXT* pInfo);
typedef VkResult (VKAPI_PTR *PFN_vkCopyMemoryToMicromapEXT)(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToMicromapInfoEXT* pInfo);
typedef VkResult (VKAPI_PTR *PFN_vkWriteMicromapsPropertiesEXT)(VkDevice device, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType queryType, size_t dataSize, void* pData, size_t stride);
typedef void (VKAPI_PTR *PFN_vkCmdCopyMicromapEXT)(VkCommandBuffer commandBuffer, const VkCopyMicromapInfoEXT* pInfo);
typedef void (VKAPI_PTR *PFN_vkCmdCopyMicromapToMemoryEXT)(VkCommandBuffer commandBuffer, const VkCopyMicromapToMemoryInfoEXT* pInfo);
typedef void (VKAPI_PTR *PFN_vkCmdCopyMemoryToMicromapEXT)(VkCommandBuffer commandBuffer, const VkCopyMemoryToMicromapInfoEXT* pInfo);
typedef void (VKAPI_PTR *PFN_vkCmdWriteMicromapsPropertiesEXT)(VkCommandBuffer commandBuffer, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery);
typedef void (VKAPI_PTR *PFN_vkGetDeviceMicromapCompatibilityEXT)(VkDevice device, const VkMicromapVersionInfoEXT* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility);
typedef void (VKAPI_PTR *PFN_vkGetMicromapBuildSizesEXT)(VkDevice device, VkAccelerationStructureBuildTypeKHR buildType, const VkMicromapBuildInfoEXT* pBuildInfo, VkMicromapBuildSizesInfoEXT* pSizeInfo);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateMicromapEXT(
 VkDevice device,
 const VkMicromapCreateInfoEXT* pCreateInfo,
 const VkAllocationCallbacks* pAllocator,
 VkMicromapEXT* pMicromap);

VKAPI_ATTR void VKAPI_CALL vkDestroyMicromapEXT(
 VkDevice device,
 VkMicromapEXT micromap,
 const VkAllocationCallbacks* pAllocator);

VKAPI_ATTR void VKAPI_CALL vkCmdBuildMicromapsEXT(
 VkCommandBuffer commandBuffer,
 uint32_t infoCount,
 const VkMicromapBuildInfoEXT* pInfos);

VKAPI_ATTR VkResult VKAPI_CALL vkBuildMicromapsEXT(
 VkDevice device,
 VkDeferredOperationKHR deferredOperation,
 uint32_t infoCount,
 const VkMicromapBuildInfoEXT* pInfos);

VKAPI_ATTR VkResult VKAPI_CALL vkCopyMicromapEXT(
 VkDevice device,
 VkDeferredOperationKHR deferredOperation,
 const VkCopyMicromapInfoEXT* pInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkCopyMicromapToMemoryEXT(
 VkDevice device,
 VkDeferredOperationKHR deferredOperation,
 const VkCopyMicromapToMemoryInfoEXT* pInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkCopyMemoryToMicromapEXT(
 VkDevice device,
 VkDeferredOperationKHR deferredOperation,
 const VkCopyMemoryToMicromapInfoEXT* pInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkWriteMicromapsPropertiesEXT(
 VkDevice device,
 uint32_t micromapCount,
 const VkMicromapEXT* pMicromaps,
 VkQueryType queryType,
 size_t dataSize,
 void* pData,
 size_t stride);

VKAPI_ATTR void VKAPI_CALL vkCmdCopyMicromapEXT(
 VkCommandBuffer commandBuffer,
 const VkCopyMicromapInfoEXT* pInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdCopyMicromapToMemoryEXT(
 VkCommandBuffer commandBuffer,
 const VkCopyMicromapToMemoryInfoEXT* pInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdCopyMemoryToMicromapEXT(
 VkCommandBuffer commandBuffer,
 const VkCopyMemoryToMicromapInfoEXT* pInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdWriteMicromapsPropertiesEXT(
 VkCommandBuffer commandBuffer,
 uint32_t micromapCount,
 const VkMicromapEXT* pMicromaps,
 VkQueryType queryType,
 VkQueryPool queryPool,
 uint32_t firstQuery);

VKAPI_ATTR void VKAPI_CALL vkGetDeviceMicromapCompatibilityEXT(
 VkDevice device,
 const VkMicromapVersionInfoEXT* pVersionInfo,
 VkAccelerationStructureCompatibilityKHR* pCompatibility);

VKAPI_ATTR void VKAPI_CALL vkGetMicromapBuildSizesEXT(
 VkDevice device,
 VkAccelerationStructureBuildTypeKHR buildType,
 const VkMicromapBuildInfoEXT* pBuildInfo,
 VkMicromapBuildSizesInfoEXT* pSizeInfo);
#endif

// VK_EXT_load_store_op_none is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_load_store_op_none 1
#define VK_EXT_LOAD_STORE_OP_NONE_SPEC_VERSION 1
#define VK_EXT_LOAD_STORE_OP_NONE_EXTENSION_NAME "VK_EXT_load_store_op_none"

// VK_HUAWEI_cluster_culling_shader is a preprocessor guard. Do not pass it to API calls.
#define VK_HUAWEI_cluster_culling_shader 1
#define VK_HUAWEI_CLUSTER_CULLING_SHADER_SPEC_VERSION 3
#define VK_HUAWEI_CLUSTER_CULLING_SHADER_EXTENSION_NAME "VK_HUAWEI_cluster_culling_shader"
typedef struct VkPhysicalDeviceClusterCullingShaderFeaturesHUAWEI {
 VkStructureType sType;
 void* pNext;
 VkBool32 clustercullingShader;
 VkBool32 multiviewClusterCullingShader;
} VkPhysicalDeviceClusterCullingShaderFeaturesHUAWEI;

typedef struct VkPhysicalDeviceClusterCullingShaderPropertiesHUAWEI {
 VkStructureType sType;
 void* pNext;
 uint32_t maxWorkGroupCount[3];
 uint32_t maxWorkGroupSize[3];
 uint32_t maxOutputClusterCount;
 VkDeviceSize indirectBufferOffsetAlignment;
} VkPhysicalDeviceClusterCullingShaderPropertiesHUAWEI;

typedef struct VkPhysicalDeviceClusterCullingShaderVrsFeaturesHUAWEI {
 VkStructureType sType;
 void* pNext;
 VkBool32 clusterShadingRate;
} VkPhysicalDeviceClusterCullingShaderVrsFeaturesHUAWEI;

typedef void (VKAPI_PTR *PFN_vkCmdDrawClusterHUAWEI)(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ);
typedef void (VKAPI_PTR *PFN_vkCmdDrawClusterIndirectHUAWEI)(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdDrawClusterHUAWEI(
 VkCommandBuffer commandBuffer,
 uint32_t groupCountX,
 uint32_t groupCountY,
 uint32_t groupCountZ);

VKAPI_ATTR void VKAPI_CALL vkCmdDrawClusterIndirectHUAWEI(
 VkCommandBuffer commandBuffer,
 VkBuffer buffer,
 VkDeviceSize offset);
#endif

// VK_EXT_border_color_swizzle is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_border_color_swizzle 1
#define VK_EXT_BORDER_COLOR_SWIZZLE_SPEC_VERSION 1
#define VK_EXT_BORDER_COLOR_SWIZZLE_EXTENSION_NAME "VK_EXT_border_color_swizzle"
typedef struct VkPhysicalDeviceBorderColorSwizzleFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 borderColorSwizzle;
 VkBool32 borderColorSwizzleFromImage;
} VkPhysicalDeviceBorderColorSwizzleFeaturesEXT;

typedef struct VkSamplerBorderColorComponentMappingCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkComponentMapping components;
 VkBool32 srgb;
} VkSamplerBorderColorComponentMappingCreateInfoEXT;

// VK_EXT_pageable_device_local_memory is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_pageable_device_local_memory 1
#define VK_EXT_PAGEABLE_DEVICE_LOCAL_MEMORY_SPEC_VERSION 1
#define VK_EXT_PAGEABLE_DEVICE_LOCAL_MEMORY_EXTENSION_NAME "VK_EXT_pageable_device_local_memory"
typedef struct VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 pageableDeviceLocalMemory;
} VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT;

typedef void (VKAPI_PTR *PFN_vkSetDeviceMemoryPriorityEXT)(VkDevice device, VkDeviceMemory memory, float priority);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkSetDeviceMemoryPriorityEXT(
 VkDevice device,
 VkDeviceMemory memory,
 float priority);
#endif

// VK_ARM_shader_core_properties is a preprocessor guard. Do not pass it to API calls.
#define VK_ARM_shader_core_properties 1
#define VK_ARM_SHADER_CORE_PROPERTIES_SPEC_VERSION 1
#define VK_ARM_SHADER_CORE_PROPERTIES_EXTENSION_NAME "VK_ARM_shader_core_properties"
typedef struct VkPhysicalDeviceShaderCorePropertiesARM {
 VkStructureType sType;
 void* pNext;
 uint32_t pixelRate;
 uint32_t texelRate;
 uint32_t fmaRate;
} VkPhysicalDeviceShaderCorePropertiesARM;

// VK_ARM_scheduling_controls is a preprocessor guard. Do not pass it to API calls.
#define VK_ARM_scheduling_controls 1
#define VK_ARM_SCHEDULING_CONTROLS_SPEC_VERSION 1
#define VK_ARM_SCHEDULING_CONTROLS_EXTENSION_NAME "VK_ARM_scheduling_controls"
typedef VkFlags64 VkPhysicalDeviceSchedulingControlsFlagsARM;

// Flag bits for VkPhysicalDeviceSchedulingControlsFlagBitsARM
typedef VkFlags64 VkPhysicalDeviceSchedulingControlsFlagBitsARM;
static const VkPhysicalDeviceSchedulingControlsFlagBitsARM VK_PHYSICAL_DEVICE_SCHEDULING_CONTROLS_SHADER_CORE_COUNT_ARM = 0x00000001ULL;

typedef struct VkDeviceQueueShaderCoreControlCreateInfoARM {
 VkStructureType sType;
 void* pNext;
 uint32_t shaderCoreCount;
} VkDeviceQueueShaderCoreControlCreateInfoARM;

typedef struct VkPhysicalDeviceSchedulingControlsFeaturesARM {
 VkStructureType sType;
 void* pNext;
 VkBool32 schedulingControls;
} VkPhysicalDeviceSchedulingControlsFeaturesARM;

typedef struct VkPhysicalDeviceSchedulingControlsPropertiesARM {
 VkStructureType sType;
 void* pNext;
 VkPhysicalDeviceSchedulingControlsFlagsARM schedulingControlsFlags;
} VkPhysicalDeviceSchedulingControlsPropertiesARM;

// VK_EXT_image_sliced_view_of_3d is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_image_sliced_view_of_3d 1
#define VK_EXT_IMAGE_SLICED_VIEW_OF_3D_SPEC_VERSION 1
#define VK_EXT_IMAGE_SLICED_VIEW_OF_3D_EXTENSION_NAME "VK_EXT_image_sliced_view_of_3d"
#define VK_REMAINING_3D_SLICES_EXT (~0U)
typedef struct VkPhysicalDeviceImageSlicedViewOf3DFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 imageSlicedViewOf3D;
} VkPhysicalDeviceImageSlicedViewOf3DFeaturesEXT;

typedef struct VkImageViewSlicedCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 uint32_t sliceOffset;
 uint32_t sliceCount;
} VkImageViewSlicedCreateInfoEXT;

// VK_VALVE_descriptor_set_host_mapping is a preprocessor guard. Do not pass it to API calls.
#define VK_VALVE_descriptor_set_host_mapping 1
#define VK_VALVE_DESCRIPTOR_SET_HOST_MAPPING_SPEC_VERSION 1
#define VK_VALVE_DESCRIPTOR_SET_HOST_MAPPING_EXTENSION_NAME "VK_VALVE_descriptor_set_host_mapping"
typedef struct VkPhysicalDeviceDescriptorSetHostMappingFeaturesVALVE {
 VkStructureType sType;
 void* pNext;
 VkBool32 descriptorSetHostMapping;
} VkPhysicalDeviceDescriptorSetHostMappingFeaturesVALVE;

typedef struct VkDescriptorSetBindingReferenceVALVE {
 VkStructureType sType;
 const void* pNext;
 VkDescriptorSetLayout descriptorSetLayout;
 uint32_t binding;
} VkDescriptorSetBindingReferenceVALVE;

typedef struct VkDescriptorSetLayoutHostMappingInfoVALVE {
 VkStructureType sType;
 void* pNext;
 size_t descriptorOffset;
 uint32_t descriptorSize;
} VkDescriptorSetLayoutHostMappingInfoVALVE;

typedef void (VKAPI_PTR *PFN_vkGetDescriptorSetLayoutHostMappingInfoVALVE)(VkDevice device, const VkDescriptorSetBindingReferenceVALVE* pBindingReference, VkDescriptorSetLayoutHostMappingInfoVALVE* pHostMapping);
typedef void (VKAPI_PTR *PFN_vkGetDescriptorSetHostMappingVALVE)(VkDevice device, VkDescriptorSet descriptorSet, void** ppData);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkGetDescriptorSetLayoutHostMappingInfoVALVE(
 VkDevice device,
 const VkDescriptorSetBindingReferenceVALVE* pBindingReference,
 VkDescriptorSetLayoutHostMappingInfoVALVE* pHostMapping);

VKAPI_ATTR void VKAPI_CALL vkGetDescriptorSetHostMappingVALVE(
 VkDevice device,
 VkDescriptorSet descriptorSet,
 void** ppData);
#endif

// VK_EXT_depth_clamp_zero_one is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_depth_clamp_zero_one 1
#define VK_EXT_DEPTH_CLAMP_ZERO_ONE_SPEC_VERSION 1
#define VK_EXT_DEPTH_CLAMP_ZERO_ONE_EXTENSION_NAME "VK_EXT_depth_clamp_zero_one"
typedef struct VkPhysicalDeviceDepthClampZeroOneFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 depthClampZeroOne;
} VkPhysicalDeviceDepthClampZeroOneFeaturesEXT;

// VK_EXT_non_seamless_cube_map is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_non_seamless_cube_map 1
#define VK_EXT_NON_SEAMLESS_CUBE_MAP_SPEC_VERSION 1
#define VK_EXT_NON_SEAMLESS_CUBE_MAP_EXTENSION_NAME "VK_EXT_non_seamless_cube_map"
typedef struct VkPhysicalDeviceNonSeamlessCubeMapFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 nonSeamlessCubeMap;
} VkPhysicalDeviceNonSeamlessCubeMapFeaturesEXT;

// VK_ARM_render_pass_striped is a preprocessor guard. Do not pass it to API calls.
#define VK_ARM_render_pass_striped 1
#define VK_ARM_RENDER_PASS_STRIPED_SPEC_VERSION 1
#define VK_ARM_RENDER_PASS_STRIPED_EXTENSION_NAME "VK_ARM_render_pass_striped"
typedef struct VkPhysicalDeviceRenderPassStripedFeaturesARM {
 VkStructureType sType;
 void* pNext;
 VkBool32 renderPassStriped;
} VkPhysicalDeviceRenderPassStripedFeaturesARM;

typedef struct VkPhysicalDeviceRenderPassStripedPropertiesARM {
 VkStructureType sType;
 void* pNext;
 VkExtent2D renderPassStripeGranularity;
 uint32_t maxRenderPassStripes;
} VkPhysicalDeviceRenderPassStripedPropertiesARM;

typedef struct VkRenderPassStripeInfoARM {
 VkStructureType sType;
 const void* pNext;
 VkRect2D stripeArea;
} VkRenderPassStripeInfoARM;

typedef struct VkRenderPassStripeBeginInfoARM {
 VkStructureType sType;
 const void* pNext;
 uint32_t stripeInfoCount;
 const VkRenderPassStripeInfoARM* pStripeInfos;
} VkRenderPassStripeBeginInfoARM;

typedef struct VkRenderPassStripeSubmitInfoARM {
 VkStructureType sType;
 const void* pNext;
 uint32_t stripeSemaphoreInfoCount;
 const VkSemaphoreSubmitInfo* pStripeSemaphoreInfos;
} VkRenderPassStripeSubmitInfoARM;

// VK_QCOM_fragment_density_map_offset is a preprocessor guard. Do not pass it to API calls.
#define VK_QCOM_fragment_density_map_offset 1
#define VK_QCOM_FRAGMENT_DENSITY_MAP_OFFSET_SPEC_VERSION 1
#define VK_QCOM_FRAGMENT_DENSITY_MAP_OFFSET_EXTENSION_NAME "VK_QCOM_fragment_density_map_offset"
typedef struct VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM {
 VkStructureType sType;
 void* pNext;
 VkBool32 fragmentDensityMapOffset;
} VkPhysicalDeviceFragmentDensityMapOffsetFeaturesQCOM;

typedef struct VkPhysicalDeviceFragmentDensityMapOffsetPropertiesQCOM {
 VkStructureType sType;
 void* pNext;
 VkExtent2D fragmentDensityOffsetGranularity;
} VkPhysicalDeviceFragmentDensityMapOffsetPropertiesQCOM;

typedef struct VkSubpassFragmentDensityMapOffsetEndInfoQCOM {
 VkStructureType sType;
 const void* pNext;
 uint32_t fragmentDensityOffsetCount;
 const VkOffset2D* pFragmentDensityOffsets;
} VkSubpassFragmentDensityMapOffsetEndInfoQCOM;

// VK_NV_copy_memory_indirect is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_copy_memory_indirect 1
#define VK_NV_COPY_MEMORY_INDIRECT_SPEC_VERSION 1
#define VK_NV_COPY_MEMORY_INDIRECT_EXTENSION_NAME "VK_NV_copy_memory_indirect"
typedef struct VkCopyMemoryIndirectCommandNV {
 VkDeviceAddress srcAddress;
 VkDeviceAddress dstAddress;
 VkDeviceSize size;
} VkCopyMemoryIndirectCommandNV;

typedef struct VkCopyMemoryToImageIndirectCommandNV {
 VkDeviceAddress srcAddress;
 uint32_t bufferRowLength;
 uint32_t bufferImageHeight;
 VkImageSubresourceLayers imageSubresource;
 VkOffset3D imageOffset;
 VkExtent3D imageExtent;
} VkCopyMemoryToImageIndirectCommandNV;

typedef struct VkPhysicalDeviceCopyMemoryIndirectFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 indirectCopy;
} VkPhysicalDeviceCopyMemoryIndirectFeaturesNV;

typedef struct VkPhysicalDeviceCopyMemoryIndirectPropertiesNV {
 VkStructureType sType;
 void* pNext;
 VkQueueFlags supportedQueues;
} VkPhysicalDeviceCopyMemoryIndirectPropertiesNV;

typedef void (VKAPI_PTR *PFN_vkCmdCopyMemoryIndirectNV)(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride);
typedef void (VKAPI_PTR *PFN_vkCmdCopyMemoryToImageIndirectNV)(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride, VkImage dstImage, VkImageLayout dstImageLayout, const VkImageSubresourceLayers* pImageSubresources);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdCopyMemoryIndirectNV(
 VkCommandBuffer commandBuffer,
 VkDeviceAddress copyBufferAddress,
 uint32_t copyCount,
 uint32_t stride);

VKAPI_ATTR void VKAPI_CALL vkCmdCopyMemoryToImageIndirectNV(
 VkCommandBuffer commandBuffer,
 VkDeviceAddress copyBufferAddress,
 uint32_t copyCount,
 uint32_t stride,
 VkImage dstImage,
 VkImageLayout dstImageLayout,
 const VkImageSubresourceLayers* pImageSubresources);
#endif

// VK_NV_memory_decompression is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_memory_decompression 1
#define VK_NV_MEMORY_DECOMPRESSION_SPEC_VERSION 1
#define VK_NV_MEMORY_DECOMPRESSION_EXTENSION_NAME "VK_NV_memory_decompression"

// Flag bits for VkMemoryDecompressionMethodFlagBitsNV
typedef VkFlags64 VkMemoryDecompressionMethodFlagBitsNV;
static const VkMemoryDecompressionMethodFlagBitsNV VK_MEMORY_DECOMPRESSION_METHOD_GDEFLATE_1_0_BIT_NV = 0x00000001ULL;

typedef VkFlags64 VkMemoryDecompressionMethodFlagsNV;
typedef struct VkDecompressMemoryRegionNV {
 VkDeviceAddress srcAddress;
 VkDeviceAddress dstAddress;
 VkDeviceSize compressedSize;
 VkDeviceSize decompressedSize;
 VkMemoryDecompressionMethodFlagsNV decompressionMethod;
} VkDecompressMemoryRegionNV;

typedef struct VkPhysicalDeviceMemoryDecompressionFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 memoryDecompression;
} VkPhysicalDeviceMemoryDecompressionFeaturesNV;

typedef struct VkPhysicalDeviceMemoryDecompressionPropertiesNV {
 VkStructureType sType;
 void* pNext;
 VkMemoryDecompressionMethodFlagsNV decompressionMethods;
 uint64_t maxDecompressionIndirectCount;
} VkPhysicalDeviceMemoryDecompressionPropertiesNV;

typedef void (VKAPI_PTR *PFN_vkCmdDecompressMemoryNV)(VkCommandBuffer commandBuffer, uint32_t decompressRegionCount, const VkDecompressMemoryRegionNV* pDecompressMemoryRegions);
typedef void (VKAPI_PTR *PFN_vkCmdDecompressMemoryIndirectCountNV)(VkCommandBuffer commandBuffer, VkDeviceAddress indirectCommandsAddress, VkDeviceAddress indirectCommandsCountAddress, uint32_t stride);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdDecompressMemoryNV(
 VkCommandBuffer commandBuffer,
 uint32_t decompressRegionCount,
 const VkDecompressMemoryRegionNV* pDecompressMemoryRegions);

VKAPI_ATTR void VKAPI_CALL vkCmdDecompressMemoryIndirectCountNV(
 VkCommandBuffer commandBuffer,
 VkDeviceAddress indirectCommandsAddress,
 VkDeviceAddress indirectCommandsCountAddress,
 uint32_t stride);
#endif

// VK_NV_device_generated_commands_compute is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_device_generated_commands_compute 1
#define VK_NV_DEVICE_GENERATED_COMMANDS_COMPUTE_SPEC_VERSION 2
#define VK_NV_DEVICE_GENERATED_COMMANDS_COMPUTE_EXTENSION_NAME "VK_NV_device_generated_commands_compute"
typedef struct VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 deviceGeneratedCompute;
 VkBool32 deviceGeneratedComputePipelines;
 VkBool32 deviceGeneratedComputeCaptureReplay;
} VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV;

typedef struct VkComputePipelineIndirectBufferInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkDeviceAddress deviceAddress;
 VkDeviceSize size;
 VkDeviceAddress pipelineDeviceAddressCaptureReplay;
} VkComputePipelineIndirectBufferInfoNV;

typedef struct VkPipelineIndirectDeviceAddressInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkPipelineBindPoint pipelineBindPoint;
 VkPipeline pipeline;
} VkPipelineIndirectDeviceAddressInfoNV;

typedef struct VkBindPipelineIndirectCommandNV {
 VkDeviceAddress pipelineAddress;
} VkBindPipelineIndirectCommandNV;

typedef void (VKAPI_PTR *PFN_vkGetPipelineIndirectMemoryRequirementsNV)(VkDevice device, const VkComputePipelineCreateInfo* pCreateInfo, VkMemoryRequirements2* pMemoryRequirements);
typedef void (VKAPI_PTR *PFN_vkCmdUpdatePipelineIndirectBufferNV)(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline);
typedef VkDeviceAddress (VKAPI_PTR *PFN_vkGetPipelineIndirectDeviceAddressNV)(VkDevice device, const VkPipelineIndirectDeviceAddressInfoNV* pInfo);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkGetPipelineIndirectMemoryRequirementsNV(
 VkDevice device,
 const VkComputePipelineCreateInfo* pCreateInfo,
 VkMemoryRequirements2* pMemoryRequirements);

VKAPI_ATTR void VKAPI_CALL vkCmdUpdatePipelineIndirectBufferNV(
 VkCommandBuffer commandBuffer,
 VkPipelineBindPoint pipelineBindPoint,
 VkPipeline pipeline);

VKAPI_ATTR VkDeviceAddress VKAPI_CALL vkGetPipelineIndirectDeviceAddressNV(
 VkDevice device,
 const VkPipelineIndirectDeviceAddressInfoNV* pInfo);
#endif

// VK_NV_linear_color_attachment is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_linear_color_attachment 1
#define VK_NV_LINEAR_COLOR_ATTACHMENT_SPEC_VERSION 1
#define VK_NV_LINEAR_COLOR_ATTACHMENT_EXTENSION_NAME "VK_NV_linear_color_attachment"
typedef struct VkPhysicalDeviceLinearColorAttachmentFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 linearColorAttachment;
} VkPhysicalDeviceLinearColorAttachmentFeaturesNV;

// VK_GOOGLE_surfaceless_query is a preprocessor guard. Do not pass it to API calls.
#define VK_GOOGLE_surfaceless_query 1
#define VK_GOOGLE_SURFACELESS_QUERY_SPEC_VERSION 2
#define VK_GOOGLE_SURFACELESS_QUERY_EXTENSION_NAME "VK_GOOGLE_surfaceless_query"

// VK_EXT_image_compression_control_swapchain is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_image_compression_control_swapchain 1
#define VK_EXT_IMAGE_COMPRESSION_CONTROL_SWAPCHAIN_SPEC_VERSION 1
#define VK_EXT_IMAGE_COMPRESSION_CONTROL_SWAPCHAIN_EXTENSION_NAME "VK_EXT_image_compression_control_swapchain"
typedef struct VkPhysicalDeviceImageCompressionControlSwapchainFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 imageCompressionControlSwapchain;
} VkPhysicalDeviceImageCompressionControlSwapchainFeaturesEXT;

// VK_QCOM_image_processing is a preprocessor guard. Do not pass it to API calls.
#define VK_QCOM_image_processing 1
#define VK_QCOM_IMAGE_PROCESSING_SPEC_VERSION 1
#define VK_QCOM_IMAGE_PROCESSING_EXTENSION_NAME "VK_QCOM_image_processing"
typedef struct VkImageViewSampleWeightCreateInfoQCOM {
 VkStructureType sType;
 const void* pNext;
 VkOffset2D filterCenter;
 VkExtent2D filterSize;
 uint32_t numPhases;
} VkImageViewSampleWeightCreateInfoQCOM;

typedef struct VkPhysicalDeviceImageProcessingFeaturesQCOM {
 VkStructureType sType;
 void* pNext;
 VkBool32 textureSampleWeighted;
 VkBool32 textureBoxFilter;
 VkBool32 textureBlockMatch;
} VkPhysicalDeviceImageProcessingFeaturesQCOM;

typedef struct VkPhysicalDeviceImageProcessingPropertiesQCOM {
 VkStructureType sType;
 void* pNext;
 uint32_t maxWeightFilterPhases;
 VkExtent2D maxWeightFilterDimension;
 VkExtent2D maxBlockMatchRegion;
 VkExtent2D maxBoxFilterBlockSize;
} VkPhysicalDeviceImageProcessingPropertiesQCOM;

// VK_EXT_nested_command_buffer is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_nested_command_buffer 1
#define VK_EXT_NESTED_COMMAND_BUFFER_SPEC_VERSION 1
#define VK_EXT_NESTED_COMMAND_BUFFER_EXTENSION_NAME "VK_EXT_nested_command_buffer"
typedef struct VkPhysicalDeviceNestedCommandBufferFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 nestedCommandBuffer;
 VkBool32 nestedCommandBufferRendering;
 VkBool32 nestedCommandBufferSimultaneousUse;
} VkPhysicalDeviceNestedCommandBufferFeaturesEXT;

typedef struct VkPhysicalDeviceNestedCommandBufferPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 uint32_t maxCommandBufferNestingLevel;
} VkPhysicalDeviceNestedCommandBufferPropertiesEXT;

// VK_EXT_external_memory_acquire_unmodified is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_external_memory_acquire_unmodified 1
#define VK_EXT_EXTERNAL_MEMORY_ACQUIRE_UNMODIFIED_SPEC_VERSION 1
#define VK_EXT_EXTERNAL_MEMORY_ACQUIRE_UNMODIFIED_EXTENSION_NAME "VK_EXT_external_memory_acquire_unmodified"
typedef struct VkExternalMemoryAcquireUnmodifiedEXT {
 VkStructureType sType;
 const void* pNext;
 VkBool32 acquireUnmodifiedMemory;
} VkExternalMemoryAcquireUnmodifiedEXT;

// VK_EXT_extended_dynamic_state3 is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_extended_dynamic_state3 1
#define VK_EXT_EXTENDED_DYNAMIC_STATE_3_SPEC_VERSION 2
#define VK_EXT_EXTENDED_DYNAMIC_STATE_3_EXTENSION_NAME "VK_EXT_extended_dynamic_state3"
typedef struct VkPhysicalDeviceExtendedDynamicState3FeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 extendedDynamicState3TessellationDomainOrigin;
 VkBool32 extendedDynamicState3DepthClampEnable;
 VkBool32 extendedDynamicState3PolygonMode;
 VkBool32 extendedDynamicState3RasterizationSamples;
 VkBool32 extendedDynamicState3SampleMask;
 VkBool32 extendedDynamicState3AlphaToCoverageEnable;
 VkBool32 extendedDynamicState3AlphaToOneEnable;
 VkBool32 extendedDynamicState3LogicOpEnable;
 VkBool32 extendedDynamicState3ColorBlendEnable;
 VkBool32 extendedDynamicState3ColorBlendEquation;
 VkBool32 extendedDynamicState3ColorWriteMask;
 VkBool32 extendedDynamicState3RasterizationStream;
 VkBool32 extendedDynamicState3ConservativeRasterizationMode;
 VkBool32 extendedDynamicState3ExtraPrimitiveOverestimationSize;
 VkBool32 extendedDynamicState3DepthClipEnable;
 VkBool32 extendedDynamicState3SampleLocationsEnable;
 VkBool32 extendedDynamicState3ColorBlendAdvanced;
 VkBool32 extendedDynamicState3ProvokingVertexMode;
 VkBool32 extendedDynamicState3LineRasterizationMode;
 VkBool32 extendedDynamicState3LineStippleEnable;
 VkBool32 extendedDynamicState3DepthClipNegativeOneToOne;
 VkBool32 extendedDynamicState3ViewportWScalingEnable;
 VkBool32 extendedDynamicState3ViewportSwizzle;
 VkBool32 extendedDynamicState3CoverageToColorEnable;
 VkBool32 extendedDynamicState3CoverageToColorLocation;
 VkBool32 extendedDynamicState3CoverageModulationMode;
 VkBool32 extendedDynamicState3CoverageModulationTableEnable;
 VkBool32 extendedDynamicState3CoverageModulationTable;
 VkBool32 extendedDynamicState3CoverageReductionMode;
 VkBool32 extendedDynamicState3RepresentativeFragmentTestEnable;
 VkBool32 extendedDynamicState3ShadingRateImageEnable;
} VkPhysicalDeviceExtendedDynamicState3FeaturesEXT;

typedef struct VkPhysicalDeviceExtendedDynamicState3PropertiesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 dynamicPrimitiveTopologyUnrestricted;
} VkPhysicalDeviceExtendedDynamicState3PropertiesEXT;

typedef struct VkColorBlendEquationEXT {
 VkBlendFactor srcColorBlendFactor;
 VkBlendFactor dstColorBlendFactor;
 VkBlendOp colorBlendOp;
 VkBlendFactor srcAlphaBlendFactor;
 VkBlendFactor dstAlphaBlendFactor;
 VkBlendOp alphaBlendOp;
} VkColorBlendEquationEXT;

typedef struct VkColorBlendAdvancedEXT {
 VkBlendOp advancedBlendOp;
 VkBool32 srcPremultiplied;
 VkBool32 dstPremultiplied;
 VkBlendOverlapEXT blendOverlap;
 VkBool32 clampResults;
} VkColorBlendAdvancedEXT;

typedef void (VKAPI_PTR *PFN_vkCmdSetTessellationDomainOriginEXT)(VkCommandBuffer commandBuffer, VkTessellationDomainOrigin domainOrigin);
typedef void (VKAPI_PTR *PFN_vkCmdSetDepthClampEnableEXT)(VkCommandBuffer commandBuffer, VkBool32 depthClampEnable);
typedef void (VKAPI_PTR *PFN_vkCmdSetPolygonModeEXT)(VkCommandBuffer commandBuffer, VkPolygonMode polygonMode);
typedef void (VKAPI_PTR *PFN_vkCmdSetRasterizationSamplesEXT)(VkCommandBuffer commandBuffer, VkSampleCountFlagBits rasterizationSamples);
typedef void (VKAPI_PTR *PFN_vkCmdSetSampleMaskEXT)(VkCommandBuffer commandBuffer, VkSampleCountFlagBits samples, const VkSampleMask* pSampleMask);
typedef void (VKAPI_PTR *PFN_vkCmdSetAlphaToCoverageEnableEXT)(VkCommandBuffer commandBuffer, VkBool32 alphaToCoverageEnable);
typedef void (VKAPI_PTR *PFN_vkCmdSetAlphaToOneEnableEXT)(VkCommandBuffer commandBuffer, VkBool32 alphaToOneEnable);
typedef void (VKAPI_PTR *PFN_vkCmdSetLogicOpEnableEXT)(VkCommandBuffer commandBuffer, VkBool32 logicOpEnable);
typedef void (VKAPI_PTR *PFN_vkCmdSetColorBlendEnableEXT)(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkBool32* pColorBlendEnables);
typedef void (VKAPI_PTR *PFN_vkCmdSetColorBlendEquationEXT)(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendEquationEXT* pColorBlendEquations);
typedef void (VKAPI_PTR *PFN_vkCmdSetColorWriteMaskEXT)(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorComponentFlags* pColorWriteMasks);
typedef void (VKAPI_PTR *PFN_vkCmdSetRasterizationStreamEXT)(VkCommandBuffer commandBuffer, uint32_t rasterizationStream);
typedef void (VKAPI_PTR *PFN_vkCmdSetConservativeRasterizationModeEXT)(VkCommandBuffer commandBuffer, VkConservativeRasterizationModeEXT conservativeRasterizationMode);
typedef void (VKAPI_PTR *PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT)(VkCommandBuffer commandBuffer, float extraPrimitiveOverestimationSize);
typedef void (VKAPI_PTR *PFN_vkCmdSetDepthClipEnableEXT)(VkCommandBuffer commandBuffer, VkBool32 depthClipEnable);
typedef void (VKAPI_PTR *PFN_vkCmdSetSampleLocationsEnableEXT)(VkCommandBuffer commandBuffer, VkBool32 sampleLocationsEnable);
typedef void (VKAPI_PTR *PFN_vkCmdSetColorBlendAdvancedEXT)(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendAdvancedEXT* pColorBlendAdvanced);
typedef void (VKAPI_PTR *PFN_vkCmdSetProvokingVertexModeEXT)(VkCommandBuffer commandBuffer, VkProvokingVertexModeEXT provokingVertexMode);
typedef void (VKAPI_PTR *PFN_vkCmdSetLineRasterizationModeEXT)(VkCommandBuffer commandBuffer, VkLineRasterizationModeEXT lineRasterizationMode);
typedef void (VKAPI_PTR *PFN_vkCmdSetLineStippleEnableEXT)(VkCommandBuffer commandBuffer, VkBool32 stippledLineEnable);
typedef void (VKAPI_PTR *PFN_vkCmdSetDepthClipNegativeOneToOneEXT)(VkCommandBuffer commandBuffer, VkBool32 negativeOneToOne);
typedef void (VKAPI_PTR *PFN_vkCmdSetViewportWScalingEnableNV)(VkCommandBuffer commandBuffer, VkBool32 viewportWScalingEnable);
typedef void (VKAPI_PTR *PFN_vkCmdSetViewportSwizzleNV)(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportSwizzleNV* pViewportSwizzles);
typedef void (VKAPI_PTR *PFN_vkCmdSetCoverageToColorEnableNV)(VkCommandBuffer commandBuffer, VkBool32 coverageToColorEnable);
typedef void (VKAPI_PTR *PFN_vkCmdSetCoverageToColorLocationNV)(VkCommandBuffer commandBuffer, uint32_t coverageToColorLocation);
typedef void (VKAPI_PTR *PFN_vkCmdSetCoverageModulationModeNV)(VkCommandBuffer commandBuffer, VkCoverageModulationModeNV coverageModulationMode);
typedef void (VKAPI_PTR *PFN_vkCmdSetCoverageModulationTableEnableNV)(VkCommandBuffer commandBuffer, VkBool32 coverageModulationTableEnable);
typedef void (VKAPI_PTR *PFN_vkCmdSetCoverageModulationTableNV)(VkCommandBuffer commandBuffer, uint32_t coverageModulationTableCount, const float* pCoverageModulationTable);
typedef void (VKAPI_PTR *PFN_vkCmdSetShadingRateImageEnableNV)(VkCommandBuffer commandBuffer, VkBool32 shadingRateImageEnable);
typedef void (VKAPI_PTR *PFN_vkCmdSetRepresentativeFragmentTestEnableNV)(VkCommandBuffer commandBuffer, VkBool32 representativeFragmentTestEnable);
typedef void (VKAPI_PTR *PFN_vkCmdSetCoverageReductionModeNV)(VkCommandBuffer commandBuffer, VkCoverageReductionModeNV coverageReductionMode);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdSetTessellationDomainOriginEXT(
 VkCommandBuffer commandBuffer,
 VkTessellationDomainOrigin domainOrigin);

VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthClampEnableEXT(
 VkCommandBuffer commandBuffer,
 VkBool32 depthClampEnable);

VKAPI_ATTR void VKAPI_CALL vkCmdSetPolygonModeEXT(
 VkCommandBuffer commandBuffer,
 VkPolygonMode polygonMode);

VKAPI_ATTR void VKAPI_CALL vkCmdSetRasterizationSamplesEXT(
 VkCommandBuffer commandBuffer,
 VkSampleCountFlagBits rasterizationSamples);

VKAPI_ATTR void VKAPI_CALL vkCmdSetSampleMaskEXT(
 VkCommandBuffer commandBuffer,
 VkSampleCountFlagBits samples,
 const VkSampleMask* pSampleMask);

VKAPI_ATTR void VKAPI_CALL vkCmdSetAlphaToCoverageEnableEXT(
 VkCommandBuffer commandBuffer,
 VkBool32 alphaToCoverageEnable);

VKAPI_ATTR void VKAPI_CALL vkCmdSetAlphaToOneEnableEXT(
 VkCommandBuffer commandBuffer,
 VkBool32 alphaToOneEnable);

VKAPI_ATTR void VKAPI_CALL vkCmdSetLogicOpEnableEXT(
 VkCommandBuffer commandBuffer,
 VkBool32 logicOpEnable);

VKAPI_ATTR void VKAPI_CALL vkCmdSetColorBlendEnableEXT(
 VkCommandBuffer commandBuffer,
 uint32_t firstAttachment,
 uint32_t attachmentCount,
 const VkBool32* pColorBlendEnables);

VKAPI_ATTR void VKAPI_CALL vkCmdSetColorBlendEquationEXT(
 VkCommandBuffer commandBuffer,
 uint32_t firstAttachment,
 uint32_t attachmentCount,
 const VkColorBlendEquationEXT* pColorBlendEquations);

VKAPI_ATTR void VKAPI_CALL vkCmdSetColorWriteMaskEXT(
 VkCommandBuffer commandBuffer,
 uint32_t firstAttachment,
 uint32_t attachmentCount,
 const VkColorComponentFlags* pColorWriteMasks);

VKAPI_ATTR void VKAPI_CALL vkCmdSetRasterizationStreamEXT(
 VkCommandBuffer commandBuffer,
 uint32_t rasterizationStream);

VKAPI_ATTR void VKAPI_CALL vkCmdSetConservativeRasterizationModeEXT(
 VkCommandBuffer commandBuffer,
 VkConservativeRasterizationModeEXT conservativeRasterizationMode);

VKAPI_ATTR void VKAPI_CALL vkCmdSetExtraPrimitiveOverestimationSizeEXT(
 VkCommandBuffer commandBuffer,
 float extraPrimitiveOverestimationSize);

VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthClipEnableEXT(
 VkCommandBuffer commandBuffer,
 VkBool32 depthClipEnable);

VKAPI_ATTR void VKAPI_CALL vkCmdSetSampleLocationsEnableEXT(
 VkCommandBuffer commandBuffer,
 VkBool32 sampleLocationsEnable);

VKAPI_ATTR void VKAPI_CALL vkCmdSetColorBlendAdvancedEXT(
 VkCommandBuffer commandBuffer,
 uint32_t firstAttachment,
 uint32_t attachmentCount,
 const VkColorBlendAdvancedEXT* pColorBlendAdvanced);

VKAPI_ATTR void VKAPI_CALL vkCmdSetProvokingVertexModeEXT(
 VkCommandBuffer commandBuffer,
 VkProvokingVertexModeEXT provokingVertexMode);

VKAPI_ATTR void VKAPI_CALL vkCmdSetLineRasterizationModeEXT(
 VkCommandBuffer commandBuffer,
 VkLineRasterizationModeEXT lineRasterizationMode);

VKAPI_ATTR void VKAPI_CALL vkCmdSetLineStippleEnableEXT(
 VkCommandBuffer commandBuffer,
 VkBool32 stippledLineEnable);

VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthClipNegativeOneToOneEXT(
 VkCommandBuffer commandBuffer,
 VkBool32 negativeOneToOne);

VKAPI_ATTR void VKAPI_CALL vkCmdSetViewportWScalingEnableNV(
 VkCommandBuffer commandBuffer,
 VkBool32 viewportWScalingEnable);

VKAPI_ATTR void VKAPI_CALL vkCmdSetViewportSwizzleNV(
 VkCommandBuffer commandBuffer,
 uint32_t firstViewport,
 uint32_t viewportCount,
 const VkViewportSwizzleNV* pViewportSwizzles);

VKAPI_ATTR void VKAPI_CALL vkCmdSetCoverageToColorEnableNV(
 VkCommandBuffer commandBuffer,
 VkBool32 coverageToColorEnable);

VKAPI_ATTR void VKAPI_CALL vkCmdSetCoverageToColorLocationNV(
 VkCommandBuffer commandBuffer,
 uint32_t coverageToColorLocation);

VKAPI_ATTR void VKAPI_CALL vkCmdSetCoverageModulationModeNV(
 VkCommandBuffer commandBuffer,
 VkCoverageModulationModeNV coverageModulationMode);

VKAPI_ATTR void VKAPI_CALL vkCmdSetCoverageModulationTableEnableNV(
 VkCommandBuffer commandBuffer,
 VkBool32 coverageModulationTableEnable);

VKAPI_ATTR void VKAPI_CALL vkCmdSetCoverageModulationTableNV(
 VkCommandBuffer commandBuffer,
 uint32_t coverageModulationTableCount,
 const float* pCoverageModulationTable);

VKAPI_ATTR void VKAPI_CALL vkCmdSetShadingRateImageEnableNV(
 VkCommandBuffer commandBuffer,
 VkBool32 shadingRateImageEnable);

VKAPI_ATTR void VKAPI_CALL vkCmdSetRepresentativeFragmentTestEnableNV(
 VkCommandBuffer commandBuffer,
 VkBool32 representativeFragmentTestEnable);

VKAPI_ATTR void VKAPI_CALL vkCmdSetCoverageReductionModeNV(
 VkCommandBuffer commandBuffer,
 VkCoverageReductionModeNV coverageReductionMode);
#endif

// VK_EXT_subpass_merge_feedback is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_subpass_merge_feedback 1
#define VK_EXT_SUBPASS_MERGE_FEEDBACK_SPEC_VERSION 2
#define VK_EXT_SUBPASS_MERGE_FEEDBACK_EXTENSION_NAME "VK_EXT_subpass_merge_feedback"

typedef enum VkSubpassMergeStatusEXT {
 VK_SUBPASS_MERGE_STATUS_MERGED_EXT = 0,
 VK_SUBPASS_MERGE_STATUS_DISALLOWED_EXT = 1,
 VK_SUBPASS_MERGE_STATUS_NOT_MERGED_SIDE_EFFECTS_EXT = 2,
 VK_SUBPASS_MERGE_STATUS_NOT_MERGED_SAMPLES_MISMATCH_EXT = 3,
 VK_SUBPASS_MERGE_STATUS_NOT_MERGED_VIEWS_MISMATCH_EXT = 4,
 VK_SUBPASS_MERGE_STATUS_NOT_MERGED_ALIASING_EXT = 5,
 VK_SUBPASS_MERGE_STATUS_NOT_MERGED_DEPENDENCIES_EXT = 6,
 VK_SUBPASS_MERGE_STATUS_NOT_MERGED_INCOMPATIBLE_INPUT_ATTACHMENT_EXT = 7,
 VK_SUBPASS_MERGE_STATUS_NOT_MERGED_TOO_MANY_ATTACHMENTS_EXT = 8,
 VK_SUBPASS_MERGE_STATUS_NOT_MERGED_INSUFFICIENT_STORAGE_EXT = 9,
 VK_SUBPASS_MERGE_STATUS_NOT_MERGED_DEPTH_STENCIL_COUNT_EXT = 10,
 VK_SUBPASS_MERGE_STATUS_NOT_MERGED_RESOLVE_ATTACHMENT_REUSE_EXT = 11,
 VK_SUBPASS_MERGE_STATUS_NOT_MERGED_SINGLE_SUBPASS_EXT = 12,
 VK_SUBPASS_MERGE_STATUS_NOT_MERGED_UNSPECIFIED_EXT = 13,
 VK_SUBPASS_MERGE_STATUS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkSubpassMergeStatusEXT;
typedef struct VkPhysicalDeviceSubpassMergeFeedbackFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 subpassMergeFeedback;
} VkPhysicalDeviceSubpassMergeFeedbackFeaturesEXT;

typedef struct VkRenderPassCreationControlEXT {
 VkStructureType sType;
 const void* pNext;
 VkBool32 disallowMerging;
} VkRenderPassCreationControlEXT;

typedef struct VkRenderPassCreationFeedbackInfoEXT {
 uint32_t postMergeSubpassCount;
} VkRenderPassCreationFeedbackInfoEXT;

typedef struct VkRenderPassCreationFeedbackCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkRenderPassCreationFeedbackInfoEXT* pRenderPassFeedback;
} VkRenderPassCreationFeedbackCreateInfoEXT;

typedef struct VkRenderPassSubpassFeedbackInfoEXT {
 VkSubpassMergeStatusEXT subpassMergeStatus;
 char description[VK_MAX_DESCRIPTION_SIZE];
 uint32_t postMergeIndex;
} VkRenderPassSubpassFeedbackInfoEXT;

typedef struct VkRenderPassSubpassFeedbackCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkRenderPassSubpassFeedbackInfoEXT* pSubpassFeedback;
} VkRenderPassSubpassFeedbackCreateInfoEXT;

// VK_LUNARG_direct_driver_loading is a preprocessor guard. Do not pass it to API calls.
#define VK_LUNARG_direct_driver_loading 1
#define VK_LUNARG_DIRECT_DRIVER_LOADING_SPEC_VERSION 1
#define VK_LUNARG_DIRECT_DRIVER_LOADING_EXTENSION_NAME "VK_LUNARG_direct_driver_loading"

typedef enum VkDirectDriverLoadingModeLUNARG {
 VK_DIRECT_DRIVER_LOADING_MODE_EXCLUSIVE_LUNARG = 0,
 VK_DIRECT_DRIVER_LOADING_MODE_INCLUSIVE_LUNARG = 1,
 VK_DIRECT_DRIVER_LOADING_MODE_MAX_ENUM_LUNARG = 0x7FFFFFFF
} VkDirectDriverLoadingModeLUNARG;
typedef VkFlags VkDirectDriverLoadingFlagsLUNARG;
typedef PFN_vkVoidFunction (VKAPI_PTR *PFN_vkGetInstanceProcAddrLUNARG)(
 VkInstance instance, const char* pName);

typedef struct VkDirectDriverLoadingInfoLUNARG {
 VkStructureType sType;
 void* pNext;
 VkDirectDriverLoadingFlagsLUNARG flags;
 PFN_vkGetInstanceProcAddrLUNARG pfnGetInstanceProcAddr;
} VkDirectDriverLoadingInfoLUNARG;

typedef struct VkDirectDriverLoadingListLUNARG {
 VkStructureType sType;
 const void* pNext;
 VkDirectDriverLoadingModeLUNARG mode;
 uint32_t driverCount;
 const VkDirectDriverLoadingInfoLUNARG* pDrivers;
} VkDirectDriverLoadingListLUNARG;

// VK_EXT_shader_module_identifier is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_shader_module_identifier 1
#define VK_MAX_SHADER_MODULE_IDENTIFIER_SIZE_EXT 32U
#define VK_EXT_SHADER_MODULE_IDENTIFIER_SPEC_VERSION 1
#define VK_EXT_SHADER_MODULE_IDENTIFIER_EXTENSION_NAME "VK_EXT_shader_module_identifier"
typedef struct VkPhysicalDeviceShaderModuleIdentifierFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 shaderModuleIdentifier;
} VkPhysicalDeviceShaderModuleIdentifierFeaturesEXT;

typedef struct VkPhysicalDeviceShaderModuleIdentifierPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 uint8_t shaderModuleIdentifierAlgorithmUUID[VK_UUID_SIZE];
} VkPhysicalDeviceShaderModuleIdentifierPropertiesEXT;

typedef struct VkPipelineShaderStageModuleIdentifierCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 uint32_t identifierSize;
 const uint8_t* pIdentifier;
} VkPipelineShaderStageModuleIdentifierCreateInfoEXT;

typedef struct VkShaderModuleIdentifierEXT {
 VkStructureType sType;
 void* pNext;
 uint32_t identifierSize;
 uint8_t identifier[VK_MAX_SHADER_MODULE_IDENTIFIER_SIZE_EXT];
} VkShaderModuleIdentifierEXT;

typedef void (VKAPI_PTR *PFN_vkGetShaderModuleIdentifierEXT)(VkDevice device, VkShaderModule shaderModule, VkShaderModuleIdentifierEXT* pIdentifier);
typedef void (VKAPI_PTR *PFN_vkGetShaderModuleCreateInfoIdentifierEXT)(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, VkShaderModuleIdentifierEXT* pIdentifier);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkGetShaderModuleIdentifierEXT(
 VkDevice device,
 VkShaderModule shaderModule,
 VkShaderModuleIdentifierEXT* pIdentifier);

VKAPI_ATTR void VKAPI_CALL vkGetShaderModuleCreateInfoIdentifierEXT(
 VkDevice device,
 const VkShaderModuleCreateInfo* pCreateInfo,
 VkShaderModuleIdentifierEXT* pIdentifier);
#endif

// VK_EXT_rasterization_order_attachment_access is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_rasterization_order_attachment_access 1
#define VK_EXT_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_SPEC_VERSION 1
#define VK_EXT_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_EXTENSION_NAME "VK_EXT_rasterization_order_attachment_access"

// VK_NV_optical_flow is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_optical_flow 1
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkOpticalFlowSessionNV)
#define VK_NV_OPTICAL_FLOW_SPEC_VERSION 1
#define VK_NV_OPTICAL_FLOW_EXTENSION_NAME "VK_NV_optical_flow"

typedef enum VkOpticalFlowPerformanceLevelNV {
 VK_OPTICAL_FLOW_PERFORMANCE_LEVEL_UNKNOWN_NV = 0,
 VK_OPTICAL_FLOW_PERFORMANCE_LEVEL_SLOW_NV = 1,
 VK_OPTICAL_FLOW_PERFORMANCE_LEVEL_MEDIUM_NV = 2,
 VK_OPTICAL_FLOW_PERFORMANCE_LEVEL_FAST_NV = 3,
 VK_OPTICAL_FLOW_PERFORMANCE_LEVEL_MAX_ENUM_NV = 0x7FFFFFFF
} VkOpticalFlowPerformanceLevelNV;

typedef enum VkOpticalFlowSessionBindingPointNV {
 VK_OPTICAL_FLOW_SESSION_BINDING_POINT_UNKNOWN_NV = 0,
 VK_OPTICAL_FLOW_SESSION_BINDING_POINT_INPUT_NV = 1,
 VK_OPTICAL_FLOW_SESSION_BINDING_POINT_REFERENCE_NV = 2,
 VK_OPTICAL_FLOW_SESSION_BINDING_POINT_HINT_NV = 3,
 VK_OPTICAL_FLOW_SESSION_BINDING_POINT_FLOW_VECTOR_NV = 4,
 VK_OPTICAL_FLOW_SESSION_BINDING_POINT_BACKWARD_FLOW_VECTOR_NV = 5,
 VK_OPTICAL_FLOW_SESSION_BINDING_POINT_COST_NV = 6,
 VK_OPTICAL_FLOW_SESSION_BINDING_POINT_BACKWARD_COST_NV = 7,
 VK_OPTICAL_FLOW_SESSION_BINDING_POINT_GLOBAL_FLOW_NV = 8,
 VK_OPTICAL_FLOW_SESSION_BINDING_POINT_MAX_ENUM_NV = 0x7FFFFFFF
} VkOpticalFlowSessionBindingPointNV;

typedef enum VkOpticalFlowGridSizeFlagBitsNV {
 VK_OPTICAL_FLOW_GRID_SIZE_UNKNOWN_NV = 0,
 VK_OPTICAL_FLOW_GRID_SIZE_1X1_BIT_NV = 0x00000001,
 VK_OPTICAL_FLOW_GRID_SIZE_2X2_BIT_NV = 0x00000002,
 VK_OPTICAL_FLOW_GRID_SIZE_4X4_BIT_NV = 0x00000004,
 VK_OPTICAL_FLOW_GRID_SIZE_8X8_BIT_NV = 0x00000008,
 VK_OPTICAL_FLOW_GRID_SIZE_FLAG_BITS_MAX_ENUM_NV = 0x7FFFFFFF
} VkOpticalFlowGridSizeFlagBitsNV;
typedef VkFlags VkOpticalFlowGridSizeFlagsNV;

typedef enum VkOpticalFlowUsageFlagBitsNV {
 VK_OPTICAL_FLOW_USAGE_UNKNOWN_NV = 0,
 VK_OPTICAL_FLOW_USAGE_INPUT_BIT_NV = 0x00000001,
 VK_OPTICAL_FLOW_USAGE_OUTPUT_BIT_NV = 0x00000002,
 VK_OPTICAL_FLOW_USAGE_HINT_BIT_NV = 0x00000004,
 VK_OPTICAL_FLOW_USAGE_COST_BIT_NV = 0x00000008,
 VK_OPTICAL_FLOW_USAGE_GLOBAL_FLOW_BIT_NV = 0x00000010,
 VK_OPTICAL_FLOW_USAGE_FLAG_BITS_MAX_ENUM_NV = 0x7FFFFFFF
} VkOpticalFlowUsageFlagBitsNV;
typedef VkFlags VkOpticalFlowUsageFlagsNV;

typedef enum VkOpticalFlowSessionCreateFlagBitsNV {
 VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_HINT_BIT_NV = 0x00000001,
 VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_COST_BIT_NV = 0x00000002,
 VK_OPTICAL_FLOW_SESSION_CREATE_ENABLE_GLOBAL_FLOW_BIT_NV = 0x00000004,
 VK_OPTICAL_FLOW_SESSION_CREATE_ALLOW_REGIONS_BIT_NV = 0x00000008,
 VK_OPTICAL_FLOW_SESSION_CREATE_BOTH_DIRECTIONS_BIT_NV = 0x00000010,
 VK_OPTICAL_FLOW_SESSION_CREATE_FLAG_BITS_MAX_ENUM_NV = 0x7FFFFFFF
} VkOpticalFlowSessionCreateFlagBitsNV;
typedef VkFlags VkOpticalFlowSessionCreateFlagsNV;

typedef enum VkOpticalFlowExecuteFlagBitsNV {
 VK_OPTICAL_FLOW_EXECUTE_DISABLE_TEMPORAL_HINTS_BIT_NV = 0x00000001,
 VK_OPTICAL_FLOW_EXECUTE_FLAG_BITS_MAX_ENUM_NV = 0x7FFFFFFF
} VkOpticalFlowExecuteFlagBitsNV;
typedef VkFlags VkOpticalFlowExecuteFlagsNV;
typedef struct VkPhysicalDeviceOpticalFlowFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 opticalFlow;
} VkPhysicalDeviceOpticalFlowFeaturesNV;

typedef struct VkPhysicalDeviceOpticalFlowPropertiesNV {
 VkStructureType sType;
 void* pNext;
 VkOpticalFlowGridSizeFlagsNV supportedOutputGridSizes;
 VkOpticalFlowGridSizeFlagsNV supportedHintGridSizes;
 VkBool32 hintSupported;
 VkBool32 costSupported;
 VkBool32 bidirectionalFlowSupported;
 VkBool32 globalFlowSupported;
 uint32_t minWidth;
 uint32_t minHeight;
 uint32_t maxWidth;
 uint32_t maxHeight;
 uint32_t maxNumRegionsOfInterest;
} VkPhysicalDeviceOpticalFlowPropertiesNV;

typedef struct VkOpticalFlowImageFormatInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkOpticalFlowUsageFlagsNV usage;
} VkOpticalFlowImageFormatInfoNV;

typedef struct VkOpticalFlowImageFormatPropertiesNV {
 VkStructureType sType;
 const void* pNext;
 VkFormat format;
} VkOpticalFlowImageFormatPropertiesNV;

typedef struct VkOpticalFlowSessionCreateInfoNV {
 VkStructureType sType;
 void* pNext;
 uint32_t width;
 uint32_t height;
 VkFormat imageFormat;
 VkFormat flowVectorFormat;
 VkFormat costFormat;
 VkOpticalFlowGridSizeFlagsNV outputGridSize;
 VkOpticalFlowGridSizeFlagsNV hintGridSize;
 VkOpticalFlowPerformanceLevelNV performanceLevel;
 VkOpticalFlowSessionCreateFlagsNV flags;
} VkOpticalFlowSessionCreateInfoNV;

typedef struct VkOpticalFlowSessionCreatePrivateDataInfoNV {
 VkStructureType sType;
 void* pNext;
 uint32_t id;
 uint32_t size;
 const void* pPrivateData;
} VkOpticalFlowSessionCreatePrivateDataInfoNV;

typedef struct VkOpticalFlowExecuteInfoNV {
 VkStructureType sType;
 void* pNext;
 VkOpticalFlowExecuteFlagsNV flags;
 uint32_t regionCount;
 const VkRect2D* pRegions;
} VkOpticalFlowExecuteInfoNV;

typedef VkResult (VKAPI_PTR *PFN_vkGetPhysicalDeviceOpticalFlowImageFormatsNV)(VkPhysicalDevice physicalDevice, const VkOpticalFlowImageFormatInfoNV* pOpticalFlowImageFormatInfo, uint32_t* pFormatCount, VkOpticalFlowImageFormatPropertiesNV* pImageFormatProperties);
typedef VkResult (VKAPI_PTR *PFN_vkCreateOpticalFlowSessionNV)(VkDevice device, const VkOpticalFlowSessionCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkOpticalFlowSessionNV* pSession);
typedef void (VKAPI_PTR *PFN_vkDestroyOpticalFlowSessionNV)(VkDevice device, VkOpticalFlowSessionNV session, const VkAllocationCallbacks* pAllocator);
typedef VkResult (VKAPI_PTR *PFN_vkBindOpticalFlowSessionImageNV)(VkDevice device, VkOpticalFlowSessionNV session, VkOpticalFlowSessionBindingPointNV bindingPoint, VkImageView view, VkImageLayout layout);
typedef void (VKAPI_PTR *PFN_vkCmdOpticalFlowExecuteNV)(VkCommandBuffer commandBuffer, VkOpticalFlowSessionNV session, const VkOpticalFlowExecuteInfoNV* pExecuteInfo);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceOpticalFlowImageFormatsNV(
 VkPhysicalDevice physicalDevice,
 const VkOpticalFlowImageFormatInfoNV* pOpticalFlowImageFormatInfo,
 uint32_t* pFormatCount,
 VkOpticalFlowImageFormatPropertiesNV* pImageFormatProperties);

VKAPI_ATTR VkResult VKAPI_CALL vkCreateOpticalFlowSessionNV(
 VkDevice device,
 const VkOpticalFlowSessionCreateInfoNV* pCreateInfo,
 const VkAllocationCallbacks* pAllocator,
 VkOpticalFlowSessionNV* pSession);

VKAPI_ATTR void VKAPI_CALL vkDestroyOpticalFlowSessionNV(
 VkDevice device,
 VkOpticalFlowSessionNV session,
 const VkAllocationCallbacks* pAllocator);

VKAPI_ATTR VkResult VKAPI_CALL vkBindOpticalFlowSessionImageNV(
 VkDevice device,
 VkOpticalFlowSessionNV session,
 VkOpticalFlowSessionBindingPointNV bindingPoint,
 VkImageView view,
 VkImageLayout layout);

VKAPI_ATTR void VKAPI_CALL vkCmdOpticalFlowExecuteNV(
 VkCommandBuffer commandBuffer,
 VkOpticalFlowSessionNV session,
 const VkOpticalFlowExecuteInfoNV* pExecuteInfo);
#endif

// VK_EXT_legacy_dithering is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_legacy_dithering 1
#define VK_EXT_LEGACY_DITHERING_SPEC_VERSION 1
#define VK_EXT_LEGACY_DITHERING_EXTENSION_NAME "VK_EXT_legacy_dithering"
typedef struct VkPhysicalDeviceLegacyDitheringFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 legacyDithering;
} VkPhysicalDeviceLegacyDitheringFeaturesEXT;

// VK_EXT_pipeline_protected_access is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_pipeline_protected_access 1
#define VK_EXT_PIPELINE_PROTECTED_ACCESS_SPEC_VERSION 1
#define VK_EXT_PIPELINE_PROTECTED_ACCESS_EXTENSION_NAME "VK_EXT_pipeline_protected_access"
typedef struct VkPhysicalDevicePipelineProtectedAccessFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 pipelineProtectedAccess;
} VkPhysicalDevicePipelineProtectedAccessFeaturesEXT;

// VK_EXT_shader_object is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_shader_object 1
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkShaderEXT)
#define VK_EXT_SHADER_OBJECT_SPEC_VERSION 1
#define VK_EXT_SHADER_OBJECT_EXTENSION_NAME "VK_EXT_shader_object"

typedef enum VkShaderCodeTypeEXT {
 VK_SHADER_CODE_TYPE_BINARY_EXT = 0,
 VK_SHADER_CODE_TYPE_SPIRV_EXT = 1,
 VK_SHADER_CODE_TYPE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkShaderCodeTypeEXT;

typedef enum VkShaderCreateFlagBitsEXT {
 VK_SHADER_CREATE_LINK_STAGE_BIT_EXT = 0x00000001,
 VK_SHADER_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT_EXT = 0x00000002,
 VK_SHADER_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT = 0x00000004,
 VK_SHADER_CREATE_NO_TASK_SHADER_BIT_EXT = 0x00000008,
 VK_SHADER_CREATE_DISPATCH_BASE_BIT_EXT = 0x00000010,
 VK_SHADER_CREATE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_EXT = 0x00000020,
 VK_SHADER_CREATE_FRAGMENT_DENSITY_MAP_ATTACHMENT_BIT_EXT = 0x00000040,
 VK_SHADER_CREATE_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkShaderCreateFlagBitsEXT;
typedef VkFlags VkShaderCreateFlagsEXT;
typedef struct VkPhysicalDeviceShaderObjectFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 shaderObject;
} VkPhysicalDeviceShaderObjectFeaturesEXT;

typedef struct VkPhysicalDeviceShaderObjectPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 uint8_t shaderBinaryUUID[VK_UUID_SIZE];
 uint32_t shaderBinaryVersion;
} VkPhysicalDeviceShaderObjectPropertiesEXT;

typedef struct VkShaderCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 VkShaderCreateFlagsEXT flags;
 VkShaderStageFlagBits stage;
 VkShaderStageFlags nextStage;
 VkShaderCodeTypeEXT codeType;
 size_t codeSize;
 const void* pCode;
 const char* pName;
 uint32_t setLayoutCount;
 const VkDescriptorSetLayout* pSetLayouts;
 uint32_t pushConstantRangeCount;
 const VkPushConstantRange* pPushConstantRanges;
 const VkSpecializationInfo* pSpecializationInfo;
} VkShaderCreateInfoEXT;

typedef VkPipelineShaderStageRequiredSubgroupSizeCreateInfo VkShaderRequiredSubgroupSizeCreateInfoEXT;

typedef VkResult (VKAPI_PTR *PFN_vkCreateShadersEXT)(VkDevice device, uint32_t createInfoCount, const VkShaderCreateInfoEXT* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkShaderEXT* pShaders);
typedef void (VKAPI_PTR *PFN_vkDestroyShaderEXT)(VkDevice device, VkShaderEXT shader, const VkAllocationCallbacks* pAllocator);
typedef VkResult (VKAPI_PTR *PFN_vkGetShaderBinaryDataEXT)(VkDevice device, VkShaderEXT shader, size_t* pDataSize, void* pData);
typedef void (VKAPI_PTR *PFN_vkCmdBindShadersEXT)(VkCommandBuffer commandBuffer, uint32_t stageCount, const VkShaderStageFlagBits* pStages, const VkShaderEXT* pShaders);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateShadersEXT(
 VkDevice device,
 uint32_t createInfoCount,
 const VkShaderCreateInfoEXT* pCreateInfos,
 const VkAllocationCallbacks* pAllocator,
 VkShaderEXT* pShaders);

VKAPI_ATTR void VKAPI_CALL vkDestroyShaderEXT(
 VkDevice device,
 VkShaderEXT shader,
 const VkAllocationCallbacks* pAllocator);

VKAPI_ATTR VkResult VKAPI_CALL vkGetShaderBinaryDataEXT(
 VkDevice device,
 VkShaderEXT shader,
 size_t* pDataSize,
 void* pData);

VKAPI_ATTR void VKAPI_CALL vkCmdBindShadersEXT(
 VkCommandBuffer commandBuffer,
 uint32_t stageCount,
 const VkShaderStageFlagBits* pStages,
 const VkShaderEXT* pShaders);
#endif

// VK_QCOM_tile_properties is a preprocessor guard. Do not pass it to API calls.
#define VK_QCOM_tile_properties 1
#define VK_QCOM_TILE_PROPERTIES_SPEC_VERSION 1
#define VK_QCOM_TILE_PROPERTIES_EXTENSION_NAME "VK_QCOM_tile_properties"
typedef struct VkPhysicalDeviceTilePropertiesFeaturesQCOM {
 VkStructureType sType;
 void* pNext;
 VkBool32 tileProperties;
} VkPhysicalDeviceTilePropertiesFeaturesQCOM;

typedef struct VkTilePropertiesQCOM {
 VkStructureType sType;
 void* pNext;
 VkExtent3D tileSize;
 VkExtent2D apronSize;
 VkOffset2D origin;
} VkTilePropertiesQCOM;

typedef VkResult (VKAPI_PTR *PFN_vkGetFramebufferTilePropertiesQCOM)(VkDevice device, VkFramebuffer framebuffer, uint32_t* pPropertiesCount, VkTilePropertiesQCOM* pProperties);
typedef VkResult (VKAPI_PTR *PFN_vkGetDynamicRenderingTilePropertiesQCOM)(VkDevice device, const VkRenderingInfo* pRenderingInfo, VkTilePropertiesQCOM* pProperties);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetFramebufferTilePropertiesQCOM(
 VkDevice device,
 VkFramebuffer framebuffer,
 uint32_t* pPropertiesCount,
 VkTilePropertiesQCOM* pProperties);

VKAPI_ATTR VkResult VKAPI_CALL vkGetDynamicRenderingTilePropertiesQCOM(
 VkDevice device,
 const VkRenderingInfo* pRenderingInfo,
 VkTilePropertiesQCOM* pProperties);
#endif

// VK_SEC_amigo_profiling is a preprocessor guard. Do not pass it to API calls.
#define VK_SEC_amigo_profiling 1
#define VK_SEC_AMIGO_PROFILING_SPEC_VERSION 1
#define VK_SEC_AMIGO_PROFILING_EXTENSION_NAME "VK_SEC_amigo_profiling"
typedef struct VkPhysicalDeviceAmigoProfilingFeaturesSEC {
 VkStructureType sType;
 void* pNext;
 VkBool32 amigoProfiling;
} VkPhysicalDeviceAmigoProfilingFeaturesSEC;

typedef struct VkAmigoProfilingSubmitInfoSEC {
 VkStructureType sType;
 const void* pNext;
 uint64_t firstDrawTimestamp;
 uint64_t swapBufferTimestamp;
} VkAmigoProfilingSubmitInfoSEC;

// VK_QCOM_multiview_per_view_viewports is a preprocessor guard. Do not pass it to API calls.
#define VK_QCOM_multiview_per_view_viewports 1
#define VK_QCOM_MULTIVIEW_PER_VIEW_VIEWPORTS_SPEC_VERSION 1
#define VK_QCOM_MULTIVIEW_PER_VIEW_VIEWPORTS_EXTENSION_NAME "VK_QCOM_multiview_per_view_viewports"
typedef struct VkPhysicalDeviceMultiviewPerViewViewportsFeaturesQCOM {
 VkStructureType sType;
 void* pNext;
 VkBool32 multiviewPerViewViewports;
} VkPhysicalDeviceMultiviewPerViewViewportsFeaturesQCOM;

// VK_NV_ray_tracing_invocation_reorder is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_ray_tracing_invocation_reorder 1
#define VK_NV_RAY_TRACING_INVOCATION_REORDER_SPEC_VERSION 1
#define VK_NV_RAY_TRACING_INVOCATION_REORDER_EXTENSION_NAME "VK_NV_ray_tracing_invocation_reorder"

typedef enum VkRayTracingInvocationReorderModeNV {
 VK_RAY_TRACING_INVOCATION_REORDER_MODE_NONE_NV = 0,
 VK_RAY_TRACING_INVOCATION_REORDER_MODE_REORDER_NV = 1,
 VK_RAY_TRACING_INVOCATION_REORDER_MODE_MAX_ENUM_NV = 0x7FFFFFFF
} VkRayTracingInvocationReorderModeNV;
typedef struct VkPhysicalDeviceRayTracingInvocationReorderPropertiesNV {
 VkStructureType sType;
 void* pNext;
 VkRayTracingInvocationReorderModeNV rayTracingInvocationReorderReorderingHint;
} VkPhysicalDeviceRayTracingInvocationReorderPropertiesNV;

typedef struct VkPhysicalDeviceRayTracingInvocationReorderFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 rayTracingInvocationReorder;
} VkPhysicalDeviceRayTracingInvocationReorderFeaturesNV;

// VK_NV_extended_sparse_address_space is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_extended_sparse_address_space 1
#define VK_NV_EXTENDED_SPARSE_ADDRESS_SPACE_SPEC_VERSION 1
#define VK_NV_EXTENDED_SPARSE_ADDRESS_SPACE_EXTENSION_NAME "VK_NV_extended_sparse_address_space"
typedef struct VkPhysicalDeviceExtendedSparseAddressSpaceFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 extendedSparseAddressSpace;
} VkPhysicalDeviceExtendedSparseAddressSpaceFeaturesNV;

typedef struct VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV {
 VkStructureType sType;
 void* pNext;
 VkDeviceSize extendedSparseAddressSpaceSize;
 VkImageUsageFlags extendedSparseImageUsageFlags;
 VkBufferUsageFlags extendedSparseBufferUsageFlags;
} VkPhysicalDeviceExtendedSparseAddressSpacePropertiesNV;

// VK_EXT_mutable_descriptor_type is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_mutable_descriptor_type 1
#define VK_EXT_MUTABLE_DESCRIPTOR_TYPE_SPEC_VERSION 1
#define VK_EXT_MUTABLE_DESCRIPTOR_TYPE_EXTENSION_NAME "VK_EXT_mutable_descriptor_type"

// VK_EXT_layer_settings is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_layer_settings 1
#define VK_EXT_LAYER_SETTINGS_SPEC_VERSION 2
#define VK_EXT_LAYER_SETTINGS_EXTENSION_NAME "VK_EXT_layer_settings"

typedef enum VkLayerSettingTypeEXT {
 VK_LAYER_SETTING_TYPE_BOOL32_EXT = 0,
 VK_LAYER_SETTING_TYPE_INT32_EXT = 1,
 VK_LAYER_SETTING_TYPE_INT64_EXT = 2,
 VK_LAYER_SETTING_TYPE_UINT32_EXT = 3,
 VK_LAYER_SETTING_TYPE_UINT64_EXT = 4,
 VK_LAYER_SETTING_TYPE_FLOAT32_EXT = 5,
 VK_LAYER_SETTING_TYPE_FLOAT64_EXT = 6,
 VK_LAYER_SETTING_TYPE_STRING_EXT = 7,
 VK_LAYER_SETTING_TYPE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkLayerSettingTypeEXT;
typedef struct VkLayerSettingEXT {
 const char* pLayerName;
 const char* pSettingName;
 VkLayerSettingTypeEXT type;
 uint32_t valueCount;
 const void* pValues;
} VkLayerSettingEXT;

typedef struct VkLayerSettingsCreateInfoEXT {
 VkStructureType sType;
 const void* pNext;
 uint32_t settingCount;
 const VkLayerSettingEXT* pSettings;
} VkLayerSettingsCreateInfoEXT;

// VK_ARM_shader_core_builtins is a preprocessor guard. Do not pass it to API calls.
#define VK_ARM_shader_core_builtins 1
#define VK_ARM_SHADER_CORE_BUILTINS_SPEC_VERSION 2
#define VK_ARM_SHADER_CORE_BUILTINS_EXTENSION_NAME "VK_ARM_shader_core_builtins"
typedef struct VkPhysicalDeviceShaderCoreBuiltinsFeaturesARM {
 VkStructureType sType;
 void* pNext;
 VkBool32 shaderCoreBuiltins;
} VkPhysicalDeviceShaderCoreBuiltinsFeaturesARM;

typedef struct VkPhysicalDeviceShaderCoreBuiltinsPropertiesARM {
 VkStructureType sType;
 void* pNext;
 uint64_t shaderCoreMask;
 uint32_t shaderCoreCount;
 uint32_t shaderWarpsPerCore;
} VkPhysicalDeviceShaderCoreBuiltinsPropertiesARM;

// VK_EXT_pipeline_library_group_handles is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_pipeline_library_group_handles 1
#define VK_EXT_PIPELINE_LIBRARY_GROUP_HANDLES_SPEC_VERSION 1
#define VK_EXT_PIPELINE_LIBRARY_GROUP_HANDLES_EXTENSION_NAME "VK_EXT_pipeline_library_group_handles"
typedef struct VkPhysicalDevicePipelineLibraryGroupHandlesFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 pipelineLibraryGroupHandles;
} VkPhysicalDevicePipelineLibraryGroupHandlesFeaturesEXT;

// VK_EXT_dynamic_rendering_unused_attachments is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_dynamic_rendering_unused_attachments 1
#define VK_EXT_DYNAMIC_RENDERING_UNUSED_ATTACHMENTS_SPEC_VERSION 1
#define VK_EXT_DYNAMIC_RENDERING_UNUSED_ATTACHMENTS_EXTENSION_NAME "VK_EXT_dynamic_rendering_unused_attachments"
typedef struct VkPhysicalDeviceDynamicRenderingUnusedAttachmentsFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 dynamicRenderingUnusedAttachments;
} VkPhysicalDeviceDynamicRenderingUnusedAttachmentsFeaturesEXT;

// VK_NV_low_latency2 is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_low_latency2 1
#define VK_NV_LOW_LATENCY_2_SPEC_VERSION 2
#define VK_NV_LOW_LATENCY_2_EXTENSION_NAME "VK_NV_low_latency2"

typedef enum VkLatencyMarkerNV {
 VK_LATENCY_MARKER_SIMULATION_START_NV = 0,
 VK_LATENCY_MARKER_SIMULATION_END_NV = 1,
 VK_LATENCY_MARKER_RENDERSUBMIT_START_NV = 2,
 VK_LATENCY_MARKER_RENDERSUBMIT_END_NV = 3,
 VK_LATENCY_MARKER_PRESENT_START_NV = 4,
 VK_LATENCY_MARKER_PRESENT_END_NV = 5,
 VK_LATENCY_MARKER_INPUT_SAMPLE_NV = 6,
 VK_LATENCY_MARKER_TRIGGER_FLASH_NV = 7,
 VK_LATENCY_MARKER_OUT_OF_BAND_RENDERSUBMIT_START_NV = 8,
 VK_LATENCY_MARKER_OUT_OF_BAND_RENDERSUBMIT_END_NV = 9,
 VK_LATENCY_MARKER_OUT_OF_BAND_PRESENT_START_NV = 10,
 VK_LATENCY_MARKER_OUT_OF_BAND_PRESENT_END_NV = 11,
 VK_LATENCY_MARKER_MAX_ENUM_NV = 0x7FFFFFFF
} VkLatencyMarkerNV;

typedef enum VkOutOfBandQueueTypeNV {
 VK_OUT_OF_BAND_QUEUE_TYPE_RENDER_NV = 0,
 VK_OUT_OF_BAND_QUEUE_TYPE_PRESENT_NV = 1,
 VK_OUT_OF_BAND_QUEUE_TYPE_MAX_ENUM_NV = 0x7FFFFFFF
} VkOutOfBandQueueTypeNV;
typedef struct VkLatencySleepModeInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkBool32 lowLatencyMode;
 VkBool32 lowLatencyBoost;
 uint32_t minimumIntervalUs;
} VkLatencySleepModeInfoNV;

typedef struct VkLatencySleepInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkSemaphore signalSemaphore;
 uint64_t value;
} VkLatencySleepInfoNV;

typedef struct VkSetLatencyMarkerInfoNV {
 VkStructureType sType;
 const void* pNext;
 uint64_t presentID;
 VkLatencyMarkerNV marker;
} VkSetLatencyMarkerInfoNV;

typedef struct VkLatencyTimingsFrameReportNV {
 VkStructureType sType;
 const void* pNext;
 uint64_t presentID;
 uint64_t inputSampleTimeUs;
 uint64_t simStartTimeUs;
 uint64_t simEndTimeUs;
 uint64_t renderSubmitStartTimeUs;
 uint64_t renderSubmitEndTimeUs;
 uint64_t presentStartTimeUs;
 uint64_t presentEndTimeUs;
 uint64_t driverStartTimeUs;
 uint64_t driverEndTimeUs;
 uint64_t osRenderQueueStartTimeUs;
 uint64_t osRenderQueueEndTimeUs;
 uint64_t gpuRenderStartTimeUs;
 uint64_t gpuRenderEndTimeUs;
} VkLatencyTimingsFrameReportNV;

typedef struct VkGetLatencyMarkerInfoNV {
 VkStructureType sType;
 const void* pNext;
 uint32_t timingCount;
 VkLatencyTimingsFrameReportNV* pTimings;
} VkGetLatencyMarkerInfoNV;

typedef struct VkLatencySubmissionPresentIdNV {
 VkStructureType sType;
 const void* pNext;
 uint64_t presentID;
} VkLatencySubmissionPresentIdNV;

typedef struct VkSwapchainLatencyCreateInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkBool32 latencyModeEnable;
} VkSwapchainLatencyCreateInfoNV;

typedef struct VkOutOfBandQueueTypeInfoNV {
 VkStructureType sType;
 const void* pNext;
 VkOutOfBandQueueTypeNV queueType;
} VkOutOfBandQueueTypeInfoNV;

typedef struct VkLatencySurfaceCapabilitiesNV {
 VkStructureType sType;
 const void* pNext;
 uint32_t presentModeCount;
 VkPresentModeKHR* pPresentModes;
} VkLatencySurfaceCapabilitiesNV;

typedef VkResult (VKAPI_PTR *PFN_vkSetLatencySleepModeNV)(VkDevice device, VkSwapchainKHR swapchain, const VkLatencySleepModeInfoNV* pSleepModeInfo);
typedef VkResult (VKAPI_PTR *PFN_vkLatencySleepNV)(VkDevice device, VkSwapchainKHR swapchain, const VkLatencySleepInfoNV* pSleepInfo);
typedef void (VKAPI_PTR *PFN_vkSetLatencyMarkerNV)(VkDevice device, VkSwapchainKHR swapchain, const VkSetLatencyMarkerInfoNV* pLatencyMarkerInfo);
typedef void (VKAPI_PTR *PFN_vkGetLatencyTimingsNV)(VkDevice device, VkSwapchainKHR swapchain, VkGetLatencyMarkerInfoNV* pLatencyMarkerInfo);
typedef void (VKAPI_PTR *PFN_vkQueueNotifyOutOfBandNV)(VkQueue queue, const VkOutOfBandQueueTypeInfoNV* pQueueTypeInfo);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkSetLatencySleepModeNV(
 VkDevice device,
 VkSwapchainKHR swapchain,
 const VkLatencySleepModeInfoNV* pSleepModeInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkLatencySleepNV(
 VkDevice device,
 VkSwapchainKHR swapchain,
 const VkLatencySleepInfoNV* pSleepInfo);

VKAPI_ATTR void VKAPI_CALL vkSetLatencyMarkerNV(
 VkDevice device,
 VkSwapchainKHR swapchain,
 const VkSetLatencyMarkerInfoNV* pLatencyMarkerInfo);

VKAPI_ATTR void VKAPI_CALL vkGetLatencyTimingsNV(
 VkDevice device,
 VkSwapchainKHR swapchain,
 VkGetLatencyMarkerInfoNV* pLatencyMarkerInfo);

VKAPI_ATTR void VKAPI_CALL vkQueueNotifyOutOfBandNV(
 VkQueue queue,
 const VkOutOfBandQueueTypeInfoNV* pQueueTypeInfo);
#endif

// VK_QCOM_multiview_per_view_render_areas is a preprocessor guard. Do not pass it to API calls.
#define VK_QCOM_multiview_per_view_render_areas 1
#define VK_QCOM_MULTIVIEW_PER_VIEW_RENDER_AREAS_SPEC_VERSION 1
#define VK_QCOM_MULTIVIEW_PER_VIEW_RENDER_AREAS_EXTENSION_NAME "VK_QCOM_multiview_per_view_render_areas"
typedef struct VkPhysicalDeviceMultiviewPerViewRenderAreasFeaturesQCOM {
 VkStructureType sType;
 void* pNext;
 VkBool32 multiviewPerViewRenderAreas;
} VkPhysicalDeviceMultiviewPerViewRenderAreasFeaturesQCOM;

typedef struct VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM {
 VkStructureType sType;
 const void* pNext;
 uint32_t perViewRenderAreaCount;
 const VkRect2D* pPerViewRenderAreas;
} VkMultiviewPerViewRenderAreasRenderPassBeginInfoQCOM;

// VK_NV_per_stage_descriptor_set is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_per_stage_descriptor_set 1
#define VK_NV_PER_STAGE_DESCRIPTOR_SET_SPEC_VERSION 1
#define VK_NV_PER_STAGE_DESCRIPTOR_SET_EXTENSION_NAME "VK_NV_per_stage_descriptor_set"
typedef struct VkPhysicalDevicePerStageDescriptorSetFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 perStageDescriptorSet;
 VkBool32 dynamicPipelineLayout;
} VkPhysicalDevicePerStageDescriptorSetFeaturesNV;

// VK_QCOM_image_processing2 is a preprocessor guard. Do not pass it to API calls.
#define VK_QCOM_image_processing2 1
#define VK_QCOM_IMAGE_PROCESSING_2_SPEC_VERSION 1
#define VK_QCOM_IMAGE_PROCESSING_2_EXTENSION_NAME "VK_QCOM_image_processing2"

typedef enum VkBlockMatchWindowCompareModeQCOM {
 VK_BLOCK_MATCH_WINDOW_COMPARE_MODE_MIN_QCOM = 0,
 VK_BLOCK_MATCH_WINDOW_COMPARE_MODE_MAX_QCOM = 1,
 VK_BLOCK_MATCH_WINDOW_COMPARE_MODE_MAX_ENUM_QCOM = 0x7FFFFFFF
} VkBlockMatchWindowCompareModeQCOM;
typedef struct VkPhysicalDeviceImageProcessing2FeaturesQCOM {
 VkStructureType sType;
 void* pNext;
 VkBool32 textureBlockMatch2;
} VkPhysicalDeviceImageProcessing2FeaturesQCOM;

typedef struct VkPhysicalDeviceImageProcessing2PropertiesQCOM {
 VkStructureType sType;
 void* pNext;
 VkExtent2D maxBlockMatchWindow;
} VkPhysicalDeviceImageProcessing2PropertiesQCOM;

typedef struct VkSamplerBlockMatchWindowCreateInfoQCOM {
 VkStructureType sType;
 const void* pNext;
 VkExtent2D windowExtent;
 VkBlockMatchWindowCompareModeQCOM windowCompareMode;
} VkSamplerBlockMatchWindowCreateInfoQCOM;

// VK_QCOM_filter_cubic_weights is a preprocessor guard. Do not pass it to API calls.
#define VK_QCOM_filter_cubic_weights 1
#define VK_QCOM_FILTER_CUBIC_WEIGHTS_SPEC_VERSION 1
#define VK_QCOM_FILTER_CUBIC_WEIGHTS_EXTENSION_NAME "VK_QCOM_filter_cubic_weights"

typedef enum VkCubicFilterWeightsQCOM {
 VK_CUBIC_FILTER_WEIGHTS_CATMULL_ROM_QCOM = 0,
 VK_CUBIC_FILTER_WEIGHTS_ZERO_TANGENT_CARDINAL_QCOM = 1,
 VK_CUBIC_FILTER_WEIGHTS_B_SPLINE_QCOM = 2,
 VK_CUBIC_FILTER_WEIGHTS_MITCHELL_NETRAVALI_QCOM = 3,
 VK_CUBIC_FILTER_WEIGHTS_MAX_ENUM_QCOM = 0x7FFFFFFF
} VkCubicFilterWeightsQCOM;
typedef struct VkPhysicalDeviceCubicWeightsFeaturesQCOM {
 VkStructureType sType;
 void* pNext;
 VkBool32 selectableCubicWeights;
} VkPhysicalDeviceCubicWeightsFeaturesQCOM;

typedef struct VkSamplerCubicWeightsCreateInfoQCOM {
 VkStructureType sType;
 const void* pNext;
 VkCubicFilterWeightsQCOM cubicWeights;
} VkSamplerCubicWeightsCreateInfoQCOM;

typedef struct VkBlitImageCubicWeightsInfoQCOM {
 VkStructureType sType;
 const void* pNext;
 VkCubicFilterWeightsQCOM cubicWeights;
} VkBlitImageCubicWeightsInfoQCOM;

// VK_QCOM_ycbcr_degamma is a preprocessor guard. Do not pass it to API calls.
#define VK_QCOM_ycbcr_degamma 1
#define VK_QCOM_YCBCR_DEGAMMA_SPEC_VERSION 1
#define VK_QCOM_YCBCR_DEGAMMA_EXTENSION_NAME "VK_QCOM_ycbcr_degamma"
typedef struct VkPhysicalDeviceYcbcrDegammaFeaturesQCOM {
 VkStructureType sType;
 void* pNext;
 VkBool32 ycbcrDegamma;
} VkPhysicalDeviceYcbcrDegammaFeaturesQCOM;

typedef struct VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM {
 VkStructureType sType;
 void* pNext;
 VkBool32 enableYDegamma;
 VkBool32 enableCbCrDegamma;
} VkSamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM;

// VK_QCOM_filter_cubic_clamp is a preprocessor guard. Do not pass it to API calls.
#define VK_QCOM_filter_cubic_clamp 1
#define VK_QCOM_FILTER_CUBIC_CLAMP_SPEC_VERSION 1
#define VK_QCOM_FILTER_CUBIC_CLAMP_EXTENSION_NAME "VK_QCOM_filter_cubic_clamp"
typedef struct VkPhysicalDeviceCubicClampFeaturesQCOM {
 VkStructureType sType;
 void* pNext;
 VkBool32 cubicRangeClamp;
} VkPhysicalDeviceCubicClampFeaturesQCOM;

// VK_EXT_attachment_feedback_loop_dynamic_state is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_attachment_feedback_loop_dynamic_state 1
#define VK_EXT_ATTACHMENT_FEEDBACK_LOOP_DYNAMIC_STATE_SPEC_VERSION 1
#define VK_EXT_ATTACHMENT_FEEDBACK_LOOP_DYNAMIC_STATE_EXTENSION_NAME "VK_EXT_attachment_feedback_loop_dynamic_state"
typedef struct VkPhysicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 attachmentFeedbackLoopDynamicState;
} VkPhysicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT;

typedef void (VKAPI_PTR *PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT)(VkCommandBuffer commandBuffer, VkImageAspectFlags aspectMask);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdSetAttachmentFeedbackLoopEnableEXT(
 VkCommandBuffer commandBuffer,
 VkImageAspectFlags aspectMask);
#endif

// VK_NV_descriptor_pool_overallocation is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_descriptor_pool_overallocation 1
#define VK_NV_DESCRIPTOR_POOL_OVERALLOCATION_SPEC_VERSION 1
#define VK_NV_DESCRIPTOR_POOL_OVERALLOCATION_EXTENSION_NAME "VK_NV_descriptor_pool_overallocation"
typedef struct VkPhysicalDeviceDescriptorPoolOverallocationFeaturesNV {
 VkStructureType sType;
 void* pNext;
 VkBool32 descriptorPoolOverallocation;
} VkPhysicalDeviceDescriptorPoolOverallocationFeaturesNV;

// VK_KHR_acceleration_structure is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_acceleration_structure 1
#define VK_KHR_ACCELERATION_STRUCTURE_SPEC_VERSION 13
#define VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME "VK_KHR_acceleration_structure"

typedef enum VkBuildAccelerationStructureModeKHR {
 VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR = 0,
 VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR = 1,
 VK_BUILD_ACCELERATION_STRUCTURE_MODE_MAX_ENUM_KHR = 0x7FFFFFFF
} VkBuildAccelerationStructureModeKHR;

typedef enum VkAccelerationStructureCreateFlagBitsKHR {
 VK_ACCELERATION_STRUCTURE_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT_KHR = 0x00000001,
 VK_ACCELERATION_STRUCTURE_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT = 0x00000008,
 VK_ACCELERATION_STRUCTURE_CREATE_MOTION_BIT_NV = 0x00000004,
 VK_ACCELERATION_STRUCTURE_CREATE_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkAccelerationStructureCreateFlagBitsKHR;
typedef VkFlags VkAccelerationStructureCreateFlagsKHR;
typedef struct VkAccelerationStructureBuildRangeInfoKHR {
 uint32_t primitiveCount;
 uint32_t primitiveOffset;
 uint32_t firstVertex;
 uint32_t transformOffset;
} VkAccelerationStructureBuildRangeInfoKHR;

typedef struct VkAccelerationStructureGeometryTrianglesDataKHR {
 VkStructureType sType;
 const void* pNext;
 VkFormat vertexFormat;
 VkDeviceOrHostAddressConstKHR vertexData;
 VkDeviceSize vertexStride;
 uint32_t maxVertex;
 VkIndexType indexType;
 VkDeviceOrHostAddressConstKHR indexData;
 VkDeviceOrHostAddressConstKHR transformData;
} VkAccelerationStructureGeometryTrianglesDataKHR;

typedef struct VkAccelerationStructureGeometryAabbsDataKHR {
 VkStructureType sType;
 const void* pNext;
 VkDeviceOrHostAddressConstKHR data;
 VkDeviceSize stride;
} VkAccelerationStructureGeometryAabbsDataKHR;

typedef struct VkAccelerationStructureGeometryInstancesDataKHR {
 VkStructureType sType;
 const void* pNext;
 VkBool32 arrayOfPointers;
 VkDeviceOrHostAddressConstKHR data;
} VkAccelerationStructureGeometryInstancesDataKHR;

typedef union VkAccelerationStructureGeometryDataKHR {
 VkAccelerationStructureGeometryTrianglesDataKHR triangles;
 VkAccelerationStructureGeometryAabbsDataKHR aabbs;
 VkAccelerationStructureGeometryInstancesDataKHR instances;
} VkAccelerationStructureGeometryDataKHR;

typedef struct VkAccelerationStructureGeometryKHR {
 VkStructureType sType;
 const void* pNext;
 VkGeometryTypeKHR geometryType;
 VkAccelerationStructureGeometryDataKHR geometry;
 VkGeometryFlagsKHR flags;
} VkAccelerationStructureGeometryKHR;

typedef struct VkAccelerationStructureBuildGeometryInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkAccelerationStructureTypeKHR type;
 VkBuildAccelerationStructureFlagsKHR flags;
 VkBuildAccelerationStructureModeKHR mode;
 VkAccelerationStructureKHR srcAccelerationStructure;
 VkAccelerationStructureKHR dstAccelerationStructure;
 uint32_t geometryCount;
 const VkAccelerationStructureGeometryKHR* pGeometries;
 const VkAccelerationStructureGeometryKHR* const* ppGeometries;
 VkDeviceOrHostAddressKHR scratchData;
} VkAccelerationStructureBuildGeometryInfoKHR;

typedef struct VkAccelerationStructureCreateInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkAccelerationStructureCreateFlagsKHR createFlags;
 VkBuffer buffer;
 VkDeviceSize offset;
 VkDeviceSize size;
 VkAccelerationStructureTypeKHR type;
 VkDeviceAddress deviceAddress;
} VkAccelerationStructureCreateInfoKHR;

typedef struct VkWriteDescriptorSetAccelerationStructureKHR {
 VkStructureType sType;
 const void* pNext;
 uint32_t accelerationStructureCount;
 const VkAccelerationStructureKHR* pAccelerationStructures;
} VkWriteDescriptorSetAccelerationStructureKHR;

typedef struct VkPhysicalDeviceAccelerationStructureFeaturesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 accelerationStructure;
 VkBool32 accelerationStructureCaptureReplay;
 VkBool32 accelerationStructureIndirectBuild;
 VkBool32 accelerationStructureHostCommands;
 VkBool32 descriptorBindingAccelerationStructureUpdateAfterBind;
} VkPhysicalDeviceAccelerationStructureFeaturesKHR;

typedef struct VkPhysicalDeviceAccelerationStructurePropertiesKHR {
 VkStructureType sType;
 void* pNext;
 uint64_t maxGeometryCount;
 uint64_t maxInstanceCount;
 uint64_t maxPrimitiveCount;
 uint32_t maxPerStageDescriptorAccelerationStructures;
 uint32_t maxPerStageDescriptorUpdateAfterBindAccelerationStructures;
 uint32_t maxDescriptorSetAccelerationStructures;
 uint32_t maxDescriptorSetUpdateAfterBindAccelerationStructures;
 uint32_t minAccelerationStructureScratchOffsetAlignment;
} VkPhysicalDeviceAccelerationStructurePropertiesKHR;

typedef struct VkAccelerationStructureDeviceAddressInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkAccelerationStructureKHR accelerationStructure;
} VkAccelerationStructureDeviceAddressInfoKHR;

typedef struct VkAccelerationStructureVersionInfoKHR {
 VkStructureType sType;
 const void* pNext;
 const uint8_t* pVersionData;
} VkAccelerationStructureVersionInfoKHR;

typedef struct VkCopyAccelerationStructureToMemoryInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkAccelerationStructureKHR src;
 VkDeviceOrHostAddressKHR dst;
 VkCopyAccelerationStructureModeKHR mode;
} VkCopyAccelerationStructureToMemoryInfoKHR;

typedef struct VkCopyMemoryToAccelerationStructureInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkDeviceOrHostAddressConstKHR src;
 VkAccelerationStructureKHR dst;
 VkCopyAccelerationStructureModeKHR mode;
} VkCopyMemoryToAccelerationStructureInfoKHR;

typedef struct VkCopyAccelerationStructureInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkAccelerationStructureKHR src;
 VkAccelerationStructureKHR dst;
 VkCopyAccelerationStructureModeKHR mode;
} VkCopyAccelerationStructureInfoKHR;

typedef struct VkAccelerationStructureBuildSizesInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkDeviceSize accelerationStructureSize;
 VkDeviceSize updateScratchSize;
 VkDeviceSize buildScratchSize;
} VkAccelerationStructureBuildSizesInfoKHR;

typedef VkResult (VKAPI_PTR *PFN_vkCreateAccelerationStructureKHR)(VkDevice device, const VkAccelerationStructureCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureKHR* pAccelerationStructure);
typedef void (VKAPI_PTR *PFN_vkDestroyAccelerationStructureKHR)(VkDevice device, VkAccelerationStructureKHR accelerationStructure, const VkAllocationCallbacks* pAllocator);
typedef void (VKAPI_PTR *PFN_vkCmdBuildAccelerationStructuresKHR)(VkCommandBuffer commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos);
typedef void (VKAPI_PTR *PFN_vkCmdBuildAccelerationStructuresIndirectKHR)(VkCommandBuffer commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkDeviceAddress* pIndirectDeviceAddresses, const uint32_t* pIndirectStrides, const uint32_t* const* ppMaxPrimitiveCounts);
typedef VkResult (VKAPI_PTR *PFN_vkBuildAccelerationStructuresKHR)(VkDevice device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos);
typedef VkResult (VKAPI_PTR *PFN_vkCopyAccelerationStructureKHR)(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureInfoKHR* pInfo);
typedef VkResult (VKAPI_PTR *PFN_vkCopyAccelerationStructureToMemoryKHR)(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo);
typedef VkResult (VKAPI_PTR *PFN_vkCopyMemoryToAccelerationStructureKHR)(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo);
typedef VkResult (VKAPI_PTR *PFN_vkWriteAccelerationStructuresPropertiesKHR)(VkDevice device, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, size_t dataSize, void* pData, size_t stride);
typedef void (VKAPI_PTR *PFN_vkCmdCopyAccelerationStructureKHR)(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureInfoKHR* pInfo);
typedef void (VKAPI_PTR *PFN_vkCmdCopyAccelerationStructureToMemoryKHR)(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo);
typedef void (VKAPI_PTR *PFN_vkCmdCopyMemoryToAccelerationStructureKHR)(VkCommandBuffer commandBuffer, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo);
typedef VkDeviceAddress (VKAPI_PTR *PFN_vkGetAccelerationStructureDeviceAddressKHR)(VkDevice device, const VkAccelerationStructureDeviceAddressInfoKHR* pInfo);
typedef void (VKAPI_PTR *PFN_vkCmdWriteAccelerationStructuresPropertiesKHR)(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery);
typedef void (VKAPI_PTR *PFN_vkGetDeviceAccelerationStructureCompatibilityKHR)(VkDevice device, const VkAccelerationStructureVersionInfoKHR* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility);
typedef void (VKAPI_PTR *PFN_vkGetAccelerationStructureBuildSizesKHR)(VkDevice device, VkAccelerationStructureBuildTypeKHR buildType, const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo, const uint32_t* pMaxPrimitiveCounts, VkAccelerationStructureBuildSizesInfoKHR* pSizeInfo);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateAccelerationStructureKHR(
 VkDevice device,
 const VkAccelerationStructureCreateInfoKHR* pCreateInfo,
 const VkAllocationCallbacks* pAllocator,
 VkAccelerationStructureKHR* pAccelerationStructure);

VKAPI_ATTR void VKAPI_CALL vkDestroyAccelerationStructureKHR(
 VkDevice device,
 VkAccelerationStructureKHR accelerationStructure,
 const VkAllocationCallbacks* pAllocator);

VKAPI_ATTR void VKAPI_CALL vkCmdBuildAccelerationStructuresKHR(
 VkCommandBuffer commandBuffer,
 uint32_t infoCount,
 const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
 const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos);

VKAPI_ATTR void VKAPI_CALL vkCmdBuildAccelerationStructuresIndirectKHR(
 VkCommandBuffer commandBuffer,
 uint32_t infoCount,
 const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
 const VkDeviceAddress* pIndirectDeviceAddresses,
 const uint32_t* pIndirectStrides,
 const uint32_t* const* ppMaxPrimitiveCounts);

VKAPI_ATTR VkResult VKAPI_CALL vkBuildAccelerationStructuresKHR(
 VkDevice device,
 VkDeferredOperationKHR deferredOperation,
 uint32_t infoCount,
 const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
 const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos);

VKAPI_ATTR VkResult VKAPI_CALL vkCopyAccelerationStructureKHR(
 VkDevice device,
 VkDeferredOperationKHR deferredOperation,
 const VkCopyAccelerationStructureInfoKHR* pInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkCopyAccelerationStructureToMemoryKHR(
 VkDevice device,
 VkDeferredOperationKHR deferredOperation,
 const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkCopyMemoryToAccelerationStructureKHR(
 VkDevice device,
 VkDeferredOperationKHR deferredOperation,
 const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkWriteAccelerationStructuresPropertiesKHR(
 VkDevice device,
 uint32_t accelerationStructureCount,
 const VkAccelerationStructureKHR* pAccelerationStructures,
 VkQueryType queryType,
 size_t dataSize,
 void* pData,
 size_t stride);

VKAPI_ATTR void VKAPI_CALL vkCmdCopyAccelerationStructureKHR(
 VkCommandBuffer commandBuffer,
 const VkCopyAccelerationStructureInfoKHR* pInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdCopyAccelerationStructureToMemoryKHR(
 VkCommandBuffer commandBuffer,
 const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdCopyMemoryToAccelerationStructureKHR(
 VkCommandBuffer commandBuffer,
 const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo);

VKAPI_ATTR VkDeviceAddress VKAPI_CALL vkGetAccelerationStructureDeviceAddressKHR(
 VkDevice device,
 const VkAccelerationStructureDeviceAddressInfoKHR* pInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdWriteAccelerationStructuresPropertiesKHR(
 VkCommandBuffer commandBuffer,
 uint32_t accelerationStructureCount,
 const VkAccelerationStructureKHR* pAccelerationStructures,
 VkQueryType queryType,
 VkQueryPool queryPool,
 uint32_t firstQuery);

VKAPI_ATTR void VKAPI_CALL vkGetDeviceAccelerationStructureCompatibilityKHR(
 VkDevice device,
 const VkAccelerationStructureVersionInfoKHR* pVersionInfo,
 VkAccelerationStructureCompatibilityKHR* pCompatibility);

VKAPI_ATTR void VKAPI_CALL vkGetAccelerationStructureBuildSizesKHR(
 VkDevice device,
 VkAccelerationStructureBuildTypeKHR buildType,
 const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo,
 const uint32_t* pMaxPrimitiveCounts,
 VkAccelerationStructureBuildSizesInfoKHR* pSizeInfo);
#endif

// VK_KHR_ray_tracing_pipeline is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_ray_tracing_pipeline 1
#define VK_KHR_RAY_TRACING_PIPELINE_SPEC_VERSION 1
#define VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME "VK_KHR_ray_tracing_pipeline"

typedef enum VkShaderGroupShaderKHR {
 VK_SHADER_GROUP_SHADER_GENERAL_KHR = 0,
 VK_SHADER_GROUP_SHADER_CLOSEST_HIT_KHR = 1,
 VK_SHADER_GROUP_SHADER_ANY_HIT_KHR = 2,
 VK_SHADER_GROUP_SHADER_INTERSECTION_KHR = 3,
 VK_SHADER_GROUP_SHADER_MAX_ENUM_KHR = 0x7FFFFFFF
} VkShaderGroupShaderKHR;
typedef struct VkRayTracingShaderGroupCreateInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkRayTracingShaderGroupTypeKHR type;
 uint32_t generalShader;
 uint32_t closestHitShader;
 uint32_t anyHitShader;
 uint32_t intersectionShader;
 const void* pShaderGroupCaptureReplayHandle;
} VkRayTracingShaderGroupCreateInfoKHR;

typedef struct VkRayTracingPipelineInterfaceCreateInfoKHR {
 VkStructureType sType;
 const void* pNext;
 uint32_t maxPipelineRayPayloadSize;
 uint32_t maxPipelineRayHitAttributeSize;
} VkRayTracingPipelineInterfaceCreateInfoKHR;

typedef struct VkRayTracingPipelineCreateInfoKHR {
 VkStructureType sType;
 const void* pNext;
 VkPipelineCreateFlags flags;
 uint32_t stageCount;
 const VkPipelineShaderStageCreateInfo* pStages;
 uint32_t groupCount;
 const VkRayTracingShaderGroupCreateInfoKHR* pGroups;
 uint32_t maxPipelineRayRecursionDepth;
 const VkPipelineLibraryCreateInfoKHR* pLibraryInfo;
 const VkRayTracingPipelineInterfaceCreateInfoKHR* pLibraryInterface;
 const VkPipelineDynamicStateCreateInfo* pDynamicState;
 VkPipelineLayout layout;
 VkPipeline basePipelineHandle;
 int32_t basePipelineIndex;
} VkRayTracingPipelineCreateInfoKHR;

typedef struct VkPhysicalDeviceRayTracingPipelineFeaturesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 rayTracingPipeline;
 VkBool32 rayTracingPipelineShaderGroupHandleCaptureReplay;
 VkBool32 rayTracingPipelineShaderGroupHandleCaptureReplayMixed;
 VkBool32 rayTracingPipelineTraceRaysIndirect;
 VkBool32 rayTraversalPrimitiveCulling;
} VkPhysicalDeviceRayTracingPipelineFeaturesKHR;

typedef struct VkPhysicalDeviceRayTracingPipelinePropertiesKHR {
 VkStructureType sType;
 void* pNext;
 uint32_t shaderGroupHandleSize;
 uint32_t maxRayRecursionDepth;
 uint32_t maxShaderGroupStride;
 uint32_t shaderGroupBaseAlignment;
 uint32_t shaderGroupHandleCaptureReplaySize;
 uint32_t maxRayDispatchInvocationCount;
 uint32_t shaderGroupHandleAlignment;
 uint32_t maxRayHitAttributeSize;
} VkPhysicalDeviceRayTracingPipelinePropertiesKHR;

typedef struct VkStridedDeviceAddressRegionKHR {
 VkDeviceAddress deviceAddress;
 VkDeviceSize stride;
 VkDeviceSize size;
} VkStridedDeviceAddressRegionKHR;

typedef struct VkTraceRaysIndirectCommandKHR {
 uint32_t width;
 uint32_t height;
 uint32_t depth;
} VkTraceRaysIndirectCommandKHR;

typedef void (VKAPI_PTR *PFN_vkCmdTraceRaysKHR)(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth);
typedef VkResult (VKAPI_PTR *PFN_vkCreateRayTracingPipelinesKHR)(VkDevice device, VkDeferredOperationKHR deferredOperation, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines);
typedef VkResult (VKAPI_PTR *PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR)(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData);
typedef void (VKAPI_PTR *PFN_vkCmdTraceRaysIndirectKHR)(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, VkDeviceAddress indirectDeviceAddress);
typedef VkDeviceSize (VKAPI_PTR *PFN_vkGetRayTracingShaderGroupStackSizeKHR)(VkDevice device, VkPipeline pipeline, uint32_t group, VkShaderGroupShaderKHR groupShader);
typedef void (VKAPI_PTR *PFN_vkCmdSetRayTracingPipelineStackSizeKHR)(VkCommandBuffer commandBuffer, uint32_t pipelineStackSize);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdTraceRaysKHR(
 VkCommandBuffer commandBuffer,
 const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable,
 const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable,
 const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable,
 const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable,
 uint32_t width,
 uint32_t height,
 uint32_t depth);

VKAPI_ATTR VkResult VKAPI_CALL vkCreateRayTracingPipelinesKHR(
 VkDevice device,
 VkDeferredOperationKHR deferredOperation,
 VkPipelineCache pipelineCache,
 uint32_t createInfoCount,
 const VkRayTracingPipelineCreateInfoKHR* pCreateInfos,
 const VkAllocationCallbacks* pAllocator,
 VkPipeline* pPipelines);

VKAPI_ATTR VkResult VKAPI_CALL vkGetRayTracingCaptureReplayShaderGroupHandlesKHR(
 VkDevice device,
 VkPipeline pipeline,
 uint32_t firstGroup,
 uint32_t groupCount,
 size_t dataSize,
 void* pData);

VKAPI_ATTR void VKAPI_CALL vkCmdTraceRaysIndirectKHR(
 VkCommandBuffer commandBuffer,
 const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable,
 const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable,
 const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable,
 const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable,
 VkDeviceAddress indirectDeviceAddress);

VKAPI_ATTR VkDeviceSize VKAPI_CALL vkGetRayTracingShaderGroupStackSizeKHR(
 VkDevice device,
 VkPipeline pipeline,
 uint32_t group,
 VkShaderGroupShaderKHR groupShader);

VKAPI_ATTR void VKAPI_CALL vkCmdSetRayTracingPipelineStackSizeKHR(
 VkCommandBuffer commandBuffer,
 uint32_t pipelineStackSize);
#endif

// VK_KHR_ray_query is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_ray_query 1
#define VK_KHR_RAY_QUERY_SPEC_VERSION 1
#define VK_KHR_RAY_QUERY_EXTENSION_NAME "VK_KHR_ray_query"
typedef struct VkPhysicalDeviceRayQueryFeaturesKHR {
 VkStructureType sType;
 void* pNext;
 VkBool32 rayQuery;
} VkPhysicalDeviceRayQueryFeaturesKHR;

// VK_EXT_mesh_shader is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_mesh_shader 1
#define VK_EXT_MESH_SHADER_SPEC_VERSION 1
#define VK_EXT_MESH_SHADER_EXTENSION_NAME "VK_EXT_mesh_shader"
typedef struct VkPhysicalDeviceMeshShaderFeaturesEXT {
 VkStructureType sType;
 void* pNext;
 VkBool32 taskShader;
 VkBool32 meshShader;
 VkBool32 multiviewMeshShader;
 VkBool32 primitiveFragmentShadingRateMeshShader;
 VkBool32 meshShaderQueries;
} VkPhysicalDeviceMeshShaderFeaturesEXT;

typedef struct VkPhysicalDeviceMeshShaderPropertiesEXT {
 VkStructureType sType;
 void* pNext;
 uint32_t maxTaskWorkGroupTotalCount;
 uint32_t maxTaskWorkGroupCount[3];
 uint32_t maxTaskWorkGroupInvocations;
 uint32_t maxTaskWorkGroupSize[3];
 uint32_t maxTaskPayloadSize;
 uint32_t maxTaskSharedMemorySize;
 uint32_t maxTaskPayloadAndSharedMemorySize;
 uint32_t maxMeshWorkGroupTotalCount;
 uint32_t maxMeshWorkGroupCount[3];
 uint32_t maxMeshWorkGroupInvocations;
 uint32_t maxMeshWorkGroupSize[3];
 uint32_t maxMeshSharedMemorySize;
 uint32_t maxMeshPayloadAndSharedMemorySize;
 uint32_t maxMeshOutputMemorySize;
 uint32_t maxMeshPayloadAndOutputMemorySize;
 uint32_t maxMeshOutputComponents;
 uint32_t maxMeshOutputVertices;
 uint32_t maxMeshOutputPrimitives;
 uint32_t maxMeshOutputLayers;
 uint32_t maxMeshMultiviewViewCount;
 uint32_t meshOutputPerVertexGranularity;
 uint32_t meshOutputPerPrimitiveGranularity;
 uint32_t maxPreferredTaskWorkGroupInvocations;
 uint32_t maxPreferredMeshWorkGroupInvocations;
 VkBool32 prefersLocalInvocationVertexOutput;
 VkBool32 prefersLocalInvocationPrimitiveOutput;
 VkBool32 prefersCompactVertexOutput;
 VkBool32 prefersCompactPrimitiveOutput;
} VkPhysicalDeviceMeshShaderPropertiesEXT;

typedef struct VkDrawMeshTasksIndirectCommandEXT {
 uint32_t groupCountX;
 uint32_t groupCountY;
 uint32_t groupCountZ;
} VkDrawMeshTasksIndirectCommandEXT;

typedef void (VKAPI_PTR *PFN_vkCmdDrawMeshTasksEXT)(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ);
typedef void (VKAPI_PTR *PFN_vkCmdDrawMeshTasksIndirectEXT)(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride);
typedef void (VKAPI_PTR *PFN_vkCmdDrawMeshTasksIndirectCountEXT)(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkCmdDrawMeshTasksEXT(
 VkCommandBuffer commandBuffer,
 uint32_t groupCountX,
 uint32_t groupCountY,
 uint32_t groupCountZ);

VKAPI_ATTR void VKAPI_CALL vkCmdDrawMeshTasksIndirectEXT(
 VkCommandBuffer commandBuffer,
 VkBuffer buffer,
 VkDeviceSize offset,
 uint32_t drawCount,
 uint32_t stride);

VKAPI_ATTR void VKAPI_CALL vkCmdDrawMeshTasksIndirectCountEXT(
 VkCommandBuffer commandBuffer,
 VkBuffer buffer,
 VkDeviceSize offset,
 VkBuffer countBuffer,
 VkDeviceSize countBufferOffset,
 uint32_t maxDrawCount,
 uint32_t stride);
#endif

}
