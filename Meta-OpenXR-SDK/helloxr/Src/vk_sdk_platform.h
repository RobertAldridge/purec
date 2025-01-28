
// vk_sdk_platform.h

#ifndef VK_SDK_PLATFORM_H
#define VK_SDK_PLATFORM_H

#if defined(_WIN32)
#define NOMINMAX
#ifndef __cplusplus
#undef inline
#define inline __inline
#endif // __cplusplus

#if (defined(_MSC_VER) && _MSC_VER < 1900 /*vs2015*/)
// C99:
// Microsoft didn't implement C99 in Visual Studio; but started adding it with
// VS2013.  However, VS2013 still didn't have snprintf().  The following is a
// work-around (Note: The _CRT_SECURE_NO_WARNINGS macro must be set in the
// "CMakeLists.txt" file).
// NOTE: This is fixed in Visual Studio 2015.
#define snprintf _snprintf
#endif

#define strdup _strdup

#endif // _WIN32

// Check for noexcept support using clang, with fallback to Windows or GCC version numbers
#ifndef NOEXCEPT
#if defined(__clang__)
#if __has_feature(cxx_noexcept)
#define HAS_NOEXCEPT
#endif
#else
#if defined(__GXX_EXPERIMENTAL_CXX0X__) && __GNUC__ * 10 + __GNUC_MINOR__ >= 46
#define HAS_NOEXCEPT
#else
#if defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 190023026 && defined(_HAS_EXCEPTIONS) && _HAS_EXCEPTIONS
#define HAS_NOEXCEPT
#endif
#endif
#endif

#ifdef HAS_NOEXCEPT
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif
#endif

#endif  // VK_SDK_PLATFORM_H
