#version 330 core
out			vec4		FragColor;
in			vec4		vertexColor;
in			vec2		texCoord;
uniform		float		timeVal;
uniform		sampler2D	defaultTexture;
void main()
{
	// FragColor = vertexColor;
	FragColor = texture(defaultTexture, texCoord);
	// FragColor = vec4(sin(timeVal) / vertexColor.x, \
	//				cos(timeVal) / vertexColor.y, \
	//				cos(timeVal) / vertexColor.z, \
	//				vertexColor.w);
}
