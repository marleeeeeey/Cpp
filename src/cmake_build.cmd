call cmake_run.cmd

mkdir build
cd build

cmake --build . --config Release 
cmake --build . --config Debug 

cd ..
pause