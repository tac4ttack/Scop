/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:49:59 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/10 16:35:37 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	mesh_rotate_self(t_scop *env, int key)
{
	if (env)
	{
		if (key == GLFW_KEY_O)
			env->world->mesh_orient = quat_mul(env->world->mesh_orient, \
										quat_rot(vec3f(1.0, 0.0, 0.0), 1.0));
		else if (key == GLFW_KEY_L)
			env->world->mesh_orient = quat_mul(env->world->mesh_orient, \
										quat_rot(vec3f(1.0, 0.0, 0.0), -1.0));
		else if (key == GLFW_KEY_K)
			env->world->mesh_orient = quat_mul(env->world->mesh_orient, \
										quat_rot(vec3f(0.0, 1.0, 0.0), 1.0));
		else if (key == GLFW_KEY_M)
			env->world->mesh_orient = quat_mul(env->world->mesh_orient, \
										quat_rot(vec3f(0.0, 1.0, 0.0), -1.0));
		else if (key == GLFW_KEY_I)
			env->world->mesh_orient = quat_mul(env->world->mesh_orient, \
										quat_rot(vec3f(0.0, 0.0, 1.0), 1.0));
		else if (key == GLFW_KEY_P)
			env->world->mesh_orient = quat_mul(env->world->mesh_orient, \
										quat_rot(vec3f(0.0, 0.0, 1.0), -1.0));
		return (true);
	}
	return (error_bool("[ERROR mesh_rotate_self]\tNULL Scop pointer!\n"));
}


/*
bool	mesh_rotate_self(t_scop *env, int key)
{
	if (env)
	{
		if (key == GLFW_KEY_O)
			env->world->mesh_euler[0] += 1.0;
		else if (key == GLFW_KEY_L)
			env->world->mesh_euler[0] -= 1.0;
		else if (key == GLFW_KEY_K)
			env->world->mesh_euler[1] += 1.0;
		else if (key == GLFW_KEY_M)
			env->world->mesh_euler[1] -= 1.0;
		else if (key == GLFW_KEY_I)
			env->world->mesh_euler[2] += 1.0;
		else if (key == GLFW_KEY_P)
			env->world->mesh_euler[2] -= 1.0;
		return (true);
	}
	return (error_bool("[ERROR mesh_rotate_self]\tNULL Scop pointer!\n"));
}
*/
