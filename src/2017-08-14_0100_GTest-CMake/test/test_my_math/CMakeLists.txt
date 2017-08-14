PROJECT(my_math_lib_test)
ENABLE_TESTING()

# gtest #

FIND_PATH(GTEST_INCLUDE_DIR
          NAMES gtest/gtest.h
          HINTS $ENV{GTEST_ROOT}
          PATH_SUFFIXES include)

SET(GMOCK_ROOT $ENV{GTEST_ROOT}../googlemock/)
          
FIND_PATH(GMOCK_INCLUDE_DIR
          NAMES gmock/gmock.h
          HINTS ${GMOCK_ROOT}
          PATH_SUFFIXES include)

message("**************************************")
message("GTEST_ROOT="$ENV{GTEST_ROOT})
message("GMOCK_ROOT="${GMOCK_ROOT})
message("GTEST_INCLUDE_DIR="${GTEST_INCLUDE_DIR})
message("GMOCK_INCLUDE_DIR="${GMOCK_INCLUDE_DIR})
message("**************************************")
          
INCLUDE_DIRECTORIES(SYSTEM 
                    ${GTEST_INCLUDE_DIR}
                    ${GMOCK_INCLUDE_DIR})

LINK_DIRECTORIES(SYSTEM 
                 $ENV{GTEST_ROOT}../build/googlemock/
                 $ENV{GTEST_ROOT}../build/googlemock/gtest/)                    
                    
INCLUDE_DIRECTORIES(SYSTEM my_math_lib_INCLUDE_DIRS)

ADD_EXECUTABLE(my_math_lib_test
               main.cpp
               test_my_math.cpp)

TARGET_LINK_LIBRARIES(my_math_lib_test
                      gtest 
                      gtest_main
                      gmock
                      gmock_main
                      my_math_lib)

ADD_TEST(NAME my_math_lib_test COMMAND my_math_lib_test)
