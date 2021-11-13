#version 460 core

uniform sampler2D texture_sampler;

in vec2 vertex_shader_texture_coordinate;

layout (location = 0) out vec4 color_out;

void main() {
    color_out = texture(texture_sampler, vertex_shader_texture_coordinate);
    // color_out = vec4(0.0, 0.0, 1.0, 1.0);
}
