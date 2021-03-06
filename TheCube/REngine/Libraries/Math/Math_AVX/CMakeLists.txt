################################################################################
# Subproject: Math_AVX (private REngine) 
################################################################################

################################################################################
cmake_minimum_required (VERSION 3.9.0)
################################################################################

################################################################################
# Subproject variables
################################################################################
set (SubprojectName "Math_AVX")
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
set (Library_REngine_Math_AVX "${LibraryName}")
set (Library_REngine_Math_AVX "${LibraryName}" PARENT_SCOPE)
################################################################################
# Include the source files
include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/Math_AVX_SourceFiles.cmake)

# Define the target
add_library ("${Library_REngine_Math_AVX}" STATIC ${Math_AVX_SourceFiles})

# Add to a project folder for generators that support this feature
set_target_properties ("${Library_REngine_Math_AVX}"
  PROPERTIES FOLDER
    "${SubprojectFolder}"
)

# Header files
target_include_directories ("${Library_REngine_Math_AVX}"
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../Common"
)

# Link libraries
target_link_libraries ("${Library_REngine_Math_AVX}"
  PUBLIC
    "${Library_REngine_Math_Base}"
)
################################################################################
# Math_AVX
################################################################################
