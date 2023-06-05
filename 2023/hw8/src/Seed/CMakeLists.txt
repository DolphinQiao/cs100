cmake_minimum_required(VERSION 3.16)

add_library(
  Seed
  STATIC
  Seed.hpp
  Seed.cpp
)

target_link_libraries(
  Seed
  Framework
  GameWorld
  GameObject
  Plant
  Zombie
  Background
)

target_include_directories(
  Seed
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/Framework/
  ${CMAKE_SOURCE_DIR}/src/GameWorld/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
  ${CMAKE_SOURCE_DIR}/src/Plant/
  ${CMAKE_SOURCE_DIR}/src/Zombie/
  ${CMAKE_SOURCE_DIR}/src/Background/
)
