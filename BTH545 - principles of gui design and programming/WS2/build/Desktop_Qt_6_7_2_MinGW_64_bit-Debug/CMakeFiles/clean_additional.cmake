# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\WS2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\WS2_autogen.dir\\ParseCache.txt"
  "WS2_autogen"
  )
endif()
