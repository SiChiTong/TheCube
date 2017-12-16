################################################################################
# Subproject: REngine (private REngine)
################################################################################

################################################################################
cmake_minimum_required (VERSION 3.9.0 FATAL_ERROR)
################################################################################

################################################################################
# Library target
################################################################################
# Include the source files
include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/REngine_HeaderFiles.cmake)
include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/REngine_SourceFiles.cmake)

# Define the target
add_library ("${Library_REngine}" STATIC
  ${REngine_HeaderFiles}
  ${REngine_SourceFiles}
)
# Add to a project folder for generators that support this feature
set_target_properties ("${Library_REngine}" 
  PROPERTIES FOLDER
    "${ProjectFolder_Libraries}"
)

# Link libraries
target_link_libraries ("${Library_REngine}"
  PUBLIC
    "${Library_REngine_Core}"
)
set (REngine_Math "Math_AVX"
  CACHE STRING "Select a Math library variant"
)
if ("${REngine_Math}" STREQUAL "Math_AVX")
  target_link_libraries ("${Library_REngine}"
    PUBLIC
      "${Library_REngine_Math_AVX}"
  )
elseif ("${REngine_Math}" STREQUAL "Math_SSE")
  target_link_libraries ("${Library_REngine}"
    PUBLIC
      "${Library_REngine_Math_SSE}"
  )
else ()
  re_LogInfoMultiline (PREFIX "${ProjectName}"
    "Math library options:"
    " -> Math_AVX - Uses AVX optimizations."
    " -> Math_SSE - Uses SSE optimizations."
  )
  re_LogError ("${ProjectName}"
    "Math library is not defined"
  )
endif () # ("${REngine_Math}" STREQUAL "Math_AVX")

# Header files
target_include_directories ("${Library_REngine}" 
  PUBLIC
    $<INSTALL_INTERFACE:${re_var_REngine_IncludeDirectoriesInstallLocation}>
)
################################################################################
