/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:35:13 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/27 14:23:12 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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
