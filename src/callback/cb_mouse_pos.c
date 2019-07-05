/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_mouse_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 11:25:42 by fmessina          #+#    #+#             */
/*   Updated: 2019/07/01 12:27:46 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	fill_mouse_pos(t_scop *env, float x, float y, float *dst)
{
	dst[0] = env->mouse->rot_speed * \
		(2.0f * env->mouse->last[0] - env->win_res[0]) / (float)env->win_res[0];
	dst[1] = env->mouse->rot_speed * \
		(env->win_res[1] - 2.0f * env->mouse->last[1]) / (float)env->win_res[1];
	dst[2] = env->mouse->rot_speed * \
		(2.0f * (float)x - env->win_res[0]) / (float)env->win_res[0];
	dst[3] = env->mouse->rot_speed * \
		(env->win_res[1] - 2.0f * (float)y) / (float)env->win_res[1];
}

void		cb_mouse_pos(GLFWwindow *window, \
						double xpos, \
						double ypos)
{
	t_scop	*env;
	float	mouse_pos[4];

	env = glfwGetWindowUserPointer(window);
	fill_mouse_pos(env, xpos, ypos, (float*)&mouse_pos);
	if (env->mouse->lmb)
	{
		input_mouse_rot(&env->mouse->prev, mouse_pos);
		env->world->mesh_orient = quat_mul(env->world->mesh_orient, \
											env->mouse->prev);
	}
	else if (env->mouse->rmb)
	{
		env->world->mesh_position.x += env->mouse->tra_speed * \
			((float)xpos - env->mouse->last[0]) / (float)env->win_res[0];
		env->world->mesh_position.y -= env->mouse->tra_speed * \
			((float)ypos - env->mouse->last[1]) / (float)env->win_res[1];
	}
	else if (env->mouse->mmb)
	{
		env->world->mesh_position.z -= env->mouse->tra_speed * \
			((float)ypos - env->mouse->last[1]) / (float)env->win_res[1];
	}
	env->mouse->last[0] = xpos;
	env->mouse->last[1] = ypos;
}
