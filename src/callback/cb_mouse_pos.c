/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_mouse_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 11:25:42 by fmessina          #+#    #+#             */
/*   Updated: 2019/07/01 11:30:30 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		cb_mouse_pos(GLFWwindow *window, \
						double xpos, \
						double ypos)
{
	t_scop	*env;
	float	mouse_pos[4];

	env = glfwGetWindowUserPointer(window);
	mouse_pos[0] = env->mouse->rot_speed * \
		(2.0f * env->mouse->last[0] - env->win_res[0]) / (float)env->win_res[0];
	mouse_pos[1] = env->mouse->rot_speed * \
		(env->win_res[1] - 2.0f * env->mouse->last[1]) / (float)env->win_res[1];
	mouse_pos[2] = env->mouse->rot_speed * \
		(2.0f * (float)xpos - env->win_res[0]) / (float)env->win_res[0];
	mouse_pos[3] = env->mouse->rot_speed * \
		(env->win_res[1] - 2.0f * (float)ypos) / (float)env->win_res[1];
	if (env->mouse->lmb)
	{
		input_mouse_rot(&env->mouse->prev, mouse_pos);
		env->world->mesh_orient = quat_mul(env->world->mesh_orient, \
											env->mouse->prev);
	}
	env->mouse->last[0] = xpos;
	env->mouse->last[1] = ypos;
}
