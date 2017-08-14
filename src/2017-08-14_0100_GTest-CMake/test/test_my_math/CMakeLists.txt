CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(basic_test)

INCLUDE_DIRECTORIES(
    ${gtest_SOURCE_DIR}/include 
    ${gtest_SOURCE_DIR}    
    )

FILE(GLOB SRCS *.cpp)

ADD_EXECUTABLE(test_my_math ${SRCS})

TARGET_LINK_LIBRARIES(test_my_math
    my_math_lib
    gtest 
    gtest_main
)

ADD_TEST(NAME test_my_math
         COMMAND test_my_math)
        