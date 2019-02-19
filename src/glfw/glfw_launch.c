/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:43:42 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/19 11:47:54 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	glfw_launch(t_scop *env)
{
	if (env)
	{
		while (!glfwWindowShouldClose(env->win))
		{
			// _update_fps_counter(env->win);

			// wipe the drawing surface clear
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// glUseProgram(shader_programme);			  // specify which shader program to use
			// glBindVertexArray(vertex_array_object_A); // specify which VBO to use
			// draw points 0-3 from the currently bound VAO with current in-use shader
			// glDrawArrays(GL_LINE_LOOP, 0, 36);

			// glUseProgram(shader_program_2);			  // specify which shader program to use
			// glBindVertexArray(vertex_array_object_B); // specify which VBO to use
			// glDrawArrays(GL_LINE_LOOP, 0, 6);

			// update other events like input handling
			glfwPollEvents();
			// put the stuff we've been drawing onto the display
			glfwSwapBuffers(env->win);

			if (GLFW_PRESS == glfwGetKey(env->win, GLFW_KEY_ESCAPE))
				glfwSetWindowShouldClose(env->win, 1);
		}
		return (true);
	}
	return (error_bool("[ERROR glfw_launch()]\tError in Scop main loop"));
}
