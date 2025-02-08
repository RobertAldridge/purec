
// logger.h

#define LOGGER_ALOGE(...) do{ __android_log_print(ANDROID_LOG_ERROR, "helloxr", __VA_ARGS__); }while(0)
#define LOGGER_ALOGV(...) do{ __android_log_print(ANDROID_LOG_VERBOSE, "helloxr", __VA_ARGS__); }while(0)

namespace Log
{

enum class Level
{
  Verbose,
  Info,
  Warning,
  Error
};

void SetLevel(Level minSeverity);

void Write(Level severity, const std::string& msg);

} // namespace Log

extern Log::Level gLogger_minSeverity;

extern std::mutex gLogger_logLock;
