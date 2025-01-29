
// vk_sdk_platform.h

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
