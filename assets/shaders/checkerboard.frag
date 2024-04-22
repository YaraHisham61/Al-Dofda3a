#version 330 core

out vec4 frag_color;

// In this shader, we want to draw a checkboard where the size of each tile is (size x size).
// The color of the top-left most tile should be "colors[0]" and the 2 tiles adjacent to it
// should have the color "colors[1]".

//TODO: (Req 1) Finish this shader.

uniform int size=32;
uniform vec3 colors[2];

void main(){
    int x=int(gl_FragCoord.x)/size;
    int y=int(gl_FragCoord.y)/size;
    //dividing by the tile size make all pexils tile take one integer value in x or y direction
    
    if(mod(x+y,2)==1){
        // sum them and get the mod of to to make the color alter for each tile from the one next to it
        frag_color=vec4(colors[1],1.);
    }else
    {frag_color=vec4(colors[0],1.);}
}