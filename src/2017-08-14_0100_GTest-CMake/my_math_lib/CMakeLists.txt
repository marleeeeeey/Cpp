CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)

PROJECT(my_math_lib)

INCLUDE_DIRECTORIES(include/my_math)

SET(HEADER_FILES
    include/my_math/my_math.h)

SET(SOURCE_FILES
    src/my_math.cpp)
    
ADD_LIBRARY(my_math_lib ${SOURCE_FILES} ${HEADER_FILES})

TARGET_INCLUDE_DIRECTORIES(my_math_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
