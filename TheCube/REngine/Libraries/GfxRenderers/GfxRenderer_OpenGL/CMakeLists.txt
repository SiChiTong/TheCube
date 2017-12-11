################################################################################
# Subproject: GfxRenderer_OpenGL (private REngine) 
################################################################################

################################################################################
cmake_minimum_required (VERSION 3.9.0)
################################################################################

################################################################################
# Subproject variables
################################################################################
set (SubprojectName "GfxRenderer_OpenGL")
set (SubprojectVersion "0.1.0.0") # MAJOR.MINOR.PATCH.TWEAK
################################################################################
re_LogSectionMultiline (SECTION_TOP PREFIX "${SubprojectName}"
  "${SubprojectVersion} is being configured now..."
  "..."
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
set (Library_REngine_GfxRenderer "${LibraryName}")
################################################################################
# Include the source files
include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/GfxRenderer_SourceFiles.cmake)

# Define the target
add_library ("${Library_REngine_GfxRenderer}" MODULE ${GfxRenderer_SourceFiles})
# Add to a project folder for generators that support this feature
set_target_properties ("${Library_REngine_GfxRenderer}" 
  PROPERTIES FOLDER "${SubprojectFolder}"
)
# Set the build output directory
if ("${re_var_IDE_BUILD_TOOL_GENERATOR}" STREQUAL "Visual Studio")
  set (IsVisualStudio TRUE)
  set (InstallDirectory "${CMAKE_INSTALL_PREFIX}")
  if (re_var_UWP)
    set (DirectoryPostfix "UWP")
  else ()
    set (DirectoryPostfix "VSIDE")
  endif ()
  set (OutputDirectory "${InstallDirectory}/${ProjectName}-${DirectoryPostfix}")
  re_LogInfoMultiline (PREFIX "${SubprojectName}" "build output directory:"
    "-> ${OutputDirectory}"
  )
endif ()
set_target_properties ("${Library_REngine_GfxRenderer}"
  PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY
      $<$<BOOL:${IsVisualStudio}>:${OutputDirectory}>
)

target_link_libraries ("${Library_REngine_GfxRenderer}"
  PUBLIC
    "${Library_REngine_GfxRenderer_Base}"
    # Prevent the symbols defined in Renderer_Base from being stripped when
    # linking.
    $<$<BOOL:${re_var_WINDOWS_MSVC}>:-WHOLEARCHIVE:${Library_REngine_GfxRenderer_Base}>
)

################################################################################
# Installation
################################################################################
set (InstallationFolder "${CMAKE_INSTALL_PREFIX}/${ProjectName}")
get_filename_component (InstallationFolder
  "${InstallationFolder}" ABSOLUTE
)
re_LogSectionMultiline (SECTION_BOTTOM
  PREFIX "${SubprojectName}" "will be installed into:"
  "-> ${InstallationFolder}"
)
install (TARGETS "${Library_REngine_GfxRenderer}"
  LIBRARY DESTINATION "${InstallationFolder}"
  RUNTIME DESTINATION "${InstallationFolder}"
)
################################################################################
