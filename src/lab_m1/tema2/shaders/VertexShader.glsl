#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform int hp;

// Output values to fragment shader
out vec3 world_position;
out vec3 world_normal;


void main()
{
    world_position = (Model * vec4(v_position,1)).xyz;
    world_normal = normalize( mat3(Model) * v_normal );
    int my_hp = hp;
    if(hp < 0)
        my_hp = 0;
    float deformationFactor = 2;  // Adjust this factor for the intensity of the deformation
    vec3 deformedPosition = vec3(v_position.x + (3-my_hp) * sin((3-my_hp)* v_position.y), v_position.y, v_position.z + (3-my_hp) * sin((3-my_hp)* v_position.y));
    gl_Position = Projection * View * Model * vec4(deformedPosition, 1.0);
}
