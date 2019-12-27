cmake_minimum_required(VERSION 3.2)

project(Arkanoid)

set(GTEST_ROOT "C:/Program Files (x86)/googletest-distribution/")
find_package(GTest REQUIRED)

set(GMOCK_ROOT "${GTEST_ROOT}")
find_package(GMock REQUIRED)

add_subdirectory(ArkanoidLib)
add_subdirectory(ArkanoidMain)