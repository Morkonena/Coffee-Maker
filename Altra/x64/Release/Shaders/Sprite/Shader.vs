#version 300 es
layout(location = 0) in vec2 vertex;
layout(location = 1) in vec2 uv;

uniform mat4 m;
uniform mat4 mvp;

out vec2 xuv;

void main ()
{
   xuv = uv;
   
   gl_Position = mvp * vec4(vertex, 0.0, 1.0);
   gl_Position.w = 1.0;
}
