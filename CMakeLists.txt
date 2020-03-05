
cmake_minimum_required(VERSION 3.16)

project(libtest)

message(STATUS "this is" ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

message(STATUS "exe is" ${EXECUTABLE_OUTPUT_PATH})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)