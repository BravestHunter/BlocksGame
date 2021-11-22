#version 330 core
out vec4 FragColor;

in vec2 texCoords;

// texture samplers
uniform sampler2D blockAtlasTexture;


void main()
{
    FragColor = texture(blockAtlasTexture, texCoords);
}