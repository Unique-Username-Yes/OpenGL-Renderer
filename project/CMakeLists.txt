project(Renderer)

include_directories(./vendors/glad)

find_package(OpenGL REQUIRED)

include_directories(vendors/glad/include)

add_executable(OGLRenderer 
    EntryPoint.cpp
    OpenGLRenderer/shaders/ShaderHandler.cpp 
    OpenGLRenderer/Application.cpp
    OpenGLRenderer/LayerStack.cpp
    OpenGLRenderer/Layer.cpp
    vendors/glad/src/glad.c
)

target_link_libraries(OGLRenderer glfw)