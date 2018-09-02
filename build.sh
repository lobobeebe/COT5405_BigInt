mkdir build
cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_SH="CMAKE_SH-NOTFOUND"
mingw32-make
