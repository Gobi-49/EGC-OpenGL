#version 330

// Input
// TODO(student): Get vertex attributes from each location

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;
uniform vec3 b[100];
uniform int a;
// Output
// TODO(student): Output values to fragment shader

out vec3 frag_color;
out vec3 normal;

void main()
{
    // TODO(student): Send output to fragment shader
    frag_color = vec3(1,1,0);
    normal = v_normal;
    
    // TODO(student): Compute gl_Position
    gl_Position = Projection * View * Model * vec4(position + vec3(time, 0, 0),1); 
}
