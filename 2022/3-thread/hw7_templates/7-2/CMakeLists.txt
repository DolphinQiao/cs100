cmake_minimum_required(VERSION 2.8.12)
project(rational)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "Version is ${Template_VERSION_MAJOR}.${Template_VERSION_MINOR}")

add_library(static_lib STATIC rational.hpp rational.cpp matrix.cpp)
#add_library(main STATIC tests.cpp mat static_lib)

#add_library(main test.cpp)

add_executable(main tests.cpp)

include_directories(${PROJECT_SOURCE_DIR})

link_directories(${PROJECT_SOURCE_DIR})

target_link_libraries(main static_lib)