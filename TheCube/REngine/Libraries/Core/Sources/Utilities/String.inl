#pragma once

////////////////////////////////////////////////////////////////////////////////
// Inline methods
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_BEGIN (REngine::Core)
////////////////////////////////////////////////////////////////////////////////

inline const char*
  String::c_str () noexcept
{
  return this->internal_string.c_str ();
}

inline const wchar_t*
  String::c_wstr () noexcept
{
  if (this->internal_wstring.empty ())
  {
    using namespace std;

    size_t charCount = 0;
    std::vector<wchar_t> dstBuffer (this->internal_string.length () + 1);
    auto srcString = this->internal_string.c_str ();
    auto srcStringLength = this->internal_string.length ();
    std::mbstate_t mbstate = std::mbstate_t ();
    memset (&mbstate, 0, sizeof (std::mbstate_t));

    mbsrtowcs_s (&charCount,
                 dstBuffer.data (),
                 dstBuffer.size (),
                 &srcString,
                 srcStringLength,
                 &mbstate);

    auto stringData = dstBuffer.data ();
    if (nullptr != stringData)
    {
      this->internal_wstring = stringData;
    }
  }

  return this->internal_wstring.c_str ();
}

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_END (REngine::Core)
////////////////////////////////////////////////////////////////////////////////
