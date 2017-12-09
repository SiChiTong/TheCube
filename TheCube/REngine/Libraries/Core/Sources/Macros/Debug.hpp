#pragma once

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
#  if defined(_DEBUG) && defined (ASSERT_ENABLED)
#    if defined(_WINDOWS)
#       if defined (SHORT_ASSERT)
#         // Use to compile smaller debug executables
#         define reAssert _ASSERT
#       else
#         define reAssert _ASSERTE
#       endif // defined (SHORT_ASSERT)
#    else
#      error Macro reAssert is not defined...
#    endif // defined (_WINDOWS)
#  else
#    define reAssert(expression)
#  endif // defined (_DEBUG) && defined (ASSERT_ENABLED)
#else
#  error Macro reAssert is already defined...
#endif // !defined (reAssert)

// Macro name:
//    reAssert
// Parameter:
//    expression
//    message
// Description:
//    Evaluates an expression and generates a debug report when the result is
//    false with the specified message.
#if !defined(reAssertM)
#  if defined(_DEBUG) && defined (ASSERT_ENABLED)
#    if defined(_WINDOWS)
#      define reAssertM(expression, message)                                   \
        _ASSERT_EXPR ((expression), _CRT_WIDE (#expression)##"\n"##message)
#    else
#      error Macro reAssertM is not defined...
#    endif // defined (_WINDOWS)
#  else
#    define reAssertM(expression, message)
#  endif // defined (_DEBUG) && defined (ASSERT_ENABLED)
#else
#  error Macro reAssertM is already defined...
#endif // !defined (reAssert)

// Macro name:
//    reVerify
// Parameter:
//    function
// Description:
//    Examinse the result of a function call and generates a debug report when
//    the result is false.
#if !defined(reVerify)
#  if defined(_DEBUG) && defined (ASSERT_ENABLED)
#    if defined(_WINDOWS)
#      define reVerify reAssert
#    else
#      error Macro reVerify is not defined...
#    endif // defined (_WINDOWS)
#  else
#    define reVerify(expression)
#  endif // defined (_DEBUG) && defined (ASSERT_ENABLED)
#else
#  error Macro reAssert is already defined...
#endif // !defined (reAssert)

////////////////////////////////////////////////////////////////////////////////
