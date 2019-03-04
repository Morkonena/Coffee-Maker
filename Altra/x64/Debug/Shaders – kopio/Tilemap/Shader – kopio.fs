#version 300 es
precision highp float;
precision highp isampler2D;
precision highp sampler2DArray;

uniform isampler2D tilemap;
uniform sampler2DArray tileset;

flat in int ve;

smooth in float vx;
smooth in float vy;

smooth in float lighting;

out vec4 color;

void main ()
{
	int index = texture(tilemap, vec2(float(vx) / float(ve), float(vy) / float(ve))).r;
		
	if (index > 0)
	{
		color = texture(tileset, vec3(fract(vx), fract(vy), index - 1)) * lighting;
	}
	else
	{
		color = vec4(0.0);
	}
}