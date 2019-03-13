/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:59:10 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/13 16:21:01 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool	init_world_cam(t_scop *env)
{
	if (env)
	{
		env->world->cam_mod[0] = FOV;
		env->world->cam_mod[1] = NEAR;
		env->world->cam_mod[2] = FAR;
		env->world->cam_speed = 0.05f;
		env->world->cam_position = vec3f(0.0f, 0.0f, 3.0f);
		env->world->cam_up = vec3f(0.0f, 1.0f, 0.0f);
		env->world->cam_front = vec3f(0.0f, 0.0f, -1.0f);
		env->world->world_up = env->world->cam_up;
		return (true);
	}
	return (false);
}

bool	init_world(t_scop *env)
{
	if (env)
	{
		if (!(env->world = ft_memalloc(sizeof(t_world))))
			return (error_bool("[ERROR init_world]\tCan\'t " \
			"allocate memory for world data!\n"));

		if (!(init_world_cam(env)))
			return (error_bool("[ERROR init_world]\tinit world cam failed!\n"));

		env->world->mesh_euler[0] = 45.0f;
		env->world->mesh_euler[1] = 45.0f;
		env->world->mesh_euler[2] = 0.0f;
		env->world->mesh_translation = mat4_set_identity();
		env->world->mesh_orientation = quat_euler(env->world->mesh_euler[0], \
													env->world->mesh_euler[1], \
													env->world->mesh_euler[2]);
		env->world->mesh_rotation = quat_2_mat4(env->world->mesh_orientation);
		env->world->mesh_scale = mat4_set_identity();
		env->world->model = mat4_mul( \
								mat4_mul(env->world->mesh_scale, \
										env->world->mesh_rotation), \
								env->world->mesh_translation);
		env->world->view = mat4_set_lookat(env->world->cam_position, \
										vec3f_add(env->world->cam_position, \
												env->world->cam_front), \
											env->world->cam_up);
		env->world->projection = mat4_set_perspective(env->world->cam_mod[0], \
												env->win_res[2], \
												env->world->cam_mod[1], \
												env->world->cam_mod[2]);
		env->world->mvp = mat4_mul( \
								mat4_mul(env->world->projection, \
										env->world->view), \
								env->world->model);
		return (true);
	}
	return (false);
}
