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
  "Platform/Windows/DynamicLibrary_Windows.cpp"
  "Platform/Windows/DynamicLibrary_Windows.hpp"
  "Platform/Windows/ObjectHandle.cpp"
  "Platform/Windows/ObjectHandle.hpp"
  "Platform/Windows/ObjectHandle.inl"
  "Platform/DynamicLibrary_Platform.cpp"
  "Platform/DynamicLibrary_Platform.hpp"
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

################################################################################
# Core_SourceFiles.cmake
################################################################################
