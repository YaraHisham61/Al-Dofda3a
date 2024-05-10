#version 330
uniform sampler2D tex;
in vec2 tex_coord;
out vec4 frag_color;

void main () {
    vec3 color = vec3(0.0);
    //Increasing texelSize will make the sampling area larger,resulting in a more pronounced blur effect,
    //while decreasing it will make the sampling area smaller, resulting in a less pronounced blur effect.
    vec2 texelSize = 1.0 / textureSize(tex, 0);
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            color += texture(tex, tex_coord + vec2(i, j) * texelSize).rgb;
        }
    }
    color /=9.0;
    frag_color.rgb = color;
    frag_color.a = 1.0;
}