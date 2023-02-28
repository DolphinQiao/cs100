cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME "Dawnbreaker")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

#SET(FREEGLUT_REPLACE_GLUT ON CACHE BOOL "" FORCE)

IF(APPLE)
    add_definitions(-DGL_SILENCE_DEPRECATION)
ENDIF()

add_subdirectory(
  "${CMAKE_CURRENT_LIST_DIR}/third_party/SOIL/"
  "${CMAKE_CURRENT_BINARY_DIR}/SOIL"
  EXCLUDE_FROM_ALL
)

IF (APPLE)
ELSE()
  add_subdirectory(
    "${CMAKE_CURRENT_LIST_DIR}/third_party/freeglut/"
    "${CMAKE_CURRENT_BINARY_DIR}/freeglut"
    EXCLUDE_FROM_ALL
  )
  set(FREEGLUT_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/third_party/freeglut/include")
ENDIF()


add_library(
  ProvidedFramework
  STATIC
  src/ProvidedFramework/ObjectBase.h
  src/ProvidedFramework/ObjectBase.cpp
  src/ProvidedFramework/WorldBase.h
  src/ProvidedFramework/WorldBase.cpp
  src/ProvidedFramework/GameManager.h
  src/ProvidedFramework/GameManager.cpp
  src/ProvidedFramework/SpriteManager.h
  src/ProvidedFramework/SpriteManager.cpp
  src/utils.h
)
IF (APPLE)
  target_link_libraries(
    ProvidedFramework
    SOIL
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
    "-framework GLUT"
  )

  target_include_directories(
    ProvidedFramework
    PUBLIC
    src/
    src/ProvidedFramework/
  )
ELSE()
  target_link_libraries(
    ProvidedFramework
    freeglut
    SOIL
  )

  target_include_directories(
    ProvidedFramework
    PUBLIC 
    ${FREEGLUT_INCLUDE_DIR}
    src/
    src/ProvidedFramework/
  )
ENDIF()

#Base
add_library(
  Base
  STATIC
  src/PartForYou/GameWorld.h
  src/PartForYou/GameWorld.cpp
  src/PartForYou/GameObjects.h
  src/PartForYou/GameObjects.cpp
  src/utils.h
)
target_link_libraries(
  Base
  ProvidedFramework
)

target_include_directories(
  Base
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/PartForYou/
)

#Spaceship
add_library(
  Spaceship
  STATIC
  src/PartForYou/Spaceship.h
  src/PartForYou/Spaceship.cpp
  src/utils.h
)
target_link_libraries(
  Spaceship
  ProvidedFramework
)

target_include_directories(
  Spaceship
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/PartForYou/
)

#Projectile
add_library(
  Projectile
  STATIC
  src/PartForYou/Projectile.h
  src/PartForYou/Projectile.cpp
  src/utils.h
)
target_link_libraries(
  Projectile
  ProvidedFramework
)

target_include_directories(
  Projectile
  PUBLIC
  src/
  src/ProvidedFramework/
  src/PartForYou/
)

#Goodie
add_library(
  Goodie
  STATIC
  src/PartForYou/Goodie.h
  src/PartForYou/Goodie.cpp
  src/utils.h
)
target_link_libraries(
  Goodie
  ProvidedFramework
)

target_include_directories(
  Goodie
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/PartForYou/
)

#Scenery
add_library(
  Scenery
  STATIC
  src/PartForYou/Scenery.h
  src/PartForYou/Scenery.cpp
  src/utils.h
)
target_link_libraries(
  Scenery
  ProvidedFramework
)

target_include_directories(
  Scenery
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/PartForYou/
)



add_executable(
  ${PROJECT_NAME}
  src/main.cpp
)

target_link_libraries(
  ${PROJECT_NAME}
  ProvidedFramework
  Base
  Projectile
  Goodie
  Scenery
  Spaceship
)

target_include_directories(
  ${PROJECT_NAME} 
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/PartForYou/
)
