cmake_minimum_required(VERSION 3.13)
PROJECT(hw8)

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS -std=c++14)

add_executable(main functional_forms.hpp test_lambdas.cpp poly.hpp)

include_directories(${PROJECT_SOURCE_DIR})

link_directories(${PROJECT_SOURCE_DIR})

#SUBDIRS( test )