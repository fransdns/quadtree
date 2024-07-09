# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\proyecto-algoritmos_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\proyecto-algoritmos_autogen.dir\\ParseCache.txt"
  "proyecto-algoritmos_autogen"
  )
endif()
