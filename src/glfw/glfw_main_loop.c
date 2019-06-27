/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_main_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:43:42 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/12 10:09:11 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"


bool	glfw_main_loop(t_scop *env)
{
	if (env)
	{
		while (!glfwWindowShouldClose(env->win))
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// wipe the drawing surface clear

			if (!(input_process(env)) || !(time_update(env)) || !(world_update(env)))
				return (error_bool("[ERROR glfw_main_loop]\t" \
				"Failed processing inputs and updating data!\n"));
			
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
				return (error_bool("[ERROR glfw_main_loop]\t" \
				"Nothing to draw! Vertices or elements arrays are empty!\n"));
			}
			glfwPollEvents(); // update other events like input handling
			glfwSwapBuffers(env->win); // put the stuff we've been drawing onto the display
		}
		glfw_clean(env);
		return (true);
	}
	return (error_bool("[ERROR glfw_main_loop]\tNULL Scop pointer!\n"));
}
