cmake_minimum_required (VERSION 2.8.11)
project (BigInt)

set (CMAKE_CXX_STANDARD 11)
if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++)
endif()

add_subdirectory (source)
