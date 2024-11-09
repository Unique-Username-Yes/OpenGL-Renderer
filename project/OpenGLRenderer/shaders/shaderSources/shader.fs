#version 330 core

out vec4 FragColor;

in vec3 customColor;
in vec3 position;
in vec2 texCoord;

uniform sampler2D textureSource;
uniform sampler2D textureSource2;

void main()
{
    FragColor = mix(texture(textureSource, texCoord), texture(textureSource2, texCoord * vec2(-1, 1)), 0.2);
} 