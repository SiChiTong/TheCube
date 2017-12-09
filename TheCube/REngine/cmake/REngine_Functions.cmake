################################################################################
include_guard() # Prevent this file from being included more than once
################################################################################

################################################################################
# Function name:
#   re_CreateSourceFilesList (<variable> 
#                             <value> <value> <value> 
#                             <value1>...<valueN>)
# Description:
#   Creates a variable holding a list of source files and creates source
#   groups for the generated Visual Studio project.
# Parameters:
#   newSourceFilesList    - <variable> A name of the new variable that will be 
#                           created and will hold the list
#   prefixDirectory       - <value> A source directory name to prepend
#   hideParentDirectory   - <value> Possible value "HIDE" or "SHOW". If set to
#                           "HIDE" the prefix won't be added
#                           to the generated project
#   sourceGroupName       - <value> A source group name
#   <source_files>        - <value1>...<valueN> Names  of source files
# Usage:
#   re_CreateSourceFilesList (SourceFiles 
#     "Sources" HIDE "Source Files"
#     # Source files
#     "Application.cpp"         # Full real path in "Sources/Application.cpp"
#     "Application.hpp"         # Full real path in "Sources/Application.hpp"
#   )
################################################################################
function (re_CreateSourceFilesList newSourceFilesList 
  parentDirectory hideParentDirectory sourceGroupName
)
  if ("${parentDirectory}" STREQUAL "")
    set (Prefix "")
  else ()
    set (Prefix "${parentDirectory}")
  endif ()

  foreach (SourceFile IN ITEMS ${ARGN})
    if ("${Prefix}" STREQUAL "")
      list (APPEND TempSourceFilesList "${SourceFile}")
    else ()
      list (APPEND TempSourceFilesList "${Prefix}/${SourceFile}")
    endif ()
  endforeach ()

  set (${newSourceFilesList} ${TempSourceFilesList} PARENT_SCOPE)

  foreach (SourceFile IN ITEMS ${TempSourceFilesList}) 
    # Get the directory of the source file
    get_filename_component (SourceFileDirectory "${SourceFile}" DIRECTORY)
    # Remove common directory prefix to make the group
    string (REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" ""
            SourceFileGroup "${SourceFileDirectory}")
    
    # If "HIDE" don't display the root of the source files in the project
    # filters
    if ("${hideParentDirectory}" STREQUAL "HIDE")
      if (NOT "${Prefix}" STREQUAL "")
          string (REGEX REPLACE "^${Prefix}([/])?" ""
                  TempSourceFilesGroup "${SourceFileGroup}")
          set (SourceFileGroup ${TempSourceFilesGroup})
      endif ()
    elseif (NOT "${hideParentDirectory}" STREQUAL "SHOW")
      message (FATAL_ERROR
               "    function re_CreateSourceFilesList(): Ivalid value"
               "\"${hideParentDirectory}\"")
    endif ()

    # Prepend the source group name
    if (NOT "${sourceGroupName}" STREQUAL "")
      set (SourceFileGroup "${sourceGroupName}/${SourceFileGroup}")
    endif ()

    # Make sure we are using Windows slashes
    if ("${CMAKE_GENERATOR}" MATCHES "Visual Studio")
      string(REPLACE "/" "\\" TempSourceFilesGroup "${SourceFileGroup}")
      set (SourceFileGroup ${TempSourceFilesGroup})
    endif ()
    
    # Set to source group of the current file
    source_group ("${SourceFileGroup}" FILES "${SourceFile}")
  endforeach()
endfunction  () # re_CreateSourceFilesList
################################################################################

