////////////////////////////////////////////////////////////////////////////////
#include "DynamicLibrary.hpp"
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_BEGIN (REngine::Core)
////////////////////////////////////////////////////////////////////////////////

// Constructors
DynamicLibrary::DynamicLibrary (const char* filename)
{
  this->ptr_ = std::make_unique<Library_Implementation> (filename);
}

DynamicLibrary::DynamicLibrary (const std::string_view& filename)
{
  this->ptr_ = std::make_unique<Library_Implementation> (filename);
}

// Copy & move constructors
DynamicLibrary::DynamicLibrary (DynamicLibrary&& other)
{
  if (!other.IsLoaded ())
  {
    this->ptr_.reset (other.ptr_.release ());
  }
}

// Copy & move assignment operators
DynamicLibrary&
  DynamicLibrary::operator= (DynamicLibrary&& other)
{
  if (!other.IsLoaded ())
  {
    this->ptr_.reset (other.ptr_.release ());
  }

  return *this;
}

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_END (REngine::Core)
////////////////////////////////////////////////////////////////////////////////
