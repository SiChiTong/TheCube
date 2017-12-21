#pragma once

////////////////////////////////////////////////////////////////////////////////
// REngine Base
////////////////////////////////////////////////////////////////////////////////
#include <REngine/Core/ReCoreBase>
////////////////////////////////////////////////////////////////////////////////
// System headers
////////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_BEGIN (REngine::Core::Platforms::Windows)
////////////////////////////////////////////////////////////////////////////////

template <typename I>
class ComPtr
{
  // Hide virtual functions
  template <typename I_>
  struct ComPtr_ : public I_
  {
    // ERROR: Use of member function 'unsigned long __stdcall AddRef ()' is
    // disallowed.
    template <typename M = bool>
    auto __stdcall AddRef () -> unsigned long;
    // ERROR: Use of member function 'unsigned long __stdcall Release ()' is
    // disallowed.
    template <typename M = bool>
    auto __stdcall Release () -> unsigned long;
  };

 public:
  ComPtr () = default;
  ~ComPtr ();

 public:
  ComPtr (const ComPtr& other) noexcept;
  template <typename I_>
  ComPtr (const ComPtr<I_>& other) noexcept;
  template <typename I_>
  ComPtr (ComPtr<I_>&& other) noexcept;

 public:
  auto operator= (const ComPtr& other) noexcept -> ComPtr&;
  template <typename I_>
  auto operator= (const ComPtr<I_>& other) noexcept -> ComPtr&;
  template <typename I_>
  auto operator= (ComPtr<I_>&& other) noexcept -> ComPtr&;

  template <typename I_>
  friend class ComPtr;

 public:
  // Returns an object of the requested interface if supported (see auto GetAs
  // (ComPtr<I_>& other) noexcept -> HRESULT)
  template <typename I_>
  auto GetAs () noexcept -> ComPtr<I_>;
  // Returns an object of the requested interface if supported (see auto GetAs
  // () noexcept -> ComPtr<I_>)
  template <typename I_>
  auto GetAs (ComPtr<I_>& other) noexcept -> HRESULT;
  // Returns the interface pointer
  auto Get () const noexcept -> I*;
  // Returns the address of the interface pointer (see auto operator& ()
  // noexcept -> I**)
  auto GetAddressOf () noexcept -> I**;
  // Releases the interface pointer
  auto Release () noexcept -> I*;
  // Replaces the interface pointer
  void Reset (I* ptr = nullptr) noexcept;
  // Swaps the interface pointers of both ComPtr objects
  void Swap (ComPtr& other) noexcept;

 public:
  // Class dereference operator
  auto operator-> () const noexcept -> ComPtr_<I>*;
  // Returns the address of the interface pointer (see auto GetAddressOf ()
  // noexcept -> I**)
  auto operator& () noexcept -> I**;
  // Returns true if the smart pointer object holds a valid interface pointer
  explicit operator bool () const noexcept;

 private:
  void IAddRef () noexcept;
  void ICopy (const ComPtr& other) noexcept;
  auto IGetAddressOf () noexcept -> I**;
  void IMove (ComPtr&& other) noexcept;
  void IRelease () noexcept;

 private:
  I* ptr_ = nullptr;
};

////////////////////////////////////////////////////////////////////////////////
// Free functions - ComPtr
////////////////////////////////////////////////////////////////////////////////

// Returns true if both 'ComPtr's point to the same COM interface object
template <typename I>
void
  swap (ComPtr<I>& lhs, ComPtr<I>& rhs);

////////////////////////////////////////////////////////////////////////////////
// Free operators - ComPtr
////////////////////////////////////////////////////////////////////////////////

// Returns true if both 'ComPtr's point to the same COM interface object
template <typename I>
auto
  operator== (const ComPtr<I>& lhs, const ComPtr<I>& rhs) -> bool;

// Returns true if both 'ComPtr's point to different COM interface objects
template <typename I>
auto
  operator!= (const ComPtr<I>& lhs, const ComPtr<I>& rhs) -> bool;

////////////////////////////////////////////////////////////////////////////////
// Free functions - COM
////////////////////////////////////////////////////////////////////////////////

// Releases the COM interface and sets the pointer 'nullptr'
template <typename I>
void
  ReleaseComInterface (I*& ptr);

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_END (REngine::Core::Platforms::Windows)
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Inline methods
////////////////////////////////////////////////////////////////////////////////
#include "ComPtr.inl"
////////////////////////////////////////////////////////////////////////////////
