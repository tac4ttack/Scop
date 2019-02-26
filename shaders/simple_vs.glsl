#version 330 core
layout (location = 0) in	vec4	aPos;
layout (location = 1) in	vec4	aHue;
out 						vec4	vertexColor;
void main()
{
	gl_Position = aPos;
	vertexColor = aHue;
}
