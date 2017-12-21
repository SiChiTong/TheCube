#pragma once

#include "ComPtr.hpp"
#include <utility>

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_BEGIN (REngine::Core::Platforms::Windows)
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// class ComPtr_
////////////////////////////////////////////////////////////////////////////////

template <typename I>
template <typename I_>
template <typename M>
inline unsigned long
  ComPtr<I>::ComPtr_<I_>::AddRef ()
{
  static_assert (false,
                 "Use of member function 'unsigned long __stdcall AddRef ()' "
                 "is disallowed.");
};

template <typename I>
template <typename I_>
template <typename M>
inline unsigned long
  ComPtr<I>::ComPtr_<I_>::Release ()
{
  static_assert (false,
                 "Use of member function 'unsigned long __stdcall Release ()' "
                 "is disallowed.");
};

////////////////////////////////////////////////////////////////////////////////
// class ComPtr
////////////////////////////////////////////////////////////////////////////////

// Constructors

// Destructor
template <typename I>
ComPtr<I>::~ComPtr ()
{
  if (nullptr != this->ptr_)
  {
    this->IRelease ();
  }
}

// Copy & move constructors
template <typename I>
ComPtr<I>::ComPtr (const ComPtr& other) noexcept
{
  this->ICopy (other);
}

template <typename I>
template <typename I_>
ComPtr<I>::ComPtr (const ComPtr<I_>& other) noexcept
  : ptr_{ other.ptr_ }
{
  // Cannot use this->ICopy() due to -> warning C4717: 'function': recursive on
  // all control paths, function will cause runtime stack overflow
  this->IAddRef ();
}

template <typename I>
template <typename I_>
ComPtr<I>::ComPtr (ComPtr<I_>&& other) noexcept
  : ptr_{ other.ptr_ }
{
  // Cannot use this->IMove() due to -> warning C4717: 'function': recursive on
  // all control paths, function will cause runtime stack overflow
  other.ptr_ = nullptr;
}

// Copy & move assignment operators
template <typename I>
inline ComPtr<I>&
  ComPtr<I>::operator= (const ComPtr& other) noexcept
{
  this->ICopy (other);

  return *this;
}

template <typename I>
template <typename I_>
inline ComPtr<I>&
  ComPtr<I>::operator= (const ComPtr<I_>& other) noexcept
{
  this->ICopy (other);

  return *this;
}

template <typename I>
template <typename I_>
inline ComPtr<I>&
  ComPtr<I>::operator= (ComPtr<I_>&& other) noexcept
{
  this->IMove (std::move (other));

  return *this;
}

template <typename I>
inline auto
  ComPtr<I>::Get () const noexcept -> I*
{
  return this->ptr_;
}

// Public methods
template <typename I>
inline I**
  ComPtr<I>::GetAddressOf () noexcept
{
  return this->IGetAddressOf ();
}

template <typename I>
template <typename I_>
inline ComPtr<I_>
  ComPtr<I>::GetAs () noexcept
{
  ComPtr<I_> ptr;
  this->GetAs (ptr);

  return ptr;
}

template <typename I>
template <typename I_>
inline HRESULT
  ComPtr<I>::GetAs (ComPtr<I_>& other) noexcept
{
  return this->ptr_->QueryInterface (&other);
}

template <typename I>
inline I*
  ComPtr<I>::Release () noexcept
{
  auto ptr = this->ptr_;
  this->IRelease ();

  return ptr;
}

template <typename I>
inline void
  ComPtr<I>::Reset (I* ptr) noexcept
{
  this->IRelease ();

  reAssert (nullptr == this->ptr_);

  this->ptr_ = ptr;
  this->IAddRef ();
}

template <typename I>
inline void
  ComPtr<I>::Swap (ComPtr& other) noexcept
{
  std::swap (this->ptr_, other.ptr_);
}

// Public operators
template <typename I>
inline ComPtr<I>::ComPtr_<I>* ComPtr<I>::operator-> () const noexcept
{
  return static_cast<ComPtr_<I>*> (this->ptr_);
};

template <typename I>
inline I** ComPtr<I>::operator& () noexcept
{
  return this->IGetAddressOf ();
}

template <typename I>
inline ComPtr<I>::operator bool () const noexcept
{
  return (nullptr != this->ptr_);
}

// Private methods
template <typename I>
inline void
  ComPtr<I>::IAddRef () noexcept
{
  if (nullptr != ptr_)
  {
    this->ptr_->AddRef ();
  }
}

template <typename I>
inline void
  ComPtr<I>::ICopy (const ComPtr& other) noexcept
{
  if (this->ptr_ != other.ptr_)
  {
    this->IRelease ();
    reVerify (nullptr == this->ptr_);
    this->ptr_ = other.ptr_;
    this->IAddRef ();
  }
}

template <typename I>
inline auto
  ComPtr<I>::IGetAddressOf () noexcept -> I**
{
  reAssert (nullptr == this->ptr_);

  return &(this->ptr_);
}

template <typename I>
inline void
  ComPtr<I>::IMove (ComPtr&& other) noexcept
{
  if (this->ptr_ != other.ptr_)
  {
    this->IRelease ();
    reVerify (nullptr == this->ptr_);
    this->ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }
}

template <typename I>
inline void
  ComPtr<I>::IRelease () noexcept
{
  auto ptr = this->ptr_;
  if (nullptr != ptr)
  {
    // Detach the interface pointer from ComPtr before calling Release () on
    // the interface to avoid possible bugs if Release () gets invoked multiple
    // times
    this->ptr_ = nullptr;
    ptr->Release ();
  }
}

////////////////////////////////////////////////////////////////////////////////
// Free functions - ComPtr
////////////////////////////////////////////////////////////////////////////////

template <typename I>
inline void
  swap (ComPtr<I>& lhs, ComPtr<I>& rhs)
{
  lhs.Swap (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Free operators - ComPtr
////////////////////////////////////////////////////////////////////////////////

template <typename I>
inline auto
  operator== (const ComPtr<I>& lhs, const ComPtr<I>& rhs) -> bool
{
  return (lhs.Get () == rhs.Get ());
}

template <typename I>
inline auto
  operator!= (const ComPtr<I>& lhs, const ComPtr<I>& rhs) -> bool
{
  return (lhs.Get () != rhs.Get ());
}

////////////////////////////////////////////////////////////////////////////////
// Free functions - COM
////////////////////////////////////////////////////////////////////////////////

template <typename I>
inline void
  ReleaseComInterface (I*& ptr)
{
  if (nullptr != ptr)
  {
    ptr->Release ();
    ptr = nullptr;
  }
}

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_END (REngine::Core::Platforms::Windows)
////////////////////////////////////////////////////////////////////////////////
