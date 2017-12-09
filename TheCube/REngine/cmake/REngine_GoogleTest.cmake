################################################################################
include_guard() # Prevent this file from being included more than once
################################################################################

option (option_EnableUnitTests "Enable Google Test based unit tests" NO)

if (option_EnableUnitTests)
  set (GoogleTest_Project "${CMAKE_CURRENT_SOURCE_DIR}/Tests")
  set (GoogleTest_Directory "${CMAKE_BINARY_DIR}/GoogleTest")

  configure_file (
    "${GoogleTest_Project}/CMakeLists.txt.in"
    "${GoogleTest_Directory}/CMakeLists.txt"
  )

  execute_process (
    COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY "${GoogleTest_Directory}"
  )
  if (result)
    message (FATAL_ERROR "CMake step for googletest failed: ${result}")
  endif()

  execute_process (
    COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY "${GoogleTest_Directory}"
  )
  if (result)
    message (FATAL_ERROR "Build step for googletest failed: ${result}")
  endif()

  # Prevent overriding the parent project's compiler/linker
  # settings on Windows
  set (gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  # Add googletest directly to our build. This defines
  # the gtest and gtest_main targets.
  add_subdirectory (
    "${GoogleTest_Directory}/GoogleTest/googletest-source"
    "${GoogleTest_Directory}/GoogleTest/googletest-binary"
    EXCLUDE_FROM_ALL
  )
  # Add to a project folder for generators that support this feature
  set_target_properties (gtest gtest_main gmock gmock_main
    PROPERTIES FOLDER "${ProjectFolder_Tests}/GoogleTest"
  )
  # Do not use GTest TR1 tuple
  target_compile_definitions (gtest
    PRIVATE
      "GTEST_HAS_TR1_TUPLE=0"
  )
  target_compile_definitions (gtest_main
    PRIVATE
      "GTEST_HAS_TR1_TUPLE=0"
  )
endif ()
