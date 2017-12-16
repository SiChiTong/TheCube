################################################################################
# Subproject: Math_Base (private REngine) 
################################################################################

################################################################################
cmake_minimum_required (VERSION 3.9.0)
################################################################################

################################################################################
# Subproject variables
################################################################################
set (SubprojectName "Math_Base")
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
set (Library_REngine_Math_Base "${LibraryName}")
set (Library_REngine_Math_Base "${LibraryName}" PARENT_SCOPE)
################################################################################
# Include the source files
include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/Math_Base_SourceFiles.cmake)

# Define the target
add_library ("${Library_REngine_Math_Base}" STATIC ${Math_Base_SourceFiles})
# Add to a project folder for generators that support this feature
set_target_properties ("${Library_REngine_Math_Base}" 
  PROPERTIES FOLDER
    "${SubprojectFolder}"
)

# Link libraries
target_link_libraries ("${Library_REngine_Math_Base}"
  PUBLIC
    "${Library_REngine_Core}"
)
################################################################################
# Math_Base
################################################################################
