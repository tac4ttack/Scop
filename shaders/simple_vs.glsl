#version 330 core
layout (location = 0) in	vec4	aPosition;
layout (location = 1) in	vec4	aHue;
layout (location = 2) in	vec3	aTexCoord;
layout (location = 3) in	vec3	aNormal;
layout (location = 4) in	vec3	aSpaceParam;

out							vec4	vertexColor;
out							vec2	texCoord;

// uniform						mat4	translation;
// uniform						mat4	rotation;
// uniform						mat4	scale;
// uniform						mat4	view;
// uniform						mat4	projection;
uniform						mat4	mvp;
void main()
{
	// mat4	model = translation * rotation * scale;
	// mat4	mvp = projection * view * model;

	gl_Position = mvp * aPosition;
	gl_PointSize = gl_Position.z * 2.5;
	vertexColor = aHue;
	texCoord = aTexCoord.xy;
}
