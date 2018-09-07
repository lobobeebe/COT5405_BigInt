add_library (BigInt BigInt.cpp BigInt.h)

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (BigInt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
