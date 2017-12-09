#pragma once

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_BEGIN (REngine::Core)
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// class ObjectHandle
////////////////////////////////////////////////////////////////////////////////

// Methods
template <typename ObjectHandleTraits>
inline void
  ObjectHandle<ObjectHandleTraits>::Close () noexcept
{
  if (nullptr != *this)
  {
    ObjectHandleTraits::Close (this->handle);
  }
}

////////////////////////////////////////////////////////////////////////////////
// ObjectHandleTraits Methods
////////////////////////////////////////////////////////////////////////////////

// struct InvalidValueHandleTraits
inline void
  InvalidValueHandleTraits::Close (
    InvalidValueHandleTraits::HandleType handle) noexcept
{
  reVerify (CloseHandle (handle));
}

inline NullptrHandleTraits::HandleType
  InvalidValueHandleTraits::Invalid () noexcept
{
  return INVALID_HANDLE_VALUE;
}

// struct NullPtrHandleTraits
inline void
  NullptrHandleTraits::Close (NullptrHandleTraits::HandleType handle) noexcept
{
  reVerify (CloseHandle (handle));
}

inline NullptrHandleTraits::HandleType
  NullptrHandleTraits::Invalid () noexcept
{
  return nullptr;
}

// struct WindowHandleTraits
inline void
  WindowHandleTraits::Close (WindowHandleTraits::HandleType handle) noexcept
{
  reVerify (DestroyWindow (handle));
}

inline WindowHandleTraits::HandleType
  WindowHandleTraits::Invalid () noexcept
{
  return nullptr;
}

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_END (REngine::Core)
////////////////////////////////////////////////////////////////////////////////
