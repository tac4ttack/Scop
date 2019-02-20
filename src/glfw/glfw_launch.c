/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:43:42 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/20 17:12:02 by fmessina         ###   ########.fr       */
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

			glDrawArrays(GL_TRIANGLES, 0, env->mesh->n_vertex);

			// glBindVertexArray(vertex_array_object_A); // specify which VBO to use
			// draw points 0-3 from the currently bound VAO with current in-use shader
			// glDrawArrays(GL_LINE_LOOP, 0, 36);

			// glUseProgram(shader_program_2);			  // specify which shader program to use
			// glBindVertexArray(vertex_array_object_B); // specify which VBO to use
			// glDrawArrays(GL_LINE_LOOP, 0, 6);



			glfwPollEvents(); // update other events like input handling
			glfwSwapBuffers(env->win); // put the stuff we've been drawing onto the display
		}
		return (true);
	}
	return (error_bool("[ERROR glfw_launch()]\tError in Scop main loop"));
}
