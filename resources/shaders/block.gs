#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 24) out;

out vec2 texCoords;

// View * Projection
uniform mat4 VP;


void build_x_positive(vec4 center)
{
    gl_Position = VP * (center + vec4(0.5, -0.5, -0.5, 0.0));
    texCoords = vec2(0.0, 0.0);
    EmitVertex();

    gl_Position = VP * (center + vec4(0.5, 0.5, -0.5, 0.0));
    texCoords = vec2(1.0, 0.0);
    EmitVertex();

    gl_Position = VP * (center + vec4(0.5, -0.5, 0.5, 0.0));
    texCoords = vec2(0.0, 1.0);
    EmitVertex();

    gl_Position = VP * (center + vec4(0.5, 0.5, 0.5, 0.0));
    texCoords = vec2(1.0, 1.0);
    EmitVertex();

    EndPrimitive();
}

void build_x_negative(vec4 center)
{
    gl_Position = VP * (center + vec4(-0.5, 0.5, -0.5, 0.0));
    texCoords = vec2(0.0, 0.0);
    EmitVertex();

    gl_Position = VP * (center + vec4(-0.5, -0.5, -0.5, 0.0));
    texCoords = vec2(1.0, 0.0);
    EmitVertex();

    gl_Position = VP * (center + vec4(-0.5, 0.5, 0.5, 0.0));
    texCoords = vec2(0.0, 1.0);
    EmitVertex();

    gl_Position = VP * (center + vec4(-0.5, -0.5, 0.5, 0.0));
    texCoords = vec2(1.0, 1.0);
    EmitVertex();

    EndPrimitive();
}

void build_y_positive(vec4 center)
{
    gl_Position = VP * (center + vec4(0.5, 0.5, -0.5, 0.0));
    texCoords = vec2(0.0, 0.0);
    EmitVertex();

    gl_Position = VP * (center + vec4(-0.5, 0.5, -0.5, 0.0));
    texCoords = vec2(1.0, 0.0);
    EmitVertex();

    gl_Position = VP * (center + vec4(0.5, 0.5, 0.5, 0.0));
    texCoords = vec2(0.0, 1.0);
    EmitVertex();

    gl_Position = VP * (center + vec4(-0.5, 0.5, 0.5, 0.0));
    texCoords = vec2(1.0, 1.0);
    EmitVertex();

    EndPrimitive();
}

void build_y_negative(vec4 center)
{
    gl_Position = VP * (center + vec4(-0.5, -0.5, -0.5, 0.0));
    texCoords = vec2(0.0, 0.0);
    EmitVertex();

    gl_Position = VP * (center + vec4(0.5, -0.5, -0.5, 0.0));
    texCoords = vec2(1.0, 0.0);
    EmitVertex();

    gl_Position = VP * (center + vec4(-0.5, -0.5, 0.5, 0.0));
    texCoords = vec2(0.0, 1.0);
    EmitVertex();

    gl_Position = VP * (center + vec4(0.5, -0.5, 0.5, 0.0));
    texCoords = vec2(1.0, 1.0);
    EmitVertex();

    EndPrimitive();
}

void build_z_positive(vec4 center)
{
    gl_Position = VP * (center + vec4(0.5, 0.5, 0.5, 0.0));
    texCoords = vec2(0.0, 0.0);
    EmitVertex();

    gl_Position = VP * (center + vec4(-0.5, 0.5, 0.5, 0.0));
    texCoords = vec2(1.0, 0.0);
    EmitVertex();

    gl_Position = VP * (center + vec4(0.5, -0.5, 0.5, 0.0));
    texCoords = vec2(0.0, 1.0);
    EmitVertex();

    gl_Position = VP * (center + vec4(-0.5, -0.5, 0.5, 0.0));
    texCoords = vec2(1.0, 1.0);
    EmitVertex();

    EndPrimitive();
}

void build_z_negative(vec4 center)
{
    gl_Position = VP * (center + vec4(-0.5, 0.5, -0.5, 0.0));
    texCoords = vec2(0.0, 0.0);
    EmitVertex();

    gl_Position = VP * (center + vec4(0.5, 0.5, -0.5, 0.0));
    texCoords = vec2(1.0, 0.0);
    EmitVertex();

    gl_Position = VP * (center + vec4(-0.5, -0.5, -0.5, 0.0));
    texCoords = vec2(0.0, 1.0);
    EmitVertex();

    gl_Position = VP * (center + vec4(0.5, -0.5, -0.5, 0.0));
    texCoords = vec2(1.0, 1.0);
    EmitVertex();

    EndPrimitive();
}

void main() 
{
    vec4 center = gl_in[0].gl_Position;

    build_x_positive(center);
    build_x_negative(center);
    build_y_positive(center);
    build_y_negative(center);
    build_z_positive(center);
    build_z_negative(center);
}
