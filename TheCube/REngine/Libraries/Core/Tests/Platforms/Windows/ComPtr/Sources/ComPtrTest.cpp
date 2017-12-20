////////////////////////////////////////////////////////////////////////////////
#include "ComInterfaces.hpp"
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

////////////////////////////////////////////////////////////////////////////////
// Test Suits
////////////////////////////////////////////////////////////////////////////////

TEST (ComPtr, DefaultConstructor)
{
  REngine::Core::Windows::ComPtr<IBase> base;
  ASSERT_EQ (nullptr, base.Get ());
  // Test address of internal pointer
  ASSERT_NE (nullptr, base.GetAddressOf ());
  ASSERT_NE (nullptr, &base);
}

TEST (ComPtr, CopyConstructor)
{
  REngine::Core::Windows::ComPtr<IBase> base1;
  ASSERT_EQ (nullptr, base1.Get ());
  CreateDerivedObject (&base1);
  ASSERT_TRUE (base1);

  REngine::Core::Windows::ComPtr<IBase> base2 (base1);
  ASSERT_TRUE (base2);
  ASSERT_EQ (base1.Get (), base2.Get ());

  REngine::Core::Windows::ComPtr<IUnknown> unknown (base1);
  ASSERT_TRUE (unknown);
  ASSERT_EQ (unknown.Get (), base2.Get ());
}

TEST (ComPtr, CopyAssignment)
{
  REngine::Core::Windows::ComPtr<IBase> base1;
  ASSERT_EQ (nullptr, base1.Get ());
  CreateDerivedObject (&base1);
  ASSERT_TRUE (base1);

  REngine::Core::Windows::ComPtr<IBase> base2;
  ASSERT_EQ (nullptr, base2.Get ());

  base2 = base1;
  ASSERT_TRUE (base2);
  ASSERT_EQ (base1.Get (), base2.Get ());

  REngine::Core::Windows::ComPtr<IUnknown> unknown;
  ASSERT_EQ (nullptr, unknown.Get ());
  unknown = base1;
  ASSERT_TRUE (unknown);
  ASSERT_EQ (unknown.Get (), base2.Get ());
}

TEST (ComPtr, MoveConstructor)
{
  REngine::Core::Windows::ComPtr<IBase> base1;
  ASSERT_EQ (nullptr, base1.Get ());
  CreateDerivedObject (&base1);
  ASSERT_TRUE (base1);

  auto basePtr = base1.Get ();
  basePtr->AddRef ();

  REngine::Core::Windows::ComPtr<IBase> base2 (std::move (base1));
  ASSERT_TRUE (base2);
  ASSERT_FALSE (base1);
  ASSERT_EQ (basePtr, base2.Get ());

  REngine::Core::Windows::ComPtr<IUnknown> unknown (std::move (base2));
  ASSERT_TRUE (unknown);
  ASSERT_FALSE (base2);
  ASSERT_EQ (basePtr, unknown.Get ());

  basePtr->Release ();
}

TEST (ComPtr, MoveAssignment)
{
  REngine::Core::Windows::ComPtr<IBase> base1;
  ASSERT_EQ (nullptr, base1.Get ());
  CreateDerivedObject (&base1);
  ASSERT_TRUE (base1);

  auto basePtr = base1.Get ();
  basePtr->AddRef ();

  REngine::Core::Windows::ComPtr<IBase> base2;
  ASSERT_EQ (nullptr, base2.Get ());

  base2 = std::move (base1);
  ASSERT_TRUE (base2);
  ASSERT_FALSE (base1);
  ASSERT_EQ (basePtr, base2.Get ());

  REngine::Core::Windows::ComPtr<IUnknown> unknown;
  ASSERT_EQ (nullptr, unknown.Get ());
  unknown = std::move (base2);
  ASSERT_TRUE (unknown);
  ASSERT_FALSE (base2);
  ASSERT_EQ (basePtr, unknown.Get ());

  basePtr->Release ();
}

