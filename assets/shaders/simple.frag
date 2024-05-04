#version 330 core

#define DIRECTIONAL 0
#define POINT 1
#define SPOT 2

struct Light{
    vec3 direction;// direction from light to object
    vec3 position;
    vec3 color;
    int type;
    vec3 specular;
    vec3 attenuation;
    vec2 cone_angles;// inner and outer angles of cones
    //in inner code 1 outer the outer cone 0 and interpolate the inbetween
};
#define MAX_LIGHTS 8

uniform Light lights[MAX_LIGHTS];
uniform int light_count;
// uniform vec3 ambient_light;// light from environment

struct Material{
    
    sampler2D albedo;
    sampler2D specular;
    sampler2D roughness;
    sampler2D ambient_occlusion;
    sampler2D emission;// if the object is the source of light
};
uniform Material material;
in Varyings{
    vec4 color;
    vec2 tex_coord;
    vec3 normal;
    vec3 world;
    vec3 view;// vector form objec to camera
}fs_in;

float lambert(vec3 normal,vec3 world_to_light_direction){
    
    return(max(0.,dot(world_to_light_direction,normal)));// angle between the light direction and normal direction
}
float phong(vec3 reflected,vec3 view,float shininess){
    // angle between the reflected light anf the camera to point vector
    
    return pow(max(0.,dot(reflected,view)),shininess);// shininess is the alpha power speculer
}
struct Sky{
    vec3 top,horizon,bottom;
};

uniform Sky sky;

vec3 compute_sky_light(vec3 normal){
    vec3 extreme=normal.y>0?sky.top:sky.bottom;
    return mix(sky.horizon,extreme,normal.y*normal.y);
}
out vec4 frag_color;

void main(){
    
    vec3 normal=normalize(fs_in.normal);
    vec3 view=normalize(fs_in.view);
    
    vec3 ambient_light=compute_sky_light(normal);
    
    vec3 diffuse=texture(material.albedo,fs_in.tex_coord).rgb;
    vec3 specular=texture(material.specular,fs_in.tex_coord).rgb;
    float roughness=texture(material.roughness,fs_in.tex_coord).r;
    vec3 ambient=diffuse*texture(material.ambient_occlusion,fs_in.tex_coord).r;
    vec3 emission=texture(material.emission,fs_in.tex_coord).rgb;
    
    float shininess=2./pow(clamp(roughness,.001,.999),4.)-2.;
    
    vec3 world_to_light_dir;
    vec3 color=emission+ambient_light*ambient;
    
    for(int light_idx=0;light_idx<min(MAX_LIGHTS,light_count);light_idx++){
        
        Light light=lights[light_idx];
        float attenuation=1.;
        if(light.type==DIRECTIONAL){
            world_to_light_dir=-light.direction;//direction from object to light
            
        }else{
            vec3 world_to_light_dir=light.position-fs_in.world;
            float light_distance=length(world_to_light_dir);// to make light decrease as we go far away
            world_to_light_dir/=light_distance;
            float attenuation=1./dot(light.attenuation,vec3(light_distance*light_distance,light_distance,1.));
            //light intinisty dec as we go away from the user by distance square
            if(light.type==SPOT){
                float angle=acos(dot(light.direction,-world_to_light_dir));// angle between the light vector and the object light vector
                attenuation*=smoothstep(light.cone_angles.y,light.cone_angles.x,angle);//to make attenuation every angle step
            }
        }
        
        vec3 computed_diffuse=light.specular*diffuse*lambert(normal,world_to_light_dir);
        
        vec3 reflected=reflect(-world_to_light_dir,normal);
        vec3 computed_specular=light.color*specular*phong(reflected,view,shininess);
        
        color+=(computed_diffuse+computed_specular)*attenuation;
        
    }
    
    frag_color=vec4(color,1.);
    
    // // vec3 world_to_light_dir=-light.direction;//direction from object to light
    // vec3 world_to_light_dir=light.position-fs_in.world;
    // float light_distance=length(world_to_light_dir);// to make light decrease as we go far away
    // world_to_light_dir /= light_distance;
    
    // vec3 ambient=ambient_light*material.ambient*1;// ambietn is weak light form all directions so there is no angle effect
    
    // vec3 diffuse=light.color*material.diffuse*lambert(light.diffuse,normal);
    
    // vec3 reflected=reflect(-world_to_light_dir,normal);
    
    // vec3 specular=light.color*material.specular*phong(reflected,view,material.shininess);
    
    // float attenuation =1.0/dot(light.attenuation,vec3(light_distance*light_distance,light_distance,1.0));
    // //light intinisty dec as we go away from the user by distance square
    
    // float angle=acos(dot(light.direction,-world_to_light_dir));// angle between the light vector and the object light vector
    // attenuation *= smoothstep(light.cone_angles.y,light.cone_angles.x,angle);//to make attenuation every angle step
    
    // frag_color.rgb=vec4(specular+(ambient+diffuse)*attenuation,1.);
    // // frag_color=vec4(1.,1.,1.,1.);
    // // frag_color.rgb*=max(0.,dot(world_to_light_dir,fs_in.normal));
}