cmake_minimum_required(VERSION 2.8)
project(kmeans)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR})

message(STATUS "Version is ${Template_VERSION_MAJOR}.${Template_VERSION_MINOR}")

#add_library(static_lib STATIC kmeans.hpp kmeans.cpp)

#add_library(main test.cpp)

add_executable(main main.cpp kmeans.hpp kmeans.cpp)

include_directories(${PROJECT_SOURCE_DIR})

link_directories(${PROJECT_SOURCE_DIR})