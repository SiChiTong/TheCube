////////////////////////////////////////////////////////////////////////////////
#include "Application.hpp"
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// REngine Base
////////////////////////////////////////////////////////////////////////////////
#include <REngine/Core/ReCoreBase>
////////////////////////////////////////////////////////////////////////////////
// REngine Library
////////////////////////////////////////////////////////////////////////////////
#include <REngine/Core/ReDynamicLibrary>
#include <REngine/GfxRenderers/ReIGfxRenderer>
////////////////////////////////////////////////////////////////////////////////
// System headers
////////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////
// C++ Standard Library
////////////////////////////////////////////////////////////////////////////////
#include <sstream>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_BEGIN (REngine)
////////////////////////////////////////////////////////////////////////////////

void
  Application::Initialize ()
{
  Core::DynamicLibrary dynamicLibrary{ "GfxRenderer_D3D12" };
  dynamicLibrary.Load ();

  auto CreateGfxRenderer =
    dynamicLibrary.ResolveSymbol<CreateGfxRenderer_funcType> (
      "CreateGfxRenderer");
  auto DestroyGfxRenderer =
    dynamicLibrary.ResolveSymbol<DestroyGfxRenderer_funcType> (
      "DestroyGfxRenderer");
  auto GetIntefaceName =
    dynamicLibrary.ResolveSymbol<GetInterfaceName_funcType> (
      "GetInterfaceName");
  auto GetIntefaceVersion =
    dynamicLibrary.ResolveSymbol<GetInterfaceVersion_funcType> (
      "GetInterfaceVersion");

  this->gfxRenderer =
    reinterpret_cast<GfxRenderers::IGfxRenderer*> (CreateGfxRenderer ());

  std::wstringstream ss;
  ss << gfxRenderer->GetName ().c_str ();
  auto [major, minor] = gfxRenderer->GetVersion ();
  ss << " version " << major << "." << minor << "\n";

  OutputDebugString (ss.str ().c_str ());

  DestroyGfxRenderer (reinterpret_cast<void**> (&this->gfxRenderer));
}

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_END (REngine)
////////////////////////////////////////////////////////////////////////////////
