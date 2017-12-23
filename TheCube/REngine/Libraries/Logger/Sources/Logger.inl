#pragma once

inline void
  Logger::Initialize ()
{
  Logger::logger = std::make_unique<Logger> ();
}

inline std::unique_ptr<Logger>&
  Logger::Instance ()
{
  assert (nullptr != logger);

  return logger;
}
