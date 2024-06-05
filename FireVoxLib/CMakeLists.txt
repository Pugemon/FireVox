cmake_minimum_required(VERSION 3.13)
project(FireVoxLib)

add_library(FireVoxLib INTERFACE)

target_include_directories(FireVoxLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
