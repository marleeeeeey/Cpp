CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)

PROJECT(calculator)
    
ADD_EXECUTABLE(calculator ${SOURCE_FILES} src/main.cpp)

TARGET_LINK_LIBRARIES(calculator my_math_lib)
