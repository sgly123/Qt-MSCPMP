# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\IM_Client_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\IM_Client_autogen.dir\\ParseCache.txt"
  "IM_Client_autogen"
  )
endif()
