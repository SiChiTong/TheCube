################################################################################
# Subproject: Core (private REngine)
# Test: StringView
################################################################################

################################################################################
# Test variables
################################################################################
set (TestName "StringView")
################################################################################

################################################################################
# Test target
################################################################################
# Include the source files
set (${TestName}_SourceFiles
  "Sources/StringViewTest.cpp"
)

# Define the target
add_executable ("${TestName}" ${${TestName}_SourceFiles})
# Add to a project folder for generators that support this feature
set_target_properties ("${TestName}" 
  PROPERTIES FOLDER "${ProjectFolder_Tests}/Libraries/${SubprojectName}"
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
