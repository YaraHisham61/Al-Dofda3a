#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 tex_coord;
layout(location = 3) in vec3 normal;
uniform vec3 camera_postion;// tp be sent form render file

uniform mat4 VP;// send in forward render
uniform mat4 M;
uniform mat4 M_IT;
//glm::mat4 M_I=glm::inverse(M);
//glUniformMatrix4fv(mit_loc,1,true,&M_i[0][0])
//true for transpose parameter
//Gluint mit_loc=glGetUniformLocation(program,M_IT);

out Varyings {
    vec4 color;
    vec2 tex_coord;
    vec3 normal;
    vec3 world;
    vec3 view;// vector form objec to camera
} vs_out;

void main(){
    vec3 world=(M*vec4(position,1.0)).xyz;//the point position in the world 
    gl_Position =  VP*vec4(world, 1.0);
    vs_out.color = color;
    vs_out.tex_coord = tex_coord;
    vs_out.normal = normalize((M_IT*vec4(normal,0.0)).xyz);
    vs_out.view=normalize(camera_postion-world);//we normalize the vericies and in frag we normaliz each pixel
    vs_out.world=world;
    // to compute the light effect in the world space 
}