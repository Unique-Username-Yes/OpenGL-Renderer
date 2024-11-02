#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>
#include "Texture2D.hpp"

namespace OpenGLRenderer
{
    Texture2D::Texture2D(const std::string& texturePath)
    {
        stbi_set_flip_vertically_on_load(true);

        int width, height, channels;
        unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &channels, 0);

        if(data)
        {
            GLenum imageFormat = 0;
            if(channels == 4)
            {
                imageFormat = GL_RGBA;
            }
            else if(channels == 3)
            {
                imageFormat = GL_RGB;
            }

            glGenTextures(1, &m_TextureID);
            glBindTexture(GL_TEXTURE_2D, m_TextureID);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }

        stbi_image_free(data);
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &m_TextureID);
    }

    void Texture2D::Bind(GLenum textureUnit)
    {
        glActiveTexture(textureUnit);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
    }
}