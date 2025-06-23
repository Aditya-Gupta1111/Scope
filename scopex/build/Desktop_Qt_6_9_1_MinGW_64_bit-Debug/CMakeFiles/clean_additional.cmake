# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appscopex_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appscopex_autogen.dir\\ParseCache.txt"
  "appscopex_autogen"
  )
endif()
