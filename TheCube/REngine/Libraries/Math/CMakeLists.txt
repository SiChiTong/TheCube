# Math

set (SubprojectFolder "${ProjectFolder_Libraries}/Math")

add_subdirectory ("Math_Base")
set (Library_REngine_Math_Base
  "${Library_REngine_Math_Base}" PARENT_SCOPE
)
add_subdirectory ("Math_AVX")
set (Library_REngine_Math_AVX
  "${Library_REngine_Math_AVX}" PARENT_SCOPE
)
add_subdirectory ("Math_SSE")
set (Library_REngine_Math_SSE
  "${Library_REngine_Math_SSE}" PARENT_SCOPE
)
