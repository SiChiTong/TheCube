################################################################################
include_guard() # Prevent this file from being included more than once
################################################################################

################################################################################
# REngine_HeaderFiles.cmake
################################################################################

# A list with the project's header files
re_CreateSourceFilesList (REngine_HeaderFiles 
  "../../include" HIDE "Include"
  # Header files
  "REngine/Core/ReCore"
  "REngine/Core/ReCoreBase"
  "REngine/GfxRenderers/ReIGfxRenderer"
  "REngine/Math/ReArithmetics"
  "REngine/Math/ReMatrix"
  "REngine/Math/ReVector"
  "REngine/ReApplication"
)

################################################################################
# REngine_HeaderFiles.cmake
################################################################################
