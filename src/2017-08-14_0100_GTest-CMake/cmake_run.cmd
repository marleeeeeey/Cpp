rd build /s /q

mkdir build
cd build

cmake ..
::cmake --build . --config Release 
::cmake --build . --config Debug 

cd ..
pause