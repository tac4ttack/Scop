#version 330 core
out vec4 FragColor;

smooth in vec4 vertexColor;
flat in vec4 vertexColorFlat;

in vec2 texCoord;
in vec2	texCoordDefault;
in vec3 vertexNormal;
in vec4	vertexNormalDefault;

uniform		sampler2D	defaultTexture;

vec4 convert_to_grayscale(vec4 source)
{
	float average = (source.x + source.y + source.z) / 3;
	return (vec4(average, average, average, source.w));
}

void main()
{
	FragColor = texture(defaultTexture, texCoord);
	// FragColor = texture(defaultTexture, texCoordDefault);
	// FragColor = vertexColorFlat;
	// FragColor = vertexColor;
	FragColor = convert_to_grayscale(vertexColorFlat);

	
	// FragColor = texture(defaultTexture, texCoord) * vertexColorSmooth;
	// FragColor = texture(defaultTexture, texCoord) * vertexColorFlat;
	
	// FragColor = vec4(sin(timeVal) / vertexColorSmooth.x, \
	// FragColor = vec4(sin(timeVal) / vertexColorSmooFlat\
	//				cos(timeVal) / vertexColorSmooth.y, \
	//				cos(timeVal) / vertexColorSmooFlat\
	//				cos(timeVal) / vertexColorSmooth.z, \
	//				cos(timeVal) / vertexColorSmooFlat\
	//				vertexColorSmooth.w);
	//				vertexColorSmoFlat;
}
