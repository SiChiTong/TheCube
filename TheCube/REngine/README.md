# REngine

## Project Structure

```
REngine                                               <- Package name
  |
  +-- cmake                                           <- Public CMake modules
  |
  +-- include                                         <- Public header files
  |     |
  |     +-- REngine
  |           +-- Core
  |           |     +-- ReCore
  |           |         ReCoreBase
  |           |         ...
  |           |
  |           +-- Math
  |           |     +-- ReArithmetics
  |           |         ReMatrix
  |           |         ReVector
  |           |
  |           +-- GfxRenderers
  |           |     +-- IeGfxRenderer
  |           |
  |           +-- ReApplication
  |
  +-- Libraries                                       <- Library subprojects
        |
        +-- Base                                      <- Interface library (links to all)
        |
        +-- Core                                      <- Static library with system services
        |
        +-- Math                                      <- Static math libraries
        |
        +-- GfxRenderers                              <- Dynamic graphics renderer libraries
        |
        +-- REngine                                   <- The public user library
```

### Core
Provides basic system specific services.
```
Core                                                  <- Subproject name
  |
  +-- cmake
  |     +-- Core_SourceFiles.cmake                    <- Source files list
  |
  +-- include                                         <- Public includes
  |     +-- Core
  |           +-- Core
  |               CoreBase
  |               ...
  |
  +-- Sources                                         <- Private includes and source
        +-- Platform
              +-- Windows
            Core.cpp
            Core.hpp
            ...
```

### Math
```
Math                                                  <- Subprojects group name
  |
  +-- Common                                          <- Common includes
  |     +-- Matrix.hpp
  |         Vector.hpp
  |
  +-- Math_AVX                                        <- Subproject name
  |     +-- cmake
  |     |     +-- Math_AVX_SourceFiles.cmake
  |     |
  |     +-- Sources
  |     |     +-- Matrix.cpp
  |     |         Vector.cpp
  |     |         ...
  |     |
  |     +-- CMakeLists.txt
  |
  +-- Math_Base                                       <- Subproject name
  |     +-- cmake
  |     |     +-- Math_Base_SourceFiles.cmake
  |     |
  |     +-- Sources
  |     |     +-- Arithmetics.cpp
  |     |         Arithmetics.hpp
  |     |         ...
  |     |
  |     +-- CMakeLists.txt
  |
  +-- Math_SSE                                        <- Subproject name
  |     +-- cmake
  |     |     +-- Math_SSE_SourceFiles.cmake
  |     |
  |     +-- Sources
  |     |     +-- Matrix.cpp
  |     |         Vector.cpp
  |     |         ...
  |     |
  |     +-- CMakeLists.txt
  |
  +-- CMakeLists.txt
```

### GfxRenderers
```
GfxRenderers                                          <- Subprojects group name
  |
  +-- Common                                          <- Common includes
  |     +-- IGfxRenderer.hpp
  |
  +-- GfxRenderer_Base
  |     +-- cmake
  |     |     +-- GfxRenderer_Base_SourceFiles.cmake
  |     |
  |     +-- Sources
  |     |     +-- IGfxRenderer.cpp
  |     |
  |     +-- CMakeLists.txt
  |
  +-- GfxRenderer_OpenGL                              <- Subproject name
  |     +-- cmake
  |     |     +-- GfxRenderer_OpenGL_SourceFiles.cmake
  |     |
  |     +-- Sources
  |     |     +-- GfxRenderer.cpp
  |     |     +-- GfxRenderer.hpp
  |     |
  |     +-- CMakeLists.txt
  |
  +-- CMakeLists.txt
```
