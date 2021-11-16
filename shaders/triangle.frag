#version 460 core

/*
note: Fragment Shaders have the following built-in input variables.
in vec4 gl_FragCoord;   // window relative coordinate (x, y, z, 1/w)
in bool gl_FrontFacing; // fragment is front or back facing
in vec2 gl_PointCoord;  //

if we're using more than one texture,
   then sampler2D should coordinate with textures
   we bind with GL_TEXTURE0 GL_TEXTURE1, etc.

//layout (binding = 0) uniform sampler2D texture_sampler;
//layout (binding = 1) uniform sampler2D texture_sampler;
*/

/* if we're only using one texture, then sampler2D is
   provided, so we don't have make a call to glBindTexture */
uniform sampler2D texture_sampler;

layout (location = 0) out vec4 color_out;

void main() {
    color_out = vec4(0.0, 0.0, 1.0, 1.0);
}
