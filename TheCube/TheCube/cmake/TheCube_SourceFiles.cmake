################################################################################
include_guard() # Prevent this file from being included more than once
################################################################################

# A list with the Target's source files
re_CreateSourceFilesList (TheCube_SourceFiles
  "Sources" HIDE "Source Files"
  # Source files
  "TheCube.cpp"
  "TheCube.hpp"
)

# A list with the Target's manifest and resource files 
# (appended to the Target's source files list)
re_AppendToSourceFilesList (TheCube_SourceFiles
  "Resources" HIDE "Resource Files"
  # Source files
  "Windows/DpiAwareness.manifest"
)

# Conditionally append a manifest file to the Target's source files list
if (option_Executable_EnableRequireAdministrator)
  re_AppendToSourceFilesList (TheCube_SourceFiles
    "Resources" HIDE "Resource Files"
    # Source files
    "Windows/RequireAdministrator.manifest"
  )
endif ()
