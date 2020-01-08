cmake_minimum_required(VERSION 3.15)

add_executable(arkanoid
src/ArkanoidMain.cpp
arkanoid.rc
)

target_compile_features(arkanoid PUBLIC cxx_std_17)
target_link_libraries(arkanoid arkanoid_lib)

install(TARGETS arkanoid
        RUNTIME
        DESTINATION bin
        COMPONENT applications)
