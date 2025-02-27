# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\WS3_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\WS3_autogen.dir\\ParseCache.txt"
  "WS3_autogen"
  )
endif()
