cmake_minimum_required(VERSION 3.13)
PROJECT(hw8)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS -std=c++14)

add_executable(main ${PROJECT_SOURCE_DIR}/src/poly.hpp ${PROJECT_SOURCE_DIR}/test/test_polynomials.cpp)

SUBDIRS( test )