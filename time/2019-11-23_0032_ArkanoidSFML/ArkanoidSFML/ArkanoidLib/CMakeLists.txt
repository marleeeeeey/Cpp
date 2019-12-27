cmake_minimum_required(VERSION 3.16)

#SFML
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)

#ArkanoidLib
function(custom_add_library TARGET)
    file(GLOB TARGET_SRC "src/*.*")
    file(GLOB TARGET_INCLUDE "include/*.*")
    add_library(${TARGET} ${TARGET_SRC} ${TARGET_INCLUDE})
endfunction()
custom_add_library(arkanoid_lib)
target_compile_features(arkanoid_lib PUBLIC cxx_std_17)
target_include_directories(arkanoid_lib PUBLIC "include")
target_include_directories(arkanoid_lib PRIVATE "${GTEST_INCLUDE_DIR}")
target_link_libraries(arkanoid_lib sfml-graphics sfml-system sfml-window)

#Tests
enable_testing()
function(custom_add_executable_tests TARGET)
    file(GLOB TARGET_SRC "tests/*.*")
    add_executable(${TARGET} ${TARGET_SRC})
    add_test(${TARGET} ${TARGET})
endfunction()
custom_add_executable_tests(arkanoid_tests)
target_link_libraries(arkanoid_tests GTest::GTest GTest::Main GMock::GMock GMock::Main arkanoid_lib)
target_include_directories(arkanoid_tests PRIVATE src include)
