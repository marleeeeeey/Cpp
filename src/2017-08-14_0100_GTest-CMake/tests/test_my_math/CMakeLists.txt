PROJECT(my_math_lib_test)

INCLUDE_DIRECTORIES(SYSTEM my_math_lib_INCLUDE_DIRS)

ADD_EXECUTABLE(my_math_lib_test
               test_my_math.cpp)

TARGET_LINK_LIBRARIES(my_math_lib_test
                      gtest 
                      gmock
                      my_math_lib)

ADD_TEST(NAME my_math_lib_test COMMAND my_math_lib_test)
