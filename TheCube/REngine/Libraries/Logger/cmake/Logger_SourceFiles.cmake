################################################################################
include_guard() # Prevent this file from being included more than once
################################################################################

################################################################################
# Logger_SourceFiles.cmake
################################################################################

# A list with the Target's source files
re_CreateSourceFilesList (${SubprojectName}_SourceFiles 
  "Sources" HIDE "Source Files"
  # Source files
  "Logger.cpp"
  "Logger.hpp"
)

if (re_var_WINDOWS)
  # A list with the Target's source files
  re_AppendToSourceFilesList (${SubprojectName}_SourceFiles 
    "include" HIDE "Include"
    # Source files
    "Logger"
  )
endif ()

if (re_var_WINDOWS)
  # A list with the Target's source files
  re_AppendToSourceFilesList (${SubprojectName}_SourceFiles 
    "Sources" HIDE "Source Files"
    # Source files
  )
endif ()

################################################################################
# Logger_SourceFiles.cmake
################################################################################
