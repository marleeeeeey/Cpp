cmake_minimum_required(VERSION 3.15)

project(TetrisSFML)

# SFML
IF (WIN32)
  set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()
find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)

add_executable(tetris
tetris.rc
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

#
# Install the executable (belongs in the "applications" component)
#
install(TARGETS tetris
        RUNTIME
        DESTINATION bin
        COMPONENT applications)

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

set(CPACK_PACKAGE_NAME "Tetris")
set(CPACK_PACKAGE_VENDOR "Sergey Tyulenev")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Tetris")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/license.txt")
set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}\\\\tetris.bmp")
set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/tetris.ico")
set(CPACK_NSIS_MENU_LINKS "bin/tetris.exe" "Tetris")

include(CPack)
