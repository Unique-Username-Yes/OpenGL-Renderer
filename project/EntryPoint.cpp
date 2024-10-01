#include "OpenGLRenderer/Application.hpp"
#include "MainLayer.hpp"

int main()
{
    OpenGLRenderer::Application sandbox {OpenGLRenderer::WindowProps{}};
    sandbox.PushLayer(new MainLayer{"Test 1"});
    sandbox.Run();

    return 0;
}
