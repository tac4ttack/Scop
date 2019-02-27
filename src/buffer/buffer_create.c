/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 14:17:20 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/27 14:34:54 by fmessina         ###   ########.fr       */
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
			glGenTextures(1, &env->texture[i].id);
			glBindTexture(GL_TEXTURE_2D, env->texture[i].id);
			// TEXTURES PART
			// specify the texture wrapping
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			// if we use GL_CLAMP_TO_BORDER
			float clamped_border_color[] = {1.0f, 1.0f, 0.0f, 1.0f };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clamped_border_color);
			// specify the filtering method
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	// nearest when unzoom
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// linear when zoom
			// tester avec GL_RGBA?
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, env->texture[i].size[0], \
						env->texture[i].size[1], 0, GL_RGB, GL_UNSIGNED_BYTE, \
						env->texture[i].pixels);
			glGenerateMipmap(GL_TEXTURE_2D);
			i++;
		}
		scop_log("Textures buffers successfully generated!\n");
		return (true);
	}
	return (error_bool("[ERROR buffer_create_texture]\tNULL scop pointer!\n"));
}

bool	buffer_create(t_scop *env)
{
	if (env)
	{
		if (env->mesh->vertex && env->mesh->n_vertex[1] >= 3)
		{
			scop_log("\nCreating OpenGL buffers...\n");
			if (!(buffer_create_texture(env)))
				return (error_bool("[ERROR buffer_create]\tFailed creating" \
				" buffers for textures!\n"));
			glGenVertexArrays(1, &env->vao); // get an id for our vertex array
			glBindVertexArray(env->vao);	// specify which vao to use

			glGenBuffers(1, &env->vbo);	// get an id for our vertex buffer
			glBindBuffer(GL_ARRAY_BUFFER, env->vbo); // bind it as an array buffer, all calls to GL_ARRAY_BUFFER will be applied to our env->vbo

			glBufferData(GL_ARRAY_BUFFER, env->mesh->n_vertex[1] \
						* sizeof(float) * 8, env->mesh->vertex, GL_STATIC_DRAW);
			if (env->mesh->face && env->mesh->n_face[1] >= 1)
			{
				scop_log("Copying faces data into EBO\n");
				glGenBuffers(1, &env->ebo); // get an id for our element buffer object
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->ebo);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, \
				sizeof(GLuint) * env->mesh->n_face[1] * env->mesh->n_face[5], \
				env->mesh->face, GL_STATIC_DRAW);
			}
			// vertex position
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, \
									8 * sizeof(GLfloat), (void*)0);
			glEnableVertexAttribArray(0);
			// vertex color
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, \
									8 * sizeof(GLfloat), \
									(void*)(4 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
			scop_log("OpenGL buffers successfully created!\n");
			return (true);
		}
	}
	return (false);
}
