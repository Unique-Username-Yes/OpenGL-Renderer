project(Renderer)

include_directories(./vendors/glad)

find_package(OpenGL REQUIRED)

include_directories(vendors/glad/include)

add_executable(OGLRenderer 
    EntryPoint.cpp
    OpenGLRenderer/shaders/ShaderHandler.h OpenGLRenderer/shaders/ShaderHandler.cpp 
    OpenGLRenderer/Application.cpp OpenGLRenderer/Application.h
    vendors/glad/src/glad.c vendors/glad/include/glad/glad.h
)

target_link_libraries(OGLRenderer glfw)