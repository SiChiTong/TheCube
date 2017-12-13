################################################################################
include_guard() # Prevent this file from being included more than once
################################################################################

# A list with the Target's source files
re_CreateSourceFilesList (REngine_SourceFiles 
  "Sources" HIDE "Source Files"
  # Source files
  "System/Settings.cpp"
  "System/Settings.hpp"
  "Application.cpp"
  "Application.hpp"
)
