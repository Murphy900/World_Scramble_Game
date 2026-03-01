# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Word_Scramble_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Word_Scramble_autogen.dir/ParseCache.txt"
  "Word_Scramble_autogen"
  )
endif()
