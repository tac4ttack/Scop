/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:35:13 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/12 10:41:48 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	update_viewport(t_scop *env)
{
	if (env)
	{
		if (env->win_res[0] > env->win_res[1])
			glViewport(0, (env->win_res[1] - env->win_res[0]) / 2.0, \
						env->win_res[0], env->win_res[0]);
		else
			glViewport((env->win_res[0] - env->win_res[1]) / 2.0, 0, \
						env->win_res[1], env->win_res[1]);
	}
}

void		cb_window_size(GLFWwindow *win, const int width, const int height)
{
	t_scop	*env;

	env = glfwGetWindowUserPointer(win);
	if (win)
	{
		env->win_res[0] = width;
		env->win_res[1] = height;
		env->win_res[2] = env->win_res[0] / env->win_res[1];
		update_viewport(env);

		if (DEBUG_SCOP)
		{
			// add a print of a glGet(GL_VIEWPORT, param)
			scop_log("\nWindow size has changed!\tnew width = " \
					"%d\tnew height = %d\n", env->win_res[0], env->win_res[1]);
		}
	}
}