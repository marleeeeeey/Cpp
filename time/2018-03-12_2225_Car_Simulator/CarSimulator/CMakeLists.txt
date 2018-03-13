cmake_minimum_required (VERSION 3.8)

add_library (CarSimulator 
    "src/CarSimulator.cpp" 
)

add_executable(CarClient
    "src/CarClient.cpp"
)

target_link_libraries(CarClient 
    "CarSimulator.lib"
)
#add_subdirectory(test)
