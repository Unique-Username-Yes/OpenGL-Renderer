#include "OpenGLRenderer/Application.hpp"
#include "MainLayer.hpp"

int main()
{
    OpenGLRenderer::Application sandbox {OpenGLRenderer::WindowProps{}};
    sandbox.PushLayer(new MainLayer{});
    sandbox.Run();

    return 0;
}
