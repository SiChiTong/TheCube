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
// C++ Standard Library
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Inline methods
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
LOGGER_NAMESPACE_BEGIN (ReLogger)
////////////////////////////////////////////////////////////////////////////////

template <typename Implementation>
inline auto
  Logger<Implementation>::SetBackgroundColor (Policy::Properties::Color color)
    -> void
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
      currentConsoleTextAttributes = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
      break;
    }
    case Color::BlueDark:
    {
      currentConsoleTextAttributes = BACKGROUND_BLUE;
      break;
    }
    case Color::Cyan:
    {
      currentConsoleTextAttributes =
        BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
      break;
    }
    case Color::CyanDark:
    {
      currentConsoleTextAttributes = BACKGROUND_BLUE | BACKGROUND_GREEN;
      break;
    }
    case Color::Gray:
    {
      currentConsoleTextAttributes =
        BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
      break;
    }
    case Color::GrayDark:
    {
      currentConsoleTextAttributes = BACKGROUND_INTENSITY;
      break;
    }
    case Color::Green:
    {
      currentConsoleTextAttributes = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
      break;
    }
    case Color::GreenDark:
    {
      currentConsoleTextAttributes = BACKGROUND_GREEN;
      break;
    }
    case Color::Magenta:
    {
      currentConsoleTextAttributes =
        BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY;
      break;
    }
    case Color::MagentaDark:
    {
      currentConsoleTextAttributes = BACKGROUND_BLUE | BACKGROUND_RED;
      break;
    }
    case Color::Red:
    {
      currentConsoleTextAttributes = BACKGROUND_RED | BACKGROUND_INTENSITY;
      break;
    }
    case Color::RedDark:
    {
      currentConsoleTextAttributes = BACKGROUND_RED;
      break;
    }
    case Color::White:
    {
      currentConsoleTextAttributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                     | BACKGROUND_RED | BACKGROUND_INTENSITY;
      break;
    }
    case Color::Yellow:
    {
      currentConsoleTextAttributes =
        BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
      break;
    }
    case Color::YellowDark:
    {
      currentConsoleTextAttributes = BACKGROUND_GREEN | BACKGROUND_RED;
      break;
    }
    default:
    {
      currentConsoleTextAttributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                     | BACKGROUND_RED | BACKGROUND_INTENSITY;
      break;
    }
  }

  SetConsoleTextAttribute (
    stdHandle, (defaultConsoleTextAttributes | currentConsoleTextAttributes));
}

template <typename Implementation>
inline auto
  Logger<Implementation>::SetForegroundColor (Policy::Properties::Color color)
    -> void
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
      currentConsoleTextAttributes = FOREGROUND_BLUE;
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

  SetConsoleTextAttribute (stdHandle, (currentConsoleTextAttributes));
}

template <typename Implementation>
Logger<Implementation>::Logger ()
{}

class outbuf : public std::streambuf
{
 public:
  outbuf ()
  {
    setp (0, 0);
  }
  char ca[2] = { 0 };

  virtual int_type overflow (int_type c = traits_type::eof ())
  {
    ca[0] = c;
    OutputDebugStringA (reinterpret_cast<char*> (&c));
    return fputc (c, stdout) == EOF ? traits_type::eof () : c;
  }
};

