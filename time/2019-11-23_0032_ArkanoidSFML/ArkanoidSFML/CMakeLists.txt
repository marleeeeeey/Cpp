cmake_minimum_required(VERSION 3.15)

project(Arkanoid)

include(CTest)

set(GTEST_ROOT "C:/Program Files (x86)/googletest-distribution/")
find_package(GTest REQUIRED)

# TODO: https://github.com/cucumber/cucumber-cpp/blob/master/cmake/modules/FindGMock.cmake
# Doesn't work correctly in the Debug config. To fix it add 'd' suffix in the gen files:
#  gmock.lib -> gmockd.lib
set(GMOCK_ROOT "${GTEST_ROOT}")
find_package(GMock REQUIRED)

add_subdirectory(ArkanoidLib)
add_subdirectory(ArkanoidMain)

#
# Tell CMake to install the windows runtime libraries to the programs
# directory and tell CPack that they belong to the applications component
#
set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
include(InstallRequiredSystemLibraries)
install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
        DESTINATION bin
        COMPONENT applications)

########################################################################
# CPack configuration
########################################################################

set(CPACK_PACKAGE_NAME "Arkanoid")
set(CPACK_PACKAGE_VENDOR "Sergey Tyulenev")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "9")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Arkanoid")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/license.txt")
set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}\\\\arkanoid.bmp")
set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/ArkanoidMain/arkanoid.ico")
set(CPACK_NSIS_MENU_LINKS "bin/arkanoid.exe" "Arkanoid")

include(CPack)
