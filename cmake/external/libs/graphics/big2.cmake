#
include(FetchContent)
#
# BIG2 external libs
#
message(STATUS "Starting download of big2-stack...")

FetchContent_Declare(
        big2
        GIT_REPOSITORY "https://github.com/Paper-Cranes-Ltd/big2-stack.git"
        GIT_TAG "v0.0.9"
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_GetProperties(big2)
if(NOT big2_POPULATED)
  FetchContent_MakeAvailable(big2)
endif()
message(STATUS "big2-stack has been downloaded to ${big2_SOURCE_DIR}")

target_link_libraries(${PROJECT_NAME} PRIVATE BIG2)
