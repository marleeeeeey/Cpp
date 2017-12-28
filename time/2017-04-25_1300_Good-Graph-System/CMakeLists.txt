cmake_minimum_required(VERSION 2.8.11)

project(GoodGraphSystem)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)


INCLUDE_DIRECTORIES(
    $ENV{STD_PLUS_DIR}/include
    $ENV{QT_PLUS_DIR}/include
    src
    )


message("******************************************")
message($ENV{STD_PLUS_DIR})
message($ENV{QT_PLUS_DIR})
message("******************************************")

# Tell CMake to create the helloworld executable
add_executable(GoodGraphSystem WIN32 
    src/AllInclude.h
    src/Application.cpp
    src/Application.h
    src/mainGraphSystem.cpp
    src/Sector.h
    )


# Use the Widgets module from Qt 5.
target_link_libraries(GoodGraphSystem Qt5::Widgets)
