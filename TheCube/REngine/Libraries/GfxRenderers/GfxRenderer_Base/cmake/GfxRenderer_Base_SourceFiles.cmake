################################################################################
include_guard() # Prevent this file from being included more than once
################################################################################

################################################################################
# GfxRenderer_Base_SourceFiles.cmake
################################################################################

# A list with the Target's source files
re_CreateSourceFilesList (GfxRenderer_Base_SourceFiles 
  "Sources" HIDE "Source Files"
  # Source files
  "IGfxRenderer.cpp"
)

# Common headers
re_AppendToSourceFilesList (GfxRenderer_Base_SourceFiles
  "../Common" HIDE "Header Files"
  # Source files
  "IGfxRenderer.hpp"
)

################################################################################
# GfxRenderer_Base_SourceFiles.cmake
################################################################################
