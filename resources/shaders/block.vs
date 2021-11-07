#version 330 core
layout (location = 0) in int aBlock;


vec4 CalculatePosition()
{
    int x = gl_VertexID / 256;
    int y = (gl_VertexID - x * 256) / 16;
    int z = gl_VertexID - x * 256 - y * 16;

    return vec4(x, y, z, 1.0);
}

void main()
{
    gl_Position = CalculatePosition();
}