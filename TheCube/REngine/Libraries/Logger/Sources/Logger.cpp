////////////////////////////////////////////////////////////////////////////////
#include "Logger.hpp"
////////////////////////////////////////////////////////////////////////////////
#include <consoleapi.h>
#include <iostream>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
LOGGER_NAMESPACE_BEGIN (Logger)
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Static members
////////////////////////////////////////////////////////////////////////////////

std::unique_ptr<Logger> Logger::logger;

////////////////////////////////////////////////////////////////////////////////

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

void
  Logger::SetPolicy (const Policy::Console& policy)
{
  printf ("Hello!\n");
  std::cout << "Hello!\n";
  if (policy.CreateConsole)
  {
    // Create the console
    if (AllocConsole ())
    {
      FILE* pCout;
      freopen_s (&pCout, "CONOUT$", "w", stdout);
      SetConsoleTitle (L"Debug Console");
    }
    printf ("Hello!\n");
    std::cout << "Hello!\n";
    // Set std::cout to use my custom streambuf
    outbuf ob;
    std::streambuf* sb = std::cout.rdbuf (&ob);

    // do some work here
    HANDLE stdHandle = GetStdHandle (STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD defaultConsoleTextAttributes;
    GetConsoleScreenBufferInfo (stdHandle, &consoleInfo);
    defaultConsoleTextAttributes = consoleInfo.wAttributes;
    WORD currentConsoleTextAttributes = FOREGROUND_INTENSITY;
    // FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
    SetConsoleTextAttribute (stdHandle, currentConsoleTextAttributes);

    printf ("c Hello!\n");
    // FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
    SetConsoleTextAttribute (stdHandle, currentConsoleTextAttributes);
    std::cout << "o Hello!\n";

    currentConsoleTextAttributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    SetConsoleTextAttribute (stdHandle, currentConsoleTextAttributes);

    SetForegroundColor (Policy::Properties::Color::Black);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::Blue);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::BlueDark);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::Cyan);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::CyanDark);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::Gray);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::Green);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::GreenDark);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::Magenta);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::MagentaDark);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::Red);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::RedDark);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::White);
    printf ("Hello!\n");

    currentConsoleTextAttributes = 0 | FOREGROUND_INTENSITY;
    // FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
    SetConsoleTextAttribute (stdHandle, currentConsoleTextAttributes);

    printf ("c Hello!\n");
    SetForegroundColor (Policy::Properties::Color::Yellow);
    printf ("Hello!\n");
    SetForegroundColor (Policy::Properties::Color::YellowDark);
    printf ("Hello!\n");

    std::cout << "Hello!\n";
    // Make sure to restore the original so we don't get a crash on close!
    std::cout.rdbuf (sb);
    std::cout << "Hello!\n";
    ShowWindow (GetConsoleWindow (), SW_HIDE);
    FreeConsole ();
    printf ("Hello!\n");
    std::cout << "Hello!\n";
  }
}

////////////////////////////////////////////////////////////////////////////////
LOGGER_NAMESPACE_END (Logger)
////////////////////////////////////////////////////////////////////////////////
