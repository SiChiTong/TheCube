################################################################################
# Subproject: Logger (private REngine)
################################################################################

################################################################################
cmake_minimum_required (VERSION 3.9.0)
################################################################################

################################################################################
# Subproject variables
################################################################################
set (SubprojectName "Logger")
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
set (Library_REngine_${SubprojectName} "${LibraryName}")
set (Library_REngine_${SubprojectName} "${LibraryName}" PARENT_SCOPE)
################################################################################
# Include the source files
include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/${SubprojectName}_SourceFiles.cmake)

# Define the target
add_library ("${Library_REngine_${SubprojectName}}" STATIC
  ${${SubprojectName}_SourceFiles}
)
# Add to a project folder for generators that support this feature
set_target_properties ("${Library_REngine_${SubprojectName}}"
  PROPERTIES FOLDER
    "${ProjectFolder_Libraries}"
)

if (re_var_WINDOWS_MSVC_CLANG)
  # This librabry contains empty *.cpp!
  # Suppress warning LNK4221: This object file does not define any previously
  # undefined public symbols, so it will not be used by any link operation that
  # consumes this library 
  set (CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} /IGNORE:4221")
endif ()

# Link libraries
target_link_libraries ("${Library_REngine_${SubprojectName}}"
  PUBLIC
    "${Library_REngine_Base}"
)
################################################################################
