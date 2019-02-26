#version 330 core
out			vec4	FragColor;
in			vec4	vertexColor;
uniform		float	timeVal;
void main()
{
	// FragColor = vertexColor;
	FragColor = vec4(sin(timeVal) / vertexColor.x, \
					cos(timeVal) / vertexColor.y, \
					cos(timeVal) / vertexColor.z, \
					vertexColor.w);
}


// glUniform4f(env->uniform_test, 0.0f, (sin(env->time_value) / 2.0f) + 0.5f, 0.0f, 1.0f);
