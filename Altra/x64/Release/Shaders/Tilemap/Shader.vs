#version 300 es
precision highp float;

layout(location = 0) in vec2 vertex;

uniform mat4 mvp;

uniform vec2  position;
uniform float scale;
uniform int   extent;

flat out int ve;

smooth out float vx;
smooth out float vy;

void main ()
{
   ve = extent;  
   vx = vertex.x * float(extent);
   vy = vertex.y * float(extent);
   
   vec2 v = position + vertex * float(extent) * scale;
   
   gl_Position = mvp * vec4(v, 0.0, 1.0);
   gl_Position.w = 1.0;
}