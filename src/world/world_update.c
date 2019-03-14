/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 11:54:23 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/14 11:57:48 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	world_update(t_scop *env)
{
	if (env)
	{
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
	return (error_bool("[ERROR world_update]\tNULL Scop pointer!\n"));
}
