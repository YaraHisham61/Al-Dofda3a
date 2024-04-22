#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 tex_coord;
layout(location = 3) in vec3 normal;

out Varyings {
    vec3 position;
    vec4 color;
    vec2 tex_coord;
    vec3 normal;
} vs_out;

uniform mat4 transform;

void main(){
    //TODO: (Req 3) Change the next line to apply the transformation matrix
    // multipy the transformation matrix 4x4 to te point vec4 to get the new position of the point
    // the transformation is done in this order scaling then rotation followed by the translation
    // so its multiplies from the left as it TRS matrix
    gl_Position=transform*vec4(position,1.0);
    // No need to change any of the following lines
    vs_out.position = position;
    vs_out.color = color;
    vs_out.tex_coord = tex_coord;
    vs_out.normal = normal;
}