////////////////////////////////////////////////////////////////////////////////
#include "GfxRenderer.hpp"
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
NAMESPACE_BEGIN (REngine::GfxRenderers)
////////////////////////////////////////////////////////////////////////////////

GfxRenderer::GfxRenderer ()
{
  this->name = "D3D 12 Renderer";
  this->version = std::make_pair<int, int> (1, 1);
}

GfxRenderer::~GfxRenderer ()
{
  this->name = "D3D 12 Renderer";
  this->version = std::make_pair<int, int> (1, 1);
}

void 
GfxRenderer::Render()
{
}

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_END (REngine::GfxRenderers)
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Exported C function definitions
////////////////////////////////////////////////////////////////////////////////

extern "C"
{
  void*
  CreateGfxRenderer ()
  {
    return new REngine::GfxRenderers::GfxRenderer ();
  }

  void
  DestroyGfxRenderer (void** ptr)
  {
    delete reinterpret_cast<REngine::GfxRenderers::GfxRenderer*> (*ptr);
    // A pointer is passed by value thus pointer to pointer is required
    *ptr = nullptr;
  }
}

////////////////////////////////////////////////////////////////////////////////
