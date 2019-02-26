#version 330 core
out			vec4	FragColor;
in			vec4	vertexColor;
uniform		float	timeVal;
void main()
{
	FragColor = vertexColor;
	// FragColor = vec4(sin(timeVal) / vertexColor.x, \
	//				cos(timeVal) / vertexColor.y, \
	//				cos(timeVal) / vertexColor.z, \
	//				vertexColor.w);
}
