#version 330 core
smooth	in			vec4		vertexColor;
flat	in			vec4		vertexColorFlat;

		in			vec2		texCoord;
		in			vec2		texCoordDefault;
		in			vec3		vertexNormal;
		in			vec4		vertexNormalDefault;

		uniform		sampler2D	defaultTexture;

		uniform		bool		uShading;
		uniform		int			uDesaturate;
		uniform		bool		uColorize;
		uniform		bool		uTextureDefault;
		uniform		bool		uTextureMesh;
		uniform		bool		uTextureUVMode;

		out			vec4		FragColor;

vec4 convert_to_grayscale(vec4 source)
{
	float average = (source.x + source.y + source.z) / 3;
	return (vec4(average, average, average, source.w));
}

void main()
{
	FragColor = vec4(0,0,0,0);

	vec4	hue = vec4(0,0,0,0);
	if (uShading)
		hue = vertexColor;
	else
		hue = vertexColorFlat;
	if (uDesaturate == 1 || uDesaturate == 3)
		hue = convert_to_grayscale(hue);

	vec2	uv = vec2(0,0);
	if (uTextureUVMode)
		uv = texCoord;
	else
		uv = texCoordDefault;

	if (uTextureDefault)
	{
		FragColor += texture(defaultTexture, uv);
		if (uDesaturate == 2 || uDesaturate == 3)
		FragColor = convert_to_grayscale(FragColor);
		if (uColorize)
			FragColor *= hue;
	}
	else
		FragColor += hue;
}
