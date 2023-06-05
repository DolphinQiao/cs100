cmake_minimum_required(VERSION 3.16)

add_library(
  Zombie
  STATIC
  Zombie.hpp
  Zombie.cpp
)

target_link_libraries(
  Zombie
  Framework
  GameWorld
  GameObject
  Plant
  Seed
  Background
)

target_include_directories(
  Zombie
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/Framework/
  ${CMAKE_SOURCE_DIR}/src/GameWorld/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
  ${CMAKE_SOURCE_DIR}/src/Plant/
  ${CMAKE_SOURCE_DIR}/src/Seed/
  ${CMAKE_SOURCE_DIR}/src/Background/
)
