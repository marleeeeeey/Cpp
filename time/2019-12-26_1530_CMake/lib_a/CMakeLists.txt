cmake_minimum_required(VERSION 3.0)

project(LibAProject)

message("Hello from CMAKE LibAProject")

add_library(lib_a STATIC 
                            src/lib_a.cpp
                            src/secret_msg.cpp
)

target_include_directories(lib_a PUBLIC ./include)
target_include_directories(lib_a PRIVATE ./src/private_include)
