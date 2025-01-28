
// shaderc_visibility.h

#ifndef SHADERC_VISIBILITY_H_
#define SHADERC_VISIBILITY_H_

// SHADERC_EXPORT tags symbol that will be exposed by the shared libraries.
#if defined(SHADERC_SHAREDLIB)
#if defined(_WIN32)
#if defined(SHADERC_IMPLEMENTATION)
#define SHADERC_EXPORT __declspec(dllexport)
#else
#define SHADERC_EXPORT __declspec(dllimport)
#endif
#else
#if defined(SHADERC_IMPLEMENTATION)
#define SHADERC_EXPORT __attribute__((visibility("default")))
#else
#define SHADERC_EXPORT
#endif
#endif
#else
#define SHADERC_EXPORT
#endif

#endif  // SHADERC_VISIBILITY_H_