template <typename Implementation>
void
  Logger<Implementation>::SetPolicy (const Policy::Console& policy)
{
  // printf ("Hello!\n");
  // std::cout << "Hello!\n";
  if (policy.CreateConsole)
  {
    // Create the console
    if (AllocConsole ())
    {
      FILE* pCout;
      freopen_s (&pCout, "CONOUT$", "w", stdout);
      SetConsoleTitle (L"Debug Console");
    }
    // printf ("Hello!\n");
    // std::cout << "Hello!\n";
    // Set std::cout to use my custom streambuf
    outbuf ob;
    std::streambuf* sb = std::cout.rdbuf (&ob);

    // do some work here
    HANDLE stdHandle = GetStdHandle (STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD defaultConsoleTextAttributes;
    GetConsoleScreenBufferInfo (stdHandle, &consoleInfo);
    defaultConsoleTextAttributes = consoleInfo.wAttributes;
    // WORD currentConsoleTextAttributes = FOREGROUND_INTENSITY;
    //// FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
    // SetConsoleTextAttribute (stdHandle, currentConsoleTextAttributes);

    // printf ("c Hello!\n");
    //// FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
    // SetConsoleTextAttribute (stdHandle, currentConsoleTextAttributes);
    // std::cout << "o Hello!\n";

    // currentConsoleTextAttributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    // SetConsoleTextAttribute (stdHandle, currentConsoleTextAttributes);

    SetForegroundColor (Policy::Properties::Color::Black);
    SetBackgroundColor (Policy::Properties::Color::Blue);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::Black);
    SetBackgroundColor (Policy::Properties::Color::BlueDark);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::Black);
    SetBackgroundColor (Policy::Properties::Color::Black);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::Black);
    SetBackgroundColor (Policy::Properties::Color::Cyan);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::White);
    SetBackgroundColor (Policy::Properties::Color::CyanDark);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::White);
    SetBackgroundColor (Policy::Properties::Color::Gray);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::White);
    SetBackgroundColor (Policy::Properties::Color::GrayDark);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::White);
    SetBackgroundColor (Policy::Properties::Color::Green);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::White);
    SetBackgroundColor (Policy::Properties::Color::GreenDark);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::White);
    SetBackgroundColor (Policy::Properties::Color::Magenta);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::White);
    SetBackgroundColor (Policy::Properties::Color::MagentaDark);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::YellowDark);
    SetBackgroundColor (Policy::Properties::Color::Red);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::Yellow);
    SetBackgroundColor (Policy::Properties::Color::RedDark);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::White);
    SetBackgroundColor (Policy::Properties::Color::White);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::CyanDark);
    SetBackgroundColor (Policy::Properties::Color::White);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::White);
    SetBackgroundColor (Policy::Properties::Color::Yellow);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::White);
    SetBackgroundColor (Policy::Properties::Color::YellowDark);
    printf ("Hello!\n");
    // SetForegroundColor (Policy::Properties::Color::Blue);
    // SetBackgroundColor (Policy::Properties::Color::RedDark);
    // printf ("Hello!\n");
    // SetForegroundColor (Policy::Properties::Color::BlueDark);
    // printf ("Hello!\n");
    // SetForegroundColor (Policy::Properties::Color::Cyan);
    // printf ("Hello!\n");
    // SetForegroundColor (Policy::Properties::Color::CyanDark);
    // printf ("Hello!\n");
    // SetForegroundColor (Policy::Properties::Color::Gray);
    // SetBackgroundColor (Policy::Properties::Color::RedDark);
    // printf ("Hello!\n");
    // SetForegroundColor (Policy::Properties::Color::Green);
    // printf ("Hello!\n");
    // SetForegroundColor (Policy::Properties::Color::GreenDark);
    // printf ("Hello!\n");
    // SetForegroundColor (Policy::Properties::Color::Magenta);
    // printf ("Hello!\n");
    // SetForegroundColor (Policy::Properties::Color::MagentaDark);
    // printf ("Hello!\n");
    // SetForegroundColor (Policy::Properties::Color::Red);
    // printf ("Hello!\n");
    // SetForegroundColor (Policy::Properties::Color::RedDark);
    // printf ("Hello!\n");
    // SetForegroundColor (Policy::Properties::Color::White);
    // SetBackgroundColor (Policy::Properties::Color::RedDark);
    // printf ("Hello!\n");

    // currentConsoleTextAttributes = 0 | FOREGROUND_INTENSITY;
    //// FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
    // SetConsoleTextAttribute (stdHandle, currentConsoleTextAttributes);

    // SetBackgroundColor (Policy::Properties::Color::RedDark);
    // printf ("c Hello!\n");
    // SetForegroundColor (Policy::Properties::Color::Yellow);
    // printf ("Hello!\n");
    // SetForegroundColor (Policy::Properties::Color::YellowDark);
    // printf ("Hello!\n");

    // std::cout << "Hello!\n";
    //// Make sure to restore the original so we don't get a crash on close!
    // std::cout.rdbuf (sb);
    // std::cout << "Hello!\n";
    ShowWindow (GetConsoleWindow (), SW_HIDE);
    FreeConsole ();
    // printf ("Hello!\n");
    // std::cout << "Hello!\n";
  }
}

////////////////////////////////////////////////////////////////////////////////
// Static free functions
////////////////////////////////////////////////////////////////////////////////

inline Logger<Logger_Implementation>&
  Instance ()
{
  // Function local initialization in C++ 11 is thread-safe, see: "Dynamic
  // Initialization and Destruction with Concurrency, 6.7 Declaration statement
  // [stmt.dcl], paragraph 4"- clarification of implementation requirements for
  // local static initialization
  static Logger<Logger_Implementation> logger;

  return logger;
}

////////////////////////////////////////////////////////////////////////////////
LOGGER_NAMESPACE_END (ReLogger)
////////////////////////////////////////////////////////////////////////////////
