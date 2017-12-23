#pragma once

#include <cassert>
#include <memory>
#include <string>

namespace Policy
{
struct Console
{
  bool CreateConsole = false;
};

struct File
{
  std::string Filename;
};

// Future development
// struct Application
//{
//};

// struct Network
//{
//  std::string NetworkAddress;
//};
}; // namespace Policy

class Logger
{
 public:
  void SetPolicy (const Policy::Console& policy);
  void SetPolicy (const Policy::File& policy);

  auto GetLogFunctionAndLockIt () -> void*;
  void UnlockLogFunction ();

  static auto Initialize () -> void;
  static auto Instance () -> std::unique_ptr<Logger>&;

 public:
 private:
  static std::unique_ptr<Logger> logger;
};

#include "Logger.inl"
