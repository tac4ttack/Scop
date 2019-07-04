/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_main_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:17:20 by fmessina          #+#    #+#             */
/*   Updated: 2019/07/04 14:28:44 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		glfw_ready_data(t_scop *env)
{
	if (env)
	{
		glUseProgram(env->shader_program);
		shader_uniform_update(env);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, env->texture[0].id);
		glBindVertexArray(env->vao);
	}
}

static bool		glfw_input_world_udpate(t_scop *env)
{
	if (env)
	{
		if (!(input_process(env)) \
			|| !(time_update(env)) \
			|| !(world_update(env)))
			return (false);
		glfw_ready_data(env);
		return (true);
	}
	return (false);
}

static bool		glfw_main_loop_error(t_scop *env)
{
	if (env)
	{
		glfwSetWindowShouldClose(env->win, 1);
		return (error_bool("[ERROR glfw_main_loop]\t" \
		"Nothing to draw! Vertices or elements arrays are empty!\n"));
	}
	return (false);
}

bool			glfw_main_loop(t_scop *env)
{
	if (env)
	{
		while (!glfwWindowShouldClose(env->win))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glfwPollEvents();
			
			// nk_glfw3_new_frame();
			
			if (!(glfw_input_world_udpate(env)))
				return (error_bool("[ERROR glfw_main_loop]\t" \
				"Failed processing inputs and updating data!\n"));
			// gui_update();
			if (env->mesh->face && env->mesh->n_face[1] >= 1)
				glDrawElements(GL_TRIANGLES, env->mesh->n_face[1] * 3, \
								GL_UNSIGNED_INT, 0);
			else if (env->mesh->vertex && env->mesh->n_vertex[1] >= 3)
				glDrawArrays(GL_TRIANGLE_STRIP, 0, env->mesh->n_vertex[1]);
			else
				glfw_main_loop_error(env);
			
			//nk_glfw3_render(NK_ANTI_ALIASING_ON);
			// gui_draw(env);
			// nk_clear(env->nuk->ctx);
		
			glfwSwapBuffers(env->win);
		}
		
		// nk_free(env->nuk->ctx);
		// nk_glfw3_shutdown();

		glfw_clean(env);
		return (true);
	}
	return (error_bool("[ERROR glfw_main_loop]\tNULL Scop pointer!\n"));
}
