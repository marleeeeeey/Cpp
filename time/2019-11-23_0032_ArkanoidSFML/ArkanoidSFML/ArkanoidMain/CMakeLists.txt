cmake_minimum_required(VERSION 3.16)

function(custom_add_executable TARGET)
    file(GLOB TARGET_SRC "src/*.*")
    add_executable(${TARGET} ${TARGET_SRC})
endfunction()
custom_add_executable(arkanoid)
target_compile_features(arkanoid PUBLIC cxx_std_17)
target_link_libraries(arkanoid arkanoid_lib)
