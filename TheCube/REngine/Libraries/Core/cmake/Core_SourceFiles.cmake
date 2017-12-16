################################################################################
include_guard() # Prevent this file from being included more than once
################################################################################

################################################################################
# Core_SourceFiles.cmake
################################################################################

# A list with the Target's source files
re_CreateSourceFilesList (Core_SourceFiles 
  "Sources" HIDE "Source Files"
  # Source files
  "Macros/Debug.cpp"
  "Macros/Debug.hpp"
  "Macros/Utilities.cpp"
  "Macros/Utilities.hpp"
  "Platforms/DynamicLibrary_Platform.cpp"
  "Platforms/DynamicLibrary_Platform.hpp"
  "System/Enums.cpp"
  "System/Enums.hpp"
  "System/Enums.cpp"
  "System/Enums.hpp"
  "Utilities/String.cpp"
  "Utilities/String.hpp"
  "Utilities/String.inl"
  "Utilities/StringView.cpp"
  "Utilities/StringView.hpp"
  "Utilities/StringView.inl"
  "Core.cpp"
  "Core.hpp"
  "DynamicLibrary.cpp"
  "DynamicLibrary.hpp"
  "DynamicLibrary.inl"
  "implementedBy.cpp"
  "implementedBy.hpp"
)

if (re_var_WINDOWS)
  # A list with the Target's source files
  re_AppendToSourceFilesList (Core_SourceFiles 
    "Sources" HIDE "Source Files"
    # Source files
    "Platforms/Windows/ComPtr.cpp"
    "Platforms/Windows/ComPtr.hpp"
    "Platforms/Windows/ComPtr.inl"
    "Platforms/Windows/DynamicLibrary_Windows.cpp"
    "Platforms/Windows/DynamicLibrary_Windows.hpp"
    "Platforms/Windows/DynamicLibrary_Windows.inl"
    "Platforms/Windows/ObjectHandle.cpp"
    "Platforms/Windows/ObjectHandle.hpp"
    "Platforms/Windows/ObjectHandle.inl"
  )
endif ()

################################################################################
# Core_SourceFiles.cmake
################################################################################
