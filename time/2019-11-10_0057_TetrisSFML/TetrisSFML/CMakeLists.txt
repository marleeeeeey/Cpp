cmake_minimum_required(VERSION 3.15)

project(TetrisSFML)

#SFML
IF (WIN32)
  set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()
find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)

add_executable(tetris 
src/Cell.cpp
src/Cell.h
src/Game.cpp
src/Game.h
src/Info.cpp
src/Info.h
src/Lines.hpp
src/Martrix.cpp
src/Matrix.h
src/Object.cpp
src/Object.h
src/TetrisMain.cpp
)

target_compile_features(tetris PUBLIC cxx_std_17)
target_link_libraries(tetris sfml-graphics sfml-system sfml-window)
