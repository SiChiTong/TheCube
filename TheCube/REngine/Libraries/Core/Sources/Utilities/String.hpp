#pragma once

////////////////////////////////////////////////////////////////////////////////
// REngine Base
#include <REngine/Core/ReCoreBase>
////////////////////////////////////////////////////////////////////////////////
// C Standard Library
////////////////////////////////////////////////////////////////////////////////
#include <cstdio>
////////////////////////////////////////////////////////////////////////////////
// C++ Standard Library
////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <vector>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_BEGIN (REngine::Core)
////////////////////////////////////////////////////////////////////////////////

class String {
public:
  String ();
  String (const char* c_str);
  String (const std::string& str);

public:
  String (const String& other);
  String (String&& other);

public:
  const String& operator= (const String& other);
  const String& operator= (String&& other);

public:
  const String& operator= (const char*& c_str);
  const String& operator= (const std::string& str);

public:
  const char* c_str () noexcept;
  const wchar_t* c_wstr () noexcept;

private:
  std::string internal_string;
  std::wstring internal_wstring;
};

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_END (REngine::Core)
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Inline methods
////////////////////////////////////////////////////////////////////////////////
#include "String.inl"
////////////////////////////////////////////////////////////////////////////////
