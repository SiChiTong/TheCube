#pragma once

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_BEGIN (REngine::Core::Platforms::Windows)
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// class ObjectHandle
////////////////////////////////////////////////////////////////////////////////

// Constructors
template <typename ObjectHandleType>
ObjectHandle<ObjectHandleType>::ObjectHandle (
  typename ObjectHandle::HandleType handle)
  : handle{ handle }
{}

template <typename ObjectHandleType>
ObjectHandle<ObjectHandleType>::ObjectHandle (ObjectHandle&& other)
  : handle{ other.Release () }
{}

// Destructor
template <typename ObjectHandleType>
ObjectHandle<ObjectHandleType>::~ObjectHandle ()
{
  this->Close ();
}

// Copy & move assignment operators
template <typename ObjectHandleType>
inline ObjectHandle<ObjectHandleType>&
  ObjectHandle<ObjectHandleType>::operator= (ObjectHandle&& other)
{
  if (nullptr != other.handle)
  {
    this->handle = other.Release ();

    return *this;
  }
}

// Public methods
template <typename ObjectHandleType>
inline typename ObjectHandle<ObjectHandleType>::HandleType
  ObjectHandle<ObjectHandleType>::Get ()
{
  return handle;
}

template <typename ObjectHandleType>
inline typename ObjectHandle<ObjectHandleType>::HandleType
  ObjectHandle<ObjectHandleType>::Release ()
{
  HandleType handle = this->handle;
  this->handle = ObjectHandleType::InvalidHandle ();

  return handle;
}

template <typename ObjectHandleType>
inline void
  ObjectHandle<ObjectHandleType>::Reset (HandleType handle)
{
  this->Close ();
  this->handle = handle;
}

// Private methods
template <typename ObjectHandleTraits>
inline void
  ObjectHandle<ObjectHandleTraits>::Close () noexcept
{
  if (ObjectHandleTraits::InvalidHandle () != this->handle)
  {
    ObjectHandleTraits::Close (this->handle);
  }
}

////////////////////////////////////////////////////////////////////////////////
// struct InvalidValueHandleTraits
////////////////////////////////////////////////////////////////////////////////

inline void
  InvalidValueHandleTraits::Close (
    InvalidValueHandleTraits::HandleType handle) noexcept
{
  reVerify (CloseHandle (handle));
}

inline InvalidValueHandleTraits::HandleType
  InvalidValueHandleTraits::InvalidHandle () noexcept
{
  return INVALID_HANDLE_VALUE;
}

////////////////////////////////////////////////////////////////////////////////
// struct NullPtrHandleTraits
////////////////////////////////////////////////////////////////////////////////

inline void
  NullptrHandleTraits::Close (NullptrHandleTraits::HandleType handle) noexcept
{
  reVerify (CloseHandle (handle));
}

inline NullptrHandleTraits::HandleType
  NullptrHandleTraits::InvalidHandle () noexcept
{
  return nullptr;
}

////////////////////////////////////////////////////////////////////////////////
// struct WindowHandleTraits
////////////////////////////////////////////////////////////////////////////////

inline void
  WindowHandleTraits::Close (WindowHandleTraits::HandleType handle) noexcept
{
  reVerify (DestroyWindow (handle));
}

inline WindowHandleTraits::HandleType
  WindowHandleTraits::InvalidHandle () noexcept
{
  return nullptr;
}

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_END (REngine::Core::Platforms::Windows)
////////////////////////////////////////////////////////////////////////////////
