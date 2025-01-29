
// exception_handling.h

#ifdef XRLOADER_DISABLE_EXCEPTION_HANDLING

#define XRLOADER_ABI_TRY
#define XRLOADER_ABI_CATCH_BAD_ALLOC_OOM
#define XRLOADER_ABI_CATCH_FALLBACK

#else // XRLOADER_DISABLE_EXCEPTION_HANDLING

#define XRLOADER_ABI_TRY try

#define XRLOADER_ABI_CATCH_BAD_ALLOC_OOM \
  catch(const std::bad_alloc& ) \
  { \
    LoaderLogger::LogErrorMessage("", "failed allocating memory"); \
    return XR_ERROR_OUT_OF_MEMORY; \
  }

#define XRLOADER_ABI_CATCH_FALLBACK \
  catch(const std::exception& e) \
  { \
    LoaderLogger::LogErrorMessage("", "Unknown failure: " + std::string(e.what() ) ); \
    return XR_ERROR_RUNTIME_FAILURE; \
  } \
  \
  catch(...) \
  { \
    LoaderLogger::LogErrorMessage("", "Unknown failure"); \
    return XR_ERROR_RUNTIME_FAILURE; \
  }
