cmake_minimum_required(VERSION 3.0)

project(LibBProject)

message("Hello from CMAKE LibBProject")

add_library(lib_b SHARED 
                            src/lib_b.cpp                            
)

target_include_directories(lib_b PUBLIC ./include)
target_compile_definitions(lib_b PRIVATE LIBB_BUILT_AS_DYNAMIC_LIB LIBB_EXPORTS)