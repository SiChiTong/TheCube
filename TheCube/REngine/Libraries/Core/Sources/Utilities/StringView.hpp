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
#include <string_view>
#include <vector>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_BEGIN (REngine::Core)
////////////////////////////////////////////////////////////////////////////////

class StringView {
public:
  StringView ();
  StringView (const char* c_str);
  StringView (const std::string_view& str_v);

  StringView (const StringView&) = delete;
  StringView (StringView&&) = delete;

  StringView& operator= (const StringView&) = delete;
  StringView& operator= (StringView&&) = delete;

public:
  const char* c_str () noexcept;
  const wchar_t* c_wstr () noexcept;
  const std::string_view& string_view () noexcept;
  const std::wstring_view& wstring_view () noexcept;

private:
  std::vector<wchar_t> wchar_t_DataBuffer;
  std::string_view internal_string_view;
  std::wstring_view internal_wstring_view;
};

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_END (REngine::Core)
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Inline methods
////////////////////////////////////////////////////////////////////////////////
#include "StringView.inl"
////////////////////////////////////////////////////////////////////////////////
