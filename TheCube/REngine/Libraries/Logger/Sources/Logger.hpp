#pragma once

////////////////////////////////////////////////////////////////////////////////
// Logger Library
////////////////////////////////////////////////////////////////////////////////
#include "Macros/UtilityMacros.hpp"
#include "Platforms/Logger_Platforms.hpp"
#include "Utilities/implementedBy.hpp"
#include "Policy.hpp"
////////////////////////////////////////////////////////////////////////////////
// C++ Standard Library
////////////////////////////////////////////////////////////////////////////////
#include <mutex>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
LOGGER_NAMESPACE_BEGIN (ReLogger)
////////////////////////////////////////////////////////////////////////////////

template <typename Implementation>
class Logger : public implementedBy<Implementation>
{
  friend auto Instance () -> Logger<Logger_Implementation>&;

 private:
  // Disable dynamic creation
  Logger ();

 public:
  auto SetBackgroundColor (Policy::Properties::Color color) -> void;
  auto SetForegroundColor (Policy::Properties::Color color) -> void;

  void SetPolicy (const Policy::Console& policy);
  void SetPolicy (const Policy::File& policy);

  auto GetLogFunctionAndLockIt () -> void*;
  void UnlockLogFunction ();

 private:
  void Initialize ();

 private:
  std::unique_ptr<Logger_Implementation> ptr_;
};

////////////////////////////////////////////////////////////////////////////////
// Free functions
////////////////////////////////////////////////////////////////////////////////

// Returns the logger instance
static auto
  Instance () -> Logger<Logger_Implementation>&;

////////////////////////////////////////////////////////////////////////////////
LOGGER_NAMESPACE_END (ReLogger)
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Inline methods
////////////////////////////////////////////////////////////////////////////////
#include "Logger.inl"
////////////////////////////////////////////////////////////////////////////////
