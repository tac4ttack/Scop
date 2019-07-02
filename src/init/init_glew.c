/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_glew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:28:09 by fmessina          #+#    #+#             */
/*   Updated: 2019/07/02 11:03:41 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	init_glew(t_scop *env)
{
	if (env)
	{
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			return (error_bool("[ERROR init_glew\t" \
			"Failed to initialize GLEW!\n"));
		glViewport(0, (env->win_res[1] - env->win_res[0]) / 2.0, \
					env->win_res[0], env->win_res[0]);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glDisable(GL_CULL_FACE);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		env->time_last = glfwGetTime();
		scop_log("Current system parameters are:\n");
		scop_log_gl_params();
		return (scop_log("Renderer: %s\n", glGetString(GL_RENDERER)) &
		scop_log("OpenGL version supported %s\n", glGetString(GL_VERSION)));
	}
	return (error_bool("[ERROR init_glew]\tNULL Scop pointer!\n"));
}
