# CMakeList.txt : Top-level CMake project file, do global configuration
cmake_minimum_required (VERSION 4.0)
project (tutorial C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # clang-tidy needs compile flags to work properly. compile_commands.json

# CPM.cmake
include(${CMAKE_CURRENT_SOURCE_DIR}/CPM.cmake)
include(${CMAKE_SOURCE_DIR}/Unix.cmake)
