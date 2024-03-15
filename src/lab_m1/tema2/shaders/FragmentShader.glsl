#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 eye_position;
uniform vec3 object_color;
uniform int hp;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    vec3 lPos = vec3(0, 6, 0);
    vec3 N = normalize(world_normal);
    vec3 L = normalize(lPos);
    vec3 R = reflect(-L, N);
    vec3 V = normalize( eye_position - world_position);
    vec3 H = normalize( L + V );

    float ambient_light = 0.4;
    float diffuse_light = 0.25 * max(dot(N, L), 0);
    float specular_light = 0;

    if (diffuse_light >= 0)
    {
    
        int primesteLum;
        if(dot(N,L) > 0)
            primesteLum = -1;
        else
            primesteLum = 0;
        specular_light = 0.5 * pow(max(dot(V,R), 0), 30);
    }
    float d = distance(lPos, world_position);
    float atenuare = 1/(d/2);
    
    vec3 color_hp = object_color;
    
    if(hp > 0)
        color_hp = object_color * hp/3;
    else
        color_hp = vec3(0);
    out_color = vec4(color_hp * ambient_light + atenuare * (diffuse_light + specular_light), 1);
}
