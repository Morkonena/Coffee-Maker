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
   vec2 padding;
   
   if (vertex.x == 0.0)
   {
      padding.x = 0.033;
   }
   else
   {
      padding.x = -0.033;
   }
   
   if (vertex.y == 0.0)
   {
      padding.y = 0.033;
   }
   else
   {
      padding.y = -0.033;
   }
   
   ve = extent;  
   vx = vertex.x * float(extent) + padding.x;
   vy = vertex.y * float(extent) + padding.y;
   
   vec2 v = position + vertex * float(extent) * scale;
   
   gl_Position = mvp * vec4(v, 0.0, 1.0);
   gl_Position.w = 1.0;
}