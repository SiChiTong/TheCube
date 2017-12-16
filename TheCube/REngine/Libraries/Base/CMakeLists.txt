################################################################################
# Subproject: Base (private REngine)
################################################################################

################################################################################
cmake_minimum_required (VERSION 3.9.0 FATAL_ERROR)
################################################################################

################################################################################
# Subproject variables
################################################################################
set (SubprojectName "Base") # Will override the parent project's variable
set (SubprojectVersion "1.0.0.0") # MAJOR.MINOR.PATCH.TWEAK
################################################################################
re_LogSection (PREFIX "${SubprojectName}"
  "${SubprojectVersion} is being configured now..."
)
################################################################################

################################################################################
# Cache variables - define and force in a parent project if required
################################################################################
# IMPORTANT: If you CHANGE the value of any of the following CACHE variables
# here, DELETE the CACHE and regenerate it anew to AVOID unexpected problems.
set (re_cache_DisableNonStandardCxxCompilerExtensions TRUE 
  CACHE INTERNAL 
  "Do not use non-standard language extensions: e.g. -std=c++11 instad of -std=gnu++11"
)
set (re_cache_EnableLatestExperimentalLanguageStandard FALSE 
  CACHE INTERNAL 
  "Use latest experimental C++ standard features: e.g. -std=c++2a"
)
set (re_cache_EnableExperimentalLanguageFeatures FALSE 
  CACHE INTERNAL 
  "Enable additional C++ features that might be included in the next standard: e.g. -fcoroutines-ts"
)
################################################################################

################################################################################
# Options - define on the command line if required
################################################################################
option (option_EnableAssertions 
  "Enable run-time assertions" NO
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
set (Library_REngine_Base "${LibraryName}")
set (Library_REngine_Base "${LibraryName}" PARENT_SCOPE)
################################################################################
# Define the target
add_library ("${Library_REngine_Base}" INTERFACE)

# Preprocessor definitions
# (Windows)
target_compile_definitions("${Library_REngine_Base}"
  INTERFACE
    $<$<BOOL:${option_EnableAssertions}>:ASSERT_ENABLED>
    $<$<BOOL:${re_var_WINDOWS}>:_UNICODE>
    $<$<BOOL:${re_var_WINDOWS}>:UNICODE>
    $<$<BOOL:${re_var_WINDOWS}>:WIN32_LEAN_AND_MEAN>
)

# Disable compiler warnings
target_compile_options ("${Library_REngine_Base}"
  INTERFACE
    # Don’t emit warning for unused driver arguments
    # ...to disable warning about the unused compiler argument "/Gm-"
    $<$<BOOL:${re_var_WINDOWS_MSVC_CLANG}>:-Qunused-arguments>
    $<$<BOOL:${re_var_WINDOWS_MSVC_CLANG}>:-Wno-microsoft-include>
)

# Fix warning C4530: C++ exception handler used, but unwind semantics are not
# enabled. Specify /EHsc
target_compile_options ("${Library_REngine_Base}"
  INTERFACE
    $<$<OR:$<BOOL:${re_var_WINDOWS_MSVC}>,$<BOOL:${re_var_WINDOWS_MSVC_CLANG}>>:/EHsc>
)

# C++ standard version
if (NOT re_cache_EnableLatestExperimentalLanguageStandard)
  # Enable official C++ standard (All compilers without MSVC-Clang)
  target_compile_features ("${Library_REngine_Base}"
    INTERFACE
      $<$<NOT:$<BOOL:${re_var_WINDOWS_MSVC_CLANG}>>:cxx_std_17>
  )
  # Enable official C++ standard (MSVC-Clang)
  target_compile_options ("${Library_REngine_Base}"
    INTERFACE
      $<$<BOOL:${re_var_WINDOWS_MSVC_CLANG}>:-Xclang -std=c++17>
  )
else ()
  # Enable latest C++ standard features (MSVC)
  target_compile_options ("${Library_REngine_Base}"
    INTERFACE
      $<$<BOOL:${re_var_WINDOWS_MSVC}>:/std:c++latest>
  )
  # Enable latest C++ standard features (Clang)
  target_compile_options ("${Library_REngine_Base}"
    INTERFACE
      $<$<AND:$<CXX_COMPILER_ID:Clang>,$<NOT:$<BOOL:${re_var_WINDOWS_MSVC_CLANG}>>>:-std=c++2a>
      $<$<BOOL:${re_var_WINDOWS_MSVC_CLANG}>:-Xclang -std=c++2a>
  )
endif ()

# Compiler specific language extensions
if (re_cache_DisableNonStandardCxxCompilerExtensions)
  # (MSVC)
  target_compile_options ("${Library_REngine_Base}"
    INTERFACE
      $<$<BOOL:${re_var_WINDOWS_MSVC}>:/permissive->
  )
  # (Clang)
  target_compile_options ("${Library_REngine_Base}"
    INTERFACE
      $<$<AND:$<CXX_COMPILER_ID:Clang>,$<NOT:$<BOOL:${re_var_WINDOWS_MSVC_CLANG}>>>:-pedantic-errors>
  )
  # (All compilers) - Use "-std=c++11" instead of "-std=gnu++11" on supported
  # compilers. This global variable doesn't do anything on Visual Studio targets.
  set (CMAKE_CXX_EXTENSIONS OFF)
endif ()

# Experimental C++ language features
if (re_cache_EnableExperimentalLanguageFeatures)
  # Enable latest experimental C++ language features (MSVC)
  target_compile_options ("${Library_REngine_Base}"
    INTERFACE
      # Coroutines - compiler flag: /await
      $<$<BOOL:${re_var_WINDOWS_MSVC}>:/await>
  )
  # Enable latest experimental C++ language features (Clang)
  target_compile_options ("${Library_REngine_Base}"
    INTERFACE
      # Coroutines - compiler flag: -fcoroutines-ts -stdlib=libc++
      # Android CMake adds -stdlib=libc++ by default
      $<$<AND:$<CXX_COMPILER_ID:Clang>,$<NOT:$<BOOL:${re_var_WINDOWS_MSVC_CLANG}>>>:-fcoroutines-ts>
  )
endif ()
################################################################################

################################################################################
# Header files
################################################################################
# Add the REngine's global header files
target_include_directories ("${Library_REngine_Base}"
  INTERFACE
    # Populate the interface include properties of the target:
    # INTERFACE_INCLUDE_DIRECTORIES
    # This will add the given path to the search paths of #include.
    # Include the required headers by using angle brackets: #include <Sample.h>
    "${re_var_REngine_IncludeDirectories}"
)

# Add the C++/WinRT header files
if (re_var_WINDOWS_UWP)
  target_include_directories ("${Library_REngine_Base}"
    INTERFACE
      "$ENV{cppwinrt}"
  )
endif ()
################################################################################

################################################################################
# Google Test related settings
################################################################################
if (option_EnableUnitTests
  AND (re_var_WINDOWS_MSVC OR re_var_WINDOWS_MSVC_CLANG)
)
  # Do not use a debug postfix. It is set when Google Test is enabled.
  set (CMAKE_DEBUG_POSTFIX ""
    CACHE STRING
      "Do not use a debug postfix. It is set when Google Test is enabled."
    FORCE
  )
else ()
  unset (CMAKE_DEBUG_POSTFIX CACHE)
endif ()
################################################################################
