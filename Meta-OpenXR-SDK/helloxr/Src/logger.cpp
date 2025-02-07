
// logger.cpp

#include "header.h"

Log::Level gLogger_minSeverity {Log::Level::Verbose};

std::mutex gLogger_logLock;

namespace Log
{

void SetLevel(Level minSeverity)
{
  gLogger_minSeverity = minSeverity;
}

void Write(Level severity, const std::string& msg)
{
  if(severity < gLogger_minSeverity)
    return;

  const auto now = std::chrono::system_clock::now();
  const time_t now_time = std::chrono::system_clock::to_time_t(now);
  tm now_tm;

  localtime_r( &now_time, &now_tm);

  // time_t only has second precision. Use the rounding error to get sub-second precision.
  const auto secondRemainder = now - std::chrono::system_clock::from_time_t(now_time);
  const int64_t milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(secondRemainder).count();

  static std::map<Level, const char*> severityName =
  {
    {Level::Verbose, "Verbose"},
    {Level::Info, "Info   "},
    {Level::Warning, "Warning"},
    {Level::Error, "Error  "}
  };

  std::ostringstream out;

  out.fill('0');

  out << "[" << std::setw(2) << now_tm.tm_hour << ":" << std::setw(2) << now_tm.tm_min << ":" << std::setw(2) << now_tm.tm_sec
    << "." << std::setw(3) << milliseconds << "]"
    << "[" << severityName[severity] << "] " << msg << std::endl;

  // Ensure output is serialized
  std::lock_guard<std::mutex> lock(gLogger_logLock);

  ( (severity == Level::Error) ? std::clog : std::cout) << out.str();

  if(severity == Level::Error)
    LOGGER_ALOGE("%s", out.str().c_str() );
  else
    LOGGER_ALOGV("%s", out.str().c_str() );
}

} // namespace Log
