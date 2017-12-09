////////////////////////////////////////////////////////////////////////////////
#include "DynamicLibrary_Windows.hpp"
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C++ Standard Library
////////////////////////////////////////////////////////////////////////////////
#include <sstream>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_BEGIN (REngine::Core)
////////////////////////////////////////////////////////////////////////////////

Library_Implementation_Win::Library_Implementation_Win (
  const std::string_view& filename)
  : libraryHandle{nullptr}
{
  std::stringstream ss;
  ss << "lib" << filename.data () << ".dll";

  this->filename = std::make_unique<REngine::Core::String> (ss.str ());
}

Library_Implementation_Win::~Library_Implementation_Win ()
{
  this->Unload ();
}

const std::string_view
  Library_Implementation_Win::GetFilename () noexcept
{
  return this->filename->c_str ();
}

void
  Library_Implementation_Win::Load () noexcept
{
  if (nullptr == this->libraryHandle)
  {
    this->libraryHandle = LoadLibrary (filename->c_wstr ());
  }
}

bool
  Library_Implementation_Win::Unload () noexcept
{
  auto result = false;
  if (nullptr != this->libraryHandle)
  {
    result = FreeLibrary (this->libraryHandle);
    this->libraryHandle = nullptr;

    return result;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_END (REngine::Core)
////////////////////////////////////////////////////////////////////////////////
