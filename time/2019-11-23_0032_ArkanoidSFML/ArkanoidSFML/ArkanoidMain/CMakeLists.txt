cmake_minimum_required(VERSION 3.15)

add_executable(arkanoid
src/ArkanoidMain.cpp
arkanoid.rc
)

target_compile_features(arkanoid PUBLIC cxx_std_17)
target_link_libraries(arkanoid arkanoid_lib)

# to make it works from visual studio run
add_custom_command(TARGET arkanoid 
POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/config/levels.txt
        ${CMAKE_CURRENT_BINARY_DIR}/config/levels.txt
)                

install(TARGETS arkanoid
RUNTIME
DESTINATION bin
COMPONENT applications
)

install(FILES ${CMAKE_SOURCE_DIR}/config/levels.txt 
DESTINATION config 
COMPONENT applications)