################################################################################
include_guard() # Prevent this file from being included more than once
################################################################################

################################################################################
# Supported compiler ID variables
################################################################################
set (re_var_WINDOWS_CLANG FALSE)
set (re_var_WINDOWS_CLANG FALSE PARENT_SCOPE)
set (re_var_WINDOWS_MSVC FALSE)
set (re_var_WINDOWS_MSVC FALSE PARENT_SCOPE)
# Uses the Clang toolchain in a Visual Studio project
set (re_var_WINDOWS_MSVC_CLANG FALSE)
set (re_var_WINDOWS_MSVC_CLANG FALSE PARENT_SCOPE)
################################################################################

################################################################################
# Supported platform ID variables
################################################################################
set (re_var_WINDOWS FALSE)
set (re_var_WINDOWS FALSE PARENT_SCOPE)
################################################################################

################################################################################
# Internal variables
################################################################################
# Minimal supported Visual C++ version: 15.3 (_MSC_VER >= 1911)
set (SUPPORTED_MSVC_VERSION "19.11")
################################################################################

################################################################################
# Set variables for Windows Desktop
################################################################################
if (WIN32)
  # Platform is Windows
  set (re_var_WINDOWS TRUE)
  set (re_var_WINDOWS TRUE PARENT_SCOPE)
  # Identify the compiler
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    if ("${CMAKE_CXX_COMPILER_VERSION}"
          VERSION_GREATER_EQUAL "${SUPPORTED_MSVC_VERSION}")
      set (re_var_WINDOWS_MSVC TRUE)
      set (re_var_WINDOWS_MSVC TRUE PARENT_SCOPE)
    else ()
      re_LogError ("Wrong compiler version")
    endif ()
  elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    if ("${CMAKE_GENERATOR_TOOLSET}" MATCHES "LLVM"
        OR "${CMAKE_CXX_SIMULATE_ID}" MATCHES "MSVC")
      set (re_var_WINDOWS_MSVC_CLANG TRUE)
      set (re_var_WINDOWS_MSVC_CLANG TRUE PARENT_SCOPE)
    else ()
      set (re_var_WINDOWS_CLANG TRUE)
      set (re_var_WINDOWS_CLANG TRUE PARENT_SCOPE)
      re_LogError (
        "Unsupported compiler:"
        " ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}"
        " Use clang-cl.exe instead!"
      )
    endif ()
  else ()
    re_LogError (
      "Unsupported compiler:"
      " ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}"
    )
  endif () #"${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
endif () # WIN32
################################################################################

################################################################################
# Prevent in-source builds
################################################################################ 
# Fail if someone tries to config an in-source build.
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  re_LogError (
    "In-source builds are not supported. Please remove CMakeCache.txt from"
    " the source direcotires and configure an out-of-source build in another"
    " directory."
  )
endif()
