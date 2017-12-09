#pragma once

////////////////////////////////////////////////////////////////////////////////
// Inline methods
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_BEGIN (REngine::Core)
////////////////////////////////////////////////////////////////////////////////

inline const char*
  StringView::c_str () noexcept
{
  return this->internal_string_view.data ();
}

inline const wchar_t*
  StringView::c_wstr () noexcept
{
  if (this->internal_wstring_view.empty ())
  {
    using namespace std;

    size_t charCount = 0;
    auto srcString = this->internal_string_view.data ();
    auto srcStringLength = this->internal_string_view.length ();
    std::mbstate_t mbstate = std::mbstate_t ();
    memset (&mbstate, 0, sizeof (std::mbstate_t));

    mbsrtowcs_s (&charCount,
                 wchar_t_DataBuffer.data (),
                 wchar_t_DataBuffer.size (),
                 &srcString,
                 srcStringLength,
                 &mbstate);

    auto stringData = wchar_t_DataBuffer.data ();
    if (nullptr != stringData)
    {
      this->internal_wstring_view = stringData;
    }
  }

  return this->internal_wstring_view.data ();
}

inline const std::string_view&
  StringView::string_view () noexcept
{
  return this->internal_string_view;
}

inline const std::wstring_view&
  StringView::wstring_view () noexcept
{
  return this->internal_wstring_view;
}

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_END (REngine::Core)
////////////////////////////////////////////////////////////////////////////////
