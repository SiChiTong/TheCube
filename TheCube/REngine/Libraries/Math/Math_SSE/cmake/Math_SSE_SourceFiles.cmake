################################################################################
include_guard() # Prevent this file from being included more than once
################################################################################

################################################################################
# OpenGL_SourceFiles.cmake
################################################################################

# A list with the Target's source files
re_CreateSourceFilesList (Math_SSE_SourceFiles 
  "Sources" HIDE "Source Files"
  # Source files
  "Matrix.cpp"
  "Vector.cpp"
)

# Common headers
re_AppendToSourceFilesList (Math_SSE_SourceFiles
  "../Common" HIDE "Header Files"
  # Source files
  "Matrix.hpp"
  "Vector.hpp"
)

################################################################################
# OpenGL_SourceFiles.cmake
################################################################################
