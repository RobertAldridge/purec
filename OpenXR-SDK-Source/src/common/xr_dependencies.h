// Copyright (c) 2018-2024, The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT
//
// This file includes headers with types which openxr.h depends on in order
// to compile when platforms, graphics apis, and the like are enabled.

#pragma once

#include <android/native_window.h>
#include <android/window.h>
#include <android/native_window_jni.h>

#ifdef XR_USE_GRAPHICS_API_D3D11
#include <d3d11.h>
#endif  // XR_USE_GRAPHICS_API_D3D11

#ifdef XR_USE_GRAPHICS_API_D3D12
#include <d3d12.h>
#endif  // XR_USE_GRAPHICS_API_D3D12

#ifdef XR_USE_PLATFORM_XLIB
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#endif  // XR_USE_PLATFORM_XLIB

#ifdef XR_USE_PLATFORM_XCB
#include <xcb/xcb.h>
#endif  // XR_USE_PLATFORM_XCB

#ifdef XR_USE_GRAPHICS_API_OPENGL
#if defined(XR_USE_PLATFORM_XLIB) || defined(XR_USE_PLATFORM_XCB)
#include <GL/glx.h>
#endif  // (XR_USE_PLATFORM_XLIB || XR_USE_PLATFORM_XCB)
#ifdef XR_USE_PLATFORM_XCB
#include <xcb/glx.h>
#endif  // XR_USE_PLATFORM_XCB
#ifdef XR_USE_PLATFORM_MACOS
#include <OpenCL/cl_gl_ext.h>
#endif  // XR_USE_PLATFORM_MACOS
#endif  // XR_USE_GRAPHICS_API_OPENGL

#ifdef XR_USE_GRAPHICS_API_OPENGL_ES
#include <EGL/egl.h>
#endif  // XR_USE_GRAPHICS_API_OPENGL_ES

#ifdef XR_USE_GRAPHICS_API_VULKAN
#include <vulkan/vulkan.h>
#endif  // XR_USE_GRAPHICS_API_VULKAN

#ifdef XR_USE_PLATFORM_WAYLAND
#include "wayland-client.h"
#endif  // XR_USE_PLATFORM_WAYLAND

#ifdef XR_USE_PLATFORM_EGL
#include <EGL/egl.h>
#endif  // XR_USE_PLATFORM_EGL

#if defined(XR_USE_PLATFORM_XLIB) || defined(XR_USE_PLATFORM_XCB)
#ifdef Success
#undef Success
#endif  // Success

#ifdef Always
#undef Always
#endif  // Always

#ifdef None
#undef None
#endif  // None
#endif  // defined(XR_USE_PLATFORM_XLIB) || defined(XR_USE_PLATFORM_XCB)
