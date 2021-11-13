#version 330 core
layout (location = 0) in int aBlock;

out int block;

out VS_TO_GEOM {
    int block;
} vs_to_geom;


vec4 CalculatePosition()
{
    int x = gl_VertexID / 4096;
    int y = (gl_VertexID - x * 4096) / 256;
    int z = gl_VertexID - x * 4096 - y * 256;

    return vec4(x, y, z, 1.0);
}

void main()
{
    vs_to_geom.block = aBlock;
    gl_Position = CalculatePosition();
}