#version 330 core
layout (location = 0) in	vec4	aPosition;
layout (location = 1) in	vec4	aHue;
layout (location = 2) in	vec3	aTexCoord;
layout (location = 3) in	vec3	aNormal;
layout (location = 4) in	vec3	aSpaceParam;

out							vec4	vertexColor;
out							vec2	texCoord;
out							vec4	vertexNormal;

uniform						mat4	mvp;
void main()
{
	gl_Position = mvp * aPosition;
	// gl_PointSize = gl_Position.z * 2.5;
	gl_PointSize = 2.5;
	vertexColor = aHue;
	vertexNormal = vec4(aNormal.xyz, 0);
	texCoord = aTexCoord.xy;
}
