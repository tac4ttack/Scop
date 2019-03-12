/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:49:59 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/12 10:50:59 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	mesh_rotate_self(t_scop *env, int key)
{
	if (env)
	{
		if (key == GLFW_KEY_HOME)
			env->mat->mesh_euler[0] += 1.0;
		else if (key == GLFW_KEY_END)
			env->mat->mesh_euler[0] -= 1.0;
		else if (key == GLFW_KEY_DELETE)
			env->mat->mesh_euler[1] += 1.0;
		else if (key == GLFW_KEY_PAGE_DOWN)
			env->mat->mesh_euler[1] -= 1.0;
		else if (key == GLFW_KEY_F13)
			env->mat->mesh_euler[2] += 1.0;
		else if (key == GLFW_KEY_F15)
			env->mat->mesh_euler[2] -= 1.0;
		env->mat->mesh_euler[0] = (env->mat->mesh_euler[0] < 0.0 ? 359.0 : env->mat->mesh_euler[0]);
		env->mat->mesh_euler[0] = (env->mat->mesh_euler[0] > 360.0 ? 1.0 : env->mat->mesh_euler[0]);
		env->mat->mesh_euler[1] = (env->mat->mesh_euler[1] < 0.0 ? 359.0 : env->mat->mesh_euler[1]);
		env->mat->mesh_euler[1] = (env->mat->mesh_euler[1] > 360.0 ? 1.0 : env->mat->mesh_euler[1]);
		env->mat->mesh_euler[2] = (env->mat->mesh_euler[2] < 0.0 ? 359.0 : env->mat->mesh_euler[2]);
		env->mat->mesh_euler[2] = (env->mat->mesh_euler[2] > 360.0 ? 1.0 : env->mat->mesh_euler[2]);
		env->mat->rotation = quat_2_mat4(quat_euler(env->mat->mesh_euler[0], \
								env->mat->mesh_euler[1], env->mat->mesh_euler[2]));
		return (true);
	}
	return (false);
}
