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
  "Macros/UtilityMacros.cpp"
  "Macros/UtilityMacros.hpp"
  "Platforms/Logger_Platforms.cpp"
  "Platforms/Logger_Platforms.hpp"
  "Utilities/implementedBy.cpp"
  "Utilities/implementedBy.hpp"
  "Logger.cpp"
  "Logger.hpp"
  "Logger.inl"
  "Policy.cpp"
  "Policy.hpp"
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
    "Platforms/Windows/Logger_Windows.cpp"
    "Platforms/Windows/Logger_Windows.hpp"
  )
endif ()

################################################################################
# Logger_SourceFiles.cmake
################################################################################
