/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:43:42 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/25 16:39:09 by fmessina         ###   ########.fr       */
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
			// _update_fps_counter(env->win);
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// wipe the drawing surface clear

			glUseProgram(env->shader_program); // specify wich shader to use
			glBindVertexArray(env->vao);
			if (env->mesh->face && env->mesh->n_face[1] >= 1)
			{
				// fprintf(stdout, "I GOT FACES!\n", NULL);
				glDrawElements(GL_TRIANGLES, \
				env->mesh->n_vertex[1] * env->mesh->n_face[5], \
				GL_UNSIGNED_INT, 0);
			}
			else if (env->mesh->vertex && env->mesh->n_vertex[1] >= 3)
			{
				// fprintf(stdout, "I GOT NO FACES but VERTEX!\n", NULL);
				// glBindVertexArray(env->vao);
				glDrawArrays(GL_TRIANGLES, 0, env->mesh->n_vertex[1]);
			}
			else
			{
				glfwSetWindowShouldClose(env->win, 1);
				return (error_bool("[ERROR glfw_launch()]\t" \
				"Nothing to draw! Vertices or elements arrays are empty!"));
			}
 			glfwPollEvents(); // update other events like input handling
			glfwSwapBuffers(env->win); // put the stuff we've been drawing onto the display
		}
		glfw_clean(env);
		return (true);
	}
	return (error_bool("[ERROR glfw_launch()]\tError in Scop main loop"));
}
