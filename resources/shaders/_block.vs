#version 330 core
layout (location = 0) in uint aBlock;

out uint block;

uniform int xOffset;
uniform int yOffset;


vec4 CalculatePosition()
{
    int z = gl_VertexID / 256;
    int y = (gl_VertexID - z * 256) / 16;
    int x = gl_VertexID - z * 256 - y * 16;

    x = x + xOffset;
    y = y + yOffset;

    return vec4(x + 0.5, y + 0.5, z, 1.0);
}

void main()
{
    block = aBlock;
    gl_Position = CalculatePosition();
}