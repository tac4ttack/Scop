/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:49:59 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/13 16:23:37 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	mesh_rotate_self(t_scop *env, int key)
{
	if (env)
	{
		if (key == GLFW_KEY_HOME)
			env->world->mesh_euler[0] += 1.0;
		else if (key == GLFW_KEY_END)
			env->world->mesh_euler[0] -= 1.0;
		else if (key == GLFW_KEY_DELETE)
			env->world->mesh_euler[1] += 1.0;
		else if (key == GLFW_KEY_PAGE_DOWN)
			env->world->mesh_euler[1] -= 1.0;
		else if (key == GLFW_KEY_F13)
			env->world->mesh_euler[2] += 1.0;
		else if (key == GLFW_KEY_F15)
			env->world->mesh_euler[2] -= 1.0;
		env->world->mesh_euler[0] = (env->world->mesh_euler[0] < 0.0 ? 359.0 : env->world->mesh_euler[0]);
		env->world->mesh_euler[0] = (env->world->mesh_euler[0] > 360.0 ? 1.0 : env->world->mesh_euler[0]);
		env->world->mesh_euler[1] = (env->world->mesh_euler[1] < 0.0 ? 359.0 : env->world->mesh_euler[1]);
		env->world->mesh_euler[1] = (env->world->mesh_euler[1] > 360.0 ? 1.0 : env->world->mesh_euler[1]);
		env->world->mesh_euler[2] = (env->world->mesh_euler[2] < 0.0 ? 359.0 : env->world->mesh_euler[2]);
		env->world->mesh_euler[2] = (env->world->mesh_euler[2] > 360.0 ? 1.0 : env->world->mesh_euler[2]);
		env->world->mesh_orientation = quat_euler(env->world->mesh_euler[0], \
								env->world->mesh_euler[1], env->world->mesh_euler[2]);
		return (true);
	}
	return (false);
}
