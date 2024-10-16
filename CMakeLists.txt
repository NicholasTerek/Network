cmake_minimum_required(VERSION 3.10)
project(ValueProject)

set(CMAKE_CXX_STANDARD 11)

# Include directories
include_directories(src)

# Add executables
add_executable(main src/Value.cpp main.cpp)
