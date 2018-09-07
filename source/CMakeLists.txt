add_executable(Main main.cpp)
target_link_libraries (Main LINK_PUBLIC BigInt)

add_subdirectory (BigInt)
add_subdirectory (test)
