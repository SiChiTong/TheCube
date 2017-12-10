////////////////////////////////////////////////////////////////////////////////
#include <REngine/Core/ReStringView>
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
////////////////////////////////////////////////////////////////////////////////
// C Standard Library
////////////////////////////////////////////////////////////////////////////////
#include <cstring>
////////////////////////////////////////////////////////////////////////////////
// C++ Standard Library
////////////////////////////////////////////////////////////////////////////////
#include <memory>
#include <string>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
#if !defined(TestString)
#  define TestString "TestString"
#else
#  error TestString is already defined
#endif // !defined (TestString)

#if !defined(TestString_char)
#  define TestString_char TestString
#else
#  error TestString_char is already defined
#endif // !defined (TestString_char)

#if !defined(TestString_wchar_t)
#  define TestString_wchar_t L"" TestString
#else
#  error TestString_wchar_t is already defined
#endif // !defined (TestString_wchar_t)
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Test Suits
////////////////////////////////////////////////////////////////////////////////
TEST (StringView, DefaultConstructor)
{
  REngine::Core::StringView sv;

  ASSERT_EQ (nullptr, sv.c_str ());
  ASSERT_EQ (nullptr, sv.c_wstr ());
}

TEST (StringView, Constructor)
{
  const char* cs1 = "";
  const char* cs2 = TestString_char;
  std::string std_s{ TestString_char };
  std::string_view std_sv{ TestString_char };

  REngine::Core::StringView cs_sv1{ cs1 };
  REngine::Core::StringView cs_sv2{ cs2 };
  REngine::Core::StringView std_s_sv{ std_s };
  REngine::Core::StringView std_sv_sv{ std_sv };

  ASSERT_STREQ (cs1, cs_sv1.c_str ());
  ASSERT_STREQ (cs2, cs_sv2.c_str ());
  ASSERT_STREQ (std_s.data (), std_s_sv.c_str ());
  ASSERT_STREQ (std_sv.data (), std_sv_sv.c_str ());

  ASSERT_STREQ (TestString_char, std_s_sv.c_str ());
  ASSERT_STREQ (TestString_char, std_sv_sv.c_str ());
}

TEST (StringView, unique_ptr)
{
  const char* cs = TestString_char;
  std::string std_s1{ TestString_char };

  std::unique_ptr<REngine::Core::StringView> cs_sv;

  ASSERT_EQ (nullptr, cs_sv);

  cs_sv = std::make_unique<REngine::Core::StringView> (TestString_char);

  ASSERT_STREQ (cs, cs_sv->c_str ());

  std::unique_ptr<REngine::Core::StringView> std_s_sv1;

  ASSERT_EQ (nullptr, std_s_sv1);

  std_s_sv1 = std::make_unique<REngine::Core::StringView> (std_s1);

  ASSERT_STREQ (std_s1.c_str (), std_s_sv1->c_str ());
  ASSERT_STREQ (TestString_wchar_t, std_s_sv1->c_wstr ());

  std::unique_ptr<REngine::Core::StringView> std_s_sv2;
  std::unique_ptr<REngine::Core::StringView> std_s_sv3;
  std::unique_ptr<REngine::Core::StringView> std_s_sv4;

  {
    std::string std_s2{ std_s1 };

    std_s_sv2 = std::make_unique<REngine::Core::StringView> (std_s2);
    std_s_sv3 = std::make_unique<REngine::Core::StringView> (std_s2.c_str ());

    const char* cs = TestString_char;
    std_s_sv4 = std::make_unique<REngine::Core::StringView> (cs);
    std::string_view sv{ std_s2 };
  }

  // "std_s2" goes out of scope and its data is destroyed thus the string data
  // that "std_s_sv2" points to is invalidated.

  // ASSERT_STRNE (std_s1.c_str (), std_s_sv2->c_str ());
  // ASSERT_STREQ (TestString_wchar_t, std_s_sv2->c_wstr ());

  ASSERT_STREQ (TestString_char, std_s_sv4->c_str ());
  ASSERT_STREQ (TestString_wchar_t, std_s_sv4->c_wstr ());
}

TEST (StringView, c_ctr)
{
  const char* cs = TestString_char;

  REngine::Core::StringView sv{ cs };

  ASSERT_STREQ (cs, sv.c_str ());
}

TEST (StringView, c_wctr)
{
  const char* cs = TestString_char;
  const wchar_t* wcs = TestString_wchar_t;
  std::wstring_view std_wsv{ wcs };

  REngine::Core::StringView sv{ cs };

  ASSERT_STREQ (std_wsv.data (), sv.c_wstr ());
}

TEST (StringView, string_view)
{
  const char* cs = TestString_char;
  const wchar_t* wcs = TestString_wchar_t;
  std::wstring_view std_wsv{ wcs };

  REngine::Core::StringView sv{ cs };

  ASSERT_STREQ (std_wsv.data (), sv.c_wstr ());
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Tests Entry Point
////////////////////////////////////////////////////////////////////////////////
int
  main (int argc, char** argv)
{
  ::testing::InitGoogleTest (&argc, argv);
  int ret = RUN_ALL_TESTS ();

  return ret;
}
////////////////////////////////////////////////////////////////////////////////
