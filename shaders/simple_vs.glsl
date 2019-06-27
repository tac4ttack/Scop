#version 330 core

layout (location = 0) in	vec4	aPosition;
layout (location = 1) in	vec4	aHue;
layout (location = 2) in	vec3	aTexCoord;
layout (location = 3) in	vec3	aNormal;

smooth	out					vec4	vertexColor;
flat	out					vec4	vertexColorFlat;
		out					vec2	texCoord;
		out					vec2	texCoordDefault;
		out					vec4	vertexNormal;
		out					vec4	vertexNormalDefault;

uniform						mat4	uMVP;

void main()
{
	gl_Position = uMVP * aPosition;

	gl_PointSize = 2.5;

	vertexColor = aHue;
	vertexColorFlat = aHue;

	texCoord = aTexCoord.xy;
	texCoordDefault = vec2(aPosition.x * 2, aPosition.y * 2);

	vertexNormal = vec4(aNormal.xyz, 0);	
}
