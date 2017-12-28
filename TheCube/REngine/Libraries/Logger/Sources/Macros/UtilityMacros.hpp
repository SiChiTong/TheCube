#pragma once

////////////////////////////////////////////////////////////////////////////////
// Namespace definition macros
////////////////////////////////////////////////////////////////////////////////

// Macro name:
//    NAMESPACE_START (ns)
// Parameter:
//    ns - namespace names
#if !defined(LOGGER_NAMESPACE_BEGIN)
#  define LOGGER_NAMESPACE_BEGIN(ns)                                           \
    namespace ns                                                               \
    {
#else
#  error Macro 'LOGGER_NAMESPACE_BEGIN' is already defined
#endif !defined(LOGGER_NAMESPACE_BEGIN)
#if !defined(LOGGER_NAMESPACE_END)
#  define LOGGER_NAMESPACE_END(ns) }
#else
#  error Macro 'LOGGER_NAMESPACE_END' is already defined
#endif !defined(LOGGER_NAMESPACE_END)

////////////////////////////////////////////////////////////////////////////////
// Linker error macros
////////////////////////////////////////////////////////////////////////////////

// This macro can suppress the MS Visual C++ Linker warning LNK4221 if put in a
// translation unit.
//
// Symbols within an annonymous namespace have external linkage, so there will
// be something in the export table. On the other hand, the namespace name
// itself will be distinct for every translation unit, so no clashes will occur.
//
// warning LNK4221: This object file does not define any previously undefined
// public symbols, so it will not be used by any link operation that consumes
// this library
#if !defined(LOGGER__Supress_Warning__)
#  define LOGGER__Supress_Warning__(warning)                                   \
    namespace                                                                  \
    {                                                                          \
    [[maybe_unused]] void* warning##__LINE__;                                  \
    } // namespace
#else
#  error Macro LOGGER__Supress_Warning__(warning) is already defined...
#endif //! defined(LOGGER__Supress_Warning__)

////////////////////////////////////////////////////////////////////////////////
