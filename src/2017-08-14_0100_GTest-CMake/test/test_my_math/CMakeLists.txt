cmake_minimum_required(VERSION 2.6)

project(basic_test)

enable_testing()

include_directories(
    ${gtest_SOURCE_DIR}/include 
    ${gtest_SOURCE_DIR}    
    )


file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(test_my_math ${SRCS})

TARGET_LINK_LIBRARIES(test_my_math
    my_math_lib
    gtest gtest_main
)

add_test(NAME test_my_math
         COMMAND test_my_math)

         
#################################
## Unit Tests
#################################
## Add test cpp file
#add_executable( runUnitTests testgtest.cpp )
## Link test executable against gtest & gtest_main
#target_link_libraries(runUnitTests gtest gtest_main)
#add_test( runUnitTests runUnitTests )