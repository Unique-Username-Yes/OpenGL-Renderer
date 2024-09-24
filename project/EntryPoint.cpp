#include "OpenGLRenderer/Application.h"

int main()
{
    OpenGLRenderer::Application sandbox {OpenGLRenderer::WindowProps{}};
    sandbox.Run();

    return 0;
}
