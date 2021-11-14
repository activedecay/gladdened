#version 460 core

layout(location = 0) in vec4 vPosition;
//layout(location = 1) in vec2 vCoordinate;

void  main() {
    gl_Position = vPosition;
//    vertex_shader_texture_coordinate = vCoordinate;
}
