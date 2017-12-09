# Graphics Renderers

set (SubprojectFolder "${ProjectFolder_Libraries}/GfxRenderers")

add_subdirectory (GfxRenderer_Base)
add_subdirectory (GfxRenderer_D3D12)
add_subdirectory (GfxRenderer_OpenGL)
add_subdirectory (GfxRenderer_Vulkan)
