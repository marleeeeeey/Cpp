ENABLE_TESTING()

FIND_PATH(GTEST_INCLUDE_DIR
          NAMES gtest/gtest.h
          HINTS $ENV{GTEST_ROOT}googletest
          PATH_SUFFIXES include)
          
FIND_PATH(GMOCK_INCLUDE_DIR
          NAMES gmock/gmock.h
          HINTS $ENV{GTEST_ROOT}googlemock
          PATH_SUFFIXES include)

message("**************************************")
message("GTEST_ROOT="$ENV{GTEST_ROOT})
message("GTEST_INCLUDE_DIR="${GTEST_INCLUDE_DIR})
message("GMOCK_INCLUDE_DIR="${GMOCK_INCLUDE_DIR})
message("**************************************")
          
INCLUDE_DIRECTORIES(SYSTEM 
                    ${GTEST_INCLUDE_DIR}
                    ${GMOCK_INCLUDE_DIR})

LINK_DIRECTORIES(SYSTEM 
                 $ENV{GTEST_ROOT}build/googlemock/
                 $ENV{GTEST_ROOT}build/googlemock/gtest/)                                        

#*************************************************************                 
#*************************************************************
                 
ADD_SUBDIRECTORY(test_my_math)
