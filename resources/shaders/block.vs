#version 330 core
layout (location = 0) in uint aBlock;

out uint block;

uniform int xOffset;
uniform int yOffset;


vec4 CalculatePosition()
{
    int x = gl_VertexID / 4096;
    int y = (gl_VertexID - x * 4096) / 256;
    int z = gl_VertexID - x * 4096 - y * 256;

    x = x + xOffset;
    y = y + yOffset;

    return vec4(x + 0.5, y + 0.5, z, 1.0);
}

void main()
{
    block = aBlock;
    gl_Position = CalculatePosition();
}