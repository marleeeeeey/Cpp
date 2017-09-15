CMAKE_MINIMUM_REQUIRED(VERSION 3.9.0)

PROJECT(cmd_parser_crosscompile)

FILE(GLOB_RECURSE SOURCE_FILES
    "*.cpp"
    "*.c"
    "*.h"
    "*.hpp")

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES})
