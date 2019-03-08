#version 330 core
layout (location = 0) in	vec4	aPosition;
layout (location = 1) in	vec4	aHue;
layout (location = 2) in	vec3	aTexCoord;
layout (location = 3) in	vec3	aNormal;
layout (location = 4) in	vec3	aSpaceParam;

out							vec4	vertexColor;
out							vec2	texCoord;

uniform						mat4	mTransformation;
void main()
{
	gl_Position = aPosition * mTransformation;
	vertexColor = aHue;
	texCoord = aTexCoord.xy;
}
