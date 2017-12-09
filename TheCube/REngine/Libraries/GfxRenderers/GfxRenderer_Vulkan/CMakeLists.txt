################################################################################
# Subproject: GfxRenderer_Vulkan (private REngine) 
################################################################################

################################################################################
cmake_minimum_required (VERSION 3.9.0)
################################################################################

################################################################################
# Subproject variables
################################################################################
set (SubprojectName "GfxRenderer_Vulkan")
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
  ARROWS "${InstallationFolder}"
)
install (TARGETS "${Library_REngine_GfxRenderer}"
  LIBRARY DESTINATION "${InstallationFolder}"
  RUNTIME DESTINATION "${InstallationFolder}"
)
################################################################################
