////////////////////////////////////////////////////////////////////////////////
#include "ComInterfaces.hpp"
////////////////////////////////////////////////////////////////////////////////
#include <REngine/Core/ReCoreBase>
////////////////////////////////////////////////////////////////////////////////

extern "C" const IID IID_IBase = __uuidof(IBase);
extern "C" const IID IID_IDerived = __uuidof(IDerived);
extern "C" const IID IID_IFeature = __uuidof(IFeature);

class Derived
  : public IDerived
  , public IFeature
{
 public:
  // IBase
  auto IBaseMethod () -> int final;

  // IDerived
  auto IDerivedMethod () -> int final;

  // IFeature
  auto IFeatureMethod () -> int final;

  // IUnknown
  auto AddRef () -> ULONG final;
  auto Release () -> ULONG final;
  auto QueryInterface (REFIID riid, LPVOID* ppvObject) -> HRESULT final;

 private:
  // Reference counter value
  long referenceCount = 0;
  // Properties
  int baseValue = IBaseMethodValue;
  int derivedValue = IDerivedMethodValue;
  int featureValue = IFeatureMethodValue;
};

// Inherited methods - IBase

auto
  Derived::IBaseMethod () -> int
{
  return this->baseValue;
}

// Inherited methods - IDerived

auto
  Derived::IDerivedMethod () -> int
{
  return this->derivedValue;
}

// Inherited methods - IFeature

auto
  Derived::IFeatureMethod () -> int
{
  return this->featureValue;
}

// Inherited methods - IUnknown

unsigned long
  Derived::AddRef ()
{
  return InterlockedIncrement (&this->referenceCount);
}

unsigned long
  Derived::Release ()
{
  // Decrement the object's internal counter
  auto referenceCount = InterlockedDecrement (&this->referenceCount);
  if (0 == referenceCount)
  {
    delete this;
  }

  return referenceCount;
}

auto
  Derived::QueryInterface (REFIID riid, LPVOID* ppvObject) -> HRESULT
{
  reAssert (nullptr != ppvObject);

  // Always set out parameter to NULL, validating it first.
  if (nullptr == ppvObject)
  {
    return E_INVALIDARG;
  }

  *ppvObject = NULL;

  if ((riid == IID_IDerived) || (riid == IID_IBase) || (riid == IID_IUnknown))
  {
    // Increment the reference count and return the pointer.
    *ppvObject = static_cast<IDerived*> (this);

    this->AddRef ();

    return NOERROR;
  }
  else if (riid == IID_IFeature)
  {
    *ppvObject = static_cast<IFeature*> (this);

    this->AddRef ();

    return NOERROR;
  }

  return E_NOINTERFACE;
}

////////////////////////////////////////////////////////////////////////////////
// Factory function
////////////////////////////////////////////////////////////////////////////////

auto
  CreateDerivedObject (IBase** derived) -> HRESULT
{
  reVerify (nullptr != derived);

  *derived = new (std::nothrow) Derived;
  if (nullptr == *derived)
  {
    return E_OUTOFMEMORY;
  }

  (*derived)->AddRef ();

  return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
