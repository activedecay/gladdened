#version 460 core

layout(location = 0) in vec4 vPosition;

out vec2 vertex_shader_texture_coordinate;

void  main() {
    gl_Position = vPosition;
    vertex_shader_texture_coordinate = vPosition.xy;
}
