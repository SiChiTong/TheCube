################################################################################
# Project: TheCube (executable)
################################################################################

################################################################################
cmake_minimum_required (VERSION 3.9.0 FATAL_ERROR)
################################################################################

################################################################################
re_LogSection (PREFIX "${ProjectName}"
  "${ProjectVersion} is being configured now..."
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

# Set linker flags
# (Windows)
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
re_LogSectionMultiline (PREFIX "${ProjectName}" "will be installed into:"
  ARROWS "${InstallationFolder}"
)
install (TARGETS "${ProjectName}"
  RUNTIME DESTINATION "${InstallationFolder}"
)
################################################################################
