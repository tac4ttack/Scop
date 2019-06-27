/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_mouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:35:13 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/27 16:36:31 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		cb_mouse_pos(GLFWwindow *window, \
									double xpos, \
									double ypos)
{
	t_scop	*env;
	double	offset[2];

	env = glfwGetWindowUserPointer(window);
	if (!env->mouse->ready)
	{
		env->mouse->last[0] = xpos;
		env->mouse->last[1] = ypos;
		env->mouse->ready = true;
	}
	offset[0] = (xpos - env->mouse->last[0]);
	offset[1] = (env->mouse->last[1] - ypos);
	env->mouse->last[0] = xpos;
	env->mouse->last[1] = ypos;
}

void		cb_mouse_btn(GLFWwindow *window, \
										int button, \
										int action, \
										int mods)
{
	t_scop	*env;

	env = glfwGetWindowUserPointer(window);
	if (DEBUG_SCOP)
		fprintf(stdout, "[DEBUG]: mouse button callback -> " \
						"btn = %d | action = %d | mods = %d\n", \
						button, action, mods);
}

void		cb_mouse_scroll(GLFWwindow *window, \
										double x_offset, \
										double y_offset)
{
	t_scop	*env;

	env = glfwGetWindowUserPointer(window);
	x_offset = 0.0f;
	if (env->world->cam_mod[0] >= 30.0f && env->world->cam_mod[0] <= 120.0f)
		env->world->cam_mod[0] -= y_offset;
	if (env->world->cam_mod[0] <= 30.0f)
		env->world->cam_mod[0] = 30.0f;
	if (env->world->cam_mod[0] >= 120.0f)
		env->world->cam_mod[0] = 120.0f;
}
