CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

MESSAGE("*****************************************************************")
MESSAGE("STD_PLUS_DIR=$ENV{STD_PLUS_DIR}")
message("GTEST_ROOT=$ENV{GTEST_ROOT}")
MESSAGE("*****************************************************************")
    
PROJECT(FunctionsTest)

# ***********************************************************

ENABLE_TESTING()

FIND_PATH(GTEST_INCLUDE_DIR
          NAMES gtest/gtest.h
          HINTS $ENV{GTEST_ROOT}googletest
          PATH_SUFFIXES include)
          
FIND_PATH(GMOCK_INCLUDE_DIR
          NAMES gmock/gmock.h
          HINTS $ENV{GTEST_ROOT}googlemock
          PATH_SUFFIXES include)

INCLUDE_DIRECTORIES(SYSTEM 
                    ${GTEST_INCLUDE_DIR}
                    ${GMOCK_INCLUDE_DIR})
                
LINK_DIRECTORIES(SYSTEM 
                 $ENV{GTEST_ROOT}build/googlemock/
                 $ENV{GTEST_ROOT}build/googlemock/gtest)    

INCLUDE_DIRECTORIES(
    $ENV{STD_PLUS_DIR}/include
    src)
    
# ***********************************************************

ADD_EXECUTABLE(FunctionsTest
    src/functions.h
    src/functions.cpp
    src/testMain.cpp)
 
TARGET_LINK_LIBRARIES(FunctionsTest
                      gtest 
                      gmock)    

ADD_TEST(NAME FunctionsTest COMMAND FunctionsTest)    
