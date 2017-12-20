////////////////////////////////////////////////////////////////////////////////
// REngine Base
////////////////////////////////////////////////////////////////////////////////
#include <REngine/Core/ReCoreBase>
////////////////////////////////////////////////////////////////////////////////
// REngine Library
////////////////////////////////////////////////////////////////////////////////
#include <REngine/Core/RePlatformInternals>
////////////////////////////////////////////////////////////////////////////////
// Google Test Library
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
////////////////////////////////////////////////////////////////////////////////
// System headers
////////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Test Suits
////////////////////////////////////////////////////////////////////////////////

TEST (ObjectHandle, NullptrHandle)
{
  HANDLE rawHandle1 = CreateEvent (nullptr, true, false, nullptr);

  // Constructor
  REngine::Core::NullptrHandle eventHandle1{ rawHandle1 };

  ASSERT_NE (nullptr, eventHandle1.Get ());

  // Move constructor
  REngine::Core::NullptrHandle eventHandle2{ std::move (eventHandle1) };

  ASSERT_EQ (nullptr, eventHandle1.Get ());
  ASSERT_NE (nullptr, eventHandle2.Get ());

  // Move assignment operator
  REngine::Core::NullptrHandle eventHandle3 = std::move (eventHandle2);

  ASSERT_EQ (nullptr, eventHandle2.Get ());
  ASSERT_NE (nullptr, eventHandle3.Get ());

  // Method: Get
  ASSERT_EQ (rawHandle1, eventHandle3.Get ());

  // Method: Release
  rawHandle1 = eventHandle3.Release ();

  ASSERT_EQ (nullptr, eventHandle3.Get ());
  ASSERT_NE (nullptr, rawHandle1);

  // Method: Reset
  HANDLE rawHandle2 = CreateEvent (nullptr, true, false, nullptr);
  eventHandle3.Reset (rawHandle2);

  ASSERT_NE (rawHandle1, eventHandle3.Get ());
  ASSERT_EQ (rawHandle2, eventHandle3.Get ());

  eventHandle3.Reset ();

  ASSERT_EQ (nullptr, eventHandle3.Get ());
}

TEST (ObjectHandle, InvalidValueHandle)
{
  auto filename1 =
    LR"(OpenHandleTest-122caa32-d0e4-4aae-b3e1-e1eea9388c98.txt)";
  auto filename2 =
    LR"(OpenHandleTest-1aa3df3e-e2e6-4d89-bc12-6ad06de3b6dd.txt)";
  {
    HANDLE rawHandle1 = CreateFile (filename1,
                                    GENERIC_READ,
                                    FILE_SHARE_DELETE,
                                    nullptr,
                                    CREATE_ALWAYS,
                                    FILE_ATTRIBUTE_NORMAL,
                                    nullptr);
    reVerify (INVALID_HANDLE_VALUE != rawHandle1);

    // Constructor
    REngine::Core::InvalidValueHandle eventHandle1{ rawHandle1 };

    ASSERT_NE (INVALID_HANDLE_VALUE, eventHandle1.Get ());

    // Move constructor
    REngine::Core::InvalidValueHandle eventHandle2{ std::move (eventHandle1) };

    ASSERT_EQ (INVALID_HANDLE_VALUE, eventHandle1.Get ());
    ASSERT_NE (INVALID_HANDLE_VALUE, eventHandle2.Get ());

    // Move assignment operator
    REngine::Core::InvalidValueHandle eventHandle3 = std::move (eventHandle2);

    ASSERT_EQ (INVALID_HANDLE_VALUE, eventHandle2.Get ());
    ASSERT_NE (INVALID_HANDLE_VALUE, eventHandle3.Get ());

    // Method: Get
    ASSERT_EQ (rawHandle1, eventHandle3.Get ());

    // Method: Release
    rawHandle1 = eventHandle3.Release ();

    ASSERT_EQ (INVALID_HANDLE_VALUE, eventHandle3.Get ());
    ASSERT_NE (INVALID_HANDLE_VALUE, rawHandle1);

    // Method: Reset
    HANDLE rawHandle2 = CreateFile (filename2,
                                    GENERIC_READ,
                                    FILE_SHARE_DELETE,
                                    nullptr,
                                    CREATE_ALWAYS,
                                    FILE_ATTRIBUTE_NORMAL,
                                    nullptr);
    reVerify (INVALID_HANDLE_VALUE != rawHandle2);

    eventHandle3.Reset (rawHandle2);

    ASSERT_NE (rawHandle1, eventHandle3.Get ());
    ASSERT_EQ (rawHandle2, eventHandle3.Get ());

    eventHandle3.Reset ();

    ASSERT_EQ (INVALID_HANDLE_VALUE, eventHandle3.Get ());
  }

  reVerify (DeleteFile (filename1));
  reVerify (DeleteFile (filename2));
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
