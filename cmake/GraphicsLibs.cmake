set(GRAPHICS_LIBS_MODULES "${CMAKE_CURRENT_LIST_DIR}/external/libs/graphics")

#
# IMGUI GLFW GLAD external libs
#
#include(${GRAPHICS_LIBS_MODULES}/imgui-glfw-glad.cmake)
#
#
# BIG2-stack external lib
#
include(${GRAPHICS_LIBS_MODULES}/big2.cmake)

find_package(OpenGL REQUIRED)

set(GRAPHICS_LIBS_LINKS OpenGL::GL)

include_directories(${OPENGL_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${GRAPHICS_LIBS_LINKS})
