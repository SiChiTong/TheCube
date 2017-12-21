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

// Handle class
template <typename ObjectHandleTraits>
class ObjectHandle
{
  using HandleType = typename ObjectHandleTraits::HandleType;

 public:
  explicit ObjectHandle (
    HandleType handle = ObjectHandleTraits::InvalidHandle ());
  ~ObjectHandle ();

 public:
  ObjectHandle (const ObjectHandle& other) = delete;
  ObjectHandle (ObjectHandle&& other);

 public:
  auto operator= (const ObjectHandle& other) -> const ObjectHandle& = delete;
  auto operator= (ObjectHandle&& other) -> ObjectHandle&;

 public:
  auto Get () -> HandleType;
  auto Release () -> HandleType;
  void Reset (HandleType handle = ObjectHandleTraits::InvalidHandle ());

 private:
  void Close () noexcept;

 private:
  HandleType handle;
};

// Handle traits
struct InvalidValueHandleTraits
{
  using HandleType = HANDLE;

  static void Close (HandleType handle) noexcept;
  static auto InvalidHandle () noexcept -> HandleType;
};

struct NullptrHandleTraits
{
  using HandleType = HANDLE;

  static void Close (HandleType handle) noexcept;
  static auto InvalidHandle () noexcept -> HandleType;
};

struct WindowHandleTraits
{
  using HandleType = HWND;

  static void Close (HandleType handle) noexcept;
  static auto InvalidHandle () noexcept -> HandleType;
};

// Handle types
using NullptrHandle = ObjectHandle<NullptrHandleTraits>;
using InvalidValueHandle = ObjectHandle<InvalidValueHandleTraits>;
using WindowHandle = ObjectHandle<WindowHandleTraits>;

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_END (REngine::Core::Platforms::Windows)
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Inline methods
////////////////////////////////////////////////////////////////////////////////
#include "ObjectHandle.inl"
////////////////////////////////////////////////////////////////////////////////
