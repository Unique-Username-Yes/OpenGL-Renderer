project(Renderer)

include_directories(./vendors/glad)

find_package(OpenGL REQUIRED)

include_directories(vendors/glad/include)

add_executable(OGLRenderer main.cpp main.h vendors/glad/src/glad.c vendors/glad/include/glad/glad.h)
target_link_libraries(OGLRenderer glfw)