#pragma once

////////////////////////////////////////////////////////////////////////////////
// REngine Base
////////////////////////////////////////////////////////////////////////////////
#include <REngine/Core/ReCoreBase>
////////////////////////////////////////////////////////////////////////////////
// C++ Standard Library
////////////////////////////////////////////////////////////////////////////////
#include <map>
#include <string>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_BEGIN (REngine::System)
////////////////////////////////////////////////////////////////////////////////

class Settings
{
 public:
  Settings ();
  Settings (int argc, const char* argv[]);

 public:
  const std::map<std::string, std::string>& Get () const;

 private:
  std::map<std::string, std::string> defaultSettings;
  std::map<std::string, std::string> settings;
};

inline const std::map<std::string, std::string>&
  Settings::Get () const
{
  return this->settings;
}

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_END (REngine::System)
////////////////////////////////////////////////////////////////////////////////