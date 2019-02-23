/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:43:42 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/23 09:57:18 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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

			glDrawArrays(GL_TRIANGLE_FAN, 0, env->mesh->n_vertex[1]);
 			glfwPollEvents(); // update other events like input handling
			glfwSwapBuffers(env->win); // put the stuff we've been drawing onto the display
		}
		return (true);
	}
	return (error_bool("[ERROR glfw_launch()]\tError in Scop main loop"));
}
