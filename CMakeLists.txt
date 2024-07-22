cmake_minimum_required(VERSION 3.13)

project(
        FireVox
        DESCRIPTION "Open source 3D voxel engine"
        HOMEPAGE_URL "https://github.com/Pugemon/FireVox"
)

set(CMAKE_CXX_STANDARD 23 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

add_subdirectory(FireVoxLib)
add_subdirectory(FireVoxEngine)
