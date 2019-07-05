/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 19:26:16 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/27 17:43:10 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static GLuint			shader_load(const char *path, GLint mod)
{
	GLuint				shader;
	GLint				status;
	const GLchar		*source;
	size_t				source_size;

	if (path && (mod == GL_VERTEX_SHADER || mod == GL_FRAGMENT_SHADER))
	{
		source_size = ft_file_len(path);
		if (!(source = (GLchar*)ft_read_file(path, &source_size)))
			return (GL_FALSE);
		shader = glCreateShader(mod);
		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);
		ft_memdel((void**)&source);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
			return (GL_FALSE);
		return (shader);
	}
	return (GL_FALSE);
}

static GLuint			shader_compile(GLuint *vertex, GLuint *fragment)
{
	GLint				status;
	GLuint				program;

	if (vertex && fragment)
	{
		program = glCreateProgram();
		glAttachShader(program, *vertex);
		glAttachShader(program, *fragment);
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (!status)
			return (GL_FALSE);
		glDeleteShader(*vertex);
		glDeleteShader(*fragment);
		return (program);
	}
	return (GL_FALSE);
}

bool					shader_build(t_scop *env)
{
	GLuint				vertex;
	GLuint				fragment;

	if (env)
	{
		scop_log("\nBuilding shaders...\n");
		if (!(vertex = shader_load(VERTEX_SHADER_PATH, GL_VERTEX_SHADER)))
			return (error_bool("[ERROR shader_build]\t" \
			"Failed to load and compile vertex shader!\n"));
		if (!(fragment = shader_load(VERTEX_FRAGMENT_PATH, GL_FRAGMENT_SHADER)))
			return (error_bool("[ERROR shader_build]\t" \
			"Failed to load and compile fragment shader!\n"));
		if (!(env->shader_program = shader_compile(&vertex, &fragment)))
			return (error_bool("[ERROR shader_build]\t" \
			"Failed to compile and build shader program!\n"));
		if (!(shader_uniform_bind(env)))
			return (error_bool("[ERROR shader_build]\t" \
			"Failed to create uniforms for the shader program"));
		scop_log("Shaders successfully compiled and built!\n");
		return (true);
	}
	return (false);
}
