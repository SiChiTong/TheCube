################################################################################
# Subproject: Core (private REngine)
################################################################################

################################################################################
cmake_minimum_required (VERSION 3.9.0)
################################################################################

################################################################################
# Subproject variables
################################################################################
set (SubprojectName "Core")
set (SubprojectVersion "0.1.0.0") # MAJOR.MINOR.PATCH.TWEAK
################################################################################
re_LogSection (PREFIX "${SubprojectName}"
  "${SubprojectVersion} is being configured now..."
)
################################################################################

################################################################################
# Library target
################################################################################
# Create the library name
if (re_var_WINDOWS_MSVC OR re_var_WINDOWS_MSVC_CLANG)
  # Add the "lib" prefix to the library name on Windows
  set (LibraryName "lib${SubprojectName}")
else ()
  set (LibraryName "${SubprojectName}")
endif ()
set (Library_REngine_Core "${LibraryName}")
set (Library_REngine_Core "${LibraryName}" PARENT_SCOPE)
################################################################################
# Include the source files
include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/Core_SourceFiles.cmake)

# Define the target
add_library ("${Library_REngine_Core}" STATIC
  ${Core_SourceFiles}
)
# Add to a project folder for generators that support this feature
set_target_properties ("${Library_REngine_Core}"
  PROPERTIES FOLDER
    "${ProjectFolder_Libraries}"
)

# Header files
target_include_directories ("${Library_REngine_Core}"
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/Sources"
)

if (re_var_WINDOWS_MSVC_CLANG)
  # This librabry contains empty *.cpp!
  # Suppress warning LNK4221: This object file does not define any previously
  # undefined public symbols, so it will not be used by any link operation that
  # consumes this library 
  set (CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} /IGNORE:4221")
endif ()

# Link libraries
target_link_libraries ("${Library_REngine_Core}"
  PUBLIC
    "${Library_REngine_Base}"
)
################################################################################

################################################################################
# Unit tests
################################################################################
add_subdirectory ("Tests")
################################################################################
