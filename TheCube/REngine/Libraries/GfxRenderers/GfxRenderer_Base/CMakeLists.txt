################################################################################
# Subproject: GfxRenderer_Base (private REngine)
################################################################################

################################################################################
cmake_minimum_required (VERSION 3.9.0 FATAL_ERROR)
################################################################################

################################################################################
# Subproject variables
################################################################################
set (SubprojectName "GfxRenderer_Base")
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
set (Library_REngine_GfxRenderer_Base "${LibraryName}")
set (Library_REngine_GfxRenderer_Base "${LibraryName}" PARENT_SCOPE)
################################################################################
# Include the source files
include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/GfxRenderer_Base_SourceFiles.cmake)

# Define the target
add_library ("${Library_REngine_GfxRenderer_Base}" STATIC ${GfxRenderer_Base_SourceFiles})
# Add to a project folder for generators that support this feature
set_target_properties ("${Library_REngine_GfxRenderer_Base}" 
  PROPERTIES FOLDER "${SubprojectFolder}"
)

# Header files
target_include_directories ("${Library_REngine_GfxRenderer_Base}"
  PUBLIC
    # Populate the local and interface include properties of the target:
    # INCLUDE_DIRECTORIES, INTERFACE_INCLUDE_DIRECTORIES
    # This will add the given path to the search paths of #include.
    "${CMAKE_CURRENT_SOURCE_DIR}/../Common"
)

# Link libraries
target_link_libraries ("${Library_REngine_GfxRenderer_Base}"
  PUBLIC
    "${Library_REngine_Core}"
)
################################################################################
# GfxRenderer_Base
################################################################################
