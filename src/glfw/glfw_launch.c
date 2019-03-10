/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:43:42 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/10 18:02:42 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void glfw_clean(t_scop *env)
{
	if (env)
	{
		glDeleteVertexArrays(1, &env->vao);
		glDeleteBuffers(1, &env->vbo);
		glDeleteBuffers(1, &env->ebo);
	}
}

static	void	update_time(t_scop *env)
{
	GLfloat		current;

	current = glfwGetTime();
	if (env)
	{
		env->time_delta = current - env->time_last;
		env->time_last = current;
		env->cam->speed = 2.5f * env->time_delta;
	}
}

bool	glfw_launch(t_scop *env)
{
	if (env)
	{
		while (!glfwWindowShouldClose(env->win))
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// wipe the drawing surface clear

			update_time(env);

			glUseProgram(env->shader_program); // specify wich shader to use
			shader_uniform_update(env);	// update our uniforms

			// here loop to load all textures
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, env->texture[0].id);

			glBindVertexArray(env->vao);
			if (env->mesh->face && env->mesh->n_face[1] >= 1)
			{
				glDrawElements(GL_TRIANGLES, \
				env->mesh->n_face[1] * 3, \
				GL_UNSIGNED_INT, 0);
			}
			else if (env->mesh->vertex && env->mesh->n_vertex[1] >= 3)
				glDrawArrays(GL_TRIANGLES, 0, env->mesh->n_vertex[1]);
			else
			{
				glfwSetWindowShouldClose(env->win, 1);
				return (error_bool("[ERROR glfw_launch]\t" \
				"Nothing to draw! Vertices or elements arrays are empty!\n"));
			}
			glfwPollEvents(); // update other events like input handling
			glfwSwapBuffers(env->win); // put the stuff we've been drawing onto the display
		}
		glfw_clean(env);
		return (true);
	}
	return (error_bool("[ERROR glfw_launch]\tNULL Scop pointer!\n"));
}
