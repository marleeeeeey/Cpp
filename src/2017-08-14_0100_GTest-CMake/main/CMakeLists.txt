CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)

PROJECT(calculator)

SET(HEADER_FILES
    )

SET(SOURCE_FILES
    src/main.cpp
    )
    
ADD_EXECUTABLE(calculator ${SOURCE_FILES} ${HEADER_FILES})

# Specify here the libraries this program depends on
TARGET_LINK_LIBRARIES(calculator
    my_math_lib
    )
