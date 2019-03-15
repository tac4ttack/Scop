/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 11:54:23 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/15 15:04:20 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool	world_update_model(t_scop *env)
{
	if (env)
	{
		env->world->mesh_translation = mat4_set_translation( \
										env->world->mesh_position);
		env->world->mesh_orientation = quat_euler(env->world->mesh_euler[0], \
													env->world->mesh_euler[1], \
													env->world->mesh_euler[2]);
		env->world->mesh_rotation = quat_2_mat4(env->world->mesh_orientation);
		env->world->mesh_scale = mat4_set_scale(env->world->mesh_scaler);
		env->world->model = mat4_mul(mat4_mul(
									env->world->mesh_scale, \
									env->world->mesh_rotation), \
									env->world->mesh_translation);
		return (true);
	}
	return (error_bool("[ERROR world_update_model]\tNULL Scop pointer!\n"));
}

bool	world_update(t_scop *env)
{
	if (env)
	{
		if (!(world_update_model(env)))
			return (error_bool("[ERROR world_update]\t" \
			"Could not update model matrix!\n"));

		env->world->view = mat4_set_lookat(env->world->cam_position, \
										env->world->cam_front, \
										env->world->cam_up);

		env->world->projection = mat4_set_perspective(env->world->cam_mod[0], \
													env->win_res[2], \
													env->world->cam_mod[1], \
													env->world->cam_mod[2]);

		env->world->mvp = mat4_mul(mat4_mul(env->world->model, \
		 									env->world->view), \
		 									env->world->projection);
		return (true);
	}
	return (error_bool("[ERROR world_update]\tNULL Scop pointer!\n"));
}
