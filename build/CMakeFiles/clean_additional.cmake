# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\FileEncrypterGUI_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\FileEncrypterGUI_autogen.dir\\ParseCache.txt"
  "FileEncrypterGUI_autogen"
  )
endif()
