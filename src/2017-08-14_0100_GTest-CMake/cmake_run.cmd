rd build /s /q

mkdir build
cd build

::cmake .. -DGTEST_FORCE_SHARED_CRT=ON -DGTEST_DISABLE_PTHREADS=OFF
cmake ..

cd ..
pause