################################################################################
include_guard() # Prevent this file from being included more than once
################################################################################

################################################################################
# Function name:
#   re_LogError (PREFIX <value> [<value> [value  [value ... ]]])
# Description:
#  Prints out a error message to the CMake output console and interrupts the 
# cache generation.
# Parameters:
#   PREFIX <value>        - <value> Optional text to prepend to the message
#   <value> <value>       - <value> The message text to print out
# Usage:
#   re_LogError (PREFIX "ProjectName" "Hello CMake!" )
# Result:
#   "    <ProjectName> Hello CMake!"
# Usage:
#   re_LogError ("Hello CMake!")
# Result:
#   "    ===> Hello CMake!"
################################################################################
function (re_LogError)
  if (NOT "${ARGV0}" STREQUAL "PREFIX")
    message (FATAL_ERROR "===> " ${ARGN})
  else ()
    # Remove the first two arguments of the function to get the message
    list (REMOVE_AT ARGN 0 1)
    message (FATAL_ERROR "<${ARGV1}> " ${ARGN})
  endif ()
endfunction () # re_LogError
################################################################################

################################################################################
# Function name:
#   re_LogInfo (PREFIX <value> [<value> [value  [value ... ]]])
# Description:
#  Prints out a info message to the CMake output console.
# Parameters:
#   PREFIX <value>        - <value> Optional text to prepend to the message
#   <value> <value>       - <value> The message text to print out
# Usage:
#   re_LogInfo (PREFIX "ProjectName" "Hello CMake!")
# Result:
#   "    <ProjectName> Hello CMake!"
# Usage:
#   re_LogInfo ("Hello CMake!")
# Result:
#   "    ===> Hello CMake!"
################################################################################
function (re_LogInfo)
  if (NOT "${ARGV0}" STREQUAL "PREFIX")
    message ("    ===> " ${ARGN})
  else ()
    # Remove the first two arguments of the function to get the message
    list (REMOVE_AT ARGN 0 1)
    message ("    <${ARGV1}> " ${ARGN})
  endif ()
endfunction () # re_LogInfo
################################################################################

################################################################################
# Function name:
#   re_LogInfoMultiline (PREFIX <value> [<value> [value  [value ... ]]])
# Description:
#  Prints out a info message to the CMake output console.
# Parameters:
#   PREFIX <value>        - <value> Optional text to prepend to the message
#   <value> <value>       - <value> The message text to print out
# Usage:
#   re_LogInfoMultiline (PREFIX "ProjectName" "Hello CMake!")
# Result:
#   "    <ProjectName> Hello CMake!"
# Usage:
#   re_LogInfoMultiline ("Hello CMake!")
# Result:
#   "    ===> Hello CMake!"
################################################################################
function (re_LogInfoMultiline)
  if (NOT "${ARGV0}" STREQUAL "PREFIX")
    message ("    ===> " ${ARGV0})
    # The first message row was printed already, so remove it
    list (REMOVE_AT ARGN 0)
    # Print the rest of the message rows
    foreach (row IN LISTS ARGN)
      message ("         " ${row})
    endforeach ()
  else ()
    # Remove the first two arguments of the function to get the message rows
    list (REMOVE_AT ARGN 0 1)
    list (GET ARGN 0 firstRow)
    set (prefix "    <${ARGV1}> ")
    message ("${prefix}" "${firstRow}" )
    # Create leding spaces with the size of the ${prefix} string
    string (REGEX REPLACE "." " " leadingSpaces "${prefix}")
    # The first message row was printed already, so remove it
    list (REMOVE_AT ARGN 0)
    # Print the rest of the message rows
    foreach (row IN LISTS ARGN)
      message ("${leadingSpaces}" "${row}")
    endforeach ()
  endif ()
endfunction () # re_LogError
################################################################################

################################################################################
# Function name:
#   re_LogSection ([SECTION_TOP | SECTION_BOTTOM]
#                  PREFIX <value> [<value> [value  [value ... ]]])
# Description:
#  Prints out a info message to the CMake output console.
# Parameters:
#   [SECTION_TOP | SECTION_BOTTOM]
#                         - If specified a bottom or a top line won't be drawn
#   PREFIX <value>        - <value> Optional text to prepend to the message
#   <value> <value>       - <value> The message text to print out
# Usage:
#   re_LogSection (PREFIX "Hello CMake!" "ProjectName")
# Result:
#   "--------------------------------------------------------------------------------"
#   "    <ProjectName> Hello CMake!"
#   "--------------------------------------------------------------------------------"
# Usage:
#   re_LogSection ("Hello CMake!")
# Result:
#   "--------------------------------------------------------------------------------"
#   "    ===> Hello CMake!"
#   "--------------------------------------------------------------------------------"
################################################################################
function (re_LogSection)
  set (SectionArguments SECTION_TOP SECTION_BOTTOM)
  set (SectionARG ${ARGV0})
  if ("${SectionARG}" IN_LIST SectionArguments)
    list (REMOVE_AT ARGN 0)
  endif ()
  list (GET ARGN 0 PrefixARG)
  if (NOT "${PrefixARG}" STREQUAL "PREFIX")
    if (NOT "${SectionARG}" STREQUAL "SECTION_BOTTOM")
      message ("--------------------------------------------------------------------------------")
    endif ()
      message ("    ===> " ${ARGN})
    if (NOT "${SectionARG}" STREQUAL "SECTION_TOP")
      message ("--------------------------------------------------------------------------------")
    endif ()
  else ()
    list (GET ARGN 1 prefix)
    # Remove the first two arguments of the function to get the message
    list (REMOVE_AT ARGN 0 1)
    if (NOT "${SectionARG}" STREQUAL "SECTION_BOTTOM")
      message ("--------------------------------------------------------------------------------")
    endif ()
      message ("    <${prefix}> " ${ARGN})
    if (NOT "${SectionARG}" STREQUAL "SECTION_TOP")
      message ("--------------------------------------------------------------------------------")
    endif ()
  endif ()
