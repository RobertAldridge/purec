
// shaderc_visibility.h

// SHADERC_EXPORT tags symbol that will be exposed by the shared libraries

#if defined(SHADERC_SHAREDLIB)

#if defined(SHADERC_IMPLEMENTATION)
#define SHADERC_EXPORT __attribute__ ( (visibility("default") ) )
#else
#define SHADERC_EXPORT
#endif

#else

#define SHADERC_EXPORT

#endif
