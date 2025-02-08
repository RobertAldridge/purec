
// check.h

#define CHK_STRINGIFY_CHECK(x) #x

#define TOSTRING_CHECK(x) CHK_STRINGIFY_CHECK(x)

#define FILE_AND_LINE_CHECK __FILE__ ":" TOSTRING_CHECK(__LINE__)

[ [noreturn] ] inline void ThrowCheck(
  std::string failureMessage,
  const char* originator = nullptr,
  const char* sourceLocation = nullptr
)
{
  if(originator != nullptr)
    failureMessage += Fmt("\nOrigin: %s", originator);

  if(sourceLocation != nullptr)
    failureMessage += Fmt("\nSource: %s", sourceLocation);

  throw std::logic_error(failureMessage);
}

#define THROW_CHECK(msg) ThrowCheck(msg, nullptr, FILE_AND_LINE_CHECK)

#define CHECK_CHECK(exp) \
  do \
  { \
    if( !(exp) ) \
      ThrowCheck("Check failed", #exp, FILE_AND_LINE_CHECK); \
  \
  }while(0)

#define CHECK_MSG(exp, msg) \
  do \
  { \
    if( !(exp) ) \
      ThrowCheck(msg, #exp, FILE_AND_LINE_CHECK); \
  \
  }while(0)

[ [noreturn] ] inline void ThrowXrResult(
  XrResult res,
  const char* originator = nullptr,
  const char* sourceLocation = nullptr
)
{
  ThrowCheck(Fmt("XrResult failure [%s]", to_string(res) ), originator, sourceLocation);
}

inline XrResult CheckXrResult(XrResult res, const char* originator = nullptr, const char* sourceLocation = nullptr)
{
  if(XR_FAILED(res) )
    ThrowXrResult(res, originator, sourceLocation);

  return res;
}

#define THROW_XR_CHECK(xr, cmd) ThrowXrResult(xr, #cmd, FILE_AND_LINE_CHECK)

#define CHECK_XRCMD_CHECK(cmd) CheckXrResult(cmd, #cmd, FILE_AND_LINE_CHECK)

#define CHECK_XRRESULT(res, cmdStr) CheckXrResult(res, cmdStr, FILE_AND_LINE_CHECK)
