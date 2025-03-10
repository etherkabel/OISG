cmake_minimum_required(VERSION 3.16)
project(OISG VERSION 0.1)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(libs/SDL EXCLUDE_FROM_ALL)

# Create your game executable target as usual
add_executable(OISG src/main.cpp)

# Link to the actual SDL3 library.
target_link_libraries(OISG PRIVATE SDL3::SDL3)

# set the project name
# project(OISG VERSION 0.1)

# Specify the directory where SDL will be downloaded and built
# set(SDL_SOURCE_DIR "${CMAKE_SOURCE_DIR}/lib/sdl")
# set(SDL_INSTALL_DIR "${CMAKE_BINARY_DIR}/sdl-install")

# file(MAKE_DIRECTORY "${SDL_SOURCE_DIR}/build")

# # Add SDL as an external project
# ExternalProject_Add(sdl
#         GIT_REPOSITORY https://github.com/libsdl-org/SDL
#         GIT_TAG main
#         SOURCE_DIR "${SDL_SOURCE_DIR}"
#         BINARY_DIR "${CMAKE_SOURCE_DIR}/lib/sdl-build"
#         INSTALL_DIR "${SDL_INSTALL_DIR}"
#         CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${SDL_INSTALL_DIR} -DSDL_WAYLAND=ON
#         )

# # Specify the include directory and library directory for SDL
# include_directories(${SDL_INSTALL_DIR}/include)
# link_directories(${SDL_INSTALL_DIR}/lib)

# # specify the C++ standard
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# # add the executable
# add_executable(OISG src/main.cpp)

# # Link SDL to your executable
# target_link_libraries(OISG SDL3)

# # Ensure SDL is built before OISG
# add_dependencies(OISG sdl)
