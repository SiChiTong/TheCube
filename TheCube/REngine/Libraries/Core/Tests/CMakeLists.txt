if (option_EnableUnitTests)
  re_LogInfo (PREFIX "${Library_REngine_Core}" "Configuring tests:")

  if (re_var_WINDOWS)
    set (Platform "Platforms/Windows")
    add_subdirectory ("${Platform}/ObjectHandle")
  endif ()

  add_subdirectory ("String")
  add_subdirectory ("StringView")
endif ()
