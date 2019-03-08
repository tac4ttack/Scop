#version 330 core
layout (location = 0) in	vec4	aPosition;
layout (location = 1) in	vec4	aHue;
layout (location = 2) in	vec3	aTexCoord;
layout (location = 3) in	vec3	aNormal;
layout (location = 4) in	vec3	aSpaceParam;

out							vec4	vertexColor;
out							vec2	texCoord;

uniform						mat4	model;
uniform						mat4	view;
uniform						mat4	projection;
void main()
{
	gl_Position = projection * view * model * aPosition;
	vertexColor = aHue;
	texCoord = aTexCoord.xy;
}
