cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)

project(face_detector)

find_package(PkgConfig)
pkg_search_module(OPENCV REQUIRED opencv)

include_directories(
    ${OPENCV_INCLUDE_DIRS}
    )

link_directories(
    ${OPENCV_LIBRARY_DIRS}
    )

add_executable(${PROJECT_NAME}
    src/main.cpp
    )

target_link_libraries(${PROJECT_NAME}
    ${OPENCV_LIBRARIES}
    pthread
    config++
    )

