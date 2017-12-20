////////////////////////////////////////////////////////////////////////////////
// REngine Library
////////////////////////////////////////////////////////////////////////////////
#include <REngine/Core/ReString>
////////////////////////////////////////////////////////////////////////////////
// Google Test Library
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
////////////////////////////////////////////////////////////////////////////////
// C Standard Library
////////////////////////////////////////////////////////////////////////////////
#include <cstring>
////////////////////////////////////////////////////////////////////////////////
// C++ Standard Library
////////////////////////////////////////////////////////////////////////////////
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
TEST (String, DefaultConstructor)
{
  REngine::Core::String s;

  std::wstring ws;

  ASSERT_STREQ ("", s.c_str ());
  ASSERT_STREQ (L"", s.c_wstr ());
}

TEST (String, CopyConstructor)
{
  const char* cs = TestString_char;

  REngine::Core::String s1{ cs };
  REngine::Core::String s2{ s1 };

  ASSERT_STREQ (s1.c_str (), s2.c_str ());
  ASSERT_STREQ (s1.c_wstr (), s2.c_wstr ());
}

TEST (String, MoveConstructor)
{
  const char* cs = TestString_char;

  REngine::Core::String s1{ cs };
  REngine::Core::String s2{ std::move (s1) };

  ASSERT_STREQ ("", s1.c_str ());
  ASSERT_STREQ (cs, s2.c_str ());
}

TEST (String, CopyAssignment)
{
  const char* cs = TestString_char;

  REngine::Core::String s1{ cs };
  REngine::Core::String s2 = s1;

  ASSERT_STREQ (s1.c_str (), s2.c_str ());
  ASSERT_STREQ (s1.c_wstr (), s2.c_wstr ());
}

TEST (String, MoveAssignment)
{
  const char* cs = TestString_char;

  REngine::Core::String s1{ cs };
  REngine::Core::String s2 = std::move (s1);

  ASSERT_STREQ ("", s1.c_str ());
  ASSERT_STREQ (cs, s2.c_str ());
}

TEST (String, c_ctr)
{
  const char* cs = TestString_char;
  REngine::Core::String s1{ cs };

  ASSERT_STREQ (cs, s1.c_str ());
}

TEST (String, c_wctr)
{
  const char* cs = TestString_char;
  const wchar_t* wcs = TestString_wchar_t;

  REngine::Core::String s1{ cs };
  std::wstring s2{ wcs };

  ASSERT_STREQ (s1.c_wstr (), s2.c_str ());
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
