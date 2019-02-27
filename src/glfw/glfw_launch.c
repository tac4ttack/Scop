/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:43:42 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/27 12:42:08 by fmessina         ###   ########.fr       */
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

static void glfw_input_handling(t_scop *env)
{
	if (env)
	{
		if (GLFW_PRESS == glfwGetKey(env->win, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(env->win, 1);
	}
}

bool	glfw_launch(t_scop *env)
{
	if (env)
	{
		while (!glfwWindowShouldClose(env->win))
		{
			glfw_input_handling(env);	// first we process all the inputs
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// wipe the drawing surface clear
			// _update_fps_counter(env->win);
			env->uni_time_val = glfwGetTime();	// update our time
			glUseProgram(env->shader_program); // specify wich shader to use
			shader_uniform_update(env);	// update our uniforms
			glBindVertexArray(env->vao);
			if (env->mesh->face && env->mesh->n_face[1] >= 1)
			{
				// glDrawElements(GL_TRIANGLES, 3,	GL_UNSIGNED_INT, 0);
				glDrawElements(GL_TRIANGLES, \
				env->mesh->n_vertex[1] * env->mesh->n_face[5], \
				GL_UNSIGNED_INT, 0);
			}
			else if (env->mesh->vertex && env->mesh->n_vertex[1] >= 3)
			{
				glDrawArrays(GL_TRIANGLES, 0, env->mesh->n_vertex[1]);
			}
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
