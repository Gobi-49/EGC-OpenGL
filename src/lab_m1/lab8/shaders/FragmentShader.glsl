#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position[2];
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform int spotlight;
uniform float spotAngle;

// TODO(student): Declare any other uniforms

uniform vec3 object_color;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    vec3 rez = vec3(0);

    for(int i=0; i<2; i++)
    {
        vec3 N = normalize(world_normal);
        vec3 L = normalize(light_position[i] - world_position);
        vec3 R = reflect(-L, N);
        vec3 V = normalize( eye_position - world_position);
        vec3 H = normalize( L + V );

        // TODO(student): Define ambient, diffuse and specular light components
        float ambient_light = 0.25;
        float diffuse_light = material_kd * max(dot(N, L), 0);;
        float specular_light = 0;
    
        // It's important to distinguish between "reflection model" and
        // "shading method". In this shader, we are experimenting with the Phong
        // (1975) and Blinn-Phong (1977) reflection models, and we are using the
        // Phong (1975) shading method. Don't mix them up!
        if (diffuse_light > 0)
        {
            specular_light = material_ks * pow(max(dot(V,R), 0), material_shininess);
        }

        // TODO(student): If (and only if) the light is a spotlight, we need to do
        // some additional things.

        if(spotlight == 1)
        {
            float cut_off = radians(spotAngle);
            float spot_light = dot(-L, light_direction);
            float spot_light_limit = cos(cut_off);
            float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
            float light_att_factor = pow(linear_att, 2);
            if (spot_light > spot_light_limit)
            {
                rez += object_color * light_att_factor * (diffuse_light + specular_light);
            }
            else
            {
                rez += vec3(0);
            }
        }
        else
        {

            float d = distance(light_position[i], world_position);
            float atenuare = 1/(pow(d,2) + 1);

            rez += object_color * atenuare * (diffuse_light + specular_light);
        }

        out_color = vec4(rez + ambient_light * object_color, 1);
    }
}