TEST (ComPtr, ComPtr)
{
  REngine::Core::Windows::ComPtr<IBase> base;
  ASSERT_NE (nullptr, &base);
  switch (auto result = CreateDerivedObject (&base); result)
  {
    case S_OK:
    {
      ASSERT_NE (nullptr, base.Get ());
      EXPECT_EQ (IBaseMethodValue, base->IBaseMethod ());

      break;
    }
    case E_INVALIDARG:
    {
      ASSERT_TRUE (false);

      break;
    }
    case E_OUTOFMEMORY:
    {
      ASSERT_TRUE (false);

      break;
    }
    default:
    {
      ASSERT_TRUE (false);

      break;
    }
  }

  REngine::Core::Windows::ComPtr<IFeature> feature;
  switch (auto result = base->QueryInterface<IFeature> (&feature); result)
  {
    case S_OK:
    {
      ASSERT_NE (nullptr, feature.Get ());
      EXPECT_EQ (IFeatureMethodValue, feature->IFeatureMethod ());

      break;
    }
    case E_INVALIDARG:
    {
      EXPECT_TRUE (false);

      break;
    }
    case E_OUTOFMEMORY:
    {
      EXPECT_TRUE (false);

      break;
    }
    default:
    {
      EXPECT_TRUE (false);

      break;
    }
  }

  REngine::Core::Windows::ComPtr<IDerived> derived;
  ASSERT_NE (nullptr, &derived);
  switch (auto result = base->QueryInterface<IDerived> (&derived); result)
  {
    case S_OK:
    {
      EXPECT_EQ (IBaseMethodValue, derived->IBaseMethod ());
      EXPECT_EQ (IDerivedMethodValue, derived->IDerivedMethod ());

      break;
    }
    case E_INVALIDARG:
    {
      EXPECT_TRUE (false);

      break;
    }
    case E_OUTOFMEMORY:
    {
      EXPECT_TRUE (false);

      break;
    }
    default:
    {
      EXPECT_TRUE (false);

      break;
    }
  }
}

TEST (ComPtr, Methods)
{
  REngine::Core::Windows::ComPtr<IBase> base1;
  ASSERT_EQ (nullptr, base1.Get ());
  // Test address of internal pointer
  ASSERT_NE (nullptr, base1.GetAddressOf ());
  ASSERT_NE (nullptr, &base1);
  ASSERT_EQ (base1.GetAddressOf (), &base1);

  CreateDerivedObject (&base1);
  ASSERT_TRUE (base1);

  auto base1Ptr = base1.Get ();
  base1Ptr->AddRef ();

  // Release ();
  auto ptr = base1.Release ();
  ptr->AddRef ();
  ASSERT_EQ (base1Ptr, ptr);
  ASSERT_FALSE (base1);
  ptr->Release ();
  ptr = nullptr;

  // Reset ();
  CreateDerivedObject (&base1);
  ASSERT_TRUE (base1);
  base1.Reset ();
  ASSERT_FALSE (base1);
  base1.Reset (base1Ptr);
  ASSERT_EQ (base1Ptr, base1.Get ());

  // Swap ();
  REngine::Core::Windows::ComPtr<IBase> base2;
  ASSERT_EQ (nullptr, base2.Get ());

  CreateDerivedObject (&base2);
  ASSERT_TRUE (base2);

  auto base2Ptr = base2.Get ();
  base2Ptr->AddRef ();

  base1.Swap (base2);

  ASSERT_EQ (base2Ptr, base1.Get ());
  ASSERT_EQ (base1Ptr, base2.Get ());

  base2Ptr->Release ();
  base2Ptr = nullptr;

  // Finalize
  base1Ptr->Release ();
  base1Ptr = nullptr;
}

TEST (ComPtr, Methods_GetAs)
{
  // GetAs ();
  REngine::Core::Windows::ComPtr<IBase> base;
  ASSERT_EQ (nullptr, base.Get ());
  // Test address of internal pointer
  ASSERT_NE (nullptr, base.GetAddressOf ());
  ASSERT_NE (nullptr, &base);
  ASSERT_EQ (base.GetAddressOf (), &base);

  CreateDerivedObject (&base);
  ASSERT_TRUE (base);

  REngine::Core::Windows::ComPtr<IFeature> feature;
  switch (auto result = base.GetAs (feature); result)
  {
    case S_OK:
    {
      ASSERT_NE (nullptr, feature.Get ());
      EXPECT_EQ (IFeatureMethodValue, feature->IFeatureMethod ());

      break;
    }
    case E_INVALIDARG:
    {
      EXPECT_TRUE (false);

      break;
    }
    case E_OUTOFMEMORY:
    {
      EXPECT_TRUE (false);

      break;
    }
    default:
    {
      EXPECT_TRUE (false);

      break;
    }
  }

  if (auto feature = base.GetAs<IFeature> (); feature)
  {
    ASSERT_NE (nullptr, feature.Get ());
    EXPECT_EQ (IFeatureMethodValue, feature->IFeatureMethod ());
  }
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
