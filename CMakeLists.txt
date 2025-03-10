cmake_minimum_required(VERSION 3.10)
include(ExternalProject)

# set the project name
project(OISG VERSION 0.1)

# Specify the directory where SDL will be downloaded and built
set(SDL_SOURCE_DIR "${CMAKE_SOURCE_DIR}/lib/sdl")
set(SDL_INSTALL_DIR "${CMAKE_BINARY_DIR}/sdl-install")

file(MAKE_DIRECTORY "${SDL_SOURCE_DIR}/build")

# Add SDL as an external project
ExternalProject_Add(sdl
        GIT_REPOSITORY https://github.com/libsdl-org/SDL
        GIT_TAG main
        SOURCE_DIR "${SDL_SOURCE_DIR}"
        BINARY_DIR "${SDL_SOURCE_DIR}/build"
        INSTALL_DIR "${SDL_INSTALL_DIR}"
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${SDL_INSTALL_DIR}
        )

# Specify the include directory and library directory for SDL
include_directories(${SDL_INSTALL_DIR}/include)
link_directories(${SDL_INSTALL_DIR}/lib)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(OISG src/main.cpp)

# Link SDL to your executable
target_link_libraries(OISG SDL3)

# Ensure SDL is built before OISG
add_dependencies(OISG sdl)