endfunction () # re_LogInfo
################################################################################

################################################################################
# Function name:
#   re_LogSectionMultiline ([SECTION_TOP | SECTION_BOTTOM] PREFIX <value>
#                           [[NOALIGN | ARROWS] <value>
#                           [value  [value ... ]]])
# Description:
#  Prints out a info message to the CMake output console.
# Parameters:
#   [SECTION_TOP | SECTION_BOTTOM]
#                         - If specified a bottom or a top line won't be drawn
#                           respectively.
#   PREFIX <value>        - <value> Optional text to prepend to the message
#   [NOALIGN | ARROWS]    - Only valid with PREFIX
#   <value> <value>       - <value> The message text to print out
# Usage:
#   re_LogSectionMultiline (PREFIX "ProjectName" "Hello CMake!")
# Result:
#   "--------------------------------------------------------------------------------"
#   "    <ProjectName> Hello CMake!"
#   "--------------------------------------------------------------------------------"
# Usage:
#   re_LogSectionMultiline (PREFIX "ProjectName" "Hello CMake!" NOALIGN "...and again!)
# Result:
#   "--------------------------------------------------------------------------------"
#   "    <ProjectName> Hello CMake!"
#   "    ...and again!"
#   "--------------------------------------------------------------------------------"
# Usage:
#   re_LogSectionMultiline ("Hello CMake!")
# Result:
#   "--------------------------------------------------------------------------------"
#   "    ===> Hello CMake!"
#   "--------------------------------------------------------------------------------"
################################################################################
function (re_LogSectionMultiline)
  set (SectionArguments SECTION_TOP SECTION_BOTTOM)
  set (SectionARG ${ARGV0})
  if ("${SectionARG}" IN_LIST SectionArguments)
    list (REMOVE_AT ARGN 0)
  endif ()
  list (GET ARGN 0 PrefixARG)
  if (NOT "${PrefixARG}" STREQUAL "PREFIX")
    if (NOT "${SectionARG}" STREQUAL "SECTION_BOTTOM")
      message ("--------------------------------------------------------------------------------")
    endif ()
    list (GET ARGN 0 firstRow)
    #list (REMOVE_AT ARGN 0)
    message ("    ===> " ${firstRow})
    # The first message row was printed already, so remove it
    list (REMOVE_AT ARGN 0)
    # Print the rest of the message rows
    foreach (row IN LISTS ARGN)
      message ("         " ${row})
    endforeach ()
    if (NOT "${SectionARG}" STREQUAL "SECTION_TOP")
      message ("--------------------------------------------------------------------------------")
    endif ()
  else ()
    # Remove the first two arguments of the function to get the message rows
    list (GET ARGN 1 prefix)
    set (prefix "    <${prefix}> ")
    list (REMOVE_AT ARGN 0 1)
    list (GET ARGN 0 firstRow)
    if (NOT "${SectionARG}" STREQUAL "SECTION_BOTTOM")
      message ("--------------------------------------------------------------------------------")
    endif ()
    message ("${prefix}" "${firstRow}" )
    # Create leding spaces with the size of the ${prefix} string
    list (REMOVE_AT ARGN 0)
    # Is the argument list empty?
    if (NOT ARGN)
      return ()
    endif ()
    # Check for an optional argument
    list (GET ARGN 0 argument)
    if (NOT ("${argument}" STREQUAL "NOALIGN"
        OR "${argument}" STREQUAL "ARROWS"
      )
    )
      string (REGEX REPLACE "." " " leadingSpaces "${prefix}")
    else ()
      if ("${argument}" STREQUAL "ARROWS")
        set (arrows "===> ")
      endif ()
      set (leadingSpaces "    ${arrows}")
      # Remove the optional argument
      list (REMOVE_AT ARGN 0)
    endif ()   
    # Print the rest of the message rows
    foreach (row IN LISTS ARGN)
      message ("${leadingSpaces}" "${row}")
    endforeach ()
    if (NOT "${SectionARG}" STREQUAL "SECTION_TOP")
      message ("--------------------------------------------------------------------------------")
    endif ()
  endif ()
endfunction () # re_LogError
################################################################################
