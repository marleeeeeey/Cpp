cmake_minimum_required(VERSION 3.0)

project(HelloFromCppProject)

message("Hello from HelloFromCppProject")

add_executable(hello_from_cpp src/main.cpp)

target_link_libraries(hello_from_cpp lib_a)
add_subdirectory(lib_a)

target_link_libraries(hello_from_cpp lib_b)
target_compile_definitions(hello_from_cpp PRIVATE LIBB_BUILT_AS_DYNAMIC_LIB)
add_subdirectory(lib_b)