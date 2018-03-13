cmake_minimum_required (VERSION 3.8)

include_directories("c:/include")
add_executable(car_test "car_test_main.cpp")
target_link_libraries(car_test "c:/lib/gtestd.lib")