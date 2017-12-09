################################################################################
include_guard() # Prevent this file from being included more than once
################################################################################

################################################################################
# OpenGL
################################################################################

################################################################################
# GfxRenderer_SourceFiles.cmake
################################################################################

# A list with the Target's source files
re_CreateSourceFilesList (GfxRenderer_SourceFiles 
  "Sources" HIDE "Source Files"
  # Source files
  "GfxRenderer.cpp"
)

# Common headers
re_AppendToSourceFilesList (GfxRenderer_SourceFiles
  "../Common" HIDE "Header Files"
  # Source files
  "IGfxRenderer.hpp"
)

################################################################################
# GfxRenderer_SourceFiles.cmake
################################################################################
