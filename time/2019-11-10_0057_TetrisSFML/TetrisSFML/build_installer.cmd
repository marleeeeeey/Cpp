mkdir build
cd build
cmake ..
cmake --build . --config Release
cpack .
cd ..