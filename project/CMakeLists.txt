project(Renderer)

include_directories(./vendors/glad)

find_package(OpenGL REQUIRED)

include_directories(
    vendors/glad/include
    vendors/stb_image
)

add_executable(OGLRenderer 
    EntryPoint.cpp
    OpenGLRenderer/shaders/ShaderHandler.cpp 
    OpenGLRenderer/Application.cpp
    OpenGLRenderer/LayerStack.cpp
    OpenGLRenderer/Layer.cpp
    OpenGLRenderer/Window.cpp
    OpenGLRenderer/Renderer/Texture2D.cpp
    vendors/glad/src/glad.c
    vendors/stb_image/stb_image.cpp
)

target_link_libraries(OGLRenderer glfw)