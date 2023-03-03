cmake_minimum_required(VERSION 2.8)

project(algorithm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE Debug)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../bin)

include_directories(./include)

aux_source_directory(./src SRC)

add_executable(algorithm ${SRC})
