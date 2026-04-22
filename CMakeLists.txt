cmake_minimum_required(VERSION 3.23)

project(
  Minesweeper
  VERSION 1.0
  DESCRIPTION "Snake"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
  CMAKE_RUNTIME_OUTPUT_DIRECTORY
  "${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)

set(
  CMAKE_LIBRARY_OUTPUT_DIRECTORY
  "${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)

add_executable(Snake
  src/main.cpp
  src/Cell.cpp
  # src/MonsterType.cpp
  # src/GameObject.cpp
  src/BoundingBox.cpp
  src/ImageComponent.cpp
  src/InputComponent.cpp
  src/Commands.cpp
  src/Component.cpp
  src/PhysicsComponent.cpp
  src/CollisionComponent.cpp
  src/Scene.cpp
)

target_include_directories(Snake
  PRIVATE ${PROJECT_SOURCE_DIR}/src
)

if(APPLE)
  set_target_properties(Snake PROPERTIES
    INSTALL_RPATH "@executable_path;@loader_path"
    BUILD_WITH_INSTALL_RPATH TRUE
    MACOSX_RPATH TRUE
  )
elseif(UNIX)
  set_target_properties(Snake PROPERTIES
    INSTALL_RPATH "$ORIGIN"
    BUILD_WITH_INSTALL_RPATH TRUE
  )
endif()

set(SDLTTF_VENDORED ON)
set(VENDOR_DIR "${PROJECT_SOURCE_DIR}/vendor")
add_subdirectory(${VENDOR_DIR}/SDL)
add_subdirectory(${VENDOR_DIR}/SDL_image)
add_subdirectory(${VENDOR_DIR}/SDL_ttf)

target_link_libraries(Snake
  SDL3::SDL3
  SDL3_image::SDL3_image
  SDL3_ttf::SDL3_ttf
)
