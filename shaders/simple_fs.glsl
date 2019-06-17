#version 330 core
out			vec4		FragColor;
in			vec4		vertexColor;
in			vec2		texCoord;
in			vec3		vertexNormal;

uniform		sampler2D	defaultTexture;
void main()
{
	// FragColor = vertexColor;
	// FragColor = texture(defaultTexture, texCoord) * vertexColor;
	FragColor = texture(defaultTexture, texCoord);
	// FragColor = vec4(sin(timeVal) / vertexColor.x, \
	//				cos(timeVal) / vertexColor.y, \
	//				cos(timeVal) / vertexColor.z, \
	//				vertexColor.w);
}
