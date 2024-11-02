#include <string>

namespace OpenGLRenderer
{
    class Texture2D
    {
        public:
            Texture2D(const std::string& texturePath);
            ~Texture2D();

            void Bind(GLenum textureUnit);

        private:
            unsigned int m_TextureID;
    };
}