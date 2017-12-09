#pragma once

////////////////////////////////////////////////////////////////////////////////
// Namespace definition macros
////////////////////////////////////////////////////////////////////////////////

// Macro name:
//    NAMESPACE_START (ns)
// Parameter:
//    ns - namespace names
#if !defined (NAMESPACE_START)
# define NAMESPACE_BEGIN(ns) namespace ns {
#else
# error Macro NAMESPACE_START is already defined...
#endif // !defined (NAMESPACE_START)

#if !defined (NAMESPACE_END)
# define NAMESPACE_END(ns) }
#else
# error Macro NAMESPACE_END is already defined...
#endif // !defined (NAMESPACE_START)

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
#if !defined (__Supress_Warning_LNK4221__)
# define __Supress_Warning_LNK4221__ \
  namespace { [[maybe_unused]] void* NoEmptyFileDummy##__LINE__; }
#else
# error Macro __Supress_Warning_LNK4221__ is already defined...
#endif // !defined (__Supress_Warning_LNK4221__)

////////////////////////////////////////////////////////////////////////////////
