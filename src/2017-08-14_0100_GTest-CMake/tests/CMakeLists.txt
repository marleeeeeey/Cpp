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
    
## if you want to find auto in enviroment folders
## you can use this way:                    
#FIND_LIBRARY(GTEST_LIBRARY gtest)                    
#FIND_LIBRARY(GMOCK_LIBRARY gmock)                    
                    
message("**************************************")
message("GTEST_ROOT="$ENV{GTEST_ROOT})
message("GTEST_INCLUDE_DIR="${GTEST_INCLUDE_DIR})
message("GMOCK_INCLUDE_DIR="${GMOCK_INCLUDE_DIR})
message("**************************************")
          
                 
ADD_SUBDIRECTORY(test_my_math)
