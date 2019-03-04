#version 300 es
precision highp float;
in vec2 xuv;

uniform sampler2D sprite;

out vec4 color;

void main ()
{
	color = texture(sprite, xuv);
}
