################################################################################
# Project: REngine (public library)
################################################################################

################################################################################
cmake_minimum_required (VERSION 3.9.0 FATAL_ERROR)
################################################################################

################################################################################
# Modules
################################################################################
# Set the CMake modules path for the this project
set (CMAKE_MODULE_PATH
  # CMAKE_SOURCE_DIR - The path to the top level of the source tree.
  ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/REngine/cmake/"
)
include ("REngine")
################################################################################

################################################################################
# Project variables
################################################################################
set (LibraryProjectName "REngine") # Will override the parent project's variable
set (ProjectVersion "0.1.0.0") # MAJOR.MINOR.PATCH.TWEAK
set (ProjectFolder "${LibraryProjectName}")
set (ProjectFolder_Libraries "${ProjectFolder}/Libraries")
set (ProjectFolder_Tests "${ProjectFolder}/Tests")
################################################################################
re_LogSection (PREFIX "${LibraryProjectName}"
  "${ProjectVersion} is being configured now..."
)
################################################################################

################################################################################
# Project declaration
################################################################################
if (NOT PROJECT_NAME)
  # If this is a stand alone project PROJECT_NAME should not be set.
	project (${LibraryProjectName} VERSION ${ProjectVersion} LANGUAGES C CXX)
endif ()

################################################################################
# Exported target name
################################################################################
if (re_var_WINDOWS_MSVC OR re_var_WINDOWS_MSVC_CLANG)
  # Add the "lib" prefix to the library name on Windows
  set (Library_REngine "lib${LibraryProjectName}")
else ()
  set (Library_REngine "${LibraryProjectName}")
endif ()
set (re_var_Library_REngine "${Library_REngine}" PARENT_SCOPE)
re_LogInfo (PREFIX "${LibraryProjectName}"
  "Use exported variable \"re_var_Library_REngine\" to link to target"
)
################################################################################

################################################################################
# Configuration info
################################################################################
re_LogInfo (PREFIX "${LibraryProjectName}"
  "Using CMake ${CMAKE_VERSION}"
)
  # CMAKE_GENERATOR_TOOLSET will be set if a toolset specification is provided
  # by the user.
if (CMAKE_GENERATOR_TOOLSET)
  # CMAKE_GENERATOR_TOOLSET is native build system toolset specification 
  # provided by user. If the user specifies a toolset (e.g. via the cmake(1) -T
  # option) the value will be available in this variable.
  # Toolset specification is supported only on specific generators:
  #  - Visual Studio Generators for VS 2010 and above
  #  - The Xcode generator for Xcode 3.0 and above
  # Example:
  #    cmake.exe -TLLVM-vs2014
re_LogInfo (PREFIX "${LibraryProjectName}"
  "Using Toolchain: ${CMAKE_GENERATOR_TOOLSET}"
)
endif ()
re_LogInfoMultiline (PREFIX "${LibraryProjectName}"
  "Build output directory: CMAKE_BINARY_DIR=\"${CMAKE_BINARY_DIR}\""
  "Install directory:      CMAKE_INSTALL_PREFIX=\"${CMAKE_INSTALL_PREFIX}\""
  "Source directory:       CMAKE_SOURCE_DIR=\"${CMAKE_SOURCE_DIR}\""
)
################################################################################

################################################################################
# Unit testing
################################################################################
include (REngine_GoogleTest)
################################################################################
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/include")
################################################################################
# Subprojects
################################################################################
# Interface library that needs to be linked by every subsequent project
add_subdirectory ("Libraries/Base")
# Core library that contains common utility functions
add_subdirectory ("Libraries/Core")
# Logging library
add_subdirectory ("Libraries/Logger")
# Sub-libraries in subdirectories
add_subdirectory ("Libraries/GfxRenderers")
add_subdirectory ("Libraries/Math")
# Main library that exports headers and symbols
add_subdirectory ("Libraries/REngine")
################################################################################
