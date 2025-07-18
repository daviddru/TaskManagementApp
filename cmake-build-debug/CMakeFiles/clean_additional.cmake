# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TaskManagement_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TaskManagement_autogen.dir\\ParseCache.txt"
  "TaskManagement_autogen"
  )
endif()
