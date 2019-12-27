cmake_minimum_required(VERSION 3.2)

project(Arkanoid)

set(GTEST_ROOT "C:/Program Files (x86)/googletest-distribution/")
find_package(GTest REQUIRED)

# TODO: https://github.com/cucumber/cucumber-cpp/blob/master/cmake/modules/FindGMock.cmake
# Doesn't work correctly in the Debug config. To fix it add 'd' suffix in the gen files:
#  gmock.lib -> gmockd.lib
set(GMOCK_ROOT "${GTEST_ROOT}")
find_package(GMock REQUIRED)

add_subdirectory(ArkanoidLib)
add_subdirectory(ArkanoidMain)