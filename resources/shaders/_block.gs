#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 24) out;

out vec2 texCoords;

in uint block[];

// View * Projection
uniform mat4 VP;

#define TEXEL_SIZE 0.25


vec2[4] getTexelCoords(uint index)
{
    vec2[4] coords;

    uint y = index / 4u;
    uint x = index - y * 4u;

    float left = float(x) * TEXEL_SIZE;
    float right = left + TEXEL_SIZE;
    float bottom = (3.0 - float(y)) * TEXEL_SIZE;
    float top = bottom + TEXEL_SIZE;

    coords[0] = vec2(left, bottom);
    coords[1] = vec2(right, bottom);
    coords[2] = vec2(left, top);
    coords[3] = vec2(right, top);

    return coords;   
}

void build_x_positive(vec4 center, vec2[4] coords)
{
    gl_Position = VP * (center + vec4(0.5, -0.5, -0.5, 0.0));
    texCoords = coords[0];
    EmitVertex();

    gl_Position = VP * (center + vec4(0.5, 0.5, -0.5, 0.0));
    texCoords = coords[1];
    EmitVertex();

    gl_Position = VP * (center + vec4(0.5, -0.5, 0.5, 0.0));
    texCoords = coords[2];
    EmitVertex();

    gl_Position = VP * (center + vec4(0.5, 0.5, 0.5, 0.0));
    texCoords = coords[3];
    EmitVertex();

    EndPrimitive();
}

void build_x_negative(vec4 center, vec2[4] coords)
{
    gl_Position = VP * (center + vec4(-0.5, 0.5, -0.5, 0.0));
    texCoords = coords[0];
    EmitVertex();

    gl_Position = VP * (center + vec4(-0.5, -0.5, -0.5, 0.0));
    texCoords = coords[1];
    EmitVertex();

    gl_Position = VP * (center + vec4(-0.5, 0.5, 0.5, 0.0));
    texCoords = coords[2];
    EmitVertex();

    gl_Position = VP * (center + vec4(-0.5, -0.5, 0.5, 0.0));
    texCoords = coords[3];
    EmitVertex();

    EndPrimitive();
}

void build_y_positive(vec4 center, vec2[4] coords)
{
    gl_Position = VP * (center + vec4(0.5, 0.5, -0.5, 0.0));
    texCoords = coords[0];
    EmitVertex();

    gl_Position = VP * (center + vec4(-0.5, 0.5, -0.5, 0.0));
    texCoords = coords[1];
    EmitVertex();

    gl_Position = VP * (center + vec4(0.5, 0.5, 0.5, 0.0));
    texCoords = coords[2];
    EmitVertex();

    gl_Position = VP * (center + vec4(-0.5, 0.5, 0.5, 0.0));
    texCoords = coords[3];
    EmitVertex();

    EndPrimitive();
}

void build_y_negative(vec4 center, vec2[4] coords)
{
    gl_Position = VP * (center + vec4(-0.5, -0.5, -0.5, 0.0));
    texCoords = coords[0];
    EmitVertex();

    gl_Position = VP * (center + vec4(0.5, -0.5, -0.5, 0.0));
    texCoords = coords[1];
    EmitVertex();

    gl_Position = VP * (center + vec4(-0.5, -0.5, 0.5, 0.0));
    texCoords = coords[2];
    EmitVertex();

    gl_Position = VP * (center + vec4(0.5, -0.5, 0.5, 0.0));
    texCoords = coords[3];
    EmitVertex();

    EndPrimitive();
}

void build_z_positive(vec4 center, vec2[4] coords)
{
    gl_Position = VP * (center + vec4(0.5, 0.5, 0.5, 0.0));
    texCoords = coords[0];
    EmitVertex();

    gl_Position = VP * (center + vec4(-0.5, 0.5, 0.5, 0.0));
    texCoords = coords[1];
    EmitVertex();

    gl_Position = VP * (center + vec4(0.5, -0.5, 0.5, 0.0));
    texCoords = coords[2];
    EmitVertex();

    gl_Position = VP * (center + vec4(-0.5, -0.5, 0.5, 0.0));
    texCoords = coords[3];
    EmitVertex();

    EndPrimitive();
}

void build_z_negative(vec4 center, vec2[4] coords)
{
    gl_Position = VP * (center + vec4(-0.5, 0.5, -0.5, 0.0));
    texCoords = coords[0];
    EmitVertex();

    gl_Position = VP * (center + vec4(0.5, 0.5, -0.5, 0.0));
    texCoords = coords[1];
    EmitVertex();

    gl_Position = VP * (center + vec4(-0.5, -0.5, -0.5, 0.0));
    texCoords = coords[2];
    EmitVertex();

    gl_Position = VP * (center + vec4(0.5, -0.5, -0.5, 0.0));
    texCoords = coords[3];
    EmitVertex();

    EndPrimitive();
}

void main() 
{
    if (block[0] == 0u)
        return;

    vec4 center = gl_in[0].gl_Position;
    vec2[4] coords = getTexelCoords(block[0] - 1u);

    build_x_positive(center, coords);
    build_x_negative(center, coords);
    build_y_positive(center, coords);
    build_y_negative(center, coords);
    build_z_positive(center, coords);
    build_z_negative(center, coords);
}
