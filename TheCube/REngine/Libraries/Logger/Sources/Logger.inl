#pragma once

////////////////////////////////////////////////////////////////////////////////
// Windows System headers
////////////////////////////////////////////////////////////////////////////////
#include <consoleapi.h>
////////////////////////////////////////////////////////////////////////////////
// C Standard Library
////////////////////////////////////////////////////////////////////////////////
#include <cassert>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
LOGGER_NAMESPACE_BEGIN (Logger)
////////////////////////////////////////////////////////////////////////////////
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

inline auto
  Logger::SetForegroundColor (Policy::Properties::Color color) -> void
{
  HANDLE stdHandle = GetStdHandle (STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
  WORD defaultConsoleTextAttributes;
  GetConsoleScreenBufferInfo (stdHandle, &consoleInfo);
  defaultConsoleTextAttributes = consoleInfo.wAttributes;
  WORD currentConsoleTextAttributes = 0;

  using Policy::Properties::Color;

  switch (color)
  {
    case Color::Black:
    {
      currentConsoleTextAttributes = 0;
      break;
    }
    case Color::Blue:
    {
      currentConsoleTextAttributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
      break;
    }
    case Color::BlueDark:
    {
      currentConsoleTextAttributes = BACKGROUND_BLUE; // FOREGROUND_BLUE;
      break;
    }
    case Color::Cyan:
    {
      currentConsoleTextAttributes =
        FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
      break;
    }
    case Color::CyanDark:
    {
      currentConsoleTextAttributes = FOREGROUND_BLUE | FOREGROUND_GREEN;
      break;
    }
    case Color::Gray:
    {
      currentConsoleTextAttributes =
        FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
      break;
    }
    case Color::GrayDark:
    {
      currentConsoleTextAttributes = FOREGROUND_INTENSITY;
      break;
    }
    case Color::Green:
    {
      currentConsoleTextAttributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
      break;
    }
    case Color::GreenDark:
    {
      currentConsoleTextAttributes = FOREGROUND_GREEN;
      break;
    }
    case Color::Magenta:
    {
      currentConsoleTextAttributes =
        FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
      break;
    }
    case Color::MagentaDark:
    {
      currentConsoleTextAttributes = FOREGROUND_BLUE | FOREGROUND_RED;
      break;
    }
    case Color::Red:
    {
      currentConsoleTextAttributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
      break;
    }
    case Color::RedDark:
    {
      currentConsoleTextAttributes = FOREGROUND_RED;
      break;
    }
    case Color::White:
    {
      currentConsoleTextAttributes = FOREGROUND_BLUE | FOREGROUND_GREEN
                                     | FOREGROUND_RED | FOREGROUND_INTENSITY;
      break;
    }
    case Color::Yellow:
    {
      currentConsoleTextAttributes =
        FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
      break;
    }
    case Color::YellowDark:
    {
      currentConsoleTextAttributes = FOREGROUND_GREEN | FOREGROUND_RED;
      break;
    }
    default:
    {
      currentConsoleTextAttributes = FOREGROUND_BLUE | FOREGROUND_GREEN
                                     | FOREGROUND_RED | FOREGROUND_INTENSITY;
      break;
    }
  }

  SetConsoleTextAttribute (stdHandle, currentConsoleTextAttributes);
}

////////////////////////////////////////////////////////////////////////////////
LOGGER_NAMESPACE_END (LOGGER)
////////////////////////////////////////////////////////////////////////////////
