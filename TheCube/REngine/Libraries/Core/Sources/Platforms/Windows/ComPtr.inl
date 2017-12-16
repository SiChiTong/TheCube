#pragma once

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_BEGIN (REngine::Core::Windows)
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
  if (nullptr != ptr_)
  {
    ptr_->Release ();
  }
}

// Copy & move constructors
template <typename I>
ComPtr<I>::ComPtr (const ComPtr& other) noexcept
  : ptr_ { other.ptr_ }
{
  this->AddRef ();
}

template <typename I>
template <typename I_>
ComPtr<I>::ComPtr (const ComPtr<I_>& other) noexcept
  : ptr_{ other.ptr_ }
{
  this->AddRef ();
}

template <typename I>
ComPtr<I>::ComPtr (ComPtr<I>&& other) noexcept
  : ptr_{ other.ptr_ }
{
  other.ptr_ = nullptr;
}

// Copy & move assignment operators
template <typename I>
template <typename I_>
ComPtr<I>&
  ComPtr<I>::operator= (const ComPtr<I_>& other) noexcept
{
  if (nullptr != this->ptr_)
  {
    this->Release ();
  }

  this->ptr_ = other->ptr_;
  this->AddRef ();
}

template <typename I>
ComPtr<I>&
  ComPtr<I>::operator= (ComPtr&& other) noexcept
{
  if (nullptr != this->ptr_)
  {
    this->Release ();
  }

  this->ptr_ = other->ptr_;
  other->ptr_ = nullptr;
}

// Operators
template <typename I>
ComPtr<I>::ComPtr_<I>* ComPtr<I>::operator-> () const noexcept
{
  return static_cast<ComPtr_<I>*> (this->ptr_);
};

// Public methods
template <typename I>
I*
  ComPtr<I>::Release () noexcept
{
  this->Release ();

  return this->ptr_;
}

template <typename I>
void
  ComPtr<I>::Reset (I* ptr) noexcept
{
  this->Release ();
  this->ptr_ = ptr;
  this->AddRef ();
}

// Private methods
template <typename I>
void
  ComPtr<I>::AddRef () noexcept
{
  if (nullptr != ptr_)
  {
    this->ptr_->AddRef ();
  }
}

template <typename I>
void
  ComPtr<I>::Release () noexcept
{
  auto ptr = this->ptr_;
  if (nullptr != ptr)
  {
    // Detach the interface pointer from ComPtr befeore calling Release () on
    // the interface.
    this->ptr_ = nullptr;
    ptr->Release ();
  }
}

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_END (REngine::Core::Windows)
////////////////////////////////////////////////////////////////////////////////
