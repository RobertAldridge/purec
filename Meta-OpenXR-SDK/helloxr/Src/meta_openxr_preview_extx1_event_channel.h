/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 * All rights reserved.
 *
 * Licensed under the Oculus SDK License Agreement (the "License");
 * you may not use the Oculus SDK except in compliance with the License,
 * which is provided at the time of installation or download, or which
 * otherwise accompanies this software in either electronic or hard copy form.
 *
 * You may obtain a copy of the License at
 * https://developer.oculus.com/licenses/oculussdk/
 *
 * Unless required by applicable law or agreed to in writing, the Oculus SDK
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**********************
This file is @generated from the OpenXR XML API registry.
Language    :   C99
Copyright   :   (c) Meta Platforms, Inc. and affiliates. Confidential and proprietary.
***********************/

extern "C" {

#ifndef XR_EXTX1_event_channel

// XR_EXTX1_event_channel is a preprocessor guard. Do not pass it to API calls.
#define XR_EXTX1_event_channel 1
XR_DEFINE_HANDLE(XrEventChannelEXTX1)
#define XR_EXTX1_event_channel_SPEC_VERSION 3
#define XR_EXTX1_EVENT_CHANNEL_EXTENSION_NAME "XR_EXTX1_event_channel"
static const XrStructureType XR_TYPE_EVENT_CHANNEL_CREATE_INFO_EXTX1 = (XrStructureType) 1000170001;
static const XrStructureType XR_TYPE_EVENT_CHANNEL_TARGET_EXTX1 = (XrStructureType) 1000170002;
static const XrStructureType XR_TYPE_SELECT_EVENT_CHANNEL_INFO_EXTX1 = (XrStructureType) 1000170003;
// XrEventChannelEXTX1
static const XrObjectType XR_OBJECT_TYPE_EVENT_CHANNEL_EXTX1 = (XrObjectType) 1000170000;

typedef enum XrSelectEventChannelFlagsEXTX1 {
    XR_SELECT_EVENT_CHANNEL_FLAGS_EXTX1_MAX_ENUM = 0x7FFFFFFF
} XrSelectEventChannelFlagsEXTX1;
typedef struct XrEventChannelCreateInfoEXTX1 {
    XrStructureType             type;
    const void* XR_MAY_ALIAS    next;
} XrEventChannelCreateInfoEXTX1;

typedef struct XrEventChannelTargetEXTX1 {
    XrStructureType             type;
    const void* XR_MAY_ALIAS    next;
    XrEventChannelEXTX1         channel;
} XrEventChannelTargetEXTX1;

typedef struct XrSelectEventChannelInfoEXTX1 {
    XrStructureType                   type;
    const void* XR_MAY_ALIAS          next;
    XrSelectEventChannelFlagsEXTX1    flags;
    XrDuration                        timeout;
    uint32_t                          eventChannelCount;
    const XrEventChannelEXTX1*        eventChannels;
} XrSelectEventChannelInfoEXTX1;

typedef XrResult (XRAPI_PTR *PFN_xrCreateEventChannelEXTX1)(XrInstance instance, const XrEventChannelCreateInfoEXTX1* createInfo, XrEventChannelEXTX1* channel);
typedef XrResult (XRAPI_PTR *PFN_xrDestroyEventChannelEXTX1)(XrEventChannelEXTX1 channel);
typedef XrResult (XRAPI_PTR *PFN_xrPollEventChannelEXTX1)(XrEventChannelEXTX1 channel, XrEventDataBuffer* eventData);
typedef XrResult (XRAPI_PTR *PFN_xrSelectEventChannelEXTX1)(XrInstance instance, XrSelectEventChannelInfoEXTX1* info, uint32_t* channelWithEvent);
typedef XrResult (XRAPI_PTR *PFN_xrSetDefaultEventChannelEXTX1)(XrInstance instance, XrEventChannelEXTX1 channel);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrCreateEventChannelEXTX1(
    XrInstance                                  instance,
    const XrEventChannelCreateInfoEXTX1*        createInfo,
    XrEventChannelEXTX1*                        channel);

XRAPI_ATTR XrResult XRAPI_CALL xrDestroyEventChannelEXTX1(
    XrEventChannelEXTX1                         channel);

XRAPI_ATTR XrResult XRAPI_CALL xrPollEventChannelEXTX1(
    XrEventChannelEXTX1                         channel,
    XrEventDataBuffer*                          eventData);

XRAPI_ATTR XrResult XRAPI_CALL xrSelectEventChannelEXTX1(
    XrInstance                                  instance,
    XrSelectEventChannelInfoEXTX1*              info,
    uint32_t*                                   channelWithEvent);

XRAPI_ATTR XrResult XRAPI_CALL xrSetDefaultEventChannelEXTX1(
    XrInstance                                  instance,
    XrEventChannelEXTX1                         channel);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */
#endif /* XR_EXTX1_event_channel */

}
