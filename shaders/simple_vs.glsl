#version 330 core
layout (location = 0) in	vec4	aPos;
layout (location = 1) in	vec4	aHue;
layout (location = 2) in	vec3	aTexture;
layout (location = 3) in	vec3	aNormal;
layout (location = 4) in	vec3	aSpace;
out 						vec4	vertexColor;
void main()
{
	gl_Position = aPos;
	vertexColor = aHue;
}
