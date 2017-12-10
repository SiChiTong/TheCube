#pragma once

////////////////////////////////////////////////////////////////////////////////
// System headers
////////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include <crtdbg.h>
#include <strsafe.h>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Assertion macros
////////////////////////////////////////////////////////////////////////////////

// Macro name:
//    reAssert
// Parameter:
//    expression
// Description:
//    Evaluates an expression and generates a debug report when the result is
//    false.
#if !defined(reAssert)
#  if defined(_DEBUG) && defined(ASSERT_ENABLED)
#    if defined(_WINDOWS)
#      if defined(SHORT_ASSERT)
#        // Use to compile smaller debug executables
#        define reAssert _ASSERT
#      else
#        define reAssert _ASSERTE
#      endif // defined (SHORT_ASSERT)
#    else
#      error Macro reAssert is not defined...
#    endif // defined (_WINDOWS)
#  else
#    define reAssert(expression)
#  endif // defined(_DEBUG) && defined(ASSERT_ENABLED)
#else
#  error Macro reAssert is already defined...
#endif // !defined(reAssert)

// Macro name:
//    reAssert
// Parameter:
//    expression
//    message
// Description:
//    Evaluates an expression and generates a debug report when the result is
//    false with the specified message.
#if !defined(reAssertM)
#  if defined(_DEBUG) && defined(ASSERT_ENABLED)
#    if defined(_WINDOWS)
#      define reAssertM(expression, message)                                   \
        _ASSERT_EXPR ((expression), _CRT_WIDE (#expression)##"\n"##message)
#    else
#      error Macro reAssertM is not defined...
#    endif // defined(_WINDOWS)
#  else
#    define reAssertM(expression, message)
#  endif // defined(_DEBUG) && defined(ASSERT_ENABLED)
#else
#  error Macro reAssertM is already defined...
#endif // !defined(reAssertM)

// Macro name:
//    reVerify
// Parameter:
//    function
// Description:
//    Examines the result of a function call, retrieves the system error message
//    for the last-error code and generates a debug report when the result is
//    false.
#if !defined(reVerify)
#  if defined(_DEBUG) && defined(ASSERT_ENABLED)
#    if defined(_WINDOWS)
#      define reVerify(function)                                               \
        if (!function)                                                         \
        {                                                                      \
          LPVOID lpMsgBuf;                                                     \
          LPVOID lpDisplayBuf;                                                 \
          DWORD dw = GetLastError ();                                          \
                                                                               \
          FormatMessage (FORMAT_MESSAGE_ALLOCATE_BUFFER                        \
                           | FORMAT_MESSAGE_FROM_SYSTEM                        \
                           | FORMAT_MESSAGE_IGNORE_INSERTS,                    \
                         NULL,                                                 \
                         dw,                                                   \
                         MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT),           \
                         (LPTSTR) &lpMsgBuf,                                   \
                         0,                                                    \
                         NULL);                                                \
                                                                               \
          lpDisplayBuf =                                                       \
            (LPVOID) LocalAlloc (LMEM_ZEROINIT,                                \
                                 (lstrlen ((LPCTSTR) lpMsgBuf)                 \
                                  + lstrlen (_CRT_WIDE (#function)) + 40)      \
                                   * sizeof (TCHAR));                          \
                                                                               \
          StringCchPrintf ((LPTSTR) lpDisplayBuf,                              \
                           LocalSize (lpDisplayBuf) / sizeof (TCHAR),          \
                           TEXT ("%s\n"                                        \
                                 "    failed with error %d: %s"),              \
                           _CRT_WIDE (#function),                              \
                           dw,                                                 \
                           lpMsgBuf);                                          \
                                                                               \
          _ASSERT_EXPR ((function), lpDisplayBuf);                             \
                                                                               \
          LocalFree (lpMsgBuf);                                                \
          LocalFree (lpDisplayBuf);                                            \
        }
#    endif // defined(_WINDOWS)
#  else
#    define reVerify(function)
#  endif // defined(_DEBUG) && defined(ASSERT_ENABLED)
#else
#  error Macro reAssert is already defined...
#endif // !defined(reVerify)

// Macro name:
//    reVerify_
// Parameter:
//    function
// Description:
//    Examines the result of a function call and generates a debug report when
//    the result is false.
#if !defined(reVerify_)
#  if defined(_DEBUG) && defined(ASSERT_ENABLED)
#    if defined(_WINDOWS)
#      define reVerify_ reAssert
#    else
#      error Macro reVerify is not defined...
#    endif // defined(_WINDOWS)
#  else
#    define reVerify_(function)
#  endif // defined(_DEBUG) && defined(ASSERT_ENABLED)
#else
#  error Macro reAssert is already defined...
#endif // !defined(reVerify)

////////////////////////////////////////////////////////////////////////////////
