/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 14:17:20 by fmessina          #+#    #+#             */
/*   Updated: 2019/07/04 14:21:24 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool	buffer_create_texture(t_scop *env)
{
	size_t	i;

	if (env)
	{
		scop_log("\nGenerating textures buffers...\n");
		i = 0;
		while (i < env->n_texture)
		{
			glGenTextures(1, &env->texture->id);
			glBindTexture(GL_TEXTURE_2D, env->texture->id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, env->texture->size[0], \
						env->texture->size[1], 0, GL_BGRA, GL_UNSIGNED_BYTE, \
						env->texture->pixels);
			glGenerateMipmap(GL_TEXTURE_2D);
			i++;
		}
		scop_log("Textures buffers successfully generated!\n");
		return (true);
	}
	return (error_bool("[ERROR buffer_create_texture]\tNULL Scop pointer!\n"));
}

static bool	buffer_create_vao_vbo(t_scop *env)
{
	if (env)
	{
		glGenVertexArrays(1, &env->vao);
		glBindVertexArray(env->vao);
		glGenBuffers(1, &env->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, env->vbo);
		if (env->mesh->face && env->mesh->n_face[0] > 0)
		{
			glBufferData(GL_ARRAY_BUFFER, \
					sizeof(GLfloat) * env->mesh->n_face[0] * 3 * VAOLEN, \
					env->prepack_vao, GL_STATIC_DRAW);
		}
		else
		{
			glBufferData(GL_ARRAY_BUFFER, \
					sizeof(GLfloat) * env->mesh->n_vertex[0] * VAOLEN, \
					env->prepack_vao, GL_STATIC_DRAW);
		}
		return (true);
	}
	return (error_bool("[ERROR buffer_create_vao_vbo]\t" \
	"NULL Scop pointer!\n"));
}

static bool	buffer_create_ebo(t_scop *env)
{
	if (env)
	{
		scop_log("Copying faces data into EBO\n");
		glGenBuffers(1, &env->ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->ebo);
		if (env->mesh->face && env->mesh->n_face[0] > 0)
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, \
					sizeof(GLuint) * env->mesh->n_face[0] * 3, \
					env->prepack_ebo, GL_STATIC_DRAW);
		}
		return (true);
	}
	return (error_bool("[ERROR buffer_create_ebo]\t" \
	"NULL Scop pointer!\n"));
}

static bool	buffer_create_vertex_attrib(t_scop *env)
{
	if (env)
	{
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, \
							VAOLEN * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VAOLEN \
							* sizeof(GLfloat), (void*)(4 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VAOLEN \
							* sizeof(GLfloat), (void*)(8 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, VAOLEN \
							* sizeof(GLfloat), (void*)(11 * sizeof(GLfloat)));
		glEnableVertexAttribArray(3);
		return (true);
	}
	return (error_bool("[ERROR buffer_create_vertex_attrib]\t" \
	"NULL Scop pointer!\n"));
}

bool		buffer_create(t_scop *env)
{
	if (env)
	{
		if (env->mesh->vertex && env->mesh->n_vertex[1] >= 3)
		{
			scop_log("\nCreating OpenGL buffers...\n");
			if (!(buffer_create_texture(env)))
				return (error_bool("[ERROR buffer_create]\tFailed creating" \
				" buffers for textures!\n"));
			if (!(buffer_create_vao_vbo(env)))
				return (error_bool("[ERROR buffer_create]\t" \
				"Failed initializing VAO and VBO buffers!\n"));
			if (env->mesh->face && env->mesh->n_face[1] >= 1)
				if (!(buffer_create_ebo(env)))
					return (error_bool("[ERROR buffer_create]\t" \
					"Failed initializing and filling EBO buffer!\n"));
			if (!(buffer_create_vertex_attrib(env)))
				return (error_bool("[ERROR buffer_create]\t" \
				"Failed copying data into VAO buffer!\n"));
			scop_log("OpenGL buffers successfully created!\n");
			return (true);
		}
		return (error_bool("[ERROR buffer_create]\t" \
		"Mesh must have at least 3 vertices!\n"));
	}
	return (error_bool("[ERROR buffer_create]\tNULL Scop pointer!\n"));
}
