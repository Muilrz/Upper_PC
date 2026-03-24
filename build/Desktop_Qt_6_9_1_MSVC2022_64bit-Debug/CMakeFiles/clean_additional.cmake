# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "app\\CMakeFiles\\UpperPC_2_0_autogen.dir\\AutogenUsed.txt"
  "app\\CMakeFiles\\UpperPC_2_0_autogen.dir\\ParseCache.txt"
  "app\\UpperPC_2_0_autogen"
  "comm\\CMakeFiles\\comm_autogen.dir\\AutogenUsed.txt"
  "comm\\CMakeFiles\\comm_autogen.dir\\ParseCache.txt"
  "comm\\comm_autogen"
  "core\\CMakeFiles\\core_autogen.dir\\AutogenUsed.txt"
  "core\\CMakeFiles\\core_autogen.dir\\ParseCache.txt"
  "core\\core_autogen"
  "devices\\CMakeFiles\\devices_autogen.dir\\AutogenUsed.txt"
  "devices\\CMakeFiles\\devices_autogen.dir\\ParseCache.txt"
  "devices\\devices_autogen"
  "sim\\CMakeFiles\\sim_autogen.dir\\AutogenUsed.txt"
  "sim\\CMakeFiles\\sim_autogen.dir\\ParseCache.txt"
  "sim\\sim_autogen"
  )
endif()
