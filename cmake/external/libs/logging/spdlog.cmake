# SPDLOG
#

message(STATUS "Starting download of spdlog...")
set(SPDLOG_BUILD_EXAMPLES OFF CACHE BOOL "Build spdlog examples" FORCE)
set(SPDLOG_BUILD_TESTING OFF CACHE BOOL "Build spdlog tests" FORCE)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.14.1
)
FetchContent_MakeAvailable(spdlog)
message(STATUS "spdlog has been downloaded to ${spdlog_SOURCE_DIR}")

target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)