/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 14:17:20 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/25 17:23:20 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	buffer_create(t_scop *env)
{
	if (env)
	{
		if (env->mesh->vertex && env->mesh->n_vertex[1] >= 3)
		{
			scop_log("\nCreating OpenGL buffers...\n");
			glGenVertexArrays(1, &env->vao); // get an id for our vertex array
			glGenBuffers(1, &env->vbo);	// get an id for our vertex buffer
			glBindVertexArray(env->vao);	// specify which vao to use
			glBindBuffer(GL_ARRAY_BUFFER, env->vbo); // bind it as an array buffer, all calls to GL_ARRAY_BUFFER will be applied to our env->vbo
			glBufferData(GL_ARRAY_BUFFER, env->mesh->n_vertex[1] \
						* sizeof(float) * 4, env->mesh->vertex, GL_STATIC_DRAW);
			if (env->mesh->face && env->mesh->n_face[1] >= 1)
			{
				scop_log("Copying faces data into EBO\n");
				glGenBuffers(1, &env->ebo); // get an id for our element buffer object
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->ebo);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, \
				sizeof(GLuint) * env->mesh->n_face[1] * env->mesh->n_face[5], \
				env->mesh->face, GL_STATIC_DRAW);
			}
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, \
									4 * sizeof(GLfloat), (void*)0);
			glEnableVertexAttribArray(0);
			scop_log("OpenGL buffers successfully created!\n");
			return (true);
		}
	}
	return (false);
}
