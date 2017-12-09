################################################################################
include_guard() # Prevent this file from being included more than once
################################################################################

################################################################################
# Macro name:
#   include_guard()
# Description:
#   Implements include_guard() from CMake 3.10.0 for lesser versions
################################################################################
if (NOT COMMAND include_guard
    AND ${CMAKE_VERSION} VERSION_LESS "3.10.0"
)
  macro (include_guard)
    if (DEFINED "_INCLUDE_GUARD_${CMAKE_CURRENT_LIST_FILE}")
      return ()
    endif ()
      set ("_INCLUDE_GUARD_${CMAKE_CURRENT_LIST_FILE}" ENTERED_ONCE)
    endmacro ()
endif ()
################################################################################

################################################################################
# Include directory to export
set (re_var_REngine_IncludeDirectories ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (re_var_REngine_IncludeDirectoriesInstallLocation ${CMAKE_CURRENT_SOURCE_DIR}/include)
################################################################################

################################################################################
# REngine_AuxiliaryLoggingFunctions need to be included first to enable logging
include ("REngine_AuxiliaryLoggingFunctions")
include ("REngine_BuildEnvironment")
include ("REngine_Functions")
################################################################################
