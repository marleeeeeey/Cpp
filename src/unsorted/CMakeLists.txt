cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)

project(local-tests)

find_package(PkgConfig)
pkg_search_module(CAIRO REQUIRED cairo)
pkg_search_module(CAIROMM REQUIRED cairomm-1.0)
pkg_search_module(OPENCV REQUIRED opencv)
pkg_search_module(FREE_TYPE2 REQUIRED freetype2)

include_directories(
    ${CAIRO_INCLUDE_DIRS}
    ${CAIROMM_INCLUDE_DIRS}
    ${OPENCV_INCLUDE_DIRS}
    ${FREE_TYPE2_INCLUDE_DIRS}
    /usr/local/include
    )

link_directories(
    ${CAIRO_LIBRARY_DIRS}
    ${CAIROMM_LIBRARY_DIRS}
    ${OPENCV_LIBRARY_DIRS}
    ${FREE_TYPE2_LIBRARY_DIRS}
    /usr/local/lib
    )

add_executable(${PROJECT_NAME}
    src/chrono_test.cpp
    )

target_link_libraries(${PROJECT_NAME}
    ${CAIRO_LIBRARIES}
    ${CAIROMM_LIBRARIES}
    ${OPENCV_LIBRARIES}
    ${FREE_TYPE2_LIBRARIES}
    pthread
    config++
    )

