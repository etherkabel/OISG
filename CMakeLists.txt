cmake_minimum_required(VERSION 3.10)

# set the project name
project(OISG VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(OISG src/main.cpp)
