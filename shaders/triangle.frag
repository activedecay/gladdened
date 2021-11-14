#version 460 core

/* if we're only using one texture, then sampler2D is provided */
uniform sampler2D texture_sampler;
/* otherwise, you'd need to bind with GL_TEXTURE0 GL_TEXTURE1, etc. */
//layout (binding = 1) uniform sampler2D texture_sampler;

/*  */
in vec2 vertex_shader_texture_coordinate;

layout (location = 0) out vec4 color_out;

void main() {
//    color_out = texture(texture_sampler, vertex_shader_texture_coordinate);
    color_out = vec4(0.0, 0.0, 1.0, 1.0);
}
