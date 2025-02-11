cmake_minimum_required(VERSION 3.31)
project(
  "zide"
  VERSION 0.0.1
  DESCRIPTION "ZIDE Is a Design Environment")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES src/zide.cpp)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

include(CTest)

add_subdirectory(external)
add_subdirectory(tests)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
