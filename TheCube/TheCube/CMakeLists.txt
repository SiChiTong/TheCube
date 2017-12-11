################################################################################
# Project: TheCube (executable)
################################################################################

################################################################################
cmake_minimum_required (VERSION 3.9.0 FATAL_ERROR)
################################################################################

################################################################################
re_LogSectionMultiline (SECTION_TOP PREFIX "${ProjectName}"
  "${ProjectName} is being configured now..."
  "..."
)
################################################################################

################################################################################
# Executable
################################################################################
# Include the source files
include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/TheCube_SourceFiles.cmake)
# Define the target
add_executable("${ProjectName}" ${TheCube_SourceFiles})
# Set the current executable project as the Startup project of the generated
# Visual Studio solution
set_property (DIRECTORY ${CMAKE_SOURCE_DIR} 
  PROPERTY VS_STARTUP_PROJECT "${ProjectName}"
)
# Set the build output directory
if ("${re_var_IDE_BUILD_TOOL_GENERATOR}" STREQUAL "Visual Studio")
  set (IsVisualStudio TRUE)
  set (InstallDirectory "${CMAKE_INSTALL_PREFIX}")
  re_LogInfoMultiline (PREFIX "${ProjectName}" "working directory:"
    "-> ${InstallDirectory}"
  )
  set (OutputDirectory "${InstallDirectory}/${ProjectName}-VS")
  re_LogInfoMultiline (PREFIX "${ProjectName}" "build output directory:"
    "-> ${OutputDirectory}"
  )
endif ()
set_target_properties ("${ProjectName}"
  PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY
      ${InstallDirectory}
    RUNTIME_OUTPUT_DIRECTORY
      $<$<BOOL:${IsVisualStudio}>:${OutputDirectory}>
)

# Set linker flags
if (re_var_WINDOWS_MSVC)
  re_SetLinkerFlags ("${ProjectName}"
    # https://docs.microsoft.com/en-gb/cpp/build/reference/linker-options
    # Create an pplication does not require a console,
    # probably because it creates its own windows.
    "/SUBSYSTEM:WINDOWS"
    # The application uses main() or wmain() as an entry point
    "/ENTRY:mainCRTStartup"
    # Do not embed User Account Control (UAC) information in the program
    # manifest.
    "/MANIFESTUAC:NO"
  )
  # Set linker flags for UWP configurations
  if ("${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsStore"
  )
    re_SetLinkerFlags ("${ProjectName}" DEBUG
      # Fix warning LNK4075 for WinRT debug builds
      # "LNK4075: ignoring '/INCREMENTAL' due to '/OPT:ICF' specification"
      "/OPT:NOICF"
      "/OPT:NOREF"
    )
  endif ()
endif ()

# Link libraries
target_link_libraries ("${ProjectName}"
	"${re_var_Library_REngine}" # Defined in the REngine library
)

################################################################################
# Installation
################################################################################
set (InstallationFolder "${CMAKE_INSTALL_PREFIX}/${ProjectName}")
get_filename_component (InstallationFolder
  "${InstallationFolder}" ABSOLUTE
)
re_LogSectionMultiline (SECTION_BOTTOM
  PREFIX "${ProjectName}" "will be installed into:"
  "-> ${InstallationFolder}"
)

install (TARGETS "${ProjectName}"
  RUNTIME DESTINATION "${InstallationFolder}"
)
################################################################################
