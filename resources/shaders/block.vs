#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 VP;


void main()
{
    TexCoords = aTexCoords;
    gl_Position = VP * vec4(aPosition, 1.0);
}
