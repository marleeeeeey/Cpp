CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)

PROJECT(calculator)

ENABLE_TESTING()

SET(GTEST_FORCE_SHARED_CRT ON)
SET(GTEST_DISABLE_PTHREADS OFF)

message("********************************************************")
message(${GTEST_FORCE_SHARED_CRT})
message(${GTEST_DISABLE_PTHREADS})
message("********************************************************")

ADD_SUBDIRECTORY(googletest)
ADD_SUBDIRECTORY(main)
ADD_SUBDIRECTORY(my_math_lib)
ADD_SUBDIRECTORY(test)
