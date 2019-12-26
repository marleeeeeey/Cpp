cmake_minimum_required(VERSION 3.2)

project(ArkanoidProject)

#Arkanoid
function(custom_add_executable_from_dir TARGET DIR)
    file(GLOB TARGET_SRC "${DIR}/*.*")
    add_executable(${TARGET} ${TARGET_SRC})
endfunction()
custom_add_executable_from_dir(arkanoid src)
target_compile_features(arkanoid PUBLIC cxx_std_17)

#SFML
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)
target_link_libraries(arkanoid sfml-graphics sfml-system sfml-window)
