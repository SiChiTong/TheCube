////////////////////////////////////////////////////////////////////////////////
#include "ObjectHandle.hpp"
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_BEGIN (REngine::Core)
////////////////////////////////////////////////////////////////////////////////

// Constructors
template <typename ObjectHandleType>
ObjectHandle<ObjectHandleType>::ObjectHandle (
  typename ObjectHandle::HandleType handle)
  : handle{handle}
{}

// Destructor
template <typename ObjectHandleType>
ObjectHandle<ObjectHandleType>::~ObjectHandle ()
{
  this->Close ();
}

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_END (REngine::Core)
////////////////////////////////////////////////////////////////////////////////