################################################################################
# Function name:
#   re_AppendToSourceFilesList (<variable> 
#                               <value> <value> <value> 
#                               <value1>...<valueN>)
# Description:
#   Use this function to append source files, resource files, manifests, etc to
#   a source files list. It will also create source groups for the generated
#   Visual Studio project.
# Parameters:
#   sourceFilesList       - <variable> The name of the variable list that files
#                           will be appended to
#   hideParentDirectory   - <value> Possible value "HIDE" or "SHOW". If set to
#                           "HIDE" the prefix won't be added
#                           to the generated project
#   sourceGroupName       - <value> A source group name
#   <source_files>        - <value1>...<valueN> Names  of source files
# Usage:
#   re_AppendToSourceFilesList (SourceFiles "source" HIDE
#     "Sources" HIDE "Source Files"
#     # Source files
#     "Application.cpp"         # Full real path in "Sources/Application.cpp"
#     "Application.hpp"         # Full real path in "Sources/Application.hpp"
#   )
################################################################################
function (re_AppendToSourceFilesList sourceFilesList 
  parentDirectory hideParentDirectory sourceGroupName
)
if ("${parentDirectory}" STREQUAL "")
    set (Prefix "")
  else ()
    set (Prefix "${parentDirectory}")
  endif ()

  foreach (SourceFile IN ITEMS ${ARGN})
    if ("${Prefix}" STREQUAL "")
      list (APPEND TempSourceFilesList "${SourceFile}")
    else ()
      list (APPEND TempSourceFilesList "${Prefix}/${SourceFile}")
    endif ()
  endforeach ()

  list (APPEND ${sourceFilesList} ${TempSourceFilesList})
  set (${sourceFilesList} "${${sourceFilesList}}" PARENT_SCOPE)

  foreach(SourceFile IN ITEMS ${TempSourceFilesList}) 
    # Get the directory of the source file
    get_filename_component (SourceFileDirectory "${SourceFile}" DIRECTORY)
    # Remove common directory prefix to make the group
    string (REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" ""
            SourceFileGroup "${SourceFileDirectory}")

    # If "HIDE" don't display the root of the source files in the project
    # filters
    if ("${hideParentDirectory}" STREQUAL "HIDE")
      if (NOT "${Prefix}" STREQUAL "")
          string (REGEX REPLACE "^${Prefix}([/])?" ""
                  TempSourceFilesGroup "${SourceFileGroup}")
          set (SourceFileGroup ${TempSourceFilesGroup})
      endif ()
    elseif (NOT "${hideParentDirectory}" STREQUAL "SHOW")
      message (FATAL_ERROR
               "    function re_CreateSourceFilesList(): Ivalid value"
               "\"${hideParentDirectory}\"")
    endif ()

    # Prepend the source group name
    if (NOT "${sourceGroupName}" STREQUAL "")
      set (SourceFileGroup "${sourceGroupName}/${SourceFileGroup}")
    endif ()

    # Make sure we are using Windows slashes
    if ("${CMAKE_GENERATOR}" MATCHES "Visual Studio")
      string(REPLACE "/" "\\" TempSourceFilesGroup "${SourceFileGroup}")
      set (SourceFileGroup ${TempSourceFilesGroup})
    endif ()
    
    # Set to source group of the current file
    source_group("${SourceFileGroup}" FILES "${SourceFile}")
  endforeach()
endfunction () # re_AppendToSourceFilesList
################################################################################

################################################################################
# Function name:
#   re_SetLinkerFlags (<variable> [DEBUG|RELEASE|RELWITHDEBINFO|MINSIZEREL]
#                      <value1>...<valueN>)
# Description:
#   Use this function to set a list of linker flags to the target. Subsequent
#   calls append to that list.
# Parameters:
#   target                - <variable> The name of the target to set the linker
#                           flags to
#   <flags>               - <value1>...<valueN> Names  of source files
# Usage:
#   re_SetLinkerFlags (TargetName
#     "-nodefaultlibs"
#     "-static"
#   )
################################################################################
function (re_SetLinkerFlags target)
  set (Configurations DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)
  if ("${ARGV1}" IN_LIST Configurations)
    set (PropertyType LINK_FLAGS_${ARGV1})
    # Removes the configuration type from the arguments list
    list (REMOVE_AT ARGN 0)
  else ()
    set (PropertyType LINK_FLAGS)
    get_target_property (LinkerFlags "${target}" ${PropertyType})
  endif ()

  string (REPLACE ";" " " NewLinkerFlags "${ARGN}")
  get_target_property (LinkerFlags "${target}" LINK_FLAGS)
  if (LinkerFlags STREQUAL "LinkerFlags-NOTFOUND")
    # Erases the invalid value
    set (LinkerFlags "${NewLinkerFlags}")
  else ()
    # Appends an empty space
    set (LinkerFlags "${LinkerFlags} ${NewLinkerFlags}")
  endif ()
  set_target_properties ("${target}"
    PROPERTIES LINK_FLAGS
      "${LinkerFlags}"
  )
endfunction ()
################################################################################
