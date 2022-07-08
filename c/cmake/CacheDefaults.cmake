#
# This script can be used with -C when generating a build system to set
# some of the configuration variable values to preferable settings.
#
# It does NOT typically make sense to load this in a CMakeLists.txt
# file.
#

set(CMAKE_BUILD_TYPE "Debug" CACHE STRING 
 "Choose the type of build" FORCE)
set(CMAKE_C_FLAGS "-Wall" CACHE STRING 
  "Flags used by the C compiler during all build types" FORCE)
set(CMAKE_CXX_FLAGS "-Wall" CACHE STRING
  "Flags used by the CXX compiler during all build types" FORCE)
set(CMAKE_C_FLAGS_DEBUG "-Og -g" CACHE STRING
  "Flags used by the C compiler during DEBUG builds" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g" CACHE STRING
  "Flags used by the CXX compiler during DEBUG builds" FORCE)
