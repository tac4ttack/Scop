/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 14:17:20 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/20 19:38:00 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	buffer_create(t_scop *env)
{
	if (env)
	{
		glGenVertexArrays(1, &env->vao); // get an id for our vertex array
		glGenBuffers(1, &env->vbo);	// get an id for our vertex buffer
		glBindVertexArray(env->vao);	// specify which vao to use
		glBindBuffer(GL_ARRAY_BUFFER, env->vbo); // bind it as an array buffer, all calls to GL_ARRAY_BUFFER will be applied to our env->vbo
		glBufferData(GL_ARRAY_BUFFER, env->mesh->n_vertex * sizeof(float) * 4, \
						env->mesh->vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, \
								4 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		return (true);
	}
	return (false);
}
