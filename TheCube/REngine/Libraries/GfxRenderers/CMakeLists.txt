# Graphics Renderers

set (SubprojectFolder "${ProjectFolder_Libraries}/GfxRenderers")

add_subdirectory ("GfxRenderer_Base")
if (re_var_WINDOWS)
  add_subdirectory ("GfxRenderer_D3D12")
endif ()
if (re_var_WINDOWS_DESKTOP)
  add_subdirectory ("GfxRenderer_OpenGL")
endif ()
if (re_var_WINDOWS_DESKTOP)
  add_subdirectory ("GfxRenderer_Vulkan")
endif ()
