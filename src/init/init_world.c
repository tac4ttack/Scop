/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:59:10 by fmessina          #+#    #+#             */
/*   Updated: 2019/03/18 15:12:35 by fmessina         ###   ########.fr       */
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
		env->world->cam_speed = 0.5f;
		env->world->cam_position = vec3f(0.0f, 0.0f, 10.0f);
		env->world->cam_up = vec3f(0.0f, 1.0f, 0.0f);
		env->world->cam_front = vec3f(0.0f, 0.0f, -1.0f);
		env->world->world_up = env->world->cam_up;
		return (true);
	}
	return (error_bool("[ERROR init_world_cam]\tNULL Scop pointer!\n"));
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

		env->world->mesh_scaler = vec3f(1.0, 1.0, 1.0);
		env->world->mesh_translation = mat4_set_identity();
		env->world->mesh_orient = quat_set_identity();
		env->world->mesh_rotation = mat4_set_identity();
		env->world->mesh_scale = mat4_set_identity();
		if (!world_update(env))
			return (error_bool("[ERROR init_world]\tCould not init MVP!\n"));

		ft_putendl("\nmodel");
		mat4_print(env->world->model);

		ft_putendl("\nview");
		mat4_print(env->world->view);

		ft_putendl("\nmodel/view");
		mat4_print(mat4_mul(env->world->model, env->world->view));

		ft_putendl("\nprojection");
		mat4_print(env->world->projection);

		ft_putendl("\nmodel/view/projection");
		mat4_print(env->world->mvp);
		// else
			return (true);
	}
	return (error_bool("[ERROR init_world]\tNULL Scop pointer!\n"));
}
