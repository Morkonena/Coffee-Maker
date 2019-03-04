#version 300 es
precision highp float;
precision highp sampler2D;
precision highp isampler2D;
precision highp sampler2DArray;

uniform sampler2D lightmap;
uniform isampler2D tilemap;
uniform sampler2DArray tileset;

flat in int ve;

smooth in float vx;
smooth in float vy;

out vec4 color;

float GetVertexLighting (int x, int y)
{
	float a, b, c;
	
	a = texture(lightmap, vec2(float(x) / float(ve), float(y) / float(ve))).r;
	b = texture(lightmap, vec2(float(x + 1) / float(ve), float(y) / float(ve))).r;
	
	c = max(a, b);
	
	a = texture(lightmap, vec2(float(x) / float(ve), float(y + 1) / float(ve))).r;
	b = texture(lightmap, vec2(float(x + 1) / float(ve), float(y + 1) / float(ve))).r;
	
	c = max(max(a, b), c);
	
	return c;
}

float GetLighting (int x, int y, float u, float v)
{
	float a, b, c;
	
	// Top Left & Top Right
	a = GetVertexLighting(x, y + 1);
	b = GetVertexLighting(x + 1, y + 1);
	
	// Lighting between top vertices at position u
	c = mix(a, b, u);
	
	// Bottom Left & Bottom Right
	a = GetVertexLighting(x, y);
	b = GetVertexLighting(x + 1, y);
	
	// Lighting between bottom vertices at position u
	a = mix(a, b, u);
	b = c;
	
	// Lighting between top and bottom lightings at position v
	return mix(a, b, v);
}

void main ()
{
	int index = texture(tilemap, vec2(float(vx) / float(ve), float(vy) / float(ve))).r;
		
	if (index > 0)
	{
		int x = int(vx) - 1;
		int y = int(vy) - 1;
		
		float u = fract(vx);
		float v = fract(vy);
		
		float lighting = GetLighting(x, y, u, v);
	
		color = texture(tileset, vec3(u, v, index - 1)) * lighting;
		color.a = 1.0;
	}
	else
	{
		color = vec4(0.0);
	}
}