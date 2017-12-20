################################################################################
# Subproject: Core (private REngine)
# Test: ObjectHandle
################################################################################

################################################################################
# Test variables
################################################################################
set (TestName "ObjectHandle")
################################################################################

################################################################################
# Test target
################################################################################

# Include the source files
re_CreateSourceFilesList (${TestName}_SourceFiles
  "Sources" HIDE "Source Files"
  # Source files
  "ObjectHandleTest.cpp"
)

# Define the target
add_executable ("${TestName}" ${${TestName}_SourceFiles})
# Add to a project folder for generators that support this feature
set_target_properties ("${TestName}"
  PROPERTIES FOLDER
    "${ProjectFolder_Tests}/Libraries/${SubprojectName}/${Platform}"
)
# Link libraries
target_link_libraries ("${TestName}"
  "${Library_REngine_Core}"
  # Link against gtest or gtest_main as needed.
  gtest_main
)

################################################################################
add_test (NAME "${TestName}" COMMAND "${TestName}")
################################################################################
