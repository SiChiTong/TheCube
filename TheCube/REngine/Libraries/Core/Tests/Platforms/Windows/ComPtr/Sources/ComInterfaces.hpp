////////////////////////////////////////////////////////////////////////////////
// Windows System headers
////////////////////////////////////////////////////////////////////////////////
#include <combaseapi.h>
////////////////////////////////////////////////////////////////////////////////

#if !defined(_WIN64)
#  error Only 64-bit platforms are not supported
#endif // !defined (_WIN64)

////////////////////////////////////////////////////////////////////////////////
// Interface helper macros
////////////////////////////////////////////////////////////////////////////////

#if !defined(COM_INTERFACE)
#  define COM_INTERFACE(__com_interface__, __base_com_interface__, __uuid__)   \
    interface __declspec(uuid (__uuid__)) __com_interface__                    \
      : __base_com_interface__
#endif // !defined (COM_INTERFACE)

////////////////////////////////////////////////////////////////////////////////
// COM interfaces
////////////////////////////////////////////////////////////////////////////////

#define IBaseMethodValue 5
extern "C" const IID IID_IBase;
COM_INTERFACE (IBase, IUnknown, "{BF4BEA56-405B-4AA6-946B-D5FA2FDF0DC6}")
{
  // Returns 'IBaseMethodValue'
  virtual auto IBaseMethod ()->int = 0;
};

#define IDerivedMethodValue 10
extern "C" const IID IID_IDerived;
COM_INTERFACE (IDerived, IBase, "{990679A6-79E7-4CA0-953E-E4C18A1FBE79}")
{
  // Returns 'IDerivedMethodValue'
  virtual auto IDerivedMethod ()->int = 0;
};

#define IFeatureMethodValue 15
extern "C" const IID IID_Feature;
COM_INTERFACE (IFeature, IUnknown, "{2346D795-C99D-458D-B7B1-BE8F0AFC6907}")
{
  // Returns 'IFeatureMethodValue'
  virtual auto IFeatureMethod ()->int = 0;
};

////////////////////////////////////////////////////////////////////////////////
// Factory functions
////////////////////////////////////////////////////////////////////////////////

auto
  CreateDerivedObject (IBase** derived) -> HRESULT;

////////////////////////////////////////////////////////////////////////////////
