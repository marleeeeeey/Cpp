CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

MESSAGE("*****************************************************************")
MESSAGE("STD_PLUS_DIR=$ENV{STD_PLUS_DIR}")
message("GTEST_ROOT=$ENV{GTEST_ROOT}")
MESSAGE("*****************************************************************")
    
PROJECT(FunctionsTest)

# ***********************************************************

if(MSVC)
  # Force to always compile with W4
  IF(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    STRING(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  ELSE()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  ENDIF()
ELSEIF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
ENDIF()

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
