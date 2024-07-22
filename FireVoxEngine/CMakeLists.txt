cmake_minimum_required(VERSION 3.13)

project(
        FireVoxEngine
        VERSION 0.0.3
        DESCRIPTION "Open source 3D voxel engine"
        HOMEPAGE_URL "https://github.com/Pugemon/FireVox"
        LANGUAGES CXX
)

set(PROJECT_SOURCE_DIR "src")

message(STATUS "${PROJECT_SOURCE_DIR}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

FILE(GLOB_RECURSE HEADER_FILES "${PROJECT_SOURCE_DIR}/*.hpp")
FILE(GLOB_RECURSE SOURCE_FILES "${PROJECT_SOURCE_DIR}/*.cpp")


add_executable(FireVoxEngine ${SOURCE_FILES} ${HEADER_FILES})


target_link_libraries(FireVoxEngine PRIVATE FireVoxLib)


source_group(
        TREE ${CMAKE_CURRENT_SOURCE_DIR}
        PREFIX "FireVoxEngine"
        FILES ${SOURCE_FILES} ${HEADER_FILES}
)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif ()

message(STATUS "AAAAAAAAAAAAAAAAAAAAAAAAA")

include(LibsCaching)

include(GraphicsLibs)

set(SHADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/shaders")
add_shaders_directory("${SHADERS_DIR}" SHADERS_TARGET_NAME)
target_link_libraries("${PROJECT_NAME}" PUBLIC "${SHADERS_TARGET_NAME}")

include(LoggingLibs)
