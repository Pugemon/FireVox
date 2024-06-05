#
include(FetchContent)
#
# GLFW GLAD IMGUI external libs
#
message(STATUS "Starting download of imgui-glfw-glad...")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build GLFW docs")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW tests")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW examples")
set(GLFW_INSTALL OFF CACHE BOOL "Install GLFW")

set(IGG_COMPONENTS "IMGUI;GLFW;GLAD")
set(IGG_GLAD_DOWNLOAD ON)
set(IGG_GLAD_GL_CORE ON)
set(IGG_GLAD_GL_VERSION "4.6")
set(IGG_IMGUI_TAG "v1.90.6")
set(IGG_GLFW_TAG "3.4")
FetchContent_Declare(
        imgui-glfw-glad
        GIT_REPOSITORY https://github.com/cmmw/imgui-glfw-glad-glm.git
        GIT_TAG "v4.2.0"
)
FetchContent_MakeAvailable(imgui-glfw-glad)

message(STATUS "imgui-glfw-glad has been downloaded to ${imgui-glfw-glad_SOURCE_DIR}")

target_link_libraries(${PROJECT_NAME} PRIVATE imgui glfw glad)