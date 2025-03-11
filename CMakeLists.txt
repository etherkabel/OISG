cmake_minimum_required(VERSION 3.14)
project(OISG VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(lib/SDL EXCLUDE_FROM_ALL)
add_subdirectory(lib/SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(lib/SDL_ttf EXCLUDE_FROM_ALL)

file(GLOB_RECURSE sources src/*.cpp src/*.h)
add_executable(OISG ${sources})

target_link_libraries(OISG PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)
