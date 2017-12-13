////////////////////////////////////////////////////////////////////////////////
#include "Settings.hpp"
////////////////////////////////////////////////////////////////////////////////
// C++ Standard Library
////////////////////////////////////////////////////////////////////////////////
#include <cstring>
#include <sstream>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_BEGIN (REngine::System)
////////////////////////////////////////////////////////////////////////////////

Settings::Settings ()
  : defaultSettings{
    { "-resolution", "1080p" },
    { "-renderer", "Vulkan" },
    { "-fullscreen", "true" },
  }
{}

Settings::Settings (int argc, const char* argv[])
  : Settings ()
{
  for (int argIndex = 1; argIndex < argc; ++argIndex)
  {
    std::string key;
    std::string value;

    std::string argument{ argv[argIndex] };
    auto pos = argument.find (":");
    // Check if the argument has a value
    if (std::string::npos == pos)
    {
      key = std::move (argument);
    }
    else
    {
      // Arguments are: the original string, the starting positions of the
      // substring, the length of substring
      key = std::move (std::string{ argument, 0, pos });
      // Check if ":" is the last element of the substring
      if (argument.length () != (pos + 1))
      {
        value = std::move (std::string{ argument, pos + 1 });
      }
    };
    // The values are moved from if the emplacement succeeds otherwise they
    // remain untouched
    auto [pair, wasInserted] =
      settings.try_emplace (std::move (key), std::move (value));

    // TODO: (HGH) Replace this check with a logging function
    if (!wasInserted)
    {
      std::wstringstream ss;
      ss << "Ignoring a duplicated command line argument: \"" << key.c_str ()
         << "\":\"" << value.c_str () << "\"\n";
      OutputDebugString (ss.str ().c_str ());
    }
    else
    {
      std::wstringstream ss;
      ss << "Inserted pair: \"" << pair->first.c_str () << "\":\""
         << pair->second.c_str () << "\"\n";
      OutputDebugString (ss.str ().c_str ());
    }
  }

  settings.merge (defaultSettings);
}

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_END (REngine::System)
////////////////////////////////////////////////////////////////////////////////
