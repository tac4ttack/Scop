/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:35:13 by fmessina          #+#    #+#             */
/*   Updated: 2019/07/05 12:23:55 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		cb_window_move(GLFWwindow *win, int xpos, int ypos)
{
	t_scop	*env;

	env = NULL;
	(void)xpos;
	(void)ypos;
	if (win)
	{
		env = glfwGetWindowUserPointer(win);
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

	if (win)
	{
		env = glfwGetWindowUserPointer(win);
		env->win_res[0] = width;
		env->win_res[1] = height;
		env->win_res[2] = env->win_res[0] / env->win_res[1];
		if (DEBUG_SCOP)
		{
			scop_log("\nWindow size has changed!\tnew width = " \
					"%d\tnew height = %d\n", env->win_res[0], env->win_res[1]);
		}
	}
}
