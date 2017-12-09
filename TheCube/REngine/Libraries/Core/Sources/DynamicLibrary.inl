#pragma once

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_BEGIN (REngine::Core)
////////////////////////////////////////////////////////////////////////////////

// Methods
inline const std::string_view
  DynamicLibrary::GetFilename () noexcept
{
  _ASSERTE (nullptr != ptr_);

  return this->ptr_->GetFilename ();
}

inline bool
  DynamicLibrary::IsLoaded () noexcept
{
  return (nullptr == this->ptr_);
}

inline void
  DynamicLibrary::Load ()
{
  this->ptr_->Load ();
}

inline bool
  DynamicLibrary::Unload ()
{
  return this->ptr_->Unload ();
}

// Templated methods
template <typename FuncType>
inline std::function<FuncType>
  DynamicLibrary::ResolveSymbol (const std::string_view& symbol)
{
  return this->ptr_->ResolveSymbol<FuncType> (symbol);
}

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_END (REngine::Core)
////////////////////////////////////////////////////////////////////////////////
