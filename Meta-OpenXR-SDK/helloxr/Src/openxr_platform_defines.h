
// openxr_platform_defines.h

#define XRAPI_ATTR
#define XRAPI_CALL
#define XRAPI_PTR

#if(defined(__LP64__) || defined(_WIN64) || (defined(__x86_64__) && !defined(__ILP32__) ) || defined(_M_X64) || \
  defined(__ia64) || defined(_M_IA64) || defined(__aarch64__) || defined(__powerpc64__) \
)
#define XR_PTR_SIZE 8
#else
#define XR_PTR_SIZE 4
#endif

#if !defined(XR_COMPILER_HAS_FEATURE)

#if defined(__clang__)
#define XR_COMPILER_HAS_FEATURE(x) __has_feature(x)
#else
#define XR_COMPILER_HAS_FEATURE(x) 0
#endif

#endif

#if !defined(XR_CPP11_ENABLED)

#if defined(__GNUC__) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#define XR_CPP11_ENABLED 1
#else
#define XR_CPP11_ENABLED 1
#endif

#endif

#if !defined(XR_CPP_NULLPTR_SUPPORTED)

#if defined(XR_CPP11_ENABLED) && \
 ( (defined(__clang__) && XR_COMPILER_HAS_FEATURE(cxx_nullptr) ) || \
 (defined(__GNUC__) && ( ( (__GNUC__ * 1000) + __GNUC_MINOR__) >= 4006) ) || \
 (defined(__EDG_VERSION__) && (__EDG_VERSION__ >= 403) ) )
#define XR_CPP_NULLPTR_SUPPORTED 1
#endif

#endif

#if !defined(XR_CPP_NULLPTR_SUPPORTED)
#define XR_CPP_NULLPTR_SUPPORTED 0
#endif // !defined(XR_CPP_NULLPTR_SUPPORTED)
